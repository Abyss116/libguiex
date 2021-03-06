/** 
* @file guimouse_default.cpp
* @brief default mouse interface, the user has to 
* set mouse value himself
* @author ken
* @date 2006-07-18
*/

//============================================================================//
// include
//============================================================================// 
#include <libguiex_module/mouse_default/guimouse_default.h>


//============================================================================//
// function
//============================================================================// 

namespace guiex
{

	//------------------------------------------------------------------------------
	GUI_INTERFACE_IMPLEMENT(IGUIMouse_default);
	//------------------------------------------------------------------------------
	const char* IGUIMouse_default::StaticGetModuleName()
	{
		return "IGUIMouse_default";
	}
	//------------------------------------------------------------------------------
	IGUIMouse_default::IGUIMouse_default()
		:IGUIInterfaceMouse( StaticGetModuleName() )
	{
	}
	//------------------------------------------------------------------------------
	IGUIMouse_default::~IGUIMouse_default()
	{
	}
	//------------------------------------------------------------------------------
	int IGUIMouse_default::DoInitialize(void* )
	{
		return 0;
	}
	//------------------------------------------------------------------------------
	void IGUIMouse_default::DoDestroy()
	{
	}
	//------------------------------------------------------------------------------
	void	IGUIMouse_default::DeleteSelf()
	{
		delete this;
	}
	//------------------------------------------------------------------------------


}//namespace guiex
