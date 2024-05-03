#pragma once
#include <string>
#include <memory>

namespace fsmEngine
{
class IAction;
class ICondition;
class CState;

class CTransition
{
public:
	CTransition( const std::string& name, std::shared_ptr<ICondition> pCondition, std::shared_ptr<IAction> pAction, std::shared_ptr<CState> pTargetState);
	virtual ~CTransition();
	
	std::shared_ptr<CState> GetTargetState();
	
	bool CanExecute();
	
	void ExecuteAction();
	
private:
	std::string m_eventName;

	std::shared_ptr<ICondition> m_pCondition;
	
	std::shared_ptr<IAction> m_pAction;
	
	std::shared_ptr<CState> m_pTargetState;
};

}