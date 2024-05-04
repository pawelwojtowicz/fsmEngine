project (fsmEngine )

SET( OUTPUT_NAME fsmEngine )

add_library ( ${OUTPUT_NAME} SHARED
CAction.cpp
CLambdaAction.cpp
CLambdaCondition.cpp
CPUMLConfigurator.cpp
CPUMLConfigurator.h
CState.cpp
CTransition.cpp
CStateMachine.cpp 
CActionFactory.cpp
CFastHash.cpp
)

#target_link_libraries ( ${OUTPUT_NAME} UCL XMLParser )
#add_dependencies (${OUTPUT_NAME} UCL XMLParser )
#install ( TARGETS ${OUTPUT_NAME} LIBRARY DESTINATION ${ECUAPP_LIBRARY_INSTALL_DIR} )
