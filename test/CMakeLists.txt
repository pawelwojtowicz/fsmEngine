project ( fsmEngine_test )

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable ( test_fsmEngine
Test_CActionFactory.cpp
Test_CPUMLConfigurator.cpp
Test_CState.cpp 
Test_CStateMachineWpuml.cpp
Test_LambdaEffectors.cpp
#Test_CArgoConfigurator.cpp 
#Test_CStateMachine.cpp 
)


add_dependencies ( test_fsmEngine fsmEngine )
target_link_libraries ( test_fsmEngine fsmEngine pthread rt  gtest gmock gtest_main )
