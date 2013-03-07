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
 * @file  QGAppParamPanel.cpp
 * @brief Implementation of class QGAppParamPanel
 *
 *        See file QGAppParamPanel.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   June 3, 2003  14:49
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGAppParamPanel.cpp,v 1.3 2005/07/13 16:30:27 masini Exp $ */



// QGUI
#include "QGAppParamPanel.h"
#include "QGAppDialogMediator.h"
#include "QGAppParamInputFile.h"
#include "QGAppParamInputInt.h"
#include "QGAppParamInputReal.h"
#include "QGAppParamInputUnknown.h"
#include "QGAbstractAppParamInput.h"
// QGAR
#include <qgarlib/QgarAppDescr.h>
#include <qgarlib/QgarAppParamDescr.h>
#include <qgarlib/stl.h>
// STL
#include <algorithm>
#include <functional>
#include <vector>
// QT
#include <QLayout>
#include <QGroupBox>


using namespace qgar;



// -------------------------------------------------------------------
// U N N A M E D   N A M E S P A C E
// -------------------------------------------------------------------

namespace
{

/**
 * @brief Checks whether a parameter given its description is an
 * output parameter.
 *
 * @param descr A pointer to the description of the parameter to
 * test.
 */
  bool isOutputParam(QgarAppParamDescr * descr) 
  {
    return (descr->passingMode() == QgarAppParamDescr::QGE_OUT);
  }

} // unnamed namespace


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------

// Default constructor
QGAppParamPanel::QGAppParamPanel(QWidget * parent, 
				 const char * name, 
				 Qt::WindowFlags f)
  : QWidget(parent, f)
{
  setWindowTitle(name);
  init();
}

// -------------------------------------------------------------------
// D E S T R U C T O R
// -------------------------------------------------------------------

QGAppParamPanel::~QGAppParamPanel()
{ /* EMPTY */ }


// -------------------------------------------------------------------
// O T H E R
// -------------------------------------------------------------------

QGAbstractAppParamInput *
QGAppParamPanel::addParameter(QgarAppParamDescr * descr,
			      QGAppDialogMediator * med)
{
  QGAbstractAppParamInput * retval(0);

  // Build subclass instance of QGAbstractAppParamInput according to
  // the parameter type and add it to the correct groupbox according
  // to its passing mode.
  if (descr->passingMode() == QgarAppParamDescr::QGE_OUT) {
    
    retval = buildLine(descr, med, _outputBox, _outputLayout);
  }
  else {
    retval = buildLine(descr, med, _inputBox, _inputLayout);
  }    

  return retval;
}

// -------------------------------------------------------------------

// -------------------------------------------------------------------

void
QGAppParamPanel::init()
{
  _layout = new QVBoxLayout(this);

  //-- Create Input & Output parameter groupBox

  _inputBox  = new QGroupBox(tr("Input Parameters"), this);
  _outputBox = new QGroupBox(tr("Output Parameters"), this);

  _inputLayout = new QGridLayout(_inputBox);
  _outputLayout = new QGridLayout(_outputBox);

  QSpacerItem * sp = new QSpacerItem(10, 10, QSizePolicy::Expanding, 
  				     QSizePolicy::Expanding);
  
  _layout->addWidget(_inputBox);
  _layout->addWidget(_outputBox);
  _layout->addItem(sp);
  //  _inputBox->setLayout(_layout);
}

// -------------------------------------------------------------------

QGAbstractAppParamInput *
QGAppParamPanel::buildLine(QgarAppParamDescr * descr,
			   QGAppDialogMediator * med,
			   QWidget * parent,
			   QGridLayout * layout)
{
  QGAbstractAppParamInput * retval(0);

  switch(descr->format() ) {

  case QgarAppParamDescr::QGE_UNKNOWN_FORMAT:
        retval = new QGAppParamInputUnknown(descr, med, parent, layout);
    break;

  case QgarAppParamDescr::QGE_INT:
        retval = new QGAppParamInputInt(descr, med, parent, layout);
    break;

  case QgarAppParamDescr::QGE_REAL:
        retval = new QGAppParamInputReal(descr, med, parent, layout);
    break;

  default:
        retval = new QGAppParamInputFile(descr, med, parent, layout);

  }

  return retval;
}

// -------------------------------------------------------------------
