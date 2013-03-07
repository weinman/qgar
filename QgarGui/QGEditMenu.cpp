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
 * @file  QGEditMenu.cpp
 * @brief Implementation of class QGEditMenu.
 *
 * See file QGEditMenu.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 2, 2002  14:39
 * @since  Qgar 2.1
 */


// QGUI
#include "QGEditMenu.h"
#include "QGMainWindow.h"
#include "QGZoomCommand.h"
// XPM
#include "xpm/viewmag+.xpm"
#include "xpm/viewmag-.xpm"

using namespace std;



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGEditMenu::QGEditMenu(QGMainWindow * main) 
  : QGMenu(main),_main(main)
{

  buildMenu();
  
  setHaveDoc(false);

  // Register as QGMainWindow observer.
  _main->attach(this);
}



// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------

QGEditMenu::~QGEditMenu() {

  // Detach self from the main window observer list.
  _main->detach(this);
}



// ---------------------------------------------------------------------
// T R A N S F O R M A T I O N
// ----------------------------------------------------------------------

void
QGEditMenu::buildMenu() {
  
  this->setTitle(tr("&Edit"));

  QGCommandIf * cmd;
  int id;

  //-- Zoom In

  cmd = new QGZoomCommand(_main, 2.0);
  id = insertCommandItem(cmd, 
  			 QIcon(QPixmap(viewmagp_xpm)), 
  			 tr("Zoom &In"));
  
  _docItemIDs.push_back(id); // Item disabled when no open doc
  
  
  
  //-- Zoom Out
  
  cmd = new QGZoomCommand(_main, 0.5);
  id = insertCommandItem(cmd, 
 			 QIcon(QPixmap(viewmagm_xpm)), 
 			 tr("Zoom &Out"));
  
  _docItemIDs.push_back(id); // Item disabled when no open doc
}

// ----------------------------------------------------------------------

void
QGEditMenu::setHaveDoc(bool haveIt) {

  for (QVector<int>::iterator it = _docItemIDs.begin();
       it!= _docItemIDs.end();
       ++it)
    {
      enableAction(*it, haveIt);
    }
}


// -------------------------------------------------------------------
// O B S E R V E R     I M P L E M E N T A T I O N 
// -------------------------------------------------------------------

void
QGEditMenu::mainWindowUpdated(int what) 
{

  if ( what == QGMainWindowSubjectIf::DOCUMENT_OPEN )
  {
    setHaveDoc(true);
  }
  
  else if ( what == QGMainWindowSubjectIf::DOCUMENT_CLOSED )
  {
    // Check is there is still an active document.
    // Disable items if not
    if ( (_main->accessListOfDocs()).empty() )
    {
      setHaveDoc(false);
    }
  }
}

// ---------------------------------------------------------------------
