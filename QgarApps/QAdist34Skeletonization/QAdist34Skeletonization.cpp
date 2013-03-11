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
 |   LORIA - йquipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-lиs-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/


/**
 * @file QAdist34Skeletonization.cpp
 *
 * @brief Binary image skeletonization, using 3-4 Chamfer distance.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   April 8, 2005  15:15
 * @since  Qgar 2.2
 */



// STL
#include <list>
#include <iostream>
#include <iomanip>

// QGAR
#include <qgarlib/CleanedBinaryImage.h>
#include <qgarlib/Dist34BlackCCImage.h>
#include <qgarlib/GenImage.h>
#include <qgarlib/HysteresisBinaryImage.h>
#include <qgarlib/LabeledSkeletonImage.h>
#include <qgarlib/LinkedChainList.h>
#include <qgarlib/PbmFile.h>
#include <qgarlib/PgmFile.h>
#include <qgarlib/QgarApp.h>



using namespace qgar;
using namespace std;



/**
 * @ingroup GRAPHX_SKEL
 *
 * @brief Binary image skeletonization, using 3-4 Chamfer distance.
 *
 * The result is an <b>image</b> of the corresponding skeleton.
 *
 * @todo
 * <ul>
 * <li>To be documented with full details!...</li>
 * <li>The chains of points of the skeleton
 *   should be optionally saved (in a file).</li>
 * </ul>
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   April 8, 2005  15:15
 * @since  Qgar 2.2
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
  app.addParameter("-outdist",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEOUT,
		   "distance image:",
		   ".34dist.pgm");

  // Output file
  app.addParameter("-outlab",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEOUT,
		   "labeled skeleton image:",
		   ".34lab.pgm");

  // Output file
  app.addParameter("-outch",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEOUT,
		   "chains of skeleton image:",
		   ".34ch.pgm");

  // Output file
  app.addParameter("-outskel",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEOUTD,
		   "binary skeleton image:",
		   ".34skel.pbm");

  // Maximum number of peripheral rows and/or columns which may be missed
  app.addParameter("-prune",
		   QgarArgs::OPTPARAM,
		   QgarArgs::INT,
		   "peripheral rows max number:",
		   0,
		   "3");

   app.setDescription("(3,4)-distance-based skeletonization", QgarArgs::PBM);

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
  
  PbmFile sourceFile((char*) app.getStringOption("-in"));
  BinaryImage sourceImg = sourceFile.read();

  app.setProgressBar(10);

  // CLEAN SOURCE IMAGE
  // ==================

  cout << "Cleaning source image..." << endl;

  CleanedBinaryImage cleanedImg(sourceImg);

  app.setProgressBar(20);

  // COMPUTING DISTANCE TRANSFORM
  // ============================

  cout << "Computing distance transform of source image..." << endl;

  Dist34BlackCCImage dist34Img(cleanedImg);

  // SAVE RESULT
  // ===========

  PgmFile distFile((char*) app.getStringOption("-outdist"));
  distFile.write(dist34Img);

  app.setProgressBar(30);

  // SKELETONIZATION
  // ===============

  cout << "Performing skeletonization..." << endl;

  LabeledSkeletonImage labImg(dist34Img, (app.isOptionSet("-prune")) ? atoi(app.getStringOption("-prune")) : 3);

  // SAVE RESULT
  // ===========

  PgmFile labFile((char*) app.getStringOption("-outlab"));
  labFile.write(labImg);

  app.setProgressBar(60);

  // CHAINING SKELETON POINTS
  // ========================

  cout << "Chaining skeleton points..." << endl;

  LinkedChainList chainsList(labImg);

  cout << setw(5) << chainsList.size() << " chains found" << endl;

  app.setProgressBar(70);

  // WRITE RESULT IMAGE
  // ==================
  
  cout << "Extracting skeleton..." << endl;
  
  IntImage chImg(sourceImg.width(), sourceImg.height());
  memset(chImg.pPixMap(), 0, sizeof(IntImage::value_type) * chImg.width() * chImg.height());
  BinaryImage skelImg(sourceImg.width(), sourceImg.height());
  memset(skelImg.pPixMap(), 0, sizeof(BinaryImage::value_type) * skelImg.width() * skelImg.height());  

  IntImage::value_type chCnt = 1;
  LinkedChainList::iterator itChain = chainsList.begin();

  while (itChain != chainsList.end())
    {
      cout << setw(5) << chCnt << " chain. ";
      cout << setw(5) << itChain->size() << " points." << endl;

      // Access the beginning of the list of points      
      list<Point>::iterator itPoint = (itChain->pointList()).begin();

      for(/* EMPTY */ ; itPoint != (itChain->pointList()).end() ; ++itPoint)
	{
          chImg.setPixel((*itPoint).x(), (*itPoint).y(), chCnt);
	  skelImg.setPixel((*itPoint).x(), (*itPoint).y(), 1);
	}

      ++chCnt;
      ++itChain;
    }

  app.setProgressBar(90);

  // SAVE RESULT
  // ===========

  PgmFile chFile((char*) app.getStringOption("-outch"));
  chFile.write(chImg);
  PbmFile skelFile((char*) app.getStringOption("-outskel"));
  skelFile.write(skelImg);

  app.setProgressBar(100);
  cout << "Skeletonization done." << endl;
  app.closeProgressBar();

  app.showPicture((char*)app.getStringOption("-outskel"));

  // EXIT THE PROGRAM
  // ================
  
  return app._CODE_END;

}
