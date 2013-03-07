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
 * @file  QGDocViewer.cpp
 * @brief Implementation of class QGDocViewer
 *
 *        See file QGDocViewer.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   December 12, 2002  14:29
 */



// QGUI
#include "QGDocViewer.h"
#include "QGImageLoader.h"
#include "QGLayerIf.h"
#include "QGMultiLayerDoc.h"
#include "QGPixmapLayer.h"
#include "QGVectorialLayer.h"

#include <QGraphicsItem>

// STD
#include <cmath>
#include <ctime>

using namespace qgar;
using namespace std;


// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGDocViewer::QGDocViewer(QWidget * parent)
  : QGraphicsView(parent)
{
  // Keeps the contents of the view static aligned in top left corner
  setAlignment(Qt::AlignLeft | Qt::AlignTop);

  setMouseTracking(true);

  // Init cache coords.
  _cacheX = _cacheY = _cacheWd = _cacheHt = 0;
  
  // Default zoom level is 1.
  _zoom = 1.0;

  // No document is shown: Background is dark.
  _document = 0;

  // Superimpose Mode is off by default
  _superimposeMode = false;

  // No items yet in the scene
  _items = 0;

  // Initialize a blank scene
  _scene.setBackgroundBrush(Qt::white);

  // Link the scene with QGDocViewer widget
  setScene(&_scene);

}


// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

// Default constructor
QGDocViewer::~QGDocViewer() 
{
  flushCache();
}


// ---------------------------------------------------------------------
// A C C E S S
// ---------------------------------------------------------------------

QGMultiLayerDoc *
QGDocViewer::document() const
{
  return _document;
}

// ---------------------------------------------------------------------

double
QGDocViewer::zoom() const
{
  return _zoom;
}

// ---------------------------------------------------------------------
// T R A N S F O R M A T I O N
// ----------------------------------------------------------------------

void 
QGDocViewer::setDocument(QGMultiLayerDoc * document)
{
  int layerCount = 0;
  // If a document was being displayed, detach self form its observer
  // list
  if (_document)
  {
    _document->activeLayer()->detach(this);
  }
  // Assign document.
  _document = document;
 
  // Settings dependant on the presence of a valid doc.
  if (_document) {

    // How many layers used in the former document?.
    layerCount = _document->layerNumber();

    // Register as document's active layer observer.
    _document->activeLayer()->attach(this);

    // Remove all former document items from the scene
    _list = _scene.items();

    for(int i=0; i<_items; i++)
    {
      if (!_list.isEmpty())
      {
	_scene.removeItem(_list.takeFirst());
      }
    }

     // Copy layer in cache
    int numberOfItems = updateCache(0, 0, _document->width(), 
				    _document->height());
  
    _scene.update();
  
    setSceneRect(0, 0, _document->width(), _document->height());

    // Updates the item counter of the new scene
    _items = numberOfItems;
  }
  else 
  {
    _list = _scene.items();    
    
    // Remove all remaining items in the scene
    QList<QGraphicsItem *>::iterator it = _list.begin();
    for(it; it != _list.end(); ++it)
      _scene.removeItem(*it);
    
    // Empty the item counter variable
    _items = 0;
    
    // Just set a small scene to suppress the scroll bars
    setSceneRect(0, 0, 200, 150);

    _scene.update();
  }
}

// -------------------------------------------------------------------

void
QGDocViewer::setZoom(double zoom)
{
  if (_zoom == zoom)
    return;

  // Verify the fraction between the new value
  // and the old zoom
  float zoomFraction = zoom/_zoom;

  _zoom = zoom;

  // If a document is being displayed, repaint it with new zoom value.
    if (_document) {
      scale( zoomFraction, zoomFraction);
    }
}

// -------------------------------------------------------------------


// -------------------------------------------------------------------
// L A Y E R    O B S E R V E R   I M P L 
// -------------------------------------------------------------------

void 
QGDocViewer::layerUpdated(int x, int y, int width, int height)
{
  updateCache(x, y, width, height);

  // Compute the visible coordinates of the rectangle to be repainted
  if (_zoom != 1.0) {
    x      = (int)(x * _zoom);
    y      = (int)(y *_zoom);
    width  = (int)(width *_zoom);
    height = (int)(height *_zoom);
  }  

  _scene.update(x, y, width, height);
}

// ----------------------------------------------------------------------
int
QGDocViewer::updateCache(int x, int y, int wd, int ht) 
{
  // Paint clip rectangle in the cache.
  //  _document->drawArea(x, y, wd, ht, &_cache);
  return _document->drawArea(x, y, wd, ht, &_scene);
}

// ----------------------------------------------------------------------

void
QGDocViewer::flushCache()
{
  //  _cache = QPixmap(0 ,0);
  //  _cache.fill(Qt::white);
}

// ----------------------------------------------------------------------

