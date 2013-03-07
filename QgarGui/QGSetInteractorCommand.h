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


#ifndef __QGSETINTERACTORCOMMAND_H_INCLUDED__
#define __QGSETINTERACTORCOMMAND_H_INCLUDED__


/**
 * @file   QGSetInteractorCommand.h
 * @brief  Header file of class QGSetInteractorCommand
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 7, 2002  10:17
 * @since  Qgar 2.1
 */


/* $Id: QGSetInteractorCommand.h,v 1.4 2005/07/13 16:30:29 masini Exp $ */



// QGUI
#include "QGAbstractMainWindowCommand.h"
class QGInteractorIf;



/**
 * @class QGSetInteractorCommand QGSetInteractorCommand.h "QGSetInteractorCommand.h"
 * @brief Command setting a given interactor on a main window instance.
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 7, 2002  10:17
 * @since  Qgar 2.1
 */
class QGSetInteractorCommand

  : public QGAbstractMainWindowCommand

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
 * The created instance takes the ownership of the interactor passed
 * as parameter and will be responsible for its deletion.
 *
 * @param main      A pointer to the main window instance to set the
 * interactor on.
 * @param interact A pointer to the interactor to set.
 */
  QGSetInteractorCommand(QGMainWindow * main, QGInteractorIf * interact);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGSetInteractorCommand();
//@}




/** @name QGCommandIf Impl */
//        ================
//@{

  /// Sets the interactor on the main window.
  virtual void execute();

//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// A pointer to the interactor.
  QGInteractorIf * _interactor;
  


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
  QGSetInteractorCommand(const QGSetInteractorCommand&);

/**
 * @brief Disabled assignment operator
 */
  QGSetInteractorCommand& operator=(const QGSetInteractorCommand&);

//@}


// -------------------------------------------------------------------
}; // class QGSetInteractorCommand


#endif /* __QGSETINTERACTORCOMMAND_H_INCLUDED__ */
