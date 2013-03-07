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


#ifndef __BININPUTSTREAMADAPTOR_H_INCLUDED__
#define __BININPUTSTREAMADAPTOR_H_INCLUDED__


/**
 * @file     BinInputStreamAdaptor.h
 * @brief    Header file of class BinInputStreamAdaptor
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 31, 2003  18:16
 * @since    Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: BinInputStreamAdaptor.h,v 1.2 2004/06/21 15:50:53 rendek Exp $ */


// XERCES
#include <xercesc/util/BinInputStream.hpp>

// STD
#include <iostream>
#include <fstream>

namespace qgxml {


/**
 * @class BinInputStreamAdaptor BinInputStreamAdaptor.h
 * @brief <BRIEF DESCRIPTION ENDING BY A BLANK LINE>
 * 
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 31, 2003  18:16
 * @since  Qgar 2.1
 *
 * @bug readBytes() has a different implementation according to the
 * dynamic type of _stream. This is a necessary workaround to the bug
 * #6746 of the libstd of gcc. Future versions will clean this as soon
 * as gcc will be upgraded.
 */
class BinInputStreamAdaptor : public xercesc::BinInputStream {

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
  BinInputStreamAdaptor(std::istream * stream)
  {
    _stream = stream;
  }

//@}


/** @name Destructor */
//        ==========
//@{
/**
 * @brief Destructor
 */
  virtual ~BinInputStreamAdaptor()
  { /* NOP */ }
//@}


  virtual unsigned int curPos() const
  {
    return (unsigned int)(_stream->tellg());
  }

  virtual unsigned int readBytes (XMLByte * const toFill, 
				  const unsigned int maxToRead)
  {

    // ---
    // @bug: Due to gcc bug #6746, readsome does not work properly
    // with ifstream instances. The following line will fix it.
    // ---
    if (std::ifstream * fs = dynamic_cast<std::ifstream *>(_stream)) {

      // --
      // Read bytes one by one until the end of file or maxToRead
      // reached 
      // --
      unsigned int count = 0;
      char * bufferPtr = (char *)toFill;

      while (fs->good() && (count < maxToRead)) {

	*(bufferPtr++) = _stream->get();
	++count;
      }

      return count;
    }

    else
      return _stream->readsome((char *)toFill, maxToRead);
  }

// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  std::istream * _stream;

// -------------------------------------------------------------------

}; // class BinInputStreamAdaptor

} // namespace qgxml


#endif /* __BININPUTSTREAMADAPTOR_H_INCLUDED__ */
