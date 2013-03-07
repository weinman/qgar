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
 * @file  QGInteractorBarFactory.cpp
 * @brief Implementation of class QGInteractorBarFactory.
 *
 * See file QGInteractorBarFactory.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 28, 2002  09:46
 * @since  Qgar 2.1
 */



// QGUI
#include "QGInteractorBarFactory.h"
#include "QGDxfLayer.h"
#include "QGPixmapInteractorBar.h"
#include "QGPixmapLayer.h"
#include "QGMainWindow.h"
#include "QGVectInteractorBar.h"
// STD
#include <cstring>
// QT
#include <QString>
#include <QToolBar>



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGInteractorBarFactory::QGInteractorBarFactory() 
{ /* EMPTY */ }


// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

// Default constructor
QGInteractorBarFactory::~QGInteractorBarFactory() 
{ /* EMPTY */ }



// ---------------------------------------------------------------------
// A C C E S S
// ---------------------------------------------------------------------

QGInteractorBarFactory * 
QGInteractorBarFactory::instance() 
{
  static QGInteractorBarFactory instance;

  return &instance;
}



// -------------------------------------------------------------------
// F A C T O R Y     M E T H O D S 
// -------------------------------------------------------------------

QToolBar *
QGInteractorBarFactory::createInteractorBar(QGMainWindow * main, 
					    const char * imageType)
{
  // Initialize return value to null. If no utility bar matching the
  // image type can be constructed, the null pointer will be returned
  QToolBar * retval = 0;

  if (! strcmp(imageType,QGDxfLayer::DXF_TYPE) )
    retval = new QGVectInteractorBar(main);

  // If image type matches one among the QGPixmapLayer types..?
  else if (! ( strcmp(imageType, QGPixmapLayer::PGM_TYPE)
	       && strcmp(imageType, QGPixmapLayer::PPM_TYPE)
	       && strcmp(imageType, QGPixmapLayer::PBM_TYPE)))

    retval = new QGPixmapInteractorBar(main);


  if(retval)
    setToolBarProperties(retval);

  return retval;
}

// ----------------------------------------------------------------------

void
QGInteractorBarFactory::setToolBarProperties(QToolBar * toolbar) const
{
  toolbar->setMovable(false);
}

// ----------------------------------------------------------------------

