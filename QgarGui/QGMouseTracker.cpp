/*---------------------------------------------------------------------*
 | Graphical user interface QgarGui                                    |
 | Copyright (C) 2004  Qgar Project, LORIA                             |
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
 * @file  QGMouseTracker.cpp
 * @brief Implementation of class QGMouseTracker.
 *
 * See file QGMouseTracker.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   May 12, 2004  17:11
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGMouseTracker.cpp,v 1.3 2005/07/13 16:30:28 masini Exp $ */



// QGUI
#include "QGMouseTracker.h"
#include "QGDocViewer.h"
// QT
#include <QApplication>
#include <QMouseEvent>
// STD
#include <iostream>



using namespace std;



// ------------------------------------------------------------------
// C O N S T R U C T O R S
// ------------------------------------------------------------------

// Default constructor
QGMouseTracker::QGMouseTracker(QWidget * parent, QGDocViewer * view)
  : QLabel("(0,0)", parent), _viewer(view)
{
  // Creates a widget to hold the events in the viewport
  // of QGDocViewer. A direct map from QGDocViewer considers
  // mouse events only in the border of the QGDocViewer
  // widget.


  _wd = _viewer->viewport();

  _wd->setMouseTracking(true);
  _wd->installEventFilter(this);

}



// ------------------------------------------------------------------
// D E S T R U C T O R
// ------------------------------------------------------------------

QGMouseTracker::~QGMouseTracker()
{
  delete _wd;
}

// ---------------------------------------------------------------------
// E V E N T   F I L T E R
// ----------------------------------------------------------------------

bool
QGMouseTracker::eventFilter (QObject * watched, QEvent * e)
{
  if (e->type() == QEvent::MouseMove) {
   
    if ( QMouseEvent * me = dynamic_cast<QMouseEvent *>(e) ) {

      QPoint pt = _viewer->toRealCoords(me->pos());

      QString str = QString("(%1, %2)").arg(pt.x()).arg(pt.y());
      setText(str);
    }
  }

  return false;
}

// ----------------------------------------------------------------------
