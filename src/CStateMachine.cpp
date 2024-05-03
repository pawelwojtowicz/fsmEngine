#include "CStateMachine.h"
#include "IActionFactory.h"
#include "IFSMConfigurator.h"
#include "IAction.h"
#include "CState.h"
#include "CTransition.h"
#include "CFastHash.h"
#include <algorithm>
#include <stdio.h>
namespace fsmEngine
{
static const uint32_t cUInt32_CSM_HashSeed = 0x11FF;


CStateMachine::CStateMachine()
: m_pActionFactory(0)
, m_pCurrentState(0)
, m_transitionInProgress(false)
{
}

CStateMachine::~CStateMachine()
{
}
	
bool CStateMachine::Initialize( IFSMConfigurator* pConfigurator, IActionFactory* pActionFactory)
{
	m_pActionFactory = pActionFactory;
		
	if ( 0!= pConfigurator && 0 != m_pActionFactory  )
	{
		return pConfigurator->InitializeStateMachine(*this);
	}
	return false;
}


void CStateMachine::AddState(	const std::string& parentName, 
															const std::string& stateName, 
															const std::string& enterActionName, 
															const std::string& leafActionName, 
															const std::string& exitActionName)
{
	CState* pParentState(0);
	
	IAction* pEnterAction(0);
	IAction* pLeafAction(0);
	IAction* pExitAction(0);
	
	uint32_t parentNameHash(CFastHash::CalculateHash32(parentName, cUInt32_CSM_HashSeed));
	uint32_t stateNameHash(CFastHash::CalculateHash32(stateName, cUInt32_CSM_HashSeed));
	
	if ( 0 != m_pActionFactory )
	{
		if ( !enterActionName.empty() )
		{
			pEnterAction = m_pActionFactory->GetAction(enterActionName);
			if (0!=pEnterAction)
			{
				pEnterAction->SetName(enterActionName);
			}
		}
		
		if ( !leafActionName.empty() )
		{
			pLeafAction = m_pActionFactory->GetAction(leafActionName);
			if (0!=pLeafAction)
			{
				pLeafAction->SetName(leafActionName);
			}
		}
		
		if ( !exitActionName.empty() )
		{
			pExitAction = m_pActionFactory->GetAction(exitActionName);
			if (0!=pExitAction)
			{
				pExitAction->SetName(exitActionName);
			}
		}
	}
	
	if ( !parentName.empty() )
	{
		tStateMapIterator parentStateIterator( m_stateMap.find(parentNameHash) );
		if ( m_stateMap.end() != parentStateIterator )
		{
			pParentState = parentStateIterator->second;
		}
		else
		{
			pParentState = new CState( 0 , parentName, 0 , 0, 0 );
		
			m_stateMap.insert( tStateMap::value_type(parentNameHash,pParentState));
		}	
	}
	
	tStateMapIterator stateIterator(m_stateMap.find(stateNameHash));
	if ( m_stateMap.end() == stateIterator )
	{
		CState* pState = new CState( pParentState, stateName, pEnterAction, pLeafAction, pExitAction );
		m_stateMap.insert( tStateMap::value_type(stateNameHash,pState));

	}
	else
	{
		stateIterator->second->UpdateState(pParentState, pEnterAction, pLeafAction, pExitAction);
	}	
}
	
void CStateMachine::AddTransition(	const std::string& eventName,
																		const std::string& sourceStateName, 
																		const std::string& targetStateName, 
																		const std::string& conditionName, 
																		const std::string& actionName)
{
	bool internalTransition(sourceStateName == targetStateName);
	uint32_t eventNameHash(CFastHash::CalculateHash32(eventName, cUInt32_CSM_HashSeed));
	uint32_t sourceNameHash(CFastHash::CalculateHash32(sourceStateName, cUInt32_CSM_HashSeed));
	uint32_t targetNameHash(CFastHash::CalculateHash32(targetStateName, cUInt32_CSM_HashSeed));
	
	CState* pSourceState(0);
	CState* pTargetState(0);
	IAction* pTransitionAction(0);
	ICondition* pTransitionCondition(0);
	
	tStateMapConstIterator pSourceStateIter(m_stateMap.find(sourceNameHash));
	if ( m_stateMap.end() != pSourceStateIter )
	{
		pSourceState = pSourceStateIter->second;
	}
	
	if (!internalTransition)
	{
		tStateMapConstIterator pTargetStateIter(m_stateMap.find(targetNameHash));
		if ( m_stateMap.end() != pTargetStateIter )
		{
			pTargetState = pTargetStateIter->second;
		}
	}
	
	if ( 0 != pSourceState )
	{
		if ( 0 !=m_pActionFactory )
		{
			if ( !conditionName.empty() )
			{
				pTransitionCondition = m_pActionFactory->GetCondition(conditionName);
			}
		
			if ( !actionName.empty() )
			{
				pTransitionAction = m_pActionFactory->GetAction(actionName);
				if (0!=pTransitionAction)
				{
					pTransitionAction->SetName(actionName);
				}
			}
		}
		
		CTransition* pTransition = new CTransition( eventName , 
																								pTransitionCondition, 
																								pTransitionAction, 
																								pTargetState);
																								
		pSourceState->AddTransition( eventNameHash , pTransition );
	}
}

void CStateMachine::SetInitialState( const std::string& initialState)
{
	uint32_t initialStateNameHash(CFastHash::CalculateHash32(initialState, cUInt32_CSM_HashSeed));
	
	tStateMapConstIterator pInitialStateIter(m_stateMap.find(initialStateNameHash));
	if ( m_stateMap.end() != pInitialStateIter )
	{
		m_pCurrentState = pInitialStateIter->second;
	}

}

bool CStateMachine::DispatchEvent( const std::string& eventName )
{
	bool returnValue(false);
	m_eventsQueue.push(eventName);

	if (!m_transitionInProgress)
	{
		m_transitionInProgress = true;
		while( !m_eventsQueue.empty() )
		{
			returnValue = ProcessEvent( m_eventsQueue.front() );
			m_eventsQueue.pop();
		}
		m_transitionInProgress = false;
	}

	return returnValue;
}


bool CStateMachine::ProcessEvent( const std::string& eventName )
{
	uint32_t eventNameHash(CFastHash::CalculateHash32( eventName, cUInt32_CSM_HashSeed));

	if ( 0 != m_pCurrentState )
	{
		//LOG(DATA, ("CSM[]: ProcessEvent - eventName[%s] originState[%s]", eventName.c_str(),m_pCurrentState->GetName().c_str()));
		CTransition* pTransition(0);
		CState* pTransitionSrc(m_pCurrentState);
		// search for the starting from the current state, up to the root parent
		while(0!=pTransitionSrc && 0==pTransition)
		{
			pTransition = pTransitionSrc->GetTransition( eventNameHash );
			pTransitionSrc = pTransitionSrc->GetParent();
		}
		
		// there is a transition, which fits the nameHash and the condition
		if ( 0 != pTransition )
		{
			CState* pTargetState( pTransition->GetTargetState() );
			
			if (0!= pTargetState)
			{
				tStateList sourceStates;
				tStateList targetStates;
			
				//prepare the list of the parents of target and source states
				//it will be used to evaluate the set of enter/exit actions to be exeuted
				CState* pState(m_pCurrentState);
				while ( 0 != pState )
				{
					sourceStates.push_back( pState );
					pState = pState->GetParent();
				}
			
				pState = pTargetState;
				while ( 0 != pState )
				{
					targetStates.push_back( pState );
					pState = pState->GetParent();
				}
			
				// iterate through all of the source states, starting from current state
				// and execute the exit action for all of the states , that are not present
				// in the target state list.
				for ( tStateListIterator iter = sourceStates.begin() ; sourceStates.end() != iter ; ++iter)
				{
					tStateListIterator targetIter = std::find(targetStates.begin(), targetStates.end() , *iter );
					if ( targetStates.end() == targetIter )
					{
						(*iter)->ExecuteExitAction();
					}
				}
			
				// execute the transition action in the middle of the transition
				pTransition->ExecuteAction();
			
				// execute the enter action on the state and all it's parens, which were not
				// present in the origin state.
				for ( tStateListReverseIterator iter = targetStates.rbegin() ; targetStates.rend() != iter ; ++iter)
				{
					tStateListIterator sourceIter = std::find(sourceStates.begin(), sourceStates.end() , *iter );
					if ( sourceStates.end() == sourceIter )
					{
						(*iter)->ExecuteEnterAction();
					}
				}
			
				if ( m_pCurrentState != pTargetState )
				{
					//change the current state to the target of the transition
					m_pCurrentState = pTargetState;
			
					// Execute Leaf Action for the currentState in case it's different from previous one.
					m_pCurrentState->ExecuteLeafAction();
				}

//				LOG(DATA, ("CSM[]: ProcessEvent - target state [%s]", m_pCurrentState->GetName().c_str()));
			}
			else
			{
				// it's an internal transition, just fire the transition action
				pTransition->ExecuteAction();
			}
		}
		else
		{
//			LOG(DATA, ("CSM[]: State: [%s] - unhandled event:[%s]", m_pCurrentState->GetName().c_str(), eventName.c_str()));
		}
	
		return true;
	}

	return false;
}
}
