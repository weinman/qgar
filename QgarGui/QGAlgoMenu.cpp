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
 * @file  QGAlgoMenu.cpp
 * @brief Implementation of class QGAlgoMenu.
 *
 * See file QGAlgoMenu.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Vitor Vasconcelos">Vitor Vasconcelos</a>
 * @date   October 3, 2002  16:37
 * @since  Qgar 2.1
 */

// QGUI
#include "QGAlgoMenu.h"
#include "QGMainWindow.h"
#include "QGMultiLayerDoc.h"
#include "QGAlgoMenu.moc"


// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGAlgoMenu::QGAlgoMenu(QGMainWindow * main) 
  : QMenu(main),_main(main)
{
  this->setTitle(tr("&Algorithms"));
  init();
}

// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------

QGAlgoMenu::~QGAlgoMenu() 
{
  cleanMap();
  _main->detach(this);
}

// ---------------------------------------------------------------------
// T R A N S F O R M A T I O N
// ----------------------------------------------------------------------

void
QGAlgoMenu::init() 
{
  // Listen to its own events
  connectSelf();

  // Register self as a QGMainWindow observer
  _main->attach(this);

  // No image, no menu
  setEnabled(false);
}

// ----------------------------------------------------------------------

void
QGAlgoMenu::connectSelf() 
{ 
  QObject::connect(this, SIGNAL(triggered(QAction *)), SLOT(slotClicked(QAction *)));
}


// ----------------------------------------------------------------------

void
QGAlgoMenu::cleanMap()
{
  // Clean the actions vector
  for(actionVector::iterator it = _actVec.begin(); it != _actVec.end(); it++)
  {
    delete((*it).first);
    delete((*it).second);
  }
}

// ----------------------------------------------------------------------

void
QGAlgoMenu::update() {

  // Remove all elements actions from the menu
  clear();

  // Enable the algoritms menu
  this->setEnabled(true);

  _actVec = QGAlgoMenuFactory::instance()->buildActions
    (_main, _main->getCurrentDoc()->layerAt(0)->format());

  //  QVector< pair<QAction*, QGLaunchBatchCommand*> >::const_iterator it;
  actionVector::const_iterator it;

  for(it =_actVec.begin(); it != _actVec.end(); ++it)
  {
    this->addAction((*it).first);
  }

}

// -------------------------------------------------------------------
// O B S E R V E R     I M P L E M E N T A T I O N 
// -------------------------------------------------------------------


void
QGAlgoMenu::mainWindowUpdated(int what) 
{ 
  if (what == QGMainWindowSubjectIf::CURRENT_DOC_CHANGED)
  {
    update();
  }
}



// -------------------------------------------------------------------
// P R O T E C T E D     S L O T S 
// -------------------------------------------------------------------


void
QGAlgoMenu::slotClicked(QAction * act) 
{
  actionVector::iterator it = _actVec.begin();
  
  for(it; it != _actVec.end(); it++)
  {
    if ( (*it).first == act ) 
    {
      (*it).second->execute();
      return;
    }
  }
}

// ----------------------------------------------------------------------

