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
 * @file  QGInfoWindow.cpp
 * @brief Implementation of class QGInfoWindow.
 *
 * See file QGInfoWindow.h for the interface.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Benoit Daviaud">Benoit Daviaud</a>
 * @date     March 13, 2002  21:18
 * @since    Qgar 2.0
 */



// QGUI
#include "QGInfoWindow.h"
#include "QGCanvasEllipse.h"
#include "QGCanvasLine.h"
#include "QGCanvasPolyline.h"
#include "QGDocViewer.h"
#include "QGEventRedirector.h"
#include "QGMainWindow.h"
#include "QGMultiLayerDoc.h"
#include "QGVectorialLayer.h"
// QT
#include <QApplication>
#include <QAbstractButton>
#include <QListWidget>
#include <QPolygon>


using namespace std;



// -------------------------------------------------------------------
// S T A T I C     M E M B E R     I N I T 
// -------------------------------------------------------------------

const int QGInfoWindow::DEFAULT_WIDTH = 250;

const int QGInfoWindow::DEFAULT_HEIGHT = 150;


// -------------------------------------------------------------------
// C O N S T R U C T O R 
// -------------------------------------------------------------------

QGInfoWindow::QGInfoWindow(QGMainWindow * main) throw (invalid_argument)
{
  
  _main = main;

  // Check if current layer displayed in the main window is of a
  // vectorial type. Raise an exception if not.  
  QGLayerIf * layer = _main->getCurrentDoc()->activeLayer();
  if (QGVectorialLayer * vectLayer = dynamic_cast<QGVectorialLayer *>(layer)) {
    
    _vectLayer = vectLayer;
  }
  else
    throw invalid_argument("Current document main layer is not of vectorial type");

  _mouseFilter = 
    new QGEventRedirector<QGInfoWindow>(this, &QGInfoWindow::mouseEventFilter);


  setWindowTitle("Item's Information");
  _listWidget=new QListWidget(this);
  resize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
  _lastPos=QPoint(0,0);
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------

QGInfoWindow::~QGInfoWindow() 
{
  _main->docViewer()->removeEventFilter(_mouseFilter);
  hide();
  delete _mouseFilter;
}


// -------------------------------------------------------------------
// O T H E R 
// -------------------------------------------------------------------

void
QGInfoWindow::resizeEvent(QResizeEvent* e)
{
  _listWidget->resize(e->size());
}

// -------------------------------------------------------------------

void
QGInfoWindow::closeEvent(QCloseEvent* e)
{ 
  hide();
  e->accept();
}

// -------------------------------------------------------------------
//to garanty that the position is good

void
QGInfoWindow::show()
{
  move(_lastPos);

  //-- Follow mouse position on the canvas view.
  _main->docViewer()->viewport()->installEventFilter(_mouseFilter);

  QDialog::show();
}

// -------------------------------------------------------------------

void
QGInfoWindow::hide()
{
  _main->docViewer()->viewport()->removeEventFilter(_mouseFilter);

  QDialog::hide();
}

// -------------------------------------------------------------------

void
QGInfoWindow::moveEvent(QMoveEvent* e)
{
  _lastPos=e->pos();
}

// -------------------------------------------------------------------

QString QGInfoWindow::text(QGraphicsItem* it)
{
  QString s("");
     QString num;

  if ( QGCanvasLine * line = dynamic_cast<QGCanvasLine *>(it) ) {

    // ----
    // Line
    // ----

    s += tr("line      ");
    s += num.setNum(line->line().x1());
    s += tr(" ");
    s += num.setNum(line->line().y1());
    s += tr(" ");
    s += num.setNum(line->line().x2());
    s += tr(" ");
    s += num.setNum(line->line().y2());
    s += tr("    ");
    s += num.setNum(line->width());
    s += tr("  L=");
    s += num.setNum(line->length());    
  }


  if ( QGCanvasPolyline * polyline = dynamic_cast<QGCanvasPolyline *>(it) ) {

    // --------
    // Polyline
    // --------

    s += tr("polyline ");
    s += num.setNum(polyline->startPoint().x());
    s += tr(" ");
    s += num.setNum(polyline->startPoint().y());
    s += tr(" ");
    s += num.setNum(polyline->endPoint().x());
    s += tr(" ");
    s += num.setNum(polyline->endPoint().y());
    s += tr("    ");
    s += num.setNum(polyline->width());
  }

  if ( QGCanvasEllipse * ellipse = dynamic_cast<QGCanvasEllipse *>(it) ) {

    // -------
    // Ellipse
    // -------

    s += tr("ellipse  ");
    QRect rect((ellipse->boundingRect()).toRect());
    s += num.setNum(rect.bottomLeft().x());
    s += tr(" ");
    s += num.setNum(rect.bottomLeft().y());
    s += tr(" ");
    s += num.setNum(rect.topRight().x());
    s += tr(" ");
    s += num.setNum(rect.topRight().y());
    s += tr("    ");
    s += num.setNum(ellipse->width());

  }

  return s;
}


// -------------------------------------------------------------------

bool
QGInfoWindow::mouseEventFilter(QObject * obj, QEvent * evt)
{
  if ( QMouseEvent * me = dynamic_cast<QMouseEvent *>(evt) ) {


    if ( evt->type() == QEvent::MouseMove ) {

      QPointF realpos(_main->docViewer()->toRealCoords(me->pos()));
      QList<QGraphicsItem*> list = _vectLayer->canvas()->items(realpos);

      if (_lastList!=list){
	_listWidget->clear();
	_listWidget->addItem(tr("type      x1  y1  x2  y2 width"));

	for (QList<QGraphicsItem*>::iterator it=list.begin();it!=list.end();it++){
	    _listWidget->addItem(text(*it));
	}
	_lastList=list;
      }

      
    }
  }

  return false;
}

// -------------------------------------------------------------------
