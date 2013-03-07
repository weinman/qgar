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


#ifndef __ABSTRACTGENPRIMITIVETEST_H_INCLUDED__
#define __ABSTRACTGENPRIMITIVETEST_H_INCLUDED__


/**
 * @file     AbstractGenPrimitiveTest.h
 * @brief    Header file of class AbstractGenPrimitiveTest
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 25, 2003  11:53
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete.
/* $Id: AbstractGenPrimitiveTest.h,v 1.4 2005/07/13 16:29:34 masini Exp $ */



// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>



/**
 * @class AbstractGenPrimitiveTest AbstractGenPrimitiveTest.h
 * @brief Test class for class AbstractGenPrimitive.
 * 
 * Untested function members:
 * - source()
 * - target()
 * - xSource()
 * - ySource()
 * - xTarget()
 * - yTarget()
 * - ... and all pure virtual function members!
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 25, 2003  11:53
 * @since  Qgar 2.1.1
 */
class AbstractGenPrimitiveTest : public CppUnit::TestFixture
{
// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( AbstractGenPrimitiveTest );

  CPPUNIT_TEST( testDefaultConstructor );
  CPPUNIT_TEST( testCopyConstructor );
  CPPUNIT_TEST( testAssignment );
  CPPUNIT_TEST( testBuildFromTwoPoints );
  CPPUNIT_TEST( testBuildFrom4Coords );
  CPPUNIT_TEST( testDx );
  CPPUNIT_TEST( testDy );

  CPPUNIT_TEST( testSetSource );
  CPPUNIT_TEST( testSetTarget );
  CPPUNIT_TEST( testSetSourceTarget );
  CPPUNIT_TEST( testSetXSource );
  CPPUNIT_TEST( testSetXTarget );
  CPPUNIT_TEST( testSetYSource );
  CPPUNIT_TEST( testSetYTarget );
  CPPUNIT_TEST( testSetXYSource );
  CPPUNIT_TEST( testSetXYTarget );
  CPPUNIT_TEST( testSetXYSourceTarget );

  CPPUNIT_TEST( testFixSource );
  CPPUNIT_TEST( testFixTarget );
  CPPUNIT_TEST( testFixSourceTarget );
  CPPUNIT_TEST( testFixXSource );
  CPPUNIT_TEST( testFixXTarget );
  CPPUNIT_TEST( testFixYSource );
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


/** @name Test Functions */
//        ==============
//@{

/**
 * @brief Tests AbstractGenPrimitive()
 *
 * Performed Checks:
 * - Ensure that source and target are initialized to (0,0)
 */
  void testDefaultConstructor();

/**
 * @brief Tests AbstractGenPrimitive(const AbstractGenPrimitive&)
 *
 * Performed Checks:
 * - Ensure that source and target are correctly copied.
 */
  void testCopyConstructor();

/**
 * @brief Tests operator=(const AbstractGenPrimitiveTest&)
 *
 * Performed Checks:
 * - Ensure that source and target are correctly copied
 * - Ensure that the function returns a valid reference on 'this'.
 */
  void testAssignment();

/**
 * @brief Tests AbstractGenPrimitive(const GenPoint&, const GenPoint&)
 *
 * Performed Tests:
 * - Ensure that the source of the created primitive is equal to the
 *   first point.
 * - Ensure that the target of the created primitive is equal to the
 *   second point.
 */
  void testBuildFromTwoPoints();

/**
 * @brief Tests AbstractGenPrimitive(T, T, T, T)
 *
 * Performed Tests:
 * - Ensure that the source is equal to the point created from the two
 *   first parameters.
 * - Ensure that the target is equal to the point created from the two
 *   next parameters.
 */
  void testBuildFrom4Coords();

/**
 * @brief Tests testDx()
 *
 * Performed Tests:
 * - Ensure that dx() return the difference between the target
 *   x-coordinate and the source x-coordinate.
 */
  void testDx();

/**
 * @brief Tests testDy()
 *
 * Performed Tests:
 * - Ensure that dy() return the difference between the target
 *   y-coordinate and the source y-coordinate.
 */
  void testDy();

/**
 * @brief Tests testSetSource()
 *
 * Performed Tests:
 * - Ensure that the source point is correctly assigned.
 * - Ensure that no update function of the class implementing
 *   the abstract class is called.
 */
  void testSetSource();

/**
 * @brief Tests testSetTarget()
 *
 * Performed Tests:
 * - Ensure that the target point is correctly assigned.
 * - Ensure that no update function of the class implementing
 *   the abstract class is called.
 */
  void testSetTarget();

/**
 * @brief Tests testSetSourceTarget()
 *
 * Performed Tests:
 * - Ensure that the source point is correctly assigned.
 * - Ensure that the target point is correctly assigned.
 * - Ensure that no update function of the class implementing
 *   the abstract class is called.
 */
  void testSetSourceTarget();

/**
 * @brief Tests setXSource()
 *
 * Performed Tests:
 * - Ensure that the X coordinate of the source point is correctly assigned.
 * - Ensure that no update function of the class implementing
 *   the abstract class is called.
 */
  void testSetXSource();

/**
 * @brief Tests setXTarget()
 *
 * Performed Tests:
 * - Ensure that the X coordinate of the target point is correctly assigned.
 * - Ensure that no update function of the class implementing
 *   the abstract class is called.
 */
  void testSetXTarget();

/**
 * @brief Tests setYSource()
 *
 * Performed Tests:
 * - Ensure that the Y coordinate of the source point is correctly assigned.
 * - Ensure that no update function of the class implementing
 *   the abstract class is called.
 */
  void testSetYSource();

/**
 * @brief Tests setYTarget()
 *
 * Performed Tests:
 * Performed Tests:
 * - Ensure that the Y coordinate of the target point is correctly assigned.
 * - Ensure that no update function of the class implementing
 *   the abstract class is called.
 */
  void testSetYTarget();

/**
 * @brief Tests setXYSource(T, T)
 *
 * Performed Tests:
 * - Ensure that the X and Y coordinates of the source point
 *   are correctly assigned.
 * - Ensure that no update function of the class implementing
 *   the abstract class is called.
 */
  void testSetXYSource();

/**
 * @brief Tests setXYTarget(T, T)
 *
 * Performed Tests:
 * - Ensure that the X and Y coordinates of the target point
 *   are correctly assigned.
 * - Ensure that no update function of the class implementing
 *   the abstract class is called.
 */
  void testSetXYTarget();

/**
 * @brief Tests setXYSourceTarget(T, T, T, T)
 *
 * Performed Tests:
 * - Ensure that the X and Y coordinates of source and target points
 *   are correctly assigned.
 * - Ensure that no update function of the class implementing
 *   the abstract class is called.
 */
  void testSetXYSourceTarget();

/**
 * @brief Tests testFixSource()
 *
 * Performed Tests:
 * - Ensure that the source point is correctly assigned.
 * - Ensure that updateSource() of the class implementing the
 *   abstract class is called.
 */
  void testFixSource();

/**
 * @brief Tests testFixTarget()
 *
 * Performed Tests:
 * - Ensure that the target point is correctly assigned.
 * - Ensure that updateTarget() of the class implementing the
 *   abstract class is called.
 */
  void testFixTarget();

/**
 * @brief Tests testFixSourceTarget()
 *
 * Performed Tests:
 * - Ensure that the source point is correctly assigned.
 * - Ensure that the target point is correctly assigned.
 * - Ensure that updateSourceTarget() of the class implementing the
 *   abstract class is called.
 */
  void testFixSourceTarget();

/**
 * @brief Tests fixXSource()
 *
 * Performed Tests:
 * - Ensure that the X coordinate of the source point is correctly assigned.
 * - Ensure that function updateSource() of the class implementing the
 *   abstract class is called.
 */
  void testFixXSource();

/**
 * @brief Tests fixXTarget()
 *
 * Performed Tests:
 * - Ensure that the X coordinate of the target point is correctly assigned.
 * - Ensure that function updateTarget() of the class implementing the
 *   abstract class is called.
 */
  void testFixXTarget();

/**
 * @brief Tests fixYSource()
 *
 * Performed Tests:
 * - Ensure that the Y coordinate of the source point is correctly assigned.
 * - Ensure that function updateSource() of the class implementing the
 *   abstract class is called.
 */
  void testFixYSource();

/**
 * @brief Tests fixYTarget()
 *
 * Performed Tests:
 * Performed Tests:
 * - Ensure that the Y coordinate of the target point is correctly assigned.
 * - Ensure that function updateTarget() of the class implementing the
 *   abstract class is called.
 */
  void testFixYTarget();

/**
 * @brief Tests fixSource(T, T)
 *
 * Performed Tests:
 * - Ensure that the X and Y coordinates of the source point
 *   are correctly assigned.
 * - Ensure that function updateSource() of the class implementing
 *   the abstract class is called.
 */
  void testFixXYSource();

/**
 * @brief Tests fixTarget(T, T)
 *
 * Performed Tests:
 * - Ensure that the X and Y coordinates of the target point
 *   are correctly assigned.
 * - Ensure that function updateTarget() of the class implementing
 *   the abstract class is called.
 */
  void testFixXYTarget();

/**
 * @brief Tests fixSourceTarget(T, T, T, T)
 *
 * Performed Tests:
 * - Ensure that the X and Y coordinates of source and target points
 *   are correctly assigned.
 * - Ensure that function updateSourceTarget() of the class implementing
 *   the abstract class is called.
 */
  void testFixXYSourceTarget();

//@}

// -------------------------------------------------------------------
}; // class AbstractGenPrimitiveTest


#endif /* __ABSTRACTGENPRIMITIVETEST_H_INCLUDED__ */
