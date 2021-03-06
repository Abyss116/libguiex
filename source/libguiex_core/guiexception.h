/** 
 * @file guiexception.h
 * @brief exception used in this system
 * @author ken
 * @date 2006-05-26
 */

#ifndef __GUI_EXCEPTION_H_20060526__
#define __GUI_EXCEPTION_H_20060526__

//============================================================================//
// include
//============================================================================// 
#include "guibase.h"
#include "guistring.h"
#include <exception>

//============================================================================//
// declare
//============================================================================// 
namespace guiex
{	
#define GUI_THROW(X) ::guiex::CGUIException::ThrowException(__FILE__, __LINE__,(X))
#define GUI_SCRIPT_THROW(X) ::guiex::CGUIException_Script::ThrowException(__FILE__, __LINE__,(X))
}

//============================================================================//
// class
//============================================================================// 
namespace guiex
{	
	/**
	 * @class CGUIBaseException
	 * @brief base class of exception, used for guiex system..
	 */
	class GUIEXPORT CGUIBaseException : public std::exception
	{
	public:
		CGUIBaseException() throw() {}
		CGUIBaseException( const char* szError ) throw();
		~CGUIBaseException() throw(){};
		virtual const char *what( ) const throw();
		
	protected:
		CGUIString	m_strError;
	};
	
	/**
	 * @class CGUIException
	 * @brief common exception, used for guiex system..
	 */
	class GUIEXPORT CGUIException : public CGUIBaseException
	{
	public:
		CGUIException( const char *format, ... ) throw();
		static void ThrowException( const char *filename, uint32 line,const char *szError );
	};
	
	/**
	 * @class CGUIException_Script
	 * @brief exception caused by parse script
	 */
	class GUIEXPORT CGUIException_Script : public CGUIBaseException
	{
	public:
		CGUIException_Script( const char *format, ... ) throw();
		static void ThrowException(const char *filename, uint32 line,const char *szError );
	};
}//namespace guiex

//============================================================================//
// function
//============================================================================// 
namespace guiex
{	
	/**
	* @brief throw a exception
	*/
	GUIEXPORT void ThrowException(const char* szError);

}//namespace guiex

#endif //__GUI_EXCEPTION_H_20060526__

