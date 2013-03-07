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
 * @file  QGAppParamInputReal.cpp
 * @brief Implementation of class QGAppParamInputReal
 *
 *        See file QGAppParamInputReal.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   July 4, 2003  15:41
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGAppParamInputReal.cpp,v 1.3 2005/07/13 16:30:27 masini Exp $ */



// QGUI
#include "QGAppParamInputReal.h"
#include "QGAppDialogMediator.h"
// QGAR
#include <qgarlib/QgarAppParamDescr.h>
// QT
#include <QLayout>
#include <QLineEdit>
#include <QValidator>
// QGUI
#include "QGAppParamInputReal.moc"


using namespace std;
using namespace qgar;



// ------------------------------------------------------------------
// C O N S T R U C T O R S
// ------------------------------------------------------------------

// Default constructor
QGAppParamInputReal::QGAppParamInputReal(qgar::QgarAppParamDescr * descr,
					 QGAppDialogMediator * med,
					 QWidget * parent,
					 QGridLayout * layout)

  : QGAbstractAppParamInput(descr, med, parent, layout)
{
  //-- create value box and validator

  _value = new QLineEdit(this);
  QDoubleValidator * valid = new QDoubleValidator(_value);
  _value->setValidator(valid);

  _value->setAlignment(Qt::AlignRight);
  _value->setSizePolicy(QSizePolicy(QSizePolicy::Maximum,
				    QSizePolicy::Maximum));

  //-- Set value bounds and default value

  if (_descr->defaultValue() != "")
    _value->setText(_descr->defaultValue().c_str());


  double val;
  bool ok; 

  val = QString(_descr->minValue().c_str()).toDouble(&ok);
 
  if (ok)
    valid->setBottom(val);

  val = QString(_descr->maxValue().c_str()).toDouble(&ok);
  if (ok)
    valid->setTop(val);
  

  this->setEnabled(enabled());
  

  _layout->addWidget(_value);

  // Connect line edit to the slot that fwds notification to the
  // mediator
  connect(_value, 
	  SIGNAL(textChanged(const QString&)),
	  SLOT(valueChanged()));
}

// ------------------------------------------------------------------
// D E S T R U C T O R
// ------------------------------------------------------------------

QGAppParamInputReal::~QGAppParamInputReal()
{
  // All allocated object are Qt object dependant on this one and will
  // be destroyed when this instance is destroyed
}

// ------------------------------------------------------------------
//
// ------------------------------------------------------------------

void
QGAppParamInputReal::reset()
{
  if (_descr->defaultValue() != "")
    _value->setText(_descr->defaultValue().c_str());  
}


// ------------------------------------------------------------------
// A C C E S S
// ------------------------------------------------------------------

string
QGAppParamInputReal::value() const
{
  return string(_value->text().toLatin1());
}


// ---------------------------------------------------------------------
// T R A N S F O R M A T I O N
// ----------------------------------------------------------------------

void
QGAppParamInputReal::setValue(const string& value)
{
  _value->setText(QString(value.c_str()));
}

// ---------------------------------------------------------------------

void
QGAppParamInputReal::setEnabled(bool enable)
{
  QGAbstractAppParamInput::setEnabled(enable);

  _value->setEnabled(enable);
}

// ---------------------------------------------------------------------
// P R O T E C T E D   S L O T S   M E M B E R
// ----------------------------------------------------------------------

void
QGAppParamInputReal::valueChanged()
{
  _mediator->widgetChanged(this);
}

// ----------------------------------------------------------------------

