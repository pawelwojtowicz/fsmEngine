#pragma once
#include <map>
#include <memory>
#include "IActionFactory.h"

namespace fsmEngine
{
class CActionFactory : public IActionFactory
{
	typedef std::map<uint32_t, std::shared_ptr<IAction>> tActionMap;
	typedef tActionMap::const_iterator tActionMapConstIterator;
	
	typedef std::map<uint32_t, std::shared_ptr<ICondition>> tConditionsMap;
	typedef tConditionsMap::const_iterator tConditionsMapConstIterator;
public:
	CActionFactory();
	virtual ~CActionFactory();
	
	void AddAction( const std::string& actionName, std::shared_ptr<IAction> pAction );
	
	void AddCondition ( const std::string& conditionName, std::shared_ptr<ICondition> pCondition );

	/** implementation of IActionFactory */
	virtual std::shared_ptr<IAction> GetAction( const std::string& actionName ) const;
	
	virtual std::shared_ptr<ICondition> GetCondition( const std::string& conditionName) const;
	
private:
	CActionFactory(const CActionFactory&);
	CActionFactory& operator=(const CActionFactory&);
	
	tActionMap m_actionMap;
	
	tConditionsMap m_conditionMap;
};
}
