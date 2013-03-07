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
 * @file  QGModifyInteractor.cpp
 * @brief Implementation of class QGModifyInteractor.
 *
 * See file QGModifyInteractor.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 14, 2002  14:41
 */



// QGUI
#include "QGModifyInteractor.h"
#include "QGDocViewer.h"
#include "QGEventRedirector.h"
#include "QGMainWindow.h"
#include "QGMoveVectItemCommand.h"
#include "QGMultiLayerDoc.h"
#include "QGDeleteVectItemCommand.h"
#include "QGVectorialLayer.h"
#include "QGVectItem.h"
// QT
#include <QApplication>
#include <QGraphicsItem>
#include <QCursor>
#include <QList>
#include <QMouseEvent>
#include <QInputEvent>

using namespace qgar;
using namespace std;



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGModifyInteractor::QGModifyInteractor(QGMainWindow * main, 
				       QGVectorialLayer * layer) 
  : QGAbstractDocViewerInteractor(main->docViewer())
{
  _main  = main;
  _layer = layer;
  _selectedItem = 0;
  _copyItem = 0;

  //-- Initialize filter redirector objects
  
  _normalFilter = new QGEventRedirector<QGModifyInteractor>
    (this, &QGModifyInteractor::normalStateFilter);

  _selectedItemFilter = new QGEventRedirector<QGModifyInteractor>
    (this, &QGModifyInteractor::selectedItemStateFilter);

  _moveFilter = new QGEventRedirector<QGModifyInteractor>
    (this, &QGModifyInteractor::moveStateFilter);

  _resizeFilter = new QGEventRedirector<QGModifyInteractor>
    (this, &QGModifyInteractor::resizeStateFilter);


  //-- Initialize cursors
  
  _oldCursor = 0;
  _cursor = new QCursor(Qt::ArrowCursor);

}


// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

// Default constructor
QGModifyInteractor::~QGModifyInteractor() 
{
  dismiss();
  
  delete _normalFilter;
  delete _selectedItemFilter;
  delete _moveFilter;
  delete _resizeFilter;

  delete _copyItem;
}



// -------------------------------------------------------------------
// A C C E S S 
// -------------------------------------------------------------------

QGraphicsItem *
QGModifyInteractor::selectedItem() const
{
  return _selectedItem;
}

// -------------------------------------------------------------------

void
QGModifyInteractor::setSelectedItem(QGraphicsItem * item)
{

  // Unselected current selected item.
  if (_selectedItem) {

    _selectedItem->setSelected(false);
    refreshItem(_selectedItem);
  }
	
  _selectedItem = item;

  if (_selectedItem) {
    _selectedItem->setSelected(true);
    refreshItem(_selectedItem);
  }

}


// -------------------------------------------------------------------
// H E L P E R S
// -------------------------------------------------------------------

void
QGModifyInteractor::refreshItem(QGraphicsItem * item)
{
  QRect repaintRect = item->boundingRect().toRect();
  repaintRect.adjust(-5, -5, 5, 5);
  
  _layer->update(repaintRect);
}


// -------------------------------------------------------------------
// S T A T E     F I L T E R S 
// -------------------------------------------------------------------

bool
QGModifyInteractor::normalStateFilter(QObject * obj, QEvent * evt)
{
  // Flag indicating if the received event must be trapped by the
  // method (ie. not passed to other filters).
  bool trap = false;

  if (evt->type() == QEvent::MouseButtonPress) {

    QMouseEvent * me = dynamic_cast<QMouseEvent *>(evt);

    if (me->button() == Qt::LeftButton) {

      // --------------------------
      // Left-Click: Item selection
      // --------------------------  
    
      //-- Look up for collisions.

      // Compute cursors 'real position'
      QPoint realPos = _view->toRealCoords( me->pos() );
      
      // Access to the current document canvas.
      QGraphicsScene * canvas = _layer->canvas();

      // Retrieve all objects intersecting with a square of 5 pixels edge.
      QRect selRect(realPos - QPoint(2, 2), realPos + QPoint(2, 2));

      QList<QGraphicsItem*> itemList = canvas->items(selRect);

      if (!itemList.empty()) {

	//-- Set the selected item. 
	// The item selected is the first item of the collision list
	// The item is informed that it is selected thus it can modify
	// its appearence.
	setSelectedItem(itemList.front());

	//-- Change state to 'selectedItem' state

	// Remove current filter and install 'selectedItem' filter.
	_view->viewport()->removeEventFilter(_normalFilter);
	_view->viewport()->installEventFilter(_selectedItemFilter);

	// Enable keyboard event on the viewport.
	_view->viewport()->setFocus();
	
	//-- Prevent the click event to be forwarded.

	trap = true;
      }// if empty()
    }// if leftButton
  }// if MouseButtonPress
  
  return trap;
}

// ---------------------------------------------------------------------

bool
QGModifyInteractor::selectedItemStateFilter(QObject * obj, QEvent * evt)
{
  // Flag indicating if the received event must be trapped by the
  // method (ie. not passed to other filters).
  bool trap = false;

  QInputEvent * ie = dynamic_cast<QInputEvent *>(evt);

  QKeyEvent * ke = dynamic_cast<QKeyEvent *>(ie);

  QMouseEvent * me = dynamic_cast<QMouseEvent *>(ie);

    //  if ( QKeyEvent * ke = dynamic_cast<QKeyEvent *>(evt) ) {
  if ( evt->type() == QEvent::KeyPress ) {

    switch ( evt->type() ) {

    case QEvent::KeyPress:
      
      if ( (ke->key() == Qt::Key_Backspace) || (ke->key() == Qt::Key_Delete) ) {


	// ---------------------
	// Delete selected item.
	// ---------------------
	
	//-- Create and execute command.
	
	QGDeleteVectItemCommand cmd(_layer, _selectedItem);
	
	// Unselect item.
	setSelectedItem(0);

	// Execute command.
	cmd.execute();

	// Register command in the current document undolist
	_main->getCurrentDoc()->registerCommand(cmd);


	//-- Revert to normal state.
	
	// Unset cursor.
	_view->viewport()->unsetCursor();
	
	// Disable key events support
	_view->viewport()->clearFocus();
	    
	// Remove current filter and install 'normal' filter.
	_view->viewport()->removeEventFilter(_selectedItemFilter);
	_view->viewport()->installEventFilter(_normalFilter);
	
	// Trap key event.
	trap = true;
      }
      
      break;

    default:
      /* EMPTY DEFAULT */
      break;
    }
  }

  else if ( me ) { 
    //  else if ( QMouseEvent * me = dynamic_cast<QMouseEvent *>(evt) ) {

    // Compute the location of the mouse pointer on the canvas.
    QPoint realpos( _view->toRealCoords(me->pos()) );

    switch( evt->type() ) {

    case QEvent::MouseMove:

      //-----------------------------------------------------------
      // Mouse-Move: Detect if mouse hovers over the item.
      // Change cursor accordingly.
      //-----------------------------------------------------------

      // Only Canvas item implementing the QGVectItem are movable and
      // resizable. If another item is selected, nothing is performed.
      if ( QGVectItem * item = dynamic_cast<QGVectItem *>(_selectedItem) ) {
	
	// Retrieve rects
	vector<QRect> rectVect(item->computeResizeRects());
	
 	// TopLeft / BottomRight
 	if ( rectVect[1].contains(realpos) || rectVect[5].contains(realpos) ) {	  
	  _view->viewport()->setCursor(Qt::SizeFDiagCursor);
 	}

	// TopCenter / BottomCenter
	else if ( rectVect[2].contains(realpos) || rectVect[6].contains(realpos) ) {
	  _view->viewport()->setCursor(Qt::SizeVerCursor);
	}

	// TopRight BottomLeft
	else if ( rectVect[3].contains(realpos) || rectVect[7].contains(realpos) ) {
	  _view->viewport()->setCursor(Qt::SizeBDiagCursor);
	}
	
	// RightCenter / LeftCenter
	else if ( rectVect[4].contains(realpos) || rectVect[8].contains(realpos) ) {
	  _view->viewport()->setCursor(Qt::SizeHorCursor);
	}

	// Body
	else if ( rectVect[0].contains(realpos) )
	  _view->viewport()->setCursor(Qt::SizeAllCursor);

	// Mouse is outside the item's bounding box.
	else 
	  _view->viewport()->unsetCursor();
      }
      
      break;
      
      
    case QEvent::MouseButtonPress:
      
      if (me->button() == Qt::LeftButton) {
	
	// --------------------------
	// Left-Click: Item selection
	// --------------------------
	
	if ( QGVectItem * item = dynamic_cast<QGVectItem *>(_selectedItem) ) {
	  
	  // Retrieve rects
	  vector<QRect> rectVect(item->computeResizeRects());

	  // 
	  _resizeType = NONE;
	  
	  // TopLeft
	  if ( rectVect[1].contains(realpos) ) {
	    _resizeType = TOP_LEFT;
	  }
	  
	  // TopCenter
	  else if ( rectVect[2].contains(realpos) ) {
	    _resizeType = TOP_CENTER;
	  }
	  
	  // TopRight
	  else if ( rectVect[3].contains(realpos) ) {
	    _resizeType = TOP_RIGHT;
	  }

	  // CenterRight
	  else if ( rectVect[4].contains(realpos) ) {
	    _resizeType = CENTER_RIGHT;
	  }

	  // BottomRight
	  else if ( rectVect[5].contains(realpos) ) {
	    _resizeType = BOTTOM_RIGHT;
	  }

	  // BottomCenter
	  else if ( rectVect[6].contains(realpos) ) {
	    _resizeType = BOTTOM_CENTER;
	  }

	  // BottomLeft
	  else if ( rectVect[7].contains(realpos) ) {
	    _resizeType = BOTTOM_LEFT;
	  }

	  // CenterLeft
	  else if ( rectVect[8].contains(realpos) ) {
	    _resizeType = CENTER_LEFT;
	  }

	  else if ( rectVect[0].contains(realpos) ) {
	    
	    // ----------------
	    // Move interaction
	    // ----------------
	    
	    //-- Switching to move state.
	    
	    // Remove current filter and install 'move' filter.
	    _view->viewport()->removeEventFilter(_selectedItemFilter);
	    _view->viewport()->installEventFilter(_moveFilter);
	    
	    // Forward event to the 'move' filter.
	    moveStateFilter(obj, evt);
	  }

	  else {
	   
	    // ------------------------------
	    // Clicked Outside the selection.
	    // ------------------------------
	    // Unselect current item.
	    // Revert to normal mode and forward the click event as another 

	    
	    _view->viewport()->unsetCursor();
	    setSelectedItem(0);
	    
	    // Disable key events support
	    _view->viewport()->clearFocus();
	    
	    // Remove current filter and install 'normal' filter.
	    _view->viewport()->removeEventFilter(_selectedItemFilter);
	    _view->viewport()->installEventFilter(_normalFilter);
	    
	    // Forward event to the normal state filter
	    normalStateFilter(obj, evt);
	  }

	  
	  if (_resizeType != NONE) {
	    
	    // -------------------
	    // Resize interaction.
	    // -------------------

	    //-- Switching to resize state.

	    // Remove current filter and install 'resize' filter.
	    _view->viewport()->removeEventFilter(_selectedItemFilter);
	    _view->viewport()->installEventFilter(_resizeFilter);
	    
	    // Forward event to the 'resize' filter.
	    resizeStateFilter(obj, evt);

	  }

	} //if dynamic_cast<QGVectItem*>
      } //if LeftButton
      

      else if (me->button() == Qt::RightButton) {      

	// -------------------------------
	// Right-Click: Display popup menu
	// --------------------------------

      }
      
      break;

    default:
      /* EMPTY DEFAULT */
      break;

    } //switch
  
  } //if dynamic_cast
    
  return trap;
}

// ---------------------------------------------------------------------

bool
QGModifyInteractor::moveStateFilter(QObject * obj, QEvent * evt)
{
  // Flag indicating if the received event must be trapped by the
  // method (ie. not passed to other filters).
  bool trap = false;
  
  if ( QMouseEvent * me = dynamic_cast<QMouseEvent *>(evt) ) {
    

    //-- Compute pointer's 'real position'
      
    // Mouse position.
    QPoint pt(me->pos());

    // Mouse location on the canvas.
    QPoint realpos(_view->toRealCoords( me->pos() ));
 
    // Locals needed in the switch.
    QPoint translationVect;
    QRect repaintRect;

    switch ( evt->type() ) {
      

    case QEvent::MouseButtonPress:

      // --------------------------------------
      // Mouse pressed: We set the move origin.
      // --------------------------------------

      // Store move origin.
      _origin  = realpos;
      
      // Update last mouse position.
      _lastPos = realpos;

      // Store a copy of the selected item.
      if (QGVectItem * item = dynamic_cast<QGVectItem *>(_selectedItem) ) {

	_copyItem = item->cloneAsGraphicsItem();

      }

      break;
      

    case QEvent::MouseMove:
    {
      // --------------------------------------
      // Mouse moved: The item is being dragged.
      // --------------------------------------
      // We move the item by ( [current mouse position] - [last position] )
      // and order the repaint of the modified regions.
      // Extra work is done, mostly to prevent mouse pointer to exit
      // viewport range while dragging. This ensures that the interaction
      // will reach a stable state and will not be interrupted.
      
      QRect sceneRect = _view->sceneRect().toRect();

      // ---------------
      // Cursor Handling
      // ---------------
      
      //-- Keep cursor within the viewport range
      
      pt.setX(max(0, min(pt.x(), sceneRect.width() - 1)));
      pt.setY(max(0, min(pt.y(), sceneRect.height() - 1)));
      
      //-- Bind cursor to the content size.
      
      // ----------------
      // Move and repaint
      // ----------------

      // Compute translation vector
      translationVect = realpos - _lastPos;

      // Move the item.

      // ATTENTION
      // The empiric solution to move elements is to divide by 2.0.
      // This is due to the QGraphicsView and QGraphicsScene with the 
      // old zoom system.
      // The zoom system must be changed to respect Qt's QGraphicsView
      // Framework
      _selectedItem->moveBy( translationVect.x()/2.0, translationVect.y()/2.0);

      _layer->update(0, 0,
		     _view->viewport()->width(), 
		     _view->viewport()->height());

      // Update previous position.
      _lastPos = realpos;

      break;

    }  
    case QEvent::MouseButtonRelease:
    {
      // --------------------------------
      // Mouse Release: Move is complete.
      // --------------------------------
      // We create the corresponding command and revert to the
      // selected item state.
      
      { // Necessary block to avoid cmd variable cleanup crossing next
	// case.

	//-- Create command and register it.
	
	QGMoveVectItemCommand cmd(_layer, _selectedItem,
				(realpos - _origin) );


	//-- Register command in the current document undolist
	
	_main->getCurrentDoc()->registerCommand(cmd);

      }
      
      //-- Change state to 'selectedItem' state

      // Remove current filter and install 'selectedItem' filter.
      _view->viewport()->removeEventFilter(_moveFilter);
      _view->viewport()->installEventFilter(_selectedItemFilter);

      break;
    }
    default:
      /* EMPTY DEFAULT */
      break;
      
    }//switch

  } //if dynamic_cast
  return trap;
}

// ---------------------------------------------------------------------

bool
QGModifyInteractor::resizeStateFilter(QObject * obj, QEvent * evt)
{
  // Flag indicating if the received event must be trapped by the
  // method (ie. not passed to other filters).
  bool trap = false;

  // Resize is only available for vector items implementing QGVectItem.
  if ( QGVectItem * vectItem = dynamic_cast<QGVectItem *>(_selectedItem) ) {

    if ( QMouseEvent * me = dynamic_cast<QMouseEvent *>(evt) ) {
      
      QPoint pt( me->pos() );
      QPoint realpos(_view->toRealCoords(me->pos()));
      QRect repaintRect;
     
      switch ( evt->type() ) {

      case QEvent::MouseButtonPress:
      
	// --------------------------------------
	// Mouse pressed: We set the resize origin.
	// --------------------------------------

	// Store resize origin.
	_origin  = realpos;
      
	// Update last mouse position.
	_lastPos = realpos;

	// Store a copy of the selected item.
	if (QGVectItem * item = dynamic_cast<QGVectItem *>(_selectedItem) ) {
	  
	  _copyItem = item->cloneAsGraphicsItem();
	}

	break;


      case QEvent::MouseMove:
      {
	// ---------------------------------------
	// Mouse moved: The item is being resized.
	// ---------------------------------------
      
	QRect sceneRect = _view->sceneRect().toRect();

	// ---------------
	// Cursor Handling
	// ---------------
      
	//-- Keep cursor within the viewport range
      
	pt.setX(max(0, min(pt.x(), sceneRect.width() - 1)));
	pt.setY(max(0, min(pt.y(), sceneRect.height() - 1)));
	pt = _view->viewport()->mapToGlobal( pt );
	QCursor::setPos(pt);
      

	//-- Bind cursor to the content size.
      
	// WARNING: from here on we work with the 'real' mouse coordinate
	// not the ones fixed with QCursor::setPos()
	QPointF ptf = _view->mapToScene( me->pos() );
	pt = ptf.toPoint();

	pt.setX(max(0, min(pt.x(), sceneRect.width() - 1)));
	pt.setY(max(0, min(pt.y(), sceneRect.height() - 1)));

      
	//-- Scroll if necessary.

	_view->ensureVisible(pt.x(), pt.y(), 10, 10);


	// -------------------
	// Resize and repaint.
	// -------------------

	// Store previous bounding rect.
	repaintRect = _selectedItem->boundingRect().toRect();

	// ==================
	// TO BE IMPLEMENTED
	// ==================
	
	// Compute resize factors
	double kx;
	double ky;

	// Perform resize.
	//	vectItem->resize(kx, ky);
	
	// ===
	// END
	// ===


	// Merge previous bounding box with the new one.
	// The merged rectangle is repainted.
	repaintRect = repaintRect.unite(_selectedItem->boundingRect().toRect());

	// Enlarge repaint rect.
	repaintRect.adjust(-10, -10, 10, 10);

	// Repaint the modified rectangle.
	_layer->update(repaintRect.x(), repaintRect.y(),
		       repaintRect.width(), repaintRect.height());


	// Update previous position.
	_lastPos = realpos;

	break;
      
      }
      case QEvent::MouseButtonRelease:

	// ------------------
	// Resize is complete
	// ------------------
	// We create the corresponding command and revert to the
	// selected item state.

	//-- Change state to 'selectedItem' state

	// Remove current filter and install 'selectedItem' filter.
	_view->viewport()->removeEventFilter(_resizeFilter);
	_view->viewport()->installEventFilter(_selectedItemFilter);

	break;

      default:
	/* EMPTY DEFAULT */
	break;
      
      }//switch
    } //if dynamic_cast<QMouseEvent *>
  } //if dynamic_cast<QGVectItem*>

  return trap;
}



// -------------------------------------------------------------------
// Q G I N T E R A C T O R I F     I M P L 
// -------------------------------------------------------------------

void
QGModifyInteractor::activate()
{
  QCursor c = ( _view->viewport()->cursor() );
  _oldCursor = &c;
  _view->viewport()->setCursor(*_cursor);

  // Set event filter.
  _view->viewport()->installEventFilter(_normalFilter);
}

// ----------------------------------------------------------------------

void
QGModifyInteractor::dismiss()
{
  // Restore previous cursor
  _view->viewport()->unsetCursor();

  // Set selected item to 0 (causes to repaint the item as unselected)
  setSelectedItem(0);

  // Remove all event filters.
  // If filter was not set, removing it has no effect.
  _view->viewport()->removeEventFilter(_normalFilter);
  _view->viewport()->removeEventFilter(_selectedItemFilter);  
  _view->viewport()->removeEventFilter(_moveFilter);
  _view->viewport()->removeEventFilter(_resizeFilter);
}

// ----------------------------------------------------------------------
