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


#ifndef __QGSCRIBBLEINTERACTOR_H_INCLUDED__
#define __QGSCRIBBLEINTERACTOR_H_INCLUDED__


/**
 * @file     QGScribbleInteractor.h
 * @brief    Header file of class QGScribbleInteractor
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     December 2, 2002  17:38
 * @since    Qgar 2.1
 */


/* $Id: QGScribbleInteractor.h,v 1.7 2005/07/13 16:30:29 masini Exp $ */



// QGUI
#include "QGAbstractDocViewerInteractor.h"
template<class T> class QGEventRedirector;
class QGMainWindow;
class QGPixmapLayer;
// STL
#include <vector>
// QT
#include <QColor>
#include <QPoint>
#include <QPixmap>

// Since Qt doesn't provide const_reverse_iterator the STL vector was kept.
// A solution using Qt's const_iterator is possible, but due to asymmetric 
// characteristic of iterators we chose to keep the code simple
// #include <QVector>

class QCursor;



/**
 * @class QGScribbleInteractor QGScribbleInteractor.h "QGScribbleInteractor.h"
 * @brief Interactor allowing the user to 'mouse draw' on a pixmap
 * layer.
 * 
 * Using this interactor the user can draw a set of pixels on top of a
 * pixmap layer. The color of the drawing is set when constructing
 * this interactor.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   December 2, 2002  17:38
 * @since  Qgar 2.1
 */
class QGScribbleInteractor

  : public QGAbstractDocViewerInteractor

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
 * @param main  A pointer to the main window.
 * @param layer A pointer to the layer to draw on.
 * @param color The color to draw with.
 */
  QGScribbleInteractor(QGMainWindow * main, 
		       QGPixmapLayer * layer,
		       const QColor& color);

/**
 * @brief Default constructor
 *
 * @param main     A pointer to the main window.
 * @param layer    A pointer to the layer to draw on.
 * @param colorIdx The index of the color to draw with.
 */
  QGScribbleInteractor(QGMainWindow * main, 
		       QGPixmapLayer * layer,
		       int colorIdx);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGScribbleInteractor();

//@}


/** @name QGInteractorIf Impl */
//        ===================
//@{

  virtual void activate();
  
  virtual void dismiss();

//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// The 'drawing cursor'.
  QCursor * _drawCursor;

  /// A pointer to the main window used to register created commands.
  QGMainWindow * _main;

  /// A pointer to the pixmap layer this class interacts with.  
  QGPixmapLayer * _pixLayer;

  /// 
  QColor _color;
  
  ///
  int _colorIdx;

  /// A vector storing the color index of the modified points.
  std::vector<int> _idxVect;

  /// A vector storing the position of the modified points.
  std::vector<QPoint> _pointVect;


/** @name Event Filter */
//        ============
//@{

/**
 * @brief The event filter catching all events occuring on the main
 * window.
 */
  QGEventRedirector<QGScribbleInteractor> * _normalFilter;


/**
 * @brief The function member to which all trapped events are
 * redirected.
 */
  bool normalStateFilter(QObject * obj, QEvent * event);

//@}


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

/**
 * @brief Draws a set of pixels on top of the layer and return the
 * image corresponding to the modified region.
 * 
 * The bounding rectangle of the vector of points is computed. The
 * part of the layer corresponding to that rectangle is cropped. The
 * points are then drawn on top, using for each the color index stored
 * in the colorVect vector. The position of the top left corner of the
 * modified area in the layer is return via the <i>position</i>
 * parameter.
 *
 * @return An image, part of the layer with the points drawn on top.
 *
 * @param ptVect    The position of the pixel to be drawn.
 * @param colorVect The color index for each pixel.
 * @param position  [out]The position of the modified area in the
 * original image.
 */
  QImage plotPoints(const std::vector<QPoint>& ptVect,
		    const std::vector<int>& colorVect,
		    QPoint& position) const;

    
/** @name Disabled */
//        ========
//@{

/**
 * @brief Disabled copy-constructor
 */
  QGScribbleInteractor(const QGScribbleInteractor&);

/**
 * @brief Disabled assignment operator
 */
  QGScribbleInteractor& operator=(const QGScribbleInteractor&);

//@}


// -------------------------------------------------------------------
}; // class QGScribbleInteractor


#endif /* __QGSCRIBBLEINTERACTOR_H_INCLUDED__ */
