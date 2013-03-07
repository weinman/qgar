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
 * @file  QGFileMenu.cpp
 * @brief Implementation of class QGFileMenu.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   September 27, 2002  10:02
 * @since  Qgar 2.1
 */



// QGUI
#include "QGFileMenu.h"
#include "QGCloseImageCommand.h"
#include "QGMainWindow.h"
#include "QGOpenImageCommand.h"
#include "QGRecentFileMenu.h"
#include "QGSimpleCommand.h"

// XPM
#include "xpm/exit.xpm"
#include "xpm/fileopen.xpm"
#include "xpm/fileprint.xpm"
#include "xpm/filesave.xpm"



using namespace std;



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGFileMenu::QGFileMenu(QGMainWindow * main)
  : QGMenu(main),_main(main)
{
  _recentFileMenu = new QGRecentFileMenu(main);

  buildMenu();
  
  // Check if a document is open, and activate items accordingly
  bool haveDoc = (_main->getCurrentDoc() != 0);
  setHaveDoc(haveDoc);

  // If no doc has been open, disable the RecentFiles menu item
  if (_main->accessListOfDocs().empty())
    enableAction(_recentFileMenuID, false);

  // Register self as MainWindow observer.
  _main->attach(this);

}



// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


QGFileMenu::~QGFileMenu() 
{  
  _main->detach(this);

  delete _recentFileMenu;
}



// -------------------------------------------------------------------
// T R A N S F O R M S 
// -------------------------------------------------------------------

void
QGFileMenu::buildMenu() {

  this->setTitle(tr("&File"));

  QGCommandIf * cmd;
  int id;

  //-- Open Image
  
  cmd = new QGOpenImageCommand(_main);
  id = insertCommandItem(cmd, 
 		    QIcon(QPixmap(fileopen_xpm)), 
 		    tr("&Open Image..."),
 		    QKeySequence(tr("CTRL+O", "FILE|OPEN")));
  

  //-- Recent Files

  cmd = 0;
  _recentFileMenuID = insertMenuItem(_recentFileMenu,
 			 tr("Open &recent"),
 			 QKeySequence(tr("CTRL+R", "RECENT")));

  //-- Close Image

  // Keep track of the ID to update the menu
  cmd = new QGCloseImageCommand(_main);
  id = insertCommandItem(cmd, 
			 tr("&Close Image"), 
 			 QKeySequence(tr("CTRL+C", "FILE|CLOSE")));

  _docItemIDs.push_back(id); // Item disabled when no open doc
  
  
  //-- Separator
  insertSeparator();


  //-- Save Image
  cmd = new QGSimpleCommand<QGMainWindow>(_main, 
 					  &QGMainWindow::saveImage);
  id = insertCommandItem(cmd, 
 			 QIcon(QPixmap(filesave_xpm)) ,
 			 tr("&Save"), 
 			 QKeySequence(tr("CTRL+S", "FILE|SAVE")));

  _docItemIDs.push_back(id); // Item disabled when no open doc


  //-- Save Image As

  cmd = new QGSimpleCommand<QGMainWindow>(_main, 
 					  &QGMainWindow::saveImage);
  id = insertCommandItem(cmd, tr("Save As"));

  _docItemIDs.push_back(id); // Item disabled when no open doc


  //-- Separator
  insertSeparator();


  //-- Print Image

  cmd = new QGSimpleCommand<QGMainWindow>(_main, 
 					  &QGMainWindow::printImage);
  id = insertCommandItem(cmd, 
 			 QIcon(QPixmap(fileprint_xpm)), 
 			 tr("&Print..."),
 			 QKeySequence(tr("CTRL+P", "FILE|PRINT")));
  _docItemIDs.push_back(id); // Item disabled when no open doc
  


  //-- Separator
  insertSeparator();

  //-- Exit
  cmd = new QGSimpleCommand<QGMainWindow>(_main, 
 					  &QGMainWindow::quit);
  insertCommandItem(cmd,
		    QIcon(QPixmap(exitIcon_xpm)),
   		    tr("E&xit"),
   		    QKeySequence(tr("CTRL+Q", "FILE|QUIT")));


}


// ---------------------------------------------------------------------

void
QGFileMenu::setHaveDoc(bool haveIt) {

  for (vector<int>::iterator it = _docItemIDs.begin();
       it!= _docItemIDs.end();
       ++it)
    {
      enableAction(*it, haveIt);
    }

  if (haveIt)
    enableAction(_recentFileMenuID, true);
}

// ---------------------------------------------------------------------



// -------------------------------------------------------------------
// O B S E R V E R     I M P L E M E N T A T I O N 
// -------------------------------------------------------------------

void
QGFileMenu::mainWindowUpdated(int what) {

  if ( what == QGMainWindowSubjectIf::DOCUMENT_OPEN )
    setHaveDoc(true);

  else if ( what == QGMainWindowSubjectIf::DOCUMENT_CLOSED )
    
    // Check is there is still an active document.
    // Disable items if not
    if ( (_main->accessListOfDocs()).empty() )
      setHaveDoc(false);
}



// ---------------------------------------------------------------------
