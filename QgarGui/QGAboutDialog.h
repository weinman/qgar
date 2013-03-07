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


#ifndef __QGABOUTDIALOG_H_INCLUDED__
#define __QGABOUTDIALOG_H_INCLUDED__


/**
 * @file     QGAboutDialog.h
 * @brief    Header file of class QGAboutDialog.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date  2001
 * @since Qgar 2.0
 */


/* $Id: QGAboutDialog.h,v 1.7 2005/07/13 16:30:26 masini Exp $ */


// QT
#include <QDialog>


/**
 * @brief Displays a dialog including Qgar version and copyright notice.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date  2001
 * @since Qgar 2.0
 */
class QGAboutDialog

  : public QDialog

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /**
   * @brief The text displayed in the dialog info.
   */
  static const char * const ABOUT_INFO;

  /** 
   * @brief Constructor.
   */
  QGAboutDialog(QWidget * parent = 0);

// -------------------------------------------------------------------
}; // class QGAboutDialog


#endif /* __QGABOUTDIALOG_H_INCLUDED__ */
