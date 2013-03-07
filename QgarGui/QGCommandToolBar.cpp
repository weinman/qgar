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


/**
 * @file  QGCommandToolBar.cpp
 * @brief Implementation of class QGCommandToolBar
 *
 *        See file QGCommandToolBar.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 8, 2002  17:05
 */


// QT
#include <QMainWindow>
#include <QButtonGroup>
#include <QAbstractButton>

// QGUI
#include "QGCommandToolBar.h"
#include "QGCommandIf.h"
#include "QGCommandToolBar.moc"


// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGCommandToolBar::QGCommandToolBar(QMainWindow * parent, const char* name) 
  : QToolBar(name, parent)
{
  // Create the button group.
  _buttonGroup = new QButtonGroup(parent);
  

  // Connect the button group to the slotClick slot.
  //  QObject::connect(_buttonGroup,
  QObject::connect(this,
		   SIGNAL( actionTriggered(QAction *) ),
		   this,
		   SLOT( slotClicked(QAction *) ));
}



// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------

QGCommandToolBar::~QGCommandToolBar()
{
  //-- Delete each stored commands

  QVector<QGCommandIf *>::iterator it;
  for( it = _cmdVect.begin(); it != _cmdVect.end(); it++) {
    delete (*it);
  }

  
  //-- Delete Button Group.
  
  delete _buttonGroup;
}

// ---------------------------------------------------------------------
// T R A N S F O R M A T I O N
// ----------------------------------------------------------------------

int
QGCommandToolBar::insertCommandButton(QAbstractButton* button, QGCommandIf* cmd) 
{
  // Insert the command in the command vector.
  _cmdVect.push_back(cmd);

  // Keep pais indexes in both command vector and action vector
  _actVect.push_back(0);

  // Insert button in the button group and return its index..
  _buttonGroup->addButton(button);

  return _cmdVect.lastIndexOf(cmd);
}

// ----------------------------------------------------------------------
int
QGCommandToolBar::insertCommandAction(QAction* act, QGCommandIf* cmd) 
{
  // Indexes MUST be the same in both vectors.
  // Insert the command in the command vector.
  _cmdVect.push_back(cmd);

  // Insert the command in the command vector.
  _actVect.push_back(act);

  return _cmdVect.lastIndexOf(cmd);

}

// ----------------------------------------------------------------------


void 
QGCommandToolBar::setExclusiveToggleButtons(bool exclusive)
{
  _buttonGroup->setExclusive(exclusive);
}


// -------------------------------------------------------------------
// P R O T E C T E D     S L O T S 
// -------------------------------------------------------------------

void
QGCommandToolBar::slotClicked(QAction * act) 
{
  QVector<QAction *>::iterator it = _actVect.begin();
  int idx = 0;
  for(it; it != _actVect.end(); it++)
  {
    if (*it == act) _cmdVect[idx]->execute();
    idx++;
  }
}

// ----------------------------------------------------------------------

