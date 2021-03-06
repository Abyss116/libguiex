/** 
* @file guiwgtlistboxitem.h
* @brief list box item
* @author ken
* @date 2011-07-07
*/

#ifndef __GUI_WGT_LISTBOXITEM_20110707_H__
#define __GUI_WGT_LISTBOXITEM_20110707_H__

//============================================================================//
// include
//============================================================================// 
#include <libguiex_core/guiwidget.h>
#include <libguiex_core/guiwidgetgenerator.h>

//============================================================================//
// declare
//============================================================================// 
namespace guiex
{
	class CGUIWgtListBox;
}//namespace guiex

//============================================================================//
// class
//============================================================================// 
namespace guiex
{
	/**
	* @class CGUIWgtListBoxItem
	* @brief base item for list box
	* used image name:
	* 	- normal
	*	- selected
	*/
	class GUIEXPORT CGUIWgtListBoxItem : public CGUIWidget
	{
	public:
		CGUIWgtListBoxItem( const CGUIString& rName, const CGUIString& rSceneName );
		virtual ~CGUIWgtListBoxItem(void);

		CGUIWgtListBox*	GetListBox();

		bool IsSelected( void ) const;
		void SetSelected( bool bSelect );

		void* GetUserData(void) const;
		void SetUserData(void* pUserData);

		void SetItemContent(const CGUIStringW& rText);
		void SetItemContentUTF8( const CGUIString& rString);
		CGUIString GetItemContentUTF8( ) const;
		const CGUIStringW& GetItemContent( ) const;

	protected:
		//init item
		void InitListboxItem();

		//render self
		virtual void RenderSelf(IGUIInterfaceRender* pRender);
		virtual void OnSetImage( const CGUIString& rName, CGUIImage* pImage );


	protected:	//!< callback function
		virtual uint32 OnMouseLeftDown( CGUIEventMouse* pEvent );
		virtual uint32 OnMouseLeftUp( CGUIEventMouse* pEvent );
		virtual uint32 OnMouseRightDown( CGUIEventMouse* pEvent );
		virtual uint32 OnMouseRightUp( CGUIEventMouse* pEvent );
		virtual uint32 OnMouseRightClick( CGUIEventMouse* pEvent );
		virtual uint32 OnMouseLeftClick( CGUIEventMouse* pEvent );
		virtual uint32 OnMouseRightDbClick( CGUIEventMouse* pEvent );
		virtual uint32 OnMouseLeftDbClick( CGUIEventMouse* pEvent );
		virtual uint32 OnMouseMove( CGUIEventMouse* pEvent );
		virtual uint32 OnParentChanged( CGUIEventRelativeChange* pEvent );

	protected:
		void* m_pUserData; //!< user data
		CGUIStringW m_strItemContent;
		bool m_bSelected; //!< whether this item is selected

		CGUIImage* m_pImageNormal; //!< normal bg image 
		CGUIImage* m_pImageSelected; //!< selected bg image 

		CGUIWgtListBox* m_pListBox;

	private:
		GUI_WIDGET_GENERATOR_DECLARE(CGUIWgtListBoxItem);
	};

}//namespace guiex

#endif //__GUI_WGT_LISTBOXITEM_20110707_H__
