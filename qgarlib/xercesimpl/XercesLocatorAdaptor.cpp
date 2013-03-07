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
 * @file  XercesLocatorAdaptor.cpp
 * @brief Implementation of class XercesLocatorAdaptor.
 *
 *        See file XercesLocatorAdaptor.h for the interface.
 *
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 28, 2003  15:53
 * @since  Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: XercesLocatorAdaptor.cpp,v 1.3 2004/07/01 22:19:37 masini Exp $ */


#include <qgarlib/xercesimpl/XercesLocatorAdaptor.h>

using namespace std;

namespace qgxml {


// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
XercesLocatorAdaptor::XercesLocatorAdaptor(xercesc::Locator * locator)
{
  _impl = locator;
}

// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

XercesLocatorAdaptor::~XercesLocatorAdaptor() 
{
}


// ---------------------------------------------------------------------
// A C C E S S
// ---------------------------------------------------------------------

int
XercesLocatorAdaptor::getColumnNumber() const
{
  return _impl->getColumnNumber();
}

// ---------------------------------------------------------------------

int
XercesLocatorAdaptor::getLineNumber() const
{
  return _impl->getLineNumber();
}

// ---------------------------------------------------------------------

string
XercesLocatorAdaptor::getPublicId() const
{
  return _sc.convert(_impl->getPublicId());
}

// ---------------------------------------------------------------------

string
XercesLocatorAdaptor::getSystemId() const
{
  return _sc.convert(_impl->getSystemId());
}

// ----------------------------------------------------------------------

} // namespace qgxml
