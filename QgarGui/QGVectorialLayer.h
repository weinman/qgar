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


#ifndef __QGVECTORIALLAYER_H_INCLUDED__
#define __QGVECTORIALLAYER_H_INCLUDED__


/**
 * @file     QGVectorialLayer.h
 * @brief    Header file of class QGVectorialLayer.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 18, 2002  17:48
 * @since    Qgar 2.1
 */


/* $Id: QGVectorialLayer.h,v 1.12 2005/07/13 16:30:29 masini Exp $ */



// QGUI
#include "QGAbstractLayer.h"
// STD
#include <map>
#include <stdexcept>
// QT
#include <QVector>
class QGraphicsItem;
class QGraphicsScene;
class QColor;
class QPoint;
class QString;



/**
 * @class QGVectorialLayer QGVectorialLayer.h "QGVectorialLayer.h"
 * @brief Base class of all vectorial layers.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 18, 2002  17:48
 * @since  Qgar 2.1
 */
class QGVectorialLayer

  : public QGAbstractLayer

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
  virtual ~QGVectorialLayer();

//@}



/** @name Item Management */
//        ===============
//@{

/**
 * @brief Inserts a vectorial item in the layer.
 *
 * @warning The layer takes ownership of the item and will be
 * responsible of deleting it.
 *
 * @param item the item to insert.
 */
  void insertVectItem(QGraphicsItem * item);


/**
 * @brief Removes a vectorial item from the layer.
 *
 * If no client holds a reference on the item, it is destroyed.
 */
  void removeVectItem(QGraphicsItem * item);
  

/**
 * @brief Checks if an item is present in the layer.
 *
 * param item The item whose presence is to be tested.
 */
  bool hasItem(QGraphicsItem * item);


/**
 * @brief Informs the layer that an item must not be destroyed until
 * the client releases the reference.
 *
 * @param item a pointer on the item of interest.
 */
  void lock(QGraphicsItem * item);
  

/**
 * @brief Notifies the layer that the calling client no longer needs
 * the vectorial item.
 *
 * @param item a pointer on the item of interest.
 */
  void unlock(QGraphicsItem * item);

//@}



/** @name Access */
//        ======
//@{

/**
 * @brief Checks if the skeleton mode is turn on
 *
 * @return true if the a skeletal view of the layer is displayed.
 */
  bool skelModeOn() const;


/**
 * @brief Retrieves a pointer on the canvas holding all vectorial
 * items composing the layer.
 *
 * @return A pointer to the canvas.
 */
  QGraphicsScene * canvas() const;

//@}

/** @name Transformation */
//        ==============
//@{

/**
 * @brief Turn on/off the skeleton mode.
 *
 * @param on true if the skeleton mode is to be set, false otherwise.
 */
  virtual void setSkelModeOn(bool on);

/**
 * @brief Change the color of all vectorial item to the given color.
 *
 * @param color The new color of the layer's items.
 */
  void setColor(const QColor& color);

//@}



/** @name QGLayerIf Impl */
//        ==============
//@{

  virtual void setWidth(int width);
  
  virtual void setHeight(int height);

  virtual void save() {/* EMPTY */}

  virtual void draw(QPainter * p,int x, int y,  int wd, int ht);

  virtual void draw(QPixmap& dst, int x, int y, int wd, int ht,
		    QPainter::CompositionMode op = QPainter::CompositionMode_SourceOver);

  virtual void draw(int x, int y, int wd, int ht, QGraphicsScene& sc);

  virtual int items() const;
//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:
  
/**
 * @brief A flag indicating if this layer displays a skeleton view of
 * itself
 */
  bool _skelModeOn;

  /// The vectorial item composing this layer.
  QVector<QGraphicsItem *> _itemVect;

  /// A pointer to the canvas the layer is currently attached to.
  QGraphicsScene * _graphicsScene;

  typedef std::map< QGraphicsItem *, unsigned int > RefCountMap;

/**
 * @brief A map counting the number of client holding a reference on a
 * layer item.
 */
  RefCountMap _lockedItemMap;



/** @name Constructors */
//        ============
//@{

/**
 * @brief Default constructor
 */
  QGVectorialLayer();

/**
 * @brief Constructor
 */
  QGVectorialLayer(const QString& filename) throw(std::runtime_error);

//@}


/**
 * @brief Loads the vectorial items from an image file.
 *
 * Retrieve all vector items from the file matching the filename
 * in the returning vector.
 * Subclasses must provide this method.
 *
 * @param filename  The name of the image file to load.
 * @param vect      [out]A vector that will be filled with all vectorial
 * items composing the opened image file.
 *
 * @return the image width & height as a point.
 */
  virtual QPoint loadItems(const QString& filename, 
			   QVector<QGraphicsItem *>& vect) 
    throw(std::runtime_error) = 0;


/**
 * @brief Function member called by subclasses constructor.
 */
  void init(const QString& filename) throw(std::runtime_error);



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
  QGVectorialLayer(const QGVectorialLayer&);

/**
 * @brief Disabled assignment operator
 */
  QGVectorialLayer& operator=(const QGVectorialLayer&);

//@}

// -------------------------------------------------------------------
}; // class QGVectorialLayer


#endif /* __QGVECTORIALLAYER_H_INCLUDED__ */
