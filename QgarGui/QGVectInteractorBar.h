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


#ifndef __QGVECTINTERACTORBAR_H_INCLUDED__
#define __QGVECTINTERACTORBAR_H_INCLUDED__


/**
 * @file     QGVectInteractorBar.h
 * @brief    Header file of class QGVectInteractorBar
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 24, 2002  15:15
 * @since    Qgar 2.1
 */


/* $Id: QGVectInteractorBar.h,v 1.4 2005/07/13 16:30:29 masini Exp $ */



// QGUI
#include "QGCommandToolBar.h"
class QGMainWindow;



/**
 * @class QGVectInteractorBar QGVectInteractorBar.h "QGVectInteractorBar.h"
 * @brief A command toolbar regrouping all interactors appliable to a
 * vectorial layer.
 *
 * <p> 
 * This toolbar regroups all interactor working on a vectorial
 * layer. Currently 5 interactors are registered:  QGModifyInteractor,
 * QGLineDrawerInteractor, QGEllipseDrawerInteractor,
 * QGPolylineInteractor
 * </p>
 * <p>
 * For each of these interactor a button is created. Clicking this
 * button will trigger the interactor via a QGSetInteractorCommand
 * instance.
 * </p>
 *
 * @see QGModifyInteractor
 * @see QGLineDrawerInteractor
 * @see QGEllipseDrawerInteractor
 * @see QGPolylineInteractor
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 24, 2002  15:15
 * @since  Qgar 2.1
 */
class QGVectInteractorBar

  : public QGCommandToolBar

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name Constructor */
//        ===========
//@{

/**
 * @brief Constructor
 *
 * @param parent A pointer to the main window on which the interactor
 * will be set/unset.
 * @param name   An optional name for this widget.
 */
  QGVectInteractorBar(QGMainWindow * parent, 
		      const char * name = 0);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGVectInteractorBar();

//@}



// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// A pointer to the main window.
  QGMainWindow * _main;
  


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

/** @name Disabled */
//        ========
//@{

/**
 * @brief Disabled copy-constructor
 */
  QGVectInteractorBar(const QGVectInteractorBar&);

/**
 * @brief Disabled assignment operator
 */
  QGVectInteractorBar& operator=(const QGVectInteractorBar&);

//@}


// -------------------------------------------------------------------
}; // class QGVectInteractorBar


#endif /* __QGVECTINTERACTORBAR_H_INCLUDED__ */
