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
 * @file  FreemanCodeTest.cpp
 * @brief Implementation of class FreemanCodeTest
 *
 *        See file FreemanCodeTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   February 3, 2004  18:14
 * @since  Qgar 2.1.1
 */



// QGAR
#include <qgarlib/FreemanCode.h>
#include <qgarlib/primitives.h>
// QGAR TESTS
#include "FreemanCodeTest.h"



using namespace qgar;


// ------------------------------------------------------------------
// T E S T F I X T U R E   I M P L
// ------------------------------------------------------------------

void
FreemanCodeTest::setUp()
{
  /* EMPTY */
}

// -------------------------------------------------------------------

void
FreemanCodeTest::tearDown()
{
  /* EMPTY */
}


// -------------------------------------------------------------------
// T E S T   F U N C T I O N S
// -------------------------------------------------------------------

void
FreemanCodeTest::testDirection()
{
  // NO TEST
}

// -------------------------------------------------------------------

void
FreemanCodeTest::testLength()
{
  // NO TEST
}

// -------------------------------------------------------------------
// -------------------------------------------------------------------


void
FreemanCodeTest::testDefaultConstructor()
{
  FreemanCode fcode;

  CPPUNIT_ASSERT_EQUAL( fcode.direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( fcode.length(), 0 );
}

// -------------------------------------------------------------------

void
FreemanCodeTest::testBuildFromDirLength()
{
  FreemanCode fcodeE18(QGE_DIRECTION_E, 18);
  CPPUNIT_ASSERT_EQUAL( fcodeE18.direction(), QGE_DIRECTION_E );
  CPPUNIT_ASSERT_EQUAL( fcodeE18.length(), 18 );

  FreemanCode fcodeSE1000(QGE_DIRECTION_SE, 1000);
  CPPUNIT_ASSERT_EQUAL( fcodeSE1000.direction(), QGE_DIRECTION_SE );
  CPPUNIT_ASSERT_EQUAL( fcodeSE1000.length(), 1000 );
}

// -------------------------------------------------------------------

void
FreemanCodeTest::testCopyConstructor()
{
  FreemanCode fcodeS666(QGE_DIRECTION_S, 666);
  CPPUNIT_ASSERT_EQUAL( fcodeS666.direction(), QGE_DIRECTION_S );
  CPPUNIT_ASSERT_EQUAL( fcodeS666.length(), 666 );

  FreemanCode cfcodeS666(fcodeS666);
  CPPUNIT_ASSERT_EQUAL( cfcodeS666.direction(), QGE_DIRECTION_S );
  CPPUNIT_ASSERT_EQUAL( cfcodeS666.length(), 666 );
}

// -------------------------------------------------------------------

void
FreemanCodeTest::testAssignment()
{
  FreemanCode fcodeW10000(QGE_DIRECTION_W, 10000);
  CPPUNIT_ASSERT_EQUAL( fcodeW10000.direction(), QGE_DIRECTION_W );
  CPPUNIT_ASSERT_EQUAL( fcodeW10000.length(), 10000 );

  FreemanCode cfcodeW10000 = fcodeW10000;
  CPPUNIT_ASSERT_EQUAL( cfcodeW10000.direction(), QGE_DIRECTION_W );
  CPPUNIT_ASSERT_EQUAL( cfcodeW10000.length(), 10000 );
}

// -------------------------------------------------------------------

void
FreemanCodeTest::testSetDir()
{
  FreemanCode fcodeNW10000(QGE_DIRECTION_NW, 10000);
  CPPUNIT_ASSERT_EQUAL( fcodeNW10000.direction(), QGE_DIRECTION_NW );
  CPPUNIT_ASSERT_EQUAL( fcodeNW10000.length(), 10000 );

  fcodeNW10000.setDir(QGE_DIRECTION_N);
  CPPUNIT_ASSERT_EQUAL( fcodeNW10000.direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( fcodeNW10000.length(), 10000 );
}

// -------------------------------------------------------------------

void
FreemanCodeTest::testSetLength()
{
  FreemanCode fcodeE7(QGE_DIRECTION_E, 7);
  CPPUNIT_ASSERT_EQUAL( fcodeE7.direction(), QGE_DIRECTION_E );
  CPPUNIT_ASSERT_EQUAL( fcodeE7.length(), 7 );

  fcodeE7.setLength(70);
  CPPUNIT_ASSERT_EQUAL( fcodeE7.direction(), QGE_DIRECTION_E );
  CPPUNIT_ASSERT_EQUAL( fcodeE7.length(), 70 );
}

// -------------------------------------------------------------------

void
FreemanCodeTest::testSetDirLength()
{
  FreemanCode fcodeSW44(QGE_DIRECTION_SW, 44);
  CPPUNIT_ASSERT_EQUAL( fcodeSW44.direction(), QGE_DIRECTION_SW );
  CPPUNIT_ASSERT_EQUAL( fcodeSW44.length(), 44 );

  fcodeSW44.setDirLength(QGE_DIRECTION_W, 88);
  CPPUNIT_ASSERT_EQUAL( fcodeSW44.direction(), QGE_DIRECTION_W );
  CPPUNIT_ASSERT_EQUAL( fcodeSW44.length(), 88 );
}

// -------------------------------------------------------------------

void
FreemanCodeTest::testToPoint()
{
  FreemanCode cN1 (QGE_DIRECTION_N,  1);
  FreemanCode cNE2(QGE_DIRECTION_NE, 2);
  FreemanCode cE3 (QGE_DIRECTION_E,  3);
  FreemanCode cSE4(QGE_DIRECTION_SE, 4);
  FreemanCode cS5 (QGE_DIRECTION_S,  5);
  FreemanCode cSW6(QGE_DIRECTION_SW, 6);
  FreemanCode cW7 (QGE_DIRECTION_W,  7);
  FreemanCode cNW8(QGE_DIRECTION_NW, 8);

  Point p44(4,4);
  Point p;

  // (4,4) -- N,1 --> (4,3)
  p = cN1.toPoint(p44);
  CPPUNIT_ASSERT_EQUAL( p.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( p.y(), 3 );

  // (4,4) -- NE,2 --> (6,2)
  p = cNE2.toPoint(p44);
  CPPUNIT_ASSERT_EQUAL( p.x(), 6 );
  CPPUNIT_ASSERT_EQUAL( p.y(), 2 );

  // (4,4) -- E,3 --> (7,4)
  p = cE3.toPoint(p44);
  CPPUNIT_ASSERT_EQUAL( p.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( p.y(), 4 );

  // (4,4) -- SE,4 --> (8,8)
  p = cSE4.toPoint(p44);
  CPPUNIT_ASSERT_EQUAL( p.x(), 8 );
  CPPUNIT_ASSERT_EQUAL( p.y(), 8 );

  // (4,4) -- S,5 --> (4,9)
  p = cS5.toPoint(p44);
  CPPUNIT_ASSERT_EQUAL( p.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( p.y(), 9 );

  // (4,4) -- SW,6 --> (-2,10)
  p = cSW6.toPoint(p44);
  CPPUNIT_ASSERT_EQUAL( p.x(), -2 );
  CPPUNIT_ASSERT_EQUAL( p.y(), 10 );

  // (4,4) -- W,7 --> (-3,4)
  p = cW7.toPoint(p44);
  CPPUNIT_ASSERT_EQUAL( p.x(), -3 );
  CPPUNIT_ASSERT_EQUAL( p.y(), 4 );

  // (4,4) -- NW,8 --> (-4,-4)
  p = cNW8.toPoint(p44);
  CPPUNIT_ASSERT_EQUAL( p.x(), -4 );
  CPPUNIT_ASSERT_EQUAL( p.y(), -4 );
}

// -------------------------------------------------------------------

void
FreemanCodeTest::testToOppositePoint()
{
  FreemanCode cN1 (QGE_DIRECTION_N,  1);
  FreemanCode cNE2(QGE_DIRECTION_NE, 2);
  FreemanCode cE3 (QGE_DIRECTION_E,  3);
  FreemanCode cSE4(QGE_DIRECTION_SE, 4);
  FreemanCode cS5 (QGE_DIRECTION_S,  5);
  FreemanCode cSW6(QGE_DIRECTION_SW, 6);
  FreemanCode cW7 (QGE_DIRECTION_W,  7);
  FreemanCode cNW8(QGE_DIRECTION_NW, 8);

  Point p44(4,4);
  Point p;

  // (4,4) -- N,1 --> (4,5)
  p = cN1.toOppositePoint(p44);
  CPPUNIT_ASSERT_EQUAL( p.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( p.y(), 5 );

  // (4,4) -- NE,2 --> (2,6)
  p = cNE2.toOppositePoint(p44);
  CPPUNIT_ASSERT_EQUAL( p.x(), 2 );
  CPPUNIT_ASSERT_EQUAL( p.y(), 6 );

  // (4,4) -- E,3 --> (1,4)
  p = cE3.toOppositePoint(p44);
  CPPUNIT_ASSERT_EQUAL( p.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( p.y(), 4 );

  // (4,4) -- SE,4 --> (0,0)
  p = cSE4.toOppositePoint(p44);
  CPPUNIT_ASSERT_EQUAL( p.x(), 0 );
  CPPUNIT_ASSERT_EQUAL( p.y(), 0 );

  // (4,4) -- S,5 --> (4,-1)
  p = cS5.toOppositePoint(p44);
  CPPUNIT_ASSERT_EQUAL( p.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( p.y(), -1 );

  // (4,4) -- SW,6 --> (10,-2)
  p = cSW6.toOppositePoint(p44);
  CPPUNIT_ASSERT_EQUAL( p.x(), 10 );
  CPPUNIT_ASSERT_EQUAL( p.y(), -2 );

  // (4,4) -- W,7 --> (11,4)
  p = cW7.toOppositePoint(p44);
  CPPUNIT_ASSERT_EQUAL( p.x(), 11 );
  CPPUNIT_ASSERT_EQUAL( p.y(), 4 );

  // (4,4) -- NW,8 --> (12,12)
  p = cNW8.toOppositePoint(p44);
  CPPUNIT_ASSERT_EQUAL( p.x(), 12 );
  CPPUNIT_ASSERT_EQUAL( p.y(), 12 );
}

// ----------------------------------------------------------------------
