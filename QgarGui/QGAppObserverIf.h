/*---------------------------------------------------------------------*
 | Graphical user interface QgarGui                                    |
 | Copyright (C) 2003  Qgar Project, LORIA                             |
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


#ifndef __QGAPPOBSERVERIF_H_INCLUDED__
#define __QGAPPOBSERVERIF_H_INCLUDED__


/**
 * @file     QGAppObserverIf.h
 * @brief    Header file of class QGAppObserverIf
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     September 11, 2003  16:47
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete.
/* $Id: QGAppObserverIf.h,v 1.3 2005/07/13 16:30:26 masini Exp $ */



// STD
#include <string>



/**
 * @class QGAppObserverIf QGAppObserverIf.h
 * @brief Interface implemented by all class whishing to be notified
 * of the status of a launched extenal application.
 *
 * <p>
 * Classes implementing this interface can register themselves as
 * observers of a QGAppTracker instance.
 * </p>
 * <p>
 * Once registered, the instance will receive a notification when the
 * external application terminates and all the application output will
 * be forwarded to it.
 * </p>
 * 
 * @see QGAppTracker
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   September 11, 2003  16:47
 * @since  Qgar 2.1.1
 */
class QGAppObserverIf
{

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name Destructor */
//        ==========
//@{

  virtual ~QGAppObserverIf()
  {
    // VOID
  }

//@}

/**
 * @brief Function member called by a QGAppTracker instance when the
 * application is correctly started.
 */
  virtual void start() = 0;

/**
 * @brief Function member called by a QGAppTracker instance when the
 * application it monitors ends.
 */
  virtual void finish() = 0;

/**
 * @brief Function member called by a QGAppTracker instance when the
 * application it monitors could not be started.
 */
  virtual void startError() = 0;

/**
 * @brief Function member called by a QGAppTracker instance to forward
 * a line of the application output.
 */
  virtual void cmdLine(const std::string& line) = 0;

// -------------------------------------------------------------------
}; // class QGAppObserverIf


#endif /* __QGAPPOBSERVERIF_H_INCLUDED__ */

