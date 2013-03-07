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


#ifndef __QGAPPLAUNCHER_H_INCLUDED__
#define __QGAPPLAUNCHER_H_INCLUDED__


/**
 * @file     QGAppLauncher.h
 * @brief    Header file of class QGAppLauncher
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     September 18, 2003  10:13
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGAppLauncher.h,v 1.5 2005/07/13 16:30:26 masini Exp $ */


// QGUI
#include "QGAppObserverIf.h"
class QGAppTracker;
class QGMainWindow;

// QT
#include <QVector>
#include <QObject>
class QProgressDialog;
class QString;


using namespace std;


/**
 * @class QGAppLauncher QGAppLauncher.h
 * @brief This class launches an external application and deals with
 * all the implied user interaction.
 *
 * <p>
 * This class launches an external application using a QGAppTracker
 * instance and register itself as an observer of the tracker.
 * </p>
 * <p>
 * This registration allows it to monitor the application ending and
 * to process the application output.
 * </p>
 * 
 * @see QGAppTracker
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   September 18, 2003  10:13
 * @since  Qgar 2.1.1
 */
class QGAppLauncher

  : public QObject,
    public QGAppObserverIf

{

  Q_OBJECT

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:


/** @name Constructors */
//        ============
//@{

/**
 * @brief Default constructor.
 *
 * @param main A pointer to the main window.
 */
  QGAppLauncher(QGMainWindow * main);


/**
 * @brief Default constructor.
 *
 * @param main A pointer to the main window.
 * @param resultFiles
 */
  QGAppLauncher(QGMainWindow * main, 
		QVector<QString> resultFiles);
  
//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Virtual destructor.
 */
  virtual ~QGAppLauncher();

//@}


/**
 * @brief Launches the application and awaits for its termination.
 *
 * @param cmdline The command line to be used to invoke the application.
 *
 * @warning This function member will release the calling control flow
 * only when the application is either cancelled or terminated.
 */
  void launch(const QString& cmdline);


/** @name QGAppObserverIf Impl */
//        ====================
//@{

  virtual void start();

  virtual void finish();

  virtual void startError();

  virtual void cmdLine(const string& line);

//@}




// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

/**
 * @brief Retrieves the list of the image files outputted by the
 * application.
 * 
 * @return The list of the application output files.
 */
//   vector<string> resultFiles() const;


/**
 * @brief Initializes the dialog progress dialog.
 */
  void createProgressDialog();


/**
 * @brief Displays a dialog informing the user that an error occured
 * while running the application.
 *
 * The displayed dialog also allows the user to access to the output
 * of the application.
 */
  void errorDialog();

/**
 * @brief Displays a dialog informing the user that the application
 * could not be run.
 *
 * The displayed dialog also allows the user to access to the output
 * of the application.
 */
  void unrunnableDialog();

/**
 * @brief Commands the main window to display the results of a Qgar
 * Application.
 *
 * This function member is called if no explicit command from the Qgar
 * Application has caused a result to be shown.
 */
  void displayResults();


  /// A pointer to the main window.
  QGMainWindow * _main;

/**
 * @brief The object monitoring the process executing the Qgar
 * application. 
 */
  QGAppTracker * _tracker;


  /// A progress dialog displaying the application state.
  QProgressDialog * _progDiag;


/**
 * @brief A flag indicating if the external app has requested the GUI
 * to open another image file.
 */
  bool _imgShown;


  /// The list of the application output filenames.
  QVector<QString> _resultFiles;

  /// The command line used to launch the application.
  QString _cmdLine;

// -------------------------------------------------------------------
// P R O T E C T E D   S L O T S
// -------------------------------------------------------------------
protected slots:


/**
 * @brief Slot invoked when the user cancels the application
 * execution.
 */
  void dialogCancelled();



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
  QGAppLauncher(const QGAppLauncher&);

/**
 * @brief Disabled assignment operator.
 */
  QGAppLauncher& operator=(const QGAppLauncher&);
  
//@}

// -------------------------------------------------------------------
}; // class QGAppLauncher


#endif /* __QGAPPLAUNCHER_H_INCLUDED__ */
