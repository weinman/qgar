/*---------------------------------------------------------------------*
 | Library QgarLib, graphics analysis and recognition                  |
 | Copyright (C) 2002  Qgar Project, LORIA                             |
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
 | http://www.gnu.org/licenses/lgpl.html for the terms of the licence. |
 | To receive a paper copy, write to the Free Software Foundation,     |
 | Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.       |
 |                                                                     |
 | Contact Project Qgar for any information:                           |
 |   LORIA - équipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-lès-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/


/**
 * @file  QGAbstractMainWindowCommand.cpp
 * @brief Implementation of class QGAbstractMainWindowCommand
 *
 *        See file QGAbstractMainWindowCommand.h for the interface.
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   September 26, 2002  11:27
 * @since  Qgar 2.1
 */



// QGUI
#include "QGAbstractMainWindowCommand.h"
#include "QGMainWindow.h"



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

QGAbstractMainWindowCommand::QGAbstractMainWindowCommand()
  : _target(0)
{ /* EMPTY */ }


// -------------------------------------------------------------------

QGAbstractMainWindowCommand::QGAbstractMainWindowCommand(QGMainWindow* target) 
  : _target(target)
{ /* EMPTY */ }

// -------------------------------------------------------------------

QGAbstractMainWindowCommand::QGAbstractMainWindowCommand(const QGAbstractMainWindowCommand& rhs)
{
  _target = rhs._target;
}

// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------

QGAbstractMainWindowCommand::~QGAbstractMainWindowCommand()
{ /* EMPTY */ }

// ---------------------------------------------------------------------
// A C C E S S
// ---------------------------------------------------------------------

const QGMainWindow * 
QGAbstractMainWindowCommand::target() const 
{
  return _target;
}

// -------------------------------------------------------------------
// T R A N S F O R M A T I O N 
// -------------------------------------------------------------------

void
QGAbstractMainWindowCommand::setTarget(QGMainWindow * target) 
{
  _target = target;
}

// ---------------------------------------------------------------------
// O P E R A T O R S
// ----------------------------------------------------------------------

// Assignment operator
QGAbstractMainWindowCommand& 
QGAbstractMainWindowCommand::operator=(const QGAbstractMainWindowCommand& rhs) 
{
  if (this != &rhs)
    _target = rhs._target;

  return *this;
}

// ----------------------------------------------------------------------
