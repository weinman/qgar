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


#ifndef __QGDELETEVECTITEMCOMMAND_H_INCLUDED__
#define __QGDELETEVECTITEMCOMMAND_H_INCLUDED__


/**
 * @file     QGDeleteVectItemCommand.h
 * @brief    Header file of class QGDeleteVectItemCommand
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     November 28, 2002  10:46
 * @since    Qgar 2.1
 */


/* $Id: QGDeleteVectItemCommand.h,v 1.7 2005/07/13 16:30:27 masini Exp $ */



// QGUI
#include "QGUndoableCommandIf.h"
class QGVectorialLayer;
class QGraphicsItem;



/**
 * @class QGDeleteVectItemCommand QGDeleteVectItemCommand.h "QGDeleteVectItemCommand.h"
 * @brief Deletes a QGraphicsItem from a QGVectorialLayer.
 *
 * This class defines the command deleting a vectorial item from a
 * vectorial layer.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 28, 2002  10:46
 * @since Qgar 2.1
 */
class QGDeleteVectItemCommand

  : public QGUndoableCommandIf

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name Constructors */
//        ============
//@{

/**
 * @brief Default constructor
 *
 * @param layer The layer from which to remove the given item when
 * executing the command.
 *
 * @param layer The layer to delete the item from.
 * @param item  The item to delete.
 */
  QGDeleteVectItemCommand(QGVectorialLayer * layer, QGraphicsItem * item);


/**
 * @brief Copy-constructor
 */
  QGDeleteVectItemCommand(const QGDeleteVectItemCommand&);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGDeleteVectItemCommand();

//@}



/** @name QGUndoableCommandIf impl */
//        ========================
//@{

/**
 * @brief Performs the item deletion.
 */
  virtual void execute();

/**
 * @brief Restores the deleted item.
 */
  virtual void undo();

/**
 * @brief Duplicate the command instance.
 *
 * @return a deep copy of the command.
 */
  QGDeleteVectItemCommand * clone() const;

//@}



/** @name Operators */
//        =========
//@{

/**
 * @brief Assignment operator
 */
  QGDeleteVectItemCommand& operator=(const QGDeleteVectItemCommand&);

//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// The layer to remove the item from.
  QGVectorialLayer * _layer;

  /// A pointer to the item to delete.
  QGraphicsItem * _itemToDelete;

// -------------------------------------------------------------------

}; // class QGDeleteVectItemCommand


#endif /* __QGDELETEVECTITEMCOMMAND_H_INCLUDED__ */
