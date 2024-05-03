#pragma once
#include <string>
#include <memory>

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
	virtual std::shared_ptr<IAction> GetAction( const std::string& actionName ) const = 0 ;
	
	virtual std::shared_ptr<ICondition> GetCondition( const std::string& conditionName) const = 0;
	
private:
	IActionFactory(const IActionFactory&);
	IActionFactory& operator=(const IActionFactory&);
};

}