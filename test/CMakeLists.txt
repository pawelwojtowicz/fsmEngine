project ( fsmEngine_test )

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable ( test_fsmEngine
Test_CState.cpp 
#Test_CArgoConfigurator.cpp 
#Test_CStateMachine.cpp 
Test_CActionFactory.cpp )


add_dependencies ( test_fsmEngine fsmEngine )
target_link_libraries ( test_fsmEngine fsmEngine pthread rt  gtest gmock gtest_main )
