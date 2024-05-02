#pragma once
#include <string>
#include <regex>

#include "ICSMConfigurator.h"

namespace fsmEngine
{
class CPUMLConfigurator : ICSMConfigurator
{
  struct sState
	{
		std::string ParentName      = {};
		std::string StateName       = {};
		std::string EnterActionName = {};
		std::string LeafActionName  = {};
		std::string ExitActionName  = {};
	};

  using tStateMap = std::map<std::string, sState>;
  using tStateIter = tStateMap::iterator;
public:

  CPUMLConfigurator( const std::string& filename );
  virtual ~CPUMLConfigurator() = default;

private:
  virtual bool InitializeStateMachine( ICSMBuilder* pBuilder ) override;

  void FlushFSMModel() const;

  tStateIter getStateByName( const std::string& stateName );

private:


  std::string m_pumlFile;

  std::regex m_initialState;
  std::regex m_transition;
  std::regex m_stateOnEnter;
  std::regex m_stateOnExit;
  std::regex m_stateOnLeaf;
  std::regex m_internalTransitionNoCondition;
  std::regex m_internalTransitionWithCondition;
  std::regex m_openingParentState;
  std::regex m_closingParentState;

  tStateMap m_statesMap;

  std::string m_initialStateName;
};
}