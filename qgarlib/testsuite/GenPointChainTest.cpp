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
 * @file  GenPointChainTest.cpp
 * @brief Implementation of class GenPointChainTest
 *
 *        See file GenPointChainTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 16, 2003  15:45
 * @since  Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenPointChainTest.cpp,v 1.4 2005/01/28 15:56:46 masini Exp $ */



// QGAR
#include <qgarlib/GenPointChain.h>
#include <qgarlib/primitives.h>
// QGAR TESTS
#include "GenPointChainTest.h"



using namespace qgar;



// ------------------------------------------------------------------
// T E S T F I X T U R E   I M P L
// ------------------------------------------------------------------

void
GenPointChainTest::setUp()
{
  _ip1.setXY(1, 1);
  _ip2.setXY(2, 2);
  _ip3.setXY(3, 3);
  _ip4.setXY(4, 4);

  _fp1.setXY(1., 1.);
  _fp2.setXY(2., 2.);
  _fp3.setXY(3., 3.);
  _fp4.setXY(4., 4.);

  _dp1.setXY(1., 1.);
  _dp2.setXY(2., 2.);
  _dp3.setXY(3., 3.);
  _dp4.setXY(4., 4.);
}

// -------------------------------------------------------------------

void
GenPointChainTest::tearDown()
{
  /* EMPTY */
}


// -------------------------------------------------------------------
// T E S T   F U N C T I O N S
// -------------------------------------------------------------------

void
GenPointChainTest::testEmpty()
{
  /* NO TEST */
}

// -------------------------------------------------------------------

void
GenPointChainTest::testSize()
{
  /* NO TEST */
}

// -------------------------------------------------------------------

void
GenPointChainTest::testFront()
{
  /* NO TEST */
}

// -------------------------------------------------------------------

void
GenPointChainTest::testBack()
{
  /* NO TEST */
}

// ----------------------------------------------------------------------

void
GenPointChainTest::testSetToBegin()
{
  /* NO TEST */
}

// -------------------------------------------------------------------
// -------------------------------------------------------------------

void
GenPointChainTest::testDefaultConstructor()
{
  // A chain of integer points
  PointChain ich;
  CPPUNIT_ASSERT( ich.empty() );

  // A chain of float points
  FPointChain fch;
  CPPUNIT_ASSERT( fch.empty() );

  // A chain of double points
  DPointChain dch;
  CPPUNIT_ASSERT( dch.empty() );
}

// -------------------------------------------------------------------

void
GenPointChainTest::testBuildFromPoint()
{
  // A chain of integer points
  PointChain ich(_ip1);
  CPPUNIT_ASSERT_EQUAL( ich.size(), 1 );  
  Point p = ich.front();
  CPPUNIT_ASSERT_EQUAL( p.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( p.y(), 1 );

  // A chain of float points
  FPointChain fch(_fp1);
  CPPUNIT_ASSERT_EQUAL( fch.size(), 1 );  
  FPoint fp = fch.back();
  CPPUNIT_ASSERT_EQUAL( fp.x(), 1.0F );
  CPPUNIT_ASSERT_EQUAL( fp.y(), 1.0F );

  // A chain of double points
  DPointChain dch(_dp1);
  CPPUNIT_ASSERT_EQUAL( dch.size(), 1 );  
  DPoint dp = dch.front();
  CPPUNIT_ASSERT_EQUAL( dp.x(), 1. );
  CPPUNIT_ASSERT_EQUAL( dp.y(), 1. );
}

// -------------------------------------------------------------------

void
GenPointChainTest::testPush_front()
{
  // A chain of integer points
  PointChain ich(_ip1);

  ich.push_front(_ip2);
  // Check first and last points
  Point ip = ich.front();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 2 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 2 );
  ip = ich.back();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 1 );

  ich.push_front(_ip3);
  // Check first and last points
  ip = ich.front();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 3 );
  ip = ich.back();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 1 );
}

// -------------------------------------------------------------------

void
GenPointChainTest::testPush_back()
{
 // A chain of integer points
  PointChain ich(_ip1);

  ich.push_back(_ip2);
  // Check first and last points
  Point ip = ich.front();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 1 );
  ip = ich.back();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 2 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 2 );

  ich.push_back(_ip3);
  // Check first and last points
  ip = ich.front();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 1 );
  ip = ich.back();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 3 );
}

// -------------------------------------------------------------------

void
GenPointChainTest::testAccessFront()
{
  // A chain of integer points
  PointChain ich(_ip1);
  ich.push_front(_ip2);
  ich.push_back(_ip3);
  Point ip = ich.accessFront();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 2 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 2 );

  // A chain of float points
  FPointChain fch(_fp1);
  fch.push_back(_fp2);
  fch.push_front(_fp2);
  fch.push_front(_fp3);
  FPoint fp = fch.accessFront();
  CPPUNIT_ASSERT_EQUAL( fp.x(), 3.0F );
  CPPUNIT_ASSERT_EQUAL( fp.y(), 3.0F );
}

// -------------------------------------------------------------------

void
GenPointChainTest::testToPointList()
{
  PointChain ich(_ip1);
  ich.push_back(_ip2);
  ich.push_back(_ip3);
  ich.push_back(_ip4);
  ich.push_back(_ip1);

  // Get list of points
  const std::list<Point> ptl = ich.toPointList();
  // Check points in list
  std::list<Point>::const_iterator itp = ptl.begin();
  //
  // (1,1) -> (2,2) -> (3,3) -> (4,4) -> (1,1) -> NIL
  //  ^
  CPPUNIT_ASSERT_EQUAL( (*itp).x(), 1 );
  CPPUNIT_ASSERT_EQUAL( (*itp).y(), 1 );
  //
  // (1,1) -> (2,2) -> (3,3) -> (4,4) -> (1,1) -> NIL
  //           ^
  itp++;
  CPPUNIT_ASSERT_EQUAL( (*itp).x(), 2 );
  CPPUNIT_ASSERT_EQUAL( (*itp).y(), 2 );
  //
  // (1,1) -> (2,2) -> (3,3) -> (4,4) -> (1,1) -> NIL
  //                    ^
  itp++;
  CPPUNIT_ASSERT_EQUAL( (*itp).x(), 3 );
  CPPUNIT_ASSERT_EQUAL( (*itp).y(), 3 );
  //
  // (1,1) -> (2,2) -> (3,3) -> (4,4) -> (1,1) -> NIL
  //                             ^
  itp++;
  CPPUNIT_ASSERT_EQUAL( (*itp).x(), 4 );
  CPPUNIT_ASSERT_EQUAL( (*itp).y(), 4 );
  //
  // (1,1) -> (2,2) -> (3,3) -> (4,4) -> (1,1) -> NIL
  //                                      ^
  itp++;
  CPPUNIT_ASSERT_EQUAL( (*itp).x(), 1 );
  CPPUNIT_ASSERT_EQUAL( (*itp).y(), 1 );
  //
  // (1,1) -> (2,2) -> (3,3) -> (4,4) -> (1,1) -> NIL
  //                                              ^  
  itp++;
  CPPUNIT_ASSERT( itp == ptl.end() );
}

// -------------------------------------------------------------------

void
GenPointChainTest::testAccessPointList()
{
  // (1,1) -> (2,2) -> (3,3) -> (2,2) -> (1,1)
  //
  PointChain ich(_ip1);
  ich.push_back(_ip2);
  ich.push_back(_ip3);
  ich.push_back(_ip2);
  ich.push_back(_ip1);

  // Get list of points
  const std::list<Point>& ptl= ich.accessPointList();
  // Check points in list
  std::list<Point>::const_iterator itp = ptl.begin();
  CPPUNIT_ASSERT_EQUAL( (*itp).x(), 1 );
  CPPUNIT_ASSERT_EQUAL( (*itp).y(), 1 );

  itp++;
  CPPUNIT_ASSERT_EQUAL( (*itp).x(), 2 );
  CPPUNIT_ASSERT_EQUAL( (*itp).y(), 2 );

  itp++;
  CPPUNIT_ASSERT_EQUAL( (*itp).x(), 3 );
  CPPUNIT_ASSERT_EQUAL( (*itp).y(), 3 );

  itp++;
  CPPUNIT_ASSERT_EQUAL( (*itp).x(), 2 );
  CPPUNIT_ASSERT_EQUAL( (*itp).y(), 2 );

  itp++;
  CPPUNIT_ASSERT_EQUAL( (*itp).x(), 1 );
  CPPUNIT_ASSERT_EQUAL( (*itp).y(), 1 );

  itp++;
  CPPUNIT_ASSERT( itp == ptl.end() );
}

// -------------------------------------------------------------------

void
GenPointChainTest::testNext()
{
  // (2,2) -> (1,1) -> (3,3)
  //  ^
  PointChain i3ch(_ip2); // Iterator should point to the beginning
  i3ch.push_back(_ip1);
  i3ch.push_back(_ip3);
  
  // (2,2) -> (1,1) -> (3,3)
  //           ^
  Point ip = i3ch.next();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 1 );

  // (2,2) -> (1,1) -> (3,3)
  //                    ^
  ip = i3ch.next();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 3 );


  i3ch.setToBegin();
  // (2,2) -> (1,1) -> (3,3)
  //           ^
  ip = i3ch.next();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 1 );

  // (2,2) -> (1,1) -> (3,3)
  //                    ^
  ip = i3ch.next();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 3 );
}

// -------------------------------------------------------------------

void
GenPointChainTest::testAccessNext()
{
  // (2,2) -> (1,1) -> (3,3)
  //  ^
  PointChain i3ch(_ip2); // Iterator should point to the beginning
  i3ch.push_back(_ip1);
  i3ch.push_back(_ip3);
  
  // (2,2) -> (1,1) -> (3,3)
  //           ^
  const Point& ip1 = i3ch.accessNext();
  CPPUNIT_ASSERT_EQUAL( ip1.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ip1.y(), 1 );

  // (2,2) -> (1,1) -> (3,3)
  //                    ^
  const Point& ip3 = i3ch.accessNext();
  CPPUNIT_ASSERT_EQUAL( ip3.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ip3.y(), 3 );


  i3ch.setToBegin();
  // (2,2) -> (1,1) -> (3,3)
  //           ^
  const Point& ip11 = i3ch.accessNext();
  CPPUNIT_ASSERT_EQUAL( ip11.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ip11.y(), 1 );

  // (2,2) -> (1,1) -> (3,3)
  //                    ^
  const Point& ip33 = i3ch.accessNext();
  CPPUNIT_ASSERT_EQUAL( ip33.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ip33.y(), 3 );
}

// -------------------------------------------------------------------

void
GenPointChainTest::testPrevious()
{
  // (1,1) -> (3,3) -> (2,2)
  //  ^
  PointChain i3ch(_ip1);
  i3ch.push_back(_ip3);
  i3ch.push_back(_ip2);

  // Check points
  //
  // (1,1) -> (3,3) -> (2,2)
  //           ^
  i3ch.setToEnd();
  Point ip = i3ch.previous();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 3 );
  //
  // (1,1) -> (3,3) -> (2,2)
  //  ^
  ip = i3ch.previous();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 1 );
}

// -------------------------------------------------------------------

void
GenPointChainTest::testAccessPrevious()
{
  // (1,1) -> (3,3) -> (2,2)
  //  ^
  PointChain i3ch(_ip1);
  i3ch.push_back(_ip3);
  i3ch.push_back(_ip2);

  // Check points
  //
  // (1,1) -> (3,3) -> (2,2)
  //           ^
  i3ch.setToEnd();
  const Point& ip3 = i3ch.accessPrevious();
  CPPUNIT_ASSERT_EQUAL( ip3.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ip3.y(), 3 );
  //
  // (1,1) -> (3,3) -> (2,2)
  //  ^
  const Point& ip1 = i3ch.accessPrevious();
  CPPUNIT_ASSERT_EQUAL( ip1.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ip1.y(), 1 );
}

// -------------------------------------------------------------------

void
GenPointChainTest::testCurrent()
{
  // Chain of 4 points
  PointChain i4ch(_ip1);
  i4ch.push_front(_ip3);
  i4ch.push_back(_ip2);
  i4ch.push_back(_ip4);
  // Iterator should point to first pushed point
  //
  // (3,3) -> (1,1) -> (2,2) -> (4,4)
  //           ^
  Point ip = i4ch.current();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 1 );

  // Move through the chain and check points
  //
  // (3,3) -> (1,1) -> (2,2) -> (4,4)
  //                             ^
  i4ch.setToEnd();
  Point ipc = i4ch.current();
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 4 );
  //
  // (3,3) -> (1,1) -> (2,2) -> (4,4)
  //                    ^
  Point ipp = i4ch.previous();
  CPPUNIT_ASSERT_EQUAL( ipp.x(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipp.y(), 2 );
  ipc = i4ch.current();
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  //
  // (3,3) -> (1,1) -> (2,2) -> (4,4)
  //           ^
  ipp = i4ch.previous();
  CPPUNIT_ASSERT_EQUAL( ipp.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ipp.y(), 1 );
  ipc = i4ch.current();
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 1 );
  //
  // (3,3) -> (1,1) -> (2,2) -> (4,4)
  //  ^
  ipp = i4ch.previous();
  CPPUNIT_ASSERT_EQUAL( ipp.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ipp.y(), 3 );
  ipc = i4ch.current();
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 3 );
  //
  // (3,3) -> (1,1) -> (2,2) -> (4,4)
  //           ^
  ipp = i4ch.next();
  CPPUNIT_ASSERT_EQUAL( ipp.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ipp.y(), 1 );
  ipc = i4ch.current();
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 1 );
  //
  // (3,3) -> (1,1) -> (2,2) -> (4,4)
  //                    ^
  ipp = i4ch.next();
  CPPUNIT_ASSERT_EQUAL( ipp.x(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipp.y(), 2 );
  ipc = i4ch.current();
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  //
  // (3,3) -> (1,1) -> (2,2) -> (4,4)
  //           ^
  ipp = i4ch.previous();
  CPPUNIT_ASSERT_EQUAL( ipp.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ipp.y(), 1 );
  ipc = i4ch.current();
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 1 );
  //
  // (3,3) -> (1,1) -> (2,2) -> (4,4)
  //                    ^
  ipp = i4ch.next();
  CPPUNIT_ASSERT_EQUAL( ipp.x(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipp.y(), 2 );
  ipc = i4ch.current();
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 2 );
  //
  // (3,3) -> (1,1) -> (2,2) -> (4,4)
  //                             ^
  ipp = i4ch.next();
  CPPUNIT_ASSERT_EQUAL( ipp.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipp.y(), 4 );
  ipc = i4ch.current();
  CPPUNIT_ASSERT_EQUAL( ipc.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ipc.y(), 4 );
}

// -------------------------------------------------------------------

void
GenPointChainTest::testAccessCurrent()
{
  // Chain of 4 points
  PointChain i4ch(_ip1);
  i4ch.push_front(_ip3);
  i4ch.push_back(_ip2);
  i4ch.push_back(_ip1);
  // Iterator should point to first pushed point
  //
  // (3,3) -> (1,1) -> (2,2) -> (1,1)
  //           ^
  const Point& ip = i4ch.accessCurrent();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 1 );

  // Move through the chain and check points
  i4ch.setToBegin();
  //
  // (3,3) -> (1,1) -> (2,2) -> (1,1)
  //  ^
  const Point& ip3 = i4ch.accessCurrent();
  CPPUNIT_ASSERT_EQUAL( ip3.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ip3.y(), 3 );
  //
  // (3,3) -> (1,1) -> (2,2) -> (1,1)
  //           ^
  Point ipn = i4ch.next();
  CPPUNIT_ASSERT_EQUAL( ipn.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ipn.y(), 1 );
  const Point& ip1 = i4ch.accessCurrent();
  CPPUNIT_ASSERT_EQUAL( ip1.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ip1.y(), 1 );
  //
  // (3,3) -> (1,1) -> (2,2) -> (1,1)
  //                    ^
  ipn = i4ch.next();
  CPPUNIT_ASSERT_EQUAL( ipn.x(), 2 );
  CPPUNIT_ASSERT_EQUAL( ipn.y(), 2 );
  const Point& ip4 = i4ch.accessCurrent();
  CPPUNIT_ASSERT_EQUAL( ip4.x(), 2 );
  CPPUNIT_ASSERT_EQUAL( ip4.y(), 2 );
  //
  // (3,3) -> (1,1) -> (2,2) -> (1,1)
  //                             ^
  ipn = i4ch.next();
  CPPUNIT_ASSERT_EQUAL( ipn.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ipn.y(), 1 );
  const Point& ip11 = i4ch.current();
  CPPUNIT_ASSERT_EQUAL( ip11.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ip11.y(), 1 );
}

// ----------------------------------------------------------------------

void
GenPointChainTest::testSetToEnd()
{
 // A chain of integer points
  PointChain ich(_ip1);
  ich.push_back(_ip2);

  ich.setToEnd();
  //
  // (1,1) -> (2,2)
  //           ^
  Point ip = ich.current();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 2 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 2 );
  
  ich.push_back(_ip3);
  //
  // (1,1) -> (2,2) -> (3,3)
  //                    ^
  ich.setToEnd();
  ip = ich.current();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 3 );

  ich.push_back(_ip1);
  ich.push_back(_ip4);
  //
  // (1,1) -> (2,2) -> (3,3) -> (1,1) -> (4,4)
  //                                      ^
  ich.setToEnd();
  ip = ich.current();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 4 );

}

// -------------------------------------------------------------------

void
GenPointChainTest::testMoveNext()
{
  // Chain of 4 points
  PointChain i4ch(_ip1);
  i4ch.push_back(_ip2);
  i4ch.push_back(_ip3);
  i4ch.push_back(_ip4);
  // Iterator should point to first point
  //
  // (1,1) -> (2,2) -> (3,3) -> (4,4)
  //  ^
  Point ip = i4ch.current();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 1 );

  // Move through the chain and check points
  //
  // (1,1) -> (2,2) -> (3,3) -> (4,4)
  //           ^
  i4ch.moveNext();
  ip = i4ch.current();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 2 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 2 );
  //
  // (1,1) -> (2,2) -> (3,3) -> (4,4)
  //                    ^
  i4ch.moveNext();
  ip = i4ch.current();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 3 );
  //
  // (1,1) -> (2,2) -> (3,3) -> (4,4)
  //                             ^
  i4ch.moveNext();
  ip = i4ch.current();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 4 );
}

// -------------------------------------------------------------------

void
GenPointChainTest::testMovePrevious()
{
  // Chain of 4 points
  PointChain i4ch(_ip4);
  i4ch.push_front(_ip3);
  i4ch.push_front(_ip2);
  i4ch.push_front(_ip1);
  // Iterator should point to last point
  //
  // (1,1) -> (2,2) -> (3,3) -> (4,4)
  //                             ^
  Point ip = i4ch.current();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 4 );

  i4ch.setToEnd();
  // Move through the chain and check points
  //
  // (1,1) -> (2,2) -> (3,3) -> (4,4)
  //                    ^
  i4ch.movePrevious();
  ip = i4ch.current();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 3 );
  //
  // (1,1) -> (2,2) -> (3,3) -> (4,4)
  //                    ^
  i4ch.movePrevious();
  ip = i4ch.current();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 2 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 2 );
  //
  // (1,1) -> (2,2) -> (3,3) -> (4,4)
  //                             ^
  i4ch.movePrevious();
  ip = i4ch.current();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 1 );
}

// -------------------------------------------------------------------

void
GenPointChainTest::testHasNext()
{
  // Chain of 1 point
  PointChain i1ch(_ip1);
  CPPUNIT_ASSERT( !(i1ch.hasNext()) );

  PointChain i4ch(_ip1);
  i4ch.push_front(_ip3);
  i4ch.push_back(_ip2);
  i4ch.push_back(_ip1);

  i4ch.setToBegin();
  //
  // (3,3) -> (1,1) -> (2,2) -> (1,1)
  //  ^
  CPPUNIT_ASSERT( i4ch.hasNext() );
  //
  // (3,3) -> (1,1) -> (2,2) -> (1,1)
  //           ^
  Point ip = i4ch.next();
  CPPUNIT_ASSERT( i4ch.hasNext() );
  //
  // (3,3) -> (1,1) -> (2,2) -> (1,1)
  //                    ^
  ip = i4ch.next();
  CPPUNIT_ASSERT( i4ch.hasNext() );
  //
  // (3,3) -> (1,1) -> (2,2) -> (1,1)
  //                             ^
  ip = i4ch.next();
  CPPUNIT_ASSERT( !(i4ch.hasNext()) );
}

// -------------------------------------------------------------------

void
GenPointChainTest::testHasPrevious()
{
  // Chain of 1 point
  PointChain i1ch(_ip1);
  CPPUNIT_ASSERT( !(i1ch.hasPrevious()) );

  // Chain of 4 points
  //
  // (3,3) -> (1,1) -> (2,2) -> (1,1)
  //           ^
  PointChain i4ch(_ip1);
  i4ch.push_front(_ip3);
  i4ch.push_back(_ip2);
  i4ch.push_back(_ip1);

 i4ch.setToEnd();
  //
  // (3,3) -> (1,1) -> (2,2) -> (1,1)
  //                             ^
  CPPUNIT_ASSERT( i4ch.hasPrevious() );
  //
  // (3,3) -> (1,1) -> (2,2) -> (1,1)
  //                    ^
  Point ip = i4ch.previous();
  CPPUNIT_ASSERT( i4ch.hasPrevious() );
  //
  // (3,3) -> (1,1) -> (2,2) -> (1,1)
  //           ^
  ip = i4ch.previous();
  CPPUNIT_ASSERT( i4ch.hasPrevious() );
  //
  // (3,3) -> (1,1) -> (2,2) -> (1,1)
  //  ^
  ip = i4ch.previous();
  CPPUNIT_ASSERT( !(i4ch.hasPrevious()) );
  //
  // (3,3) -> (1,1) -> (2,2) -> (1,1)
  //           ^
  ip = i4ch.next();
  CPPUNIT_ASSERT( i4ch.hasPrevious() );
}

// -------------------------------------------------------------------

void
GenPointChainTest::testAccessBack()
{
  // A chain of integer points
  PointChain ich(_ip2);
  CPPUNIT_ASSERT_EQUAL( (ich.accessBack()).x(), 2 );
  CPPUNIT_ASSERT_EQUAL( (ich.accessBack()).y(), 2 );
  const Point& rp = ich.accessBack();
  CPPUNIT_ASSERT_EQUAL( rp.x(), 2 );
  CPPUNIT_ASSERT_EQUAL( rp.y(), 2 );

  // A chain of float points
  FPointChain fch(_fp2);
  CPPUNIT_ASSERT_EQUAL( (fch.accessBack()).x(), 2.0F );
  CPPUNIT_ASSERT_EQUAL( (fch.accessBack()).y(), 2.0F );
  const FPoint& rfp = fch.accessBack();
  CPPUNIT_ASSERT_EQUAL( rfp.x(), 2.0F );
  CPPUNIT_ASSERT_EQUAL( rfp.y(), 2.0F );

  // A chain of double points
  DPointChain dch(_dp2);
  CPPUNIT_ASSERT_EQUAL( (dch.accessBack()).x(), 2. );
  CPPUNIT_ASSERT_EQUAL( (dch.accessBack()).y(), 2. );
  const DPoint& rdp = dch.accessBack();
  CPPUNIT_ASSERT_EQUAL( rdp.x(), 2. );
  CPPUNIT_ASSERT_EQUAL( rdp.y(), 2. );
}

// -------------------------------------------------------------------

void
GenPointChainTest::testReverse()
{
  // EMPTY CHAIN
  // -----------
  FPointChain fch;
  CPPUNIT_ASSERT( fch.empty() );
  
  fch.reverse();
  // Check chain is always empty!
  CPPUNIT_ASSERT( fch.empty() );

  // NON-EMPTY CHAINS
  // ----------------

  PointChain ich(_ip1);
  ich.push_back(_ip2);
  ich.push_back(_ip3);
  ich.push_back(_ip4);

  // (1,1) -> (2,2) -> (3,3) -> (4,4)
  //  ^
  ich.setToBegin();
  Point ip =  ich.current();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 1 );
  //
  // (1,1) -> (2,2) -> (3,3) -> (4,4)
  //           ^
  ip = ich.next();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 2 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 2 );
  //
  // (1,1) -> (2,2) -> (3,3) -> (4,4)
  //                    ^
  ip = ich.next();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 3 );
  //
  // (1,1) -> (2,2) -> (3,3) -> (4,4)
  //                             ^
  ip = ich.next();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 4 );
  // Move backward
  //
  // (1,1) -> (2,2) -> (3,3) -> (4,4)
  //                    ^
  ip = ich.previous();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 3 );


  // Reverse the chain
  //
  // (4,4) -> (3,3) -> (2,2) -> (1,1)
  //           ^
  ich.reverse();
  // Iterator remains valid
  Point ipc = ich.current();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 3 );


  // Check points
  ich.setToBegin();
  //
  // (4,4) -> (3,3) -> (2,2) -> (1,1)
  //  ^
  ip = ich.current();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 4 );
  //
  // (4,4) -> (3,3) -> (2,2) -> (1,1)
  //           ^
  ip = ich.next();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 3 );
  //
  // (4,4) -> (3,3) -> (2,2) -> (1,1)
  //                    ^
  ip = ich.next();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 2 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 2 );
  //
  // (4,4) -> (3,3) -> (2,2) -> (1,1)
  //                             ^
  ip = ich.next();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 1 );
}

// -------------------------------------------------------------------

void
GenPointChainTest::testCopyConstructor()
{
  // EMPTY CHAINS
  // ------------
  PointChain ich;
  CPPUNIT_ASSERT( ich.empty() );
  CPPUNIT_ASSERT( ich.size() == 0 );
  
  PointChain iechcop(ich);
  CPPUNIT_ASSERT( iechcop.empty() );
  CPPUNIT_ASSERT( iechcop.size() == 0 );

  // NON-EMPTY CHAINS
  // ----------------

  PointChain i3ch(_ip3);
  i3ch.push_back(_ip1);
  i3ch.push_back(_ip4);
  // Check points in chain
  //
  // (3,3) -> (1,1) -> (4,4)
  //  ^
  i3ch.setToBegin();
  Point ip = i3ch.current();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 3 );
  //
  // (3,3) -> (1,1) -> (4,4)
  //           ^
  ip = i3ch.next();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 1 );
  //
  // (3,3) -> (1,1) -> (4,4)
  //                    ^
  ip = i3ch.next();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 4 );

  // Make a copy
  PointChain ichcop(i3ch);

  // Check iterator points to beginning in copy
  //
  // (3,3) -> (1,1) -> (4,4)
  //  ^
  Point iip = ichcop.current();
  CPPUNIT_ASSERT_EQUAL( iip.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( iip.y(), 3 );
  // Check other points in copy
  //
  // (3,3) -> (1,1) -> (4,4)
  //           ^
  iip = ichcop.next();
  CPPUNIT_ASSERT_EQUAL( iip.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( iip.y(), 1 );
  //
  // (3,3) -> (1,1) -> (4,4)
  //                    ^
  iip = ichcop.next();

  // Check initial chain is not modified
  //
  // (3,3) -> (1,1) -> (4,4)
  //  ^
  i3ch.setToBegin();
  ip = i3ch.current();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 3 );
  //
  // (3,3) -> (1,1) -> (4,4)
  //           ^
  ip = i3ch.next();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 1 );
  //
  // (3,3) -> (1,1) -> (4,4)
  //                    ^
  ip = i3ch.next();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 4 );
}

// -------------------------------------------------------------------

void
GenPointChainTest::testAssignment()
{
  // EMPTY CHAINS
  // ------------
  PointChain ich;
  CPPUNIT_ASSERT( ich.empty() );
  CPPUNIT_ASSERT( ich.size() == 0 );
  
  PointChain iechcop(ich);
  CPPUNIT_ASSERT( iechcop.empty() );
  CPPUNIT_ASSERT( iechcop.size() == 0 );

  // NON-EMPTY CHAINS
  // ----------------

  PointChain i3ch(_ip3);
  i3ch.push_back(_ip1);
  i3ch.push_back(_ip4);
  // Check points in chain
  //
  // (3,3) -> (1,1) -> (4,4)
  //  ^
  i3ch.setToBegin();
  Point ip = i3ch.current();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 3 );
  //
  // (3,3) -> (1,1) -> (4,4)
  //           ^
  ip = i3ch.next();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 1 );
  //
  // (3,3) -> (1,1) -> (4,4)
  //                    ^
  ip = i3ch.next();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 4 );


  // Make a copy
  PointChain ichcop = i3ch;


  // Check iterator points to beginning in copy
  //
  // (3,3) -> (1,1) -> (4,4)
  //  ^
  Point iip = ichcop.current();
  CPPUNIT_ASSERT_EQUAL( iip.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( iip.y(), 3 );
  // Check other points in copy
  //
  // (3,3) -> (1,1) -> (4,4)
  //           ^
  iip = ichcop.next();
  CPPUNIT_ASSERT_EQUAL( iip.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( iip.y(), 1 );
  //
  // (3,3) -> (1,1) -> (4,4)
  //                    ^
  iip = ichcop.next();

  // Check initial chain is not modified
  //
  // (3,3) -> (1,1) -> (4,4)
  //  ^
  i3ch.setToBegin();
  ip = i3ch.current();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 3 );
  //
  // (3,3) -> (1,1) -> (4,4)
  //           ^
  ip = i3ch.next();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 1 );
  //
  // (3,3) -> (1,1) -> (4,4)
  //                    ^
  ip = i3ch.next();
  CPPUNIT_ASSERT_EQUAL( ip.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ip.y(), 4 );
}

// -------------------------------------------------------------------

//void
//GenPointChainTest::testMerge()
//{
//  /* CPPUNIT_FAIL("Not implemented"); */
//}

// -------------------------------------------------------------------
