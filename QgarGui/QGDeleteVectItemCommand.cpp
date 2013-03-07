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
 * @file  QGDeleteVectItemCommand.cpp
 * @brief Implementation of class QGDeleteVectItemCommand
 *
 *        See file QGDeleteVectItemCommand.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 28, 2002  10:46
 */


#include "QGDeleteVectItemCommand.h"

// QGAR
#include "QGVectorialLayer.h"

// QT
#include <QGraphicsItem>

// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGDeleteVectItemCommand::QGDeleteVectItemCommand(QGVectorialLayer * layer,
						 QGraphicsItem * item) 
{
  _layer = layer;
  _itemToDelete = item;

  _layer->lock(_itemToDelete);
}

// ---------------------------------------------------------------------

// Copy-constructor
QGDeleteVectItemCommand::QGDeleteVectItemCommand(const QGDeleteVectItemCommand& rhs)
{
  _layer = rhs._layer;
  _itemToDelete = rhs._itemToDelete;
  
  _layer->lock(_itemToDelete);
}


// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

// Default constructor
QGDeleteVectItemCommand::~QGDeleteVectItemCommand() 
{
  _layer->unlock(_itemToDelete);
}


// -------------------------------------------------------------------
// U N D O A B L E   C O M M A N D   I M P L 
// -------------------------------------------------------------------

void
QGDeleteVectItemCommand::execute()
{  
  _layer->removeVectItem(_itemToDelete);
  _layer->update(_itemToDelete->boundingRect().toRect());
}

// ---------------------------------------------------------------------

void
QGDeleteVectItemCommand::undo()
{
  _layer->insertVectItem(_itemToDelete);
  _layer->update(_itemToDelete->boundingRect().toRect());
}

// ---------------------------------------------------------------------

QGDeleteVectItemCommand *
QGDeleteVectItemCommand::clone() const
{
  return new QGDeleteVectItemCommand(*this);
}


// ---------------------------------------------------------------------
// O P E R A T O R S
// ----------------------------------------------------------------------

// Assignment operator
QGDeleteVectItemCommand& 
QGDeleteVectItemCommand::operator=(const QGDeleteVectItemCommand& rhs) 
{
  if ( this != &rhs ) {
    
    QGUndoableCommandIf::operator=(rhs);
    
    _layer = rhs._layer;
    _itemToDelete = rhs._itemToDelete;
    
    _layer->lock(_itemToDelete);
  }

  return *this;
}

// ----------------------------------------------------------------------

