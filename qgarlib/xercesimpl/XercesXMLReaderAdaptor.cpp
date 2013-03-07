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
 * @file  XercesXMLReaderAdaptor.cpp
 * @brief Implementation of class XercesXMLReaderAdaptor.
 *
 *        See file XercesXMLReaderAdaptor.h for the interface.
 *
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   April 1, 2003  10:33
 * @since  Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: XercesXMLReaderAdaptor.cpp,v 1.3 2004/07/01 22:19:37 masini Exp $ */


#include <qgarlib/xercesimpl/XercesXMLReaderAdaptor.h>

// QGAR
#include <qgarlib/xercesimpl/XercesQgarContentHandlerAdaptor.h>
#include <qgarlib/xercesimpl/XercesQgarDTDHandlerAdaptor.h>
#include <qgarlib/xercesimpl/XercesQgarEntityResolverAdaptor.h>
#include <qgarlib/xercesimpl/XercesQgarErrorHandlerAdaptor.h>
#include <qgarlib/xercesimpl/XercesQgarInputSourceAdaptor.h>

// STD
#include <stdexcept>

// XERCES
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLException.hpp>
#include <xercesc/util/XMLString.hpp>

using namespace std;

namespace qgxml {


// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
XercesXMLReaderAdaptor::XercesXMLReaderAdaptor()
{

  xercesc::XMLPlatformUtils::Initialize();
  _impl = xercesc::XMLReaderFactory::createXMLReader();

  //-- Initialize handler pointers

  _contentHandler = 0;
  _dtdHandler     = 0;
  _entityRes      = 0;
  _errorHandler   = 0;


  //-- Initialize wrapper objs

  _contentHandlerA = 0;
  _dtdHandlerA     = 0;
  _entityResA      = 0;
  _errorHandlerA   = 0;
}



// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

XercesXMLReaderAdaptor::~XercesXMLReaderAdaptor()
{ 
  delete _impl;

  delete _contentHandlerA;
  delete _dtdHandlerA;
  delete _entityResA;
  delete _errorHandlerA;
}



// ---------------------------------------------------------------------
// A C C E S S
// ---------------------------------------------------------------------

ContentHandler * 
XercesXMLReaderAdaptor::getContentHandler() const
{
  return _contentHandler;;
}
  
// ---------------------------------------------------------------------

DTDHandler *
XercesXMLReaderAdaptor::getDTDHandler() const
{
  return _dtdHandler;
}

// ---------------------------------------------------------------------

EntityResolver * 
XercesXMLReaderAdaptor::getEntityResolver() const
{
  return _entityRes;
}

// ---------------------------------------------------------------------

ErrorHandler * 
XercesXMLReaderAdaptor::getErrorHandler() const
{
  return _errorHandler;
}
// ----------------------------------------------------------------------

bool 
XercesXMLReaderAdaptor::getFeature(const string& name) const
{
  return _impl->getFeature(_sc.convert(name));
}

// ---------------------------------------------------------------------

void * 
XercesXMLReaderAdaptor::getProperty(const string& name) const
{
  return _impl->getProperty(_sc.convert(name));
}


// ---------------------------------------------------------------------
// T R A N S F O R M A T I O N
// ----------------------------------------------------------------------

void 
XercesXMLReaderAdaptor::setContentHandler(ContentHandler * handler)
{
  _contentHandler = handler;

  delete _contentHandlerA;
  _contentHandlerA = new XercesQgarContentHandlerAdaptor(handler);

  _impl->setContentHandler(_contentHandlerA);
}

// ---------------------------------------------------------------------

void 
XercesXMLReaderAdaptor::setDTDHandler(DTDHandler * handler)
{
  _dtdHandler = handler;
  
  delete _dtdHandlerA;
  _dtdHandlerA = new XercesQgarDTDHandlerAdaptor(handler);

  _impl->setDTDHandler(_dtdHandlerA);
}

// ---------------------------------------------------------------------

void 
XercesXMLReaderAdaptor::setEntityResolver(EntityResolver * resolver)
{
  _entityRes = resolver;

  delete _entityResA;
  _entityResA = new XercesQgarEntityResolverAdaptor(resolver);

  _impl->setEntityResolver(_entityResA);
}

// ---------------------------------------------------------------------

void 
XercesXMLReaderAdaptor::setErrorHandler(ErrorHandler * handler)
{
  _errorHandler = handler;

  delete _errorHandlerA;
  _errorHandlerA = new XercesQgarErrorHandlerAdaptor(handler);

  _impl->setErrorHandler(_errorHandlerA);
}

// ---------------------------------------------------------------------

void 
XercesXMLReaderAdaptor::setFeature(const string& name, bool value)
{
  _impl->setFeature(_sc(name), value);
}

// ---------------------------------------------------------------------

void 
XercesXMLReaderAdaptor::setProperty(const string& name, void * value)
{
  _impl->setProperty(_sc(name), value);
}



// -------------------------------------------------------------------
// O T H E R 
// -------------------------------------------------------------------

void 
XercesXMLReaderAdaptor::parse(InputSource& input)
{
  XercesQgarInputSourceAdaptor source(&input);

  _impl->parse(source);
}

// ---------------------------------------------------------------------

void 
XercesXMLReaderAdaptor::parse(const string& systemId)
{
  _impl->parse(_sc.convert(systemId));
}


// ----------------------------------------------------------------------

} // namespace qgxml
