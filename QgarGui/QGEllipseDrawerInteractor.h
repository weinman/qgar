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


#ifndef __QGELLIPSEDRAWERINTERACTOR_H_INCLUDED__
#define __QGELLIPSEDRAWERINTERACTOR_H_INCLUDED__


/**
 * @file   QGEllipseDrawerInteractor.h
 * @brief  Header file of class QGEllipseDrawerInteractor.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 12, 2002  17:20
 * @since  Qgar 2.1
 */


/* $Id: QGEllipseDrawerInteractor.h,v 1.5 2005/07/13 16:30:27 masini Exp $ */



// QGUI
#include "QGAbstractDocViewerInteractor.h"
template<class T> class QGEventRedirector;
class QGVectorialLayer;
class QGMainWindow;

// Qt
#include "QGraphicsPathItem"

/**
 * @class QGEllipseDrawerInteractor QGEllipseDrawerInteractor.h "QGEllipseDrawerInteractor.h"
 * @brief Interactor that draws a ellipse and insert it in a Vectorial
 * Layer.
 * 
 * <p>
 * This interactor allows the user to define an ellipse on a vectorial
 * layer. The ellipse is inserted via a QGInsertVectItem command.
 * </p>
 * <p>
 * The ellipse is drawn by trapping the user inputs, mouse clicks and
 * moves, on the main window document viewer. The drawing helpers
 * such as the bounding box of the ellipse are drawn on top of the
 * QGDocViewer widget using the XOR mode. This allows to draw and
 * erase them without refreshing the widget.
 * </p>
 * <p>
 * This interactor defines two states:
 * - <strong>Normal State: </strong><br>
 * The default state when it is activated. The interactor waits for
 * the user to fix one corner of the ellipse-to-be bounding box by
 * clicking on one point of the document. Fixing this corner will
 * automatically switch the interactor to the drawing state.
 * - <strong>Drawing State: </strong><br>
 * The user is to set the second corner of the ellipse bounding
 * box. Every mouse move draws the rectangle defined by the point set
 * in the previous phase and the current mouse pointer position. The
 * user cancel the current drawing by clicking on the right
 * mouse button or accept the drawn rectangle as the new ellipse
 * bounding box. If the drawing is cancelled, no action is performed
 * and the interactor goes into normal mode. If the drawing is
 * completed, the interactor creates a QGInsertVectItemCommand
 * instance with the defined ellipse, executes it and goes into normal
 * mode.
 * </p>
 *
 * @see QGInsertVectItemCommand
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 12, 2002  17:20
 * @since Qgar 2.1
 */
class QGEllipseDrawerInteractor

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
 * @param main  The main window displaying the working document.
 * @param layer The layer the ellipse is to be inserted in.
 */
  QGEllipseDrawerInteractor(QGMainWindow * main, QGVectorialLayer * layer);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGEllipseDrawerInteractor();
//@}



/** @name QGInteractorIf Impl */
//        ===================
//@{

/**
 * @brief Activate this interactor.
 *
 * On activation the application cursor is changed to display a pen
 * cursor and the interactor enters its normal mode.
 */
  virtual void activate();

/**
 * @brief Dismisses this interactor.
 *
 * Previous application cursor is restored.
 */
  virtual void dismiss();

//@}



// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// A pointer to the layer the defined ellipse will be inserted in.
  QGVectorialLayer * _layer;
  
  /// A pointer to the main window storing an displaying the document
  /// holding the layer.
  QGMainWindow * _main;



// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  /// Drawing cursor.
  const QCursor * _cursor;

  /// Start point of the ellipse bounding rectangle.
  QPoint _startPoint;

  /// End point of the ellispe bounding rectangle.
  QPoint _endPoint;

  /// A pointer to a QGraphicsPathItem which is the selection rectangle
  QGraphicsPathItem * _path;

  /// A pointer to the Ellipse being drawn
  QGraphicsEllipseItem * _ellipse;

/**
 * @brief Redirector trapping document viewer events while in normal
 * mode. 
 */
  QGEventRedirector<QGEllipseDrawerInteractor> * _normalFilter;


/**
 * @brief Redirector trapping document viewer events while in normal
 * mode. 
 */
  QGEventRedirector<QGEllipseDrawerInteractor> * _drawingFilter;


/**
 * @brief The event filter trapping the document viewer events used in
 * normal mode.
 */
  bool normalStateFilter(QObject * obj, QEvent * evt);

/**
 * @brief The event filter trapping the document viewer events used in
 * drawing mode.
 */
  bool drawingStateFilter(QObject * obj, QEvent * evt);

/**
 * @brief Draws the ellipse included in the rectangle defined by
 * #_startPoint and the point passed as parameter.
 *
 * param point The second corner of the ellipse bounding
 * rectangle. The first being _startPoint
 */
  void drawEllipse(const QPoint& point);


/**
 * @brief Create the command that insert the new ellipse in _layer.
 *
 * A QGInsertVectItemCommand is created, registered in the document
 * undo list and executed.
 */
  void createAndExecuteCommand();
  


/** @name Disabled */
//        ========
//@{

/**
 * @brief Copy-constructor
 */
  QGEllipseDrawerInteractor(const QGEllipseDrawerInteractor&);

/**
 * @brief Assignment operator
 */
  QGEllipseDrawerInteractor& operator=(const QGEllipseDrawerInteractor&);

//@}

// -------------------------------------------------------------------
}; // class QGEllipseDrawerInteractor


#endif /* __QGELLIPSEDRAWERINTERACTOR_H_INCLUDED__ */
