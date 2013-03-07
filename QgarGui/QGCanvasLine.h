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


#ifndef __QGCANVASLINE_H_INCLUDED__
#define __QGCANVASLINE_H_INCLUDED__


/**
 * @file     QGCanvasLine.h
 * @brief    Header file of class QGCanvasLine.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date  2001
 * @since Qgar 2.0
 */



// QT
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QPolygon>
// QGUI
#include "QGVectItem.h"
// QGAR
namespace qgar
{
  template <class T> class GenQgarSegment;
}



/**
 * @class QGCanvasLine QGCanvasLine.h
 * @brief A line on a canvas, customized for Qgar.
 *
 * @warning No assignement constructor is provided nor destructor.
 * The clone() method simply calls the copy constructor that simply
 * call default QGraphicsEllipse and puts the new object in the scene.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date  2001
 * @since Qgar 2.0
 */
class QGCanvasLine

  : public QGraphicsLineItem, public QGVectItem

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  static const int RTTI_LINE;
  
/**
 * @brief Constructor.
 *
 * @param canvas The canvas this item will be attached to.
 * @param width  The thickness of this item.
 */
  QGCanvasLine(QGraphicsScene * canvas, int width = 0);


/**
 * @brief Converts a GenQgarSegment<int>
 *
 * @param seg The segment to be converted.
 */
  QGCanvasLine(const qgar::GenQgarSegment<int>& seg);

/**
 * @brief Copy constructor.
 *
 * @param obj Object to be copied.
 */
  QGCanvasLine(const QGCanvasLine & obj);

  /// Return the type of the primitive (1001).
  int rtti() const {return RTTI_LINE;}


  /// Turn the line into skeleton mode.
  virtual void skelMode();

  /// Turn the line into normal mode.
  virtual void normalMode();

  ///give the width
  virtual int width() const {return _realWidth;};

  ///give the width
  virtual int originalWidth() const {return _originalWidth;};

  ///set the width
  virtual void setWidth(int w);

 ///give a QPolygon with the startpoint and the EndPoint in this order (pour homogénéiser avec la QGCanvasPolyline)
  QPolygon getPoints();

  /// Moves the polyline by (dx, dy).
  void moveBy(double dx, double dy);

  ///resize the line by performing an homothetie of rate k from the initial position.
  virtual void resize(double k);

  /**
   * @brief Resizes the item both horizontally and vertically.
   *
   * @param kx
   * @param ky
   */
  virtual void resize(double kx, double ky);
  
  ///created the selection rectangle associated to the QGCanvasLine
  virtual QRect coordsSelectionRectangle();

  ///give data about the line
  double length();
  double tanT();
  double cosT();
  double sinT();
  bool isVertical();
  bool isHorizontal();

  virtual QGVectItem * clone();

// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /**
   * @brief Overloaded drawing method.
   * Draws a visible bounding box when the item is selected.
   */
  virtual void paint(QPainter& p, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

  uint _realWidth;
  uint _originalWidth;

  //for resizing
  QPoint _center;
  QPolygon* _initialPoints;
  bool _isResizing;

// -------------------------------------------------------------------
}; // class QGCanvasLine


#endif /* __QGCANVASLINE_H_INCLUDED__ */
