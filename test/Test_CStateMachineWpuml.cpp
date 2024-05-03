#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <CActionFactory.h>
#include <CGenericAction.h>
#include <CGenericCondition.h>
#include <CStateMachine.h>
#include <CPUMLConfigurator.h>
#include "ITestInterface.h"

using ::testing::Return;
using ::testing::Sequence;
using ::testing::InvokeWithoutArgs;

void InitializeSMActionFactory( fsmEngine::CActionFactory& actionFactory, TestOperationsMock* pMockPointer)
{
	actionFactory.AddAction("OperationA", new fsmEngine::CGenericAction<ITestInterface>( pMockPointer, &ITestInterface::OperationA ));
	actionFactory.AddAction("OperationB", new fsmEngine::CGenericAction<ITestInterface>( pMockPointer, &ITestInterface::OperationB ));
	actionFactory.AddAction("OperationC", new fsmEngine::CGenericAction<ITestInterface>( pMockPointer, &ITestInterface::OperationC ));
	actionFactory.AddAction("OperationD", new fsmEngine::CGenericAction<ITestInterface>( pMockPointer, &ITestInterface::OperationD ));
	actionFactory.AddAction("OperationE", new fsmEngine::CGenericAction<ITestInterface>( pMockPointer, &ITestInterface::OperationE ));
	actionFactory.AddAction("OperationF", new fsmEngine::CGenericAction<ITestInterface>( pMockPointer, &ITestInterface::OperationF ));
	actionFactory.AddAction("OperationG", new fsmEngine::CGenericAction<ITestInterface>( pMockPointer, &ITestInterface::OperationG ));
	actionFactory.AddAction("OperationH", new fsmEngine::CGenericAction<ITestInterface>( pMockPointer, &ITestInterface::OperationH ));
	
	actionFactory.AddCondition( "Condition1", new fsmEngine::CGenericCondition<ITestInterface>( pMockPointer, &ITestInterface::Condition1));
	actionFactory.AddCondition( "Condition2", new fsmEngine::CGenericCondition<ITestInterface>( pMockPointer, &ITestInterface::Condition2));
	actionFactory.AddCondition( "Condition3", new fsmEngine::CGenericCondition<ITestInterface>( pMockPointer, &ITestInterface::Condition3));
	actionFactory.AddCondition( "Condition4", new fsmEngine::CGenericCondition<ITestInterface>( pMockPointer, &ITestInterface::Condition4));
	actionFactory.AddCondition( "Condition5", new fsmEngine::CGenericCondition<ITestInterface>( pMockPointer, &ITestInterface::Condition5));
	actionFactory.AddCondition( "Condition6", new fsmEngine::CGenericCondition<ITestInterface>( pMockPointer, &ITestInterface::Condition6));
	actionFactory.AddCondition( "Condition7", new fsmEngine::CGenericCondition<ITestInterface>( pMockPointer, &ITestInterface::Condition7));
	actionFactory.AddCondition( "Condition8", new fsmEngine::CGenericCondition<ITestInterface>( pMockPointer, &ITestInterface::Condition8));	
}

TEST( CStateMachine, BasicTest_1)
{
	// action/condition mocks
	fsmEngine::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	InitializeSMActionFactory(actionFactory,&operationsMock);

  std::string filename("/home/pawel/fsmEngine/fsmExamples/puml/basicFSM.puml");
  fsmEngine::CPUMLConfigurator fsmConfigurator( filename );

  fsmEngine::CStateMachine stateMachine;
  stateMachine.Initialize( &fsmConfigurator, &actionFactory );
	
	
	EXPECT_CALL(	operationsMock, OperationC());
	EXPECT_CALL(	operationsMock, OperationD());
	EXPECT_CALL(	operationsMock, OperationE());
	
	EXPECT_TRUE(stateMachine.DispatchEvent("GoFurther"));
	
  EXPECT_CALL(	operationsMock, OperationF());
	EXPECT_CALL(	operationsMock, OperationA());
	EXPECT_CALL(	operationsMock, OperationB());

	EXPECT_TRUE(stateMachine.DispatchEvent("GoFurther"));
}