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


#ifndef __QGMODIFYINTERACTOR_H_INCLUDED__
#define __QGMODIFYINTERACTOR_H_INCLUDED__


/**
 * @file   QGModifyInteractor.h
 * @brief  Header file of class QGModifyInteractor.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 14, 2002  14:41
 * @since  Qgar 2.1
 */


/* $Id: QGModifyInteractor.h,v 1.5 2005/07/13 16:30:28 masini Exp $ */



// QGUI
#include "QGAbstractDocViewerInteractor.h"
template<class T> class QGEventRedirector;
class QGMainWindow;
class QGVectorialLayer;
// STL
#include <vector>
// QT
class QCursor;
class QGraphicsItem;
class QGVectItem;



/**
 * @class QGModifyInteractor QGModifyInteractor.h "QGModifyInteractor.h"
 * @brief Interactor that move, resize or delete a vectorial item in a
 * vectorial layer.
 * 
 * This interactor defines four states:
 * <p>
 * <h3>Normal State:</h3>
 * This is the initial state of the interactor. In this mode, the user
 * can select a vectorial item from the layer by left-clicking on it.
 * Selecting an item will switch this interactor into 'selected state'.
 * </p>
 * <p>
 * <h3>Selected State:</h3>
 * In this state, an item has be selected. The selected item is
 * highlighted. 
 * - Hovering the mouse over the bounding box of the item
 *   will display a 'move' cursor. Left-clicking on the mouse while in
 *   the bounding box will switch this interactor into 'moving state'.
 * - Hovering the mouse over the edges of the bounding box of the item
 *   will display a 'resize' cursor whose orientation depends on the
 *   edge.Left-clicking on the mouse while over the edge of the
 *   boundig box will switch this interactor into 'resizing state'.
 * - Pressing the 'Del' key will delete the selected item and revert
 *   this interactor state to 'normal state'.
 * - Left-clicking outside of the item bounding box will deselect the
 *   item and switch this interactor into 'normal state'.
 * .
 * </p>
 * <p>
 * <h3>Moving State:</h3>
 * While in moving state, dragging the mouse will move the item
 * following the new mouse position.<br> 
 * Releasing the mouse will switch the interator into 'selected
 * state'.
 * </p>
 * <p>
 * <h3>Resizing State:</h3>
 * While in resizing state, dragging the mouse will resize the item
 * according to the direction set while clicking.<br>
 * Releasing the mouse will switch the interator into 'selected
 * state'.
 * </p>
 *
 * @todo Upgrade interactor so that it works no matter the zoom level.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 14, 2002  14:41
 * @since  Qgar 2.1
 */
class QGModifyInteractor

  : public QGAbstractDocViewerInteractor

{
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
 * @param layer A pointer to the vectorial layer this class interacts
 * with.
 */
  QGModifyInteractor(QGMainWindow * main, 
		     QGVectorialLayer * layer);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGModifyInteractor();
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

  /// The vectorial layer this interactor works with.
  QGVectorialLayer * _layer;

  /// A pointer to the main window.
  QGMainWindow * _main;


/** 
 * @brief Change the selected item.
 *
 * @param item The newly selected item.
 */
  void setSelectedItem(QGraphicsItem * item);


/** 
 * @brief Repaints the part of the layer corresponding to the bounding
 * rectangle of a given item.
 */
  void refreshItem(QGraphicsItem * item);



/** @name Accessors */
//        =========
//@{

/**
 * @brief Retrieve the selected item.
 *
 * @return A pointer to the selected item.
 */
  QGraphicsItem * selectedItem() const;
  
//@}


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:


/** @name Cursors */
//        =======
//@{

  /// The current cursor set.
  const QCursor * _cursor;

  /// The previous cursor.
  const QCursor * _oldCursor;

//@}



/** @name Event Filters */
//        =============
//@{

  /// Default initial filter.
  QGEventRedirector<QGModifyInteractor> * _normalFilter;

  /// Filter used when a vector item is selected.
  QGEventRedirector<QGModifyInteractor> * _selectedItemFilter;

  /// Filter used when a vector item is being moved.
  QGEventRedirector<QGModifyInteractor> * _moveFilter;

  /// Filter used when a vector item is being resized.
  QGEventRedirector<QGModifyInteractor> * _resizeFilter;

/**
 * @brief Event filter function member for the normal state.
 */
  bool normalStateFilter(QObject * obj, QEvent * evt);


/**
 * @brief Event filter function member for the selected state.
 */
  bool selectedItemStateFilter(QObject * obj, QEvent * evt);


/**
 * @brief Event filter function member for the move state.
 */
  bool moveStateFilter(QObject * obj, QEvent * evt);


/**
 * @brief Event filter function member for the resize state.
 */
  bool resizeStateFilter(QObject * obj, QEvent * evt);

//@}

  
  /// A pointer to the selected vector item
  QGraphicsItem * _selectedItem;


  /// Storage for the origin of a transformation.
  QPoint _origin;

  /// Storage for the last mouse pointer position
  QPoint _lastPos;

  /// The possible resize origins.
  enum ResizeType { TOP_LEFT, 
		    TOP_CENTER, 
		    TOP_RIGHT, 
		    CENTER_RIGHT, 
		    BOTTOM_RIGHT, 
		    BOTTOM_CENTER, 
		    BOTTOM_LEFT, 
		    CENTER_LEFT, 
		    NONE};

  /// The current resize type while resizing.
  ResizeType _resizeType;

  /// A copy of the selected item.
  QGraphicsItem * _copyItem;

  
/** @name Disabled */
//        ========
//@{

/**
 * @brief Disabled copy-constructor
 */
  QGModifyInteractor(const QGModifyInteractor&);

/**
 * @brief Disabled assignment operator
 */
  QGModifyInteractor& operator=(const QGModifyInteractor&);

//@}


// -------------------------------------------------------------------
}; // class QGModifyInteractor


#endif /* __QGMODIFYINTERACTOR_H_INCLUDED__ */
