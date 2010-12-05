/*
 *  ApplicationEngine.cpp
 *  libguiex
 *
 *  Created by Lou Guo Liang on 11/10/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ApplicationEngine.h"

//libguiex
#include <libguiex_core/guiex.h>
#include <libguiex_widget/guiwgt.h>

//libguiex module
//#include <libguiex_module/keyboard_winapi\guikeyboard_winapi.h>
//#include <libguiex_module/mouse_winapi\guimouse_winapi.h>
#include <libguiex_module/font_cocoa/guifont_cocoa.h>
#include <libguiex_module/imageloader_tga/guiimageloader_tga.h>
#include <libguiex_module/filesys_cocoa/guifilesys_cocoa.h>
#include <libguiex_module/configfile_tinyxml/guiconfigfile_tinyxml.h>
#include <libguiex_module/render_opengles/guirender_opengles.h>
#include <libguiex_module/stringconv_cocoa/guistringconv_cocoa.h>
#include <libguiex_module/stringconv_iconv/guistringconv_iconv.h>
#include <libguiex_module/script_lua/guiscript_lua.h>
//#include <libguiex_module/ime_winapi\guiime_winapi.h>


class CLibGuiexEngine : public IApplicationEngine
{
public:
	CLibGuiexEngine();
	virtual ~CLibGuiexEngine();
	virtual void Initialize( int width, int height, const char* szDataPath );
	virtual void Update( float deltaTime );
	virtual void OnRotate( DeviceOrientation newOrientation );
	virtual void OnFingerUp(float x, float y);
    virtual void OnFingerDown(float x,float y);
    virtual void OnFingerMove(float oldx, float oldy, float x, float y);
	
private:
	void InitWidgets();
};

struct IApplicationEngine* CreateApplicationEngine()
{
	return new CLibGuiexEngine;
}

void DestroyApplicationEngine( IApplicationEngine* pEngine )
{
	delete pEngine;
}

CLibGuiexEngine::CLibGuiexEngine()
{
	new guiex::CGUISystem;
    guiex::CGUISystem::Instance()->Initialize();	
}

CLibGuiexEngine::~CLibGuiexEngine()
{
	guiex::CGUISystem::Instance()->Release();
	delete guiex::CGUISystem::Instance();
}

void CLibGuiexEngine::Initialize( int width, int height, const char* szDataPath )
{
    //guiex::CGUIAssert::SetWarningCB(EditorWarningCB, NULL);
    guiex::CGUISystem::Instance()->SetScreenSize(width,height);
    guiex::CGUISystem::Instance()->SetDataPath(guiex::CGUIString(szDataPath) + "/");
    //guiex::CGUISystem::Instance()->SetDrawExtraInfo(true);
	
    //register interface
    GUI_REGISTER_INTERFACE_LIB( IGUIRender_opengles);
    GUI_REGISTER_INTERFACE_LIB( IGUIImageLoader_tga);
	GUI_REGISTER_INTERFACE_LIB( IGUIStringConv_cocoa);
	//GUI_REGISTER_INTERFACE_LIB( IGUIStringConv_iconv);	
	GUI_REGISTER_INTERFACE_LIB( IGUIFileSys_cocoa);
    //GUI_REGISTER_INTERFACE_LIB( "IGUIMouse", IGUIMouse_winapi);
    GUI_REGISTER_INTERFACE_LIB( IGUIFont_cocoa);
    //GUI_REGISTER_INTERFACE_LIB( "IGUIKeyboard", IGUIKeyboard_winapi);
    GUI_REGISTER_INTERFACE_LIB( IGUIConfigFile_tinyxml);
    GUI_REGISTER_INTERFACE_LIB( IGUIScript_lua);
	
    //register widget
    guiex::CGUIWidgetGenerator** pGenerator = guiex::GetAllGenerators();
    while(*pGenerator)
    {
        guiex::CGUIWidgetFactory::Instance()->RegisterGenerator( *pGenerator);
        pGenerator ++;
    }
	
	InitWidgets();
}

void CLibGuiexEngine::InitWidgets()
{	
	if( 0 != guiex::CGUISceneInfoManager::Instance()->LoadScenes("test/", ".uip"))
	{
		return;
	}
	
	for( size_t i=0; i<guiex::CGUISceneInfoManager::Instance()->GetSceneFilePaths().size(); ++i )
	{
		printf("scene: %s\n", guiex::CGUISceneInfoManager::Instance()->GetSceneFilePaths()[i].c_str());
	}
	
	if( 0 != guiex::CGUISceneUtility::LoadResource( "common.uip" ))
	{
		return;
	}		
	
#if 1
	guiex::CGUIWidget* pWidget = guiex::CGUIWidgetManager::Instance()->LoadPage( "dialog_ok.xml", "common.uip");

	
	guiex::CGUIAsContainer* pAsContainer = guiex::CGUIAsManager::Instance()->AllocateResource<guiex::CGUIAsContainer>( );
	pAsContainer->SetLooping(true);
	pAsContainer->SetReceiver( pWidget );
	
	
	guiex::CGUIAsScale* pAsScale = guiex::CGUIAsManager::Instance()->AllocateResource<guiex::CGUIAsScale>( );
	pAsScale->SetInterpolationValue( guiex::CGUISize(0.1,0.1), guiex::CGUISize(1,1), 2 );
	//pAsScale->SetInterpolationType(guiex::eInterpolationType_EaseInOut);
	pAsContainer->AddItem( pAsScale, 0.0f );
	pAsScale->RefRelease();	
	
	pAsScale = guiex::CGUIAsManager::Instance()->AllocateResource<guiex::CGUIAsScale>( );
	pAsScale->SetInterpolationValue( guiex::CGUISize(1,1), guiex::CGUISize(0.1,0.1), 2 );
	//pAsScale->SetInterpolationType(guiex::eInterpolationType_EaseInOut);
	pAsContainer->AddItem( pAsScale, 2.0f );
	pAsScale->RefRelease();	
	
	pWidget->PlayAs( pAsContainer );
	pAsContainer->RefRelease();
	
	guiex::CGUISystem::Instance()->OpenPage(pWidget);	
	
#else
	guiex::CGUIWidget* pWidget_staticimage = GUI_CREATE_WIDGET("CGUIWgtStaticImage", "staticimage_0", "hello_ipad");
	pWidget_staticimage->SetImage( "BGIMAGE", "bg_blue" );
	pWidget_staticimage->SetSize( 200, 200 );
	pWidget_staticimage->SetPosition( 200, 200 );
	pWidget_staticimage->SetAnchorPoint( 0.5, 0.5 );
	pWidget_staticimage->Create();
	
	guiex::CGUIWidget* pWidget_staticimage2 = GUI_CREATE_WIDGET("CGUIWgtStaticImage", "staticimage_2", "hello_ipad");
	pWidget_staticimage2->SetParent( pWidget_staticimage );
	pWidget_staticimage2->SetImage( "BGIMAGE", "bg_blue" );
	pWidget_staticimage2->SetSize( 100, 100 );
	pWidget_staticimage2->SetPosition( 0, 0 );
	pWidget_staticimage2->SetAnchorPoint( 0.5, 0.5 );
	pWidget_staticimage2->SetRotation( 0.0f, 0.0f, 45.0f );
	pWidget_staticimage2->Create();	
	
	{
		guiex::CGUIAsScale* pAsScale = guiex::CGUIAsManager::Instance()->AllocateResource<guiex::CGUIAsScale>();
		pAsScale->SetInterpolationValue( guiex::CGUISize(0.1,0.1), guiex::CGUISize(1,1), 1 );
		pAsScale->SetReceiver( pWidget_staticimage );
		//pAsScale->SetLooping( true );
		pAsScale->SetInterpolationType(guiex::eInterpolationType_EaseIn);
		pWidget_staticimage->PlayAs( pAsScale );	
		pAsScale->RefRelease();
	}
	
	{
		guiex::CGUIAsAlpha* pAsAlpha = guiex::CGUIAsManager::Instance()->AllocateResource<guiex::CGUIAsAlpha>( );
		pAsAlpha->SetInterpolationValue( 0, 1, 1 );
		pAsAlpha->SetReceiver( pWidget_staticimage2 );
		pAsAlpha->SetLooping( true );
		pAsAlpha->SetInterpolationType(guiex::eInterpolationType_EaseInOut);
		pWidget_staticimage2->PlayAs( pAsAlpha );
		pAsAlpha->RefRelease();
	}
	
	
	guiex::CGUIWidgetManager::Instance()->AddPage(pWidget_staticimage);
	guiex::CGUISystem::Instance()->OpenPage(pWidget_staticimage); 
#endif 
}



void CLibGuiexEngine::Update( float deltaTime )
{
	guiex::CGUISystem::Instance()->Update( deltaTime );
	guiex::CGUISystem::Instance()->Render();
	
	static float fFpsTimer = 0.0f;
	fFpsTimer += deltaTime;
	if( fFpsTimer >= 3.0f )
	{
		fFpsTimer = 0.0f;
		printf( "fps = %d\n", guiex::CGUISystem::Instance()->GetFPS());
	}
}

void CLibGuiexEngine::OnRotate( DeviceOrientation newOrientation )
{
}

void CLibGuiexEngine::OnFingerUp(float x, float y)
{
}

void CLibGuiexEngine::OnFingerDown(float x,float y)
{
}

void CLibGuiexEngine::OnFingerMove(float oldx, float oldy, float x, float y)
{
}


