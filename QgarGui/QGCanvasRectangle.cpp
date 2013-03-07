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


/**
 * @file  QGCanvasRectangle.cpp
 * @brief Implementation of class QGCanvasRectangle.
 *
 * See file QGCanvasRectangle.h for the interface.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date  December, 12  2000  10:27
 * @since Qgar 2.0
 */



// QGUI
// Not very clean, but useful to access to removeFromChunks and addToChunks
// whithout changing the header of QGraphicsScene (the others QCanvasItems are
// declared as friend)
#define private protected
#include "QGCanvasRectangle.h"
#undef private
// QGAR
#include <qgarlib/BoundingBox.h>
// STL
#include <vector>
#include <algorithm>
// QT
#include <QPainter>


using namespace qgar;
using namespace std;



// -------------------------------------------------------------------
// S T A T I C     C O N S T     M E M B E R S    I N I T 
// -------------------------------------------------------------------

const int QGCanvasRectangle::RTTI_RECTANGLE = 1003;

// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

QGCanvasRectangle::QGCanvasRectangle(QGraphicsScene* canvas)
  : QGraphicsRectItem()
{
  setZValue(10); //important -> they must be first in the collisions list.
  canvas->addItem(this);
}

// ---------------------------------------------------------------------

QGCanvasRectangle::QGCanvasRectangle(QGraphicsScene* canvas, int x, int y, int w, int h)
  : QGraphicsRectItem(x,y,w,h)
{
  setZValue(10);
  canvas->addItem(this);
}

// ---------------------------------------------------------------------

QGCanvasRectangle::QGCanvasRectangle(QGraphicsScene* canvas, QRect rect)
  : QGraphicsRectItem(rect)
{
  setZValue(10);
  canvas->addItem(this);
}

// ---------------------------------------------------------------------
// Construit un QGCanvasRectangle à partir de deux point diagonaux
QGCanvasRectangle::QGCanvasRectangle(QGraphicsScene* canvas, QPoint P1, QPoint P2)
  : QGraphicsRectItem(QRect(min(P1.x(), P2.x()), min(P1.y(), P2.y()),
			   abs(P1.x() - P2.x()), abs(P1.y() - P2.y())))
{
  setZValue(10);
  canvas->addItem(this);
}

// ---------------------------------------------------------------------

QGCanvasRectangle::QGCanvasRectangle(const BoundingBox& rect)
  : QGraphicsRectItem(rect.topLeft().x(), 
		     rect.topLeft().y(),
		     rect.length(),   // WARNING this may change with
		     rect.height(),   // future version of QgarLib
		     0)
{
  setZValue(10);
}

// ---------------------------------------------------------------------

QGCanvasRectangle::QGCanvasRectangle(const QGCanvasRectangle & obj)
  : QGraphicsRectItem()
{
  obj.scene()->addItem(this);
}


// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------


QGCanvasRectangle::~QGCanvasRectangle()
{
    hide();
}

// ---------------------------------------------------------------------
// O T H E R   M E T H O D S
// ---------------------------------------------------------------------

void
QGCanvasRectangle::skelMode()
{
  QPen p = pen();

  p.setWidth(1);
  setPen(p);
}

// ---------------------------------------------------------------------


void
QGCanvasRectangle::normalMode()
{
  QPen p = pen();

  p.setWidth(_realWidth);
  setPen(p);
}

// ---------------------------------------------------------------------

void
QGCanvasRectangle::setWidth(int width)
{
  QPen p = pen();

  p.setWidth(width);
  setPen(p);
  _realWidth = width;
}

// ---------------------------------------------------------------------

void
QGCanvasRectangle::setPen(QPen p)
{
    this->setPen(p);
}

// ---------------------------------------------------------------------


// void QGCanvasRectangle::moveBy(double dx, double dy)
// {
//     // Note: does NOT call QCanvasPolygonalItem::moveBy(), since that
//     // only does half this work.
//     //
//     int idx = int(x()+dx)-int(x());
//     int idy = int(y()+dy)-int(y());
//     if ( idx || idy ) {
// 	removeFromChunks();
// 	(this->canvas())->setChanged(this->boundingRect());
// 	_thePoints.translate(idx,idy);
//     }
//     if ( idx || idy ) {
// 	addToChunks();
//     }
// }

// ---------------------------------------------------------------------

void QGCanvasRectangle::resize(QPoint Po, double k) {
  int xo = Po.x();
  int yo = Po.y();
  this->setPos(int(xo + k * (x() - xo)),
  	       int(yo + k * (y() - yo)));
  this->scale(k, k);

}

// ---------------------------------------------------------------------

void
QGCanvasRectangle::resize(double kx, double ky)
{
}

// ---------------------------------------------------------------------

void QGCanvasRectangle::resizeX(QPoint Po, double k) {
  int xo = Po.x();
  this->setPos(xo + k * (x() - xo), y());
  this->scale(k, 1.0);
}

// ---------------------------------------------------------------------

void QGCanvasRectangle::resizeY(QPoint Po, double k) {
  int yo = Po.y();
  this->setPos(x(), yo + k * (y() - yo));
  this->scale(1.0, k);
}

// ---------------------------------------------------------------------

QRect QGCanvasRectangle::coordsSelectionRectangle() {

  return this->rect().toRect();
}

//----------------------------------------------------------------------

int QGCanvasRectangle::min (int x, int y) {
  if (x<y) {return x;} else {return y;}
}

//----------------------------------------------------------------------

// void QGCanvasRectangle::setPoints(QPointArray pa) {
//   if (pa.size()>4 || pa.size() <=1) {
//     cerr << "impossible de dessiner un tel rectangle" << endl;
//   }
//   removeFromChunks();
//   _thePoints = pa;
//   if (pa.size()==2) {
//     QPoint P1 = pa.point(0);
//     QPoint P2 = pa.point(1);
//     this->setX(min(P1.x(), P2.x()));
//     this->setY(min(P1.y(), P2.y()));
//     this->setSize(abs(P1.x()-P2.x()), abs(P1.y()-P2.y()));
//   }
//     addToChunks();
// }

//----------------------------------------------------------------------

QGVectItem *
QGCanvasRectangle::clone()
{
  return new QGCanvasRectangle(*this);
}

//----------------------------------------------------------------------
