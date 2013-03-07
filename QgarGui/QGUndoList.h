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


#ifndef __QGUNDOLIST_H_INCLUDED__
#define __QGUNDOLIST_H_INCLUDED__


/**
 * @file     QGUndoList.h
 * @brief    Header file of class QGUndoList.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     November 4, 2002  15:48
 * @since    Qgar 2.1
 */


/* $Id: QGUndoList.h,v 1.5 2005/07/13 16:30:29 masini Exp $ */



// QGUI
#include "QGUndoSubjectIf.h"
class QGUndoableCommandIf;
class QGUndoObserverIf;
// STL
#include <vector>



/**
 * @class QGUndoList QGUndoList.h "QGUndoList.h"
 * @brief A list of reversible commands managing their undo/redo
 * status.
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 4, 2002  15:48
 * @since  Qgar 2.1
 */
class QGUndoList

  : public QGUndoSubjectIf

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name Constructor */
//        ===========
//@{

/**
 * @brief Default constructor
 *
 * @param depth The number of commands that can be stored.
 */
  QGUndoList(unsigned int depth);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGUndoList();
//@}


/** @name Access */
//        ======
//@{

/**
 * @brief Check if a reversible command is registered.
 * 
 * @return True if one or more command is registered.
 */
  bool hasUndo() const;


/**
 * @brief Check if there is a registered undone action, candidate to
 * be redone.
 *
 * @return true If there is a registered undone action.
 */
  bool hasRedo() const;

//@}


/** @name Transformation */
//        ==============
//@{

/**
 * @brief Deletes all registered commands.
 */
  void clear();


/**
 * @brief Undo the last registered command.
 */
  void undo();


/**
 * @brief Redo the last undone command.
 */
  void redo();


/**
 * @brief Registers a command in the undo list.
 *
 * @param cmd The command to register.
 */
  void registerCommand(const QGUndoableCommandIf& cmd);

//@}


/** @name QGUndoSubjectIf Impl */
//        ====================
//@{

  virtual void attach(QGUndoObserverIf * obs);

  virtual void detach(QGUndoObserverIf * obs);

  virtual void notify();

//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:
  
  /// The maximum number of commands that can be stored.
  unsigned int _depth;

  /// Vector storing the last performed actions.
  std::vector<QGUndoableCommandIf *> _cmdVect;

  /// Vector storing the last undone actions.
  std::vector<QGUndoableCommandIf *> _undoVect;


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  /// Deletes all command stored in _undoVect.
  void cleanUndoVect();


  /// Observer vector
  std::vector<QGUndoObserverIf *> _obsVect;
  

/** @name Disabled */
//        ========
//@{

/**
 * @brief Disabled copy-constructor
 */
  QGUndoList(const QGUndoList&);

/**
 * @brief Disabled assignment operator
 */
  QGUndoList& operator=(const QGUndoList&);

//@}


// -------------------------------------------------------------------
}; // class QGUndoList


#endif /* __QGUNDOLIST_H_INCLUDED__ */
