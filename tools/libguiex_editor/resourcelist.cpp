/** 
 * @file resourcelist.cpp
 * @brief 
 * @author Lou Guoliang (louguoliang@gmail.com)
 * @date 2010-12-24
 */


//============================================================================//
// include
//============================================================================//
#include "resourcelist.h"
#include "editorutility.h"
#include <wx/filename.h> 



//============================================================================//
// function
//============================================================================//
//------------------------------------------------------------------------------
CResourceList::CResourceList()
{
}
//------------------------------------------------------------------------------
CResourceList::~CResourceList()
{
	ResetImageList();
	ResetAsList();
}
//------------------------------------------------------------------------------
CResourceList* CResourceList::Instance()
{
	static CResourceList sInstance;
	return &sInstance;
}
//------------------------------------------------------------------------------
void CResourceList::UpdateResourceList()
{
	UpdateImageList();
	UpdateAsNameList();
}
//------------------------------------------------------------------------------
void CResourceList::ResetImageList()
{
	m_arrayImageArray.Clear();
	for( std::map<wxString, wxBitmap*>::iterator itor = m_mapImageThumbnails.begin();
		itor != m_mapImageThumbnails.end();
		++itor )
	{
		delete itor->second;
	}
	m_mapImageThumbnails.clear();
}
//------------------------------------------------------------------------------
void CResourceList::UpdateImageList()
{
	ResetImageList();

	m_arrayImageArray.Add(_T(""));
	const std::map<CGUIString, CGUIImage*>& rMapImageList = CGUIImageManager::Instance()->GetRegisterResourceMap();
	for( std::map<CGUIString,CGUIImage*>::const_iterator itor = rMapImageList.begin();
		itor != rMapImageList.end();
		++itor)
	{
		CGUIImage* pGuiImage = itor->second;
		const CGUIString& rGuiImageName = itor->first;
		wxString rWxImageName = Gui2wxString( rGuiImageName );

		m_arrayImageArray.Add( rWxImageName );

		// Create the image thumbnail
		wxString rImagePath = Gui2wxString( GSystem->GetDataPath() + CGUISceneManager::Instance()->GetScenePath( pGuiImage->GetSceneName() ) + pGuiImage->GetFilePath() );
		wxFileName filename( rImagePath );
		if ( filename.FileExists() )
		{
			wxImage* pWxImage = new wxImage( filename.GetFullPath(), wxBITMAP_TYPE_TGA );
			if ( pWxImage && pWxImage->Ok() )
			{
				const CGUIRect& rRect = pGuiImage->GetUVRect();
				wxSize newSize( 
					pWxImage->GetSize().GetWidth() * rRect.GetWidth(), 
					pWxImage->GetSize().GetHeight()* rRect.GetHeight() );
				wxPoint newPoint( 
					rRect.GetPosition().x * pWxImage->GetSize().GetWidth(), 
					rRect.GetPosition().y * pWxImage->GetSize().GetHeight() );
				pWxImage->Resize( newSize, -newPoint );
				switch( pGuiImage->GetOrientation() )
				{
				case eImageOrientation_90CW:
					pWxImage->Rotate90( true );
					break;
				case eImageOrientation_90CCW:
					pWxImage->Rotate90( false );
					break;
				case eImageOrientation_FlipHorizon:
					pWxImage->Mirror( true );
					break;
				case eImageOrientation_FlipVertical:
					pWxImage->Mirror( false );
					break;
				}

				int im_wid = pWxImage->GetWidth();
				int im_hei = pWxImage->GetHeight();
				if ( pWxImage->GetWidth() > pWxImage->GetHeight() )
				{
					// TNW = (TNH*IW)/IH
					im_wid = PREF_THUMBNAIL_HEIGHT;
					im_hei = PREF_THUMBNAIL_HEIGHT * pWxImage->GetHeight() / pWxImage->GetWidth();
				}
				else
				{
					im_hei = PREF_THUMBNAIL_HEIGHT;
					im_wid = (PREF_THUMBNAIL_HEIGHT*pWxImage->GetWidth())/pWxImage->GetHeight();
				}
				pWxImage->Rescale( im_wid, im_hei );

				wxBitmap* pBitmap = new wxBitmap( *pWxImage );
				m_mapImageThumbnails[rWxImageName] = pBitmap;

				delete pWxImage;
			}
		}
	}
	m_arrayImageArray.Sort();
}
//------------------------------------------------------------------------------
const wxBitmap* CResourceList::GetImageThumbnail( const wxString& rImageName )
{
	std::map<wxString, wxBitmap*>::iterator itor = m_mapImageThumbnails.find( rImageName );
	if( itor != m_mapImageThumbnails.end() )
	{
		return itor->second;
	}
	return NULL;
}
//------------------------------------------------------------------------------
void CResourceList::ResetAsList()
{
	m_arrayAsArray.Clear();
}
//------------------------------------------------------------------------------
void CResourceList::UpdateAsNameList()
{
	ResetAsList();

	m_arrayAsArray.Add(_T(""));
	const std::map<CGUIString, CGUIAs*>& rMapAsList = CGUIAsManager::Instance()->GetRegisterResourceMap();
	for( std::map<CGUIString,CGUIAs*>::const_iterator itor = rMapAsList.begin();
		itor != rMapAsList.end();
		++itor)
	{
		m_arrayAsArray.Add(Gui2wxString( itor->first));
	}
	m_arrayAsArray.Sort();
}
//------------------------------------------------------------------------------
const wxArrayString& CResourceList::GetImageList()
{
	return m_arrayImageArray;
}
//------------------------------------------------------------------------------
const wxArrayString& CResourceList::GetAsList()
{
	return m_arrayAsArray;
}
//------------------------------------------------------------------------------
