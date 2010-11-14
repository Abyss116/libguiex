/** 
* @file guias.cpp
* @brief widget action sequence
* @author ken
* @date 2007-11-21
*/

//============================================================================//
// include
//============================================================================// 
#include <libguiex_core/guias.h>
#include <libguiex_core/guiwidget.h>
#include <libguiex_core/guiwidgetsystem.h>
#include <libguiex_core/guimath.h>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------ 


//============================================================================//
// function
//============================================================================// 

namespace guiex
{
	int32 GUIRegisterAllAs()
	{
		if( 0 != GUI_AS_REGISTER(CGUIAsAlpha)) {return -1;}
		if( 0 != GUI_AS_REGISTER(CGUIAsScale)) {return -1;}
		if( 0 != GUI_AS_REGISTER(CGUIAsPosition)) {return -1;}
		if( 0 != GUI_AS_REGISTER(CGUIAsRotation)) {return -1;}

		return 0;
	} 
 

	//*****************************************************************************
	//	CGUIAs
	//*****************************************************************************

	//------------------------------------------------------------------------------
	CGUIAs::CGUIAs(const char* pAsName)
		:m_pReceiver(NULL)
		,m_bRetired(false)
		,m_fTotalTime(0.1f)
		,m_fElapsedTime(0.0f)
		,m_strAsName(pAsName)
		,m_pAsGenerator(NULL)
		,m_bLooping(false)
	{
	}
	//------------------------------------------------------------------------------
	CGUIAs::~CGUIAs()
	{
		for(TListSuccessor::iterator itor = m_listSuccessor.begin();
			itor != m_listSuccessor.end();
			++itor)
		{
			CGUIAsFactory::Instance()->DestroyAs(*itor);
		}
		m_listSuccessor.clear();
	}
	//------------------------------------------------------------------------------
	const CGUIString& CGUIAs::GetAsName() const
	{
		return m_strAsName;
	}
	//------------------------------------------------------------------------------
	void CGUIAs::Retire( bool bRetired )
	{
		m_bRetired = bRetired;
	}
	//------------------------------------------------------------------------------
	bool CGUIAs::IsRetired()
	{
		return m_bRetired;
	}
	//------------------------------------------------------------------------------
	void CGUIAs::SetLooping( bool bLooping )
	{
		m_bLooping = bLooping;
	}
	//------------------------------------------------------------------------------
	bool CGUIAs::IsLooping()
	{
		return m_bLooping;
	}
	//------------------------------------------------------------------------------
	void CGUIAs::SetReceiver(CGUIWidget* pReceiver)
	{
		m_pReceiver = pReceiver;
	}
	//------------------------------------------------------------------------------
	CGUIWidget*	CGUIAs::GetReceiver()
	{
		return m_pReceiver;
	}
	//------------------------------------------------------------------------------
	void CGUIAs::SetTotalTime(real fTotalTime)
	{
		if( fTotalTime <= 0.0f )
		{
			fTotalTime = 0.1f;
		}
		m_fTotalTime = fTotalTime;
	}
	//------------------------------------------------------------------------------
	real CGUIAs::GetTotalTime( ) const
	{
		return m_fTotalTime;
	}
	//------------------------------------------------------------------------------
	void CGUIAs::Update( real fDeltaTime )
	{
		m_fElapsedTime += fDeltaTime;
		if( m_fElapsedTime >= m_fTotalTime )
		{
			if( IsLooping() )
			{
				m_fElapsedTime = m_fElapsedTime - m_fTotalTime;
			}
			else
			{
				m_fElapsedTime = m_fTotalTime;
				Retire( true );
			}
		}
	}
	//------------------------------------------------------------------------------
	void CGUIAs::PushSuccessor( CGUIAs* pAs)
	{
		GUI_ASSERT(pAs, "wrong parameter");
		m_listSuccessor.push_back(pAs);
	}
	//------------------------------------------------------------------------------
	CGUIAs* CGUIAs::PopSuccessor()
	{
		if( m_listSuccessor.empty())
		{
			return NULL;
		}
		else
		{
			CGUIAs* pAs = m_listSuccessor.front();
			m_listSuccessor.pop_front();
			return pAs;
		}
	}
	//------------------------------------------------------------------------------
	void CGUIAs::SetGenerator( const CGUIAsGenerator* pGenerator)
	{
		m_pAsGenerator = pGenerator;
	}
	//------------------------------------------------------------------------------
	const CGUIAsGenerator* CGUIAs::GetGenerator() const
	{
		return m_pAsGenerator;
	}
	//------------------------------------------------------------------------------




	//*****************************************************************************
	//	CGUIAsAlpha
	//*****************************************************************************
	//------------------------------------------------------------------------------
	GUI_AS_GENERATOR_IMPLEMENT( CGUIAsAlpha );
	
	
	//------------------------------------------------------------------------------
	CGUIAsAlpha::CGUIAsAlpha( )
		:CGUIAsLinearBase<real>("CGUIAsAlpha" )
	{
	}
	//------------------------------------------------------------------------------
	void CGUIAsAlpha::Update( real fDeltaTime )
	{
		CGUIAsLinearBase<real>::Update( fDeltaTime );
		GUI_ASSERT( GetReceiver(), "no receiver");
		GetReceiver()->SetAlpha(GetCurrentValue());
	}
	//------------------------------------------------------------------------------



	//*****************************************************************************
	//	CGUIAsRotation
	//*****************************************************************************
	//------------------------------------------------------------------------------
	GUI_AS_GENERATOR_IMPLEMENT( CGUIAsRotation );
	//------------------------------------------------------------------------------
	CGUIAsRotation::CGUIAsRotation()
		:CGUIAsLinearBase<CGUIVector3>("CGUIAsRotation")
	{
	}
	//------------------------------------------------------------------------------
	void CGUIAsRotation::Update( real fDeltaTime )
	{
		CGUIAsLinearBase<CGUIVector3>::Update( fDeltaTime );
		GUI_ASSERT( GetReceiver(), "no receiver");
		GetReceiver()->SetRotation(GetCurrentValue());
	}
	//------------------------------------------------------------------------------


	//*****************************************************************************
	//	CGUIAsScale
	//*****************************************************************************
	//------------------------------------------------------------------------------
	GUI_AS_GENERATOR_IMPLEMENT( CGUIAsScale );
	//------------------------------------------------------------------------------
	CGUIAsScale::CGUIAsScale()
		:CGUIAsLinearBase<CGUISize>("CGUIAsScale")
	{
	}
	//------------------------------------------------------------------------------
	void CGUIAsScale::Update( real fDeltaTime )
	{
		CGUIAsLinearBase<CGUISize>::Update( fDeltaTime );
		GUI_ASSERT( GetReceiver(), "no receiver");
		GetReceiver()->SetScale(GetCurrentValue());
	}
	//------------------------------------------------------------------------------

	//*****************************************************************************
	//	CGUIAsPosition
	//*****************************************************************************
	//------------------------------------------------------------------------------
	GUI_AS_GENERATOR_IMPLEMENT( CGUIAsPosition );
	//------------------------------------------------------------------------------
	CGUIAsPosition::CGUIAsPosition()
		:CGUIAsLinearBase<CGUIVector2>("CGUIAsPosition")
	{
	}
	//------------------------------------------------------------------------------
	void CGUIAsPosition::Update( real fDeltaTime )
	{
		CGUIAsLinearBase<CGUIVector2>::Update( fDeltaTime );
		GUI_ASSERT( GetReceiver(), "no receiver");
		GetReceiver()->SetPixelPosition(GetCurrentValue());
	}
	//------------------------------------------------------------------------------
}//namespace guiex


