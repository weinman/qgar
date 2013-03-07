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


#ifndef __QGABSTRACTDOCVIEWERINTERACTOR_H_INCLUDED__
#define __QGABSTRACTDOCVIEWERINTERACTOR_H_INCLUDED__


/**
 * @file     QGAbstractDocViewerInteractor.h
 * @brief    Header file of class QGAbstractDocViewerInteractor
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     December 20, 2002  10:18
 * @since    Qgar 2.1
 */


/* $Id: QGAbstractDocViewerInteractor.h,v 1.6 2005/07/13 16:30:26 masini Exp $ */



// QGUI
#include "QGInteractorIf.h"
class QGDocViewer;

// QT
#include "QPoint"

/**
 * @class QGAbstractDocViewerInteractor QGAbstractDocViewerInteractor.h
 * @brief Base class of interactors acting upon QGDocViewer events.
 * 
 * <p>
 * This abstraction has mainly a structural purpose. It regroups all
 * interactors (ie. classes implementing the QGInteractorIf interface)
 * that react to a QGDocViewer instance events.
 * </p>
 * <p>
 * The only feature offered by this class is the handling of the
 * pointer to the QGDocViewer instance.
 * </p>
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   December 20, 2002  10:18
 *
 * @since Qgar 2.1
 */
class QGAbstractDocViewerInteractor

  : public QGInteractorIf

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
 * @param _view A pointer to the QGDocViewer instance the interactor
 * works with.
 */
  QGAbstractDocViewerInteractor(QGDocViewer * _view);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGAbstractDocViewerInteractor();

//@}



// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /** 
   * @brief Test if a point is within the displayed range
   *
   * @param pt The coordinate of the point
   */
  bool isOnCanvas(const QPoint& pt);


  /// The QGDocViewer instance the interactor interacts with.
  QGDocViewer * _view;


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
  QGAbstractDocViewerInteractor(const QGAbstractDocViewerInteractor&);

/**
 * @brief Assignment operator
 */
  QGAbstractDocViewerInteractor& operator=(const QGAbstractDocViewerInteractor&);

//@}


// -------------------------------------------------------------------

}; // class QGAbstractDocViewerInteractor


#endif /* __QGABSTRACTDOCVIEWERINTERACTOR_H_INCLUDED__ */
