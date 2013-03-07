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
 * @file  QGVectInteractorBar.cpp
 * @brief Implementation of class QGVectInteractorBar.
 *
 * See file QGVectInteractorBar.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 24, 2002  15:15
 * @since    Qgar 2.1
 */



// QGUI
#include "QGVectInteractorBar.h"
#include "QGEllipseDrawerInteractor.h"
#include "QGLineDrawerInteractor.h"
#include "QGPolylineDrawerInteractor.h"
#include "QGModifyInteractor.h"
#include "QGMainWindow.h"
#include "QGMultiLayerDoc.h"
#include "QGSetInteractorCommand.h"
#include "QGVectorialLayer.h"
// QT
#include <QAction>
// XPM
#include <xpm/arc.xpm>
#include <xpm/polyline.xpm>
#include <xpm/move.xpm>
#include <xpm/segment.xpm>



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGVectInteractorBar::QGVectInteractorBar(QGMainWindow * main, const char * name)
  : QGCommandToolBar(main, name), _main(main)
{

  if (QGVectorialLayer * layer = 
      dynamic_cast<QGVectorialLayer *>(_main->getCurrentDoc()->activeLayer()) ) {

    // Since only one interactor at a time can be set, we enable
    // the exclusive behavior of the toggle buttons in the button group
    //   setExclusiveToggleButtons(true);
    
    // All actions are added to an Action Group to allow exclusive
    // toggled buttons
    QActionGroup * actGroup = new QActionGroup(this);

    // ----------
    // Build Menu
    // ----------

    
    QGCommandIf * cmd;
    QGInteractorIf * interact;


    //-- Move/Modify interactor 
    QAction * moveAction =  new QAction(this);
    moveAction->setIcon(QPixmap(move_xpm));
    moveAction->setText(tr("Select, move, resize"));
    moveAction->setCheckable(true);

    interact = new QGModifyInteractor(_main, layer);
    cmd = new QGSetInteractorCommand(_main, interact);
    insertCommandAction(moveAction, cmd);
    this->addAction(moveAction);
    actGroup->addAction(moveAction); 
   //moveAction->animateClick();
  

    //-- Draw segment interactor
    QAction * drawAction =  new QAction(this);
    drawAction->setIcon(QPixmap(segment_xpm));
    drawAction->setText(tr("Draw a segment"));
    drawAction->setCheckable(true);

    interact = new QGLineDrawerInteractor(_main, layer);
    cmd = new QGSetInteractorCommand(_main, interact);
    insertCommandAction(drawAction, cmd);
    this->addAction(drawAction);
    actGroup->addAction(drawAction);
 
    //-- Draw arc interactor
    QAction * arcAction =  new QAction(this);
    arcAction->setIcon(QPixmap(arc_xpm));
    arcAction->setText(tr("Draw an arc"));
    arcAction->setCheckable(true);

    interact = new QGEllipseDrawerInteractor(_main, layer);
    cmd = new QGSetInteractorCommand(_main, interact);
    insertCommandAction(arcAction, cmd);
    this->addAction(arcAction);
    actGroup->addAction(arcAction);
 
    //-- Draw polyline interactor
    QAction * polyAction =  new QAction(this);
    polyAction->setIcon(QPixmap(polyline_xpm));
    polyAction->setText(tr("Draw a polyline"));
    polyAction->setCheckable(true);
  
    interact = new QGPolylineDrawerInteractor(_main, layer);
    cmd = new QGSetInteractorCommand(_main, interact);
    insertCommandAction(polyAction, cmd);
    this->addAction(polyAction);
    actGroup->addAction(polyAction); 
  }
}


// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

// Default constructor
QGVectInteractorBar::~QGVectInteractorBar() 
{
  // VOID
}

// ----------------------------------------------------------------------
