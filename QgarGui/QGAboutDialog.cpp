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
 * @file  QGAboutDialog.cpp
 * @brief Implementation of class QGAboutDialog.
 *
 *        See file QGAboutDialog.h for the interface.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date  2001
 * @since Qgar 2.0
 */



// QT
#include <QLabel>
#include <QPushButton>
// QGUI
#include "QGAboutDialog.h"



const char * const  QGAboutDialog::ABOUT_INFO = "Version 4.0\n\nCopyright (C) 2001-2008\n\
Team QGAR\nLORIA\nBP 101\n54602 Villers-lès-Nancy Cedex\nFrance\n\
\nContact: qgar-contact@loria.fr";


// ----------------------------------------------------------------------
// C O N S T R U C T O R S
// ----------------------------------------------------------------------


QGAboutDialog::QGAboutDialog (QWidget* parent)

  : QDialog(parent)

{
  setWindowModality(Qt::WindowModal);
  QString info(ABOUT_INFO);
  
  setWindowTitle(tr("About Qgar"));
  resize(400, 300);
  setFixedSize(size());
  
  QLabel * label = new QLabel(this);
  
  label = new QLabel("Qgar Software", this);
  label->setFont(QFont("helvetica", 18, QFont::Bold));
  label->setAlignment(Qt::AlignHCenter);
  label->setGeometry(50, 30, 290, 180);
  
  label = new QLabel(info, this);
  label->setAlignment(Qt::AlignHCenter);
  label->setGeometry(50, 65, 290, 180);
  
  QFrame * frame = new QFrame(this);
  frame->setLineWidth(1);
  frame->setFrameStyle(QFrame::HLine | QFrame::Sunken);
  frame->setGeometry(5, 235, 390, 5);
  
  
  QPushButton * button = new QPushButton("OK", this);
  button->setGeometry(width() / 2 - 50, height() - 45, 75, 32);
  button->setDefault(true);
  connect(button, SIGNAL(released()), this, SLOT(accept()));
  button->setFocus();
}


// ----------------------------------------------------------------------
