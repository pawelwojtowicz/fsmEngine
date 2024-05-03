#include "CState.h"
#include "IAction.h"
#include "CTransition.h"

namespace fsmEngine
{
CState::CState( std::shared_ptr<CState> pParentState, const std::string& stateName, std::shared_ptr<IAction> enterAction, std::shared_ptr<IAction> leafAction, std::shared_ptr<IAction> exitAction)
: m_pParentState(pParentState)
, m_stateName(stateName)
, m_pEnterAction(enterAction)
, m_pLeafAction(leafAction)
, m_pExitAction(exitAction)	
{
}
	
CState::~CState()
{
}

void CState::UpdateState(std::shared_ptr<CState> pParentState, std::shared_ptr<IAction> enterAction, std::shared_ptr<IAction> leafAction, std::shared_ptr<IAction> exitAction)
{
	m_pParentState = pParentState;
	m_pEnterAction = enterAction;
  m_pLeafAction = leafAction;
  m_pExitAction = exitAction;
}


const std::string& CState::GetName() const
{
	return m_stateName;
}

std::shared_ptr<CState> CState::GetParent() const
{
	return m_pParentState;
}

void CState::AddTransition( const uint32_t eventNameHash, std::shared_ptr<CTransition> pTransition )
{
	m_nameHashToTransitionMap.insert( tTransitionMap::value_type(eventNameHash, pTransition));
}
	
void CState::ExecuteEnterAction()
{
	if ( m_pEnterAction )
	{
		//LOG(DATA, ("CSM[]: State:[%s] - Executing ENTER action [%s]", m_stateName.c_str(), m_pEnterAction->GetName().c_str()));
		m_pEnterAction->Execute();
	}
}

void CState::ExecuteLeafAction()
{
	if ( m_pLeafAction )
	{
//		LOG(DATA, ("CSM[]: State:[%s] - Executing LEAF action [%s]", m_stateName.c_str(), m_pLeafAction->GetName().c_str()));
		m_pLeafAction->Execute();
	}
}

void CState::ExecuteExitAction()
{
	if ( m_pExitAction )
	{
//		LOG(DATA, ("CSM[]: State:[%s] - Executing EXIT action [%s]", m_stateName.c_str(), m_pExitAction->GetName().c_str()));
		m_pExitAction->Execute();
	}
}

std::shared_ptr<CTransition> CState::GetTransition( const uint32_t eventNameHash )
{
	tTranstionIterator beginIter( m_nameHashToTransitionMap.lower_bound( eventNameHash) );
	tTranstionIterator endIter( m_nameHashToTransitionMap.upper_bound( eventNameHash ) );
																							
	for ( ; beginIter != endIter ; ++beginIter)
	{
		if ( beginIter->second->CanExecute() )
		{
			return beginIter->second;
		}
	}
	
	return 0;
}


}
