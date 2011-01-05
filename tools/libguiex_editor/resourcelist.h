/** 
 * @file resourcelist.h
 * @brief 
 * @author Lou Guoliang (louguoliang@gmail.com)
 * @date 2010-12-24
 */

#ifndef __KEN_RESOURCELIST_20101224_H__
#define	__KEN_RESOURCELIST_20101224_H__


//============================================================================//
// include
//============================================================================//
#include <wx/wxprec.h>
#include <libguiex_core/guiex.h>
#include <string>
#include <map>
#include <vector>

using namespace guiex;

// Preferred thumbnail height.
#define PREF_THUMBNAIL_HEIGHT       32

//============================================================================//
// class
//============================================================================//
class CResourceList
{
public:
	static CResourceList* Instance();

	void UpdateResourceList();

	const wxArrayString& GetImageList();
	const wxArrayString& GetAsList();
	const wxArrayString& GetSoundList();

	const wxBitmap* GetImageThumbnail( const wxString& rImageName );
	const wxBitmap* GetOriginalImageThumbnail( const wxString& rImageName );

protected:
	//update image used in the system
	void UpdateImageList();
	void ResetImageList();

	//update as used in the system
	void UpdateAsNameList();
	void ResetAsList();

	//update sound used in the system
	void UpdateSoundList();
	void ResetSoundList();

protected:
	CResourceList();
	~CResourceList();

private:
	wxArrayString m_arrayImageArray;
	std::map<wxString, wxBitmap*> m_mapImageThumbnails;
	std::map<wxString, wxBitmap*> m_mapOriginalImageThumbnails;
	wxArrayString m_arrayAsArray;
	wxArrayString m_arraySoundArray;
};


#endif //__KEN_RESOURCELIST_20101224_H__
