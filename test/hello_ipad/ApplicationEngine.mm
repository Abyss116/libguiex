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
#include <libguiex_framework/guiframework.h>
using namespace guiex;


class CGUIFrameworkTest : public CGUIFramework
{
	public:
		CGUIFrameworkTest(  )
			:CGUIFramework(  )
		{
		}
};

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
	CGUIFrameworkTest* m_pFramework;
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
	:m_pFramework( NULL )
{
}

CLibGuiexEngine::~CLibGuiexEngine()
{
	if( m_pFramework )
	{
		m_pFramework->Release();
		delete m_pFramework;
		m_pFramework = NULL;
	}
}

void CLibGuiexEngine::Initialize( int width, int height, const char* szDataPath )
{
	m_pFramework = new CGUIFrameworkTest(  );
	m_pFramework->Initialize( CGUISize( width, height ), (CGUIString(szDataPath) + "/test/").c_str() );
	
	InitWidgets();
}

void CLibGuiexEngine::InitWidgets()
{	
	CGUISceneManager::Instance()->RegisterScenesFromDir("/", ".uip");
	CGUISceneManager::Instance()->LoadResources( "common.uip" );
	CGUISceneManager::Instance()->LoadWidgets( "common.uip" );
	CGUIWidget* pWidget = CGUIWidgetManager::Instance()->GetPage( "common.uip", "dialog_ok.xml" );
	CGUISystem::Instance()->OpenPage(pWidget);	
}


void CLibGuiexEngine::Update( float deltaTime )
{
	m_pFramework->Update( deltaTime );
	m_pFramework->Render();
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


