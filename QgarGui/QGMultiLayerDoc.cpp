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
 * @file  QGMultiLayerDoc.cpp
 * @brief Implementation of class QGMultiLayerDoc
 *
 *        See file QGMultiLayerDoc.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 17, 2002  16:04
 */



// QGUI
#include "QGMultiLayerDoc.h"
#include "QGCanvasLine.h"
#include "QGInfoLayer.h"
#include "QGLayerIf.h"
#include "QGUndoList.h"
#include "QGDocViewer.h"

// QGAR
#include <qgarlib/primitives.h>
#include <qgarlib/stl.h>
// QT
#include <QPainter>
#include <QPixmap>

// STD
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <functional>


using namespace std;
using namespace qgar;


// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGMultiLayerDoc::QGMultiLayerDoc()
{
  _width    = 0;
  _height   = 0;
  _modified = false;
  _zoom     = 1.0F;
  _superimposeMode = false;

  _undoList = new QGUndoList(10);
  _infoLayer = new QGInfoLayer();

}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------

QGMultiLayerDoc::~QGMultiLayerDoc()
{
  delete _undoList;
  delete _infoLayer;
  
  // Delete all layers.
  for_each(_layerVect.begin(), _layerVect.end(), qstlDeleteObject());
}


// ---------------------------------------------------------------------
// A C C E S S
// ---------------------------------------------------------------------

// -------
// Getters
// -------

QGInfoLayer *
QGMultiLayerDoc::infoLayer() const
{
  return _infoLayer;
}

int
QGMultiLayerDoc::layerNumber() const
{
  return _layerVect.size();
}

// ---------------------------------------------------------------------

int 
QGMultiLayerDoc::width() const
{ 
  return _width;
}

// ---------------------------------------------------------------------

int
QGMultiLayerDoc::height() const
{
  return _height;
}

// ---------------------------------------------------------------------

bool
QGMultiLayerDoc::modified() const
{
  return _modified;
}

// ---------------------------------------------------------------------

float
QGMultiLayerDoc::zoom() const
{
  return _zoom;
}

// ---------------------------------------------------------------------

QString 
QGMultiLayerDoc::fileName() const
{
  return _fileName;
}

// ---------------------------------------------------------------------

QString
QGMultiLayerDoc::name() const
{
  return _name;
}

// ---------------------------------------------------------------------

QGUndoList *
QGMultiLayerDoc::undoList() const
{
  return _undoList;
}

// -------------------------------------------------------------------

QGLayerIf *
QGMultiLayerDoc::activeLayer() const
{
  return _layerVect.front();
}

// -------
// Setters
// -------

void
QGMultiLayerDoc::setWidth(int wd)
{
  _width = wd;
}

// ---------------------------------------------------------------------

void
QGMultiLayerDoc::setHeight(int ht)
{
  _height = ht;
}

// ---------------------------------------------------------------------

void
QGMultiLayerDoc::setModified(bool mod)
{
  _modified = mod;
}

// ---------------------------------------------------------------------

void
QGMultiLayerDoc::setZoom(float zoom)
{
  _zoom = zoom;
}

// ---------------------------------------------------------------------

void
QGMultiLayerDoc::setFileName(const QString& fileName)
{
  _fileName = fileName;
}

// ---------------------------------------------------------------------

void
QGMultiLayerDoc::setName(const QString& name)
{
  _name = name;
}

// -------------------------------------------------------------------
// U N D O     M A N A G E M E N T 
// -------------------------------------------------------------------

void
QGMultiLayerDoc::undo() 
{
  _undoList->undo();
}

// -------------------------------------------------------------------


void
QGMultiLayerDoc::redo()
{
  _undoList->redo();
}

// -------------------------------------------------------------------

void
QGMultiLayerDoc::registerCommand(const QGUndoableCommandIf& command)
{
    _undoList->registerCommand(command);
  
  // Mark this document as modified.
  _modified = true;
}

// -------------------------------------------------------------------
// L A Y E R     M A N A G E M E N T 
// -------------------------------------------------------------------

void
QGMultiLayerDoc::addLayer(QGLayerIf * layer, int depth) 
{
  //-- Check if depth is valid.

  if ( (depth < 0) || (depth > (int)_layerVect.size()) )
    throw invalid_argument("Depth is negative or beyond vector range");


  //-- Check if layer is already inserted

  QVector<QGLayerIf *>::iterator it;
  it = find(_layerVect.begin(), _layerVect.end(), layer);

  
  //-- If not, insert it at position depth

  if (it == _layerVect.end() ) {
    
    it = _layerVect.begin();
    _layerVect.insert(it + depth, layer);

    
    // Resize canvas if necessary, to match new layer size
    
    bool resize = false;
    int wd = layer->width();
    int ht = layer->height();
    resize = ( (_width < wd ) || (_height < ht));

    if (resize) {
      _width  = max(_width, wd);
      _height = max(_height, ht);

    }
  }

  // Resize info canvas
  _infoLayer->setWidth(_width);
  _infoLayer->setHeight(_height);
}

// ----------------------------------------------------------------------
void 
QGMultiLayerDoc::removeLayer(QGLayerIf * layer)
{
  QVector<QGLayerIf *>::iterator it;
  
  //-- Seek element
  
  it = find(_layerVect.begin(), _layerVect.end(), layer);

  
  //-- Delete it and remove it from the vector
  
  if (it != _layerVect.end()) {

    delete (*it);
    _layerVect.erase(it);
  }
}
// ----------------------------------------------------------------------

QGLayerIf *
QGMultiLayerDoc::layerAt(int depth) 
{
  //-- Check if depth is valid

  if ( (depth < 0) || (depth > (int)_layerVect.size()) )
    throw invalid_argument("Depth is negative or beyond vector range");


  //-- Search for item
  QVector<QGLayerIf *>::iterator it(_layerVect.begin());

  return *(it + depth);
}
// ----------------------------------------------------------------------

int
QGMultiLayerDoc::layerCount() const
{
  return _layerVect.size();
}

// ----------------------------------------------------------------------

void
QGMultiLayerDoc::addToInfoLayer(QGraphicsItem * item)
{
  _infoLayer->insertVectItem(item);
  activeLayer()->update(item->boundingRect().toRect());
}

// ----------------------------------------------------------------------

void
QGMultiLayerDoc::removeFromInfoLayer(QGraphicsItem * item)
{
  if(item)
  {
    _infoLayer->removeVectItem(item);
    activeLayer()->update();
  }
}

// ----------------------------------------------------------------------

int 
QGMultiLayerDoc::drawArea(int cx, int cy, int cw, int ch, QPainter  * p)
{
  if (_layerVect.empty())
    return 0;
  
  QVector<QGLayerIf *>::iterator it = _layerVect.begin();
  
//   // Draw first with CopyROP as raster op.
  (*it)->draw(p, cx, cy, cw, ch);
  ++it;
  
  
//   // Draw other layers on top.   
//   //  p->setRasterOp(Qt::AndROP);
//   for (/* EMPTY */ ; it != _layerVect.end(); ++it)    
//     (*it)->draw(p, cx, cy, cw, ch);
  
//   // Draw informations on top
//  _infoLayer->draw(p, cx, cy, cw, ch);
  return 0;
}

// ----------------------------------------------------------------------

int
QGMultiLayerDoc::drawArea(int cx, int cy, int cw, int ch, QPixmap * pix)
{
  QVector<QGLayerIf *>::iterator it = _layerVect.begin();

  // Draw first with CopyROP as raster op.
  (*it)->draw(*pix, cx, cy, cw, ch, QPainter::CompositionMode_SourceOver);
  ++it;
  
  //  Draw the next layer on top.
  for (/* EMPTY */; it != _layerVect.end(); ++it)    
    (*it)->draw(*pix, cx, cy, cw, ch, QPainter::CompositionMode_SourceOver);
  
  // Draw informations on top
  _infoLayer->draw(*pix, cx, cy, cw, ch, QPainter::CompositionMode_Destination);

  return 0;
}

// ----------------------------------------------------------------------

int
QGMultiLayerDoc::drawArea(int cx, int cy, int cw, int ch, QGraphicsScene * _scene)//, QList<QGraphicsItem *> list)
{
  int items = 0;
  QVector<QGLayerIf *>::iterator it = _layerVect.begin();

  // First layer
  (*it)->draw(0, cy, cw, ch, (*_scene));
  items += (*it)->items();
  ++it;

  // If another layer available, it's superimpose mode
  
  if(it != _layerVect.end())
  {
    (*it)->draw(1, cy, cw, ch, (*_scene));
    items += (*it)->items();
    ++it;
  }

  _infoLayer->draw(2, cy, cw, ch, (*_scene));
  items += _infoLayer->items();

  return items; 
  
}

