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


#ifndef __QGSIMPLECOMMAND_H_INCLUDED__
#define __QGSIMPLECOMMAND_H_INCLUDED__


/**
 * @file     QGSimpleCommand.h
 * @brief    Header file of class QGSimpleCommand
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     September 27, 2002  14:45
 * @since    Qgar 2.1
 */


/* $Id: QGSimpleCommand.h,v 1.5 2005/07/13 16:30:29 masini Exp $ */



// QGUI
#include "QGCommandIf.h"


/**
 * @class QGSimpleCommand QGSimpleCommand.h "QGSimpleCommand.h"
 * @brief Simple command template (see Command Pattern [Gamma & al])
 *
 * <p>
 * This template generate simple commands. Simple commands are
 * stateless and their execution can be summarized to a mere function
 * call.
 * </p>
 * 
 * <p>
 * Usage:<br>
 * <code>
 * MyTarget* target = new MyTarget();
 * //..
 * QGCommandIf aCommand = new QGSimpleCommand<MyTarget>(target, &MyTarget::Action);
 * //...
 * aCommand->execute;
 * </code>
 * </p>
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   September 27, 2002  14:45
 * @since  Qgar 2.1
 */
template <class Target>
class QGSimpleCommand

  : public QGCommandIf

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  // Action is a pointer on a method of Target (no param, void return)
  typedef void (Target::* Action)();


/** @name Constructors */
//        ============
//@{

/**
 * @brief Default constructor
 *
 * @param target A pointer to the object that will perform the
 * action.
 * @param action A pointer on the function member of target to call
 * when the exectution is triggered.
 */
  QGSimpleCommand(Target * target, Action action)

    : _target(target), _action(action)

  {
    /* EMPTY */
  }

/**
 * @brief Copy-constructor
 */
  QGSimpleCommand(const QGSimpleCommand& other)

    : _target(other._target), _action(other._action)

  {
    /* EMPTY */
  }

//@} 
 

/** @name Destructor */
//        ==========
//@{

  /// Virtual destructor.
  virtual ~QGSimpleCommand() 
  {
    /* EMPTY */
  }

//@}





/** @name QGCommandIf Impl */
//        ================
//@{

/**
 * @brief Calls the _action function member on _target.
 */
  virtual void execute()
  {
    (_target->*_action)();
  }

//@}


/** @name Operators */
//        =========
//@{

/**
 * Assignment operator
 */
  QGSimpleCommand& operator=(const QGSimpleCommand& rhs)
  {
    if (this != &rhs)
      {
	_target = rhs._target;
	_action = rhs._action;
      }
  }

//@}


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// A pointer to the object that will perform the exectution.
  Target * _target;

  /// A pointer to the function member to execute.
  Action _action;
  
    
// -------------------------------------------------------------------
}; // class QGSimpleCommand


#endif /* __QGSIMPLECOMMAND_H_INCLUDED__ */
