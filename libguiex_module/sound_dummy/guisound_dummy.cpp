/** 
 * @file guisound_dummy.cpp
 * @brief sound module, use openal
 * @author ken
 * @date 2006-08-31
 */

//============================================================================//
// include
//============================================================================// 
#include "guisound_dummy.h"
#include "guisounddata_dummy.h"
#include <libguiex_core/guiexception.h>
#include <libguiex_core/guisystem.h>


//============================================================================//
// function
//============================================================================// 
namespace guiex
{
	//------------------------------------------------------------------------------
	GUI_INTERFACE_IMPLEMENT(IGUISound_dummy);
	//------------------------------------------------------------------------------
	const char* IGUISound_dummy::StaticGetModuleName()
	{
		return "IGUISound_dummy";
	}
	//------------------------------------------------------------------------------
	IGUISound_dummy::IGUISound_dummy()
	:IGUIInterfaceSound( StaticGetModuleName() )
	{
	}
	//------------------------------------------------------------------------------
	IGUISound_dummy::~IGUISound_dummy()
	{
	}
	//------------------------------------------------------------------------------
	int IGUISound_dummy::DoInitialize(void* )
	{
		return 0;
	}
	//------------------------------------------------------------------------------
	void IGUISound_dummy::DoDestroy()
	{
	}
	//------------------------------------------------------------------------------
	void IGUISound_dummy::DeleteSelf()
	{
		delete this;
	}
	//------------------------------------------------------------------------------
	CGUISoundData* IGUISound_dummy::CreateSoundData( const CGUIString& rName, const CGUIString& rSceneName, const CGUIString& rPath, uint32 nSoundID )
	{
		if( m_mapSoundData.find( nSoundID ) != m_mapSoundData.end() )
		{
			throw CGUIException("[IGUISound_dummy::CreateSoundData]: the sound <%d> has existing", nSoundID );
			return NULL;
		}
		CGUISoundData_dummy* pSoundData = new CGUISoundData_dummy( rName, rSceneName, rPath, nSoundID );
		m_mapSoundData.insert( std::make_pair( nSoundID, pSoundData ) );
		return pSoundData;
	}
	//------------------------------------------------------------------------------
	void IGUISound_dummy::DestroySoundData( CGUISoundData* pData )
	{
		GUI_ASSERT( pData, "invalid parameter" );
		for( TMapSoundData::iterator itor = m_mapSoundData.begin();
			itor != m_mapSoundData.end();
			++itor )
		{
			if( itor->second == pData )
			{
				delete pData;
				m_mapSoundData.erase( itor );
				return;
			}
		}
		throw CGUIException(
			"[IGUISound_dummy::DestroySoundData]: the sound <%s:%s> doesn't existing", 
			pData->GetName().c_str(),
			pData->GetSceneName().c_str());
		return;
	}
	//------------------------------------------------------------------------------
	int32 IGUISound_dummy::LoadEffect( int32 /*nID*/,  const CGUIString& /*rFileName*/)
	{
		return 0;
	}
	//------------------------------------------------------------------------------
	void IGUISound_dummy::UnloadEffect( int32 /*nID*/ )
	{
	}
	//------------------------------------------------------------------------------
	int32 IGUISound_dummy::PlayEffect( int32 /*nID*/ )
	{
		return 0;
	}
	//------------------------------------------------------------------------------
	
}//namespace guiex
