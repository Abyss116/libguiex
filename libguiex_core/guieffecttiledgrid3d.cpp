/** 
 * @file guieffecttiledgrid3d.cpp
 * @brief 
 * @author Lou Guoliang (louguoliang@gmail.com)
 * @date 2011-03-16
 */


//============================================================================//
// include
//============================================================================//
#include "guieffecttiledgrid3d.h"
#include "guiexception.h"
#include "guiinterfacerender.h"
#include "guitexture.h"
#include "guitexturemanager.h"


//============================================================================//
// function
//============================================================================//

namespace guiex
{
	//------------------------------------------------------------------------------
	CGUIEffectTiledGrid3D::CGUIEffectTiledGrid3D( const CGUIIntSize& rSceneSize, const CGUIIntSize& rGridSize )
		:CGUIEffectGridBase( rSceneSize, rGridSize )
	{

	}
	//------------------------------------------------------------------------------
	CGUIEffectTiledGrid3D::~CGUIEffectTiledGrid3D()
	{

	}
	//------------------------------------------------------------------------------
	int32 CGUIEffectTiledGrid3D::Initialize( )
	{
		if( CGUIEffectGridBase::Initialize( ) != 0 )
		{
			return -1;
		}

		return 0;
	}
	//------------------------------------------------------------------------------
	void CGUIEffectTiledGrid3D::Release( )
	{

		CGUIEffectGridBase::Release();
	}
	//------------------------------------------------------------------------------
	void CGUIEffectTiledGrid3D::ProcessCaptureTexture( IGUIInterfaceRender* pRender )
	{
		CGUIEffectGridBase::ProcessCaptureTexture( pRender );

	}
	//------------------------------------------------------------------------------
}//namespace guiex
