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


#ifndef __QGOPENIMAGECOMMAND_H_INCLUDED__
#define __QGOPENIMAGECOMMAND_H_INCLUDED__


/**
 * @file     QGOpenImageCommand.h
 * @brief    Header file of class QGOpenImageCommand.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     September 26, 2002  14:50
 * @since    Qgar 2.1
 */


/* $Id: QGOpenImageCommand.h,v 1.6 2005/07/13 16:30:28 masini Exp $ */



// QGUI
#include "QGAbstractMainWindowCommand.h"
// QT
#include <QFileDialog>



/**
 * @class QGOpenImageCommand QGOpenImageCommand.h "QGOpenImageCommand.h"
 * @brief Command opening a new image file.
 * 
 * This command helps the user to open a new image file. The selection
 * is performed using a filechooser dialog with a set of filters.
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   September 26, 2002  14:50
 * @since  Qgar 2.1
 */
class QGOpenImageCommand

  : public  QGAbstractMainWindowCommand

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name Constructors */
//        ============
//@{


/**
 * @brief Default constructor.
 *
 * @param target A pointer on the main window.
 */
  QGOpenImageCommand(QGMainWindow * target);

//@}



/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGOpenImageCommand();

//@}



/** @name QGCommandIf Impl */
//        ================
//@{

/**
 * @brief Displays a file chooser to select a file and open it.
 */
  virtual void execute();

//@}


// -------------------------------------------------------------------
// P R O T E C T E D   M E M B E R S
// -------------------------------------------------------------------
protected:

  /// The filechooser dialog to open a new file.
  QFileDialog * _qfd;

  /// Storage for the last selected file filter
  QString _lastFilter;


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

/** @name Disabled */
//        ========
//@{

/**
 * @brief Assignment operator
 */
  QGOpenImageCommand& operator=(const QGOpenImageCommand&);

/**
 * @brief Copy-constructor
 */
  QGOpenImageCommand(const QGOpenImageCommand&);
  
//@}


// -------------------------------------------------------------------
}; // class QGOpenImageCommand


#endif /* __QGOPENIMAGECOMMAND_H_INCLUDED__ */
