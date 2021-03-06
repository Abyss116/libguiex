/** 
* @file wxresourcepreviewcontainer.h
* @brief 
* @author ken
* @date 2011-09-14
*/

#ifndef __KEN_RESOURCEPREVIEWCONTAINER_20110914_H__
#define __KEN_RESOURCEPREVIEWCONTAINER_20110914_H__


//============================================================================//
// include
//============================================================================// 
#include <wx/wxprec.h>
#include <wx/propgrid/manager.h>
#include <wx/aui/aui.h>

#include <libguiex_core/guiex.h>

//============================================================================//
// class
//============================================================================// 
class WxResourcePreviewContainer : public wxPanel
{
public:
	WxResourcePreviewContainer(wxWindow* parent);
	~WxResourcePreviewContainer();

	void SetGUIProperty( const guiex::CGUIProperty* pResourceProperty );

protected:
	void CreatePreviewCanvas( const guiex::CGUIProperty* pResourceProperty );
	void DestroyPreviewCanvas();

protected:
	class WxResourcePreviewPanelBase* m_pPreviewPanel;
	wxPropertyGridManager* m_pPropertyGridMgr;
	wxAuiManager m_mgr;

protected:
	DECLARE_EVENT_TABLE()
};


#endif //__KEN_RESOURCEPREVIEWCONTAINER_20110914_H__

