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
 |   LORIA - �quipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-l�s-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/


/**
 * @file  XercesQgarDTDHandlerAdaptor.cpp
 * @brief Implementation of class XercesQgarDTDHandlerAdaptor.
 *
 *        See file XercesQgarDTDHandlerAdaptor.h for the interface.
 *
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 31, 2003  14:05
 * @since  Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: XercesQgarDTDHandlerAdaptor.cpp,v 1.3 2004/07/01 22:19:37 masini Exp $ */


#include <qgarlib/xercesimpl/XercesQgarDTDHandlerAdaptor.h>

// QGAR
#include <qgarlib/sax/DTDHandler.h>
#include <qgarlib/sax/SAXException.h>

// XERCES
#include <xercesc/sax/SAXException.hpp>

namespace qgxml {


// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

XercesQgarDTDHandlerAdaptor::XercesQgarDTDHandlerAdaptor(qgxml::DTDHandler * handler)
{
  _impl = handler;
}



// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

XercesQgarDTDHandlerAdaptor::~XercesQgarDTDHandlerAdaptor()
{ /* NOP */ }


  
// ---------------------------------------------------------------------
// O T H E R
// ---------------------------------------------------------------------

void
XercesQgarDTDHandlerAdaptor::notationDecl(const XMLCh * const name,
					  const XMLCh * const publicId, 
					  const XMLCh * const systemId)
{
  try {
    _impl->notationDecl(_sc(name), _sc(publicId), _sc(systemId));
  }
  catch (qgxml::SAXException& se) {
    
    throw xercesc::SAXException(se.getMessage());
  }
}

// ---------------------------------------------------------------------

void
XercesQgarDTDHandlerAdaptor::unparsedEntityDecl(const XMLCh * const name, 
						const XMLCh * const publicId,
						const XMLCh * const systemId,
						const XMLCh * const notationName)
{
  try {
    _impl->unparsedEntityDecl(_sc(name), 
			      _sc(publicId),
			      _sc(systemId),
			      _sc(notationName));
  }
  catch (qgxml::SAXException& se) {
    
    throw xercesc::SAXException(se.getMessage());
  }
}

// ---------------------------------------------------------------------

void 
XercesQgarDTDHandlerAdaptor::resetDocType()
{ /* NOP */ }


// ----------------------------------------------------------------------

} // namespace qgxml
