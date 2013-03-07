/*---------------------------------------------------------------------*
 | Graphical user interface QgarGui                                    |
 | Copyright (C) 2004  Qgar Project, LORIA                             |
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
 * @file  QGCloseImageCommand.cpp
 * @brief Implementation of class qgar::QGCloseImageCommand.
 *
 * See file QGCloseImageCommand.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   August 31, 2004  15:09
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGCloseImageCommand.cpp,v 1.2 2005/07/13 16:30:27 masini Exp $ */



// QGUI
#include "QGCloseImageCommand.h"
#include "QGMainWindow.h"
#include "QGMultiLayerDoc.h"
// QT
#include <QMessageBox>



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------


QGCloseImageCommand::QGCloseImageCommand(QGMainWindow * target)
  : QGAbstractMainWindowCommand(target)
{
  // EMPTY
}


// ---------------------------------------------------------------------
// Q G C O M M A N D I F   I M P L E M E N T A T I O N
// ----------------------------------------------------------------------

void
QGCloseImageCommand::execute()
{
  if ( _target->getCurrentDoc()->modified() ) {
    
    int ret = QMessageBox::warning(_target, "Save document? ",
 				_target->getCurrentDoc()->fileName()
 				+ " has been modified.\nDo you want to save it ?",
				   QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
				   QMessageBox::Cancel);

    switch(ret) 
    {
    case QMessageBox::Yes:
      _target->saveImage();
      //     |
      //     |    WARNING: this case also executes the next one
      //     v
    case QMessageBox::No:
      _target->closeImage();
      break;

    default:
      break;
      	
    } //-- end switch
    
  } //-- end if

  else {
    _target->closeImage();
  }
}

// ----------------------------------------------------------------------
