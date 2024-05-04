#pragma once
#include "CAction.h"
#include <functional>

namespace fsmEngine
{
class CLambdaAction : public CAction
{
public:
  CLambdaAction( std::function<void()> lambda);

private:
  void Execute() override;

private:
  std::function<void()> m_lambdaAction;
};
}