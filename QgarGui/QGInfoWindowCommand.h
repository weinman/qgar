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


#ifndef __QGINFOWINDOWCOMMAND_H_INCLUDED__
#define __QGINFOWINDOWCOMMAND_H_INCLUDED__


/**
 * @file     QGInfoWindowCommand.h
 * @brief    Header file of class QGInfoWindowCommand
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     December 1, 2002  20:36
 * @since Qgar 2.1
 */


/* $Id: QGInfoWindowCommand.h,v 1.6 2005/07/13 16:30:28 masini Exp $ */



// QGUI
#include "QGCommandIf.h"
class QGInfoWindow;
class QGMainWindow;



/**
 * @class QGInfoWindowCommand QGInfoWindowCommand.h "QGInfoWindowCommand.h"
 * @brief A Command invoking a QGInfoWindow instance on a vectorial view.
 * 
 * The first execution this command provokes the display of a QGInfoWindow
 * instance. Further executions will toggle this QGInfoWindow object
 * visibility status.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   December 1, 2002  20:36
 * @since  Qgar 2.1
 */
class QGInfoWindowCommand

  : public QGCommandIf

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name Constructors */
//        ============
//@{

/**
 * @brief Default constructor
 *
 * @param main A pointer to the main window this command is attached to.
 */
  QGInfoWindowCommand(QGMainWindow * main);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGInfoWindowCommand();
//@}


/** @name QGCommandIf Impl */
//        ================
//@{

/**
 * @brief Shows the info window if it is hidden, hide it otherwise.
 */
  virtual void execute();

//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// Flag storing the display status of the info window.
  bool _isOn;

/**
 * @brief The QGInfoWindow instance to be shown or hidden on the
 * execution of this command.
 */
  QGInfoWindow * _infoWnd;


/** @name Access */
//        ======
//@{

  /// Queries the display status of the info window.
  bool on() const;

//@}


/** @name Transformation */
//        ==============
//@{

/**
 * @brief Sets the display status of the info window.
 *
 * @param on The new display status to be set.
 */
  void setOn(bool on);

//@}


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

/** @name Disabled */
//        ========
//@{

/**
 * @brief Copy-constructor
 */
  QGInfoWindowCommand(const QGInfoWindowCommand&);

/**
 * @brief Assignment operator
 */
  QGInfoWindowCommand& operator=(const QGInfoWindowCommand&);

//@}

// -------------------------------------------------------------------
}; // class QGInfoWindowCommand


#endif /* __QGINFOWINDOWCOMMAND_H_INCLUDED__ */
