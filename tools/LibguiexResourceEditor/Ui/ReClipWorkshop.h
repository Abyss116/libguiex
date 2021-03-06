// -----------------------------------------------------------------------------
// Author: GameCrashDebug.
// Date: 20110115.
// -----------------------------------------------------------------------------
#ifndef _RE_EDITOR_CLIPWORKSHOP
#define _RE_EDITOR_CLIPWORKSHOP
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#include "Core\ReTypes.h"
#include "Core\ReModelBase.h"
#include "Core\ReDragInfo.h"
#include "Core\ReZoomInfo.h"
#include "Core\ReItemGroup.h"
#include "Core\ReWidgetSelection.h"
#include "UI\ReClipWidget.h"
#include "Ui\ReBaseWidget.h"
#include <QWidget>


class QMenu;
class QAction;
class QTabWidget;


namespace RE
{


class ReClipModel;
class ReClipCell;


class ReClipWorkshop : public ReBaseWidget< QWidget >
{
	Q_OBJECT
	typedef ReBaseWidget< QWidget >			TSuper;

	// -------------------------------------------------------------------------
	// General.
	// -------------------------------------------------------------------------
public:
	ReClipWorkshop( ReClipModel* _model, QWidget* _parent = NULL );

	// -------------------------------------------------------------------------
	// Override QWidget.
	// -------------------------------------------------------------------------
public:
	virtual void		paintEvent( QPaintEvent* _event );
	virtual void		resizeEvent( QResizeEvent* _event );

	// -------------------------------------------------------------------------
	// Slots.
	// -------------------------------------------------------------------------
public slots:
	void				OnContextMenu( const QPoint& _point );
	void				OnLoadImage();
	void				OnImport();
	void				OnSave();
	void				OnSaveAs();

	// -------------------------------------------------------------------------
	// Utilities.
	// -------------------------------------------------------------------------
protected:
	void				InitMenus();
	void				Reset();
	ePromptResult		CheckAndPromptToSave();

	// -------------------------------------------------------------------------
	// Variables.
	// -------------------------------------------------------------------------
protected:
	typedef ReItemGroup< ReClipCell* >		TCellList;
	typedef TCellList::TItemListItor		TCellListItor;
	typedef TCellList::TItemListCItor		TCellListCItor;

	ReClipModel*		m_clipModel;
	TCellList			m_cellList;
	ReDragInfo			m_dragInfo;

	QTabWidget*			m_tab;
	QString				m_filePath;

	QMenu*				m_editMenu;
	QAction*			m_loadImageAction;
	QAction*			m_importAction;
	QAction*			m_saveAction;
	QAction*			m_saveAsAction;
};


}
#endif	// _RE_EDITOR_CLIPWORKSHOP
