/*---------------------------------------------------------------------*
 | Library QgarApps, graphics analysis and recognition applications    |
 | Copyright (C) 2004  Qgar Project, LORIA                             |
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
 | http://www.gnu.org/licenses/lgpl.html for the terms of the license. |
 | To receive a paper copy, write to the Free Software Foundation,     |
 | Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.       |
 |                                                                     |
 | Contact Project Qgar for any information:                           |
 |   LORIA - équipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-lès-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/


/**
 * @file QAthickThinSeparation.cpp
 *
 * @brief Separate thick line segments from thin line segments
 * in a binary image.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar">Karl Tombre, Philippe Dosch & Bart Lamiroy</a>
 * @date   August 8,  1999  1:50
 * @since  Qgar 1.0
 */



// QGAR
#include <qgarlib/DilatedBinaryImage.h>
#include <qgarlib/GenImage.h>
#include <qgarlib/OpenBinaryImage.h>
#include <qgarlib/PbmFile.h>
#include <qgarlib/QgarApp.h>



using namespace std;
using namespace qgar;



/**
 * @ingroup GRAPHX_THINTHICK
 * @brief Separate thick line segments (or components) from
 *   thin line segments (or components) in a binary image,
 *   using operators of Mathematical Morphology.
 *
 * The result is obtained by consecutively performing an
 * 8-connexity-based opening (i.e. a composition of an
 * erosion and a dilation) and a geodesic recontruction,
 * using a square structural element.
 * The size (i.e. width) of the structural element should be an
 * odd number. If it is not the case, the size is automatically
 * rounded to the nearest superior odd number.
 *
 * Line segments are then classified according to their thickness
 * (width). Line segments having a width greater than the structural
 * element size are stored in a given file, and line segments having
 * a width smaller or equal to the structural element size are
 * stored in second, separate given file.
 *
 * In fact, the method does not only apply to line segments: The source
 * image may contain any kind of graphical elements, identified as
 * the black connected components. Let <i>c</i> be such a component.
 * The (connected) parts of <i>c</i> which fit the structural element
 * (i.e. in which the structural element can be moved without overrunning
 * the border) are considered as ''thick'' elements, the other parts are
 * considered as ''thin'' elements.
 *
 * @warning
 * Let <i>s</i> be the size of the structural element. Because of the
 * very nature of Mathematical Morphology operations, the content of
 * the <i>s</i> rows and columns contiguous to the borders of the
 * resulting image is not relevant.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar">Karl Tombre,
 *   Philippe Dosch & Bart Lamiroy</a>
 * @date   August 8,  1999  1:50
 * @since  Qgar 1.0
 */

int
main(int argc, char* argv[])
{
  QgarApp app;

  // PARAMETERS DESCRIPTION
  // ======================

  //
  app.addParameter("-in",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEIN,
		   "Source image:");

  //
  app.addParameter("-size",
		   QgarArgs::REQPARAM,
		   QgarArgs::INT,
		   "Maximum width:",
		   0,
		   "6");

  //
  app.addParameter("-outhick",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEOUTD,
		   "Image of thick lines:",
		   ".thick.pbm");

  //
  app.addParameter("-outhin",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEOUTD,
		   "Image of thin lines:",
		   ".thin.pbm");

  app.setDescription("Thick-thin separation", QgarArgs::PBM);

  // COMMAND LINE ANALYSIS
  // =====================

  app.analyzeLine(argc, argv);

  // Error while parsing parameters?
  if (app.isError())
    {
      return app._CODE_ERROR;
    }

  // Application invoked with flag '-gui'?
  if (app.isExit())
    {
      return app._CODE_GUI;
    }

  app.showProgressBar();

  // GET SOURCE IMAGE
  // ================

  cout << "Loading source image..." << endl;

  PbmFile sourceFile((char*) app.getStringOption("-in"));
  BinaryImage sourceImg = sourceFile.read();

  app.setProgressBar(20);

  // EXTRACT THICK LINES
  // ===================

  cout << "Extracting thick lines..." << endl;

  OpenBinaryImage thickImg(sourceImg, atoi(app.getStringOption("-size")) / 2);
  DilatedBinaryImage::perform(&thickImg);

  BinaryImage::value_type* pMapSource = sourceImg.pPixMap();
  BinaryImage::value_type* pMapThick  = thickImg.pPixMap();

  int size = thickImg.width() * thickImg.height();
  for (int iCnt = 0 ; iCnt < size; ++iCnt, ++pMapThick, ++pMapSource)
    {
      *pMapThick &= *pMapSource;
    }

  app.setProgressBar(50);

  // SAVE THICK LINES
  // ================

  cout << "Saving thick lines..." << endl;

  PbmFile thickFile((char*) app.getStringOption("-outhick"));
  thickFile.write(thickImg);

  app.setProgressBar(60);

  // EXTRACT THIN LINES
  // ==================

  cout << "Extracting thin lines..." << endl;

  sourceImg -= thickImg;  

  app.setProgressBar(90);

  // SAVE THIN LINES
  // ===============

  cout <<"Saving thin lines..."  << endl;

  PbmFile thinFile((char*) app.getStringOption("-outhin"));
  thinFile.write(sourceImg);

  app.setProgressBar(100);

  // DISPLAY RESULTS
  // ===============

  cout << "Thick-thin separation done." << endl;
  app.closeProgressBar();

  app.showPicture((char*)app.getStringOption("-outhick"));
  app.showPicture((char*)app.getStringOption("-outhin"));

  // NORMAL TERMINATION
  // ==================

  return app._CODE_END;

}
