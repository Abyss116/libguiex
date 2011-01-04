/** 
 * @file guiframework_mac.h
 * @brief framework to use this engine
 * @author ken
 * @date 2010-12-10
 */

//============================================================================//
// include 
//============================================================================// 
#include "guiframework_mac.h"

#include <libguiex_widget/guiwgt.h>

//libguiex module
#include <libguiex_module/font_cocoa/guifont_cocoa.h>
#include <libguiex_module/imageloader_tga/guiimageloader_tga.h>
#include <libguiex_module/filesys_cocoa/guifilesys_cocoa.h>
#include <libguiex_module/configfile_tinyxml/guiconfigfile_tinyxml.h>
#include <libguiex_module/render_opengles/guirender_opengles.h>
#include <libguiex_module/stringconv_cocoa/guistringconv_cocoa.h>
#include <libguiex_module/stringconv_iconv/guistringconv_iconv.h>
#include <libguiex_module/script_lua/guiscript_lua.h>
#include <libguiex_module/physics_box2d/guiphysics_box2d.h>
#include <libguiex_module/sound_dummy/guisound_dummy.h>

//============================================================================//
// function
//============================================================================// 
namespace guiex
{
	//------------------------------------------------------------------------------
	CGUIFramework_Mac::CGUIFramework_Mac( )
		:CGUIFrameworkBase( )
	{
	}
	//------------------------------------------------------------------------------
	CGUIFramework_Mac::~CGUIFramework_Mac()
	{
	}
	//------------------------------------------------------------------------------
	int32 CGUIFramework_Mac::InitializeSystem( const CGUISize& rScreenSize, const char* pDataPath )
	{
		//init system
		if( GSystem != NULL )
		{
			throw CGUIException( "[CGUIFramework_Mac::InitializeSystem] GSystem has been created!" );
			return -1;
		}
		GSystem = new CGUISystem;
		if( 0 != GSystem->Initialize())
		{
			return -1;
		}

		//setup log system
		SetupLogSystem();

		GSystem->SetScreenSize( rScreenSize );

		//register interface
		RegisterInterfaces();

		//register widget
		RegisterWidgetGenerators();

		//set date path
		GSystem->SetDataPath( pDataPath );

		return 0;
	}
	//------------------------------------------------------------------------------ 
	void CGUIFramework_Mac::SetupLogSystem( )
	{
		GUI_LOG->Open( "gui_framework_log", CGUILogMsg::FLAG_STDERR);
		GUI_LOG->SetPriorityMask( GUI_LM_DEBUG | GUI_LM_TRACE | GUI_LM_WARNING|GUI_LM_ERROR );
	}
	//------------------------------------------------------------------------------ 
	void CGUIFramework_Mac::ReleaseSystem()
	{
		//release system
		if( GSystem == NULL )
		{
			throw CGUIException( "[CGUIFramework_Mac::ReleaseSystem] GSystem has been released!" );
			return;
		}
		GSystem->Release();
		delete GSystem;
	}
	//------------------------------------------------------------------------------ 
	void CGUIFramework_Mac::RegisterInterfaces( )
	{
		GUI_REGISTER_INTERFACE_LIB( IGUIRender_opengles);
		GUI_REGISTER_INTERFACE_LIB( IGUIImageLoader_tga);
		GUI_REGISTER_INTERFACE_LIB( IGUIStringConv_cocoa);
		GUI_REGISTER_INTERFACE_LIB( IGUIFileSys_cocoa);
		GUI_REGISTER_INTERFACE_LIB( IGUIFont_cocoa);
		GUI_REGISTER_INTERFACE_LIB( IGUIConfigFile_tinyxml);
		GUI_REGISTER_INTERFACE_LIB( IGUIScript_lua);
		GUI_REGISTER_INTERFACE_LIB( IGUIPhysics_box2d );
		GUI_REGISTER_INTERFACE_LIB( IGUISound_dummy );
	}
	//------------------------------------------------------------------------------ 
	void CGUIFramework_Mac::RegisterWidgetGenerators( )
	{
		CGUIWidgetGenerator** pGenerator = GetAllWidgetGenerators();
		while(*pGenerator)
		{
			CGUIWidgetFactory::Instance()->RegisterGenerator( *pGenerator);
			pGenerator ++;
		}
	}
	//------------------------------------------------------------------------------ 
	int32 CGUIFramework_Mac::InitializeGame( )
	{
		return 0;
	}
	//------------------------------------------------------------------------------ 
	void CGUIFramework_Mac::ReleaseGame()
	{
	}
	//------------------------------------------------------------------------------
	void CGUIFramework_Mac::PreUpdate( real fDeltaTime )
	{
	}
	//------------------------------------------------------------------------------
	void CGUIFramework_Mac::PostUpdate( real fDeltaTime )
	{
	}
	//------------------------------------------------------------------------------
	void CGUIFramework_Mac::OutputFatalError( const char* pErrorDesc )
	{
		printf( "fatal error: %s\n", pErrorDesc );
	}
	//------------------------------------------------------------------------------


}//namespace guiex

