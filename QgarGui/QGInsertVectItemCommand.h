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


#ifndef __QGINSERTVECTITEMCOMMAND_H_INCLUDED__
#define __QGINSERTVECTITEMCOMMAND_H_INCLUDED__


/**
 * @file     QGInsertVectItemCommand.h
 * @brief    Header file of class QGInsertVectItemCommand
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     November 4, 2002  18:11
 * @since Qgar 2.1
 */


/* $Id: QGInsertVectItemCommand.h,v 1.7 2005/07/13 16:30:28 masini Exp $ */



// QGUI
#include "QGUndoableCommandIf.h"
class QGVectorialLayer;
class QGraphicsItem;



/**
 * @class QGInsertVectItemCommand QGInsertVectItemCommand.h "QGInsertVectItemCommand.h"
 * @brief Inserts a QCanvas item in a QGVectorialLayer.
 * 
 * This reversible command inserts a item in a vectorial layer. On
 * destruction, the item is deleted if the command was not executed or
 * undone (ie. the item is not part of the layer).
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 4, 2002  18:11
 * @since  Qgar 2.1
 */
class QGInsertVectItemCommand

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
 * @param layer The layer to insert the item in.
 * @param item  The vector item to insert in the layer.
 */
  QGInsertVectItemCommand(QGVectorialLayer * layer, 
			  QGraphicsItem * item);

/**
 * @brief Copy-constructor
 */
  QGInsertVectItemCommand(const QGInsertVectItemCommand&);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGInsertVectItemCommand();

//@}


/** @name QGUndoableCommandIf Impl */
//        ========================
//@{

  virtual void execute();
  
  virtual void undo();

  virtual QGUndoableCommandIf * clone() const;

//@}


/** @name Operators */
//        =========
//@{

/**
 * @brief Assignment operator
 */
  QGInsertVectItemCommand& operator=(const QGInsertVectItemCommand&);

//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:
  
  /// The layer in which to insert the vector item
  QGVectorialLayer * _layer;

  /// A pointer to the inserted item
  QGraphicsItem  * _item;


// -------------------------------------------------------------------
}; // class QGInsertVectItemCommand


#endif /* __QGINSERTVECTITEMCOMMAND_H_INCLUDED__ */
