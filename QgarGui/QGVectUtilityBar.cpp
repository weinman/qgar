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
 * @file  QGVectUtilityBar.cpp
 * @brief Implementation of class QGVectUtilityBar.
 *
 * See file QGVectUtilityBar.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 28, 2002  15:13
 */



// QGUI
#include "QGVectUtilityBar.h"
#include "QGCommandIf.h"
#include "QGInfoWindowCommand.h"
#include "QGMainWindow.h"
#include "QGMultiLayerDoc.h"
#include "QGSkelModeCommand.h"
#include "QGVectorialLayer.h"
// QT
#include <QAction>
// XPM
#include <xpm/info.xpm>
#include <xpm/skull.xpm>



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGVectUtilityBar::QGVectUtilityBar(QGMainWindow * parent, const char * name)
  : QGCommandToolBar(parent, name)//, _main(parent)
{
  // ----------
  // Build Menu
  // ----------

  QGCommandIf * cmd;

  //-- Skeleton view selector interactor

  QAction  * skelAction =  new QAction(QPixmap(skull),
				       tr("Toggle skeleton / normal mode"),
				       this);
  skelAction->setCheckable(true);


  QGLayerIf * layer = parent->getCurrentDoc()->layerAt(0);

  if (QGVectorialLayer * vectLayer = dynamic_cast<QGVectorialLayer *>(layer)) {
    cmd = new QGSkelModeCommand(vectLayer);
    skelAction->setChecked(vectLayer->skelModeOn());
  }
  else 
    skelAction->setEnabled(false);

  insertCommandAction(skelAction, cmd);
  this->addAction(skelAction);

  //-- Vector items info window selector

  QAction * infoWndAction = new QAction(QPixmap(info_xpm),
				       tr("Toggle display item's informations"),
				       this);
  infoWndAction->setCheckable(true);

  cmd = new QGInfoWindowCommand(parent);
  insertCommandAction(infoWndAction, cmd);
  this->addAction(infoWndAction);
}

// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

// Default constructor
QGVectUtilityBar::~QGVectUtilityBar() 
{ /* EMPTY */ }



// ----------------------------------------------------------------------

