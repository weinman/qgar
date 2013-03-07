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


#ifndef __QGVECTUTILITYBAR_H_INCLUDED__
#define __QGVECTUTILITYBAR_H_INCLUDED__


/**
 * @file     QGVectUtilityBar.h
 * @brief    Header file of class QGVectUtilityBar.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 28, 2002  15:13
 * @since    Qgar 2.1
 */


/* $Id: QGVectUtilityBar.h,v 1.4 2005/07/13 16:30:29 masini Exp $ */



// QGUI
#include "QGCommandToolBar.h"
class QGMainWindow;
// QT
class QToolButton;



/**
 * @class QGVectUtilityBar QGVectUtilityBar.h "QGVectUtilityBar.h"
 * @brief The utility toolbar common to all vectorial layers.
 *
 * This toolbar regroups two buttons, each triggering a command.
 * The embedded commands are:
 * - Turning on/off the skeleton view of the layer.
 * - Show/hide the window provinding information on the vectorial
 *   items.
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 28, 2002  15:13
 * @since  Qgar 2.1
 */
class QGVectUtilityBar

  : public QGCommandToolBar

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
 * @param parent A pointer to the main window, parent-to-be of this
 * toolbar.
 * @param name   An optional name for this toolbar.
 */
  QGVectUtilityBar(QGMainWindow * parent, const char * name = 0);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGVectUtilityBar();

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
  QGVectUtilityBar(const QGVectUtilityBar&);

/**
 * @brief Disabled assignment operator
 */
  QGVectUtilityBar& operator=(const QGVectUtilityBar&);

//@}

// -------------------------------------------------------------------
}; // class QGVectUtilityBar


#endif /* __QGVECTUTILITYBAR_H_INCLUDED__ */
