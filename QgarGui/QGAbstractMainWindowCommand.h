/*---------------------------------------------------------------------*
 | Library QgarLib, graphics analysis and recognition                  |
 | Copyright (C) 2002  Qgar Project, LORIA                             |
 |                                                                     |
 | This library is free software; you can redistribute it and/or       |
 | modify it under the terms of the GNU Lesser General Public          |
 | License version 2.1, as published by the Free Software Foundation.  |
 |                                                                     |
 | This library is distributed in the hope that it will be useful,     |
 | but WITHOUT ANY WARRANTY; without even the implied warranty of      |
 | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                |
 | See the GNU Lesser General Public License for more details.         |
 |                                                                     |
 | The GNU Lesser General Public License is included in the file       |
 | LICENSE.LGPL, in the root directory of the Qgar packaging. See      |
 | http://www.gnu.org/licenses/lgpl.html for the terms of the licence. |
 | To receive a paper copy, write to the Free Software Foundation,     |
 | Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.       |
 |                                                                     |
 | Contact Project Qgar for any information:                           |
 |   LORIA - équipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-lès-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/


#ifndef __QGABSTRACTMAINWINDOWCOMMAND_H_INCLUDED__
#define __QGABSTRACTMAINWINDOWCOMMAND_H_INCLUDED__


/**
 * @file     QGAbstractMainWindowCommand.h
 * @brief    Header file of class QGAbstractMainWindowCommand
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     September 26, 2002  11:27
 * @since    Qgar 2.1
 */


/* $Id: QGAbstractMainWindowCommand.h,v 1.6 2005/07/13 16:30:26 masini Exp $ */



// QGUI
#include "QGCommandIf.h"
class QGMainWindow;



/**
 * @brief Abstract Base class to all command having a QGMainWindow
 * instance as target.
 *
 * This class has mainly a structural purpose, regrouping all classes
 * implementing QGCommandIf with a QGMainWindow instance as target.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan
 * Rendek">Jan Rendek</a>
 * @date   September 26, 2002  11:27
 *
 * @since Qgar 2.1
 */
class QGAbstractMainWindowCommand

  : public QGCommandIf

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name Constructors */
//        ============
//@{

/**
 * @brief Empty Construtor.
 *
 * Builds a command with no target. Target will be set later using the
 * setTarget() function member.
 */
  QGAbstractMainWindowCommand();


/**
 * @brief Default Construtor
 *
 * @param target The QGMainWindow instance, target of this command
 */
  QGAbstractMainWindowCommand(QGMainWindow * target);


/**
 * @brief Copy-constructor
 */
  QGAbstractMainWindowCommand(const QGAbstractMainWindowCommand&);

//@}


/** @name Destructors */
//        ===========
//@{

  /**
   * @brief Destructor.
   */
  virtual ~QGAbstractMainWindowCommand();

//@}


/** @name Operators */
//        =========
//@{

/**
 * @brief Assignment operator
 */
  QGAbstractMainWindowCommand& 
  operator=(const QGAbstractMainWindowCommand&);

//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// The QGMainWindow instance, target of the command.
  QGMainWindow * _target;


/** @name Access */
//        ======
//@{

/**
 * @brief Acces the target instance
 *
 * @return the instance of QGMainWindow used as target
 */
  const QGMainWindow *  target() const;

//@}


/** @name Transformation */
//        ==============
//@{

/**
 * @brief Set the target instance
 *
 * @param target a pointer on the new target-to-be.
 */
  void setTarget(QGMainWindow * target);

//@}


// -------------------------------------------------------------------
}; // class QGAbstractMainWindowCommand


#endif /* __QGABSTRACTMAINWINDOWCOMMAND_H_INCLUDED__ */
