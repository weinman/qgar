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


#ifndef __XERCESQGARCONTENTHANDLERADAPTOR_H_INCLUDED__
#define __XERCESQGARCONTENTHANDLERADAPTOR_H_INCLUDED__


/**
 * @file     XercesQgarContentHandlerAdaptor.h
 * @brief    Header file of class XercesQgarContentHandlerAdaptor
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 31, 2003  10:24
 * @since    Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: XercesQgarContentHandlerAdaptor.h,v 1.2 2004/06/21 15:50:53 rendek Exp $ */

// QGAR
#include <qgarlib/xercesimpl/XercesStringConverter.h>

// XERCES
#include <xercesc/sax2/ContentHandler.hpp>


namespace qgxml {

class ContentHandler;
class XercesLocatorAdaptor;

/**
 * @class XercesQgarContentHandlerAdaptor XercesQgarContentHandlerAdaptor.h
 * @brief <BRIEF DESCRIPTION ENDING BY A BLANK LINE>
 * 
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 31, 2003  10:24
 * @since  Qgar 2.1
 */
class XercesQgarContentHandlerAdaptor : public xercesc::ContentHandler
{

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
  explicit  XercesQgarContentHandlerAdaptor(qgxml::ContentHandler * handler);


//@}


/** @name Destructors */
//        ===========
//@{
/**
 * @brief Destructor
 */
  virtual ~XercesQgarContentHandlerAdaptor();
//@}

  virtual void characters(const XMLCh * const chars, 
			  const unsigned int length);

  virtual void endDocument();

  virtual void endElement(const XMLCh * const uri, 
			  const XMLCh * const localname, 
			  const XMLCh * const qName); 
  
  virtual void ignorableWhitespace(const XMLCh * const chars, 
				   const unsigned int length);

  virtual void processingInstruction(const XMLCh * const target, 
				     const XMLCh * const data );

  virtual void setDocumentLocator(const xercesc::Locator * const  locator);

  virtual void startDocument();

  virtual void startElement(const XMLCh * const uri,
			    const XMLCh * const localname, 
			    const XMLCh * const qname, 
			    const xercesc::Attributes & attrs);
  
  virtual void startPrefixMapping(const XMLCh * const prefix, 
				  const XMLCh * const uri);  

  virtual void endPrefixMapping(const XMLCh * const prefix );

  virtual void skippedEntity(const XMLCh * name );
  


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:
  
  qgxml::ContentHandler * _impl;

  XercesStringConverter _sc;

  XercesLocatorAdaptor * _locatorImpl;

}; // class XercesQgarContentHandlerAdaptor

} // namespace qgxml


#endif /* __XERCESQGARCONTENTHANDLERADAPTOR_H_INCLUDED__ */
