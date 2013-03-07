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


#ifndef __QGZOOMCOMMAND_H_INCLUDED__
#define __QGZOOMCOMMAND_H_INCLUDED__


/**
 * @file     QGZoomCommand.h
 * @brief    Header file of class QGZoomCommand.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 2, 2002  17:37
 * @since    Qgar 2.1
 */


/* $Id: QGZoomCommand.h,v 1.4 2005/07/13 16:30:29 masini Exp $ */



// QGUI
#include "QGAbstractMainWindowCommand.h"



/**
 * @class QGZoomCommand QGZoomCommand.h "QGZoomCommand.h"
 * @brief Command incrementing the zoom level of the main window by a
 * given factor.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 2, 2002  17:37
 * @since  Qgar 2.1
 */
class QGZoomCommand

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
 * @brief Creates a command with an increment factor of 1.0.
 *
 * @param target A pointer to the main window.
 */
  QGZoomCommand(QGMainWindow * target);


/**
 * @brief Creates a command with an increment a given factor.
 *
 * @param target  A pointer to the main window
 * @param zoomInc The step used when incrementing the zoom level of
 * the main window.
 */
  QGZoomCommand(QGMainWindow * target, float zoomInc);


/**
 * @brief Copy-constructor
 */
  QGZoomCommand(const QGZoomCommand&);

//@}


/** @name Destructor */
//        ==========
//@{


/**
 * @brief Destructor
 */
  virtual ~QGZoomCommand();

//@}


/** @name Access */
//        ======
//@{

/**
 * @brief Retrieve the zoom increment.
 *
 * @return the zoom level
 */
  float zoomInc() const;

//@}


/** @name Transformation */
//        ==============
//@{

/**
 * @brief Sets the zoom increment for this command
 *
 * @param level the new zoom increment
 */
  void setZoomInc(float level);

//@}


/** @name QGCommandIf Impl */
//        ================
//@{

  virtual void execute();

//@}


/** @name Operators */
//        =========
//@{

/**
 * @brief Assignment operator
 */
  QGZoomCommand& operator=(const QGZoomCommand&);

//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

/** @name Properties */
//        ==========
//@{

  /// The step used to increment the main window current zoom level.
  float _zoomInc;

//@}


// -------------------------------------------------------------------
}; // class QGZoomCommand


#endif /* __QGZOOMCOMMAND_H_INCLUDED__ */
