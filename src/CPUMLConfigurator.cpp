#include "CPUMLConfigurator.h"
#include <iostream>
#include <fstream>

namespace fsmEngine
{

CPUMLConfigurator::CPUMLConfigurator( const std::string& filename )
: m_pumlFile( filename )
, m_initialState("^\\s*\\[\\*\\]\\s*-->([a-zA-Z0-9_\\s]+)$")
, m_transition("^([a-zA-Z0-9_\\(\\)\\s]+)->([a-zA-Z0-9_\\(\\)\\s]+):([a-zA-Z0-9_\\s]+)$")
, m_stateOnEnter("([a-zA-Z0-9_\\(\\)]+)\\s+:\\s+OnEnter:([a-zA-Z0-9_\\(\\)\\s]+)")
, m_stateOnExit("([a-zA-Z0-9_\\(\\)]+)\\s+:\\s+OnExit:([a-zA-Z0-9_\\(\\)\\s]+)")
, m_stateOnLeaf("([a-zA-Z0-9_\\(\\)]+)\\s+:\\s+OnLeaf:([a-zA-Z0-9_\\(\\)\\s]+)")
, m_internalTransitionNoCondition("([a-zA-Z0-9_\\(\\)]+)\\s+:\\s+([a-zA-Z0-9_\\(\\)\\s]+):\\s*\\(\\s*([a-zA-Z0-9_\\(\\)\\s]+)\\s*\\)")
, m_internalTransitionWithCondition("([a-zA-Z0-9_\\(\\)]+)\\s+:\\s+([a-zA-Z0-9_\\(\\)\\s]+):\\s*\\[\\s*([a-zA-Z0-9_\\(\\)\\s]+)\\s*\\]\\(\\s*([a-zA-Z0-9_\\(\\)\\s]+)\\s*\\)")
, m_openingParentState("state\\s+([a-zA-Z0-9]+)\\s+{\\s*$")
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
        m_initialStateName = match[1];
      }
      else if ( std::regex_search(pumlLine ,match, m_stateOnExit) )
      {
        m_initialStateName = match[1];
      }
      else if ( std::regex_search(pumlLine ,match, m_stateOnLeaf) )
      {
        m_initialStateName = match[1];
      }
      else if ( std::regex_search(pumlLine ,match, m_initialState) )
      {
        m_initialStateName = match[1];
      }
    }
  }

  FlushFSMModel();

  return retVal;
}

CPUMLConfigurator::tStateIter CPUMLConfigurator::getStateByName( const std::string& stateName )
{
  tStateIter stateIterator = m_statesMap.find(stateName); 

  if ( m_statesMap.end() != stateIterator )
  {
    sState newStateRecord;
    newStateRecord.StateName = stateName;

    auto [ stateIterator, result ] = m_statesMap.insert( tStateMap::value_type( stateName, newStateRecord));
  }

  return stateIterator;
}

void CPUMLConfigurator::FlushFSMModel() const
{
  for (const auto& statePair : m_statesMap )
  {
    const auto& state = statePair.second;
    std::cout << "----------------------------------------------------------"<< std::endl;
    std::cout << "Parent: "<< state.ParentName << std::endl;
    std::cout << "Name: "<< state.StateName << std::endl;
    std::cout << "Enter: " << state.EnterActionName << std::endl;
    std::cout << "Leaf: " << state.LeafActionName << std::endl;
    std::cout << "Exit: " << state.ExitActionName << std::endl;
  }

  std::cout << "Initial State: " << m_initialStateName << std::endl;
}



};