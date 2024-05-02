#pragma once
#include <map>
#include "IActionFactory.h"

namespace fsmEngine
{
class CActionFactory : public IActionFactory
{
	typedef std::map<uint32_t, IAction*> tActionMap;
	typedef tActionMap::const_iterator tActionMapConstIterator;
	
	typedef std::map<uint32_t, ICondition*> tConditionsMap;
	typedef tConditionsMap::const_iterator tConditionsMapConstIterator;
public:
	CActionFactory();
	virtual ~CActionFactory();
	
	void AddAction( const std::string& actionName, IAction* pAction );
	
	void AddCondition ( const std::string& conditionName, ICondition* pCondition );

	/** implementation of IActionFactory */
	virtual IAction* GetAction( const std::string& actionName ) const;
	
	virtual ICondition* GetCondition( const std::string& conditionName) const;
	
private:
	CActionFactory(const CActionFactory&);
	CActionFactory& operator=(const CActionFactory&);
	
	tActionMap m_actionMap;
	
	tConditionsMap m_conditionMap;
};
}
