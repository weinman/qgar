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


#ifndef __GENMASK2DTEST_H_INCLUDED__
#define __GENMASK2DTEST_H_INCLUDED__


/**
 * @file     GenMask2dTest.h
 * @brief    Header file of class GenMask2dTest
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     December 15, 2003  15:03
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete.
/* $Id: GenMask2dTest.h,v 1.2 2005/01/28 15:56:45 masini Exp $ */



// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>



/**
 * @class GenMask2dTest GenMask2dTest.h
 * @brief Test class for class GenMask2d.
 * 
 * Untested function members:
 * - width()
 * - height()
 * - coeff(int, int)
 * 
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   December 15, 2003  15:03
 * @since  Qgar 2.1.1
 */
class GenMask2dTest : public CppUnit::TestFixture
{
// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( GenMask2dTest );
  CPPUNIT_TEST( testDefaultConstructor );
  CPPUNIT_TEST( testCopyConstructor );
  CPPUNIT_TEST( testAssignment );
  CPPUNIT_TEST( testBuildWithDefaultValue );
  CPPUNIT_TEST( testBuildFromValArray );
  CPPUNIT_TEST( testPCoeffMap );
  CPPUNIT_TEST( testSetCoeff );
  CPPUNIT_TEST( testShallowCopy );
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
 * @brief Tests GenMask2d()
 *
 * Performed Checks:
 * - Ensure that width and height are correctly initialized to 0.
 * - Ensure that the pointer to the coefficient map is initialized to
 *   null.
 */
  void testDefaultConstructor();

/**
 * @brief Tests GenMask2d(const GenMask2d&)
 *
 * Performed Checks:
 * - Ensure that width and height are correctly assigned.
 * - Ensure that the coefficient map is correctly copied.
 */
  void testCopyConstructor();

/**
 * @brief Tests operator=(const GenMask2d&)
 *
 * Performed Checks:
 * - Ensure that width and height are correctly assigned.
 * - Ensure that the coefficient map is correctly copied.
 * - Ensure that the function returns a valid reference on 'this'.
 */
  void testAssignment();

/**
 * @brief Tests GenMask2d(unsigned, unsigned, T)
 *
 * Performed Tests:
 * - Ensure that width and height are correctly assigned.
 * - Ensure that all coeffs from the coefficient map are initialized
 *   to the passed default value.
 */
  void testBuildWithDefaultValue();

/**
 * @brief Tests GenMask2d(unsigned, unsigned, T *)
 *
 * Performed Tests:
 * - Ensure that width and height are correctly assigned.
 * - Ensure that the passed value array is copied.
 */
  void testBuildFromValArray();

/**
 * @brief Tests pCoeffMap()
 *
 * Performed Tests:
 * - Ensure that the array pointed by pCoeff() is equal to the one
 *   used to create a mask2d instance.
 */
  void testPCoeffMap();

/**
 * @brief Tests setCoeff()
 *
 * Performed Tests:
 * - Ensure that a coeff value is equal to one that is set.
 */
  void testSetCoeff();

/**
 * @brief Tests shallowCopy()
 *
 * Performed Tests:
 * - Ensure that the width of the duplicated instance is equal to the
 *   original one.
 * - Ensure that the mask values are correctly copied.
 */
  void testShallowCopy();
//@}

// -------------------------------------------------------------------
}; // class GenMask2dTest


#endif /* __GENMASK2DTEST_H_INCLUDED__ */
