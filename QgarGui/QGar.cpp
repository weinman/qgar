/*---------------------------------------------------------------------+
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
 * @file  QGar.cpp
 * @brief Qgar User Interface (QgarGui) main program.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   September 25, 2000  15:59
 * @since  Qgar 2.0
 */



// QT
#include <QApplication> 
#include <QTimer>
// QGUI
#include "QGMainWindow.h"

/**
 * @brief  Qgar User Interface (QgarGui) main program.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   September 25, 2000  15:59
 * @since  Qgar 2.0
 */

int main(int argc, char *argv[])
{
  QTimer timer;
  QGMainWindow *myMainWin;
  QApplication app(argc, argv, "QGar");
  int result;

  QApplication::setOverrideCursor(Qt::WaitCursor);

  while (timer.isActive())
    app.processEvents();

   myMainWin = new QGMainWindow;
   myMainWin->setMinimumSize(QSize(800, 600));
   myMainWin->show();

   QApplication::restoreOverrideCursor();
   
   result = app.exec();
   
   return result;
}
