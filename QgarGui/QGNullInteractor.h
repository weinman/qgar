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


#ifndef __QGNULLINTERACTOR_H_INCLUDED__
#define __QGNULLINTERACTOR_H_INCLUDED__


/**
 * @file     QGNullInteractor.h
 * @brief    Header file of class QGNullInteractor.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 30, 2002  18:36
 * @since    Qgar 2.1
 */


/* $Id: QGNullInteractor.h,v 1.4 2005/07/13 16:30:28 masini Exp $ */



// QGUI
#include <QGInteractorIf.h>



/**
 * @class QGNullInteractor QGNullInteractor.h "QGNullInteractor.h"
 * @brief Base interface for interactors.
 *
 * <p>
 * This interface must be implemented by all classes acting as
 * interactors in the application.
 * </p>
 * <p>
 * An interactor class defines objects that allow the user to
 * 'interact' with the application. Meaning objects that react upon
 * user input (keyboard, mouse...) and perform specific actions.<br>
 * An object allowing the user to draw on a widget using the mouse is
 * an example of interactor.
 * </p>
 * <p>
 * The purpose of this class is double:
 * -  It provides a structural asset by regrouping all interactors in
 *    a same inheritance tree.
 * - It offers a common way to set and revoke interactor via the
 *   activate() and dismiss() methods.
 * .
 * </p>
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 30, 2002  18:36
 * @since  Qgar 2.1.1
 */
class QGNullInteractor

  : public QGInteractorIf

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
  virtual ~QGNullInteractor() { }
//@}

/**
 * @brief Activate the interactor.
 *
 * Subclasses must make sure that their instances are idle until
 * this method is called.<br>
 * Once it is called, the interactor is considered active and can do
 * its job.
 */
  virtual void activate() {}

/**
 * @brief Dismisses the interactor.
 *
 * The interactor must stop acting upon user input. It also must also
 * revert to a 'clean' state. Restore cursor, close temporary files...
 *
 */
  virtual void dismiss() {}

// -------------------------------------------------------------------
}; // class QGNullInteractor


#endif /* __QGNULLINTERACTOR_H_INCLUDED__ */
