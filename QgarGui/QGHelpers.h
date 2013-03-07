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


#ifndef __QGHELPERS_H_INCLUDED__
#define __QGHELPERS_H_INCLUDED__


/**
 * @file     QGHelpers.h
 * @brief    Header file of class QGHelpers.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     November 28, 2002  10:31
 * @since    Qgar 2.1
 */


/* $Id: QGHelpers.h,v 1.5 2005/07/13 16:30:27 masini Exp $ */



// QGUI
class QGraphicsItem;

// QT
#include <QVector>
#include <QPoint>
#include <QRect>


/**
 * @class QGHelpers QGHelpers.h "QGHelpers.h"
 * @brief Class regrouping all global functions of the GUI.
 *
 * This class cannot be instanciated. It is only a collection of static
 * methods.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 28, 2002  10:31
 * @since  Qgar 2.1
 */
class QGHelpers
{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/**
 * @brief Creates a deep copy of a QGraphicsItem instance.
 *
 * If the instance to be copied implements QGVectItem, the copy will be
 * performed using QGVectItem::cloneAsCanvasItem().
 *
 * @param item The item to be copied.
 *
 * @return A deep copy of item.
 *
 * @see QGVectItem
 */
  static QGraphicsItem * duplicateItem(QGraphicsItem * item);

/**
 * @brief Computes the bounding rectangle of a set of points.
 *
 * @param ptVect The set of points.
 *
 * @return The bounding rectangle.
 */
  static QRect computeBoundingRect(const QVector<QPoint>& ptVect);



// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

/** @name DISABLED */
//        ========
//@{

/**
 * @brief Default constructor
 *
 * This class is only a storage place for static function members, used as
 * global function in QgarGui. Creating an instance has no sense.
 */
  QGHelpers();

//@}


/**
 * @brief Compares two points and returns the top-left-most point.
 *
 * This method is used by computeBoundingRect() to compute the top left corner
 * of the bounding box of a set of points.
 *
 * @param a The first point to be compared.
 * @param b The second point to be compared
 *
 * @return The top-left-most point.
 */
  static QPoint computeTopLeft(const QPoint& a, const QPoint& b);


/**
 * @brief Compares two points and returns the bottom-right-most point.
 *
 * This method is used by computeBoundingRect() to compute the bottom right
 * corner of the bounding box of a set of points.
 *
 * @param a The first point to be compared.
 * @param b The second point to be compared
 *
 * @return The Bottom-Right-most point.
 */
  static QPoint computeBottomRight(const QPoint& a, const QPoint& b);

// -------------------------------------------------------------------
}; // class QGHelpers


#endif /* __QGHELPERS_H_INCLUDED__ */
