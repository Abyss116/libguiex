/** 
* @file guiwidgetscrollbarcontainer.cpp
* @brief widget: scrollbar container
* @author ken
* @date 2007-05-18
*/


//============================================================================//
// include 
//============================================================================// 
#include <libguiex_widget/guiwgtscrollpanel.h>
#include <libguiex_widget/guiwgtscrollbar.h>
#include <libguiex_core/guiinterfacerender.h>
#include <libguiex_core/guiwidgetsystem.h>
#include <libguiex_core/guiexception.h>
#include <libguiex_core/guistringconvertor.h>
#include <libguiex_core/guiproperty.h>
#include <libguiex_core/guipropertymanager.h>

//============================================================================//
// function
//============================================================================// 
namespace guiex
{
	//------------------------------------------------------------------------------
	GUI_WIDGET_GENERATOR_IMPLEMENT(CGUIWgtScrollPanel);
	//------------------------------------------------------------------------------
	CGUIWgtScrollPanel::CGUIWgtScrollPanel(const CGUIString& rName, const CGUIString& rSceneName)
		:CGUIWidget(StaticGetType(), rName, rSceneName)
	{
		InitScrollPanel();
	}
	//------------------------------------------------------------------------------
	CGUIWgtScrollPanel::~CGUIWgtScrollPanel(  )
	{
	}
	//------------------------------------------------------------------------------
	void CGUIWgtScrollPanel::InitScrollPanel()
	{
		m_bForceVertScrollShow = false;
		m_bForceHorzScrollShow = false;

		//
		m_UseSelfCreatedScrollbar = false;

		m_pScrollbarVert = NULL;
		m_pScrollbarHorz = NULL;

		m_pPanelBG = NULL;
		m_aScrollClientRect.SetRect( CGUIRect(0.f,0.f,0.f,0.f ));

		//set flag
		SetFocusable(true);
		SetGenerateClickEvent( true );
	}
	//------------------------------------------------------------------------------
	void CGUIWgtScrollPanel::Create()
	{
		if( m_UseSelfCreatedScrollbar )
		{
			//create scrollbar
			m_pScrollbarVert = static_cast<CGUIWgtScrollbar*>(GUI_CREATE_WIDGET("CGUIWgtScrollbar", GetName()+"_scrollbar_vert__auto__", GetSceneName()));
			m_pScrollbarVert->SetParent(this);
			m_pScrollbarVert->SetFocusAgency( true );
			m_pScrollbarVert->SetOpenWithParent( false );
			m_pScrollbarVert->EnableNotifyParent(true);
			m_pScrollbarVert->EnableAutoPosition(true);
			m_pScrollbarVert->SetScrollbarType( eSB_VERTICAL );
			m_pScrollbarVert->SetImage("SCROLLBAR_BG", GetImage("SCROLLBAR_VERTIC_BG"));
			m_pScrollbarVert->SetImage("SCROLLBAR_ARROW_NORMAL_0", GetImage("SCROLLBAR_VERTIC_ARROW_NORMAL_0"));
			m_pScrollbarVert->SetImage("SCROLLBAR_ARROW_HOVER_0", GetImage("SCROLLBAR_VERTIC_ARROW_HOVER_0"));
			m_pScrollbarVert->SetImage("SCROLLBAR_ARROW_DISABLE_0", GetImage("SCROLLBAR_VERTIC_ARROW_DISABLE_0"));
			m_pScrollbarVert->SetImage("SCROLLBAR_ARROW_PUSH_0", GetImage("SCROLLBAR_VERTIC_ARROW_PUSH_0"));
			m_pScrollbarVert->SetImage("SCROLLBAR_ARROW_NORMAL_1", GetImage("SCROLLBAR_VERTIC_ARROW_NORMAL_1"));
			m_pScrollbarVert->SetImage("SCROLLBAR_ARROW_HOVER_1", GetImage("SCROLLBAR_VERTIC_ARROW_HOVER_1"));
			m_pScrollbarVert->SetImage("SCROLLBAR_ARROW_DISABLE_1", GetImage("SCROLLBAR_VERTIC_ARROW_DISABLE_1"));
			m_pScrollbarVert->SetImage("SCROLLBAR_ARROW_PUSH_1", GetImage("SCROLLBAR_VERTIC_ARROW_PUSH_1"));
			m_pScrollbarVert->SetImage("SCROLLBAR_SLIDE_NORMAL", GetImage("SCROLLBAR_VERTIC_SLIDE_NORMAL"));
			m_pScrollbarVert->SetImage("SCROLLBAR_SLIDE_HOVER", GetImage("SCROLLBAR_VERTIC_SLIDE_HOVER"));
			m_pScrollbarVert->SetImage("SCROLLBAR_SLIDE_DISABLE", GetImage("SCROLLBAR_VERTIC_SLIDE_DISABLE"));
			m_pScrollbarVert->SetImage("SCROLLBAR_SLIDE_PUSH", GetImage("SCROLLBAR_VERTIC_SLIDE_PUSH"));
			
			m_pScrollbarHorz = static_cast<CGUIWgtScrollbar*>(GUI_CREATE_WIDGET("CGUIWgtScrollbar", GetName()+"_scrollbar_hort__auto__", GetSceneName()));
			m_pScrollbarHorz->SetParent(this);
			m_pScrollbarHorz->SetFocusAgency( true );
			m_pScrollbarHorz->SetOpenWithParent( false );
			m_pScrollbarHorz->EnableNotifyParent(true);
			m_pScrollbarHorz->EnableAutoPosition(true);
			m_pScrollbarHorz->SetScrollbarType( eSB_HORIZONAL );
			m_pScrollbarHorz->SetImage("SCROLLBAR_BG", GetImage("SCROLLBAR_HORIZON_BG"));
			m_pScrollbarHorz->SetImage("SCROLLBAR_ARROW_NORMAL_0", GetImage("SCROLLBAR_HORIZON_ARROW_NORMAL_0"));
			m_pScrollbarHorz->SetImage("SCROLLBAR_ARROW_HOVER_0", GetImage("SCROLLBAR_HORIZON_ARROW_HOVER_0"));
			m_pScrollbarHorz->SetImage("SCROLLBAR_ARROW_DISABLE_0", GetImage("SCROLLBAR_HORIZON_ARROW_DISABLE_0"));
			m_pScrollbarHorz->SetImage("SCROLLBAR_ARROW_PUSH_0", GetImage("SCROLLBAR_HORIZON_ARROW_PUSH_0"));
			m_pScrollbarHorz->SetImage("SCROLLBAR_ARROW_NORMAL_1", GetImage("SCROLLBAR_HORIZON_ARROW_NORMAL_1"));
			m_pScrollbarHorz->SetImage("SCROLLBAR_ARROW_HOVER_1", GetImage("SCROLLBAR_HORIZON_ARROW_HOVER_1"));
			m_pScrollbarHorz->SetImage("SCROLLBAR_ARROW_DISABLE_1", GetImage("SCROLLBAR_HORIZON_ARROW_DISABLE_1"));
			m_pScrollbarHorz->SetImage("SCROLLBAR_ARROW_PUSH_1", GetImage("SCROLLBAR_HORIZON_ARROW_PUSH_1"));
			m_pScrollbarHorz->SetImage("SCROLLBAR_SLIDE_NORMAL", GetImage("SCROLLBAR_HORIZON_SLIDE_NORMAL"));
			m_pScrollbarHorz->SetImage("SCROLLBAR_SLIDE_HOVER", GetImage("SCROLLBAR_HORIZON_SLIDE_HOVER"));
			m_pScrollbarHorz->SetImage("SCROLLBAR_SLIDE_DISABLE", GetImage("SCROLLBAR_HORIZON_SLIDE_DISABLE"));
			m_pScrollbarHorz->SetImage("SCROLLBAR_SLIDE_PUSH", GetImage("SCROLLBAR_HORIZON_SLIDE_PUSH"));
		}

		//create scrollbar
		if( m_pScrollbarHorz )
		{
			m_pScrollbarHorz->Create();
		}

		if( m_pScrollbarVert )
		{
			m_pScrollbarVert->Create();
		}

		CGUIWidget::Create();
	}
	//------------------------------------------------------------------------------
	void	CGUIWgtScrollPanel::UseSelfCreatedScrollbar( bool bSelfCreated )
	{
		m_UseSelfCreatedScrollbar = bSelfCreated;
	}
	//------------------------------------------------------------------------------
	bool	CGUIWgtScrollPanel::IsUseSelfCreatedScrollbar() const
	{
		return m_UseSelfCreatedScrollbar;
	}
	//------------------------------------------------------------------------------
	void		CGUIWgtScrollPanel::OnSetImage( const CGUIString& rName, CGUIImage* pImage )
	{		
		if( rName == "BGIMAGE")
		{
			m_pPanelBG = pImage;
			if( GetSize().IsEqualZero() && m_pPanelBG )
			{
				SetSize(m_pPanelBG->GetSize());
			}
		}
	}
	//------------------------------------------------------------------------------
	void	CGUIWgtScrollPanel::RenderSelf(IGUIInterfaceRender* pRender)
	{
	}
	//------------------------------------------------------------------------------
	bool	CGUIWgtScrollPanel::IsVertScrollbarAlwaysShown(void) const
	{
		return m_bForceVertScrollShow;
	}
	//------------------------------------------------------------------------------
	void	CGUIWgtScrollPanel::ForceVertScrollbarShow(bool bSetting)
	{
		if (m_bForceVertScrollShow != bSetting)
		{
			m_bForceVertScrollShow = bSetting;

			UpdateScrollbars();
		}
	}
	//------------------------------------------------------------------------------
	bool	CGUIWgtScrollPanel::IsHorzScrollbarAlwaysShown(void) const
	{
		return m_bForceHorzScrollShow;
	}
	//------------------------------------------------------------------------------
	void	CGUIWgtScrollPanel::ForceHorzScrollbarShow(bool bSetting)
	{
		if (m_bForceHorzScrollShow != bSetting)
		{
			m_bForceHorzScrollShow = bSetting;

			UpdateScrollbars();
		}
	}
	//------------------------------------------------------------------------------
	void		CGUIWgtScrollPanel::UpdateDirtyRect()
	{
		CGUIWidget::UpdateDirtyRect();

		//clip rect for client
		if( m_UseSelfCreatedScrollbar )
		{
			if( m_pScrollbarVert->IsOpen() )
			{
				m_aClientClipRect.SetWidth(m_aWidgetRect.GetWidth() - m_pScrollbarVert->GetSize().GetWidth()*m_pScrollbarVert->GetDerivedScale().GetWidth());
			}
			if( m_pScrollbarHorz->IsOpen() )
			{
				m_aClientClipRect.SetHeight(m_aWidgetRect.GetHeight() - m_pScrollbarHorz->GetSize().GetHeight()*m_pScrollbarHorz->GetDerivedScale().GetHeight());
			}
		}

		//update client rect
		m_aClientRect = m_aWidgetRect;
		m_aClientRect.SetSize(m_aScrollClientRect.GetSize());
		CGUIVector2 aWorkPos(m_aClientRect.m_fLeft, m_aClientRect.m_fTop);
		if ( m_pScrollbarHorz && m_pScrollbarHorz->IsOpen())
		{
			aWorkPos.x -=  m_pScrollbarHorz->GetCurrentPos()*GetDerivedScale().m_fWidth;
		}
		if ( m_pScrollbarVert && m_pScrollbarVert->IsOpen())
		{
			aWorkPos.y -= m_pScrollbarVert->GetCurrentPos()*GetDerivedScale().m_fHeight;
		}
		m_aClientRect.SetPosition(aWorkPos);
	}
	//------------------------------------------------------------------------------
	void	CGUIWgtScrollPanel::UpdateScrollbars(void)
	{
		if( IsOpen()==false)
		{
			if( m_pScrollbarVert && m_pScrollbarVert->IsOpen()  )
			{
				m_pScrollbarVert->Close();
			}
			if( m_pScrollbarHorz && m_pScrollbarHorz->IsOpen()  )
			{
				m_pScrollbarHorz->Close();
			}
			return;
		}

		//update Get client area size
		CGUIRect aScrollClientRect = GetRect();
		CGUIWidget* pWidget = GetChild();
		while( pWidget )
		{
			aScrollClientRect += pWidget->GetRect();
			pWidget = pWidget->GetNextSibling();
		}
		if( m_aScrollClientRect != aScrollClientRect )
		{
			m_aScrollClientRect = aScrollClientRect;
//			SetRectDirty();
		}
		

		const CGUISize&		rClientClipSize = GetClientClipRect().GetSize();
		const CGUISize&		rPageSize = GetClientRect().GetSize();

		uint32 nVertRange = 
			static_cast<uint32>(rPageSize.m_fHeight>rClientClipSize.GetHeight() ? rPageSize.m_fHeight-rClientClipSize.GetHeight() : 0);
		uint32 nHorzRange = 
			static_cast<uint32>(rPageSize.m_fWidth>rClientClipSize.GetWidth() ? rPageSize.m_fWidth-rClientClipSize.GetWidth() : 0);


		// for vertical scrollbar
		if( m_pScrollbarVert )
		{
			if( m_bForceVertScrollShow )
			{
				if( m_pScrollbarVert->IsOpen()==false  )
				{
					m_pScrollbarVert->Open();
					//SetRectDirty();
				}
			}
			else
			{
				if( nVertRange > 0 && m_pScrollbarVert->IsOpen()==false)
				{
					m_pScrollbarVert->Open();
					//SetRectDirty();
				}
				else if( nVertRange == 0 && m_pScrollbarVert->IsOpen() )
				{
					m_pScrollbarVert->Close();
					//SetRectDirty();
				}
			}

			nVertRange = static_cast<uint32>(
				GetClientRect().GetHeight()>GetClientClipRect().GetHeight() ?
				GetClientRect().GetHeight()-GetClientClipRect().GetHeight() : 0);
			m_pScrollbarVert->SetRange(nVertRange);
			m_pScrollbarVert->SetPageSize(static_cast<uint32>(GetClientClipRect().GetHeight()));
		}

		// for horizontal scrollbar
		if( m_pScrollbarHorz )
		{
			if( m_bForceHorzScrollShow )
			{
				if( m_pScrollbarHorz->IsOpen()==false )
				{
					m_pScrollbarHorz->Open();
					//SetRectDirty();
				}
			}
			else
			{
				if( nHorzRange > 0 && m_pScrollbarHorz->IsOpen()==false )
				{
					m_pScrollbarHorz->Open();
					//SetRectDirty();
				}
				else if( nHorzRange == 0 && m_pScrollbarHorz->IsOpen() )
				{
					m_pScrollbarHorz->Close();
					//SetRectDirty();
				}
			}

			nHorzRange = static_cast<uint32>(
				GetClientRect().GetWidth()>GetClientClipRect().GetWidth() ?
				GetClientRect().GetWidth()-GetClientClipRect().GetWidth() : 0 );
			m_pScrollbarHorz->SetRange(nHorzRange);
			m_pScrollbarHorz->SetPageSize(static_cast<uint32>(GetClientClipRect().GetWidth()));
		}
	}
	//------------------------------------------------------------------------------
	CGUIWgtScrollPanel*	CGUIWgtScrollPanel::FromWidget( CGUIWidget* pWidget )
	{
		if( !pWidget )
		{
			throw CGUIException("[CGUIWgtScrollPanel::FromWidget]: the given widget is nil" );
		}
		if( pWidget->GetType() != ms_strType )
		{
			throw CGUIException("[CGUIWgtScrollPanel::FromWidget]: the real type of given widget is <%s>!", pWidget->GetType().c_str());
		}
		return dynamic_cast<CGUIWgtScrollPanel *>(pWidget);
	}
//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	uint32		CGUIWgtScrollPanel::OnOpen( CGUIEventNotification* pEvent )
	{
		UpdateScrollbars();
		return CGUIWidget::OnOpen( pEvent);
	}
	//------------------------------------------------------------------------------
	uint32		CGUIWgtScrollPanel::OnScaleChange( CGUIEventNotification* pEvent )
	{
		UpdateScrollbars();
		return CGUIWidget::OnScaleChange(pEvent);
	}
	//------------------------------------------------------------------------------
	uint32		CGUIWgtScrollPanel::OnSizeChanged( CGUIEventSize* pEvent )
	{
		UpdateScrollbars();
		return CGUIWidget::OnSizeChanged(pEvent);
	}
	//------------------------------------------------------------------------------
	uint32		CGUIWgtScrollPanel::OnScrollbarScroll( CGUIEventScrollbar* pEvent )
	{
		//SetRectDirty();
		return CGUIWidget::OnScrollbarScroll( pEvent);
	}
	//------------------------------------------------------------------------------
	void		CGUIWgtScrollPanel::SetVerticalScrollbar( const CGUIString& rName)
	{
		m_strVertScrollbarName = rName;
		if( m_pScrollbarVert )
		{
			m_pScrollbarVert->SetScrollbarHost(NULL);
			m_pScrollbarVert = NULL;
		}
		if( GSystem->HasWidget(m_strVertScrollbarName, GetSceneName()) )
		{
			CGUIWidget* pWidget = GSystem->GetWidget(m_strVertScrollbarName, GetSceneName());
			if( pWidget->GetType() == CGUIWgtScrollbar::StaticGetType())
			{
				m_pScrollbarVert = (CGUIWgtScrollbar*)pWidget;
				m_pScrollbarVert->SetScrollbarHost( this );
			}
		}
	}
	//------------------------------------------------------------------------------
	void		CGUIWgtScrollPanel::SetHorizonalScrollbar( const CGUIString& rName)
	{
		m_strHorzScrollbarName = rName;
		if( m_pScrollbarHorz )
		{
			m_pScrollbarHorz->SetScrollbarHost(NULL);
			m_pScrollbarHorz = NULL;
		}
		if( GSystem->HasWidget(m_strHorzScrollbarName, GetSceneName()) )
		{
			CGUIWidget* pWidget = GSystem->GetWidget(m_strHorzScrollbarName,GetSceneName());
			if( pWidget->GetType() == CGUIWgtScrollbar::StaticGetType())
			{
				m_pScrollbarHorz = (CGUIWgtScrollbar*)pWidget;
				m_pScrollbarHorz->SetScrollbarHost( this );
			}
		}
	}
	//------------------------------------------------------------------------------
	CGUIProperty*	CGUIWgtScrollPanel::GenerateProperty(const CGUIString& rName, const CGUIString& rType )
	{
		CGUIProperty* pProperty = NULL;

		if( rName == "SHOW_VERT_SCROLLBAR" && rType=="BOOL")
		{
			pProperty = CGUIPropertyManager::Instance()->CreateProperty(
				rName, 
				rType, 
				CGUIStringConvertor::BoolToString(IsVertScrollbarAlwaysShown( )));
		}
		else if( rName == "SHOW_HORZ_SCROLLBAR" && rType=="BOOL")
		{
			pProperty = CGUIPropertyManager::Instance()->CreateProperty(
				rName, 
				rType, 
				CGUIStringConvertor::BoolToString(IsHorzScrollbarAlwaysShown( )));
		}
		else if( rName == "VERTICAL_SCROLLBAR" && rType=="CGUIString")
		{
			pProperty = CGUIPropertyManager::Instance()->CreateProperty(
				rName, 
				rType, 
				m_strVertScrollbarName);
		}
		else if( rName == "HORIZONAL_SCROLLBAR" && rType=="CGUIString")
		{
			pProperty = CGUIPropertyManager::Instance()->CreateProperty(
				rName, 
				rType, 
				m_strHorzScrollbarName);
		}

		return pProperty ? pProperty : CGUIWidget::GenerateProperty(rName, rType);
	}
	//------------------------------------------------------------------------------
	void			CGUIWgtScrollPanel::ProcessProperty( const CGUIProperty* pProperty)
	{
		CGUIWidget::ProcessProperty(pProperty);
		
		////////////////////////////////////////////////////////////////////////////////////////////////////
		//property for parent
		/*
		*<property name="SHOW_VERT_SCROLLBAR" type="BOOL" value="true" />
		*/
		if( pProperty->GetName() == "SHOW_VERT_SCROLLBAR" && pProperty->GetType()=="BOOL")
		{
			ForceVertScrollbarShow(StringToValue(pProperty->GetValue()));
		}
		else if( pProperty->GetName() == "SHOW_HORZ_SCROLLBAR" && pProperty->GetType()=="BOOL")
		{
			ForceHorzScrollbarShow(StringToValue(pProperty->GetValue()));
		}
		else if( pProperty->GetName() == "VERTICAL_SCROLLBAR" && pProperty->GetType()=="CGUIString")
		{
			SetVerticalScrollbar(pProperty->GetValue());
		}
		else if( pProperty->GetName() == "HORIZONAL_SCROLLBAR" && pProperty->GetType()=="CGUIString")
		{
			SetHorizonalScrollbar(pProperty->GetValue());
		}
	}
	//------------------------------------------------------------------------------
}//namespace guiex
