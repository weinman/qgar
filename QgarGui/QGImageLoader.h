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


#ifndef __QGIMAGELOADER_H_INCLUDED__
#define __QGIMAGELOADER_H_INCLUDED__


/**
 * @file     QGImageLoader.h
 * @brief    Header file of class QGImageLoader
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 21, 2002  17:37
 * @since Qgar 2.1
 */


/* $Id: QGImageLoader.h,v 1.5 2005/07/13 16:30:27 masini Exp $ */



// QGUI
class QGLayerIf;
// QT
class QString;



/**
 * @class QGImageLoader QGImageLoader.h "QGImageLoader.h"
 * @brief Factory creating an image layer (QGLayerIf instance) from an
 * image file..
 * 
 * This class implements a singleton pattern.
 *
 * @warning Current implementation of the singleton is not thread-safe.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 21, 2002  17:37
 *
 * @since Qgar 2.1
 */
class QGImageLoader
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
  virtual ~QGImageLoader();
//@}


/** @name Access */
//        ======
//@{

/**
 * @brief Access to the unique instance.
 *
 * @return The unique instance of this class.
 */
  static QGImageLoader* instance();

//@}


/**
 * @brief Loads an image and create the matching layer.
 *
 * The method creates a correct layer according to the image file format.
 *
 * @param filename The name of the image file to load.
 *
 * @return The layer handling the image file.
 */
  QGLayerIf* loadLayer(const QString& filename);



// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

/** @name Constructors */
//        ============
//@{

/**
 * @brief Default constructor
 *
 * This class is a singleton. The only way to retrieve a valid instance is thru
 * the instance() function member.
 */
  QGImageLoader();

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
  QGImageLoader(const QGImageLoader&);

/**
 * @brief Disabled assignment operator
 */
  QGImageLoader& operator=(const QGImageLoader&);

//@}

// -------------------------------------------------------------------
}; // class QGImageLoader


#endif /* __QGIMAGELOADER_H_INCLUDED__ */
