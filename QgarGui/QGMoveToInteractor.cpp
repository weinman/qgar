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
 * @file  QGMoveToInteractor.cpp
 * @brief Implementation of class QGMoveToInteractor
 *
 * See file QGMoveToInteractor.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   December 6, 2002  11:31
 * @since  Qgar 2.1
 */



// QGUI
#include "QGMoveToInteractor.h"
#include "QGDocViewer.h"
#include "QGEventRedirector.h"
#include "QGPixmapLayer.h"
#include "QGMainWindow.h"
#include "QGMultiLayerDoc.h"
#include "QGSwapImagesCommand.h"
// QT
#include <QCursor>
#include <QMenu>
#include <QPainter>
#include <QAction>
#include <QMouseEvent>
#include <QGraphicsRectItem>
#include <QAction>
// STD
#include <cmath>
// QGUI
#include "QGMoveToInteractor.moc"



using namespace qgar;
using namespace std;



// ---------------------------------------------------------------------
// U N N A M E D   N A M E S P A C E
// ---------------------------------------------------------------------

namespace {
  
  // WARNING - Qt4
  // If the image has 32bits per pixels the scanLine() pointer must
  // be cast to QRgb due to platform byte order
  void doOR(QImage& dest, const QImage& src) {

    for(int i = 0; i < dest.height(); ++i) {

      uchar * destLine = dest.scanLine(i);
      
      // WARNING
      // Constness problem resolved, but would be better to find
      // another solution.
      uchar * srcLine  = const_cast<uchar *>(src.scanLine(i));
      
      for (int j = 0; j < dest.width(); ++j) {
	
	destLine[j] |= srcLine[j];
      }
    }
  }
}


// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGMoveToInteractor::QGMoveToInteractor(QGMainWindow * main,
				       QGPixmapLayer * layer)
  : QGAbstractDocViewerInteractor(main->docViewer()),
    _doc(main->getCurrentDoc()),
    _canvasRect(0)
{
  _main  = main;
  _layer = layer;
  _docMenu = 0;

  // Build popup menu.
  buildDocMenu();

  // Create custom cursor.
  _cursor = new QCursor( Qt::CrossCursor );

  // Create state filters.
  
  _normalState = new QGEventRedirector<QGMoveToInteractor>
    (this, &QGMoveToInteractor::normalStateFilter);

  _drawingState = new QGEventRedirector<QGMoveToInteractor>
    (this, &QGMoveToInteractor::drawingStateFilter);

  _selectState = new QGEventRedirector<QGMoveToInteractor>
    (this, &QGMoveToInteractor::selectStateFilter);

}


// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

// Default constructor
QGMoveToInteractor::~QGMoveToInteractor() 
{
  dismiss();

  // Delete all stored actions
  for(QVector<QAction *>::iterator it = _actVec.begin();
      it !=_actVec.end(); it++)
    delete(*it);

  delete _docMenu;
  delete _cursor;
}

// ---------------------------------------------------------------------
// T R A N S F O R M A T I O N
// ----------------------------------------------------------------------

void
QGMoveToInteractor::buildDocMenu()
{
  if (_docMenu)
    delete _docMenu;

  _docMenu  = new QMenu(_main);
  QMenu * moveMenu = new QMenu(_docMenu);
			   
  QAction * act;

  list<QGMultiLayerDoc *>::const_iterator it;

  QGMultiLayerDoc * currentDoc = _main->getCurrentDoc();
  
  int id;
  for (it  = _main->accessListOfDocs().begin();
       it != _main->accessListOfDocs().end();
       ++it) {

    if ( currentDoc->name() != (*it)->name() ) {

    
      if (! strcmp( (*it)->activeLayer()->type(), _layer->type() )) {
	
	if ( (*it)->width() == currentDoc->width() 
	     || (*it)->height() == currentDoc->height() ) {

	  act = moveMenu->addAction((*it)->name());
	  QObject::connect(moveMenu, SIGNAL(triggered(QAction*)),
			   this, SLOT(slotClicked(QAction*)));
	  _actVec.push_back(act);
			   
	}      
      }
    }
  }
  
  act = _docMenu->addMenu(moveMenu);
  act->setText(tr("Move to..."));
  QObject::connect(_docMenu, SIGNAL(triggered(QAction*)),
		   this, SLOT(slotCancel(QAction*)));
  _actVec.push_back(act);

}

// -------------------------------------------------------------------

void
QGMoveToInteractor::drawRect(const QPoint& pt) 
{
  QRect rect(_view->mapToScene(_selStartPoint).toPoint(), 
	     _view->mapToScene(_selEndPoint).toPoint());

  rect = rect.normalized();

  QPainterPath painterPath;
  painterPath.addRect(rect);

  _path->setPath(painterPath);
}

// -------------------------------------------------------------------

void
QGMoveToInteractor::createAndExecuteCommand(const QString& moveTarget) 
{
 
  QGMultiLayerDoc * targetDoc = _main->findDoc(moveTarget);
  QGPixmapLayer * pixLayer = 
    dynamic_cast<QGPixmapLayer *>(targetDoc->activeLayer());

  
  // ---------------------
  // Store selected zones.
  // ---------------------

  // Copy the selected area in a new image.
  QImage selCopy = _layer->image().copy(_selRect);

  // Create an empty image corresponding to the cleared selected area.
  QImage blankImg(selCopy);
  blankImg.detach();
  blankImg.fill(0);
  
  // Copy target's pixmap at selected area.
  QImage targetCopy = pixLayer->image().copy(_selRect);


  // /!\ WORK AROUND: On destination image ne selected zone
  // must be replaced by (targetCopy) OR (selCopy)
  // The following function call performs the OR.
  QImage orResult = selCopy.copy();
  doOR(orResult, targetCopy);


  // -------------
  // Perform move.
  // -------------  

  //-- Act on current doc: Create a QGSwapImagesCommand [area] -> [blank]

  // Create, register and execute command.
  QGSwapImagesCommand cmd(_layer, selCopy, blankImg, _selRect.topLeft());
  _doc->registerCommand(cmd);
  cmd.execute();


  //-- Act on current doc: Create a QGSwapImagesCommand [oldArea] -> [newArea]

  // Create, register and execute command.
  //  QGSwapImagesCommand cmd2(pixLayer, targetCopy, selCopy, _selRect.topLeft());
  QGSwapImagesCommand cmd2(pixLayer, targetCopy, orResult, _selRect.topLeft());
  targetDoc->registerCommand(cmd2);
  cmd2.execute();

}


// -------------------------------------------------------------------
// S T A T E     F I L T E R S 
// -------------------------------------------------------------------

bool
QGMoveToInteractor::normalStateFilter(QObject * obj, QEvent * evt)
{
  bool retval = false;

  _tmpPath = _path;

  // Initialize the selection rectangle
  _path = new QGraphicsPathItem(0, _main->docViewer()->scene());
  _path->setPen(QPen(Qt::red));
  _path->setBrush(QBrush(Qt::red, Qt::Dense7Pattern));

  if (QMouseEvent * me = dynamic_cast<QMouseEvent *>(evt)) {

    switch(evt->type()) {

      
    case QEvent::MouseButtonPress:
      
      if (me->button() == Qt::LeftButton) {
	
	// --------------------------------------------------
	// Left-Click: - Fix selection start point.
	//             - Switch to drawing mode.
	// --------------------------------------------------

	// Store selection area starting point.
	_selStartPoint = _view->mapFromScene( me->pos() );

	// Initialize selection end point to start point
	_selEndPoint = _selStartPoint;

	// Switch to drawing state.
	_view->viewport()->removeEventFilter(_normalState);
	_view->viewport()->installEventFilter(_drawingState);

	// Trap event.
	retval = true;
      }
      
      break;

    default:
      /* EMPTY DEFAULT */
      break;
    }
  }

  return retval;
}

// -------------------------------------------------------------------

bool
QGMoveToInteractor::drawingStateFilter(QObject * obj, QEvent * evt)
{
  bool retval = false;

  if (QMouseEvent * me = dynamic_cast<QMouseEvent *>(evt)) {

    QPoint pt;

    switch(evt->type()) {
      
    case QEvent::MouseMove:
    {
      QRect sceneRect = _view->sceneRect().toRect();
      
      //-- Keep cursor within the viewport range.
      
      // This prevent user to modify the view while the segment drawing
      // is not complete.
      // The 1 pixel substracted from the visibleWidth & visibleHeight
      // is mandatory, since viewport ranges is: 
      //    [(0,0), (visibleWidth - 1, visibleHeight - 1)]
      pt = me->pos();    
      if (!isOnCanvas(pt)) {

	// WARNING
	// visibleWidth() considered the same as contentsWidth()
	// visibleHeight() considered the same as contentsHeight()
	// due to the new Scene and View definitions on Qt4
	
	pt.setX(max(0, min(pt.x(), sceneRect.width()  - 1)));
	pt.setY(max(0, min(pt.y(), sceneRect.height() - 1)));
	
	pt = _view->viewport()->mapToGlobal( pt );
	QCursor::setPos(pt);
      }
      
      
      //-- Bind cursor to the content size.
      
      // WARNING: from here on we work with the 'real' mouse coordinate
      // not the ones fixed with QCursor::setPos()
      //      pt = _view->mapFromScene(me->pos());
      QPointF ptf = _view->mapToScene(me->pos());
      pt = ptf.toPoint();      

      // WARNING
      // visibleWidth() considered the same as contentsWidth()
      // visibleHeight() considered the same as contentsHeight()
      // due to the new Scene and View definitions on Qt4
      
      pt.setX(max(0, min(pt.x(), sceneRect.width()  - 1)));
      pt.setY(max(0, min(pt.y(), sceneRect.height() - 1)));
      
      //-- Scroll if necessary
      
      _view->ensureVisible(pt.x(), pt.y(), 10, 10);
      
      
      //-- Draw new rect
      
      // Set new end point.
      _selEndPoint = pt;
      
      // Draw new rect.
      drawRect(_selEndPoint);
      
      // Confirm the draw
      _path->update();

    }
    break;
    
    case QEvent::MouseButtonRelease:
      
      // Disable Mouse tracking.
      //       QApplication::setGlobalMouseTracking(false);
      //       _view->viewport()->setMouseTracking(false);
      
      if (me->button() == Qt::LeftButton) {

	// ----------------------------------
	// Left-Click: Selection is complete.
	// ----------------------------------
	
	// Compute selection rect.
	_selRect = QRect(_selStartPoint, _selEndPoint);
	_selRect = _selRect.normalized();
	_selRect = _view->invZoom(_selRect);
	
	// Switch to selected state.
	_view->viewport()->removeEventFilter(_drawingState);
	_view->viewport()->installEventFilter(_selectState);
	

	retval = true;
      }
      
      
      //       else {
      
      // 	// -------------------------------------------
      // 	// Right-Click, other click: Cancel Selection.
      // 	// -------------------------------------------
      
      // 	// Erase rectangle.
      //  	drawRect(_selEndPoint);
      
      // 	// Switch to normal state.
      // 	_view->viewport()->removeEventFilter(_drawingState);
      // 	_view->viewport()->installEventFilter(_normalState);
      //       }
      break; 
      
    default:
      /* EMPTY DEFAULT */
      break;
      
    }//end--switch
  }//end--dynamic_cast
  
  return retval;
}

// -------------------------------------------------------------------

bool
QGMoveToInteractor::selectStateFilter(QObject * obj, QEvent * evt)
{
  bool retval = false;
  
  if (QMouseEvent * me = dynamic_cast<QMouseEvent *>(evt)) {

    switch( evt->type() ) {
      
    case QEvent::MouseButtonPress:
      
      if ( me->button() == Qt::LeftButton ) {

	// ----------------------------------------------------
	// Left-Click: Discard current sel and start a new one.
	// ----------------------------------------------------

	// Erase selection rectangle
	_doc->removeFromInfoLayer(_tmpPath);
	delete _tmpPath;

	// Dismiss current event filter and install normal state filter.
	_view->viewport()->removeEventFilter(_selectState);
	_view->viewport()->installEventFilter(_normalState);
	
	// Forward current event to the new install event filter.
	retval = normalStateFilter(obj, evt);
	retval = true;
      }


      else if ( me->button() == Qt::RightButton ) {
	
	// -----------------------------------
	// RightClick: Display moveTo options.
	// -----------------------------------
	
	_docMenu->exec(_view->viewport()->mapToGlobal(me->pos()));
	retval = true;
      }

      break;

    default:
      /* EMPTY DEFAULT */
      break;

    }//end--switch

  } //end--dynamic_cast

  return retval;
}


// -------------------------------------------------------------------
// Q G I N T E R A C T O R I F     I M P L
// -------------------------------------------------------------------

void
QGMoveToInteractor::activate()
{
  _view->viewport()->setCursor(*_cursor);
  _view->viewport()->installEventFilter(_normalState);  
}

// ----------------------------------------------------------------------

void
QGMoveToInteractor::dismiss()
{
  // Remove canvas rect from info layer
  if (_tmpPath) {
    _doc->removeFromInfoLayer(_tmpPath);
    _tmpPath = 0;
  }

  // Restore previous cursor.
  _view->viewport()->unsetCursor();

  // Remove event filters.
  _view->viewport()->removeEventFilter(_normalState);
  _view->viewport()->removeEventFilter(_drawingState);  
  _view->viewport()->removeEventFilter(_selectState);  
  
}


// -------------------------------------------------------------------
// S L O T S 
// -------------------------------------------------------------------

void
QGMoveToInteractor::slotClicked(QAction * act)
{
  //-- Perform moveTo to the selected destination.

  createAndExecuteCommand(act->text());
  
  //-- Revert to normal state.

  // Dismiss current event filter and install normal state filter.
  _view->viewport()->removeEventFilter(_selectState);
  _view->viewport()->installEventFilter(_normalState);  
}

// ----------------------------------------------------------------------

void
QGMoveToInteractor::slotCancel(QAction *)
{
  _doc->removeFromInfoLayer(_tmpPath);
  _tmpPath = 0;

  // Dismiss current event filter and install normal state filter.
  _view->viewport()->removeEventFilter(_selectState);
  _view->viewport()->installEventFilter(_normalState);

  // Erase selection rectangle.
   _view->update(_view->zoom(_selRect));
}

// ----------------------------------------------------------------------
