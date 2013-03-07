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
 * @file  QGPixmapInteractorBar.cpp
 * @brief Implementation of class QGPixmapInteractorBar.
 *
 * See file QGPixmapInteractorBar.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 28, 2002  09:18
 * @since    Qgar 2.1
 */



// QGUI
#include "QGPixmapInteractorBar.h"
#include "QGCommandIf.h"
#include "QGHelpers.h"
#include "QGPixmapLayer.h"
#include "QGMainWindow.h"
#include "QGMoveToInteractor.h"
#include "QGMultiLayerDoc.h"
#include "QGNullInteractor.h"
#include "QGScribbleInteractor.h"
#include "QGSetInteractorCommand.h"
// QT
#include <QAction>
// XPM
#include <xpm/eraser.xpm>
#include <xpm/move.xpm>
#include <xpm/pencil.xpm>
#include <xpm/rectangle_select.xpm>



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

QGPixmapInteractorBar::QGPixmapInteractorBar(QGMainWindow * parent, 
					     const char * name)

  : QGCommandToolBar(parent, name),
    _main(parent)

{
  if (QGPixmapLayer * layer = 
      dynamic_cast<QGPixmapLayer *>(_main->getCurrentDoc()->activeLayer()))
  {
	
    // Since only one interactor at a time can be set, we enable
    // the exclusive behavior of the toggle buttons in the button group
    setExclusiveToggleButtons(true);
    
    // All actions are added to an Action Group to allow exclusive
    // toggled buttons
    QActionGroup * actGroup = new QActionGroup(this);

    // ----------
    // Build Menu
    // ----------

    QAction * actMove;
    QGCommandIf * cmd;
    QGInteractorIf * interact;

    actMove = new QAction(QPixmap(move_xpm), 
			    tr("No tool"),
			    this);
    actMove->setCheckable(true);

    interact = new QGNullInteractor();
    cmd = new QGSetInteractorCommand(_main, interact);

    insertCommandAction(actMove, cmd);
    this->addAction(actMove);
    actGroup->addAction(actMove);

    // First item is enabled.
    //    actButton->

    
    //-- Rectangle selection interactor
    
    QAction * actSelect = new QAction(QPixmap(rectangleSelect_xpm),
			    tr("cut and move"),    
			    this);
    actSelect->setCheckable(true);
    
    interact = new QGMoveToInteractor(_main, layer);
    cmd = new QGSetInteractorCommand(_main, interact);
    
    insertCommandAction(actSelect, cmd);
    this->addAction(actSelect);
    actGroup->addAction(actSelect);
    
    //-- Draw something
    QAction * actDraw;
    actDraw = new QAction(QPixmap(pencil_xpm),
			    tr("Draw something"),    
			    this);
    actDraw->setCheckable(true);

    // Check if pixmap is a bitmap.
    if (layer->image().numColors() == 2)
      interact = new QGScribbleInteractor(_main, layer, 1);
    else
      interact = new QGScribbleInteractor(_main, layer, 0);
    
    cmd = new QGSetInteractorCommand(_main, interact);
    insertCommandAction(actDraw, cmd);
    this->addAction(actDraw);
    actGroup->addAction(actDraw);
    
    //-- Erase something
    QAction * actErase;
    actErase =  new QAction(QPixmap(eraser_xpm),
			     tr("Erase something"),
			     this);
    actErase->setCheckable(true);

    // Check if pixmap is a bitmap.
    if (layer->image().numColors() == 2)
      interact = new QGScribbleInteractor(_main, layer, 0);
    
    else
      interact = new QGScribbleInteractor(_main, layer, 255);
    
    cmd = new QGSetInteractorCommand(_main, interact);
    insertCommandAction(actErase, cmd);
    this->addAction(actErase);
    actGroup->addAction(actErase);

} //if -- dynamic_cast<QGPixmapLayer *>
}

// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

// Default constructor
QGPixmapInteractorBar::~QGPixmapInteractorBar() 
{
  // VOID
}

// ----------------------------------------------------------------------

