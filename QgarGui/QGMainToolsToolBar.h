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


#ifndef __QGMAINTOOLSTOOLBAR_H_INCLUDED__
#define __QGMAINTOOLSTOOLBAR_H_INCLUDED__


/**
 * @file     QGMainToolsToolBar.h
 * @brief    Header file of class QGMainToolsToolBar.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 11, 2002  09:09
 * @since    Qgar 2.1
 */


/* $Id: QGMainToolsToolBar.h,v 1.6 2005/07/13 16:30:28 masini Exp $ */



// QGUI
#include "QGMainWindowObserverIf.h"
#include "QGCommandToolBar.h"
class QGMainWindow;

// QT
class QToolButton;



/**
 * @class QGMainToolsToolBar QGMainToolsToolBar.h "QGMainToolsToolBar.h"
 * @brief Toolbar regrouping tools independent of the image type.
 *
 * This toolbar only holds a shortcut to the superimpose mode
 * feature. This feature allows the user to visualize another image on
 * top of the one currently displayed.
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 11, 2002  09:09
 * @since  Qgar 2.1
 */
class QGMainToolsToolBar

  : public QGCommandToolBar, 
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
 * @param parent A pointer to the main window that will become the
 * parent of this toolbar.
 * @param name A optional name for this widget.
 */
  QGMainToolsToolBar(QGMainWindow * parent, const char * name = 0);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGMainToolsToolBar();
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

/**
 * @brief Updates the state of the SI button when the document
 * displayed in the main window changes.
 */
  void updateSIAction();


  /// A pointer to the main window.
  QGMainWindow * _main;

  /// The superimpose mode button.
  QToolButton * _siButton;
  QAction * _siAction;

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
  QGMainToolsToolBar(const QGMainToolsToolBar&);


/**
 * @brief Disabled assignment operator
 */
  QGMainToolsToolBar& operator=(const QGMainToolsToolBar&);

//@}


// -------------------------------------------------------------------
}; // class QGMainToolsToolBar


#endif /* __QGMAINTOOLSTOOLBAR_H_INCLUDED__ */
