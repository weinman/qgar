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


/**
 * @file  QGSwapImagesCommand.cpp
 * @brief Implementation of class QGSwapImagesCommand.
 *
 * See file QGSwapImagesCommand.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   December 3, 2002  16:36
 * @since  Qgar 2.1
 */



// QGUI
#include "QGSwapImagesCommand.h"
#include "QGPixmapLayer.h"
// STD
#include <cstring>



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

QGSwapImagesCommand::QGSwapImagesCommand(QGPixmapLayer * layer, 
					 QImage oldImg,
					 QImage newImg,
					 const QPoint& pos)

  : _oldImg(oldImg),
    _newImg(newImg),
    _pos(pos)

{
  _layer = layer;

  // Convert depth.
  _newImg = _newImg.convertToFormat(_layer->image().format());
}

// ---------------------------------------------------------------------

QGSwapImagesCommand::QGSwapImagesCommand(const QGSwapImagesCommand& rhs)

  : _oldImg(rhs._oldImg),
    _newImg(rhs._newImg),
    _pos(rhs._pos)

{
  _layer = rhs._layer;
}

// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

QGSwapImagesCommand::~QGSwapImagesCommand() 
{
}


// -------------------------------------------------------------------
// 
// -------------------------------------------------------------------


void
QGSwapImagesCommand::copyToImage(QImage& dst, QImage img, int x, int y)
{
  if (dst.depth() == 1) {
    // NOT YET IMPLEMENTED
  }


  else if (dst.depth() == 8) {
    // -----------
    // 8 bpp copy.
    // -----------
    for(int i = 0; i < img.height(); ++i) { // for each line of the
					    // image to copy
            
      // Copy image line to destination, starting at column x
      memcpy( (dst.scanLine(i+y) + x), img.scanLine(i), img.width() );
    }
  }

  else if (dst.depth() == 16) {
    // NOT YET IMPLEMENTED
  }

  else if (dst.depth() == 24) {
    // NOT YET IMPLEMENTED
  }

  else if (dst.depth() == 32) {
    // NOT YET IMPLEMENTED
  }  
}


// -------------------------------------------------------------------
// Q G U N D O A B L E I F     I M P L 
// -------------------------------------------------------------------

void
QGSwapImagesCommand::execute()
{
  copyToImage(_layer->image(), _newImg, _pos.x(), _pos.y());

  _layer->update(_pos.x(), _pos.y(), _newImg.width(), _newImg.height());
}

// ---------------------------------------------------------------------

void
QGSwapImagesCommand::undo()
{
  copyToImage(_layer->image(), _oldImg, _pos.x(), _pos.y());

  _layer->update(_pos.x(), _pos.y(), _newImg.width(), _newImg.height());
}

// ---------------------------------------------------------------------

QGSwapImagesCommand *
QGSwapImagesCommand::clone() const
{
  return new QGSwapImagesCommand(*this);
}

// ---------------------------------------------------------------------
// O P E R A T O R S
// ----------------------------------------------------------------------

QGSwapImagesCommand& 
QGSwapImagesCommand::operator=(const QGSwapImagesCommand& rhs) 
{
  if (this != &rhs) {
    
    QGUndoableCommandIf::operator=(rhs);
    
    _oldImg = rhs._oldImg;
    _newImg = rhs._newImg;
  }

  return *this;
}

// ----------------------------------------------------------------------

