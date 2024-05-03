#pragma once
#include <map>
#include <list>
#include "IFSMBuilder.h"
#include <queue>

namespace fsmEngine
{

class IActionFactory;
class IFSMConfigurator;
class CState;

class CStateMachine : public IFSMBuilder
{
	typedef std::map<uint32_t, CState*> tStateMap;
	typedef tStateMap::const_iterator tStateMapConstIterator;
	typedef tStateMap::iterator tStateMapIterator;
	
	typedef std::list<CState*> tStateList;
	typedef tStateList::iterator tStateListIterator;
	typedef tStateList::reverse_iterator tStateListReverseIterator;

	typedef std::queue<std::string> tEventsQueue;
	
	
public:
	CStateMachine();
	virtual ~CStateMachine();
	
	bool Initialize( IFSMConfigurator* pConfigurator, IActionFactory* pFactory);
	
	bool DispatchEvent( const std::string& eventName );

private:

	/** implementation of fsmEngine::IFSMBuilder */
	virtual void AddState(const std::string& parent, 
												const std::string& stateName, 
												const std::string& enterActionName, 
												const std::string& leafActionName, 
												const std::string& exitActioName);
	
	virtual void AddTransition(	const std::string& eventName,
															const std::string& sourceStateName, 
															const std::string& destinationStateName, 
															const std::string& conditionName, 
															const std::string& actionName);
															
	virtual void SetInitialState( const std::string& initialState);
	
private:
	bool ProcessEvent( const std::string& eventName);

	
private:
	CStateMachine(const CStateMachine&);
	CStateMachine& operator=(const CStateMachine&);
	
	IActionFactory* m_pActionFactory;
	
	tStateMap m_stateMap;
	
	CState* m_pCurrentState;

	bool m_transitionInProgress;

	tEventsQueue m_eventsQueue;
};
}