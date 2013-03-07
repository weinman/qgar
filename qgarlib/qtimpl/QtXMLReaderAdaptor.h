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


#ifndef __QTXMLREADERADAPTOR_H_INCLUDED__
#define __QTXMLREADERADAPTOR_H_INCLUDED__

// Compatibility to shared libraries in
// Windows.
#ifdef WIN32
#define DLL_EXPORT    __declspec( dllexport )
#else
#define DLL_EXPORT
#endif

/**
 * @file     QtXMLReaderAdaptor.h
 * @brief    Header file of class QtXMLReaderAdaptor
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 11, 2003  11:08
 * @since    Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QtXMLReaderAdaptor.h,v 1.3 2004/06/21 16:03:37 rendek Exp $ */


// QGAR
#include <qgarlib/qtimpl/QtStringConverter.h>
#include <qgarlib/sax/XMLReader.h>


// QT
#include <QtXml>



namespace qgxml {

class ContentHandler;
class DTDHandler;
class EntityResolver;
class ErrorHandler;

class QtQgarContentHandlerAdaptor;
class QtQgarDTDHandlerAdaptor;
class QtQgarEntityResolverAdaptor;
class QtQgarErrorHandlerAdaptor;


/**
 * @class QtXMLReaderAdaptor QtXMLReaderAdaptor.h
 * @brief <BRIEF DESCRIPTION ENDING BY A BLANK LINE>
 * 
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 11, 2003  11:08
 * @since  Qgar 2.1
 */
class QtXMLReaderAdaptor : public XMLReader {

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
DLL_EXPORT QtXMLReaderAdaptor();

//@}


/** @name Destructor */
//        ==========
//@{
/**
 * @brief Destructor
 */
DLL_EXPORT virtual ~QtXMLReaderAdaptor();
//@}


/** @name Access */
//        ======
//@{

DLL_EXPORT  virtual ContentHandler * getContentHandler() const;

DLL_EXPORT  virtual DTDHandler * getDTDHandler() const;

DLL_EXPORT  virtual EntityResolver * getEntityResolver() const;

DLL_EXPORT  virtual ErrorHandler * getErrorHandler() const;

DLL_EXPORT  virtual bool getFeature(const std::string& name) const;

DLL_EXPORT  virtual void * getProperty(const std::string& name) const;

//@}


DLL_EXPORT  virtual void parse(InputSource& input);

DLL_EXPORT  virtual void parse(const std::string& systemId);


/** @name Transformation */
//        ==============
//@{

DLL_EXPORT  virtual void setContentHandler(ContentHandler * handler);

DLL_EXPORT  virtual void setDTDHandler(DTDHandler * handler);

DLL_EXPORT  virtual void setEntityResolver(EntityResolver * resolver);

DLL_EXPORT  virtual void setErrorHandler(ErrorHandler * handler);

DLL_EXPORT  virtual void setFeature(const std::string& name, bool value);

DLL_EXPORT  virtual void setProperty(const std::string& name, void * value);

//@}



// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  QXmlReader * _impl;

  ContentHandler * _contentHandler;
  DTDHandler     * _dtdHandler;
  EntityResolver * _entityRes;
  ErrorHandler   * _errorHandler;

  QtQgarContentHandlerAdaptor * _contentHandlerA;
  QtQgarDTDHandlerAdaptor *     _dtdHandlerA;
  QtQgarEntityResolverAdaptor * _entityResA;
  QtQgarErrorHandlerAdaptor *   _errorHandlerA;
  
  QtStringConverter _sc;

// -------------------------------------------------------------------

}; // class QtXMLReaderAdaptor

} // namespace qgxml


#endif /* __QTXMLREADERADAPTOR_H_INCLUDED__ */
