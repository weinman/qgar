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


#ifndef __QGEDITMENU_H_INCLUDED__
#define __QGEDITMENU_H_INCLUDED__


/**
 * @file     QGEditMenu.h
 * @brief    Header file of class QGEditMenu
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 2, 2002  14:39
 * @since    Qgar 2.1
 */


/* $Id: QGEditMenu.h,v 1.6 2005/07/13 16:30:27 masini Exp $ */



// QGUI
#include "QGMenu.h"
#include "QGMainWindowObserverIf.h"

// QT
class QGMainWindow;
#include <QList>


/**
 * @class QGEditMenu QGEditMenu.h "QGEditMenu.h"
 * @brief A menu containing the standard edition commands (zoom, cut,
 * paste...).
 * 
 * This class defines the Edit menu included in each QGMainWindow
 * instance. The features this menu triggers are currently:
 * - zoom in  (QGZoomCommand).
 * - zoom out (QGZoomCommand).
 *
 * The menu registers as a Main Window observer in order to monitor
 * changes in the main window and update itself accordingly.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 2, 2002  14:39
 * @since Qgar 2.1
 */
class QGEditMenu

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
 * @param main A pointer to the main window this instance will be
 * attached to.
 */
  QGEditMenu(QGMainWindow * main);

//@}

/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGEditMenu();

//@}



/** @name QGMainWindowObserverIf Impl */
//        ===========================
//@{

/**
 * @brief Catches main window changes and enables/disables some menu
 * items accordingly.
 *
 * @param what The update type.
 */
  virtual void mainWindowUpdated(int what);

//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// A pointer to the main window this menu is attached to.
  QGMainWindow * _main;


/**
 * @brief the list of the IDs of all items that must be enabled
 * when a document is opened and disabled when no document is
 * present.
 */
  QVector<int> _docItemIDs;



/** @name Transformation */
//        ==============
//@{

/**
 * @brief Creates the buttons and commands instances and builds the
 * menu.
 */
  void buildMenu();

/**
 * @brief Updates the menu items according to the presence of a
 * displayed document.
 *
 * @param haveIt A flag that is true if the main window is currently
 * displaying a document, false otherwise.
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
  QGEditMenu(const QGEditMenu&);


/**
 * @brief Disabled assignment operator
 */
  QGEditMenu& operator=(const QGEditMenu&);

//@}



// -------------------------------------------------------------------
}; // class QGEditMenu


#endif /* __QGEDITMENU_H_INCLUDED__ */
