#pragma once
#include "ICondition.h"

namespace fsmEngine
{

template <class EXECUTE_CONTEXT>
class CGenericCondition : public ICondition
{
	typedef bool (EXECUTE_CONTEXT::*tFunctionPointer)();
public:
	CGenericCondition( EXECUTE_CONTEXT* pExecuteContext, tFunctionPointer pFunction )
	: m_pExecuteContext(pExecuteContext)
	, m_pFunction(pFunction)
	{
	};
	
	virtual ~CGenericCondition()
	{
	};
private:
	virtual bool Evaluate()
	{
		if ( 0 != m_pExecuteContext && 0!= m_pFunction )
		{
			return (m_pExecuteContext->*m_pFunction)();
		}
		return false;
	};

private:
	EXECUTE_CONTEXT* m_pExecuteContext;
	
	tFunctionPointer m_pFunction;
};
}
