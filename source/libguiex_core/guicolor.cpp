/** 
* @file guicolor.cpp
* @brief implement of class CGUIColor.
* @author ken
* @date 2006-03-23
*/


//============================================================================//
// include
//============================================================================// 
#include <libguiex_core/guicolor.h>
#include <algorithm>



//============================================================================//
// define
//============================================================================// 


//============================================================================//
// function
//============================================================================// 
namespace guiex
{
	//------------------------------------------------------------------------------
	CGUIColor::CGUIColor()
		:m_nARGB(0xFF000000)
	{
	}
	//------------------------------------------------------------------------------ 
	CGUIColor::CGUIColor(const CGUIColor &rColor)
	{
		SetColor(rColor);
	}
	//------------------------------------------------------------------------------ 
	CGUIColor::CGUIColor(GUIARGB argb)
	{
		SetARGB(argb);
	}
	//------------------------------------------------------------------------------ 
	CGUIColor::CGUIColor(real fRed, real fGreen, real fBlue, real fAlpha /*=1.0f*/ )
	{
		SetColor(fRed, fGreen, fBlue, fAlpha);
	}
	//------------------------------------------------------------------------------ 
	GUIRGBA CGUIColor::ARGB2RGBA( GUIARGB aColorARGB )
	{
		return ((aColorARGB<<8) + ((aColorARGB>>24)&0xFF));
	}
	//------------------------------------------------------------------------------ 

}//namespace guiex

