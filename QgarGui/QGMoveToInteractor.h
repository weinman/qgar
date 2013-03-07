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


#ifndef __QGMOVETOINTERACTOR_H_INCLUDED__
#define __QGMOVETOINTERACTOR_H_INCLUDED__


/**
 * @file     QGMoveToInteractor.h
 * @brief    Header file of class QGMoveToInteractor
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     December 6, 2002  11:31
 * @since    Qgar 2.1
 */


/* $Id: QGMoveToInteractor.h,v 1.6 2005/07/13 16:30:28 masini Exp $ */



// QGUI
#include "QGAbstractDocViewerInteractor.h"
template<class T> class QGEventRedirector;
class QGMainWindow;
class QGMultiLayerDoc;
class QGPixmapLayer;
// QT
#include <QRect>
#include <QVector>
#include <QGraphicsPathItem>
class QGraphicsRectItem;
class QMenu;
class QCursor;
class QAction;


/**
 * @class QGMoveToInteractor QGMoveToInteractor.h "QGMoveToInteractor.h"
 * @brief Interactor copying a part of a pixmap layer to another.
 * 
 * <p>
 * This interactor allows the user to copy a rectangular portion of a
 * pixmap layer to another. For now, this interactor only works with
 * binary images (bitmaps). This move can only be perfomed between two
 * layers having the same size (same width and same height).
 * </p>
 * <p>
 * The portion is bounded by a rectangle. The initial pixmap part
 * enclosed in this rectangle is blanked while in the target layer
 * this zone is replaced by the result of a logical or performed
 * between the two layers.
 * </p>
 * <p>
 * This interactor proceeds in three steps or state:
 * <p>
 * <h3>Normal State:</h3>
 * This is the initial state of the interactor. In this mode, the user
 * can start the selection of a part of the layer to copy. The
 * selection starts when the user first clicks on the mouse left
 * button.<br>
 * This click will set the selection rectangle origin and will switch
 * the interactor into the 'drawing state'.
 * </p>
 * <p>
 * <h3>Drawing State</h3>
 * In this state the user defines the end point of the selection
 * rectangle. A preview of the rectangle is drawn between the origin
 * set in the normal state and the mouse cursor position. The user has
 * then two choices:
 * - Left-click: The user accepts the selection rectangle and the
 * interactor goes into 'selected state'.
 * - Right-click: The user discards any selection. The preview
 * rectangle is erased and the interactor goes into 'normal state'.
 * .
 * </p>
 * <p>
 * <h3>Selected State</h3>
 * In this state a selection rectangle is defined. 
 * - Pressing the left mouse button will discard the current selection
 *   and start a new one with the clicked point as origin. The
 *   interactor switching to 'normal state'.
 * - Right-clicking will cause a popup menu to appear. This popup menu
 *   allows the user to pick a valid destination among the open
 *   documents to perform the move, or to cancel the current
 *   selection. In both cases the interactor reverts to 'normal state'.
 * .
 * </p>
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   December 6, 2002  11:31
 * @since  Qgar 2.1
 *
 * @bug Bad refresh when a selection rectangle is drawn and user draws
 * another. This will be corrected later when storage for extra action
 * info will be provided.
 */
class QGMoveToInteractor

  : public QGAbstractDocViewerInteractor

{

  Q_OBJECT

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name Constructor */
//        ===========
//@{

/**
 * @brief Default constructor
 *
 * @param main  A pointer to the main window.
 * @param layer A pointer to the pixmap layer this class interacts
 * with.
 */
  QGMoveToInteractor(QGMainWindow * main, QGPixmapLayer * layer);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGMoveToInteractor();
//@}



/** @name QGInteractorIf Impl */
//        ===================
//@{

/**
 * @brief Sets up a new cursor and go to 'normal state'
 */
  virtual void activate();


/**
 * @brief Restore cursor and clean up.
 */
  virtual void dismiss();

//@}



// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// The current cursor.
  QCursor * _cursor;

  /// A vector to store Menu's actions
  QVector<QAction *> _actVec;

/** @name Event Filters */
//        =============
//@{

  /// Initial event filter.
  QGEventRedirector<QGMoveToInteractor> * _normalState;

  /// Filter used when the selection rectangle is being drawn.
  QGEventRedirector<QGMoveToInteractor> * _drawingState;

  /// Filter used when a selection rectangle is defined.
  QGEventRedirector<QGMoveToInteractor> * _selectState;

/**
 * @brief Event filter function member for the normal state.
 */
  bool normalStateFilter(QObject * obj, QEvent * event);


/**
 * @brief Event filter function member for the drawing state.
 */
  bool drawingStateFilter(QObject * obj, QEvent * event);


/**
 * @brief Event filter function member for the selected state.
 */
  bool selectStateFilter(QObject * obj, QEvent * event);

//@}


/**
 * @brief A popup menu listing all possible target to move the selected
 * image rectangle to.
 */
  QMenu * _docMenu;

  /// A pointer to the main window.
  QGMainWindow * _main;

  /// A pointer to the current document.
  QGMultiLayerDoc * _doc;

  /// A pointer to the vectorial layer this instance interacts with.
  QGPixmapLayer * _layer;

/** @name Selection Rectangle Coordinates. */
//        ================================
//@{

  /// The starting point of the selection.
  QPoint _selStartPoint;

  /// The end point of the selection rectangle.
  QPoint _selEndPoint;

  /// The selection rectangle.
  QRect _selRect;

  /// The selection rectangle item
  QGraphicsRectItem * _canvasRect;

  /// A pointer to a QGraphicsPathItem which is the selection rectangle
  QGraphicsPathItem * _path;
  
  /// The selection rectangle item
  QGraphicsPathItem * _tmpPath;

//@}


// -------------------------------------------------------------------
// P R O T E C T E D    S L O T S
// -------------------------------------------------------------------
protected slots:

/**
 * @brief Slot activated when the user picks up a destination for the
 * move in the popup menu.
 *
 * Since a selection is acquired and a destination is chosen, this
 * slot creates the appropriate commands to perform the move and
 * executes them.
 *
 * @param act The action of the destination picked in the popup menu.
 */
  void slotClicked(QAction * act);

/**
 * @brief Slot activated when while the user cancels the selection
 * using the popup menu.
 */
  void slotCancel(QAction *);



// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:


/**
 * @brief Draws a preview of the selection rectangle over the current
 * document.
 *
 * The preview is drawn using a painter with an XOR mode and is not
 * stored. Refreshing the view of the document will erase the preview.
 *
 * @param rect The rectangle to be drawn.
 */ 
  void drawRect(const QRect& rect);

 
/**
 * @brief Draws a preview of the selection rectangle over the current
 * document.
 *
 * <p>
 * The rectangle drawn is the one defined by #_selStartPoint and the
 * given point.
 * </p>
 * The preview is drawn using a painter with an XOR mode and is not
 * stored. Refreshing the view of the document will erase the preview.
 *
 * @param pt The destination of the rectangle.
 */ 
  void drawRect(const QPoint& pt);


/**
 * @brief Builds the popup menu.
 */
  void buildDocMenu();

/**
 * @brief Creates the required commands to perform the move and
 * executes them.
 *
 * Two commands are defined. The one that blanks the current document
 * part and the one replacing in the target image the selected area by
 * a merge of the target image and the current document.
 *
 * @param moveTarget The name of the document, target of the move.
 */
  void createAndExecuteCommand(const QString& moveTarget);


/** @name Disabled */
//        ========
//@{

/**
 * @brief Disabled copy-constructor
 */
  QGMoveToInteractor(const QGMoveToInteractor&);

/**
 * @brief Disabled assignment operator
 */
  QGMoveToInteractor& operator=(const QGMoveToInteractor&);

//@}


// -------------------------------------------------------------------
}; // class QGMoveToInteractor


#endif /* __QGMOVETOINTERACTOR_H_INCLUDED__ */
