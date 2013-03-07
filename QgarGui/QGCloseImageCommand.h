/*---------------------------------------------------------------------*
 | Graphical user interface QgarGui                                    |
 | Copyright (C) 2004  Qgar Project, LORIA                             |
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


#ifndef __QGCLOSEIMAGECOMMAND_H_INCLUDED__
#define __QGCLOSEIMAGECOMMAND_H_INCLUDED__


/**
 * @file   QGCloseImageCommand.h
 * @brief  Header file of class qgar::QGCloseImageCommand.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   August 31, 2004  15:09
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGCloseImageCommand.h,v 1.2 2005/07/13 16:30:27 masini Exp $ */



// QGUI
#include "QGAbstractMainWindowCommand.h"



/**
 * @class QGCloseImageCommand QGCloseImageCommand.h "QGCloseImageCommand.h"
 * @brief Command handling the user interaction when a document is
 * closed in the main window.
 * 
 * When a modified document is closed, the user must be prompted
 * whether it wishes to save the document before closing it. This
 * class builds the required dialogs and handles the interaction.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   August 31, 2004  15:09
 * @since  Qgar 2.1.1
 */
class QGCloseImageCommand

  : public QGAbstractMainWindowCommand

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:


/**
 * @brief Builds a command linked with the given main window
 * @param target A pointer to the main window this command is linked
 *               to.
 */
  QGCloseImageCommand(QGMainWindow * target);
//@}


  // USING DEFAULT DESTRUCTOR


/** @name QGCommandIf implementation */
//        ==========================
//@{
  
  virtual void execute();

//@}


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

//
/** @name Disabled */
//        ========
//@{
  /// Disabled copy constructor
  QGCloseImageCommand(const QGCloseImageCommand&);

  /// Disabled assignment operator
  QGCloseImageCommand& operator=(const QGCloseImageCommand& rhs);
//@}

// -------------------------------------------------------------------
}; // class QGCloseImageCommand


#endif /* __QGCLOSEIMAGECOMMAND_H_INCLUDED__ */
