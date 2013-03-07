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
 * @file  XercesQgarEntityResolverAdaptor.cpp
 * @brief Implementation of class XercesQgarEntityResolverAdaptor.
 *
 *        See file XercesQgarEntityResolverAdaptor.h for the interface.
 *
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 31, 2003  15:05
 * @since  Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: XercesQgarEntityResolverAdaptor.cpp,v 1.3 2004/07/01 22:19:37 masini Exp $ */


#include <qgarlib/xercesimpl/XercesQgarEntityResolverAdaptor.h>

// QGAR
#include <qgarlib/sax/EntityResolver.h>
#include <qgarlib/sax/InputSource.h>
#include <qgarlib/sax/SAXException.h>
#include <qgarlib/xercesimpl/XercesQgarInputSourceAdaptor.h>

// XERCES
#include <xercesc/sax/InputSource.hpp>
#include <xercesc/sax/SAXException.hpp>

namespace qgxml {


// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

XercesQgarEntityResolverAdaptor::XercesQgarEntityResolverAdaptor(
					      qgxml::EntityResolver * e
					      )
{
  _impl = e;
}


// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

XercesQgarEntityResolverAdaptor::~XercesQgarEntityResolverAdaptor()
{ /* NOP */ }

// ---------------------------------------------------------------------
// O T H E R
// ---------------------------------------------------------------------

xercesc::InputSource * 
XercesQgarEntityResolverAdaptor::resolveEntity(const XMLCh * const publicId, 
					       const XMLCh *const systemId)
{
  xercesc::InputSource * retval = 0;

  try {
    
    InputSource * is = _impl->resolveEntity(_sc(publicId),
					    _sc(systemId));

    retval = new XercesQgarInputSourceAdaptor(is);
    
  }
  catch(qgxml::SAXException se) {
    
    throw xercesc::SAXException(se.getMessage());
  } 

  return retval;
}

// ----------------------------------------------------------------------

} // namespace qgxml
