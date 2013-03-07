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
 * @file  QGRecentFileMenu.cpp
 * @brief Implementation of class QGRecentFileMenu.
 *
 * See file QGRecentFileMenu.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 1, 2002  10:08
 */



// QGUI
#include "QGRecentFileMenu.h"
#include "QGMainWindow.h"
#include "QGMultiLayerDoc.h"
// QT
#include "QGRecentFileMenu.moc"

using namespace std;



// -------------------------------------------------------------------
// S T A T I C     M E M B E R S
// -------------------------------------------------------------------

const unsigned int QGRecentFileMenu::DEFAULT_SIZE = 4;



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGRecentFileMenu::QGRecentFileMenu(QGMainWindow * main, 
				   unsigned int size) 
  : _listMaxSize(size),_main(main)
{ 
  init();
}



// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------

QGRecentFileMenu::~QGRecentFileMenu() {
  
  // Empty the QAction * list
  for(QList<QAction*>::iterator it = _actList.begin();
      it != _actList.end(); it++) {
    delete *it;
  }
  _main->detach(this);
}



// ---------------------------------------------------------------------
// A C C E S S
// ---------------------------------------------------------------------

int
QGRecentFileMenu::getListMaxSize() const {
  
  return _listMaxSize;
}


// ---------------------------------------------------------------------
// T R A N S F O R M A T I O N
// ----------------------------------------------------------------------

void
QGRecentFileMenu::init() {

  // Listen to its own events
  connectSelf();

  // Register self as a QGMainWindow observer
  _main->attach(this);

  // File list is empty. The menu is disabled.
  // The menu will be enabled at the first inserted document
  setEnabled(false);
}

// ----------------------------------------------------------------------

void
QGRecentFileMenu::connectSelf() {

  QObject::connect(this, SIGNAL(triggered(QAction*)), SLOT(slotClicked(QAction*)));
}

// ----------------------------------------------------------------------

void
QGRecentFileMenu::insertDoc(const QString& docName) {


  //-- Check if document is already in the list
  
  if (_fileList.contains(docName) == true)
    return;

  //-- If capacity is reached, make room for the new item
  
  if( _fileList.count() == _listMaxSize) {
    _fileList.removeLast();
    _actList.removeLast();
  }

  //-- Insert document
  _fileList.prepend(docName);
  
  //-- Rebuild menu
  clear();
  _actList.clear();

  for (unsigned int i = 0; i < _fileList.count(); i++) {

    QAction * act;

    act = addAction(_fileList.at(i)); // Direct map between Qt ID and list idx
    _actList.insert(i, act);
  }

  // At least one document is present in the list.
  // Menu can be enabled.
  setEnabled(true);
}

// -------------------------------------------------------------------
// O B S E R V E R     I M P L E M E N T A T I O N 
// -------------------------------------------------------------------

void
QGRecentFileMenu::mainWindowUpdated(int what) 
{
  if (what == QGMainWindowSubjectIf::DOCUMENT_OPEN)
  {
    insertDoc(_main->getCurrentDoc()->fileName());
  }
}


// -------------------------------------------------------------------
// S L O T S 
// -------------------------------------------------------------------

void
QGRecentFileMenu::slotClicked(QAction * action) {

  // Find the index corresponding to the action executed
  // open the related file
  
  int n = 0;
  for(QList<QAction*>::iterator it=_actList.begin();
      *it != action; it++) {
    n++;
  }
  
  // n MUST be a valid index
  _main->openImage(_fileList.at(n));
}

// ----------------------------------------------------------------------

