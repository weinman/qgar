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
 * @file  QGMoveVectItemCommand.cpp
 * @brief Implementation of class QGMoveVectItemCommand.
 *
 * See file QGMoveVectItemCommand.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 28, 2002  16:17
 * @since  Qgar 2.1
 */



// QGUI
#include "QGMoveVectItemCommand.h"
#include "QGVectorialLayer.h"
// QT
#include <QGraphicsItem>



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGMoveVectItemCommand::QGMoveVectItemCommand(QGVectorialLayer * layer,
					     QGraphicsItem* item,
					     int dx, int dy)
{
  _layer = layer;
  _item  = item;
  _dx = dx;
  _dy = dy;
   
}

// ---------------------------------------------------------------------

// Default constructor
QGMoveVectItemCommand::QGMoveVectItemCommand(QGVectorialLayer * layer,
					     QGraphicsItem* item,
					     const QPoint& pt)
{
  _layer = layer;
  _item  = item;
  _dx = pt.x();
  _dy = pt.y();

  _layer->lock(_item);
}

// ---------------------------------------------------------------------

// Copy-constructor
QGMoveVectItemCommand::QGMoveVectItemCommand(const QGMoveVectItemCommand& rhs) 
{
  _layer = rhs._layer;
  _item  = rhs._item;
  _dx = rhs._dx;
  _dy = rhs._dy;

  _layer->lock(_item);  
}

// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

// Default constructor
QGMoveVectItemCommand::~QGMoveVectItemCommand() 
{ 
  _layer->unlock(_item);
}



// -------------------------------------------------------------------
// Q G U N D O A B L E C O M M A N D I F     I M P L 
// -------------------------------------------------------------------

void
QGMoveVectItemCommand::execute()
{
  QRect oldPos = _item->boundingRect().toRect();

  _item->moveBy(_dx, _dy);

  _layer->update(oldPos);
  _layer->update(_item->boundingRect().toRect());
}

// ---------------------------------------------------------------------

void
QGMoveVectItemCommand::undo()
{
  QRect oldPos = _item->boundingRect().toRect();

  _item->moveBy(-_dx, -_dy);

  _layer->update(oldPos);
  _layer->update(_item->boundingRect().toRect());
}

// ---------------------------------------------------------------------

QGUndoableCommandIf * 
QGMoveVectItemCommand::clone() const
{
  return new QGMoveVectItemCommand(*this);
}

// ---------------------------------------------------------------------
// O P E R A T O R S
// ----------------------------------------------------------------------

// Assignment operator
QGMoveVectItemCommand& 
QGMoveVectItemCommand::operator=(const QGMoveVectItemCommand& rhs)
{
  if ( this != &rhs ) {
    
    QGUndoableCommandIf::operator=(rhs);
    
    _layer = rhs._layer;
    _item  = rhs._item;
    _dx = rhs._dx;
    _dy = rhs._dy;
  }

  return *this;
}

// ----------------------------------------------------------------------

