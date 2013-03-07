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
 * @file  QtAttributesAdaptor.cpp
 * @brief Implementation of class QtAttributesAdaptor
 *
 *        See file QtAttributesAdaptor.h for the interface.
 *
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 11, 2003  09:52
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QtAttributesAdaptor.cpp,v 1.3 2004/06/21 16:03:37 rendek Exp $ */


#include <qgarlib/qtimpl/QtAttributesAdaptor.h>


using namespace std;

namespace qgxml {


// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
DLL_EXPORT QtAttributesAdaptor::QtAttributesAdaptor(QXmlAttributes * attributes)
{
  _impl = attributes;
}



// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

DLL_EXPORT QtAttributesAdaptor::~QtAttributesAdaptor()
{ /* EMPTY */ }



// ---------------------------------------------------------------------
// A C C E S S
// ---------------------------------------------------------------------

DLL_EXPORT int
QtAttributesAdaptor::getIndex(const string& qName) const
{
  return _impl->index( _sc.convert(qName) );
}

// ----------------------------------------------------------------------

DLL_EXPORT int 
QtAttributesAdaptor::getIndex(const string& uri, 
			      const string& localName) const
{
  return _impl->index( _sc.convert(uri), _sc.convert(localName) );
}

// ----------------------------------------------------------------------

DLL_EXPORT int
QtAttributesAdaptor::getLength() const
{
  return _impl->length();
}
  
// ----------------------------------------------------------------------

DLL_EXPORT string
QtAttributesAdaptor::getLocalName(int index) const
{
  return _sc.convert(_impl->localName(index));
}
 
// ----------------------------------------------------------------------

DLL_EXPORT string
QtAttributesAdaptor::getQName(int index) const
{
  return _sc.convert(_impl->qName(index));
}
  
// ----------------------------------------------------------------------

DLL_EXPORT string
QtAttributesAdaptor::getType(int index) const
{
  return _sc.convert(_impl->type(index));
}
  
// ----------------------------------------------------------------------

DLL_EXPORT string
QtAttributesAdaptor::getType(const string& qName) const
{
  return _sc.convert(_impl->type(_sc.convert(qName)));
}
  
// ----------------------------------------------------------------------

DLL_EXPORT string 
QtAttributesAdaptor::getType(const string& uri, 
			     const string& localName) const
{
  return _sc.convert(_impl->type( _sc.convert(uri), 
				  _sc.convert(localName)));
}
  
// ----------------------------------------------------------------------

DLL_EXPORT string
QtAttributesAdaptor::getURI(int index) const
{
  return _sc.convert(_impl->uri(index));
} 
  
// ----------------------------------------------------------------------

DLL_EXPORT string 
QtAttributesAdaptor::getValue(int index) const
{
  return _sc.convert(_impl->value(index));
}
  
// ----------------------------------------------------------------------

DLL_EXPORT string 
QtAttributesAdaptor::getValue(const string& qName) const
{
  return _sc.convert( _impl->value(_sc.convert(qName)) );
}
  
// ----------------------------------------------------------------------

DLL_EXPORT string 
QtAttributesAdaptor::getValue(const string& uri, 
			      const string& localName) const
{
  return _sc.convert( _impl->value(_sc.convert(uri),
				   _sc.convert(localName)) );
}
  
// ----------------------------------------------------------------------

} // namespace qgxml
