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
 * @file  GenQgarPolygonTest.cpp
 * @brief Implementation of class GenQgarPolygonTest.
 *
 *        See file GenQgarPolygonTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   March 24, 2004  18:11
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenQgarPolygonTest.cpp,v 1.6 2005/07/13 16:29:34 masini Exp $ */



// STD
#include <deque>
#include <list>
#include <vector>
// QGAR
#include <qgarlib/primitives.h>
// QGAR TESTS
#include "GenQgarPolygonTest.h"



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
cmp(const GenQgarPolygon<T>& qpoly1, const GenQgarPolygon<T>& qPoly2)
{
  const deque< GenPoint<T> >& dv1 = qpoly1.accessVertices();
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
    && (qpoly1.accessSource() == dv1.front())
    && (qpoly1.accessTarget() == dv1.back())
    && (qpoly1.accessSource() == qPoly2.accessSource())
    && (qpoly1.accessTarget() == qPoly2.accessTarget());
}


} // unnamed namespace


// ------------------------------------------------------------------
// T E S T   F I X T U R E   I M P L E M E N T A T I O N
// ------------------------------------------------------------------


void
GenQgarPolygonTest::setUp()
{
  // Initialize Points

  _iPt0 = IPoint(16, 4);
  _iPt1 = IPoint(-4, -9);
  _iPt2 = IPoint(78, 55);
  _iPt3 = IPoint(-11, 53);

  _fPt0 = FPoint(4.14F, 9.1F);
  _fPt1 = FPoint(-4.46F, -13.59);
  _fPt2 = FPoint(3.178F, 5.25F);
  _fPt3 = FPoint(-1.11F, 5.173F);

  _dPt0 = DPoint(0.876, 0.298);
  _dPt1 = DPoint(-9.190, -4.894);
  _dPt2 = DPoint(0.84, 37.38);
  _dPt3 = DPoint(-1.0941, 53.984);

  // Initialize Point Lists
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
GenQgarPolygonTest::tearDown()
{
  /* EMPTY */
}


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


void
GenQgarPolygonTest::testDefaultConstructor()
{
  // ------
  // Set Up
  // ------

  IQgarPolygon iqPoly0;
  IQgarPolygon iqPoly(2);
  FQgarPolygon fqPoly(3, QGE_COLOR_BLUE);
  DQgarPolygon dqPoly(4, QGE_COLOR_RED, QGE_OUTLINE_DOT);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqPoly0.thickness() == 1 );
  CPPUNIT_ASSERT( iqPoly0.color()     == QGE_COLOR_DEFAULT);
  CPPUNIT_ASSERT( iqPoly0.outline()   == QGE_OUTLINE_DEFAULT);
  CPPUNIT_ASSERT( (iqPoly0.accessVertices()).empty() );

  CPPUNIT_ASSERT( iqPoly.thickness() == 2 );
  CPPUNIT_ASSERT( iqPoly.color()     == QGE_COLOR_DEFAULT);
  CPPUNIT_ASSERT( iqPoly.outline()   == QGE_OUTLINE_DEFAULT);
  CPPUNIT_ASSERT( (iqPoly.accessVertices()).empty() );

  CPPUNIT_ASSERT( fqPoly.thickness() == 3 );
  CPPUNIT_ASSERT( fqPoly.color()     == QGE_COLOR_BLUE);
  CPPUNIT_ASSERT( fqPoly.outline()   == QGE_OUTLINE_DEFAULT);
  CPPUNIT_ASSERT( (fqPoly.accessVertices()).empty() );

  CPPUNIT_ASSERT( dqPoly.thickness() == 4 );
  CPPUNIT_ASSERT( dqPoly.color()     == QGE_COLOR_RED);
  CPPUNIT_ASSERT( dqPoly.outline()   == QGE_OUTLINE_DOT);
  CPPUNIT_ASSERT( (dqPoly.accessVertices()).empty() );
}


void
GenQgarPolygonTest::testCopyConstructor()
{
  // Triangle:  (1,2) (3,4) (5,6)
  //            ^^^^^       ^^^^^
  //            source      target

  list<Point> lp;
  lp.push_back(Point(1,2));
  lp.push_back(Point(3,4));
  lp.push_back(Point(5,6));

  // Create polygon and copy
  QgarPolygon plg(lp, 2, QGE_COLOR_CYAN, QGE_OUTLINE_DASH_LSS);
  QgarPolygon cplg(plg);

  // Check copy
  // Check source and target
  CPPUNIT_ASSERT_EQUAL( cplg.xSource(), 1);
  CPPUNIT_ASSERT_EQUAL( cplg.ySource(), 2);
  CPPUNIT_ASSERT_EQUAL( cplg.xTarget(), 5);
  CPPUNIT_ASSERT_EQUAL( cplg.yTarget(), 6);

  // Check vertices
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

  // Check attributes
  CPPUNIT_ASSERT( plg.thickness() == 2                    );
  CPPUNIT_ASSERT( plg.color()     == QGE_COLOR_CYAN       );
  CPPUNIT_ASSERT( plg.outline()   == QGE_OUTLINE_DASH_LSS );
}


void
GenQgarPolygonTest::testBuildFromPolygon()
{
  // DEFAULT ATTRIBUTES
  // ==================

  // Triangle:  (1,2) (3,4) (5,6)
  //            ^^^^^       ^^^^^
  //            source      target

  list<Point> lp;
  lp.push_back(Point(1,2));
  lp.push_back(Point(3,4));
  lp.push_back(Point(5,6));

  // Create polygon and copy with default attributes
  Polygon plg(lp);
  QgarPolygon cplg(plg);

  // Check copy
  // Check source and target
  CPPUNIT_ASSERT_EQUAL( cplg.xSource(), 1);
  CPPUNIT_ASSERT_EQUAL( cplg.ySource(), 2);
  CPPUNIT_ASSERT_EQUAL( cplg.xTarget(), 5);
  CPPUNIT_ASSERT_EQUAL( cplg.yTarget(), 6);

  // Check vertices
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

  // Check attributes
  CPPUNIT_ASSERT( cplg.thickness() == 1                   );
  CPPUNIT_ASSERT( cplg.color()     == QGE_COLOR_DEFAULT   );
  CPPUNIT_ASSERT( cplg.outline()   == QGE_OUTLINE_DEFAULT );

  // GIVEN ATTRIBUTES
  // ================

  QgarPolygon cplg1(plg, 2);
  QgarPolygon cplg2(plg, 2, QGE_COLOR_YELLOW);
  QgarPolygon cplg3(plg, 2, QGE_COLOR_YELLOW, QGE_OUTLINE_DASH_LSS);

  // Check copies
  // Check source and target
  CPPUNIT_ASSERT_EQUAL( cplg1.xSource(), 1);
  CPPUNIT_ASSERT_EQUAL( cplg1.ySource(), 2);
  CPPUNIT_ASSERT_EQUAL( cplg1.xTarget(), 5);
  CPPUNIT_ASSERT_EQUAL( cplg1.yTarget(), 6);

  CPPUNIT_ASSERT_EQUAL( cplg2.xSource(), 1);
  CPPUNIT_ASSERT_EQUAL( cplg2.ySource(), 2);
  CPPUNIT_ASSERT_EQUAL( cplg2.xTarget(), 5);
  CPPUNIT_ASSERT_EQUAL( cplg2.yTarget(), 6);

  CPPUNIT_ASSERT_EQUAL( cplg3.xSource(), 1);
  CPPUNIT_ASSERT_EQUAL( cplg3.ySource(), 2);
  CPPUNIT_ASSERT_EQUAL( cplg3.xTarget(), 5);
  CPPUNIT_ASSERT_EQUAL( cplg3.yTarget(), 6);

  // Check vertices
  CPPUNIT_ASSERT_EQUAL( (int)cplg1.size(), 3);
  const deque<Point>& vv1 = cplg1.accessVertices();
  deque<Point>::const_iterator itV1 = vv1.begin();
  CPPUNIT_ASSERT_EQUAL( itV1->x(), 1);
  CPPUNIT_ASSERT_EQUAL( itV1->y(), 2);
  ++itV1;
  CPPUNIT_ASSERT_EQUAL( itV1->x(), 3);
  CPPUNIT_ASSERT_EQUAL( itV1->y(), 4);
  ++itV1;
  CPPUNIT_ASSERT_EQUAL( itV1->x(), 5);
  CPPUNIT_ASSERT_EQUAL( itV1->y(), 6);

  CPPUNIT_ASSERT_EQUAL( (int)cplg2.size(), 3);
  const deque<Point>& vv2 = cplg2.accessVertices();
  deque<Point>::const_iterator itV2 = vv2.begin();
  CPPUNIT_ASSERT_EQUAL( itV2->x(), 1);
  CPPUNIT_ASSERT_EQUAL( itV2->y(), 2);
  ++itV2;
  CPPUNIT_ASSERT_EQUAL( itV2->x(), 3);
  CPPUNIT_ASSERT_EQUAL( itV2->y(), 4);
  ++itV2;
  CPPUNIT_ASSERT_EQUAL( itV2->x(), 5);
  CPPUNIT_ASSERT_EQUAL( itV2->y(), 6);

  CPPUNIT_ASSERT_EQUAL( (int)cplg3.size(), 3);
  const deque<Point>& vv3 = cplg3.accessVertices();
  deque<Point>::const_iterator itV3 = vv3.begin();
  CPPUNIT_ASSERT_EQUAL( itV3->x(), 1);
  CPPUNIT_ASSERT_EQUAL( itV3->y(), 2);
  ++itV3;
  CPPUNIT_ASSERT_EQUAL( itV3->x(), 3);
  CPPUNIT_ASSERT_EQUAL( itV3->y(), 4);
  ++itV3;
  CPPUNIT_ASSERT_EQUAL( itV3->x(), 5);
  CPPUNIT_ASSERT_EQUAL( itV3->y(), 6);

  // Check attributes
  CPPUNIT_ASSERT( cplg1.thickness() == 2                   );
  CPPUNIT_ASSERT( cplg1.color()     == QGE_COLOR_DEFAULT   );
  CPPUNIT_ASSERT( cplg1.outline()   == QGE_OUTLINE_DEFAULT );

  CPPUNIT_ASSERT( cplg2.thickness() == 2                   );
  CPPUNIT_ASSERT( cplg2.color()     == QGE_COLOR_YELLOW    );
  CPPUNIT_ASSERT( cplg2.outline()   == QGE_OUTLINE_DEFAULT );

  CPPUNIT_ASSERT( cplg3.thickness() == 2                    );
  CPPUNIT_ASSERT( cplg3.color()     == QGE_COLOR_YELLOW     );
  CPPUNIT_ASSERT( cplg3.outline()   == QGE_OUTLINE_DASH_LSS );
}


void
GenQgarPolygonTest::testBuildFromPointList()
{
  // Triangle:  (1,2) (3,4) (5,6)
  //            ^^^^^       ^^^^^
  //            source      target

  list<Point> lp;
  lp.push_back(Point(1,2));
  lp.push_back(Point(3,4));
  lp.push_back(Point(5,6));

  // DEFAULT ATTRIBUTES
  // ==================

  QgarPolygon plg(lp);

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

  // Check (default) attributes
  CPPUNIT_ASSERT( plg.thickness() == 1                   );
  CPPUNIT_ASSERT( plg.color()     == QGE_COLOR_DEFAULT   );
  CPPUNIT_ASSERT( plg.outline()   == QGE_OUTLINE_DEFAULT );

  // EXPLICITELY SPECIFIED ATTRIBUTES
  // ================================

  QgarPolygon plg1(lp, 2);
  QgarPolygon plg2(lp, 2, QGE_COLOR_YELLOW);
  QgarPolygon plg3(lp, 2, QGE_COLOR_YELLOW, QGE_OUTLINE_DASH_LSS);

  // Check copies
  // Check source and target
  CPPUNIT_ASSERT_EQUAL( plg1.xSource(), 1);
  CPPUNIT_ASSERT_EQUAL( plg1.ySource(), 2);
  CPPUNIT_ASSERT_EQUAL( plg1.xTarget(), 5);
  CPPUNIT_ASSERT_EQUAL( plg1.yTarget(), 6);

  CPPUNIT_ASSERT_EQUAL( plg2.xSource(), 1);
  CPPUNIT_ASSERT_EQUAL( plg2.ySource(), 2);
  CPPUNIT_ASSERT_EQUAL( plg2.xTarget(), 5);
  CPPUNIT_ASSERT_EQUAL( plg2.yTarget(), 6);

  CPPUNIT_ASSERT_EQUAL( plg3.xSource(), 1);
  CPPUNIT_ASSERT_EQUAL( plg3.ySource(), 2);
  CPPUNIT_ASSERT_EQUAL( plg3.xTarget(), 5);
  CPPUNIT_ASSERT_EQUAL( plg3.yTarget(), 6);

  // Check vertices
  CPPUNIT_ASSERT_EQUAL( (int)plg1.size(), 3);
  const deque<Point>& vv1 = plg1.accessVertices();
  deque<Point>::const_iterator itV1 = vv1.begin();
  CPPUNIT_ASSERT_EQUAL( itV1->x(), 1);
  CPPUNIT_ASSERT_EQUAL( itV1->y(), 2);
  ++itV1;
  CPPUNIT_ASSERT_EQUAL( itV1->x(), 3);
  CPPUNIT_ASSERT_EQUAL( itV1->y(), 4);
  ++itV1;
  CPPUNIT_ASSERT_EQUAL( itV1->x(), 5);
  CPPUNIT_ASSERT_EQUAL( itV1->y(), 6);

  CPPUNIT_ASSERT_EQUAL( (int)plg2.size(), 3);
  const deque<Point>& vv2 = plg2.accessVertices();
  deque<Point>::const_iterator itV2 = vv2.begin();
  CPPUNIT_ASSERT_EQUAL( itV2->x(), 1);
  CPPUNIT_ASSERT_EQUAL( itV2->y(), 2);
  ++itV2;
  CPPUNIT_ASSERT_EQUAL( itV2->x(), 3);
  CPPUNIT_ASSERT_EQUAL( itV2->y(), 4);
  ++itV2;
  CPPUNIT_ASSERT_EQUAL( itV2->x(), 5);
  CPPUNIT_ASSERT_EQUAL( itV2->y(), 6);

  CPPUNIT_ASSERT_EQUAL( (int)plg3.size(), 3);
  const deque<Point>& vv3 = plg3.accessVertices();
  deque<Point>::const_iterator itV3 = vv3.begin();
  CPPUNIT_ASSERT_EQUAL( itV3->x(), 1);
  CPPUNIT_ASSERT_EQUAL( itV3->y(), 2);
  ++itV3;
  CPPUNIT_ASSERT_EQUAL( itV3->x(), 3);
  CPPUNIT_ASSERT_EQUAL( itV3->y(), 4);
  ++itV3;
  CPPUNIT_ASSERT_EQUAL( itV3->x(), 5);
  CPPUNIT_ASSERT_EQUAL( itV3->y(), 6);

  // Check attributes
  CPPUNIT_ASSERT( plg1.thickness() == 2                   );
  CPPUNIT_ASSERT( plg1.color()     == QGE_COLOR_DEFAULT   );
  CPPUNIT_ASSERT( plg1.outline()   == QGE_OUTLINE_DEFAULT );

  CPPUNIT_ASSERT( plg2.thickness() == 2                   );
  CPPUNIT_ASSERT( plg2.color()     == QGE_COLOR_YELLOW    );
  CPPUNIT_ASSERT( plg2.outline()   == QGE_OUTLINE_DEFAULT );

  CPPUNIT_ASSERT( plg3.thickness() == 2                     );
  CPPUNIT_ASSERT( plg3.color()     == QGE_COLOR_YELLOW      );
  CPPUNIT_ASSERT( plg3.outline()   == QGE_OUTLINE_DASH_LSS );
}


void
GenQgarPolygonTest::testBuildFromPointListExc()
{
  // List with 2 points

  list<Point> lp;
  lp.push_back(Point(1,2));
  lp.push_back(Point(3,4));

  // Should raise a QgaErrorUser exception:
  // The list of points must include at least 3 elements
  QgarPolygon plg(lp, 7, QGE_COLOR_RED, QGE_OUTLINE_DASH_LSS);
}



// -------------------------------------------------------------------
// C O P Y
// -------------------------------------------------------------------


void
GenQgarPolygonTest::testClone()
{
  // Triangle:  (1,2) (3,4) (5,6)
  //            ^^^^^       ^^^^^
  //            source      target

  list<Point> lp;
  lp.push_back(Point(1,2));
  lp.push_back(Point(3,4));
  lp.push_back(Point(5,6));

  // Create polygon and copy
  QgarPolygon plg(lp, 6, QGE_COLOR_GRAY, QGE_OUTLINE_DASH_SS);
  QgarPolygon* cplg = plg.clone();

  // Check copy
  // Check source and target
  CPPUNIT_ASSERT_EQUAL( cplg->xSource(), 1);
  CPPUNIT_ASSERT_EQUAL( cplg->ySource(), 2);
  CPPUNIT_ASSERT_EQUAL( cplg->xTarget(), 5);
  CPPUNIT_ASSERT_EQUAL( cplg->yTarget(), 6);

  // Check vertices
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

  // Check attributes
  CPPUNIT_ASSERT( plg.thickness() == 6                   );
  CPPUNIT_ASSERT( plg.color()     == QGE_COLOR_GRAY      );
  CPPUNIT_ASSERT( plg.outline()   == QGE_OUTLINE_DASH_SS );
}


// -------------------------------------------------------------------
// O P E R A T O R S
// -------------------------------------------------------------------


void
GenQgarPolygonTest::testAssignment()
{
  // Triangle:  (1,2) (3,4) (5,6)
  //            ^^^^^       ^^^^^
  //            source      target

  list<Point> lp;
  lp.push_back(Point(1,2));
  lp.push_back(Point(3,4));
  lp.push_back(Point(5,6));

  // Create polygon and copy
  QgarPolygon plg(lp, 5, QGE_COLOR_BROWN, QGE_OUTLINE_DASH_SS);
  QgarPolygon cplg = plg;

  // Check copy
  // Check source and target
  CPPUNIT_ASSERT_EQUAL( cplg.xSource(), 1);
  CPPUNIT_ASSERT_EQUAL( cplg.ySource(), 2);
  CPPUNIT_ASSERT_EQUAL( cplg.xTarget(), 5);
  CPPUNIT_ASSERT_EQUAL( cplg.yTarget(), 6);

  // Check vertices
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

  // Check attributes
  CPPUNIT_ASSERT( plg.thickness() == 5                   );
  CPPUNIT_ASSERT( plg.color()     == QGE_COLOR_BROWN     );
  CPPUNIT_ASSERT( plg.outline()   == QGE_OUTLINE_DASH_SS );

  // Ensure that function returns a valid reference on 'this'.
  CPPUNIT_ASSERT( &cplg == &(cplg = plg) );
}


// -------------------------------------------------------------------
// A R E A
// -------------------------------------------------------------------


void
GenQgarPolygonTest::testArea()
{
  // RECTANGLE TRIANGLE, VERTICES IN CLOCKWISE ORDER
  // (1,1) (1,4) (4,4)
 
  list<Point> lp;
  lp.push_back(Point(1,1));
  lp.push_back(Point(1,4));
  lp.push_back(Point(4,4));
  QgarPolygon plg(lp, 22, QGE_COLOR_WHITE, QGE_OUTLINE_DASH_SS);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 4.5, 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), -4.5, 0. );

  ////////////////////////////////////////////////////////////////////////////

  // SAME RECTANGLE TRIANGLE, VERTICES IN COUNTER-CLOCKWISE ORDER

  lp.reverse();
  plg = QgarPolygon(lp, 2, QGE_COLOR_RED);

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
  plg = QgarPolygon(lp, 9);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 9., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), -9., 0. );

  ////////////////////////////////////////////////////////////////////////////

  // SQUARE, COUNTER-CLOCKWISE VERTICES

  lp.reverse();
  plg = QgarPolygon(lp, 12, QGE_COLOR_BLUE, QGE_OUTLINE_SOLID);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 9., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), 9., 0. );

  ////////////////////////////////////////////////////////////////////////////

  // SQUARE WITH ALIGNED VERTICES, COUNTER-CLOCKWISE VERTICES
  // (4,1) (4,4) (1,4) (1,1) (2,1) (3,1)

  lp.push_back(Point(2,1));
  lp.push_back(Point(3,1));
  plg = QgarPolygon(lp);

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
  plg = QgarPolygon(lp);
  
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 38., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), -38., 0. );

  ////////////////////////////////////////////////////////////////////////////

  // CONVEX POLYGON, COUNTER-CLOCKWISE VERTICES

  lp.reverse();
  plg = QgarPolygon(lp, 4, QGE_COLOR_GREEN, QGE_OUTLINE_DOT);

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
  plg = QgarPolygon(lp, 6, QGE_COLOR_CYAN);
  
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 80.5, 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), -80.5, 0. );

  ////////////////////////////////////////////////////////////////////////////

  // CONCAVE POLYGON, COUNTER-CLOCKWISE VERTICES

  lp.reverse();
  plg = QgarPolygon(lp, 28);
  
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
  plg = QgarPolygon(lp, 3, QGE_COLOR_BLACK, QGE_OUTLINE_DASH_SS);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 30., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), -30., 0. );

  ////////////////////////////////////////////////////////////////////////////

  // CONCAVE POLYGON (CROSS) WITH ALIGNED VERTICES, COUNTER-CLOCKWISE VERTICES

  lp.reverse();
  plg = QgarPolygon(lp);

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
  plg = QgarPolygon(lp, 3, QGE_COLOR_RED);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 8., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), -8., 0. );

  ////////////////////////////////////////////////////////////////////////////

  // CONCAVE POLYGON WITH NON-CONSECUTIVE DUPLICATE POINTS (BUTTERFLY)
  // COUNTER-CLOCKWISE VERTICES

  lp.reverse();
  plg = QgarPolygon(lp, 2, QGE_COLOR_BROWN, QGE_OUTLINE_DASH_LSS);

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
  plg = QgarPolygon(lp, 20);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 16., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), -16., 0. );

  ////////////////////////////////////////////////////////////////////////////

  // SQUARE WITH CONSECUTIVE DUPLICATE VERTICES, COUNTER-CLOCKWISE VERTICES

  lp.reverse();
  plg = QgarPolygon(lp, 1, QGE_COLOR_GRAY);

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
  plg = QgarPolygon(lp, 14, QGE_COLOR_YELLOW, QGE_OUTLINE_DASH_REGULAR);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 4.5, 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), -4.5, 0. );

  ////////////////////////////////////////////////////////////////////////////

  // RECTANGLE TRIANGLE PLUS TWO OVERLAPPING SIDES, COUNTER-CLOCKWISE VERTICES

  lp.reverse();
  plg = QgarPolygon(lp, 5);

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
  plg = QgarPolygon(lp, 10, QGE_COLOR_PINK, QGE_OUTLINE_DASH_SPACED);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 36., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), 36., 0. );

  ////////////////////////////////////////////////////////////////////////////

  // SQUARE WITH NEGATIVE COORDINATES, COUNTER-CLOCKWISE VERTICES

  lp.reverse();
  plg = QgarPolygon(lp);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.area(), 36., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( plg.signedArea(), -36., 0. );
}


// -------------------------------------------------------------------
// A C C E S S   T O   V E R T I C E S
// -------------------------------------------------------------------


void
GenQgarPolygonTest::testSize()
{
  // ------
  // Set Up
  // ------
  
  // Empty polygon
  IQgarPolygon iqPoly(7);

  // Polygon with 4 vertices
  DQgarPolygon dqPoly(_dPtList, 20, QGE_COLOR_RED, QGE_OUTLINE_DASH_SPACED);

  // ------
  // Set Up
  // ------

  int si = iqPoly.size();
  int sd = dqPoly.size();

  // -------
  // Process
  // -------

  CPPUNIT_ASSERT_EQUAL( si, 0 );
  CPPUNIT_ASSERT_EQUAL( sd, 4 );
}


void
GenQgarPolygonTest::testGetVertices()
{
  // ------
  // Set Up
  // ------
  
  // A polygon and a copy of it
  IQgarPolygon iqPoly(_iPtList, 20, QGE_COLOR_RED);

  // The vertices of the polygon
  deque<IPoint>& id = iqPoly.getVertices();

  // ------
  // Set Up
  // ------

  int os = iqPoly.size();

  // Modification of the vertices
  id.push_back(_iPt0);

  int ns = iqPoly.size();

  // -------
  // Process
  // -------

  // The polygon has one more vertex
  CPPUNIT_ASSERT_EQUAL( ns, os + 1 );
  CPPUNIT_ASSERT( (iqPoly.accessVertices()).back() == _iPt0 );
}


// -------------------------------------------------------------------
// I N S E R T   V E R T I C E S
// -------------------------------------------------------------------


void
GenQgarPolygonTest::testAppend()
{
  // ---------------
  // APPEND A SOURCE
  // --------------

  IPoint iPt(1, 5);
  FPoint fPt(2.2f, 4.71f);
  DPoint dPt(41.14, 9.212);
  
  IQgarPolygon iqPoly(_iPtList, 10, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);
  FQgarPolygon fqPoly(_fPtList, 20, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);
  DQgarPolygon dqPoly(_dPtList, 30, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);

  iqPoly.appendSource(iPt);
  fqPoly.appendSource(fPt);
  dqPoly.appendSource(dPt);

  // CHECK

  // Nb of vertices
  CPPUNIT_ASSERT_EQUAL( iqPoly.size(), (int) _iPtList.size() + 1 );
  CPPUNIT_ASSERT_EQUAL( fqPoly.size(), (int) _fPtList.size() + 1 );
  CPPUNIT_ASSERT_EQUAL( dqPoly.size(), (int) _dPtList.size() + 1 );

  // Attributes
  CPPUNIT_ASSERT( iqPoly.thickness() == 10 );
  CPPUNIT_ASSERT( iqPoly.color()     == QGE_COLOR_BLUE);
  CPPUNIT_ASSERT( iqPoly.outline()   == QGE_OUTLINE_DASH_SS);

  CPPUNIT_ASSERT( fqPoly.thickness() == 20 );
  CPPUNIT_ASSERT( fqPoly.color()     == QGE_COLOR_BLUE);
  CPPUNIT_ASSERT( fqPoly.outline()   == QGE_OUTLINE_DASH_SS);

  CPPUNIT_ASSERT( dqPoly.thickness() == 30 );
  CPPUNIT_ASSERT( dqPoly.color()     == QGE_COLOR_BLUE);
  CPPUNIT_ASSERT( dqPoly.outline()   == QGE_OUTLINE_DASH_SS);

  // Sources
  CPPUNIT_ASSERT( iqPoly.source() == iPt );
  CPPUNIT_ASSERT( fqPoly.source() == fPt );
  CPPUNIT_ASSERT( dqPoly.source() == dPt );

  // Targets
  CPPUNIT_ASSERT( iqPoly.target() == _iPtList.back() );
  CPPUNIT_ASSERT( fqPoly.target() == _fPtList.back() );
  CPPUNIT_ASSERT( dqPoly.target() == _dPtList.back() );

  // Vertices
  _iPtList.push_front(iPt);
  CPPUNIT_ASSERT( cmp(iqPoly, IQgarPolygon(_iPtList)) );
  _fPtList.push_front(fPt);
  CPPUNIT_ASSERT( cmp(fqPoly, FQgarPolygon(_fPtList)) );
  _dPtList.push_front(dPt);
  CPPUNIT_ASSERT( cmp(dqPoly, DQgarPolygon(_dPtList)) );

  // Ensure that function returns a valid reference on 'this'
  CPPUNIT_ASSERT( &iqPoly == &(iqPoly.appendSource(iPt)) );
  CPPUNIT_ASSERT( &fqPoly == &(fqPoly.appendSource(fPt)) );
  CPPUNIT_ASSERT( &dqPoly == &(dqPoly.appendSource(dPt)) );


  // ---------------
  // APPEND A TARGET
  // ---------------

  IPoint iPt0(3, 7);
  FPoint fPt0(8.21f, 1.07f);
  DPoint dPt0(1.678, 212.89);
  
  IQgarPolygon iqPoly0(_iPtList, 1, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);
  FQgarPolygon fqPoly0(_fPtList, 2, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);
  DQgarPolygon dqPoly0(_dPtList, 3, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);

  iqPoly0.appendTarget(iPt0);
  fqPoly0.appendTarget(fPt0);
  dqPoly0.appendTarget(dPt0);

  // CHECK

  // Nb of vertices
  CPPUNIT_ASSERT_EQUAL( iqPoly0.size(), (int) _iPtList.size() + 1 );
  CPPUNIT_ASSERT_EQUAL( fqPoly0.size(), (int) _fPtList.size() + 1 );
  CPPUNIT_ASSERT_EQUAL( dqPoly0.size(), (int) _dPtList.size() + 1 );

  // Attributes
  CPPUNIT_ASSERT( iqPoly0.thickness() == 1                   );
  CPPUNIT_ASSERT( iqPoly0.color()     == QGE_COLOR_BLUE      );
  CPPUNIT_ASSERT( iqPoly0.outline()   == QGE_OUTLINE_DASH_SS );

  CPPUNIT_ASSERT( fqPoly0.thickness() == 2                   );
  CPPUNIT_ASSERT( fqPoly0.color()     == QGE_COLOR_BLUE      );
  CPPUNIT_ASSERT( fqPoly0.outline()   == QGE_OUTLINE_DASH_SS );

  CPPUNIT_ASSERT( dqPoly0.thickness() == 3                   );
  CPPUNIT_ASSERT( dqPoly0.color()     == QGE_COLOR_BLUE      );
  CPPUNIT_ASSERT( dqPoly0.outline()   == QGE_OUTLINE_DASH_SS );

  // Sources
  CPPUNIT_ASSERT( iqPoly0.source() == _iPtList.front() );
  CPPUNIT_ASSERT( fqPoly0.source() == _fPtList.front() );
  CPPUNIT_ASSERT( dqPoly0.source() == _dPtList.front() );

  // Targets
  CPPUNIT_ASSERT( iqPoly0.target() == iPt0 );
  CPPUNIT_ASSERT( fqPoly0.target() == fPt0 );
  CPPUNIT_ASSERT( dqPoly0.target() == dPt0 );

  // Vertices
  _iPtList.push_back(iPt0);
  CPPUNIT_ASSERT( cmp(iqPoly0, IQgarPolygon(_iPtList)) );
  _fPtList.push_back(fPt0);
  CPPUNIT_ASSERT( cmp(fqPoly0, FQgarPolygon(_fPtList)) );
  _dPtList.push_back(dPt0);
  CPPUNIT_ASSERT( cmp(dqPoly0, DQgarPolygon(_dPtList)) );

  // Ensure that function returns a valid reference on 'this'
  CPPUNIT_ASSERT( &iqPoly0 == &(iqPoly0.appendSource(iPt0)) );
  CPPUNIT_ASSERT( &fqPoly0 == &(fqPoly0.appendSource(fPt0)) );
  CPPUNIT_ASSERT( &dqPoly0 == &(dqPoly0.appendSource(dPt0)) );


  // -------------------------
  // APPEND A VECTOR OF POINTS
  // -------------------------

  // A Qgar polygon
  IQgarPolygon iqPoly1(_iPtList, 2, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);
  
  // A vector of points
  IPoint iPt1(-43, 1);
  IPoint iPt2(4, 2);
  IPoint iPt3(9, -5);
  IPoint iPt4(6, 15);
  vector<IPoint> ptVect;
  ptVect.push_back(iPt1);
  ptVect.push_back(iPt2);
  ptVect.push_back(iPt3);
  ptVect.push_back(iPt4);

  // The model of the resulting polygon
  list<IPoint> imodList(_iPtList);
  imodList.push_back(iPt1);
  imodList.push_back(iPt2);
  imodList.push_back(iPt3);
  imodList.push_back(iPt4);
  IQgarPolygon iqModPoly(imodList, 2, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);

  // Process

  iqPoly1.append(ptVect);

  // CHECK

  // Ensure that color, thickness, outline are not modified.
  CPPUNIT_ASSERT( iqPoly1.thickness() == 2 );
  CPPUNIT_ASSERT( iqPoly1.color()     == QGE_COLOR_BLUE );
  CPPUNIT_ASSERT( iqPoly1.outline()   == QGE_OUTLINE_DASH_SS );

  // Ensure that the resulting polygon conforms to the model
  CPPUNIT_ASSERT( cmp(iqPoly1, iqModPoly) );

  // Ensure that the function returns a valid reference to 'this'
  CPPUNIT_ASSERT( &iqPoly1 == &(iqPoly1.append(ptVect)) );    
}


// -------------------------------------------------------------------
// R E M O V E   V E R T I C E S
// -------------------------------------------------------------------


void
GenQgarPolygonTest::testRemoveVertex()
{
  // ------
  // Set Up
  // ------

  IQgarPolygon       iQPoly(_iPtList, 3, QGE_COLOR_WHITE, QGE_OUTLINE_DASH_LS);
  IQgarPolygon iSourceQPoly(_iPtList, 4, QGE_COLOR_BLACK);
  IQgarPolygon iTargetQPoly(_iPtList, 5, QGE_COLOR_RED, QGE_OUTLINE_DASH_SS);

  // -------
  // Process
  // -------

  // Remove a point which is not the source neither the target
  iQPoly.remove(_iPt2);
  // The theoretical resulting vertices deque
  deque<IPoint> iDeq;
  iDeq.push_back(_iPt0);
  iDeq.push_back(_iPt1);
  iDeq.push_back(_iPt3);

  // Remove source point
  iSourceQPoly.remove( iSourceQPoly.source() );
  // The theoretical resulting vertices deque
  deque<IPoint> iSourceDeq;
  copy(++_iPtList.begin(), _iPtList.end(), back_inserter(iSourceDeq));

  // Remove target point
  iTargetQPoly.remove( iTargetQPoly.accessTarget() );

  // The theoretical resulting vertices deque
  deque<IPoint> iTargetDeq;
  copy(_iPtList.begin(), --_iPtList.end(), back_inserter(iTargetDeq));

  // -----
  // Check
  // -----

  // Ensure that thickness, color and outline are unchanged
  CPPUNIT_ASSERT( iQPoly.thickness()       == 3 );
  CPPUNIT_ASSERT( iSourceQPoly.thickness() == 4 );
  CPPUNIT_ASSERT( iTargetQPoly.thickness() == 5 );

  CPPUNIT_ASSERT( iQPoly.color()       == QGE_COLOR_WHITE );
  CPPUNIT_ASSERT( iSourceQPoly.color() == QGE_COLOR_BLACK );
  CPPUNIT_ASSERT( iTargetQPoly.color() == QGE_COLOR_RED   );

  CPPUNIT_ASSERT( iQPoly.outline()       == QGE_OUTLINE_DASH_LS );
  CPPUNIT_ASSERT( iSourceQPoly.outline() == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( iTargetQPoly.outline() == QGE_OUTLINE_DASH_SS );

  // Ensure that vertices lists are one element shorter
  CPPUNIT_ASSERT( iQPoly.size()       == (int) (_iPtList.size() - 1) );
  CPPUNIT_ASSERT( iSourceQPoly.size() == (int) (_iPtList.size() - 1) );
  CPPUNIT_ASSERT( iTargetQPoly.size() == (int) (_iPtList.size() - 1) );

  // Check that resulting vertices are correct
  CPPUNIT_ASSERT( iQPoly.source() == iDeq.front() );
  CPPUNIT_ASSERT( iQPoly.target() == iDeq.back() );
  CPPUNIT_ASSERT( cmp(iQPoly.accessVertices(), iDeq) );

  CPPUNIT_ASSERT( iSourceQPoly.source() == iSourceDeq.front() );
  CPPUNIT_ASSERT( iSourceQPoly.target() == iSourceDeq.back() );
  CPPUNIT_ASSERT( cmp(iSourceQPoly.accessVertices(), iSourceDeq) );

  CPPUNIT_ASSERT( iTargetQPoly.source() == iTargetDeq.front() );
  CPPUNIT_ASSERT( iTargetQPoly.target() == iTargetDeq.back() );
  CPPUNIT_ASSERT( cmp(iTargetQPoly.accessVertices(), iTargetDeq) );

  // Ensure that the function returns a valid reference to 'this'

  // Warning: A polygon always must be provided with 3 vertices
  iQPoly.appendTarget(_iPt0);

  CPPUNIT_ASSERT( &iQPoly == &(iQPoly.remove(_iPt1)) );
}


void
GenQgarPolygonTest::testRemoveVertexExc()
{
  // A polygon with 3 vertices

  qgar::FPoint fPt0(1.34f, 2.78f);
  qgar::FPoint fPt1(6.98f, 5.46f);
  qgar::FPoint fPt2(0.27f, 9.99f);

  std::list<qgar::FPoint> fPtList;
  fPtList.push_back(fPt0);
  fPtList.push_back(fPt1);
  fPtList.push_back(fPt2);
  FQgarPolygon fqPoly(fPtList, 6, QGE_COLOR_RED);

  // Removing a vertex should throw an exception
  fqPoly.remove(fPt0);
}


// -------------------------------------------------------------------
// C O N V E R S I O N S   O F   T H E   V E R T I C E S
// -------------------------------------------------------------------


void
GenQgarPolygonTest::testToPtVect()
{
  // ------
  // Set Up
  // ------

  IQgarPolygon iqPoly(_iPtList, 3, QGE_COLOR_RED, QGE_OUTLINE_SOLID);

  // -------
  // Process
  // -------
  
  vector<IPoint> ptVect = iqPoly.toPointVector();

  // -----
  // Check
  // -----
  
  // Thickness, color and outline are unchanged
  CPPUNIT_ASSERT( iqPoly.thickness() == 3 );
  CPPUNIT_ASSERT( iqPoly.color()     == QGE_COLOR_RED );
  CPPUNIT_ASSERT( iqPoly.outline()   == QGE_OUTLINE_SOLID );

  // The resulting vector has the same size as the polygon
  CPPUNIT_ASSERT( (int) ptVect.size() == iqPoly.size() );

  // The vector and the polygon include the same vertices
  deque<IPoint>::const_iterator itPoly = iqPoly.accessVertices().begin();
  vector<IPoint>::iterator itVect      = ptVect.begin();

  while( itVect != ptVect.end() )
    {
      CPPUNIT_ASSERT_EQUAL( *itVect++, *itPoly++);
    }
}


void
GenQgarPolygonTest::testToSegList()
{
  IQgarPolygon iqPoly(_iPtList, 3, QGE_COLOR_RED, QGE_OUTLINE_SOLID);

  // Theorectical list of segment extremities

  deque<IPoint> ptDeq = iqPoly.vertices();
  ptDeq.push_back(iqPoly.source());
  deque<IPoint>::iterator itPt;

  // -----------------
  // TO A SEGMENT LIST
  // -----------------

  list<ISegment> segList = iqPoly.toSegList();

  // CHECK

  // Thickness, color and outline are unchanged
  CPPUNIT_ASSERT( iqPoly.thickness() == 3 );
  CPPUNIT_ASSERT( iqPoly.color()     == QGE_COLOR_RED );
  CPPUNIT_ASSERT( iqPoly.outline()   == QGE_OUTLINE_SOLID );

  // Nb of segments is equal to nb of points
  CPPUNIT_ASSERT_EQUAL( (int) segList.size(), iqPoly.size() );

  // Do segments conform to polygon vertices?
  list<ISegment>::iterator itSeg = segList.begin();
  itPt = ptDeq.begin();

  while( itSeg != segList.end() )
    {
      IPoint pt = *itPt++;
      CPPUNIT_ASSERT( *itSeg++ == ISegment(pt, *itPt) );
    }

  // ----------------------
  // TO A QGAR SEGMENT LIST
  // ----------------------

  list<IQgarSegment> qSegList = iqPoly.toQgarSegList();

  // CHECK

  // Nb of segments is equals to nb of points
  CPPUNIT_ASSERT_EQUAL( (int) qSegList.size(), iqPoly.size() );

  // Do segments conform to polygon vertices?
  list<IQgarSegment>::iterator itQSeg = qSegList.begin();
  itPt = ptDeq.begin();

  while( itQSeg != qSegList.end() )
    {
      IPoint pt = *itPt++;
      CPPUNIT_ASSERT( (*itQSeg).equal(IQgarSegment(pt, *itPt, 3, QGE_COLOR_RED, QGE_OUTLINE_SOLID)) );
      ++itQSeg;
    }
}


// -------------------------------------------------------------------
// G E O M E T R Y :   T R A N S L A T I O N
// -------------------------------------------------------------------


void
GenQgarPolygonTest::testTranslate()
{
  // ------
  // Set Up
  // ------

  int tx = 27;
  int ty = -89005;

  IQgarPolygon iqPoly(_iPtList, 2, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);

  // -------
  // Process
  // -------

  iqPoly.translate(tx,ty);

  // -----
  // Check
  // -----

  // Thickness, color and outline are unchanged
  CPPUNIT_ASSERT( iqPoly.thickness() == 2 );
  CPPUNIT_ASSERT( iqPoly.color()     == QGE_COLOR_BLUE );
  CPPUNIT_ASSERT( iqPoly.outline()   == QGE_OUTLINE_DASH_SS );

  // Source and target are correctly translated
  IPoint s(_iPtList.front());
  s.translate(tx,ty);

  IPoint t(_iPtList.back());
  t.translate(tx,ty);

  CPPUNIT_ASSERT( iqPoly.accessSource() == s );
  CPPUNIT_ASSERT( iqPoly.accessTarget() == t );

  // Vertices are correctly translated
  const deque<IPoint>& dv = iqPoly.accessVertices();
  deque<IPoint>::const_iterator itPoly = dv.begin();

  list<IPoint>::const_iterator itList = _iPtList.begin();

  while( itPoly != dv.end() )
    {
      IPoint p(*itList);
      p.translate(tx,ty);

      CPPUNIT_ASSERT( *itPoly == p );
      ++itPoly;
      ++itList;
    }
}


// -------------------------------------------------------------------
// S E R I A L I Z A T I O N / D E S E R I A L I Z A T I O N
// -------------------------------------------------------------------


void
GenQgarPolygonTest::testSerializeDeserialize()
{
  // ------
  // Set Up
  // ------

  IQgarPolygon iqPoly(_iPtList, 2, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);
  FQgarPolygon fqPoly(_fPtList, 3, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);
  DQgarPolygon dqPoly(_dPtList, 4, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);

  IQgarPolygon iqOutInPoly;
  FQgarPolygon fqOutInPoly;
  DQgarPolygon dqOutInPoly;

  // -------
  // Process
  // -------

  std::stringstream ss;

  ss << iqPoly;
  ss >> iqOutInPoly;
  ss.flush();

  ss << fqPoly;
  ss >> fqOutInPoly;
  ss.flush();

  ss << dqPoly;
  ss >> dqOutInPoly;
  ss.flush();

  // -----
  // Check
  // -----

  // In and out polygons are provided with the same attributes
  CPPUNIT_ASSERT( iqPoly.thickness() == iqOutInPoly.thickness() );
  CPPUNIT_ASSERT( iqPoly.color()     == iqOutInPoly.color()     );
  CPPUNIT_ASSERT( iqPoly.outline()   == iqOutInPoly.outline()   );

  // In and out polygons are geometrically identical
  CPPUNIT_ASSERT( cmp(iqPoly, iqOutInPoly) );
  CPPUNIT_ASSERT( cmp(fqPoly, fqOutInPoly) );
  CPPUNIT_ASSERT( cmp(dqPoly, dqOutInPoly) );
}


// -------------------------------------------------------------------
// S O U R C E   A N D   T A R G E T   U P D A T E S
// -------------------------------------------------------------------


void
GenQgarPolygonTest::testUpdateSourceTarget()
{
  // Rectangle triangle
  // (1,1) (1,4) (4,4)
 
  list<Point> lp;
  lp.push_back(Point(1,1));
  lp.push_back(Point(1,4));
  lp.push_back(Point(4,4));
  IQgarPolygon pll(lp, 18, QGE_COLOR_WHITE, QGE_OUTLINE_DOT);

  // SET SOURCE POINT
  // ----------------
  pll.fixSource(Point(-1,-1));

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( pll.xSource(), -1 );
  CPPUNIT_ASSERT_EQUAL( pll.ySource(), -1 );
  CPPUNIT_ASSERT_EQUAL( pll.xTarget(),  4 );
  CPPUNIT_ASSERT_EQUAL( pll.yTarget(),  4 );
  // Check vertices
  const deque<Point>& v1 = pll.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (v1[0]).x(), -1 );
  CPPUNIT_ASSERT_EQUAL( (v1[0]).y(), -1 );
  CPPUNIT_ASSERT_EQUAL( (v1[1]).x(),  1 );
  CPPUNIT_ASSERT_EQUAL( (v1[1]).y(),  4 );
  CPPUNIT_ASSERT_EQUAL( (v1[2]).x(),  4 );
  CPPUNIT_ASSERT_EQUAL( (v1[2]).y(),  4 );

  // SET SOURCE COORDINATES
  // ----------------------
  pll.fixSource(-10,-10);

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( pll.xSource(), -10 );
  CPPUNIT_ASSERT_EQUAL( pll.ySource(), -10 );
  CPPUNIT_ASSERT_EQUAL( pll.xTarget(),  4  );
  CPPUNIT_ASSERT_EQUAL( pll.yTarget(),  4  );
  // Check vertices
  const deque<Point>& v10 = pll.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (v10[0]).x(), -10 );
  CPPUNIT_ASSERT_EQUAL( (v10[0]).y(), -10 );
  CPPUNIT_ASSERT_EQUAL( (v10[1]).x(),  1  );
  CPPUNIT_ASSERT_EQUAL( (v10[1]).y(),  4  );
  CPPUNIT_ASSERT_EQUAL( (v10[2]).x(),  4  );
  CPPUNIT_ASSERT_EQUAL( (v10[2]).y(),  4  );

  // SET TARGET POINT
  // ----------------
  pll.fixTarget(Point(6,5));

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( pll.xSource(), -10 );
  CPPUNIT_ASSERT_EQUAL( pll.ySource(), -10 );
  CPPUNIT_ASSERT_EQUAL( pll.xTarget(),  6 );
  CPPUNIT_ASSERT_EQUAL( pll.yTarget(),  5 );
  // Check vertices
  const deque<Point>& v2 = pll.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (v2[0]).x(), -10 );
  CPPUNIT_ASSERT_EQUAL( (v2[0]).y(), -10 );
  CPPUNIT_ASSERT_EQUAL( (v2[1]).x(),  1 );
  CPPUNIT_ASSERT_EQUAL( (v2[1]).y(),  4 );
  CPPUNIT_ASSERT_EQUAL( (v2[2]).x(),  6 );
  CPPUNIT_ASSERT_EQUAL( (v2[2]).y(),  5 );

  // SET TARGET COORDINATES
  // ----------------------
  pll.fixTarget(60,50);

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( pll.xSource(), -10 );
  CPPUNIT_ASSERT_EQUAL( pll.ySource(), -10 );
  CPPUNIT_ASSERT_EQUAL( pll.xTarget(),  60 );
  CPPUNIT_ASSERT_EQUAL( pll.yTarget(),  50 );
  // Check vertices
  const deque<Point>& v20 = pll.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (v20[0]).x(), -10 );
  CPPUNIT_ASSERT_EQUAL( (v20[0]).y(), -10 );
  CPPUNIT_ASSERT_EQUAL( (v20[1]).x(),   1 );
  CPPUNIT_ASSERT_EQUAL( (v20[1]).y(),   4 );
  CPPUNIT_ASSERT_EQUAL( (v20[2]).x(),  60 );
  CPPUNIT_ASSERT_EQUAL( (v20[2]).y(),  50 );

  // SET BOTH SOURCE & TARGET POINTS
  // -------------------------------
  pll.fixSourceTarget(Point(-2,-2), Point(10,10));

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( pll.xSource(), -2 );
  CPPUNIT_ASSERT_EQUAL( pll.ySource(), -2 );
  CPPUNIT_ASSERT_EQUAL( pll.xTarget(), 10 );
  CPPUNIT_ASSERT_EQUAL( pll.yTarget(), 10 );
  // Check vertices
  const deque<Point>& v3 = pll.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (v3[0]).x(), -2 );
  CPPUNIT_ASSERT_EQUAL( (v3[0]).y(), -2 );
  CPPUNIT_ASSERT_EQUAL( (v3[1]).x(),  1 );
  CPPUNIT_ASSERT_EQUAL( (v3[1]).y(),  4 );
  CPPUNIT_ASSERT_EQUAL( (v3[2]).x(), 10 );
  CPPUNIT_ASSERT_EQUAL( (v3[2]).y(), 10 );

  // SET BOTH SOURCE & TARGET COORDINATES
  // ------------------------------------
  pll.fixSourceTarget(Point(-20,-20), Point(20,20));

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( pll.xSource(), -20 );
  CPPUNIT_ASSERT_EQUAL( pll.ySource(), -20 );
  CPPUNIT_ASSERT_EQUAL( pll.xTarget(),  20 );
  CPPUNIT_ASSERT_EQUAL( pll.yTarget(),  20 );
  // Check vertices
  const deque<Point>& v30 = pll.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (v30[0]).x(), -20 );
  CPPUNIT_ASSERT_EQUAL( (v30[0]).y(), -20 );
  CPPUNIT_ASSERT_EQUAL( (v30[1]).x(),   1 );
  CPPUNIT_ASSERT_EQUAL( (v30[1]).y(),   4 );
  CPPUNIT_ASSERT_EQUAL( (v30[2]).x(),  20 );
  CPPUNIT_ASSERT_EQUAL( (v30[2]).y(),  20 );

  // SET X SOURCE
  // ------------
  pll.fixXSource(8);

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( pll.xSource(),   8 );
  CPPUNIT_ASSERT_EQUAL( pll.ySource(), -20 );
  CPPUNIT_ASSERT_EQUAL( pll.xTarget(),  20 );
  CPPUNIT_ASSERT_EQUAL( pll.yTarget(),  20 );
  // Check vertices
  const deque<Point>& v4 = pll.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (v4[0]).x(),   8 );
  CPPUNIT_ASSERT_EQUAL( (v4[0]).y(), -20 );
  CPPUNIT_ASSERT_EQUAL( (v4[1]).x(),   1 );
  CPPUNIT_ASSERT_EQUAL( (v4[1]).y(),   4 );
  CPPUNIT_ASSERT_EQUAL( (v4[2]).x(),  20 );
  CPPUNIT_ASSERT_EQUAL( (v4[2]).y(),  20 );

  // SET Y SOURCE
  // ------------
  pll.fixYSource(-8);

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( pll.xSource(),  8 );
  CPPUNIT_ASSERT_EQUAL( pll.ySource(), -8 );
  CPPUNIT_ASSERT_EQUAL( pll.xTarget(), 20 );
  CPPUNIT_ASSERT_EQUAL( pll.yTarget(), 20 );
  // Check vertices
  const deque<Point>& v5 = pll.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (v5[0]).x(),  8 );
  CPPUNIT_ASSERT_EQUAL( (v5[0]).y(), -8 );
  CPPUNIT_ASSERT_EQUAL( (v5[1]).x(),  1 );
  CPPUNIT_ASSERT_EQUAL( (v5[1]).y(),  4 );
  CPPUNIT_ASSERT_EQUAL( (v5[2]).x(), 20 );
  CPPUNIT_ASSERT_EQUAL( (v5[2]).y(), 20 );

  // SET X TARGET
  // ------------
  pll.fixXTarget(9);

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( pll.xSource(),  8 );
  CPPUNIT_ASSERT_EQUAL( pll.ySource(), -8 );
  CPPUNIT_ASSERT_EQUAL( pll.xTarget(),  9 );
  CPPUNIT_ASSERT_EQUAL( pll.yTarget(), 20 );
  // Check vertices
  const deque<Point>& v6 = pll.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (v6[0]).x(),  8 );
  CPPUNIT_ASSERT_EQUAL( (v6[0]).y(), -8 );
  CPPUNIT_ASSERT_EQUAL( (v6[1]).x(),  1 );
  CPPUNIT_ASSERT_EQUAL( (v6[1]).y(),  4 );
  CPPUNIT_ASSERT_EQUAL( (v6[2]).x(),  9 );
  CPPUNIT_ASSERT_EQUAL( (v6[2]).y(), 20 );

  // SET Y TARGET
  // ------------
  pll.fixYTarget(11);

  // Check source and target
  CPPUNIT_ASSERT_EQUAL( pll.xSource(),  8 );
  CPPUNIT_ASSERT_EQUAL( pll.ySource(), -8 );
  CPPUNIT_ASSERT_EQUAL( pll.xTarget(),  9 );
  CPPUNIT_ASSERT_EQUAL( pll.yTarget(), 11 );
  // Check vertices
  const deque<Point>& v7 = pll.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (v7[0]).x(),  8 );
  CPPUNIT_ASSERT_EQUAL( (v7[0]).y(), -8 );
  CPPUNIT_ASSERT_EQUAL( (v7[1]).x(),  1 );
  CPPUNIT_ASSERT_EQUAL( (v7[1]).y(),  4 );
  CPPUNIT_ASSERT_EQUAL( (v7[2]).x(),  9 );
  CPPUNIT_ASSERT_EQUAL( (v7[2]).y(), 11 );
}

// -------------------------------------------------------------------
