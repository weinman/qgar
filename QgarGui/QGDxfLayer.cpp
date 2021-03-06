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
 |   LORIA - �quipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-l�s-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/


/**
 * @file  QGDxfLayer.cpp
 * @brief Implementation of class QGDxfLayer
 *
 *        See file QGDxfLayer.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 21, 2002  09:42
 */



// QGUI
#include "QGDxfLayer.h"
#include "QGDxfFile.h"
// STL
#include <algorithm>
#include <functional>
// QT
#include <QGraphicsScene>
#include <QString>
#include <QList>


using namespace qgar;
using namespace std;



// -------------------------------------------------------------------
// S T A T I C     M E M B E R     I N I T 
// -------------------------------------------------------------------

const char * QGDxfLayer::DXF_TYPE = "DXF";



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

QGDxfLayer::QGDxfLayer()
{ /* NOP */ }

// -------------------------------------------------------------------

QGDxfLayer::QGDxfLayer(const QString& filename)  throw (runtime_error)
  : QGVectorialLayer(filename)
{
  init(filename);
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


QGDxfLayer::~QGDxfLayer()
{ /* NOP */ }


// -------------------------------------------------------------------
// Q G L A Y E R I F     I M P L 
// -------------------------------------------------------------------

const char *
QGDxfLayer::type() const
{ 
  return DXF_TYPE;
}


// -------------------------------------------------------------------

QgarAppParamDescr::ParamFormat 
QGDxfLayer::format() const
{
  return QgarAppParamDescr::QGE_DXF;
}

// -------------------------------------------------------------------
// Q G V E C T O R I A L L A Y E R     I M P L 
// -------------------------------------------------------------------

QPoint
QGDxfLayer::loadItems(const QString& filename, QVector<QGraphicsItem *>& vect)
  throw (runtime_error)
{

  //-- Load vector elements from file
  
  //  QGraphicsScene canvas;
  QGDxfFile file(filename, _graphicsScene);
  QList<QGraphicsItem *> theItems = file.getList();


  //-- Unbind items from canvas

  // The following is a hack to retrieve the vector items from a
  // DxfFile instance, without keeping it.
  // Future versions will correct this behavior

  QList<QGraphicsItem *>::iterator it;
  for(it = theItems.begin(); it != theItems.end(); ++it)
  {
    //-- Copy the retrieved items in the item vector
    vect.push_back(*it);
  }

  //-- Return image size
  
  QPoint p(file.getWidth(), file.getHeight());
  
  return p;
}

// ----------------------------------------------------------------------

