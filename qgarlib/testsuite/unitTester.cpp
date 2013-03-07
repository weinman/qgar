/*---------------------------------------------------------------------*
 | Library QgarLib, graphics analysis and recognition                  |
 | Copyright (C) 2003  Qgar Project, LORIA                             |
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


#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


// // CHAINS OF POINTS
// //
#include "FreemanChainTest.h"
#include "FreemanCodeTest.h"
#include "GenPointChainTest.h"
// //
// // CONVEX HULLS
// //
#include "GenConvexHullTest.h"
// //
// // CONVOLUTIONS
// //
#include "GenConvolImageTest.h"
// //
// // GEOMETRICAL PRIMITIVES
// //
#include "AbstractGenPrimitiveTest.h"
#include "BoundingBoxTest.h"
#include "GenArcTest.h"
// //
#include "GenPointTest.h"
// //
#include "GenPolygonTest.h"
#include "GenPolylineTest.h"
#include "GenSegmentTest.h"
// //
// // HISTOGRAMS
// //
#include "HistogramTest.h"
// //
// // IMAGES
// //
#include "GenImageTest.h"
// //
// // KMEANS
// //
#include "GenKMeansTest.h"
// //
// // MASKS
// //
#include "GenMask1dTest.h"
#include "GenMask2dTest.h"
// //
// // Qgar GEOMETRICAL PRIMITIVES
// //
#include "AbstractGenQgarPrimitiveTest.h"
#include "GenQgarArcTest.h"
#include "GenQgarPolygonTest.h"
#include "GenQgarPolylineTest.h"
#include "GenQgarSegmentTest.h"
// //
// // TREES
// //
#include "GenTreeTest.h"
// //
// // GRAPHS
// //
#include "GenEdgeGenNodeTest.h"
#include "GenUGraphTest.h"
// //
// // GLOBAL FUNCTIONS
// //
#include "GlobalFunctionsTest.h"
//
// CONNECTED COMPONENTS
//
#include "ConnectedComponentsTest.h"


// -------------------------------------------------------------------
// R E G I S T E R   T E S T S
// -------------------------------------------------------------------

// // Tests GEOMETRICAL PRIMITIVES.
// // The order of the tests tries to reflect the dependency
// // between the primitives
// //
CPPUNIT_TEST_SUITE_REGISTRATION( AbstractGenPrimitiveTest );
// //
CPPUNIT_TEST_SUITE_REGISTRATION( GenPointTest );
// //
CPPUNIT_TEST_SUITE_REGISTRATION( BoundingBoxTest );
CPPUNIT_TEST_SUITE_REGISTRATION( GenSegmentTest );
CPPUNIT_TEST_SUITE_REGISTRATION( GenArcTest );
CPPUNIT_TEST_SUITE_REGISTRATION( GenPolylineTest );
CPPUNIT_TEST_SUITE_REGISTRATION( GenPolygonTest );
// //
// //
// // Tests QGAR GEOMETRICAL PRIMITIVES
// // The order of the tests tries to reflect the dependency
// // between the primitives
// //
CPPUNIT_TEST_SUITE_REGISTRATION( AbstractGenQgarPrimitiveTest );
CPPUNIT_TEST_SUITE_REGISTRATION( GenQgarSegmentTest );
CPPUNIT_TEST_SUITE_REGISTRATION( GenQgarArcTest );
CPPUNIT_TEST_SUITE_REGISTRATION( GenQgarPolylineTest );
CPPUNIT_TEST_SUITE_REGISTRATION( GenQgarPolygonTest );
// //
// //
// // Tests the template IMAGE representation
// //
CPPUNIT_TEST_SUITE_REGISTRATION( GenImageTest );
// //
// //
// // Tests HISTOGRAMS
// //
CPPUNIT_TEST_SUITE_REGISTRATION( HistogramTest );
// //
// //
// // Tests MASKS
// //
CPPUNIT_TEST_SUITE_REGISTRATION( GenMask1dTest );
CPPUNIT_TEST_SUITE_REGISTRATION( GenMask2dTest );
// //
// //
// // Tests CHAINS OF POINTS
// //
CPPUNIT_TEST_SUITE_REGISTRATION( GenPointChainTest );
CPPUNIT_TEST_SUITE_REGISTRATION( FreemanCodeTest );
CPPUNIT_TEST_SUITE_REGISTRATION( FreemanChainTest );
// //
// //
// // Tests TREES and TREE NODES
// //
CPPUNIT_TEST_SUITE_REGISTRATION( GenTreeTest );
// //
// //
// // Tests GRAPHS, GRAPH EDGES and NODES
// //
//CPPUNIT_TEST_SUITE_REGISTRATION( GenEdgeGenNodeTest );
CPPUNIT_TEST_SUITE_REGISTRATION( GenUGraphTest );
// //
// //
// // Tests CONVEX HULL
// //
CPPUNIT_TEST_SUITE_REGISTRATION( GenConvexHullTest );
// //
// //
// // Tests CONVOLUTIONS
// //
CPPUNIT_TEST_SUITE_REGISTRATION( GenConvolImageTest );
// //
// //
// // Tests K-MEANS algorithm
// //
CPPUNIT_TEST_SUITE_REGISTRATION( GenKMeansTest );
// //
// //
// // Tests GLOBAL FUNCTIONS
// //
CPPUNIT_TEST_SUITE_REGISTRATION( GlobalFunctionsTest );
//
//
// Tests CONNECTED COMPONENTS
//
CPPUNIT_TEST_SUITE_REGISTRATION( ConnectedComponentsTest );



// -------------------------------------------------------------------
// R U N   T E S T S
// -------------------------------------------------------------------

int main(int argc, char* argv[])
{
  // Get the top level suite from the registry
  CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

  // Adds the test to the list of test to run
  CppUnit::TextUi::TestRunner runner;
  runner.addTest( suite );

  // Change the default outputter to a compiler error format outputter
  runner.setOutputter( new CppUnit::CompilerOutputter( &runner.result(),
						       std::cerr ) );
  // Run the tests.
  bool wasSucessful = runner.run();

  // Return error code 1 if the one of test failed.
  return wasSucessful ? 0 : 1;
}
