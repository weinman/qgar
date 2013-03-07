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


#ifndef __QGVIEWMENU_H_INCLUDED__
#define __QGVIEWMENU_H_INCLUDED__


/**
 * @file     QGViewMenu.h
 * @brief    Header file of class QGViewMenu.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 9, 2002  18:26
 * @since    Qgar 2.1
 */


/* $Id: QGViewMenu.h,v 1.5 2005/07/13 16:30:29 masini Exp $ */



// QGUI
#include "QGMenu.h"
class QWidget;
// QT
#include <QVector>



/**
 * @class QGViewMenu QGViewMenu.h "QGViewMenu.h"
 * @brief A menu to hide/show a set of registered widgets.
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 9, 2002  18:26
 * @since  Qgar 2.1
 */
class QGViewMenu

  : public QGMenu

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
 * @param parent The parent widget for this menu
 * @param name   An optional name for this widget.
 */
  QGViewMenu(QWidget * parent = 0, const char * name = 0);

//@}



/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGViewMenu();

//@}


/** @name Transformation */
//        ==============
//@{

  /**
   * @brief Add a widget that will be hidden/shown using this menu.
   *
   * Once a widget is registered, a new menu item corresponding to it
   * is added in the menu. Checking or unchecking this item in the
   * menu will enable or disable the widget.
   *
   * @param widget The widget to be added.
   * @param name   The name of the widget in the menu.
   */
  void registerWidget(QWidget * widget, const char * name);

//@}


// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
protected slots:

/**
 * @brief Toggle a registered widget status (on or off).
 *
 * This slot is called when a menu item is updated. It will swich on
 * or off the widget corresponding to the menu item.
 *
 * @param param the index of the updated menu item.
 */
  void slotToggleWidget(QAction *);

// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// A vector containing all the pointers to the widgets.
  QVector<QWidget *> _widgetVect;

  /// A vector holding all widget actions.
  QVector<QAction *> _actVect;

  /// The last index assigned to a menu item.
  int _lastIdx;

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
  QGViewMenu(const QGViewMenu&);


/**
 * @brief Disabled assignment operator
 */
  QGViewMenu& operator=(const QGViewMenu&);

//@}


// -------------------------------------------------------------------
}; // class QGViewMenu


#endif /* __QGVIEWMENU_H_INCLUDED__ */
