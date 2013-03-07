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
 * @file  GenPolygonTest.cpp
 * @brief Implementation of class GenPolygonTest
 *
 *        See file GenPolygonTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   March 24, 2004  18:11
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenPolygonTest.cpp,v 1.7 2005/07/13 16:29:34 masini Exp $ */



// STD
#include <deque>
#include <list>
#include <vector>
// QGAR
#include <qgarlib/primitives.h>
// QGAR TESTS
#include "GenPolygonTest.h"



using namespace qgar;
using namespace std;



// ------------------------------------------------------------------
// U N N A M E D   N A M E S P A C E
// ------------------------------------------------------------------


namespace
{


template <class T>
bool
cmp(const deque< GenPoint<T> >& listA, const deque< GenPoint<T> >& listB) 
{
  bool match = true;

  if (listA.size() != listB.size())
    {
      match = false;
    }
  else
    {
      typename deque< GenPoint<T> >::const_iterator itA = listA.begin();
      typename deque< GenPoint<T> >::const_iterator itB = listB.begin();

      while (itA != listA.end() && match)
	{
	  match = ( *itA++ == *itB++ );
	}
    }

  return match;
}


template <class T>
bool
cmp(const GenPolygon<T>& poly1, const GenQgarPolygon<T>& qPoly2)
{
  const deque< GenPoint<T> >& dv1 = poly1.accessVertices();
  const deque< GenPoint<T> >& dv2 = qPoly2.accessVertices();

  bool match = true;

  if ( dv1.size() != dv2.size() )
    {
      match = false;
    }
  else
    {
      typename deque< GenPoint<T> >::const_iterator it1 = dv1.begin();
      typename deque< GenPoint<T> >::const_iterator it2 = dv2.begin();

      while ( it1 != dv1.end() && match )
	{
	  match = ( *it1++ == *it2++ );
	}
    }

  return
        match
    && (poly1.accessSource() == dv1.front())
    && (poly1.accessTarget() == dv1.back())
    && (poly1.accessSource() == qPoly2.accessSource())
    && (poly1.accessTarget() == qPoly2.accessTarget());
}


template <class T>
bool
cmp(const GenPolygon<T>& poly1, const GenPolygon<T>& poly2)
{
  const deque< GenPoint<T> >& dv1 = poly1.accessVertices();
  const deque< GenPoint<T> >& dv2 = poly2.accessVertices();

  bool match = true;

  if ( dv1.size() != dv2.size() )
    {
      match = false;
    }
  else
    {
      typename deque< GenPoint<T> >::const_iterator it1 = dv1.begin();
      typename deque< GenPoint<T> >::const_iterator it2 = dv2.begin();

      while ( it1 != dv1.end() && match )
	{
	  match = ( *it1++ == *it2++ );
	}
    }

  return
        match
    && (poly1.accessSource() == dv1.front())
    && (poly1.accessTarget() == dv1.back())
    && (poly1.accessSource() == poly2.accessSource())
    && (poly1.accessTarget() == poly2.accessTarget());
}


} // unnamed namespace


// ------------------------------------------------------------------
// T E S T    F I X T U R E   I M P L E M E N T A T I O N
// ------------------------------------------------------------------


void
GenPolygonTest::setUp()
{
  // Initialize points

  _iPt0 = IPoint(16, 4);
  _iPt1 = IPoint(-4, -9);
  _iPt2 = IPoint(78, 55);
  _iPt3 = IPoint(-11, 53);

  _fPt0 = FPoint(4.14f, 9.1f);
  _fPt1 = FPoint(-4.46f, -13.59f);
  _fPt2 = FPoint(3.178f, 5.25f);
  _fPt3 = FPoint(-1.11f, 5.173f);

  _dPt0 = DPoint(0.876, 0.298);
  _dPt1 = DPoint(-9.190, -4.894);
  _dPt2 = DPoint(0.84, 37.38);
  _dPt3 = DPoint(-1.0941, 53.984);

  // Initialize lists of point

  _iPtList.push_back(_iPt0);
  _iPtList.push_back(_iPt1);
  _iPtList.push_back(_iPt2);
  _iPtList.push_back(_iPt3);

  _fPtList.push_back(_fPt0);
  _fPtList.push_back(_fPt1);
  _fPtList.push_back(_fPt2);
  _fPtList.push_back(_fPt3);

  _dPtList.push_back(_dPt0);
  _dPtList.push_back(_dPt1);
  _dPtList.push_back(_dPt2);
  _dPtList.push_back(_dPt3);
}


void
GenPolygonTest::tearDown()
{
  /* EMPTY */
}


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


void
GenPolygonTest::testDefaultConstructor()
{
  // ------
  // Set Up
  // ------

  IPolygon iPoly;
  FPolygon fPoly;
  DPolygon dPoly;

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iPoly.accessVertices().empty() );
  CPPUNIT_ASSERT( fPoly.accessVertices().empty() );
  CPPUNIT_ASSERT( dPoly.accessVertices().empty() );
}


void
GenPolygonTest::testCopyConstructor()
{
  // Triangle:  (1,2) (3,4) (5,6)
  //            ^^^^^       ^^^^^
  //            source      target

  list<Point> lp;
  lp.push_back(Point(1,2));
  lp.push_back(Point(3,4));
  lp.push_back(Point(5,6));

  // Create polygon
  Polygon plg(lp);

  // Create copy
  Polygon cplg(plg);

  // Check source and target of copy
  CPPUNIT_ASSERT_EQUAL( cplg.xSource(), 1);
  CPPUNIT_ASSERT_EQUAL( cplg.ySource(), 2);
  CPPUNIT_ASSERT_EQUAL( cplg.xTarget(), 5);
  CPPUNIT_ASSERT_EQUAL( cplg.yTarget(), 6);

  // Check vertices of copy
  const deque<Point>& v = cplg.accessVertices();
  deque<Point>::const_iterator itV = v.begin();
  CPPUNIT_ASSERT_EQUAL( itV->x(), 1);
  CPPUNIT_ASSERT_EQUAL( itV->y(), 2);
  ++itV;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 3);
  CPPUNIT_ASSERT_EQUAL( itV->y(), 4);
  ++itV;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 5);
  CPPUNIT_ASSERT_EQUAL( itV->y(), 6);
}


void
GenPolygonTest::testBuildFromQgarPolygon()
{
  // Triangle:  (1,2) (3,4) (5,6)
  //            ^^^^^       ^^^^^
  //           source       target

  list<Point> lp;
  lp.push_back(Point(1,2));
  lp.push_back(Point(3,4));
  lp.push_back(Point(5,6));

  // Create a Qgar polygon and a geometrical copy
 QgarPolygon plg(lp, 3, QGE_COLOR_WHITE, QGE_OUTLINE_DASH_SS);
 Polygon g(plg);

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( g.xSource(), 1);
  CPPUNIT_ASSERT_EQUAL( g.ySource(), 2);
  CPPUNIT_ASSERT_EQUAL( g.xTarget(), 5);
  CPPUNIT_ASSERT_EQUAL( g.yTarget(), 6);

  // Check vertices
  const deque<Point>& v = g.accessVertices();
  deque<Point>::const_iterator itV = v.begin();
  CPPUNIT_ASSERT_EQUAL( itV->x(), 1);
  CPPUNIT_ASSERT_EQUAL( itV->y(), 2);
  ++itV;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 3);
  CPPUNIT_ASSERT_EQUAL( itV->y(), 4);
  ++itV;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 5);
  CPPUNIT_ASSERT_EQUAL( itV->y(), 6);
}


void
GenPolygonTest::testBuildFromPointList()
{
  // Triangle:  (1,2) (3,4) (5,6)
  //            ^^^^^       ^^^^^
  //           source       target

  list<Point> lp;
  lp.push_back(Point(1,2));
  lp.push_back(Point(3,4));
  lp.push_back(Point(5,6));

  // Create polygon
  Polygon plg(lp);

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( plg.xSource(), 1);
  CPPUNIT_ASSERT_EQUAL( plg.ySource(), 2);
  CPPUNIT_ASSERT_EQUAL( plg.xTarget(), 5);
  CPPUNIT_ASSERT_EQUAL( plg.yTarget(), 6);

  // Check vertices
  const deque<Point>& v = plg.accessVertices();
  deque<Point>::const_iterator itV = v.begin();
  CPPUNIT_ASSERT_EQUAL( itV->x(), 1);
  CPPUNIT_ASSERT_EQUAL( itV->y(), 2);
  ++itV;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 3);
  CPPUNIT_ASSERT_EQUAL( itV->y(), 4);
  ++itV;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 5);
  CPPUNIT_ASSERT_EQUAL( itV->y(), 6);
}


void
GenPolygonTest::testBuildFromPointListThrow()
{
  // List with 2 points

  list<Point> lp;
  lp.push_back(Point(1,2));
  lp.push_back(Point(3,4));

  // Should raise a QgaErrorUser exception:
  // The list of points must include at least 3 elements
  Polygon plg(lp);
}


// -------------------------------------------------------------------
// C O P Y
// -------------------------------------------------------------------


void
GenPolygonTest::testClone()
{
  // Triangle:  (1,2) (3,4) (5,6)
  //            ^^^^^       ^^^^^
  //            source      target

  list<Point> lp;
  lp.push_back(Point(1,2));
  lp.push_back(Point(3,4));
  lp.push_back(Point(5,6));

  // Create polygon
  Polygon plg(lp);

  // Create copy
  Polygon* cplg = plg.clone();

  // Check source and target of clone
  CPPUNIT_ASSERT_EQUAL( cplg->xSource(), 1);
  CPPUNIT_ASSERT_EQUAL( cplg->ySource(), 2);
  CPPUNIT_ASSERT_EQUAL( cplg->xTarget(), 5);
  CPPUNIT_ASSERT_EQUAL( cplg->yTarget(), 6);

  // Check vertices of clone
  const deque<Point>& v = cplg->accessVertices();
  deque<Point>::const_iterator itV = v.begin();

  CPPUNIT_ASSERT_EQUAL( itV->x(), 1);
  CPPUNIT_ASSERT_EQUAL( itV->y(), 2);
  ++itV;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 3);
  CPPUNIT_ASSERT_EQUAL( itV->y(), 4);
  ++itV;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 5);
  CPPUNIT_ASSERT_EQUAL( itV->y(), 6);

  // ---------
  // Tear Down
  // ---------

  delete cplg;
}


// -------------------------------------------------------------------
// O P E R A T O R S
// -------------------------------------------------------------------


void
GenPolygonTest::testAssignment()
{
  // Triangle:  (1,2) (3,4) (5,6)
  //            ^^^^^       ^^^^^
  //            source      target

  list<Point> lp;
  lp.push_back(Point(1,2));
  lp.push_back(Point(3,4));
  lp.push_back(Point(5,6));

  // Create polygon
  Polygon plg(lp);

  // Create copy
  Polygon cplg = plg;

  // Check source and target of copy
  CPPUNIT_ASSERT_EQUAL( cplg.xSource(), 1);
  CPPUNIT_ASSERT_EQUAL( cplg.ySource(), 2);
  CPPUNIT_ASSERT_EQUAL( cplg.xTarget(), 5);
  CPPUNIT_ASSERT_EQUAL( cplg.yTarget(), 6);

  // Check vertices of copy
  const deque<Point>& v = cplg.accessVertices();
  deque<Point>::const_iterator itV = v.begin();
  CPPUNIT_ASSERT_EQUAL( itV->x(), 1);
  CPPUNIT_ASSERT_EQUAL( itV->y(), 2);
  ++itV;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 3);
  CPPUNIT_ASSERT_EQUAL( itV->y(), 4);
  ++itV;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 5);
  CPPUNIT_ASSERT_EQUAL( itV->y(), 6);

  // Ensure operator returns a correct reference to 'this'
  CPPUNIT_ASSERT( &cplg == &(cplg = plg) );
}


// -------------------------------------------------------------------
// A R E A
// -------------------------------------------------------------------


void
GenPolygonTest::testArea()
{
  // RECTANGLE TRIANGLE, VERTICES IN CLOCKWISE ORDER
  // (1,1) (1,4) (4,4)
 
  list<Point> lp;
  lp.push_back(Point(1,1));
  lp.push_back(Point(1,4));
  lp.push_back(Point(4,4));
  Polygon plg(lp);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 4.5, 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), -4.5, 0. );

  ////////////////////////////////////////////////////////////////////////////

  // SAME RECTANGLE TRIANGLE, VERTICES IN COUNTER-CLOCKWISE ORDER

  lp.reverse();
  plg = Polygon(lp);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 4.5, 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), 4.5, 0. );

  ////////////////////////////////////////////////////////////////////////////

  // SQUARE, CLOCKWISE VERTICES
  // (1,1) (1,4) (4,4) (4,1)

  lp.clear();
  lp.push_back(Point(1,1));
  lp.push_back(Point(1,4));
  lp.push_back(Point(4,4));
  lp.push_back(Point(4,1));
  plg = Polygon(lp);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 9., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), -9., 0. );

  ////////////////////////////////////////////////////////////////////////////

  // SQUARE, COUNTER-CLOCKWISE VERTICES

  lp.reverse();
  plg = Polygon(lp);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 9., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), 9., 0. );

  ////////////////////////////////////////////////////////////////////////////

  // SQUARE WITH ALIGNED VERTICES, COUNTER-CLOCKWISE VERTICES
  // (4,1) (4,4) (1,4) (1,1) (2,1) (3,1)

  lp.push_back(Point(2,1));
  lp.push_back(Point(3,1));
  plg = Polygon(lp);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 9., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), 9., 0. );

  ////////////////////////////////////////////////////////////////////////////

  // CONVEX POLYGON, CLOCKWISE VERTICES

  lp.clear();
  lp.push_back(Point(5,6));
  lp.push_back(Point(3,8));
  lp.push_back(Point(3,11));
  lp.push_back(Point(8,11));
  lp.push_back(Point(9,10));
  lp.push_back(Point(9,9));
  lp.push_back(Point(11,9));
  lp.push_back(Point(11,6));
  lp.push_back(Point(10,5));
  lp.push_back(Point(6,5));
  lp.push_back(Point(6,6));
  plg = Polygon(lp);
  
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 38., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), -38., 0. );

  ////////////////////////////////////////////////////////////////////////////

  // CONVEX POLYGON, COUNTER-CLOCKWISE VERTICES

  lp.reverse();
  plg = Polygon(lp);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 38., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), 38., 0. );

  ////////////////////////////////////////////////////////////////////////////

  // CONCAVE POLYGON, CLOCKWISE VERTICES

  lp.clear();
  lp.push_back(Point(7,5));
  lp.push_back(Point(7,13));
  lp.push_back(Point(11,13));
  lp.push_back(Point(13,11));
  lp.push_back(Point(16,14));
  lp.push_back(Point(17,14));
  lp.push_back(Point(17,13));
  lp.push_back(Point(18,13));
  lp.push_back(Point(18,8));
  lp.push_back(Point(16,6));
  lp.push_back(Point(19,3));
  lp.push_back(Point(15,3));
  lp.push_back(Point(15,4));
  lp.push_back(Point(16,4));
  lp.push_back(Point(14,6));
  lp.push_back(Point(14,8));
  lp.push_back(Point(12,8));
  lp.push_back(Point(10,10));
  lp.push_back(Point(9,9));
  lp.push_back(Point(13,5));
  lp.push_back(Point(13,4));
  lp.push_back(Point(10,4));
  lp.push_back(Point(10,6));
  lp.push_back(Point(9,6));
  lp.push_back(Point(9,3));
  plg = Polygon(lp);
  
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 80.5, 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), -80.5, 0. );

  ////////////////////////////////////////////////////////////////////////////

  // CONCAVE POLYGON, COUNTER-CLOCKWISE VERTICES

  lp.reverse();
  plg = Polygon(lp);
  
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 80.5, 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), 80.5, 0. );

  ////////////////////////////////////////////////////////////////////////////

  // CONCAVE POLYGON (CROSS) WITH ALIGNED VERTICES, CLOCKWISE VERTICES

  lp.clear();
  lp.push_back(Point(1004,1000));
  lp.push_back(Point(1004,1002));
  lp.push_back(Point(1003,1002));
  lp.push_back(Point(1000,1002));
  lp.push_back(Point(1000,1004));
  lp.push_back(Point(1002,1004));
  lp.push_back(Point(1004,1004));
  lp.push_back(Point(1004,1005));
  lp.push_back(Point(1004,1008));
  lp.push_back(Point(1005,1008));
  lp.push_back(Point(1006,1008));
  lp.push_back(Point(1006,1007));
  lp.push_back(Point(1006,1005));
  lp.push_back(Point(1006,1004));
  lp.push_back(Point(1008,1004));
  lp.push_back(Point(1009,1004));
  lp.push_back(Point(1009,1002));
  lp.push_back(Point(1008,1002));
  lp.push_back(Point(1006,1002));
  lp.push_back(Point(1006,1001));
  lp.push_back(Point(1006,1000));
  lp.push_back(Point(1005,1000));
  plg = Polygon(lp);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 30., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), -30., 0. );

  ////////////////////////////////////////////////////////////////////////////

  // CONCAVE POLYGON (CROSS) WITH ALIGNED VERTICES, COUNTER-CLOCKWISE VERTICES

  lp.reverse();
  plg = Polygon(lp);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 30., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), 30., 0. );

  ////////////////////////////////////////////////////////////////////////////

  // CONCAVE POLYGON WITH NON-CONSECUTIVE DUPLICATE POINTS (BUTTERFLY)
  // CLOCKWISE VERTICES
  /*
      1 +     + 5
        |\ 6 /|
        | \_/ |
        | / \ |
        |/ 3 \|
      2 +     + 4
  */

  lp.clear();
  lp.push_back(Point(20,35));
  lp.push_back(Point(20,39));
  lp.push_back(Point(22,37));
  lp.push_back(Point(24,39));
  lp.push_back(Point(24,35));
  lp.push_back(Point(22,37));
  plg = Polygon(lp);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 8., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), -8., 0. );

  ////////////////////////////////////////////////////////////////////////////

  // CONCAVE POLYGON WITH NON-CONSECUTIVE DUPLICATE POINTS (BUTTERFLY)
  // COUNTER-CLOCKWISE VERTICES

  lp.reverse();
  plg = Polygon(lp);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 8., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), 8., 0. );

  ////////////////////////////////////////////////////////////////////////////

  // SQUARE WITH CONSECUTIVE DUPLICATE VERTICES, CLOCKWISE VERTICES

  lp.clear();
  lp.push_back(Point(0,0));
  lp.push_back(Point(0,0));
  lp.push_back(Point(0,4));
  lp.push_back(Point(4,4));
  lp.push_back(Point(4,4));
  lp.push_back(Point(4,2));
  lp.push_back(Point(4,2));
  lp.push_back(Point(4,0));
  plg = Polygon(lp);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 16., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), -16., 0. );

  ////////////////////////////////////////////////////////////////////////////

  // SQUARE WITH CONSECUTIVE DUPLICATE VERTICES, COUNTER-CLOCKWISE VERTICES

  lp.reverse();
  plg = Polygon(lp);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 16., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), 16., 0. );

  ////////////////////////////////////////////////////////////////////////////

  // RECTANGLE TRIANGLE PLUS TWO OVERLAPPING SIDES, CLOCKWISE VERTICES
  /*
     1 +
       |\
       | \
       |  \
     2 +---+---+
           4   3
  */

  lp.clear();
  lp.push_back(Point(2,2));
  lp.push_back(Point(2,5));
  lp.push_back(Point(8,5));
  lp.push_back(Point(5,5));
  plg = Polygon(lp);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 4.5, 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), -4.5, 0. );

  ////////////////////////////////////////////////////////////////////////////

  // RECTANGLE TRIANGLE PLUS TWO OVERLAPPING SIDES, COUNTER-CLOCKWISE VERTICES

  lp.reverse();
  plg = Polygon(lp);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 4.5, 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), 4.5, 0. );

  ////////////////////////////////////////////////////////////////////////////

  // SQUARE WITH NEGATIVE COORDINATES, CLOCKWISE VERTICES
  /*
              ^
    (-3,3)    |    (3,3)
          +-------+
          |   |   |
       ---|---+---|--->
          |   |   |
          +-------+
   (-3,-3)    |    (3,-3)


  */

  lp.clear();
  lp.push_back(Point(3,3));
  lp.push_back(Point(-3,3));
  lp.push_back(Point(-3,-3));
  lp.push_back(Point(3,-3));
  plg = Polygon(lp);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 36., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), 36., 0. );

  ////////////////////////////////////////////////////////////////////////////

  // SQUARE WITH NEGATIVE COORDINATES, COUNTER-CLOCKWISE VERTICES

  lp.reverse();
  plg = Polygon(lp);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 36., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), -36., 0. );
}


// -------------------------------------------------------------------
// A C C E S S   T O   V E R T I C E S
// -------------------------------------------------------------------


void
GenPolygonTest::testSize()
{
  // For fun: Polygon created by default constructor
  Polygon plg0;

  CPPUNIT_ASSERT_EQUAL( plg0.size(), 0);

  // Using predefined list

  Polygon plg4(_iPtList);

  CPPUNIT_ASSERT_EQUAL( plg4.size(), 4);
}


void
GenPolygonTest::testGetVertices()
{
  // ------
  // Set Up
  // ------
  
  // A polygon and its copy
  IPolygon iPoly(_iPtList);

  // The vertices of the polygon
  deque<IPoint>& id = iPoly.getVertices();

  // ------
  // Set Up
  // ------

  int os = iPoly.size();

  // Modification of the vertices
  id.push_back(_iPt3);

  int ns = iPoly.size();

  // -------
  // Process
  // -------

  // The polygon has one more vertex
  CPPUNIT_ASSERT_EQUAL( ns, os + 1 );
  CPPUNIT_ASSERT( (iPoly.accessVertices()).back() == _iPt3 );
}


// -------------------------------------------------------------------
// I N S E R T   V E R T I C E S
// -------------------------------------------------------------------


void
GenPolygonTest::testAppend()
{
  // Rectangle triangle
  // (1,1) (1,4) (4,4)

  list<Point> lp;
  lp.push_back(Point(1,1));
  lp.push_back(Point(1,4));
  lp.push_back(Point(4,4));
  Polygon plg(lp);

  // APPEND SOURCE
  // -------------

  plg.appendSource(Point(-1,-1));

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( plg.xSource(), -1);
  CPPUNIT_ASSERT_EQUAL( plg.ySource(), -1);
  CPPUNIT_ASSERT_EQUAL( plg.xTarget(), 4);
  CPPUNIT_ASSERT_EQUAL( plg.yTarget(), 4);
  // Check vertices
  const deque<Point>& v = plg.accessVertices();
  deque<Point>::const_iterator itV = v.begin();
  CPPUNIT_ASSERT_EQUAL( itV->x(), -1 );
  CPPUNIT_ASSERT_EQUAL( itV->y(), -1 );
  ++itV;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 1 );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 1 );
  ++itV;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 1 );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 4 );
  ++itV;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 4 );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 4 );

  // APPEND TARGET
  // -------------

  plg.appendTarget(Point(5,6));

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( plg.xSource(), -1);
  CPPUNIT_ASSERT_EQUAL( plg.ySource(), -1);
  CPPUNIT_ASSERT_EQUAL( plg.xTarget(), 5);
  CPPUNIT_ASSERT_EQUAL( plg.yTarget(), 6);
  // Check vertices
  const deque<Point>& vv = plg.accessVertices();
  itV = vv.begin();
  CPPUNIT_ASSERT_EQUAL( itV->x(), -1 );
  CPPUNIT_ASSERT_EQUAL( itV->y(), -1 );
  ++itV;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 1 );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 1 );
  ++itV;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 1 );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 4 );
  ++itV;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 4 );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 4 );
  ++itV;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 5 );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 6 );

  // APPEND A VECTOR OF POINTS
  // -------------------------

  plg = Polygon(lp);
  vector<Point> vp;
  vp.push_back(Point(1,2));
  vp.push_back(Point(3,4));
  plg.append(vp);

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( plg.xSource(), 1);
  CPPUNIT_ASSERT_EQUAL( plg.ySource(), 1);
  CPPUNIT_ASSERT_EQUAL( plg.xTarget(), 3);
  CPPUNIT_ASSERT_EQUAL( plg.yTarget(), 4);
  // Check vertices
  const deque<Point>& vvv = plg.accessVertices();
  itV = vvv.begin();
  CPPUNIT_ASSERT_EQUAL( itV->x(), 1 );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 1 );
  ++itV;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 1 );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 4 );
  ++itV;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 4 );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 4 );
  ++itV;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 1 );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 2 );
  ++itV;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 3 );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 4 );
}


// -------------------------------------------------------------------
// R E M O V E   V E R T I C E S
// -------------------------------------------------------------------


void
GenPolygonTest::testRemove()
{
  // REMOVE SOURCE
  // =============

  // square, clockwise vertices
  // (1,1) (1,4) (4,4) (4,1)
  list<Point> lp;
  lp.push_back(Point(1,1));
  lp.push_back(Point(1,4));
  lp.push_back(Point(4,4));
  lp.push_back(Point(4,1));
  Polygon plg(lp);

  plg.remove(Point(1,1));

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( plg.xSource(), 1 );
  CPPUNIT_ASSERT_EQUAL( plg.ySource(), 4 );
  CPPUNIT_ASSERT_EQUAL( plg.xTarget(), 4 );
  CPPUNIT_ASSERT_EQUAL( plg.yTarget(), 1 );
  // Check vertices
  CPPUNIT_ASSERT_EQUAL( plg.size(), 3 );
  const deque<Point>& v1 = plg.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (v1[0]).x(), 1 );
  CPPUNIT_ASSERT_EQUAL( (v1[0]).y(), 4 );
  CPPUNIT_ASSERT_EQUAL( (v1[1]).x(), 4 );
  CPPUNIT_ASSERT_EQUAL( (v1[1]).y(), 4 );
  CPPUNIT_ASSERT_EQUAL( (v1[2]).x(), 4 );
  CPPUNIT_ASSERT_EQUAL( (v1[2]).y(), 1 );

  // REMOVE TARGET
  // =============

  // square, clockwise vertices
  // (1,1) (1,4) (4,4) (4,1)
  lp.clear();
  lp.push_back(Point(1,1));
  lp.push_back(Point(1,4));
  lp.push_back(Point(4,4));
  lp.push_back(Point(4,1));
  plg = Polygon(lp);

  plg.remove(Point(4,1));

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( plg.xSource(), 1 );
  CPPUNIT_ASSERT_EQUAL( plg.ySource(), 1 );
  CPPUNIT_ASSERT_EQUAL( plg.xTarget(), 4 );
  CPPUNIT_ASSERT_EQUAL( plg.yTarget(), 4 );
  // Check vertices
  CPPUNIT_ASSERT_EQUAL( plg.size(), 3 );
  const deque<Point>& v2 = plg.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (v2[0]).x(), 1 );
  CPPUNIT_ASSERT_EQUAL( (v2[0]).y(), 1 );
  CPPUNIT_ASSERT_EQUAL( (v2[1]).x(), 1 );
  CPPUNIT_ASSERT_EQUAL( (v2[1]).y(), 4 );
  CPPUNIT_ASSERT_EQUAL( (v2[2]).x(), 4 );
  CPPUNIT_ASSERT_EQUAL( (v2[2]).y(), 4 );

  // REMOVE INTERMEDIATE VERTEX
  // ==========================

  // square, clockwise vertices
  // (1,1) (1,4) (4,4) (4,1)
  lp.clear();
  lp.push_back(Point(1,1));
  lp.push_back(Point(1,4));
  lp.push_back(Point(4,4));
  lp.push_back(Point(4,1));
  plg = Polygon(lp);

  plg.remove(Point(4,4));

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( plg.xSource(), 1 );
  CPPUNIT_ASSERT_EQUAL( plg.ySource(), 1 );
  CPPUNIT_ASSERT_EQUAL( plg.xTarget(), 4 );
  CPPUNIT_ASSERT_EQUAL( plg.yTarget(), 1 );
  // Check vertices
  CPPUNIT_ASSERT_EQUAL( plg.size(), 3 );
  const deque<Point>& v3 = plg.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (v3[0]).x(), 1 );
  CPPUNIT_ASSERT_EQUAL( (v3[0]).y(), 1 );
  CPPUNIT_ASSERT_EQUAL( (v3[1]).x(), 1 );
  CPPUNIT_ASSERT_EQUAL( (v3[1]).y(), 4 );
  CPPUNIT_ASSERT_EQUAL( (v3[2]).x(), 4 );
  CPPUNIT_ASSERT_EQUAL( (v3[2]).y(), 1 );

  // NO REMOVAL
  // ==========

  // square, clockwise vertices
  // (1,1) (1,4) (4,4) (4,1)
  lp.clear();
  lp.push_back(Point(1,1));
  lp.push_back(Point(1,4));
  lp.push_back(Point(4,4));
  lp.push_back(Point(4,1));
  plg = Polygon(lp);

  plg.remove(Point(1,2));

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( plg.xSource(), 1 );
  CPPUNIT_ASSERT_EQUAL( plg.ySource(), 1 );
  CPPUNIT_ASSERT_EQUAL( plg.xTarget(), 4 );
  CPPUNIT_ASSERT_EQUAL( plg.yTarget(), 1 );
  // Check vertices
  CPPUNIT_ASSERT_EQUAL( plg.size(), 4 );
  const deque<Point>& v4 = plg.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (v4[0]).x(), 1 );
  CPPUNIT_ASSERT_EQUAL( (v4[0]).y(), 1 );
  CPPUNIT_ASSERT_EQUAL( (v4[1]).x(), 1 );
  CPPUNIT_ASSERT_EQUAL( (v4[1]).y(), 4 );
  CPPUNIT_ASSERT_EQUAL( (v4[2]).x(), 4 );
  CPPUNIT_ASSERT_EQUAL( (v4[2]).y(), 4 );
  CPPUNIT_ASSERT_EQUAL( (v4[3]).x(), 4 );
  CPPUNIT_ASSERT_EQUAL( (v4[3]).y(), 1 );
}


void
GenPolygonTest::testRemoveThrow()
{
  list<Point> lp;
  lp.push_back(Point(1,2));
  lp.push_back(Point(3,4));
  lp.push_back(Point(5,6));

  Polygon plg(lp);

  // Should raise a QgarErrorUser exception:
  // One cannot remove a vertex from a polygon with 3 vertices
  plg.remove(Point(3,4));
}


// -------------------------------------------------------------------
// C O N V E R S I O N S   O F   T H E   V E R T I C E S
// -------------------------------------------------------------------


void
GenPolygonTest::testToPtVect()
{
  // ------
  // Set Up
  // ------

  IPolygon iPoly(_iPtList);

  // -------
  // Process
  // -------
  
  vector<IPoint> ptVect = iPoly.toPointVector();

  // -----
  // Check
  // -----

  // Size
  CPPUNIT_ASSERT_EQUAL((int) ptVect.size(), iPoly.size() );

  // Source and target
  CPPUNIT_ASSERT( iPoly.source() == _iPtList.front() );
  CPPUNIT_ASSERT( iPoly.target() == _iPtList.back() );

  // Vertices
  deque<IPoint>::const_iterator itPoly = iPoly.accessVertices().begin();
  vector<IPoint>::iterator itVect = ptVect.begin();

  while( itVect != ptVect.end() )
    {
      CPPUNIT_ASSERT_EQUAL( *itVect++, *itPoly++);
    }
}


void
GenPolygonTest::testToSegList()
{
  // TO A SEGMENT LIST
  // =================

  // square, clockwise vertices
  // (1,1) (1,4) (4,4) (4,1)
  list<Point> lp;
  lp.push_back(Point(1,1));
  lp.push_back(Point(1,4));
  lp.push_back(Point(4,4));
  lp.push_back(Point(4,1));
  Polygon plg(lp);

  list<Segment> ls = plg.toSegList();

  // Check segments
  CPPUNIT_ASSERT_EQUAL( (int)ls.size(), 4 );
  list<Segment>::iterator itS = ls.begin();
  CPPUNIT_ASSERT_EQUAL( itS->xSource(), 1 );
  CPPUNIT_ASSERT_EQUAL( itS->ySource(), 1 );
  CPPUNIT_ASSERT_EQUAL( itS->xTarget(), 1 );
  CPPUNIT_ASSERT_EQUAL( itS->yTarget(), 4 );
  ++itS;
  CPPUNIT_ASSERT_EQUAL( itS->xSource(), 1 );
  CPPUNIT_ASSERT_EQUAL( itS->ySource(), 4 );
  CPPUNIT_ASSERT_EQUAL( itS->xTarget(), 4 );
  CPPUNIT_ASSERT_EQUAL( itS->yTarget(), 4 );
  ++itS;
  CPPUNIT_ASSERT_EQUAL( itS->xSource(), 4 );
  CPPUNIT_ASSERT_EQUAL( itS->ySource(), 4 );
  CPPUNIT_ASSERT_EQUAL( itS->xTarget(), 4 );
  CPPUNIT_ASSERT_EQUAL( itS->yTarget(), 1 );
  ++itS;
  CPPUNIT_ASSERT_EQUAL( itS->xSource(), 4 );
  CPPUNIT_ASSERT_EQUAL( itS->ySource(), 1 );
  CPPUNIT_ASSERT_EQUAL( itS->xTarget(), 1 );
  CPPUNIT_ASSERT_EQUAL( itS->yTarget(), 1 );

  // TO A LIST OF QGAR SEGMENTS WITH DEFAULT ATTRIBUTES
  // ==================================================

  list<QgarSegment> lqs = plg.toQgarSegList();

  // Check segments
  CPPUNIT_ASSERT_EQUAL( (int)lqs.size(), 4 );
  list<QgarSegment>::iterator itQS = lqs.begin();
  CPPUNIT_ASSERT_EQUAL( itQS->xSource(), 1 );
  CPPUNIT_ASSERT_EQUAL( itQS->ySource(), 1 );
  CPPUNIT_ASSERT_EQUAL( itQS->xTarget(), 1 );
  CPPUNIT_ASSERT_EQUAL( itQS->yTarget(), 4 );
  CPPUNIT_ASSERT( itQS->thickness() == 1                   );
  CPPUNIT_ASSERT( itQS->color()     == QGE_COLOR_DEFAULT   );
  CPPUNIT_ASSERT( itQS->outline()   == QGE_OUTLINE_DEFAULT );
  ++itQS;
  CPPUNIT_ASSERT_EQUAL( itQS->xSource(), 1 );
  CPPUNIT_ASSERT_EQUAL( itQS->ySource(), 4 );
  CPPUNIT_ASSERT_EQUAL( itQS->xTarget(), 4 );
  CPPUNIT_ASSERT_EQUAL( itQS->yTarget(), 4 );
  CPPUNIT_ASSERT( itQS->thickness() == 1                   );
  CPPUNIT_ASSERT( itQS->color()     == QGE_COLOR_DEFAULT   );
  CPPUNIT_ASSERT( itQS->outline()   == QGE_OUTLINE_DEFAULT );
  ++itQS;
  CPPUNIT_ASSERT_EQUAL( itQS->xSource(), 4 );
  CPPUNIT_ASSERT_EQUAL( itQS->ySource(), 4 );
  CPPUNIT_ASSERT_EQUAL( itQS->xTarget(), 4 );
  CPPUNIT_ASSERT_EQUAL( itQS->yTarget(), 1 );
  CPPUNIT_ASSERT( itQS->thickness() == 1                   );
  CPPUNIT_ASSERT( itQS->color()     == QGE_COLOR_DEFAULT   );
  CPPUNIT_ASSERT( itQS->outline()   == QGE_OUTLINE_DEFAULT );
  ++itQS;
  CPPUNIT_ASSERT_EQUAL( itQS->xSource(), 4 );
  CPPUNIT_ASSERT_EQUAL( itQS->ySource(), 1 );
  CPPUNIT_ASSERT_EQUAL( itQS->xTarget(), 1 );
  CPPUNIT_ASSERT_EQUAL( itQS->yTarget(), 1 );
  CPPUNIT_ASSERT( itQS->thickness() == 1                   );
  CPPUNIT_ASSERT( itQS->color()     == QGE_COLOR_DEFAULT   );
  CPPUNIT_ASSERT( itQS->outline()   == QGE_OUTLINE_DEFAULT );

  // TO A LIST OF QGAR SEGMENTS WITH GIVEN ATTRIBUTES
  // ================================================

  lqs = plg.toQgarSegList(7, QGE_COLOR_PURPLE, QGE_OUTLINE_DASH_SS);

  // Check segments
  CPPUNIT_ASSERT_EQUAL( (int)lqs.size(), 4 );
  itQS = lqs.begin();
  CPPUNIT_ASSERT_EQUAL( itQS->xSource(), 1 );
  CPPUNIT_ASSERT_EQUAL( itQS->ySource(), 1 );
  CPPUNIT_ASSERT_EQUAL( itQS->xTarget(), 1 );
  CPPUNIT_ASSERT_EQUAL( itQS->yTarget(), 4 );
  CPPUNIT_ASSERT( itQS->thickness() == 7                   );
  CPPUNIT_ASSERT( itQS->color()     == QGE_COLOR_PURPLE    );
  CPPUNIT_ASSERT( itQS->outline()   == QGE_OUTLINE_DASH_SS );
  ++itQS;
  CPPUNIT_ASSERT_EQUAL( itQS->xSource(), 1 );
  CPPUNIT_ASSERT_EQUAL( itQS->ySource(), 4 );
  CPPUNIT_ASSERT_EQUAL( itQS->xTarget(), 4 );
  CPPUNIT_ASSERT_EQUAL( itQS->yTarget(), 4 );
  CPPUNIT_ASSERT( itQS->thickness() == 7                   );
  CPPUNIT_ASSERT( itQS->color()     == QGE_COLOR_PURPLE    );
  CPPUNIT_ASSERT( itQS->outline()   == QGE_OUTLINE_DASH_SS );
  ++itQS;
  CPPUNIT_ASSERT_EQUAL( itQS->xSource(), 4 );
  CPPUNIT_ASSERT_EQUAL( itQS->ySource(), 4 );
  CPPUNIT_ASSERT_EQUAL( itQS->xTarget(), 4 );
  CPPUNIT_ASSERT_EQUAL( itQS->yTarget(), 1 );
  CPPUNIT_ASSERT( itQS->thickness() == 7                   );
  CPPUNIT_ASSERT( itQS->color()     == QGE_COLOR_PURPLE    );
  CPPUNIT_ASSERT( itQS->outline()   == QGE_OUTLINE_DASH_SS );
  ++itQS;
  CPPUNIT_ASSERT_EQUAL( itQS->xSource(), 4 );
  CPPUNIT_ASSERT_EQUAL( itQS->ySource(), 1 );
  CPPUNIT_ASSERT_EQUAL( itQS->xTarget(), 1 );
  CPPUNIT_ASSERT_EQUAL( itQS->yTarget(), 1 );
  CPPUNIT_ASSERT( itQS->thickness() == 7                   );
  CPPUNIT_ASSERT( itQS->color()     == QGE_COLOR_PURPLE    );
  CPPUNIT_ASSERT( itQS->outline()   == QGE_OUTLINE_DASH_SS );
}


// -------------------------------------------------------------------
// G E O M E T R Y :   T R A N S L A T I O N
// -------------------------------------------------------------------

void
GenPolygonTest::testTranslate()
{
  // TRANSLATION USING XY COORDINATES

  // Rectangle triangle
  // (1,1) (1,4) (4,4)
 
  list<Point> lp;
  lp.push_back(Point(1,1));
  lp.push_back(Point(1,4));
  lp.push_back(Point(4,4));
  Polygon plg(lp);

  plg.translate(10,20);

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( plg.xSource(), 11 );
  CPPUNIT_ASSERT_EQUAL( plg.ySource(), 21 );
  CPPUNIT_ASSERT_EQUAL( plg.xTarget(), 14 );
  CPPUNIT_ASSERT_EQUAL( plg.yTarget(), 24 );

  // Check vertices
  const deque<Point>& v1 = plg.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (v1[0]).x(), 11 );
  CPPUNIT_ASSERT_EQUAL( (v1[0]).y(), 21 );
  CPPUNIT_ASSERT_EQUAL( (v1[1]).x(), 11 );
  CPPUNIT_ASSERT_EQUAL( (v1[1]).y(), 24 );
  CPPUNIT_ASSERT_EQUAL( (v1[2]).x(), 14 );
  CPPUNIT_ASSERT_EQUAL( (v1[2]).y(), 24 );
}


// -------------------------------------------------------------------
// S E R I A L I Z A T I O N / D E S E R I A L I Z A T I O N
// -------------------------------------------------------------------


void
GenPolygonTest::testSerializeDeserialize()
{
  // Triangle:  (1.1, 2.2) (3.3, 4.4) (5.5, 6.6)
  //            ^^^^^^^^^^           ^^^^^^^^^^
  //              source               target

  list<DPoint> lp;
  lp.push_back(DPoint(1.1 , 2.2));
  lp.push_back(DPoint(3.3 , 4.4));
  lp.push_back(DPoint(5.5 , 6.6));

  DPolygon oplg(lp);
  DPolygon iplg;
  stringstream ss;

  ss << oplg;
  ss >> iplg;
  ss.flush();

  // Check source and target
  CPPUNIT_ASSERT_DOUBLES_EQUAL( oplg.xSource(), 1.1, 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( oplg.ySource(), 2.2, 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( oplg.xTarget(), 5.5, 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( oplg.yTarget(), 6.6, 0. );

  CPPUNIT_ASSERT_DOUBLES_EQUAL( iplg.xSource(), 1.1, 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( iplg.ySource(), 2.2, 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( iplg.xTarget(), 5.5, 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( iplg.yTarget(), 6.6, 0. );

  // Check vertices
  const deque<DPoint>& vo = oplg.accessVertices();
  const deque<DPoint>& vi = iplg.accessVertices();

  deque<DPoint>::const_iterator itVO = vo.begin();
  deque<DPoint>::const_iterator itVI = vi.begin();

  CPPUNIT_ASSERT_DOUBLES_EQUAL( itVO->x(), 1.1, 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( itVO->y(), 2.2, 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( itVI->x(), 1.1, 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( itVI->y(), 2.2, 0. );
  ++itVO;
  ++itVI;
  CPPUNIT_ASSERT_DOUBLES_EQUAL( itVO->x(), 3.3, 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( itVO->y(), 4.4, 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( itVI->x(), 3.3, 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( itVI->y(), 4.4, 0. );
  ++itVO;
  ++itVI;
  CPPUNIT_ASSERT_DOUBLES_EQUAL( itVO->x(), 5.5, 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( itVO->y(), 6.6, 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( itVI->x(), 5.5, 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( itVI->y(), 6.6, 0. );
}


// -------------------------------------------------------------------
// S O U R C E   A N D   T A R G E T   U P D A T E S
// -------------------------------------------------------------------


void
GenPolygonTest::testUpdateSourceTarget()
{
  // Rectangle triangle
  // (1,1) (1,4) (4,4)
 
  list<Point> lp;
  lp.push_back(Point(1,1));
  lp.push_back(Point(1,4));
  lp.push_back(Point(4,4));
  Polyline plg(lp);

  // SET SOURCE POINT
  // ----------------
  plg.fixSource(Point(-1,-1));

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( plg.xSource(), -1 );
  CPPUNIT_ASSERT_EQUAL( plg.ySource(), -1 );
  CPPUNIT_ASSERT_EQUAL( plg.xTarget(),  4 );
  CPPUNIT_ASSERT_EQUAL( plg.yTarget(),  4 );
  // Check vertices
  const deque<Point>& v1 = plg.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (v1[0]).x(), -1 );
  CPPUNIT_ASSERT_EQUAL( (v1[0]).y(), -1 );
  CPPUNIT_ASSERT_EQUAL( (v1[1]).x(),  1 );
  CPPUNIT_ASSERT_EQUAL( (v1[1]).y(),  4 );
  CPPUNIT_ASSERT_EQUAL( (v1[2]).x(),  4 );
  CPPUNIT_ASSERT_EQUAL( (v1[2]).y(),  4 );

  // SET SOURCE COORDINATES
  // ----------------------
  plg.fixSource(-10,-10);

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( plg.xSource(), -10 );
  CPPUNIT_ASSERT_EQUAL( plg.ySource(), -10 );
  CPPUNIT_ASSERT_EQUAL( plg.xTarget(),  4  );
  CPPUNIT_ASSERT_EQUAL( plg.yTarget(),  4  );
  // Check vertices
  const deque<Point>& v10 = plg.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (v10[0]).x(), -10 );
  CPPUNIT_ASSERT_EQUAL( (v10[0]).y(), -10 );
  CPPUNIT_ASSERT_EQUAL( (v10[1]).x(),  1  );
  CPPUNIT_ASSERT_EQUAL( (v10[1]).y(),  4  );
  CPPUNIT_ASSERT_EQUAL( (v10[2]).x(),  4  );
  CPPUNIT_ASSERT_EQUAL( (v10[2]).y(),  4  );

  // SET TARGET POINT
  // ----------------
  plg.fixTarget(Point(6,5));

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( plg.xSource(), -10 );
  CPPUNIT_ASSERT_EQUAL( plg.ySource(), -10 );
  CPPUNIT_ASSERT_EQUAL( plg.xTarget(),  6 );
  CPPUNIT_ASSERT_EQUAL( plg.yTarget(),  5 );
  // Check vertices
  const deque<Point>& v2 = plg.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (v2[0]).x(), -10 );
  CPPUNIT_ASSERT_EQUAL( (v2[0]).y(), -10 );
  CPPUNIT_ASSERT_EQUAL( (v2[1]).x(),  1 );
  CPPUNIT_ASSERT_EQUAL( (v2[1]).y(),  4 );
  CPPUNIT_ASSERT_EQUAL( (v2[2]).x(),  6 );
  CPPUNIT_ASSERT_EQUAL( (v2[2]).y(),  5 );

  // SET TARGET COORDINATES
  // ----------------------
  plg.fixTarget(60,50);

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( plg.xSource(), -10 );
  CPPUNIT_ASSERT_EQUAL( plg.ySource(), -10 );
  CPPUNIT_ASSERT_EQUAL( plg.xTarget(),  60 );
  CPPUNIT_ASSERT_EQUAL( plg.yTarget(),  50 );
  // Check vertices
  const deque<Point>& v20 = plg.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (v20[0]).x(), -10 );
  CPPUNIT_ASSERT_EQUAL( (v20[0]).y(), -10 );
  CPPUNIT_ASSERT_EQUAL( (v20[1]).x(),   1 );
  CPPUNIT_ASSERT_EQUAL( (v20[1]).y(),   4 );
  CPPUNIT_ASSERT_EQUAL( (v20[2]).x(),  60 );
  CPPUNIT_ASSERT_EQUAL( (v20[2]).y(),  50 );

  // SET BOTH SOURCE & TARGET POINTS
  // -------------------------------
  plg.fixSourceTarget(Point(-2,-2), Point(10,10));

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( plg.xSource(), -2 );
  CPPUNIT_ASSERT_EQUAL( plg.ySource(), -2 );
  CPPUNIT_ASSERT_EQUAL( plg.xTarget(), 10 );
  CPPUNIT_ASSERT_EQUAL( plg.yTarget(), 10 );
  // Check vertices
  const deque<Point>& v3 = plg.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (v3[0]).x(), -2 );
  CPPUNIT_ASSERT_EQUAL( (v3[0]).y(), -2 );
  CPPUNIT_ASSERT_EQUAL( (v3[1]).x(),  1 );
  CPPUNIT_ASSERT_EQUAL( (v3[1]).y(),  4 );
  CPPUNIT_ASSERT_EQUAL( (v3[2]).x(), 10 );
  CPPUNIT_ASSERT_EQUAL( (v3[2]).y(), 10 );

  // SET BOTH SOURCE & TARGET COORDINATES
  // ------------------------------------
  plg.fixSourceTarget(Point(-20,-20), Point(20,20));

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( plg.xSource(), -20 );
  CPPUNIT_ASSERT_EQUAL( plg.ySource(), -20 );
  CPPUNIT_ASSERT_EQUAL( plg.xTarget(),  20 );
  CPPUNIT_ASSERT_EQUAL( plg.yTarget(),  20 );
  // Check vertices
  const deque<Point>& v30 = plg.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (v30[0]).x(), -20 );
  CPPUNIT_ASSERT_EQUAL( (v30[0]).y(), -20 );
  CPPUNIT_ASSERT_EQUAL( (v30[1]).x(),   1 );
  CPPUNIT_ASSERT_EQUAL( (v30[1]).y(),   4 );
  CPPUNIT_ASSERT_EQUAL( (v30[2]).x(),  20 );
  CPPUNIT_ASSERT_EQUAL( (v30[2]).y(),  20 );

  // SET X SOURCE
  // ------------
  plg.fixXSource(8);

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( plg.xSource(),   8 );
  CPPUNIT_ASSERT_EQUAL( plg.ySource(), -20 );
  CPPUNIT_ASSERT_EQUAL( plg.xTarget(),  20 );
  CPPUNIT_ASSERT_EQUAL( plg.yTarget(),  20 );
  // Check vertices
  const deque<Point>& v4 = plg.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (v4[0]).x(),   8 );
  CPPUNIT_ASSERT_EQUAL( (v4[0]).y(), -20 );
  CPPUNIT_ASSERT_EQUAL( (v4[1]).x(),   1 );
  CPPUNIT_ASSERT_EQUAL( (v4[1]).y(),   4 );
  CPPUNIT_ASSERT_EQUAL( (v4[2]).x(),  20 );
  CPPUNIT_ASSERT_EQUAL( (v4[2]).y(),  20 );

  // SET Y SOURCE
  // ------------
  plg.fixYSource(-8);

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( plg.xSource(),  8 );
  CPPUNIT_ASSERT_EQUAL( plg.ySource(), -8 );
  CPPUNIT_ASSERT_EQUAL( plg.xTarget(), 20 );
  CPPUNIT_ASSERT_EQUAL( plg.yTarget(), 20 );
  // Check vertices
  const deque<Point>& v5 = plg.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (v5[0]).x(),  8 );
  CPPUNIT_ASSERT_EQUAL( (v5[0]).y(), -8 );
  CPPUNIT_ASSERT_EQUAL( (v5[1]).x(),  1 );
  CPPUNIT_ASSERT_EQUAL( (v5[1]).y(),  4 );
  CPPUNIT_ASSERT_EQUAL( (v5[2]).x(), 20 );
  CPPUNIT_ASSERT_EQUAL( (v5[2]).y(), 20 );

  // SET X TARGET
  // ------------
  plg.fixXTarget(9);

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( plg.xSource(),  8 );
  CPPUNIT_ASSERT_EQUAL( plg.ySource(), -8 );
  CPPUNIT_ASSERT_EQUAL( plg.xTarget(),  9 );
  CPPUNIT_ASSERT_EQUAL( plg.yTarget(), 20 );
  // Check vertices
  const deque<Point>& v6 = plg.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (v6[0]).x(),  8 );
  CPPUNIT_ASSERT_EQUAL( (v6[0]).y(), -8 );
  CPPUNIT_ASSERT_EQUAL( (v6[1]).x(),  1 );
  CPPUNIT_ASSERT_EQUAL( (v6[1]).y(),  4 );
  CPPUNIT_ASSERT_EQUAL( (v6[2]).x(),  9 );
  CPPUNIT_ASSERT_EQUAL( (v6[2]).y(), 20 );

  // SET Y TARGET
  // ------------
  plg.fixYTarget(11);

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( plg.xSource(),  8 );
  CPPUNIT_ASSERT_EQUAL( plg.ySource(), -8 );
  CPPUNIT_ASSERT_EQUAL( plg.xTarget(),  9 );
  CPPUNIT_ASSERT_EQUAL( plg.yTarget(), 11 );
  // Check vertices
  const deque<Point>& v7 = plg.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (v7[0]).x(),  8 );
  CPPUNIT_ASSERT_EQUAL( (v7[0]).y(), -8 );
  CPPUNIT_ASSERT_EQUAL( (v7[1]).x(),  1 );
  CPPUNIT_ASSERT_EQUAL( (v7[1]).y(),  4 );
  CPPUNIT_ASSERT_EQUAL( (v7[2]).x(),  9 );
  CPPUNIT_ASSERT_EQUAL( (v7[2]).y(), 11 );
}


// ----------------------------------------------------------------------
