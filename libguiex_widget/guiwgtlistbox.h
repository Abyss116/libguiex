/** 
* @file guiwgtlistbox.h
* @brief list box
* @author ken
* @date 2006-09-18
*/
#ifndef __GUI_WGTLISTBOX_20060918_H__
#define __GUI_WGTLISTBOX_20060918_H__

//============================================================================//
// include
//============================================================================// 
#include <libguiex_core/guiwidget.h>
#include <libguiex_core/guiwidgetgenerator.h>
#include "guiwgtscrollbarcontainer.h"
#include "guiwgtscrollbarcontainer.h"

#include <vector>


//============================================================================//
// declare
//============================================================================// 
namespace guiex
{
	class CGUIWgtListBoxItem;
}

//============================================================================//
// class
//============================================================================// 
namespace guiex
{
	/**
	* @class CGUIWgtListBox
	* @brief list box
	*
	* used image name:
	* - background
	*/
	class GUIEXPORT CGUIWgtListBox : public CGUIWgtScrollbarContainer
	{
	public:
		CGUIWgtListBox( const CGUIString& rName, const CGUIString& rSceneName );
		virtual ~CGUIWgtListBox( );

		virtual int32 GenerateProperty( CGUIProperty& rProperty );
		virtual void ProcessProperty( const CGUIProperty& rProperty );

		uint32 GetItemCount(void) const;

		CGUIWgtListBoxItem*	GetItemByIndex(uint32 nIndex) const;
		uint32	GetItemIndex(const CGUIWgtListBoxItem* pItem) const;

		void AddItem(CGUIWgtListBoxItem* pItem);
		void RemoveItem( CGUIWgtListBoxItem* pItem);
		void RemoveItem( uint32 nIndex);
		void RemoveAllItems(void);

		uint32 GetSelectedItemCount(void) const;
		void GetSelectedItems( std::vector<CGUIWgtListBoxItem*>& rItems) const;
		void SetItemSelected(CGUIWgtListBoxItem* pItem, bool bSelected);
		void SetItemSelected(uint32 nItemIndex, bool bSelected);

		void ClearAllSelections(void);

		void EnableMultiselect(bool bEnable);
		bool IsMultiselectEnabled(void) const;

	protected:
		void InitListBox();

		virtual void OnSetImage( const CGUIString& rName, CGUIImage* pImage );
		virtual void RenderSelf(IGUIInterfaceRender* pRender);
		virtual void RefreshSelf();

		bool ClearAllSelections_impl(void);

		friend class CGUIWgtListBoxItem;
		void DoAddItem(CGUIWgtListBoxItem* pItem);
		void DoRemoveItem( CGUIWgtListBoxItem* pItem);

		void UpdateTotalItems( );

		virtual CGUISize GetDesiredVirtualClientSize( );

	protected:	//!< callback function
		virtual uint32 OnAddChild( CGUIEventRelativeChange* pEvent );
		virtual uint32 OnRemoveChild( CGUIEventRelativeChange* pEvent );
		virtual uint32 OnOpen( CGUIEventNotification* pEvent );
		virtual uint32 OnChildSizeChange( CGUIEventSize* pEvent );

		friend class CGUIWgtListBoxItem;
		virtual void ProcessMouseLeftDown(CGUIWgtListBoxItem* pItem, CGUIEventMouse* pEvent);
		virtual void ProcessMouseLeftUp(CGUIWgtListBoxItem* pItem, CGUIEventMouse* pEvent);
		virtual void ProcessMouseRightDown(CGUIWgtListBoxItem* pItem, CGUIEventMouse* pEvent);
		virtual void ProcessMouseRightUp(CGUIWgtListBoxItem* pItem, CGUIEventMouse* pEvent);
		virtual void ProcessMouseLeftClick(CGUIWgtListBoxItem* pItem, CGUIEventMouse* pEvent);
		virtual void ProcessMouseRightClick(CGUIWgtListBoxItem* pItem, CGUIEventMouse* pEvent);
		virtual void ProcessMouseLeftDbClick(CGUIWgtListBoxItem* pItem, CGUIEventMouse* pEvent);
		virtual void ProcessMouseRightDbClick(CGUIWgtListBoxItem* pItem, CGUIEventMouse* pEvent);
		virtual void ProcessMouseMove(CGUIWgtListBoxItem* pItem, CGUIEventMouse* pEvent);

	protected:
		typedef std::vector<CGUIWgtListBoxItem*> TListItem;
		TListItem m_aListItems; //!< list of items in the list box.

		bool m_bMultiselect; //!< true if multi-select is enabled

		CGUIImage* m_pImageBG; /// image for listbox's background

		CGUIWgtListBoxItem*	m_pLastOperateItem; /// the last item which is been operated.for multiselect

		CGUISize m_aTotalItemSize;

	private:
		GUI_WIDGET_GENERATOR_DECLARE(CGUIWgtListBox);
	};

}//namespace guiex

#endif //__GUI_WGTFLISTBOX_20060918_H__
