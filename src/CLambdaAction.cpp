#include "CLambdaAction.h"

namespace fsmEngine
{
CLambdaAction::CLambdaAction( std::function<void()> lambda)
: m_lambdaAction(lambda)
{
}

void CLambdaAction::Execute()
{
  m_lambdaAction();
}
}