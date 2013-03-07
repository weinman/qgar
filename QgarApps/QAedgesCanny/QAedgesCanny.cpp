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
 * @file QAedgesCanny.cpp
 *
 * @brief Edges detection using Canny's operator.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   June 18, 2002  18:13
 * @since  Qgar 2.1.1
 */



// STL
#include <list>

// QGAR
#include <qgarlib/CannyGradientImage.h>
#include <qgarlib/GenImage.h>
#include <qgarlib/GradientLocalMaxImage.h>
#include <qgarlib/HysteresisBinaryImage.h>
#include <qgarlib/PbmFile.h>
#include <qgarlib/PgmFile.h>
#include <qgarlib/QgarApp.h>



using namespace qgar;
using namespace std;



/**
 * @ingroup EDGES_CANNY
 * @brief Edges detection using Canny's operator.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   June 18, 2002  18:13
 * @since  Qgar 2.1.1
 */

int
main(int argc, char* argv[])
{
  QgarApp app;
  
  // PARAMETERS DESCRIPTION
  // ======================

  // Input file
  app.addParameter("-in",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEIN,
		   "source image:");

  // Output file
  app.addParameter("-out",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEOUTD,
		   "result image:",
		   ".pbm");

  //
  app.addParameter("-low",
		   QgarArgs::REQPARAM,
		   QgarArgs::INT,
		   "low Gradient threshold:",
		   0,
		   "0");

  //
  app.addParameter("-high",
		   QgarArgs::REQPARAM,
		   QgarArgs::INT,
		   "high Gradient threshold:",
		   0,
		   "5");

  app.setDescription("Edges detection", QgarArgs::PGM);

  // ANALYZE THE COMMAND LINE
  // ========================

  app.analyzeLine(argc, argv);

  if (app.isError())
    {
      return app._CODE_ERROR;
    }

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

  app.setProgressBar(20);

  // COMPUTE GRADIENT
  // ================

  cout << "Computing Gradient..." << endl;

  // Canny, using sigma == 1.2
  CannyGradientImage gradImg(sourceImg, 1.2);

  app.setProgressBar(40);

  // COMPUTE LOCAL MAXIMA
  // ====================

  cout << "Computing local maxima..." << endl;

  GradientLocalMaxImage maxImg(gradImg);

  app.setProgressBar(60);

  // HYSTERESIS THRESHOLDING
  // =======================

  cout << "Hysteresis thresholding..." << endl;

  HysteresisBinaryImage edgesImg(maxImg, 
				 atoi(app.getStringOption("-low")),
				 atoi(app.getStringOption("-high")));

  app.setProgressBar(80);

  // SAVE RESULT
  // ===========

  cout << "Saving edges..." << endl;

  PbmFile resultFile((char*) app.getStringOption("-out"));
  resultFile.write(edgesImg);

  app.setProgressBar(100);

  // DISPLAY RESULT
  // ==============

  cout << "Edges detection done." << endl;
  app.closeProgressBar();

  app.showPicture((char*)app.getStringOption("-out"));

  // NORMAL TERMINATION
  // ==================

  return app._CODE_END;
}
