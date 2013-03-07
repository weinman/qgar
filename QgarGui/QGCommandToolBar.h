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


#ifndef __QGCOMMANDTOOLBAR_H_INCLUDED__
#define __QGCOMMANDTOOLBAR_H_INCLUDED__


/**
 * @file     QGCommandToolBar.h
 * @brief    Header file of class QGCommandToolBar.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 8, 2002  17:05
 * @since    Qgar 2.1
 */


/* $Id: QGCommandToolBar.h,v 1.7 2005/07/13 16:30:27 masini Exp $ */



// QGUI
class QGCommandIf;
class QMainWindow;

// QT
#include <QVector>
#include <QToolBar>
#include <QButtonGroup>
class QAbstractButton;

/**
 * @class QGCommandToolBar QGCommandToolBar.h "QGCommandToolBar.h"
 * @brief Custom toolbar in which clicking on an item triggers the
 * execution an associated QGCommandIf instance.
 *
 * <p>
 * This class embeds the event handling logic needed for a toolbar
 * (ie. detect a mouse click on a toolbar item). It allows the
 * creation of toolbars where each item is directly associated with a
 * command (a QGCommandIf instance). Clicking on the item calls the
 * execute() function member of the associated command.
 * </p>
 * <p>
 * This class is the base class of almost all toolbars in the
 * QgarGui. Its aim is to weaken the dependency between user input
 * handling and the actions to be performed. Inheriting classes are
 * discharged of the event handling part and only have to specify
 * which button is to be used and what command it triggers
 * </p>
 * <p>
 * Internally, the QGCommandToolBar defines a QButtonGroup to group
 * all the button inserted via the insertCommandButton() and a vector
 * to store the associated command.<br>
 * The mapping between a button in the group and a command in the
 * vector is perfomed using the index of the button in the group,
 * which is the same as the associated command in the vector.<br>
 * <b>Caveat: </b>Buttons and command inserted via
 * insertCommandButton() are not supposed to be removed. Doing so would
 * lead to an undefined behavior of the toolbar.
 * </p>
 *
 * @warning Do not remove buttons inserted with the insertCommandButton().
 *
 * @see QGCommandIf 
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 8, 2002  17:05
 *
 * @since Qgar 2.1
 */
class QGCommandToolBar

  : public QToolBar
{

  Q_OBJECT

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name Constructors */
//        ============
//@{

/**
 * @brief Constructor.
 *
 * @param parent The parent window of this toolbar.
 * @param name   The name of the toolbar
 */
  QGCommandToolBar( QMainWindow * parent, const char * name = 0);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGCommandToolBar();

//@}



/**
 * @brief inserts a button in the toolbar. 
 *
 * Clicking on the button triggers the execution of the given command
 *
 * @param button A button to be inserted in the toolbar.
 * @param cmd    The command associated with the given button.
 *
 * @return The index of the button in the toolbar.
 */
  int insertCommandButton(QAbstractButton * button, QGCommandIf* cmd);
  int insertCommandAction(QAction * act, QGCommandIf* cmd);

/**
 * @brief Sets the exclusive behavior of the toggle buttons in the toolbar.
 *
 * If the exclusive mode is on and a toggle button is down, clicking on another
 * will set the first up triggering the associated command before executing
 * the second one.
 *
 * @param exclusive TRUE if the exclusive behavior is to be set, FALSE otherwise.
 */
  void setExclusiveToggleButtons(bool exclusive);



// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /**
   * @brief Group of all buttons having an associated QGCommandIf instance.
   */
  QButtonGroup * _buttonGroup;

  /**
   * @brief The QVector storing all the QGCommandIf.
   */
  QVector<QGCommandIf *> _cmdVect;

  /**
   * @brief The QVector storing all the QActions.
   */
  QVector<QAction *> _actVect;

// -------------------------------------------------------------------
// P R O T E C T E D   S L O T   M E M B E R S
// -------------------------------------------------------------------

protected slots:

/**
 * @brief Callback called when a button having an associated command is clicked.
 *
 * This method is automatically called whenever a button inserted in
 * the toolbar using the insertCommandAction() method is clicked. This
 * method will execute the associated command (calling the QGCommandIf
 * instance's execute() function member).
 *
 * @param act The action associated to the command.
 */
  void slotClicked(QAction * act);


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:


/** @name Disabled */
//        ========
//@{

/**
 * @brief Copy-constructor
 */
  QGCommandToolBar(const QGCommandToolBar&);


/**
 * @brief Assignment operator
 */
  QGCommandToolBar& operator=(const QGCommandToolBar&);

//@}


// -------------------------------------------------------------------

}; // class QGCommandToolBar


#endif /* __QGCOMMANDTOOLBAR_H_INCLUDED__ */
