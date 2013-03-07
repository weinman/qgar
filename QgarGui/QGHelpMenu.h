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


#ifndef __QGHELPMENU_H_INCLUDED__
#define __QGHELPMENU_H_INCLUDED__


/**
 * @file   QGHelpMenu.h
 * @brief  Header file of class QGHelpMenu.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 10, 2002  14:42
 * @since  Qgar 2.1
 */


/* $Id: QGHelpMenu.h,v 1.5 2005/07/13 16:30:27 masini Exp $ */

#include "QGMenu.h"

/**
 * @class QGHelpMenu QGHelpMenu.h "QGHelpMenu.h"
 * @brief Help menu to be inserted in a QGMainWindow.
 *
 * The Help menu has the following items:
 * - About...: Displays copyright notice.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 10, 2002  14:42
 * @since  Qgar 2.1
 */
class QGHelpMenu

  : public QGMenu

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:


/** @name Constructor */
//        ===========
//@{

/**
 * @brief Default constructor.
 *
 * @param parent The parent widget of this menu.
 * @param name   An optional name for this menu.
 */
  QGHelpMenu(QWidget * parent = 0, const char * name = 0);

//@}



/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGHelpMenu();
//@}



// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:



/** @name Disabled */
//        ========
//@{

/**
 * @brief Copy-constructor
 */
  QGHelpMenu(const QGHelpMenu&);


/**
 * @brief Assignment operator
 */
  QGHelpMenu& operator=(const QGHelpMenu&);


//@}


// -------------------------------------------------------------------
}; // class QGHelpMenu


#endif /* __QGHELPMENU_H_INCLUDED__ */
