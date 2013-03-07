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


#ifndef __LABELTEST_H_INCLUDED__
#define __LABELTEST_H_INCLUDED__


/**
 * @file     LabelTest.h
 * @brief    Header file of class LabelTest
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date     February 16, 2004  18:16
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete.
/* $Id: LabelTest.h,v 1.4 2005/01/28 15:56:46 masini Exp $ */



// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>
// QGAR
#include <qgarlib/QgarErrorAlgorithm.h>
#include <qgarlib/QgarErrorUser.h>



/**
 * @class LabelTest LabelTest.h
 * @brief Test class for class Label.
 * 
 * Untested function members:
 * - qgar::Label::int()
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   February 16, 2004  18:16
 * @since  Qgar 2.1.1
 */
class LabelTest : public CppUnit::TestFixture
{
// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( LabelTest );

  // No test
  CPPUNIT_TEST( testCastIntoInt );

  // Effective tests
  CPPUNIT_TEST( testDefaultConstructor );
  CPPUNIT_TEST( testBuildFromUShort );
  CPPUNIT_TEST( testCopyConstructor );
  CPPUNIT_TEST( testAssignment );
  CPPUNIT_TEST( testMaxLabel );
  CPPUNIT_TEST( testPrefixedPP );
  CPPUNIT_TEST_EXCEPTION( testPrefixedPPThrow, qgar::QgarErrorAlgorithm );
  CPPUNIT_TEST( testPostfixedPP );
  CPPUNIT_TEST_EXCEPTION( testPostfixedPPThrow, qgar::QgarErrorAlgorithm );
  CPPUNIT_TEST( testPrefixedMM );
  CPPUNIT_TEST_EXCEPTION( testPrefixedMMThrow, qgar::QgarErrorUser );
  CPPUNIT_TEST( testPostfixedMM );
  CPPUNIT_TEST_EXCEPTION( testPostfixedMMThrow, qgar::QgarErrorUser );
  CPPUNIT_TEST( testEqualityOp );
  CPPUNIT_TEST( testNequalityOp );
  CPPUNIT_TEST( testGreaterOp );
  CPPUNIT_TEST( testGreaterOrEqOp );
  CPPUNIT_TEST( testLessOp );
  CPPUNIT_TEST( testLessOrEqOp );
  CPPUNIT_TEST( testMin );
  CPPUNIT_TEST( testMax );

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

// -------------------------------------------------------------------

/**
 * @brief Tests int()
 *
 * Performed Tests:
 * - none : The function is assumed to be correct!
 */
  void testCastIntoInt();

// -------------------------------------------------------------------

/**
 * @brief Tests Label()
 *
 * Performed Checks:
 * - label value is initialized to zero
 */
  void testDefaultConstructor();

/**
 * @brief Tests Label(QGTuShort)
 *
 * Performed Tests:
 * - label is initialized to the given value
 */
  void testBuildFromUShort();

/**
 * @brief Tests Label(const Label&)
 *
 * Performed Checks:
 * - label is initialized to the same value as given label
 */
  void testCopyConstructor();

/**
 * @brief Tests operator=(const Label&)
 *
 * Performed Checks:
 * - label is assigned with the same value as the right hand side label
 */
  void testAssignment();

/**
 * @brief Tests QG_MAX_LABEL
 *
 * Performed Tests:
 * - the value of the qgar::Label::QG_MAX_LABEL static data member
 *   is equal to the maximum unsigned short
 */
  void testMaxLabel();

/**
 * @brief Tests operator++()
 *
 * Performed Tests:
 * - the value of the label is correctly incremented
 * - Ensure that the operator returns a valid reference on the current
 *   object
 */
  void testPrefixedPP();

/**
 * @brief Tests operator++()
 *
 * Performed Tests:
 * - throw a qgar::QgarErrorAlgorithm exception when label is at maximum value
 */
  void testPrefixedPPThrow();

/**
 * @brief Tests operator++(int)
 *
 * Performed Tests:
 * - the value of the label is correctly incremented
 */
  void testPostfixedPP();

/**
 * @brief Tests operator++(int)
 *
 * Performed Tests:
 * - throw a qgar::QgarErrorAlgorithm exception when label is at maximum value
 */
  void testPostfixedPPThrow();

/**
 * @brief Tests operator--()
 *
 * Performed Tests:
 * - the value of the label is correctly decremented
 * - Ensure that the operator returns a valid reference on the current
 *   object
 */
  void testPrefixedMM();

/**
 * @brief Tests operator--()
 *
 * Performed Tests:
 * - throw a qgar::QgarErrorUser exception when label value is 0
 */
  void testPrefixedMMThrow();

/**
 * @brief Tests operator--(int)
 *
 * Performed Tests:
 * - the value of the label is correctly decremented
 */
  void testPostfixedMM();

/**
 * @brief Tests operator--()
 *
 * Performed Tests:
 * - throw a qgar::QgarErrorUser exception when label value is 0
 */
  void testPostfixedMMThrow();

/**
 * @brief Tests equalityOp()
 *
 * Performed Tests:
 * - equality is correctly tested
 */
  void testEqualityOp();

/**
 * @brief Tests nequalityOp()
 *
 * Performed Tests:
 * - inequality is correctly tested
 */
  void testNequalityOp();

/**
 * @brief Tests greaterOp()
 *
 * Performed Tests:
 * - comparison is correctly performed
 */
  void testGreaterOp();

/**
 * @brief Tests greaterOrEqOp()
 *
 * Performed Tests:
 * - comparison is correctly performed
 */
  void testGreaterOrEqOp();

/**
 * @brief Tests lessOp()
 *
 * Performed Tests:
 * - comparison is correctly performed
 */
  void testLessOp();

/**
 * @brief Tests lessOrEqOp()
 *
 * Performed Tests:
 * - comparison is correctly performed
 */
  void testLessOrEqOp();

/**
 * @brief Tests min()
 *
 * Performed Tests:
 * - minimum between tow labels is correct
 */
  void testMin();

/**
 * @brief Tests max()
 *
 * Performed Tests:
 * - maximum between tow labels is correct
 */
  void testMax();

//@}

// -------------------------------------------------------------------
}; // class LabelTest


#endif /* __LABELTEST_H_INCLUDED__ */
