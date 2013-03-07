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


#ifndef __QGDXFLAYER_H_INCLUDED__
#define __QGDXFLAYER_H_INCLUDED__


/**
 * @file     QGDxfLayer.h
 * @brief    Header file of class QGDxfLayer
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 21, 2002  09:42
 * @since    Qgar 2.1
 */


/* $Id: QGDxfLayer.h,v 1.7 2005/07/13 16:30:27 masini Exp $ */



// QGUI
#include "QGVectorialLayer.h"



/**
 * @class QGDxfLayer QGDxfLayer.h "QGDxfLayer.h"
 * @brief A vectorial layer whose source base image is in DXF format.
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 21, 2002  09:42
 * @since Qgar 2.1
 */
class QGDxfLayer

  : public QGVectorialLayer

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:


/** @name Consts */
//        ======
//@{

/**
 * @brief The id of this image format type.
 */
  static const char * DXF_TYPE;

//@}



/** @name Constructors */
//        ============
//@{

/**
 * @brief Default constructor
 *
 * Creates an empty layer.
 */
  QGDxfLayer();


/**
 * @brief Creates a layer from the given file.
 *
 * @param filename The name of the DXF file to create the layer from.
 *
 * @throws std::runtime_error if an error while reading the file
 * occurs.
 */
  QGDxfLayer(const QString& filename) throw(std::runtime_error);


//@}

/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGDxfLayer();
//@}


/**
 * @brief Retrieve the id of this image format.
 *
 * @return A string identifying the type of layer
 */
  virtual const char * type() const;

/**
 * @brief Retrieve the format of this image.
 *
 * @return The format of the image.
 */
  virtual qgar::QgarAppParamDescr::ParamFormat format() const;


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:


/** @name QGVectorialLayer Impl */
//        =====================
//@{

/**
 * @brief Loads the vectorial items from an image file.
 *
 * Retrieve all vector items from the file matching the filename
 * in the returning vector.
 * Subclasses must provide this method.
 *
 * @param filename  The name of the image file to load.
 * @param vect      [out]The vector in which to store the read items.
 * @return the image width & height
 */
  virtual QPoint loadItems(const QString& filename,
			   QVector<QGraphicsItem *>& vect)
    throw (std::runtime_error);
    
//@}


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
  QGDxfLayer(const QGDxfLayer&);

/**
 * @brief Disabled assignment operator
 */
  QGDxfLayer& operator=(const QGDxfLayer&);


//@}


// -------------------------------------------------------------------
}; // class QGDxfLayer


#endif /* __QGDXFLAYER_H_INCLUDED__ */
