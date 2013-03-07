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


#ifndef __QGABSTRACTLAYER_H_INCLUDED__
#define __QGABSTRACTLAYER_H_INCLUDED__


/**
 * @file     QGAbstractLayer.h
 * @brief    Header file of class QGAbstractLayer
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     December 20, 2002  14:57
 * @since    Qgar 2.1
 */


/* $Id: QGAbstractLayer.h,v 1.8 2005/07/13 16:30:26 masini Exp $ */



// QGUI
#include "QGLayerIf.h"
// QGAR
class QGLayerObserverIf;
// STL
#include <vector>



/**
 * @class QGAbstractLayer QGAbstractLayer.h
 * @brief Provides a default implementation of the QGLayerSubjectIf interface.
 * 
 * <p>
 * The purpose of this abstract class is to factorize the
 * implementation of the QGLayerSubjectIf for all derived 'real'
 * layers. It provides storage and handling for the observers
 * (ie. classes implementing QGLayerObserverIf).
 * </p>
 * <p>
 * The instance maintains a list of all its observers. An observer may
 * only be attached once to this subject. Further calls to attach()
 * will have no effects. Each call to the update() method will trigger
 * a notification sending to all attached observers.
 * </p>
 *
 * @see QGLayerObserverIf
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   December 20, 2002  14:57
 * 
 * @since Qgar 2.1
 */
class QGAbstractLayer

  : public QGLayerIf

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
 */
  QGAbstractLayer();

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGAbstractLayer();

//@}



/**
 * @brief Hints the layer that it has been partially modified.
 *
 * This member is called by clients that directly modify the layer
 * data. The call will notify all attached observers that a part of the
 * layer as been modified, allowing them to refresh themselves.
 *
 * @param x  The x coordinate of the top left corner of the modified
 * area.
 * @param y  The x coordinate of the top left corner of the modified
 * area.
 * @param width  The width of the modified area.
 * @param height The height of the modified area.
 */
  virtual void update(int x, int y, int width, int height);


/**
 * @brief Hints the layer that it has been partially modified.
 *
 * @param rect The rectangular aera that has been modified.
 *
 * @overload
 */
  virtual void update(const QRect& rect);


/**
 * @brief Hints the layer that it has been fully modified.
 *
 * This call is equivalent to update(0, 0, width(), height())
 *
 * @overload
 */
  virtual void update();


/** @name QGLayerSubjectIf impl */
//        =====================
//@{

/**
 * @brief Adds an Observer to the observer list.
 *
 * With the current implementation, an observer may only appear once
 * in the observer list. Adding it more than once will have no effect.
 *
 * @param obs A pointer to the observer to add.
 */
  virtual void attach(QGLayerObserverIf * obs);


/**
 * @brief Removes an Observer to the observer list.
 *
 * @param obs A pointer to the observer to add.
 */
  virtual void detach(QGLayerObserverIf * obs);

//@}


/** @name QGLayerIf impl */
//        ==============
//@{

  virtual int width() const;
  virtual int height() const;
  virtual const char * type() const;
  virtual qgar::QgarAppParamDescr::ParamFormat format() const;

  virtual void setWidth(int);
  virtual void setHeight(int);

//@}



// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// The vector storing the attached observers.
  std::vector<QGLayerObserverIf *> _obsVect;


/**
 * @brief Notifies all the attached observer that the layer as been
 * modified.
 *
 * This methods sends a message to all observers attached to the
 * instance. The message is send using the observers layerUpdated()
 * function member, precising which part of the layer as been
 * modified..
 *
 * @param x  The x coordinate of the top left corner of the modified
 * area.
 * @param y  The x coordinate of the top left corner of the modified
 * area.
 * @param width  The width of the modified area.
 * @param height The height of the modified area.
 */
  virtual void notifyUpdate(int x, int y, int width, int height);



// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// The type of image this layer embeds
  const char * _type;
  
  /// The format of the image this layer embeds.
  qgar::QgarAppParamDescr::ParamFormat _format;

  /// The width of the layer.
  int _width;

  /// The height of the layer.
  int _height;

  /// Number of elements of the layer.
  int _items;


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
  QGAbstractLayer(const QGAbstractLayer&);

/**
 * @brief Assignment operator
 */
  QGAbstractLayer& operator=(const QGAbstractLayer&);

//@}

// -------------------------------------------------------------------

}; // class QGAbstractLayer


#endif /* __QGABSTRACTLAYER_H_INCLUDED__ */
