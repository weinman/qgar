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


#ifndef __QGCOMMANDIF_H_INCLUDED__
#define __QGCOMMANDIF_H_INCLUDED__

#include <QObject>

/**
 * @file     QGCommandIf.h
 * @brief    Header file of class QGCommandIf.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     September 26, 2002  11:07
 * @since Qgar 2.1
 */


/* $Id: QGCommandIf.h,v 1.7 2005/07/13 16:30:27 masini Exp $ */


/**
 * @class QGCommandIf QGCommandIf.h
 * @brief Base interface of all commands in QGarGui. Direct
 * implementation of the pattern of the same name.
 * 
 * <p>
 * This is the base class of all commands. A Command provides an
 * indirection level between a user action and the real action
 * performed by the command target. 
 * </p>
 * <p>
 * A command consists mainly on a target and a action to perform on
 * it. The action is performed in the execute() function member.
 * </p>
 * <p>
 * This interface has two purposes:
 * - Decouple the GUI widget and user input from the core of the
 * application. Application main classes such as QGMainWindow are
 * freed of user input handling, like handling a filechooser for
 * instance.
 * - Provide an indirection level useful to deal with
 * non-stateless commands. State data can be stored in the command
 * instance
 * .
 *
 * A template sub-class, QGSimpleCommand, is provided to generate
 * simple commands. By simple command, we mean, classes implementing
 * QGCommandIf where the execute() body consists only in calling a
 * target's method that takes no parameters.
 * <p>
 * This interface is the direct implementation of the Command pattern
 * described in <i>Design Patterns, Gamma & al, Addisson-Wesley 1994</i>
 * </p>
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan
 * Rendek">Jan Rendek</a>
 * @date   September 26, 2002  11:07
 *
 * @since Qgar 2.1
 */
class QGCommandIf {

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name Destructor */
//        ==========
//@{

  /**
   * @brief Destructor.
   */
  virtual ~QGCommandIf()
  {
    // VOID
  }

//@}

/**
 * @brief Performs the command.
 */
  virtual void execute() = 0;

// -------------------------------------------------------------------
}; // class QGCommandIf


#endif /* __QGCOMMANDIF_H_INCLUDED__ */
