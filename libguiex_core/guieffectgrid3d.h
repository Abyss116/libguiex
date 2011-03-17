/** 
 * @file guieffectgrid3d.h
 * @brief 
 * @author Lou Guoliang (louguoliang@gmail.com)
 * @date 2011-03-16
 */


#ifndef __KEN_GUIEFFECTGRID3D_20110316_H__
#define	__KEN_GUIEFFECTGRID3D_20110316_H__


//============================================================================//
// include
//============================================================================//
#include "guieffectgridbase.h"
#include "guivector2.h"

//============================================================================//
// declare
//============================================================================// 
namespace guiex
{
	class IGUIInterfaceRender;
	struct SR_T2F;
	struct SR_V3F;
	struct SR_V3F;
}

//============================================================================//
// class
//============================================================================//
namespace guiex
{
	class GUIEXPORT CGUIEffectGrid3D : public CGUIEffectGridBase
	{
	public:
		CGUIEffectGrid3D( const CGUIIntSize& rSceneSize, const CGUIIntSize& rGridSize );

		virtual int32 Initialize( );
		virtual void Release( );

		void SetTextureFlipped( bool bFlipped );
		bool IsTextureFlipped() const;

	protected:
		virtual ~CGUIEffectGrid3D();
		virtual void ProcessCaptureTexture( IGUIInterfaceRender* pRender );

	protected:
		SR_T2F *m_pTexCoordinates;
		SR_V3F *m_pVertices;
		SR_V3F *m_pOriginalVertices;
		uint16 *m_pIndices;
	};
}

#endif //__KEN_GUIEFFECTGRID3D_20110316_H__
