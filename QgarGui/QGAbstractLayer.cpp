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
 * @file  QGAbstractLayer.cpp
 * @brief Implementation of class QGAbstractLayer
 *
 *        See file QGAbstractLayer.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   December 20, 2002  14:57
 * @since  Qgar 2.1
 */


// QGUI
#include "QGAbstractLayer.h"
#include "QGLayerObserverIf.h"
// QT
#include <QRect>
// STL
#include <algorithm>
#include <functional>
#include <vector>



using namespace qgar;
using namespace std;



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGAbstractLayer::QGAbstractLayer()
  : _width(0), _height(0), _items(0)
{ /* EMPTY */ }

// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

// Default constructor
QGAbstractLayer::~QGAbstractLayer() 
{ /* EMPTY */ }

// -------------------------------------------------------------------
// U P D A T E S 
// -------------------------------------------------------------------

void
QGAbstractLayer::update() 
{
  notifyUpdate(0, 0, width(), height());
}

// -------------------------------------------------------------------

void
QGAbstractLayer::update(int x, int y, int width, int height)
{
  notifyUpdate(x, y, width, height);
}

// -------------------------------------------------------------------

void
QGAbstractLayer::update(const QRect& rect)
{
  notifyUpdate(rect.x(), rect.y(), rect.width(), rect.height());
}

// -------------------------------------------------------------------
// L A Y E R     S U B J E C T     I M P L 
// -------------------------------------------------------------------

void
QGAbstractLayer::attach(QGLayerObserverIf * obs)
{
  // Search if observer is in the vector
  vector<QGLayerObserverIf*>::iterator it;

  it = find(_obsVect.begin(), _obsVect.end(), obs);
  
  // If not found, insert observer
  if( it == _obsVect.end())

     _obsVect.push_back(obs);  
}

// ---------------------------------------------------------------------

void
QGAbstractLayer::detach(QGLayerObserverIf * obs) {

  _obsVect.erase(remove(_obsVect.begin(), _obsVect.end(), obs), 
		 _obsVect.end());
}

// ---------------------------------------------------------------------


void
QGAbstractLayer::notifyUpdate(int x, int y, int width, int height)
{

  // For each observer, call layerUpdated()

  vector<QGLayerObserverIf*>::iterator it;

  for(it=_obsVect.begin(); it !=_obsVect.end(); ++it) {
    (*it)->layerUpdated(x, y, width, height);
  }
}

// ----------------------------------------------------------------------
// Q G L A Y E R I F   I M P L
// ----------------------------------------------------------------------

int
QGAbstractLayer::width() const
{
  return _width;
}

// -------------------------------------------------------------------

int
QGAbstractLayer::height() const
{
  return _height;
}

// -------------------------------------------------------------------

const char *
QGAbstractLayer::type() const
{
  return _type;
}

// -------------------------------------------------------------------

QgarAppParamDescr::ParamFormat
QGAbstractLayer::format() const
{
  return _format;
}

// -------------------------------------------------------------------
void
QGAbstractLayer::setWidth(int width)
{
  _width = width;
}

// -------------------------------------------------------------------

void
QGAbstractLayer::setHeight(int height)
{
  _height = height;
}

// -------------------------------------------------------------------
