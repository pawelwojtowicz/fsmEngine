#pragma once
#include <string>
#include <regex>

#include "ICSMConfigurator.h"

namespace fsmEngine
{
class CPUMLConfigurator : ICSMConfigurator
{
  struct sState
	{
		std::string ParentName;
		std::string StateName;
		std::string EnterActionName;
		std::string LeafActionName;
		std::string ExitActionName;
	};

public:
  CPUMLConfigurator( const std::string& filename );
  virtual ~CPUMLConfigurator() = default;

private:
  virtual bool InitializeStateMachine( ICSMBuilder* pBuilder ) override;

  std::string m_pumlFile;
};
}