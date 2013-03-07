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


#ifndef __QGLAYERIF_H_INCLUDED__
#define __QGLAYERIF_H_INCLUDED__


/**
 * @file     QGLayerIf.h
 * @brief    Header file of class QGLayerIf
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 17, 2002  17:13
 * @since   Qgar 2.1
 */


/* $Id: QGLayerIf.h,v 1.13 2005/07/13 16:30:28 masini Exp $ */



// QGUI
#include "QGLayerSubjectIf.h"
// QGAR
#include <qgarlib/QgarAppParamDescr.h>
// QT
#include <QPainter>
#include <QGraphicsScene>

static int layerCounter = 0;

class QPainter;
class QPixmap;
class QRect;


/**
 * @class QGLayerIf QGLayerIf.h "QGLayerIf.h"
 * @brief This class is the base interface of all layers of the
 * application.
 *
 * <p>
 * This interface is clearly intended to be a <i>protocol class</i>
 * between the different layer implementations and the rest of the
 * application.
 * </p>
 * <p>
 * The subclasses differ mainly in the type of image they represent
 * whether they are vectorial images or ordinary image<br>
 * This interface defines function members needed by the application
 * to handle a loaded layer. These function member can be regrouped in
 * three categories:
 * - Access function members: Clients must have means to query the
 *   image dimensions.
 * - Drawing function members: Clients willing to paint the layer will defer
 *   the drawing to the layer itself, using dynamic binding.
 * - Notification Function Members: Implementing the QGLayerSubjectIf
 *   interface allow client classes to monitor a layer internal change
 *   in order to update itself accordingly.
 * </p>
 * <p>
 * No layer is created directly. Use and update the QGImageLoader
 * singleton to load an image file and create the corresponding valid
 * layer.
 * </p>
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 17, 2002  17:13
 * @since  Qgar 2.1
 */
class QGLayerIf

  : public QGLayerSubjectIf

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGLayerIf() {}

//@}


/**
 * @brief Saves the layer on disk.
 */
  virtual void save() = 0;


/** @name Access */
//        ======
//@{
/**
 * @brief Access to the width of the layer.
 *
 * @return The layer width.
 */
  virtual int width() const = 0;


/**
 * @brief Access to the height of the layer.
 *
 * @return The layer height.
 */
  virtual int height() const = 0;

/**
 * @brief Access to the number of items of the layer.
 *
 * @return The number of item of the layer.
 */
  virtual int items() const = 0;


/**
 * @brief The keyword identifying the type of layer.
 *
 * @return the layer type.
 */
  virtual const char * type() const = 0;


/**
 * @brief Retrieve the format of the layer.
 *
 * @return The layer format.
 */
  virtual qgar::QgarAppParamDescr::ParamFormat format() const = 0;
//@}


/** @name Layer update notification */
//@{
/**
 * @brief Informs the layer that a rectangular region has been
 * modified.
 *
 * @param x The x-coordinate of the top left corner of the modified
 * region.
 * @param y The y-coordinate of the top left corner of the modified
 * region.
 * @param width  The width of the modified region.
 * @param height The height of the modified region.
 */
  virtual void update(int x, int y, int width, int height) = 0;


/**
 * @brief Informs the layer that its whole area has been modified.
 *
 * @overload
 */
  virtual void update() = 0;


/**
 * @brief Informs the layer that a rectangular region has been
 * modified.
 *
 * @param rect The modified region.
 *
 * @overload
 */
  virtual void update(const QRect& rect) = 0;
//@}


/** @name Transform */
//@{
/**
 * @brief Set the layer width.
 *
 * @param width The layer new width
 */
  virtual void setWidth(int width) = 0;

/**
 * @brief Set the layer height.
 *
 * @param height The layer new height
 */
  virtual void setHeight(int height) = 0;
//@}


/** @name Paint methods */
//@{
/**
 * @brief Draws a rectangular part of the layer using a given painter.
 *
 * @param p The painter to draw with.
 * @param x The x-coordinate of the top left corner of the rectangle
 * to paint.
 * @param y The y-coordinate of the top left corner of the rectangle
 * to paint.
 * @param wd  The width of the rectangle to paint.
 * @param ht The height of the rectangle to paint.
 */
  virtual void draw(QPainter* p, int x, int y, int wd, int ht) = 0;
 
/**
 * @brief Draws a rectangular part of the layer in a given pixmap.
 *
 * This function member assumes that the pixmap size can at least
 * contain the rectangle portion of the image
 *
 * @param dst The destination pixmap.
 * @param x The x-coordinate of the top left corner of the rectangle
 * to paint.
 * @param y The y-coordinate of the top left corner of the rectangle
 * to paint.
 * @param wd The width of the rectangle to paint.
 * @param ht The height of the rectangle to paint.
 */
  virtual void draw(QPixmap& dst, 
		    int x, 
		    int y, 
		    int wd, 
		    int ht,
		    //Qt::RasterOp op = Qt::CopyROP
		    QPainter::CompositionMode op = QPainter::CompositionMode_SourceOver
		    ) = 0;

  //////////////////////////////////////////////
  //TEST
  virtual void draw(int x, int y, int wd, int ht, QGraphicsScene&  sc) = 0;

//@}

// -------------------------------------------------------------------
}; // class QGLayerIf


#endif /* __QGLAYERIF_H_INCLUDED__ */
