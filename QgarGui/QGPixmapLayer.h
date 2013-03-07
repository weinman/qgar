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


#ifndef __QGPIXMAPLAYER_H_INCLUDED__
#define __QGPIXMAPLAYER_H_INCLUDED__


/**
 * @file   QGPixmapLayer.h
 * @brief  Header file of class QGPixmapLayer
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 17, 2002  17:27
 * @since  Qgar 2.1
 */


/* $Id: QGPixmapLayer.h,v 1.12 2005/07/13 16:30:28 masini Exp $ */



// QGUI
#include "QGAbstractLayer.h"
// STL
#include <stdexcept>

// QT4
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QString>
#include <QGraphicsScene>

/**
 * @class QGPixmapLayer QGPixmapLayer.h "QGPixmapLayer.h"
 * @brief An image layer displaying a pixmap.
 * 
 * This class creates layers for all pixmap images loaded in the
 * application. The supported format are: PGM, PBM, PPM.
 *
 * @todo Remove the char* identifying the format and replace them
 * with the QgarLib enum.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 17, 2002  17:27
 * @since  Qgar 2.1
 */

static int lc = 0;

class QGPixmapLayer

  : public QGAbstractLayer

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:


/** @name Consts */
//        ======
//@{

  /// A string identifying the PGM type
  static const char * PGM_TYPE;

  /// A string identifying the PBM type
  static const char * PBM_TYPE;

  /// A string identifying the PPM type
  static const char * PPM_TYPE;

//@}



/** @name Constructors */
//        ============
//@{

/**
 * @brief Creates an empty pixmap layer.
 */
  QGPixmapLayer();


/**
 * @brief Creates a pixmap layer from an image file
 *
 * @param filename The name of the image file to create the layer from
 * 
 * @throw runtime_error if an error occured while loading the file.
 */
  QGPixmapLayer(const QString& filename) throw(std::runtime_error);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGPixmapLayer();
//@}


/** @name Access */
//        ======
//@{

/**
 * @brief Access to this layer image.
 */
  QImage& image();

/**
 * @brief Access to this scene.
 */
  QGraphicsScene* getScene();

//@}


/** @name Transformation */
//        ==============
//@{

/**
 * @brief Set type.
 *
 * @param type
 */
  void setType(const char * type);


/**
 * @brief Set format.
 *
 * @param format
 */
  void setFormat(qgar::QgarAppParamDescr::ParamFormat format);

//@}

/** @name Other */
//        =====
//@{

/**
 * @brief Initialize scene
 *
 * @param filename
 */
  void init(const QString& filename) throw(std::runtime_error);

/** @name QGLayerIf Impl */
//        ==============
//@{

  virtual void save();

  virtual qgar::QgarAppParamDescr::ParamFormat format() const;

  virtual void draw(QPainter * p, int x, int y, int wd, int ht); 

  virtual void draw(QPixmap& dst, int x, int y, int wd, int ht,
		    QPainter::CompositionMode op = QPainter::CompositionMode_SourceOver);

  virtual void draw(int x, int y, int wd, int ht, QGraphicsScene& scene);

  virtual int items() const;

//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// The layer image
  QImage _image;

  /// The name of the file this layer was created from.
  QString _filename;

  /// The scene to hold the image
  QGraphicsScene * _scene;

/**
 * @brief Loads an image.
 *
 * @throw std::runtime_error if the file cannot be reached
 * or if it does not contain a compatible image.
 */
  virtual void loadImage(const QString& filename) throw(std::runtime_error);





// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:


/** @name Disabled */
//        ========
//@{

/**
 * @brief Copy-constructor
 */
  QGPixmapLayer(const QGPixmapLayer&);

/**
 * @brief Assignment operator
 */
  QGPixmapLayer& operator=(const QGPixmapLayer&);

//@}


// -------------------------------------------------------------------
}; // class QGPixmapLayer


#endif /* __QGPIXMAPLAYER_H_INCLUDED__ */
