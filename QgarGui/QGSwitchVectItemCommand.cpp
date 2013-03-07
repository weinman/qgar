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
 * @file  QGSwitchVectItemCommand.cpp
 * @brief Implementation of class QGSwitchVectItemCommand.
 *
 * See file QGSwitchVectItemCommand.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 28, 2002  09:48
 * @since  Qgar 2.1
 */



// QGUI
#include "QGSwitchVectItemCommand.h"
#include "QGDeleteVectItemCommand.h"
#include "QGInsertVectItemCommand.h"
#include "QGVectorialLayer.h"
// QT
#include <QGraphicsItem>



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGSwitchVectItemCommand::QGSwitchVectItemCommand(QGVectorialLayer * layer,
						 QGraphicsItem * oldItem,
						 QGraphicsItem * newItem)
{
  _deleteOldCmd = new QGDeleteVectItemCommand(layer, oldItem);
  _insertNewCmd = new QGInsertVectItemCommand(layer, newItem);
}

// ---------------------------------------------------------------------

// Copy constructor
QGSwitchVectItemCommand::QGSwitchVectItemCommand(const QGSwitchVectItemCommand& rhs)
{
  _deleteOldCmd = new QGDeleteVectItemCommand( *(rhs._deleteOldCmd) );
  _insertNewCmd = new QGInsertVectItemCommand( *(rhs._insertNewCmd) );
}


// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

// Default constructor
QGSwitchVectItemCommand::~QGSwitchVectItemCommand() 
{
  delete _deleteOldCmd;
  delete _insertNewCmd;
}


// -------------------------------------------------------------------
// Q G U N D O A B L E C O M M A N D I F     I M P L 
// -------------------------------------------------------------------

void
QGSwitchVectItemCommand::execute()
{
  _deleteOldCmd->execute();
  _insertNewCmd->execute();
}

// ---------------------------------------------------------------------

void
QGSwitchVectItemCommand::undo()
{
  _insertNewCmd->undo();
  _deleteOldCmd->undo();
}

// ---------------------------------------------------------------------

QGUndoableCommandIf *
QGSwitchVectItemCommand::clone() const
{
  return new QGSwitchVectItemCommand(*this);
}


// ---------------------------------------------------------------------
// O P E R A T O R S
// ----------------------------------------------------------------------

// Assignment operator
QGSwitchVectItemCommand&
QGSwitchVectItemCommand::operator=(const QGSwitchVectItemCommand& rhs) 
{
  if (this != &rhs)
    {
      QGUndoableCommandIf::operator=(rhs);
    
      _deleteOldCmd = new QGDeleteVectItemCommand( *(rhs._deleteOldCmd) );
      _insertNewCmd = new QGInsertVectItemCommand( *(rhs._insertNewCmd) );
  }
  
  return *this;
}

// ----------------------------------------------------------------------

