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
 * @file  QGPolylineDrawerInteractor.cpp
 * @brief Implementation of class QGPolylineDrawerInteractor.
 *
 * See file QGPolylineDrawerInteractor.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 12, 2002  11:38
 * @since  Qgar 2.1
 */



// QGUI
#include "QGPolylineDrawerInteractor.h"
#include "QGCanvasLine.h"
#include "QGCanvasPolyline.h"
#include "QGDocViewer.h"
#include "QGEventRedirector.h"
#include "QGInsertVectItemCommand.h"
#include "QGMainWindow.h"
#include "QGMultiLayerDoc.h"
#include "QGVectorialLayer.h"
// QT
#include <QPixmap>
#include <QPainter>
#include <QApplication>
#include <QInputDialog>
#include <QPolygon>
// XPM
#include <xpm/drawCursor.xpm>
// STD
#include <cmath>



using namespace std;
using namespace qgar;



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGPolylineDrawerInteractor::QGPolylineDrawerInteractor(QGMainWindow * main,
						       QGVectorialLayer * layer)
  : QGAbstractDocViewerInteractor(main->docViewer())
{
  _main  = main;
  _layer = layer;


  //-- Initialize filter redirector objects
  
  _normalFilter = new QGEventRedirector<QGPolylineDrawerInteractor>
    (this, &QGPolylineDrawerInteractor::normalStateFilter);

  _drawingFilter = new QGEventRedirector<QGPolylineDrawerInteractor>
    (this, &QGPolylineDrawerInteractor::drawingStateFilter);    


  //-- Initialize cursors
  
  _cursor = new QCursor(QPixmap(drawCursor_xpm), 0, 0);
}



// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

// Default constructor
QGPolylineDrawerInteractor::~QGPolylineDrawerInteractor()
{
  dismiss();

  delete _cursor;
  delete _normalFilter;
  delete _drawingFilter;
}



// -------------------------------------------------------------------
// S T A T E     F I L T E R S 
// -------------------------------------------------------------------

bool
QGPolylineDrawerInteractor::normalStateFilter(QObject * obj, QEvent * evt)
{
  // Flag indicating if the received event must be trapped by the
  // method (ie. not passed to other filters).
  bool trap = false;

  // Create the polyline
  _polyline = new QGraphicsPathItem(0, _main->docViewer()->scene());
  _polyline->setPen(QPen(Qt::blue));
  _polyline->setBrush(QBrush(Qt::blue, Qt::NoBrush));

  // We trap only mouse left button click event.
  // This event sets the segment-to-be origin.
  if (evt->type() == QEvent::MouseButtonPress) {

    QMouseEvent * me = dynamic_cast<QMouseEvent *>(evt);
    if (me->button() == Qt::LeftButton) {
      
      // Segment origin is the point at current mouse position.
      // First end point is start point so first call to drawLine()
      // will have no effect.
      QPointF ptf = _view->mapToScene(me->pos());
      _startPoint = ptf.toPoint();

      _endPoint = _startPoint;
      
      // Store first point
      _pointVect.push_back(_startPoint);
      
      // Go to drawing state. Remove current event filter and install
      // drawing event filter
      _view->viewport()->removeEventFilter(_normalFilter);
      _view->viewport()->installEventFilter(_drawingFilter);
      
      // Trap event. Event will not be forwarded to other filters.
      trap = true;
    }

    else
      trap = false;
  }
  
  return trap;
}

// ----------------------------------------------------------------------

bool
QGPolylineDrawerInteractor:: drawingStateFilter(QObject * obj, QEvent * evt)
{
  // Flag set if the received event must be trapped by the
  // method (ie. not passed to other filters).
  bool trap = false;

  QMouseEvent * me;
  QPoint pt;
  switch( evt->type() ) {

  case QEvent::MouseMove:
  {
    me = dynamic_cast<QMouseEvent *>(evt);
    
    QRect sceneRect = _view->sceneRect().toRect();

    //-- Keep cursor within the viewport range.

    // This prevent user to modify the view while the segment drawing
    // is not complete.
    // The 1 pixel substracted from the visibleWidth & visibleHeight
    // is mandatory, since viewport ranges is: 
    //    [(0,0), (visibleWidth - 1, visibleHeight - 1)]
    pt = me->pos();
    if (! isOnCanvas(pt) ) {
      pt.setX(max(0, min(pt.x(), sceneRect.width() - 1)));
      pt.setY(max(0, min(pt.y(), sceneRect.height() - 1)));
      pt = _view->viewport()->mapToGlobal( pt );
      QCursor::setPos(pt);
    }


    //-- Bind cursor to the content size.
    
    // WARNING: from here on we work with the 'real' mouse coordinate
    // not the ones fixed with QCursor::setPos()
    QPointF ptf = _view->mapToScene(me->pos());
    pt = ptf.toPoint();
    pt.setX(max(0, min(pt.x(), sceneRect.width() - 1)));
    pt.setY(max(0, min(pt.y(), sceneRect.height() - 1)));

    //-- Draw new line
    _endPoint = pt;

    drawLine( _endPoint );

    // Confirme draw (update the scene)
    _polyline->update();
   
    break;

  }
  case QEvent::MouseButtonPress:
  {
    me = dynamic_cast<QMouseEvent *>(evt);

    // --------------------------------------
    // Qt::Left Button
    // --------------------------------------
    if (me->button() == Qt::LeftButton) {
      
      _pointVect.push_back(_endPoint);
      _startPoint = _endPoint;
    }


    // --------------------------------------
    // Mid Button
    // --------------------------------------
    else if (me->button() == Qt::MidButton) {

      if (_pointVect.size() > 1) {
	
	// Remove last drawn line
	_main->docViewer()->scene()->removeItem(_polyline);

	// Insert segment in the document.
	createAndExecuteCommand();

	// Revert to normal state.(Either a segment is defined or the 
	// drawing is cancelled).
	_view->viewport()->removeEventFilter(_drawingFilter);
	_view->viewport()->installEventFilter(_normalFilter);
      }
    }

    // ----------------------------
    // Right button
    // -----------------------------
    else {

      // Insert segment in the document
      createAndExecuteCommand();

      // The temporary object must be removed from the scene
      _main->docViewer()->scene()->removeItem(_polyline);

      // Switch to normal state.
      _view->viewport()->removeEventFilter(_drawingFilter);
      _view->viewport()->installEventFilter(_normalFilter);

      // Clear point vector
      _pointVect.clear();
    }

    trap = true;  
    break;
  }
  default:
    /* EMPTY DEFAULT */
    break;
  }

  return trap;
}

// ----------------------------------------------------------------------

void
QGPolylineDrawerInteractor::drawLine(const QPoint& point) 
{
  // Initializes the QPainterPath with the first Polyline point
  QPainterPath path(_pointVect.at(0));

  _polyline->setPen(QPen(Qt::blue));
  
  if (_pointVect.size()  >= 2) {
    
    vector<QPoint>::iterator start(_pointVect.begin());
    vector<QPoint>::iterator end(_pointVect.begin());
    
    for (++end; end != _pointVect.end(); ++start, ++end) {
      path.lineTo(*end);
    }
  }
  path.lineTo(point);

  _polyline->setPath(path);
}


// -------------------------------------------------------------------

void
QGPolylineDrawerInteractor::createAndExecuteCommand() 
{
  // ----------------------
  // Width selection dialog
  // ----------------------
  bool ok;
  int width = QInputDialog::getInteger(_view, tr("Thickness"),
				       tr("Enter the desired line width"),
				       1, 0, 100, 1, &ok);


  // Cancelling dialog cancels the line drawing.
  if (!ok)
    return;


  // ----------------
  // Command Creation
  // ----------------

  //-- Transform content coordinate to real canvas coordinate (zoom).

  // Create an inverse zoom matrix.
  QMatrix m;
  m.scale(_view->zoom(), _view->zoom());
  m = m.inverted();

  //-- Create the polyline canvas line.

  QPolygon ptArray(_pointVect.size());

  vector<QPoint>::iterator it;
  int i;
  for(i=0, it = _pointVect.begin();  it != _pointVect.end(); ++it, ++i) {
  
    ptArray.setPoint(i, (*it));
  }

  //-- Scale points

  ptArray = m.map(ptArray);
  
  QGCanvasPolyline * line = new QGCanvasPolyline(0);
  line->setWidth(width);
  line->setPoints(ptArray);

  
  //-- Create the line insertion command, execute it and repaint.
  
  QGInsertVectItemCommand cmd(_layer, line);
  cmd.execute();
  

  //-- Register command in the current document undolist

  _main->getCurrentDoc()->registerCommand(cmd);

  
  //-- Discard input points
  
  _pointVect.clear();
  
}



// -------------------------------------------------------------------
// Q G I N T E R A C T O R I F     I M P L 
// -------------------------------------------------------------------

void
QGPolylineDrawerInteractor::activate()
{
  // Reset state
  _pointVect.clear();

  // Change Cursor.
  _view->viewport()->setCursor(*_cursor);

  // Set event filter.
  _view->viewport()->installEventFilter(_normalFilter);
}

// ----------------------------------------------------------------------

void 
QGPolylineDrawerInteractor::dismiss()
{
  // Restore previous cursor.
  _view->viewport()->unsetCursor();

  // Remove all event filters.
  _view->viewport()->removeEventFilter(_normalFilter);
  _view->viewport()->removeEventFilter(_drawingFilter);
}

// ----------------------------------------------------------------------
