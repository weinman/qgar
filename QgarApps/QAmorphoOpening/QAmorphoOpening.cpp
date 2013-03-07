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
 * @file QAmorphoOpening.cpp
 *
 * @brief Open a binary image using morphological operators.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   May 2, 2002  17:14
 * @since  Qgar 2.0
 */



// QGAR
#include <qgarlib/GenImage.h>
#include <qgarlib/OpenBinaryImage.h>
#include <qgarlib/PbmFile.h>
#include <qgarlib/QgarApp.h>



using namespace std;
using namespace qgar;



/**
 * @ingroup MATHMORPH_OPEN
 * @brief Opening of a binary image, using a square structural element.
 *
 * The opening is the composition of an erosion and a dilation
 * (8-connexity-based), using a square as structural element. The size
 * (i.e. width) of the structural element should be an odd number.
 * If it is not the case, the size is automatically rounded to the
 * nearest superior odd number.
 *
 * The result is a binary image containing the black pixels sets of the
 * source image which match (are identical to) the structural element.
 * In other words, it does not contain any black region whose size is
 * smaller than the structural element size.
 *
 * @warning Let <i>s</i> be the size of the structural element.
 * Because of the very nature of erosion and dilation, the content of
 * the <i>s</i> rows and columns close to the borders of the resulting
 * image is not relevant.
 *
 * @author  <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date    May 2, 2002  17:14
 * @since   Qgar 2.0
 */

int
main(int argc, char* argv[])
{
  QgarApp app;

  // PARAMETERS DESCRIPTION
  // ======================

  // Pathname of the file containing the source binary image
  app.addParameter("-in",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEIN,
		   "source image:");

  // Size of the square structural element
  app.addParameter("-size",
		   QgarArgs::REQPARAM,
		   QgarArgs::INT,
		   "structural element size:",
		   0,
		   "6");

  // Pathname of the file in which the opening will be stored
  app.addParameter("-out",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEOUTD,
		   "result image:",
		   ".opened.pbm");

  app.setDescription("Image opening", QgarArgs::PBM);

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

  app.showProgressBar();
  app.setProgressBar(25);

  // THE OPENING
  // ===========

  cout << "Performing opening..." << endl;

  OpenBinaryImage::perform(&sourceImg,
			   atoi(app.getStringOption("-size")) / 2);

  app.setProgressBar(75);

  // SAVE RESULT
  // ===========

  cout << "Saving resulting image..." << endl;

  PbmFile resultFile((char*) app.getStringOption("-out"));
  resultFile.write(sourceImg);

  app.setProgressBar(100);

  // DISPLAY RESULT
  // ==============

  cout << "Opening done." << endl;
  app.closeProgressBar();

  app.showPicture((char*) app.getStringOption("-out"));

  // NORMAL TERMINATION
  // ==================

  return app._CODE_END;

}
