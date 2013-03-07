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


#ifndef __GENQGARSEGMENTTEST_H_INCLUDED__
#define __GENQGARSEGMENTTEST_H_INCLUDED__


/**
 * @file     GenQgarSegmentTest.h
 * @brief    Header file of class GenQgarSegmentTest
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 24, 2003  09:40
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete.
/* $Id: GenQgarSegmentTest.h,v 1.8 2005/09/14 10:53:38 masini Exp $ */



// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>



/**
 * @class GenQgarSegmentTest GenQgarSegmentTest.h
 * @brief Test class for class GenQgarSegment.
 * 
 * Untested function members:
 * - accessGeomStructure()
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 24, 2003  09:40
 * @since  Qgar 2.1.1
 */
class GenQgarSegmentTest : public CppUnit::TestFixture
{
// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( GenQgarSegmentTest );

  // Constructors
  CPPUNIT_TEST( testDefaultConstructor );
  CPPUNIT_TEST( testBuildFromSegment );
  CPPUNIT_TEST( testBuildFromTwoPoints );
  CPPUNIT_TEST( testBuildFromCoords );
  CPPUNIT_TEST( testCopyConstructor );

  // Copy
  CPPUNIT_TEST( testClone );

  // Access to geometrical features
  CPPUNIT_TEST( testLength );
  CPPUNIT_TEST( testRho );
  CPPUNIT_TEST( testAngles );

  // Geometrical predicates
  CPPUNIT_TEST( testContains );

  // Operators
  CPPUNIT_TEST( testAssignmentOp );
  CPPUNIT_TEST( testEqualOp );
  CPPUNIT_TEST( testNotEqualOp );

  // Functional operators
  CPPUNIT_TEST( testEq );
  CPPUNIT_TEST( testNotEq );

  // Geometry: Translation
  CPPUNIT_TEST( testTranslate );

  // Serialization
  CPPUNIT_TEST( testSerializeDeserialize );

  CPPUNIT_TEST_SUITE_END();


// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name TestFixture Impl */
//        ================
//@{

  virtual void setUp();

  virtual void tearDown();

//@}


/** @name Constructors */
//        ============
//@{

/**
 * @brief Tests qgar::GenQgarSegment::GenQgarSegment().
 *
 * Perfomed Tests:
 * - Ensure that a zero-length segment at (0,0) is created
 */
  void testDefaultConstructor();

/**
 * @brief Tests qgar::GenQgarSegment::GenQgarSegment(const GenQgarSegment<T>&).
 *
 * Perfomed Tests:
 * - Check that target and source of the duplicated object
 *   are equal to the original ones.
 */
  void testCopyConstructor();

/**
 * @brief Tests
 *   qgar::GenQgarSegment::GenQgarSegment(const GenSegment<T>&, QEGColor, int, QGEoutline).
 *
 * Perfomed Tests:
 * - Check that target and source of the duplicated object
 *   are equal to the original ones.
 */
  void testBuildFromSegment();

/**
 * @brief Tests
 *   qgar::GenQgarSegment::GenQgarSegment(const GenPoint<T>&, const GenPoint<T>&, QEGColor, int, QGEoutline).
 *
 * Perfomed Tests:
 * - Check that target, source, and additional features
 *   are correctly initialized
 */
  void testBuildFromTwoPoints();

/**
 * @brief Tests qgar::GenQgarSegment::GenQgarSegment(T, T, T, T, QEGColor, int, QGEoutline).
 *
 * Perfomed Tests:
 * - Same tests as for testBuildFromTwoPoints
 */
  void testBuildFromCoords();

//@}


/** @name Copy */
//        ====
//@{

/**
 * @brief Tests qgar::GenQgarSegment::clone().
 *
 * Perfomed Tests:
 * - Check that target and source of the duplicated object
 *   are equal to the original ones.
 */
  void testClone();

//@}


/** @name Access to geometrical features */
//        ==============================
//@{

/**
 * @brief Tests qgar::GenQgarSegment::length().
 *
 * Perfomed Tests:
 * - Ensure that the length of the segment is equal
 *   to the distance between the source
 *   and the target of the segment.
 */
  void testLength();

/**
 * @brief Tests qgar::GenQgarSegment::sqr_length().
 *
 * Perfomed Tests:
 * - Ensure that the square length of the segment is equal
 *   to the square of the distance between the source
 *   and the target of the segment.
 */
  void testSqrLength();

/**
 * @brief Tests qgar::GenQgarSegment::rho().
 *
 * Perfomed Tests:
 * - Ensure that the function returns the distance between
 *   point (0,0) and its perpendicular projection onto the line
 *   supporting the current segment.
 * - Ensure that the result is negative if the line supporting
 *   the segment intersects the Y axis at a negative value.
 */
  void testRho();

/**
 * @brief Tests qgar::GenQgarSegment::theta(),
 *              qgar::GenQgarSegment::thetaDegrees(),
 *              qgar::GenQgarSegment::angle(),
 *              qgar::GenQgarSegment::angleDegrees(),
 *              qgar::GenQgarSegment::slope(),
 *              qgar::GenQgarSegment::slopeDegrees().
 *
 * Perfomed Tests:
 * - Ensure that the functions return the angle between
 *   the X axis and the segment, in [0,2PI[ radians
 *   or [0,360[ degrees.
 */
  void testAngles();

//@}


/** @name Geometrical predicates */
//        ======================
//@{
/**
 * @brief Tests
 *   qgar::GenQgarSegment::contains(const GenPoint<T>&, double aDist).
 *
 * Perfomed Tests:
 * - Ensure that the given point is correctly considered as being
 *   on the line segment, regarding the given distance.
 */
  void testContains();

//@}


/** @name Operators */
//        =========
//@{

/**
 * @brief Tests qgar::GenQgarSegment::operator=(const GenQgarSegment<T>&).
 *
 * Perfomed Tests:
 * - Ensure that the operator returns a copy of the given segment.
 */
  void testAssignmentOp();

/**
 * @brief Tests qgar::GenQgarSegment::operator==(const GenQgarSegment<T>&).
 *
 * Perfomed Tests:
 * - Test operator reflexivity: Let S be a segment,
 *   ensure that (S == S) returns true.
 * - Test that a segment is not equal to another, different segment.
 * - Test that a segment is equal to a copy of itself
 */
  void testEqualOp();

/**
 * @brief Tests qgar::GenQgarSegment::operator!=(const GenQgarSegment<T>&).
 *
 * Perfomed Tests:
 * - Ensure that a segment is not equal to itself
 * - Check that two different segments are not equal.
 */
  void testNotEqualOp();

//@}


/** @name Functional operators */
//        ====================
//@{

/**
 * @brief Tests qgar::GenQgarSegment::eq(const GenQgarSegment<T>&)
 *   and qgar::GenQgarSegment::equal(const GenQgarSegment<T>&).
 *
 * Perfomed Tests:
 * - Check that a segment is equal to itself
 * - Check that a segment is equal to a copy of itself
 * - Check partial and full (in)equality
 */
  void testEq();

/**
 * @brief Tests qgar::GenQgarSegment::notEq(const GenQgarSegment<T>&)
 *   and qgar::GenQgarSegment::notEqual(const GenQgarSegment<T>&).
 *
 * Perfomed Tests:
 * - Check that a segment is not not-equal to itself
 * - Check that a segment is not not-equal to a copy of itself
 * - Check partial and full (in)equality
 */
  void testNotEq();

//@}


/** @name Geometry: Translation */
//        =====================
//@{

/**
 * @brief Tests qgar::GenQgarSegment::translate(T, T).
 *
 * Perfomed Tests:
 * - Check that the translation is correctly performed.
 */
  void testTranslate();

//@}


/** @name Serialization */
//        =============
//@{

/**
 * @brief Tests qgar::GenQgarSegment::read(std::istream&),
 *               qgar::GenQgarSegment::write(std::ostream&).
 *
 * Perfomed Tests:
 * - Serialize and deserialize a segment and compare it
 *   to the original.
 */
  void testSerializeDeserialize();

//@}


// -------------------------------------------------------------------
}; // class GenQgarSegmentTest


#endif /* __GENQGARSEGMENTTEST_H_INCLUDED__ */
