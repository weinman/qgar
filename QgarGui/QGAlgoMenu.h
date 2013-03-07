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


#ifndef __QGALGOMENU_H_INCLUDED__
#define __QGALGOMENU_H_INCLUDED__


/**
 * @file   QGAlgoMenu.h
 * @brief  Header file of class QGAlgoMenu
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Vitor Vasconcelos">Vitor Vasconcelos</a>
 * @date   October 3, 2002  16:37
 * @since  Qgar 2.1
 */


/* $Id: QGAlgoMenu.h,v 1.6 2005/07/13 16:30:28 masini Exp $ */



// QGUI
class QGMainWindow;
#include "QGMainWindowObserverIf.h"
#include "QGMenu.h"
#include "QGLaunchBatchCommand.h"
#include "QGAlgoMenuFactory.h"
#include "QGLayerIf.h"

// QT
#include <QStringList>
#include <QVector>
#include <QAction>

/**
 * @class QGAlgoMenu QGAlgoMenu.h "QGAlgoMenu.h"
 * @brief Creates a menu to navigate between all open documents.
 * 
 * <p>
 * This menu displays all algorithms related to the type of opened document.
 * </p>
 * <p>
 * This class is a QGMainWindow observer to update itself when
 * documents are open or closed. It therefore implements the
 * QGMainWindowObserverIf interface.
 * </p>
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Vitor Vasconcelos">Vitor Vasconcelos</a>
 * @date   June 2, 2008  15:50
 * @since  Qgar 3.1
 */
class QGAlgoMenu

  : public QMenu, 
    public QGMainWindowObserverIf
{

  Q_OBJECT

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name Constructors */
//        ============
//@{

/**
 * @brief Default constructor.
 *
 * @param main The parent window of this menu.
 */
  QGAlgoMenu(QGMainWindow * main);

//@}



/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGAlgoMenu();

//@}



/** @name TRANSFORMATIONS */
//        ===============
//@{

  /**
   * @brief Updates the menu.
   * 
   * The list of open documents is queried and the menu is update accordingly.
   */
  void update();

//@}



/** @name QGMainWindowObserverIf Impl */
//        ===========================
//@{

  virtual void mainWindowUpdated(int what);

//@}



// -------------------------------------------------------------------
// P U B L I C    S L O T S   M E M B E R S
// -------------------------------------------------------------------
protected slots:

/**
 * @brief Open the selected document in the Main Window.
 * 
 * @param act The Action performed by the Menu Bar item.
 */
  void slotClicked(QAction * act);



// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// Reference to the main window.
  QGMainWindow * _main;

  // Brief typedef
  typedef QVector< pair<QAction*, QGLaunchBatchCommand*> > actionVector;

  /// The map of actions and commands    
  actionVector _actVec;

  /**
   * @brief This connects the signals generated by this menu to its
   * slotClicked() function member.
   */
  void connectSelf();
  
  

// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:


/**
 * @brief Creates the menu and bind the different events
 */
  void init();

/**
 * @brief Cleans the map binding actions and commands
 */
  void cleanMap();

/** @name Disabled */
//        ========
//@{

/**
 * @brief Disabled copy-constructor
 */
  QGAlgoMenu(const QGAlgoMenu&);


/**
 * @brief Disabled assignment operator
 */
  QGAlgoMenu& operator=(const QGAlgoMenu&);

//@}


// -------------------------------------------------------------------

}; // class QGAlgoMenu


#endif /* __QGALGOMENU_H_INCLUDED__ */
