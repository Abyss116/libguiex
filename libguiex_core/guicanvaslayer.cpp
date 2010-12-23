/** 
 * @file guicanvaslayer.cpp
 * @brief canvas layer used in system
 * @author ken
 * @date 2010-12-22
 */

//============================================================================//
// include 
//============================================================================// 
#include "guicanvaslayer.h"


//============================================================================//
// function
//============================================================================// 
namespace guiex
{
	//------------------------------------------------------------------------------
	CGUICanvasLayer::CGUICanvasLayer( const char* szLayerName )
	{
	}
	//------------------------------------------------------------------------------
	CGUICanvasLayer::~CGUICanvasLayer()
	{
	}
	//------------------------------------------------------------------------------
	const CGUIString& CGUICanvasLayer::GetLayerName( ) const
	{
		return m_strLayerName;
	}
	//------------------------------------------------------------------------------
	void CGUICanvasLayer::Update( real /*fDeltaTime*/ )
	{

	}
	//------------------------------------------------------------------------------
	void CGUICanvasLayer::Render( IGUIInterfaceRender* pRender )
	{

	}
	//------------------------------------------------------------------------------
}
