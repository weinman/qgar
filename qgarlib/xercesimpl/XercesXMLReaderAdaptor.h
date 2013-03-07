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


#ifndef __XERCESXMLREADERADAPTOR_H_INCLUDED__
#define __XERCESXMLREADERADAPTOR_H_INCLUDED__


/**
 * @file     XercesXMLReaderAdaptor.h
 * @brief    Header file of class XercesXMLReaderAdaptor
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     April 1, 2003  10:33
 * @since    Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: XercesXMLReaderAdaptor.h,v 1.2 2004/06/21 15:50:53 rendek Exp $ */


#include <qgarlib/sax/XMLReader.h>

// QGAR
#include <qgarlib/xercesimpl/XercesStringConverter.h>


// XERCES
#include <xercesc/sax2/SAX2XMLReader.hpp>



namespace qgxml {

class ContentHandler;
class DTDHandler;
class EntityResolver;
class ErrorHandler;

class XercesQgarContentHandlerAdaptor;
class XercesQgarDTDHandlerAdaptor;
class XercesQgarEntityResolverAdaptor;
class XercesQgarErrorHandlerAdaptor;


/**
 * @class XercesXMLReaderAdaptor XercesXMLReaderAdaptor.h
 * @brief <BRIEF DESCRIPTION ENDING BY A BLANK LINE>
 * 
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   April 1, 2003  10:33
 * @since  Qgar 2.1
 */
class XercesXMLReaderAdaptor : public XMLReader {

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
  XercesXMLReaderAdaptor();
//@}


/** @name Destructor */
//        ==========
//@{
/**
 * @brief Destructor
 */
virtual ~XercesXMLReaderAdaptor();
//@}


/** @name Access */
//        ======
//@{

  virtual ContentHandler * getContentHandler() const;

  virtual DTDHandler * getDTDHandler() const;

  virtual EntityResolver * getEntityResolver() const;

  virtual ErrorHandler * getErrorHandler() const;

  virtual bool getFeature(const std::string& name) const;

  virtual void * getProperty(const std::string& name) const;

//@}


  virtual void parse(InputSource& input);

  virtual void parse(const std::string& systemId);


/** @name Transformation */
//        ==============
//@{

  virtual void setContentHandler(ContentHandler * handler);

  virtual void setDTDHandler(DTDHandler * handler);

  virtual void setEntityResolver(EntityResolver * resolver);

  virtual void setErrorHandler(ErrorHandler * handler);

  virtual void setFeature(const std::string& name, bool value);

  virtual void setProperty(const std::string& name, void * value);

//@}



// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  xercesc::SAX2XMLReader * _impl;

  ContentHandler * _contentHandler;
  DTDHandler     * _dtdHandler;
  EntityResolver * _entityRes;
  ErrorHandler   * _errorHandler;

  XercesQgarContentHandlerAdaptor * _contentHandlerA;
  XercesQgarDTDHandlerAdaptor *     _dtdHandlerA;
  XercesQgarEntityResolverAdaptor * _entityResA;
  XercesQgarErrorHandlerAdaptor *   _errorHandlerA;
  
  XercesStringConverter _sc;

}; // class XercesXMLReaderAdaptor

} // namespace qgxml


#endif /* __XERCESXMLREADERADAPTOR_H_INCLUDED__ */
