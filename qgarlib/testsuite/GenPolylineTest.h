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


#ifndef __GENPOLYLINETEST_H_INCLUDED__
#define __GENPOLYLINETEST_H_INCLUDED__


/**
 * @file     GenPolylineTest.h
 * @brief    Header file of class GenPolylineTest
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 16, 2003  10:45
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenPolylineTest.h,v 1.5 2005/07/13 16:29:34 masini Exp $ */



// STD
#include <list>
// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>
// QGAR
#include <qgarlib/primitives.h>
#include <qgarlib/QgarErrorUser.h>



/**
 * @class GenPolylineTest GenPolylineTest.h
 * @brief Test class for class qgar::GenPolyline.
 * 
 * Untested function members:
 * - qgar::GenPolyline::accessVertices
 * - qgar::GenPolyline::vertices
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 16, 2003  10:45
 * @since  Qgar 2.1.1
 */
class GenPolylineTest

  : public CppUnit::TestFixture

{
// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( GenPolylineTest );

  // Constructors
  CPPUNIT_TEST( testDefaultConstructor );
  CPPUNIT_TEST( testCopyConstructor );
  CPPUNIT_TEST( testBuildFromQgarPolyline );
  CPPUNIT_TEST( testBuildFromQgarSegment );
  CPPUNIT_TEST( testBuildFromSegment );
  CPPUNIT_TEST( testBuildFrom2Points );
  CPPUNIT_TEST( testBuildFromPointList );
  CPPUNIT_TEST_EXCEPTION( testBuildFromPointListExc, qgar::QgarErrorUser );

  // Copy
  CPPUNIT_TEST( testClone );

  // Operators
  CPPUNIT_TEST( testAssignment );

  // Access to vertices
  CPPUNIT_TEST( testSize );
  CPPUNIT_TEST( testGetVertices );

  // Insert vertices
  CPPUNIT_TEST( testAppendSource );
  CPPUNIT_TEST( testAppendTarget );
  CPPUNIT_TEST( testAppendPoly );
  CPPUNIT_TEST( testAppendQgarPoly );
  CPPUNIT_TEST( testAppendPtVect );

  // Remove vertices
  CPPUNIT_TEST( testRemove );
  CPPUNIT_TEST_EXCEPTION( testRemoveExc, qgar::QgarErrorUser );

  // Conversions
  CPPUNIT_TEST( testToPointVector );
  CPPUNIT_TEST( testToSegList );
  CPPUNIT_TEST( testToQgarSegList );

  // Geometry: Translation
  CPPUNIT_TEST( testTranslate );

  // Serialization/deserialization
  CPPUNIT_TEST( testSerializeDeserialize );

  // Spurce and target updates
  CPPUNIT_TEST( testUpdateSourceTarget );

  CPPUNIT_TEST_SUITE_END();


// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name Test Fixture Implementation */
//        ===========================
//@{

  virtual void setUp();

  virtual void tearDown();

//@}


/** @name Constructors */
//        ============
//@{

/**
 * @brief Tests GenPolyline()
 *
 * Performed Checks:
 * - Ensure that the list of vertices is created empty.
 */
  void testDefaultConstructor();

/**
 * @brief Tests GenPolyline(const GenPolyline&)
 *
 * Performed Checks:
 * - Ensure that the source, target and the list of vertices equal
 *   to thoses of the original polyline.
 */
  void testCopyConstructor();

/**
 * @brief Tests GenPolyline(const GenQgarPolyline&)
 *
 * Performed Checks:
 * - Ensure that the source, target and the list of vertices are equal
 *   to those of the Qgar polyline.
 */
  void testBuildFromQgarPolyline();

/**
 * @brief Tests GenPolyline(const GenQgarSegment&)
 *
 * Performed Checks:
 * - Ensure that the source of the polyline is the source of the
 *   Qgar segment.
 * - Ensure that the target of the polyline is the target of the
 *   Qgar segment.
 * - Ensure that the vertices list of the polyline contains only two
 *   points.
 */
  void testBuildFromQgarSegment();

/**
 * @brief Tests GenPolyline(const GenSegment&)
 *
 * Performed Checks:
 * - Ensure that the source of the polyline is the source of the
 *   segment.
 * - Ensure that the target of the polyline is the target of the
 *   segment.
 * - Ensure that the vertices list of the polyline contains only two
 *   points.
 */
  void testBuildFromSegment();

/**
 * @brief Tests GenPolyline(const GenPoint&, const GenPoint&)
 *
 * Performed Checks:
 * - Ensure that the source of the polyline is equal to the first
 *   point.
 * - Ensure that the target of the polyline is equal to the second
 *   point.
 * - Ensure that the vertices list contains only two points.
 */
  void testBuildFrom2Points();

/**
 * @brief Tests GenPolyline(const list<GenPoint>&)
 *
 * Performed Checks:
 * - Ensure that the polyline source is equal to the first point of
 *   the list.
 * - Ensure that the polyline target is equal to the last point of
 *   the list.
 * - Ensure that the list of vertices of the polyline is equal to the
 *   list of points used to build it.
 */
  void testBuildFromPointList();

/**
 * @brief Tests GenPolyline(const std::list<GenPoint>&)
 *
 * Performed Checks:
 * - Giving a list containing less than 2 vertices
 *   throws a qgar::QgarErrorUser exception
 */
  void testBuildFromPointListExc();

//@}


/** @name Copy */
//        ====
//@{

/**
 * @brief Tests clone()
 *
 * Performed Checks:
 * -
 */
  void testClone();

//@}


/** @name Operators */
//        =========
//@{

/**
 * @brief Tests operator=(const GenPolyline&)
 *
 * Performed Checks:
 * - Ensure that the list of vertices of the rhs and the lhs polylines
 *   are equal after the assignment.
 * - Ensure that the function returns a valid reference on the lhs of
 *   the assignment.
 */
  void testAssignment();

//@}


/** @name Access to vertices */
//        ==================
//@{

/**
 * @brief Tests size()
 *
 * Performed Checks:
 * - Ensure that returned number is the effective number of vertices
 */
  void testSize();

/**
 * @brief Tests getVertices()
 *
 * Performed Checks:
 * - a client can directly modify the vertices of a polyline
 */
  void testGetVertices();

//@}


/** @name Insert vertices */
//        ===============
//@{

/**
 * @brief Tests appedSource(const GenPoint&)
 *
 * Performed Checks:
 * - Ensure that the passed point becomes the new source of the
 *   polyline.
 * - Ensure that the size of the list of vertices is incremented by
 *   one after the call.
 * - Ensure that the function returns a valid reference on 'this'.
 */
  void testAppendSource();

/**
 * @brief Tests appendTarget(const GenPoint&)
 *
 * Performed Checks:
 * - Ensure that the passed point becomes the new target of the
 *   polyline.
 * - Ensure that the size of the list of vertices is incremented by
 *   one after the call.
 * - Ensure that the function returns a valid reference on 'this'.
 */
  void testAppendTarget();

/**
 * @brief Tests append(const GenPolyline&)
 *
 * Performed Checks:
 * - Ensure that the size of the list of vertices of the polyline is
 *   equal to the sum of the sizes of the vertices lists of both
 *   polylines before the call.
 * - Ensure that target the polyline is equal to the target of the
 *   given polyline.
 * - Ensure that the vertices list of the polyline after the call is
 *   equal to its previous vertices list plus the vertices list
 *   of the given polyline.
 * - Ensure that the function returns a valid reference on 'this'.
 */
  void testAppendPoly();

/**
 * @brief Tests append(const GenQgarPolyline&)
 *
 * Performed Checks:
 * - Ensure that the size of the list of vertices of the polyline is
 *   equal to the sum of the sizes of the vertices lists of both
 *   polylines before the call.
 * - Ensure that target the polyline is equal to the target of the
 *   given polyline.
 * - Ensure that the vertices list of the polyline after the call is
 *   equal to its previous vertices list plus the vertices list
 *   of the given polyline.
 * - Ensure that the function returns a valid reference on 'this'.
 */
  void testAppendQgarPoly();

/**
 * @brief Tests append(const std::vector<GenPoint>&)
 *
 * Performed Checks:
 * - Ensure that the size of the list of vertices of the polyline is
 *   equal to the size of the vertices list before the call plus the
 *   size of the point vector.
 * - Ensure that the target of the polyline is equal to the last
 *   element of the vector.
 * - Ensure that the vertices list of the polyline is equal to the
 *   previous vertices list plus the points of the vector.
 * - Ensure that the function return a valid reference on 'this'.
 */
  void testAppendPtVect();

//@}


/** @name Remove vertices */
//        ===============
//@{

/**
 * @brief Tests remove(const GenPoint&)
 *
 * Performed Checks:
 * - Ensure that the size of the list of decremented by one after a
 *   successfull removal.
 * - Ensure that the source is correctly updated if the source point
 *   has to be removed.
 * - Ensure that the target is correctly updated if the target point
 *   has to be removed.
 */
  void testRemove();

/**
 * @brief Tests remove(const GenPoint&)
 *
 * Performed Checks:
 * - Removing a vertex from a polyline containing 2 vertices
 *   throws a qgar::QgarErrorUser exception
 */
  void testRemoveExc();

//@}


/** @name Conversions */
//        ===========
//@{

/**
 * @brief Tests toPointVector()
 *
 * Performed Checks:
 * - Ensure that the list of vertices of the polyline are correctly
 *   copied in the vector.
 */
  void testToPointVector();

/**
 * @brief Tests toSegList()
 *
 * Performed Checks:
 * - Ensure that the size of the segment list is equal to the size of
 *   the polyline vertices list minus one.
 * - Test if the segments of the segment list are correctly built.
 */
  void testToSegList();

/**
 * @brief Tests toQgarSegList()
 *
 * Performed Checks:
 * - Ensure that the size of the qgar segment list is equal to the
 *   size of the polyline vertices list minus one.
 * - Test if the segments of the segment list are correctly built.
 */
  void testToQgarSegList();

//@}


/** @name Geometry: Translation */
//        =====================
//@{

/**
 * @brief Tests translate(T,T)
 *
 * Performed Checks:
 * - Ensure that the coordinates of the translated polyline conforms
 *   to the translation specified by the arguments.
 */ 
  void testTranslate();

//@}


/** @name Serialization/deserialization */
//        =============================
//@{

/**
 * @brief Tests operator<< and operator>>
 *
 * Performed Checks:
 * - Serialize and deserialize a polyline and ensure that it is equal
 *   to the original
 */ 
  void testSerializeDeserialize();

//@}


/** @name Source and target updates */
//        =========================
//@{

/**
 * @brief Tests correctness of functions 
 *   qgar::GenPolyline::updateSource(),
 *   qgar::GenPolyline::updateTarget(),
 *   and
 *   qgar::GenPolyline::updateSourceTarget().
 * when using functions
 *   qgar::GenPolyline::fixSource,
 *   qgar::GenPolyline::fixTarget,
 *   qgar::GenPolyline::fixSourceTarget,
 *   qgar::GenPolyline::fixXSource,
 *   qgar::GenPolyline::fixYSource,
 *   qgar::GenPolyline::fixXTarget,
 *   and
 *   qgar::GenPolyline::fixYTarget.
 *
 * Performed Tests:
 * - source and target modifications are propagated into vertices list
 */
  void testUpdateSourceTarget();

//@}


// -------------------------------------------------------------------
// P R O T E C T E D   M E M B E R S
// -------------------------------------------------------------------
protected:

  qgar::IPoint _iPt0;
  qgar::IPoint _iPt1;
  qgar::IPoint _iPt2;
  qgar::IPoint _iPt3;

  std::list<qgar::IPoint> _iPtList;

  qgar::FPoint _fPt0;
  qgar::FPoint _fPt1;
  qgar::FPoint _fPt2;
  qgar::FPoint _fPt3;

  std::list<qgar::FPoint> _fPtList;

  qgar::DPoint _dPt0;
  qgar::DPoint _dPt1;
  qgar::DPoint _dPt2;
  qgar::DPoint _dPt3;

  std::list<qgar::DPoint> _dPtList;


// -------------------------------------------------------------------

}; // class GenPolylineTest


#endif /* __GENPOLYLINETEST_H_INCLUDED__ */
