/** 
* @file guiframework_android.h
* @brief framework to use this engine
* @author ken
* @date 2011-04-28
*/

#ifndef __GUI_FRAMEWORKANDROID_20110428_H__
#define __GUI_FRAMEWORKANDROID_20110428_H__

//============================================================================//
// include
//============================================================================// 
#include "guiframeworkbase.h"


//============================================================================//
// class
//============================================================================// 
namespace guiex
{
	class GUIEXPORT CGUIFramework_Android : public CGUIFrameworkBase
	{
	public:
		CGUIFramework_Android( );
		virtual ~CGUIFramework_Android();


	protected:
		virtual int32 InitializeGame( );
		virtual void ReleaseGame( );

		virtual int32 InitializeSystem( const CGUIIntSize& rScreenSize, const char* pDataPath );
		virtual void ReleaseSystem( );

		virtual void SetupLogSystem( );
		virtual void RegisterInterfaces( );
		virtual void RegisterWidgetGenerators( );

		virtual void PreUpdate( real fDeltaTime );
		virtual void PostUpdate( real fDeltaTime );

		virtual void OutputFatalError( const char* pErrorDesc );

	private:
	};

}//namespace guiex


#endif	//__GUI_FRAMEWORKANDROID_20110428_H__

