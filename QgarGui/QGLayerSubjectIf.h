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


#ifndef __QGLAYERSUBJECTIF_H_INCLUDED__
#define __QGLAYERSUBJECTIF_H_INCLUDED__


/**
 * @file   QGLayerSubjectIf.h
 * @brief  Header file of class QGLayerSubjectIf.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   December 20, 2002  14:51
 * @since  Qgar 2.1
 */


/* $Id: QGLayerSubjectIf.h,v 1.6 2005/07/13 16:30:28 masini Exp $ */



// QGUI
class QGLayerObserverIf;



/**
 * @class QGLayerSubjectIf QGLayerSubjectIf.h "QGLayerSubjectIf.h"
 * @brief This interface proposes the layer subject to all class
 * wishing to monitor the changes of layer.
 *
 * <p>
 * This interface implements with QGLayerObserver an Observer pattern
 * between a layer (a QGLayerIf subclass) and the classes willing to
 * act upon its updates.
 * </p>
 * <p>
 * This interface declares the methods implementing the registration
 * mechanism along with the notification method.
 * </p>
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   December 20, 2002  14:51
 * @since  Qgar 2.1
 */
class QGLayerSubjectIf
{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGLayerSubjectIf() { }
//@}


/** @name Layer Subject */
//        =============
//@{

/**
 * @brief Attaches a QGLayerObserverIf instance to this subject.
 *
 * The registered instance will then be notified in case of updates.
 *
 * @param obs The observer to attach to this subject.
 */
  virtual void attach(QGLayerObserverIf * obs) = 0;


/**
 * @brief Detaches a QGLayerObserverIf instance from this subject.
 *
 * @param obs The observer to detach
 */
  virtual void detach(QGLayerObserverIf * obs) = 0;


/**
 * @brief Notifies all registered observer that a rectangular region
 * of the layer has been updated.
 *
 * @param x The x-coordinate of the top left corner of updated
 * rectangle.
 *
 * @param y The y-coordinate of the top left corner of the updated
 * rectangle.
 *
 * @param wd The width of the updated rectangle.
 * @param ht The height of the updated rectangle.
 */
  virtual void notifyUpdate(int x, int y, int wd, int ht) = 0;

//@}


// -------------------------------------------------------------------
}; // class QGLayerSubjectIf


#endif /* __QGLAYERSUBJECTIF_H_INCLUDED__ */
