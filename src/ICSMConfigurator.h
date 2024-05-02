#pragma once

namespace fsmEngine
{
class ICSMBuilder;

class ICSMConfigurator
{
public:
	ICSMConfigurator() {};
	virtual ~ICSMConfigurator() {};
	
	virtual bool InitializeStateMachine( ICSMBuilder& pBuilder ) = 0;

private:
	ICSMConfigurator(const ICSMConfigurator&);
	ICSMConfigurator& operator=(const ICSMConfigurator&);
};

}
