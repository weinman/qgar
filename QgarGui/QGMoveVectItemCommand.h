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


#ifndef __QGMOVEVECTITEMCOMMAND_H_INCLUDED__
#define __QGMOVEVECTITEMCOMMAND_H_INCLUDED__


/**
 * @file     QGMoveVectItemCommand.h
 * @brief    Header file of class QGMoveVectItemCommand
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     November 28, 2002  16:17
 * @since    Qgar 2.1
 */


/* $Id: QGMoveVectItemCommand.h,v 1.6 2005/07/13 16:30:28 masini Exp $ */



// QGUI
#include "QGUndoableCommandIf.h"
class QGVectorialLayer;
// QT
class QGraphicsItem;
class QPoint;



/**
 * @class QGMoveVectItemCommand QGMoveVectItemCommand.h "QGMoveVectItemCommand.h"
 * @brief Revesible command translating an item from a vectorial
 * layer.
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 28, 2002  16:17
 * @since  Qgar 2.1
 */
class QGMoveVectItemCommand

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
 * @brief Creates a translation command from a layer, an item and the
 * translation vector coordinates.
 *
 * @param layer A pointer to the layer this command works on.
 * @param item  A pointer to the vectorial item to be translated.
 * @param dx    The translation vector x coordinate.
 * @param dy    The translation vector y coordinate.
 */
  QGMoveVectItemCommand(QGVectorialLayer * layer,
			QGraphicsItem * item, 
			int dx, 
			int dy);


/**
 * @brief Creates a translation command from a layer, an item and a
 * translation vector.
 *
 * @param layer A pointer to the layer this command works on.
 * @param item  A pointer to the vectorial item to be translated.
 * @param pt    The translation vector coordinates.
 */
  QGMoveVectItemCommand(QGVectorialLayer * layer, 
			QGraphicsItem * item, 
			const QPoint& pt);


/**
 * @brief Copy-constructor.
 *
 * @param other Another instance to build a command from.
 */
  QGMoveVectItemCommand(const QGMoveVectItemCommand& other);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGMoveVectItemCommand();
//@}



/** @name QGUndoableCommandIf Impl */
//        ========================
//@{

  virtual void execute();
  
  virtual void undo();
  
  QGUndoableCommandIf * clone() const;

//@}



/** @name Operators */
//        =========
//@{

/**
 * @brief Assignment operator
 */
  QGMoveVectItemCommand& operator=(const QGMoveVectItemCommand&);

//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// The layer this command operates on.
  QGVectorialLayer * _layer;

  /// A pointer on the item to translate.
  QGraphicsItem * _item;

  /// Translation vector x-coordinate.
  int _dx;

  /// Translation vector y-coordinate.
  int _dy;


// -------------------------------------------------------------------
}; // class QGMoveVectItemCommand


#endif /* __QGMOVEVECTITEMCOMMAND_H_INCLUDED__ */
