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
 * @file  QGMainToolBar.cpp
 * @brief Implementation of class QGMainToolBar.
 *
 * See file QGMainToolBar.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 8, 2002  17:51
 * @since  Qgar 2.1
 */



// QGUI
#include "QGMainToolBar.h"
#include "QGMainWindow.h"
#include "QGMultiLayerDoc.h"
#include "QGOpenImageCommand.h"
#include "QGSimpleCommand.h"
#include "QGUndoList.h"
#include "QGZoomCommand.h"

// QT
#include <QGroupBox>
#include <QToolButton>
#include <QAction>

// XPM
#include "xpm/exit.xpm"
#include "xpm/fileopen.xpm"
#include "xpm/filesave.xpm"
#include "xpm/fileprint.xpm"
#include "xpm/redo.xpm"
#include "xpm/undo.xpm"
#include "xpm/viewmag+.xpm"
#include "xpm/viewmag-.xpm"

#include <iostream>

using namespace std;



// ---------------------------------------------------------------------
// I N N E R   C L A S S
// ---------------------------------------------------------------------

/**
 * Command that performs an undo on the current document of a
 * QGMainWindow instance.
 *
 * This class is used only in QGMainToolBar.cpp and is not meant to be
 * used anywhere else.
 * 
 * SINCE Qgar 2.1
 */
class QGUndoCommand

  : public QGCommandIf

{
public:

/**
 * @brief Constructor
 *
 * @param main A pointer to the main window on the displayed document
 * of which the undo will be performed.
 */
  QGUndoCommand(QGMainWindow * main)

    : _main(main)

  {
    // VOID
  }

/**
 * @brief Performs the undo.
 */
  void execute()
  {
    _main->getCurrentDoc()->undo();
  }

private:

  /// Pointer to the main window
  QGMainWindow * _main;

}; // class QGUndoCommand



/**
 * Command that performs a redo on the current document of a
 * QGMainWindow instance.
 *
 * This class is used only in QGMainToolBar.cpp and is not meant to be
 * used anywhere else.
 * 
 * SINCE Qgar 2.1
 */
class QGRedoCommand

  : public QGCommandIf

{
public:
  
/**
 * Constructor
 *
 * PARAM main: A pointer to the main window on the displayed document
 * of which the redo will be performed.
 */
  QGRedoCommand(QGMainWindow * main)

    : _main(main)

  {
    // VOID
  }

/**
 * Performs the redo.
 */
  void execute()
  {
    _main->getCurrentDoc()->redo();
  }

private:

  // Pointer to the main window
  QGMainWindow* _main;
};



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGMainToolBar::QGMainToolBar(QGMainWindow* parent, const char* name)

  : QGCommandToolBar(parent, name),
    _main(parent)

{
  init();
  _main->attach(this);

  _lastDoc = 0;
  updateUndoRedo();
}



// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------

QGMainToolBar::~QGMainToolBar()
{
  // Delete all QActions used
  delete _actOpen;
  delete _actSave;
  delete _actPrint;
  delete _actQuit;
  delete _actUndo;
  delete _actRedo;
  delete _actZoomIn;
  delete _actZoomOut;

  _main->detach(this);
}




// ---------------------------------------------------------------------
// T R A N S F O R M A T I O N
// ----------------------------------------------------------------------

void
QGMainToolBar::init()
{
  // ------------------
  // General properties
  // ------------------

  setMovable(true);

  // -------------
  // Toolbar items
  // -------------

  QGCommandIf * cmd;
  int id;

  //-- Open a File
  _actOpen = new QAction(QIcon(fileopen_xpm), 
			      tr("Open File"), this);
  
  _actOpen->setToolTip(tr("Open a new file"));
  _actOpen->setStatusTip(tr("Open a new file"));
  _actOpen->setWhatsThis(tr("This opens a new file"));

  insertCommandAction(_actOpen, new QGOpenImageCommand(_main));
  this->addAction(_actOpen);


  //-- Save file
  
  _actSave = new QAction(QIcon(filesave_xpm),
			tr("Save file"), this);

  _actSave->setToolTip(tr("Save file"));
  _actSave->setStatusTip(tr("Save file"));
  _actSave->setWhatsThis(tr("This saves the current image"));


  cmd = new QGSimpleCommand<QGMainWindow>(_main, 
					  &QGMainWindow::saveImage);
  id = insertCommandAction(_actSave, cmd);
  this->addAction(_actSave);

  // Disable item when no document is open
  _docItemIDs.push_back(id);
  

  //-- Print File

  _actPrint = new QAction(QIcon(fileprint_xpm),
			 tr("Print file"), this);

  _actPrint->setToolTip(tr("Print file"));
  _actPrint->setStatusTip(tr("Print file"));
  _actPrint->setWhatsThis(tr("Print current image."));

  cmd = new QGSimpleCommand<QGMainWindow>(_main, 
					  &QGMainWindow::printImage);
  id = insertCommandAction(_actPrint, cmd);
  this->addAction(_actPrint);

  // Disable item when no document is open
  _docItemIDs.push_back(id);


  //-- Quit

  _actQuit = new QAction(QIcon(exitIcon_xpm),
			tr("Exit"), this);

  _actQuit->setToolTip(tr("Exit"));
  _actQuit->setStatusTip(tr("Exit"));
  _actQuit->setWhatsThis(tr("Quit Qgar."));

  cmd = new QGSimpleCommand<QGMainWindow>(_main, 
					  &QGMainWindow::quit);
  insertCommandAction(_actQuit, cmd);
  this->addAction(_actQuit);

  addSeparator();


  //-- Zoom in

  _actZoomIn = new QAction(QIcon(viewmagp_xpm),
			  tr("Zoom in"), this);

  _actZoomIn->setToolTip(tr("Zoom in"));
  _actZoomIn->setStatusTip(tr("Zoom in"));
  _actZoomIn->setWhatsThis(tr("Zoom in."));

  cmd = new QGZoomCommand(_main, 2.0);
  id = insertCommandAction(_actZoomIn, cmd);

  // Disable item when no document is open
  _docItemIDs.push_back(id);
  this->addAction(_actZoomIn);

  //-- Zoom out

  _actZoomOut = new QAction(QIcon(viewmagm_xpm),
			  tr("Zoom out"), this);

  _actZoomOut->setToolTip(tr("Zoom out"));
  _actZoomOut->setStatusTip(tr("Zoom out"));
  _actZoomOut->setWhatsThis(tr("Zoom out."));

  cmd = new QGZoomCommand(_main, 0.5);
  id = insertCommandAction(_actZoomOut, cmd);

  // Disable item when no document is open
  _docItemIDs.push_back(id);
  this->addAction(_actZoomOut);

  addSeparator();


  //-- Undo
  
  _actUndo = new QAction(QIcon(undo_xpm),
			 tr("Undo"), this);

  _actUndo->setToolTip(tr("Undo"));
  _actUndo->setStatusTip(tr("Undo"));
  _actUndo->setWhatsThis(tr("Undo."));

  cmd = new QGUndoCommand(_main);
  insertCommandAction(_actUndo, cmd);
  this->addAction(_actUndo);

  if (!_lastDoc)
    _actUndo->setEnabled(false);
  
  //-- Redo

  _actRedo = new QAction(QIcon(redo_xpm),
			 tr("Redo"), this);

  _actRedo->setToolTip(tr("Redo"));
  _actRedo->setStatusTip(tr("Redo"));
  _actRedo->setWhatsThis(tr("Redo."));

  cmd = new QGRedoCommand(_main);
  insertCommandAction(_actRedo, cmd);
  this->addAction(_actRedo);

  if (!_lastDoc)
    _actRedo->setEnabled(false);

  addSeparator();  

  //-- Check if a document is already open and activate buttons accordingly

  if (_main->accessListOfDocs().empty())
    setHaveDoc(false);

}

// -------------------------------------------------------------------

void
QGMainToolBar::setHaveDoc(bool haveIt)
{  
  for (QVector<int>::iterator it = _docItemIDs.begin();
       it!= _docItemIDs.end();
       ++it)
    {
      _actVect[*it]->setEnabled(haveIt);
    }
}

// -------------------------------------------------------------------

void
QGMainToolBar::updateUndoRedo()
{
  if (_lastDoc)
    {
      list<QGMultiLayerDoc *>::const_reverse_iterator it;  
      it = _main->accessHistoOfDisplayedDocs().rbegin();
      
      it++;
      if ( (*it) == _lastDoc )
	_lastDoc->undoList()->detach(this);
    }

  if( _main->getCurrentDoc() )
    {
      _lastDoc = _main->getCurrentDoc();
      _lastDoc->undoList()->attach(this);
    }
  else
    {
      _lastDoc = 0;
    }

  undoChanged();
}


// -------------------------------------------------------------------
// M A I N   W I N D O W   O B S E R V E R   I M P L 
// -------------------------------------------------------------------

void
QGMainToolBar::mainWindowUpdated(int what)
{
  if ( what == QGMainWindowSubjectIf::DOCUMENT_OPEN ) {
    setHaveDoc(true);
  } 
  else if ( what == QGMainWindowSubjectIf::DOCUMENT_CLOSED ) {
    
    // Check is there is still an active document.
    // Disable items if not
    if (! _main->getCurrentDoc() ) {
      setHaveDoc(false);
      updateUndoRedo();
    }
  }
  else if ( what == QGMainWindowSubjectIf::CURRENT_DOC_CHANGED ) {
    updateUndoRedo();
  }
}


// -------------------------------------------------------------------
// U N D O     O B S E R V E R     I M P L 
// -------------------------------------------------------------------

void
QGMainToolBar::undoChanged()
{
  QGMultiLayerDoc * doc = _main->getCurrentDoc();

  if (doc) {
    _actUndo->setEnabled(doc->undoList()->hasUndo());
    _actRedo->setEnabled(doc->undoList()->hasRedo());
  }

  else {
    _actUndo->setEnabled(false);
    _actRedo->setEnabled(false);
  }
}


// ----------------------------------------------------------------------
