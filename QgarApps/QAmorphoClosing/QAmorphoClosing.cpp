/*---------------------------------------------------------------------*
 | Library QgarLib, graphics analysis and recognition                  |
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
 * @file QAmorphoClosing.cpp
 *
 * @brief Close an image using morphological operators.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   May 2, 2002  16:14
 * @since  Qgar 2.0
 */



// QGAR
#include <qgarlib/CloseBinaryImage.h>
#include <qgarlib/GenImage.h>
#include <qgarlib/PbmFile.h>
#include <qgarlib/QgarApp.h>



using namespace qgar;
using namespace std;



/**
 * @ingroup MATHMORPH_CLOSE
 * @brief  Closing of a binary image, using a square structural
 *   element.
 *
 * The closing is the composition of a dilation and an erosion
 * (8-connexity-based), using a square as structural element. The size
 * (i.e. width) of the structural element should be an odd number.
 * If it is not the case, the size is automatically rounded to the
 * nearest superior odd number.
 *
 * The result is a binary image containing the white pixels sets of the
 * source image which match (are identical to) the structural element.
 * In other words, it does not contain any white region whose size is
 * smaller than the structural element size.
 *
 * @warning Let <i>s</i> be the size of the structural element.
 * Because of the very nature of dilation and erosion, the content of
 * the <i>s</i> rows and columns close to the borders of the resulting
 * image is not relevant.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   May 2, 2002  16:14
 * @since  Qgar 2.0
 */

int
main(int argc, char * argv[])
{
  QgarApp app;

  // PARAMETER DESCRIPTION
  // =====================

  // Pathname of the file containing the source binary image
  app.addParameter("-in",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEIN,
		   "Source image:");

  // Pathname of the file to store the closing
  app.addParameter("-size",
		   QgarArgs::REQPARAM,
		   QgarArgs::INT,
		   "Structural element size:",
		   0,
		   "6");

  // Size of the square structural element used for the closing
  app.addParameter("-out",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEOUTD,
		   "Result image:",
		   ".closed.pbm");

  app.setDescription("Image closing", QgarArgs::PBM);

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
  app.setProgressBar(0);

  // GET SOURCE IMAGE
  // ================

  cout << "Loading source image..." << endl;

  PbmFile sourceFile((char*) app.getStringOption("-in"));
  BinaryImage sourceImg = sourceFile.read();

  app.setProgressBar(25);

  // CLOSING
  // =======

  cout << "Performing closing..." << endl;

  CloseBinaryImage::perform(&sourceImg,
			    atoi(app.getStringOption("-size")) / 2);

  app.setProgressBar(75);

  // SAVE RESULT
  // ===========

  cout << "Saving result image..." << endl;

  PbmFile resultFile((char*) app.getStringOption("-out"));
  resultFile.write(sourceImg);

  app.setProgressBar(100);
  
  // DISPLAY RESULT
  // ==============

  cout << "Closing done." << endl;
  app.closeProgressBar();

  app.showPicture((char*) app.getStringOption("-out"));

  // NORMAL TERMINATION
  // ==================

  return app._CODE_END;
}
