/** 
 * @file guisceneeffectgrid3d.cpp
 * @brief 
 * @author Lou Guoliang (louguoliang@gmail.com)
 * @date 2011-03-15
 */


//============================================================================//
// include
//============================================================================//
#include "guisceneeffectgrid3d.h"
#include "guiexception.h"
#include "guiinterfacerender.h"
#include "guitexture.h"
#include "guitexturemanager.h"
#include "guirendertype.h"
#include "guirect.h"

//TEMP
#include "guiimage.h"
#include "guiimagemanager.h"

//============================================================================//
// function
//============================================================================//

namespace guiex
{
	//------------------------------------------------------------------------------
	CGUISceneEffectGrid3D::CGUISceneEffectGrid3D( const CGUISize& rSceneSize, const CGUIIntSize& rGridSize )
		:CGUISceneEffectGridBase( rSceneSize, rGridSize )
		,m_pTexCoordinates( NULL )
		,m_pVertices( NULL )
		,m_pOriginalVertices( NULL )
		,m_pIndices( NULL )
	{

	}
	//------------------------------------------------------------------------------
	CGUISceneEffectGrid3D::~CGUISceneEffectGrid3D()
	{

	}
	//------------------------------------------------------------------------------
	int32 CGUISceneEffectGrid3D::Initialize(  )
	{
		//call parent function
		if( CGUISceneEffectGridBase::Initialize( ) != 0 )
		{
			return -1;
		}

		// allocating data space
		m_pVertices = new SR_V3F[(m_aGridSize.m_uWidth+1)*(m_aGridSize.m_uHeight+1)];
		m_pOriginalVertices = new SR_V3F[(m_aGridSize.m_uWidth+1)*(m_aGridSize.m_uHeight+1)];
		m_pTexCoordinates = new SR_T2F[(m_aGridSize.m_uWidth+1)*(m_aGridSize.m_uHeight+1)];
		m_pIndices = new uint16[ m_aGridSize.m_uWidth * m_aGridSize.m_uHeight * 6];

		for( uint32 x = 0; x < m_aGridSize.m_uWidth; x++ )
		{
			for( uint32 y = 0; y < m_aGridSize.m_uHeight; y++ )
			{
				uint16 idxTL = x * (m_aGridSize.m_uHeight+1) + y; //top left
				uint16 idxTR = (x+1) * (m_aGridSize.m_uHeight+1) + y; //top right
				uint16 idxBR = (x+1) * (m_aGridSize.m_uHeight+1) + (y+1); //bottom right
				uint16 idxBL = x * (m_aGridSize.m_uHeight+1) + (y+1); //bottom left

				uint16	tempidx[6] = { idxTL, idxBL, idxTR, idxBR, idxTR, idxBL };
				int idx = (y * m_aGridSize.m_uWidth) + x;
				memcpy( &m_pIndices[6*idx], tempidx, 6*sizeof(uint16) );

				real x1 = x * m_aStep.x;
				real x2 = x1 + m_aStep.x;
				real y1 = y * m_aStep.y;
				real y2 = y1 + m_aStep.y;

				SR_V3F	vTL = {x1,y1,0}; //top left
				SR_V3F	vTR = {x2,y1,0}; //top right
				SR_V3F	vBR = {x2,y2,0}; //bottom right
				SR_V3F	vBL = {x1,y2,0}; //bottom left

				uint16 indexs[4] = { idxTL, idxTR, idxBR, idxBL };
				SR_V3F vertices[4] = { vTL, vTR, vBR, vBL };

				for( int32 i = 0; i < 4; i++ )
				{
					m_pVertices[ indexs[i] ] = vertices[i];

					m_pTexCoordinates[ indexs[i] ].u = vertices[i].x / m_pTexture->GetWidth();
					if( m_bIsTextureFlipped )
					{
						m_pTexCoordinates[ indexs[i] ].v = m_pTexture->UVConvertTopleft2Engine_v( (m_aSceneSize.m_fHeight - vertices[i].y) / m_pTexture->GetHeight());
					}
					else
					{
						m_pTexCoordinates[ indexs[i] ].v = m_pTexture->UVConvertTopleft2Engine_v(vertices[i].y / m_pTexture->GetHeight());
					}
				}
			}
		}

		memcpy(m_pOriginalVertices, m_pVertices, (m_aGridSize.m_uWidth+1)*(m_aGridSize.m_uHeight+1)*sizeof(SR_V3F));


		return 0;
	}
	//------------------------------------------------------------------------------
	void CGUISceneEffectGrid3D::Release( )
	{
		if( m_pTexCoordinates )
		{
			delete[] m_pTexCoordinates;
			m_pTexCoordinates = NULL;
		}
		if( m_pVertices )
		{
			delete[] m_pVertices;
			m_pVertices = NULL;
		}
		if( m_pOriginalVertices )
		{
			delete[] m_pOriginalVertices;
			m_pOriginalVertices = NULL;
		}
		if( m_pIndices )
		{
			delete[] m_pIndices;
			m_pIndices = NULL;
		}

		CGUISceneEffectGridBase::Release();
	}
	//------------------------------------------------------------------------------
	void CGUISceneEffectGrid3D::ProcessCaptureTexture( IGUIInterfaceRender* pRender )
	{
		uint32 n = m_aGridSize.m_uWidth * m_aGridSize.m_uHeight;
		pRender->DrawGrid( m_pTexture, m_pTexCoordinates, m_pVertices, m_pIndices, n );
		
		//pRender->DrawTile( 
		//	CGUIRect( CGUIVector2(), m_aSceneSize ), 
		//	0, 
		//	m_pTexture, 
		//	CGUIRect(0,0,m_aSceneSize.GetWidth() / m_pTexture->GetWidth(), m_aSceneSize.GetHeight() / m_pTexture->GetHeight()),  
		//	eImageOrientation_Normal, 
		//	CGUIColor());
	}
	//------------------------------------------------------------------------------
	/** 
	* returns the vertex than belongs to certain position in the grid 
	*/
	const SR_V3F& CGUISceneEffectGrid3D::GetVertex( uint32 uX, uint32 uY )
	{
		GUI_ASSERT( uX <= m_aGridSize.m_uWidth && uY <= m_aGridSize.m_uHeight, "invalid pos" );

		int	index = (uX * (m_aGridSize.m_uHeight+1) + uY);
		return m_pVertices[index]; 
	}
	//------------------------------------------------------------------------------
	/** 
	* returns the non-transformed vertex than belongs to certain position in the grid 
	*/
	const SR_V3F& CGUISceneEffectGrid3D::GetOriginalVertex( uint32 uX, uint32 uY )
	{
		GUI_ASSERT( uX <= m_aGridSize.m_uWidth && uY <= m_aGridSize.m_uHeight, "invalid pos" );
		
		int	index = (uX * (m_aGridSize.m_uHeight+1) + uY);
		return m_pOriginalVertices[index];
	}
	//------------------------------------------------------------------------------
	/**
	 * sets a new vertex to a certain position of the grid 
	 */
	void CGUISceneEffectGrid3D::SetVertex( uint32 uX, uint32 uY, const SR_V3F& rVertex )
	{
		GUI_ASSERT( uX <= m_aGridSize.m_uWidth && uY <= m_aGridSize.m_uHeight, "invalid pos" );

		int	index = (uX * (m_aGridSize.m_uHeight+1) + uY);
		m_pVertices[index] = rVertex;
	}
	//------------------------------------------------------------------------------
}//namespace guiex
