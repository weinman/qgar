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
 * @file  QGImageMenu.cpp
 * @brief Implementation of class QGImageMenu.
 *
 * See file QGImageMenu.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 3, 2002  16:37
 * @since  Qgar 2.1
 */



// QGUI
#include "QGImageMenu.h"
#include "QGMainWindow.h"
#include "QGMultiLayerDoc.h"
#include "QGImageMenu.moc"

// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGImageMenu::QGImageMenu(QGMainWindow * main) 
  : QMenu(main),_main(main), _lastImgIdx(-1), _currentImgIdx(-1)
{
  this->setTitle(tr("&Images"));
  init();
}

// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------

QGImageMenu::~QGImageMenu() 
{
  cleanActionVector();
  _main->detach(this);
}

// ---------------------------------------------------------------------
// T R A N S F O R M A T I O N
// ----------------------------------------------------------------------

void
QGImageMenu::init() 
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
QGImageMenu::connectSelf() 
{ 
  QObject::connect(this, SIGNAL(triggered(QAction *)), SLOT(slotClicked(QAction *)));
}

// ----------------------------------------------------------------------

int
QGImageMenu::findAction(const QString& filename) const {

  int idx = 0;
  for(QVector<QAction *>::const_iterator it = _actVect.begin();
      it != _actVect.end(); it++)
  {
    if( filename == (*it)->text() ) return idx;
    else idx++;
  }
  
  // If we drop out of the loop, no action associated
  // with the file is found
  return -1;
}

// ----------------------------------------------------------------------

void QGImageMenu::enableAction(int idx, bool value) {

  // ATTENTION: the idx MUST be the index of a valid action
  // otherwise, the call to the function will be just ignored.
  if(idx >= 0)
    _actVect[idx]->setEnabled(value);

}

// ----------------------------------------------------------------------

void
QGImageMenu::insertImage(const QString& imageName) 
{
  int idx;

  // Check if item is already in the menu
  idx = findAction(imageName);
  if (idx == -1) {

    QAction * act = new QAction(imageName, this);    
    // Creat and configure the new Action and insert an
    // entry in the menu HEAD INSERTION and in the 
    // action vector.
    act->setCheckable(true);
    
    insertAction(0, act);
    
    _actVect.push_back(act);
  }
}

// ----------------------------------------------------------------------

void
QGImageMenu::removeCurrentImage() 
{
  // Remove current image
  removeAction(_actVect[_currentImgIdx]);
  _actVect.remove(_currentImgIdx);

  const list<QGMultiLayerDoc *> docList = 
    _main->accessHistoOfDisplayedDocs();

  if (!docList.empty()) {

    // Find current open doc
    _currentImgIdx = findAction(_main->getCurrentDoc()->fileName());
    
    // Highlight current open doc
    _actVect[_currentImgIdx]->setEnabled(false);
    _actVect[_currentImgIdx]->setChecked(true);
  }
  else
    _currentImgIdx = -1;
  

  if (docList.size() > 1) {

    // Search for previous open doc
    list<QGMultiLayerDoc *>::const_iterator it;
    it = _main->accessHistoOfDisplayedDocs().begin();
    
    // Last document is the second document of the list
    _lastImgIdx = findAction((*(++it))->fileName());

    _lastImgName = _actVect[_lastImgIdx]->text();
    _actVect[_lastImgIdx]->setShortcut(Qt::Key_Space);

  }

  else {
    _lastImgIdx = 0;
    _lastImgName = "";
    
  }
}

// ----------------------------------------------------------------------

void
QGImageMenu::update() {

  // Remove all elements
  clear();

  // The pointers to the actions stored in the vector
  // are automatically delete by the menu (the owner)
  // clear() method.
  _actVect.clear();

  list<QGMultiLayerDoc *> docList =  _main->accessListOfDocs();

  if (docList.empty()) 
  {
    setEnabled(false);
    return;
  }
  
  setEnabled(true);

  // Rebuild menu
  list<QGMultiLayerDoc *>::const_iterator it;
  for(it = docList.begin(); it != docList.end(); ++it) {
    
    QAction * act = new QAction((*it)->fileName(), this);
    act->setCheckable(true);
    
    insertAction(0, act);
    
    _actVect.push_back(act);
  }
  
  list<QGMultiLayerDoc *> histo =  _main->accessHistoOfDisplayedDocs();

  it = histo.begin();
  int idx;

  // Highlight current doc
  idx = findAction( (*it)->fileName() );
  _currentImgIdx = idx;
  _actVect[idx]->setEnabled(false);
  _actVect[idx]->setChecked(true);
  
  // Access second element
  it++;

  if (it != histo.end()) {
    idx = findAction( (*it)->fileName() );
    _lastImgIdx = idx;
    _lastImgName = _actVect[idx]->text();
    _actVect[idx]->setShortcut(Qt::Key_Space);
  }
}

void
QGImageMenu::cleanActionVector()
{
  // Destroy all Actions
  QVector<QAction *>::iterator it = _actVect.begin();
  
  for(it; it != _actVect.end(); it++)
  {  
    delete *it;
  }

  _actVect.clear();
}

// -------------------------------------------------------------------
// O B S E R V E R     I M P L E M E N T A T I O N 
// -------------------------------------------------------------------


void
QGImageMenu::mainWindowUpdated(int what) 
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
QGImageMenu::slotClicked(QAction * act) 
{
  int idx = -1;
  int n = 0;
  QVector<QAction *>::iterator it = _actVect.begin();
  for(it; it != _actVect.end(); it++)
  {
    if ( *it == act ) idx = n;
    n++;
  }

  // If current image is clicked => DO NOTHING.
  if (idx == _currentImgIdx)
    return;
  
  // If last image is clicked, open last image
  // This test is necessary since text(_lastImageID) is modified
  // by the setting of the accelerator.
  if (idx == _lastImgIdx)
    _main->changeToImage(_lastImgName);
  
  // Else open image whose name matches the clicked menu item.
  else
    _main->changeToImage(_actVect[idx]->text());
}

// ----------------------------------------------------------------------

