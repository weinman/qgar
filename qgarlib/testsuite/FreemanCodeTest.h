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


#ifndef __FREEMANCODETEST_H_INCLUDED__
#define __FREEMANCODETEST_H_INCLUDED__


/**
 * @file     FreemanCodeTest.h
 * @brief    Header file of class FreemanCodeTest
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date     February 3, 2004  18:14
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete.
/* $Id: FreemanCodeTest.h,v 1.2 2005/01/28 15:56:45 masini Exp $ */



// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>
// QGAR
#include <qgarlib/QgarErrorInvalidArg.h>



/**
 * @class FreemanCodeTest FreemanCodeTest.h
 * @brief Test class for class FreemanCode.
 * 
 * Untested function members:
 * - qgar::FreemanCode::direction()
 * - qgar::FreemanCode::testLength()
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   February 3, 2004  18:14
 * @since  Qgar 2.1.1
 */
class FreemanCodeTest : public CppUnit::TestFixture
{
// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( FreemanCodeTest );

  // NO TEST
  CPPUNIT_TEST( testDirection );
  CPPUNIT_TEST( testLength );

  // EFFECTIVE TESTS
  CPPUNIT_TEST( testDefaultConstructor );
  CPPUNIT_TEST( testBuildFromDirLength );
  CPPUNIT_TEST( testCopyConstructor );
  CPPUNIT_TEST( testAssignment );
  CPPUNIT_TEST( testSetDir );
  CPPUNIT_TEST( testSetLength );
  CPPUNIT_TEST( testSetDirLength );
  CPPUNIT_TEST( testToPoint );
  CPPUNIT_TEST( testToOppositePoint );

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


/** @name Not tested */
//        ==========
//@{

/**
 * @brief Tests qgar::FreemanCode::direction()
 */
  void testDirection();

/**
 * @brief Tests qgar::FreemanCode::length()
 */
  void testLength();
//@}


/** @name Effective test functions */
//        ========================
//@{

/**
 * @brief Tests qgar::FreemanCode::FreemanCode()
 *
 * Performed Checks:
 * - initial direction is qgar::QGE_DIRECTION_N
 * - initial length is 0
 */
  void testDefaultConstructor();

/**
 * @brief Tests qgar::FreemanCode::FreemanCode(QGEdirection, unsigned int)
 *
 * Performed Tests:
 * - direction and length are correctly initialized
 */
  void testBuildFromDirLength();

/**
 * @brief Tests qgar::FreemanCode::FreemanCode(const FreemanCode&)
 *
 * Performed Checks:
 * - direction and length are correctly initialized
 */
  void testCopyConstructor();

/**
 * @brief Tests qgar::FreemanCode::operator=(const FreemanCode&)
 *
 * Performed Checks:
 * - direction and length are correctly initialized
 */
  void testAssignment();

/**
 * @brief Tests qgar::FreemanCode::setDir(QGEdirection)
 *
 * Performed Tests:
 * - direction is correctly set
 * - length is unchanged
 */
  void testSetDir();

/**
 * @brief Tests qgar::FreemanCode::setLength(unsigned int)
 *
 * Performed Tests:
 * - length is correctly set
 * - direction is unchanged
 */
  void testSetLength();

/**
 * @brief Tests qgar::FreemanCode::setDirLength(QGEdirection, unsigned int)
 *
 * Performed Tests:
 * - direction and length are correctly set
 */
  void testSetDirLength();

/**
 * @brief Tests qgar::FreemanCode::toPoint(const GenPoint<int>&)
 *
 * Performed Tests:
 * - conversion into point is correct for all directions
 */
  void testToPoint();

/**
 * @brief Tests qgar::FreemanCode::toMirrorPoint(const GenPoint<int>&)
 *
 * Performed Tests:
 * - same same as testToPoint()
 */
  void testToOppositePoint();

//@}

// -------------------------------------------------------------------
}; // class FreemanCodeTest


#endif /* __FREEMANCODETEST_H_INCLUDED__ */
