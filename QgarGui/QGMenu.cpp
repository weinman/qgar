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
 * @file  QGMenu.cpp
 * @brief Implementation of class QGMenu.
 *
 * See file QGMenu.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   September 27, 2002  09:07
 * @since  Qgar 2.1
 */



// QGUI
#include "QGMenu.h"
#include "QGCommandIf.h"
// QT
#include "QGMenu.moc"

using namespace std;



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGMenu::QGMenu(QWidget * parent, const char * name)
  : QMenu(parent), _lastIdx(0)
{ 
  connectSelf();
}

// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

QGMenu::~QGMenu() 
{
  // Delete all commands held in _cmdVect 

  for (QVector<QGCommandIf *>::iterator it = _cmdVect.begin();
       it!= _cmdVect.end();
       ++it) { 

    delete *it; 
  }   

  // all actions held in _actVect
  for (QVector<QAction *>::iterator it = _actVect.begin();
       it!= _actVect.end();
       ++it){
    
    delete *it;
  }

}

// ---------------------------------------------------------------------
// T R A N S F O R M A T I O N
// ----------------------------------------------------------------------

void
QGMenu::connectSelf()
{
  QObject::connect(this, SIGNAL(triggered(QAction*)), this, SLOT(slotClicked(QAction*)));
}

// ----------------------------------------------------------------------

int 
QGMenu::registerCommand(QGCommandIf * command) 
{
  _cmdVect.push_back(command);

  // Get the last position
  return _lastIdx++;
}

// ----------------------------------------------------------------------

void 
QGMenu::insertSeparator()
{
  // Register an empty command to keep consistence
  // among action items and command items
  registerCommand(0);

  QAction *act = QMenu::addSeparator();

  // Store the separator action
  _actVect.push_back(act);
}

// ----------------------------------------------------------------------

int
QGMenu::insertMenuItem(QMenu* menu,
		       const QString& text,
		       const QKeySequence& accel)
{
  // Register a null command to keep consistence
  // among action items and command items
  int retval = registerCommand(0);

  QAction *act = new QAction(text, this);
  act->setMenu(menu);
  if (0 != accel) act->setShortcut(accel);

  _actVect.push_back(act);

  return retval;
}
		       

// ----------------------------------------------------------------------

int
QGMenu::insertCommandItem(QGCommandIf * command, 
			  const QString& text, 
			  const QKeySequence& accel)
{
  // Store command
  int retval = registerCommand(command);
  
  QAction * act = new QAction(text, this);
  if (0 != accel) act->setShortcut(accel);

  /// The command and the action vectores are related.
  /// This means a command and its correspondent action have
  /// (and MUST have) the same index.

  // Store the action
  _actVect.push_back(act);

  return retval;

}

// ----------------------------------------------------------------------

int
QGMenu::insertCommandItem(QGCommandIf * command,
			  const QIcon& icon,		
			  const QString& text,
			  const QKeySequence& accel) 
{
  // Store command
  int retval = registerCommand(command);
  
  QAction * act = new QAction(icon, text, this);
  if (0 != accel) act->setShortcut(accel);

  /// The command and the action vectors are related.
  /// This means a command and its correspondent action have
  /// (and MUST have) the same index.

  // Store the action
  _actVect.push_back(act);

  return retval;
}

// ----------------------------------------------------------------------

int 
QGMenu::insertCommandItem(QGCommandIf * command,
			  const QPixmap & pixmap,
			  const QKeySequence& accel)
{
  // Store command
  int retval = registerCommand(command);
  
  QAction * act = new QAction(this);
  if (0 != accel) act->setShortcut(accel);

  /// The command and the action vectores are related.
  /// This means a command and its correspondent action have
  /// (and MUST have) the same index.

  // Store the action
  _actVect.push_back(act);

  return retval;
}


// ----------------------------------------------------------------------

int
QGMenu::insertCommandItem(QGCommandIf * command,
			  const QIcon& icon,
			  const QPixmap& pixmap,
			  const QKeySequence& accel)
{
  // Store command
  int retval = registerCommand(command);
  
  QAction * act = new QAction(this);
  if (0 != accel) act->setShortcut(accel);
  act->setIcon(icon);

  /// The command and the action vectores are related.
  /// This means a command and its correspondent action have
  /// (and MUST have) the same index.

  // Store the action
  _actVect.push_back(act);

  return retval;
}


// ----------------------------------------------------------------------
QAction *
QGMenu::getAction(const int index) {

  return _actVect.at(index);
}

// ----------------------------------------------------------------------
int
QGMenu::numberOfActions() {
  
  return _actVect.size();
}

// ----------------------------------------------------------------------
void
QGMenu::enableAction(const int index, bool status) {

  _actVect[index]->setEnabled(status);
}

// ---------------------------------------------------------------------
// S L O T S
// ----------------------------------------------------------------------
void
QGMenu::slotClicked(QAction * ac) 
{
  // Check the Action received by the menu and execute the
  // correspondent command held in _cmdVect
  
  // Find the index
  int n = 0;

  QVector<QAction *>::iterator it = _actVect.begin();
  for(it; it != _actVect.end() ; it++)
  {
    // If the action is not in the vector, this is un unmapped
    // action from a submenu inserted. Ignore it.
    
    // If there is no command in the command vector 
    // (0 means null), does not execute it.
    if((*it==ac) && (_cmdVect[n] != 0)) _cmdVect[n]->execute();
    n++;
  }
}


// ----------------------------------------------------------------------

