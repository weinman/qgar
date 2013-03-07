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


#ifndef __QGLAYEROBSERVERIF_H_INCLUDED__
#define __QGLAYEROBSERVERIF_H_INCLUDED__


/**
 * @file   QGLayerObserverIf.h
 * @brief  Header file of class QGLayerObserverIf.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   December 20, 2002  15:17
 * @since  Qgar 2.1
 */


/* $Id: QGLayerObserverIf.h,v 1.5 2005/07/13 16:30:28 masini Exp $ */



/**
 * @class QGLayerObserverIf QGLayerObserverIf.h "QGLayerObserverIf.h"
 * @brief Interface part of an Observer pattern with the
 * QGLayerSubjectIf interface.
 *
 * This interface is to be implemented by all classes wishing to be
 * notified when a layer is modified or updated.
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   December 20, 2002  15:17
 * @since  Qgar 2.1
 */
class QGLayerObserverIf
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
  virtual ~QGLayerObserverIf() {}
//@}


/**
 * @brief Callback method called whenever the layer the implementing
 * class monitors is updated.
 *
 * @param x The x-coordinate of the top left corner of the updated
 * region bounding rectangle
 *
 * @param y The y-coordinate of the top left corner of the updated
 * region bounding rectangle

 * @param width  The width of the updated region.
 * @param height The height of the updated region.
 */
  virtual void layerUpdated(int x, int y, int width, int height) = 0;

// -------------------------------------------------------------------
}; // class QGLayerObserverIf


#endif /* __QGLAYEROBSERVERIF_H_INCLUDED__ */
