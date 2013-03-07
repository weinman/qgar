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


#ifndef __QGPOLYLINEDRAWERINTERACTOR_H_INCLUDED__
#define __QGPOLYLINEDRAWERINTERACTOR_H_INCLUDED__


/**
 * @file   QGPolylineDrawerInteractor.h
 * @brief  Header file of class QGPolylineDrawerInteractor
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 12, 2002  11:38
 * @since  Qgar 2.1
 */


/* $Id: QGPolylineDrawerInteractor.h,v 1.4 2005/07/13 16:30:28 masini Exp $ */



// QGUI
#include "QGAbstractDocViewerInteractor.h"
template<class T> class QGEventRedirector;
class QGMainWindow;
class QGVectorialLayer;
// STL
#include <vector>
// QT
#include <QPoint>
#include <QCursor>
#include <QMouseEvent>
#include <QGraphicsPathItem>
#include <QPainterPath>

/**
 * @class QGPolylineDrawerInteractor QGPolylineDrawerInteractor.h "QGPolylineDrawerInteractor.h"
 * @brief Interactor drawing a new polyline in a vectorial layer.
 *
 * <p>
 * This interactor allows the user to create a new polyline in a
 * vectorial layer.
 * </p>
 * <p>
 * The polyline is drawn by trapping the user inputs, mouse clicks and
 * moves, on the main window document viewer. A preview of the
 * polyline is drawn while the user defines the polyline.
 * </p>
 * <p>
 * This interactor has two different states:
 * <p>
 * <h3>Normal state</h3>
 * In this state, the user can fix the starting point of the new
 * polyline. Left clicking will set that point and switch this
 * interactor into 'drawing state'.
 * </p>
 * <p>
 * <h3>Drawing state</h3>
 * In this state the user can:
 * - Set another point part of the polyline using the mouse left
 *   button.
 * - Finish the polyline an insert it in the active layer using the
 *   mouse middle button.
 * - Cancel the current drawing using the mouse right button.
 * .
 * In all these cases, the interactro reverts to 'normal mode'.
 * </p>
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 12, 2002  11:38
 * @since  Qgar 2.1
 */
class QGPolylineDrawerInteractor

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
 * @param layer A pointer to the vectorial layer to interact with.
 */
  QGPolylineDrawerInteractor(QGMainWindow * main, 
			     QGVectorialLayer * layer);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGPolylineDrawerInteractor();
//@}



/** @name QGInteractorIf impl */
//        ===================
//@{

/**
 * @brief Sets up this interactor default cursor and enter 'normal
 * state'.
 */
  virtual void activate();

/**
 * @brief Restore previous cursor and clean up.
 */
  virtual void dismiss();

//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// A pointer to the vectorial layer to draw a polyline in.
  QGVectorialLayer * _layer;

  /// A pointer to the main window.
  QGMainWindow * _main;

  void createAndExecuteCommand();

  /// This interactor default cursor.
  const QCursor * _cursor;


/** @name Polyline Coordinates */
//        ====================
//@{

  /// The polyline origin.
  QPoint _startPoint;

  /// The polyline end point.
  QPoint _endPoint;

  /// A vector containing all the points forming the polyline.
  std::vector<QPoint> _pointVect;

  /// A pointer to the Ellipse being drawn
  QGraphicsPathItem * _polyline;

//@}



/** @name Event Filters */
//        =============
//@{

  /// Initial event filter.
  QGEventRedirector<QGPolylineDrawerInteractor> * _normalFilter;

  /// Event filter used when the polyline is being drawn.
  QGEventRedirector<QGPolylineDrawerInteractor> * _drawingFilter;

  /// Event function member for the normal state.
  bool normalStateFilter(QObject * obj, QEvent * evt);

  /// Event function member for the drawing.
  bool drawingStateFilter(QObject * obj, QEvent * evt);
  
  void drawLine(const QPoint& point);

//@}


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
  QGPolylineDrawerInteractor(const QGPolylineDrawerInteractor&);

/**
 * @brief Assignment operator
 */
  QGPolylineDrawerInteractor& operator=(const QGPolylineDrawerInteractor&);

//@}


// -------------------------------------------------------------------
}; // class QGPolylineDrawerInteractor


#endif /* __QGPOLYLINEDRAWERINTERACTOR_H_INCLUDED__ */
