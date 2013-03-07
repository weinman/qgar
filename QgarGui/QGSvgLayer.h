/*---------------------------------------------------------------------*
 | Graphical user interface QgarGui                                    |
 | Copyright (C) 2003  Qgar Project, LORIA                             |
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


#ifndef __QGSVGLAYER_H_INCLUDED__
#define __QGSVGLAYER_H_INCLUDED__


/**
 * @file     QGSvgLayer.h
 * @brief    Header file of class QGSvgLayer
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     May 6, 2003  15:06
 * @since    Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGSvgLayer.h,v 1.2 2005/07/13 16:30:29 masini Exp $ */



// QGUI
#include "QGVectorialLayer.h"
// STD
#include <stdexcept>



/**
 * @class QGSvgLayer QGSvgLayer.h "QGSvgLayer.h"
 * @brief A vectorial layer whose a base image in SVG format.
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   May 6, 2003  15:06
 * @since  Qgar 2.1
 */
class QGSvgLayer

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
  static const char * SVG_TYPE;

//@}


/** @name Constructors */
//        ============
//@{
/**
 * @brief Default constructor
 *
 * Creates an empty layer.
 */
  QGSvgLayer();

/**
 * @brief Creates a layer from the given file.
 *
 * @param filename The name of the SVG file to create the layer from.
 *
 * @throws std::runtime_error if an error while reading the file
 * occurs.
 */
  QGSvgLayer(const QString& filename) throw(std::runtime_error);

//@}


/** @name Destructors */
//        ===========
//@{
/**
 * @brief Destructor
 */
  virtual ~QGSvgLayer();
//@}


/** @name Access */
//        ======
//@{

/**
 * @brief Retrieve the id of this image format type.
 *
 * @return a string identifying the image format of this layer.
 */
  virtual const char * type() const;


/**
 * @brief Retrieve the format of the image this layer is built from.
 *
 * @return The format of this image. 
 */
  virtual qgar::QgarAppParamDescr::ParamFormat format() const;

//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

/** @name QGVectorialLayer Impl */
//        =====================
//@{
  virtual QPoint loadItems(const QString& filename, 
			   std::vector<QGraphicsItem *>& vect)
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
  QGSvgLayer(const QGSvgLayer&);


/**
 * @brief Disabled assignment operator
 */
  QGSvgLayer& operator=(const QGSvgLayer&);

//@}

// -------------------------------------------------------------------
}; // class QGSvgLayer


#endif /* __QGSVGLAYER_H_INCLUDED__ */
