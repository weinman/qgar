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


#ifndef __XERCESQGARINPUTSOURCEADAPTOR_H_INCLUDED__
#define __XERCESQGARINPUTSOURCEADAPTOR_H_INCLUDED__


/**
 * @file     XercesQgarInputSourceAdaptor.h
 * @brief    Header file of class XercesQgarInputSourceAdaptor
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 31, 2003  17:51
 * @since    Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: XercesQgarInputSourceAdaptor.h,v 1.2 2004/06/21 15:50:53 rendek Exp $ */


// QGAR
#include <qgarlib/xercesimpl/BinInputStreamAdaptor.h>
#include <qgarlib/xercesimpl/XercesStringConverter.h>
#include <qgarlib/sax/InputSource.h>

// XERCES
#include <xercesc/sax/InputSource.hpp>
#include <xercesc/util/BinInputStream.hpp>


namespace qgxml {


/**
 * @class XercesQgarInputSourceAdaptor XercesQgarInputSourceAdaptor.h
 * @brief <BRIEF DESCRIPTION ENDING BY A BLANK LINE>
 * 
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 31, 2003  17:51
 * @since  Qgar 2.1
 */
class XercesQgarInputSourceAdaptor : public xercesc::InputSource {

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:


/** @name CONSTRUCTORS */
//        ============
//@{
/**
 * @brief Default constructor
 */
  XercesQgarInputSourceAdaptor(qgxml::InputSource * source)
    :  xercesc::InputSource(XercesStringConverter::convert(source->getSystemId()),
			    XercesStringConverter::convert(source->getPublicId()))
  {
    _impl = source;
  }

//@}



  virtual xercesc::BinInputStream * makeStream () const
  {
    xercesc::BinInputStream * retval;

    if (_impl->getByteStream()) {
      
      retval = new BinInputStreamAdaptor(_impl->getByteStream());
    }
    else {
      
      retval = 0;
    }

    return retval;
  }

// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  qgxml::InputSource * _impl;

// -------------------------------------------------------------------

}; // class XercesQgarInputSourceAdaptor

} // namespace qgxml


#endif /* __XERCESQGARINPUTSOURCEADAPTOR_H_INCLUDED__ */
