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


#ifndef __GENQGARARCTEST_H_INCLUDED__
#define __GENQGARARCTEST_H_INCLUDED__


/**
 * @file     GenQgarArcTest.h
 * @brief    Header file of class GenQgarArcTest
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date     October 27, 2003  15:13
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete.
/* $Id: GenQgarArcTest.h,v 1.6 2005/07/13 16:29:34 masini Exp $ */



// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>



/**
 * @class GenQgarArcTest GenQgarArcTest.h
 * @brief Test class for class GenQgarArc.
 * 
 * Untested function members:
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   October 27, 2003  15:13
 * @since  Qgar 2.1.1
 */
class GenQgarArcTest

  : public CppUnit::TestFixture

{
// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( GenQgarArcTest );

  // Constructors
  CPPUNIT_TEST( testDefaultConstructor );
  CPPUNIT_TEST( testBuildFrom3Points );
  CPPUNIT_TEST( testBuildFromArc );
  CPPUNIT_TEST( testCopyConstructor );

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
 * @brief Tests qgar::GenQgarArc::GenQgarArc(QGEcolor, int, QGEoutline).
 *
 * Performed Checks:
 * - Ensure that the color, thickness and outline are correctly
 *   initialized.
 * - Ensure that the geometrical Structure is equal
 *   to a qgar::GenArc instance built from its default constructor.
 */
  void testDefaultConstructor();

/**
 * @brief Tests qgar::GenQgarArc::GenQgarArc(const GenQgarArc&).
 *
 * Performed Checks:
 * - Ensure that color, thickness and outline of the created object
 *   are equal to those of the original one.
 * - Ensure that the geometrical structure of the created object is
 *   equal to the original one.
 */
  void testCopyConstructor();

/**
 * @brief Tests
 *   qgar::GenQgarArc::GenQgarArc(const GenArc, QGEcolor, int, QGEoutline).
 *
 * Performed Tests:
 * - Ensure that color, thickness and outline of the created object
 *   are correctly assigned.
 * - Ensure that the geometrical structure of the created object
 *   is equal to the geometrical structure of the arc given as argument.
 */
  void testBuildFromArc();

/**
 * @brief Tests
 *   qgar::GenQgarArc::GenQgarArc(const GenPoint&, const GenPoint&, const GenPoint&, QGEcolor, int, QGEoutline).
 *
 * Performed Tests:
 * - Ensure that color, thickness and outline of the created object
 *   are correctly assigned.
 * - Ensure that the geometrical structure is equal to a qgar::GenArc
 *   instance built from the same three points.
 */
  void testBuildFrom3Points();

//@}


/** @name Copy */
//        ====
//@{

/**
 * @brief Tests qgar::GenQgarArc::clone().
 *
 * Performed Checks:
 * - Ensure that color, thickness and outline of the created object
 *   are equal to those of the original one.
 * - Ensure that the geometrical structure of the created object is
 *   equal to the original one.
 */
  void testClone();

//@}


/** @name Access to geometrical features */
//        ==============================
//@{

/**
 * @brief Tests qgar::GenQgarArc::radius().
 *
 * Performed Checks:
 * - Ensure that the value of the radius is correct.
 */
  void testRadius();

/**
 * @brief Tests qgar::GenQgarArc::length().
 *
 * Performed Checks:
 * - Ensure that the value of the length is correct.
 */
  void testLength();

/**
 * @brief Tests
 *   qgar::GenQgarArc::sourceAngle(),
 *   qgar::GenQgarArc::sourceAngleDegrees(),
 *   qgar::GenQgarArc::targetAngle(),
 *   qgar::GenQgarArc::targetAngleDegrees(),
 *   qgar::GenQgarArc::angle(),
 *   and qgar::GenQgarArc::angleDegrees().
 *
 * Performed Tests:
 * - Ensure that source angle, target angle, and arc angle are
 *   correctly computed.
 */
  void testAngles();

//@}


/** @name Center */
//        ======
//@{

/**
 * @brief Tests
 *   qgar::GenQgarArc::accessCenter,
 *   qgar::GenQgarArc::center,
 *   qgar::GenQgarArc::xCenter,
 *   qgar::GenQgarArc::yCenter,
 *   qgar::GenQgarArc::setXCenter,
 *   qgar::GenQgarArc::setYCenter,
 *   qgar::GenQgarArc::setCenter(T,T),
 *   and qgar::GenQgarArc::setCenter(const GenPoint<T>&).
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
 * @brief Tests qgar::GenQgarArc::operator=(const GenQgarArc&).
 *
 * Performed Checks:
 * - Ensure that color, thickness and outline of the created object
 *   are equal to those of rhs.
 * - Ensure that the geometrical structure of the created object is
 *   equal to the geometrical structure of rhs.
 * - Check that the function returns a valid reference on the left
 *   hand side of the assignment.
 */
  void testAssignment();

/**
 * @brief Tests
 *   qgar::GenQgarArc::operator==(const GenQgarArc&),
 *   qgar::GenQgarArc::eq(const GenQgarArc&),
 *   qgar::GenQgarArc::equal(const GenQgarArc&),
 *   qgar::GenQgarArc::operator!=(const GenQgarArc&),
 *   qgar::GenQgarArc::notEq(const GenQgarArc&).
 *   and
 *   qgar::GenQgarArc::notEqual(const GenQgarArc&).
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
 * @brief Tests qgar::GenQgarArc::translate.
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
 * @brief Tests qgar::GenQgarArc::read(std::istream&),
 *   and qgar::GenQgarArc::write(std::ostream&).
 *
 * Performed Tests:
 * - Serialize and deserialize a Qgar arc, then compare it to the
 *   original.
 */
  void testSerializeDeserialize();

//@}


// -------------------------------------------------------------------

}; // class GenQgarArcTest


#endif /* __GENQGARARCTEST_H_INCLUDED__ */
