#include "CLambdaCondition.h"

namespace fsmEngine
{

CLambdaCondition::CLambdaCondition(std::function<bool()> rCondition)
: m_rCondition(rCondition)
{

}

bool CLambdaCondition::Evaluate()
{
  return m_rCondition();
}

}