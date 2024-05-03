#include "CActionFactory.h"
#include "CFastHash.h"
#include "IAction.h"
#include "ICondition.h"

namespace fsmEngine
{
static const uint32_t sUInt32_ActionFactoryHashSeed = 0xFF00FF;

CActionFactory::CActionFactory()
{
}

CActionFactory::~CActionFactory()
{
}

void CActionFactory::AddAction( const std::string& actionName, std::shared_ptr<IAction> pAction )
{
  uint32_t actionNameHash(CFastHash::CalculateHash32(actionName,sUInt32_ActionFactoryHashSeed));
	
	m_actionMap.insert(tActionMap::value_type(actionNameHash,pAction));
}
	
void CActionFactory::AddCondition ( const std::string& conditionName, std::shared_ptr<ICondition> pCondition )
{
	uint32_t conditionNameHash(CFastHash::CalculateHash32(conditionName,sUInt32_ActionFactoryHashSeed));
	
	m_conditionMap.insert( tConditionsMap::value_type(conditionNameHash, pCondition));
}
	
std::shared_ptr<IAction> CActionFactory::GetAction( const std::string& actionName ) const
{
	uint32_t actionNameHash(CFastHash::CalculateHash32(actionName,sUInt32_ActionFactoryHashSeed));
	
	tActionMapConstIterator pCIter = m_actionMap.find(actionNameHash);
	
	if ( m_actionMap.end() != pCIter)
	{
		return pCIter->second;
	}
	
	return {};
}
	
std::shared_ptr<ICondition> CActionFactory::GetCondition( const std::string& conditionName) const
{
	uint32_t conditionNameHash(CFastHash::CalculateHash32(conditionName,sUInt32_ActionFactoryHashSeed));
	
	tConditionsMapConstIterator pCIter = m_conditionMap.find(conditionNameHash);
	
	if ( m_conditionMap.end() != pCIter )
	{
		return pCIter->second;
	}
	
	return {};
}
}
