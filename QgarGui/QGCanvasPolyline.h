/*---------------------------------------------------------------------+
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


#ifndef __QGCANVASPOLYLINE_H_INCLUDED__
#define __QGCANVASPOLYLINE_H_INCLUDED__


/**
 * @file  QGCanvasPolyline.h
 * @brief Header file of class QGCanvasPolyline.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date  December, 12  2000  10:27
 * @since Qgar 2.0
 */


/* $Id: QGCanvasPolyline.h,v 1.7 2005/07/13 16:30:27 masini Exp $ */



// QT
#include <QGraphicsScene>
#include <QAbstractGraphicsShapeItem>

// QGUI
#include "QGVectItem.h"
// QGAR
namespace qgar
{
  template <class T> class GenQgarPolyline;
}



/** 
 * @brief Class QGCanvasPolyline: A polyline on a canvas.
 *
 * @todo
 * - Check the QGCanvasPolyline::boundingRect implementation
 * - Check the QGCanvasPolyline::areaPoints implementation
 * - Refactor QGCanvasPolyline::coordsSelectionRectangle computation
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date  December, 12  2000  10:27
 * @since Qgar 2.0
 */
class QGCanvasPolyline

  : public QAbstractGraphicsShapeItem, 
    public QGVectItem 

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  static const int RTTI_POLYLINE;

/** @name Constructors */
//        ============
//@{

/**
 * @brief Constructor.
 *
 * @param canvas The canvas this polyline will be attached to.
 */
  QGCanvasPolyline(QGraphicsScene * canvas);

/**
 * @brief Converts a GenQgarPolyline<int>.
 *
 * @param polyline The GenQgarPolyline to convert.
 */
  QGCanvasPolyline(const qgar::GenQgarPolyline<int>& polyline);
  
/**
 * @brief Copy constructor.
 *
 * @param obj Object that wil be copied.
 */
  QGCanvasPolyline(const QGCanvasPolyline & obj);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Virtual destructor.
 */
  virtual ~QGCanvasPolyline();

//@}


  /// Set the points of the polyline.
  void setPoints(QPolygon thePoints);

  /// Get the start point of the polyline.
  QPoint startPoint() const {return _thePoints.point(0);}

  /// Get the end point of the polyline.
  QPoint endPoint() const {return _thePoints.point(_thePoints.size() - 1);}

  /// return the points of the polyline.
  QPolygon getPoints() {return _thePoints;}

  //make problemes (the walue mustn't be good)

//   ///reimplemented because didn't worked fine
//   double x() const;
  
//   ///reimplemented because didn't worked fine
//   double y() const ;
  
//   ///reimplemented because didn't worked fine
//   double z() const ;

 
 /// Returns the type of the primitive (1000).
  int rtti() const {return RTTI_POLYLINE;}

  /// Set a pen used when drawing the item.
  void setPen(QPen p);

  /// Turn the line into skeleton mode.
  virtual void skelMode();

  /// Turn the line into normal mode.
  virtual void normalMode();

  /// Set the width of the polyline.
  virtual void setWidth(int width);

  virtual int width() const {return _realWidth;}

  virtual int originalWidth() const {return _originalWidth;}

  ///return the QRect fitting the polyline
  virtual QRect coordsSelectionRectangle();

  ///resize the line by performing an homothetie of rate k from the initial position.
  virtual void resize(double k);

  ///
  virtual void resize(double kx, double ky);

  /// Moves the polyline by (dx, dy).
  void moveBy(double dx, double dy);

  QGVectItem * clone();

// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  uint _realWidth;
  int _originalWidth;

  //for resizing
  QPoint _center;
  QPolygon* _initialPoints;
  bool _isResizing;

  QPolygon _thePoints;

  /// Pen used to hold line properties
  QPen _pen;

  /// Draw the shape of the polyline.
  void paint(QPainter*, const QStyleOptionGraphicsItem *, QWidget *);

  /// Implements the boudingRect() function
  QRectF boundingRect() const;

  /// Return the points bounding the shape.
  QPolygon areaPoints() const;

  /// Return the points bounding a part of the shape.
  QPolygon areaPoints(int x1, int x2, int y1, int y2) const;

// -------------------------------------------------------------------
}; // Class QGCanvasPolyline


#endif /* __QGCANVASPOLYLINE_H_INCLUDED__ */
