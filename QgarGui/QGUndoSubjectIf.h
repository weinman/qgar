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


#ifndef __QGUNDOSUBJECTIF_H_INCLUDED__
#define __QGUNDOSUBJECTIF_H_INCLUDED__


/**
 * @file     QGUndoSubjectIf.h
 * @brief    Header file of class QGUndoSubjectIf.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     November 7, 2002  15:00
 * @since    Qgar 2.1
 */


/* $Id: QGUndoSubjectIf.h,v 1.4 2005/07/13 16:30:29 masini Exp $ */



// QGUI
class QGUndoObserverIf;



/**
 * @class QGUndoSubjectIf QGUndoSubjectIf.h "QGUndoSubjectIf.h"
 * @brief Interface proposing the undo subject to all classes wishing
 * to monitor the changes of a QGUndoList instance.
 *
 * Along with QGUndoObserverIf this interface forms an Observer
 * pattern. This pattern is used by clients wishing to be notified
 * when commands eligible for an undo or redo action appear.
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 7, 2002  15:00
 * @since  Qgar 2.1
 */
class QGUndoSubjectIf {

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
  virtual ~QGUndoSubjectIf()
  {
    // VOID
  }

//@}


/**
 * @brief Registers a new observer for this subject.
 *
 * @param obs The observer to be registered.
 */
  virtual void attach(QGUndoObserverIf * obs) = 0;

/**
 * @brief Removes an observer from the observer list.
 *
 * @param obs The observer to be removed.
 */
  virtual void detach(QGUndoObserverIf * obs) = 0;

/**
 * @brief Notifies all observers that the undo list has be modified.
 */
  virtual void notify() = 0;

// -------------------------------------------------------------------
}; // class QGUndoSubjectIf


#endif /* __QGUNDOSUBJECTIF_H_INCLUDED__ */
