/*---------------------------------------------------------------------+
 | Graphical user interface QgarGui                                    |
 | Copyright (C) 2002  Qgar Project, LORIA                             |
 |                                                                     |
 | This file may be distributed under the terms of the Q Public        |
 | License as defined by Trolltech AS of Norway and appearing in the   |
 | file LICENSE.QPL included in root directory of the Qgar packaging.  |
 |                                                                     |
 | Licensees holding valid Qt Enterprise Edition or Qt Professional    |
 | Edition licenses may use this file in accordance with the Qt        |
 | Commercial License Agreement provided with the Software.            |
 |                                                                     |
 | This file is provided AS IS with NO WARRANTY OF ANY KIND,           |
 | INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS       |
 | FOR A PARTICULAR PURPOSE.                                           |
 |                                                                     |
 | See http://www.trolltech.com/pricing.html                           |
 | or email sales@trolltech.com for information about Qt Commercial    |
 | License Agreements.                                                 |
 | See http://www.trolltech.com/qpl/ for QPL licensing information.    |
 |                                                                     |
 | Contact info@trolltech.com if any conditions of this licensing are  |
 | not clear to you.                                                   |
 |                                                                     |
 | Contact Project Qgar for any information:                           |
 |   LORIA - équipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-lès-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/


/**
 * @file  QGApplicationEntry.cpp
 * @brief Implementation of class QGApplicationEntry.
 *
 * See file QGApplicationEntry.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   November 2, 2000  17:17
 * @since  Qgar 2.1.1
 */



// QGUI
#include "QGApplicationEntry.h"


using namespace std;
using namespace qgar; 



// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------

QGApplicationEntry::QGApplicationEntry(string name,
				       string descrPath,
				       string applicationPath)
  throw (runtime_error)
  : _name(name.c_str()), 
    _descrPath(descrPath),
    _applicationPath(applicationPath),
    _descr(descrPath)
{ /* EMPTY */ }


// -------------------------------------------------------------------
// A C C E S S
// -------------------------------------------------------------------

QString 
QGApplicationEntry::name() const 
{
  return _name;
}

// ---------------------------------------------------------------------

string
QGApplicationEntry::descrPath() const
{
  return _descrPath;
}

// ---------------------------------------------------------------------

string 
QGApplicationEntry::applicationPath() const
{
  return _applicationPath;
}

// ---------------------------------------------------------------------

QgarAppDescr
QGApplicationEntry::descr() const 
{
  return _descr;
}

// ---------------------------------------------------------------------

const QgarAppDescr&
QGApplicationEntry::accessDescr() const
{
  return _descr;
}

// ---------------------------------------------------------------------

