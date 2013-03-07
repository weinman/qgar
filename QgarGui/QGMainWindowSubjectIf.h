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


#ifndef __QGMAINWINDOWSUBJECTIF_H_INCLUDED__
#define __QGMAINWINDOWSUBJECTIF_H_INCLUDED__


/**
 * @file     QGMainWindowSubjectIf.h
 * @brief    Header file of class QGMainWindowSubjectIf
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     September 30, 2002  18:26
 * @since    Qgar 2.1
 */


/* $Id: QGMainWindowSubjectIf.h,v 1.4 2005/07/13 16:30:28 masini Exp $ */



// QGUI
class QGMainWindowObserverIf;



/**
 * @class QGMainWindowSubjectIf QGMainWindowSubjectIf.h "QGMainWindowSubjectIf.h"
 * @brief QGMainWindow subject, part of an Observer pattern with
 *        QGMainWindowObserverIf.
 *
 * Observers monitoring that subject will be aware of changes in the
 * QGMainWindow instance.
 *
 * @see QGMainWindowSubjectIf
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   September 30, 2002  18:26
 * @since  Qgar 2.1
 */
class QGMainWindowSubjectIf
{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  enum Event {DOCUMENT_OPEN, DOCUMENT_CLOSED, CURRENT_DOC_CHANGED};

/** @name Destructors */
//        ===========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGMainWindowSubjectIf() {}

//@}


/** @name Transformation */
//        ==============
//@{

/**
 * @brief Regsiters a new observer for this subject.
 *
 * @param obs The observer to attach.
 */
  virtual void attach(QGMainWindowObserverIf * obs) = 0;

/**
 * @brief Removes an observer for this subject.
 *
 * @param obs The observer to detach.
 */
  virtual void detach(QGMainWindowObserverIf * obs) = 0;

/**
 * @brief Notifies all observer that a particular event has occured.
 *
 * @param what An info on the event that triggered the notification.
 */
  virtual void notify(Event what) = 0;

//@}


// -------------------------------------------------------------------
}; // class QGMainWindowSubjectIf



#endif /* __QGMAINWINDOWSUBJECTIF_H_INCLUDED__ */
