/** 
* @file guimusicmanager.h
* @brief music data manager.
* @author ken
* @date 2011-01-06
*/

#ifndef __GUI_MUSICMANAGER_20110106_H__
#define __GUI_MUSICMANAGER_20110106_H__

//============================================================================//
// include
//============================================================================// 
#include "guibase.h"
#include "guistring.h"
#include "guimusicdata.h"
#include "guiresourcemanager.h"
#include <set>
#include <map>


//============================================================================//
// declare
//============================================================================// 
namespace guiex
{
	class CGUIProperty;
}

//============================================================================//
// class
//============================================================================// 
namespace guiex
{
	/**
	* @class CGUIMusicManager
	* @brief music manager
	* 
	*/
	class GUIEXPORT CGUIMusicManager : public CGUIResourceManager <CGUIMusicData>
	{
	public:
		CGUIMusicManager();
		virtual ~CGUIMusicManager();

		static CGUIMusicManager* Instance(); 

		int32 RegisterMusic( const CGUIString& rSceneName, const CGUIProperty& rProperty);
		CGUIMusicData* AllocateResource( const CGUIString& rMusicName ) const;
		int32 DeallocateResource( CGUIMusicData* pMusic );

	protected:
		virtual	void DestroyResourceImp( void* pRes ); 
		
		CGUIMusicData* DoCreateMusic(
			const CGUIString& rName, 
			const CGUIString& rSceneName, 
			const CGUIString& rPath);

	private:
		static CGUIMusicManager* m_pSingleton;
	};

}//namespace guiex

#endif //__GUI_MUSICMANAGER_20110106_H__

