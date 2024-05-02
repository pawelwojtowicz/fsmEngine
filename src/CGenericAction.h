#pragma once
#include "CAction.h"

namespace fsmEngine
{

template <class EXECUTE_CONTEXT>
class CGenericAction : public CAction
{
	typedef void (EXECUTE_CONTEXT::*tFunctionPointer)(void);
public:
	CGenericAction( EXECUTE_CONTEXT* pExecuteContext, tFunctionPointer pFunction )
	: m_pExecuteContext(pExecuteContext)
	, m_pFunction(pFunction)
	{
	};
	
	virtual ~CGenericAction()
	{
	};
private:
	virtual void Execute()
	{
		if ( 0 != m_pExecuteContext && 0!= m_pFunction )
		{
			(m_pExecuteContext->*m_pFunction)();
		} 
	};

private:
	EXECUTE_CONTEXT* m_pExecuteContext;
	
	tFunctionPointer m_pFunction;
};
}
