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
 |   LORIA - �quipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-l�s-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/


/**
 * @file  QIODeviceAdaptor.cpp
 * @brief Implementation of class QIODeviceAdaptor
 *
 *        See file QIODeviceAdaptor.h for the interface.
 *
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 14, 2003  15:27
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QIODeviceAdaptor.cpp,v 1.3 2004/06/21 16:03:37 rendek Exp $ */


#include <qgarlib/qtimpl/QIODeviceAdaptor.h>

#include <stdexcept>

using namespace std;

namespace qgxml {


// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
DLL_EXPORT QIODeviceAdaptor::QIODeviceAdaptor(istream * stream)
{
  _stream = stream;
  // Only the ReadOnly flag was added.
  ///////////////////////////////////
  //
  // IMPORTANT: To finish the class!
  //
  ///////////////////////////////////
  open(ReadOnly);

  //-- Initialize device with proper flag.
  //setFlags( ReadOnly | isSequential() | isOpen() );
}

// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

DLL_EXPORT QIODeviceAdaptor::~QIODeviceAdaptor()
{ 
  close();
}


// ---------------------------------------------------------------------
// O T H E R
// ---------------------------------------------------------------------
DLL_EXPORT bool
QIODeviceAdaptor::open(QIODevice::OpenMode mode)
{
  QIODevice::setOpenMode(mode);
  return true;
}
  
// ----------------------------------------------------------------------

DLL_EXPORT void
QIODeviceAdaptor::close()
{ 
  // To maintain compatibility with QIODevice::close()
  setOpenMode(NotOpen);
  setErrorString(0);

  flush();
}
  
// ----------------------------------------------------------------------

DLL_EXPORT void
QIODeviceAdaptor::flush()
{ 
  _stream->sync(); 
}

// ----------------------------------------------------------------------

DLL_EXPORT qint64
QIODeviceAdaptor::readData(char * data, qint64 maxlen)
{
  return (qint64)(_stream->readsome(data, maxlen));
}

// ----------------------------------------------------------------------

DLL_EXPORT qint64 
QIODeviceAdaptor::writeData(const char * data, qint64 len)
{
  // This class only provides the features to read from a stream.
  throw runtime_error("Unimplemented method");
  return 0;
}

// ----------------------------------------------------------------------

DLL_EXPORT bool
QIODeviceAdaptor::getChar(char * c)
{
  *c = (char)_stream->get();
  return true;
}

// ----------------------------------------------------------------------

} // namespace qgxml
