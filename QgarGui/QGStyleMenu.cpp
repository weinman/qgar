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
 * @file  QGStyleMenu.cpp
 * @brief Implementation of class QGStyleMenu.
 *
 * See file QGStyleMenu.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 9, 2002  14:28
 * @since  Qgar 2.1
 */



// QT
#include <QApplication>
#include <QStyleFactory>
// QGUI
#include "QGStyleMenu.h"
#include "QGStyleMenu.moc"



// -------------------------------------------------------------------
// S T A T I C     M E M B E R S     I N I T 
// -------------------------------------------------------------------

const QStringList QGStyleMenu::_styleList = QStyleFactory::keys();


// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGStyleMenu::QGStyleMenu(QWidget * parent, const char * name  ) 
  : QMenu(name, parent)
{
  this->setTitle(tr("&Style"));

  _lastActionChecked = new QAction(this);

  int id;
  int idx;

  QString str;
  QStringList::const_iterator it;

  for(idx = 0, it = _styleList.begin(); 
      it != _styleList.end(); 
      idx++, it++) {
    
    // One action for each style is created.
    // They're stored in a vector to be explicitely
    // deleted in the destructor
    QAction *act = new QAction(this);
    str = *it;

    act = addAction(str);
    act->setCheckable(true);

    _actVect.push_back(act);

    connect(this, SIGNAL(triggered(QAction *)), 
		this, SLOT(slotClicked(QAction *)));

  }

}



// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------

QGStyleMenu::~QGStyleMenu() 
{
  // Destroy all QAction * stored in the action vector
  QVector<QAction *>::iterator it = _actVect.begin();
  for(it; it != _actVect.end(); it ++)
  {
    delete *it;
  }
}


// -------------------------------------------------------------------
// P R O T E C T E D     S L O T S 
// -------------------------------------------------------------------

void
QGStyleMenu::slotClicked(QAction * act) 
{  
  if (_lastActionChecked != act)
    _lastActionChecked->setChecked(false);

  _lastActionChecked = act;

  _lastActionChecked->setChecked(true);
  
  if (act == 0)
    return;

  int idx = _styleList.indexOf(act->text());
  QApplication::setStyle(_styleList[idx]);
}


// ----------------------------------------------------------------------
