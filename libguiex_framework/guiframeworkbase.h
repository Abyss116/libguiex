/** 
* @file guiframeworkbase.h
* @brief framework to use this engine
* @author ken
* @date 2010-12-10
*/

#ifndef __GUI_FRAMEWORKBASE_20101210_H__
#define __GUI_FRAMEWORKBASE_20101210_H__

//============================================================================//
// include
//============================================================================// 
#include <libguiex_core/guiex.h>


//============================================================================//
// class
//============================================================================// 
namespace guiex
{
	class GUIEXPORT CGUIFrameworkBase
	{
	public:
		CGUIFrameworkBase( );
		virtual ~CGUIFrameworkBase();

		int32 Initialize( const CGUISize& rScreenSize, const char* pDataPath );
		void Release( );

		void Update( real fDeltaTime );
		void Render( );

	protected:
		virtual int32 InitializeGame( ) = 0;
		virtual void ReleaseGame( ) = 0;
		
		virtual int32 InitializeSystem( const CGUISize& rScreenSize, const char* pDataPath ) = 0;
		virtual void ReleaseSystem( ) = 0;

		virtual void PreUpdate( real fDeltaTime ) = 0;
		virtual void PostUpdate( real fDeltaTime ) = 0;
		virtual void PreRender( ) = 0;
		virtual void PostRender( ) = 0;

		void UpdateSystem( real fDeltaTime );

		virtual void OutputFatalError( const char* pErrorDesc ) = 0;

	private:
		bool m_bIsInitialized;
	};

}//namespace guiex


#endif	//__GUI_FRAMEWORKBASE_20101210_H__
