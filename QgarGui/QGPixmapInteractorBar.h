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


#ifndef __QGPIXMAPINTERACTORBAR_H_INCLUDED__
#define __QGPIXMAPINTERACTORBAR_H_INCLUDED__


/**
 * @file     QGPixmapInteractorBar.h
 * @brief    Header file of class QGPixmapInteractorBar
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 28, 2002  09:18
 * @since    Qgar 2.1
 */


/* $Id: QGPixmapInteractorBar.h,v 1.4 2005/07/13 16:30:28 masini Exp $ */



// QGUI
#include "QGCommandToolBar.h"
class QGMainWindow;



/**
 * @class QGPixmapInteractorBar QGPixmapInteractorBar.h "QGPixmapInteractorBar.h"
 * @brief A toolbar embedding a set of interactors appliable on a
 * pixmap layer.
 *
 * <p> 
 * This toolbar regroups a set of toolbutton, each activating a
 * specific interactor using the a QGSetInteractorCommand instance.
 * </p>
 * <p>
 * The possible interactors features are:
 * - Move a part of the layer to another (QGMoveToInteractor).
 * - Draw on the layer (QGScribbleInteractor).
 * - Erase a part of the layer (QGScribbleInteractor).
 * .
 * </p>
 * <p>
 * This toolbar is normally not instanciated directly but via the
 * factory QGInteractorBarFactory.
 *
 * @see QGMoveToInteractor
 * @see QGScribbleInteractor
 * @see QGInteractorBarFactory
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 28, 2002  09:18
 * @since  Qgar 2.1
 */
class QGPixmapInteractorBar

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
 * @brief Default constructor
 *
 * @param parent An optional parent for this widget.
 * @param name   An optional name for this widget.
 */
  QGPixmapInteractorBar(QGMainWindow * parent, const char * name = 0);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGPixmapInteractorBar();
//@}



// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// A pointer on the main window used to set the chosen interactor.
  QGMainWindow * _main;



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
  QGPixmapInteractorBar(const QGPixmapInteractorBar&);

/**
 * @brief Assignment operator
 */
  QGPixmapInteractorBar& operator=(const QGPixmapInteractorBar&);

//@}

// -------------------------------------------------------------------
}; // class QGPixmapInteractorBar


#endif /* __QGPIXMAPINTERACTORBAR_H_INCLUDED__ */
