#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <CSM/CArgoConfigurator.h>
#include <CSM/ICSMBuilder.h>
#include <UCL/SystemEnvironment.h>
#include "CCSMBuilderMock.h"


TEST( CArgoConfigurator, TestScenario_1)
{
	CCSMBuilderMock mockInstance;
	CCSMBuilderIF mockInterface(&mockInstance);
	std::string configFile(UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/CSM/CSM_testConfig_1.xmi"));
	std::string smName("TestScenario_1");

	EXPECT_CALL(mockInstance, AddState( std::string(""),		 					// parent, 
																			std::string("top"), 					// stateName, 
																			std::string(""), 							// enterActionName, 
																			std::string(""), 							// leafActionName, 
																			std::string("")  							// exitActioName
																			)).Times(1);	

	
	EXPECT_CALL(mockInstance, AddState( std::string("top"), 					// parent, 
																			std::string("Parent1"), 			// stateName, 
																			std::string(""), 							// enterActionName, 
																			std::string(""), 							// leafActionName, 
																			std::string("")  							// exitActioName
																			)).Times(1);	

	EXPECT_CALL(mockInstance, AddState( std::string("Parent1"), 			// parent, 
																			std::string("Child1"), 				// stateName, 
																			std::string("A_EnterChild1"),	// enterActionName, 
																			std::string(""), 							// leafActionName, 
																			std::string("")  							// exitActioName
																			)).Times(1);	

	EXPECT_CALL(mockInstance, AddState( std::string("Parent1"), 			// parent, 
																			std::string("Child2"), 				// stateName, 
																			std::string(""), 							// enterActionName, 
																			std::string(""), 							// leafActionName, 
																			std::string("A_ExitChild2")  	// exitActioName
																			)).Times(1);	

	EXPECT_CALL(mockInstance, AddState( std::string("top"), 					// parent, 
																			std::string("Parent2"), 			// stateName, 
																			std::string(""), 							// enterActionName, 
																			std::string("A_DoParent2"),		// leafActionName, 
																			std::string("")  							// exitActioName
																			)).Times(1);
																			
	EXPECT_CALL(mockInstance, AddTransition(std::string("E_GoToParent2"),	// eventName,
																					std::string("Parent1"),				// sourceStateName,
																					std::string("Parent2"),				// destinationStateName,
																					std::string(""),							// conditionName,
																					std::string("A_WeAreLeaving")	// actionName);
																					)).Times(1);

	EXPECT_CALL(mockInstance, AddTransition(std::string("E_GoToChild1"),	// eventName,
																					std::string("Parent2"),				// sourceStateName,
																					std::string("Child1"),				// destinationStateName,
																					std::string("C_CanGoBack"),		// conditionName,
																					std::string("")		  					// actionName);
																					)).Times(1);

	EXPECT_CALL(mockInstance, AddTransition(std::string("E_GoToChild2"),	// eventName,
																					std::string("Child1"),				// sourceStateName,
																					std::string("Child2"),				// destinationStateName,
																					std::string(""),							// conditionName,
																					std::string("")		  					// actionName);
																					)).Times(1);


	EXPECT_CALL(mockInstance, AddTransition(std::string("E_GoToChild1"),	// eventName,
																					std::string("Child2"),				// sourceStateName,
																					std::string("Child1"),				// destinationStateName,
																					std::string(""),							// conditionName,
																					std::string("")		  					// actionName);
																					)).Times(1);
																					
	EXPECT_CALL(mockInstance, SetInitialState( std::string("Child1")));
	
	CSM::CArgoConfigurator configurator(configFile, smName);
	configurator.InitializeStateMachine(&mockInterface);
}

TEST( CArgoConfigurator, TestScenario_2)
{
	CCSMBuilderMock mockInstance;
	CCSMBuilderIF mockInterface(&mockInstance);
	std::string configFile(UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/CSM/CSM_testConfig_1.xmi"));
	std::string smName("TestScenario_2");

	EXPECT_CALL(mockInstance, AddState( std::string(""),		 					// parent, 
																			std::string("top"), 					// stateName, 
																			std::string(""), 							// enterActionName, 
																			std::string(""), 							// leafActionName, 
																			std::string("")  							// exitActioName
																			)).Times(1);	

	
	EXPECT_CALL(mockInstance, AddState( std::string("top"), 					// parent, 
																			std::string("OneState"), 			// stateName, 
																			std::string(""), 							// enterActionName, 
																			std::string(""), 							// leafActionName, 
																			std::string("")  							// exitActioName
																			)).Times(1);	

	EXPECT_CALL(mockInstance, AddState( std::string("top"), 					// parent, 
																			std::string("SecondState"), 	// stateName, 
																			std::string(""),							// enterActionName, 
																			std::string(""), 							// leafActionName, 
																			std::string("")  							// exitActioName
																			)).Times(1);
																			
	EXPECT_CALL(mockInstance, AddTransition(std::string("E_ToSecond"),// eventName,
																					std::string("OneState"),	// sourceStateName,
																					std::string("SecondState"),// destinationStateName,
																					std::string(""),					// conditionName,
																					std::string("")		  			// actionName);
																					)).Times(1);
																					
	EXPECT_CALL(mockInstance, SetInitialState( std::string("OneState")));


	CSM::CArgoConfigurator configurator(configFile, smName);
	configurator.InitializeStateMachine(&mockInterface);
}
