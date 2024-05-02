#pragma once

namespace fsmEngine
{
class ICondition
{
public:
	ICondition() {};
	virtual ~ICondition() {};
	
	virtual bool Evaluate() = 0;
	
private:
	ICondition(const ICondition&);
	ICondition& operator=(const ICondition&);
};
}