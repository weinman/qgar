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
 * @file  QGImageLoader.cpp
 * @brief Implementation of class QGImageLoader.
 *
 * See file QGImageLoader.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 21, 2002  17:37
 * @since  Qgar 2.1
 */



// QGUI
#include "QGImageLoader.h"
#include "QGDxfLayer.h"
#include "QGPixmapLayer.h"
#include "QGSvgLayer.h"
// QT
#include <QImage>
#include <QString>
#include <QImageReader>


using namespace qgar;
using namespace std;



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGImageLoader::QGImageLoader() 
{ /* EMPTY */ }



// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

// Default constructor
QGImageLoader::~QGImageLoader() 
{ /* EMPTY */ }



// -------------------------------------------------------------------
// A C C E S S 
// -------------------------------------------------------------------

QGImageLoader *
QGImageLoader::instance()
{
  static QGImageLoader loader;

  return &loader; 
}


// -------------------------------------------------------------------
// C R E A T I O N     M E T H O D S 
// -------------------------------------------------------------------

QGLayerIf *
QGImageLoader::loadLayer(const QString& filename) 
{ 
  QGLayerIf * retval = 0;

  QByteArray byteArray = QImageReader::imageFormat(filename);

  // If file is a QT supported image format, it is a pixmap and
  // it can be loaded.
  if (!byteArray.isEmpty()) {

    try {
      QGPixmapLayer * layer = new QGPixmapLayer(filename);

      // Set Layer type
      if (!strcmp(byteArray, "pgm")) {
	layer->setType(QGPixmapLayer::PGM_TYPE);
	layer->setFormat(QgarAppParamDescr::QGE_PGM);
      }
      
      else if (!strcmp(byteArray, "pbm")) {
	layer->setType(QGPixmapLayer::PBM_TYPE);
	layer->setFormat(QgarAppParamDescr::QGE_PBM);
      }

      else if (!strcmp(byteArray, "ppm")) {  
	layer->setType(QGPixmapLayer::PPM_TYPE);
	layer->setFormat(QgarAppParamDescr::QGE_PPM);
      }

      retval = layer;
    }

    catch(exception e) {
      retval = 0;
    }  
  }

  // ELSE: the image is a vector image file.
  else { 
    try {
      retval = new QGDxfLayer(filename);
    }
    catch(exception e) {
      retval = 0;
    }
  }
  
//     try {
//       retval = new QGSvgLayer(filename);
//       retval->setFormat(QGE_SVG);
//     }
//     catch(exception e) {
//       retval = 0;
//     }
//   }
  return retval;
}

// ----------------------------------------------------------------------

