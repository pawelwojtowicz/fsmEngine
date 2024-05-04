#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <CActionFactory.h>
#include <CGenericAction.h>
#include <CGenericCondition.h>
#include <CStateMachine.h>
#include <CPUMLConfigurator.h>
#include "ITestInterface.h"
#include <memory>

using ::testing::Return;
using ::testing::Sequence;
using ::testing::InvokeWithoutArgs;

void InitializeSMActionFactory( fsmEngine::CActionFactory& actionFactory, TestOperationsMock* pMockPointer)
{
	actionFactory.AddAction("OperationA", std::make_shared<fsmEngine::CGenericAction<ITestInterface>>( pMockPointer, &ITestInterface::OperationA ));
	actionFactory.AddAction("OperationB", std::make_shared<fsmEngine::CGenericAction<ITestInterface>>( pMockPointer, &ITestInterface::OperationB ));
	actionFactory.AddAction("OperationC", std::make_shared<fsmEngine::CGenericAction<ITestInterface>>( pMockPointer, &ITestInterface::OperationC ));
	actionFactory.AddAction("OperationD", std::make_shared<fsmEngine::CGenericAction<ITestInterface>>( pMockPointer, &ITestInterface::OperationD ));
	actionFactory.AddAction("OperationE", std::make_shared<fsmEngine::CGenericAction<ITestInterface>>( pMockPointer, &ITestInterface::OperationE ));
	actionFactory.AddAction("OperationF", std::make_shared<fsmEngine::CGenericAction<ITestInterface>>( pMockPointer, &ITestInterface::OperationF ));
	actionFactory.AddAction("OperationG", std::make_shared<fsmEngine::CGenericAction<ITestInterface>>( pMockPointer, &ITestInterface::OperationG ));
	actionFactory.AddAction("OperationH", std::make_shared<fsmEngine::CGenericAction<ITestInterface>>( pMockPointer, &ITestInterface::OperationH ));
	
	actionFactory.AddCondition( "Condition1", std::make_shared<fsmEngine::CGenericCondition<ITestInterface>>( pMockPointer, &ITestInterface::Condition1));
	actionFactory.AddCondition( "Condition2", std::make_shared<fsmEngine::CGenericCondition<ITestInterface>>( pMockPointer, &ITestInterface::Condition2));
	actionFactory.AddCondition( "Condition3", std::make_shared<fsmEngine::CGenericCondition<ITestInterface>>( pMockPointer, &ITestInterface::Condition3));
	actionFactory.AddCondition( "Condition4", std::make_shared<fsmEngine::CGenericCondition<ITestInterface>>( pMockPointer, &ITestInterface::Condition4));
	actionFactory.AddCondition( "Condition5", std::make_shared<fsmEngine::CGenericCondition<ITestInterface>>( pMockPointer, &ITestInterface::Condition5));
	actionFactory.AddCondition( "Condition6", std::make_shared<fsmEngine::CGenericCondition<ITestInterface>>( pMockPointer, &ITestInterface::Condition6));
	actionFactory.AddCondition( "Condition7", std::make_shared<fsmEngine::CGenericCondition<ITestInterface>>( pMockPointer, &ITestInterface::Condition7));
	actionFactory.AddCondition( "Condition8", std::make_shared<fsmEngine::CGenericCondition<ITestInterface>>( pMockPointer, &ITestInterface::Condition8));	
}

TEST( CStateMachine, BasicTest)
{
	// action/condition mocks
	fsmEngine::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	InitializeSMActionFactory(actionFactory,&operationsMock);

  std::string filename("fsmExamples/puml/basicFSM.puml");
  fsmEngine::CPUMLConfigurator fsmConfigurator( filename );

  fsmEngine::CStateMachine stateMachine(actionFactory);
  stateMachine.Initialize( fsmConfigurator );
	
	
	EXPECT_CALL(	operationsMock, OperationC());
	EXPECT_CALL(	operationsMock, OperationD());
	EXPECT_CALL(	operationsMock, OperationE());
	
	EXPECT_TRUE(stateMachine.DispatchEvent("GoFurther"));
	
  EXPECT_CALL(	operationsMock, OperationF());
	EXPECT_CALL(	operationsMock, OperationA());
	EXPECT_CALL(	operationsMock, OperationB());

	EXPECT_TRUE(stateMachine.DispatchEvent("GoFurther"));
}

TEST( CStateMachine, TransitionsWithActions)
{
	// action/condition mocks
	fsmEngine::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	InitializeSMActionFactory(actionFactory,&operationsMock);

  std::string filename("fsmExamples/puml/transitionsWithActions.puml");
  fsmEngine::CPUMLConfigurator fsmConfigurator( filename );

  fsmEngine::CStateMachine stateMachine(actionFactory);
  stateMachine.Initialize( fsmConfigurator );
	
	
	EXPECT_CALL(	operationsMock, OperationC());
  EXPECT_CALL(	operationsMock, OperationG());
	EXPECT_CALL(	operationsMock, OperationD());
	EXPECT_CALL(	operationsMock, OperationE());
	
	EXPECT_TRUE(stateMachine.DispatchEvent("GoFurther"));
	
  EXPECT_CALL(	operationsMock, OperationF());
  EXPECT_CALL(	operationsMock, OperationH());
	EXPECT_CALL(	operationsMock, OperationA());
	EXPECT_CALL(	operationsMock, OperationB());

	EXPECT_TRUE(stateMachine.DispatchEvent("GoFurther"));
}

TEST( CStateMachine, TransitionsWithActionsAndConditions_1)
{
	// action/condition mocks
	fsmEngine::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	InitializeSMActionFactory(actionFactory,&operationsMock);

  std::string filename("fsmExamples/puml/transitionsWithActionsAndConditions.puml");
  fsmEngine::CPUMLConfigurator fsmConfigurator( filename );

  fsmEngine::CStateMachine stateMachine(actionFactory);
  stateMachine.Initialize( fsmConfigurator );
	
  EXPECT_CALL(	operationsMock, Condition1()).WillOnce(Return(true));
	EXPECT_CALL(	operationsMock, OperationC());
  EXPECT_CALL(	operationsMock, OperationG());
	EXPECT_CALL(	operationsMock, OperationD());
	EXPECT_CALL(	operationsMock, OperationE());
	
	EXPECT_TRUE(stateMachine.DispatchEvent("GoFurther"));
	
  EXPECT_CALL(	operationsMock, Condition2()).WillOnce(Return(true));
  EXPECT_CALL(	operationsMock, OperationF());
  EXPECT_CALL(	operationsMock, OperationH());
	EXPECT_CALL(	operationsMock, OperationA());
	EXPECT_CALL(	operationsMock, OperationB());

	EXPECT_TRUE(stateMachine.DispatchEvent("GoFurther"));
}

TEST( CStateMachine, TransitionsWithActionsAndConditions_2)
{
	// action/condition mocks
	fsmEngine::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	InitializeSMActionFactory(actionFactory,&operationsMock);

  std::string filename("fsmExamples/puml/transitionsWithActionsAndConditions.puml");
  fsmEngine::CPUMLConfigurator fsmConfigurator( filename );

  fsmEngine::CStateMachine stateMachine(actionFactory);
  stateMachine.Initialize( fsmConfigurator );
	
  EXPECT_CALL(	operationsMock, Condition1()).WillOnce(Return(false));
	EXPECT_CALL(	operationsMock, OperationC()).Times(0);
  EXPECT_CALL(	operationsMock, OperationG()).Times(0);
	EXPECT_CALL(	operationsMock, OperationD()).Times(0);
	EXPECT_CALL(	operationsMock, OperationE()).Times(0);
	
	EXPECT_TRUE(stateMachine.DispatchEvent("GoFurther"));
	
  EXPECT_CALL(	operationsMock, Condition1()).WillOnce(Return(false));
  EXPECT_CALL(	operationsMock, Condition2()).Times(0);
  EXPECT_CALL(	operationsMock, OperationF()).Times(0);
  EXPECT_CALL(	operationsMock, OperationH()).Times(0);
	EXPECT_CALL(	operationsMock, OperationA()).Times(0);
	EXPECT_CALL(	operationsMock, OperationB()).Times(0);

	EXPECT_TRUE(stateMachine.DispatchEvent("GoFurther"));
}

TEST( CStateMachine, InternalTransition_1 )
{
	// action/condition mocks
	fsmEngine::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	InitializeSMActionFactory(actionFactory,&operationsMock);

  std::string filename("fsmExamples/puml/internalTransition.puml");
  fsmEngine::CPUMLConfigurator fsmConfigurator( filename );

  fsmEngine::CStateMachine stateMachine(actionFactory);
  stateMachine.Initialize( fsmConfigurator );
	
  EXPECT_CALL(	operationsMock, Condition1()).WillOnce(Return(false));
	EXPECT_CALL(	operationsMock, OperationA()).Times(1);
  EXPECT_CALL(	operationsMock, OperationB()).Times(0);
	EXPECT_CALL(	operationsMock, OperationC()).Times(0);
	EXPECT_CALL(	operationsMock, OperationD()).Times(0);
	
	EXPECT_TRUE(stateMachine.DispatchEvent("FireAction1"));
  EXPECT_TRUE(stateMachine.DispatchEvent("FireAction2"));
	
}

TEST( CStateMachine, InternalTransition_2 )
{
	// action/condition mocks
	fsmEngine::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	InitializeSMActionFactory(actionFactory,&operationsMock);

  std::string filename("fsmExamples/puml/internalTransition.puml");
  fsmEngine::CPUMLConfigurator fsmConfigurator( filename );

  fsmEngine::CStateMachine stateMachine(actionFactory);
  stateMachine.Initialize( fsmConfigurator );
	
  EXPECT_CALL(	operationsMock, Condition1()).WillOnce(Return(true));
	EXPECT_CALL(	operationsMock, OperationA()).Times(1);
  EXPECT_CALL(	operationsMock, OperationB()).Times(1);
	EXPECT_CALL(	operationsMock, OperationC()).Times(0);
	EXPECT_CALL(	operationsMock, OperationD()).Times(0);
	
	EXPECT_TRUE(stateMachine.DispatchEvent("FireAction1"));
  EXPECT_TRUE(stateMachine.DispatchEvent("FireAction2"));
	
}

TEST( CStateMachine, InternalTransition_3 )
{
	// action/condition mocks
	fsmEngine::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	InitializeSMActionFactory(actionFactory,&operationsMock);

  std::string filename("fsmExamples/puml/internalTransition.puml");
  fsmEngine::CPUMLConfigurator fsmConfigurator( filename );

  fsmEngine::CStateMachine stateMachine(actionFactory);
  stateMachine.Initialize( fsmConfigurator );
	
  EXPECT_CALL(	operationsMock, Condition1()).Times(0);
  EXPECT_CALL(	operationsMock, Condition2()).Times(0);
	EXPECT_CALL(	operationsMock, OperationA()).Times(0);
  EXPECT_CALL(	operationsMock, OperationB()).Times(0);
	EXPECT_CALL(	operationsMock, OperationC()).Times(0);
	EXPECT_CALL(	operationsMock, OperationD()).Times(0);
  EXPECT_CALL(	operationsMock, OperationG()).Times(1);
	
	EXPECT_TRUE(stateMachine.DispatchEvent("GoFurther"));	

  EXPECT_CALL(	operationsMock, Condition1()).Times(0);
  EXPECT_CALL(	operationsMock, Condition2()).Times(0);
	EXPECT_CALL(	operationsMock, OperationA()).Times(0);
  EXPECT_CALL(	operationsMock, OperationB()).Times(0);
	EXPECT_CALL(	operationsMock, OperationC()).Times(1);
	EXPECT_CALL(	operationsMock, OperationD()).Times(0);
  EXPECT_CALL(	operationsMock, OperationG()).Times(0);

  EXPECT_TRUE( stateMachine.DispatchEvent("FireAction2"));

  EXPECT_CALL(	operationsMock, Condition1()).Times(0);
  EXPECT_CALL(	operationsMock, Condition2()).WillOnce(Return(true));
	EXPECT_CALL(	operationsMock, OperationA()).Times(0);
  EXPECT_CALL(	operationsMock, OperationB()).Times(0);
	EXPECT_CALL(	operationsMock, OperationC()).Times(0);
	EXPECT_CALL(	operationsMock, OperationD()).Times(1);
  EXPECT_CALL(	operationsMock, OperationG()).Times(0);

  EXPECT_TRUE( stateMachine.DispatchEvent("FireAction1"));

}