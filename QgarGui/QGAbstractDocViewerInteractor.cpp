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
 |   LORIA - �quipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-l�s-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/


/**
 * @file  QGAbstractDocViewerInteractor.cpp
 * @brief Implementation of class QGAbstractDocViewerInteractor.
 *
 * See file QGAbstractDocViewerInteractor.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   December 20, 2002  10:18
 * @since  Qgar 2.1
 */


// QGUI
#include "QGAbstractDocViewerInteractor.h"
#include "QGDocViewer.h"



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------


// Default constructor
QGAbstractDocViewerInteractor::QGAbstractDocViewerInteractor(QGDocViewer* view) 
{ 
  _view = view; 
}


bool 
QGAbstractDocViewerInteractor::isOnCanvas(const QPoint& pt)
{
  QRect visibleScene = _view->sceneRect().toRect();

  return ( (pt.x() >= 0) 
	   && (pt.y()>= 0)
	   && (pt.x() < visibleScene.width())
	   && (pt.y() < visibleScene.height()) );
}


// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------


// Default constructor
QGAbstractDocViewerInteractor::~QGAbstractDocViewerInteractor() 
{
  /* EMPTY */
}


// ----------------------------------------------------------------------
