#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <CPUMLConfigurator.h>
#include <iostream>



TEST( CPUMLConfigurator, Basic )
{
  std::string filename("/home/pawel/fsmEngine/fsmExamples/puml/exampleFSM.puml");

  fsmEngine::CPUMLConfigurator fsmConfigurator( filename );
  fsmEngine::ICSMConfigurator& configuratorInterface(fsmConfigurator);
  configuratorInterface.InitializeStateMachine(0);
}
