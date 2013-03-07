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
 * @file  BoundingBoxTest.cpp
 * @brief Implementation of class BoundingBoxTest
 *
 *        See file BoundingBoxTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   February 19, 2004  17:17
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: BoundingBoxTest.cpp,v 1.8 2005/10/14 17:06:36 masini Exp $ */



// QGAR
#include <qgarlib/primitives.h>
//////////////////////////////////////////////////////////////////////////////
#include<iostream>
using namespace std;
//////////////////////////////////////////////////////////////////////////////
// QGAR TESTS
#include "BoundingBoxTest.h"




using namespace qgar;



// ------------------------------------------------------------------
// T E S T    F I X T U R E   I M P L E M E N T A T I O N
// ------------------------------------------------------------------


void
BoundingBoxTest::setUp()
{
  // Int values
  _ix0 = 14;
  _iy0 = 11;
  _ix1 = 137;
  _iy1 = 212;

  _iTopLeft     = IPoint(_ix0, _iy0);
  _iTopRight    = IPoint(_ix1, _iy0);
  _iBottomLeft  = IPoint(_ix0, _iy1);
  _iBottomRight = IPoint(_ix1, _iy1);
  
  _iBox = BoundingBox(_iTopLeft, _iBottomRight);
}


void
BoundingBoxTest::tearDown()
{
  /* EMPTY */
}


// -------------------------------------------------------------------
// C O N S T R U C T O R S 
// -------------------------------------------------------------------

void
BoundingBoxTest::testDefaultConstructor()
{
  // -------
  // Process
  // -------

  BoundingBox iBox;

  // -----
  // Check
  // -----

  // All coordinates are initialized to 0
  CPPUNIT_ASSERT_EQUAL(0, iBox.xTopLeft());
  CPPUNIT_ASSERT_EQUAL(0, iBox.yTopLeft());
  CPPUNIT_ASSERT_EQUAL(0, iBox.xBottomRight());
  CPPUNIT_ASSERT_EQUAL(0, iBox.yBottomRight());
}


void
BoundingBoxTest::testBuildFromTwoPoints()
{
  // -------
  // Process
  // -------

  BoundingBox bb1(_iTopLeft,     _iBottomRight);
  BoundingBox bb2(_iBottomRight, _iTopLeft);
  BoundingBox bb3(_iTopRight,    _iBottomLeft);
  BoundingBox bb4(_iBottomLeft,  _iTopRight);

  // -----
  // Check
  // -----

  // Top left and bottom right points are correctly assigned
  CPPUNIT_ASSERT_EQUAL( bb1.xTopLeft(),     _ix0 );
  CPPUNIT_ASSERT_EQUAL( bb1.yTopLeft(),     _iy0 );
  CPPUNIT_ASSERT_EQUAL( bb1.xBottomRight(), _ix1 );
  CPPUNIT_ASSERT_EQUAL( bb1.yBottomRight(), _iy1 );

  CPPUNIT_ASSERT_EQUAL( bb2.xTopLeft(),     _ix0 );
  CPPUNIT_ASSERT_EQUAL( bb2.yTopLeft(),     _iy0 );
  CPPUNIT_ASSERT_EQUAL( bb2.xBottomRight(), _ix1 );
  CPPUNIT_ASSERT_EQUAL( bb2.yBottomRight(), _iy1 );

  CPPUNIT_ASSERT_EQUAL( bb3.xTopLeft(),     _ix0 );
  CPPUNIT_ASSERT_EQUAL( bb3.yTopLeft(),     _iy0 );
  CPPUNIT_ASSERT_EQUAL( bb3.xBottomRight(), _ix1 );
  CPPUNIT_ASSERT_EQUAL( bb3.yBottomRight(), _iy1 );

  CPPUNIT_ASSERT_EQUAL( bb4.xTopLeft(),     _ix0 );
  CPPUNIT_ASSERT_EQUAL( bb4.yTopLeft(),     _iy0 );
  CPPUNIT_ASSERT_EQUAL( bb4.xBottomRight(), _ix1 );
  CPPUNIT_ASSERT_EQUAL( bb4.yBottomRight(), _iy1 );
}


void
BoundingBoxTest::testBuildFrom4Coords()
{
  // -------
  // Process
  // -------

  BoundingBox bb1(_ix1, _iy1, _ix0, _iy0);
  BoundingBox bb2(_ix0, _iy0, _ix1, _iy1);
  BoundingBox bb3(_ix1, _iy0, _ix0, _iy1);
  BoundingBox bb4(_ix0, _iy1, _ix1, _iy0);

  // -----
  // Check
  // -----

  // Ensure that x and y coordinate for top left and bottom right
  // points are correctly assigned
  CPPUNIT_ASSERT_EQUAL( bb1.xTopLeft(),     _ix0 );
  CPPUNIT_ASSERT_EQUAL( bb1.yTopLeft(),     _iy0 );
  CPPUNIT_ASSERT_EQUAL( bb1.xBottomRight(), _ix1 );
  CPPUNIT_ASSERT_EQUAL( bb1.yBottomRight(), _iy1 );

  CPPUNIT_ASSERT_EQUAL( bb2.xTopLeft(),     _ix0 );
  CPPUNIT_ASSERT_EQUAL( bb2.yTopLeft(),     _iy0 );
  CPPUNIT_ASSERT_EQUAL( bb2.xBottomRight(), _ix1 );
  CPPUNIT_ASSERT_EQUAL( bb2.yBottomRight(), _iy1 );

  CPPUNIT_ASSERT_EQUAL( bb3.xTopLeft(),     _ix0 );
  CPPUNIT_ASSERT_EQUAL( bb3.yTopLeft(),     _iy0 );
  CPPUNIT_ASSERT_EQUAL( bb3.xBottomRight(), _ix1 );
  CPPUNIT_ASSERT_EQUAL( bb3.yBottomRight(), _iy1 );

  CPPUNIT_ASSERT_EQUAL( bb4.xTopLeft(),     _ix0 );
  CPPUNIT_ASSERT_EQUAL( bb4.yTopLeft(),     _iy0 );
  CPPUNIT_ASSERT_EQUAL( bb4.xBottomRight(), _ix1 );
  CPPUNIT_ASSERT_EQUAL( bb4.yBottomRight(), _iy1 );
}


void
BoundingBoxTest::testBuildFromTopLeftWidthAndHeight()
{
  // ------
  // Set Up
  // ------

  int iWd = 134;
  int iHt = 2;

  // -------
  // Process
  // -------

  BoundingBox iBox(_iTopLeft, iWd, iHt);

  // -----
  // Check
  // -----

  // Ensure that top left point is correctly assigned
  CPPUNIT_ASSERT_EQUAL( _iTopLeft, iBox.topLeft() );

  // Ensure that bottom right point is correctly assigned
  CPPUNIT_ASSERT_EQUAL( iBox.xBottomRight(), iBox.xTopLeft() + iWd - 1 );
  CPPUNIT_ASSERT_EQUAL( iBox.yBottomRight(), iBox.yTopLeft() + iHt - 1 );

  // Ensure that width is correct
  CPPUNIT_ASSERT_EQUAL( iWd, iBox.width() );

  // Ensure that height is correct
  CPPUNIT_ASSERT_EQUAL( iHt, iBox.height() );
}


void
BoundingBoxTest::testBuildFromTopLeftWidthAndHeightBadWidth()
{
  // ------
  // Set Up
  // ------

  int iWd = -1; // Bad value
  int iHt = 2;

  // -------
  // Process
  // -------

  BoundingBox iBox(_iTopLeft, iWd, iHt);
}


void
BoundingBoxTest::testBuildFromTopLeftWidthAndHeightBadHeight()
{
  // ------
  // Set Up
  // ------

  int iWd = 2; 
  int iHt = 0; // Bad value

  // -------
  // Process
  // -------

  BoundingBox iBox(_iTopLeft, iWd, iHt);
}


void
BoundingBoxTest::testBuildFromWidthHeightAndBottomRight()
{
  // ------
  // Set Up
  // ------

  int iWd = 134;
  int iHt = 2;

  // -------
  // Process
  // -------

  BoundingBox iBox(iWd, iHt, _iBottomRight);

  // -----
  // Check
  // -----

  // Ensure that bottom right point is correctly assigned
  CPPUNIT_ASSERT_EQUAL( _iBottomRight, iBox.bottomRight() );

  // Ensure that top left point is correctly assigned
  CPPUNIT_ASSERT_EQUAL( iBox.xTopLeft(), iBox.xBottomRight() - iWd + 1 );
  CPPUNIT_ASSERT_EQUAL( iBox.yTopLeft(), iBox.yBottomRight() - iHt + 1 );

  // Ensure that width is correct
  CPPUNIT_ASSERT_EQUAL( iWd, iBox.width() );

  // Ensure that height is correct
  CPPUNIT_ASSERT_EQUAL( iHt, iBox.height() );
}


void
BoundingBoxTest::testBuildFromWidthHeightAndBottomRightBadWidth()
{
  // ------
  // Set Up
  // ------

  int iWd = 0; // Bad value
  int iHt = 2; 

  // -------
  // Process
  // -------

  BoundingBox iBox(iWd, iHt, _iBottomRight);
}


void
BoundingBoxTest::testBuildFromWidthHeightAndBottomRightBadHeight()
{
  // ------
  // Set Up
  // ------

  int iWd = 14;
  int iHt = -9834; // Bad value

  // -------
  // Process
  // -------

  BoundingBox iBox(iWd, iHt, _iBottomRight);
}


void
BoundingBoxTest::testCopyConstructor()
{  
  // -------
  // Process
  // -------

  BoundingBox iDupBox(_iBox);

  // -----
  // Check
  // -----

  // Ensure that top left points and the bottom points
  // of both bounding boxes are the same
  CPPUNIT_ASSERT_EQUAL( _iBox.topLeft(),     iDupBox.topLeft() );
  CPPUNIT_ASSERT_EQUAL( _iBox.bottomRight(), iDupBox.bottomRight() );
}


// -------------------------------------------------------------------
//  A C C E S S   T O   C O R N E R S
// -------------------------------------------------------------------


void
BoundingBoxTest::testAccessCorners()
{
  // -----
  // Check
  // -----

  // Access to top left point
  CPPUNIT_ASSERT_EQUAL( _iBox.accessTopLeft(), _iTopLeft );
  CPPUNIT_ASSERT_EQUAL( _iBox.topLeft(),       _iTopLeft );

  // Access to coordinates of top left point
  CPPUNIT_ASSERT_EQUAL( _iBox.xTopLeft(), _ix0 );
  CPPUNIT_ASSERT_EQUAL( _iBox.yTopLeft(), _iy0 );

  // Access to bottom right point
  CPPUNIT_ASSERT_EQUAL( _iBox.accessBottomRight(), _iBottomRight );
  CPPUNIT_ASSERT_EQUAL( _iBox.bottomRight(),       _iBottomRight );

  // Access to coordinates of bottom right point
  CPPUNIT_ASSERT_EQUAL( _iBox.xBottomRight(), _ix1 );
  CPPUNIT_ASSERT_EQUAL( _iBox.yBottomRight(), _iy1 );
}


// -------------------------------------------------------------------
//  A C C E S S   T O   D I M E N S I O N S
// -------------------------------------------------------------------


void
BoundingBoxTest::testLength()
{
  // -------
  // Process
  // -------

  // Compute box length from corner coordinates.
  int length = _iBox.xBottomRight() - _iBox.xTopLeft() + 1;

  // -----
  // Check
  // -----
  
  CPPUNIT_ASSERT_EQUAL(length, _iBox.length() );
}


void
BoundingBoxTest::testWidth()
{
  // -------
  // Process
  // -------

  // Compute box width from corner coordinates.
  int width = _iBox.xBottomRight() - _iBox.xTopLeft() + 1;

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL(width, _iBox.width() );  
}


void
BoundingBoxTest::testHeight()
{
  // -------
  // Process
  // -------

  // Compute box width from corner coordinates.
  int height = _iBox.yBottomRight() - _iBox.yTopLeft() + 1;

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL(height, _iBox.height() );    
}


void
BoundingBoxTest::testArea()
{
  // -------
  // Process
  // -------

  // Compute box area from corner coordinates
  int area =   (_iBox.xBottomRight() - _iBox.xTopLeft() + 1)
	     * (_iBox.yBottomRight() - _iBox.yTopLeft() + 1);
  
  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( area, _iBox.area() );
}


// -------------------------------------------------------------------
// S E T   C O R N E R S
// -------------------------------------------------------------------


void
BoundingBoxTest::testSetTopLeft()
{
  // SET, USING A POINT
  // ------------------

  IPoint pt(1, 4);
  _iBox.setTopLeft(pt);

  // Ensure that top left corner is correctly assigned
  CPPUNIT_ASSERT_EQUAL( pt, _iBox.topLeft() );

  // Ensure that bottom right corner is unchanged
  CPPUNIT_ASSERT_EQUAL( _iBottomRight, _iBox.accessBottomRight() );

  // SET, USING 2 COORDINATES
  // ------------------------

  _iBox.setTopLeft(-4, -7);

  // Ensure that top left corner is correctly assigned
  CPPUNIT_ASSERT_EQUAL( -4, _iBox.xTopLeft() );
  CPPUNIT_ASSERT_EQUAL( -7, _iBox.yTopLeft() );

  // Ensure that bottom right corner is unchanged
  CPPUNIT_ASSERT_EQUAL( _iBottomRight, _iBox.accessBottomRight() );
}


void
BoundingBoxTest::testSetTopLeftExc()
{
  // ------
  // Set Up
  // ------

  BoundingBox box(1, 2, 30, 35);
  IPoint newTopLeft(40, 14);      // Bad value

  // -------
  // Process
  // -------

  _iBox.setBottomRight(newTopLeft);
}


void
BoundingBoxTest::testSetBottomRight()
{
  // SET USING A POINT
  // -----------------

  IPoint pt(435, 664);
  _iBox.setBottomRight(pt);

  // Ensure that bottom right is correctly assigned.
  CPPUNIT_ASSERT_EQUAL( pt, _iBox.bottomRight() );

  // Ensure that top left corner is unchanged
  CPPUNIT_ASSERT_EQUAL( _iTopLeft, _iBox.accessTopLeft() );

  // SET USING 2 COORDINATES
  // -----------------------

  _iBox.setBottomRight(1011, 980654);

  // Ensure that top left corner is correctly assigned
  CPPUNIT_ASSERT_EQUAL( 1011,   _iBox.xBottomRight() );
  CPPUNIT_ASSERT_EQUAL( 980654, _iBox.yBottomRight() );

  // Ensure that top left corner is unchanged
  CPPUNIT_ASSERT_EQUAL( _iTopLeft, _iBox.accessTopLeft() );
}


void
BoundingBoxTest::testSetBottomRightExc()
{
  // ------
  // Set Up
  // ------

  BoundingBox box(20, 20, 30, 30);
  IPoint newBottomRight(5, 2);      // Bad value

  // -------
  // Process
  // -------

  _iBox.setBottomRight(newBottomRight);
}


void
BoundingBoxTest::testSetCornersFrom2Points()
{
  // ------
  // Set Up
  // ------

  IPoint topLeft0(5, 1);
  IPoint bottomRight0(563, 490);

  IPoint topLeft1(50, 10);
  IPoint bottomRight1(5630, 4900);

  BoundingBox box0;
  BoundingBox box1;

  // -------
  // Process
  // -------

  box0.setCorners(topLeft0, bottomRight0);
  box1.setCorners(bottomRight1, topLeft1);

  // -----
  // Check
  // -----

  // Ensure that top left corners are correcly assigned
  CPPUNIT_ASSERT_EQUAL( topLeft0, box0.topLeft()       );
  CPPUNIT_ASSERT_EQUAL( topLeft1, box1.accessTopLeft() );
  
  // Ensure that bottom right corner is correctly assigned
  CPPUNIT_ASSERT_EQUAL( bottomRight0, box0.accessBottomRight() );
  CPPUNIT_ASSERT_EQUAL( bottomRight1, box1.bottomRight()       );
}


void
BoundingBoxTest::testSetCornersFrom4Coords()
{
  // ------
  // Set Up
  // ------

  //     0     2                9
  //      +----+----------------+-------> X
  //      |    |                |
  //      |    |(x1,y1)         |
  //    1 +----o----------------+ (x4,y4)
  //      |    |////////////////|
  //      |    |////////////////|
  //      |    |////////////////|
  //   10 +----+----------------o
  //      | (x3,y3)          (x2,y2) 
  //      |   
  //      V
  //      Y

  int x1 = 2;
  int y1 = 1;
  int x2 = 9;
  int y2 = 10;

  int x1N = -2;
  int y1N = -1;
  int x2N = -9;
  int y2N = -10;

  int x3 = 2;
  int y3 = 10;
  int x4 = 9;
  int y4 = 1;

  int x3N = -2;
  int y3N = -10;
  int x4N = -9;
  int y4N = -1;

  BoundingBox bb12;
  BoundingBox bb12N;
  BoundingBox bb21;
  BoundingBox bb21N;

  BoundingBox bb34;
  BoundingBox bb34N;
  BoundingBox bb43;
  BoundingBox bb43N;

  // -------
  // Process
  // -------

  bb12.setCorners(x1, y1, x2, y2);
  bb12N.setCorners(x1N, y1N, x2N, y2N);

  bb21.setCorners(x2, y2, x1, y1);
  bb21N.setCorners(x2N, y2N, x1N, y1N);

  bb34.setCorners(x3, y3, x4, y4);
  bb34N.setCorners(x3N, y3N, x4N, y4N);

  bb43.setCorners(x4, y4, x3, y3);
  bb43N.setCorners(x4N, y4N, x3N, y3N);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( bb12.xTopLeft()    , x1 );
  CPPUNIT_ASSERT_EQUAL( bb12.yTopLeft()    , y1 );
  CPPUNIT_ASSERT_EQUAL( bb12.xBottomRight(), x2 );
  CPPUNIT_ASSERT_EQUAL( bb12.yBottomRight(), y2 );

  CPPUNIT_ASSERT_EQUAL( bb12N.xTopLeft()    , x2N );
  CPPUNIT_ASSERT_EQUAL( bb12N.yTopLeft()    , y2N );
  CPPUNIT_ASSERT_EQUAL( bb12N.xBottomRight(), x1N );
  CPPUNIT_ASSERT_EQUAL( bb12N.yBottomRight(), y1N );

  CPPUNIT_ASSERT_EQUAL( bb21.xTopLeft()    , x1 );
  CPPUNIT_ASSERT_EQUAL( bb21.yTopLeft()    , y1 );
  CPPUNIT_ASSERT_EQUAL( bb21.xBottomRight(), x2 );
  CPPUNIT_ASSERT_EQUAL( bb21.yBottomRight(), y2 );

  CPPUNIT_ASSERT_EQUAL( bb21N.xTopLeft()    , x2N );
  CPPUNIT_ASSERT_EQUAL( bb21N.yTopLeft()    , y2N );
  CPPUNIT_ASSERT_EQUAL( bb21N.xBottomRight(), x1N );
  CPPUNIT_ASSERT_EQUAL( bb21N.yBottomRight(), y1N );

  CPPUNIT_ASSERT_EQUAL( bb34.xTopLeft()    , x1 );
  CPPUNIT_ASSERT_EQUAL( bb34.yTopLeft()    , y1 );
  CPPUNIT_ASSERT_EQUAL( bb34.xBottomRight(), x2 );
  CPPUNIT_ASSERT_EQUAL( bb34.yBottomRight(), y2 );

  CPPUNIT_ASSERT_EQUAL( bb34N.xTopLeft()    , x2N );
  CPPUNIT_ASSERT_EQUAL( bb34N.yTopLeft()    , y2N );
  CPPUNIT_ASSERT_EQUAL( bb34N.xBottomRight(), x1N );
  CPPUNIT_ASSERT_EQUAL( bb34N.yBottomRight(), y1N );

  CPPUNIT_ASSERT_EQUAL( bb43.xTopLeft()    , x1 );
  CPPUNIT_ASSERT_EQUAL( bb43.yTopLeft()    , y1 );
  CPPUNIT_ASSERT_EQUAL( bb43.xBottomRight(), x2 );
  CPPUNIT_ASSERT_EQUAL( bb43.yBottomRight(), y2 );

  CPPUNIT_ASSERT_EQUAL( bb43N.xTopLeft()    , x2N );
  CPPUNIT_ASSERT_EQUAL( bb43N.yTopLeft()    , y2N );
  CPPUNIT_ASSERT_EQUAL( bb43N.xBottomRight(), x1N );
  CPPUNIT_ASSERT_EQUAL( bb43N.yBottomRight(), y1N );
}


// -------------------------------------------------------------------
// G E O M E T R I C A L   P R E D I C A T E S
// -------------------------------------------------------------------


void
BoundingBoxTest::testContainsPoint()
{
  // ------
  // Set Up
  // ------

  BoundingBox box(-10, -2, 100, 45);

  // Points in
  IPoint pIn1(-4, -1);
  IPoint pIn2( 0,  0);
  IPoint pIn3(43, 39);
  IPoint pIn4(76, 45);  // Border point
  IPoint pIn5(-1, -2);  // Border point

  // Points out
  IPoint pOut1(-11, 28);
  IPoint pOut2(101, -1);
  IPoint pOut3(1000, 1000);

  // -----
  // Check
  // -----

  // Points in
  CPPUNIT_ASSERT( box.contains(pIn1)  );
  CPPUNIT_ASSERT( box.contains(-4,-1) );
  CPPUNIT_ASSERT( box.contains(pIn2)  );
  CPPUNIT_ASSERT( box.contains(0,0)   );
  CPPUNIT_ASSERT( box.contains(pIn3)  );
  CPPUNIT_ASSERT( box.contains(43,39) );
  CPPUNIT_ASSERT( box.contains(pIn4)  );
  CPPUNIT_ASSERT( box.contains(76,45) );
  CPPUNIT_ASSERT( box.contains(pIn5)  );
  CPPUNIT_ASSERT( box.contains(-1,-2) );

  // Points out
  CPPUNIT_ASSERT( !(box.contains(pOut1))     );
  CPPUNIT_ASSERT( !(box.contains(-11,28))    );
  CPPUNIT_ASSERT( !(box.contains(pOut2))     );
  CPPUNIT_ASSERT( !(box.contains(101,-1))    );
  CPPUNIT_ASSERT( !(box.contains(pOut3))     );
  CPPUNIT_ASSERT( !(box.contains(1000,1000)) );
}


void
BoundingBoxTest::testContainsBox()
{
  // ------
  // Set Up
  // ------

  BoundingBox bb(40,70,80,40);
  BoundingBox bbN(-40,-70,-80,-40);
  BoundingBox bbDup(bb);


  // +-----+             +------+        +-----+     +-----+
  // |     |             |      |        |/////|     |/////|
  // |  +------+      +------+  |     +--|--+//|     |//+-----+
  // |  |//|///|      |//|///|  |     |  |//|//|     |//|//|  |
  // +-----+///|      |//+------+     |  +-----+     +-----+  |
  //    |////bb|      |//////|        |     |           |     |    
  //    +------+      +------+        +-----+           +-----+
  // case 1           case 2          case 3         case 4

  BoundingBox bb1(20,90,50,60);
  BoundingBox bb2(60,90,100,50);
  BoundingBox bb3(0,50,50,0);
  BoundingBox bb4(60,50,90,10);
  BoundingBox bb1N(-20,-90,-50,-60);
  BoundingBox bb2N(-60,-90,-100,-50);
  BoundingBox bb3N(0,-50,-50,0);
  BoundingBox bb4N(-60,-50,-90,-10);

  //      +--+                        +------+
  //      |  |                        |//////|
  //    +------+      +------+        |/+--+/|        +-----+
  //    |/|//|/|      |///+-----+     |/|//|/|     +--|--+//|
  //    |/+--+/|      |// |//|  |     +-|--|-+     |  |//|//|
  //    |//////|      |///+-----+       |  |       +--|--+//|    
  //    +------+      +------+          +--+          +-----+
  // case 5           case 6          case 7       case 8

  BoundingBox bb5(50,100,60,50);
  BoundingBox bb6(50,60,120,50);
  BoundingBox bb7(50,50,70,10);
  BoundingBox bb8(10,60,70,50);
  BoundingBox bb5N(-50,-100,-60,-50);
  BoundingBox bb6N(-50,-60,-120,-50);
  BoundingBox bb7N(-50,-50,-70,-10);
  BoundingBox bb8N(-10,-60,-70,-50);

  //      +--+                        +------+
  //      |//|                        |      |
  //    +------+      +------+        | +--+ |        +-----+
  //    | |//| |      |   +-----+     | |//| |     +--|--+  |
  //    | +--+ |      |   |//|//|     +-|--|-+     |//|//|  |
  //    |      |      |   +-----+       |//|       +--|--+  |    
  //    +------+      +------+          +--+          +-----+
  //    case 9        case 10         case 11      case 12

  BoundingBox bb9 (20,50,100,10);
  BoundingBox bb10(0,100,50,20);
  BoundingBox bb11(10,100,120,60);
  BoundingBox bb12(50,80,110,10);
  BoundingBox bb9N (-20,-50,-100,-10);
  BoundingBox bb10N(0,-100,-50,-20);
  BoundingBox bb11N(-10,-100,-120,-60);
  BoundingBox bb12N(-50,-80,-110,-10);

  //      +--+                        +------+
  //      |//|                        |      |    +-----------+
  //    +------+      +------+        | +--+ |    |///////////|
  //    | |//| |   +--|------|--+     | |//| |    |//+-----+//|
  //    | |//| |   |//|//////|//|     | |//| |    |//|/////|//|
  //    | |//| |   +--|------|--+     | |//| |    |//+-----+//|    
  //    +------+      +------+        | +--+ |    |///////////|
  //      |//|                        |      |    +-----------+
  //      +--+                        +------+
  //    case 13        case 14        case 15      case 16

  BoundingBox bb13(20,60,90,50);
  BoundingBox bb14(50,90,70,10);
  BoundingBox bb15(10,100,90,0);
  BoundingBox bb16(50,60,60,50);
  BoundingBox bb13N(-20,-60,-90,-50);
  BoundingBox bb14N(-50,-90,-70,-10);
  BoundingBox bb15N(-10,-100,-90,0);
  BoundingBox bb16N(-50,-60,-60,-50);

  // +------+                            +------+
  // |      |                            |//////|
  // +------+             +-----+        |//////|        +-----+
  //                 +--+ |/////|        |//////|        |/////|  +-----+
  //    +------+     |  | |/////|        +------+        |/////|  |     |
  //    |//////|     +--+ |/////|                        +-----+  |     |
  //    |//////|          +-----+      +-----------+              |     |
  //    |//////|                       |           |              +-----+
  //    +------+                       +-----------+
  //    case 17      case 18           case 19            case 20

  BoundingBox bb17(10,100,70,80);
  BoundingBox bb18(10,60,20,50);
  BoundingBox bb19(20,30,110,0);
  BoundingBox bb20(110,60,130,-40);
  BoundingBox bb17N(-10,-100,-70,-80);
  BoundingBox bb18N(-10,-60,-20,-50);
  BoundingBox bb19N(-20,-30,-110,0);
  BoundingBox bb20N(-110,-60,-130,40);

  // +--+                            +------+                 +----+
  // |  |                            |//////|                 |    |
  // |  |                 +-----+    |//////|           +-----+----+
  // |  |            +----+/////|    |//////|           |/////|
  // +--+------+     |    |/////|    +-+----+------+    |/////|
  //    |//////|     +----+/////|      |           |    +-----+
  //    |//////|          +-----+      |           |
  //    |//////|                       |           |
  //    +------+                       +-----------+
  //    case 21      case 22           case 23            case 24

  BoundingBox bb21(10,100,70,80);
  BoundingBox bb22(10,60,40,50);
  BoundingBox bb23(70,40,110,0);
  BoundingBox bb24(80,110,130,70);
  BoundingBox bb21N(-10,-100,-70,-80);
  BoundingBox bb22N(-10,-60,-40,-50);
  BoundingBox bb23N(-70,-40,-110,0);
  BoundingBox bb24N(-80,-110,-130,-70);

  // -----
  // Check
  // -----

  // Self-inclusion
  CPPUNIT_ASSERT( bb.contains(bb)    );
  CPPUNIT_ASSERT( bbN.contains(bbN)  );
  CPPUNIT_ASSERT( bb.contains(bbDup) );
  // Case 1
  CPPUNIT_ASSERT( !(bb.contains(bb1))   );
  CPPUNIT_ASSERT( !(bbN.contains(bb1N)) );
  // Case 2
  CPPUNIT_ASSERT( !(bb.contains(bb2))   );
  CPPUNIT_ASSERT( !(bbN.contains(bb2N)) );
  // Case 3
  CPPUNIT_ASSERT( !(bb.contains(bb3))   );
  CPPUNIT_ASSERT( !(bbN.contains(bb3N)) );
  // Case 4
  CPPUNIT_ASSERT( !(bb.contains(bb4))   );
  CPPUNIT_ASSERT( !(bbN.contains(bb4N)) );
  // Case 5
  CPPUNIT_ASSERT( !(bb.contains(bb5))   );
  CPPUNIT_ASSERT( !(bbN.contains(bb5N)) );
  // Case 6
  CPPUNIT_ASSERT( !(bb.contains(bb6))   );
  CPPUNIT_ASSERT( !(bbN.contains(bb6N)) );
  // Case 7
  CPPUNIT_ASSERT( !(bb.contains(bb7))   );
  CPPUNIT_ASSERT( !(bbN.contains(bb7N)) );
  // Case 8
  CPPUNIT_ASSERT( !(bb.contains(bb8))   );
  CPPUNIT_ASSERT( !(bbN.contains(bb8N)) );
  // Case 9
  CPPUNIT_ASSERT( !(bb.contains(bb9))   );
  CPPUNIT_ASSERT( !(bbN.contains(bb9N)) );
  // Case 10
  CPPUNIT_ASSERT( !(bb.contains(bb10))   );
  CPPUNIT_ASSERT( !(bbN.contains(bb10N)) );
  // Case 11
  CPPUNIT_ASSERT( !(bb.contains(bb11))   );
  CPPUNIT_ASSERT( !(bbN.contains(bb11N)) );
  // Case 12
  CPPUNIT_ASSERT( !(bb.contains(bb12))   );
  CPPUNIT_ASSERT( !(bbN.contains(bb12N)) );
  // Case 13
  CPPUNIT_ASSERT( !(bb.contains(bb13))   );
  CPPUNIT_ASSERT( !(bbN.contains(bb13N)) );
  // Case 14
  CPPUNIT_ASSERT( !(bb.contains(bb14))   );
  CPPUNIT_ASSERT( !(bbN.contains(bb14N)) );
  // Case 15
  CPPUNIT_ASSERT( !(bb.contains(bb15))   );
  CPPUNIT_ASSERT( !(bbN.contains(bb15N)) );
  // Case 16
  CPPUNIT_ASSERT( bb.contains(bb16)   );
  CPPUNIT_ASSERT( bbN.contains(bb16N) );
  // Case 17
  CPPUNIT_ASSERT( !(bb.contains(bb17))   );
  CPPUNIT_ASSERT( !(bb.contains(bb17N)) );
  // Case 18
  CPPUNIT_ASSERT( !(bb.contains(bb18))   );
  CPPUNIT_ASSERT( !(bbN.contains(bb18N)) );
  // Case 19
  CPPUNIT_ASSERT( !(bb.contains(bb19))   );
  CPPUNIT_ASSERT( !(bbN.contains(bb19N)) );
  // Case 20
  CPPUNIT_ASSERT( !(bb.contains(bb20))   );
  CPPUNIT_ASSERT( !(bbN.contains(bb20N)) );
  // Case 21
  CPPUNIT_ASSERT( !(bb.contains(bb21))   );
  CPPUNIT_ASSERT( !(bb.contains(bb21N)) );
  // Case 22
  CPPUNIT_ASSERT( !(bb.contains(bb22))   );
  CPPUNIT_ASSERT( !(bbN.contains(bb22N)) );
  // Case 23
  CPPUNIT_ASSERT( !(bb.contains(bb23))   );
  CPPUNIT_ASSERT( !(bbN.contains(bb23N)) );
  // Case 24
  CPPUNIT_ASSERT( !(bb.contains(bb24))   );
  CPPUNIT_ASSERT( !(bbN.contains(bb24N)) );
}


void
BoundingBoxTest::testIntersects()
{
  // ------
  // Set Up
  // ------

  BoundingBox bb(40,40,80,70);
  BoundingBox bbDup(bb);
  BoundingBox bbN(-80,-70,-40,-40);

  // +-----+             +------+        +-----+     +-----+
  // |     |             |      |        |/////|     |/////|
  // |  +------+      +------+  |     +--|--+//|     |//+-----+
  // |  |//|///|      |//|///|  |     |  |//|//|     |//|//|  |
  // +-----+///|      |//+------+     |  +-----+     +-----+  |
  //    |////bb|      |//////|        |     |           |     |    
  //    +------+      +------+        +-----+           +-----+
  // case 1           case 2          case 3         case 4

  BoundingBox bb1(20,10,50,60);   // intersection = (40,40) (50,60)
  BoundingBox bb2(60,10,100,50);  // intersection = (60,40) (80,50)
  BoundingBox bb3(0,50,50,90);    // intersection = (40,50) (50,70)
  BoundingBox bb4(60,50,90,80);   // intersection = (60,50) (80,70)

  //      +--+                        +------+
  //      |  |                        |//////|
  //    +------+      +------+        |/+--+/|        +-----+
  //    |/|//|/|      |///+-----+     |/|//|/|     +--|--+//|
  //    |/+--+/|      |// |//|  |     +-|--|-+     |  |//|//|
  //    |//////|      |///+-----+       |  |       +--|--+//|    
  //    +------+      +------+          +--+          +-----+
  // case 5           case 6          case 7       case 8

  BoundingBox bb5(50,30,60,60);   // intersection = (50,40) (60,60)
  BoundingBox bb6(50,50,120,60);  // intersection = (50,50) (80,60)
  BoundingBox bb7(50,50,70,100);  // intersection = (50,50) (70,70)
  BoundingBox bb8(10,50,50,60);   // intersection = (40,50) (50,60)

  //      +--+                        +------+
  //      |//|                        |      |
  //    +------+      +------+        | +--+ |        +-----+
  //    | |//| |      |   +-----+     | |//| |     +--|--+  |
  //    | +--+ |      |   |//|//|     +-|--|-+     |//|//|  |
  //    |      |      |   +-----+       |//|       +--|--+  |    
  //    +------+      +------+          +--+          +-----+
  //    case 9        case 10         case 11      case 12

  BoundingBox bb9 (20,50,100,100);  // intersection = (40,50) (80,70)
  BoundingBox bb10(0,0,50,80);      // intersection = (40,40) (50,70)
  BoundingBox bb11(10,0,120,60);    // intersection = (40,40) (80,60)
  BoundingBox bb12(50,30,110,120);  // intersection = (50,40) (80,70)

  //      +--+                        +------+
  //      |//|                        |      |    +-----------+
  //    +------+      +------+        | +--+ |    |///////////|
  //    | |//| |   +--|------|--+     | |//| |    |//+-----+//|
  //    | |//| |   |//|//////|//|     | |//| |    |//|/////|//|
  //    | |//| |   +--|------|--+     | |//| |    |//+-----+//|    
  //    +------+      +------+        | +--+ |    |///////////|
  //      |//|                        |      |    +-----------+
  //      +--+                        +------+
  //    case 13        case 14        case 15      case 16

  BoundingBox bb13(20,10,90,60);   // intersection = (40,40) (80,60)
  BoundingBox bb14(50,20,70,90);   // intersection = (50,40) (70,70)
  BoundingBox bb15(10,10,90,80);   // intersection = (40,40) (80,70)
  BoundingBox bb16(50,50,60,60);   // intersection = (50,50) (60,60)

  // +------+                            +------+
  // |      |                            |//////|
  // +------+             +-----+        |//////|        +-----+
  //                 +--+ |/////|        |//////|        |/////|  +-----+
  //    +------+     |  | |/////|        +------+        |/////|  |     |
  //    |//////|     +--+ |/////|                        +-----+  |     |
  //    |//////|          +-----+      +-----------+              |     |
  //    |//////|                       |           |              +-----+
  //    +------+                       +-----------+
  //    case 17      case 18           case 19            case 20

  BoundingBox bb17(10,20,70,30);    // No intersection
  BoundingBox bb18(10,50,30,60);    // No intersection
  BoundingBox bb19(20,90,110,120);  // No intersection
  BoundingBox bb20(110,60,130,120); // No intersection

  // +--+                            +------+                 +----+
  // |  |                            |//////|                 |    |
  // |  |                 +-----+    |//////|           +-----+----+
  // |  |            +----+/////|    |//////|           |/////|
  // +--+------+     |    |/////|    +-+----+------+    |/////|
  //    |//////|     +----+/////|      |           |    +-----+
  //    |//////|          +-----+      |           |
  //    |//////|                       |           |
  //    +------+                       +-----------+
  //    case 21      case 22           case 23            case 24

  BoundingBox bb21(10,10,40,40);   // intersection = (40,40) (40,40)
  BoundingBox bb22(20,50,40,60);   // intersection = (40,50) (40,60)
  BoundingBox bb23(50,70,90,110);  // intersection = (50,70) (80,70)
  BoundingBox bb24(80,0,130,40);   // intersection = (80,40) (80,40)

  // -----
  // Check
  // -----

  // Self-intersection
  CPPUNIT_ASSERT( bb.intersects(bb)    );
  CPPUNIT_ASSERT( bb.intersects(bbDup) );
  // Case 1
  CPPUNIT_ASSERT( bb.intersects(bb1)   );
  // Case 2
  CPPUNIT_ASSERT( bb.intersects(bb2)   );
  // Case 3
  CPPUNIT_ASSERT( bb.intersects(bb3)   );
  // Case 4
  CPPUNIT_ASSERT( bb.intersects(bb4)   );
  // Case 5
  CPPUNIT_ASSERT( bb.intersects(bb5)   );
  // Case 6
  CPPUNIT_ASSERT( bb.intersects(bb6)   );
  // Case 7
  CPPUNIT_ASSERT( bb.intersects(bb7)   );
  // Case 8
  CPPUNIT_ASSERT( bb.intersects(bb8)   );
  // Case 9
  CPPUNIT_ASSERT( bb.intersects(bb9)   );
  // Case 10
  CPPUNIT_ASSERT( bb.intersects(bb10)   );
  // Case 11
  CPPUNIT_ASSERT( bb.intersects(bb11)   );
  // Case 12
  CPPUNIT_ASSERT( bb.intersects(bb12)   );
  // Case 13
  CPPUNIT_ASSERT( bb.intersects(bb13)   );
  // Case 14
  CPPUNIT_ASSERT( bb.intersects(bb14)   );
  // Case 15
  CPPUNIT_ASSERT( bb.intersects(bb15)   );
  // Case 16
  CPPUNIT_ASSERT( bb.intersects(bb16)   );
  // Case 17
  CPPUNIT_ASSERT( !(bb.intersects(bb17)) );
  // Case 18
  CPPUNIT_ASSERT( !(bb.intersects(bb18)) );
  // Case 19
  CPPUNIT_ASSERT( !(bb.intersects(bb19)) );
  // Case 20
  CPPUNIT_ASSERT( !(bb.intersects(bb20)) );
  // Case 21
  CPPUNIT_ASSERT( bb.intersects(bb21)   );
  // Case 22
  CPPUNIT_ASSERT( bb.intersects(bb22)   );
  // Case 23
  CPPUNIT_ASSERT( bb.intersects(bb23)   );
  // Case 24
  CPPUNIT_ASSERT( bb.intersects(bb24)   );
}


// -------------------------------------------------------------------
// G E O M E T R I C A L   O P E R A T I O N S
// -------------------------------------------------------------------


void
BoundingBoxTest::testIntersection()
{
  // ------
  // Set Up
  // ------

  BoundingBox bb(40,40,80,70);
  BoundingBox bbDup(bb);
  BoundingBox bbN(-80,-70,-40,-40);

  // +-----+             +------+        +-----+     +-----+
  // |     |             |      |        |/////|     |/////|
  // |  +------+      +------+  |     +--|--+//|     |//+-----+
  // |  |//|///|      |//|///|  |     |  |//|//|     |//|//|  |
  // +-----+///|      |//+------+     |  +-----+     +-----+  |
  //    |////bb|      |//////|        |     |           |     |    
  //    +------+      +------+        +-----+           +-----+
  // case 1           case 2          case 3         case 4

  BoundingBox bb1(20,10,50,60);   // intersection = (40,40) (50,60)
  BoundingBox bb2(60,10,100,50);  // intersection = (60,40) (80,50)
  BoundingBox bb3(0,50,50,90);    // intersection = (40,50) (50,70)
  BoundingBox bb4(60,50,90,80);   // intersection = (60,50) (80,70)

  //      +--+                        +------+
  //      |  |                        |//////|
  //    +------+      +------+        |/+--+/|        +-----+
  //    |/|//|/|      |///+-----+     |/|//|/|     +--|--+//|
  //    |/+--+/|      |// |//|  |     +-|--|-+     |  |//|//|
  //    |//////|      |///+-----+       |  |       +--|--+//|    
  //    +------+      +------+          +--+          +-----+
  // case 5           case 6          case 7       case 8

  BoundingBox bb5(50,30,60,60);   // intersection = (50,40) (60,60)
  BoundingBox bb6(50,50,120,60);  // intersection = (50,50) (80,60)
  BoundingBox bb7(50,50,70,100);  // intersection = (50,50) (70,70)
  BoundingBox bb8(10,50,50,60);   // intersection = (40,50) (50,60)

  //      +--+                        +------+
  //      |//|                        |      |
  //    +------+      +------+        | +--+ |        +-----+
  //    | |//| |      |   +-----+     | |//| |     +--|--+  |
  //    | +--+ |      |   |//|//|     +-|--|-+     |//|//|  |
  //    |      |      |   +-----+       |//|       +--|--+  |    
  //    +------+      +------+          +--+          +-----+
  //    case 9        case 10         case 11      case 12

  BoundingBox bb9 (20,50,100,100);  // intersection = (40,50) (80,70)
  BoundingBox bb10(0,0,50,80);      // intersection = (40,40) (50,70)
  BoundingBox bb11(10,0,120,60);    // intersection = (40,40) (80,60)
  BoundingBox bb12(50,30,110,120);  // intersection = (50,40) (80,70)

  //      +--+                        +------+
  //      |//|                        |      |    +-----------+
  //    +------+      +------+        | +--+ |    |///////////|
  //    | |//| |   +--|------|--+     | |//| |    |//+-----+//|
  //    | |//| |   |//|//////|//|     | |//| |    |//|/////|//|
  //    | |//| |   +--|------|--+     | |//| |    |//+-----+//|    
  //    +------+      +------+        | +--+ |    |///////////|
  //      |//|                        |      |    +-----------+
  //      +--+                        +------+
  //    case 13        case 14        case 15      case 16

  BoundingBox bb13(20,10,90,60);   // intersection = (40,40) (80,60)
  BoundingBox bb14(50,20,70,90);   // intersection = (50,40) (70,70)
  BoundingBox bb15(10,10,90,80);   // intersection = (40,40) (80,70)
  BoundingBox bb16(50,50,60,60);   // intersection = (50,50) (60,60)

  // +------+                            +------+
  // |      |                            |//////|
  // +------+             +-----+        |//////|        +-----+
  //                 +--+ |/////|        |//////|        |/////|  +-----+
  //    +------+     |  | |/////|        +------+        |/////|  |     |
  //    |//////|     +--+ |/////|                        +-----+  |     |
  //    |//////|          +-----+      +-----------+              |     |
  //    |//////|                       |           |              +-----+
  //    +------+                       +-----------+
  //    case 17      case 18           case 19            case 20

  BoundingBox bb17(10,20,70,30);    // No intersection
  BoundingBox bb18(10,50,30,60);    // No intersection
  BoundingBox bb19(20,90,110,120);  // No intersection
  BoundingBox bb20(110,60,130,120); // No intersection

  // +--+                            +------+                 +----+
  // |  |                            |//////|                 |    |
  // |  |                 +-----+    |//////|           +-----+----+
  // |  |            +----+/////|    |//////|           |/////|
  // +--+------+     |    |/////|    +-+----+------+    |/////|
  //    |//////|     +----+/////|      |           |    +-----+
  //    |//////|          +-----+      |           |
  //    |//////|                       |           |
  //    +------+                       +-----------+
  //    case 21      case 22           case 23            case 24

  BoundingBox bb21(10,10,40,40);   // intersection = (40,40) (40,40)
  BoundingBox bb22(20,50,40,60);   // intersection = (40,50) (40,60)
  BoundingBox bb23(50,70,90,110);  // intersection = (50,70) (80,70)
  BoundingBox bb24(80,0,130,40);   // intersection = (80,40) (80,40)

  // -------
  // Process
  // -------

  BoundingBox* intS   = bb.intersection(bbDup);
  BoundingBox* int1   = bb.intersection(bb1);
  BoundingBox* int2   = bb.intersection(bb2);
  BoundingBox* int3   = bb.intersection(bb3);
  BoundingBox* int4   = bb.intersection(bb4);
  BoundingBox* int5   = bb.intersection(bb5);
  BoundingBox* int6   = bb.intersection(bb6);
  BoundingBox* int7   = bb.intersection(bb7);
  BoundingBox* int8   = bb.intersection(bb8);
  BoundingBox* int9   = bb.intersection(bb9);
  BoundingBox* int10  = bb.intersection(bb10);
  BoundingBox* int11  = bb.intersection(bb11);
  BoundingBox* int12  = bb.intersection(bb12);
  BoundingBox* int13  = bb.intersection(bb13);
  BoundingBox* int14  = bb.intersection(bb14);
  BoundingBox* int15  = bb.intersection(bb15);
  BoundingBox* int16  = bb.intersection(bb16);
  BoundingBox* int17  = bb.intersection(bb17);
  BoundingBox* int18  = bb.intersection(bb18);
  BoundingBox* int19  = bb.intersection(bb19);
  BoundingBox* int20  = bb.intersection(bb20);
  BoundingBox* int21  = bb.intersection(bb21);
  BoundingBox* int22  = bb.intersection(bb22);
  BoundingBox* int23  = bb.intersection(bb23);
  BoundingBox* int24  = bb.intersection(bb24);

  // -----
  // Check
  // -----

  // Self-intersection
  CPPUNIT_ASSERT( intS != (BoundingBox*)0  );
  CPPUNIT_ASSERT_EQUAL( intS->xTopLeft(),     40 );
  CPPUNIT_ASSERT_EQUAL( intS->yTopLeft(),     40 );
  CPPUNIT_ASSERT_EQUAL( intS->xBottomRight(), 80 );
  CPPUNIT_ASSERT_EQUAL( intS->yBottomRight(), 70 );
  // Case 1
  CPPUNIT_ASSERT( int1 != (BoundingBox*)0  );
  CPPUNIT_ASSERT_EQUAL( int1->xTopLeft(),     40 );
  CPPUNIT_ASSERT_EQUAL( int1->yTopLeft(),     40 );
  CPPUNIT_ASSERT_EQUAL( int1->xBottomRight(), 50 );
  CPPUNIT_ASSERT_EQUAL( int1->yBottomRight(), 60 );
  // Case 2
  CPPUNIT_ASSERT( int2 != (BoundingBox*)0  );
  CPPUNIT_ASSERT_EQUAL( int2->xTopLeft(),     60 );
  CPPUNIT_ASSERT_EQUAL( int2->yTopLeft(),     40 );
  CPPUNIT_ASSERT_EQUAL( int2->xBottomRight(), 80 );
  CPPUNIT_ASSERT_EQUAL( int2->yBottomRight(), 50 );
  // Case 3
  CPPUNIT_ASSERT( int3 != (BoundingBox*)0  );
  CPPUNIT_ASSERT_EQUAL( int3->xTopLeft(),     40 );
  CPPUNIT_ASSERT_EQUAL( int3->yTopLeft(),     50 );
  CPPUNIT_ASSERT_EQUAL( int3->xBottomRight(), 50 );
  CPPUNIT_ASSERT_EQUAL( int3->yBottomRight(), 70 );
  // Case 4
  CPPUNIT_ASSERT( int4 != (BoundingBox*)0  );
  CPPUNIT_ASSERT_EQUAL( int4->xTopLeft(),     60 );
  CPPUNIT_ASSERT_EQUAL( int4->yTopLeft(),     50 );
  CPPUNIT_ASSERT_EQUAL( int4->xBottomRight(), 80 );
  CPPUNIT_ASSERT_EQUAL( int4->yBottomRight(), 70 );
  // Case 5
  CPPUNIT_ASSERT( int5 != (BoundingBox*)0  );
  CPPUNIT_ASSERT_EQUAL( int5->xTopLeft(),     50 );
  CPPUNIT_ASSERT_EQUAL( int5->yTopLeft(),     40 );
  CPPUNIT_ASSERT_EQUAL( int5->xBottomRight(), 60 );
  CPPUNIT_ASSERT_EQUAL( int5->yBottomRight(), 60 );
  // Case 6
  CPPUNIT_ASSERT( int6 != (BoundingBox*)0  );
  CPPUNIT_ASSERT_EQUAL( int6->xTopLeft(),     50 );
  CPPUNIT_ASSERT_EQUAL( int6->yTopLeft(),     50 );
  CPPUNIT_ASSERT_EQUAL( int6->xBottomRight(), 80 );
  CPPUNIT_ASSERT_EQUAL( int6->yBottomRight(), 60 );
  // Case 7
  CPPUNIT_ASSERT( int7 != (BoundingBox*)0  );
  CPPUNIT_ASSERT_EQUAL( int7->xTopLeft(),     50 );
  CPPUNIT_ASSERT_EQUAL( int7->yTopLeft(),     50 );
  CPPUNIT_ASSERT_EQUAL( int7->xBottomRight(), 70 );
  CPPUNIT_ASSERT_EQUAL( int7->yBottomRight(), 70 );
  // Case 8
  CPPUNIT_ASSERT( int8 != (BoundingBox*)0  );
  CPPUNIT_ASSERT_EQUAL( int8->xTopLeft(),     40 );
  CPPUNIT_ASSERT_EQUAL( int8->yTopLeft(),     50 );
  CPPUNIT_ASSERT_EQUAL( int8->xBottomRight(), 50 );
  CPPUNIT_ASSERT_EQUAL( int8->yBottomRight(), 60 );
  // Case 9
  CPPUNIT_ASSERT( int9 != (BoundingBox*)0  );
  CPPUNIT_ASSERT_EQUAL( int9->xTopLeft(),     40 );
  CPPUNIT_ASSERT_EQUAL( int9->yTopLeft(),     50 );
  CPPUNIT_ASSERT_EQUAL( int9->xBottomRight(), 80 );
  CPPUNIT_ASSERT_EQUAL( int9->yBottomRight(), 70 );
  // Case 10
  CPPUNIT_ASSERT( int10 != (BoundingBox*)0  );
  CPPUNIT_ASSERT_EQUAL( int10->xTopLeft(),     40 );
  CPPUNIT_ASSERT_EQUAL( int10->yTopLeft(),     40 );
  CPPUNIT_ASSERT_EQUAL( int10->xBottomRight(), 50 );
  CPPUNIT_ASSERT_EQUAL( int10->yBottomRight(), 70 );
  // Case 11
  CPPUNIT_ASSERT( int11 != (BoundingBox*)0  );
  CPPUNIT_ASSERT_EQUAL( int11->xTopLeft(),     40 );
  CPPUNIT_ASSERT_EQUAL( int11->yTopLeft(),     40 );
  CPPUNIT_ASSERT_EQUAL( int11->xBottomRight(), 80 );
  CPPUNIT_ASSERT_EQUAL( int11->yBottomRight(), 60 );
  // Case 12
  CPPUNIT_ASSERT( int12 != (BoundingBox*)0  );
  CPPUNIT_ASSERT_EQUAL( int12->xTopLeft(),     50 );
  CPPUNIT_ASSERT_EQUAL( int12->yTopLeft(),     40 );
  CPPUNIT_ASSERT_EQUAL( int12->xBottomRight(), 80 );
  CPPUNIT_ASSERT_EQUAL( int12->yBottomRight(), 70 );
  // Case 13
  CPPUNIT_ASSERT( int13 != (BoundingBox*)0  );
  CPPUNIT_ASSERT_EQUAL( int13->xTopLeft(),     40 );
  CPPUNIT_ASSERT_EQUAL( int13->yTopLeft(),     40 );
  CPPUNIT_ASSERT_EQUAL( int13->xBottomRight(), 80 );
  CPPUNIT_ASSERT_EQUAL( int13->yBottomRight(), 60 );
  // Case 14
  CPPUNIT_ASSERT( int14 != (BoundingBox*)0  );
  CPPUNIT_ASSERT_EQUAL( int14->xTopLeft(),     50 );
  CPPUNIT_ASSERT_EQUAL( int14->yTopLeft(),     40 );
  CPPUNIT_ASSERT_EQUAL( int14->xBottomRight(), 70 );
  CPPUNIT_ASSERT_EQUAL( int14->yBottomRight(), 70 );
  // Case 15
  CPPUNIT_ASSERT( int15 != (BoundingBox*)0  );
  CPPUNIT_ASSERT_EQUAL( int15->xTopLeft(),     40 );
  CPPUNIT_ASSERT_EQUAL( int15->yTopLeft(),     40 );
  CPPUNIT_ASSERT_EQUAL( int15->xBottomRight(), 80 );
  CPPUNIT_ASSERT_EQUAL( int15->yBottomRight(), 70 );
  // Case 16
  CPPUNIT_ASSERT( int16 != (BoundingBox*)0  );
  CPPUNIT_ASSERT_EQUAL( int16->xTopLeft(),     50 );
  CPPUNIT_ASSERT_EQUAL( int16->yTopLeft(),     50 );
  CPPUNIT_ASSERT_EQUAL( int16->xBottomRight(), 60 );
  CPPUNIT_ASSERT_EQUAL( int16->yBottomRight(), 60 );
  // Case 17
  CPPUNIT_ASSERT( int17 == (BoundingBox*)0  );
  // Case 18
  CPPUNIT_ASSERT( int18 == (BoundingBox*)0  );
  // Case 19
  CPPUNIT_ASSERT( int19 == (BoundingBox*)0  );
  // Case 20
  CPPUNIT_ASSERT( int20 == (BoundingBox*)0  );
  // Case 21
  CPPUNIT_ASSERT( int21 != (BoundingBox*)0  );
  CPPUNIT_ASSERT_EQUAL( int21->xTopLeft(),     40 );
  CPPUNIT_ASSERT_EQUAL( int21->yTopLeft(),     40 );
  CPPUNIT_ASSERT_EQUAL( int21->xBottomRight(), 40 );
  CPPUNIT_ASSERT_EQUAL( int21->yBottomRight(), 40 );
  // Case 22
  CPPUNIT_ASSERT( int22 != (BoundingBox*)0  );
  CPPUNIT_ASSERT_EQUAL( int22->xTopLeft(),     40 );
  CPPUNIT_ASSERT_EQUAL( int22->yTopLeft(),     50 );
  CPPUNIT_ASSERT_EQUAL( int22->xBottomRight(), 40 );
  CPPUNIT_ASSERT_EQUAL( int22->yBottomRight(), 60 );
  // Case 23
  CPPUNIT_ASSERT( int23 != (BoundingBox*)0  );
  CPPUNIT_ASSERT_EQUAL( int23->xTopLeft(),     50 );
  CPPUNIT_ASSERT_EQUAL( int23->yTopLeft(),     70 );
  CPPUNIT_ASSERT_EQUAL( int23->xBottomRight(), 80 );
  CPPUNIT_ASSERT_EQUAL( int23->yBottomRight(), 70 );
  // Case 24
  CPPUNIT_ASSERT( int24 != (BoundingBox*)0  );
  CPPUNIT_ASSERT_EQUAL( int24->xTopLeft(),     80 );
  CPPUNIT_ASSERT_EQUAL( int24->yTopLeft(),     40 );
  CPPUNIT_ASSERT_EQUAL( int24->xBottomRight(), 80 );
  CPPUNIT_ASSERT_EQUAL( int24->yBottomRight(), 40 );

  // ---------------------------------------
  // Free dynamically allocated memory space
  // ---------------------------------------

  delete intS;
  delete int1;
  delete int2;
  delete int3;
  delete int4;
  delete int5;
  delete int6;
  delete int7;
  delete int8;
  delete int9;
  delete int10;
  delete int11;
  delete int12;
  delete int13;
  delete int14;
  delete int15;
  delete int16;
  delete int17;
  delete int18;
  delete int19;
  delete int20;
  delete int21;
  delete int22;
  delete int23;
  delete int24;
}


// -------------------------------------------------------------------
// O P E R A T O R S
// -------------------------------------------------------------------


void
BoundingBoxTest::testAssignment()
{
  // ------
  // Set Up
  // ------
  
  BoundingBox iDupBox;

  // -------
  // Process
  // -------

  iDupBox = _iBox;

  // -----
  // Check
  // -----

  // Ensure that top left and the bottom corners
  // of both boxes are the same
  CPPUNIT_ASSERT_EQUAL( _iBox.topLeft(),     iDupBox.topLeft()     );
  CPPUNIT_ASSERT_EQUAL( _iBox.bottomRight(), iDupBox.bottomRight() );

  // Ensure that assignment returns a valid reference on 'this'
  CPPUNIT_ASSERT( &iDupBox == &(iDupBox = _iBox) );
}


void
BoundingBoxTest::testInEquality()
{
  // ------
  // Set Up
  // ------
  
  BoundingBox box(16, 78, -39, 44);
  BoundingBox boxEq(16, 78, -39, 44);
  BoundingBox boxNotEq(16, 78, -38, 44);

  // -----
  // Check
  // -----

  // Operators
  CPPUNIT_ASSERT( box == box         );  // Self-equality
  CPPUNIT_ASSERT( !(box != box)      );  // Self-equality
  CPPUNIT_ASSERT( box == boxEq       );
  CPPUNIT_ASSERT( !(box != boxEq)    );
  CPPUNIT_ASSERT( box != boxNotEq    );
  CPPUNIT_ASSERT( !(box == boxNotEq) );

  // Functional operators
  CPPUNIT_ASSERT( box.eq(box)         );  // Self-equality
  CPPUNIT_ASSERT( !(box.notEq(box))   );  // Self-equality
  CPPUNIT_ASSERT( box.eq(boxEq)       );
  CPPUNIT_ASSERT( !(box.notEq(boxEq)) );
  CPPUNIT_ASSERT( box.notEq(boxNotEq) );
  CPPUNIT_ASSERT( !(box.eq(boxNotEq)) );
}


// -------------------------------------------------------------------
// S E R I A L I Z A T I O N / D E S E R I A L I Z A T I O N
// -------------------------------------------------------------------


void
BoundingBoxTest::testSerializeDeserialize()
{
  // ------
  // Set Up
  // ------

  BoundingBox deserializedBox;

  // -------
  // Process
  // -------

  std::stringstream ss;

  ss << _iBox;
  ss >> deserializedBox;

  // -----
  // Check
  // -----
  
  CPPUNIT_ASSERT_EQUAL( _iBox.topLeft(),     deserializedBox.topLeft()     );
  CPPUNIT_ASSERT_EQUAL( _iBox.bottomRight(), deserializedBox.bottomRight() );
}


// -------------------------------------------------------------------
