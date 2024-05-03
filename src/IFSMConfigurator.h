#pragma once

namespace fsmEngine
{
class IFSMBuilder;

class IFSMConfigurator
{
public:
	IFSMConfigurator() {};
	virtual ~IFSMConfigurator() {};
	
	virtual bool InitializeStateMachine( IFSMBuilder& rBuilder ) = 0;

private:
	IFSMConfigurator(const IFSMConfigurator&) = delete;
	IFSMConfigurator& operator=(const IFSMConfigurator&) = delete;
};

}
