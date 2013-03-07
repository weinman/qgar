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


#ifndef __QGAPPDIALOGMEDIATOR_H_INCLUDED__
#define __QGAPPDIALOGMEDIATOR_H_INCLUDED__


/**
 * @file     QGAppDialogMediator.h
 * @brief    Header file of class QGAppDialogMediator
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     June 13, 2003  15:08
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGAppDialogMediator.h,v 1.5 2005/07/13 16:30:26 masini Exp $ */



// QGUI
class QGAppCmdLinePanel;
class QGAppDescrPanel;
class QGApplicationEntry;
class QGAbstractAppParamInput;
class QGAppParamPanel;
class QGMainWindow;

//STL
#include <vector>
// QT
#include <QString>
#include <QVector>
class QDialog;
class QPushButton;
class QString;
class QTabWidget;
class QVBoxLayout;
class QWhatsThis;
class QWidget;



/**
 * @class QGAppDialogMediator QGAppDialogMediator.h
 * @brief Mediator of the activation dialog launching QgarApps.
 *
 * <p>
 * This class is the mediator of the dialog launching an external Qgar
 * application. It is part of a mediator pattern as described in Gamma
 * et al p. 273, its colleagues being the descendents of
 * QGAbstractAppParamInput.
 * </p>
 * <p>
 * It fulfills 3 purposes:
 * - build the dialog
 * - manage the interaction between the dialog widgets
 * - compute data (such as the final command line) for the client
 * objects.
 *
 * These three aims are documented below.
 * </p>
 *
 * <p>
 * <b>Building the dialog</b><br>
 * The dialog is composed of 3 main elements:
 * - A Title (QLabel) showing the application name that is about to be
 *   launched.
 * - A tab widget holding 3 differents panel to customize the
 *   application call.
 * - A button bar to access to the online help, reject the dialog or
 *   accept the dialog.
 *
 * The tab widget childs are:
 * - a QGAppParamPanel instance that displays input field allowing to
 *   edit the value of the parameters passed to the application.
 * - a QGAppCmdLinePanel instance offering a preview of the command line
 *   that will be used to invoke the application and allowing to
 *   directly modify it.
 * - a QGAppDescrPanel instance displaying the documentation of the
 *   application and its parameters.
 *
 * </p>
 *
 * <p>
 * <p>
 * <b>Managing dialog child widgets interactions</b><br>
 * Anytime a colleague is modified, the mediator is notified and
 * updates the dialog accordingly. For instance when the value of a
 * parameter is set (by inputting it in a textfield) the mediator will
 * update the value of the textfield displaying the command line.
 * </p>
 * <p>
 * Currently this implementation manages two kind of interaction:
 * - It updates the command line panel whenever a parameter value is
 *   changed in the parameter panel.
 * - It displays the online documentation of a parameter when the
 *   contextual help is requested from the parameter panel (see
 *   jumpToAnchor()).
 *
 * </p>
 * <p>
 * Colleagues use the widgetChanged() function member to notify the
 * mediator of their updates.
 * </p>
 * <p>
 * <b>Compute data for the client object</b><br>
 * Once the user as entered all required data, the mediator makes
 * this data available for the client class (ie. the class that
 * created it and invoked the dialog creation).
 * The client can access this data using the following function
 * members:
 * - resultFileList(): Retrieve the list of the name of the image
 *   files that will be outputted if the QgarApp is launched.
 * - cmdLine(): Retrieve the valid command line that will trigger the
 *   QgarApps with all the settings defined in the dialog.
 * </p>
 *
 *
 * @see QGAbstractAppParamInput
 * @see QGAppParamPanel
 * @see QGAppCmdLinePanel
 * @see QGAppDescrPanel
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   June 13, 2003  15:08
 * @since  Qgar 2.1.1
 */
class QGAppDialogMediator
{
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
 * <p>
 * Creates and mediates the activation dialog of a Qgar application
 * referenced a QGApplicationEntry instance.
 * </p>
 * <p>
 * The dialog parent is the QGMainWindow instance main.
 * </p>
 *
 * @param entry The application entry describing the external
 * application to build a dialog for.
 *
 * @param main The main window instance that will become the parent of
 * the dialog.
 */
  QGAppDialogMediator(const QGApplicationEntry& entry,
		      QGMainWindow * main);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Virtual destructor.
 */
  virtual ~QGAppDialogMediator();

//@}
  

/** @name Access */
//        ======
//@{

/**
 * @brief Returns the default filename stem
 *
 * See #_defaultFileStem for details.
 *
 * @return the default filename stem
 */
  QString defaultFileStem() const;

/**
 * @brief Retrieves the list of the name of the image files created by
 * the application.
 *
 * @return The list of the name of the files created by the
 * application.
 */
  QVector<QString> resultFiles() const;
  
//@}


/**
 * @brief Displays the dialog.
 *
 * @return true if the dialog has been accepted, false otherwise.
 */
  virtual bool showDialog();

/**
 * @brief Resets the dialog. 
 *
 * All parameters corresponding to image filenames are reset, the
 * other are kept.
 */
  virtual void reset();


/**
 * @brief Callback function member used by colleagues to notify their
 * change of state.
 *
 * Widgets created by this mediator use this function member to notify
 * the mediator that their state has changed. This allows the mediator
 * to reflect these changes on the other widgets part of the dialog.
 *
 * @param widget a pointer to the QGAbstractAppParamInput instance
 * that has been modified.
 */
  virtual void widgetChanged(QGAbstractAppParamInput * widget);


/**
 * @brief Commands the dialog to display the HTML documentation at a
 * specific anchor.
 *
 * <p>
 * This function member is used to display the documentation of a
 * given application parameter.
 * </p>
 * <p>
 * Two steps are needed to achieve this:
 * - first, the mediator commands the dialog to show the application
 *   description tab in the _tabWidget.
 * - second, it scrolls the application documentation until the
 *   requested anchor is made visible.
 *
 * </p>
 *
 * @param anchor the name of the anchor to display
 */
  virtual void jumpToAnchor(const QString& anchor);


/**
 * @brief Retrieves the command line that will launch the
 * application.
 *
 * A QString holding the command to launch the application with the
 * parameters inputted by the user is created and returned.
 *
 * @return the command line.
 */
  QString cmdLine();
  


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

/**
 * @brief Creates the dialog and its child widgets.
 *
 * The dialog is created with with main as parent widget. All created
 * widgets are children or grand children of the dialog instance, so
 * deleting parent will delete all widgets (using QObject properties).
 *
 * @param main The main window, parent widget of this dialog.
 */
  virtual void createWidgets(QGMainWindow * main);


/**
 * @brief Creates the dialog button bar.
 *
 * <p>
 * This function member is part of the dialog widget construction. It
 * is called from createWidgets()
 * </p>
 * <p>
 * The created button bar consists in a group of 3 buttons<br>
 * The buttons and their associated action are:
 * - Help:   displays qgarGUI contextual help for activation dialogs.
 * - Cancel: dismiss the dialog and does NOT launch the application.
 * - Ok: Accepts the dialog. The dialog is dismissed and the
 *   application is launched using the defined command line.
 * </p>
 *
 * @return a pointer to the created button bar.
 */
  virtual QWidget * createButtonBar();


/** 
 * @brief Creates the widgets for the application parameters panel of
 * the main tab widget.
 *
 * <p>
 * For each parameter of the application, a QGAppParamInputLine is
 * created and added to the parameter panel.
 * </p>
 * <p>
 * This function member also sets the default filename stem for
 * filename parameters. The value of the default filename stem is the
 * name of the input image file (if any) stripped from its extension.
 * </p>
 *
 * @param main A pointer to the main window.
 */
  virtual void createParamLines(QGMainWindow * main);


/**
 * @brief Initializes the command line panel of the main tab widget.
 *
 * Since default values may be computed for some parameters while
 * creating the parameter panel, the command line panel must be
 * updated to reflect these changes. This function member updates the
 * command line panel (#_cmdLinePanel) according to the new parameter
 * values.
 */
  virtual void initCmdLinePanel();


/**
 *  @brief The application entry referencing the application to create
 *  a dialog for.
 */
  const QGApplicationEntry& _entry;  


/** 
 * @brief A pointer to the main window.
 *
 * This pointer to the main window is used to compute some default
 * value according to the current state of the application.
 */
  QGMainWindow * _main;
  
/** 
 * @brief The default filename stem for output files.
 *
 * <p>
 * If there is only one input image file default filenames can be
 * computed for the application output file parameters. The default
 * filename stem is the filename of the input file stripped from its
 * extension.
 * </p>
 * <p>
 * Default filenames for output parameters are computed by appending
 * to this default stem the suffix defined for the parameter in the
 * application configuration file.
 * </p>
 * <p>
 * For instance, for an input image filename of "house.pbm" and
 * default suffix of .cleaned.pbm the default filename stem is "house"
 * and the initial value of the parameter will be "house.cleaned.pbm".
 * </p>
 */
  QString _defaultFileStem;

  /// The list of the name of the files outputted by the application.
  QVector<QString> _resultFiles;


  
/** @name Dialog Widgets */
//        ==============
//@{
  
  /// Panel for input and validation of the application parameters.
  QGAppParamPanel   * _paramPanel;

  /// Panel for display and direct modification of the command line.
  QGAppCmdLinePanel * _cmdLinePanel;

/**
 * Panel displaying the HMTL documentation of the application and its
 * parameters.
 */
  QGAppDescrPanel   * _descrPanel;

  /// The dialog created by this mediator.
  QDialog * _dialog;

  /// The layout of the dialog, all widgets are stacked vertically.
  QVBoxLayout * _layout;

/**
 * @brief The dialog center tab widget.
 *
 * This tab widget holds the #_paramPanel, #_descrPanel and
 * #_cmdLinePanel (in that order).
 */
  QTabWidget * _tabWidget;

  /// The help button of the dialog button bar.
  QPushButton * _helpButton;

  /// The ok button of the dialog button bar.
  QPushButton * _okButton;

  /// The cancel button of the dialog button bar.
  QPushButton * _cancelButton;

//@}


/** @name Parameter Lines Managment */
//        =========================
//@{

/**
 * @brief A pointer to the QGAbstractAppParamInput instance corresponding to
 * the leading input image file parameter.
 */
  QGAbstractAppParamInput * _inputFileLine;

  /// Pointers on the subwidgets of the param panel.
  std::vector<QGAbstractAppParamInput*> _paramLines;

//@}



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
 *
 * @param other another instance of the class
 */
  QGAppDialogMediator(const QGAppDialogMediator& other);


/**
 * @brief Disabled assignment operator.
 *
 * @param rhs an instance of the class
 */
  QGAppDialogMediator& operator=(const QGAppDialogMediator& rhs);

//@}

// -------------------------------------------------------------------
}; // class QGAppDialogMediator


#endif /* __QGAPPDIALOGMEDIATOR_H_INCLUDED__ */
