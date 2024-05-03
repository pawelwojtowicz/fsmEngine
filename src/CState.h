#pragma once
#include <memory>
#include <string>
#include <map>
namespace fsmEngine
{
class IAction;
class CTransition;

class CState
{
	typedef std::multimap<uint32_t, std::shared_ptr<CTransition>> tTransitionMap;
	typedef tTransitionMap::iterator tTranstionIterator;
	
public:
	CState( std::shared_ptr<CState> pParentState, const std::string& stateName, std::shared_ptr<IAction> enterAction, std::shared_ptr<IAction> leafAction, std::shared_ptr<IAction> exitAction);
	virtual ~CState();
	
	void UpdateState(std::shared_ptr<CState> pParentState, std::shared_ptr<IAction> enterAction, std::shared_ptr<IAction> leafAction, std::shared_ptr<IAction> exitAction);
	
	
	const std::string& GetName() const;
	
	std::shared_ptr<CState> GetParent() const;
	
	void ExecuteEnterAction();
	void ExecuteLeafAction();
	void ExecuteExitAction();
	
	
	void AddTransition( const uint32_t eventNameHash, std::shared_ptr<CTransition> pTransition );
	
	std::shared_ptr<CTransition> GetTransition( const uint32_t eventNameHash );

private:
	std::shared_ptr<CState> m_pParentState;

	std::string m_stateName;
	
	std::shared_ptr<IAction> m_pEnterAction;
	
	std::shared_ptr<IAction> m_pLeafAction;
	
	std::shared_ptr<IAction> m_pExitAction;
	
	tTransitionMap m_nameHashToTransitionMap;
};

}