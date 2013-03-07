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


#ifndef __QGSWITCHVECTITEMCOMMAND_H_INCLUDED__
#define __QGSWITCHVECTITEMCOMMAND_H_INCLUDED__


/**
 * @file     QGSwitchVectItemCommand.h
 * @brief    Header file of class QGSwitchVectItemCommand
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     November 28, 2002  09:48
 * @since    Qgar 2.1
 */


/* $Id: QGSwitchVectItemCommand.h,v 1.4 2005/07/13 16:30:29 masini Exp $ */



// QGUI
#include "QGUndoableCommandIf.h"
class QGDeleteVectItemCommand;
class QGInsertVectItemCommand;
class QGVectorialLayer;
// QT
class QGraphicsItem;



/**
 * @class QGSwitchVectItemCommand QGSwitchVectItemCommand.h "QGSwitchVectItemCommand.h"
 * @brief Reversible command replacing, in a vectorial layer,  an item
 * by another.
 * 
 * This command is the composition of two other:
 * - a delete command, instance of QGDeleteVectItemCommand
 * - an insert command, instance of QGInsertVectItemCommand.
 * .
 * Replacing an item by another mainly consists in deleting the first
 * and inserting the second. Since both command are reversible, this
 * one is also.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 28, 2002  09:48
 * @since  Qgar 2.1
 */
class QGSwitchVectItemCommand

  : public QGUndoableCommandIf

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name Constructor */
//        ===========
//@{

/**
 * @brief Default constructor
 *
 * @param layer   The layer in which the replacement takes place.
 * @param oldItem The item to be replaced.
 * @param newItem The item to be put in place.
 */
  QGSwitchVectItemCommand(QGVectorialLayer *  layer, 
			  QGraphicsItem * oldItem,
			  QGraphicsItem * newItem);


/**
 * @brief Copy-constructor
 */
  QGSwitchVectItemCommand(const QGSwitchVectItemCommand&);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGSwitchVectItemCommand();

//@}


/** @name QGUndoableCommandif Impl */
//        ========================
//@{

  /// Replaces the old vectorial item by the new one.
  virtual void execute();

  /// Restores the old vectorial item in place of the new one.
  virtual void undo();

  QGUndoableCommandIf * clone() const;

//@}


/** @name Operators */
//        =========
//@{

/**
 * @brief Assignment operator
 */
  QGSwitchVectItemCommand& operator=(const QGSwitchVectItemCommand&);

//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// Command deleting the existing vectorial item.
  QGDeleteVectItemCommand * _deleteOldCmd;

  /// Command inserting the new vectorial item.
  QGInsertVectItemCommand * _insertNewCmd;


// -------------------------------------------------------------------
}; // class QGSwitchVectItemCommand


#endif /* __QGSWITCHVECTITEMCOMMAND_H_INCLUDED__ */
