#include "CPUMLConfigurator.h"
#include <iostream>
#include <fstream>

namespace fsmEngine
{

CPUMLConfigurator::CPUMLConfigurator( const std::string& filename )
: m_pumlFile( filename )
, m_initialState("^\\s*\\[\\*\\]\\s*-->\\s*([a-zA-Z0-9_]+)\\s*$")
, m_transition("^([a-zA-Z0-9_\\(\\)]+)\\s*->\\s*([a-zA-Z0-9_\\(\\)]+)\\s*:\\s*([a-zA-Z0-9_]+)\\s*$")
//^([a-zA-Z0-9_\(\)]+)\s*->\s*([a-zA-Z0-9_\(\)]+)\s*:\s*([a-zA-Z0-9_]+)\s*:\s*\(([a-zA-Z0-9]+)\)$
, m_transitionWithAct("^([a-zA-Z0-9_\\(\\)]+)\\s*->\\s*([a-zA-Z0-9_\\(\\)]+)\\s*:\\s*([a-zA-Z0-9_]+)\\s*:\\s*\\(([a-zA-Z0-9]+)\\)$")
//^([a-zA-Z0-9_\(\)]+)\s*->\s*([a-zA-Z0-9_\(\)]+)\s*:\s*([a-zA-Z0-9_]+)\s*:\s*\[([a-zA-Z0-9]+)\]\s*$
, m_transitionWithCnd("^([a-zA-Z0-9_\\(\\)]+)\\s*->\\s*([a-zA-Z0-9_\\(\\)]+)\\s*:\\s*([a-zA-Z0-9_]+)\\s*:\\s*\\[([a-zA-Z0-9]+)\\]\\s*$")
//^([a-zA-Z0-9_\(\)]+)\s*->\s*([a-zA-Z0-9_\(\)]+)\s*:\s*([a-zA-Z0-9_]+)\s*:\s*\[([a-zA-Z0-9]+)\]\s*\(([a-zA-Z0-9]+)\)$
, m_transitionWithCndAndAct("^([a-zA-Z0-9_\\(\\)]+)\\s*->\\s*([a-zA-Z0-9_\\(\\)]+)\\s*:\\s*([a-zA-Z0-9_]+)\\s*:\\s*\\[([a-zA-Z0-9]+)\\]\\s*\\(([a-zA-Z0-9]+)\\)$")
, m_stateOnEnter("([a-zA-Z0-9_\\(\\)]+)\\s*:\\s+OnEnter\\s*:\\s*([a-zA-Z0-9_\\(\\)\\s]+)")
, m_stateOnExit("([a-zA-Z0-9_\\(\\)]+)\\s*:\\s+OnExit\\s*:\\s*([a-zA-Z0-9_\\(\\)\\s]+)")
, m_stateOnLeaf("([a-zA-Z0-9_\\(\\)]+)\\s+:\\s*OnLeaf\\s*:\\s*([a-zA-Z0-9_\\(\\)\\s]+)")
, m_internalTransitionNoCondition("([a-zA-Z0-9_\\(\\)]+)\\s+:\\s+([a-zA-Z0-9_\\(\\)\\s]+):\\s*\\(\\s*([a-zA-Z0-9_\\(\\)\\s]+)\\s*\\)")
, m_internalTransitionWithCondition("([a-zA-Z0-9_\\(\\)]+)\\s+:\\s+([a-zA-Z0-9_\\(\\)\\s]+):\\s*\\[\\s*([a-zA-Z0-9_\\(\\)\\s]+)\\s*\\]\\(\\s*([a-zA-Z0-9_\\(\\)\\s]+)\\s*\\)")
, m_openingParentState("state\\s+([a-zA-Z0-9]+)\\s+\\{\\s*$")
, m_closingParentState("^([}\\s*]+)$")
{

}


bool CPUMLConfigurator::InitializeStateMachine( ICSMBuilder* pBuilder )
{
  bool retVal(false);

  std::string pumlLine; 
  std::ifstream pumlFileStream( m_pumlFile );

  if ( pumlFileStream.is_open() )
  {
    while( std::getline( pumlFileStream, pumlLine ) )
    {
      std::smatch match;

      if ( std::regex_search(pumlLine ,match, m_stateOnEnter) )
      {
        const std::string& stateName( match[1]);
        const std::string& actionName( match[2]);

        auto stateIter = getStateByName(stateName);
        stateIter->second.EnterActionName = actionName;
      }
      else if ( std::regex_search(pumlLine ,match, m_stateOnExit) )
      {
        const std::string& stateName( match[1]);
        const std::string& actionName( match[2]);
        auto stateIter = getStateByName(stateName);
        stateIter->second.ExitActionName = actionName;
      }
      else if ( std::regex_search(pumlLine ,match, m_stateOnLeaf) )
      {
        const std::string& stateName( match[1]);
        const std::string& actionName( match[2]);

        auto stateIter = getStateByName(stateName);
        stateIter->second.LeafActionName = actionName;
      }
      else if ( std::regex_search(pumlLine, match, m_transition) )
      {
        const std::string& srcState( match[1]);
        getStateByName(srcState);
        const std::string& dstState( match[2]);
        getStateByName(dstState);
        const std::string& eventName( match[3]);
        sTransition transition;
        transition.SourceStateName      = srcState;
        transition.DestinationStateName = dstState;
        transition.EventName            = eventName;
        m_transitions.push_back(transition);
      }
      else if ( std::regex_search(pumlLine ,match, m_transitionWithCndAndAct) )
      {
        const std::string& srcState( match[1]);
        getStateByName(srcState);
        const std::string& dstState( match[2]);
        getStateByName(dstState);
        const std::string& eventName( match[3]);
        const std::string& condition( match[4]);
        const std::string& action( match[5]);
        sTransition transition;
        transition.SourceStateName      = srcState;
        transition.DestinationStateName = dstState;
        transition.EventName            = eventName;
        transition.ConditionName        = condition;
        transition.ActionName           = action;
        m_transitions.push_back(transition);
      }
      else if ( std::regex_search(pumlLine ,match, m_transitionWithAct) )
      {
        const std::string& srcState( match[1]);
        getStateByName(srcState);
        const std::string& dstState( match[2]);
        getStateByName(dstState);
        const std::string& eventName( match[3]);
        const std::string& action( match[4]);
        sTransition transition;
        transition.SourceStateName      = srcState;
        transition.DestinationStateName = dstState;
        transition.EventName            = eventName;
        transition.ActionName           = action;
        m_transitions.push_back(transition);
      }
      else if ( std::regex_search(pumlLine, match, m_transitionWithCnd))
      {
        const std::string& srcState( match[1]);
        getStateByName(srcState);
        const std::string& dstState( match[2]);
        getStateByName(dstState);
        const std::string& eventName( match[3]);
        const std::string& condition( match[4]);
        sTransition transition;
        transition.SourceStateName      = srcState;
        transition.DestinationStateName = dstState;
        transition.EventName            = eventName;
        transition.ConditionName        = condition;
        m_transitions.push_back(transition);

      }
      else if ( std::regex_search(pumlLine ,match, m_initialState) )
      {
        m_initialStateName = match[1];
        getStateByName(m_initialStateName);
        std::cout << "initialState "<< m_initialStateName << std::endl;
      } 
      else if ( std::regex_search( pumlLine, match, m_openingParentState))
      {
        const std::string& parentName( match[1]);
        std::cout << "ParentDetected" << parentName << std::endl;

        getStateByName(parentName);
        m_parentStack.push(parentName);
      }
      else if ( std::regex_search( pumlLine, match, m_closingParentState) )
      {
        int closingCounts( std::count_if(pumlLine.begin(), pumlLine.end(), [](auto a){ return a=='}';}));
        while( closingCounts > 0 && !m_parentStack.empty() )
        {
          std::cout << "closing Parent" <<  std::endl;

          m_parentStack.pop();
          ++closingCounts; 
        }
      }
    }
  }

  FlushFSMModel();

  return retVal;
}

CPUMLConfigurator::tStateIter CPUMLConfigurator::getStateByName( const std::string& stateName )
{
  tStateIter stateIterator = m_statesMap.find(stateName); 

  if ( m_statesMap.end() == stateIterator )
  {
    sState newStateRecord;
    newStateRecord.StateName = stateName;
    newStateRecord.ParentName = m_parentStack.empty() ? std::string("") : m_parentStack.top();
    stateIterator = m_statesMap.insert( tStateMap::value_type( stateName, newStateRecord)).first;
  }

  return stateIterator;
}

void CPUMLConfigurator::FlushFSMModel() const
{
  for (const auto& statePair : m_statesMap )
  {
    const auto& state = statePair.second;
    std::cout << "----------------------------------------------------------"<< std::endl;
    std::cout << "Parent: ["<< state.ParentName << std::endl;
    std::cout << "Name: ["<< state.StateName << std::endl;
    std::cout << "Enter: [" << state.EnterActionName << std::endl;
    std::cout << "Leaf: [" << state.LeafActionName << std::endl;
    std::cout << "Exit: [" << state.ExitActionName << std::endl;
  }

  std::cout << "Initial State: " << m_initialStateName << std::endl;
}



};