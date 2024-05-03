#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <CState.h>
#include <CTransition.h>
#include <CActionFactory.h>
#include <CGenericAction.h>
#include <CGenericCondition.h>
#include "ITestInterface.h"
#include <memory>

using namespace fsmEngine;

void InitializeFactory( fsmEngine::CActionFactory& actionFactory, TestOperationsMock* pMockPointer)
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


using ::testing::Sequence;
using ::testing::Return;

TEST( CState, SingleMatch_ConditionOK )
{
	fsmEngine::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	
	InitializeFactory( actionFactory, &operationsMock );
	
	fsmEngine::CState stateUnderTest(0, std::string("name"), 0, 0, 0);
	
	stateUnderTest.AddTransition( 1 , std::make_shared<fsmEngine::CTransition>( std::string("evName") , actionFactory.GetCondition("Condition1"), actionFactory.GetAction("OperationA") , std::shared_ptr<CState>({}) ) );
	
	stateUnderTest.AddTransition( 2 , std::make_shared<fsmEngine::CTransition>( std::string("evName") , actionFactory.GetCondition("Condition2"), actionFactory.GetAction("OperationB") , std::shared_ptr<CState>({}) ) );

	stateUnderTest.AddTransition( 2 , std::make_shared<fsmEngine::CTransition>( std::string("evName") , actionFactory.GetCondition("Condition3"), actionFactory.GetAction("OperationC") , std::shared_ptr<CState>({}) ) );

	stateUnderTest.AddTransition( 3 , std::make_shared<fsmEngine::CTransition>( std::string("evName") , actionFactory.GetCondition("Condition4"), actionFactory.GetAction("OperationD") , std::shared_ptr<CState>({}) ) );
	
	EXPECT_CALL(	operationsMock, Condition1() ).WillOnce(Return(true));
	EXPECT_CALL(	operationsMock, OperationA());

	std::shared_ptr<fsmEngine::CTransition> pTransition = stateUnderTest.GetTransition(1);
	
	EXPECT_TRUE( 0 != pTransition );
	
	pTransition->ExecuteAction();
}

TEST( CState, SingleMatch_ConditionNOK )
{
	fsmEngine::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	
	InitializeFactory( actionFactory, &operationsMock );
	
	fsmEngine::CState stateUnderTest(0, std::string("name"), 0, 0, 0);
	
	stateUnderTest.AddTransition( 1 , std::make_shared<fsmEngine::CTransition>( std::string("evName") , actionFactory.GetCondition("Condition1"), actionFactory.GetAction("OperationA") , std::shared_ptr<CState>({}) ) );
	
	stateUnderTest.AddTransition( 2 , std::make_shared<fsmEngine::CTransition>( std::string("evName") , actionFactory.GetCondition("Condition2"), actionFactory.GetAction("OperationB") , std::shared_ptr<CState>({}) ) );

	stateUnderTest.AddTransition( 2 , std::make_shared<fsmEngine::CTransition>( std::string("evName") , actionFactory.GetCondition("Condition3"), actionFactory.GetAction("OperationC") , std::shared_ptr<CState>({}) ) );

	stateUnderTest.AddTransition( 3 , std::make_shared<fsmEngine::CTransition>( std::string("evName") , actionFactory.GetCondition("Condition4"), actionFactory.GetAction("OperationD") , std::shared_ptr<CState>({}) ) );
	
	EXPECT_CALL(	operationsMock, Condition1() ).WillOnce(Return(false));

	std::shared_ptr<fsmEngine::CTransition> pTransition = stateUnderTest.GetTransition(1);
	
	EXPECT_FALSE( 0 != pTransition );
}

TEST( CState, MultipleMatch_ConditionOK )
{
	fsmEngine::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	
	InitializeFactory( actionFactory, &operationsMock );
	
	fsmEngine::CState stateUnderTest(std::shared_ptr<CState>({}), std::string("name"), std::shared_ptr<IAction>({}), std::shared_ptr<IAction>({}), std::shared_ptr<IAction>({}));
	
	stateUnderTest.AddTransition( 1 , std::make_shared<fsmEngine::CTransition>( std::string("evName") , actionFactory.GetCondition("Condition1"), actionFactory.GetAction("OperationA") , std::shared_ptr<CState>({}) ) );
	
	stateUnderTest.AddTransition( 2 , std::make_shared<fsmEngine::CTransition>( std::string("evName") , actionFactory.GetCondition("Condition2"), actionFactory.GetAction("OperationB") , std::shared_ptr<CState>({}) ) );

	stateUnderTest.AddTransition( 2 , std::make_shared<fsmEngine::CTransition>( std::string("evName") , actionFactory.GetCondition("Condition3"), actionFactory.GetAction("OperationC") , std::shared_ptr<CState>({}) ) );

	stateUnderTest.AddTransition( 3 , std::make_shared<fsmEngine::CTransition>( std::string("evName") , actionFactory.GetCondition("Condition4"), actionFactory.GetAction("OperationD") , std::shared_ptr<CState>({}) ) );
	
	EXPECT_CALL(	operationsMock, Condition2() ).WillOnce(Return(true));
	EXPECT_CALL(	operationsMock, OperationB());

	std::shared_ptr<fsmEngine::CTransition> pTransition = stateUnderTest.GetTransition(2);
	
	EXPECT_TRUE( 0 != pTransition );
	
	pTransition->ExecuteAction();
}

TEST( CState, MultipleMatch_ConditionNOK_OK )
{
	fsmEngine::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	
	InitializeFactory( actionFactory, &operationsMock );
	
	fsmEngine::CState stateUnderTest(std::shared_ptr<CState>({}), std::string("name"), std::shared_ptr<IAction>({}), std::shared_ptr<IAction>({}), std::shared_ptr<IAction>({}));
	
	stateUnderTest.AddTransition( 1 , std::make_shared<fsmEngine::CTransition>( std::string("evName") , actionFactory.GetCondition("Condition1"), actionFactory.GetAction("OperationA") , std::shared_ptr<CState>({}) ) );
	
	stateUnderTest.AddTransition( 2 , std::make_shared<fsmEngine::CTransition>( std::string("evName") , actionFactory.GetCondition("Condition2"), actionFactory.GetAction("OperationB") , std::shared_ptr<CState>({}) ) );

	stateUnderTest.AddTransition( 2 , std::make_shared<fsmEngine::CTransition>( std::string("evName") , actionFactory.GetCondition("Condition3"), actionFactory.GetAction("OperationC") , std::shared_ptr<CState>({}) ) );

	stateUnderTest.AddTransition( 3 , std::make_shared<fsmEngine::CTransition>( std::string("evName") , actionFactory.GetCondition("Condition4"), actionFactory.GetAction("OperationD") , std::shared_ptr<CState>({}) ) );
	
	EXPECT_CALL(	operationsMock, Condition2() ).WillOnce(Return(false));
	EXPECT_CALL(	operationsMock, Condition3() ).WillOnce(Return(true));

	EXPECT_CALL(	operationsMock, OperationC());

	std::shared_ptr<fsmEngine::CTransition> pTransition = stateUnderTest.GetTransition(2);
	
	EXPECT_TRUE( 0 != pTransition );
	
	pTransition->ExecuteAction();
}

TEST( CState, MultipleMatch_ConditionNOK_NOK )
{
	fsmEngine::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	
	InitializeFactory( actionFactory, &operationsMock );
	
	fsmEngine::CState stateUnderTest(std::shared_ptr<CState>({}), std::string("name"), std::shared_ptr<IAction>({}), std::shared_ptr<IAction>({}), std::shared_ptr<IAction>({}));
	
	stateUnderTest.AddTransition( 1 , std::make_shared<fsmEngine::CTransition>( std::string("evName") , actionFactory.GetCondition("Condition1"), actionFactory.GetAction("OperationA") , std::shared_ptr<CState>({}) ) );
	
	stateUnderTest.AddTransition( 2 , std::make_shared<fsmEngine::CTransition>( std::string("evName") , actionFactory.GetCondition("Condition2"), actionFactory.GetAction("OperationB") , std::shared_ptr<CState>({}) ) );

	stateUnderTest.AddTransition( 2 , std::make_shared<fsmEngine::CTransition>( std::string("evName") , actionFactory.GetCondition("Condition3"), actionFactory.GetAction("OperationC") , std::shared_ptr<CState>({}) ) );

	stateUnderTest.AddTransition( 3 , std::make_shared<fsmEngine::CTransition>( std::string("evName") , actionFactory.GetCondition("Condition4"), actionFactory.GetAction("OperationD") , std::shared_ptr<CState>({}) ) );
	
	EXPECT_CALL(	operationsMock, Condition2() ).WillOnce(Return(false));
	EXPECT_CALL(	operationsMock, Condition3() ).WillOnce(Return(false));

	std::shared_ptr<fsmEngine::CTransition> pTransition = stateUnderTest.GetTransition(2);
	
	EXPECT_FALSE( pTransition );
}

