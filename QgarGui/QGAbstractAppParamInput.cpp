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
 * @file  QGAbstractAppParamInput.cpp
 * @brief Implementation of class QGAbstractAppParamInput
 *
 *        See file QGAbstractAppParamInput.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   June 3, 2003  18:07
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGAbstractAppParamInput.cpp,v 1.5 2005/07/13 16:30:26 masini Exp $ */


// QGUI
#include "QGAppDialogMediator.h"
#include "QGAbstractAppParamInput.h"
// QGAR
#include <qgarlib/QgarAppParamDescr.h>
// STL
#include <string>
// XPM
#include <xpm/d_help.xpm>
#include <xpm/help.xpm>
// QT
#include <QCheckBox>
#include <QGroupBox>
#include <QIcon>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QWhatsThis>
#include <QGridLayout>
#include <QWhatsThisClickedEvent>
// QGUI
#include "QGAbstractAppParamInput.moc"



#include <iostream>

using namespace std;
using namespace qgar;



// ------------------------------------------------------------------
// U N N A M E D   N A M E S P A C E
// ------------------------------------------------------------------

namespace {

  /**
   * @brief Returns a string describing a parameter format passed as
   * parameter.
   *
   * Provides a string that is a human readable version of a
   * QGEparamFormat value.
   *
   * @param f the format to be qualified.
   * @return a string describing the given parameter format.
   */
  QString toString(QgarAppParamDescr::ParamFormat f) {
    
    QString retval;
    
    switch (f) {

    case QgarAppParamDescr::QGE_PBM:
      retval = "PBM";
      break;
      
    case QgarAppParamDescr::QGE_PPM:
      retval = "PPM";
      break;
      
    case QgarAppParamDescr::QGE_PGM:
      retval = "PGM";
      break;

    case QgarAppParamDescr::QGE_DXF:
      retval = "DXF";
      break;
     
    case QgarAppParamDescr::QGE_SVG:
      retval = "SVG";
      break;
      
    case QgarAppParamDescr::QGE_INT:
      retval = "int";
      break;

    case QgarAppParamDescr::QGE_REAL:
      retval = "real";
      break;

    default:
      retval = "unknown";
    
    }

    return retval;
  }
}



// ------------------------------------------------------------------
// C O N S T R U C T O R S
// ------------------------------------------------------------------

// Default constructor
QGAbstractAppParamInput::QGAbstractAppParamInput(QgarAppParamDescr * descr, 
						 QGAppDialogMediator * med,
						 QWidget * parent,
						 QGridLayout * layout)
  : QWidget(parent), _layout(layout), _descr(descr), _mediator(med), _enabled(true)
{
  init();
}

  

// ------------------------------------------------------------------
// D E S T R U C T O R
// ------------------------------------------------------------------

QGAbstractAppParamInput::~QGAbstractAppParamInput()
{ 
  // All allocated objects are QObjects with this instance as
  // ancestor. Qt will delete them for us.
}



// ---------------------------------------------------------------------
// A C C E S S
// ----------------------------------------------------------------------

QgarAppParamDescr *
QGAbstractAppParamInput::descr()
{
  return _descr;
}

// ---------------------------------------------------------------------

bool
QGAbstractAppParamInput::enabled() const
{
  return _enabled;
}

// ---------------------------------------------------------------------
// T R A N S F O R M A T I O N
// ----------------------------------------------------------------------

void
QGAbstractAppParamInput::setEnabled(bool enable)
{
  _enabled = enable;

  _nameLabel->setEnabled(enable);
}


// ---------------------------------------------------------------------
// P R O T E C T E D   S L O T S
// ----------------------------------------------------------------------

void
QGAbstractAppParamInput::enableClicked() {
  setEnabled(_optionBox->isChecked());
  _mediator->widgetChanged(this);
}

// ---------------------------------------------------------------------

void
QGAbstractAppParamInput::helpClicked() {
  string helpText ="<qt>";
  helpText += _descr->briefDoc();
  helpText += "<p align=\"right\"><a href=\"" 
              + _descr->flag() 
              + "\">more</a></p>";
  helpText += "</qt>";

  QWhatsThis::showText(QCursor::pos(), QString(helpText.c_str()),
		       this);
}



// ---------------------------------------------------------------------
// O T H E R 
// ----------------------------------------------------------------------

void
QGAbstractAppParamInput::init()
{
  // ---------------
  // Widget Creation
  // ---------------

  //-- Help Button

  // Build icon set
  QIcon icon;
  icon.addPixmap(QPixmap(help_xpm), QIcon::Normal, QIcon::On);
  icon.addPixmap(QPixmap(d_help), QIcon::Disabled, QIcon::On);

  // Create button & set options
  _helpButton = new QPushButton(icon,"", this);
  _helpButton->setFocusPolicy(Qt::NoFocus);
  _helpButton->setFlat(true);
  // Attention: the size argument is randon. actualSize() method
  // will return a smaller value, never bigger.
  _helpButton->setMaximumSize(icon.actualSize(QSize(50, 50),
					      QIcon::Normal,
					      QIcon::On));


  QSpacerItem * spacer1 = new QSpacerItem(10, 10, QSizePolicy::Fixed,
					  QSizePolicy::Maximum);


  //-- Create parameter name Label

  string label = _descr->name() + "(" + (toString(_descr->format())).toStdString() + ")";
  _nameLabel = new QLabel( label.c_str(), this);


  //-- Create checkbox if parameter is optional// QGUI


  // If parameter is required, check checkbox and disabled it (line
  // can never be disabled since the checkbox can no longer be activated).
  QSpacerItem * spacer2 = 0;
  if ( _descr->required() ) {
    _optionBox = 0;
  }
  else {
    _optionBox = new QCheckBox(this);
    _optionBox->setChecked(false);
    this->setEnabled(false);
    
    spacer2 = new QSpacerItem(10, 10, 
			      QSizePolicy::Fixed, QSizePolicy::Maximum);
    
    connect(_optionBox,  SIGNAL(clicked()), SLOT(enableClicked()));
  }

// QGUI

  //-- Create spacer in order to align all _value fields
  
  QSpacerItem * spacer3 = new QSpacerItem(10, 10, QSizePolicy::Expanding, 
					  QSizePolicy::Expanding);


  //-- Add Widgets 
  _colCounter = 0;
  _rowCounter = _layout->rowCount();

  _layout->addWidget(_helpButton, _rowCounter, _colCounter);
  _colCounter++;
  if (_optionBox) {
    _layout->addWidget(_optionBox, _rowCounter, _colCounter);
    _colCounter++;
  }

  _layout->addWidget(_nameLabel, _rowCounter, _colCounter);
  _colCounter++;

  // -------------------------------
  // Widget Signals/Slots Connection
  // -------------------------------

  connect(_helpButton, SIGNAL(clicked()), SLOT(helpClicked()));
}


bool QGAbstractAppParamInput::event(QEvent* event)
{
  if(event->type() == QEvent::WhatsThisClicked)
  {
    QWhatsThisClickedEvent* clicked = static_cast<QWhatsThisClickedEvent*>(event);

    // Verify the reference string and pass it to the mediator
    if(!(clicked->href().isEmpty()))
    {
      _mediator->jumpToAnchor(clicked->href());
    }
    // Return false to close the QWhatsThis window
    return false;
  }
  return QWidget::event(event);
}

// ----------------------------------------------------------------------
