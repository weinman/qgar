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


#ifndef __GENSEGMENTTEST_H_INCLUDED__
#define __GENSEGMENTTEST_H_INCLUDED__


/**
 * @file     GenSegmentTest.h
 * @brief    Header file of class GenSegmentTest.
 *
 * Untested function member:
 * - qgar::GenSegment::updateSource
 * - qgar::GenSegment::updateTarget
 * - qgar::GenSegment::updateSourceTarget
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 8, 2003  15:46
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenSegmentTest.h,v 1.8 2005/09/14 10:53:38 masini Exp $ */



// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>



/**
 * @class GenSegmentTest GenSegmentTest.h
 * @brief Test class for class qgar::GenSegment<T>.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 8, 2003  15:46
 * @since  Qgar 2.1.1
 */
class GenSegmentTest

  : public CppUnit::TestFixture

{
// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( GenSegmentTest );

  // Constructors
  CPPUNIT_TEST( testDefaultConstructor );
  CPPUNIT_TEST( testBuildFromQgarSegment );
  CPPUNIT_TEST( testBuildFromTwoPoints );
  CPPUNIT_TEST( testBuildFrom4Coords );
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
 * @brief Tests qgar::GenSegment::GenSegment().
 *
 * Perfomed Tests:
 * - Ensure that a zero-length segment at (0,0) is created
 */
  void testDefaultConstructor();

/**
 * @brief Tests qgar::GenSegment::GenSegment(const GenSegment<T>&).
 *
 * Perfomed Tests:
 * - Check that target and source of the duplicated object
 *   are equal to the original ones.
 */
  void testCopyConstructor();

/**
 * @brief Tests qgar::GenSegment::GenSegment(const GenQgarSegment<T>&).
 *
 * Perfomed Tests:
 * - Check that target and source of the duplicated object
 *   are equal to the original ones.
 */
  void testBuildFromQgarSegment();

/**
 * @brief Tests qgar::GenSegment::GenSegment(const GenPoint<T>&, const GenPoint<T>&).
 *
 * Perfomed Tests:
 * - Check that target and source are correctly initialized
 */
  void testBuildFromTwoPoints();

/**
 * @brief Tests qgar::GenSegment::GenSegment(T, T, T, T).
 *
 * Perfomed Tests:
 * - Same tests as for testBuildFromTwoPoints
 */
  void testBuildFrom4Coords();

//@}


/** @name Copy */
//        ====
//@{

/**
 * @brief Tests qgar::GenSegment::clone().
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
 * @brief Tests qgar::GenSegment::length().
 *
 * Perfomed Tests:
 * - Ensure that the length of the segment is equal
 *   to the distance between the source
 *   and the target of the segment.
 */
  void testLength();

/**
 * @brief Tests qgar::GenSegment::sqr_length().
 *
 * Perfomed Tests:
 * - Ensure that the square length of the segment is equal
 *   to the square of the distance between the source
 *   and the target of the segment.
 */
  void testSqrLength();

/**
 * @brief Tests qgar::GenSegment::rho().
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
 * @brief Tests qgar::GenSegment::theta(),
 *              qgar::GenSegment::thetaDegrees(),
 *              qgar::GenSegment::angle(),
 *              qgar::GenSegment::angleDegrees(),
 *              qgar::GenSegment::slope(),
 *              qgar::GenSegment::slopeDegrees().
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
 *   qgar::GenSegment::contains(const GenPoint<T>&, double aDist).
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
 * @brief Tests qgar::GenSegment::operator=(const GenSegment<T>&).
 *
 * Perfomed Tests:
 * - Ensure that the operator returns a copy of the given segment.
 */
  void testAssignmentOp();

/**
 * @brief Tests qgar::GenSegment::operator==(const GenSegment<T>&).
 *
 * Perfomed Tests:
 * - Test operator reflexivity: Let S be a segment,
 *   ensure that (S == S) returns true.
 * - Test that a segment is not equal to another, different segment.
 * - Test that a segment is equal to a copy of itself
 */
  void testEqualOp();

/**
 * @brief Tests qgar::GenSegment::operator!=(const GenSegment<T>&).
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
 * @brief Tests qgar::GenSegment::eq(const GenSegment<T>&).
 *
 * Perfomed Tests:
 * - Test function reflexivity: let S be a segment,
 *   ensure that S.eq(S) returns true.
 * - Test that a segment is not equal to another, different segment.
 * - Test that a segment is equal to a copy of itself
 */
  void testEq();

/**
 * @brief Tests qgar::GenSegment::notEq(const GenSegment<T>&).
 *
 * Perfomed Tests:
 * - Ensure that a segment is not equal to itself
 * - Check that two different segments are not equal.
 */
  void testNotEq();

//@}


/** @name Geometry: Translation */
//        =====================
//@{

/**
 * @brief Tests qgar::GenSegment::translate(T, T).
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
 * @brief Tests qgar::GenSegment::read(std::istream&),
 *   and qgar::GenSegment::write(std::ostream&).
 *
 * Perfomed Tests:
 * - Serialize and deserialize a segment and compare it
 *   to the original.
 */
  void testSerializeDeserialize();

//@}


// -------------------------------------------------------------------
}; // class GenSegmentTest


#endif /* __GENSEGMENTTEST_H_INCLUDED__ */
