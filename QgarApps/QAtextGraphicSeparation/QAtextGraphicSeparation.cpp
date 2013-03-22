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
 * @file QAtextGraphicSeparation.cpp
 *
 * @brief Separate textual parts from graphics parts
 *  among components of a binary image.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar">Karl Tombre, Philippe Dosch & Bart Lamiroy</a>
 * @date   October 15,  1997  10:48
 * @since  Qgar 1.0
 */



// For debugging only
#include <iostream>



// STD
#include <list>
// QGAR
#include <qgarlib/Component.h>
#include <qgarlib/ConnectedComponents.h>
#include <qgarlib/GenImage.h>
#include <qgarlib/Histogram.h>
#include <qgarlib/Maer.h>
#include <qgarlib/PbmFile.h>
#include <qgarlib/primitives.h>
#include <qgarlib/PruneSmallCCBinaryImage.h>
#include <qgarlib/QgarApp.h>



using namespace std;
using namespace qgar;




// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TYPEDEF
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


/**
 * @ingroup TEXT_GRAPH
 *
 * @brief Pointer to a node of the component tree
 *   (representing a component).
 */
typedef ConnectedComponents::node_type QGTnode;


/**
 * @ingroup TEXT_GRAPH
 *
 * @brief Label type.
 */
typedef Component::label_type QGTlabel;


// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT



/**
 * @ingroup TEXT_GRAPH
 *
 * @brief Compute the size (bounding box area)
 *   of the biggest black component.
 *
 * @param aPNode    pointer to the root of the component tree
 * @param aMaxSize  size of the biggest black component
 */

void
qaMaxBlackCC(QGTnode* aPNode, int& aMaxSize)
{
  if (aPNode != 0)
    {
      const Component& cc = *(aPNode->data());

      if (cc.color() == QGE_BW_BLACK)
	{
	  int bbArea = (cc.accessBoundingBox()).area();
	  if (bbArea > aMaxSize)
	    {
	      aMaxSize = bbArea;
	    }
	  // WARNING:
	  // Examining the descendants of a black component
	  // is useless as they are supposed to be *smaller*
	  // (according the bounding box size criterium) than
	  // the component itself
	}
      else
	{
	  QGTnode* pChild = aPNode->pFirstChild();

	  while (pChild != 0)
	    {
	      qaMaxBlackCC(pChild, aMaxSize);
	      pChild = pChild->pRSibling();
	    }
	}
    } // END if aPNode
}


/**
 * @ingroup TEXT_GRAPH
 *
 * @brief Compute histogram of black component areas.
 *
 * @param aPNode     pointer to the root of the component tree
 * @param aHist      histogram of black component areas
 * @param aSum       sum of black components areas
 * @param aCompCnt   black components count
 */

void
qaBlackAreaHist(QGTnode* aPNode,
		Histogram& aHist,
		long& aSum,
		int& aCompCnt)
{
  if (aPNode != 0)
    {
      const Component& cc = *(aPNode->data());

      if (cc.color() == QGE_BW_BLACK)
	{
	  int bbArea = (cc.accessBoundingBox()).area();
	  aHist.plus(bbArea);
	  aSum += bbArea;
	  ++aCompCnt;
	}

      QGTnode* pChild = aPNode->pFirstChild();

      while (pChild != 0)
 	{
 	  qaBlackAreaHist(pChild, aHist, aSum, aCompCnt);
  	  pChild = pChild->pRSibling();
 	}
    }
}


/**
 * @ingroup TEXT_GRAPH
 *
 * @brief Get ratio between longest and shortest sides of given MAER.
 *
 * @param aMaer  a Minimum-Area Encasing Rectangle
 */

double
qaMaxMinRatio(const Maer& aMaer)
{
  list<DPoint>::const_iterator itPL1 = (aMaer.accessVertices()).begin();
  list<DPoint>::const_iterator itPL2 = itPL1;
  ++itPL2;

  // distance betwen first two vertices
  double d1 = qgDist(*itPL1, *itPL2);

  // distance betwen second and third vertices
  ++itPL1;
  ++itPL2;
  double d2 = qgDist(*itPL1, *itPL2);

  if (d1 > d2)
    {
      return d1 / d2;
    }
  else
    {
      return d2 / d1;
    }
}


/**
 * @ingroup TEXT_GRAPH
 *
 * @brief
 *
 * @param aPNode      pointer to the root of a component tree
 * @param aPCompList  
 * @param anAreaThrs  
 * @param aSizeThrs   
 * @param aDimThrs    
 *
 * @todo To be documented!...
 */

void
qaFilter(QGTnode* aPNode,
       list<Component*>& aPCompList,
       int anAreaThrs,
       int aSizeThrs,
       int aDimThrs)
{
  if (aPNode != 0)
    {
      const Component& cc = *(aPNode->data());

      if (cc.color() == QGE_BW_BLACK)
 	{
	  const BoundingBox& bbox = cc.accessBoundingBox();

	  // IMHO at least the test (bbox.area() < anAreaThrs) is
	  // unnecessary, since it is included in the other ones.
	  // I strongly suspect we can reduce the four remaining tests
	  // into 3 tests. 
	  // bbox.length() < aDimThrs * aSizeThrs && 
	  // bbox.height() < aDimThrs * aSizeThrs &&
	  // bbox.area() < anAreaThrs 
	  // should give similar results

	  if ((bbox.area() < anAreaThrs) &&
	      (bbox.length() < aDimThrs * bbox.height()) &&
	      (bbox.height() < aDimThrs * bbox.length()) &&
	      (bbox.length() < aSizeThrs) &&
	      (bbox.height() < aSizeThrs))
	    {
	      aPCompList.push_back(aPNode->data());
	    }
 	}

      QGTnode* pChild = aPNode->pFirstChild();

      while (pChild != 0)
 	{
 	  qaFilter(pChild, aPCompList, anAreaThrs, aSizeThrs, aDimThrs);
  	  pChild = pChild->pRSibling();
 	}
    }
}

 
// -------------------------------------------------------------------
// -------------------------------------------------------------------
// M A I N
// -------------------------------------------------------------------
// -------------------------------------------------------------------

/**
 * @ingroup TEXT_GRAPH
 * @brief  Separate textual parts from graphics parts among components
 *   of a binary image.
 *
 * @todo
 * <ul>
 * <li>To be documented!...</li>
 * <li>Do not prune small components: Construct connected components
 *   and then discard those which are too small. At least one complete
 *   traversal of the source image is saved in that way!</li>
 * </ul>
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar">Karl Tombre, Philippe Dosch & Bart Lamiroy</a>
 * @date   October 15,  1997  10:48
 * @since  Qgar 1.0
 */

int
main(int argc, char* argv[])
{
  QgarApp app;

  // PARAMETERS DESCRIPTION
  // ======================

  // Source image
  app.addParameter("-in",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEIN,
		   "source image:");

  // Image of textual parts
  app.addParameter("-outxt",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEOUTD,
		   "image of textual parts:",
		   ".text.pbm");

  // Image of graphical parts
  app.addParameter("-outg",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEOUTD,
		   "image of graphical parts:",
		   ".graphx.pbm");

  // Image of undertermined parts
  app.addParameter("-outu",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEOUTD,
		   "image of undetermined parts:",
		   ".undet.pbm");

  // Maximum size of a black component to be pruned
  app.addParameter("-prune",
		   QgarArgs::OPTPARAM,
		   QgarArgs::INT,
		   "small CC max size:",
		   0,
		   "3");

  // Factor to be multiplied by the average bounding box area to get
  // the maximum area of a bounding box of a textual component.
  app.addParameter("-area",
		   QgarArgs::REQPARAM,
		   QgarArgs::INT,
		   "multiplying factor for textual max box area:",
		   0,
		   "3");

  // Maximum elongation factor of the bounding box of a textual component
  app.addParameter("-elbbox",
		   QgarArgs::REQPARAM,
		   QgarArgs::INT,
		   "max elongation factor of a textual box:",
		   0,
		   "20.");

  // Minimum elongation factor of the Minimum-Area Encasing Rectangle
  // (MAER) of a dash character
  app.addParameter("-elmaer",
		   QgarArgs::REQPARAM,
		   QgarArgs::FLOAT,
		   "min elongation factor of a dash MAER:",
		   0,
		   "2.");

  // Minimum value of the Minimum-Area Encasing Rectangle
  // (MAER) density of a dash character
  app.addParameter("-dmaer",
		   QgarArgs::REQPARAM,
		   QgarArgs::FLOAT,
		   "min density of a dash MAER:",
		   0,
		   ".6");

  app.setDescription("Text-graphics separation", QgarArgs::PBM);

  // ANALYZE THE COMMAND LINE
  // ========================

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

  app.setProgressBar(10);

  // PRUNE SMALL CONNECTED COMPONENTS
  // ================================

  if (app.isOptionSet("-prune"))
    {
      cout << "Pruning small components..." << endl;

      PruneSmallCCBinaryImage prunImg(sourceImg,
				      atoi(app.getStringOption("-prune")));
      sourceImg = prunImg;

      app.setProgressBar(20);
    }


  // CONSTRUCT CONNECTED COMPONENTS
  // ==============================

  cout << "Constructing connected components..." << endl;
  
  ConnectedComponents ccImg(sourceImg);

  if (ccImg.componentCnt() < 2)
    {
      // 1 component: The given image is completely white!
      std::cerr << std::endl
		<< "QGAR APPLICATION: User error"
		<< std::endl
		<< "QAtextGraphicsSeparation >>> File "
		<< (char*) app.getStringOption("-in")
		<< " is blank!"
		<< std::endl;
      return app._CODE_ERROR;
    }

  QGTnode* pCCRoot = ccImg.pRoot();

  app.setProgressBar(30);

  // TEXT-GRAPHICS SEPARATION
  // ========================

  cout << "Text-graphics separation..." << endl;
  
  // Find area of the bounding box containing the biggest black component
  int maxBlackArea = 0;
  qaMaxBlackCC(pCCRoot, maxBlackArea);

  // Create a histogram for areas of black components
  Histogram areaHist(1,            // lower bound
		     maxBlackArea, // upper bound
		     10000);           // sampling rate

  // Sum of areas stored in histogram
  long areaSum = 0;
  // Number of connected components contributing to the histogram 
  int ccNb = 0;
  // Filling the histogram while computing areaSum and ccNb
  qaBlackAreaHist(pCCRoot, areaHist, areaSum, ccNb);

  // Most populated area
  int mostFrequentBboxArea = areaHist.maxSample();
  // Average area
  int averageBboxArea = areaSum / ccNb;

  // Compute thresholds for filtering bounding boxes
  // supposed to contain text characters

  // Threshold for bounding box areas filtering
  int areaThres =
    atoi(app.getStringOption("-area")) * max(mostFrequentBboxArea, averageBboxArea);

  // Threshold for bounding box lengths filtering
  int sizThres = (int) sqrt((double) areaThres);


//////////////////////////////////////////////////////////////////////////////  
  cout << endl << "SAMPLING RATE = 10000"
       << endl << "MAX BLACK CC AREA = " << maxBlackArea
       << endl << "NB OF CC IN HISTOGRAM = " << ccNb
       << endl << "MOST POPULATED AREA = " << mostFrequentBboxArea
       << endl << "AVERAGE AREA = " << averageBboxArea
       << endl << "THRESHOLD FOR BOUNDING BOX AREAS FILTERING = " << areaThres
       << endl << "THRESHOLD FOR BOUNDING BOX LENGTHS FILTERING = " << sizThres
       << endl
       << endl;
//////////////////////////////////////////////////////////////////////////////

  app.setProgressBar(50);

  // ????????????????????????
  // ========================

  list<Component*> ccList;

  qaFilter(pCCRoot,
	   ccList,
	   areaThres,
	   sizThres,
	   atoi(app.getStringOption("-elbbox")));

  vector<Component::label_type> labSet;
  vector<Component::label_type> dashSet;

  list<Component*>::iterator itCL = ccList.begin();

   while (itCL != ccList.end())
    {
      Component* pCC = *itCL;

      if (pCC->densityMaer() > atof(app.getStringOption("-dmaer")))
	{
	  if (qaMaxMinRatio(pCC->accessMaer()) > atof(app.getStringOption("-elmaer")))
	    {
	      dashSet.push_back(pCC->label());
	    }
	  else
	    {
	      labSet.push_back(pCC->label());
	    }
	}
      else
	{
	  labSet.push_back(pCC->label());
	}

      ++itCL;
    } // END while
  
  BinaryImage* pImgSep   = ccImg.makeBinaryImg(labSet);
  BinaryImage* pImgDoubt = ccImg.makeBinaryImg(dashSet);

  sourceImg -= *pImgSep;
  sourceImg -= *pImgDoubt;

  app.setProgressBar(80);

  // SAVE RESULTS
  // ============

  cout << "Saving results..." << endl;

  PbmFile txtFile((char*) app.getStringOption("-outxt"));
  txtFile.write(*pImgSep);

  PbmFile graphxFile((char*) app.getStringOption("-outg"));
  graphxFile.write(sourceImg);

  PbmFile undetFile((char*) app.getStringOption("-outu"));
  undetFile.write(*pImgDoubt);

  app.setProgressBar(100);

  // DISPLAY RESULT
  // ==============

  app.closeProgressBar();
  cout << "Text-graphics separation done." << endl;

  app.showPicture((char*) app.getStringOption("-outxt"));
  app.showPicture((char*) app.getStringOption("-outg"));
  app.showPicture((char*) app.getStringOption("-outu"));

  // NORMAL TERMINATION
  // ==================

  return app._CODE_END;

} // END main

// -------------------------------------------------------------------
// -------------------------------------------------------------------
