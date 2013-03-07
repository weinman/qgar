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


/**
 * @file  FreemanChainTest.cpp
 * @brief Implementation of class FreemanChainTest
 *
 * See file FreemanChainTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   January 29, 2004  17:55
 * @since  Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: FreemanChainTest.cpp,v 1.7 2006/03/29 17:40:39 masini Exp $ */



// QGAR
#include <qgarlib/FreemanChain.h>
#include <qgarlib/FreemanCode.h>
#include <qgarlib/primitives.h>
// QGAR TESTS
#include "FreemanChainTest.h"



using namespace qgar;



// ------------------------------------------------------------------
// T E S T F I X T U R E   I M P L
// ------------------------------------------------------------------

void
FreemanChainTest::setUp()
{
  /* EMPTY */
}

// -------------------------------------------------------------------

void
FreemanChainTest::tearDown()
{
  /* EMPTY */
}


// -------------------------------------------------------------------
// N O T   T E S T E D
// -------------------------------------------------------------------

void
FreemanChainTest::testEmpty()
{
  /* NO TEST */
}

// -------------------------------------------------------------------

void
FreemanChainTest::testSize()
{
  /* NO TEST */
}

// -------------------------------------------------------------------

void
FreemanChainTest::testAccessFront()
{
  /* NO TEST */
}

// -------------------------------------------------------------------

void
FreemanChainTest::testFront()
{
  /* NO TEST */
}

// -------------------------------------------------------------------

void
FreemanChainTest::testAccessCurrent()
{
  /* NO TEST */
}

// -------------------------------------------------------------------

void
FreemanChainTest::testCurrent()
{
  /* NO TEST */
}

// -------------------------------------------------------------------

void
FreemanChainTest::testAccessBack()
{
  /* NO TEST */
}

// -------------------------------------------------------------------

void
FreemanChainTest::testBack()
{
  /* NO TEST */
}

// -------------------------------------------------------------------

void
FreemanChainTest::testAccessCodesList()
{
  /* NO TEST */
}

// ----------------------------------------------------------------------

void
FreemanChainTest::testSetToBegin()
{
  /* NO TEST */
}

// ----------------------------------------------------------------------

void
FreemanChainTest::testHasNext()
{
  /* NO TEST */
}

// -------------------------------------------------------------------

void
FreemanChainTest::testHasPrevious()
{
  /* NO TEST */
}

// -------------------------------------------------------------------
// E F F E C T I V E   T E S T S
// -------------------------------------------------------------------

void
FreemanChainTest::testBuildFromPoint()
{
  // A Freeman chain
  FreemanChain fch(Point(4,2));

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );

  // Chain size == 1
  CPPUNIT_ASSERT( fch.size() == 1 );

  // No previous and next points
  CPPUNIT_ASSERT( !(fch.hasNext()) );
  CPPUNIT_ASSERT( !(fch.hasPrevious()) );  

  // Front, current and last points are correctly set
  Point ipf = fch.front();
  Point ipc = fch.current();
  Point ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 2 );
}

// -------------------------------------------------------------------

void
FreemanChainTest::testPush_frontPoint()
{
  // (3,4)
  //  ^
  FreemanChain fch(Point(3,4));

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 1
  CPPUNIT_ASSERT( fch.size() == 1 );
  // No previous and next points
  CPPUNIT_ASSERT( !(fch.hasNext()) );
  CPPUNIT_ASSERT( !(fch.hasPrevious()) );  
  // Front, current and last points are correctly set
  Point ipf = fch.front();
  Point ipc = fch.current();
  Point ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 4 );

  // CHAIN INCLUDING A SINGLE POINT
  // ------------------------------

  // (7,8) -> (3,4)
  //           ^
  fch.push_front(Point(7,8));

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 2
  CPPUNIT_ASSERT( fch.size() == 2 );
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 8 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 4 );
  // No next point
  CPPUNIT_ASSERT( !(fch.hasNext()) );
  // There is a previous point
  CPPUNIT_ASSERT( fch.hasPrevious() );

  // Check codes in chain
  const std::list<FreemanCode>& lfc = fch.accessCodesList();
  std::list<FreemanCode>::const_iterator it = lfc.begin();
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 0 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_NW );
  CPPUNIT_ASSERT_EQUAL( it->length(), 4 );

  // CHAIN INCLUDING AT LEAST TWO POINTS
  // -----------------------------------

  // (7,5) -> (7,8) -> (3,4)
  //                    ^
  fch.push_front(Point(7,5));

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 3
  CPPUNIT_ASSERT( fch.size() == 3 );
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 5 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 4 );
  // No next point
  CPPUNIT_ASSERT( !(fch.hasNext()) );
  // There is a previous point
  CPPUNIT_ASSERT( fch.hasPrevious() );  

  // Check codes in chain
  it = lfc.begin();
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 0 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_S );
  CPPUNIT_ASSERT_EQUAL( it->length(), 3 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_NW );
  CPPUNIT_ASSERT_EQUAL( it->length(), 4 );

 // NEW POINT IN THE SAME DIRECTION AS THE FIRST ONE
  //
  // (7,2) -> (7,5) -> (7,8) -> (3,4)
  //                             ^
  fch.push_front(Point(7,2));

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 4
  CPPUNIT_ASSERT( fch.size() == 4 );
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 4 );
  // No next point
  CPPUNIT_ASSERT( !(fch.hasNext()) );
  // There is a previous point
  CPPUNIT_ASSERT( fch.hasPrevious() );  

  // Check codes in chain
  const std::list<FreemanCode>& lfc1 = fch.accessCodesList();
  it = lfc1.begin();
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 0 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_S );
  CPPUNIT_ASSERT_EQUAL( it->length(), 3 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_S );
  CPPUNIT_ASSERT_EQUAL( it->length(), 3 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_NW );
  CPPUNIT_ASSERT_EQUAL( it->length(), 4 );

  // NEW POINT
  //
  // (10,2) -> (7,2) -> (7,5) -> (7,8) -> (3,4)
  //                                       ^
  fch.push_front(Point(10,2));

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 5
  CPPUNIT_ASSERT( fch.size() == 5 );
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 10 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 4 );
  // No next point
  CPPUNIT_ASSERT( !(fch.hasNext()) );
  // There is a previous point
  CPPUNIT_ASSERT( fch.hasPrevious() );  

  // Check codes in chain
  const std::list<FreemanCode>& lfc2 = fch.accessCodesList();
  it = lfc2.begin();
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 0 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_W );
  CPPUNIT_ASSERT_EQUAL( it->length(), 3 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_S );
  CPPUNIT_ASSERT_EQUAL( it->length(), 3 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_S );
  CPPUNIT_ASSERT_EQUAL( it->length(), 3 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_NW );
  CPPUNIT_ASSERT_EQUAL( it->length(), 4 );

  // TWO NEW POINTS IN THE SAME DIRECTION AS THE FIRST ONE
  //
  // (28,2) -> (15,2) -> (10,2) -> (7,2) -> (7,5) -> (7,8) -> (3,4)
  //                                                           ^
  fch.push_front(Point(15,2));
  fch.push_front(Point(28,2));

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 7
  CPPUNIT_ASSERT( fch.size() == 7 );
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 28 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 4 );
  // No next point
  CPPUNIT_ASSERT( !(fch.hasNext()) );
  // There is a previous point
  CPPUNIT_ASSERT( fch.hasPrevious() );  

  // Check codes in chain
  const std::list<FreemanCode>& lfc3 = fch.accessCodesList();
  it = lfc3.begin();
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 0 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_W );
  CPPUNIT_ASSERT_EQUAL( it->length(), 13 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_W );
  CPPUNIT_ASSERT_EQUAL( it->length(), 5 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_W );
  CPPUNIT_ASSERT_EQUAL( it->length(), 3 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_S );
  CPPUNIT_ASSERT_EQUAL( it->length(), 3 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_S );
  CPPUNIT_ASSERT_EQUAL( it->length(), 3 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_NW );
  CPPUNIT_ASSERT_EQUAL( it->length(), 4 );
}

// -------------------------------------------------------------------

void
FreemanChainTest::testPush_frontCode()
{
  // (4,2)
  //  ^
  FreemanChain fch(Point(4,2));

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 1
  CPPUNIT_ASSERT( fch.size() == 1 );
  // No previous and next points
  CPPUNIT_ASSERT( !(fch.hasNext()) );
  CPPUNIT_ASSERT( !(fch.hasPrevious()) );  
  // Front, current and last points are correctly set
  Point ipf = fch.front();
  Point ipc = fch.current();
  Point ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 2 );

  // CHAIN INCLUDING A SINGLE POINT
  // ------------------------------

  // +(EAST,4) : (8,2) -> (4,2)
  //                       ^
  FreemanCode code(QGE_DIRECTION_E, 4);
  fch.push_front(code);

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 2
  CPPUNIT_ASSERT( fch.size() == 2 );
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 8 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 2 );
  // No next point
  CPPUNIT_ASSERT( !(fch.hasNext()) );
  // There is a previous point
  CPPUNIT_ASSERT( fch.hasPrevious() );  

  // Check codes in chain
  const std::list<FreemanCode>& lfc = fch.accessCodesList();
  std::list<FreemanCode>::const_iterator it = lfc.begin();
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 0 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_W );
  CPPUNIT_ASSERT_EQUAL( it->length(), 4 );

  // CHAIN INCLUDING AT LEAST TWO POINTS
  // -----------------------------------

  // SAME DIRECTION AS FIRST CODE
  //
  // +(EAST,4) : (10,2) -> (8,2) -> (4,2)
  //                                 ^
  code.setDirLength(QGE_DIRECTION_E, 2);
  fch.push_front(code);

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 3
  CPPUNIT_ASSERT( fch.size() == 3 );
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 10 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 2 );
  // No next point
  CPPUNIT_ASSERT( !(fch.hasNext()) );
  // There is a previous point
  CPPUNIT_ASSERT( fch.hasPrevious() );  

  // Check codes in chain
  const std::list<FreemanCode>& lfc1 = fch.accessCodesList();
  it = lfc1.begin();
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 0 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_W );
  CPPUNIT_ASSERT_EQUAL( it->length(), 2 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_W );
  CPPUNIT_ASSERT_EQUAL( it->length(), 4 );

  // NEW POINT
  //
  // +(SOUTH,9) : (10,11) -> (10,2) -> (8,2) -> (4,2)
  //                                             ^
  code.setDirLength(QGE_DIRECTION_S, 9);
  fch.push_front(code);

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 4
  CPPUNIT_ASSERT( fch.size() == 4 );
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 10 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 11 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 2 );
  // No next point
  CPPUNIT_ASSERT( !(fch.hasNext()) );
  // There is a previous point
  CPPUNIT_ASSERT( fch.hasPrevious() );  

  // Check codes in chain
  const std::list<FreemanCode>& lfc2 = fch.accessCodesList();
  it = lfc2.begin();
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 0 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 9 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_W );
  CPPUNIT_ASSERT_EQUAL( it->length(), 2 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_W );
  CPPUNIT_ASSERT_EQUAL( it->length(), 4 );

  // OPPOSITE DIRECTION AS FIRST CODE
  //
  // +(NORTH,8) : (10,3) -> (10,11) -> (10,2) -> (8,2) -> (4,2)
  //                                                       ^
  code.setDirLength(QGE_DIRECTION_N, 8);
  fch.push_front(code);

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 5
  CPPUNIT_ASSERT( fch.size() == 5 );
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 10 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 3 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 2 );
  // No next point
  CPPUNIT_ASSERT( !(fch.hasNext()) );
  // There is a previous point
  CPPUNIT_ASSERT( fch.hasPrevious() );  

  // Check codes in chain
  const std::list<FreemanCode>& lfc3 = fch.accessCodesList();
  it = lfc3.begin();
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 0 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_S );
  CPPUNIT_ASSERT_EQUAL( it->length(), 8 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 9 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_W );
  CPPUNIT_ASSERT_EQUAL( it->length(), 2 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_W );
  CPPUNIT_ASSERT_EQUAL( it->length(), 4 );
}

// -------------------------------------------------------------------

void
FreemanChainTest::testPush_backPoint()
{
  // (4,2)
  //  ^
  FreemanChain fch(Point(4,2));

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 1
  CPPUNIT_ASSERT( fch.size() == 1 );
  // No previous and next points
  CPPUNIT_ASSERT( !(fch.hasNext()) );
  CPPUNIT_ASSERT( !(fch.hasPrevious()) );  
  // Front, current and last points are correctly set
  Point ipf = fch.front();
  Point ipc = fch.current();
  Point ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 2 );

  // CHAIN INCLUDING A SINGLE POINT
  // ------------------------------

  // (4,2) -> (10,2)
  //  ^
  fch.push_back(Point(10,2));

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 2
  CPPUNIT_ASSERT( fch.size() == 2 );
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 10 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 2 );
  // There is a next point
  CPPUNIT_ASSERT( fch.hasNext() );
  // No previous point
  CPPUNIT_ASSERT( !(fch.hasPrevious()) );  

  // Check codes in chain
  const std::list<FreemanCode>& lfc = fch.accessCodesList();
  std::list<FreemanCode>::const_iterator it = lfc.begin();
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 0 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_E );
  CPPUNIT_ASSERT_EQUAL( it->length(), 6 );

  // CHAIN INCLUDING AT LEAST TWO POINTS
  // -----------------------------------

  // (4,2) -> (10,2) -> (7,5)
  //  ^
  fch.push_back(Point(7,5));

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 3
  CPPUNIT_ASSERT( fch.size() == 3 );
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 5 );
  // There is a next point
  CPPUNIT_ASSERT( fch.hasNext() );
  // No previous point
  CPPUNIT_ASSERT( !(fch.hasPrevious()) );  

  // Check codes in chain
  const std::list<FreemanCode>& lfc2 = fch.accessCodesList();
  it = lfc2.begin();
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 0 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_E );
  CPPUNIT_ASSERT_EQUAL( it->length(), 6 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_SW );
  CPPUNIT_ASSERT_EQUAL( it->length(), 3 );

  // NEW POINT IN THE SAME DIRECTION AS THE FIRST ONE
  //
  // (4,2) -> (10,2) -> (7,5) -> (3,9)
  //  ^
  fch.push_back(Point(3,9));

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 4
  CPPUNIT_ASSERT( fch.size() == 4 );
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 9 );
  // There is a next point
  CPPUNIT_ASSERT( fch.hasNext() );
  // No previous point
  CPPUNIT_ASSERT( !(fch.hasPrevious()) );  

  // Check codes in chain
  const std::list<FreemanCode>& lfc3 = fch.accessCodesList();
  it = lfc3.begin();
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 0 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_E );
  CPPUNIT_ASSERT_EQUAL( it->length(), 6 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_SW );
  CPPUNIT_ASSERT_EQUAL( it->length(), 3 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_SW );
  CPPUNIT_ASSERT_EQUAL( it->length(), 4 );

  // NEW POINT
  //
  // (4,2) -> (10,2) -> (7,5) -> (3,9) -> (1,7)
  //  ^
  fch.push_back(Point(1,7));

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 5
  CPPUNIT_ASSERT( fch.size() == 5 );
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 7 );
  // There is a next point
  CPPUNIT_ASSERT( fch.hasNext() );
  // No previous point
  CPPUNIT_ASSERT( !(fch.hasPrevious()) );  

  // Check codes in chain
  const std::list<FreemanCode>& lfc4 = fch.accessCodesList();
  it = lfc4.begin();
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 0 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_E );
  CPPUNIT_ASSERT_EQUAL( it->length(), 6 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_SW );
  CPPUNIT_ASSERT_EQUAL( it->length(), 3 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_SW );
  CPPUNIT_ASSERT_EQUAL( it->length(), 4 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_NW );
  CPPUNIT_ASSERT_EQUAL( it->length(), 2 );

  // TWO NEW POINTS IN THE SAME DIRECTION AS THE FIRST ONE
  // NEGATIVE COORDINATES
  //
  // (4,2) -> (10,2) -> (7,5) -> (3,9) -> (1,7) -> (0,6) -> (-1,5)
  //  ^
  fch.push_back(Point(0,6));
  fch.push_back(Point(-1,5));

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 7
  CPPUNIT_ASSERT( fch.size() == 7 );
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), -1 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 5 );
  // There is a next point
  CPPUNIT_ASSERT( fch.hasNext() );
  // No previous point
  CPPUNIT_ASSERT( !(fch.hasPrevious()) );  

  // Check codes in chain
  const std::list<FreemanCode>& lfc5 = fch.accessCodesList();
  it = lfc5.begin();
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 0 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_E );
  CPPUNIT_ASSERT_EQUAL( it->length(), 6 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_SW );
  CPPUNIT_ASSERT_EQUAL( it->length(), 3 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_SW );
  CPPUNIT_ASSERT_EQUAL( it->length(), 4 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_NW );
  CPPUNIT_ASSERT_EQUAL( it->length(), 2 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_NW );
  CPPUNIT_ASSERT_EQUAL( it->length(), 1 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_NW );
  CPPUNIT_ASSERT_EQUAL( it->length(), 1 );
}

// -------------------------------------------------------------------

void
FreemanChainTest::testPush_backCode()
{
  // (4,2)
  //  ^
  FreemanChain fch(Point(4,2));

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 1
  CPPUNIT_ASSERT( fch.size() == 1 );
  // No previous and next points
  CPPUNIT_ASSERT( !(fch.hasNext()) );
  CPPUNIT_ASSERT( !(fch.hasPrevious()) );  
  // Front, current and last points are correctly set
  Point ipf = fch.front();
  Point ipc = fch.current();
  Point ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 2 );

  // CHAIN INCLUDING A SINGLE POINT
  // ------------------------------

  // +(EAST,6) : (4,2) -> (10,2)
  //              ^
  FreemanCode code(QGE_DIRECTION_E, 6);
  fch.push_back(code);

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 2
  CPPUNIT_ASSERT( fch.size() == 2 );
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 10 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 2 );
  // There is a next point
  CPPUNIT_ASSERT( fch.hasNext() );
  // No previous point
  CPPUNIT_ASSERT( !(fch.hasPrevious()) );

  // Check codes in chain
  const std::list<FreemanCode>& lfc = fch.accessCodesList();
  std::list<FreemanCode>::const_iterator it = lfc.begin();
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 0 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_E );
  CPPUNIT_ASSERT_EQUAL( it->length(), 6 );

  // CHAIN INCLUDING AT LEAST TWO POINTS
  // -----------------------------------

  // +(SOUTH-WEST,3) : (4,2) -> (10,2) -> (7,5)
  //                    ^
  code.setDirLength(QGE_DIRECTION_SW, 3);
  fch.push_back(code);

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 3
  CPPUNIT_ASSERT( fch.size() == 3 );
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 5 );
  // There is a next point
  CPPUNIT_ASSERT( fch.hasNext() );
  // No previous point
  CPPUNIT_ASSERT( !(fch.hasPrevious()) );

  // Check codes in chain
  const std::list<FreemanCode>& lfc1 = fch.accessCodesList();
  it = lfc1.begin();
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 0 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_E );
  CPPUNIT_ASSERT_EQUAL( it->length(), 6 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_SW );
  CPPUNIT_ASSERT_EQUAL( it->length(), 3 );

  // SAME DIRECTION AS LAST CODE
  //
  // +(SOUTH-WEST,4) : (4,2) -> (10,2) -> (7,5) -> (3,9)
  //                    ^
  code.setDirLength(QGE_DIRECTION_SW, 4);
  fch.push_back(code);

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 4
  CPPUNIT_ASSERT( fch.size() == 4 );
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 9 );
  // There is a next point
  CPPUNIT_ASSERT( fch.hasNext() );
  // No previous point
  CPPUNIT_ASSERT( !(fch.hasPrevious()) );

  // Check codes in chain
  const std::list<FreemanCode>& lfc2 = fch.accessCodesList();
  it = lfc2.begin();
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 0 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_E );
  CPPUNIT_ASSERT_EQUAL( it->length(), 6 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_SW );
  CPPUNIT_ASSERT_EQUAL( it->length(), 3 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_SW );
  CPPUNIT_ASSERT_EQUAL( it->length(), 4 );

  // OPPOSITE DIRECTION AS LAST CODE
  //
  // +(NORTH-EAST,8) : (4,2) -> (10,2) -> (7,5) -> (3,9) -> (11,1)
  //                    ^
  code.setDirLength(QGE_DIRECTION_NE, 8);
  fch.push_back(code);

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 5
  CPPUNIT_ASSERT( fch.size() == 5 );
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 11 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 1 );
  // There is a next point
  CPPUNIT_ASSERT( fch.hasNext() );
  // No previous point
  CPPUNIT_ASSERT( !(fch.hasPrevious()) );

  // Check codes in chain
  const std::list<FreemanCode>& lfc3 = fch.accessCodesList();
  it = lfc3.begin();
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 0 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_E );
  CPPUNIT_ASSERT_EQUAL( it->length(), 6 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_SW );
  CPPUNIT_ASSERT_EQUAL( it->length(), 3 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_SW );
  CPPUNIT_ASSERT_EQUAL( it->length(), 4 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_NE );
  CPPUNIT_ASSERT_EQUAL( it->length(), 8 );
}

// ----------------------------------------------------------------------

void
FreemanChainTest::testSetToEnd()
{
  // A Freeman chain
  //
  // (4,2) -> (10,2) -> (7,5) -> (7,8)
  //  ^
  FreemanChain fch(Point(4,2));
  fch.push_back(Point(10,2));
  fch.push_back(Point(7,5));
  fch.push_back(Point(7,8));

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 4
  CPPUNIT_ASSERT( fch.size() == 4 );
  // Front, current and last points are correctly set
  Point ipf = fch.front();
  Point ipc = fch.current();
  Point ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 8 );
  // There is a next point
  CPPUNIT_ASSERT( fch.hasNext() );
  // No previous point
  CPPUNIT_ASSERT( !(fch.hasPrevious()) );

  fch.setToEnd();
  //
  // (4,2) -> (10,2) -> (7,5) -> (7,8)
  //                              ^
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 8 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 8 );
  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 4
  CPPUNIT_ASSERT( fch.size() == 4 );
  // No next point
  CPPUNIT_ASSERT( !(fch.hasNext()) );
  // There is a previous point
  CPPUNIT_ASSERT( fch.hasPrevious() );
  
  fch.setToBegin();
  //
  // (4,2) -> (10,2) -> (7,5) -> (7,8)
  //  ^
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 8 );
  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 4
  CPPUNIT_ASSERT( fch.size() == 4 );
  // There is a next point
  CPPUNIT_ASSERT( fch.hasNext() );
  // No previous point
  CPPUNIT_ASSERT( !(fch.hasPrevious()) );
}

// -------------------------------------------------------------------

void
FreemanChainTest::testMoveNext()
{
  // A Freeman chain
  //
  // (4,2) -> (10,2) -> (7,5)
  //  ^
  FreemanChain fch(Point(4,2));
  fch.push_back(Point(10,2));
  fch.push_back(Point(7,5));

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 3
  CPPUNIT_ASSERT( fch.size() == 3 );
  // Front, current and last points are correctly set
  Point ipf = fch.front();
  Point ipc = fch.current();
  Point ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 5 );
  // There is a next point
  CPPUNIT_ASSERT( fch.hasNext() );
  // No previous point
  CPPUNIT_ASSERT( !(fch.hasPrevious()) );

  fch.moveNext();
  //
  // (4,2) -> (10,2) -> (7,5)
  //           ^
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 10 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 5 );
  // There is a next point
  CPPUNIT_ASSERT( fch.hasNext() );
  // There is a previous point
  CPPUNIT_ASSERT( fch.hasPrevious() );
  
  fch.moveNext();
  //
  // (4,2) -> (10,2) -> (7,5)
  //                     ^
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 5 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 5 );
  // No next point
  CPPUNIT_ASSERT( !(fch.hasNext()) );
  // There is a previous point
  CPPUNIT_ASSERT( fch.hasPrevious() );
}

// -------------------------------------------------------------------

void
FreemanChainTest::testMovePrevious()
{
  // A Freeman chain
  //
  // (4,2) -> (10,2) -> (7,5)
  //                     ^
  FreemanChain fch(Point(4,2));
  fch.push_back(Point(10,2));
  fch.push_back(Point(7,5));
  fch.setToEnd();

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 3
  CPPUNIT_ASSERT( fch.size() == 3 );
  // Front, current and last points are correctly set
  Point ipf = fch.front();
  Point ipc = fch.current();
  Point ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 5 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 5 );
  // No next point
  CPPUNIT_ASSERT( !(fch.hasNext()) );
  // There is a previous point
  CPPUNIT_ASSERT( fch.hasPrevious() );

  fch.movePrevious();
  //
  // (4,2) -> (10,2) -> (7,5)
  //           ^
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 10 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 5 );
  // There is a next point
  CPPUNIT_ASSERT( fch.hasNext() );
  // There is a previous point
  CPPUNIT_ASSERT( fch.hasPrevious() );
  
  fch.movePrevious();
  //
  // (4,2) -> (10,2) -> (7,5)
  //  ^
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 5 );
  // There is a next point
  CPPUNIT_ASSERT( fch.hasNext() );
  // No previous point
  CPPUNIT_ASSERT( !(fch.hasPrevious()) );
}

// -------------------------------------------------------------------

void
FreemanChainTest::testNext()
{
  // A Freeman chain
  //
  // (4,2) -> (10,2) -> (7,5)
  //  ^
  FreemanChain fch(Point(4,2));
  fch.push_back(Point(10,2));
  fch.push_back(Point(7,5));

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 3
  CPPUNIT_ASSERT( fch.size() == 3 );
  // Front, current and last points are correctly set
  Point ipf = fch.front();
  Point ipc = fch.current();
  Point ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 5 );
  // There is a next point
  CPPUNIT_ASSERT( fch.hasNext() );
  // No previous point
  CPPUNIT_ASSERT( !(fch.hasPrevious()) );

  Point ipn = fch.next();
  //
  // (4,2) -> (10,2) -> (7,5)
  //           ^
  // Returned point is correct
  CPPUNIT_ASSERT_EQUAL( ipn.x(), 10 );
  CPPUNIT_ASSERT_EQUAL( ipn.y(), 2 );
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 10 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 5 );
  // There is a next point
  CPPUNIT_ASSERT( fch.hasNext() );
  // There is a previous point
  CPPUNIT_ASSERT( fch.hasPrevious() );
  
  const Point& ipN = fch.accessNext();
  //
  // (4,2) -> (10,2) -> (7,5)
  //                     ^
  // Returned point is correct
  CPPUNIT_ASSERT_EQUAL( ipN.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipN.y(), 5 );
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 5 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 5 );
  // No next point
  CPPUNIT_ASSERT( !(fch.hasNext()) );
  // There is a previous point
  CPPUNIT_ASSERT( fch.hasPrevious() );
}

// -------------------------------------------------------------------

void
FreemanChainTest::testPrevious()
{
  // A Freeman chain
  //
  // (4,2) -> (10,2) -> (7,5)
  //                     ^
  FreemanChain fch(Point(4,2));
  fch.push_back(Point(10,2));
  fch.push_back(Point(7,5));
  fch.setToEnd();

  // Chain is not empty
  CPPUNIT_ASSERT( !(fch.empty()) );
  // Chain size == 3
  CPPUNIT_ASSERT( fch.size() == 3 );
  // Front, current and last points are correctly set
  Point ipf = fch.front();
  Point ipc = fch.current();
  Point ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 5 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 5 );
  // No next point
  CPPUNIT_ASSERT( !(fch.hasNext()) );
  // There is a previous point
  CPPUNIT_ASSERT( fch.hasPrevious() );

  Point ipp = fch.previous();
  //
  // (4,2) -> (10,2) -> (7,5)
  //           ^
  // Returned point is correct
  CPPUNIT_ASSERT_EQUAL( ipp.x(), 10 );
  CPPUNIT_ASSERT_EQUAL( ipp.y(), 2 );
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 10 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 5 );
  // There is a next point
  CPPUNIT_ASSERT( fch.hasNext() );
  // There is a previous point
  CPPUNIT_ASSERT( fch.hasPrevious() );
  
  const Point& ipP = fch.accessPrevious();
  //
  // (4,2) -> (10,2) -> (7,5)
  //  ^
  // Returned point is correct
  CPPUNIT_ASSERT_EQUAL( ipP.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipP.y(), 2 );
  // Front, current and last points are correctly set
  ipf = fch.front();
  ipc = fch.current();
  ipb = fch.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 5 );
  // There is a next point
  CPPUNIT_ASSERT( fch.hasNext() );
  // No previous point
  CPPUNIT_ASSERT( !(fch.hasPrevious()) );
}

// -------------------------------------------------------------------

void
FreemanChainTest::testToPointList()
{
  // CHAIN INCLUDING ONE POINT
  // -------------------------
  //
  // (4,2)
  //  ^
  FreemanChain fch1(Point(4,2));
  std::list<Point> lp = fch1.toPointList();

  // The chain includes one point
  CPPUNIT_ASSERT( fch1.size() == 1 );
  // Front, current and last points are correctly set
  Point ipf = fch1.front();
  Point ipc = fch1.current();
  Point ipb = fch1.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 2 );

  // The list includes one point
  CPPUNIT_ASSERT( lp.size() == 1 );
  ipf = lp.front();
  ipb = lp.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 2 );

  // CHAIN INCLUDING AT LEAST TWO POINTS
  // -----------------------------------
  //
  // (4,2) -> (10,2) -> (7,5) -> (7,8)
  //  ^
  FreemanChain fch4(Point(4,2));
  fch4.push_back(Point(10,2));
  fch4.push_back(Point(7,5));
  fch4.push_back(Point(7,8));
  lp = fch4.toPointList();

  // The resulting list contains the points described by the chain
  CPPUNIT_ASSERT( lp.size() == 4 );

  std::list<Point>::iterator itlp = lp.begin();

  ipc = *itlp;
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );

  itlp++;
  ipc = *itlp;
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 10 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );

  itlp++;
  ipc = *itlp;
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 5 );

  itlp++;
  ipc = *itlp;
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 8 );
}

// -------------------------------------------------------------------

void
FreemanChainTest::testReverse()
{
  // CHAIN INCLUDING ONE POINT
  // -------------------------
  //
  // (4,2)
  //  ^
  FreemanChain fch1(Point(4,2));
  // The chain includes one point
  CPPUNIT_ASSERT( fch1.size() == 1 );
  // Front, current and last points are correctly set
  Point ipf = fch1.front();
  Point ipc = fch1.current();
  Point ipb = fch1.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 2 );

  fch1.reverse();
  // The chain still includes one point
  CPPUNIT_ASSERT( fch1.size() == 1 );
  // Front, current and last points are correctly set
  ipf = fch1.front();
  ipc = fch1.current();
  ipb = fch1.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 2 );

  // Check codes in chain
  const std::list<FreemanCode>& lfc = fch1.accessCodesList();
  std::list<FreemanCode>::const_iterator it = lfc.begin();
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 0 );

  // CHAIN INCLUDING TWO POINTS
  // --------------------------
  //
  // (4,2) -> (10,2)
  //  ^
  FreemanChain fch2(Point(4,2));
  fch2.push_back(Point(10,2));

  fch2.reverse();
  //
  // (10,2) -> (4,2)
  //  ^
  // The chain still includes 2 points
  CPPUNIT_ASSERT( fch2.size() == 2 );
  // Internal iterator is preserved,
  // front, current and last points are correctly set
  ipf = fch2.front();
  ipc = fch2.current();
  ipb = fch2.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 10 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 10 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 2 );

  // Points are correctly ordered
  fch2.setToBegin();
  ipc = fch2.current();
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 10 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  ipc = fch2.next();
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT( !(fch2.hasNext()) );

  // Check codes in chain
  const std::list<FreemanCode>& lfc1 = fch2.accessCodesList();
  it = lfc1.begin();
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 0 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_W );
  CPPUNIT_ASSERT_EQUAL( it->length(), 6 );


  // CHAIN INCLUDING AN ODD NUMBER OF POINTS (5)
  // -------------------------------------------
  //
  // (4,2) -> (10,2) -> (6,6) -> (6,9) -> (11,4)
  //                              ^
  FreemanChain fch4(Point(4,2));
  fch4.push_back(Point(10,2));
  fch4.push_back(Point(6,6));
  fch4.push_back(Point(6,9));
  fch4.push_back(Point(11,4));
  fch4.moveNext();
  fch4.moveNext();
  fch4.moveNext();

  fch4.reverse();
  //
  // (11,4) -> (6,9) -> (6,6) -> (10,2) -> (4,2)
  //                              ^
  // The chain still includes 5 points
  CPPUNIT_ASSERT( fch4.size() == 5 );
  // Internal iterator is preserved,
  // front, current and last points are correctly set
  ipf = fch4.front();
  ipc = fch4.current();
  ipb = fch4.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 11 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 10 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 2 );

  // Points are correctly ordered
  fch4.setToBegin();
  ipc = fch4.current();
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 11 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 4 );
  ipc = fch4.next();
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 6 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 9 );
  ipc = fch4.next();
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 6 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 6 );
  ipc = fch4.next();
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 10 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  ipc = fch4.next();
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );

  // Check codes in chain
  const std::list<FreemanCode>& lfc2 = fch4.accessCodesList();
  it = lfc2.begin();
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 0 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_SW );
  CPPUNIT_ASSERT_EQUAL( it->length(), 5 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 3 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_NE );
  CPPUNIT_ASSERT_EQUAL( it->length(), 4 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_W );
  CPPUNIT_ASSERT_EQUAL( it->length(), 6 );
}

// -------------------------------------------------------------------

void
FreemanChainTest::testCopyConstructor()
{
  // CHAIN INCLUDING ONE POINT
  // -------------------------
  //
  // (4,2)
  //  ^
  FreemanChain fch1(Point(4,2));

  FreemanChain cfch1(fch1);
  // The chain includes one point too
  CPPUNIT_ASSERT( cfch1.size() == 1 );
  // Front, current and last points are correctly set
  Point ipf = cfch1.front();
  Point ipc = cfch1.current();
  Point ipb = cfch1.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 2 );

  // Check codes in chain
  const std::list<FreemanCode>& lfc1 = fch1.accessCodesList();
  std::list<FreemanCode>::const_iterator it = lfc1.begin();
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 0 );

  // CHAIN INCLUDING AT LEAST TWO POINTS
  // -----------------------------------
  //
  // (4,2) -> (10,2) -> (7,5) -> (7,8)
  //           ^
  FreemanChain fch4(Point(4,2));
  fch4.push_back(Point(10,2));
  fch4.push_back(Point(7,5));
  fch4.push_back(Point(7,8));
  fch4.moveNext();

  FreemanChain cfch4(fch4);
  // The copy includes 4 points
  CPPUNIT_ASSERT( fch4.size() == 4 );
  // Internal iterator is preserved,
  // front, current and last points are correctly set
  ipf = fch4.front();
  ipc = fch4.current();
  ipb = fch4.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 10 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 8 );

  // Points are correctly copied
  fch4.setToBegin();

  ipc = fch4.current();
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  ipc = fch4.next();
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 10 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  ipc = fch4.next();
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 5 );
  ipc = fch4.next();
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 8 );

  // Check codes in chain
  const std::list<FreemanCode>& lfc4 = fch4.accessCodesList();
  it = lfc4.begin();
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 0 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_E );
  CPPUNIT_ASSERT_EQUAL( it->length(), 6 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_SW );
  CPPUNIT_ASSERT_EQUAL( it->length(), 3 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_S );
  CPPUNIT_ASSERT_EQUAL( it->length(), 3 );
}

// -------------------------------------------------------------------

void
FreemanChainTest::testAssignment()
{
  // CHAIN INCLUDING ONE POINT
  // -------------------------
  //
  // (4,2)
  //  ^
  FreemanChain fch1(Point(4,2));

  FreemanChain cfch1 = fch1;
  // The chain includes one point too
  CPPUNIT_ASSERT( cfch1.size() == 1 );
  // Front, current and last points are correctly set
  Point ipf = cfch1.front();
  Point ipc = cfch1.current();
  Point ipb = cfch1.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 2 );

  // Check codes in chain
  const std::list<FreemanCode>& lfc1 = cfch1.accessCodesList();
  std::list<FreemanCode>::const_iterator it = lfc1.begin();
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 0 );

  // CHAIN INCLUDING AT LEAST TWO POINTS
  // -----------------------------------
  //
  // (4,2) -> (10,2) -> (7,5) -> (7,8)
  //                     ^
  FreemanChain fch4(Point(4,2));
  fch4.push_back(Point(10,2));
  fch4.push_back(Point(7,5));
  fch4.push_back(Point(7,8));
  fch4.moveNext();
  fch4.moveNext();

  FreemanChain cfch4 = fch4;
  // The copy includes 4 points
  CPPUNIT_ASSERT( fch4.size() == 4 );
  // Internal iterator is preserved,
  // front, current and last points are correctly set
  ipf = fch4.front();
  ipc = fch4.current();
  ipb = fch4.back();
  CPPUNIT_ASSERT_EQUAL( ipf.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipf.y(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 5 );
  CPPUNIT_ASSERT_EQUAL( ipb.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipb.y(), 8 );

  // Points are correctly copied
  fch4.setToBegin();
  ipc = fch4.current();
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  ipc = fch4.next();
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 10 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  ipc = fch4.next();
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 5 );
  ipc = fch4.next();
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 7 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 8 );

  // Check codes in chain
  const std::list<FreemanCode>& lfc4 = cfch4.accessCodesList();
  it = lfc4.begin();
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_N );
  CPPUNIT_ASSERT_EQUAL( it->length(), 0 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_E );
  CPPUNIT_ASSERT_EQUAL( it->length(), 6 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_SW );
  CPPUNIT_ASSERT_EQUAL( it->length(), 3 );
  it++;
  CPPUNIT_ASSERT_EQUAL( it->direction(), QGE_DIRECTION_S );
  CPPUNIT_ASSERT_EQUAL( it->length(), 3 );
}

// -------------------------------------------------------------------

//void
//FreemanChainTest::testMerge()
//{
//  /* CPPUNIT_FAIL("Not implemented"); */
//}

// -------------------------------------------------------------------
