#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <CActionFactory.h>
#include <CGenericAction.h>
#include <CGenericCondition.h>
#include "ITestInterface.h"
#include <memory>

void InitializeActionFactory( fsmEngine::CActionFactory& actionFactory, TestOperationsMock* pMockPointer)
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

TEST( CActionFactory, Actions_Found_NotFound )
{
	fsmEngine::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	
	InitializeActionFactory( actionFactory, &operationsMock );
	
	std::shared_ptr<fsmEngine::IAction> pAction = actionFactory.GetAction("OperationA");
	
	EXPECT_TRUE( 0 != pAction );

	pAction = actionFactory.GetAction("Dupa");
	
	EXPECT_TRUE( 0 == pAction );

	EXPECT_TRUE(true);
}

TEST( CActionFactory, Actions_ExecuteSequence )
{
	fsmEngine::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	
	InitializeActionFactory( actionFactory, &operationsMock );

	Sequence executionSequence;
	
	EXPECT_CALL(operationsMock, OperationB()).InSequence(executionSequence);
	EXPECT_CALL(operationsMock, OperationD()).InSequence(executionSequence);
	EXPECT_CALL(operationsMock, OperationH()).InSequence(executionSequence);
	EXPECT_CALL(operationsMock, OperationA()).InSequence(executionSequence);
	
	std::shared_ptr<fsmEngine::IAction> pAction = actionFactory.GetAction("OperationB");
	
	EXPECT_TRUE( 0!= pAction );
	if ( 0 !=pAction )
	{
		pAction->Execute();
	}

	pAction = actionFactory.GetAction("OperationD");
	EXPECT_TRUE( 0!= pAction );
	if ( 0 !=pAction )
	{
		pAction->Execute();
	}

	pAction = actionFactory.GetAction("OperationH");
	EXPECT_TRUE( 0!= pAction );
	if ( 0 !=pAction )
	{
		pAction->Execute();
	}

	pAction = actionFactory.GetAction("OperationA");
	EXPECT_TRUE( 0!= pAction );
	if ( 0 !=pAction )
	{
		pAction->Execute();
	}
}

TEST( CActionFactory, Conditions_FoundNotFound )
{
	fsmEngine::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	
	InitializeActionFactory( actionFactory, &operationsMock );
	
	std::shared_ptr<fsmEngine::ICondition> pCondition = actionFactory.GetCondition( "Condition1" );
	
	EXPECT_TRUE( pCondition );
	
	pCondition = actionFactory.GetCondition( "Condition9" );

	EXPECT_FALSE( pCondition );


}

TEST( CActionFactory , Conditions_ExecutedInSequenceReturningRightValues)
{

	fsmEngine::CActionFactory actionFactory;
	TestOperationsMock operationsMock;
	
	InitializeActionFactory( actionFactory, &operationsMock );


	Sequence executionSequence;
	
	EXPECT_CALL(operationsMock, Condition8()).InSequence(executionSequence).WillOnce(Return(true));
	EXPECT_CALL(operationsMock, Condition4()).InSequence(executionSequence).WillOnce(Return(false));
	EXPECT_CALL(operationsMock, Condition2()).InSequence(executionSequence).WillOnce(Return(false));
	EXPECT_CALL(operationsMock, Condition7()).InSequence(executionSequence).WillOnce(Return(true));
	EXPECT_CALL(operationsMock, Condition8()).InSequence(executionSequence).WillOnce(Return(false));
	
	EXPECT_TRUE( actionFactory.GetCondition("Condition8")->Evaluate());
	EXPECT_FALSE( actionFactory.GetCondition("Condition4")->Evaluate());
	EXPECT_FALSE( actionFactory.GetCondition("Condition2")->Evaluate());
	EXPECT_TRUE( actionFactory.GetCondition("Condition7")->Evaluate());
	EXPECT_FALSE( actionFactory.GetCondition("Condition8")->Evaluate());

}
