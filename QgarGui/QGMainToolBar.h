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


#ifndef __QGMAINTOOLBAR_H_INCLUDED__
#define __QGMAINTOOLBAR_H_INCLUDED__


/**
 * @file     QGMainToolBar.h
 * @brief    Header file of class QGMainToolBar
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 8, 2002  17:51
 * @since    Qgar 2.1
 */


/* $Id: QGMainToolBar.h,v 1.5 2005/07/13 16:30:28 masini Exp $ */



// QGUI
#include "QGCommandToolBar.h"
#include "QGMainWindowObserverIf.h"
#include "QGUndoObserverIf.h"
class QAbstractButton;
class QGMultiLayerDoc;
class QGMainWindow;



/**
 * @class QGMainToolBar QGMainToolBar.h "QGMainToolBar.h"
 * @brief The main toolbar of a QGMainWindow instance.
 *
 * Currently instances of this toolbar offer the following functionalities:
 * - open a document
 * - save a document
 * - print a document
 * - quit the application
 * - zoom in/out the document
 * - undo/redo the last action performed
 * .
 * Some of these action can be disabled if there is no document being
 * displayed or no undo/redo is available. This is why this class
 * implements both QGMainWindowObserverIf and QGUndoObserver interfaces.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 8, 2002  17:51
 * @since  Qgar 2.1
 */
class QGMainToolBar

  : public QGCommandToolBar,
    public QGMainWindowObserverIf,
    public QGUndoObserverIf

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name Constructors */
//        ============
//@{


/**
 * @brief Constructor.
 *
 * @param parent A pointer to the main window that will become the
 * parent of this toolbar.
 * @param name An optional name for this widget.
 */
  QGMainToolBar(QGMainWindow * parent = 0, const char * name = 0);

//@}



/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGMainToolBar();

//@}



/** @name QGMainWindowObserverIf Impl */
//        ===========================
//@{

  virtual void mainWindowUpdated(int what);

//@}


/** @name QGUndoObserver Impl */
//        ===================
//@{

  virtual void undoChanged();
   
//@}



// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// A pointer to the instance of the main window.
  QGMainWindow * _main;


  /// Build  and initializes the toolbar
  void init();


/** 
 * @brief Vector of the IDs of the items that have to be disabled when no
 * document is being shown in the main window.
 */
  QVector<int> _docItemIDs;


/**
 * @brief Updates the widgets when a document is displayed in the main
 * window.
 *
 * This method is called to enable/disable all widget whose state
 * depends on the fact that a document is being displayed.
 *
 * @param on A flag indicating if a document is displayed in the main
 * window.
 */
  void setHaveDoc(bool on);




// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  /// An action opening a file.
  QAction * _actOpen;

  /// An action to perform a save file.
  QAction * _actSave;

  /// An action triggering the print dialog.
  QAction * _actPrint;

  /// An action quitting Qgar.
  QAction * _actQuit;

  /// An action for zooming in the image.
  QAction * _actZoomIn;

  /// An action for zooming out the image.
  QAction * _actZoomOut;

  /// An action triggering the undo of the last command performed.
  QAction * _actUndo;

  /// An action triggering the redo of the last command undone.
  QAction * _actRedo;

  /**
   * @brief A reference to the most recent open doc.
   * This reference is used to detach the instance from the
   * Undo observer list when the document changes or is closed
   */
  QGMultiLayerDoc * _lastDoc;

/**
 * @brief Enables/Disables the undo and redo buttons according to the
 * undo state.
 */
  void updateUndoRedo();


/** @name Disabled */
//        ========
//@{

/**
 * @brief Copy-constructor
 */
  QGMainToolBar(const QGMainToolBar&);

/**
 * @brief Assignment operator
 */
  QGMainToolBar& operator=(const QGMainToolBar&);


//@}



// -------------------------------------------------------------------
}; // class QGMainToolBar


#endif /* __QGMAINTOOLBAR_H_INCLUDED__ */
