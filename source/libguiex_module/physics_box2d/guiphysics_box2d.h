/** 
* @file guiphysics_box2d.h
* @brief use box2d as physics engine
* @author ken
* @date 2010-12-21
*/

#ifndef __GUI_PHYSICS_BOX2D_20101221_H__
#define __GUI_PHYSICS_BOX2D_20101221_H__

//============================================================================//
// include
//============================================================================// 
#include <libguiex_core/guiinterfacephysics.h>
#include <vector>

//============================================================================//
// class
//============================================================================// 
class b2World;
class b2Draw;

namespace guiex
{

	class GUIEXPORT IGUIPhysics_box2d : public IGUIInterfacePhysics
	{
	public:
		IGUIPhysics_box2d();
		virtual ~IGUIPhysics_box2d();


	public:
		virtual void DeleteSelf();
		virtual	void Update( real fDeltaTime );
		virtual void RenderExtraInfo( IGUIInterfaceRender* pRender );

		b2World* GetWorld();
		bool IsSimulating() const;
		void PauseSimulate();
		void BeginSimulate();

		static void SetMeterPixelScale( real fScale );
		static real GetMeterPixelScale( );
		static real Meter2Pixel( real fMeter );
		static real Pixel2Meter( real fPixel );

	protected:
		virtual int DoInitialize(void* );
		virtual void DoDestroy();

	protected:
		b2Draw * m_pDebugDraw;
		b2World * m_pWorld;
		static real ms_fScale;
		bool m_bSimulateWorld;

	public: 
		static const char* StaticGetModuleName();
	};

	GUI_INTERFACE_DECLARE();

}//namespace guiex

#endif //__GUI_PHYSICS_BOX2D_20101221_H__
