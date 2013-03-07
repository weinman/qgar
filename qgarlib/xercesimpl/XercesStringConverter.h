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


#ifndef __XERCESSTRINGCONVERTER_H_INCLUDED__
#define __XERCESSTRINGCONVERTER_H_INCLUDED__


/**
 * @file     XercesStringConverter.h
 * @brief    Header file of class XercesStringConverter
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 28, 2003  11:27
 * @since    Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: XercesStringConverter.h,v 1.1 2003/04/29 13:25:10 rendek Exp $ */


// STD
#include <string>

// XERCES
#include <xercesc/util/XMLString.hpp>

namespace qgxml {

class XercesStr {

public:  
  
  XercesStr(XMLCh * str) : _str(str)
  { /* NOP */ }

  XercesStr(const XercesStr& rhs) 
  {
    _str = xercesc::XMLString::replicate(rhs._str);
  }

  ~XercesStr() 
  { 
    xercesc::XMLString::release(&_str); 
  }

  operator XMLCh*() { 
    return _str; 
  }

private:
  XMLCh * _str;

  XercesStr& operator=(const XercesStr&);
};


/**
 * @class XercesStringConverter XercesStringConverter.h
 * @brief <BRIEF DESCRIPTION ENDING BY A BLANK LINE>
 * 
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 28, 2003  11:27
 * @since  Qgar 2.1
 */
class XercesStringConverter {

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  // ----------------------------------------------------
  // USING DEFAULT CONSTRUCTORS, DESTRUCTOR AND OPERATOR.
  // ----------------------------------------------------


  static std::string convert(const XMLCh * xString) 
  {
    if (xString) {

      // Convert string.
      char * s =  xercesc::XMLString::transcode(xString);
      std::string retval(s);

      // Cleanup
      xercesc::XMLString::release(&s);      

      return retval;
    }

    else {

      return std::string("");
    }	 
  }

// -------------------------------------------------------------------

  static XercesStr convert(const std::string& stlString) 
  {
    return XercesStr(xercesc::XMLString::transcode(stlString.c_str()));
  }

// -------------------------------------------------------------------

  std::string operator()(const XMLCh * xString)
  {
    return convert(xString);
  }
  
// -------------------------------------------------------------------

  XercesStr operator()(const std::string& stlString)
  {
    return convert(stlString);
  }

// -------------------------------------------------------------------

}; // class XercesStringConverter

} // namespace qgxml


#endif /* __XERCESSTRINGCONVERTER_H_INCLUDED__ */
