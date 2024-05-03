#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <CPUMLConfigurator.h>
#include <iostream>
#include "CCSMBuilderMock.h"



TEST( CPUMLConfigurator, Basic )
{
  CCSMBuilderMock mockInstance;
	CCSMBuilderIF mockInterface(&mockInstance);

  std::string filename("/home/pawel/fsmEngine/fsmExamples/puml/basicFSM.puml");

  fsmEngine::CPUMLConfigurator fsmConfigurator( filename );
  fsmEngine::IFSMConfigurator& configuratorInterface(fsmConfigurator);

	EXPECT_CALL(mockInstance, AddState( std::string(""),		 					// parent, 
																			std::string("SuperParent"),  // stateName, 
																			std::string(""), 							// enterActionName, 
																			std::string(""), 							// leafActionName, 
																			std::string("")  							// exitActioName
																			)).Times(1);	

	
	EXPECT_CALL(mockInstance, AddState( std::string("SuperParent"), 					// parent, 
																			std::string("Parental"), 			// stateName, 
																			std::string("Action"),        // enterActionName, 
																			std::string(""), 							// leafActionName, 
																			std::string("")  							// exitActioName
																			)).Times(1);	

	EXPECT_CALL(mockInstance, AddState( std::string("Parental"), 			// parent, 
																			std::string("State1"), 				// stateName, 
																			std::string("OperationA"),	// enterActionName, 
																			std::string("OperationB"), 							// leafActionName, 
																			std::string("OperationC")  							// exitActioName
																			)).Times(1);	

	EXPECT_CALL(mockInstance, AddState( std::string(""), 			// parent, 
																			std::string("State2"), 				// stateName, 
																			std::string("OperationD"), 							// enterActionName, 
																			std::string("OperationE"), 							// leafActionName, 
																			std::string("OperationF")  	// exitActioName
																			)).Times(1);	
																			
	EXPECT_CALL(mockInstance, AddTransition(std::string("GoFurther"),	// eventName,
																					std::string("State1"),				// sourceStateName,
																					std::string("State2"),				// destinationStateName,
																					std::string(""),							// conditionName,
																					std::string("")	// actionName);
																					)).Times(1);

	EXPECT_CALL(mockInstance, AddTransition(std::string("GoFurther"),	// eventName,
																					std::string("State2"),				// sourceStateName,
																					std::string("State1"),				// destinationStateName,
																					std::string(""),		// conditionName,
																					std::string("")		  					// actionName);
																					)).Times(1);

	EXPECT_CALL(mockInstance, AddTransition(std::string("Stay"),	// eventName,
																					std::string("State2"),				// sourceStateName,
																					std::string("State2"),				// destinationStateName,
																					std::string(""),							// conditionName,
																					std::string("")		  					// actionName);
																					)).Times(1);

																					
	EXPECT_CALL(mockInstance, SetInitialState( std::string("State1")));

  configuratorInterface.InitializeStateMachine(mockInterface);
}
