/** 
 * @file guisceneeffectgrid3d.h
 * @brief 
 * @author Lou Guoliang (louguoliang@gmail.com)
 * @date 2011-03-16
 */


#ifndef __KEN_GUISCENEEFFECTGRID3D_20110316_H__
#define	__KEN_GUISCENEEFFECTGRID3D_20110316_H__


//============================================================================//
// include
//============================================================================//
#include "guisceneeffectgridbase.h"
#include "guivector2.h"

//============================================================================//
// declare
//============================================================================// 
namespace guiex
{
	class IGUIInterfaceRender;
	struct SVertexFormat_T2F_C4UB;
	struct SVertexFormat_V3F;
}

//============================================================================//
// class
//============================================================================//
namespace guiex
{
	class GUIEXPORT CGUISceneEffectGrid3D : public CGUISceneEffectGridBase
	{
	public:
		CGUISceneEffectGrid3D( const CGUISize& rSceneSize, const CGUIIntSize& rGridSize );

		virtual int32 Initialize( );
		virtual void Release( );

		virtual void Reset( );

		void SetTextureFlipped( bool bFlipped );
		bool IsTextureFlipped() const;

		const SVertexFormat_V3F& GetVertex( uint32 uX, uint32 uY );
		const SVertexFormat_V3F& GetOriginalVertex( uint32 uX, uint32 uY );
		void SetVertex( uint32 uX, uint32 uY, const SVertexFormat_V3F& rVertex );

	protected:
		virtual ~CGUISceneEffectGrid3D();
		virtual void ProcessCaptureTexture( IGUIInterfaceRender* pRender );

	protected:
		SVertexFormat_T2F_C4UB *m_pVerticeInfos;
		SVertexFormat_V3F *m_pVertices;
		SVertexFormat_V3F *m_pOriginalVertices;
		uint16 *m_pIndices;
	};
}//namespace guiex

#endif //__KEN_GUISCENEEFFECTGRID3D_20110316_H__
