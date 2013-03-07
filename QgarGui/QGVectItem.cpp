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
 * @file  QGVectItem.cpp
 * @brief Implementation of class QGVectItem.
 *
 * See file QGVectItem.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 21, 2002  11:13
 * @since  Qgar 2.1
 */



// QGUI
#include "QGVectItem.h"
// QT
#include <QPainter>
#include <QColor>
#include <QGraphicsScene>
#include <QGraphicsItem>
//#include <QTransform>


using namespace std;



// -------------------------------------------------------------------
// S T A T I C     M E M B E R     I N I T 
// -------------------------------------------------------------------

const int QGVectItem::RESIZE_BOX_WIDTH = 6;

// -------------------------------------------------------------------
// O T H E R 
// -------------------------------------------------------------------

vector<QPoint> 
QGVectItem::computeCoords()
{
  QRect rect = coordsSelectionRectangle();

  int x1 = rect.x();
  int y1 = rect.y();
  int x2 = rect.topRight().x();
  int y2 = rect.bottomLeft().y();
    
  int xCenter = rect.center().x();
  int yCenter = rect.center().y();

  int halfW = (int)( RESIZE_BOX_WIDTH / 2 );
  
  vector<QPoint> list;
  list.reserve(8);
  
  list.push_back( QPoint(x1 - halfW, y1 - halfW) ); // topLeft
  list.push_back( QPoint(xCenter , y1 - halfW) );   // topCenter
  list.push_back( QPoint(x2 + halfW, y1 - halfW) ); // topRight
  list.push_back( QPoint(x2 + halfW, yCenter) );    // centerRight
  list.push_back( QPoint(x2 + halfW, y2 + halfW) ); // bottomRight
  list.push_back( QPoint(xCenter, y2 + halfW) );    // bottomCenter
  list.push_back( QPoint(x1 - halfW, y2 + halfW) ); // bottomLeft
  list.push_back( QPoint(x1 - halfW, yCenter) );    // centerLeft

  return list;
}

// -------------------------------------------------------------------
vector<QRect> 
QGVectItem::computeResizeRects()
{
  vector<QRect> retval;

  retval.reserve(9);

  // first item is the bounding rect
  retval.push_back( coordsSelectionRectangle() );

  vector<QPoint> summitCoords( computeCoords() );
  QRect rect(0, 0, RESIZE_BOX_WIDTH, RESIZE_BOX_WIDTH);
  
  for (int iCnt = 0; iCnt < 8; iCnt++) {
    rect.moveCenter(summitCoords[iCnt]);
    retval.push_back(rect);
  }

  return retval;
}

// -------------------------------------------------------------------

void
QGVectItem::drawSelectionRectangle(QPainter& p)
{
  //-- Save current painter state.

  p.save();

  //  p.setWorldXForm(false);
  // No equivalent. Only allow or not if a transformation matrix
  // is passed as argument...
 
  //-- Draw bounding rect. With resize rect on the edges.
  
  QRectF bounding;
  vector<QPoint> summitVect;
  QMatrix m = p.worldMatrix();
  //  QTransform t = p.worldTransform();

  // Draw the bounding rectangle with a 1px width.
  // The transformation matrix is explicitly applied and the 
  // world transformations are then disabled to ensure that
  // the width is 1px whatever scaling is performed on the painter.

  // Since Qt4, the rendering of rectangles changes depending on
  // its thickness.
  bounding = coordsSelectionRectangle();
  //  bounding = QRect(m * bounding.topLeft(), bounding.size());

  // Create a pen painting in red with 1px width
  QPen pen;
  pen.setColor(QColor("red"));
  pen.setWidth(1);
  
  p.setPen(pen);
  
  // Draw selection rectangle.
  p.drawRect(bounding);


  //-- Draw resize boxes around the object.

  // Set paint color.
  pen.setColor(QColor("black"));

  
  p.setPen(pen);
  QBrush brush(Qt::red);
  p.setBrush(brush);
  summitVect = computeCoords();
  QRect rect(0, 0, RESIZE_BOX_WIDTH, RESIZE_BOX_WIDTH);

  //@D Temporarily disabled.
//   for (int iCnt = 0; iCnt < 8; iCnt++) {
//     rect.moveCenter( m * summitVect[iCnt] );
//     p.drawRect(rect);
//   }
  
  // Restore previous painter state.
  p.restore();

}


// ----------------------------------------------------------------------


QGraphicsItem *
QGVectItem::cloneAsGraphicsItem()
{

  QGVectItem * copy = this->clone();
  QGraphicsItem * retval = dynamic_cast<QGraphicsItem *>(copy);

  if (!retval)
    delete copy;

  return retval;
}

// ----------------------------------------------------------------------
