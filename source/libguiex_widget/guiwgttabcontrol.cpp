/** 
* @file guiwgttabcontrol.cpp
* @brief tab control panel
* @author ken
* @date 2007-07-09
*/


//============================================================================//
// include 
//============================================================================// 
#include <libguiex_widget\guiwgttabcontrol.h>
#include <libguiex_widget\guiwgttabbutton.h>
#include <libguiex_core\guiinterfacerender.h>
#include <libguiex_core\guievent.h>
#include <libguiex_core\guiwidgetsystem.h>

//============================================================================//
// function
//============================================================================// 
namespace guiex
{
	//------------------------------------------------------------------------------
	GUI_WIDGET_GENERATOR_IMPLEMENT(CGUIWgtTabControl);
	//------------------------------------------------------------------------------
	CGUIString CGUIWgtTabControl::ms_strType = "CGUIWgtTabControl";
	//------------------------------------------------------------------------------
	CGUIWgtTabControl::CGUIWgtTabControl(const CGUIString& rName, const CGUIString& rProjectName)
		:CGUIWidget(ms_strType, rName, rProjectName)
	{
		InitTabControl();
	}
	//------------------------------------------------------------------------------
	CGUIWgtTabControl::CGUIWgtTabControl( const CGUIString& rType, const CGUIString& rName, const CGUIString& rProjectName )
		:CGUIWidget(rType, rName, rProjectName)
	{
		InitTabControl();
	}
	//------------------------------------------------------------------------------
	void CGUIWgtTabControl::InitTabControl()
	{
		NewSetSizeType(eScreenValue_Percentage);
		NEWSetSize( 1.0f, 1.0f );
	}
	//------------------------------------------------------------------------------
	void    CGUIWgtTabControl::SetSelectedTab(const CGUIString &name)
	{
		for( TVecBtn::iterator itor=m_vecButtons.begin(); 
			itor!=m_vecButtons.end(); ++itor)
		{
			CGUIWgtTabButton* pBtn = *itor;
			if( pBtn->GetName() == name)
			{
				pBtn->SetCheck(true);
				pBtn->GetChild()->SetVisible( true );
			}
			else
			{
				pBtn->SetCheck(false);
				pBtn->GetChild()->SetVisible( false );
			}
		}
	}
	//------------------------------------------------------------------------------
	void    CGUIWgtTabControl::SetSelectedTab(uint32 index)
	{
		index = index % m_vecButtons.size();

		for( uint32 i=0; i<m_vecButtons.size(); ++i)
		{
			CGUIWgtTabButton* pBtn = m_vecButtons[i];
			if( i == index)
			{
				pBtn->SetCheck(true);
				pBtn->SetVisible( true );
			}
			else
			{
				pBtn->SetCheck(false);
				pBtn->SetVisible( false );
			}
		}
	}
	//------------------------------------------------------------------------------






	//------------------------------------------------------------------------------
	uint32 CGUIWgtTabControl::OnAddChild( CGUIEventRelativeChange* pEvent )
	{
		m_vecButtons.push_back((CGUIWgtTabButton*)pEvent->GetRelative());

		return CGUIWidget::OnAddChild(pEvent);
	}
	//------------------------------------------------------------------------------
	uint32 CGUIWgtTabControl::OnRemoveChild( CGUIEventRelativeChange* pEvent )
	{
		for( TVecBtn::iterator itor = m_vecButtons.begin();
			itor != m_vecButtons.end();
			++itor)
		{
			if( (*itor) == (CGUIWgtTabButton*)pEvent->GetRelative())
			{
				m_vecButtons.erase(itor);
				break;
			}
		}

		return CGUIWidget::OnRemoveChild(pEvent);
	}
	//------------------------------------------------------------------------------
}//namespace guiex

