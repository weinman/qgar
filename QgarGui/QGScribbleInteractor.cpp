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
 * @file  QGScribbleInteractor.cpp
 * @brief Implementation of class QGScribbleInteractor.
 *
 * See file QGScribbleInteractor.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   December 2, 2002  17:38
 * @since  Qgar 2.1
 */



// QGUI
#include "QGScribbleInteractor.h"
#include "QGDocViewer.h"
#include "QGEventRedirector.h"
#include "QGMainWindow.h"
#include "QGMultiLayerDoc.h"
#include "QGPixmapLayer.h"
#include "QGSwapImagesCommand.h"
// STL
#include <algorithm>
#include <numeric>
// QT
#include <QCursor>
#include <QPainter>
#include <QMouseEvent>
// XPM
#include <xpm/drawCursor.xpm>



using namespace std;
using namespace qgar;



// ---------------------------------------------------------------------
// U N N A M E D   N A M E S P A C E
// ---------------------------------------------------------------------

namespace
{


  /**
   * @brief Compares two points and returns the top-left-most point.
   *
   * This method is used by computeBoundingRect() to compute the top left corner
   * of the bounding box of a set of points.
   *
   * @param a The first point to be compared.
   * @param b The second point to be compared
   *
   * @return The top-left-most point.
   */
  QPoint computeTopLeft(const QPoint& a, const QPoint& b)
  {
    return QPoint( min( a.x(), b.x() ), min( a.y(), b.y() ) );
  }
  
  /**
   * @brief Compares two points and returns the bottom-right-most
   * point.
   *
   * This method is used by computeBoundingRect() to compute the
   * bottom right corner of the bounding box of a set of points.
   *
   * @param a The first point to be compared.
   * @param b The second point to be compared
   *
   * @return The Bottom-Right-most point.
   */
  QPoint computeBottomRight(const QPoint& a, const QPoint& b)
  {
    return QPoint( max( a.x(), b.x() ), max( a.y(), b.y() ) );
  }

  /**
   * @brief Computes the bounding rectangle of a set of points.
   *
   * @param ptVect The set of points.
   *
   * @return The bounding rectangle.
   */
  QRect computeBoundingRect(const vector<QPoint>& ptVect)
  {
    // Compute the top left point of the rectangle bounding the
    // points.
    QPoint topLeft = accumulate(ptVect.begin(), ptVect.end(),
				ptVect.front(),
				computeTopLeft);

    // Compute the top left point of the rectangle bounding the
    // points.
    QPoint bottomRight = accumulate(ptVect.begin(), ptVect.end(),
				    ptVect.front(),
				    computeBottomRight);
    
    return QRect(topLeft, bottomRight);
  }


} // unnamed namespace


// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

QGScribbleInteractor::QGScribbleInteractor(QGMainWindow * main, 
					   QGPixmapLayer * layer,
					   const QColor& color)

  : QGAbstractDocViewerInteractor(main->docViewer()),
    _color(color)

{
  // Store pointers
  _main = main;
  _pixLayer = layer;

  // Create event filter.
  _normalFilter =  new QGEventRedirector<QGScribbleInteractor>
    (this, &QGScribbleInteractor::normalStateFilter);

  // Create cursor.
  _drawCursor = new QCursor(QPixmap(drawCursor_xpm),0, 0);
}

// ---------------------------------------------------------------------

QGScribbleInteractor::QGScribbleInteractor(QGMainWindow * main, 
					   QGPixmapLayer * layer,
					   int colorIdx)

  : QGAbstractDocViewerInteractor(main->docViewer()),
    _colorIdx(colorIdx)

{

  // Store pointers
  _main = main;
  _pixLayer = layer;


  // Create event filter.
  _normalFilter =  new QGEventRedirector<QGScribbleInteractor>
    (this, &QGScribbleInteractor::normalStateFilter);


  // Create cursor.
  _drawCursor = new QCursor(QPixmap(drawCursor_xpm),0, 0);
}

// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

// Default constructor
QGScribbleInteractor::~QGScribbleInteractor() 
{
  dismiss();

  delete _normalFilter;
  delete _drawCursor;
}



// -------------------------------------------------------------------
// S T A T E     F I L T E R 
// -------------------------------------------------------------------

bool
QGScribbleInteractor::normalStateFilter(QObject * obj, QEvent * evt)
{
  static bool drawing = false;

  if ( QMouseEvent * me = dynamic_cast<QMouseEvent *>(evt) ) {

    QPoint pt;
    QPoint realpos( _view->toRealCoords( me->pos() ) );
    
    // repaint rectangle is 5px wide.
    // Empirical value that seems to repaint correctly the pixel at
    // any zoom level. Future code will fix that.
    QRect repaintRect(-2, -2, 5, 5);

    switch ( evt->type() ) {

    case QEvent::MouseButtonPress:
      
      // Store pixel.
      _pointVect.push_back(realpos);
      _idxVect.push_back(_pixLayer->image().pixelIndex(realpos.x(), realpos.y()));
	  
	  
      // Draw pixel
      _pixLayer->image().setPixel(realpos.x(), realpos.y(), _colorIdx);
      _pixLayer->update(repaintRect);
      drawing = true;
      break;


    case QEvent::MouseMove:
      if (drawing) {

	QRect sceneRect = _view->sceneRect().toRect();

	//-- Keep cursor within the viewport range.
	
	// This prevent user to modify the view while the segment drawing
	// is not complete.
	// The 1 pixel substracted from the visibleWidth & visibleHeight
	// is mandatory, since viewport ranges is: 
	//    [(0,0), (visibleWidth - 1, visibleHeight - 1)]
	pt = me->pos();
	if (! isOnCanvas(pt) ) {
	  pt.setX(max(0, min(pt.x(), sceneRect.width()  - 1)));
	  pt.setY(max(0, min(pt.y(), sceneRect.height() - 1)));
	  pt = _view->viewport()->mapToGlobal( pt );
	  QCursor::setPos(pt);
	}
      

	//-- Bind cursor to the content size.
	
	// WARNING: from here on we work with the 'real' mouse coordinate
	// not the ones fixed with QCursor::setPos()
	QPointF ptf = _view->mapToScene(me->pos());
	pt = ptf.toPoint();

	pt.setX(max(0, min(pt.x(), sceneRect.width()  - 1)));
	pt.setY(max(0, min(pt.y(), sceneRect.height() - 1)));


	//-- Scroll if necessary
	
	_view->ensureVisible(pt.x(), pt.y(), 10, 10);


	//-- Paint pixel
	
	repaintRect.moveCenter(_view->toRealCoords(me->pos()));

	//-- Store pixel.
	
	_pointVect.push_back(realpos);
	_idxVect.push_back(_pixLayer->image().pixelIndex(realpos.x(), realpos.y()));
	  
	
	//-- Draw pixel

	_pixLayer->image().setPixel(realpos.x(), realpos.y(),
	_colorIdx);
	_pixLayer->update(repaintRect);	        
      }
      break;

    case QEvent::MouseButtonRelease:
      drawing = false;
      { // Necessary block to avoid cmd variable cleanup crossing next
	// case.
      
	//-- Create command.
	
	// Recompute previous background.
	QPoint pixPos;
	
	// Recreate previous image.
	QImage oldImg = plotPoints(_pointVect,
				   _idxVect,
				   pixPos);

	
	// Copy new modified area
	QImage newImg = _pixLayer->image().copy(pixPos.x(),
						pixPos.y(),
						oldImg.width(),
						oldImg.height());

	// Create command and register it.
	QGSwapImagesCommand cmd(_pixLayer, oldImg, newImg, pixPos);
	_main->getCurrentDoc()->registerCommand(cmd);
      }

      //-- Cleanup

      _pointVect.clear();
      _idxVect.clear();
      
      break;

    default:
      /* EMPTY DEFAULT */
      break;
    }
  }

  return false;
}


// -------------------------------------------------------------------
// O T H E R
// -------------------------------------------------------------------

QImage
QGScribbleInteractor::plotPoints(const vector<QPoint>& ptVect,
				 const vector<int>& colorVect,
				 QPoint& position) const
{

  //-- Compute the bounding rectangle of the points.

  QRect bRect = computeBoundingRect(ptVect);

  // Store top left point of the bounding rect.
  position = bRect.topLeft();
  
  // Create a new pixmap with the same dimensions as the bounding rect
  // and the same color depth as the given pixmap.
  QImage modifiedArea = _pixLayer->image().copy(bRect);

  
  //-- Plot the set of points.

  // Temporary point
  QPoint px;
  vector<QPoint>::const_reverse_iterator ptIt;
  vector<int>::const_reverse_iterator colorIt;

  // Iterate on all the points in reverse order.
  for (ptIt = ptVect.rbegin(), colorIt = colorVect.rbegin();
       ptIt != ptVect.rend(); 
       ++ptIt, ++colorIt) {
    
    // Translate point
    px = (*ptIt) - position;

    // Put pixel.
    modifiedArea.setPixel( px.x(), px.y(), (*colorIt));
  }
 
  return modifiedArea;
}

// -------------------------------------------------------------------
// Q G I N T E R A C T O R     I M P L 
// -------------------------------------------------------------------

void
QGScribbleInteractor::activate()
{
  _view->viewport()->setCursor(*_drawCursor);

  _view->viewport()->installEventFilter(_normalFilter);
}

// ----------------------------------------------------------------------

void
QGScribbleInteractor::dismiss()
{
  _view->viewport()->unsetCursor();
  _view->viewport()->removeEventFilter(_normalFilter);
}


// ----------------------------------------------------------------------

