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


/**
 * @file  XercesQgarErrorHandlerAdaptor.cpp
 * @brief Implementation of class XercesQgarErrorHandlerAdaptor.
 *
 *        See file XercesQgarErrorHandlerAdaptor.h for the interface.
 *
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 31, 2003  15:42
 * @since  Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: XercesQgarErrorHandlerAdaptor.cpp,v 1.3 2004/07/01 22:19:37 masini Exp $ */


#include <qgarlib/xercesimpl/XercesQgarErrorHandlerAdaptor.h>

// QGAR
#include <qgarlib/sax/ErrorHandler.h>
#include <qgarlib/sax/SAXParseException.h>
#include <qgarlib/sax/SAXException.h>

// XERCES
#include <xercesc/sax/SAXException.hpp>
#include <xercesc/sax/SAXParseException.hpp>


namespace qgxml
{


// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

XercesQgarErrorHandlerAdaptor::XercesQgarErrorHandlerAdaptor(
						qgxml::ErrorHandler* h
						)
{
  _impl = h;
}


// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

XercesQgarErrorHandlerAdaptor::~XercesQgarErrorHandlerAdaptor()
{ /* NOP */ }



// ---------------------------------------------------------------------
// O T H E R
// ----------------------------------------------------------------------

void
XercesQgarErrorHandlerAdaptor::warning(const xercesc::SAXParseException& e)
{
  try {
    _impl->warning(qgxml::SAXParseException(_sc(e.getMessage()),
					    _sc(e.getPublicId()),
					    _sc(e.getSystemId()),
					    e.getLineNumber(),
					    e.getColumnNumber()
					    ));
  }
  catch(qgxml::SAXException& se) {
    
    throw xercesc::SAXException(se.getMessage());
  }
}

// ----------------------------------------------------------------------

void
XercesQgarErrorHandlerAdaptor::error(const xercesc::SAXParseException& e)
{
  try {
    _impl->error(qgxml::SAXParseException(_sc(e.getMessage()),
					  _sc(e.getPublicId()),
					  _sc(e.getSystemId()),
					  e.getLineNumber(),
					  e.getColumnNumber()
					  ));
  }
  catch(qgxml::SAXException& se) {
    
    throw xercesc::SAXException(se.getMessage());
  }
}
  
// ----------------------------------------------------------------------

void
XercesQgarErrorHandlerAdaptor::fatalError(const xercesc::SAXParseException& e)
{
  try {
    _impl->fatalError(qgxml::SAXParseException(_sc(e.getMessage()),
					       _sc(e.getPublicId()),
					       _sc(e.getSystemId()),
					       e.getLineNumber(),
					       e.getColumnNumber()
					       ));
  }
  catch(qgxml::SAXException& se) {
    
    throw xercesc::SAXException(se.getMessage());
  }
}

// ----------------------------------------------------------------------
  
void
XercesQgarErrorHandlerAdaptor::resetErrors()
{ /* NOP */ }

// ----------------------------------------------------------------------

} // namespace qgxml
