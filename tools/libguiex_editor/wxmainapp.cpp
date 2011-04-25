/** 
* @file mainapp.cpp
* @brief entry of the application
* @author ken
* @date 2007-09-10
*/

//============================================================================//
// include
//============================================================================// 
#include "wxmainapp.h"
#include "wxmainframe.h"
#include "propertyconfigmgr.h"
#include "editorutility.h"


//============================================================================//
// function
//============================================================================// 

//------------------------------------------------------------------------------
IMPLEMENT_APP(WxMainApp)
//------------------------------------------------------------------------------
WxMainApp::WxMainApp()
:wxApp()
,m_hSciDll(NULL)
{
}
//------------------------------------------------------------------------------
bool WxMainApp::OnInit()
{
	//get base dir
    wxString strDir;
	wxSplitPath(wxGetFullModuleName(), &strDir, NULL, NULL);
	m_strBaseDir = strDir.char_str(wxConvUTF8).data();
	m_strBaseDir += "\\";

	///////////////////////////////////////////////////////////////////////////////////////////////////
	//initialize guiex system
	try
	{
		CGUIFrameworkEditor::ms_pFramework = new CGUIFrameworkEditor( );
		CGUIFrameworkEditor::ms_pFramework->Initialize( CGUIIntSize(1024,768), "" );

		GSystem->SetDrawExtraInfo( false );
		GSystem->SetPlayingAs( false );
		GSystem->SetEditorMode( true );
	}
	catch (CGUIBaseException& rError)
	{
		wxMessageBox( Gui2wxString(rError.what()), _T("error") );

		if( CGUIFrameworkEditor::ms_pFramework )
		{
			CGUIFrameworkEditor::ms_pFramework->Release();
			delete CGUIFrameworkEditor::ms_pFramework;
			CGUIFrameworkEditor::ms_pFramework = NULL;
		}
	}

	//load scintilla dll
	m_hSciDll = LoadLibrary(_T("SciLexer.DLL"));
	if (m_hSciDll==NULL)
	{
		wxMessageBox(_T("The Scintilla DLL could not be loaded."),
			_T("Error loading Scintilla"), wxOK|wxCENTER|wxICON_ERROR,NULL);
		return false;
	}

	//load localization config file
	if( 0 != CPropertyConfigMgr::Instance()->ReadLocalizationConfig(GetBaseDir() + "../editorconfig/localization_config.xml"))
	{
		wxMessageBox(_T("failed to read config file localization_config.xml!"), _T("error"));
		return false;
	}

	//load config file
	if( 0 != CPropertyConfigMgr::Instance()->ReadPropertyConfig(GetBaseDir() + "../editorconfig/libguiex_editor_config.xml"))
	{
		wxMessageBox(_T("failed to read property config filelibguiex_editor_config.xml!"), _T("error"));
		return false;
	}

	//load box2d config file
	if( 0 != CPropertyConfigMgr::Instance()->ReadPropertyConfig(GetBaseDir() + "../editorconfig/libguiex_editor_config_box2d.xml"))
	{
		wxMessageBox(_T("failed to read property config file <libguiex_editor_config_box2d.xml>!"), _T("error"));
		return false;
	}

	//load game config file
	if( 0 != CPropertyConfigMgr::Instance()->ReadPropertyConfig(GetBaseDir() + "../editorconfig/libguiex_editor_config_game.xml"))
	{
		wxMessageBox(_T("failed to read property config file <libguiex_editor_config_game.xml>!"), _T("error"));
		return false;
	}

	//check default property
	if( false == CheckProperty() )
	{
		wxMessageBox(_T("check default property!"), _T("error"));
		return false;
	}

	//create frame
	wxFrame* frame = new WxMainFrame(NULL,
		wxID_ANY,
		wxT("liguiex editor"),
		wxDefaultPosition,
		wxSize(1024, 768));
	SetTopWindow(frame);
	frame->Show();

	wxToolTip::Enable(true);
	wxToolTip::SetDelay(1000);

	return true;
}
//------------------------------------------------------------------------------
int WxMainApp::OnExit()
{
	//free scintilla
	if (m_hSciDll != NULL)
	{
		FreeLibrary(m_hSciDll);
		m_hSciDll = NULL;
	}

	//release libguiex system
	if( CGUIFrameworkEditor::ms_pFramework )
	{
		CGUIFrameworkEditor::ms_pFramework->Release();
		delete CGUIFrameworkEditor::ms_pFramework;
		CGUIFrameworkEditor::ms_pFramework = NULL;
	}

	return wxApp::OnExit();
}
//------------------------------------------------------------------------------
const std::string& WxMainApp::GetBaseDir( ) const 
{
	return m_strBaseDir;
}
//------------------------------------------------------------------------------
bool WxMainApp::CheckProperty() const
{
	const CPropertyConfigMgr::TSetType& rTypes = CPropertyConfigMgr::Instance()->GetWidgetTypes( );
	for( CPropertyConfigMgr::TSetType::const_iterator itor = rTypes.begin();
		itor != rTypes.end();
		++itor )
	{
		const std::string& rWidgetType = *itor;
		guiex::CGUIWidget* pWidget = guiex::CGUIWidgetManager::Instance()->CreateWidget( rWidgetType,"__template4check__", "" );
		const CGUIProperty& rDefaultProperty = CPropertyConfigMgr::Instance()->GetPropertySet( rWidgetType );
		
		for( uint32 i=0; i<rDefaultProperty.GetPropertyNum(); ++i )
		{
			const guiex::CGUIProperty* pDefaultProperty = rDefaultProperty.GetProperty(i);
			if( CPropertyData::GetPropertyData(*pDefaultProperty)->IsAlternaitiveSave() == false )
			{
				continue;
			}

			guiex::CGUIProperty aWidgetProperty;
			aWidgetProperty.SetName( pDefaultProperty->GetName() );
			aWidgetProperty.SetType( pDefaultProperty->GetTypeAsString() );
			if( 0 != pWidget->GenerateProperty( aWidgetProperty ))
			{
				wxString strError = wxString::Format( 
					_T("failed to create property <%s:%s> in widget <%s>!"), 
					Gui2wxString(aWidgetProperty.GetName()).c_str(),
					Gui2wxString(aWidgetProperty.GetTypeAsString()).c_str(),
					Gui2wxString(pWidget->GetType()).c_str()
					);
				wxMessageBox(strError, _T("error"));
				return false;
			}

			if( aWidgetProperty != *pDefaultProperty )
			{
				wxString strError = wxString::Format( 
					_T("failed to check property <%s:%s> in widget <%s>!"), 
					Gui2wxString(aWidgetProperty.GetName()).c_str(),
					Gui2wxString(aWidgetProperty.GetTypeAsString()).c_str(),
					Gui2wxString(pWidget->GetType()).c_str()
					);
				wxMessageBox(strError, _T("error"));
				return false;
			}
		}

		guiex::CGUIWidgetManager::Instance()->DestroyWidget( pWidget );
	}
	return true;
}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
WxMainFrame* GetMainFrame()
{
	return (WxMainFrame*)wxGetApp().GetTopWindow();
}
//------------------------------------------------------------------------------
