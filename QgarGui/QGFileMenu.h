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


#ifndef __QGFILEMENU_H_INCLUDED__
#define __QGFILEMENU_H_INCLUDED__


/**
 * @file     QGFileMenu.h
 * @brief    Header file of class QGFileMenu
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     September 27, 2002  10:02
 * @since    Qgar 2.1
 */


/* $Id: QGFileMenu.h,v 1.7 2005/07/13 16:30:27 masini Exp $ */



// QGUI
#include "QGMainWindowObserverIf.h"
#include "QGMenu.h"
class QGMainWindow;
class QGRecentFileMenu;
// STL
#include <vector>



/**
 * @class QGFileMenu QGFileMenu.h "QGFileMenu.h"
 * @brief The file image menu of a QGMainWindow.
 *
 * It implements the basic commands to Open/Close/Save files.<br>
 * This class is an Observer of QGMainWindow. This allows to
 * enable/disable commands when the application state is modified.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   September 27, 2002  10:02
 * @since  Qgar 2.1
 */
class QGFileMenu

  : public QGMenu,
    public QGMainWindowObserverIf
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
 * @param main A pointer to the parent QGMainWindow.
 */
  QGFileMenu(QGMainWindow * main);

//@}


/** @name Destructors */
//        ===========
//@{

/**
 * @brief Destructor
 */

  virtual ~QGFileMenu();

//@}



/** @name QGMainWindowObserverIf Impl */
//        ===========================
//@{

  virtual void mainWindowUpdated(int what);

//@}



// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// a reference to the window the menu is attached to
  QGMainWindow * _main;

  /// The QT id of the Recent files menu item.
  int _recentFileMenuID;

  /// The QAction of the Recent files menu item.
  QAction * _act;
  
/**
 * @brief the list of the IDs of all items that must be enabled
 * when a document is opened and disabled when no documents are
 * presents.
 */
  std::vector<int> _docItemIDs;

  /// Menu for reloading a recently opened document.
  QGRecentFileMenu * _recentFileMenu;


/** @name Mutators */
//        ========
//@{

/**
 * @brief creates the menu.
 */
  void buildMenu();

 protected:
/**
 * @brief Informs the menu on whether the main window is displaying a
 * document or not.
 *
 * This menu has a different appearence whether a document is being
 * displayed in the main window or not. This function member will
 * update it according to the given information.
 *
 * @param haveIt A flag set to true if the main window is diplaying a
 * document.
 */
  void setHaveDoc(bool haveIt);

//@}

// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

/** @name Disabled */
//        ========
//@{

/**
 * @brief Disabled copy-constructor
 */
  QGFileMenu(const QGFileMenu&);

/**
 * @brief Disabled assignment operator
 */
  QGFileMenu& operator=(const QGFileMenu&);

//@}

// -------------------------------------------------------------------
}; // class QGFileMenu


#endif /* __QGFILEMENU_H_INCLUDED__ */
