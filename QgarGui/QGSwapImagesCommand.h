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


#ifndef __QGSWAPIMAGESCOMMAND_H_INCLUDED__
#define __QGSWAPIMAGESCOMMAND_H_INCLUDED__


/**
 * @file   QGSwapImagesCommand.h
 * @brief  Header file of class QGSwapImagesCommand.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   December 3, 2002  16:36
 * @since  Qgar 2.1
 */


/* $Id: QGSwapImagesCommand.h,v 1.5 2005/07/13 16:30:29 masini Exp $ */



// QGUI
#include "QGUndoableCommandIf.h"
class QGPixmapLayer;
// QT
#include <QImage>



/**
 * @class QGSwapImagesCommand QGSwapImagesCommand.h "QGSwapImagesCommand.h"
 * @brief Reversible command replacing a part of an image by another.
 *
 * <p>
 * This command replaces an image region by another. This is performed
 * by filling the region by another smaller image.
 * </p>
 * <p>
 * This command stores the image corresponding to region before the
 * replacement has been done, allowing the user to undo the action.
 * </p>
 *
 * @todo Implement image copy for 1bpp, 16 bpp, 24 bpp and 32 bpp images.
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   December 3, 2002  16:36
 * @since  Qgar 2.1
 */
class QGSwapImagesCommand

  : public QGUndoableCommandIf

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
 * @param layer  The layer in which the replacement takes place.
 * @param oldImg The image of the region before the replacement.
 * @param newImg The image to put in place of the old one.
 * @param pos    The position of the replacement.
 */
  QGSwapImagesCommand(QGPixmapLayer * layer, 
		      QImage oldImg,
		      QImage newImg,
		      const QPoint& pos);


/**
 * @brief Copy-constructor
 */
  QGSwapImagesCommand(const QGSwapImagesCommand&);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGSwapImagesCommand();

//@}




/** @name QGUndoablecommandIf IMPL */
//        ========================
//@{

  virtual void execute();

  virtual void undo();

  QGSwapImagesCommand * clone() const;

//@}



/** @name Operators */
//        =========
//@{

/**
 * @brief Assignment operator
 */
  QGSwapImagesCommand& operator=(const QGSwapImagesCommand&);

//@}



// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// A pointer to the pixmap layer this command swaps images in.
  QGPixmapLayer * _layer;

  /// The previous image part.
  QImage _oldImg;

  /// The new image part.
  QImage _newImg;

/**
 *  @brief The position of the top left corner of the region to
 *  substitute the image in.
 */
  QPoint _pos;


/**
 * @brief Replaces a region of an image
 *
 * This method copies an image into a bigger one. The location of the
 * copy if given.
 *
 * @param dst The image in which to copy.
 * @param img The image to be copied.
 * @param x   The x-coordinate of the point locating where to copy
 * must take place.
 * @param y   The x-coordinate of the point locating where to copy
 * must take place.
 */
  void copyToImage(QImage& dst, QImage img, int x, int y);

// -------------------------------------------------------------------
}; // class QGSwapImagesCommand


#endif /* __QGSWAPIMAGESCOMMAND_H_INCLUDED__ */
