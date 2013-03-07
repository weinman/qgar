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
 * @file  QGVectorialLayer.cpp
 * @brief Implementation of class QGVectorialLayer.
 *
 * See file QGVectorialLayer.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 18, 2002  17:48
 * @since    Qgar 2.1
 */



// QGUI
#include "QGVectorialLayer.h"
#include "QGVectItem.h"
#include "QGCanvasEllipse.h"
// QT
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPoint>
#include <QString>
#include <QPainter>
#include <QPixmap>
// STD
#include <algorithm>
#include <functional>

#include <iostream>

#include <QtGui>

using namespace std;



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGVectorialLayer::QGVectorialLayer()
{ 
  _skelModeOn = false;
  _graphicsScene = new QGraphicsScene();
}

// -------------------------------------------------------------------

// Default constructor
QGVectorialLayer::QGVectorialLayer(const QString& filename) 
  throw(runtime_error)
{ 
  _skelModeOn = false;
  _graphicsScene = new QGraphicsScene();
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------

QGVectorialLayer::~QGVectorialLayer() 
{ 
  // Delete all vector items
  QVector<QGraphicsItem *>::iterator it;
  
  for (it = _itemVect.begin(); it != _itemVect.end(); ++it)
     delete (*it);

  // The GraphicsScene member must not be explicitaly deleted because 
  // it's referenced by Skelmode GraphicsScene instance.
  // Qt controls the object destruction and inheritance and it will
  // control this reference.
}


// -------------------------------------------------------------------
// A C C E S S 
// -------------------------------------------------------------------

bool
QGVectorialLayer::skelModeOn() const
{
  return _skelModeOn;
}

// -------------------------------------------------------------------

QGraphicsScene *
QGVectorialLayer::canvas() const
{
  return _graphicsScene;
}

// -------------------------------------------------------------------
// T R A N S F O R M A T I O N 
// -------------------------------------------------------------------

void
QGVectorialLayer::setSkelModeOn(bool on)
{
  if (_skelModeOn == on)
    return;

  if (on) {

    //-- For each QGraphicsItem implementing QGVectItem, switch to skeleton mode.
    
    QVector<QGraphicsItem *>::iterator it(_itemVect.begin());
    for ( /* EMPTY */; it != _itemVect.end(); it++) {
      if ( QGVectItem * vectItem = dynamic_cast<QGVectItem *>(*it) ) {
	vectItem->setWidth(0);
      }
      else
	std::cout << "Item " << (*it) << " nao sofreu cast." << std::endl;
    }
  }
  
  else {
    QVector<QGraphicsItem *>::iterator it(_itemVect.begin());
    for ( /* EMPTY */; it != _itemVect.end(); it++) {
      
      if ( QGVectItem * vectItem = dynamic_cast<QGVectItem *>(*it) ) {
	vectItem->setWidth(vectItem->originalWidth());
      }
      else
	std::cout << "Item " << (*it) << " nao sofreu cast." << std::endl;
    }
  }

  
  //-- Notify update.

  update();


  //-- Update _skelModeOn
  
  _skelModeOn = on;
}

// -------------------------------------------------------------------

void
QGVectorialLayer::setColor(const QColor& color)
{
  QPen pen(color);

  QVector<QGraphicsItem *>::iterator it;

  for(it = _itemVect.begin(); it !=  _itemVect.end(); ++it) {
    
    if (QAbstractGraphicsShapeItem * polyItem =
	dynamic_cast<QAbstractGraphicsShapeItem *>(*it))
    {
      polyItem->setPen(pen);
    }
  }
}

// -------------------------------------------------------------------
// O T H E R
// -------------------------------------------------------------------

void
QGVectorialLayer::init(const QString& filename) throw (runtime_error)
{
  QPoint pt = loadItems(filename, _itemVect);

  _width  = pt.x();
  _height = pt.y();

  _graphicsScene->setSceneRect(0, 0, _width, _height);

}

// -------------------------------------------------------------------

void
QGVectorialLayer::insertVectItem(QGraphicsItem * item)
{
  _graphicsScene->addItem(item);
  item->setVisible(true);
  _itemVect.push_back(item);
}

// -------------------------------------------------------------------

void
QGVectorialLayer::removeVectItem(QGraphicsItem * item)
{
  if (!item) 
    return;

  QVector<QGraphicsItem *>::iterator it;
  it = find(_itemVect.begin(), _itemVect.end(), item);

  if (it != _itemVect.end()) {
    _graphicsScene->removeItem(*it);

    // If item is not locked, delete it.
    if ( _lockedItemMap.find(item) == _lockedItemMap.end() ) {
      
      delete (*it);
    }

    _itemVect.erase(it);

  }
}

// -------------------------------------------------------------------

bool
QGVectorialLayer::hasItem(QGraphicsItem * item)
{
  QVector<QGraphicsItem *>::iterator it;

  it = find(_itemVect.begin(), _itemVect.end(), item);

  return ( it != _itemVect.end() );
}

// -------------------------------------------------------------------

void
QGVectorialLayer::lock(QGraphicsItem * item) {

  // Check if value is already in the map.

  RefCountMap::iterator it = _lockedItemMap.find(item);
  
  if ( it != _lockedItemMap.end() ) {
    ++(*it).second; // Increment reference counter.
  }

  else {
    // insert item in map
    RefCountMap::value_type value(item, 1);
    _lockedItemMap.insert(value);
  }
}

// -------------------------------------------------------------------

void QGVectorialLayer::unlock(QGraphicsItem * item) {
  
  RefCountMap::iterator it = _lockedItemMap.find(item);
  
  if ( it != _lockedItemMap.end() ) {
    
    if ( --( (*it).second) == 0 ) { // Decrement reference counter.
      
      // If item is no longer member of the _itemVect (ie. effectively
      // displayed) delete it.
      if (find(_itemVect.begin(), _itemVect.end(), item) 
	  == _itemVect.end()) {

	delete (*it).first;
      }
      _lockedItemMap.erase(it);
    }
  }
}

// -------------------------------------------------------------------
// Q G L A Y E R I F     I M P L E M E N T A T I O N 
// -------------------------------------------------------------------

void
QGVectorialLayer::setWidth(int width)
{
  QGAbstractLayer::setWidth(width);
  _graphicsScene->setSceneRect(0, 0, _width, _height);
}

// ----------------------------------------------------------------------

void
QGVectorialLayer::setHeight(int height)
{
  QGAbstractLayer::setHeight(height);
  _graphicsScene->setSceneRect(0, 0, _width, _height);
}

// ----------------------------------------------------------------------

int QGVectorialLayer::items() const
{
  return _itemVect.size();
}

// -------------------------------------------------------------------

void
QGVectorialLayer::draw(QPainter * p, int cx, int cy, int cw, int ch)
{
  QRectF rect = QRectF(cx, cy, cw, ch);
  _graphicsScene->render(p, rect);
}

// ----------------------------------------------------------------------

void 
QGVectorialLayer::draw(QPixmap& dst, int x, int y, int wd, int ht,
		       QPainter::CompositionMode op)
{
  QRectF rect = QRectF(x, y, wd, ht);

  dst.fill(Qt::white);
  QPainter paint(&dst);
  
  paint.setCompositionMode(op);
  
  _graphicsScene->render(&paint);
  paint.end();
}

// ----------------------------------------------------------------------

void 
QGVectorialLayer::draw(int x, int y, int wd, int ht, QGraphicsScene& sc)
{
  // The draw function is called at any operation needing refresh.
  // So, all elementes are tested before being inserted once they can 
  // already be at the scene
  QList<QGraphicsItem *> list = sc.items();

  // The x parameter will control the Z value of items
  // It means the 'level' on the scene, and control superimpose
  // among items
  QVector<QGraphicsItem *>::iterator it = _itemVect.begin();
  for(it; it != _itemVect.end(); ++it)
  {
    if(!list.contains(*it))
    {
      sc.addItem(*it);
      if(x>=0) (*it)->setZValue(x);
    }
  }
  _graphicsScene = &sc;

}
