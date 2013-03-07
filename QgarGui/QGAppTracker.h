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


#ifndef __QGAPPTRACKER_H_INCLUDED__
#define __QGAPPTRACKER_H_INCLUDED__


/**
 * @file     QGAppTracker.h
 * @brief    Header file of class QGAppTracker
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     September 10, 2003  16:45
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGAppTracker.h,v 1.6 2005/07/13 16:30:27 masini Exp $ */



// QGUI
class QGAppObserverIf;
// QT
#include <QObject>
#include <QString>
#include <QStringList>
#include <QProcess>
class QProcess;



/**
 * @class QGAppTracker QGAppTracker.h
 * @brief This class launches an external application and monitors its
 * state, forwarding events to requesting objects.
 *
 * <p>
 * Instances of this class monitor the state of a application launched
 * using the startApp() function member. They also forward information
 * on the application state to an optional registered observer.
 * </p>
 * <p>
 * The data forwarded to the observer can be:
 * - A notification that the application has ended.
 * - A line outputted by the application on its standard or error output.
 * </p>
 * 
 * @see QGAppObserverIf
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   September 10, 2003  16:45
 * @since  Qgar 2.1.1
 */
class QGAppTracker

  : public QObject

{
  Q_OBJECT

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /// The various states of the external application process
  enum State {
    READY, 
    RUNNING, 
    NORMAL_EXIT, 
    ABNORMAL_EXIT, 
    CANCELLED,  
    UNRUNNABLE
  }; 

/** @name Constructors */
//        ============
//@{

/**
 * @brief Default constructor.
 */
  QGAppTracker();


/**
 * @brief Builds a tracker with and sets the observer.
 *
 * @param obs The object this instance will report to.
 */
  QGAppTracker(QGAppObserverIf * obs);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Virtual destructor.
 *
 * If a process is still running, it WILL be detroyed.
 */
  virtual ~QGAppTracker();
//@}


/** @name Access */
//        ======
//@{
  
/**
 * @brief Retrieves the stat of the application.
 *
 * @return the state of the application.
 */
  State state() const;


/**
 * @brief Retrieves the application output log.
 *
 * @return The application output log.
 */
  const QStringList& appLog() const;

//@}


/** @name Transformation */
//        ==============
//@{

/**
 * @brief Sets the observer of the application.
 *
 * All events requiring a callback function call will be redirected to
 * this observer.
 *
 * @param obs A pointer to the new application observer.
 */
 void setAppObserver(QGAppObserverIf * obs);

//@}



/** @name Application Management */
//        ======================
//@{

/**
 * @brief Start the application.
 * @param cmdLine The command line used to activate the application.
 * @param waitEnd A flag indicating if the call may return immediatly
 *                or wait for the application to end.
 *
 * If the flag waitEnd is positionned, this function will only return
 * when the application is terminated.
 *
 * If the application is already started, this function
 * member does nothing. 
 */
  void startApp(const QString& cmdLine, bool waitEnd = false);


/**
 * @brief Interrupts the the running application.
 *
 * This method tries to cleanly terminate the process running the
 * application before killing it.
 */
  void cancelApp();

//@}


// -------------------------------------------------------------------
// P R O T E C T E D    S L O T S
// -------------------------------------------------------------------
protected slots:

/**
 * @brief Notifies the observer when the process executing the
 * application is finished.
 *
 * This slot is called as soon as the pocess is terminated. The
 * observer is notified using its finish() function member. Client may
 * then check the application exit status using state().
 */
 void appFinished(int, QProcess::ExitStatus);


// -------------------------------------------------------------------

/**
 * @brief Logs the application output and forward it to the observer
 *
 * This function logs all application out from both the standard
 * output and the error output. It forward the standard output to the
 * observer using its appLog() function member.
 */
  void logAndFwdOutput();



// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// Initializes this classes members.
  void init();

  /// The process in which the Qgar application is called.
  QProcess * _process;

  /// The observer watching the progress of the application.
  QGAppObserverIf * _obs;

  /// The current state of the application.
  State _state;

  /// The application ouput log.
  QStringList _appLog;


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

//
/** @name Disabled */
//        ========
//@{

/**
 * @brief Disabled copy-constructor.
 */
  QGAppTracker(const QGAppTracker& other);

/**
 * @brief Assignment operator.
 */
  QGAppTracker& operator=(const QGAppTracker& rhs);

//@}

// -------------------------------------------------------------------
}; // class QGAppTracker

#endif /* __QGAPPTRACKER_H_INCLUDED__ */
