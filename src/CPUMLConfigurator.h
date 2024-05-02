#pragma once
#include <string>
#include <list>
#include <stack>
#include <regex>

#include "ICSMConfigurator.h"

namespace fsmEngine
{
class CPUMLConfigurator : public ICSMConfigurator
{
  struct sState
	{
		std::string ParentName      = {};
		std::string StateName       = {};
		std::string EnterActionName = {};
		std::string LeafActionName  = {};
		std::string ExitActionName  = {};
	};

  struct sTransition
  {
    std::string EventName             = {};
		std::string SourceStateName       = {};
		std::string DestinationStateName  = {};
		std::string ConditionName         = {}; 
		std::string ActionName            = {};
  };

  using tStateMap = std::map<std::string, sState>;
  using tStateIter = tStateMap::iterator;

  using tTransitionList = std::list<sTransition>;

  using tParentStack = std::stack<std::string>;
public:

  CPUMLConfigurator( const std::string& filename );
  virtual ~CPUMLConfigurator() = default;

private:
  virtual bool InitializeStateMachine( ICSMBuilder& pBuilder ) override;

  void FlushFSMModel( ICSMBuilder& pBuilder ) const;

  tStateIter getStateByName( const std::string& stateName );

private:


  std::string m_pumlFile;

  std::regex m_initialState;
  std::regex m_transition;
  std::regex m_transitionWithAct;
  std::regex m_transitionWithCnd;
  std::regex m_transitionWithCndAndAct;
  std::regex m_stateOnEnter;
  std::regex m_stateOnExit;
  std::regex m_stateOnLeaf;
  std::regex m_internalTransitionNoCondition;
  std::regex m_internalTransitionWithCondition;
  std::regex m_openingParentState;
  std::regex m_closingParentState;

  tStateMap m_statesMap;

  tTransitionList m_transitions;

  tParentStack m_parentStack;

  std::string m_initialStateName;
};
}