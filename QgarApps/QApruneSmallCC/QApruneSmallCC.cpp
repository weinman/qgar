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
 * @file QApruneSmallCC.cpp
 *
 * @brief Prune small connected components of a binary image.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   April 3, 2001  11:35
 * @since  Qgar 2.0
 */



// QGAR
#include <qgarlib/PbmFile.h>
#include <qgarlib/PruneSmallCCBinaryImage.h>
#include <qgarlib/QgarApp.h>



using namespace qgar;
using namespace std;



/**
 * @ingroup CC_PRUNE
 * @brief  Prune small black (connected) components of a binary image.
 *
 * Only black components are considered here. The application delivers
 * two binary images, one containing the black components of the given
 * image having a size smaller than a given threshold, the other
 * containing the black components having a size greater than the
 * threshold.
 *
 * This application is faster than the construction of the whole set of
 * components of the image (see class qgar::ConnectedComponents in the
 * QgaLib library), as it does not construct any effective component:
 * Small components are detected by simply examining configurations of
 * 2*3 pixels (8-connexity based) for each consecutive pairs of rows of
 * the given image.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   April 3, 2001  11:35
 * @since  Qgar 2.0
 */

int
main(int argc, char *argv[])
{
  QgarApp app;

  // PARAMETERS DESCRIPTION
  // ======================

  // Pathname of the file containing the source binary image
  app.addParameter("-in",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEIN,
		   "source image:");

  // Pathname of the file to store small components
  app.addParameter("-outscc",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEOUTD,
		   "image of small CC:",
		   ".smallCC.pbm");

  // Pathname of the file to store big components
  app.addParameter("-outbcc",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEOUTD,
		   "image of big CC:",
		   ".bigCC.pbm");

  // Maximum size of a component to be pruned
  app.addParameter("-prune",
		   QgarArgs::REQPARAM,
		   QgarArgs::INT,
		   "small CC max size:",
		   0,
		   "3");

  app.setDescription("Prune small connnected components", QgarArgs::PBM);

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

  PbmFile sourceFile((char *) app.getStringOption("-in"));
  BinaryImage sourceImg = sourceFile.read();

  app.setProgressBar(20);

  // PRUNE SMALL CC
  // ==============
  
  cout << "Pruning small (connected) components..." << endl;

  PruneSmallCCBinaryImage prunedImg(sourceImg,
				    atoi(app.getStringOption("-prune")));

  app.setProgressBar(50);

  // SAVE BIG CC
  // ===========

  cout << "Saving big components..." << endl;

  PbmFile bigCCFile((char *) app.getStringOption("-outbcc"));
  bigCCFile.write(prunedImg);

  app.setProgressBar(60);

  // CONSTRUCT SMALL CC IMAGE
  // ========================

  cout << "Extracting small components..." << endl;

  sourceImg -= prunedImg;

  app.setProgressBar(90);

  // SAVE SMALL CC
  // =============

  cout << "Saving small components..." << endl;

  PbmFile smallCCFile((char *) app.getStringOption("-outscc"));
  smallCCFile.write(sourceImg);

  app.setProgressBar(100);

  // DISPLAY RESULTS
  // ===============

  cout << "Pruning done." << endl;
  app.closeProgressBar();

  app.showPicture((char *) app.getStringOption("-outbcc"));
  app.showPicture((char *) app.getStringOption("-outscc"));

  // NORMAL TERMINATION
  // ==================

  return app._CODE_END;

}
