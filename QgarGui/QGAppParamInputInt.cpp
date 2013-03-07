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
 * @file  QGAppParamInputInt.cpp
 * @brief Implementation of class QGAppParamInputInt
 *
 *        See file QGAppParamInputInt.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   June 10, 2003  17:18
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGAppParamInputInt.cpp,v 1.4 2005/07/13 16:30:27 masini Exp $ */



// QGUI
#include "QGAppParamInputInt.h"
#include "QGAppDialogMediator.h"
// QGAR
#include <qgarlib/QgarAppParamDescr.h>
// STL
#include <limits>
// QT
#include <QCheckBox>
#include <QLayout>
#include <QSpinBox>
// QGUI
#include "QGAppParamInputInt.moc"



using namespace qgar;
using namespace std;



// ------------------------------------------------------------------
// C O N S T R U C T O R S
// ------------------------------------------------------------------

// Default constructor
QGAppParamInputInt::QGAppParamInputInt(QgarAppParamDescr * descr,
				       QGAppDialogMediator * med,
				       QWidget * parent,
				       QGridLayout * layout)
  
  : QGAbstractAppParamInput(descr, med, parent, layout)

{
  //-- Create spinbox with bounds and default values matching specs
  
  _spinBox = new QSpinBox(this);

  if (_descr->minValue() != "")
    _spinBox->setMinimum(atoi(_descr->minValue().c_str()));

  else {
    _spinBox->setMinimum(numeric_limits<int>::min());
  }


  if (_descr->maxValue() != "")
    _spinBox->setMaximum(atoi(_descr->maxValue().c_str()));

  else {
    _spinBox->setMaximum(numeric_limits<int>::max());
  }


  if (_descr->defaultValue() != "")
    _spinBox->setValue(atoi(_descr->defaultValue().c_str()));

  _layout->addWidget(_spinBox, _rowCounter, _colCounter);


  //-- If base class widgets are disabled set widgets accordingly.

  this->setEnabled(enabled());


  //-- Detect value changes and notify the mediator

  connect(_spinBox, 
	  SIGNAL(valueChanged(const QString&)),
	  SLOT(valueChanged()));

  reset();
}

// -------------------------------------------------------------------
// D E S T R U C T O R
// -------------------------------------------------------------------

QGAppParamInputInt::~QGAppParamInputInt()
{
  // All allocated object are Qt object dependant on this one and will
  // be destroyed when this instance is destroyed
}


// ------------------------------------------------------------------
//
// ------------------------------------------------------------------

void
QGAppParamInputInt::reset()
{
  if (_descr->defaultValue() != "")
    _spinBox->setValue(atoi(_descr->defaultValue().c_str()));
}

// ------------------------------------------------------------------

void
QGAppParamInputInt::setEnabled(bool enable) 
{
  // Enable all widgets created by base class
  QGAbstractAppParamInput::setEnabled(enable);

  // Enable all widgets created by this class
  _spinBox->setEnabled(enable);

  // Notify mediator
  _mediator->widgetChanged(this);
}

// ------------------------------------------------------------------

string
QGAppParamInputInt::value() const
{
  return string(_spinBox->text().toLatin1());
}

// ------------------------------------------------------------------

void
QGAppParamInputInt::setValue(const std::string& value)
{
  
}


// ------------------------------------------------------------------
// P R O T E C T E D   S L O T   M E M B E R
// ------------------------------------------------------------------

void
QGAppParamInputInt::valueChanged() 
{
  _mediator->widgetChanged(this);
}

// -------------------------------------------------------------------

