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


#ifndef __QGLINEDRAWERINTERACTOR_H_INCLUDED__
#define __QGLINEDRAWERINTERACTOR_H_INCLUDED__


/**
 * @file     QGLineDrawerInteractor.h
 * @brief    Header file of class QGLineDrawerInteractor.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 30, 2002  19:05
 * @since    Qgar 2.1
 */


/* $Id: QGLineDrawerInteractor.h,v 1.7 2005/07/13 16:30:28 masini Exp $ */



// QGUI
#include "QGAbstractDocViewerInteractor.h"
#include "QGEventRedirector.h"
class QGMainWindow;
class QGMultiLayerDoc;
class QGVectorialLayer;
// QT
#include <QPoint>
#include <QGraphicsLineItem>

class QCursor;


/**
 * @class QGLineDrawerInteractor QGLineDrawerInteractor.h "QGLineDrawerInteractor.h"
 * @brief Interactor drawing a new segment in a vectorial layer.
 *
 * <p>
 * The aim of this interactor is to allow the user to define and
 * insert a new segment in a displayed vectorial layer.<br>
 * It assumes that the layer displayed in the QGDocViewer instance it
 * is attached to is a valid QGVectorialLayer object when it is activated.
 * </p>
 * <p>
 * The segment is drawn by trapping the user inputs, mouse clicks and
 * moves, on the main window document viewer. The drawing helpers
 * such as the segment preview are drawn on top of the QGDocViewer
 * widget using the XOR mode. This allows to draw and erase them
 * without refreshing the widget.
 * </p>
 * <p>
 * This interactor defines two states:<br>
 * <strong>Normal State: </strong><br>
 * The default state when it is activated. The interactor waits for
 * the user to fix the first point of the segment by clicking on one
 * point of the document. Fixing this point will automatically switch
 * the interactor to the drawing state.
 * </p>
 * <p>
 * <strong>Drawing State: </strong><br>
 * On mouse move, the interactor displays a preview of the segment
 * between the start point fixed in the previous state and the current
 * mouse position.<br>
 * The user can validate the second point by clicking on the left
 * mouse button. The point pointed by the mouse will be used as the
 * end point of the segmet.<br>
 * At any time, the user may cancel the current action by clicking on
 * the right mouse button.<br>
 * If the drawing is completed, a QGCanvasLine defined by the two
 * points is created and inserted in the layer. Else, nothing is
 * performed.<br>
 * The interactor goes into normal state once the drawing is either
 * complete or cancelled.
 * </p>
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 30, 2002  19:05
 * @since  Qgar 2.1
 */
class QGLineDrawerInteractor

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
 * @param main  The main window the instance interacts with.
 * @param layer The layer the created segment will be inserted in.
 */
  QGLineDrawerInteractor(QGMainWindow * main, 
			 QGVectorialLayer * layer);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGLineDrawerInteractor();
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

  /// A pointer to the layer the vector will be inserted in.
  QGVectorialLayer * _layer;

  /// A pointer to the main window displaying the layer.
  QGMainWindow * _main;


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  /// The cursor indicating that the interactor is active.
  const QCursor * _cursor;

  /// The starting point of the current segment.
  QPoint _startPoint;

  /// The ending point of the current segment.
  QPoint _endPoint;

  /// A pinter to the LineItem being drawn
  QGraphicsLineItem * _line;

/**
 * @brief The event filter redirecting events to the
 * normalStateFilter() function member while in normal state.
 */
  QGEventRedirector<QGLineDrawerInteractor> * _normalFilter;


/**
 * @brief The event filter redirecting events to the
 * drawingStateFilter() function member while in drawing state.
 */
  QGEventRedirector<QGLineDrawerInteractor> * _drawingFilter;
  

/**
 * @brief The method processing user event while in normal state.
 *
 * @param obj The object the event is originating from.
 * @param evt The event to be processed.
 */
  bool normalStateFilter(QObject * obj, QEvent * evt);


/**
 * @brief The method processing user event while in normal state.
 *
 * @param obj The object the event is originating from.
 * @param evt The event to be processed.
 */
  bool drawingStateFilter(QObject * obj, QEvent * evt);
  

/**
 * @brief The method drawing the segment preview.
 *
 * <p>
 * This method draws a preview of the segment using _startPoint as
 * origin and the given point as end.
 * </p>
 * <p>
 * The preview is drawn using XOR mode, hence two calls with the same
 * value will have no effect. The first one will draw the segment and
 * the second one erase it.
 * </p>
 *
 * @param point The end point of the segment.
 */
  void drawLine(const QPoint& point);


/**
 * @brief Creates the command that insert the segment defined by
 * _startPoint and _endPoint and executes it.
 */
  void createAndExecuteCommand();


  
/** @name Disabled */
//        ========
//@{

/**
 * @brief Disabled copy-constructor
 */
  QGLineDrawerInteractor(const QGLineDrawerInteractor&);

/**
 * @brief Disabled assignment operator
 */
  QGLineDrawerInteractor& operator=(const QGLineDrawerInteractor&);

//@}

// -------------------------------------------------------------------
}; // class QGLineDrawerInteractor


#endif /* __QGLINEDRAWERINTERACTOR_H_INCLUDED__ */
