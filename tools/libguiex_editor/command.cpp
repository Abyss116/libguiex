/** 
* @file command.cpp
* @brief command
* @author ken
* @date 2007-11-30
*/

//============================================================================//
// include
//============================================================================//
#include "command.h"
#include "wxmainapp.h"
#include "wxmainframe.h"

//============================================================================//
// function
//============================================================================// 


//***********************************************
// CCommand
//*********************************************** 
//------------------------------------------------------------------------------
CCommand::CCommand()
{

}
//------------------------------------------------------------------------------
CCommand::~CCommand()
{

}
//------------------------------------------------------------------------------


//***********************************************
// CCommandWidgetBase
//*********************************************** 
//------------------------------------------------------------------------------
CCommandWidgetBase::CCommandWidgetBase( CGUIWidget* pWidget )
	:m_strWidgetName( pWidget->GetName() )
{
}
//------------------------------------------------------------------------------
CGUIWidget* CCommandWidgetBase::GetWidget()
{
	CGUIWidget* pWidget = CGUIWidgetManager::Instance()->GetWidget( m_strWidgetName, GetMainFrame()->GetCurrentSceneName() );
	GUI_ASSERT( pWidget, "CCommandWidgetBase::GetWidget: invalid pointer" );
	return pWidget;
}
//------------------------------------------------------------------------------


//***********************************************
// CCommand_SetProperty
//*********************************************** 
//------------------------------------------------------------------------------
CCommand_SetProperty::CCommand_SetProperty( CGUIWidget* pWidget, const CGUIProperty& rNewProp )
	:CCommandWidgetBase( pWidget )
{
	m_NewProp = rNewProp;
	m_OldProp.SetName( rNewProp.GetName() );
	m_OldProp.SetType( rNewProp.GetTypeAsString() );
	pWidget->GenerateProperty(m_OldProp);
}
//------------------------------------------------------------------------------
void CCommand_SetProperty::Execute()
{
	CGUIWidget * pWidget = GetWidget();
	pWidget->InsertProperty( m_NewProp );
	pWidget->ProcessProperty(m_NewProp);
	pWidget->Refresh();
}
//------------------------------------------------------------------------------
void CCommand_SetProperty::Undo()
{
	CGUIWidget * pWidget = GetWidget();
	pWidget->InsertProperty( m_OldProp );
	pWidget->ProcessProperty(m_OldProp);
	pWidget->Refresh();
}
//------------------------------------------------------------------------------



//***********************************************
// CCommand_SetPosition
//*********************************************** 
//------------------------------------------------------------------------------
CCommand_SetPosition::CCommand_SetPosition( CGUIWidget* pWidget, const CGUIVector2& rPixelOldPos,const CGUIVector2& rPixelNewPos )
	:CCommandWidgetBase( pWidget )
	,m_aPosOld(rPixelOldPos)
	,m_aPosNew(rPixelNewPos)
{
}
//------------------------------------------------------------------------------
void CCommand_SetPosition::Execute()
{
	GetWidget()->SetPixelPosition( m_aPosNew );
	GetWidget()->Refresh();
	GetMainFrame()->UpdateWidgetSizeAndPos();
}
//------------------------------------------------------------------------------
void CCommand_SetPosition::Undo()
{
	GetWidget()->SetPixelPosition( m_aPosOld );
	GetWidget()->Refresh();
	GetMainFrame()->UpdateWidgetSizeAndPos();
}
//------------------------------------------------------------------------------



//***********************************************
// CCommand_SetSize
//*********************************************** 
//------------------------------------------------------------------------------
CCommand_SetSize::CCommand_SetSize( CGUIWidget* pWidget, const CGUISize& rPixelOldSize, const CGUISize& rPixelNewSize )
	:CCommandWidgetBase( pWidget )
	,m_aSizeOld(rPixelOldSize)
	,m_aSizeNew(rPixelNewSize)
{
}
//------------------------------------------------------------------------------
void CCommand_SetSize::Execute()
{
	GetWidget()->SetPixelSize( m_aSizeNew );
	GetWidget()->Refresh();
	GetMainFrame()->UpdateWidgetSizeAndPos();
}
//------------------------------------------------------------------------------
void CCommand_SetSize::Undo()
{
	GetWidget()->SetPixelSize( m_aSizeOld );
	GetWidget()->Refresh();
	GetMainFrame()->UpdateWidgetSizeAndPos();
}
//------------------------------------------------------------------------------



//***********************************************
// CCommand_WidgetOp
//*********************************************** 
//------------------------------------------------------------------------------
CCommand_WidgetOp::CCommand_WidgetOp( CGUIWidget* pWidget )
	:CCommandWidgetBase(pWidget)
{
	SaveWidgetCache( pWidget );
}
//------------------------------------------------------------------------------
void CCommand_WidgetOp::SaveWidgetCache( CGUIWidget* pWidget )
{
	if(CGUIWidgetManager::IsInternalName( pWidget->GetName()))
	{
		//internal widget should be ignored
		return;
	}

	m_vecPropertyCaches.push_back( CWidgetPropertyCache(pWidget) );

	//process it's child
	CGUIWidget* pChild = pWidget->GetChild();
	while( pChild )
	{
		SaveWidgetCache( pChild );
		pChild = pChild->GetNextSibling();
	}
}
//------------------------------------------------------------------------------


//***********************************************
// CCommand_DeleteWidget
//*********************************************** 
//------------------------------------------------------------------------------
CCommand_DeleteWidget::CCommand_DeleteWidget( CGUIWidget* pWidget )
	:CCommand_WidgetOp(pWidget)
{
}
//------------------------------------------------------------------------------
void CCommand_DeleteWidget::Execute()
{
	CGUIWidget* pWidget = GetWidget();
	if( pWidget->IsPageRoot() )
	{
		//is page
		GSystem->GetUICanvas()->CloseUIPage(pWidget);
		CGUIWidgetManager::Instance()->DestroyWidget(pWidget);
	}
	else
	{
		if( pWidget->IsOpen() )
		{
			pWidget->Close();
		}
		CGUIWidgetManager::Instance()->DestroyWidget(pWidget);
	}

	GetMainFrame()->OnWidgetDeleted();
}
//------------------------------------------------------------------------------
void CCommand_DeleteWidget::Undo()
{
	for( std::vector<CWidgetPropertyCache>::iterator itor = m_vecPropertyCaches.begin();
		itor != m_vecPropertyCaches.end();
		++itor )
	{
		CWidgetPropertyCache& aCache = *itor;
		CGUIWidget* pWidget = aCache.GenerateWidget( );
		if( pWidget->IsPageRoot() )
		{
			CGUIWidgetManager::Instance()->AddPage( pWidget);
			GSystem->GetUICanvas()->OpenUIPage( pWidget);
		}
		else
		{
			pWidget->Open();
		}
	}

	GetMainFrame()->OnWidgetModified();
}
//------------------------------------------------------------------------------




//***********************************************
// CCommand_CreateWidget
//*********************************************** 
//------------------------------------------------------------------------------
CCommand_CreateWidget::CCommand_CreateWidget( CGUIWidget* pWidget )
	:CCommand_WidgetOp(pWidget)
{
}
//------------------------------------------------------------------------------
void CCommand_CreateWidget::Execute()
{
	for( std::vector<CWidgetPropertyCache>::iterator itor = m_vecPropertyCaches.begin();
		itor != m_vecPropertyCaches.end();
		++itor )
	{
		CWidgetPropertyCache& aCache = *itor;
		CGUIWidget* pWidget = aCache.GenerateWidget( );
		if( pWidget->IsPageRoot() )
		{
			CGUIWidgetManager::Instance()->AddPage( pWidget);
			GSystem->GetUICanvas()->OpenUIPage( pWidget);
		}
		else
		{
			pWidget->Open();
		}
	}

	GetMainFrame()->OnWidgetModified();
}
//------------------------------------------------------------------------------
void CCommand_CreateWidget::Undo()
{
	CGUIWidget* pWidget = GetWidget();
	if( pWidget->IsPageRoot() )
	{
		//is page
		GSystem->GetUICanvas()->CloseUIPage(pWidget);
		CGUIWidgetManager::Instance()->DestroyWidget(pWidget);
	}
	else
	{
		if( pWidget->IsOpen() )
		{
			pWidget->Close();
		}
		CGUIWidgetManager::Instance()->DestroyWidget(pWidget);
	}

	GetMainFrame()->OnWidgetDeleted();
}
//------------------------------------------------------------------------------



//***********************************************
// CCommand_WidgetChangeParent
//*********************************************** 
//------------------------------------------------------------------------------
CCommand_WidgetChangeParent::CCommand_WidgetChangeParent( CGUIWidget* pWidget, const CGUIString& rOldParentName, const CGUIString& rNewParentName )
	:CCommandWidgetBase(pWidget)
	,m_strOldParent( rOldParentName )
	,m_strNewParent( rNewParentName )
{
}
//------------------------------------------------------------------------------
void CCommand_WidgetChangeParent::Execute()
{
	CGUIWidget* pWidget = GetWidget();
	pWidget->SetParent( CGUIWidgetManager::Instance()->GetWidget( m_strNewParent, GetMainFrame()->GetCurrentSceneName()));
	pWidget->Refresh();

	GetMainFrame()->OnWidgetModified();
}
//------------------------------------------------------------------------------
void CCommand_WidgetChangeParent::Undo()
{
	CGUIWidget* pWidget = GetWidget();
	pWidget->SetParent( CGUIWidgetManager::Instance()->GetWidget( m_strOldParent, GetMainFrame()->GetCurrentSceneName()));
	pWidget->Refresh();

	GetMainFrame()->OnWidgetModified();
}
//------------------------------------------------------------------------------
