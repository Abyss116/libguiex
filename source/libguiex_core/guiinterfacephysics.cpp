/** 
* @file guiinterfacephysics.cpp
* @brief physics interface
* @author ken
* @date 2010-12-21
*/


//============================================================================//
// include
//============================================================================// 
#include "guiinterfacephysics.h"
#include "guiinterfacemanager.h"

//============================================================================//
// function
//============================================================================// 
namespace guiex
{
	//------------------------------------------------------------------------------
	const char* IGUIInterfacePhysics::StaticGetModuleType()
	{ 
		return "IGUIPhysics";
	}
	//------------------------------------------------------------------------------
	IGUIInterfacePhysics::IGUIInterfacePhysics( const char* szModuleName )
		:IGUIInterface(StaticGetModuleType(), szModuleName)
	{
	}
	//------------------------------------------------------------------------------
	IGUIInterfacePhysics::~IGUIInterfacePhysics()
	{
	}
	//------------------------------------------------------------------------------
}//namespace guiex
