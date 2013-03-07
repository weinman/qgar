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
 * @file  QGUtilityBarFactory.cpp
 * @brief Implementation of class QGUtilityBarFactory.
 *
 * See file QGUtilityBarFactory.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 28, 2002  16:51
 * @since  Qgar 2.1
 */



// QGUI
#include "QGUtilityBarFactory.h"
#include "QGDxfLayer.h"
#include "QGVectUtilityBar.h"
// STD
//#include <cstring>
// QT
#include <QToolBar>



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGUtilityBarFactory::QGUtilityBarFactory()
{ /* EMPTY */ }


// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

// Default constructor
QGUtilityBarFactory::~QGUtilityBarFactory() 
{ /* EMPTY */ }


// -------------------------------------------------------------------
// A C C E S S 
// -------------------------------------------------------------------

QGUtilityBarFactory *
QGUtilityBarFactory::instance()
{
  static QGUtilityBarFactory instance;

  return &instance;
}


// -------------------------------------------------------------------
// F A C T O R Y     M E T H O D S 
// -------------------------------------------------------------------

QToolBar *
QGUtilityBarFactory::createUtilityBar(QGMainWindow * main, 
				      const char * imageType)
{
  // Initialize return value to null. If no utility bar matching the image type
  // can be constructed, the null pointer will be returned
  QToolBar * retval = 0;
  
  if (! strcmp(imageType, QGDxfLayer::DXF_TYPE) ) // image type is DXF
    retval = new QGVectUtilityBar(main);


  if (retval)
    setToolBarProperties(retval);

  return retval;
}

// ----------------------------------------------------------------------

void
QGUtilityBarFactory::setToolBarProperties(QToolBar * toolbar) const
{
  toolbar->setMovable(false);
  
  // Qt4 QToolBar doesn't inherits from QFrame anymore
  // no frames allowed
  //toolbar->setFrameShadow(QFrame::Raised);
}

// ----------------------------------------------------------------------

