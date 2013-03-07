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
 * @file  QGAppTracker.cpp
 * @brief Implementation of class QGAppTracker
 *
 *        See file QGAppTracker.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   September 10, 2003  16:45
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGAppTracker.cpp,v 1.4 2005/07/13 16:30:27 masini Exp $ */



// QGUI
#include "QGAppTracker.h"
#include "QGLaunchBatchCommand.h"
#include "QGAppObserverIf.h"
// QT
#include <QEventLoop>
#include <QProcess>
#include <QRegExp>
#include <QStringList>
#include <QTimer>

// QGUI
#include "QGAppTracker.moc"



using namespace std;



// ------------------------------------------------------------------
// C O N S T R U C T O R S
// ------------------------------------------------------------------

QGAppTracker::QGAppTracker()
{
  _obs = 0;

  init();
}

// ------------------------------------------------------------------

QGAppTracker::QGAppTracker(QGAppObserverIf * obs)
{
  _obs = obs;

  init();
}


// ------------------------------------------------------------------
// D E S T R U C T O R
// ------------------------------------------------------------------

QGAppTracker::~QGAppTracker()
{
  _process->kill();
}


// ------------------------------------------------------------------
// A C C E S S
// ------------------------------------------------------------------

QGAppTracker::State
QGAppTracker::state() const 
{
  return _state;
}

// ---------------------------------------------------------------------

const QStringList&
QGAppTracker::appLog() const
{
  return _appLog;
}


// ---------------------------------------------------------------------
// T R A N S F O R M A T I O N
// ----------------------------------------------------------------------

void
QGAppTracker::init()
{
  // Initializes process.
  _state = READY;
  _process = new QProcess(this);

  connect(_process, SIGNAL(finished(int, QProcess::ExitStatus)), SLOT(appFinished(int, QProcess::ExitStatus)));
  connect(_process, SIGNAL(readyReadStandardOutput()), SLOT(logAndFwdOutput()));
}

// ---------------------------------------------------------------------

void
QGAppTracker::setAppObserver(QGAppObserverIf * obs)
{
  _obs = obs;
}


// ---------------------------------------------------------------------
// A P P L I C A T I O N   M A N A G E M E N T
// ----------------------------------------------------------------------

void
QGAppTracker::startApp(const QString& cmdline, bool waitEnd) 
{
  // Ensure that the process is runnable.
  if (_state != READY)
    return;


  QStringList list = cmdline.split(" ");

  _process->start(list.takeFirst(), list, QIODevice::ReadWrite);
  _process->waitForStarted();

  if(_process->state() == QProcess::NotRunning) 
  {
    _state = UNRUNNABLE;
    _process->kill();
  
    _obs->startError();
  }
  
  else {
    _state = RUNNING;
    _obs->start();
   
    // Block the application until the process is finished
    if (waitEnd)
    {
      _process->waitForFinished(-1);
    }
  }
}


// ----------------------------------------------------------------------

void
QGAppTracker::cancelApp()
{
  
  // Ensure that the process is being run.
  if (_state != RUNNING)
    return;
  
  _state = CANCELLED;
  _process->kill();
}

// ---------------------------------------------------------------------
// P R O T E C T E D   S L O T
// ----------------------------------------------------------------------

void
QGAppTracker::appFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
  if ( (_state != CANCELLED) && (_state != UNRUNNABLE) )
  {
    if(exitStatus == QProcess::NormalExit) _state = NORMAL_EXIT;
    else if (exitStatus == QProcess::CrashExit) _state = ABNORMAL_EXIT;
  }
  _obs->finish();
}

// ----------------------------------------------------------------------

void
QGAppTracker::logAndFwdOutput()
{
  QString line = _process->readAllStandardOutput();
  
  // Log command line
  _appLog.append(line);

  // Process command line.
  _obs->cmdLine(line.toStdString());
}

// ----------------------------------------------------------------------
