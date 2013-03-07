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


#ifndef __QGUNDOABLECOMMANDIF_H_INCLUDED__
#define __QGUNDOABLECOMMANDIF_H_INCLUDED__


/**
 * @file     QGUndoableCommandIf.h
 * @brief    Header file of class QGUndoableCommandIf.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 30, 2002  17:09
 * @since    Qgar 2.1
 */


/* $Id: QGUndoableCommandIf.h,v 1.4 2005/07/13 16:30:29 masini Exp $ */



// QGUI
#include "QGCommandIf.h"



/**
 * @class QGUndoableCommandIf QGUndoableCommandIf.h "QGUndoableCommandIf.h"
 * @brief Interface of all reversible commands of the application.
 * 
 * <p>
 * This interface is implemented by all command that can be undone.
 * It defines the undo() function member, discarding all changes
 * implied by the execute().
 * </p>
 * <p>
 * It also defines a clone() function member as reversible commands
 * are to be managed by undo lists.
 * </p>
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 30, 2002  17:09
 * @since  Qgar 2.1
 */
class QGUndoableCommandIf

  : public QGCommandIf

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGUndoableCommandIf()
  {
    // VOID
  }

//@}



/** @name Transform */
//        =========
//@{

/**
 * @brief Undoes the actions performed by execute()
 */
  virtual void undo() = 0;

/**
 * @brief Duplicates this object
 *
 * @return A copy of this object.
 */ 
  virtual QGUndoableCommandIf * clone() const = 0;

//@}


// -------------------------------------------------------------------
}; // class QGUndoableCommandIf


#endif /* __QGUNDOABLECOMMANDIF_H_INCLUDED__ */
