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


#ifndef __QGVECTITEM_H_INCLUDED__
#define __QGVECTITEM_H_INCLUDED__


/**
 * @file     QGVectItem.h
 * @brief    Header file of class QGVectItem
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     November 15, 2002  10:35
 * @since    Qgar 2.1
 */


/* $Id: QGVectItem.h,v 1.4 2005/07/13 16:30:29 masini Exp $ */



// STL
#include <vector>
// QT
#include <QRect>
class QPainter;
class QGraphicsItem;
class QGraphicsItem;



/**
 * @class QGVectItem QGVectItem.h "QGVectItem.h"
 * @brief Abstract base class of all Qgar vectorial items.
 *
 * <p>
 * This class provide a common root to all vectorial items in the
 * application other than QGraphicsItem.
 * </p>
 * <p>
 * It declares a set of features that all child classes must
 * implement. These features are:
 * - Managing the width (thickness) of the item.
 * - Manage the skeleton/normal view of the item.
 * - Handle the resizing of the item.
 * - Compute the bounding box of the item.
 * - A clone function member.
 * .
 * </p>
 * <p>
 * This class offers also two features:
 * - The clone() function member. This function member usefully to
 *   duplicate a subclasse instance whose dynamic type is
 *   unknown. This avoids to use the awkward Qt way using rtti().
 * - A common function member to draw a selection box around a
 *   selected item: the drawSelectionRectangle() function member.
 * </p>
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 15, 2002  10:35
 * @since  Qgar 2.1
 */
class QGVectItem
{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/**
 * @brief The width of the resize rectangle drawn around the selection
 * rectangle
 */

  static const int RESIZE_BOX_WIDTH;


  // -------------------------------------------------------------
  // USING DEFAULT CONSTRUCTOR, COPY-CONSTRUCTOR AND ASSIGNMENT OP
  // -------------------------------------------------------------


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGVectItem() {}
//@}

/**
 * @brief Orders the item to provide a skeleton view of itself on
 * repaint.
 */
  virtual void skelMode()   = 0;

/**
 * @brief Orders the item to provide a normal view of itself on
 * repaint.
 */
  virtual void normalMode() = 0;

/**
 * @brief Retrieves the width (thickness) of the item.
 *
 * @return The thickness of the item.
 */
  virtual int width() const = 0;

/**
 * @brief Retrieves the width (thickness) of the item.
 *
 * @return The thickness of the item.
 */
  virtual int originalWidth() const = 0;

/**
 * @brief Sets the thickness of the item.
 *
 * @param width The new thickness for the item.
 */
  virtual void setWidth(int width)   = 0;


/**
 * @brief Resizes the item, perfoming an homothetie of rate k from the
 * initial position.
 *
 * @param k The rate of the homothetie to be performed.
 */
  virtual void resize(double k) = 0;

/**
 * @brief Resizes the item both vertically and horizontally.
 *
 * @param kx
 * @param ky
 */
  virtual void resize(double kx, double ky) = 0;

/**
 * @brief Duplicates the item.
 *
 * @return a copy of the item.
 */
  virtual QGVectItem  * clone() = 0;

/**
 * @brief Retrieve the selection rectangle of the item.
 */
  virtual QRect coordsSelectionRectangle() = 0;

/**
 * @brief Draws the rectangle highlighting the item when it is
 * selected.
 */
  virtual void drawSelectionRectangle(QPainter& p);
  
  std::vector<QRect> computeResizeRects();

/**
 * @brief Creates a copy of the item and return it as a QGraphicsItem.
 *
 * @return A clone of the item with QGraphicsItem as static type.
 */
  QGraphicsItem * cloneAsGraphicsItem();

// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

/**
 * @brief Computes the coordinates of the corners and the middle of
 * the edges of the selection rectangle.
 *
 * @return The computed points with the following order in the vector:
 * top left, top center, top right, center right , bottom right,
 * bottom center, bottom left, center left.
 */ 
  std::vector<QPoint> computeCoords();

// -------------------------------------------------------------------
}; // class QGVectItem


#endif /* __QGVECTITEM_H_INCLUDED__ */
