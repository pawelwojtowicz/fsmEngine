#pragma once
#include "IAction.h"

namespace fsmEngine
{

class CAction: public IAction
{
public:
	CAction();
	virtual ~CAction();

	/** implementation of CSM::IAction*/
	virtual void SetName( const std::string& name);
	virtual const std::string& GetName() const;


private:
	CAction(const CAction&);
	CAction& operator=(const CAction&);

private:
	std::string m_actionName;
};
}
