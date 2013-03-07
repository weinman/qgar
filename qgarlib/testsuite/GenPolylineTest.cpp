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
 * @file  GenPolylineTest.cpp
 * @brief Implementation of class GenPolylineTest
 *
 *        See file GenPolylineTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 16, 2003  10:45
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenPolylineTest.cpp,v 1.9 2005/07/13 16:29:34 masini Exp $ */



// STD
#include <list>
// QGAR
#include <qgarlib/primitives.h>
// QGAR TESTS
#include "GenPolylineTest.h"



using namespace std;
using namespace qgar;


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


} // unnamed namespace


// ------------------------------------------------------------------
// T E S T    F I X T U R E   I M P L E M E N T A T I O N
// ------------------------------------------------------------------

void
GenPolylineTest::setUp()
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

  // Initialize lists of points

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
GenPolylineTest::tearDown()
{
  /* EMPTY */
}


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


void
GenPolylineTest::testDefaultConstructor()
{
  // ------
  // Set Up
  // ------

  IPolyline _iPoly;
  FPolyline _fPoly;
  DPolyline _dPoly;

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( _iPoly.accessVertices().empty() );
  CPPUNIT_ASSERT( _fPoly.accessVertices().empty() );
  CPPUNIT_ASSERT( _dPoly.accessVertices().empty() );
}


void
GenPolylineTest::testCopyConstructor()
{
  // ------
  // Set Up
  // ------

  IPolyline _iPoly(_iPtList);
  FPolyline _fPoly(_fPtList);
  DPolyline _dPoly(_dPtList);

  // -------
  // Process
  // -------

  IPolyline iDupPoly(_iPoly);
  FPolyline fDupPoly(_fPoly);
  DPolyline dDupPoly(_dPoly);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL(_iPoly.source(), iDupPoly.source());
  CPPUNIT_ASSERT_EQUAL(_fPoly.source(), fDupPoly.source());
  CPPUNIT_ASSERT_EQUAL(_dPoly.source(), dDupPoly.source());

  CPPUNIT_ASSERT_EQUAL(_iPoly.target(), iDupPoly.target());
  CPPUNIT_ASSERT_EQUAL(_fPoly.target(), fDupPoly.target());
  CPPUNIT_ASSERT_EQUAL(_dPoly.target(), dDupPoly.target());

  CPPUNIT_ASSERT( cmp(_iPoly.accessVertices(), iDupPoly.accessVertices()) );
  CPPUNIT_ASSERT( cmp(_fPoly.accessVertices(), fDupPoly.accessVertices()) );
  CPPUNIT_ASSERT( cmp(_dPoly.accessVertices(), dDupPoly.accessVertices()) );
}


void
GenPolylineTest::testBuildFromQgarPolyline()
{
  // ------
  // Set Up
  // ------

  IQgarPolyline iQPoly(_iPtList, 3, QGE_COLOR_RED, QGE_OUTLINE_DOT);
  FQgarPolyline fQPoly(_fPtList, 7, QGE_COLOR_GREEN);
  DQgarPolyline dQPoly(_dPtList, 6);

  // -------
  // Process
  // -------

  IPolyline iPoly(iQPoly);
  FPolyline fPoly(fQPoly);
  DPolyline dPoly(dQPoly);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL(iPoly.source(), iQPoly.source());
  CPPUNIT_ASSERT_EQUAL(fPoly.source(), fQPoly.source());
  CPPUNIT_ASSERT_EQUAL(dPoly.source(), dQPoly.source());

  CPPUNIT_ASSERT_EQUAL(iPoly.target(), iQPoly.target());
  CPPUNIT_ASSERT_EQUAL(fPoly.target(), fQPoly.target());
  CPPUNIT_ASSERT_EQUAL(dPoly.target(), dQPoly.target());

  CPPUNIT_ASSERT( cmp(iPoly.accessVertices(), iQPoly.accessVertices()) );
  CPPUNIT_ASSERT( cmp(fPoly.accessVertices(), fQPoly.accessVertices()) );
  CPPUNIT_ASSERT( cmp(dPoly.accessVertices(), dQPoly.accessVertices()) );
}


void
GenPolylineTest::testBuildFromQgarSegment()
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
  
  IPolyline iPoly(iqSeg);
  FPolyline fPoly(fqSeg);
  DPolyline dPoly(dqSeg);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iPoly.accessVertices().size() == 2 );
  CPPUNIT_ASSERT( fPoly.accessVertices().size() == 2 );
  CPPUNIT_ASSERT( dPoly.accessVertices().size() == 2 );

  CPPUNIT_ASSERT_EQUAL(iPoly.source(), iqSeg.source());
  CPPUNIT_ASSERT_EQUAL(fPoly.source(), fqSeg.source());
  CPPUNIT_ASSERT_EQUAL(dPoly.source(), dqSeg.source());

  CPPUNIT_ASSERT_EQUAL(iPoly.target(), iqSeg.target());
  CPPUNIT_ASSERT_EQUAL(fPoly.target(), fqSeg.target());
  CPPUNIT_ASSERT_EQUAL(dPoly.target(), dqSeg.target());
}


void
GenPolylineTest::testBuildFromSegment()
{
  // ------
  // Set Up
  // ------

  ISegment iSeg(_iPt2, _iPt3);
  FSegment fSeg(_fPt2, _fPt3);
  DSegment dSeg(_dPt2, _dPt3);

  // -------
  // Process
  // -------
  
  IPolyline iPoly(iSeg);
  FPolyline fPoly(fSeg);
  DPolyline dPoly(dSeg);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iPoly.accessVertices().size() == 2 );
  CPPUNIT_ASSERT( fPoly.accessVertices().size() == 2 );
  CPPUNIT_ASSERT( dPoly.accessVertices().size() == 2 );

  CPPUNIT_ASSERT_EQUAL(iPoly.source(), iSeg.source());
  CPPUNIT_ASSERT_EQUAL(fPoly.source(), fSeg.source());
  CPPUNIT_ASSERT_EQUAL(dPoly.source(), dSeg.source());

  CPPUNIT_ASSERT_EQUAL(iPoly.target(), iSeg.target());
  CPPUNIT_ASSERT_EQUAL(fPoly.target(), fSeg.target());
  CPPUNIT_ASSERT_EQUAL(dPoly.target(), dSeg.target());
}


void
GenPolylineTest::testBuildFrom2Points()
{
  // -------
  // Process
  // -------

  IPolyline iPoly(_iPt0, _iPt3);
  FPolyline fPoly(_fPt0, _fPt3);
  DPolyline dPoly(_dPt0, _dPt3);
  
  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iPoly.accessVertices().size() == 2 );
  CPPUNIT_ASSERT( fPoly.accessVertices().size() == 2 );
  CPPUNIT_ASSERT( dPoly.accessVertices().size() == 2 );

  CPPUNIT_ASSERT_EQUAL(iPoly.source(), _iPt0);
  CPPUNIT_ASSERT_EQUAL(fPoly.source(), _fPt0);
  CPPUNIT_ASSERT_EQUAL(dPoly.source(), _dPt0);

  CPPUNIT_ASSERT_EQUAL(iPoly.target(), _iPt3);
  CPPUNIT_ASSERT_EQUAL(fPoly.target(), _fPt3);
  CPPUNIT_ASSERT_EQUAL(dPoly.target(), _dPt3);
}

void
GenPolylineTest::testBuildFromPointList()
{
  // -------
  // Process
  // -------
  
  IPolyline iPoly(_iPtList);
  FPolyline fPoly(_fPtList);
  DPolyline dPoly(_dPtList);
  
  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL(iPoly.source(), _iPtList.front() );
  CPPUNIT_ASSERT_EQUAL(fPoly.source(), _fPtList.front() );
  CPPUNIT_ASSERT_EQUAL(dPoly.source(), _dPtList.front() );

  CPPUNIT_ASSERT_EQUAL(iPoly.target(), _iPtList.back() );
  CPPUNIT_ASSERT_EQUAL(fPoly.target(), _fPtList.back() );
  CPPUNIT_ASSERT_EQUAL(dPoly.target(), _dPtList.back() );

  // Ensure that the polyline contains as many vertices as the list
  CPPUNIT_ASSERT( iPoly.accessVertices().size() == _iPtList.size() );
  CPPUNIT_ASSERT( fPoly.accessVertices().size() == _fPtList.size() );
  CPPUNIT_ASSERT( dPoly.accessVertices().size() == _dPtList.size() );

  // Ensure that the list of vertices of the polyline is equal to the
  // list of points used to build it
  deque<IPoint> iDeque;
  copy(_iPtList.begin(),_iPtList.end(), back_inserter(iDeque));
  CPPUNIT_ASSERT( cmp(iDeque, iPoly.accessVertices()) );
    
  deque<FPoint> fDeque;
  copy(_fPtList.begin(),_fPtList.end(), back_inserter(fDeque));
  CPPUNIT_ASSERT( cmp(fDeque, fPoly.accessVertices()) );

  deque<DPoint> dDeque;
  copy(_dPtList.begin(),_dPtList.end(), back_inserter(dDeque));
  CPPUNIT_ASSERT( cmp(dDeque, dPoly.accessVertices()) );  
}


void
GenPolylineTest::testBuildFromPointListExc()
{
  list<DPoint> l;
  l.push_back(_dPt0);

  // Giving a list containing less than 2 points
  // should throw an exception
  DPolyline dPoly(l);
}


// -------------------------------------------------------------------
// C O P Y
// -------------------------------------------------------------------


void
GenPolylineTest::testClone()
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

  IPolyline * iClone = iPoly.clone();
  FPolyline * fClone = fPoly.clone();
  DPolyline * dClone = dPoly.clone();

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL(iPoly.source(), iClone->source());
  CPPUNIT_ASSERT_EQUAL(fPoly.source(), fClone->source());
  CPPUNIT_ASSERT_EQUAL(dPoly.source(), dClone->source());

  CPPUNIT_ASSERT_EQUAL(iPoly.target(), iClone->target());
  CPPUNIT_ASSERT_EQUAL(fPoly.target(), fClone->target());
  CPPUNIT_ASSERT_EQUAL(dPoly.target(), dClone->target());

  CPPUNIT_ASSERT( cmp(iPoly.accessVertices(), iClone->accessVertices()) );
  CPPUNIT_ASSERT( cmp(fPoly.accessVertices(), fClone->accessVertices()) );
  CPPUNIT_ASSERT( cmp(dPoly.accessVertices(), dClone->accessVertices()) );

  // ---------
  // Tear Down
  // ---------

  delete iClone;
  delete fClone;
  delete dClone;
}


// -------------------------------------------------------------------
// O P E R A T O R S
// -------------------------------------------------------------------


void
GenPolylineTest::testAssignment()
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
  
  IPolyline iDupPoly;
  FPolyline fDupPoly;
  DPolyline dDupPoly;

  iDupPoly = iPoly;  
  fDupPoly = fPoly;
  dDupPoly = dPoly;

  // -----
  // Check
  // -----

  // Ensure that vertices are the same
  CPPUNIT_ASSERT( cmp(iPoly.accessVertices(), iDupPoly.accessVertices()) );
  CPPUNIT_ASSERT( cmp(fPoly.accessVertices(), fDupPoly.accessVertices()) );
  CPPUNIT_ASSERT( cmp(dPoly.accessVertices(), dDupPoly.accessVertices()) );

  // Ensure operator returns a correct reference to 'this'
  CPPUNIT_ASSERT( &iDupPoly == &(iDupPoly = iPoly) );
  CPPUNIT_ASSERT( &fDupPoly == &(fDupPoly = fPoly) );
  CPPUNIT_ASSERT( &dDupPoly == &(dDupPoly = dPoly) );  
}


// -------------------------------------------------------------------
// A C C E S S   T O   V E R T I C E S
// -------------------------------------------------------------------


void
GenPolylineTest::testSize()
{
  // ------
  // Set Up
  // ------
  
  // Empty polyline
  IPolyline iPoly;

  // Polyline with 2 vertices
  FPolyline fPoly(_fPt0, _fPt1);

  // Polyline with 4 vertices
  DPolyline dPoly(_dPtList);

  // ------
  // Set Up
  // ------

  int si = iPoly.size();
  int sf = fPoly.size();
  int sd = dPoly.size();

  // -------
  // Process
  // -------

  CPPUNIT_ASSERT_EQUAL( si, 0 );
  CPPUNIT_ASSERT_EQUAL( sf, 2 );
  CPPUNIT_ASSERT_EQUAL( sd, 4 );
}


void
GenPolylineTest::testGetVertices()
{
  // ------
  // Set Up
  // ------
  
  // A polyline and a copy of it
  IPolyline iPoly(_iPtList);

  // The vertices of the polyline
  deque<IPoint>& id = iPoly.getVertices();

  // ------
  // Set Up
  // ------

  int os = iPoly.size();

  // Modification of the vertices
  id.push_back(_iPt1);

  int ns = iPoly.size();

  // -------
  // Process
  // -------

  // The polyline has one more vertex
  CPPUNIT_ASSERT_EQUAL( ns, os + 1 );
  CPPUNIT_ASSERT( (iPoly.accessVertices()).back() == _iPt1 );
}


// -------------------------------------------------------------------
// I N S E R T   V E R T I C E S
// -------------------------------------------------------------------


void
GenPolylineTest::testAppendSource()
{
  // ------
  // Set Up
  // ------

  IPoint iPt(31, 85);
  FPoint fPt(1.52f, 8.7471f);
  DPoint dPt(4.14, 59.12);

  IPolyline iPoly(_iPtList);
  FPolyline fPoly(_fPtList);
  DPolyline dPoly(_dPtList);

  // -------
  // Process
  // -------

  iPoly.appendSource(iPt);
  fPoly.appendSource(fPt);
  dPoly.appendSource(dPt);

  // -----
  // Check
  // -----

  // Ensure that the vertices list contains an extra point
  CPPUNIT_ASSERT_EQUAL( _iPtList.size() + 1, iPoly.accessVertices().size() );
  CPPUNIT_ASSERT_EQUAL( _fPtList.size() + 1, fPoly.accessVertices().size() );
  CPPUNIT_ASSERT_EQUAL( _dPtList.size() + 1, dPoly.accessVertices().size() );
  
  // Ensure that the source is correctly updated
  CPPUNIT_ASSERT_EQUAL( iPt, iPoly.source() );
  CPPUNIT_ASSERT_EQUAL( iPt, (iPoly.accessVertices()).front() );

  CPPUNIT_ASSERT_EQUAL( fPt, fPoly.source() );
  CPPUNIT_ASSERT_EQUAL( fPt, (fPoly.accessVertices()).front() );

  CPPUNIT_ASSERT_EQUAL( dPt, dPoly.source() );
  CPPUNIT_ASSERT_EQUAL( dPt, (dPoly.accessVertices()).front() );
  
  // Ensure that the function returns a valid reference to 'this'
  CPPUNIT_ASSERT( &iPoly == &(iPoly.appendSource(iPt)) );
}


void
GenPolylineTest::testAppendTarget()
{
  // ------
  // Set Up
  // ------

  IPoint iPt(31, 85);
  FPoint fPt(1.52f, 8.7471f);
  DPoint dPt(4.14, 59.12);

  IPolyline iPoly(_iPtList);
  FPolyline fPoly(_fPtList);
  DPolyline dPoly(_dPtList);
  
  // -------
  // Process
  // -------

  iPoly.appendTarget(iPt);
  fPoly.appendTarget(fPt);
  dPoly.appendTarget(dPt);

  // -----
  // Check
  // -----

  // Ensure that the vertices list contains an extra point
  CPPUNIT_ASSERT_EQUAL( _iPtList.size() + 1, iPoly.accessVertices().size() );
  CPPUNIT_ASSERT_EQUAL( _fPtList.size() + 1, fPoly.accessVertices().size() );
  CPPUNIT_ASSERT_EQUAL( _dPtList.size() + 1, dPoly.accessVertices().size() );

  // Ensure that the target is correctly updated
  CPPUNIT_ASSERT_EQUAL( iPt, iPoly.target() );
  CPPUNIT_ASSERT_EQUAL( iPt, (iPoly.accessVertices()).back() );

  CPPUNIT_ASSERT_EQUAL( fPt, fPoly.target() );
  CPPUNIT_ASSERT_EQUAL( fPt, (fPoly.accessVertices()).back() );

  CPPUNIT_ASSERT_EQUAL( dPt, dPoly.target() );
  CPPUNIT_ASSERT_EQUAL( dPt, (dPoly.accessVertices()).back() );  

  // Ensure that the function returns a valid reference on this.
  CPPUNIT_ASSERT( &iPoly == &(iPoly.appendTarget(iPt)) );  
}


void
GenPolylineTest::testAppendPoly()
{
  // ------
  // Set Up
  // ------
  
  IPolyline iPoly(_iPtList);
  
  // Create another polyline

  IPoint iPt0(1, 5);
  IPoint iPt1(-43, 1);
  IPoint iPt2(4, 2);
  IPoint iPt3(9, -5);
  IPoint iPt4(6, 15);
  
  list<IPoint> ptList;
  ptList.push_back(iPt0);
  ptList.push_back(iPt1);
  ptList.push_back(iPt2);
  ptList.push_back(iPt3);
  ptList.push_back(iPt4);

  IPolyline iPoly2(ptList);

  // -------
  // Process
  // -------

  iPoly.append(iPoly2);

  // -----
  // Check
  // -----
  
  // The resulting number of vertices
  CPPUNIT_ASSERT( (iPoly.accessVertices()).size() 
		  == (_iPtList.size() + ptList.size()) );

  // The resulting source is unchanged
  // The resulting target is the target of the appended polyline
  CPPUNIT_ASSERT( iPoly.source() == _iPtList.front() );
  CPPUNIT_ASSERT( iPoly.target() == iPoly2.target()  );

  // The resulting vertices list is the given list
  // appended to the initial one
  deque<IPoint> ptDeque;
  copy(_iPtList.begin(), _iPtList.end(), back_inserter(ptDeque));
  copy(ptList.begin(), ptList.end(), back_inserter(ptDeque));

  CPPUNIT_ASSERT( cmp( ptDeque, iPoly.accessVertices() ) );

  // Ensure that the function returns a correct reference to 'this'
  CPPUNIT_ASSERT( &iPoly == &(iPoly.append(iPoly2)));
}


void
GenPolylineTest::testAppendQgarPoly()
{
  // ------
  // Set Up
  // ------
  
  IQgarPolyline iPoly(_iPtList);
  
  // Create a Qgar polyline

  IPoint iPt0(1, 5);
  IPoint iPt1(-43, 1);
  IPoint iPt2(4, 2);
  IPoint iPt3(9, -5);
  IPoint iPt4(6, 15);
  
  list<IPoint> ptList;
  ptList.push_back(iPt0);
  ptList.push_back(iPt1);
  ptList.push_back(iPt2);
  ptList.push_back(iPt3);
  ptList.push_back(iPt4);

  IQgarPolyline iqPoly(ptList, 13, QGE_COLOR_YELLOW, QGE_OUTLINE_DOT);

  // -------
  // Process
  // -------

  iPoly.append(iqPoly);

  // -----
  // Check
  // -----
  
  // The resulting number of vertices
  CPPUNIT_ASSERT( (iPoly.accessVertices()).size() 
		  == (_iPtList.size() + ptList.size()) );

  // The resulting source is unchanged
  // The resulting target is the target of the appended polyline
  CPPUNIT_ASSERT( iPoly.source() == _iPtList.front() );
  CPPUNIT_ASSERT( iPoly.target() == iqPoly.target()  );

  // The resulting vertices list is the given list
  // appended to the initial one
  deque<IPoint> ptDeque;
  copy(_iPtList.begin(), _iPtList.end(), back_inserter(ptDeque));
  copy(ptList.begin(), ptList.end(), back_inserter(ptDeque));

  CPPUNIT_ASSERT( cmp( ptDeque, iPoly.accessVertices() ) );

  // Ensure that the function returns a correct reference to 'this'
  CPPUNIT_ASSERT( &iPoly == &(iPoly.append(iqPoly)));
}


void
GenPolylineTest::testAppendPtVect()
{
  // ------
  // Set Up
  // ------
  
  IPolyline iPoly(_iPtList);
  
  // Create a vector of points
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

  // -------
  // Process
  // -------

  iPoly.append(ptVect);

  // -----
  // Check
  // -----
  
  // The resulting number of vertices
  CPPUNIT_ASSERT( iPoly.accessVertices().size() 
		  == (_iPtList.size() + ptVect.size()) );

  // The resulting source is unchanged
  // The resulting target is the target of the appended polyline
  CPPUNIT_ASSERT( iPoly.source() == _iPtList.front() );
  CPPUNIT_ASSERT( iPoly.target() == ptVect.back()    );

  // The resulting vertices list is the given list
  // appended to the initial one
  deque<IPoint> ptDeque;
  copy(_iPtList.begin(), _iPtList.end(), back_inserter(ptDeque));
  copy(ptVect.begin(), ptVect.end(), back_inserter(ptDeque));

  CPPUNIT_ASSERT( cmp( ptDeque, iPoly.accessVertices() ) );

  // Ensure that the function returns a correct reference to 'this'
  CPPUNIT_ASSERT( &iPoly == &(iPoly.append(ptVect)) );
}


// -------------------------------------------------------------------
// R E M O V E   V E R T I C E S
// -------------------------------------------------------------------


void
GenPolylineTest::testRemove()
{
  // ------
  // Set Up
  // ------

  IPolyline iPoly(_iPtList);
  IPolyline iSourcePoly(iPoly);
  IPolyline iTargetPoly(iPoly);

  // -------
  // Process
  // -------

  // Remove a point which is not the source neither the target
  iPoly.remove(_iPt2);
  // The theoretical resulting vertices deque
  deque<IPoint> iDeq;
  iDeq.push_back(_iPt0);
  iDeq.push_back(_iPt1);
  iDeq.push_back(_iPt3);

  // Remove source point
  iSourcePoly.remove( iSourcePoly.source() );
  // The theoretical resulting vertices deque
  deque<IPoint> iSourceDeq;
  copy(++_iPtList.begin(), _iPtList.end(), back_inserter(iSourceDeq));

  // Remove target point
  iTargetPoly.remove( iTargetPoly.accessTarget() );
  // The theoretical resulting vertices deque
  deque<IPoint> iTargetDeq;
  copy(_iPtList.begin(), --_iPtList.end(), back_inserter(iTargetDeq));

  // -----
  // Check
  // -----

  // Ensure that vertices lists are one element shorter
  CPPUNIT_ASSERT( iPoly.accessVertices().size()
		  == (_iPtList.size() - 1) );
  CPPUNIT_ASSERT( iSourcePoly.accessVertices().size() 
		  == (_iPtList.size() - 1) );
  CPPUNIT_ASSERT( iTargetPoly.accessVertices().size() 
		  == (_iPtList.size() - 1) );

  // Check that resulting vertices are correct
  CPPUNIT_ASSERT( iPoly.source() == iDeq.front() );
  CPPUNIT_ASSERT( iPoly.target() == iDeq.back() );
  CPPUNIT_ASSERT( cmp(iPoly.accessVertices(), iDeq) );

  CPPUNIT_ASSERT( iSourcePoly.source() == iSourceDeq.front() );
  CPPUNIT_ASSERT( iSourcePoly.target() == iSourceDeq.back() );
  CPPUNIT_ASSERT( cmp(iSourcePoly.accessVertices(), iSourceDeq) );

  CPPUNIT_ASSERT( iTargetPoly.source() == iTargetDeq.front() );
  CPPUNIT_ASSERT( iTargetPoly.target() == iTargetDeq.back() );
  CPPUNIT_ASSERT( cmp(iTargetPoly.accessVertices(), iTargetDeq) );

  // Ensure that the function returns a valid reference to 'this'
  CPPUNIT_ASSERT( &iPoly == &(iPoly.remove(_iPt1)) );
}


void
GenPolylineTest::testRemoveExc()
{
  // A polyline with 2 vertices
  list<DPoint> l;
  l.push_back(_dPt0);
  l.push_back(_dPt1);
  DPolyline dPoly(l);

  // Removing a vertex should throw an exception
  dPoly.remove(dPoly.target());
}


// -------------------------------------------------------------------
// C O N V E R S I O N S
// -------------------------------------------------------------------


void
GenPolylineTest::testToPointVector()
{
  // ------
  // Set Up
  // ------

  IPolyline iPoly(_iPtList);

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
GenPolylineTest::testToSegList()
{
  // ------
  // Set Up
  // ------

  IPolyline iPoly(_iPtList);

  // -------
  // Process
  // -------

  list<ISegment> segList = iPoly.toSegList();

  // -----
  // Check
  // -----

  // Nb of segments is equal to nb of vertices minus 1
  CPPUNIT_ASSERT_EQUAL( segList.size(), iPoly.accessVertices().size() - 1 );

  // Resulting segments
  deque<IPoint>::const_iterator itPoly = iPoly.accessVertices().begin();
  list<ISegment>::iterator itSeg = segList.begin();

  while( itSeg != segList.end() )
    {
      IPoint source = *itPoly;
      ++itPoly;
      IPoint target = *itPoly;

      CPPUNIT_ASSERT( *itSeg == ISegment(source, target) );

      ++itSeg;
    }
}


void
GenPolylineTest::testToQgarSegList()
{
  // ------
  // Set Up
  // ------

  IPolyline iPoly(_iPtList);

  // -------
  // Process
  // -------

  list<IQgarSegment> segList3 = iPoly.toQgarSegList(3, QGE_COLOR_WHITE, QGE_OUTLINE_DOT);
  list<IQgarSegment> segList2 = iPoly.toQgarSegList(3, QGE_COLOR_WHITE);
  list<IQgarSegment> segList1 = iPoly.toQgarSegList(3);
  list<IQgarSegment> segList0 = iPoly.toQgarSegList();

  // -----
  // Check
  // -----

  // Nb of segments is equal to nb of vertices minus 1
  CPPUNIT_ASSERT_EQUAL( segList3.size(), iPoly.accessVertices().size() - 1 );
  CPPUNIT_ASSERT_EQUAL( segList2.size(), iPoly.accessVertices().size() - 1 );
  CPPUNIT_ASSERT_EQUAL( segList1.size(), iPoly.accessVertices().size() - 1 );
  CPPUNIT_ASSERT_EQUAL( segList0.size(), iPoly.accessVertices().size() - 1 );

  // Resulting segments
  deque<IPoint>::const_iterator itPoly3 = iPoly.accessVertices().begin();
  list<IQgarSegment>::iterator itSeg3 = segList3.begin();

  while( itSeg3 != segList3.end() )
    {
      IPoint s = *itPoly3;
      ++itPoly3;
      IPoint t = *itPoly3;

      CPPUNIT_ASSERT( *itSeg3 == IQgarSegment(s, t, 3, QGE_COLOR_WHITE, QGE_OUTLINE_DOT) );
      ++itSeg3;
    }

  deque<IPoint>::const_iterator itPoly2 = iPoly.accessVertices().begin();
  list<IQgarSegment>::iterator itSeg2 = segList2.begin();

  while( itSeg2 != segList2.end() )
    {
      IPoint s = *itPoly2;
      ++itPoly2;
      IPoint t = *itPoly2;

      CPPUNIT_ASSERT( *itSeg2 == IQgarSegment(s, t, 3, QGE_COLOR_WHITE, QGE_OUTLINE_DEFAULT) );
      ++itSeg2;
    }

  deque<IPoint>::const_iterator itPoly1 = iPoly.accessVertices().begin();
  list<IQgarSegment>::iterator itSeg1 = segList1.begin();

  while( itSeg1 != segList1.end() )
    {
      IPoint s = *itPoly1;
      ++itPoly1;
      IPoint t = *itPoly1;

      CPPUNIT_ASSERT( *itSeg1 == IQgarSegment(s, t, 3, QGE_COLOR_DEFAULT, QGE_OUTLINE_DEFAULT) );
      ++itSeg1;
    }

  deque<IPoint>::const_iterator itPoly0 = iPoly.accessVertices().begin();
  list<IQgarSegment>::iterator itSeg0 = segList0.begin();

  while( itSeg0 != segList0.end() )
    {
      IPoint s = *itPoly0;
      ++itPoly0;
      IPoint t = *itPoly0;

      CPPUNIT_ASSERT( *itSeg0 == IQgarSegment(s, t, 1, QGE_COLOR_DEFAULT, QGE_OUTLINE_DEFAULT) );
      ++itSeg0;
    }

}


// -------------------------------------------------------------------
// G E O M E T R Y :   T R A N S L A T I O N
// -------------------------------------------------------------------


void
GenPolylineTest::testTranslate()
{
  // ------
  // Set Up
  // ------

  int tx = 27;
  int ty = -89005;

  IPolyline iPoly(_iPtList);

  // -------
  // Process
  // -------

  iPoly.translate(tx,ty);

  // -----
  // Check
  // -----

  // Source and target are correctly translated
  IPoint s(_iPtList.front());
  s.translate(tx,ty);

  IPoint t(_iPtList.back());
  t.translate(tx,ty);

  CPPUNIT_ASSERT( iPoly.accessSource() == s );
  CPPUNIT_ASSERT( iPoly.accessTarget() == t );

  // Vertices are correctly translated
  const deque<IPoint>& dv = iPoly.accessVertices();
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
GenPolylineTest::testSerializeDeserialize()
{
  // ------
  // Set Up
  // ------

  IPolyline iPoly(_iPtList);
  FPolyline fPoly(_fPtList);
  DPolyline dPoly(_dPtList);

  IPolyline iOutInPoly;
  FPolyline fOutInPoly;
  DPolyline dOutInPoly;

  // -------
  // Process
  // -------

  std::stringstream ss;

  ss << iPoly;
  ss >> iOutInPoly;
  ss.flush();

  ss << fPoly;
  ss >> fOutInPoly;
  ss.flush();

  ss << dPoly;
  ss >> dOutInPoly;
  ss.flush();

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL(iPoly.source(), iOutInPoly.source());
  CPPUNIT_ASSERT_EQUAL(fPoly.source(), fOutInPoly.source());
  CPPUNIT_ASSERT_EQUAL(dPoly.source(), dOutInPoly.source());

  CPPUNIT_ASSERT_EQUAL(iPoly.target(), iOutInPoly.target());
  CPPUNIT_ASSERT_EQUAL(fPoly.target(), fOutInPoly.target());
  CPPUNIT_ASSERT_EQUAL(dPoly.target(), dOutInPoly.target());

  CPPUNIT_ASSERT( cmp(iPoly.accessVertices(), iOutInPoly.accessVertices()) );
  CPPUNIT_ASSERT( cmp(fPoly.accessVertices(), fOutInPoly.accessVertices()) );
  CPPUNIT_ASSERT( cmp(dPoly.accessVertices(), dOutInPoly.accessVertices()) );
}


// -------------------------------------------------------------------
// S O U R C E   A N D   T A R G E T   U P D A T E S
// -------------------------------------------------------------------


void
GenPolylineTest::testUpdateSourceTarget()
{
  // Rectangle triangle
  // (1,1) (1,4) (4,4)
 
  list<Point> lp;
  lp.push_back(Point(1,1));
  lp.push_back(Point(1,4));
  lp.push_back(Point(4,4));
  Polyline pll(lp);

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
