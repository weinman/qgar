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
 * @file  QtXMLReaderAdaptor.cpp
 * @brief Implementation of class QtXMLReaderAdaptor.
 *
 *        See file QtXMLReaderAdaptor.h for the interface.
 *
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 11, 2003  11:08
 * @since  Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QtXMLReaderAdaptor.cpp,v 1.3 2004/07/01 22:19:21 masini Exp $ */


#include <qgarlib/qtimpl/QtXMLReaderAdaptor.h>

// QGAR
#include <qgarlib/qtimpl/QtQgarContentHandlerAdaptor.h>
#include <qgarlib/qtimpl/QtQgarDTDHandlerAdaptor.h>
#include <qgarlib/qtimpl/QtQgarEntityResolverAdaptor.h>
#include <qgarlib/qtimpl/QtQgarErrorHandlerAdaptor.h>
#include <qgarlib/qtimpl/QtQgarInputSourceAdaptor.h>
#include <qgarlib/sax/ContentHandler.h>
#include <qgarlib/sax/DTDHandler.h>
#include <qgarlib/sax/EntityResolver.h>
#include <qgarlib/sax/ErrorHandler.h>


// STD
#include <stdexcept>


using namespace std;

namespace qgxml {


// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

DLL_EXPORT QtXMLReaderAdaptor::QtXMLReaderAdaptor()
{
  _impl = new QXmlSimpleReader();


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

DLL_EXPORT QtXMLReaderAdaptor::~QtXMLReaderAdaptor()
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

DLL_EXPORT ContentHandler * 
QtXMLReaderAdaptor::getContentHandler() const
{
  return _contentHandler;
}
  
// ---------------------------------------------------------------------

DLL_EXPORT DTDHandler *
QtXMLReaderAdaptor::getDTDHandler() const
{
  return _dtdHandler;
}

// ---------------------------------------------------------------------

DLL_EXPORT EntityResolver * 
QtXMLReaderAdaptor::getEntityResolver() const
{
  return _entityRes;
}

// ---------------------------------------------------------------------

DLL_EXPORT ErrorHandler * 
QtXMLReaderAdaptor::getErrorHandler() const
{
  return _errorHandler;
}

// ---------------------------------------------------------------------

DLL_EXPORT bool 
QtXMLReaderAdaptor::getFeature(const string& name) const
{
  return _impl->hasFeature(_sc.convert(name));
}

// ---------------------------------------------------------------------

DLL_EXPORT void * 
QtXMLReaderAdaptor::getProperty(const string& name) const
{
  return _impl->property(_sc.convert(name));
}



// ---------------------------------------------------------------------
// T R A N S F O R M A T I O N
// ----------------------------------------------------------------------

DLL_EXPORT void 
QtXMLReaderAdaptor::setContentHandler(ContentHandler * handler)
{
  _contentHandler = handler;

  delete _contentHandlerA;
  _contentHandlerA = new QtQgarContentHandlerAdaptor(handler);

  _impl->setContentHandler(_contentHandlerA);
}

// ---------------------------------------------------------------------

DLL_EXPORT void 
QtXMLReaderAdaptor::setDTDHandler(DTDHandler * handler)
{
  _dtdHandler = handler;

  delete _dtdHandlerA;
  _dtdHandlerA = new QtQgarDTDHandlerAdaptor(handler);

  _impl->setDTDHandler(_dtdHandlerA);
}

// ---------------------------------------------------------------------

DLL_EXPORT void 
QtXMLReaderAdaptor::setEntityResolver(EntityResolver * resolver)
{
  _entityRes = resolver;

  delete _entityResA;
  _entityResA = new QtQgarEntityResolverAdaptor(resolver);

  _impl->setEntityResolver(_entityResA);
}

// ---------------------------------------------------------------------

DLL_EXPORT void 
QtXMLReaderAdaptor::setErrorHandler(ErrorHandler * handler)
{
  _errorHandler = handler;

  delete _errorHandlerA;
  _errorHandlerA = new QtQgarErrorHandlerAdaptor(handler);

  _impl->setErrorHandler(_errorHandlerA);
}

// ---------------------------------------------------------------------

DLL_EXPORT void 
QtXMLReaderAdaptor::setFeature(const string& name, bool value)
{
  _impl->setFeature(_sc(name), value);
}

// ---------------------------------------------------------------------

DLL_EXPORT void 
QtXMLReaderAdaptor::setProperty(const string& name, void * value)
{
  _impl->setProperty(_sc(name), value);
}


// -------------------------------------------------------------------
// O T H E R 
// -------------------------------------------------------------------

DLL_EXPORT void 
QtXMLReaderAdaptor::parse(InputSource& input)
{
  QtQgarInputSourceAdaptor * source = 
    new QtQgarInputSourceAdaptor(&input);
  
  _impl->parse(source);
  
  delete source;
}

// ---------------------------------------------------------------------

DLL_EXPORT void 
QtXMLReaderAdaptor::parse(const string& systemId)
{
  throw runtime_error("Feature unsupported by Qt\n");
}


// ----------------------------------------------------------------------

} // namespace qgxml
