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
 * @file  QGCanvasPolyline.cpp
 * @brief Implementation of class QGCanvasPolyline.
 *
 * See file QGCanvasPolyline.h for the interface.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date  December, 12  2000  10:27
 * @since Qgar 2.0
 */



// QGAR
#include <qgarlib/primitives.h>
// STD
#include <algorithm>
#include <iostream>
#include <deque>
#include <vector>
// QT
#include <QPainter>
// QGUI
#include "QGCanvasPolyline.h"



using namespace qgar;
using namespace std;



// -------------------------------------------------------------------
// S T A T I C     M E M B E R S     I N I T 
// -------------------------------------------------------------------

const int QGCanvasPolyline::RTTI_POLYLINE = 1000;


// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

QGCanvasPolyline::QGCanvasPolyline(QGraphicsScene * canvas)

  : QAbstractGraphicsShapeItem(0),
    _realWidth(0),
    _originalWidth(-1)
  
{
  _isResizing=false;
}

// ---------------------------------------------------------------------

QGCanvasPolyline::QGCanvasPolyline(const GenQgarPolyline<int>& poly)

  : QAbstractGraphicsShapeItem(0), 
    _realWidth(poly.thickness()),
    _originalWidth(poly.thickness())
{
  //-- Copy polyline points.
  
  deque<Point> points = poly.vertices();
  deque<Point>::iterator it;

  QPolygon ptArray(points.size());
  int i;

  for (it = points.begin(), i=0; it != points.end(); ++it, ++i) {

    ptArray.setPoint(i, QPoint( (*it).x(), (*it).y() ));
  }


  //-- Build Qt Polyline from the extracted points 

  _pen.setWidth(poly.thickness());

  setPoints(ptArray);
  setWidth(poly.thickness());
}

// ---------------------------------------------------------------------

QGCanvasPolyline::QGCanvasPolyline(const QGCanvasPolyline & obj)
  : QAbstractGraphicsShapeItem(),
    _originalWidth(obj.originalWidth())
{
  obj.scene()->addItem(this);
}

// ---------------------------------------------------------------------

QGCanvasPolyline::~QGCanvasPolyline()
{
  hide();
}

// ---------------------------------------------------------------------
// O T H E R   M E T H O D S
// ---------------------------------------------------------------------

void
QGCanvasPolyline::skelMode()
{
  //  QPen p = pen();
  _pen.setWidth(1);
  setPen(_pen);
}

// ---------------------------------------------------------------------


void
QGCanvasPolyline::normalMode()
{
  QPen p = pen();

  p.setWidth(_realWidth);
  setPen(p);
}

// ---------------------------------------------------------------------

void
QGCanvasPolyline::setWidth(int width)
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
QGCanvasPolyline::setPen(QPen p)
{ 
  QAbstractGraphicsShapeItem::setPen(p);
}

// ---------------------------------------------------------------------

void
QGCanvasPolyline::setPoints(QPolygon thePoints)
{
    _thePoints = thePoints; //shallow copy !!!!!
}

// ---------------------------------------------------------------------

void
QGCanvasPolyline::paint(QPainter* p, const QStyleOptionGraphicsItem * option, QWidget * widget = 0)
{
  QPolygon pa = _thePoints;
  
  QPen pen;
  pen.setWidth(width());
  p->setPen(pen);
  
  if ( isSelected() ) {
    
    drawSelectionRectangle(*p);
    
     QPen pen(p->pen());
     pen.setColor(QColor("blue"));
     p->setPen(pen);
   }
  
  pa.translate((int) x(), (int) y());
  p->drawPolyline(pa);
}

// ---------------------------------------------------------------------

QRectF
QGCanvasPolyline::boundingRect() const
{
  // Implemented as coordsSelectionRectangle but 
  // returning a Float Rectangle.
  // This method must be reimplemented to inherits
  // QAbstractGraphicShapeItem

  vector<int> vx(_thePoints.size());
  vector<int> vy(_thePoints.size());
  
  for (int i = 0; i < (int)_thePoints.size(); i++) {
    vx[i]=_thePoints.point(i).x();
    vy[i]=_thePoints.point(i).y();
  }
  
  qreal minx = *min_element(vx.begin(), vx.end());
  qreal miny = *min_element(vy.begin(), vy.end());
  qreal maxx = *max_element(vx.begin(), vx.end());
  qreal maxy = *max_element(vy.begin(), vy.end());
  
  // Correct bounding rect with polyline width.
  qreal halfW = (pen().width()/2);
  
  return QRectF(minx - halfW, miny - halfW, 
	       maxx - minx + 1 + 2 * halfW, maxy - miny + 1 + 2 * halfW);
  
}

// ---------------------------------------------------------------------

QPolygon
QGCanvasPolyline::areaPoints() const
{
  // A polyline contains at least 2 points...

  if (_thePoints.size() > 2) {
    QPolygon result(2 * _thePoints.size());
    vector<QPolygon> theAreas(_thePoints.size() - 1);
    int i;
    
    
    // First, we compute areas associated with each line
    // of the polyline
    
    for (i = 0; i < (int)_thePoints.size() - 1; i++)
      theAreas[i] = areaPoints(_thePoints[i].x(), _thePoints[i + 1].x(),
			       _thePoints[i].y(), _thePoints[i + 1].y());
    
    // After that, we compute the area of the whole polyline
    
    for (i = 0; i < (int)_thePoints.size() - 1; i++)
      result[i] = theAreas[i][0];
    
    result[_thePoints.size() - 1] = theAreas[_thePoints.size() - 2][1];
    result[_thePoints.size()] = theAreas[_thePoints.size() - 2][2];
    
    for (i = _thePoints.size() - 2; i >= 0; i--)
      result[2 * _thePoints.size() - 1 - i] = theAreas[i][3];
    
    return result;
  }
  else
    return areaPoints(_thePoints[0].x(), _thePoints[1].x(),
		      _thePoints[0].y(), _thePoints[1].y());
}

// ---------------------------------------------------------------------

// Note: This method is the original QCanvasLine::areaPoints() method,
// provided by the Qt sources

QPolygon
QGCanvasPolyline::areaPoints(int x1, int x2, int y1, int y2) const
{
    QPolygon p(4);
    int xi = int(x());
    int yi = int(y());
    int pw = pen().width();
    int dx = qAbs(x1 - x2);
    int dy = qAbs(y1 - y2);
    if ( pw <= 1 ) {
	// thin
	if (dx > dy) {
	    p[0] = QPoint(x1 + xi, y1 + yi - 1);
	    p[1] = QPoint(x2 + xi, y2 + yi - 1);
	    p[2] = QPoint(x2 + xi, y2 + yi + 1);
	    p[3] = QPoint(x1 + xi, y1 + yi + 1);
	} else {
	    p[0] = QPoint(x1 + xi - 1, y1 + yi);
	    p[1] = QPoint(x2 + xi - 1, y2 + yi);
	    p[2] = QPoint(x2 + xi + 1, y2 + yi);
	    p[3] = QPoint(x1 + xi + 1, y1 + yi);
	}
    } else {
	pw = pw * 4 / 3 +2; // approx pw*sqrt(2)
	int px = (x1 < x2)? -pw : pw ;
	int py = (y1 < y2)? -pw : pw ;

	if (dx && dy && (dx > dy ? (dx * 2 / dy <= 2) : (dy * 2 / dx <= 2))) {
	    // steep
	    if (px == py) {
		p[0] = QPoint(x1 + xi     , y1 + yi + py);
		p[1] = QPoint(x2 + xi - px, y2 + yi     );
		p[2] = QPoint(x2 + xi     , y2 + yi - py);
		p[3] = QPoint(x1 + xi + px, y1 + yi     );
	    } else {
		p[0] = QPoint(x1 + xi + px, y1 + yi     );
		p[1] = QPoint(x2 + xi     , y2 + yi - py);
		p[2] = QPoint(x2 + xi - px, y2 + yi     );
		p[3] = QPoint(x1 + xi     , y1 + yi + py);
	    }
	} else if (dx > dy) {
	    // horizontal
	    p[0] = QPoint(x1 + xi + px, y1 + yi + py);
	    p[1] = QPoint(x2 + xi - px, y2 + yi + py);
	    p[2] = QPoint(x2 + xi - px, y2 + yi - py);
	    p[3] = QPoint(x1 + xi + px, y1 + yi - py);
	} else {
	    // vertical
	    p[0] = QPoint(x1 + xi + px, y1 + yi + py);
	    p[1] = QPoint(x2 + xi + px, y2 + yi - py);
	    p[2] = QPoint(x2 + xi - px, y2 + yi - py);
	    p[3] = QPoint(x1 + xi - px, y1 + yi + py);
	}
    }
    return p;
}

void QGCanvasPolyline::moveBy(double dx, double dy){

  this->moveBy(dx, dy);

  // Note: does NOT call QAbstractGraphicsShapeItem::moveBy(), since that
  // only does half this work.
  
  //anyway x() and y() give always 0 ... (because we have reimplemented moveBy)

//   int idx = int(x() + dx) - int(x());
//   int idy = int(y() + dy) - int(y());

//   if (idx || idy) {
//     (this->canvas())->setChanged(this->boundingRect());
//     _thePoints.translate(idx,idy);
//     addToChunks();
//   }
}

// ---------------------------------------------------------------------

void
QGCanvasPolyline::resize(double kx, double ky)
{
}

// ---------------------------------------------------------------------

void QGCanvasPolyline::resize(double k) {
//   if (!_isResizing){
//     cerr<<"we can't resize befor beginning resizing!"<<endl;
//     return;
//   } 
//   QPolygon * pa = new QPolygon(_thePoints.size());
//   int i=0;
 
//   switch(_type){
//   case QGSelMovResInteractor::XY:
//     for (; i<_thePoints.size(); i++) {
//       pa->setPoint(i, int(_center.x() + k * ((*_initialPoints)[i].x() - _center.x())),
// 		   int(_center.y() + k * ( (*_initialPoints)[i].y() - _center.y())));
//     }
//     break;
//   case QGSelMovResInteractor::X:
//     for (; i<_thePoints.size(); i++) {
//       pa->setPoint(i, int(_center.x() + k * ( (*_initialPoints)[i].x() - _center.x())),
// 		   int((*_initialPoints)[i].y()));
//     }
//     break;
//   case QGSelMovResInteractor::Y:
//     for (; i<_thePoints.size(); i++) {
//       pa->setPoint(i, int((*_initialPoints)[i].x()),
// 		   int(_center.y() + k * ( (*_initialPoints)[i].y() - _center.y())));
//     }
//     break;
//   }

//   setPoints(*pa);
}

// ---------------------------------------------------------------------

QRect QGCanvasPolyline::coordsSelectionRectangle() {
    vector<int> vx(_thePoints.size());
    vector<int> vy(_thePoints.size());

    for (int i = 0; i < (int)_thePoints.size(); i++) {
      vx[i]=_thePoints.point(i).x();
      vy[i]=_thePoints.point(i).y();
    }

    int minx = *min_element(vx.begin(), vx.end());
    int miny = *min_element(vy.begin(), vy.end());
    int maxx = *max_element(vx.begin(), vx.end());
    int maxy = *max_element(vy.begin(), vy.end());
    
    // Correct bounding rect with polyline width.
    int halfW = (int)(pen().width()/2);

    return QRect(minx - halfW, miny - halfW, 
		 maxx - minx + 1 + 2 * halfW, maxy - miny + 1 + 2 * halfW);
}

// ---------------------------------------------------------------------

QGVectItem * 
QGCanvasPolyline::clone() {
  return new QGCanvasPolyline(*this);
}

// **********************************************************************

