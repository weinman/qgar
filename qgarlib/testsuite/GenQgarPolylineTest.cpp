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
 * @file  GenQgarPolylineTest.cpp
 * @brief Implementation of class GenQgarPolylineTest
 *
 *        See file GenQgarPolylineTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 29, 2003  09:41
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenQgarPolylineTest.cpp,v 1.7 2005/07/13 16:29:34 masini Exp $ */



// QGAR
#include <qgarlib/primitives.h>
// QGAR TESTS
#include "GenQgarPolylineTest.h"



using namespace qgar;
using namespace std;



// ------------------------------------------------------------------
// U N N A M E D   N A M E S P A C E
// ------------------------------------------------------------------

namespace
{


template <class T>
bool
cmp(const GenQgarPolyline<T>& qPoly1, const GenQgarPolyline<T>& qPoly2)
{
  const deque< GenPoint<T> >& dv1 = qPoly1.accessVertices();
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
    && (qPoly1.accessSource() == dv1.front())
    && (qPoly1.accessTarget() == dv1.back())
    && (qPoly1.accessSource() == qPoly2.accessSource())
    && (qPoly1.accessTarget() == qPoly2.accessTarget());
}


template <class T>
bool
cmp(const GenQgarPolyline<T>& qPoly1, const GenPolyline<T>& poly2)
{
  const deque< GenPoint<T> >& dv1 = qPoly1.accessVertices();
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
    && (qPoly1.accessSource() == dv1.front())
    && (qPoly1.accessTarget() == dv1.back())
    && (qPoly1.accessSource() == poly2.accessSource())
    && (qPoly1.accessTarget() == poly2.accessTarget());
}


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


} // unnamed namespace


// ------------------------------------------------------------------
// T E S T    F I X T U R E   I M P L E M E N T A T I O N
// ------------------------------------------------------------------

void
GenQgarPolylineTest::setUp()
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
GenQgarPolylineTest::tearDown()
{
  /* EMPTY */
}


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------

void
GenQgarPolylineTest::testDefaultConstructor()
{
  // ------
  // Set Up
  // ------

  IQgarPolyline iqPoly0;
  IQgarPolyline iqPoly(2);
  FQgarPolyline fqPoly(3, QGE_COLOR_BLUE);
  DQgarPolyline dqPoly(4, QGE_COLOR_RED, QGE_OUTLINE_DOT);

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
GenQgarPolylineTest::testCopyConstructor()
{
  // ------
  // Set Up
  // ------

  IQgarPolyline iqPoly(_iPtList, 2);
  FQgarPolyline fqPoly(_fPtList, 3, QGE_COLOR_BLUE);
  DQgarPolyline dqPoly(_dPtList, 4, QGE_COLOR_RED, QGE_OUTLINE_DASH_SS);

  // -------
  // Process
  // -------

  IQgarPolyline iqDupPoly(iqPoly);
  FQgarPolyline fqDupPoly(fqPoly);
  DQgarPolyline dqDupPoly(dqPoly);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqDupPoly.thickness() == 2 );
  CPPUNIT_ASSERT( iqDupPoly.color()     == QGE_COLOR_DEFAULT);
  CPPUNIT_ASSERT( iqDupPoly.outline()   == QGE_OUTLINE_DEFAULT);
  CPPUNIT_ASSERT( cmp(iqDupPoly, iqPoly) );

  CPPUNIT_ASSERT( fqDupPoly.thickness() == 3 );
  CPPUNIT_ASSERT( fqDupPoly.color()     == QGE_COLOR_BLUE);
  CPPUNIT_ASSERT( fqDupPoly.outline()   == QGE_OUTLINE_DEFAULT);
  CPPUNIT_ASSERT( cmp(fqDupPoly, fqPoly) );

  CPPUNIT_ASSERT( dqDupPoly.thickness() == 4 );
  CPPUNIT_ASSERT( dqDupPoly.color()     == QGE_COLOR_RED);
  CPPUNIT_ASSERT( dqDupPoly.outline()   == QGE_OUTLINE_DASH_SS);
  CPPUNIT_ASSERT( cmp(dqDupPoly, dqPoly) );
}


void
GenQgarPolylineTest::testBuildFromPolyline()
{
  // ------
  // Set Up
  // ------

  IPolyline iPoly(_iPtList);
  FPolyline fPoly(_fPtList);
  DPolyline dPoly(_dPtList);
  
  // -------
  // Process
  // -------
  
  IQgarPolyline iqPoly0(iPoly);
  IQgarPolyline iqPoly(iPoly, 2);
  FQgarPolyline fqPoly(fPoly, 3, QGE_COLOR_BLUE);
  DQgarPolyline dqPoly(dPoly, 4, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqPoly0.thickness() == 1 );
  CPPUNIT_ASSERT( iqPoly0.color()     == QGE_COLOR_DEFAULT);
  CPPUNIT_ASSERT( iqPoly0.outline()   == QGE_OUTLINE_DEFAULT);
  CPPUNIT_ASSERT( cmp(iqPoly0, iPoly) );

  CPPUNIT_ASSERT( iqPoly.thickness() == 2 );
  CPPUNIT_ASSERT( iqPoly.color()     == QGE_COLOR_DEFAULT);
  CPPUNIT_ASSERT( iqPoly.outline()   == QGE_OUTLINE_DEFAULT);
  CPPUNIT_ASSERT( cmp(iqPoly, iPoly) );

  CPPUNIT_ASSERT( fqPoly.thickness() == 3 );
  CPPUNIT_ASSERT( fqPoly.color()     == QGE_COLOR_BLUE);
  CPPUNIT_ASSERT( fqPoly.outline()   == QGE_OUTLINE_DEFAULT);
  CPPUNIT_ASSERT( cmp(fqPoly, fPoly) );

  CPPUNIT_ASSERT( dqPoly.thickness() == 4 );
  CPPUNIT_ASSERT( dqPoly.color()     == QGE_COLOR_BLUE);
  CPPUNIT_ASSERT( dqPoly.outline()   == QGE_OUTLINE_DASH_SS);
  CPPUNIT_ASSERT( cmp(dqPoly, dPoly) );
}


void
GenQgarPolylineTest::testBuildFromQgarSegment()
{
  // ------
  // Set Up
  // ------

  IQgarSegment iqSeg(_iPt0, _iPt1, 2, QGE_COLOR_BLUE, QGE_OUTLINE_DOT);
  FQgarSegment fqSeg(_fPt0, _fPt1, 3, QGE_COLOR_BLUE, QGE_OUTLINE_DOT);
  DQgarSegment dqSeg(_dPt0, _dPt1, 4, QGE_COLOR_BLUE, QGE_OUTLINE_DOT);

  // -------
  // Process
  // -------

  IQgarPolyline iqPoly(iqSeg);
  FQgarPolyline fqPoly(fqSeg);
  DQgarPolyline dqPoly(dqSeg);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqPoly.thickness() == iqSeg.thickness() );
  CPPUNIT_ASSERT( iqPoly.color()     == iqSeg.color() );
  CPPUNIT_ASSERT( iqPoly.outline()   == iqPoly.outline() );
  CPPUNIT_ASSERT( cmp(iqPoly, IPolyline(iqSeg)) );

  CPPUNIT_ASSERT( fqPoly.color()     == fqSeg.color() );
  CPPUNIT_ASSERT( fqPoly.thickness() == fqSeg.thickness() );
  CPPUNIT_ASSERT( fqPoly.outline()   == fqSeg.outline() );
  CPPUNIT_ASSERT( cmp(fqPoly, FPolyline(fqSeg)) );

  CPPUNIT_ASSERT( dqPoly.color()     == dqSeg.color() );
  CPPUNIT_ASSERT( dqPoly.thickness() == dqSeg.thickness() );
  CPPUNIT_ASSERT( dqPoly.outline()   == dqSeg.outline() );
  CPPUNIT_ASSERT( cmp(dqPoly, DPolyline(dqSeg)) );
}


void
GenQgarPolylineTest::testBuildFromSegment()
{
  // ------
  // Set Up
  // ------

  ISegment iSeg(_iPt0, _iPt1);
  FSegment fSeg(_fPt0, _fPt1);
  DSegment dSeg(_dPt0, _dPt1);

  // -------
  // Process
  // -------

  IQgarPolyline iqPoly0(iSeg);
  IQgarPolyline iqPoly(iSeg, 3);
  FQgarPolyline fqPoly(fSeg, 4, QGE_COLOR_BLUE);
  DQgarPolyline dqPoly(dSeg, 5, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqPoly0.thickness() == 1 );
  CPPUNIT_ASSERT( iqPoly0.color()     == QGE_COLOR_DEFAULT );
  CPPUNIT_ASSERT( iqPoly0.outline()   == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( cmp(iqPoly0, IPolyline(iSeg)) );

  CPPUNIT_ASSERT( iqPoly.thickness() == 3 );
  CPPUNIT_ASSERT( iqPoly.color()     == QGE_COLOR_DEFAULT );
  CPPUNIT_ASSERT( iqPoly.outline()   == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( cmp(iqPoly, IPolyline(iSeg)) );

  CPPUNIT_ASSERT( fqPoly.thickness() == 4 );
  CPPUNIT_ASSERT( fqPoly.color()     == QGE_COLOR_BLUE );
  CPPUNIT_ASSERT( fqPoly.outline()   == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( cmp(fqPoly, FPolyline(fSeg)) );

  CPPUNIT_ASSERT( dqPoly.thickness() == 5 );
  CPPUNIT_ASSERT( dqPoly.color()     == QGE_COLOR_BLUE );
  CPPUNIT_ASSERT( dqPoly.outline()   == QGE_OUTLINE_DASH_SS );
  CPPUNIT_ASSERT( cmp(dqPoly, DPolyline(dSeg)) );
}


void
GenQgarPolylineTest::testBuildFrom2Points()
{
  // -------
  // Process
  // -------

  IQgarPolyline iqPoly0(_iPt0, _iPt3);
  IQgarPolyline iqPoly(_iPt0, _iPt3, 6);
  FQgarPolyline fqPoly(_fPt0, _fPt3, 7, QGE_COLOR_GREEN);
  DQgarPolyline dqPoly(_dPt0, _dPt3, 8, QGE_COLOR_GREEN, QGE_OUTLINE_DOT);
  
  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqPoly0.thickness() == 1 );
  CPPUNIT_ASSERT( iqPoly0.color()     == QGE_COLOR_DEFAULT );
  CPPUNIT_ASSERT( iqPoly0.outline()   == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( cmp(iqPoly0, IPolyline(_iPt0, _iPt3)) );

  CPPUNIT_ASSERT( iqPoly.thickness() == 6 );
  CPPUNIT_ASSERT( iqPoly.color()     == QGE_COLOR_DEFAULT );
  CPPUNIT_ASSERT( iqPoly.outline()   == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( cmp(iqPoly, IPolyline(_iPt0, _iPt3)) );

  CPPUNIT_ASSERT( fqPoly.thickness() == 7 );
  CPPUNIT_ASSERT( fqPoly.color()     == QGE_COLOR_GREEN );
  CPPUNIT_ASSERT( fqPoly.outline()   == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( cmp(fqPoly, FPolyline(_fPt0, _fPt3)) );

  CPPUNIT_ASSERT( dqPoly.thickness() == 8 );
  CPPUNIT_ASSERT( dqPoly.color()     == QGE_COLOR_GREEN );
  CPPUNIT_ASSERT( dqPoly.outline()   == QGE_OUTLINE_DOT );
  CPPUNIT_ASSERT( cmp(dqPoly, DPolyline(_dPt0, _dPt3)) );
}


void
GenQgarPolylineTest::testBuildFromPointList()
{ 
  // ------
  // Set Up
  // ------
  
  IQgarPolyline iqPoly0(_iPtList);
  IQgarPolyline iqPoly(_iPtList, 3);
  FQgarPolyline fqPoly(_fPtList, 4, QGE_COLOR_BLUE);
  DQgarPolyline dqPoly(_dPtList, 5, QGE_COLOR_BLUE, QGE_OUTLINE_DOT);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqPoly0.thickness() == 1 );
  CPPUNIT_ASSERT( iqPoly0.color()     == QGE_COLOR_DEFAULT );
  CPPUNIT_ASSERT( iqPoly0.outline()   == QGE_OUTLINE_DEFAULT);
  CPPUNIT_ASSERT( cmp(iqPoly0, IPolyline(_iPtList)) );

  CPPUNIT_ASSERT( iqPoly.thickness() == 3 );
  CPPUNIT_ASSERT( iqPoly.color()     == QGE_COLOR_DEFAULT );
  CPPUNIT_ASSERT( iqPoly.outline()   == QGE_OUTLINE_DEFAULT);
  CPPUNIT_ASSERT( cmp(iqPoly, IPolyline(_iPtList)) );

  CPPUNIT_ASSERT( fqPoly.thickness() == 4 );
  CPPUNIT_ASSERT( fqPoly.color()     == QGE_COLOR_BLUE );
  CPPUNIT_ASSERT( fqPoly.outline()   == QGE_OUTLINE_DEFAULT);
  CPPUNIT_ASSERT( cmp(fqPoly, FPolyline(_fPtList)) );

  CPPUNIT_ASSERT( dqPoly.thickness() == 5 );
  CPPUNIT_ASSERT( dqPoly.color()     == QGE_COLOR_BLUE );
  CPPUNIT_ASSERT( dqPoly.outline()   == QGE_OUTLINE_DOT);
  CPPUNIT_ASSERT( cmp(dqPoly, DPolyline(_dPtList)) );
}


void
GenQgarPolylineTest::testBuildFromPointListExc()
{
  list<DPoint> l;
  l.push_back(_dPt0);

  // Giving a list containing less than 2 points
  // should throw an exception
  DQgarPolyline dPoly(l);
}


// -------------------------------------------------------------------
// C O P Y
// -------------------------------------------------------------------


void
GenQgarPolylineTest::testClone()
{
  // ------
  // Set Up
  // ------

  IQgarPolyline iqPoly0(_iPtList);
  IQgarPolyline iqPoly(_iPtList, 2);
  FQgarPolyline fqPoly(_fPtList, 4, QGE_COLOR_BLUE);
  DQgarPolyline dqPoly(_dPtList, 6, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);

  // -------
  // Process
  // -------

  IQgarPolyline* iqDupPoly0 = iqPoly.clone();
  IQgarPolyline* iqDupPoly  = iqPoly.clone();
  FQgarPolyline* fqDupPoly  = fqPoly.clone();
  DQgarPolyline* dqDupPoly  = dqPoly.clone();

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqPoly0.thickness() == 1 );
  CPPUNIT_ASSERT( iqPoly0.color()     == QGE_COLOR_DEFAULT);
  CPPUNIT_ASSERT( iqPoly0.outline()   == QGE_OUTLINE_DEFAULT);
  CPPUNIT_ASSERT( cmp(*iqDupPoly0, iqPoly) );

  CPPUNIT_ASSERT( iqPoly.thickness() == 2 );
  CPPUNIT_ASSERT( iqPoly.color()     == QGE_COLOR_DEFAULT);
  CPPUNIT_ASSERT( iqPoly.outline()   == QGE_OUTLINE_DEFAULT);
  CPPUNIT_ASSERT( cmp(*iqDupPoly, iqPoly) );

  CPPUNIT_ASSERT( fqPoly.thickness() == 4 );
  CPPUNIT_ASSERT( fqPoly.color()     == QGE_COLOR_BLUE);
  CPPUNIT_ASSERT( fqPoly.outline()   == QGE_OUTLINE_DEFAULT);
  CPPUNIT_ASSERT( cmp(*fqDupPoly, fqPoly) );

  CPPUNIT_ASSERT( dqPoly.thickness() == 6 );
  CPPUNIT_ASSERT( dqPoly.color()     == QGE_COLOR_BLUE);
  CPPUNIT_ASSERT( dqPoly.outline()   == QGE_OUTLINE_DASH_SS);
  CPPUNIT_ASSERT( cmp(*dqDupPoly, dqPoly) );

  // ---------
  // Tear Down
  // ---------

  delete iqDupPoly;
  delete fqDupPoly;
  delete dqDupPoly;
}

// -------------------------------------------------------------------
// O P E R A T O R S
// -------------------------------------------------------------------


void
GenQgarPolylineTest::testAssignment()
{
  // ------
  // Set Up
  // ------

  IQgarPolyline iqPoly(_iPtList, 10, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);
  FQgarPolyline fqPoly(_fPtList, 20, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);
  DQgarPolyline dqPoly(_dPtList, 30, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);

  // -------
  // Process
  // -------

  IQgarPolyline iqDupPoly;
  FQgarPolyline fqDupPoly;
  DQgarPolyline dqDupPoly;

  iqDupPoly = iqPoly;
  fqDupPoly = fqPoly;
  dqDupPoly = dqPoly;

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqPoly.thickness() == 10 );
  CPPUNIT_ASSERT( iqPoly.color()     == QGE_COLOR_BLUE);
  CPPUNIT_ASSERT( iqPoly.outline()   == QGE_OUTLINE_DASH_SS);
  CPPUNIT_ASSERT( cmp(iqDupPoly, iqPoly) );

  CPPUNIT_ASSERT( fqPoly.thickness() == 20 );
  CPPUNIT_ASSERT( fqPoly.color()     == QGE_COLOR_BLUE);
  CPPUNIT_ASSERT( fqPoly.outline()   == QGE_OUTLINE_DASH_SS);
  CPPUNIT_ASSERT( cmp(fqDupPoly, fqPoly) );

  CPPUNIT_ASSERT( dqPoly.thickness() == 30 );
  CPPUNIT_ASSERT( dqPoly.color()     == QGE_COLOR_BLUE);
  CPPUNIT_ASSERT( dqPoly.outline()   == QGE_OUTLINE_DASH_SS);
  CPPUNIT_ASSERT( cmp(dqDupPoly, dqPoly) );

  // Ensure that function returns a valid reference on 'this'.
  CPPUNIT_ASSERT( &iqDupPoly == &(iqDupPoly = iqPoly) );
  CPPUNIT_ASSERT( &fqDupPoly == &(fqDupPoly = fqPoly) );
  CPPUNIT_ASSERT( &dqDupPoly == &(dqDupPoly = dqPoly) );
}


// -------------------------------------------------------------------
// A C C E S S   T O   V E R T I C E S
// -------------------------------------------------------------------


void
GenQgarPolylineTest::testSize()
{
  // ------
  // Set Up
  // ------
  
  // Empty polyline
  IQgarPolyline iqPoly(7);

  // Polyline with 2 vertices
  FQgarPolyline fqPoly(_fPt0, _fPt1, 18, QGE_COLOR_BLUE);

  // Polyline with 4 vertices
  DQgarPolyline dqPoly(_dPtList, 20);

  // ------
  // Set Up
  // ------

  int si = iqPoly.size();
  int sf = fqPoly.size();
  int sd = dqPoly.size();

  // -------
  // Process
  // -------

  CPPUNIT_ASSERT_EQUAL( si, 0 );
  CPPUNIT_ASSERT_EQUAL( sf, 2 );
  CPPUNIT_ASSERT_EQUAL( sd, 4 );
}


void
GenQgarPolylineTest::testGetVertices()
{
  // ------
  // Set Up
  // ------
  
  // A polyline and a copy of it
  IQgarPolyline iqPoly(_iPtList);

  // The vertices of the polyline
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

  // The polyline has one more vertex
  CPPUNIT_ASSERT_EQUAL( ns, os + 1 );
  CPPUNIT_ASSERT( (iqPoly.accessVertices()).back() == _iPt0 );
}


// -------------------------------------------------------------------
// I N S E R T   V E R T I C E S
// -------------------------------------------------------------------


void
GenQgarPolylineTest::testAppendSource()
{
  // ------
  // Set Up
  // ------

  IPoint iPt(1, 5);
  FPoint fPt(2.2f, 4.71f);
  DPoint dPt(41.14, 9.212);
  
  IQgarPolyline iqPoly(_iPtList, 10, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);
  FQgarPolyline fqPoly(_fPtList, 20, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);
  DQgarPolyline dqPoly(_dPtList, 30, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);

  // -------
  // Process
  // -------

  iqPoly.appendSource(iPt);
  fqPoly.appendSource(fPt);
  dqPoly.appendSource(dPt);

  // -----
  // Check
  // -----

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
  CPPUNIT_ASSERT( cmp(iqPoly, IPolyline(_iPtList)) );
  _fPtList.push_front(fPt);
  CPPUNIT_ASSERT( cmp(fqPoly, FPolyline(_fPtList)) );
  _dPtList.push_front(dPt);
  CPPUNIT_ASSERT( cmp(dqPoly, DPolyline(_dPtList)) );

  // Ensure that function returns a valid reference on 'this'
  CPPUNIT_ASSERT( &iqPoly == &(iqPoly.appendSource(iPt)) );
  CPPUNIT_ASSERT( &fqPoly == &(fqPoly.appendSource(fPt)) );
  CPPUNIT_ASSERT( &dqPoly == &(dqPoly.appendSource(dPt)) );
}


void
GenQgarPolylineTest::testAppendTarget()
{
  // ------
  // Set Up
  // ------

  IPoint iPt(1, 5);
  FPoint fPt(2.2f, 4.71f);
  DPoint dPt(41.14, 9.212);
  
  IQgarPolyline iqPoly(_iPtList, 10, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);
  FQgarPolyline fqPoly(_fPtList, 20, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);
  DQgarPolyline dqPoly(_dPtList, 30, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);

  // -------
  // Process
  // -------

  iqPoly.appendTarget(iPt);
  fqPoly.appendTarget(fPt);
  dqPoly.appendTarget(dPt);

  // -----
  // Check
  // -----

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
  CPPUNIT_ASSERT( iqPoly.source() == _iPtList.front() );
  CPPUNIT_ASSERT( fqPoly.source() == _fPtList.front() );
  CPPUNIT_ASSERT( dqPoly.source() == _dPtList.front() );

  // Targets
  CPPUNIT_ASSERT( iqPoly.target() == iPt );
  CPPUNIT_ASSERT( fqPoly.target() == fPt );
  CPPUNIT_ASSERT( dqPoly.target() == dPt );

  // Vertices
  _iPtList.push_back(iPt);
  CPPUNIT_ASSERT( cmp(iqPoly, IPolyline(_iPtList)) );
  _fPtList.push_back(fPt);
  CPPUNIT_ASSERT( cmp(fqPoly, FPolyline(_fPtList)) );
  _dPtList.push_back(dPt);
  CPPUNIT_ASSERT( cmp(dqPoly, DPolyline(_dPtList)) );

  // Ensure that function returns a valid reference on 'this'
  CPPUNIT_ASSERT( &iqPoly == &(iqPoly.appendSource(iPt)) );
  CPPUNIT_ASSERT( &fqPoly == &(fqPoly.appendSource(fPt)) );
  CPPUNIT_ASSERT( &dqPoly == &(dqPoly.appendSource(dPt)) );
}


void
GenQgarPolylineTest::testAppendPoly()
{
  // ------
  // Set Up
  // ------
  
  // Some points
  IPoint iPt0(1, 5);
  IPoint iPt1(-43, 1);
  IPoint iPt2(4, 2);
  IPoint iPt3(9, -5);
  IPoint iPt4(6, 15);

  // The Qgar polyline
  IQgarPolyline iqPoly(_iPtList, 2, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);

  // The polyline to be appended
  list<IPoint> appList; 
  appList.push_back(iPt0);
  appList.push_back(iPt1);
  appList.push_back(iPt2);
  appList.push_back(iPt3);
  appList.push_back(iPt4);
  IPolyline iappPoly(appList);

  // The model of the resulting polyline
  list<IPoint> imodList(_iPtList);
  imodList.push_back(iPt0);
  imodList.push_back(iPt1);
  imodList.push_back(iPt2);
  imodList.push_back(iPt3);
  imodList.push_back(iPt4);
  IPolyline imodPoly(imodList);

  // -------
  // Process
  // -------

  iqPoly.append(iappPoly);

  // -----
  // Check
  // -----

  // Ensure that color, thickness, outline are not modified
  CPPUNIT_ASSERT( iqPoly.thickness() == 2 );
  CPPUNIT_ASSERT( iqPoly.color()     == QGE_COLOR_BLUE );
  CPPUNIT_ASSERT( iqPoly.outline()   == QGE_OUTLINE_DASH_SS );

  // Ensure that the resulting polyline conforms to the model
  CPPUNIT_ASSERT( cmp(iqPoly, imodPoly) );

  // Ensure that the function returns a valid reference to 'this'
  CPPUNIT_ASSERT( &iqPoly == &(iqPoly.append(iappPoly)) );  
}


void
GenQgarPolylineTest::testAppendQgarPoly()
{
  // ------
  // Set Up
  // ------
  
  // Some points
  IPoint iPt0(1, 5);
  IPoint iPt1(-43, 1);
  IPoint iPt2(4, 2);
  IPoint iPt3(9, -5);
  IPoint iPt4(6, 15);

  // The Qgar polyline
  IQgarPolyline iqPoly(_iPtList, 2, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);

  // The polyline to be appended
  list<IPoint> appList; 
  appList.push_back(iPt0);
  appList.push_back(iPt1);
  appList.push_back(iPt2);
  appList.push_back(iPt3);
  appList.push_back(iPt4);
  IQgarPolyline iappqPoly(appList, 12, QGE_COLOR_RED, QGE_OUTLINE_DOT);

  // The model of the resulting polyline
  list<IPoint> imodList(_iPtList);
  imodList.push_back(iPt0);
  imodList.push_back(iPt1);
  imodList.push_back(iPt2);
  imodList.push_back(iPt3);
  imodList.push_back(iPt4);
  IPolyline imodPoly(imodList);

  // -------
  // Process
  // -------

  iqPoly.append(iappqPoly);

  // -----
  // Check
  // -----

  // Ensure that color, thickness, outline are not modified
  CPPUNIT_ASSERT( iqPoly.thickness() == 2 );
  CPPUNIT_ASSERT( iqPoly.color()     == QGE_COLOR_BLUE );
  CPPUNIT_ASSERT( iqPoly.outline()   == QGE_OUTLINE_DASH_SS );

  // Ensure that the resulting polyline conforms to the model
  CPPUNIT_ASSERT( cmp(iqPoly, imodPoly) );

  // Ensure that the function returns a valid reference to 'this'
  CPPUNIT_ASSERT( &iqPoly == &(iqPoly.append(iappqPoly)) );  
}


void
GenQgarPolylineTest::testAppendPtVect()
{
  // ------
  // Set Up
  // ------
  
  // A Qgar polyline
  IQgarPolyline iqPoly(_iPtList, 2, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);
  
  // A vector of points
  IPoint iPt0(1, 5);
  IPoint iPt1(-43, 1);
  IPoint iPt2(4, 2);
  IPoint iPt3(9, -5);
  IPoint iPt4(6, 15);
  vector<IPoint> ptVect;
  ptVect.push_back(iPt0);
  ptVect.push_back(iPt1);
  ptVect.push_back(iPt2);
  ptVect.push_back(iPt3);
  ptVect.push_back(iPt4);

  // The model of the resulting polyline
  list<IPoint> imodList(_iPtList);
  imodList.push_back(iPt0);
  imodList.push_back(iPt1);
  imodList.push_back(iPt2);
  imodList.push_back(iPt3);
  imodList.push_back(iPt4);
  IPolyline imodPoly(imodList);

  // -------
  // Process
  // -------

  iqPoly.append(ptVect);

  // -----
  // Check
  // -----

  // Ensure that color, thickness, outline are not modified.
  CPPUNIT_ASSERT( iqPoly.thickness() == 2 );
  CPPUNIT_ASSERT( iqPoly.color()     == QGE_COLOR_BLUE );
  CPPUNIT_ASSERT( iqPoly.outline()   == QGE_OUTLINE_DASH_SS );

  // Ensure that the resulting polyline conforms to the model
  CPPUNIT_ASSERT( cmp(iqPoly, imodPoly) );

  // Ensure that the function returns a valid reference to 'this'
  CPPUNIT_ASSERT( &iqPoly == &(iqPoly.append(ptVect)) );    
}


// -------------------------------------------------------------------
// R E M O V E   V E R T I C E S
// -------------------------------------------------------------------


void
GenQgarPolylineTest::testRemove()
{
  // ------
  // Set Up
  // ------

  IQgarPolyline iQPoly(_iPtList, 3, QGE_COLOR_WHITE, QGE_OUTLINE_DASH_LS);
  IQgarPolyline iSourceQPoly(_iPtList, 4, QGE_COLOR_BLACK);
  IQgarPolyline iTargetQPoly(_iPtList, 5, QGE_COLOR_RED, QGE_OUTLINE_DASH_SS);

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
  CPPUNIT_ASSERT( &iQPoly == &(iQPoly.remove(_iPt1)) );
}


void
GenQgarPolylineTest::testRemoveExc()
{
  // A polyline with 2 vertices
  DQgarPolyline dqPoly(DSegment(_dPt0,_dPt1));

  // Removing a vertex should throw an exception
  dqPoly.remove(_dPt0);
}


// -------------------------------------------------------------------
// C O N V E R S I O N S
// -------------------------------------------------------------------


void
GenQgarPolylineTest::testToPointVector()
{
  // ------
  // Set Up
  // ------

  IQgarPolyline iqPoly(_iPtList, 3, QGE_COLOR_RED, QGE_OUTLINE_SOLID);

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

  // The resulting vector has the same size as the polyline
  CPPUNIT_ASSERT( (int) ptVect.size() == iqPoly.size() );

  // The vector and the polyline include the same vertices
  deque<IPoint>::const_iterator itPoly = iqPoly.accessVertices().begin();
  vector<IPoint>::iterator itVect      = ptVect.begin();

  while( itVect != ptVect.end() )
    {
      CPPUNIT_ASSERT_EQUAL( *itVect++, *itPoly++);
    }
}


void
GenQgarPolylineTest::testToSegList()
{
  // ------
  // Set Up
  // ------

  IQgarPolyline iqPoly(_iPtList, 3, QGE_COLOR_RED, QGE_OUTLINE_SOLID);

  // -------
  // Process
  // -------

  list<ISegment> segList = iqPoly.toSegList();

  // -----
  // Check
  // -----

  // Thickness, color and outline are unchanged
  CPPUNIT_ASSERT( iqPoly.thickness() == 3 );
  CPPUNIT_ASSERT( iqPoly.color()     == QGE_COLOR_RED );
  CPPUNIT_ASSERT( iqPoly.outline()   == QGE_OUTLINE_SOLID );

  // Nb of segments is equal to nb of points - 1
  CPPUNIT_ASSERT_EQUAL( (int) segList.size(), iqPoly.size() - 1 );

  // The list of segments
  deque<IPoint>::const_iterator itPoly = iqPoly.accessVertices().begin();
  list<ISegment>::iterator      itSeg  = segList.begin();

  while( itSeg != segList.end() )
    {
      IPoint pt = *itPoly++;
      CPPUNIT_ASSERT( *itSeg++ == ISegment(pt, *itPoly) );
    }
}


void
GenQgarPolylineTest::testToQgarSegList()
{
  // ------
  // Set Up
  // ------

  IQgarPolyline iqPoly(_iPtList, 2, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);

  // -------
  // Process
  // -------

  list<IQgarSegment> segList = iqPoly.toQgarSegList();

  // -----
  // Check
  // -----

  // Nb of segments is equals to nb of points - 1
  CPPUNIT_ASSERT_EQUAL( (int) segList.size(), iqPoly.size() - 1 );

  // The resulting Qgar segments
  deque<IPoint>::const_iterator itPoly = iqPoly.accessVertices().begin();
  list<IQgarSegment>::iterator  itSeg  = segList.begin();

  while( itSeg != segList.end() )
    {
      IPoint pt = *itPoly++;
      CPPUNIT_ASSERT( (*itSeg).thickness() == 2 );
      CPPUNIT_ASSERT( (*itSeg).color()     == QGE_COLOR_BLUE );
      CPPUNIT_ASSERT( (*itSeg).outline()   == QGE_OUTLINE_DASH_SS );
      CPPUNIT_ASSERT( ISegment(*itSeg++) == ISegment(pt, *itPoly) );
    }
}


// -------------------------------------------------------------------
// G E O M E T R Y :   T R A N S L A T I O N
// -------------------------------------------------------------------


void
GenQgarPolylineTest::testTranslate()
{
  // ------
  // Set Up
  // ------

  int tx = 27;
  int ty = -89005;

  IQgarPolyline iqPoly(_iPtList, 2, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);

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
GenQgarPolylineTest::testSerializeDeserialize()
{
  // ------
  // Set Up
  // ------

  IQgarPolyline iqPoly(_iPtList, 2, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);
  FQgarPolyline fqPoly(_fPtList, 3, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);
  DQgarPolyline dqPoly(_dPtList, 4, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);

  IQgarPolyline iqOutInPoly;
  FQgarPolyline fqOutInPoly;
  DQgarPolyline dqOutInPoly;

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

  // In and out polylines are provided with the same attributes
  CPPUNIT_ASSERT( iqPoly.thickness() == iqOutInPoly.thickness() );
  CPPUNIT_ASSERT( iqPoly.color()     == iqOutInPoly.color()     );
  CPPUNIT_ASSERT( iqPoly.outline()   == iqOutInPoly.outline()   );

  // In and out polylines are geometrically identical
  CPPUNIT_ASSERT( cmp(iqPoly, iqOutInPoly) );
  CPPUNIT_ASSERT( cmp(fqPoly, fqOutInPoly) );
  CPPUNIT_ASSERT( cmp(dqPoly, dqOutInPoly) );
}


// -------------------------------------------------------------------
// S O U R C E   A N D   T A R G E T   U P D A T E S
// -------------------------------------------------------------------


void
GenQgarPolylineTest::testUpdateSourceTarget()
{
  // Rectangle triangle
  // (1,1) (1,4) (4,4)
 
  list<Point> lp;
  lp.push_back(Point(1,1));
  lp.push_back(Point(1,4));
  lp.push_back(Point(4,4));
  IQgarPolyline pll(lp, 18, QGE_COLOR_WHITE, QGE_OUTLINE_DOT);

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
