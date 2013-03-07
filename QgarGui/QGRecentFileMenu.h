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


#ifndef __QGRECENTFILEMENU_H_INCLUDED__
#define __QGRECENTFILEMENU_H_INCLUDED__


/**
 * @file   QGRecentFileMenu.h
 * @brief  Header file of class QGRecentFileMenu
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 1, 2002  10:08
 * @since  Qgar 2.1
 */


/* $Id: QGRecentFileMenu.h,v 1.7 2005/07/13 16:30:28 masini Exp $ */



// QT
#include <QMenu>
#include <QStringList>
// QGUI
#include "QGMainWindowObserverIf.h"
class QGMainWindow;



/**
 * @class QGRecentFileMenu QGRecentFileMenu.h "QGRecentFileMenu.h"
 * @brief A menu allowing quick access to a recent open document.
 *
 * <p>
 * This menu keeps track of the last N opened document, where N is set
 * on creation. A menu item is created for each of these
 * documents. Clicking on this item will cause the main window to
 * display the selected document.
 * </p>
 * <p>
 * This menu is an observer of the QGMainWindow (it implements the
 * QGMainWindow interface) to update itself when documents are closed
 * or new document open.
 * </p>
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 1, 2002  10:08
 * @since  Qgar 2.1
 */
class QGRecentFileMenu

  : public QMenu,
    public QGMainWindowObserverIf
{

  Q_OBJECT

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /// The default list size.
  static const unsigned int DEFAULT_SIZE;


/** @name Constructors */
//        ============
//@{


/**
 * @brief Creates a recent files menu with a given size.
 *
 * @param main A pointer to the main window.
 * @param size The number of item this menu can contain.
 */
  QGRecentFileMenu(QGMainWindow * main, 
		   unsigned int size = DEFAULT_SIZE);

//@}



/** @name Destructors */
//        ===========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGRecentFileMenu();

//@}



/** @name Access */
//        ======
//@{

/**
 * @brief Retrieve the maximum number of documents stored.
 *
 * @return The maximum number of documents stored.
 */
  int getListMaxSize() const;

//@}



/** @name Transformation */
//        ==============
//@{


/**
 * @brief Inserts a new document in the menu.
 *
 * @param docName The name of the document.
 */
  void insertDoc(const QString& docName);


//@}



/** @name QGMainWindowObserverIf  Impl */
//        ============================
//@{

  virtual void mainWindowUpdated(int what);

//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// The maximum size of the document list.
  unsigned int _listMaxSize;

  /// A pointer to the Main Window.
  QGMainWindow * _main;

  /// The list of recently open files
  QStringList _fileList;

  /// The vector of QActions related to opened files
  QList<QAction*> _actList;

  /**
   * @brief Creates the menu and bind the different events.
   */
  void init();

  /**
   * @brief Connects the SIGNALS from the menu to the appropriate
   * slots.
   */
  void connectSelf();

// -------------------------------------------------------------------
// P R O T E C T E D   S L O T    M E M B E R S
// -------------------------------------------------------------------
protected slots:

/**
 * Open the selected document in the Main Window.
 *
 * @param action The QAction* of the menu item
 */
  void slotClicked(QAction * action);


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:


/** @name Disabled */
//        ========
//@{

/**
 * @brief Copy constructor.
 */
  QGRecentFileMenu(const QGRecentFileMenu&);

/**
 * @brief Assignment operator
 */
  QGRecentFileMenu& operator=(const QGRecentFileMenu&);

//@}


// -------------------------------------------------------------------
}; // class QGRecentFileMenu


#endif /* __QGRECENTFILEMENU_H_INCLUDED__ */
