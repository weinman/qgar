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


#ifndef __XERCESATTRIBUTESADAPTOR_H_INCLUDED__
#define __XERCESATTRIBUTESADAPTOR_H_INCLUDED__


/**
 * @file     XercesAttributesAdaptor.h
 * @brief    Header file of class XercesAttributesAdaptor
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 31, 2003  10:10
 * @since    Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: XercesAttributesAdaptor.h,v 1.2 2004/06/21 15:50:53 rendek Exp $ */


// QGAR
#include <qgarlib/sax/Attributes.h>
#include <qgarlib/xercesimpl/XercesStringConverter.h>

// XERCES
#include <xercesc/sax2/Attributes.hpp>

namespace qgxml {


/**
 * @class XercesAttributesAdaptor XercesAttributesAdaptor.h
 * @brief <BRIEF DESCRIPTION ENDING BY A BLANK LINE>
 * 
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 31, 2003  10:10
 * @since  Qgar 2.1
 */
class XercesAttributesAdaptor : public Attributes {

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
  XercesAttributesAdaptor(xercesc::Attributes * attributes);

//@}


/** @name Destructors */
//        ===========
//@{
/**
 * @brief Destructor
 */
  virtual ~XercesAttributesAdaptor();
//@}


/** @name Access */
//        ======
//@{

  virtual int getIndex(const std::string& qName) const;
  
  virtual int getIndex(const std::string& uri, 
		       const std::string& localName) const;
  
  virtual int getLength() const;
  
  virtual std::string getLocalName(int index) const;
  
  virtual std::string getQName(int index) const;
  
  virtual std::string getType(int index) const;
  
  virtual std::string getType(const std::string& qName) const;
  
  virtual std::string getType(const std::string& uri, 
			      const std::string& localName) const;

  virtual std::string getURI(int index) const;
  
  virtual std::string getValue(int index) const;
  
  virtual std::string getValue(const std::string& qName) const;
  
  virtual std::string getValue(const std::string& uri, 
			       const std::string& localName) const;
//@}



// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  xercesc::Attributes * _impl;
  
  XercesStringConverter _sc;


// -------------------------------------------------------------------

}; // class XercesAttributesAdaptor

} // namespace qgxml


#endif /* __XERCESATTRIBUTESADAPTOR_H_INCLUDED__ */
