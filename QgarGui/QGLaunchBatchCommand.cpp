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
 * @file  QGLaunchBatchCommand.cpp
 * @brief Implementation of class QGLaunchBatchCommand.
 *
 * See file QGLaunchBatchCommand.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 14, 2002  17:32
 * @since  Qgar 2.1
 */



// QGUI
#include "QGLaunchBatchCommand.h"
#include "QGAppDialogMediator.h"
#include "QGApplicationEntry.h"
#include "QGMainWindow.h"
#include "QGMultiLayerDoc.h"


// QT
#include <QString>
#include <QFile>
#include <QMessageBox>

using namespace std;



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

QGLaunchBatchCommand::QGLaunchBatchCommand(QGApplicationEntry& app)
  : _applicationEntry(app)
  ,_mediator(0)
{
  /* EMPTY */
}

// ---------------------------------------------------------------------

QGLaunchBatchCommand::QGLaunchBatchCommand(QGMainWindow * target, 
					   QGApplicationEntry& app)
  : QGAbstractMainWindowCommand(target), 
    _applicationEntry(app)
{
  _mediator = new QGAppDialogMediator(_applicationEntry, _target);
}



// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------

QGLaunchBatchCommand::~QGLaunchBatchCommand() 
{ 
  delete _mediator;
}


// ---------------------------------------------------------------------
// A C C E S S
// ---------------------------------------------------------------------

bool
QGLaunchBatchCommand::existingFilesInteraction(const QVector<QString>& files)
{
  bool isOverWrite = false;
  int res = true;

  QString msg = "The following files will be overwritten:<ul>";
  for (QVector<QString>::const_iterator it = files.begin();
       it != files.end();
       ++it)
    {
      if (QFile((*it)).exists()) {
	isOverWrite = true;
	msg += "<li>" + (*it) + "</li>";
      }
    }
  msg += "</ul>Do you wish to proceed ?";

  if ( isOverWrite )
    {

      bool query = QMessageBox::warning(
	       _target, "Warning", msg, 
	       QMessageBox::Yes,
	       QMessageBox::No  | QMessageBox::Escape | QMessageBox::Default 
      );
      res = (query != QMessageBox::Yes);
    }

  return res; // Returns true if the user answered yes
}



// ---------------------------------------------------------------------
// A C C E S S
// ---------------------------------------------------------------------

const QGApplicationEntry&
QGLaunchBatchCommand::applicationEntry() const {
  return _applicationEntry;
}


// -------------------------------------------------------------------
// Q G C O M M A N D I F     I M P L E M E N T A T I O N 
// -------------------------------------------------------------------

void
QGLaunchBatchCommand::execute() {
  
  // Check if this command has a target, and if it is currently
  // displaying a document. Return otherwise.
  if (!_target)
    return;

  if (!_target->getCurrentDoc())
    return;

  _mediator->reset();

  // Build application dialog to retrieve the app parameter values and
  // launch the application.
  if ( _mediator->showDialog() ) {
    
    // If files are to be erased by the command ask user for
    // confirmation.
    if ( existingFilesInteraction(_mediator->resultFiles()) ) {
    
            _target->launchBatch(_mediator->cmdLine(),
      			   _mediator->resultFiles());
    }
  } 
}


// ----------------------------------------------------------------------

