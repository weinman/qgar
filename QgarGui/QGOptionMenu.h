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


#ifndef __QGOPTIONMENU_H_INCLUDED__
#define __QGOPTIONMENU_H_INCLUDED__


/**
 * @file     QGOptionMenu.h
 * @brief    Header file of class QGOptionMenu
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 9, 2002  15:30
 * @since    Qgar 2.1
 */


/* $Id: QGOptionMenu.h,v 1.5 2005/07/13 16:30:28 masini Exp $ */



// QT
#include <QMenu>
// QGAR
#include "QGStyleMenu.h"

/**
 * @class QGOptionMenu QGOptionMenu.h "QGOptionMenu.h"
 * @brief Menu to tune the application options.
 * 
 * This menu contains only a submenu allowing the user to change the
 * style of the application widgets.
 * 
 * @see QGStyleMenu
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 9, 2002  15:30
 * @since  Qgar 2.1
 */
class QGOptionMenu

: public QMenu

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
 * @param parent An optional parent for this widget.
 * @param name   An optional name for this widget.
 */
  QGOptionMenu(QWidget * parent = 0, const char * name = 0);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGOptionMenu();
//@}



// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

/** 
 * @brief A menu allowing the user to set the widget style for the
 * application.
 */
  QMenu * _styleMenu;



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
  QGOptionMenu(const QGOptionMenu&);

/**
 * @brief Disabled assignment operator
 */
  QGOptionMenu& operator=(const QGOptionMenu&);


//@}


// -------------------------------------------------------------------
}; // class QGOptionMenu


#endif /* __QGOPTIONMENU_H_INCLUDED__ */
