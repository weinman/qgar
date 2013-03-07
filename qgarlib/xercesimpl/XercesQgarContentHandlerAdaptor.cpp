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
 * @file  XercesQgarContentHandlerAdaptor.cpp
 * @brief Implementation of class XercesQgarContentHandlerAdaptor.
 *
 *        See file XercesQgarContentHandlerAdaptor.h for the interface.
 *
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 31, 2003  10:24
 * @since  Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: XercesQgarContentHandlerAdaptor.cpp,v 1.3 2004/07/01 22:19:37 masini Exp $ */


#include <qgarlib/xercesimpl/XercesQgarContentHandlerAdaptor.h>

// QGAR
#include <qgarlib/sax/ContentHandler.h>
#include <qgarlib/sax/SAXException.h>
#include <qgarlib/xercesimpl/XercesAttributesAdaptor.h>
#include <qgarlib/xercesimpl/XercesLocatorAdaptor.h>

// XERCES
#include <xercesc/sax/SAXException.hpp>

namespace qgxml {


// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

XercesQgarContentHandlerAdaptor::XercesQgarContentHandlerAdaptor(
				     qgxml::ContentHandler * handler
					     )
{
  _impl = handler;
  _locatorImpl = 0;
}




// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

XercesQgarContentHandlerAdaptor::~XercesQgarContentHandlerAdaptor() 
{
  delete _locatorImpl;
}



// ---------------------------------------------------------------------
// O T H E R
// ---------------------------------------------------------------------

void 
XercesQgarContentHandlerAdaptor::characters(const XMLCh * const chars, 
					    const unsigned int length)
{
  try {

    _impl->characters(_sc(chars).c_str(), 0, length);
  }
  catch (qgxml::SAXException& se) {
    throw xercesc::SAXException(se.getMessage());
  }
}

// ---------------------------------------------------------------------

void
XercesQgarContentHandlerAdaptor::endDocument()
{
  try {

    _impl->endDocument();
  }
  catch (qgxml::SAXException& se) {
    throw xercesc::SAXException(se.getMessage());
  }  
}

// ---------------------------------------------------------------------

void
XercesQgarContentHandlerAdaptor::endElement(const XMLCh * const uri, 
					    const XMLCh * const localname, 
					    const XMLCh * const qName)
{
  try {

    _impl->endElement(_sc(uri), _sc(localname), _sc(qName));
  }
  catch (qgxml::SAXException& se) {
    throw xercesc::SAXException(se.getMessage());
  }  
}
  
// ---------------------------------------------------------------------

void
XercesQgarContentHandlerAdaptor::ignorableWhitespace(const XMLCh * const chars, 
						     const unsigned
						     int length)
{
  try {
    
    _impl->ignorableWhitespace(_sc(chars).c_str(), 0, length);
  }
  catch (qgxml::SAXException& se) {
    throw xercesc::SAXException(se.getMessage());
  }  
}

// ---------------------------------------------------------------------

void
XercesQgarContentHandlerAdaptor::processingInstruction(const XMLCh * const target, 
						       const XMLCh * const data)
{
  try {
    
    _impl->processingInstruction(_sc(target), _sc(data));
  }
  catch (qgxml::SAXException& se) {
    throw xercesc::SAXException(se.getMessage());
  }    
}

// ---------------------------------------------------------------------

void
XercesQgarContentHandlerAdaptor::setDocumentLocator(
				  const xercesc::Locator * const locator
				  )
{
  //-- Update the locator adaptor.
  
  delete _locatorImpl;
  _locatorImpl = new XercesLocatorAdaptor(const_cast<xercesc::Locator *>(locator));
  
  
  //-- Delegate to the adaptee.

  _impl->setDocumentLocator(_locatorImpl);

}

// ---------------------------------------------------------------------

void
XercesQgarContentHandlerAdaptor::startDocument()
{
  try {
    
    _impl->startDocument();
  }
  catch (qgxml::SAXException& se) {
    throw xercesc::SAXException(se.getMessage());
  }      
}

// ---------------------------------------------------------------------

void
XercesQgarContentHandlerAdaptor::startElement(const XMLCh * const uri,
					      const XMLCh * const localname,
					      const XMLCh * const qname, 
					      const xercesc::Attributes & attrs)
{
  try {
    
    _impl->startElement(_sc(uri),
			_sc(localname),
			_sc(qname),
			XercesAttributesAdaptor(
			    const_cast<xercesc::Attributes *>(&attrs))
			);
  }
  catch (qgxml::SAXException& se) {
    throw xercesc::SAXException(se.getMessage());
  }      
}
  
// ---------------------------------------------------------------------

void
XercesQgarContentHandlerAdaptor::startPrefixMapping(const XMLCh * const prefix, 
						    const XMLCh * const uri)
{
  try {
    
    _impl->startPrefixMapping(_sc(prefix), _sc(uri));
  }
  catch (qgxml::SAXException& se) {
    throw xercesc::SAXException(se.getMessage());
  }      
}

// ---------------------------------------------------------------------

void
XercesQgarContentHandlerAdaptor::endPrefixMapping(const XMLCh * const prefix)
{
  try {
    
    _impl->endPrefixMapping(_sc(prefix));
  }
  catch (qgxml::SAXException& se) {
    throw xercesc::SAXException(se.getMessage());
  }      
}

// ---------------------------------------------------------------------

void
XercesQgarContentHandlerAdaptor::skippedEntity(const XMLCh * name)
{
  try {
    
    _impl->skippedEntity(_sc(name));
  }
  catch (qgxml::SAXException& se) {
    throw xercesc::SAXException(se.getMessage());
  }      
}
  
// ----------------------------------------------------------------------

} // namespace qgxml
