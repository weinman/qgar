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


#ifndef __QGSIMODECOMMAND_H_INCLUDED__
#define __QGSIMODECOMMAND_H_INCLUDED__


/**
 * @file     QGSIModeCommand.h
 * @brief    Header file of class QGSIModeCommand
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 11, 2002  14:45
 * @since    Qgar 2.1
 */


/* $Id: QGSIModeCommand.h,v 1.5 2005/07/13 16:30:29 masini Exp $ */



// QGUI
#include "QGAbstractMainWindowCommand.h"
class QFileDialog;



/**
 * @class QGSIModeCommand QGSIModeCommand.h "QGSIModeCommand.h"
 * @brief Opens a new image to display on top of the document or
 * discards a layer already on top.
 * 
 * <p>
 * This command deals with the 'superimpose' mode. When this mode is
 * on, another image is opened and drawn on top of the current
 * document.
 * </p>
 * <p>
 * This command will toggle this mode on or off. If the mode is off,
 * executing the command will open a file chooser dialog to select an
 * image to place on top of the document. If the mode is on, the image
 * on top will be removed.
 * </p>
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 11, 2002  14:45
 * @since  Qgar 2.1
 */
class QGSIModeCommand

  : public QGAbstractMainWindowCommand

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name Constructors */
//        ============
//@{

/**
 * @brief Constructor
 *
 * @param main A pointer to the main window.
 */
  QGSIModeCommand(QGMainWindow * main);


/**
 * @brief Copy-constructor
 * 
 * @param other Another instance to create a this command from.
 */
  QGSIModeCommand(const QGSIModeCommand& other);

//@}



/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGSIModeCommand();

//@}


/** @name Operators */
//        =========
//@{

/**
 * @brief Assignment operator
 */
  QGSIModeCommand& operator=(const QGSIModeCommand&);

//@}


/** @name QGCommandIf Impl */
//        ================
//@{

/**
 * @brief Opens a new layer or removes the top layer if it already
 * exists.
 */
  virtual void execute();

//@}

protected:

  /// File dialog to open superimpose layer
  QFileDialog * _qfd;

// -------------------------------------------------------------------
}; // class QGSIModeCommand


#endif /* __QGSIMODECOMMAND_H_INCLUDED__ */
