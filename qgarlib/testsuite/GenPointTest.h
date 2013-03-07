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


#ifndef __GENPOINTTEST_H_INCLUDED__
#define __GENPOINTTEST_H_INCLUDED__


/**
 * @file     GenPointTest.h
 * @brief    Header file of class GenPointTest
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 3, 2003  17:17
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenPointTest.h,v 1.9 2005/07/13 16:29:34 masini Exp $ */



// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>



/**
 * @class GenPointTest GenPointTest.h
 * @brief Test class for class GenPoint<T>
 *
 * Untested function members:
 * - x()
 * - y()
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 3, 2003  17:17
 * @since  Qgar 2.1.1
 */
class GenPointTest : public CppUnit::TestFixture
{

// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( GenPointTest );

  // CONSTRUCTORS
  CPPUNIT_TEST( testDefaultConstructor );
  CPPUNIT_TEST( testCopyConstructor );
  CPPUNIT_TEST( testBuildFromCoordsConstructor );
  CPPUNIT_TEST( testBuildFromOtherPoint );

  // ACCESS TO COORDINATES
  CPPUNIT_TEST( testRho );
  CPPUNIT_TEST( testTheta );

  // COORDINATE ASSIGNMENT
  CPPUNIT_TEST( testSetX );
  CPPUNIT_TEST( testSetY );
  CPPUNIT_TEST( testSetXY );

  // OPERATORS
  CPPUNIT_TEST( testAssignment );
  CPPUNIT_TEST( testOpPlus );
  CPPUNIT_TEST( testOpPlusEqual );
  CPPUNIT_TEST( testOpMinus );
  CPPUNIT_TEST( testOpMinusEqual );
  CPPUNIT_TEST( testOpEqual );
  CPPUNIT_TEST( testOpNotEqual );

  // FUNCTIONAL OPERATORS
  CPPUNIT_TEST( testPlus );
  CPPUNIT_TEST( testPlusEqual );
  CPPUNIT_TEST( testMinus );
  CPPUNIT_TEST( testMinusEqual );
  CPPUNIT_TEST( testEq );
  CPPUNIT_TEST( testNotEq );

  // GEOMETRY
  CPPUNIT_TEST( testProject );
  CPPUNIT_TEST( testTranslate );

  // SERIALIZATION
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


/** @name Constructor tests */
//        =================
//@{

/**
 * @brief Tests GenPoint()
 *
 * Performed Checks:
 * - ensure that point is correctly initialized to (0, 0)
 */
  void testDefaultConstructor();

/**
 * @brief Tests GenPoint(const GenPoint<T>&)
 *
 * Performed Checks:
 * - ensure that point coordinates are identical to the passed point.
 */
  void testCopyConstructor();

/**
 * @brief Tests GenPoint(const GenPoint<U>&)
 *
 * Performed Checks:
 * - ensure that point coordinates are correctly converted
 */
  void testBuildFromOtherPoint();

/**
 * @brief Tests GenPoint(T, T)
 *
 * Performed Checks:
 * - ensure that x() and y() return the passed values.
 */
  void testBuildFromCoordsConstructor();

//@}


/** @name Access to coordinates tests */
//        ===========================
//@{

/**
 * @brief Tests rho()
 * 
 * Performed Checks:
 * - test computation with three different examples.
 */
  void testRho();

/**
 * @brief Test tetha()
 * 
 * Performed Checks:
 * - test computation with three different examples.
 */
  void testTheta();

//@}


/** @name Coordinate assignment tests */
//        ===========================
//@{

/**
 * @brief Tests setX(T)
 * 
 * Performed Checks:
 * - test that x() returns the value setted.
 */
  void testSetX();

/**
 * @brief Tests setY(T)
 * 
 * Performed Checks:
 * - test that y() returns the value setted.
 */
  void testSetY();

/**
 * @brief Tests setXY(T)
 * 
 * Performed Checks:
 * - test that x() and y() return the values setted.
 */
  void testSetXY();

//@}


/** @name Operator tests */
//        ==============
//@{

/**
 * @brief Tests operator=(const GenPoint<T>&)
 *
 * Performed Checks:
 * - Test that values for x() and y() are correctly assigned .
 * - Check that the function returns a valid reference on the left
 *   hand side of the assignment.
 */
  void testAssignment();

/**
 * @brief Tests operator+(const GenPoint<T>&)
 *
 * Performed Checks:
 * - Test operator on 3 examples.
 */
  void testOpPlus();

/**
 * @brief Tests operator+=(const GenPoint<T>&)
 *
 * Performed Checks:
 * - Test operator on 3 examples.
 * - Check that the function returns a valid reference on the left
 *   hand side operand.
 */
  void testOpPlusEqual();

/**
 * @brief Tests operator-(const GenPoint<T>&)
 *
 * Performed Checks:
 * - Test operator on 3 examples.
 */
  void testOpMinus();

/**
 * @brief Tests operator-=(const GenPoint<T>&)
 *
 * Performed Checks:
 * - Test operator on 3 examples. 
 * - Check that the function returns a valid reference on the left
 *   hand side operand.
 */
  void testOpMinusEqual();

/**
 * @brief Tests operator==(const GenPoint<T>&)
 *
 * Performed Checks:
 * - Test function refexivity: let A a point ensure that A == A.
 * - Test equality on 3 examples.
 */
  void testOpEqual();

/**
 * @brief Tests operator!=(const GenPoint<T>&)
 *
 * Performed Checks:
 * - Check That a point is equal to itself using a double negation:
 *   let A a point ensure that !(A != A).
 * - Check that a point is not equal to another .
 */
  void testOpNotEqual();

//@}


/** @name Functional operator tests */
//        =========================
//@{

/**
 * @brief Tests plus(const GenPoint<T>&)
 *
 * Performed Checks:
 * - Test function on 3 examples.
 */
  void testPlus();

/**
 * @brief Tests plusEqual(const GenPoint<T>&)
 *
 * Performed Checks:
 * - Test function on 3 examples.
 * - Check that the function returns a valid reference on the left
 *   hand side operand.
 */
  void testPlusEqual();

/**
 * @brief Tests minus(const GenPoint<T>&)
 *
 * Performed Checks:
 * - Test function on 3 examples.
 */
  void testMinus();

/**
 * @brief Tests minusEqual(const GenPoint<T>&)
 *
 * Performed Checks:
 * - Test operator on 3 examples.
 * - Check that the function returns a valid reference on the left
 *   hand side operand.
 */
  void testMinusEqual();

/**
 * @brief Tests eq(const GenPoint<T>&)
 *
 * Performed Checks:
 * - Test function refexivity: let A a point ensure that A.eq(A).
 * - Test equality on 3 examples.
 */
  void testEq();

/**
 * @brief Tests notEq(const GenPoint<T>&)
 *
 * Performed Checks:
 * - Check That a point is equal to itself using a double negation:
 *   let A a point ensure that !(A.notEq(A)).
 * - Check that a point is not equal to another .
 */
  void testNotEq();

//@}


/** @name Geometry tests */
//        ==============
//@{

/**
 * @brief Tests
 *   project(const GenSegment<T>&) and project(const GenQgarSegment<T>&)
 *
 * Performed Tests:
 * - Ensure that the returned segment is perpendicular to the original
 *   segment.
 */
  void testProject();

/**
 * @brief Tests translated(T, T)
 *
 * Performed Checks:
 * - test the correctness of the coordinates of the translated point.
 */
  void testTranslate();

//@}


/** @name Serialization tests */
//        ===================
//@{

/**
 * @brief Tests (de)serialization operators
 *
 * Performed Checks:
 * - Serialize and deserialize a point an compare it to the original.
 */
  void testSerializeDeserialize();

//@}

// -------------------------------------------------------------------
}; // class GenPointTest




#endif /* __GENPOINTTEST_H_INCLUDED__ */
