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
 * @file  QGOpenImageCommand.cpp
 * @brief Implementation of class QGOpenImageCommand.
 *
 * See file QGOpenImageCommand.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   September 26, 2002  14:50
 * @since  Qgar 2.1
 */



// QGUI
#include "QGOpenImageCommand.h"
#include "QGMainWindow.h"
// QT
#include <QFileDialog>
#include <QMessageBox>
#include <QString>



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Constructor
QGOpenImageCommand::QGOpenImageCommand(QGMainWindow * target) 
  : QGAbstractMainWindowCommand(target)
{ 
  QString filter;
  filter += QObject::tr("Grayscale Images") + "(*.pgm);;";
  filter += QObject::tr("Binary Images") + "(*.pbm);;";
  filter += QObject::tr("Vectorial Images") + "(*.dxf);;";
  filter += QObject::tr("Color Images") + "(*.ppm);;";
  filter += QObject::tr("All Files") + "(*)";

  _qfd = new QFileDialog(_target, "", "", filter);

  //  _qfd->setShowHiddenFiles(true);
  _qfd->setFileMode(QFileDialog::ExistingFile);
}


// -------------------------------------------------------------------
// D E S T R U C T O R
// -------------------------------------------------------------------
QGOpenImageCommand::~QGOpenImageCommand()
{
  delete _qfd;
}

// -------------------------------------------------------------------
// T R A N S F O R M S 
// -------------------------------------------------------------------

void
QGOpenImageCommand::execute()
{

  //-- File selection
  QString lastDir = _target->accessLastDir();

  _qfd->setDirectory(_target->accessLastDir());

  if (_qfd->exec() == QDialog::Accepted) {

    QStringList listOfFiles =_qfd->selectedFiles();

    try {
      _target->openImage(listOfFiles.takeFirst());
    }

    catch(std::exception& e) {
      QMessageBox::critical(_target, 
			    QObject::tr("QGar error"), 
			    QObject::tr("Unable to open file"));
    }
  }
}




// ----------------------------------------------------------------------

// EOF
