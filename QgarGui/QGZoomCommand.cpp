/*---------------------------------------------------------------------*
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
 * @file  QGZoomCommand.cpp
 * @brief Implementation of class QGZoomCommand.
 *
 * See file QGZoomCommand.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 2, 2002  17:37
 * @since  Qgar 2.1
 */



// QGUI
#include "QGZoomCommand.h"
#include "QGMainWindow.h"
// STD
#include <stdexcept>



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGZoomCommand::QGZoomCommand(QGMainWindow * target)

  : QGAbstractMainWindowCommand(target), _zoomInc(1.0)

{
  // VOID
}


// Default constructor
QGZoomCommand::QGZoomCommand(QGMainWindow * target, float zoomInc)

  : QGAbstractMainWindowCommand(target), _zoomInc(zoomInc)

{
  // VOID
}


// Copy-constructor
QGZoomCommand::QGZoomCommand(const QGZoomCommand& other)

  : QGAbstractMainWindowCommand(other), _zoomInc(other._zoomInc)

{
  // VOID
}

// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------

QGZoomCommand::~QGZoomCommand() 
{
  // VOID
}

// ---------------------------------------------------------------------
// A C C E S S
// ---------------------------------------------------------------------


float
QGZoomCommand::zoomInc() const
{
  return  _zoomInc;
}


// ---------------------------------------------------------------------
// T R A N S F O R M A T I O N
// ----------------------------------------------------------------------

void
QGZoomCommand::setZoomInc(float level)
{
  if (level <= 0)
    throw std::invalid_argument("Bad parameter value");

  _zoomInc = level;
}


void 
QGZoomCommand::execute()
{
  _target->incZoom(_zoomInc);
}

// ---------------------------------------------------------------------
// O P E R A T O R S
// ----------------------------------------------------------------------

// Assignment operator
QGZoomCommand& QGZoomCommand::operator=(const QGZoomCommand& other) 
{
  _target  = other._target;
  _zoomInc = other._zoomInc;

  return *this;
}

// ----------------------------------------------------------------------

