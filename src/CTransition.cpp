#include "CTransition.h"
#include "IAction.h"
#include "ICondition.h"
#include "CState.h"

namespace fsmEngine
{

CTransition::CTransition( const std::string& name, ICondition* pCondition, IAction* pAction, CState* pTargetState)
:	m_eventName(name)
, m_pCondition(pCondition)
, m_pAction(pAction)
, m_pTargetState(pTargetState)
{
}

CTransition::~CTransition()
{
}
	
bool CTransition::CanExecute()
{
	if ( 0 != m_pCondition )
	{
		return m_pCondition->Evaluate();
	}
	
	return true;
}
	
void CTransition::ExecuteAction()
{
	if ( 0 != m_pAction )
	{
		if (0!=m_pTargetState)
		{
/**			LOG(DATA, ("CSM[]: Transition to state:[%s]triggered by event:[%s] fires the action:[%s]", 	m_pTargetState->GetName().c_str(), 
																																																				m_eventName.c_str(), 
																																																				m_pAction->GetName().c_str()));*/
		}
		else
		{
/**			RETAILMSG(DATA, ("CSM[]: Internal transition triggered by event:[%s] fires the action:[%s]", m_eventName.c_str(), 
																																																	 m_pAction->GetName().c_str()));*/
		}
		m_pAction->Execute();
	}
}

CState* CTransition::GetTargetState()
{

	return m_pTargetState;
}

}

