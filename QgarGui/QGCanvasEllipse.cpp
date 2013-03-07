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


/**
 * @file  QGCanvasEllipse.cpp
 * @brief Implementation of class QGCanvasEllipse.
 *
 * See file QGCanvasEllipse.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   2001
 * @since  Qgar 2.0
 */



// QGUI
#include "QGCanvasEllipse.h"
// QGAR
#include <qgarlib/primitives.h>
// QT
#include <QPainter>


using namespace qgar;



// -------------------------------------------------------------------
// S T A T I C   M E M B E R   I N I T 
// -------------------------------------------------------------------

const int QGCanvasEllipse::RTTI_ELLIPSE = 1002;


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


QGCanvasEllipse::QGCanvasEllipse(QGraphicsScene * canvas, int width)
  : QGraphicsEllipseItem(),
    _realWidth(width),
    _originalWidth(width)
{
  QPen p = pen();
  p.setWidth(width);
  setPen(p);         

  QBrush b("red");
  setBrush(b);

  _realWidth = width; 
  _isResizing = false;

}

// -------------------------------------------------------------------


// Warning: qt'degrees are expressed in 16th of degree

QGCanvasEllipse::QGCanvasEllipse(int ptx, int pty, int width, int height, int startangle,
				 int angle, QGraphicsScene * canvas, int widthArc)
  : QGraphicsEllipseItem(ptx, pty, width, height),
    _realWidth(widthArc),
    _originalWidth(widthArc)

{
  // Set the angles
  setStartAngle(startangle % 5760);
  setSpanAngle(((angle % 5760) == 0)? 5760 : (angle % 5760) - (startangle % 5760));

  QPen p = pen();
  p.setWidth(widthArc);
  setPen(p);

  _realWidth = widthArc; 
  _isResizing = false;

}

// -------------------------------------------------------------------

QGCanvasEllipse::QGCanvasEllipse(const GenQgarArc<int>& arc)
    : QGraphicsEllipseItem(0.0, 0.0, (arc.radius() * 2),
			   (arc.radius() * 2), 0),
    _realWidth(0),
    _originalWidth(-1)
{
  Point c(arc.center());
  moveBy(c.x() + arc.radius(), c.y() + arc.radius() );
}

// -------------------------------------------------------------------

QGCanvasEllipse::QGCanvasEllipse(const QGCanvasEllipse & obj)
  : QGraphicsEllipseItem(),
    _realWidth(obj.width()),
    _originalWidth(obj.width())

{
  obj.scene()->addItem(this);
}

// -------------------------------------------------------------------
// P U B L I C   M E M B E R S
// -------------------------------------------------------------------

void
QGCanvasEllipse::skelMode()
{
  QPen p = pen();

  p.setWidth(1);
  setPen(p);
}

// -------------------------------------------------------------------


void
QGCanvasEllipse::normalMode()
{
  QPen p = pen();

  p.setWidth(_realWidth);
  setPen(p);
}

// -------------------------------------------------------------------

void
QGCanvasEllipse::setWidth(int width)
{
  QPen p = pen();
  p.setWidth(width);
  setPen(p);

  if(_originalWidth < 0)
    _originalWidth = width;
  _realWidth = width;
}

// ---------------------------------------------------------------------

void
QGCanvasEllipse::setPen(QPen p)
{ 
  QAbstractGraphicsShapeItem::setPen(p);
}

// ---------------------------------------------------------------------

void
QGCanvasEllipse::resize(double k)
{
//   //calculate the new enclosingRect. 
//   QPoint newTopLeft,newBottomRight;

//   switch (_type) {
//   case QGSelMovResInteractor::XY:
//     newTopLeft = QPoint((int)(_center.x() + k * (_initialRect.topLeft().x() - _center.x())),
// 			(int)(_center.y() + k * (_initialRect.topLeft().y() - _center.y())));
//     newBottomRight = QPoint((int)(_center.x() + k * (_initialRect.bottomRight().x() - _center.x())),
// 			    (int)(_center.y() + k * (_initialRect.bottomRight().y() - _center.y())));
//     break;

//   case QGSelMovResInteractor::X:
//     newTopLeft = QPoint((int)(_center.x() + k * (_initialRect.topLeft().x() - _center.x())),
// 			_initialRect.topLeft().y());
//     newBottomRight = QPoint((int)(_center.x() + k * (_initialRect.bottomRight().x() - _center.x())),
// 			    _initialRect.bottomRight().y());
//     break;

//   case QGSelMovResInteractor::Y:
//     newTopLeft = QPoint(_initialRect.topLeft().x(),
// 			(int)(_center.y() + k * (_initialRect.topLeft().y() - _center.y())));
//     newBottomRight = QPoint(_initialRect.bottomRight().x(),
// 			    (int)(_center.y() + k * (_initialRect.bottomRight().y() - _center.y())));
//     break;
//   }
  
//   QRect newEnclosingRect(newTopLeft, newBottomRight);
//   //deduce from it the x, y , width and height easily. the angles don't change.
//   setSize(newEnclosingRect.width(), newEnclosingRect.height());
//   setX(newTopLeft.x() + width() / 2);
//   setY(newTopLeft.y() + height() / 2);
}
// -------------------------------------------------------------------

void
QGCanvasEllipse::resize(double kx, double ky)
{
}

// -------------------------------------------------------------------

//should be improved to take in account the angles...
QRect
QGCanvasEllipse::coordsSelectionRectangle()
{
  QRectF r = boundingRect();
  return r.toRect();
}

// -------------------------------------------------------------------

QGVectItem *
QGCanvasEllipse::clone()
{
  return new QGCanvasEllipse(*this);
}

// -------------------------------------------------------------------
// P R O T E C T E D   M E M B E R S
// -------------------------------------------------------------------

void
QGCanvasEllipse::paint(QPainter & p, const QStyleOptionGraphicsItem* opt, QWidget * widget)
{
//   if ( !a1 && a2 == 360*16 ) {
//     p.drawEllipse(int(x()-w/2.0+0.5), int(y()-h/2.0+0.5), w, h);
//   } else {
//     p.drawArc(int(x()-w/2.0+0.5), int(y()-h/2.0+0.5), w, h, a1, a2);
//   }  

  // Where the variables a1, a2, w and h come from???
  p.drawEllipse(boundingRect()); // TO TEST!

  if ( isSelected() )
    drawSelectionRectangle(p);
}

// -------------------------------------------------------------------
