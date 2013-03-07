/*---------------------------------------------------------------------*
 | Library QgarLib, graphics analysis and recognition                  |
 | Copyright (C) 2002  Qgar Project, LORIA                             |
 |                                                                     |
 | This library is free software; you can redistribute it and/or       |
 | modify it under the terms of the GNU Lesser General Public          |
 | License version 2.1, as published by the Free Software Foundation.  |
 |                                                                     |
 | This library is distributed in the hope that it will be useful,     |
 | but WITHOUT ANY WARRANTY; without even the implied warranty of      |
 | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                |
 | See the GNU Lesser General Public License for more details.         |
 |                                                                     |
 | The GNU Lesser General Public License is included in the file       |
 | LICENSE.LGPL, in the root directory of the Qgar packaging. See      |
 | http://www.gnu.org/licenses/lgpl.html for the terms of the licence. |
 | To receive a paper copy, write to the Free Software Foundation,     |
 | Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.       |
 |                                                                     |
 | Contact Project Qgar for any information:                           |
 |   LORIA - �quipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-l�s-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/


/**
 * @file  DilatedImage.cpp
 * @brief Implementation of class DilatedImage
 *
 * See file DilatedImage.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 5, 2002  17:39
 * @since  Qgar 2.0
 */


// STD
#include <sstream>
// QGAR
#include <qgarlib/DilatedImage.h>
#include <qgarlib/LinDilatedImage.h>
#include <qgarlib/GenImage.h>
#include <qgarlib/QgarErrorDomain.h>



namespace qgar
{

// -------------------------------------------------------------------
// C O N S T R U C T O R
// -------------------------------------------------------------------
DilatedImage::DilatedImage(GreyLevelImage& anImg, unsigned int aDilSize)
  throw(QgarErrorDomain)
  : GreyLevelImage(anImg)
{
  int sqsize = (2 * aDilSize) + 1;  // Effective mask size

  if ((sqsize > anImg.width()) || (sqsize > anImg.height()))
    {
      std::ostringstream os;
      os << "Dilation size ("
	 << aDilSize
	 << " -> "
	 << sqsize
	 << ") too large for an image "
	 << anImg.width()
	 << " X "
	 << anImg.height();
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "qgar::DilatedImage::DilatedImage(qgar::GreyLevelImage&, unsigned int)",
			    os.str());
    }

  perform(this, aDilSize);
}
 
// -------------------------------------------------------------------
// D I L A T I O N
// -------------------------------------------------------------------

void
DilatedImage::perform(GreyLevelImage* anImg, unsigned int aDilSize)
{
  LinDilatedImage::perform(anImg, QGE_ORIENTATION_HOR, aDilSize);
  LinDilatedImage::perform(anImg, QGE_ORIENTATION_VER, aDilSize);
}

// -------------------------------------------------------------------

} // namespace qgar


