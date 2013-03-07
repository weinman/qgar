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
 * @file  QGMainToolsToolBar.cpp
 * @brief Implementation of class QGMainToolsToolBar.
 *
 * See file QGMainToolsToolBar.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 11, 2002  09:09
 * @since  Qgar 2?1
 */



// QGUI
#include "QGMainToolsToolBar.h"
#include "QGCommandIf.h"
#include "QGMainWindow.h"
#include "QGMouseTracker.h"
#include "QGMultiLayerDoc.h"
#include "QGSIModeCommand.h"
// QT
#include <QToolButton>
#include <QAction>
// XPM
#include "xpm/superimp.xpm"



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGMainToolsToolBar::QGMainToolsToolBar(QGMainWindow * parent, const char * name)
  : QGCommandToolBar(parent, name), _main(parent)
{
  setMovable(false);

  QGCommandIf * cmd;  
  _siAction = new QAction(QIcon(superimp_xpm),
			  tr("Toggle superimpose/normal mode"),
			  this);
  _siAction->setToolTip(tr("Superimpose mode"));
  _siAction->setStatusTip(tr("Superimpose mode"));
  _siAction->setWhatsThis(tr("Toggle superimpose/normal mode."));
  _siAction->setCheckable(true);

  cmd = new QGSIModeCommand(_main);
  
  insertCommandAction(_siAction, cmd);
  this->addAction(_siAction);
  _main->attach(this);

  updateSIAction();

  //  new QGMouseTracker(this, _main->docViewer());
  this->addWidget(new QGMouseTracker(this, _main->docViewer()));
}




// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


QGMainToolsToolBar::~QGMainToolsToolBar() 
{
  _main->detach(this);
}



// -------------------------------------------------------------------
// T R A N S F O R M A T I O N 
// -------------------------------------------------------------------

void
QGMainToolsToolBar::updateSIAction()
{
  QGMultiLayerDoc * doc = _main->getCurrentDoc();

  if (doc) {
    _siAction->setEnabled(true);

    bool haveSI = (doc->layerCount() > 1);
    _siAction->setChecked(haveSI);
  }

  else {
    _siAction->setEnabled(false);
    _siAction->setChecked(false);
  }
}

// -------------------------------------------------------------------
// M A I N   W I N D O W   O B S E R V E R   I M P L
// -------------------------------------------------------------------

void
QGMainToolsToolBar::mainWindowUpdated(int what)
{
  updateSIAction();
}

// ---------------------------------------------------------------------
