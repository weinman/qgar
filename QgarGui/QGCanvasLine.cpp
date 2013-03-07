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
 * @file  QGCanvasLine.cpp
 * @brief Implementation of class QGCanvasLine.
 *
 *        See file QGCanvasLine.h for the interface.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date  2001
 * @since Qgar 2.0
 */



// STL
#include <math.h>
using namespace std;
// QGUI
#include <QGCanvasLine.h>
// QGAR
#include <qgarlib/primitives.h>
// QT
#include <QPainter>



// -------------------------------------------------------------------
// S T A T I C     C O N S T     M E M B E R     I N I T 
// -------------------------------------------------------------------

const int QGCanvasLine::RTTI_LINE = 1001;



// **********************************************************************
// C O N S T R U C T O R S   A N D   D E S T R U C T O R
// **********************************************************************

QGCanvasLine::QGCanvasLine(QGraphicsScene * canvas, int width)
  : QGraphicsLineItem(), 
    _originalWidth(width)
{
  QPen p = pen();
  
  p.setWidth(width);
  setPen(p);
  _realWidth = width;
  _isResizing=false;

}


// -------------------------------------------------------------------

QGCanvasLine::QGCanvasLine(const qgar::GenQgarSegment<int>& seg)
  : QGraphicsLineItem(0),
  _originalWidth(seg.thickness())
{
  QPen p = pen();
  
  p.setWidth(seg.thickness());
  setPen(p);

  setLine(QLineF(seg.xSource(), seg.ySource(),
	    seg.xTarget(), seg.yTarget()));

  _realWidth = seg.thickness();
  _isResizing=false;
}

// -------------------------------------------------------------------

QGCanvasLine::QGCanvasLine(const QGCanvasLine & obj)
  : QGraphicsLineItem(),
    _originalWidth(obj.width())
{
  obj.scene()->addItem(this);
}

// **********************************************************************
// P U B L I C   M E M B E R S
// **********************************************************************

void
QGCanvasLine::skelMode()
{
  QPen p = pen();

  p.setWidth(1);
  setPen(p);
}

// **********************************************************************

void
QGCanvasLine::normalMode()
{
  QPen p = pen();

  p.setWidth(_realWidth);
  setPen(p);
}

// **********************************************************************
void QGCanvasLine::setWidth(int w) {
  _realWidth=w;
  normalMode();
}

void QGCanvasLine::moveBy(double dx, double dy)
{
  QGraphicsLineItem::moveBy(dx, dy);

    // Note: does NOT call QCanvasPolygonalItem::moveBy(), since that
    // only does half this work.
    //
//     int idx = int(x()+dx)-int(x());
//     int idy = int(y()+dy)-int(y());
//     if ( idx || idy ) {
// 	removeFromChunks();
// 	this->setPoints(startPoint().x() + idx, startPoint().y() + idy,
// 			endPoint().x() + idx, endPoint().y() + idy);
// 	addToChunks();
//     }
}

// **********************************************************************

void
QGCanvasLine::resize(double kx, double ky)
{
  
}


// **********************************************************************

void QGCanvasLine::resize(double k) {
//   if (!_isResizing){
//     cerr<<"we can't resize befor biginning resizing!"<<endl;
//     return;
//   }
  
//   switch(_type){
//   case QGSelMovResInteractor::XY:
//     setPoints( int(_center.x() + k * ((*_initialPoints)[0].x() -  _center.x())),
// 	       int(_center.y() + k * ((*_initialPoints[0]).y() -  _center.y())),
// 	       int(_center.x() + k * ((*_initialPoints)[1].x() -  _center.x())),
// 	       int(_center.y() + k * ((*_initialPoints)[1].y() -  _center.y())));
//     break;

//   case QGSelMovResInteractor::X:
//     setPoints( int(_center.x() + k * ((*_initialPoints)[0].x() - _center.x())),
// 	       int((*_initialPoints)[0].y()),
// 	       int(_center.x() + k * ((*_initialPoints)[1].x() - _center.x())),
// 	       int((*_initialPoints)[1].y()));
//     break;

//   case QGSelMovResInteractor::Y:
//     setPoints( int((*_initialPoints)[0].x()),
// 	       int(_center.y() + k * ((*_initialPoints)[0].y() - _center.y())),
// 	       int((*_initialPoints)[1].x()),
// 	       int(_center.y() + k * ((*_initialPoints)[1].y() - _center.y())));
//     break;
//   }
}

// **********************************************************************

QRect QGCanvasLine::coordsSelectionRectangle() {

  QLineF lineF = this->line();
  QLine line = lineF.toLine();

  qreal minX;
  qreal minY;
  qreal maxX;
  qreal maxY;

  if (lineF.x1() < lineF.x2()) {
    minX = lineF.x1();
    maxX = lineF.x2();
  }
  else {
    minX = lineF.x2();
    maxX = lineF.x1();
  }

  if (lineF.y1() < lineF.y2()) {
    minY = lineF.y1();
    maxY = lineF.y2();
  }
  else {
    minY = lineF.y2();
    maxY = lineF.y1();
  }
  
  QRectF rectF(minX, minY, maxX - minX, maxY - minY);
  return rectF.toRect();
}

// **********************************************************************

QPolygon QGCanvasLine::getPoints() {
 QPolygon qpta = QPolygon();
 QLineF lineF = this->line();
 
 qpta.setPoints(2, (int)lineF.x1(), (int)lineF.y1(),
		(int)lineF.x2(), (int)lineF.y2());
 return qpta;
}

// **********************************************************************

double QGCanvasLine::length() {

  QLineF lineF = this->line();
  return sqrt( (lineF.x2() - lineF.x1()) * (lineF.x2() - lineF.x1()) + (lineF.y2() - lineF.y1()) * (lineF.y2() - lineF.y1()) );
} 

// **********************************************************************

double QGCanvasLine::tanT() {

  QLineF lineF = this->line();
  return (lineF.y2() - lineF.y1()) / (lineF.x2() - lineF.x1());
}

// **********************************************************************

double QGCanvasLine::sinT() {

  QLineF lineF = this->line();
  return (lineF.y2() - lineF.y1()) / length();
}

// **********************************************************************

double QGCanvasLine::cosT() {

  QLineF lineF = this->line();
  return (lineF.x2() - lineF.x1()) / length();
}

// **********************************************************************

bool QGCanvasLine::isVertical() {

  QLineF lineF = this->line();
  return ( lineF.x1() == lineF.x2() );
}

// **********************************************************************

bool QGCanvasLine::isHorizontal() {
  
  QLineF lineF = this->line();
  return ( lineF.y1() == lineF.y2() );
} 


// **********************************************************************

QGVectItem * 
QGCanvasLine::clone() 
{
  return new QGCanvasLine(*this);
}

// **********************************************************************
// P R O T E C T E D   M E M B E R S
// **********************************************************************

void
QGCanvasLine::paint(QPainter& p, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
  if ( isSelected() ) {

    drawSelectionRectangle(p);
  }

  // Call base class drawing method.
  QGraphicsLineItem::paint(&p, option, widget);
}

// **********************************************************************
