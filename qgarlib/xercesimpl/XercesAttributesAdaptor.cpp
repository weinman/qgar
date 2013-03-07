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
 * @file  XercesAttributesAdaptor.cpp
 * @brief Implementation of class XercesAttributesAdaptor.
 *
 *        See file XercesAttributesAdaptor.h for the interface.
 *
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 31, 2003  10:10
 * @since  Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: XercesAttributesAdaptor.cpp,v 1.3 2004/07/01 22:19:37 masini Exp $ */


#include <qgarlib/xercesimpl/XercesAttributesAdaptor.h>

using namespace std;

namespace qgxml {


// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
XercesAttributesAdaptor::XercesAttributesAdaptor(xercesc::Attributes * attributes) 
{
  _impl = attributes;
}



// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

XercesAttributesAdaptor::~XercesAttributesAdaptor()
{ /* NOP */ }



// ---------------------------------------------------------------------
// A C C E S S
// ---------------------------------------------------------------------

int
XercesAttributesAdaptor::getIndex(const string& qName) const
{
  return _impl->getIndex( _sc.convert(qName) );
}

// ----------------------------------------------------------------------

int 
XercesAttributesAdaptor::getIndex(const string& uri, 
				  const string& localName) const
{
  return _impl->getIndex(_sc.convert(uri), _sc.convert(localName));
}

// ----------------------------------------------------------------------

int
XercesAttributesAdaptor::getLength() const
{
  return _impl->getLength();
}
  
// ----------------------------------------------------------------------

string
XercesAttributesAdaptor::getLocalName(int index) const
{
  return _sc.convert(_impl->getLocalName(index));
}
 
// ----------------------------------------------------------------------

string
XercesAttributesAdaptor::getQName(int index) const
{
  return _sc.convert(_impl->getQName(index));
}
  
// ----------------------------------------------------------------------

string
XercesAttributesAdaptor::getType(int index) const
{
  return _sc.convert(_impl->getType(index));
}
  
// ----------------------------------------------------------------------

string
XercesAttributesAdaptor::getType(const string& qName) const
{
  return _sc.convert(_impl->getType(_sc.convert(qName)));
}
  
// ----------------------------------------------------------------------

string 
XercesAttributesAdaptor::getType(const string& uri, 
				 const string& localName) const
{
  return _sc.convert(_impl->getType( _sc.convert(uri), 
				     _sc.convert(localName)));
}
  
// ----------------------------------------------------------------------

string
XercesAttributesAdaptor::getURI(int index) const
{
  return _sc.convert(_impl->getURI(index));
} 
  
// ----------------------------------------------------------------------

string 
XercesAttributesAdaptor::getValue(int index) const
{
  return _sc.convert(_impl->getValue(index));
}
  
// ----------------------------------------------------------------------

string 
XercesAttributesAdaptor::getValue(const string& qName) const
{
  return _sc.convert( _impl->getValue(_sc.convert(qName)) );
}
  
// ----------------------------------------------------------------------

string 
XercesAttributesAdaptor::getValue(const string& uri, 
				  const string& localName) const
{
  return _sc.convert( _impl->getValue(_sc.convert(uri),
				      _sc.convert(localName)) );
}

// ----------------------------------------------------------------------

} // namespace qgxml
