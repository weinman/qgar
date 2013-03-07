/*---------------------------------------------------------------------*
 | Graphical user interface QgarGui                                    |
 | Copyright (C) 2003  Qgar Project, LORIA                             |
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
 * @file  QGAppParamInputFile.cpp
 * @brief Implementation of class QGAppParamInputFile
 *
 *        See file QGAppParamInputFile.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   June 10, 2003  14:22
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGAppParamInputFile.cpp,v 1.4 2005/07/13 16:30:26 masini Exp $ */




// QGUI
#include "QGAppParamInputFile.h"
#include "QGAppDialogMediator.h"
// QGAR
#include <qgarlib/QgarAppParamDescr.h>
// XPM
#include <xpm/fileopen2.xpm>
#include <xpm/d_fileopen2.xpm>
// QT
#include <QCheckBox>
#include <QFileDialog>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QToolButton>
// QGUI
#include "QGAppParamInputFile.moc"



using namespace qgar;
using namespace std;



// ------------------------------------------------------------------
// C O N S T R U C T O R S
// ------------------------------------------------------------------

// Default constructor
QGAppParamInputFile::QGAppParamInputFile(QgarAppParamDescr * descr,
					 QGAppDialogMediator * med,
					 QWidget * parent,
					 QGridLayout * layout)

  : QGAbstractAppParamInput(descr, med, parent, layout)

{  
  //-- Create choose file button

  // Build icon set
  QIcon icon;
  icon.addPixmap(QPixmap(fileopen2_xpm), 
		    QIcon::Normal, QIcon::On);
  icon.addPixmap(QPixmap(d_fileopen2_xpm), 
		    QIcon::Disabled, QIcon::On);

  // Create button
  _chooseButton = new QPushButton(icon, "", this);
  _chooseButton->setFocusPolicy(Qt::NoFocus);
  _chooseButton->setFlat(true);
  // Attention: the size argument is randon. actualSize() method
  // will always return a smaller value, never bigger
  _chooseButton->setMaximumSize(icon.actualSize(QSize(50, 50),
						QIcon::Normal,
						QIcon::On));

  //-- Create value field

  _value = new QLineEdit(this);  
  _value->setMinimumSize(QSize(300, 20));
  _value->setSizePolicy(QSizePolicy(QSizePolicy::Maximum,
				    QSizePolicy::Maximum));
  _layout->addWidget(_value, _rowCounter, _colCounter);
  _colCounter++;

  //-- If base class widgets are disabled set widgets accordingly.

  _layout->addWidget(_chooseButton, _rowCounter, _colCounter, Qt::AlignLeft);
  _colCounter++;


  this->setEnabled(enabled());


  //-- Connect button to its slot

  connect(_chooseButton,  SIGNAL(clicked()), SLOT(chooseFile()));
  connect(_value, 
	  SIGNAL(textChanged(const QString&)),
	  SLOT(valueChanged()));

  // Set text field value to the default parameter value.
  reset();
}

// ------------------------------------------------------------------
// D E S T R U C T O R
// ------------------------------------------------------------------

QGAppParamInputFile::~QGAppParamInputFile()
{
  // Qt deletes all QObject having this instance as ancestor for us.
}


// ----------------------------------------------------------------------
//
// ----------------------------------------------------------------------

void
QGAppParamInputFile::reset()
{
  //-- Set default value according to the mediator default file stem
  
  if ( (_mediator->defaultFileStem() != "") 
       && (_descr->passingMode() == QgarAppParamDescr::QGE_OUT)
       && (_descr->defaultValue() != "") ) {
    
    QString filename(_descr->defaultValue().c_str());
    filename = filename.remove("_");
    filename = _mediator->defaultFileStem() + filename;
    _value->setText(filename);  
  }

  else {
    _value->setText("");
  }
}

// ----------------------------------------------------------------------

void
QGAppParamInputFile::setEnabled(bool enable) 
{
  QGAbstractAppParamInput::setEnabled(enable);

  _value->setEnabled(enable);
  _chooseButton->setEnabled(enable);
}

// ----------------------------------------------------------------------

string
QGAppParamInputFile::value() const
{
  return _value->text().toStdString();
}

// ----------------------------------------------------------------------

void
QGAppParamInputFile::setValue(const string& value)
{
  _value->setText(QString(value.c_str()));
}

// ----------------------------------------------------------------------
// P R O T E C T E D   S L O T S
// ----------------------------------------------------------------------

void
QGAppParamInputFile::chooseFile()
{
  QFileDialog qfd(this, QObject::tr("Choose..."), "", QString::null);
  
  //  qfd.showHidden();

  QString fileToOpen = qfd.getOpenFileName(this, 
					   QObject::tr("Choose..."),
					   "", 
					   "");

  qfd.hide();
  
  if(!fileToOpen.isNull())
    _value->setText(fileToOpen);

  // qfd is automatically destroyed on exit of this function member.
}

// ----------------------------------------------------------------------

void
QGAppParamInputFile::valueChanged()
{
  _mediator->widgetChanged(this);
}

// ----------------------------------------------------------------------
