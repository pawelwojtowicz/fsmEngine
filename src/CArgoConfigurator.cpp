#include "CArgoConfigurator.h"
#include "ICSMBuilder.h"
#include <XMLParser/xmlParser.h>
#include <UCL/SystemEnvironment.h>
#include <stdio.h>
namespace fsmEngine
{

static const char s_constXMI[] 							= {"XMI"};
static const char s_constXMI_Content[] 			= {"XMI.content"};
static const char s_constUML_Model[] 				= {"UML:Model"};
static const char s_constUML_OwnedElement[]		= {"UML:Namespace.ownedElement"};
static const char s_constUML_StateMachine[]		= {"UML:StateMachine"};
static const char s_constUML_TopState[]			= {"UML:StateMachine.top"};

static const char s_constUML_Transitions[]		= {"UML:StateMachine.transitions"};
static const char s_constUML_Transition[]		= {"UML:Transition"};
static const char s_constUML_InternalTransition[]	= {"UML:State.internalTransition"};
static const char s_constUML_TransitionTrigger[] 	= {"UML:Transition.trigger"};
static const char s_constUML_TransitionAction[]		= {"UML:Transition.effect"};
static const char s_constUML_TransitionSource[]		= {"UML:Transition.source"};
static const char s_constUML_TransitionTarget[]	 	= {"UML:Transition.target"};
static const char s_constUML_TransitionGuard[]		= {"UML:Transition.guard"};
static const char s_constUML_Guard[]							= {"UML:Guard"};



static const char s_constUML_CompositeState[]	= {"UML:CompositeState"};
static const char s_constUML_SimpleState[]	= {"UML:SimpleState"};
static const char s_constUML_StateVertex[]	= {"UML:CompositeState.subvertex"};
static const char s_constUML_PseudoState[]	= {"UML:Pseudostate"};

static const char s_constUML_SignalEvent[]	= {"UML:SignalEvent"};


static const char s_constUML_kind[]					= {"kind"};
static const char s_constUML_name[]					= {"name"};
static const char s_constUML_xmiId[]			  = {"xmi.id"};
static const char s_constUML_xmiIdRef[]			= {"xmi.idref"};

static const char s_constUML_CallAction[]		= {"UML:CallAction"};
static const char s_constUML_EntryAction[]	= {"UML:State.entry"};
static const char s_constUML_LeafAction[]		= {"UML:State.doActivity"};
static const char s_constUML_ExitAction[]		= {"UML:State.exit"};



CArgoConfigurator::CArgoConfigurator(const std::string& xmiFileName, const std::string& statechartName)
: m_xmiFileName(xmiFileName)
, m_statechartName(statechartName)
, m_pCSMBuilder(0)

{
}

//------------------------------------------------------------------------------------------

CArgoConfigurator::~CArgoConfigurator()
{
}

//------------------------------------------------------------------------------------------
	
bool CArgoConfigurator::InitializeStateMachine(	ICSMBuilder* pBuilder )
{
	if ( 0 == pBuilder )
	{
		return false;
	}
	
	m_pCSMBuilder = pBuilder;
	
	if ( m_xmiFileName.empty() )
	{
		return false;
	}
	
	XMLNode xMainNode=XMLNode::openFileHelper(	UCL::SystemEnvironment::ResolveEnvironmentVariable(m_xmiFileName.c_str()).c_str(),s_constXMI);
	
	if ( 1 !=  xMainNode.nChildNode(s_constXMI_Content) )
	{
		return false;
	}
	
	const XMLNode& contentNode = xMainNode.getChildNode( s_constXMI_Content , 0 );

	{
		const UInt32 numberOfSignalEvents(contentNode.nChildNode(s_constUML_SignalEvent));
		for ( UInt32 i = 0 ; i < numberOfSignalEvents; ++i )
		{
			const XMLNode& signalEventNode = contentNode.getChildNode( s_constUML_SignalEvent , i );
			
			m_IdToNameMap.insert( tIdToNameMap::value_type( signalEventNode.getAttribute(s_constUML_xmiId) , signalEventNode.getAttribute(s_constUML_name) ) );
		}
	}
	
	if (1 !=  contentNode.nChildNode(s_constUML_Model) )
	{
		return false;
	}
	
	const XMLNode& modelNode = contentNode.getChildNode( s_constUML_Model , 0 );
	
	if (1 !=  modelNode.nChildNode(s_constUML_OwnedElement) )
	{
		return false;
	}

	const XMLNode& ownedElementNode = modelNode.getChildNode( s_constUML_OwnedElement , 0 );
	
	{
		const UInt32 numberOfSignalEvents(ownedElementNode.nChildNode(s_constUML_SignalEvent));
		for ( UInt32 i = 0 ; i < numberOfSignalEvents; ++i )
		{
			const XMLNode& signalEventNode = ownedElementNode.getChildNode( s_constUML_SignalEvent , i );
			
			m_IdToNameMap.insert( tIdToNameMap::value_type( signalEventNode.getAttribute(s_constUML_xmiId) , 																												signalEventNode.getAttribute(s_constUML_name) ) );
		}
	}
	
	const UInt32 numberOfStateMachines( ownedElementNode.nChildNode(s_constUML_StateMachine) );
	
	for ( UInt32 soIndex = 0 ; soIndex < numberOfStateMachines ; ++soIndex )
	{
		const XMLNode& stateMachineNode = ownedElementNode.getChildNode( s_constUML_StateMachine , soIndex );
		
		const std::string smName = stateMachineNode.getAttribute(s_constUML_name);
		
		if ( smName == m_statechartName )
		{
			if ( 1 == stateMachineNode.nChildNode(s_constUML_TopState) )
			{
				const XMLNode& stateMachineTopNode = stateMachineNode.getChildNode( s_constUML_TopState , 0 );
				
				if (1 == stateMachineTopNode.nChildNode(s_constUML_CompositeState))
				{
					std::string noName("");
					ReadCompositeStateConfiguration(	noName, 
																						stateMachineTopNode.getChildNode( s_constUML_CompositeState, 0 ));
				
				}
			}
			
			if ( 1 == stateMachineNode.nChildNode(s_constUML_Transitions) )
			{
				const XMLNode& transitionsNode = stateMachineNode.getChildNode( s_constUML_Transitions , 0 );
				
				ConfigureTransitions( transitionsNode );
			}
			
			return true;
		}
	}
	
	return false;
}

//------------------------------------------------------------------------------------------

void CArgoConfigurator::ReadCompositeStateConfiguration ( const std::string& parentName, const XMLNode& stateConfigNode )
{
	sState stateStructure;
	stateStructure.ParentName = parentName;
	stateStructure.StateName = stateConfigNode.getAttribute(s_constUML_name);
	std::string stateId(stateConfigNode.getAttribute(s_constUML_xmiId));
	
  stateStructure.EnterActionName  = ReadNestedProperty(stateConfigNode, s_constUML_EntryAction, s_constUML_CallAction, s_constUML_name);
  stateStructure.LeafActionName   = ReadNestedProperty(stateConfigNode, s_constUML_LeafAction, s_constUML_CallAction, s_constUML_name);
  stateStructure.ExitActionName   = ReadNestedProperty(stateConfigNode, s_constUML_ExitAction, s_constUML_CallAction, s_constUML_name);
  
	if ( 1 == stateConfigNode.nChildNode( s_constUML_StateVertex ) )
	{
		const XMLNode& stateVertex = stateConfigNode.getChildNode( s_constUML_StateVertex, 0 );
		
		UInt32 internalSimpleStateCount( stateVertex.nChildNode(s_constUML_SimpleState) );
		for( UInt32 i = 0 ; i < internalSimpleStateCount ; ++i)
		{
			ReadCompositeStateConfiguration( 	stateStructure.StateName , 
																				stateVertex.getChildNode( s_constUML_SimpleState , 
																				i ));
		}
		
		UInt32 internalCompositeStateCount( stateVertex.nChildNode(s_constUML_CompositeState) );
		for( UInt32 i = 0 ; i < internalCompositeStateCount ; ++i)
		{
			ReadCompositeStateConfiguration( 	stateStructure.StateName , 
																				stateVertex.getChildNode( s_constUML_CompositeState , 
																				i ));
		}

		if ( 0 < stateVertex.nChildNode(s_constUML_PseudoState) )
		{
			const XMLNode& initialStateNode( stateVertex.getChildNode(s_constUML_PseudoState,0));
			
			if ( initialStateNode.isAttributeSet(s_constUML_kind) )
			{
				if ( std::string("initial") == initialStateNode.getAttribute(s_constUML_kind) )
				{
					m_initialStateId = initialStateNode.getAttribute(s_constUML_xmiId);
				}
			}
		}
	}

	m_statesMap.insert( tIdToState::value_type(stateId, stateStructure));
	
	m_pCSMBuilder->AddState( stateStructure.ParentName,
													 stateStructure.StateName,
													 stateStructure.EnterActionName,
													 stateStructure.LeafActionName,
													 stateStructure.ExitActionName);
	UInt32 internalTransitionsCount(stateConfigNode.nChildNode( s_constUML_InternalTransition ) );

	//read internal transitions of the state and add them
	for( UInt32 i = 0 ; i < internalTransitionsCount ; ++i )
	{
		const XMLNode& internalTransitionNode = stateConfigNode.getChildNode(s_constUML_InternalTransition , i );

		UInt32 transitionCount(internalTransitionNode.nChildNode( s_constUML_Transition ));
		for ( UInt32 ii = 0 ; ii < transitionCount ; ++ii)
		{
			std::string triggerName;

			const XMLNode& transitionNode = internalTransitionNode.getChildNode(s_constUML_Transition , ii );

			std::string eventNameId( ReadNestedProperty(transitionNode, s_constUML_TransitionTrigger, s_constUML_SignalEvent, s_constUML_xmiIdRef));
			tIdToNameMapConstIterator cIter = m_IdToNameMap.find(eventNameId);
			if (m_IdToNameMap.end() != cIter )
			{
				triggerName = cIter->second;
			}

			std::string guardName(ReadNestedProperty( transitionNode, s_constUML_TransitionGuard, s_constUML_Guard, s_constUML_name));
			std::string actionName(ReadNestedProperty( transitionNode, s_constUML_TransitionAction, s_constUML_CallAction, s_constUML_name ));

			m_pCSMBuilder->AddTransition(	triggerName, 
							stateStructure.StateName,
							stateStructure.StateName,																		guardName,
							actionName);
		}
	}																					
}

//------------------------------------------------------------------------------------------

void CArgoConfigurator::ConfigureTransitions( const XMLNode& transitions)
{
	UInt32 noOfTransitions( transitions.nChildNode(s_constUML_Transition) );
		
	for(UInt32 i = 0 ; i < noOfTransitions ; ++i )
	{
		bool dropTransition(false);
		std::string triggerName;
		std::string sourceName;
		std::string targetName;
		std::string guardName;
		std::string actionName;

		const XMLNode& transitionNode = transitions.getChildNode(s_constUML_Transition , i );

    
    std::string eventNameId( ReadNestedProperty(transitionNode, s_constUML_TransitionTrigger, s_constUML_SignalEvent, s_constUML_xmiIdRef));
    tIdToNameMapConstIterator cIter = m_IdToNameMap.find(eventNameId);
    if (m_IdToNameMap.end() != cIter )
    {
      triggerName = cIter->second;
    }

    
         
    {
      std::string stateId(ReadNestedProperty( transitionNode, s_constUML_TransitionSource, s_constUML_CompositeState, s_constUML_xmiIdRef));
      if ( stateId.empty() )
      {
        stateId = ReadNestedProperty( transitionNode, s_constUML_TransitionSource, s_constUML_SimpleState, s_constUML_xmiIdRef);
				if ( stateId.empty() )
      	{
        	stateId = ReadNestedProperty( transitionNode, s_constUML_TransitionSource, s_constUML_PseudoState, s_constUML_xmiIdRef);       
      	}     
      }
      
      if ( !stateId.empty() )
      {
      	if (m_initialStateId != stateId)
    		{
		      tIdToStateConstIterator cIter = m_statesMap.find(stateId);
		      if (m_statesMap.end() != cIter )
		      {
		        sourceName = cIter->second.StateName;
		      }
        }
        else
        {
        	dropTransition = true;
        }   
      }
    }


    {
      std::string stateId(ReadNestedProperty( transitionNode, s_constUML_TransitionTarget, s_constUML_CompositeState, s_constUML_xmiIdRef));
      if ( stateId.empty() )
      {
        stateId = ReadNestedProperty( transitionNode, s_constUML_TransitionTarget, s_constUML_SimpleState, s_constUML_xmiIdRef);
      }
      
      if ( !stateId.empty() )
      {
        tIdToStateConstIterator cIter = m_statesMap.find(stateId);
        if (m_statesMap.end() != cIter )
        {
          targetName = cIter->second.StateName;
        }     
      }
    }
    
    guardName = ReadNestedProperty( transitionNode, s_constUML_TransitionGuard, s_constUML_Guard, s_constUML_name);
    actionName = ReadNestedProperty( transitionNode, s_constUML_TransitionAction, s_constUML_CallAction, s_constUML_name );
     
		if ( !dropTransition)
		{
			m_pCSMBuilder->AddTransition(	triggerName, 
																		sourceName,
																		targetName,
																		guardName,
																		actionName);
		}
		else
		{
			m_pCSMBuilder->SetInitialState( targetName);
		}
	}
}

//------------------------------------------------------------------------------------------

const std::string CArgoConfigurator::ReadNestedProperty( const XMLNode& parentNode, const char firstLevelNodeName[], const char secondLevelNodeName[], const char propertyName[] )
{
  std::string propertyValue;
  
  
  if ( 1 == parentNode.nChildNode(firstLevelNodeName) )
  {
    const XMLNode& childNode = parentNode.getChildNode(firstLevelNodeName);
    
    if ( 1 == childNode.nChildNode(secondLevelNodeName) )
    {

    	if ( childNode.getChildNode(secondLevelNodeName).isAttributeSet(propertyName) )
    	{
      	propertyValue = childNode.getChildNode(secondLevelNodeName).getAttribute(propertyName);
      }
    }
  }
  return propertyValue;
}
}

