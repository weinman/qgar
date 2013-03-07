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


#ifndef __QGINFOWINDOW_H_INCLUDED__
#define __QGINFOWINDOW_H_INCLUDED__


/**
 * @file     QGInfoVindow.h
 * @brief    Header file of class QGInfoVindow.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Benoit Daviaud">Benoit Daviaud</a>
 * @date     March 13, 2002  21:18
 * @since    Qgar 2.0
 */




// QGUI
class QGCanvasView;
template <class T> class QGEventRedirector;
class QGMainWindow;
class QGVectorialLayer;
// STL
#include <stdexcept>
// QT
#include <QDialog>
#include <QGraphicsScene>
#include <QListWidget>
#include <QList>
#include <QResizeEvent>


/**
 * @class QGInfoWindow QGInfoWindow.h "QGInfoWindow.h"
 * @brief A window displaying information on vectorial items of a
 * displayed layer.
 *
 * This widget monitors the mouse position on a displayed vectorial
 * layer and shows the properties of the items under the mouse pointer.
 * 
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Benoit Daviaud">Benoit Daviaud</a>
 * @date     March 13, 2002  21:18
 * @since    Qgar 2.0
 */
class QGInfoWindow

  : public QDialog

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------

public:

  /// The window default width.
  static const int DEFAULT_WIDTH;

  /// The window default height
  static const int DEFAULT_HEIGHT;


/** @name Constructor */
//        ===========
//@{

/**
 * @brief Default Constructor.
 *
 * The active layer of the main window is retrieved. If the active
 * layer is not a vectorial layer, an exception is thrown.
 *
 * @param main A pointer to a main window instance.
 *
 * @throws std::invalid_argument If the layer displayed by the main
 * window is not a vectorial layer.
 */
  QGInfoWindow(QGMainWindow * main) throw (std::invalid_argument);

//@}



/** @name Destructor */
//        ==========
//@{

  /// Destructor.
  virtual ~QGInfoWindow();

//@}

  

  /// Called when the infoWindow is closed.
  void closeEvent(QCloseEvent* e);

  /// When we're resized.
  void resizeEvent(QResizeEvent* e);

  /// When we're moved.
  void moveEvent(QMoveEvent* e);

  /// To show ourself at the right place.
  virtual void show();

  /// Hide this window.
  virtual void hide();


/**
 * @brief The function member filtering the events of the widget
 * displaying the layer.
 *
 * This function will filter the events of the Document Viewer
 * displaying the active layer. By monitoring these events, it will
 * update the information about the vectorial items in the window.
 *
 * @param obj The object the event is addressed to.
 * @param evt The event to process.
 */
  bool mouseEventFilter(QObject *obj, QEvent *evt);


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------

protected:

/**
 * @brief Computes the text to be displayed in the dialog about a
 * vectorial item.
 *
 * @param i A canvas item pointed by the mouse pointer on the
 * displaying widget.
 */
  QString text(QGraphicsItem* i);

  /// The list box of all info about the pointed item.
  QListWidget* _listWidget;

  /// The last list of pointed item.
  QList<QGraphicsItem*> _lastList;

  /// The last cursor position.
  QPoint _lastPos;

  /// A pointer to the main window.
  QGMainWindow * _main;

  /// The layer displayed in the main window being inspected.
  QGVectorialLayer * _vectLayer;

/**
 * @brief The filter object redirecting events to the
 * mouseEventFilter() function member.
 */
  QGEventRedirector<QGInfoWindow> * _mouseFilter;

// -------------------------------------------------------------------
}; // class QGInfoWindow


#endif /* __QGINFOWINDOW_H_INCLUDED__ */
