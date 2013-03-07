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
 * @file  QGInsertVectItemCommand.cpp
 * @brief Implementation of class QGInsertVectItemCommand.
 *
 * See file QGInsertVectItemCommand.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 4, 2002  18:11
 * @since  Qgar 2.1
 */



// QGUI
#include "QGInsertVectItemCommand.h"
#include "QGCanvasEllipse.h"
#include "QGCanvasLine.h"
#include "QGCanvasPolyline.h"
#include "QGCanvasRectangle.h"
#include "QGHelpers.h"
#include "QGMainWindow.h"
#include "QGVectorialLayer.h"
// QT
#include <QGraphicsItem>


// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGInsertVectItemCommand::QGInsertVectItemCommand(QGVectorialLayer * layer, 
						 QGraphicsItem * item)

{
  //-- Assign members.

  _layer = layer;
  _item  = item;

  _layer->lock(_item);
}

// ---------------------------------------------------------------------

// Copy-constructor
QGInsertVectItemCommand::QGInsertVectItemCommand(const QGInsertVectItemCommand& rhs)
  : QGUndoableCommandIf(rhs)
{
  _layer = rhs._layer;
  _item  = rhs._item;

  _layer->lock(_item);
}

// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

// Default constructor
QGInsertVectItemCommand::~QGInsertVectItemCommand() 
{
  // Automatically deletes the item, if it is not inserted in the
  // layer.
  _layer->unlock(_item);
}

// -------------------------------------------------------------------
// Q G U N D O A B L E C O M M A N D I F     I M P L 
// -------------------------------------------------------------------

void
QGInsertVectItemCommand::execute()
{
  // Insert item in the layer.
  _layer->insertVectItem(_item);

  // Notity layer listeners that the layer has been modified.
  _layer->update( _item->boundingRect().toRect() );
}

// ---------------------------------------------------------------------

void
QGInsertVectItemCommand::undo()
{
  // Remove item
  _layer->removeVectItem(_item);

  // Notity layer listeners that the layer has been modified.
  _layer->update( _item->boundingRect().toRect() );
}

// ---------------------------------------------------------------------

QGUndoableCommandIf *
QGInsertVectItemCommand::clone() const
{
  return new QGInsertVectItemCommand(*this);
}


// ---------------------------------------------------------------------
// O P E R A T O R S
// ----------------------------------------------------------------------

// Assignment operator
QGInsertVectItemCommand& 
QGInsertVectItemCommand::operator=(const QGInsertVectItemCommand& rhs) 
{
  if (this != &rhs) {

    QGUndoableCommandIf::operator=(rhs);
    
    _layer = rhs._layer;
    _item  = rhs._item;
  }
  return *this;
}

// ----------------------------------------------------------------------

