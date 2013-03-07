/*---------------------------------------------------------------------*
 | Library QgarLib, graphics analysis and recognition                  |
 | Copyright (C) 2004  Qgar Project, LORIA                             |
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


#ifndef __GLOBALFUNCTIONSTEST_H_INCLUDED__
#define __GLOBALFUNCTIONSTEST_H_INCLUDED__


/**
 * @file     GlobalFunctionsTest.h
 * @brief    Header file of class GlobalFunctionsTest
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     May 17, 2004  16:06
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete.
/* $Id: GlobalFunctionsTest.h,v 1.4 2005/10/14 17:06:36 masini Exp $ */



// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>



/**
 * @class GlobalFunctionsTest GlobalFunctionsTest.h
 * @brief Test class for global functions.
 * 
 * Untested global function:
 * - qgar::qgReadObjName
 * - qgar::qgReadObjData
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek & Gérald Masini</a>
 * @date   May 17, 2004  16:06
 * @since  Qgar 2.1.1
 */
class GlobalFunctionsTest

  : public CppUnit::TestFixture

{
// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( GlobalFunctionsTest );

  // Arrays
  CPPUNIT_TEST( testQgFill );
  CPPUNIT_TEST( testQgForEach );
  CPPUNIT_TEST( testQgMinElement );
  CPPUNIT_TEST( testQgMaxElement );

  // Angles
  CPPUNIT_TEST( testQgRadiansToDegrees );
  CPPUNIT_TEST( testQgDegreesToRadians );
  CPPUNIT_TEST( testQgDirection );
  CPPUNIT_TEST( testQgOpposite );

  // (In)equality tests
  CPPUNIT_TEST( testQgEq0 );
  CPPUNIT_TEST( testQgNotEq0 );
  CPPUNIT_TEST( testQgNeg );

  // Error function
  CPPUNIT_TEST( testQgErf );

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


  /** @name Arrays */
  //        ======
  //@{

  /**
   * @brief Tests qgar::qgFill().
   *
   * Performed Tests:
   * - Tests overloaded template versions for int float and double.
   */
  void testQgFill();

  /**
   * @brief Tests qgar::qgForEach().
   *
   * Performed Tests:
   * - Ensure that the function is correctly called on an example.
   */
  void testQgForEach();

  /**
   * @brief Tests qgar::qgMinElement().
   *
   * Performed Tests:
   * - 1 test using an int array.
   */
  void testQgMinElement();

  /**
   * @brief Tests qgar::qgMaxElement().
   *
   * Performed Tests:
   * - 1 test using an int array.
   */
  void testQgMaxElement();

  //@}


  /** @name Angles */
  //        ======
  //@{

  /**
   * @brief Tests qgar::qgRadiansToDegrees().
   *
   * Performed Tests:
   * - Ensure that the conversion is correct.
   */
  void testQgRadiansToDegrees();

  /**
   * @brief Tests qgar::qgDegreesToRadians()
   *
   * Performed Tests:
   * - Ensure that the conversion is correct.
   */
  void testQgDegreesToRadians();

  /**
   * @brief Tests qgar::qgDirection()
   *
   * Performed Tests:
   * - Ensure that the computed direction is correct for each 8
   *   directions.
   */
  void testQgDirection();

  /**
   * @brief Tests qgar::qgOpposite()
   *
   * Performed Tests:
   * - Ensure that the computed opposite direction is correct for each 8
   *   directions.
   */
  void testQgOpposite();

  //@}


  /** @name (In)equality tests */
  //        ==================
  //@{

  /**
   * @brief Tests qgar::qgEq0f()
   *
   * Performed Tests:
   * - 1 test using a simple example.
   */
  void testQgEq0();

  /**
   * @brief Tests qgar::qgNeq0f()
   *
   * Performed Tests:
   * - 1 test using a simple example.
   */
  void testQgNotEq0();

  /**
   * @brief Tests qgar::qgNeg()
   *
   * Performed Tests:
   * - 1 test using a simple example
   */
  void testQgNeg();

  //@}


  /** @name Error function */
  //        ==============
  //@{

  /**
   * @brief Tests qgar::qgErf and qgar::qgErfc.
   *
   * Performed Tests:
   * - Check that both functions deliver same results as C functions
   *   erf(x) and erfc(x), using arrays GlobalFunctionsTest::_erfTab
   *   and  GlobalFunctionsTest::_erfcTab
   */
  void testQgErf();

  //@}

// -------------------------------------------------------------------
// P R O T E C T E D   M E M B E R S
// -------------------------------------------------------------------
protected:


  /// An array of int used for testing.
  static int _intTab1[10];

  /// An array of int used for testing.
  static int _intTab2[10];
  
  /// Consecutive pairs (x, erf(x)), where erf(x) is the value
  /// delivered by the same-named C function from cmath.
  static double _erfTab[];

  /// Consecutive pairs (x, erfC(x)), where erfC(x) is the value
  /// delivered by the same-named C function from cmath.
  static double _erfcTab[];


// -------------------------------------------------------------------

}; // class GlobalFunctionsTest


#endif /* __GLOBALFUNCTIONSTEST_H_INCLUDED__ */
