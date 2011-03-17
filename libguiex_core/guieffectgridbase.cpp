/** 
 * @file guieffectgridbase.cpp
 * @brief 
 * @author Lou Guoliang (louguoliang@gmail.com)
 * @date 2011-03-15
 */


//============================================================================//
// include
//============================================================================//
#include "guieffectgridbase.h"
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
	CGUIEffectGridBase::CGUIEffectGridBase( const CGUISize& rSceneSize, const CGUIIntSize& rGridSize )
		:CGUISceneCapture( rSceneSize )
		,m_aGridSize( rGridSize )
		,m_bIsTextureFlipped( false )
	{

	}
	//------------------------------------------------------------------------------
	int32 CGUIEffectGridBase::Initialize(  )
	{
		//call parent function
		if( CGUISceneCapture::Initialize( ) != 0 )
		{
			return -1;
		}

		//set step size
		m_aStep.x = m_aSceneSize.m_fWidth / m_aGridSize.m_uWidth;
		m_aStep.y = m_aSceneSize.m_fHeight / m_aGridSize.m_uHeight;

		return 0;
	}
	//------------------------------------------------------------------------------
	void CGUIEffectGridBase::Release( )
	{
		CGUISceneCapture::Release();
	}
	//------------------------------------------------------------------------------
	void CGUIEffectGridBase::SetTextureFlipped( bool bFlipped )
	{
		m_bIsTextureFlipped = bFlipped;
	}
	//------------------------------------------------------------------------------
	bool CGUIEffectGridBase::IsTextureFlipped() const
	{
		return m_bIsTextureFlipped;
	}
	//------------------------------------------------------------------------------
}//namespace guiex
