#pragma once
#include <string>

namespace fsmEngine
{
class IAction;
class ICondition;

class IActionFactory
{
protected:
	IActionFactory() {};
	virtual ~IActionFactory() {};

public:
	virtual IAction* GetAction( const std::string& actionName ) const = 0 ;
	
	virtual ICondition* GetCondition( const std::string& conditionName) const = 0;
	
private:
	IActionFactory(const IActionFactory&);
	IActionFactory& operator=(const IActionFactory&);
};

}