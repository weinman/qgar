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


#ifndef __QGIMAGEMENU_H_INCLUDED__
#define __QGIMAGEMENU_H_INCLUDED__


/**
 * @file   QGImageMenu.h
 * @brief  Header file of class QGImageMenu
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 3, 2002  16:37
 * @since  Qgar 2.1
 */


/* $Id: QGImageMenu.h,v 1.6 2005/07/13 16:30:28 masini Exp $ */



// QGUI
class QGMainWindow;
#include "QGMainWindowObserverIf.h"
// QT
#include <QStringList>
#include <QVector>
#include <QAction>
#include <QMenu>

/**
 * @class QGImageMenu QGImageMenu.h "QGImageMenu.h"
 * @brief Creates a menu to navigate between all open documents.
 * 
 * <p>
 * This menu displays all opened document in the application. For each
 * of these documents there is a menu item. Clicking on the item will cause the
 * main window to display the document.
 * </p>
 * <p>
 * This class also sets a key accelerator: the SPACE key.  Pressing
 * space will display the previous document viewed before the current
 * document in the main window.
 * </p> 
 * <p>
 * This class is a QGMainWindow observer to update itself when
 * documents are open or closed. It therefore implements the
 * QGMainWindowObserverIf interface.
 * </p>
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 3, 2002  16:37
 * @since  Qgar 2.1
 */
class QGImageMenu

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
  QGImageMenu(QGMainWindow * main);

  /**
   * @brief Lookup for the index of a menu action stored in the vector of actions 
   * knowing the name of the file it represents.
   *
   * @note This method is public due to previous graphical user interface
   * constraints imposed by Qt changes from version 3 to 4.
   *
   * @param filename The name of the document.
   *
   * @return The index of the menu action corresponding to the filename.
   */
  int findAction(const QString& filename) const;
  
  /**
   * @brief Set the enable property of aa stored action.
   *
   * @note This method is public due to previous graphical user interface
   * constraints imposed by Qt changes from version 3 to 4.
   *
   * @param idx The index of the stored action in the actions vector.
   *
   * @param value The boolean value to activate/deactivate the action.
   */
  void enableAction(int idx, bool value);
//@}



/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGImageMenu();

//@}



/** @name TRANSFORMATIONS */
//        ===============
//@{


  /**
   * @brief Insert a menu item with the givent image name in the menu.
   *
   * @param imageName The name of the image matching the menu item to insert in
   * the menu.
   */
  void insertImage(const QString& imageName);


  /**
   * @brief Removes the menu item corresponding to the document being
   * displayed.
   *
   * This method is called when the current document is closed.
   */
  void removeCurrentImage();
  

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

  /// The index of the current open document
  int _lastImgIdx;

  /// The id of the current open document
  int _currentImgIdx;

  /// The name of the previous image
  QString _lastImgName;

  /// The vector of actions
  QVector<QAction *> _actVect;

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
 * @brief Cleans the vector binding the different actions
 */
  void cleanActionVector();

/** @name Disabled */
//        ========
//@{

/**
 * @brief Disabled copy-constructor
 */
  QGImageMenu(const QGImageMenu&);


/**
 * @brief Disabled assignment operator
 */
  QGImageMenu& operator=(const QGImageMenu&);

//@}


// -------------------------------------------------------------------

}; // class QGImageMenu


#endif /* __QGIMAGEMENU_H_INCLUDED__ */
