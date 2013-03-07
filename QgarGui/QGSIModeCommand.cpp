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
 * @file  QGSIModeCommand.cpp
 * @brief Implementation of class QGSIModeCommand.
 *
 * See file QGSIModeCommand.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 11, 2002  14:45
 * @since  Qgar 2.1
 */



// QGUI
#include "QGSIModeCommand.h"
#include "QGMainWindow.h"
#include "QGMultiLayerDoc.h"
// QT
#include <QFileDialog>
#include <QFileInfo>
#include <QString>



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// constructore
QGSIModeCommand::QGSIModeCommand(QGMainWindow * target) 
  : QGAbstractMainWindowCommand(target)
{ 
  QString filter ="*.info.dxf | Info. Files\n*.dxf | DXF Images";
  _qfd = new QFileDialog(target, filter, 
			 QObject::tr("Open  Info. File..."));
  _qfd->setFileMode(QFileDialog::ExistingFile);
}


// Copy-constructor
QGSIModeCommand::QGSIModeCommand(const QGSIModeCommand& other) 
  : QGAbstractMainWindowCommand(other)
{ /* EMPTY */ }



// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------

QGSIModeCommand::~QGSIModeCommand() 
{ /* EMPTY */ }



// ---------------------------------------------------------------------
// O P E R A T O R S
// ----------------------------------------------------------------------

// Assignment operator
QGSIModeCommand& QGSIModeCommand::operator=(const QGSIModeCommand& rhs) 
{
  if (! (this == &rhs) ) {
  
    _target = rhs._target;
  }

  return *this;
}


// -------------------------------------------------------------------
// Q G C O M M A N D I F     I M P L E M E N T A T I O N 
// -------------------------------------------------------------------

void
QGSIModeCommand::execute() {
  
  QGMultiLayerDoc * doc = _target->getCurrentDoc();

  // If no document is open, do nothing
  if (!doc)
    return;

  if (doc->layerCount() > 1) {

    _target->deleteSIItems();
  }

  else {

    // Select the file
    QString filter ="*.dxf | DXF Images";
    _qfd->setFilter(filter);
    if (_qfd->exec() == QDialog::Accepted) {
      QStringList selectedFiles = _qfd->selectedFiles();
      QString fileToOpen = selectedFiles.first();

	// Get the file and open it
	
	QFileInfo finfo(fileToOpen);
    
      if (!fileToOpen.isEmpty())
	_target->loadSIItems(fileToOpen);
      
    }
  }
}

// ----------------------------------------------------------------------

