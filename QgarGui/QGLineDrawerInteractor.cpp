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
 * @file  QGLineDrawerInteractor.cpp
 * @brief Implementation of class QGLineDrawerInteractor.
 *
 * See file QGLineDrawerInteractor.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 30, 2002  19:05
 * @since  Qgar 2.1
 */



// QGUI
#include "QGLineDrawerInteractor.h"
#include "QGCanvasLine.h"
#include "QGDocViewer.h"
#include "QGInsertVectItemCommand.h"
#include "QGMainWindow.h"
#include "QGMultiLayerDoc.h"
#include "QGVectorialLayer.h"
// QT
#include <QCursor>
#include <QPixmap>
#include <QPainter>
#include <QApplication>
#include <QInputDialog>
#include <QMouseEvent>
// XPM
#include <xpm/drawCursor.xpm>
// STD
#include <cmath>



using namespace qgar;
using namespace std;



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGLineDrawerInteractor::QGLineDrawerInteractor(QGMainWindow * main,
					       QGVectorialLayer * layer)
  : QGAbstractDocViewerInteractor(main->docViewer())
{
  _main  = main;
  _layer = layer;

  //-- Initialize filter redirector objects
  
  _normalFilter = new QGEventRedirector<QGLineDrawerInteractor>
    (this, &QGLineDrawerInteractor::normalStateFilter);

  _drawingFilter = new QGEventRedirector<QGLineDrawerInteractor>
    (this, &QGLineDrawerInteractor::drawingStateFilter);    


  _cursor = new QCursor(QPixmap(drawCursor_xpm), 0, 0);
}


// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

// Default constructor
QGLineDrawerInteractor::~QGLineDrawerInteractor() 
{
  dismiss();
  delete _normalFilter;
  delete _drawingFilter;
  delete _cursor;
}


// -------------------------------------------------------------------
// S T A T E     F I L T E R S 
// -------------------------------------------------------------------

bool 
QGLineDrawerInteractor::normalStateFilter(QObject * obj, QEvent * evt)
{
  // Flag indicating if the received event must be trapped by the
  // method (ie. not passed to other filters).
  bool trap = false;

  // Create the line object
  _line = new QGraphicsLineItem(0, _main->docViewer()->scene());
  _line->setPen(QPen(Qt::blue));

  // We trap only mouse left button click event.
  // This event sets the segment-to-be origin.
  if (evt->type() == QEvent::MouseButtonPress) {

    QMouseEvent * me = dynamic_cast<QMouseEvent *>(evt);
    if (me->button() == Qt::LeftButton) {
      
      // Segment origin is the point at current mouse position.
      // First end point is start point so first call to drawLine()
      // will have no effect.
      _startPoint = _view->mapToScene(me->pos()).toPoint();
      _endPoint = _startPoint;
	
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

// -------------------------------------------------------------------


bool
QGLineDrawerInteractor::drawingStateFilter(QObject * obj, QEvent * evt)
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
    if (! isOnCanvas(pt)) {
      pt.setX(max(0, min(pt.x(), sceneRect.width() - 1)));
      pt.setY(max(0, min(pt.y(), sceneRect.height() - 1)));

      pt = _view->viewport()->mapToGlobal( pt );
      QCursor::setPos(pt);
    }


    //-- Bind cursor to the content size.
    
    // WARNING: from here on we work with the 'real' mouse coordinate
    // not the ones fixed with QCursor::setPos()
    //
    // WARNING: considered contentsWidth() = visibleWidth()
    // must be verified
    QPointF ptf = _view->mapToScene(me->pos());
    pt = ptf.toPoint();

    pt.setX(max(0, min(pt.x(), sceneRect.width() - 1)));
    pt.setY(max(0, min(pt.y(), sceneRect.height() - 1)));


    //-- Scroll if necessary

    _view->ensureVisible(pt.x(), pt.y(), 10, 10);


    //-- Draw new line

    _endPoint = pt;
    drawLine( _endPoint );

    // Confirme draw
    _line->update();

    break;
  }

  case QEvent::MouseButtonRelease:
    me = dynamic_cast<QMouseEvent *>(evt);


    // --------------------------------------
    // Segment is defined, insert it in layer
    // --------------------------------------
    if (me->button() == Qt::LeftButton) {
      
      // Insert segment in the document.
      createAndExecuteCommand();

      // Delete the reference line
      _main->docViewer()->scene()->removeItem(_line);

      // Revert to normal state.(Either a segment is defined or the 
      // drawing is cancelled).
      _view->viewport()->removeEventFilter(_drawingFilter);
      _view->viewport()->installEventFilter(_normalFilter);
      
      trap = true;  
    }

    break;

  default:
    /* EMPTY DEFAULT */
    break;
  }

  return trap;
}

// -------------------------------------------------------------------

void
QGLineDrawerInteractor::drawLine(const QPoint& point) 
{
  _line->setLine(_startPoint.x(), _startPoint.y(),
		 point.x(), point.y());
}


// -------------------------------------------------------------------

void
QGLineDrawerInteractor::createAndExecuteCommand() 
{

  // ----------------------
  // Width selection dialog
  // ----------------------
  bool ok;
  int width = QInputDialog::getInteger(_main, tr("Thickness"),
				       tr("Enter the desired line width"),
				       1, 0, 100, 1, &ok);

  // Erase previous line 
  drawLine(_endPoint);

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

  // Apply it to line coordinates.
  QPoint realStart = m.map(_startPoint);
  QPoint realEnd = m.map(_endPoint);


  //-- Create the canvas line.

  QGCanvasLine * line = new QGCanvasLine(0, width);
  line->setLine(realStart.x(), realStart.y(),
 		realEnd.x(), realEnd.y());
  
  
  //-- Create the line insertion command, execute it and repaint.
  
  QGInsertVectItemCommand cmd(_layer, line);
  cmd.execute();
  
  //-- Register command in the current document undolist
  
  _main->getCurrentDoc()->registerCommand(cmd);
}


// -------------------------------------------------------------------
// Q G I N T E R A C T O R I F     I M P L 
// -------------------------------------------------------------------

void
QGLineDrawerInteractor::activate()
{
  // Change Cursor.
  _view->viewport()->setCursor(*_cursor);

  // Set event filter.
  _view->viewport()->installEventFilter(_normalFilter);
}

// ----------------------------------------------------------------------

void 
QGLineDrawerInteractor::dismiss()
{
  // Restore previous cursor.
  _view->viewport()->unsetCursor();

  // Remove all event filters.
  _view->viewport()->removeEventFilter(_normalFilter);
  _view->viewport()->removeEventFilter(_drawingFilter);
}

// ----------------------------------------------------------------------
