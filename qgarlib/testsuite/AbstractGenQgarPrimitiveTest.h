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


#ifndef __ABSTRACTGENQGARPRIMITIVETEST_H_INCLUDED__
#define __ABSTRACTGENQGARPRIMITIVETEST_H_INCLUDED__


/**
 * @file     AbstractGenQgarPrimitiveTest.h
 * @brief    Header file of class AbstractGenQgarPrimitiveTest
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 29, 2003  16:12
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete.
/* $Id: AbstractGenQgarPrimitiveTest.h,v 1.3 2005/07/13 16:29:34 masini Exp $ */



// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>



/**
 * @class AbstractGenQgarPrimitiveTest AbstractGenQgarPrimitiveTest.h
 * @brief Test class for class AbstractGenQgarPrimitiveTest.
 * 
 * Untested function members:
 * - color()
 * - thickness()
 * - outline()
 * - source()
 * - accessSource()
 * - target()
 * - accessTarget()
 * 
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 29, 2003  16:12
 * @since  Qgar 2.1.1
 */
class AbstractGenQgarPrimitiveTest : public CppUnit::TestFixture
{
// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( AbstractGenQgarPrimitiveTest );

  // Constructors
  CPPUNIT_TEST( testDefaultConstructor );
  CPPUNIT_TEST( testCopyConstructor );

  // Access to coordinates
  CPPUNIT_TEST( testCoordinatesCoherency );

  // Access to geometrical characteristics
  CPPUNIT_TEST( testDxDy );

  // Set attributes
  CPPUNIT_TEST( testSetThickness );
  CPPUNIT_TEST( testSetColor );
  CPPUNIT_TEST( testSetOutline );

  // Operators
  CPPUNIT_TEST( testAssignment );

  // Set source and/or target without update
  CPPUNIT_TEST( testSetSource );
  CPPUNIT_TEST( testSetTarget );
  CPPUNIT_TEST( testSetSourceTarget );
  CPPUNIT_TEST( testSetXSource );
  CPPUNIT_TEST( testSetYSource );
  CPPUNIT_TEST( testSetXTarget );
  CPPUNIT_TEST( testSetYTarget );
  CPPUNIT_TEST( testSetXYSource );
  CPPUNIT_TEST( testSetXYTarget );
  CPPUNIT_TEST( testSetXYSourceTarget );

  // Set source and/or target with update
  CPPUNIT_TEST( testFixTarget );
  CPPUNIT_TEST( testFixSourceTarget );
  CPPUNIT_TEST( testFixXSource );
  CPPUNIT_TEST( testFixYSource );
  CPPUNIT_TEST( testFixXTarget );
  CPPUNIT_TEST( testFixYTarget );
  CPPUNIT_TEST( testFixXYSource );
  CPPUNIT_TEST( testFixXYTarget );
  CPPUNIT_TEST( testFixXYSourceTarget );

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
 * @brief Tests AbstractGenQgarPrimitiveTest()
 *
 * Performed Checks:
 * - Ensure that the color is initialized to QGE_COLOR_BLACK.
 * - Ensure that the thickness is initialized to 1.
 * - Ensure that the outline is initialized to QGE_OUTLINE_SOLID.
 * - Ensure that source and target are initialized to (0,0).
 */
  void testDefaultConstructor();

/**
 * @brief Tests AbstractGenQgarPrimitiveTest(const AbstractGenQgarPrimitiveTest&)
 *
 * Performed Checks:
 * - Ensure that color, thickness and outline are correctly copied.
 */
  void testCopyConstructor();

//@}


/** @name Access to coordinates */
//        =====================
//@{

/**
 * @brief Tests coordinatesCoherency()
 *
 * Performed Tests:
 * - Ensure that source() equals GenPoint<T>(xSource(), ySource()).
 * - Ensure that target() equals GenPoint<T>(xTarget(), yTarget()).
 * - Ensure that source() equals accessSource().
 * - Ensure that target() equals accessTarget().
 */
  void testCoordinatesCoherency();

//@}


/** @name Access to geometrical characteristics */
//        =====================================
//@{

/**
 * @brief Tests dx() and dy().
 */
  void testDxDy();

//@}


/** @name Set attributes */
//        ==============
//@{

/**
 * @brief Tests setThickness()
 *
 * Performed Tests:
 * - Set the thickness of the primitive and ensure that thickness()
 *   returns the right value.
 */
  void testSetThickness();

/**
 * @brief Tests setColor()
 *
 * Performed Tests:
 * - Set the color of the primitive and ensure that color() returns
 *   the right value.
 */
  void testSetColor();

/**
 * @brief Tests setOutline()
 *
 * Performed Tests:
 * - Set the outline of the primitive and ensure that outline()
 *   returns the right value.
 */
  void testSetOutline();

//@}


/** @name Operators */
//        =========
//@{

/**
 * @brief Tests assignment()
 *
 * Performed Tests:
 * - Ensure that color, thickness and outline of the lhs are equal to
 *   those of the rhs after assignment.
 * - Ensure that the function returns a valid reference on this.
 */
  void testAssignment();

//@}


/** @name Set source and/or target without update */
//        =======================================
//@{

/**
 * @brief Tests testSetSource()
 *
 * Performed Tests:
 * - Ensure that the source point is correctly assigned.
 */
  void testSetSource();

/**
 * @brief Tests testSetTarget()
 *
 * Performed Tests:
 * - Ensure that the target point is correctly assigned.
 */
  void testSetTarget();

/**
 * @brief Tests testSetSourceTarget()
 *
 * Performed Tests:
 * - Ensure that the source point is correctly assigned.
 * - Ensure that the target point is correctly assigned.
 */
  void testSetSourceTarget();

/**
 * @brief Tests setXSource()
 *
 * Performed Tests:
 * - Ensure that the X coordinate of the source point is correctly assigned.
 */
  void testSetXSource();

/**
 * @brief Tests setXTarget()
 *
 * Performed Tests:
 * - Ensure that the X coordinate of the target point is correctly assigned.
 */
  void testSetXTarget();

/**
 * @brief Tests setYSource()
 *
 * Performed Tests:
 * - Ensure that the Y coordinate of the source point is correctly assigned.
 */
  void testSetYSource();

/**
 * @brief Tests setYTarget()
 *
 * Performed Tests:
 * Performed Tests:
 * - Ensure that the Y coordinate of the target point is correctly assigned.
 */
  void testSetYTarget();

/**
 * @brief Tests setXYSource(T, T)
 *
 * Performed Tests:
 * - Ensure that the X and Y coordinates of the source point
 *   are correctly assigned.
 */
  void testSetXYSource();

/**
 * @brief Tests setXYTarget(T, T)
 *
 * Performed Tests:
 * - Ensure that the X and Y coordinates of the target point
 *   are correctly assigned.
 */
  void testSetXYTarget();

/**
 * @brief Tests setXYSourceTarget(T, T, T, T)
 *
 * Performed Tests:
 * - Ensure that the X and Y coordinates of source and target points
 *   are correctly assigned.
 */
  void testSetXYSourceTarget();

//@}


/** @name Set source and/or target with update */
//        ====================================
//@{

/**
 * @brief Tests testFixSource()
 *
 * Performed Tests:
 * - Ensure that the source point is correctly assigned.
 */
  void testFixSource();

/**
 * @brief Tests testFixTarget()
 *
 * Performed Tests:
 * - Ensure that the target point is correctly assigned.
 */
  void testFixTarget();

/**
 * @brief Tests testFixSourceTarget()
 *
 * Performed Tests:
 * - Ensure that the source point is correctly assigned.
 * - Ensure that the target point is correctly assigned.
 */
  void testFixSourceTarget();

/**
 * @brief Tests fixXSource()
 *
 * Performed Tests:
 * - Ensure that the X coordinate of the source point is correctly assigned.
 */
  void testFixXSource();

/**
 * @brief Tests fixXTarget()
 *
 * Performed Tests:
 * - Ensure that the X coordinate of the target point is correctly assigned.
 */
  void testFixXTarget();

/**
 * @brief Tests fixYSource()
 *
 * Performed Tests:
 * - Ensure that the Y coordinate of the source point is correctly assigned.
 */
  void testFixYSource();

/**
 * @brief Tests fixYTarget()
 *
 * Performed Tests:
 * Performed Tests:
 * - Ensure that the Y coordinate of the target point is correctly assigned.
 */
  void testFixYTarget();

/**
 * @brief Tests fixSource(T, T)
 *
 * Performed Tests:
 * - Ensure that the X and Y coordinates of the source point
 *   are correctly assigned.
 */
  void testFixXYSource();

/**
 * @brief Tests fixTarget(T, T)
 *
 * Performed Tests:
 * - Ensure that the X and Y coordinates of the target point
 *   are correctly assigned.
 */
  void testFixXYTarget();

/**
 * @brief Tests fixSourceTarget(T, T, T, T)
 *
 * Performed Tests:
 * - Ensure that the X and Y coordinates of source and target points
 *   are correctly assigned.
 */
  void testFixXYSourceTarget();

//@}


// -------------------------------------------------------------------

}; // class AbstractGenQgarPrimitiveTest


#endif /* __ABSTRACTGENQGARPRIMITIVETEST_H_INCLUDED__ */
