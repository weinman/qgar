/*---------------------------------------------------------------------*
 | Graphical user interface QgarGui                                    |
 | Copyright (C) 2003  Qgar Project, LORIA                             |
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
 * @file  QGSvgLayer.cpp
 * @brief Implementation of class QGSvgLayer.
 *
 * See file QGSvgLayer.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   May 6, 2003  15:06
 * @since  Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGSvgLayer.cpp,v 1.3 2005/07/13 16:30:29 masini Exp $ */



// QGUI
#include "QGSvgLayer.h"
#include "QGCanvasLine.h"
#include "QGCanvasPolyline.h"
// WARNING: Disable until changes are commited in QgarLib
// #include <SvgFile.h>
// QT
#include <QGraphicsItem>
#include <QString>



using namespace qgar;
using namespace std;



// -------------------------------------------------------------------
// S T A T I C     M E M B E R     I N I T 
// -------------------------------------------------------------------

const char * QGSvgLayer::SVG_TYPE = "SVG";



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

QGSvgLayer::QGSvgLayer()
{ /* EMPTY */ }


// ---------------------------------------------------------------------

QGSvgLayer::QGSvgLayer(const QString& filename)  throw (runtime_error)
  : QGVectorialLayer(filename)
{
  init(filename);
}


// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

QGSvgLayer::~QGSvgLayer()
{ /* EMPTY */ }


// -------------------------------------------------------------------
// Q G L A Y E R I F     I M P L 
// -------------------------------------------------------------------

const char *
QGSvgLayer::type() const
{ 
  return SVG_TYPE;
}

// -------------------------------------------------------------------

QgarAppParamDescr::ParamFormat
QGSvgLayer::format() const {
  return QgarAppParamDescr::QGE_SVG;
}

// -------------------------------------------------------------------
// Q G V E C T O R I A L L A Y E R     I M P L 
// -------------------------------------------------------------------

QPoint
QGSvgLayer::loadItems(const QString& filename, std::vector<QGraphicsItem *>& vect)
  throw (runtime_error)
{
//   SvgFile file(filename.latin1());

//   file.readEntities();



//   //-- Retrieve Segments

//   const list<QgarSegment *>& segs = file.getSegments();

//   list<QgarSegment *>::const_iterator it;

//   for (it = segs.begin(); it != segs.end(); ++it) {

//     _itemVect.push_back(new QGCanvasLine(*(*it)));
//   }



//   //-- Retrieve Polyline

//   const list<QgarPolyline *>& polys = file.getPolylines();
   
//   list<QgarPolyline *>::const_iterator it2;
  
//   for (it2 = polys.begin(); it2 != polys.end(); ++it2) {

//     _itemVect.push_back(new QGCanvasPolyline(*(*it2)));
//   }



//   //-- Retrieve Arcs

//   for_each(_itemVect.begin(), _itemVect.end(), 
// 	   mem_fun(&QGraphicsItem::show));

//   cout << file.width() << " " << file.height() << endl;

//   return QPoint(file.width(), file.height());

  // Added for compilation purposed
  return QPoint(0, 0);
}

// ----------------------------------------------------------------------
