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


#ifndef __GENQGARPOLYLINETEST_H_INCLUDED__
#define __GENQGARPOLYLINETEST_H_INCLUDED__


/**
 * @file     GenQgarPolylineTest.h
 * @brief    Header file of class GenQgarPolylineTest
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 29, 2003  09:41
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete.
/* $Id: GenQgarPolylineTest.h,v 1.5 2005/07/13 16:29:34 masini Exp $ */



// STL
#include <list>
// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>
// QGAR
#include <qgarlib/primitives.h>
#include <qgarlib/QgarErrorUser.h>



/**
 * @class GenQgarPolylineTest GenQgarPolylineTest.h
 * @brief Test class for class GenQgarPolylineTest.
 * 
 * Untested function members:
 * - GenQgarPolylineTest::accessVertices
 * - GenQgarPolylineTest::vertices
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 29, 2003  09:41
 * @since  Qgar 2.1.1
 */
class GenQgarPolylineTest : public CppUnit::TestFixture
{
// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( GenQgarPolylineTest );

  // Constructors
  CPPUNIT_TEST( testDefaultConstructor );
  CPPUNIT_TEST( testCopyConstructor );
  CPPUNIT_TEST( testBuildFromPolyline );
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
 * @brief Tests GenQgarPolyline(int, QGEcolor, QGEoutline)
 *
 * Performed Checks:
 * - Ensure that the color, the thickness and the outline are
 *   correctly assigned.
 * - Ensure that the geomStructure is equal to a polyline created with
 *   the default constructor.
 */
  void testDefaultConstructor();

/**
 * @brief Tests GenQgarPolyline(const GenQgarPolyline&)
 *
 * Performed Checks:
 * - Ensure that the color, the thickness and the outline are
 *   equal to those of the object passed as parameter.
 * - Ensure that the geomStructure of the created object is equal to
 *   the one of the original.
 */
  void testCopyConstructor();

/**
 * @brief Tests GenQgarPolyline(const GenPolyline&, int, QGEcolor, QGEoutline)
 *
 * Performed Tests:
 * - Ensure that the color, the thickness and the outline are
 *   correctly assigned.
 * - Ensure that the geomStructure is equal to a polyline passed as
 *   parameter.
 */
  void testBuildFromPolyline();

/**
 * @brief Tests GenQgarPolyline(const GenQgarSegment&)
 *
 * Performed Tests:
 * - Ensure that the color, the thickness and the outline of the
 *   created polyline are equal to those of the parameter Qgar
 *   segment. 
 * - Ensure that the geomStructure is equal to a polyline created from
 *   the given Qgar segment.
 */
  void testBuildFromQgarSegment();

/**
 * @brief Tests GenQgarPolyline(const GenSegment&, int, QGEcolor, QGEoutline)
 *
 * Performed Tests:
 * - Ensure that the color, the thickness and the outline are
 *   correctly assigned.
 * - Ensure that the geomStructure is equal to a polyline created from
 *   the given segment.
 */
  void testBuildFromSegment();

/**
 * @brief Tests GenQgarPolyline(const GenPoint&, const GenPoint&)
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
 * @brief Tests GenQgarPolyline(const std::list<GenPoint<T> >&, int, QGEcolor, QGEoutline)
 *
 * Performed Tests:
 * - Ensure that the color, the thickness and the outline are
 *   correctly assigned.
 * - Ensure that the geomStructure is equal to a polyline created from
 *   the point list.
 */
  void testBuildFromPointList();

/**
 * @brief Tests GenQgarPolyline(const std::list<GenPoint>&, int, QGEcolor, QGEoutline))
 *
 * Performed Checks:
 * - Giving a list containing less than 2 vertices
 *   throws a qgar::QgarErrorUser exception
 */
  void testBuildFromPointListExc();


/** @name Copy */
//        ====
//@{


/**
 * @brief Tests clone()
 *
 * Performed Checks:
 * - Ensure that thickness, color and outline are those of rhs instance.
 * - Ensure that the geometrical structure of the created object is the
 *   same as the one of the rhs instance.
 */
  void testClone();

//@}


/** @name Operators */
//        =========
//@{

/**
 * @brief Tests operator=(const GenQgarPolyline&)
 *
 * Performed Checks:
 * - Ensure that thickness, color and outline are those of rhs instance.
 * - Ensure that the geometrical structure of the created object is the
 *   same as the one of the rhs instance.
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
 * - Ensure that the function allows the client to directly modify
 *   the vertices of a polyline
 */
  void testGetVertices();

//@}


/** @name Insert vertices */
//        ===============
//@{

/**
 * @brief Tests appendSource(const GenPoint&)
 *
 * Performed Tests:
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
 * Performed Tests:
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
 * Performed Tests:
 * - Ensure that the thickness, color and outline are not modified by
 *   the function.
 * - Ensure that the size of the list of vertices of the polyline is
 *   equal to the sum of the sizes of the vertices lists of both
 *   polyline before the call.
 * - Ensure that target the polyline is equal to the target of the
 *   polyline passed as parameter.
 * - Ensure that the vertices list of the polyline after the call is
 *   equal to its previous vertices list plus the parameter polyline
 *   vertices list.
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
 * @brief Tests append(const vector<GenPoint>&)
 *
 * Performed Tests:
 * - Ensure that the color, thickness and outline are not modified by
 *   the function.
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


/** @name Remove vertices */
//        ===============
//@{

/**
 * @brief Tests remove(const GenPoint&)
 *
 * Performed Tests:
 * - Ensure that the size of the list of decremented by one after a
 *   successfull removal.
 * - Ensure that the source is correctly updated if the source point
 *   is to be removed.
 * - Ensure that the target is correctly updated if the target point
 *   is to be removed.
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
 * Performed Tests:
 * - Ensure that the list of vertices of the polyline are correctly
 *   copied in the vector.
 */
  void testToPointVector();

/**
 * @brief Tests toSegList()
 *
 * Performed Tests:
 * - Ensure that the size of the segment list is equal to the size of
 *   the polyline vertices list minus one.
 * - Test if the segments of the segment list are correctly build.
 */
  void testToSegList();

/**
 * @brief Tests toQgarSegList()
 *
 * Performed Tests:
 * - Ensure that the color, thickness and outline of the created
 *   segments are equal to those of the Qgar polyline.
 * - Ensure that the size of the qgar segment list is equal to the
 *   size of the polyline vertices list minus one.
 * - Test if the segments of the segment list are correctly build.
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
 * Performed Tests:
 * - Serialize and deserialize a polyline and ensure that it is equal
 *   to the original.
 */
  void testSerializeDeserialize();

//@}


/** @name Source and target updates */
//        =========================
//@{

/**
 * @brief Tests correctness of functions 
 *   qgar::GenQgarPolyline::updateSource(),
 *   qgar::GenQgarPolyline::updateTarget(),
 *   and
 *   qgar::GenQgarPolyline::updateSourceTarget().
 * when using functions
 *   qgar::GenQgarPolyline::fixSource,
 *   qgar::GenQgarPolyline::fixTarget,
 *   qgar::GenQgarPolyline::fixSourceTarget,
 *   qgar::GenQgarPolyline::fixXSource,
 *   qgar::GenQgarPolyline::fixYSource,
 *   qgar::GenQgarPolyline::fixXTarget,
 *   and
 *   qgar::GenQgarPolyline::fixYTarget.
 *
 * Performed Tests:
 * - source and target modifications are propagated into vertices list
 */
  void testUpdateSourceTarget();

//@}


// -------------------------------------------------------------------
// P R O T E C T E D   M E M B E R
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
}; // class GenQgarPolylineTest


#endif /* __GENQGARPOLYLINETEST_H_INCLUDED__ */
