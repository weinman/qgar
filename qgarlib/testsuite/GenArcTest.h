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


#ifndef __GENARCTEST_H_INCLUDED__
#define __GENARCTEST_H_INCLUDED__


/**
 * @file     GenArcTest.h
 * @brief    Header file of class GenArcTest
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 14, 2003  17:45
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenArcTest.h,v 1.6 2005/07/13 16:29:34 masini Exp $ */



// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>



/**
 * @class GenArcTest GenArcTest.h
 * @brief Test class for class GenArc<T>
 *
 * Untested function member:
 * - qgar::GenArc::updateSource
 * - qgar::GenArc::updateSourceTarget
 * - qgar::GenArc::updateTarget
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 14, 2003  17:45
 * @since  Qgar 2.1.1
 */
class GenArcTest

  : public CppUnit::TestFixture

{

// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( GenArcTest );

  // Constructors
  CPPUNIT_TEST( testDefaultConstructor );
  CPPUNIT_TEST( testCopyConstructor );
  CPPUNIT_TEST( testBuildFromQgarArc );
  CPPUNIT_TEST( testBuildFrom3Points );

  // Copy
  CPPUNIT_TEST( testClone );

  // Access to geometrical features
  CPPUNIT_TEST( testRadius );
  CPPUNIT_TEST( testLength );
  CPPUNIT_TEST( testAngles );

  // Center
  CPPUNIT_TEST( testCenter );

  // Operators
  CPPUNIT_TEST( testAssignment );
  CPPUNIT_TEST( testIn_Equality );

  // Geometry: Translation
  CPPUNIT_TEST( testTranslate );

  // Serialization
  CPPUNIT_TEST( testSerializeDeserialize );

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
 * @brief Tests qgar::GenArc::GenArc().
 *
 * Performed Checks:
 * - Ensure that center, radius, source angle, target angle are
 *   correctly initialized to 0.
 */
  void testDefaultConstructor();

/**
 * @brief Tests qgar::GenArc::GenArc(const GenArc&).
 *
 * Performed Checks:
 * - Ensure that the values of center, radius, source angle and target
 *   angle are correctly duplicated.
 */
  void testCopyConstructor();

/**
 * @brief Tests qgar::GenArc::GenArc(const GenQgarArc&).
 *
 * Performed Checks:
 * - Ensure that the values of center, radius, source angle and target
 *   angle are equal to the ones of the Qgar arc.
 */
  void testBuildFromQgarArc();

/**
 * @brief Tests
 *   qgar::GenArc::GenArc(const GenPoint&, const GenPoint&, const GenPoint&).
 *
 * Performed Checks:
 * - Ensure that the center point is correctly copied.
 * - Ensure that source angle is equal to the angle of [center, sourcePt]
 * - Ensure that the target angle is equal to the angle of [center, targetPoint]
 */
  void testBuildFrom3Points();

//@}


/** @name Copy */
//        ====
//@{

/**
 * @brief Tests qgar::GenArc::clone().
 *
 * Performed Checks:
 * - Ensure that the features of the created object are the same as
 *   those of the original one.
 */
  void testClone();

//@}


/** @name Access to geometrical features */
//        ==============================
//@{

/**
 * @brief Tests qgar::GenArc::radius().
 *
 * Performed Checks:
 * - Ensure that the value of the radius is correct.
 */
  void testRadius();

/**
 * @brief Tests qgar::GenArc::length().
 *
 * Performed Checks:
 * - Ensure that the value of the length is correct.
 */
  void testLength();

/**
 * @brief Tests
 *   qgar::GenArc::sourceAngle(),
 *   qgar::GenArc::sourceAngleDegrees(),
 *   qgar::GenArc::targetAngle(),
 *   qgar::GenArc::targetAngleDegrees(),
 *   qgar::GenArc::angle(),
 *   and qgar::GenArc::angleDegrees().
 *
 * Performed Tests:
 * - Ensure that source angle, target angle, and arc angle are
 *   correctly computed, in radians as well as in degrees.
 */
  void testAngles();

//@}


/** @name Center */
//        ======
//@{

/**
 * @brief Tests
 *   qgar::GenArc::accessCenter,
 *   qgar::GenArc::center,
 *   qgar::GenArc::xCenter,
 *   qgar::GenArc::yCenter,
 *   qgar::GenArc::setXCenter,
 *   qgar::GenArc::setYCenter,
 *   qgar::GenArc::setCenter(T,T),
 *   and qgar::GenArc::setCenter(const GenPoint<T>&).
 *
 * Performed Checks:
 * - Check that the coordinates of the center are correctly
 *   accessed and modified.
 */
  void testCenter();

//@}


/** @name Operators */
//        =========
//@{

/**
 * @brief Tests qgar::GenArc::operator=(const GenArc&).
 *
 * Performed Checks:
 * - Ensure that the values of center, radius, source angle and target
 *   angle are equal to those of the rhs of the assignment.
 * - Check that the function returns a valid reference on the left
 *   hand side of the assignment.
 */
  void testAssignment();

/**
 * @brief Tests
 *   qgar::GenArc::operator==(const GenArc&),
 *   qgar::GenArc::eq(const GenArc&),
 *   qgar::GenArc::operator!=(const GenArc&),
 *   and
 *   qgar::GenArc::notEq(const GenArc&).
 *
 * Performed Checks:
 * - Ensure that arcs are correctly compared.
 */
  void testIn_Equality();

//@}


/** @name Geometry: Translation */
//        =====================
//@{

/**
 * @brief Tests qgar::GenArc::translate.
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
 * @brief Tests qgar::GenArc::read(std::istream&),
 *   and qgar::GenArc::write(std::ostream&).
 *
 * Performed Checks:
 * - Serialize and deserialize an arc, then ensure that the resulting arc
 *   is equal to the initial one.
 */
  void testSerializeDeserialize();

//@}


// -------------------------------------------------------------------
}; // class GenArcTest



#endif /* __GENARCTEST_H_INCLUDED__ */
