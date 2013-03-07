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


#ifndef __GENMASK1DTEST_H_INCLUDED__
#define __GENMASK1DTEST_H_INCLUDED__


/**
 * @file     GenMask1dTest.h
 * @brief    Header file of class GenMask1dTest
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     December 12, 2003  10:50
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete.
/* $Id: GenMask1dTest.h,v 1.3 2005/01/28 15:56:45 masini Exp $ */



// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>



/**
 * @class GenMask1dTest GenMask1dTest.h
 * @brief Test class for class GenMask1d.
 * 
 * Untested function members:
 * - coeff(int)
 * - width()
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   December 12, 2003  10:50
 * @since  Qgar 2.1.1
 */
class GenMask1dTest : public CppUnit::TestFixture
{
// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( GenMask1dTest );
  CPPUNIT_TEST( testDefaultConstructor );
  CPPUNIT_TEST( testCopyConstructor );
  CPPUNIT_TEST( testConversionConstructor );
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
 * @brief Tests GenMask1d()
 *
 * Performed Checks:
 * - Ensure that the mask size is initialized to 0.
 * - Ensure that the pointer to the mask values is null.
 */
  void testDefaultConstructor();

/**
 * @brief Tests GenMask1d(const GenMask1d&)
 *
 * Performed Checks:
 * - Ensure that the width of the duplicated instance is equal to the
 *   original one.
 * - Ensure that the mask values are correctly copied.
 */
  void testCopyConstructor();

/**
 * @brief Tests conversionConstructor()
 *
 * Performed Tests:
 * - 
 */
  void testConversionConstructor();

/**
 * @brief Tests operator=(const GenMask1d&)
 *
 * Performed Checks:
 * - Ensure that the width of the duplicated instance is equal to the
 *   original one.
 * - Ensure that the mask values are correctly copied.
 * - Ensure that the function returns a valid reference on 'this'.
 */
  void testAssignment();

/**
 * @brief Tests GenMask1d(unsigned int, T)
 *
 * Performed Tests:
 * - Ensure that the mask width is correctly initialized.
 * - Ensure that the mask values are all initialized to the passed
 *   default value.
 */
  void testBuildWithDefaultValue();

/**
 * @brief Tests GenMask1d(unsigned int, T *)
 *
 * Performed Tests:
 * - Ensure that the mask width is correctly initialized.
 * - Ensure that the mask values are equal to the one passed.
 */
  void testBuildFromValArray();

/**
 * @brief Tests testPCoeffMap()
 *
 * Performed Tests:
 * - Ensure that the array pointed by pCoeff() is equal to the one
 *   used to create a mask1d instance.
 */
  void testPCoeffMap();

/**
 * @brief Tests testSetCoeff()
 *
 * Performed Tests:
 * - Ensure that a coeff value is equal to one that is set.
 */
  void testSetCoeff();

/**
 * @brief Tests testShallowCopy()
 *
 * Performed Tests:
 * - Ensure that the width of the duplicated instance is equal to the
 *   original one.
 * - Ensure that the mask values are correctly copied.
 */
  void testShallowCopy();

//@}

// -------------------------------------------------------------------
}; // class GenMask1dTest


#endif /* __GENMASK1DTEST_H_INCLUDED__ */
