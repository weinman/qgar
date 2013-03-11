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
 |   LORIA - йquipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-lиs-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/


/**
 * @file QAvectorizationRW.cpp
 *
 * @brief Vectorization using Rosin & West's polygonal approximation.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   June 18,  2004  18:41
 * @since  Qgar 2.0
 */



// STD
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <list>
// QGAR
#include <qgarlib/CleanedBinaryImage.h>
#include <qgarlib/Dist34BlackCCImage.h>
#include <qgarlib/DxfFile.h>
#include <qgarlib/GenImage.h>
#include <qgarlib/LabeledSkeletonImage.h>
#include <qgarlib/LinkedChainList.h>
#include <qgarlib/PbmFile.h>
#include <qgarlib/QgarApp.h>
#include <qgarlib/RWSegmentVector.h>



using namespace qgar;
using namespace std;



/**
 * @ingroup GRAPHX_VECTO
 *
 * @brief Vectorization using a polygonal approximation
 * as proposed by Rosin & West.
 *
 *
 * @todo To be fully documented!...
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   June 18,  2004  18:41
 * @since  Qgar 2.0
 */

int
main(int argc, char *argv[])
{
  QgarApp app;

  // PARAMETERS DESCRIPTION
  // ======================

  // Binary source image
  app.addParameter("-in",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEIN,
		   "source image:");

  // File to store resulting vectors (line segments)
  app.addParameter("-out",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEOUTD,
		   "image of vectors:",
		   ".dxf");  

  // Maximum number of peripheral rows and/or columns which may be missed
  app.addParameter("-prune",
		   QgarArgs::OPTPARAM,
		   QgarArgs::INT,
		   "peripheral rows max number:",
		   0,
		   "5");

  app.setDescription("Rosin-&-West-based vectorization",
		     QgarArgs::PBM);

  // COMMAND LINE ANALYSIS
  // =====================

  app.analyzeLine(argc, argv);

  if (app.isError() || app.isExit())
    {
      exit(1);
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

  app.setProgressBar(30);

  // SKELETONIZATION
  // ===============

  cout << "Performing skeletonization..." << endl;

  LabeledSkeletonImage skelImg(dist34Img, (app.isOptionSet("-prune")) ? atoi(app.getStringOption("-prune")) : 5);

  app.setProgressBar(40);

  // CHAINING SKELETON POINTS
  // ========================

  cout << "Chaining skeleton points..." << endl;

  LinkedChainList chainsList(skelImg);

  cout << setw(5) << chainsList.size() << " chains found" << endl;

  app.setProgressBar(50);

  // POLYGONAL APPROXIMATION
  // =======================

  cout << "Performing polygonal approximation..." << endl;

  LinkedChainList::iterator itChain = chainsList.begin();

  // OPEN REQUIRED (DXF) FILES

  DxfFile segResFile((char*) app.getStringOption("-out"));
  segResFile.openWONLY();
  segResFile.writeHeader();  

  int chCnt = 1;

  // PERFORM POLYGONAL APPROXIMATION ON EACH CHAIN

  while (itChain != chainsList.end())
    {

      cout << setw(5) << chCnt << " chain. ";
      cout << setw(5) << itChain->size() << " points. ";      

      // Polygonal approximation
      RWSegmentVector aPolygApprox(*itChain);

      cout << setw(5) << aPolygApprox.size() << " segments.";

      RWSegmentVector::iterator itSeg = aPolygApprox.begin();

      // Access the beginning of the list of points
      list<Point>::iterator itPoint = (itChain->pointList()).begin();

      // Compute line width
      int myw = (int) skelImg.pixel(itPoint->x(), itPoint->y());
      int numPixel = 1;
      long int totalWidth;
      int totalNumPixels;
      int thickness;

      while ((*itPoint) != itSeg->target())
	{
	  ++itPoint;
	  myw += (int) skelImg.pixel(itPoint->x(), itPoint->y());
	  ++numPixel;
	}
      
      myw = (myw * 2) / (3 * numPixel);
      totalWidth = myw * numPixel;
      totalNumPixels = numPixel;

      // Build a Qgar polyline - Initialize width (useless!)
      QgarSegment tmpSeg(itSeg->source(),
			 itSeg->target(),
			 myw,
			 QGE_COLOR_DEFAULT);

      QgarPolyline myPol(tmpSeg);
      ++itSeg;

      // Complete it with the remaining segments

      while (itSeg != aPolygApprox.end())
	{
	  // Compute line width
      
	  myw = (int) skelImg.pixel(itPoint->x(), itPoint->y());
	  numPixel = 1;
      
	  while ((*itPoint) != itSeg->target())
	    {
	      ++itPoint;
	      myw += (int) skelImg.pixel(itPoint->x(), itPoint->y());
	      ++numPixel;
	    }
      
	  myw = (myw * 2) / (3 * numPixel);
	  totalWidth += myw * numPixel;
	  totalNumPixels += numPixel;

	  // Expand the polyline
	
	  myPol.appendTarget(itSeg->target());
	  ++itSeg;
	}

      // Set the final width, and save the Qgar polyline

      thickness = totalWidth / totalNumPixels;
      
      cout << setw(5) << thickness << " points thick." << endl;

      myPol.setThickness(thickness);
      segResFile.write(myPol);        

      ++chCnt;
      ++itChain;
    } // END while


  // CLOSE FILES

  segResFile.writeFooter();
  segResFile.close();  

  // DISPLAY RESULT
  // ==============

  app.setProgressBar(100);
  cout << "Vectorization done." << endl;
  app.closeProgressBar();

  app.showPicture((char*)app.getStringOption("-out"));  

  // EXIT THE PROGRAM
  // ================
  
  return app._CODE_END;

}
