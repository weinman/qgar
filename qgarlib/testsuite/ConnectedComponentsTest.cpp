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
 * @file  ConnectedComponentsTest.cpp
 * @brief Implementation of class ConnectedComponentsTest.
 *
 *        See file ConnectedComponentsTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   June 21, 2004  14:55
 * @since  Qgar 2.1.1
 */



// STD
#include <iostream>
// QGAR
#include <qgarlib/BoundingBox.h>
#include <qgarlib/Component.h>
#include <qgarlib/ConnectedComponents.h>
#include <qgarlib/File.h>
#include <qgarlib/GenImage.h>
#include <qgarlib/Maer.h>
#include <qgarlib/PbmFile.h>
#include <qgarlib/PgmFile.h>
#include <qgarlib/primitives.h>
// QGAR TESTS
#include "ConnectedComponentsTest.h"



using namespace qgar;
using namespace std;



// __________________________________________________________________
//
// (I) FORMAT OF THE FILES CONTAINING THE COMPONENTS
//
// Each file named
//   ConnectedComponentsTest.contours_XX.qgar
// contains the connected components of image in file named
//   ConnectedComponentsTest.img_XX.pbm
// __________________________________________________________________
//
// NUMBER_OF_COMPONENTS
//   LABEL                                        |
//   LABEL_OF_COMPRISING_COMPONENT                | repeated
//   COLOR                                        | for
//   X_COORDINATE_OF_TOP_LEFT_PIXEL               | each component
//   Y_COORDINATE_OF_TOP_LEFT_PIXEL               |
//   BOUNDING_BOX                                 |
//   NUMBER_OF_CONTOUR_POINTS                     |
//     point_1                                    |
//     ...                                        |
//     point_N                                    |
//   NUMBER_OF_MAER_CORNERS (4)                   |
//     maer_corner_1                              |
//     maer_corner_2                              |
//     maer_corner_3                              |
//     maer_corner_4                              |
//   MAER_AREA                                    |
//   AREA                                         |
//   DENSITY                                      |
//   PERIMETER IN PIXELS                          |
//   PERIMETER IN POINTS                          |
// __________________________________________________________________




// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// L O C A L   A U X I L I A R I E S
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace
{


// =======
// S A V E
// =======



// WRITE A LIST OF POINT ON THE GIVEN FILE STREAM

template <class T>
void
CCTEST_savePointList(std::fstream& aFileStream,
		     const std::list<T>& aPtList)
{
  // NUMBER OF POINTS
  aFileStream << aPtList.size() << endl;

  // POINTS
  for(typename list<T>::const_iterator itPL = aPtList.begin();
      itPL != aPtList.end();
      ++itPL)
    {
      aFileStream << *itPL << endl;
    }
}



// SAVE CONNECTED COMPONENTS IN A GIVEN FILE
// ACCORDING TO FORMAT (I)
// aFileImg: name of a file containing a PBM image
//           to compute connected components
// aFileCC : name of the file to save the components

void
CCTEST_saveComponents(const char* aFileImg, const char* aFileCC)
{
  // Make a binary image from a PBM image file
  PbmFile pbmFile(aFileImg);
  BinaryImage binImg = pbmFile.read();

//////////////////////////////////////////////////////////////////////////////
  cout << "TTT> FICHIER " << aFileImg << " LU" << endl;
//////////////////////////////////////////////////////////////////////////////

  // Connected components
  ConnectedComponents components(binImg);

//////////////////////////////////////////////////////////////////////////////
  cout << "TTT> COMPOSANTES CONNEXES CONSTRUITES" << endl;
//////////////////////////////////////////////////////////////////////////////

  // Open file to store the components
  File fileCC(aFileCC);
  fileCC.openWONLY();
  std::fstream& fs = fileCC.fstream();

//////////////////////////////////////////////////////////////////////////////
  cout << "TTT> FICHIER " << aFileCC << " OUVERT" << endl;
//////////////////////////////////////////////////////////////////////////////

  // NUMBER OF COMPONENTS
  fs << components.componentCnt() << endl;

  // For each component
  for (int iCnt = 0 ; iCnt < components.componentCnt() ; ++iCnt)
    {
//////////////////////////////////////////////////////////////////////////////
      cout << "TTTTTTT> COMPOSANTE No " << iCnt << endl;
//////////////////////////////////////////////////////////////////////////////
      Component& cc = components[iCnt];

      // LABELaFileStream
      fs << cc.label() << endl;
      // LABEL OF COMPRISING COMPONENT
      fs << cc.inLabel() << endl;
      // COLOR
      fs << cc.color() << endl;
      // X COORDINATE OF TOP LEFT PIXEL
      fs << cc.xTopLeftPix() << endl;
      // Y COORDINATE OF TOP LEFT PIXEL
      fs << cc.yTopLeftPix() << endl;
      // BOUNDING BOX
      fs << cc.accessBoundingBox() << endl;
      // CONTOUR POINTS
      CCTEST_savePointList(fs, cc.accessContour());
//////////////////////////////////////////////////////////////////////////////
  cout << "TTT> Contours finis" << endl;
//////////////////////////////////////////////////////////////////////////////
      // MAER CORNERS
      const Maer& maer = cc.accessMaer();
//////////////////////////////////////////////////////////////////////////////
  cout << "TTT> Acces Maer fini" << endl;
//////////////////////////////////////////////////////////////////////////////
      CCTEST_savePointList(fs, maer.accessVertices());
//////////////////////////////////////////////////////////////////////////////
  cout << "TTT> Sommets Maer finis" << endl;
//////////////////////////////////////////////////////////////////////////////
      // MAER AREA
      fs << maer.areaPx() << endl;
      // AREA
      fs << cc.areaPx() << endl;
      // DENSITY
      fs << cc.densityBox() << endl;
      // PERIMETER IN PIXELS
      fs << cc.perimeterPx() << endl;
      // PERIMETER IN POINTS
      fs << cc.perimeterPt() << endl;
    } // END for iCnt

//////////////////////////////////////////////////////////////////////////////
  cout << "TTT> Sortie de boucle..." << endl;
//////////////////////////////////////////////////////////////////////////////

  fileCC.close();
//////////////////////////////////////////////////////////////////////////////
  cout << "TTT> FICHIER " << aFileCC << " FERME" << endl;
//////////////////////////////////////////////////////////////////////////////
}



// // =========
// // C H E C K
// // =========



// // CHECK THAT integer POINTS OF LIST aPtList
// // ARE THE SAME AS THOSE STORED IN A GIVEN FILE
// // ACCORDING TO THE FOLLOWING FORMAT:
// //
// // NUMBER_OF_POINTS
// //   point_1
// //   ...
// //   point_N

// void
// CCTEST_checkIPointList(fstream& aFileStream,
// 		       const list< GenPoint<int> >& aPtList)
// {

//   // Number of points
//   int ptCnt;
//   aFileStream >> ptCnt;

//   // CHECK NUMBER OF POINTS
//   // ----------------------
//   CPPUNIT_ASSERT_EQUAL( ptCnt, (int) aPtList.size() );  

//   // CHECK EACH POINT
//   // ----------------
//   list< GenPoint<int> >::const_iterator itPL = aPtList.begin();

//   for(int iCnt = 0 ; iCnt < ptCnt ; ++iCnt, ++itPL)
//     {
//       IPoint pt;
//       aFileStream >> pt;

//       CPPUNIT_ASSERT_EQUAL( pt.x(), (*itPL).x() );
//       CPPUNIT_ASSERT_EQUAL( pt.y(), (*itPL).y() );
//     }

// } // END CCTEST_checkIPointList



// // CHECK THAT double POINTS OF LIST aPtList
// // ARE THE SAME AS THOSE STORED IN A GIVEN FILE
// // ACCORDING TO THE FOLLOWING FORMAT:
// //
// // NUMBER_OF_POINTS
// //   point_1
// //   ...
// //   point_N

// void
// CCTEST_checkDPointList(fstream& aFileStream,
// 		       const list< GenPoint<double> >& aPtList)
// {

//   // Number of points
//   int ptCnt;
//   aFileStream >> ptCnt;

//   // CHECK NUMBER OF POINTS
//   // ----------------------
//   CPPUNIT_ASSERT_EQUAL( ptCnt, (int) aPtList.size() );  

//   // CHECK EACH POINT
//   // ----------------
//   list< GenPoint<double> >::const_iterator itPL = aPtList.begin();

//   for(int iCnt = 0 ; iCnt < ptCnt ; ++iCnt, ++itPL)
//     {
//       DPoint pt;
//       aFileStream >> pt;

//       CPPUNIT_ASSERT_DOUBLES_EQUAL( pt.x(), (*itPL).x(), 0.001 );
//       CPPUNIT_ASSERT_DOUBLES_EQUAL( pt.y(), (*itPL).y(), 0.001 );
//     }

// } // END CCTEST_checkDPointList



// // CHECK CONNECTED COMPONENTS IN A GIVEN FILE
// // (STORED ACCORDING TO FORMAT (I))
// // aFileImg: name of a file containing a PBM image
// //           to compute connected components
// // aFileCC : name of the file containing the corresponding components

// void
// CCTEST_checkComponents(const char* aFileImg, const char* aFileCC)
// {

//   // A trace to identify the concerned file in case of test failure
//   cout << endl
//        << "TESTING> Connected components"
//        << endl
//        << "         Files " << aFileImg << "  &  " << aFileCC
//        << endl;

//   // Make a binary image from the given PBM image file
//   PbmFile pbmFile(aFileImg);
//   BinaryImage binImg = pbmFile.read();

//   // Connected components
//   ConnectedComponents components(binImg);

//   // Open file of components
//   File fileCC(aFileCC);
//   fileCC.openRONLY();
//   std::fstream& fs = fileCC.fstream();

//   // CHECK NUMBER OF COMPONENTS
//   // --------------------------
//   int ccCnt;
//   fs >> ccCnt;
//   CPPUNIT_ASSERT_EQUAL( ccCnt, components.componentCnt() );  

//   // For each component
//   for (int iCnt = 0 ; iCnt < ccCnt ; ++iCnt)
//     {
//       Component& cc = components[iCnt];

//       // CHECK LABEL
//       // -----------
//       int l;
//       fs >> l;
//       CPPUNIT_ASSERT_EQUAL( l, (int) cc.label() );

//       // CHECK LABEL OF COMPRISING COMPONENT
//       // -----------------------------------
//       int inl;
//       fs >> inl;
//       CPPUNIT_ASSERT_EQUAL( inl, (int) cc.inLabel() );

//       // CHECK COLOR
//       // -----------
//       int color;
//       fs >> color;
//       CPPUNIT_ASSERT_EQUAL( color, (int) cc.color() );

//       // CHECK X COORDINATE OF TOP LEFT PIXEL
//       // ------------------------------------
//       int xTop;
//       fs >> xTop;
//       CPPUNIT_ASSERT_EQUAL( xTop, cc.xTopLeftPix() );

//       // CHECK Y COORDINATE OF TOP LEFT PIXEL
//       // ------------------------------------
//       int yTop;
//       fs >> yTop;
//       CPPUNIT_ASSERT_EQUAL( yTop, cc.yTopLeftPix() );

//       // CHECK BOUNDING BOX
//       // ------------------
//       const BoundingBox& bb = cc.accessBoundingBox();
//       BoundingBox b;
//       fs >> b;
//       CPPUNIT_ASSERT_EQUAL( b.xTopLeft(), bb.xTopLeft() );
//       CPPUNIT_ASSERT_EQUAL( b.yTopLeft(), bb.yTopLeft() );
//       CPPUNIT_ASSERT_EQUAL( b.xBottomRight(), bb.xBottomRight() );
//       CPPUNIT_ASSERT_EQUAL( b.yBottomRight(), bb.yBottomRight() );

//       // CHECK MAER CORNERS
//       // ------------------
//       const Maer& maer = cc.accessMaer();
//       CCTEST_checkDPointList(fs, maer.accessVertices());

//       // CHECK MAER AREA
//       // ---------------
//       double mArea;
//       fs >> mArea;
//       CPPUNIT_ASSERT_DOUBLES_EQUAL( mArea, maer.areaPx(), 0.001 );

//       // CHECK AREA
//       // ----------
//       int area;
//       fs >> area;
//       CPPUNIT_ASSERT_EQUAL( area, cc.areaPx() );

//       // CHECK DENSITY
//       // -------------
//       double density;
//       fs >> density;
//       CPPUNIT_ASSERT_DOUBLES_EQUAL( density, cc.densityBox(), 0.001);

//       // CHECK PERIMETER IN PIXELS
//       // -------------------------
//       double ppx;
//       fs >> ppx;
//       CPPUNIT_ASSERT_DOUBLES_EQUAL( ppx, cc.perimeterPx(), 0.001 );

//       // CHECK PERIMETER IN PIXELS
//       // -------------------------
//       double ppt;
//       fs >> ppt;
//       CPPUNIT_ASSERT_DOUBLES_EQUAL( ppt, cc.perimeterPt(), 0.001 );

//       // CHECK CONTOUR POINTS
//       // --------------------
//       CCTEST_checkIPointList(fs, cc.accessContour());
//     } // END for iCnt

//   // Close file of components
//   fileCC.close();

// } // END CCTEST_checkComponents



} // unnamed namespace
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++




// ------------------------------------------------------------------
// T E S T F I X T U R E   I M P L
// ------------------------------------------------------------------

void
ConnectedComponentsTest::setUp()
{
  /* EMPTY */
}

// -------------------------------------------------------------------

void
ConnectedComponentsTest::tearDown()
{
  /* EMPTY */
}


// -------------------------------------------------------------------
// CONSTRUCTION OF THE FILES CONTAINING THE COMPONENTS
// -------------------------------------------------------------------

void
ConnectedComponentsTest::testConnectedComponentsTest()
{
  // CONSTRUCTION OF THE FILES CONTAINING THE COMPONENTS

  CCTEST_saveComponents("ConnectedComponentsTest.img_00.pbm",
			"ConnectedComponentsTest.contours_00.qgar");
  CCTEST_saveComponents("ConnectedComponentsTest.img_01.pbm",
			"ConnectedComponentsTest.contours_01.qgar");
  CCTEST_saveComponents("ConnectedComponentsTest.img_02.pbm",
			"ConnectedComponentsTest.contours_02.qgar");
  CCTEST_saveComponents("ConnectedComponentsTest.img_03.pbm",
			"ConnectedComponentsTest.contours_03.qgar");
  CCTEST_saveComponents("ConnectedComponentsTest.img_04.pbm",
			"ConnectedComponentsTest.contours_04.qgar");
  CCTEST_saveComponents("ConnectedComponentsTest.img_05.pbm",
			"ConnectedComponentsTest.contours_05.qgar");
  CCTEST_saveComponents("ConnectedComponentsTest.img_06.pbm",
			"ConnectedComponentsTest.contours_06.qgar");
  CCTEST_saveComponents("ConnectedComponentsTest.img_07.pbm",
			"ConnectedComponentsTest.contours_07.qgar");
  CCTEST_saveComponents("ConnectedComponentsTest.img_08.pbm",
			"ConnectedComponentsTest.contours_08.qgar");
  CCTEST_saveComponents("ConnectedComponentsTest.img_09.pbm",
			"ConnectedComponentsTest.contours_09.qgar");
  CCTEST_saveComponents("ConnectedComponentsTest.img_10.pbm",
			"ConnectedComponentsTest.contours_10.qgar");
}

// ----------------------------------------------------------------------
// TESTS WITH IMAGES ConnectedComponentsTest.img_*.pbm
// ----------------------------------------------------------------------

// void
// ConnectedComponentsTest::testConnectedComponentsTest()
// {
//    CCTEST_checkComponents("ConnectedComponentsTest.img_00.pbm",
// 			  "ConnectedComponentsTest.contours_00.qgar");
//    CCTEST_checkComponents("ConnectedComponentsTest.img_01.pbm",
// 			  "ConnectedComponentsTest.contours_01.qgar");
//    CCTEST_checkComponents("ConnectedComponentsTest.img_02.pbm",
// 			  "ConnectedComponentsTest.contours_02.qgar");
//    CCTEST_checkComponents("ConnectedComponentsTest.img_03.pbm",
// 			  "ConnectedComponentsTest.contours_03.qgar");
//    CCTEST_checkComponents("ConnectedComponentsTest.img_04.pbm",
// 			  "ConnectedComponentsTest.contours_04.qgar");
//    CCTEST_checkComponents("ConnectedComponentsTest.img_05.pbm",
// 			  "ConnectedComponentsTest.contours_05.qgar");
//    CCTEST_checkComponents("ConnectedComponentsTest.img_06.pbm",
// 			  "ConnectedComponentsTest.contours_06.qgar");
//    CCTEST_checkComponents("ConnectedComponentsTest.img_07.pbm",
// 			  "ConnectedComponentsTest.contours_07.qgar");
//    CCTEST_checkComponents("ConnectedComponentsTest.img_08.pbm",
// 			  "ConnectedComponentsTest.contours_08.qgar");
//    CCTEST_checkComponents("ConnectedComponentsTest.img_09.pbm",
// 			  "ConnectedComponentsTest.contours_09.qgar");
//    CCTEST_checkComponents("ConnectedComponentsTest.img_10.pbm",
// 			  "ConnectedComponentsTest.contours_10.qgar");
// }

// ----------------------------------------------------------------------

