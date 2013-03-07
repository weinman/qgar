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


#ifndef __QGLAUNCHBATCHCOMMAND_H_INCLUDED__
#define __QGLAUNCHBATCHCOMMAND_H_INCLUDED__


/**
 * @file     QGLaunchBatchCommand.h
 * @brief    Header file of class QGLaunchBatchCommand
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 14, 2002  17:32
 * @since Qgar 2.1
 */


/* $Id: QGLaunchBatchCommand.h,v 1.9 2005/07/13 16:30:28 masini Exp $ */



// QGUI
#include "QGAbstractMainWindowCommand.h"
class QGMainWindow;
class QGAppDialogMediator;
class QGApplicationEntry;
// QT
#include <QVector>



/**
 * @class QGLaunchBatchCommand QGLaunchBatchCommand.h "QGLaunchBatchCommand.h"
 * @brief Command triggering the execution of a Qgar application
 * (from QgarApps).
 *
 * <p>
 * This command launches a Qgar application and awaits for its
 * termination.
 * </p>
 * <p>
 * If the application returns correctly its output image files will be
 * displayed in QgarGUI main window.
 * </p>
 * <p>
 * If an error occured while running the application, the command line
 * dialog between the GUI and the application will be made available.
 * </p>
 * 
 * @bug A segfault occurs in display result on string conversion in
 * displayResult. There is probably a multithreading issue with the
 * duplication of the vector of string _resultFiles since passing the
 * list of file thru a static variable does not cause any issue.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 14, 2002  17:32
 * @since  Qgar 2.1
 */
class QGLaunchBatchCommand

  : public QGAbstractMainWindowCommand

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name Constructors */
//        ============
//@{

/**
 * @brief Constructor.
 *
 * @param app The application entry referencing the binary to be
 * executed.
 */

  QGLaunchBatchCommand(QGApplicationEntry& app);


/**
 * @brief Constructor.
 *
 * @param main The main window that interacts with the executable. The
 * results produced by the binary will be displayed in it.
 *
 * @param main A pointer to the main window.
 * @param app  The application entry referencing the binary to be
 * executed.
 */
  QGLaunchBatchCommand(QGMainWindow * main, QGApplicationEntry& app);


//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGLaunchBatchCommand();
//@}


/** @name Access */
//        ======
//@{

/**
 * @brief Access to the application entry describing the Qgar
 * Application to launch.
 *
 * @return a reference to the QGApplicationEntry instance describing
 * the binary.
 */
  const QGApplicationEntry& applicationEntry() const;

//@}



/** @name QGCommandIf Implementation */
//        ==========================
//@{

/**
 * @brief Launches the Qgar application and waits for its completion.
 */
  virtual void execute();
  
//@}



// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  bool existingFilesInteraction(const QVector<QString>& files);

  /// The application entry referencing the binary to execute.
  QGApplicationEntry& _applicationEntry;

  /// The dialog mediator
  QGAppDialogMediator * _mediator;


// -------------------------------------------------------------------
// P R I V A T E   M E M B E R S
// -------------------------------------------------------------------
private:

  
/** @name Disabled */
//        ========
//@{

/**
 * @brief Disabled copy-constructor.
 */
  QGLaunchBatchCommand(const QGLaunchBatchCommand& other);

/**
 * @brief Disabled assignment operator.
 */
  QGLaunchBatchCommand& operator=(const QGLaunchBatchCommand&);

//@}


// -------------------------------------------------------------------
}; // class QGLaunchBatchCommand


#endif /* __QGLAUNCHBATCHCOMMAND_H_INCLUDED__ */
