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
 * @file QAthrsBinarization.cpp
 *
 * @brief Binarization using a constant threshold.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   August 8,  1999  1:50
 * @since  Qgar 1.0
 */



// STD
#include <string>
// QGAR
#include <qgarlib/GenImage.h>
#include <qgarlib/PbmFile.h>
#include <qgarlib/PgmFile.h>
#include <qgarlib/QgarApp.h>
#include <qgarlib/ThresBinaryImage.h>



using namespace qgar;
using namespace std;



/**
 * @ingroup BIN_BASIC
 *
 * @brief Elementary binarization, using a constant threshold.
 *
 * All pixels having a grey-level number greater than the given
 * threshold are set to <b>white</b> (0), the others are set
 * to <b>black</b> (1).
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   August 8,  1999  1:50
 * @since  Qgar 1.0
 */

int
main(int argc, char* argv[])
{
  QgarApp app;
  
  // PARAMETER DESCRIPTION
  // =====================

  // Pathname of the file containing the source grey-level image
  app.addParameter("-in",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEIN,
		   "Source image:");

  // Pathname of the file to store the binarized image
  app.addParameter("-out",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEOUTD,
		   "Result image:",
		   ".pbm");

  // Binarization threshold
  app.addParameter("-t",
		   QgarArgs::REQPARAM,
		   QgarArgs::INT,
		   "Binarization threshold:",
		   0,
		   "127");
  
  app.setDescription("Binarization using a constant threshold.",
		     QgarArgs::PGM);

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

  PgmFile sourceFile((char*) app.getStringOption("-in"));
  GreyLevelImage sourceImg = sourceFile.read();

  app.setProgressBar(30);

  // BINARIZATION
  // ============

  cout << "Performing binarization..." << endl;

  ThresBinaryImage resultImg(sourceImg, atoi(app.getStringOption("-t")));

  app.setProgressBar(70);

  // SAVE RESULT
  // ===========

  cout << "Saving result image..." << endl;

  PbmFile resultFile((char*) app.getStringOption("-out"));
  resultFile.write(resultImg);

  app.setProgressBar(100);
  
  // DISPLAY RESULT
  // ==============

  cout << "Binarization done" << endl;
  app.closeProgressBar();
  
  app.showPicture((char*) app.getStringOption("-out"));
  
  // NORMAL TERMINATION
  // ==================

  return app._CODE_END;

}
