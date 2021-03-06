// -----------------------------------------------------------------------------
// Author: GameCrashDebug.
// Date: 20101109.
// -----------------------------------------------------------------------------
#ifndef _RE_BASE_WIDGET_H_
#define _RE_BASE_WIDGET_H_

#include <QWidget>
#include "Ui\ReWidgetInterface.h"
#include "Core\ReDragInfo.h"


class QMenu;


namespace RE
{


template< class T >
class ReBaseWidget : public T, public ReWidgetInterface
{
//	Q_OBJECT
//	typedef T	TSuper;

	// -----------------------------------------------------
	// General
	// -----------------------------------------------------
public:
	ReBaseWidget( QWidget* _parent = NULL );

	ReDragInfo&			GetDragInfoRef()					{ return m_dragInfo; }
	const ReDragInfo&	GetDragInfo() const					{ return m_dragInfo; }
	ReDragInfo::eResize	CalcResizeType( const QPoint& _point ) const;

	int					GetLeftPadding() const				{ return m_leftPadding; }
	int&				GetLeftPaddingRef()					{ return m_leftPadding; }
	int					GetTopPadding() const				{ return m_topPadding; }
	int&				GetTopPaddingRef()					{ return m_topPadding; }
	int					GetRightPadding() const				{ return m_rightPadding; }
	int&				GetRightPaddingRef()				{ return m_rightPadding; }
	int					GetBottomPadding() const			{ return m_bottomPadding; }
	int&				GetBottomPaddingRef()				{ return m_bottomPadding; }
	int					GetHorizontalGap() const			{ return m_horizontalGap; }
	int&				GetHorizontalGapRef()				{ return m_horizontalGap; }
	int					GetVerticalGap() const				{ return m_verticalGap; }
	int&				GetVerticalGapRef() 				{ return m_verticalGap; }

protected:
	ReDragInfo			m_dragInfo;
	int					m_leftPadding;
	int					m_topPadding;
	int					m_rightPadding;
	int					m_bottomPadding;
	int					m_horizontalGap;
	int					m_verticalGap;
};


template< class T >
ReBaseWidget< T >::ReBaseWidget( QWidget* _parent /* = NULL */ )
: T( _parent )
, m_leftPadding( 0 )
, m_topPadding( 0 )
, m_rightPadding( 0 )
, m_bottomPadding( 0 )
, m_horizontalGap( 0 )
, m_verticalGap( 0 )
{
}


template< class T >
ReDragInfo::eResize ReBaseWidget< T >::CalcResizeType( const QPoint& _point ) const
{
	ReDragInfo::eResize result = ReDragInfo::EResize_None;	
	QPoint localPos = _point;
	const int padding = 3;
	const int width = T::width();
	const int height = T::height();

	bool isLeft = ( localPos.x() >= 0 ) && ( localPos.x() < padding );
	bool isRight = ( width > localPos.x() ) && ( ( width - localPos.x() ) <= padding );
	bool isTop = ( localPos.y() >= 0 ) && ( localPos.y() < padding );
	bool isBottom = ( height > localPos.y() ) && ( ( height - localPos.y() ) <= padding );
	bool isV = ( localPos.y() >= 0 && localPos.y() < height );
	bool isH = ( localPos.x() >= 0 && localPos.x() < width );

	if( isLeft && isTop )
	{
		result = ReDragInfo::EResize_LeftTop;
	}
	else if( isLeft && isBottom )
	{
		result = ReDragInfo::EResize_LeftBottom;
	}
	else if( isRight && isTop )
	{
		result = ReDragInfo::EResize_RightTop;
	}
	else if( isRight && isBottom )
	{
		result = ReDragInfo::EResize_RightBottom;
	}
	else
	{
		if( isH )
		{
			if( isLeft )
				result = ReDragInfo::EResize_Left;
			else if( isRight )
				result = ReDragInfo::EResize_Right;
		}

		if( isV )
		{
			if( isTop )
				result = ReDragInfo::EResize_Top;
			else if( isBottom )
				result = ReDragInfo::EResize_Bottom;
		}
	}

	return result;
}


}		// namespace RE
#endif	// _RE_BASE_WIDGET_H_
