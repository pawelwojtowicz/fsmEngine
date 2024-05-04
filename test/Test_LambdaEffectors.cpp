#include <gtest/gtest.h>
#include <CLambdaAction.h>
#include <CLambdaCondition.h>
#include <memory>

TEST( LambdaActors, CLambdaCondition_Basic)
{
  bool returnValue(false);

  std::shared_ptr<fsmEngine::ICondition> condition = std::make_shared<fsmEngine::CLambdaCondition>([&returnValue](){ return returnValue;});

  EXPECT_FALSE( condition->Evaluate());
  returnValue = true;
  EXPECT_TRUE( condition->Evaluate());
  returnValue = false;
  EXPECT_FALSE( condition->Evaluate());

}

TEST( LambdaActors, CLambdaAction_Basic)
{
  int counter(0);

  std::shared_ptr<fsmEngine::IAction> action = std::make_shared<fsmEngine::CLambdaAction>([&counter](){ return ++counter;});

  EXPECT_EQ( counter , 0);
  action->Execute();
  EXPECT_EQ( counter , 1);
  action->Execute();
  EXPECT_EQ( counter , 2);
  action->Execute();
  EXPECT_EQ( counter , 3);
}