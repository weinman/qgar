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
 * @file  QGAppParamInputUnknown.cpp
 * @brief Implementation of class QGAppParamInputUnknown
 *
 *        See file QGAppParamInputUnknown.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   July 10, 2003  10:43
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGAppParamInputUnknown.cpp,v 1.4 2005/07/13 16:30:27 masini Exp $ */



// QGUI
#include "QGAppParamInputUnknown.h"
#include "QGAppDialogMediator.h"
// QGAR
#include <qgarlib/QgarAppParamDescr.h>
// QT
#include <QLayout>
#include <QLineEdit>
// QGUI
#include "QGAppParamInputUnknown.moc"



using namespace qgar;
using namespace std;



// ------------------------------------------------------------------
// C O N S T R U C T O R S
// ------------------------------------------------------------------

// Default constructor
QGAppParamInputUnknown::QGAppParamInputUnknown(QgarAppParamDescr * descr,
					       QGAppDialogMediator * med,
					       QWidget * parent,
					       QGridLayout * layout)

  : QGAbstractAppParamInput(descr, med, parent, layout)

{
  //-- Create value field

  _value = new QLineEdit(this);
  _value->setMinimumSize(QSize(300, 20));
  _value->setSizePolicy(QSizePolicy(QSizePolicy::Maximum,
				    QSizePolicy::Maximum));
  _layout->addWidget(_value, _rowCounter, _colCounter);


  //-- If base class widgets are disabled set widgets accordingly.

  this->setEnabled(enabled());

  // Connect line edit to the slot that fwds notification to the
  // mediator
  connect(_value, 
	  SIGNAL(textChanged(const QString&)),
	  SLOT(valueChanged()));

  //-- Set default value.
  
  reset();
}

// ------------------------------------------------------------------
// D E S T R U C T O R
// ------------------------------------------------------------------

QGAppParamInputUnknown::~QGAppParamInputUnknown()
{ 
  // Qt deletes all QObject depending on this one for us.
}


// ------------------------------------------------------------------
// 
// ------------------------------------------------------------------

void
QGAppParamInputUnknown::reset()
{
  if (_descr->defaultValue() != "") {
    if (_descr->defaultValue()[0] == '_') {
    
      // Default value depends on main image filename stem
      
      if ( (_mediator->defaultFileStem() != "") 
	 && (_descr->passingMode() == QgarAppParamDescr::QGE_OUT)
	 && (_descr->defaultValue() != "") ) {
      
	QString filename(_descr->defaultValue().c_str());
	filename = filename.remove("_");
	filename = _mediator->defaultFileStem() + filename;
	_value->setText(filename);
      }
      
    }
    
    else {
      _value->setText(_descr->defaultValue().c_str());
    }  
  }
}


// ------------------------------------------------------------------
// A C C E S S
// ------------------------------------------------------------------

string
QGAppParamInputUnknown::value() const
{
  return _value->text().toStdString();
}

// ---------------------------------------------------------------------
// T R A N S F O R M A T I O N
// ----------------------------------------------------------------------

void
QGAppParamInputUnknown::setValue(const std::string& value)
{
  _value->setText(QString(value.c_str()));
}

// ---------------------------------------------------------------------

void
QGAppParamInputUnknown::setEnabled(bool enable)
{
  QGAbstractAppParamInput::setEnabled(enable);

  _value->setEnabled(enable);
}

// ---------------------------------------------------------------------
// P R O T E C T E D   S L O T S
// ----------------------------------------------------------------------

void
QGAppParamInputUnknown::valueChanged()
{
  _mediator->widgetChanged(this);
}

// ----------------------------------------------------------------------

