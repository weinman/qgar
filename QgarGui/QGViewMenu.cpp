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
 * @file  QGViewMenu.cpp
 * @brief Implementation of class QGViewMenu.
 *
 * See file QGViewMenu.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 9, 2002  18:26
 * @since  Qgar 2.1
 */



// QGUI
#include "QGViewMenu.h"
#include "QGViewMenu.moc"


#include <iostream>


// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGViewMenu::QGViewMenu(QWidget* parent, const char* name ) 

  : QGMenu(parent, name)

{ 
  this->setTitle(tr("&View"));

   // Connect item with the slot that when click will toggle shown/hidden
  connect(this, SIGNAL(triggered(QAction *)), 
	  this, SLOT(slotToggleWidget(QAction *)));
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------

QGViewMenu::~QGViewMenu()
{
  // Destroy all actions related to widgets
  QVector<QAction *>::iterator it = _actVect.begin();
  for(it; it != _actVect.end(); it++)
  {
    delete *it;
  }
}

// ---------------------------------------------------------------------
// T R A N S F O R M A T I O N
// ----------------------------------------------------------------------

void
QGViewMenu::registerWidget(QWidget* widget, const char* name)
{
  // Create an associated Action to each widget to be inserted
  QAction * act;
 
  // Insert Item in the menu
  act = addAction(name);
  act->setCheckable(true);

  // If widget is visible, the corresponding item is checked
  act->setChecked(!widget->isHidden());

  // Store widget and the associated action
  _actVect.push_back(act);
  _widgetVect.push_back(widget);

}

// -------------------------------------------------------------------
// P R O T E C T E D     S L O T 
// -------------------------------------------------------------------

void
QGViewMenu::slotToggleWidget(QAction *act)
{
  int idx =_actVect.indexOf(act);

  // If this action is not in the vector it was called
  // by the command add by QGMenu::insertCommandItem.
  // So, forward it to the action vector in QGMenu class.
  if(idx < 0)
  {
    QGMenu::slotClicked(act);
    return;
  }  

  if ( !_actVect[idx]->isChecked() ) 
  {
    _actVect[idx]->setChecked(false);
    _widgetVect[idx]->hide();
  }
  else 
  {
    _actVect[idx]->setChecked(true);
    _widgetVect[idx]->show();
  }
}

// ----------------------------------------------------------------------
