/** 
 * @file guicanvaslayer.h
 * @brief canvas layer used in system
 * @author ken
 * @date 2010-12-22
 */

#ifndef __GUI_CANVASLAYER_20101222_H__
#define __GUI_CANVASLAYER_20101222_H__

//============================================================================//
// include
//============================================================================// 
#include "guibase.h"

//============================================================================//
// class
//============================================================================// 
namespace guiex
{
	class GUIEXPORT CGUICanvasLayer
	{
	public:
		CGUICanvasLayer( const char* szLayerName );
		virtual ~CGUICanvasLayer();

		virtual void Update( real fDeltaTime );
		virtual void Render( class IGUIInterfaceRender* pRender );

		virtual void DestroySelf( ) = 0;

		const CGUIString& GetLayerName( ) const;

	private:
		CGUIString m_strLayerName;
	};

}//namespace guiex

#endif //__GUI_CANVASLAYER_20101222_H__