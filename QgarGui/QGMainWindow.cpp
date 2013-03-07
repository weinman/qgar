/*---------------------------------------------------------------------+
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
 * @file  QGMainWindow.cpp
 * @brief Implementation of class QGMainWindow.
 *
 * See file QGMainWindow.h for the interface.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date     September 25, 2000  16:30
 * @since    Qgar 2.1
 */



// QGUI
#include "QGMainWindow.h"
#include "QGAlgoMenuFactory.h"
#include "QGAppLauncher.h"
#include "QGDocViewer.h"
#include "QGInteractorIf.h"
#include "QGImageLoader.h"
#include "QGLayerIf.h"
#include "QGMainWindowObserverIf.h"
#include "QGMultiLayerDoc.h"
#include "QGSimpleCommand.h"
#include "QGVectorialLayer.h"
#include "QGEditMenu.h"
#include "QGFileMenu.h"
#include "QGHelpMenu.h"
#include "QGImageMenu.h"
#include "QGAlgoMenu.h"
#include "QGOptionMenu.h"
#include "QGViewMenu.h"
#include "QGInteractorBarFactory.h"
#include "QGMainToolBar.h"
#include "QGMainToolsToolBar.h"
#include "QGUtilityBarFactory.h"

//STL
#include <algorithm>
#include <functional>

//STD
#include <cmath>
#include <iostream>

//QT
#include <QApplication>
#include <QFileInfo>
#include <QFile>
#include <QMenuBar>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QStatusBar> 
#include <QLabel>
#include <QCloseEvent>

#include <QtDebug>

using namespace std;
using namespace qgar;



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

QGMainWindow::QGMainWindow(int sizeX, int sizeY) 
{
  //-- Initialization of variables
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

  _lastDir    = ".";  // Last directory is current directory.
  _zoomFactor = 1.;   // All documents zoom is 1
  _currentDoc = 0;    // No document is open.
  _intToolBar = 0;    // No interactor bar is present.
  _viewToolsToolBar = 0;  // Layer specific tool bar is present.
  _currentInteract  = 0;


  //-- Set Window default size.

  setMinimumWidth(sizeX);
  setMinimumHeight(sizeY);


  //-- Create the QGDocViewer instance.
  _docViewer = new QGDocViewer(this);

  _docViewer->show();
  setCentralWidget(_docViewer);

  //-- Create default menus and toolbars.

  initMenuBar();
  initToolBars();  
  initStatusBar();
  initViewMenu();

  setAcceptDrops(true);

  
  //-- Enable/disable widgets according to their startup status.

  QApplication::restoreOverrideCursor(); 

  initDocument();
}



// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------

QGMainWindow::~QGMainWindow()
{
  // All Qt Widget created with this instance as parents are
  // automatically deleted.
}



// ---------------------------------------------------------------------
// O T H E R   M E T H O D S
// ---------------------------------------------------------------------

void
QGMainWindow::initMenuBar()
{
  // Get a menuBar from MainWindow
  _menuBar = menuBar();

  // ------------
  // Create Menus
  // ------------

  _fileMenu    = new QGFileMenu(this);
  _editMenu    = new QGEditMenu(this);
  _viewMenu    = new QGViewMenu(this);
  _imagesMenu  = new QGImageMenu(this);
  _algoMenu    = new QGAlgoMenu(this);
  _optionsMenu = new QGOptionMenu(this);
  _helpMenu    = new QGHelpMenu(this);


  //---------------------
  // Add menus to menubar
  //---------------------

  // Add and Create file menu
  _menuBar->addMenu(_fileMenu);
  for(int n=0; n < _fileMenu->numberOfActions(); n++) {
    _fileMenu->addAction(_fileMenu->getAction(n));
  }

  // Add and create edit menu
  _menuBar->addMenu(_editMenu);
  for(int n=0; n < _editMenu->numberOfActions(); n++) {
    _editMenu->addAction(_editMenu->getAction(n));
  }

  // Add the menus don't need explicit action initialization
  _menuBar->addMenu(_viewMenu);
  _menuBar->addMenu(_imagesMenu);
  _menuBar->addMenu(_algoMenu);
  _menuBar->addMenu(_optionsMenu);

  _menuBar->addSeparator();

  // Create help menu
  _menuBar->addMenu(_helpMenu);
   for(int n=0; n < _helpMenu->numberOfActions(); n++) {
     _helpMenu->addAction(_helpMenu->getAction(n));
   }

}

// ---------------------------------------------------------------------

void
QGMainWindow::initToolBars()
{
  
  // Build the main tools toolbar
  addToolBar(_mainToolsToolBar = new QGMainToolsToolBar(this));

  // Build the main toolbar
  addToolBar(_mainToolBar = new QGMainToolBar(this));
}


// ---------------------------------------------------------------------

void
QGMainWindow::initStatusBar()
{
  statusBarMsg(tr("Ready."));
}

// ---------------------------------------------------------------------

void
QGMainWindow::initDocument()
{
  // Disable menu and toolbar items at startup
  //  _algoMenuAction->setEnabled(false);
}


// ---------------------------------------------------------------------

void
QGMainWindow::initViewMenu()
{
  // Register hidable widgets
   _viewMenu->registerWidget(statusBar(), "&Status Bar");
   _viewMenu->registerWidget(_mainToolBar, "&Tool Bar");
   _viewMenu->registerWidget(_mainToolsToolBar, "&Main Tool Bar");

  _viewMenu->insertSeparator();
  QGCommandIf * cmd = 
    new QGSimpleCommand<QGMainWindow>(this, &QGMainWindow::refreshView);
  _viewMenu->insertCommandItem(cmd, tr("&Refresh Screen"));  

  // The action is added to menu in the initialization of ViewMenu
  for(int n=0; n < _viewMenu->numberOfActions(); n++) {
    _viewMenu->addAction(_viewMenu->getAction(n));
  }
  
}

// ---------------------------------------------------------------------

void
QGMainWindow::saveOptions()
{	
}

// ---------------------------------------------------------------------

void
QGMainWindow::readOptions()
{
}

// ---------------------------------------------------------------------

void
QGMainWindow::openImage(const QString& fileName) throw (exception)
{
  QFileInfo finfo(fileName);
  
  // ------------------------
  // Check if file is correct
  // ------------------------

  if ( fileName.isEmpty() )  // Empty filename, nothing to be open
    return;
  
  if (!finfo.isFile() || !finfo.isReadable())  // Is file accessible ?
    throw exception();

  else {

    // ---------
    // Open File
    // ---------
    
    //-- If document is already open, we close it and reload it.

    QGMultiLayerDoc * doc = findDoc(fileName);    
    if (doc != 0)
    {
      removeDoc(fileName);
    }
    
    //-- Create new document containing image as bottom layer.
    
    // Create a temporary empty document.
    QGMultiLayerDoc *docTmp = new QGMultiLayerDoc();

    // Init filename
    QFile file(fileName);
    docTmp->setFileName(fileName);
    docTmp->setName(fileName);
    

    // Init zoom factor: ALL DOCS are diplayed with the same zoom level.
    docTmp->setZoom(_zoomFactor);

    // Load layer and add it to temporaty doc.
    statusBarMsg(tr("Opening file..."));

    // Set cursor to wait cursor.
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    QGLayerIf * layer = QGImageLoader::instance()->loadLayer(fileName);

    // Ensure that a layer has correctly been created.
    if (!layer) {
      // Restore cursor.
      QApplication::restoreOverrideCursor();
      QMessageBox::warning(this, 
			   tr("Error"),
			   tr("The file " + fileName.toAscii() + " could not be open"),
			   QMessageBox::Ok,
			   QMessageBox::NoButton,
			   QMessageBox::NoButton);
      return;
    }
    
    docTmp->addLayer(layer, 0);
    
    //-- Set last directory to the directory holding this file.

    _lastDir = finfo.absoluteFilePath();

    //-- If doc has correctly been created. 
    // + Add it to document list.
    // + Display it in canvas view.
    // + Notify observer that a new document is created.
    if (docTmp) {

      // Insert document in the list of displayed docs.
      _listOfDocs.push_front(docTmp);

      // Change current open document to the loaded one.
      changeToImage( docTmp->fileName() );

      // Notify Observers that a new document is open.
      //
      // WARNING: This notification must be issued after the
      // changeToImage() call. The call sets the _currentDoc member.
      // If the notif of a new document is issued before, listener
      // will not be able to retrieve info on the new document
      notify(DOCUMENT_OPEN);
    }

    // Restore cursor.
    QApplication::restoreOverrideCursor();
  }

  statusBarMsg(tr("Ready."));
}

// ---------------------------------------------------------------------

void
QGMainWindow::saveImage() {

  if (_currentDoc) {
    statusBarMsg(tr("Saving file..."));

    // Hackish
     QGLayerIf * layer = _currentDoc->activeLayer();
     layer->save();
     _currentDoc->setModified(false);

     statusBarMsg(tr("Ready."));
  }  
}

// ---------------------------------------------------------------------

void
QGMainWindow::saveImageAs(const QString& filename, const char * format)
{ 
}


// ---------------------------------------------------------------------

void
QGMainWindow::printImage() 
{
  if (!_currentDoc)
    return;

  QPrinter printer;

  statusBarMsg(tr("Printing..."));

  // 0 means no file printing
  printer.setOutputFileName(0);

  // Set default color printing to grayscale
  // it gives better results in case of printing to files
  printer.setColorMode(QPrinter::GrayScale);

  QPrintDialog dialog(&printer, this);
  
  if(dialog.exec() == QDialog::Accepted)
  {
    QPainter paint(&printer);
    
    // Change the scale of the painter in order to fit the image
    // to the dimensions of the printer
    
    QRect pageRect = printer.pageRect();
    
    if(_currentDoc->width() > pageRect.width()
    || _currentDoc->height() > pageRect.height()) {
    
      double rw = ((double) pageRect.width()) / ((double) _currentDoc->width());
        double rh = ((double) pageRect.height()) / ((double)_currentDoc->height());
        double rm = min(rw, rh);
	
        paint.scale(rm, rm);
    }
    
    // Set cursor to wait...
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    //-- Draw the view on the printer paint device.
    _currentDoc->drawArea(0, 0, _currentDoc->width(), _currentDoc->height(), 
    			  &paint);

    paint.end();

    // Unset wait cursor.
    QApplication::restoreOverrideCursor();
    
  }    

  statusBarMsg(tr("Ready."));

}

// ---------------------------------------------------------------------


void
QGMainWindow::quit() {

  saveOptions();
  close();	
}

// ---------------------------------------------------------------------

void
QGMainWindow::incZoom(float factor) {


  _zoomFactor *= factor;  

  _docViewer->setZoom(_zoomFactor);

  // Keep all document w/ the same zoom level
  for_each(_listOfDocs.begin(), _listOfDocs.end(),
	   bind2nd(mem_fun(&QGMultiLayerDoc::setZoom), _zoomFactor));
}

// ---------------------------------------------------------------------

void
QGMainWindow::launchBatch(QString command,  QVector<QString> files)
{
  QGAppLauncher launcher(this, files);
  
  launcher.launch(command);
}

// ---------------------------------------------------------------------


void
QGMainWindow::openSuperimposeImage(QString fileName)
{
  loadSIItems(fileName);
}

// ---------------------------------------------------------------------

void
QGMainWindow::closeImage(const QString& fileName)
{
  QGMultiLayerDoc * doc = findDoc(fileName);

  if (!doc)
    return; // If the document is not open, do nothing

  // If the superimpose mode is on, turn it of to keep
  // the number of layers in 1.
  if(_currentDoc->isSuperimposeMode())
    deleteSIItems();

  // We delete the document  
  _listOfDocs.remove(doc);
  
  // We delete it from the history list...
  cleanHistoryList(doc);
  
  notify(DOCUMENT_CLOSED);

  // Display previous document or dark screen if no open document exist.
  if (!_histoOfDisplayedDocs.empty()) {
  
    QGMultiLayerDoc * lastDoc = _histoOfDisplayedDocs.front();
    _histoOfDisplayedDocs.pop_front();
    
    changeToImage(lastDoc->fileName());
  }
    
  else {
  
    // Display an empty document in central widget
    _docViewer->setDocument(0);

    // Reset zoom factor to 1.0
    _zoomFactor = 1.0;

    // Destroy and hide interactors toolbar
    delete _intToolBar;
    _intToolBar = 0;
    _currentInteract = 0;

    // Destroy and hide interactors toolbar
    delete _viewToolsToolBar;
    _viewToolsToolBar = 0;

    // Blank current document
    _currentDoc = 0;

    // Update title so that no document is displayed in the caption.
    refreshTitle();
  }

  delete doc;
}

// ---------------------------------------------------------------------

void
QGMainWindow::closeImage() {
  
  // If no document is open, nothing is to be closed ( the call is
  // probably incorrect).
  if (!_currentDoc)
    return;

  closeImage(_currentDoc->fileName());
}

// ---------------------------------------------------------------------


void
QGMainWindow::changeToImage(const QString& filename) {

  //-- Lookup for document knowing its name

  QGMultiLayerDoc * doc = findDoc(filename);

  //-- Check if a change is necessary

  if (doc == 0)            // Document does not exist
    return;

  if (doc == _currentDoc)  // Document is already being displayed
    return;


  //-- Document is found, switching to it

  _currentDoc = doc;
  _histoOfDisplayedDocs.push_front(doc);
  
  //-- Update document dependent widgets

  updateView();
  updateInteractorBar();
  updateUtilityBar();

  refreshTitle();

  // ---------------------
  // First Opened Document.
  // ---------------------
  if (_listOfDocs.size() == 1) {
    
    // The following action are taken when the document is the first
    // one to be opened.
    
    // Enable menu image. At least One doc must be present
    // Find the correspondent Action to the parameter image
    int idx = _imagesMenu->findAction(filename);
    _imagesMenu->enableAction(idx, true);
 
  }
  //-- Notify listener that a new document is open
  notify(CURRENT_DOC_CHANGED);
}


// ---------------------------------------------------------------------


QGMultiLayerDoc * 
QGMainWindow::findDoc(const QString& fileName)
{
  list<QGMultiLayerDoc*>::iterator it;

  for (it = _listOfDocs.begin(); it != _listOfDocs.end(); it++)
    if (fileName == (*it)->fileName())
      return (*it);

  return 0;
}

// ---------------------------------------------------------------------

void
QGMainWindow::removeDoc(const QString& filename)
{
  QGMultiLayerDoc * doc = findDoc(filename);


  if (!doc)
    return; // If the document is not open, do nothing
  
  
  // We delete the document  
  _listOfDocs.remove(doc);
    
  // We delete it from the history list...
  cleanHistoryList(doc);

  // We delete the document
  delete doc;
  doc = 0;
}

// ---------------------------------------------------------------------

void
QGMainWindow::updateView()
{
  _docViewer->setZoom(_currentDoc->zoom());
  _docViewer->setDocument(_currentDoc);
}

// ---------------------------------------------------------------------

void
QGMainWindow::refreshTitle()
{
  QString cap = "Qgar";

  if (_currentDoc) {
    cap += ": " + _currentDoc->name();
    
    if (_currentDoc->modified()) 
      cap += "(*)";
  }

  setWindowTitle(cap);
}

// ---------------------------------------------------------------------

bool
QGMainWindow::isSomeModifiedImages() const
{
  list<QGMultiLayerDoc*>::const_iterator it;

  if (_listOfDocs.size())
    for (it = _listOfDocs.begin(); it != _listOfDocs.end(); it++)
      if ((*it)->modified())
	return true;

  return false;
}

// ---------------------------------------------------------------------

void
QGMainWindow::closeEvent(QCloseEvent* ce)
{
  bool cancelled = false;
  switch(QMessageBox::information(this, "QGar", tr("Really quit QGar?"),
  				  tr("Yes"), tr("No"), 
  				  QString::null, 0, 1))   {
  case 0:
    
    //-- Prompt user for saving modified document.
    if ( isSomeModifiedImages() ) {

      list<QGMultiLayerDoc*>::iterator it;
      
      for (it = _listOfDocs.begin(); 
	   it != _listOfDocs.end() && (!cancelled); 
	   ++it) {
	
	if ( (*it)->modified() ) {
	  
	  // Show modified document.
	  changeToImage( (*it)->fileName() );
	  
	  switch (QMessageBox::warning(this, "Qgar", 
				       (*it)->fileName() 
				       + tr(" has been  modified.\n Do you want to save it ?"),
				       tr("Yes"), tr("No"), tr("Cancel")))	{	    
	  case 0:
	    saveImage();
	    break;
	
	  case 2:
	    cancelled = true;
	    break;
	    
	  default:
	    break;
	  } //-- end switch
	} //-- end if modified
      } //-- end loop on all open documents
    } // --end if some image are modified
    
    if (cancelled)
      ce->ignore();
    else
      ce->accept();
    break;
    
  case 1:
  default:
    ce->ignore();
    break;

  }
}

// -------------------------------------------------------------------

void 
QGMainWindow::refreshView()
{
  _docViewer->repaint();
}


// -------------------------------------------------------------------
// D R A G     N     D R O P 
// -------------------------------------------------------------------

void 
QGMainWindow::dragEnterEvent(QDragEnterEvent* e)
{
 
  QString f,s;

  if (e->provides("text/uri-list")) {
    f=(QString)(e->encodedData("text/uri-list"));
    s=f.trimmed();
  }
  else if (e->provides("text/plain")) {
    f=(QString)(e->encodedData("text/plain"));
    s=f.trimmed();
  }
  else if (e->provides("_NETSCAPE_URL")) {
    f=(QString)(e->encodedData("_NETSCAPE_URL"));
    s=f.trimmed();
  }
  else
    return;//we reject the event

  s = s.right(3); //we keep just the extension
  s.toLower();

  if (s == "dxf" || s == "pbm" || s== "pgm" || s == "ppm")
    e->accept();
}

// ---------------------------------------------------------------------


void
QGMainWindow::dropEvent(QDropEvent* e)
{

  //display the awailable format
 //  int i=0;
//   QString ff ;
//   while(ff=e->format(i++)){
//     cout<<ff<<" contains: "<<endl;
//     cout<<e->encodedData(ff)<<endl;
//   }

  e->accept();
  QString f,s;

  if (e->provides("text/uri-list")) {
    f=(QString)(e->encodedData("text/uri-list"));
    f.replace(0,5,"");//remove "file:"
    s=f.trimmed();
  }
  else if (e->provides("text/plain")) {
    f=(QString)(e->encodedData("text/plain"));
    f.replace(0,5,"");//remove "file:"
    s=f.trimmed();
  }
  else if (e->provides("_NETSCAPE_URL")) {
    f=(QString)(e->encodedData("_NETSCAPE_URL"));
    f.replace(0,7,"");//remove "file://"
    s=f.trimmed();
  }
  else
    return;//we shouldn't arrive here...

  //we check that the file is good
 
  //cout<<"we use: "<<s<<endl;
  
  QFileInfo finfo(s);
  
  if (!finfo.isFile()) {
    cerr<<"QGMainWindow::dropEvent: not a file"<<endl;
    return ;
  }
  if (!finfo.isReadable()) {
    cerr<<"QGMainWindow::dropEvent: not readable"<<endl;
    return ;
  }
  
  openImage(s);
}

// ---------------------------------------------------------------------

void
QGMainWindow::cleanHistoryList(QGMultiLayerDoc * doc)
{
  list<QGMultiLayerDoc*>::iterator cur, next;
  bool stop;

  // We delete it from the history list...

  _histoOfDisplayedDocs.remove(doc);

  // ... and we clean the history list to avoid
  // duplicate following entries

  for (cur = _histoOfDisplayedDocs.begin();
       cur != _histoOfDisplayedDocs.end();
       cur++) {

    next = cur;
    next++;
    stop = false;
    
    while (!(next == _histoOfDisplayedDocs.end()) && !stop)
      if (*cur == *next) {
	_histoOfDisplayedDocs.erase(next);
	next = cur;
	next++;
      }
      else
	stop = true;
  }
}


// -------------------------------------------------------------------
// S U P E R I M P O S E   M O D E
// -------------------------------------------------------------------

void 
QGMainWindow::loadSIItems(const QString& filename)
{
  if (!_currentDoc)
    return;

  // Set the superimpose mode flag to on
  _docViewer->setSuperimposeMode(true);

  QGLayerIf * layer = QGImageLoader::instance()->loadLayer(filename);


  //-- Set weird color to the SI layer.
  _currentDoc->setSuperimposeMode(true);
  _currentDoc->addLayer(layer, 1);
  //  _currentDoc->activeLayer()->update();
  _docViewer->setDocument(_currentDoc);

  refreshView();
}

// ---------------------------------------------------------------------

void 
QGMainWindow::deleteSIItems()
{
  if (!_currentDoc)
    return;

  _currentDoc->removeLayer(_currentDoc->layerAt(1));
  //  _currentDoc->activeLayer()->update();
  _docViewer->setDocument(_currentDoc);

  // It's changed after to allow the update work
  // with 2 layers
  _currentDoc->setSuperimposeMode(false);

  refreshView();
}



// ---------------------------------------------------------------------
// S L O T   I M P L E M E N T A T I O N
// ---------------------------------------------------------------------

void
QGMainWindow::statusBarMsg(const QString text)
{
  statusBar()->clearMessage();
  statusBar()->showMessage(text);
}

// ---------------------------------------------------------------------

void 
QGMainWindow::interactive()
{  
  //  QGVariableDialog dialog(_view, _process);
//   QGVariableDialog dialog(this, _currentDoc, _process);
//   dialog.exec();
}

// ---------------------------------------------------------------------


// -------------------------------------------------------------------

void
QGMainWindow::updateInteractorBar()
{
  // Delete previous interactor toolbar. If no toolbar has been
  // created, pointer value is 0 and deleting it is still correct.
  removeToolBar(_intToolBar);
  delete _intToolBar;

  // Interactor is deleted when the interactor toolbar is deleted.
  if (_currentInteract) {
    _currentInteract = 0;    
  }  

  // Create the interactor toolbar associated with the background
  // layer of the current document
  
  _intToolBar =
    QGInteractorBarFactory::instance()->createInteractorBar(this,
				_currentDoc->activeLayer()->type());
  addToolBar(_intToolBar);
}

// -------------------------------------------------------------------

void 
QGMainWindow::updateUtilityBar()
{
  // Delete previous utility toolbar. If no toolbar has been
  // created, pointer value is 0 and deleting it is still correct.
  removeToolBar(_viewToolsToolBar);
  delete _viewToolsToolBar;

  // Create the utility toolbar associated with the background
  // layer of the current document
  _viewToolsToolBar =
    QGUtilityBarFactory::instance()->createUtilityBar(this,
					    _currentDoc->layerAt(0)->type());
  // Only adds the bar if the image is vectorial
  if(_viewToolsToolBar != 0)
    addToolBar(_viewToolsToolBar);
}

// -------------------------------------------------------------------
// A C C E S S O R S 
// -------------------------------------------------------------------


QGMultiLayerDoc *
QGMainWindow::getCurrentDoc() const 
{
  return _currentDoc;
}

// ---------------------------------------------------------------------

QString
QGMainWindow::getLastDir() const 
{
  return _lastDir;
}

// ---------------------------------------------------------------------

const QString& 
QGMainWindow::accessLastDir() const 
{  
  return _lastDir;
}

// ---------------------------------------------------------------------

const list<QGMultiLayerDoc *>&
QGMainWindow::accessListOfDocs() 
{
  return _listOfDocs;
}

// ---------------------------------------------------------------------


const list<QGMultiLayerDoc *>&
QGMainWindow::accessHistoOfDisplayedDocs()
{
  return _histoOfDisplayedDocs;
}

// ---------------------------------------------------------------------

QGDocViewer *
QGMainWindow::docViewer() const
{
  return _docViewer;
}

// ---------------------------------------------------------------------

const QGInteractorIf *
QGMainWindow::currentInteractor() const
{
  return _currentInteract;
}


// ---------------------------------------------------------------------

void
QGMainWindow::setCurrentInteractor(QGInteractorIf * interact)
{
  if (_currentInteract)
    _currentInteract->dismiss();

  _currentInteract = interact;
  interact->activate();
}

// -------------------------------------------------------------------
// S U B J E C T     I M P L E M E N T A T I O N 
// -------------------------------------------------------------------

void
QGMainWindow::attach(QGMainWindowObserverIf * obs) {

  // Search if observer is in the vector
  QVector<QGMainWindowObserverIf*>::iterator it;

  it = std::find(_obsVect.begin(), _obsVect.end(), obs);
  
  // If not found, insert observer
  if( it == _obsVect.end())

     _obsVect.push_back(obs);
}

// ---------------------------------------------------------------------

void
QGMainWindow::detach(QGMainWindowObserverIf * obs) {

  _obsVect.erase(remove(_obsVect.begin(), _obsVect.end(), obs),
		 _obsVect.end());
}

// ---------------------------------------------------------------------


void
QGMainWindow::notify(Event what) {

  // QGAR 2.2 Comments
  //
  // For each observer obs, call mainWindowUpdated(what)
  // Equivalent as :  
  QVector<QGMainWindowObserverIf*>::iterator it;
  for(it=_obsVect.begin(); it !=_obsVect.end(); ++it) 
  {
    (*it)->mainWindowUpdated(what);
  }

//   for_each(_obsVect.begin(), _obsVect.end(),
// 	   bind2nd(mem_fun(&QGMainWindowObserverIf::mainWindowUpdated), 
// 		   what)
// 	   );  
}

// ---------------------------------------------------------------------
