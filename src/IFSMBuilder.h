#pragma once
#include <string>

namespace fsmEngine
{
class IFSMBuilder
{
protected:
	IFSMBuilder() {};
	virtual ~IFSMBuilder() {};
	
public:
	virtual void AddState(const std::string& parent, 
												const std::string& stateName, 
												const std::string& enterActionName, 
												const std::string& leafActionName, 
												const std::string& exitActioName) = 0;
	
	virtual void AddTransition(	const std::string& eventName,
															const std::string& sourceStateName, 
															const std::string& destinationStateName, 
															const std::string& conditionName, 
															const std::string& actionName) = 0;
															
	virtual void SetInitialState( const std::string& initialState) = 0;
	
private:
	IFSMBuilder(const IFSMBuilder&);
	IFSMBuilder& operator=( const IFSMBuilder&);
};
}