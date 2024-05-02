#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <CActionFactory.h>
#include <CGenericAction.h>
#include <CGenericCondition.h>
#include <CStateMachine.h>
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
	
	// configurator initialization parameters
	std::string configFile(UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/CSM/CSM_testConfig_2.xmi"));
	std::string smName("SimpleActions");
	
	fsmEngine::CArgoConfigurator configurator(configFile, smName);
	fsmEngine::CStateMachine stateMachine;
	stateMachine.Initialize( &configurator, &actionFactory );
	
	EXPECT_CALL(	operationsMock, OperationC());
	EXPECT_CALL(	operationsMock, OperationB());
	EXPECT_CALL(	operationsMock, OperationF());
	
	EXPECT_TRUE(stateMachine.DispatchEvent("E_GO"));
	
	EXPECT_CALL(	operationsMock, OperationD());
	EXPECT_CALL(	operationsMock, OperationA());
	EXPECT_CALL(	operationsMock, OperationE());
	EXPECT_TRUE(stateMachine.DispatchEvent("E_GO_BACK"));

}

TEST( CStateMachine, Conditions_variant_1)
{
	// action/condition mocks
	fsmEngine::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	InitializeSMActionFactory(actionFactory,&operationsMock);
	
	// configurator initialization parameters
	std::string configFile(UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/CSM/CSM_testConfig_2.xmi"));
	std::string smName("ConditionalScenario");
	
	fsmEngine::CArgoConfigurator configurator(configFile, smName);
	fsmEngine::CStateMachine stateMachine;
	stateMachine.Initialize( &configurator, &actionFactory );
	
	EXPECT_CALL(	operationsMock, Condition1()).WillOnce(Return(true));
	EXPECT_CALL(	operationsMock, OperationA());
	
	EXPECT_TRUE(stateMachine.DispatchEvent("E_GO"));
}

TEST( CStateMachine, Conditions_variant_2)
{
	// action/condition mocks
	fsmEngine::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	InitializeSMActionFactory(actionFactory,&operationsMock);
	
	// configurator initialization parameters
	std::string configFile(UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/CSM/CSM_testConfig_2.xmi"));
	std::string smName("ConditionalScenario");
	
	fsmEngine::CArgoConfigurator configurator(configFile, smName);
	fsmEngine::CStateMachine stateMachine;
	stateMachine.Initialize( &configurator, &actionFactory );
	
	EXPECT_CALL(	operationsMock, Condition1()).WillOnce(Return(false));
	EXPECT_CALL(	operationsMock, Condition2()).WillOnce(Return(true));

	EXPECT_CALL(	operationsMock, OperationB());
	
	EXPECT_TRUE(stateMachine.DispatchEvent("E_GO"));
}


TEST( CStateMachine, DetailedActionBehaviour)
{
	// action/condition mocks
	fsmEngine::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	InitializeSMActionFactory(actionFactory,&operationsMock);
	
	// configurator initialization parameters
	std::string configFile(UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/CSM/CSM_testConfig_2.xmi"));
	std::string smName("DetailedActionScenario");
	
	fsmEngine::CArgoConfigurator configurator(configFile, smName);
	fsmEngine::CStateMachine stateMachine;
	stateMachine.Initialize( &configurator, &actionFactory );
	
	Sequence executionSequence;
	
	EXPECT_CALL(operationsMock, OperationC()).InSequence(executionSequence);
	EXPECT_CALL(operationsMock, OperationB()).InSequence(executionSequence);
	EXPECT_CALL(operationsMock, OperationA()).InSequence(executionSequence);
	EXPECT_CALL(operationsMock, OperationD()).InSequence(executionSequence);
	EXPECT_CALL(operationsMock, OperationE()).InSequence(executionSequence);
	EXPECT_CALL(operationsMock, OperationF()).InSequence(executionSequence);
	EXPECT_CALL(operationsMock, OperationG()).InSequence(executionSequence);
	EXPECT_CALL(operationsMock, OperationH()).InSequence(executionSequence);
	
	EXPECT_TRUE(stateMachine.DispatchEvent("E_GO"));	
}

TEST( CStateMachine, DetailedActionSpecialCase)
{
	// action/condition mocks
	fsmEngine::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	InitializeSMActionFactory(actionFactory,&operationsMock);
	
	// configurator initialization parameters
	std::string configFile(UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/CSM/CSM_testConfig_2.xmi"));
	std::string smName("DetailedActionScenario");
	
	fsmEngine::CArgoConfigurator configurator(configFile, smName);
	fsmEngine::CStateMachine stateMachine;
	stateMachine.Initialize( &configurator, &actionFactory );
	
	Sequence executionSequence;
	
	EXPECT_CALL(operationsMock, OperationC()).InSequence(executionSequence);
	EXPECT_CALL(operationsMock, OperationB()).InSequence(executionSequence);
	EXPECT_CALL(operationsMock, OperationH()).InSequence(executionSequence);
	
	EXPECT_TRUE(stateMachine.DispatchEvent("E_GO_WITHIN_SUPERPARENT"));	
}

class EventHelper
{
public:
	EventHelper(fsmEngine::CStateMachine& rStateMachine): m_rStateMachine(rStateMachine) {};

	void FireEventB() { m_rStateMachine.DispatchEvent("E_IN_ACTION_B_EVENT");};
	void FireEventC() { m_rStateMachine.DispatchEvent("E_IN_ACTION_C_EVENT");};

private:
	fsmEngine::CStateMachine& m_rStateMachine;
};

TEST( CStateMachine, EventsFiredInsideTheSMActions)
{
	// action/condition mocks
	fsmEngine::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	InitializeSMActionFactory(actionFactory,&operationsMock);
	
	// configurator initialization parameters
	std::string configFile(UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/CSM/CSM_testConfig_2.xmi"));
	std::string smName("NestedEventsScenario");
	
	fsmEngine::CArgoConfigurator configurator(configFile, smName);
	fsmEngine::CStateMachine stateMachine;
	EventHelper eventHelper(stateMachine);
	stateMachine.Initialize( &configurator, &actionFactory );
	
	Sequence executionSequence;

	EXPECT_CALL(operationsMock, OperationA()).InSequence(executionSequence);	
	EXPECT_CALL(operationsMock, OperationB()).InSequence(executionSequence).WillOnce(InvokeWithoutArgs(&eventHelper,&EventHelper::FireEventB));
	EXPECT_CALL(operationsMock, OperationC()).InSequence(executionSequence).WillOnce(InvokeWithoutArgs(&eventHelper,&EventHelper::FireEventC));
	EXPECT_CALL(operationsMock, OperationA()).InSequence(executionSequence);	
	EXPECT_CALL(operationsMock, OperationD()).InSequence(executionSequence);
	
	EXPECT_TRUE(stateMachine.DispatchEvent("E_GO_SECOND"));	
}
