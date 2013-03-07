/*---------------------------------------------------------------------*
 | Graphical user interface QgarGui                                    |
 | Copyright (C) 2003  Qgar Project, LORIA                             |
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
 * @file  QGAppLauncher.cpp
 * @brief Implementation of class QGAppLauncher
 *
 *        See file QGAppLauncher.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   September 18, 2003  10:13
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGAppLauncher.cpp,v 1.7 2005/07/13 16:30:26 masini Exp $ */



// QGUI
#include "QGAppLauncher.h"
#include "QGAppTracker.h"
#include "QGMainWindow.h"
// QT
#include <QProgressDialog>
#include <QMessageBox>
#include <QString>
// QGUI
#include "QGAppLauncher.moc"
// STD
#include <iostream>



using namespace std;



// ------------------------------------------------------------------
// C O N S T R U C T O R S
// ------------------------------------------------------------------

QGAppLauncher::QGAppLauncher(QGMainWindow * main)
  : _main(main), _progDiag(0),_imgShown(false)
{
  _tracker = new QGAppTracker(this);
}

QGAppLauncher::QGAppLauncher(QGMainWindow * main, 
			     QVector<QString> resultFiles)
  : _main(main), 
    _progDiag(0),
    _imgShown(false),
    _resultFiles(resultFiles)
{
  _tracker = new QGAppTracker(this);
}


// ------------------------------------------------------------------
// D E S T R U C T O R
// ------------------------------------------------------------------

QGAppLauncher::~QGAppLauncher()
{
  delete _tracker;
}


// ------------------------------------------------------------------
// Q G A P P O B S E R V E R I F   I M P L
// ------------------------------------------------------------------

void
QGAppLauncher::cmdLine(const string& line)
{
  QString cmd = line.c_str();

  //-- Progress Bar ON/OFF

  if(cmd.startsWith("SET ProgressBar")) {
    string s("SET ProgressBar");
    int length = s.length();

    // Get the value
    string value = line.substr(length + 1, cmd.length() - length);

    if(value == "ON")
      _progDiag->show();
    
    else if(value == "OFF")
      _progDiag->hide();
    
    else {
      QString str(value.c_str());
      int percent = str.toInt();
      _progDiag->setValue(percent);
    }    
  }


  //-- Open Image
  
  else if(cmd.startsWith("SHOW PICTURE")) {
    string s("SHOW PICTURE");
    int length = s.length();

    // Get the file name
    string value = line.substr(length + 1, cmd.length() - length);

//     try {
//       _main->openImage(value.c_str());
//       _imgShown = true;
//     }
//     catch (...) { /* EMPTY */ }
  }


  //-- Open superimpose image

  else if(cmd.startsWith("SHOW SUPERIMPOSE")) {
    string s("SHOW SUPERIMPOSE");
    int length = s.length();

    // Get the file name
    string value = line.substr(length + 1, cmd.length() - length);

    _main->openSuperimposeImage(value.c_str());
    _imgShown = true;
  }

  else
    _main->statusBarMsg(cmd);
}

// ---------------------------------------------------------------------

void
QGAppLauncher::start()
{
  delete _progDiag;
  createProgressDialog();
}

// ---------------------------------------------------------------------

void
QGAppLauncher::finish()
{ 
  switch(_tracker->state()) {

  case QGAppTracker::CANCELLED:
    _progDiag->hide();
    _main->statusBarMsg(tr("Application Cancelled"));
    break;

  case QGAppTracker::NORMAL_EXIT:
    _progDiag->setValue(100);

    _progDiag->hide();
    if (!_imgShown)
      displayResults();
    break;

  case QGAppTracker::ABNORMAL_EXIT:
    errorDialog();
    break;

  default:
    // This case should never occur. Throwing panic error.
    throw runtime_error("[QGLaunchBatchCommand]invalid application state");
  }
}

// ---------------------------------------------------------------------

void
QGAppLauncher::startError()
{
  unrunnableDialog();
}

// ---------------------------------------------------------------------
// M U T A T O R
// ----------------------------------------------------------------------

void
QGAppLauncher::launch(const QString& cmdline)
{
  _cmdLine = cmdline;
  _tracker->startApp(cmdline, true);
}

// -------------------------------------------------------------------

void
QGAppLauncher::createProgressDialog()
{
  _progDiag = new QProgressDialog(QObject::tr("Application in progress"),
				  QObject::tr("Cancel application"),
				  100, 0, _main, Qt::Dialog);
  _progDiag->setValue(0);
  _progDiag->setMinimumDuration(0);
  _progDiag->setWindowTitle("Qgar");

  //  connect(_progDiag, SIGNAL(cancelled()), SLOT(dialogCancelled()));
  connect(_progDiag, SIGNAL(canceled()), SLOT(dialogCancelled()));
}

// -------------------------------------------------------------------

void
QGAppLauncher::errorDialog()
{
  //-- Display error message box.

  QMessageBox * box = 
    new QMessageBox(QMessageBox::Warning,
		    QObject::tr("An error occured while running the application"),
		    QObject::tr("Error"),
		    QMessageBox::Ok | QMessageBox::Default | QMessageBox::Escape | QMessageBox::Cancel,		    
		    _main,
		    Qt::Dialog);

  box->setButtonText(2, QObject::tr("Details..."));
  

  
  if (box->exec() != QDialog::Accepted) {

    // User requests details.
    // Display log in a message box.

    QStringList list = _tracker->appLog();
    QString log;
    
    for (QStringList::Iterator i = list.begin(); i != list.end(); i++) {
      log += (*i);
      log += "\n";
    }

    QMessageBox * logBox = 
      new QMessageBox(QMessageBox::NoIcon,
		      QObject::tr("Details"),
		      log,
		      QMessageBox::Ok,
		      box,
		      Qt::Dialog);


    logBox->exec();
    delete logBox;
  }

  delete box;
}

// -------------------------------------------------------------------

void
QGAppLauncher::unrunnableDialog()
{

  //-- Display error message box.

  QMessageBox * box = 
    new QMessageBox(QMessageBox::Warning,
		    QObject::tr("Error"),
		    QObject::tr("The application could not be started"),
		    QMessageBox::Ok | QMessageBox::Default | QMessageBox::Escape | QMessageBox::Cancel,
		    _main,
		    Qt::Dialog);

  box->setButtonText(2, QObject::tr("View command line..."));
  

  if (box->exec() != QDialog::Accepted) {

    // User requests details.
    // Display log in a message box.

    QMessageBox * cmdlineBox = 
      new QMessageBox(QMessageBox::NoIcon,
		      QObject::tr("Command Line"),
		      _cmdLine,
		      QMessageBox::Ok,
		      box,
		      Qt::Dialog);


    cmdlineBox->exec();
    delete cmdlineBox;
  }

  delete box;
}

// -------------------------------------------------------------------

void
QGAppLauncher::displayResults()
{
  QVector<QString>::const_iterator it;

  for (it = _resultFiles.begin(); it != _resultFiles.end(); ++it) {

    QString filename = (*it);
    try {
      _main->openImage(filename);
    }
    catch (exception&) {
      QMessageBox::critical(_main,
 			    QObject::tr("Unable to open file "),
 			    QObject::tr("An error occured while loading image ") 
 			    + filename);
    }		   
    catch(...) {
      QMessageBox::critical(_main,
			    QObject::tr("Unexpected exception"),
			    QObject::tr("An unexpected exception occured while loading file "));
    }
  }
}


// ---------------------------------------------------------------------
// S L O T S
// ----------------------------------------------------------------------

void
QGAppLauncher::dialogCancelled()
{
  _tracker->cancelApp();
}

// ----------------------------------------------------------------------

