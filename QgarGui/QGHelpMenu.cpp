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
 * @file  QGHelpMenu.cpp
 * @brief Implementation of class QGHelpMenu
 *
 *        See file QGHelpMenu.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 10, 2002  14:42
 * @since Qgar 2.1
 */



// QGUI
#include "QGHelpMenu.h"
#include "QGShowAboutCommand.h"
#include "QGSimpleCommand.h"
// QT
#include <QWhatsThis>



// ---------------------------------------------------------------------
// U N N A M E D   N A M E S P A C E
// ---------------------------------------------------------------------

namespace
{

  /**
   * @brief Redirection structure used to build a QGSimpleCommand
   * calling QWhatsThis::enterWhatsThisMode()
   *
   * @since Qgar 2.1
   */
  struct Redirector
  {
    /**
     * @brief Executes QWhatsThis::enterWhatsThisMode()
     */
    void operator()() {
      QWhatsThis::enterWhatsThisMode();
    }
  };

} // unnamed namespace

// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGHelpMenu::QGHelpMenu(QWidget * parent, const char * name) 
  : QGMenu(parent, name)
{  
  this->setTitle(tr("&Help"));

  // Create a simple command that calls enterWhatsThisMode
  // And register it in the menu.
  static Redirector redirect;

  QGCommandIf * cmd;
  cmd = new QGSimpleCommand<Redirector>(&redirect, &Redirector::operator());
  insertCommandItem(cmd, QObject::tr("What's This"));

  insertSeparator();

  cmd = new QGShowAboutCommand();
  insertCommandItem(cmd, QObject::tr("&About Qgar"));
}

// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------

QGHelpMenu::~QGHelpMenu()
{
  /* EMPTY */
}

// ----------------------------------------------------------------------

