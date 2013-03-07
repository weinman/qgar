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


#ifndef __QGMAINWINDOWOBSERVERIF_H_INCLUDED__
#define __QGMAINWINDOWOBSERVERIF_H_INCLUDED__


/**
 * @file     QGMainWindowObserverIf.h
 * @brief    Header file of class QGMainWindowObserverIf
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     September 30, 2002  17:46
 * @since    Qgar 2.1
 */


/* $Id: QGMainWindowObserverIf.h,v 1.4 2005/07/13 16:30:28 masini Exp $ */



/**
 * @class QGMainWindowObserverIf QGMainWindowObserverIf.h "QGMainWindowObserverIf.h"
 * @brief Observer interface for a QGMainWindowSubject.
 *
 * @see QGMainWindowSubjectIf
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   September 30, 2002  17:46
 * @since  Qgar 2.1
 */
class QGMainWindowObserverIf
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
  virtual ~QGMainWindowObserverIf() {}

//@}


/** @name Transformation */
//        ==============
//@{

/**
 * @brief Callback method used to be notified from
 * a QGMainWindowSubject interface.
 *
 * @param what an int used to distinguish the kind of event
 * that caused the update.
 */
  virtual void mainWindowUpdated(int what) = 0;

//@}

// -------------------------------------------------------------------
}; // class QGMainWindowObserverIf


#endif /* __QGMAINWINDOWOBSERVERIF_H_INCLUDED__ */
