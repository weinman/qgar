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
 * @file  QGPixmapLayer.cpp
 * @brief Implementation of class QGPixmapLayer.
 *
 * See file QGPixmapLayer.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 17, 2002  17:27
 * @since  Qgar 2.1
 */



// QGUI
#include "QGPixmapLayer.h"
// QT
#include <QGraphicsPixmapItem>

#include <iostream>

using namespace qgar;
using namespace std;



// -------------------------------------------------------------------
// S T A T I C     M E M B E R S     I N I T 
// -------------------------------------------------------------------

const char * QGPixmapLayer::PGM_TYPE = "PGM";
const char * QGPixmapLayer::PBM_TYPE = "PBM";
const char * QGPixmapLayer::PPM_TYPE = "PPM";



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGPixmapLayer::QGPixmapLayer()
  : _filename("")
{
}

// -------------------------------------------------------------------


QGPixmapLayer::QGPixmapLayer(const QString& filename) throw (runtime_error)
{
  loadImage(filename);
}



// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------

QGPixmapLayer::~QGPixmapLayer()
{
  layerCounter--;
}



// -------------------------------------------------------------------
// A C C E S S 
// -------------------------------------------------------------------

QgarAppParamDescr::ParamFormat
QGPixmapLayer::format() const {
  return _format;
}

QGraphicsScene*
QGPixmapLayer::getScene()
{
  return _scene;
}
// -------------------------------------------------------------------

QImage&
QGPixmapLayer::image()
{
  return _image;
}

// -------------------------------------------------------------------
// T R A N S F O R M
// -------------------------------------------------------------------

void 
QGPixmapLayer::setType(const char * type)
{
  _type = type;
}

// -------------------------------------------------------------------

void
QGPixmapLayer::setFormat(QgarAppParamDescr::ParamFormat format) {
  _format = format;
}

// -------------------------------------------------------------------
// I / O     M E T H O D S 
// -------------------------------------------------------------------

void
QGPixmapLayer::loadImage(const QString& filename) throw(runtime_error)
{
  layerCounter++;

  _image.load(filename);

  if(_image.isNull())
    throw runtime_error("Error while loading image");

  if (_image.depth() == 1)
    _image = _image.convertToFormat(QImage::Format_Indexed8);
    
  _width  = _image.width();
  _height = _image.height(); 

  _filename = filename;

}

// -------------------------------------------------------------------
// O T H E R
// -------------------------------------------------------------------

void QGPixmapLayer::init(const QString& filename) throw(runtime_error)
{
}

// -------------------------------------------------------------------
// Q G L A Y E R I F     I M P L E M E N T A T I O N 
// -------------------------------------------------------------------

void
QGPixmapLayer::save()
{
  if (_filename != "") {
    
    _image.save(_filename);

  }
}

// -------------------------------------------------------------------

int 
QGPixmapLayer::items() const
{
  //  QList<QGraphicsItem *> list = _scene->items();
  //  return list.size();
  //  if(!_scene)
  if(_image.isNull())
    return 0;
  else
    return 1;
}

// -------------------------------------------------------------------

void
QGPixmapLayer::draw(QPainter * p, int cx, int cy, int cw, int ch)
{
  p->drawImage(0, 0, _image, cx, cy, cw, ch, 
		 Qt::AutoColor | Qt::ThresholdDither | Qt::NoAlpha | Qt::AvoidDither
		 );
}

// -------------------------------------------------------------------

void
QGPixmapLayer::draw(QPixmap& dst, int cx, int cy, int cw, int ch,
		    QPainter::CompositionMode op)
{
  QPainter p(&dst);
  p.setCompositionMode(op);

  p.drawImage(cx, cy, _image, cx, cy, cw, ch,
	      Qt::AutoColor | Qt::ThresholdDither | Qt::NoAlpha | Qt::AvoidDither
	      );

}

// -------------------------------------------------------------------

void
QGPixmapLayer::draw(int cx, int cy, int cw, int ch,
		    QGraphicsScene& scene)
{
  // Clean the scene
  QList<QGraphicsItem *> list = scene.items();
  QList<QGraphicsItem *>::iterator it = list.begin();
  for(it; it != list.end(); ++it)
  {
    scene.removeItem(*it);
  }

  QGraphicsPixmapItem * item = new 
    QGraphicsPixmapItem(QPixmap::fromImage(_image, Qt::AutoColor));
  scene.addItem(item);
}
