/*---------------------------------------------------------------------*
 | Library QgarLib, graphics analysis and recognition                  |
 | Copyright (C) 2003  Qgar Project, LORIA                             |
 |                                                                     |
 | This library is free software; you can redistribute it and/or       |
 | modify it under the terms of the GNU Lesser General Public          |
 | License version 2.1, as published by the Free Software Foundation.  |
 |                                                                     |
 | This library is distributed in the hope that it will be useful,     |
 | but WITHOUT ANY WARRANTY; without even the implied warranty of      |
 | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                |
 | See the GNU Lesser General Public License for more details.         |
 |                                                                     |
 | The GNU Lesser General Public License is included in the file       |
 | LICENSE.LGPL, in the root directory of the Qgar packaging. See      |
 | http://www.gnu.org/licenses/lgpl.html for the terms of the license. |
 | To receive a paper copy, write to the Free Software Foundation,     |
 | Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.       |
 |                                                                     |
 | Contact Project Qgar for any information:                           |
 |   LORIA - équipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-lès-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/


#ifndef __XERCESQGARERRORHANDLERADAPTOR_H_INCLUDED__
#define __XERCESQGARERRORHANDLERADAPTOR_H_INCLUDED__


/**
 * @file     XercesQgarErrorHandlerAdaptor.h
 * @brief    Header file of class XercesQgarErrorHandlerAdaptor
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 31, 2003  15:42
 * @since    Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: XercesQgarErrorHandlerAdaptor.h,v 1.2 2004/06/21 15:50:53 rendek Exp $ */


// QGAR
#include <qgarlib/xercesimpl/XercesStringConverter.h>


// XERCES
#include <xercesc/sax/ErrorHandler.hpp>
class xercesc::SAXParseException;


namespace qgxml {

class ErrorHandler;

/**
 * @class XercesQgarErrorHandlerAdaptor XercesQgarErrorHandlerAdaptor.h
 * @brief <BRIEF DESCRIPTION ENDING BY A BLANK LINE>
 * 
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 31, 2003  15:42
 * @since  Qgar 2.1
 */
class XercesQgarErrorHandlerAdaptor : public xercesc::ErrorHandler {

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:


/** @name Constructors */
//        ============
//@{
/**
 * @brief Default constructor
 */
  XercesQgarErrorHandlerAdaptor(qgxml::ErrorHandler * handler);

//@}


/** @name Destructor */
//        ==========
//@{
/**
 * @brief Destructor
 */
  virtual ~XercesQgarErrorHandlerAdaptor();
//@}


  virtual void warning(const xercesc::SAXParseException & exception);
  
  virtual void error(const xercesc::SAXParseException & exception);
  
  virtual void fatalError(const xercesc::SAXParseException & exception);
  
  virtual void resetErrors();


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  qgxml::ErrorHandler * _impl;

  XercesStringConverter _sc;

// -------------------------------------------------------------------

}; // class XercesQgarErrorHandlerAdaptor

} // namespace qgxml


#endif /* __XERCESQGARERRORHANDLERADAPTOR_H_INCLUDED__ */
