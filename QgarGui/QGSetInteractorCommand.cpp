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
 * @file  QGSetInteractorCommand.cpp
 * @brief Implementation of class QGSetInteractorCommand.
 *
 * See file QGSetInteractorCommand.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 7, 2002  10:17
 * @since  Qgar 2.1
 */



// QGUI
#include "QGSetInteractorCommand.h"
#include "QGInteractorIf.h"
#include "QGMainWindow.h"



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGSetInteractorCommand::QGSetInteractorCommand(QGMainWindow * main,
					       QGInteractorIf * interact)
  : QGAbstractMainWindowCommand(main)
{ 
  _interactor = interact;
}


// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

// Default constructor
QGSetInteractorCommand::~QGSetInteractorCommand() 
{
  delete _interactor;
}


// -------------------------------------------------------------------
// Q G C O M M A N D I F     I M P L 
// -------------------------------------------------------------------

void
QGSetInteractorCommand::execute()
{
  if (_target->currentInteractor() != _interactor)
    _target->setCurrentInteractor(_interactor);
}

// ----------------------------------------------------------------------
