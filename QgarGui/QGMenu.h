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


#ifndef __QGMENU_H_INCLUDED__
#define __QGMENU_H_INCLUDED__


/**
 * @file   QGMenu.h
 * @brief  Header file of class QGMenu
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   September 26, 2002  16:59
 * @since  Qgar 2.1
 */


/* $Id: QGMenu.h,v 1.4 2005/07/13 16:30:28 masini Exp $ */



// QT
#include <QMenu>
#include <QAction>
#include <QVector>
// QGUI
class QGCommandIf;



/**
 * @class QGMenu QGMenu.h "QGMenu.h"
 * @brief Base class for command based menu.
 *
 * <p>
 * A QGMenu is a popup menu where command items are inserted. A
 * command item is a menu item that, when clicked, will trigger the
 * exectution of a command. A command is an instance of QGCommandIf.
 * </p>
 * <p>
 * The menu takes care of all of its events. There is therefore no
 * need to deal with signals or slots while using command items.
 * The menu takes the ownership of all inserted commands. These
 * commands will be deleted when the menu is destroyed.
 * </p>
 * <p>
 * Other menu items may be inserted normally as long as they are not
 * inserted with a positive ID. This class assignes positive IDs to
 * the command menu item so using such an ID without a command may
 * lead to a segmentation fault.
 * </p>
 * <p>
 * IMPORTANT:
 * The ID is no longer used. All inserted item or menu must have
 * a valid respective QAction. In the case of submenu objects with
 * their own slots, their actions you'll be ignored by the QGMenu 
 * object in charge of the menu.
 * </p>
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   September 26, 2002  16:59
 * @since  Qgar 2.1
 */
class QGMenu

  : public QMenu

{

  Q_OBJECT

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:


/** @name Constructor  */
//        ===========
//@{

/**
 * @brief Default constructor
 * 
 * @param parent The parent widget for this menu
 * @param name   An optional name for this widget.
 */
  QGMenu(QWidget * parent = 0, const char * name = 0);


//@}



/** @name Destructor  */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGMenu();

//@}

/**
 * @brief Inserts a separator, storing the action in the action QVector.
 */
  void insertSeparator();

/**
 * @brief Inserts a submenu to a menu.
 *
 * @param menu    The Menu reference associated with the menu item
 * @param text    The label of the menu item.
 * @param accel   An optional key accelerator for this item
 *
 * @return the ID assigned to the item
 * 
 */
  int insertMenuItem(QMenu* menu,
		      const QString& text,
		      const QKeySequence& accel = 0);
/**
 * @brief Inserts a command item with a label and an accelerator.
 *
 * @param command The command associated with the menu item
 * @param text    The label of the menu item.
 * @param accel   An optional key accelerator for this item
 *
 * @return the ID assigned to the item
 */
  int insertCommandItem(QGCommandIf * command, 
			const QString& text, 
			const QKeySequence& accel = 0);

  /**
   * @brief Inserts a command item with an icon, a text and an
   * accelerator.
   *
   * @param command The command associated with the menu item
   * @param icon    The icon of the menu item
   * @param text    The label of the menu item.
   * @param accel   An optional key accelerator for this item.
   *
   * @return the ID assigned to the item
   * @overload
   */
   int insertCommandItem(QGCommandIf * command, 
 			const QIcon& icon,		 
 			const QString& text, 
 			const QKeySequence& accel = 0); 

  
  /**
   * @brief The QGMenu is responsible for deleting the command.
   *
   * @param command The command associated with the menu item
   * @param pixmap  The pixmap associated with this menu item.
   * @param accel   An optional key accelerator for this item.
   *
   * @return the ID assigned to the item
   * @overload
   */
   int insertCommandItem(QGCommandIf * command, 
 			const QPixmap & pixmap, 
 			const QKeySequence& accel = 0);
  
  /**
   * @brief The QGMenu is responsible for deleting the command.
   *
   * @param command The command associated with the menu item
   * @param icon    The iconset of the menu item
   * @param pixmap  The pixmap for this menu item
   * @param accel   An optional key accelerator for this item.
   *
   * @return the ID assigned to the item
   * @overload
   */
   int insertCommandItem(QGCommandIf * command, 
 			const QIcon& icon, 
 			const QPixmap& pixmap, 
 			const QKeySequence& accel = 0); 


// -------------------------------------------------------------------
// P U B L I C   S L O T S   M E M B E R S
// -------------------------------------------------------------------
public slots:

  /**
   * @brief the slot catching the selected items
   *
   * @param the menu thrown QAction* 
   */
  void slotClicked(QAction *);

// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// The QVector storing the commands
  QVector<QGCommandIf *> _cmdVect;

  /// The action to associated to the menu
  QVector<QAction *> _actVect;

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
  QGMenu(const QGMenu&);


/**
 * @brief Disabled assignment operator
 */
  QGMenu& operator=(const QGMenu&);

//@}



  /// The idx of the last Command inserted in the menu
  int _lastIdx;

  /**
   * @brief Connect the instance 'slotClicked(QAction *)' to its own 
   * 'triggered(QAction *)' signal.
   */
  void connectSelf();

// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /**
   * @brief Store the commands in the QVector object.
   *
   * @param command The QGCommandIf* to be called by the menu action.
   */
  int registerCommand(QGCommandIf * command);

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /**
   * @brief Gets a stored QAction*.
   *
   * @param index of QAction* in the action QVector.
   */
  QAction * getAction(int);

  /**
   * @brief number of stored actions.
   * 
   */
  int numberOfActions();

  /**
   * @brief change a property of a stored QAction by calling 
   * setEnabled(bool).
   * 
   * @param index  QAction index in the QVector.
   * @param status Boolean to enable or disable the Action.
   */
  void enableAction(int index, bool status);

// -------------------------------------------------------------------


}; // class QGMenu


#endif /* __QGMENU_H_INCLUDED__ */
