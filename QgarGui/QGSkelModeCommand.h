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


#ifndef __QGSKELMODECOMMAND_H_INCLUDED__
#define __QGSKELMODECOMMAND_H_INCLUDED__


/**
 * @file   QGSkelModeCommand.h
 * @brief  Header file of class QGSkelModeCommand
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   December 1, 2002  16:09
 * @since  Qgar 2.1
 */


/* $Id: QGSkelModeCommand.h,v 1.4 2005/07/13 16:30:29 masini Exp $ */



// QGUI
#include "QGCommandIf.h"
class QGVectorialLayer;



/**
 * @class QGSkelModeCommand QGSkelModeCommand.h "QGSkelModeCommand.h"
 * @brief Command toggling on or off the skeleton view of a vectorial
 * layer.
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   December 1, 2002  16:09
 * @since  Qgar 2.1
 */
class QGSkelModeCommand

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
 * @param layer The layer to pilot the skeleton mode.
 */
  QGSkelModeCommand(QGVectorialLayer * layer);

//@}

  // ------------------------------------------------------
  // USING DEFAULT COPY-CONSTRUCTOR AND ASSIGNMENT OPERATOR
  // ------------------------------------------------------

/** @name QGCommandIf Impl */
//        ================
//@{

/**
 * @brief Toggles on or off the skeleton mode of the layer.
 */
  virtual void execute();

//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// A pointer to the vectorial layer to work with.  
  QGVectorialLayer * _layer;

// -------------------------------------------------------------------
}; // class QGSkelModeCommand


#endif /* __QGSKELMODECOMMAND_H_INCLUDED__ */
