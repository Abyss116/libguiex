// -----------------------------------------------------------------------------
// Author: GameCrashDebug.
// Date: 20101127.
// -----------------------------------------------------------------------------
#ifndef _RE_TRACK_FRAME_WIDGET_H_
#define _RE_TRACK_FRAME_WIDGET_H_


#include <QLabel>
#include "Ui\ReBaseWidget.h"


namespace RE
{


class ReTrackFrameWidget : public ReBaseWidget< QLabel >
{
	Q_OBJECT
	typedef ReBaseWidget< QLabel >	TSuper;

	// ----------------------------------------------------------------------------
	// General.
	// ----------------------------------------------------------------------------
public:
	ReTrackFrameWidget( QWidget* _parent = NULL );

	// ----------------------------------------------------------------------------
	// Override QWidget.
	// ----------------------------------------------------------------------------
protected:
	virtual void			paintEvent( QPaintEvent* _event );

	// ----------------------------------------------------------------------------
	// Slots.
	// ----------------------------------------------------------------------------

	// ----------------------------------------------------------------------------
	// Utilities.
	// ----------------------------------------------------------------------------

	// ----------------------------------------------------------------------------
	// Variables.
	// ----------------------------------------------------------------------------
};


}
#endif	// _RE_TRACK_FRAME_WIDGET_H_
