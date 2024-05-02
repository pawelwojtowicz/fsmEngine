#pragma once
#include "ICSMConfigurator.h"

class XMLNode; 

namespace fsmEngine
{
class IActionFactory;
class ICSMBuilder;

class CArgoConfigurator : public ICSMConfigurator
{
	struct sState
	{
		std::string ParentName;
		std::string StateName;
		std::string EnterActionName;
		std::string LeafActionName;
		std::string ExitActionName;
	};
	
	typedef std::map<std::string, sState> tIdToState;
	typedef tIdToState::const_iterator tIdToStateConstIterator;

	typedef std::map<std::string, std::string> tIdToNameMap;
	typedef tIdToNameMap::const_iterator tIdToNameMapConstIterator;
	
public:
	CArgoConfigurator( const std::string& stateMachineConfigFile, const std::string& statechartName );
	virtual ~CArgoConfigurator();
	
	virtual bool InitializeStateMachine( ICSMBuilder* pBuilder );
																
private:
	CArgoConfigurator(const CArgoConfigurator&);
	CArgoConfigurator& operator=(const CArgoConfigurator&);

private:
	void ReadCompositeStateConfiguration ( const std::string& parentName, const XMLNode& stateConfigNode );
	void ConfigureTransitions( const XMLNode& transitions);
  const std::string ReadNestedProperty( const XMLNode& parentNode , const char firstLevelNodeName[], const char secondLevelNodeName[], const char propertyName[] );

private:
	std::string m_xmiFileName;
	
	std::string m_statechartName;	
	
	ICSMBuilder* m_pCSMBuilder;

	tIdToState m_statesMap;
	
	tIdToNameMap m_IdToNameMap;
	
	std::string m_initialStateId;
	
};
}
#endif
