#pragma once
#include "ICondition.h"
#include <functional>

namespace fsmEngine
{
class CLambdaCondition : public ICondition
{
public:
  CLambdaCondition(std::function<bool()> rCondition);

private:
  bool Evaluate() override;

private:
  std::function<bool()> m_rCondition;
};
}