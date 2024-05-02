#pragma once
#include <string>

namespace fsmEngine
{
class IAction
{
public:
	IAction() {};
	virtual ~IAction() {};

	virtual void SetName( const std::string& name) = 0;
	virtual const std::string& GetName() const = 0;
	
	virtual void Execute() = 0;
	
private:
	IAction(const IAction&);
	IAction& operator=(const IAction&);
};
}
