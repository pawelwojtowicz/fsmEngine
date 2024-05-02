#include "CAction.h"

namespace fsmEngine
{
CAction::CAction()
: m_actionName("")
{
}

CAction::~CAction()
{
}

void CAction::SetName( const std::string& name)
{
	m_actionName = name;
}

const std::string& CAction::GetName() const
{
	return m_actionName;
}


}
