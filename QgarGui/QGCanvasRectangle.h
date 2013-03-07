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


#ifndef __QGCANVASRECTANGLE_H_INCLUDED__
#define __QGCANVASRECTANGLE_H_INCLUDED__


/**
 * @file  QGCanvasRectangle.h
 * @brief Header file of class QGCanvasRectangle.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date  December, 12  2000  10:27
 * @since Qgar 2.0
 */


/* $Id: QGCanvasRectangle.h,v 1.7 2005/07/13 16:30:27 masini Exp $ */


// STD
#include <math.h>
// QGUI
#include "QGVectItem.h"
// QGAR
namespace qgar
{
  class BoundingBox;
}
// QT
#include <QGraphicsScene>
#include <QGraphicsRectItem>


/** 
 * Class QGCanvasRectangle: A rectangle on a canvas.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date  December, 12  2000  10:27
 * @since Qgar 2.0
 */
class QGCanvasRectangle

  : public QGraphicsRectItem, 
    public QGVectItem

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  static const int RTTI_RECTANGLE;


/** @name Constructors */
//        ============
//@{

/**
 * @brief Contructor
 */
  explicit QGCanvasRectangle(QGraphicsScene* canvas);


/**  
 * @brief Creates a QGraphicsRectItem by specifying the rectangle
 * coordinates.
 *
 * @param x The x coordinate of the top left corner of the rectangle
 * @param y The y coordinate of the top left corner of the rectangle
 * @param width  The width of the rectangle.
 * @param height The height of the rectangle.
 * @param canvas The canvas this rectangle will be attached to.
 */
  QGCanvasRectangle(QGraphicsScene* canvas, int x, int y, 
		    int width, int height);


/**
 * @brief Creates a QGraphicsRectItem instance from a QRect.
 *
 * @param rect   The coordinates of the rectangle to create.
 * @param canvas The canvas this rectangle will be attached to.
 */
  QGCanvasRectangle(QGraphicsScene* canvas, QRect rect);

/**
 * @brief Creates a QGraphicsRectItem instance from two points.
 *
 * @param p1     The top left point of the rectangle.
 * @param p2     The bottom left point of the rectangle.
 * @param canvas The canvas this rectangle will be attached to.
 */
  QGCanvasRectangle(QGraphicsScene* canvas, QPoint p1, QPoint p2);

/**
 * @brief Converts a Bounding box instance.
 *
 * @param boundingBox The boundingBox to convert.
 */
  QGCanvasRectangle(const qgar::BoundingBox& boundingBox);

/**
 * @brief Copy constructor.
 *
 * @param obj QGCanvasRectangle object that will be copied.
 */
  QGCanvasRectangle(const QGCanvasRectangle & obj);

//@}


/** @name Destructor */
//        ==========
//@{

  /// Destructor.
  virtual ~QGCanvasRectangle(); 

//@}


  /// Set a pen used when drawing the item.
  void setPen(QPen p);



/** @name VectItem Impl */
//        =============
//@{

  /// Returns the type of the primitive (1003).
  int rtti() const {return RTTI_RECTANGLE;}

  /// Return the width of the rectangle.
  virtual int width() const { return _realWidth;};

  /// Return the original width of the rectangle.
  virtual int originalWidth() const { return _originalWidth;};


  /// Turn the line into skeleton mode.
  virtual void skelMode();

  /// Turn the line into normal mode.
  virtual void normalMode();

  /// Set the width of the rectangle.
  virtual void setWidth(int width);


  /// Return the QRect fitting the rectangle.
  virtual QRect coordsSelectionRectangle();

  /// Perform an homothetie
  virtual void resize(double k) {}

  virtual void resize(double kx, double ky);

  /// Perform an homothetie of enter Po and rate k.
  void resize(QPoint Po, double k);

  /// Perform an homothetie of enter Po and rate k only in the X direction.
  void resizeX(QPoint Po, double k); 
  
  /// Perform an homothetie of enter Po and rate k only in the Y direction.
  void resizeY(QPoint Po, double k); 

  /// Give the minimum value of x compared to y.
  int min (int x, int y);

  virtual QGVectItem * clone();

//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------

protected:
  uint _realWidth;

  uint _originalWidth;

  //QPointArray _thePoints;

// -------------------------------------------------------------------
}; // class QGCanvasrectangle


#endif /* __QGCANVASRECTANGLE_H_INCLUDED__ */
