#pragma once
#include <gmock/gmock.h>
#include <ICSMBuilder.h>

class ICSMBuilderUT
{
public:
	ICSMBuilderUT() {};
	virtual ~ICSMBuilderUT() {};
	
	virtual void AddState(std::string parent, 
												std::string stateName, 
												std::string enterActionName, 
												std::string leafActionName, 
												std::string exitActioName) = 0;
	
	virtual void AddTransition(	std::string eventName,
															std::string sourceStateName, 
															std::string destinationStateName, 
															std::string conditionName, 
															std::string actionName) = 0;
															
	virtual void SetInitialState( std::string initialState) = 0;

private:
	ICSMBuilderUT(const ICSMBuilderUT&);
	ICSMBuilderUT& operator=(const ICSMBuilderUT&);
};

class CCSMBuilderIF: public CSM::ICSMBuilder
{
public:
	CCSMBuilderIF(ICSMBuilderUT* pIF ):m_pBuilderUTIF(pIF) {};
	virtual ~CCSMBuilderIF() {};
private:	
	virtual void AddState(const std::string& parent, 
												const std::string& stateName, 
												const std::string& enterActionName, 
												const std::string& leafActionName, 
												const std::string& exitActioName)
	{
		m_pBuilderUTIF->AddState(parent,stateName,enterActionName,leafActionName,exitActioName);
	};
	
	virtual void AddTransition(	const std::string& eventName,
															const std::string& sourceStateName, 
															const std::string& destinationStateName, 
															const std::string& conditionName, 
															const std::string& actionName)
	{
		m_pBuilderUTIF->AddTransition(eventName,sourceStateName,destinationStateName,conditionName,actionName);
	};
	
	virtual void SetInitialState( const std::string& initialState)
	{
		m_pBuilderUTIF->SetInitialState(initialState);
	}

	
private:
	CCSMBuilderIF(CCSMBuilderIF&);
	CCSMBuilderIF& operator=( const CCSMBuilderIF&);
	
	ICSMBuilderUT* m_pBuilderUTIF;

};

class CCSMBuilderMock: public ICSMBuilderUT
{
public:
	MOCK_METHOD5(AddState, void (std::string parent, 
												std::string stateName, 
												std::string enterActionName, 
												std::string leafActionName, 
												std::string exitActioName));
												
	MOCK_METHOD5(AddTransition, void (	std::string eventName,
																			std::string sourceStateName, 
																			std::string destinationStateName, 
																			std::string conditionName, 
																			std::string actionName));
																			
	MOCK_METHOD1(	SetInitialState, void( std::string initialState) );
};


#endif

