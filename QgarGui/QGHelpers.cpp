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
 * @file  QGHelpers.cpp
 * @brief Implementation of class QGHelpers.
 *
 * See file QGHelpers.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 28, 2002  10:31
 * @since  Qgar 2.1
 */


// QGUI
#include "QGHelpers.h"
#include "QGVectItem.h"
// STL
#include <algorithm>
#include <iostream>
#include <numeric>
// QT
#include <QGraphicsItem>
#include <QImage>



using namespace std;



// -------------------------------------------------------------------
// S T A T I C     M E M B E R     F U N C T I O N S 
// -------------------------------------------------------------------

QGraphicsItem *
QGHelpers::duplicateItem(QGraphicsItem * item)
{
  if (! item)
    return 0;


  QGraphicsItem * retval = 0;

  if ( QGVectItem * vectItem = dynamic_cast<QGVectItem *>(item) ) {
    
    retval = vectItem->cloneAsGraphicsItem();
  }

  else {

    //    switch ( item->type() ) {
      
//     case QGraphicsItem::Rtti_Sprite:
//       retval = new QCanvasSprite(*(dynamic_cast<QCanvasSprite *>(item)));
      
//     case QGraphicsItem::Rtti_Text:
//       retval = new QCanvasText(*(dynamic_cast<QCanvasText *>(item)));
//       break;

// WARNING
// New commented part
// No equivalent in Qt4 - studying the solution      
//     case QGraphicsItem::Rtti_Polygon:
//       retval = new QGraphicsPolygonItem(*(dynamic_cast<QGraphicsPolygonItem *>(item)));
//       break;
      
//     case QGraphicsItem::Rtti_Rectangle:
//       retval = new QGraphicsRectItem(*(dynamic_cast<QGraphicsRectItem *>(item)));
//       break;
      
//     case QGraphicsItem::Rtti_Ellipse:
//       retval = new QGraphicsEllipseItem(*(dynamic_cast<QGraphicsEllipseItem *>(item)));
//       break;
      
//     case QGraphicsItem::Rtti_Line:
//       retval = new QGraphicsLineItem(*(dynamic_cast<QGraphicsLineItem *>(item)));
//       break;
      
//     case QGraphicsItem::Rtti_Spline:
//       retval = new QGraphicsPathItem(*(dynamic_cast<QGraphicsPathItem *>(item)));
//       break;
    
//     }  
   }

  return retval;
}

// ----------------------------------------------------------------------

QRect
QGHelpers::computeBoundingRect(const QVector<QPoint>& ptVect)
{
  // Compute the top left point of the rectangle bounding the points.
  QPoint topLeft = accumulate(ptVect.begin(), ptVect.end(),
			      ptVect.front(),
			      computeTopLeft);

  // Compute the top left point of the rectangle bounding the points.
  QPoint bottomRight = accumulate(ptVect.begin(), ptVect.end(),
				  ptVect.front(),
				  computeBottomRight);

  return QRect(topLeft, bottomRight);
}

// ----------------------------------------------------------------------

QPoint 
QGHelpers::computeTopLeft(const QPoint& a, const QPoint& b)
{
  return QPoint( min( a.x(), b.x() ), 
		 min( a.y(), b.y() ) );
}

// ----------------------------------------------------------------------

QPoint 
QGHelpers::computeBottomRight(const QPoint& a, const QPoint& b)
{
  return QPoint( max( a.x(), b.x() ), 
		 max( a.y(), b.y() ) );
}

// ----------------------------------------------------------------------
