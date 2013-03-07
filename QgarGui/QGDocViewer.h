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


#ifndef __QGDOCVIEWER_H_INCLUDED__
#define __QGDOCVIEWER_H_INCLUDED__


/**
 * @file     QGDocViewer.h
 * @brief    Header file of class QGDocViewer
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     December 12, 2002  14:29
 * @since    Qgar 2.1
 */


/* $Id: QGDocViewer.h,v 1.8 2005/07/13 16:30:27 masini Exp $ */



// QGUI
#include "QGLayerObserverIf.h"
class QGMultiLayerDoc;
class QWidget;

// QT
#include <QImage>
#include <QPixmap>
#include <QGraphicsView>
#include <QGraphicsScene>


/**
 * @class QGDocViewer QGDocViewer.h "QGDocViewer.h"
 * @brief A widget displaying a view of a QGMultiLayerDoc instance.
 *
 * <p>
 * This widget is a document viewer. Viewing includes horizontal and
 * vertical scrolling along with forward and reverse zooming.<br>
 * It also offers a set of methods to transform coordinates from the
 * view coordinate system to the document or from the document to
 * the view.
 * </p>
 * <p>
 * The view is automatically updated if the document it displays is
 * modified. The instance is notified that a change in the document
 * has occured via the Observer pattern defined between
 * QGLayerObserverIf and QGLayerSubjectIf.
 * </p>
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   December 12, 2002  14:29
 *
 * @since Qgar 2.1
 */
class QGDocViewer

: public QGraphicsView, public QGLayerObserverIf

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name Constructors */
//        ============
//@{

/**
 * @brief Default constructor
 *
 * By default this widget is created with the following flags:
 * - WResizeNoErase
 * - WStaticContents.
 * .
 * Both flag allow better refresh performence.<br>
 * Any flag passed to the constructor will be appended to these two.
 *
 * @param parent The parent of this widget in the Qt object model.
 * @param name   The name of this widget.
 * @param f      The creation flags of this widget.
 */
  QGDocViewer(QWidget * parent = 0);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGDocViewer();

//@}


/** @name Access */
//        ======
//@{

/**
 * @brief Retrieve a pointer to the document being displayed.
 *
 * @return A pointer on the document being displayed or 0 if no
 * document is shown.
 */
  QGMultiLayerDoc * document() const;


/**
 * @brief Retrieve the zoom level with which the document is shown.
 *
 * @return The current zooming factor.
 */
  double zoom() const;

//@}


/** @name Transformation */
//        ==============
//@{

/**
 * @brief Sets the document to be displayed.
 *
 * @param document the new document to be shown.
 */
  void setDocument(QGMultiLayerDoc * document);


/**
 * @brief Sets the zoom factor of the document.
 *
 * @param zoom The new zoom factor
 */
  void setZoom(double zoom);

/**
 * @brief Sets the superimpose mode.
 *
 * @param status True to turn on, false to turn off.
 */
  inline void setSuperimposeMode(bool status) {_superimposeMode = status;}

/**
 * @brief Sets the superimpose mode.
 *
 * @param status True to turn on, false to turn off.
 */
  inline bool isSuperimposeMode() {return _superimposeMode;}

//@}

/**
 * @brief Draws a clip rectangle of the document on a given painter.
 * 
 * The clip rectangle is defined in contents coordinates.
 *
 * @param p     The painter to draw with.
 * @param clipx The x coordinate of the clip rect.
 * @param clipy The y coordinate of the clip rect.
 * @param clipw The width of the clip rect.
 * @param cliph The height of the clip rect.
 */
/*   virtual void drawContents(QPainter * p, int clipx, int clipy,  */
/* 			    int clipw, int cliph); */




/** @name QGLayerObserverIf Impl */
//        ======================
//@{

  virtual void layerUpdated(int x, int y, int width, int height);

//@}





/** @name Coordinates Transformation */
//        ==========================
//@{

 /**
  * @brief Transforms a QPoint from the canvas coordinate to the
  * canvas view viewport coordinates.
  *
  * Transformation involves performing zoom and contents to viewport
  * transformation.
  *
  * @param pt The QPoint to transform.
  *
  * @return The point in QGDocViewer viewport coordinates.
  */
  //  QPoint toViewCoords(const QPoint& pt) const 
  //  {
  //    return contentsToViewport(pt * _zoom);
  //  }


/**
 * @brief Transforms a QRect from the canvas coordinate to the
 * canvas view viewport coordinates.
 *
 * Transformation involves performing zoom and contents to viewport
 * transformation.
 *
 * @param rect The QRect to transform.
 *
 * @return The point in QGDocViewer viewport coordinates.
 */
//  QRect toViewCoords(const QRect& rect) const 
//  {
//    return QRect(toViewCoords(rect.topLeft()), toViewCoords(rect.bottomRight()));
//  }


/**
 * @brief Transforms a QPoint from the canvas view viewport coordinates
 * to the canvas coordinates.
 *
 * Transformation involves performing viewport to contents and
 * inverse zoom transformation.
 *
 * @param pt The QPoint to transform.
 *
 * @return The point in real coordinates.
 */
  QPoint toRealCoords(const QPointF& pt) const 
  {
    return mapFromScene(pt);
    //    return QPointF(mapToScene(pt.toPoint())).toPoint();
  }

/**
 * @brief Transforms a QRect from the canvas view viewport coordinates
 * to the canvas coordinates.
 *
 * Transformation involves performing viewport to contents and
 * inverse zoom transformation.
 *
 * @param rect The QRect to transform.
 *
 * @return The point in real coordinates.
 */
  QRect toRealCoords(const QRect& rect) const {
    return QRect(toRealCoords(rect.topLeft()), toRealCoords(rect.bottomRight()));
  }


/**
 * @brief Apply zoom on a QPoint
 *
 * @param pt The QPoint to zoom.
 *
 * @return The zoomed QPoint.
 */
  QPoint zoom(const QPoint& pt) const {
    return pt * _zoom;
  }


/**
 * @brief Apply zoom on a QRect
 *
 * @param rect The QRect to inverse zoom to.
 *
 * @return The zoomed QRect.
 */
  QRect zoom(const QRect& rect) const {
    return QRect( zoom( rect.topLeft() ), zoom( rect.bottomRight() ) );
  }


/**
 * @brief Apply inverse zoom on a QPoint
 *
 * @param pt the QPoint to apply the inverse zoom to.
 *
 * @return The inverse zoomed QPoint
 */
  QPoint invZoom(const QPoint& pt) const {
    return pt / _zoom;
  }


/**
 * @brief Apply inverse zoom on a QRect
 *
 * @param rect the QRect to apply the inverse zoom to.
 *
 * @return The inverse zoomed QRect.
 */
  QRect invZoom(const QRect& rect) const {
    return QRect( invZoom( rect.topLeft() ), invZoom( rect.bottomRight() ) );
  }

//@}




// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// A pointer to the document shown.
  QGMultiLayerDoc * _document;

  /// The buffered image of the viewport.
  //  QPixmap _cache;

  /// The GraphicsScene to display the View
  QGraphicsScene _scene;

  /// The item list
  QList<QGraphicsItem*> _list;

 protected:
  /// The cache x origin on the document.
  int _cacheX;

  /// The cache y origin on the document.
  int _cacheY;

  /// The cache width.
  int _cacheWd;

  /// The cache height.
  int _cacheHt;

  /// The current zoom factor.
  double _zoom;

  /// Number of items in the current scene
  int _items;

  /// Superimpose mode
  bool _superimposeMode;


/**
 * @brief Updates a portion of the cache.
 *
 * @param x  The x-coordinate of the clip rect.
 * @param y  The x-coordinate of the clip rect.
 * @param wd The width of the clip rect.
 * @param ht The height of the clip rect.
 * 
 * @return The number of items in the document
 */
  int updateCache(int x, int y, int wd, int ht);


/**
 * @brief Discards cache document preview.
 */
  void flushCache();



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
  QGDocViewer(const QGDocViewer&);

/**
 * @brief Assignment operator
 */
  QGDocViewer& operator=(const QGDocViewer&);

//@}

// -------------------------------------------------------------------
}; // class QGDocViewer


#endif /* __QGDOCVIEWER_H_INCLUDED__ */
