/*---------------------------------------------------------------------+
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


#ifndef __QGMAINWINDOW_H_INCLUDED__
#define __QGMAINWINDOW_H_INCLUDED__


/**
 * @file     QGMainWindow.h
 * @brief    Header file of class QGMainWindow.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date     September 25, 2000  16:30
 * @since    Qgar 2.1
 */


/* $Id: QGMainWindow.h,v 1.15 2005/07/13 16:30:28 masini Exp $ */



// QGUI
#include "QGMainWindowSubjectIf.h"
class QGApplicationEntry;
class QGDocViewer;
class QGInteractorIf;
class QGMainWindowObserverIf;
class QGViewMenu;
class QGFileMenu;
class QGEditMenu;
class QGImageMenu;
class QGAlgoMenu;
class QGOptionMenu;
class QGHelpMenu;
class QGMultiLayerDoc;

// STL
#include <list>
#include <stdexcept>
#include <string>

// QT4
#include <QMainWindow>
#include <QVector>
class QMenu;
class QShortcut;
class QProgressDialog;
class QCloseEvent;

using namespace std;

/** 
 * @class QGMainWindow QGMainWindow.h "QGMainWindow.h"
 * @brief The base class for QGar application windows.
 *
 * It sets up the main window and reads the config file as well as
 * providing a menubar, toolbar and statusbar.  An instance of QGView
 * creates your center view, which is connected to the window's Doc
 * object.  QGMainWindow reimplements the methods that QMainWindow
 * provides for main window handling and supports full session
 * management as well as keyboard accelerator configuration by using
 * QAccel.
 *
 * @todo
 * - Implement save()
 * - Implement saveAs()
 * - Implement saveIfModified()
 * - Implement or remove interactive function member
 * - Update class documentation
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   September 25, 2000  16:30
 * @since  Qgar 2.1
 */
class QGMainWindow

  : public QMainWindow,
    public QGMainWindowSubjectIf

{

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name Constructor */
//        ===========
//@{

/**
 * @brief Constructor of QGMainWindow.
 *
 * @param sizeX The desired horizontal window size
 * @param sizeY The desired vertical window size.
 */
  QGMainWindow(int sizeX = 800, int sizeY = 600);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Virtual destructor.
 */
  virtual ~QGMainWindow();
//@}



/** @name Document Management */
//        ===================
//@{

/**
 * @brief Opens a file.
 *
 * @param filename The name of the image file to open.
 *
 * @throw std::exception if an error occured while opening the file.
 */
  void openImage(const QString& filename) throw (std::exception);

/**
 * @brief Close the current document.
 */
  void closeImage();


/**
 * @brief Close an opened image.
 *
 * @param filename The name of the filename attached to the document
 * to be closed.
 */
  void closeImage(const QString& filename);


/**
 * @brief Display the document whose filename is filename
 *
 * @param filename The name of the file the document is created from.
 */
  void changeToImage(const QString& filename);

  
/**
 * @brief Save the current image.
 *
 * The image is save in the file it has been loaded from.
 */
  void saveImage();


/**
 * @brief Save the current image with a different name or format
 *
 * @warning Not yet implemented
 *
 * @param filename The name of the file to save the image in.
 * @param format   A string identifying the format in with the image
 * is to be saved.
 */
  void saveImageAs(const QString& filename, const char * format);


/**
 * @brief Print the image
 */
  void printImage();

//@}

/**
 * @brief Clean exit from the application
 */
  void quit();

 public:
/**
 * @brief Multiply current zoom by a given factor.
 *
 * @param factor The factor to multiply the current zoom level by.
 */
  void incZoom(float factor);


/**
 * @brief Launches a Qgar external application.
 *
 * @param command The command line to be used.
 */
  void launchBatch(QString command, QVector<QString> files);


/**
 * @brief Open a superimposing file.
 *
 * Loads the image and displays it on top of the current document.
 *
 * @param filename The name of the file to open.
 */
  void openSuperimposeImage(QString filename);


  // Handle the close event.
  void closeEvent(QCloseEvent* ce);

/**
 * @brief Refresh the canvas view.
 *
 * Order the document viewer to repaint itself.
 */
  void refreshView();


/** @name Drag'n'Drop */
//        ===========
//@{

  ///to receive drops
  void dropEvent(QDropEvent* e);

  ///called when a drag enters the mainWindow
  void dragEnterEvent(QDragEnterEvent* e);

//@}



/** @name QGMainWindowSubjectIf impl */
//        ==========================
//@{
  virtual void attach(QGMainWindowObserverIf * obs);

  virtual void detach(QGMainWindowObserverIf * obs);

  virtual void notify(Event what);
//@}




/** @name Superimpose Mode */
//        ================
//@{

/**
 * @brief Loads an image file and displays it on top of the current
 * document.
 *
 * @param filename The name of the image file to open.
 */
  void loadSIItems(const QString& filename);


/**
 * @brief Removes the image displayed on top of the current document.
 */
  void deleteSIItems();
  
//@}


/**
 * @brief Change the statusbar contents.
 *
 * @param text The message to be displayed in the status bar.
 */
//  void statusBarMsg(const char * text);
  void statusBarMsg(const QString text);

/** @name QgarApps Callbacks */
//        ==================
//@{

  /// Show a dialog to modify program's parameters
  void interactive();

//@}



/** @name Accessors */
//        =========
//@{

/**
 * @brief Retrieve a pointer on the document being displayed.
 *
 * @return the current document being displayed
 */ 
  QGMultiLayerDoc * getCurrentDoc() const;


/**
 * @brief Get a copy of the last accessed directory.
 *
 * @return The last accessed directory.
 */
  QString getLastDir() const;


/**
 * @brief Retrieve the last accessed directory
 *
 * @return A reference on the last accessed directory.
 */
  const QString& accessLastDir() const;


/**
 * @brief Access to the document list
 *
 * @return A constant reference on the list of the open documents.
 */
  const list<QGMultiLayerDoc *>& accessListOfDocs();


/**
 * @brief Access to the document history list
 *
 * @return A constant reference on the document history list.
 */
  const list<QGMultiLayerDoc *>& accessHistoOfDisplayedDocs();


/** 
 * @brief Access to the zoom factor.
 *
 * @return the current zoom factor.
 */
  float zoom() const {return _zoomFactor;}


/**
 * @brief Retrieve a handle to the document viewer.
 *
 * @return a pointer to the document viewer
 */
  QGDocViewer * docViewer() const;


/**
 * @brief Retrieve a handle to the current interactor
 *
 * @return A pointer to the current interactor.
 */
  const QGInteractorIf * currentInteractor() const;

//@}


/**
 * @brief Sets the current interactor.
 *
 * @param interact The new interactor to be set.
 */
  void setCurrentInteractor(QGInteractorIf * interact);
  

/** 
 * @brief Search a file among the opened files.
 *
 * @return the file if the file is found, and 0 else.
 */
  QGMultiLayerDoc* findDoc(const QString& fileName);

// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

/** @name Toolbars */
//        ========
//@{

/**
 * @brief Toolbar regrouping shortcuts to file management features,
 * zoom and undo/redo system.
 */
  QToolBar * _mainToolBar;

/** 
 * @brief Toolbar regrouping access to the interactors appliabled to
 * the current document.
 */
  QToolBar * _intToolBar;

/**
 * @brief Toolbar holding a set of features dependent of the image
 * file type.
 */
  QToolBar * _viewToolsToolBar;

/**
 * @brief Toolbar regrouping shortcuts to treatments appliable to all
 * document types.
 */
  QToolBar * _mainToolsToolBar;

//@}


/** @name Menus */
//        =====
//@{

/**
 * @brief MenuBar to hold all menus
 */
  QMenuBar * _menuBar;

/**
 * @brief Menu for opening, saving or printing a document or quitting
 * the application.
 */
  QGFileMenu * _fileMenu;

  /// Menu for zooming in or out the document.
  QGEditMenu * _editMenu;

/** 
 * @brief Menu for enabling or diabling some application widgets such
 * as the status bar.
 */
  QGViewMenu * _viewMenu;

  /// Menu offering shortcuts to display an open document.
  QGImageMenu * _imagesMenu;

/**
 * @brief Menu listing all registered algorithms appliable to the
 * current document and its respective action.
 */
  QGAlgoMenu * _algoMenu;

  /// Menu allowing user to set up various options of the application.
  QGOptionMenu * _optionsMenu;

/** 
 * @brief Submenu of the option menu, allowing user to set the style
 * of the widget of the application.
 */
  QMenu * _styleMenu;

  /// Menu offering shortcuts to the online help.
  QGHelpMenu * _helpMenu;

//@}


/** @name Document Storage */
//        ================
//@{
  
/**
 * @brief Remove a document identified by its filename
 *
 * The document is removed from the document list, the history list
 * and is deleted.
 */
  void removeDoc(const QString& filename);

  /// A pointer to the document being displayed.
  QGMultiLayerDoc * _currentDoc;

  /// The list of the open documents.
  list<QGMultiLayerDoc *> _listOfDocs;

/** 
 * @brief An list keeping track of the order in which the documents have
 * been displayed.
 *
 * This list is used to display the previous displayed document when
 * the current document is closed.
 */
  list<QGMultiLayerDoc *> _histoOfDisplayedDocs;

//@}

  /// The name of the last directory accessed by the application.
  QString _lastDir;

  /// The current zoom factor.
  float _zoomFactor;	

  /// The current interactor set.
  QGInteractorIf * _currentInteract;

  /// The document viewer.
  QGDocViewer * _docViewer;

  /// Observer List
  QVector<QGMainWindowObserverIf *> _obsVect;

  /// Save general options.
  void saveOptions();

  /// Read general options.
  void readOptions();


/** @name Widget Initialization */
//        =====================
//@{

  /// Registers hiddable widgets in the View menu
  void initViewMenu();

  /// Creates the menubar.
  void initMenuBar();

  /// Creates the toolbars.
  void initToolBars();

/**
 * @brief Sets up the statusbar. for the main window by initializing a
 * status label.
 */
  void initStatusBar();

  /// Initializes the document object.
  void initDocument();

//@}



/** @name Widget Update */
//        =============
//@{

  /// Refresh the view.
  void updateView();

/**
 * @brief Updates the interactor toolbar when the current document is
 * changed.
 */
  void updateInteractorBar();

/**
 * @brief Updates the utility toolbar when the current document is
 * changed.
 */
  void updateUtilityBar();

/**
 * @brief Refresh the title bar to display the name of the current
 * document.
 */ 
  void refreshTitle();
//@}


/**
 * @brief Clean the history list of displayed image.
 *
 * This function member is called when a document is closed to remove
 * all pointers pointing to it from the history list.
 */
  void cleanHistoryList(QGMultiLayerDoc * doc);

  /// Is there some modified images?
  bool isSomeModifiedImages() const;


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  /// Disabled copy constructor.
  QGMainWindow(const QGMainWindow&);

  /// Disabled assignment operator.
  QGMainWindow& operator=(const QGMainWindow&);

// -------------------------------------------------------------------
}; // class QGMainWindow


#endif /* __QGMAINWINDOW_H_INCLUDED__ */
