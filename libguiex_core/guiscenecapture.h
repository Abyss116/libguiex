/** 
 * @file guiscenecapture.h
 * @brief 
 * @author Lou Guoliang (louguoliang@gmail.com)
 * @date 2011-03-15
 */


#ifndef __KEN_GUISCENECAPTURE_20110315_H__
#define	__KEN_GUISCENECAPTURE_20110315_H__


//============================================================================//
// include
//============================================================================//
#include "guibase.h"
#include "guireference.h"

//============================================================================//
// declare
//============================================================================// 
namespace guiex
{
	class IGUIInterfaceRender;
	class CGUITexture;
}

//============================================================================//
// class
//============================================================================//
namespace guiex
{
	class GUIEXPORT CGUISceneCapture : public CGUIReference
	{
	public:
		CGUISceneCapture( );

		virtual int32 Initialize( uint32 uTextureWidth, uint32 uTextureHeight );
		virtual void Release( );

		virtual void RefRelease();

		virtual void BeforeRender( IGUIInterfaceRender* pRender );
		virtual void AfterRender( IGUIInterfaceRender* pRender );

	protected:
		virtual ~CGUISceneCapture();
		virtual void ProcessCaptureTexture( IGUIInterfaceRender* pRender ) = 0;

	protected:
		CGUITexture* m_pTexture; //!< texture

	private:
		uint32 m_fbo;
		int32 m_oldfbo;
	};
}

#endif //__KEN_GUISCENECAPTURE_20110315_H__
