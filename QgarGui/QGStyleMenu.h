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


#ifndef __QGSTYLEMENU_H_INCLUDED__
#define __QGSTYLEMENU_H_INCLUDED__


/**
 * @file     QGStyleMenu.h
 * @brief    Header file of class QGStyleMenu
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 9, 2002  14:28
 * @since    Qgar 2.1
 */


/* $Id: QGStyleMenu.h,v 1.4 2005/07/13 16:30:29 masini Exp $ */



// QT
#include <QMenu>
#include <QStringList>
#include <QAction>


/**
 * @class QGStyleMenu QGStyleMenu.h "QGStyleMenu.h"
 * @brief A menu allowing the user to change the look and feel of the
 * application.
 *
 * This menu list all the possible styles for the application. For
 * each a menuitem is created. Clicking on one will change the look
 * and feel of the application to match the user choice.
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 9, 2002  14:28
 * @since  Qgar 2.1
 */
class QGStyleMenu

  : public QMenu

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
  QGStyleMenu(QWidget * parent = 0, const char * name = 0 );

//@}



/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGStyleMenu();
//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// The list of the available widget styles.
  static const QStringList _styleList;

  /// Keep the id of the last menu item activated.
  QAction* _lastActionChecked;

  /// Hold the actions controling style items
  QVector<QAction *> _actVect;

// -------------------------------------------------------------------
// P R O T E C T E D   S L O T   M E M B E R S
// -------------------------------------------------------------------
protected slots:

/**
 * @brief Changes the widget style according to the style
 * corresponding to the item clicked.
 *
 * @param act The QAction * related to the menu item clicked.
 */
  void slotClicked(QAction *);


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
  QGStyleMenu(const QGStyleMenu&);

/**
 * @brief Disabled assignment operator
 */
  QGStyleMenu& operator=(const QGStyleMenu&);

//@}


// -------------------------------------------------------------------
}; // class QGStyleMenu


#endif /* __QGSTYLEMENU_H_INCLUDED__ */
