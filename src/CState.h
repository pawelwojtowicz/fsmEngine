#pragma once
#include <string>
#include <map>
namespace fsmEngine
{
class IAction;
class CTransition;

class CState
{
	typedef std::multimap<uint32_t, CTransition*> tTransitionMap;
	typedef tTransitionMap::iterator tTranstionIterator;
	
public:
	CState( CState* pParentState, const std::string& stateName, IAction* enterAction, IAction* leafAction, IAction* exitAction);
	virtual ~CState();
	
	void UpdateState(CState* pParentState, IAction* enterAction, IAction* leafAction, IAction* exitAction);
	
	
	const std::string& GetName() const;
	
	CState* GetParent() const;
	
	void ExecuteEnterAction();
	void ExecuteLeafAction();
	void ExecuteExitAction();
	
	
	void AddTransition( const uint32_t eventNameHash, CTransition* pTransition );
	
	CTransition* GetTransition( const uint32_t eventNameHash );

private:
	CState* m_pParentState;

	std::string m_stateName;
	
	IAction* m_pEnterAction;
	
	IAction* m_pLeafAction;
	
	IAction* m_pExitAction;
	
	tTransitionMap m_nameHashToTransitionMap;
};
}