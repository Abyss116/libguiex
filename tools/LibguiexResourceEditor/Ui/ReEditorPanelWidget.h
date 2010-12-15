// -----------------------------------------------------------------------------
// Author: GameCrashDebug.
// Date: 20101109.
// -----------------------------------------------------------------------------
#ifndef _RE_CONTROL_PANEL_WIDGET_
#define _RE_CONTROL_PANEL_WIDGET_


#include <QWidget>
#include "UI\ReBaseWidget.h"


class QPushButton;
class QLabel;
class QImage;
class QStackedWidget;


namespace RE
{


class ReImagePanel;
class ReSettingsWidget;
class ReClipPanelWidget;
class ReClipModel;
class ReAnimPanelWidget;
class ReAnimModel;


class ReEditorPanelWidget : public ReBaseWidget< QWidget >
{
	Q_OBJECT

	typedef ReBaseWidget< QWidget >	TSuper;

	// -----------------------------------------------------
	// General
	// -----------------------------------------------------
public:
	class ReParam
	{
	public:
		ReClipModel*	m_clipModel;
		ReAnimModel*	m_animModel;
	};

	ReEditorPanelWidget( const ReParam& _param, QWidget* _parent = NULL );
	~ReEditorPanelWidget();

	// -----------------------------------------------------
	// -----------------------------------------------------
public:
	enum ePanel
	{
		EPanel_ClipPanel,
		EPanel_AnimPanel,
		EPanel_ImagePanel,		
		EPanel_Settings,
		EPanel_Count
	};

public:
	void				Tick( qreal _delta );
	void				SwitchPanel( ePanel _panel );

public slots:
	void				OnToggleSetting();
	void				OnSettingsChanged();

	// -----------------------------------------------------
	// Override
	// -----------------------------------------------------
protected:
	void				paintEvent( QPaintEvent* _event );

	// -----------------------------------------------------
	// Utility
	// -----------------------------------------------------
protected:
	void				RefreshItemList();
	void				RefreshImages();

	// -----------------------------------------------------
	// Variable
	// -----------------------------------------------------
protected:
	QPushButton*		m_settingBtn;
	ReImagePanel*		m_imagePanelWidget;
	ReSettingsWidget*	m_settingsWidget;
	ReClipPanelWidget*	m_clipPanelWidget;
	ReAnimPanelWidget*	m_animPanelWidget;
	QStackedWidget*		m_stack;

	ePanel				m_lastPanel;
};


}		// namespace RE
#endif	// _RE_CONTROL_PANEL_WIDGET_