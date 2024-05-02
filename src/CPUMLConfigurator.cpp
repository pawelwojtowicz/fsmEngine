#include "CPUMLConfigurator.h"
#include <iostream>
#include <fstream>
#include <string>

namespace fsmEngine
{

CPUMLConfigurator::CPUMLConfigurator( const std::string& filename )
: m_pumlFile( filename )
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
    }
  }



  return retVal;
}


}