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


#ifndef __GENIMAGETEST_H_INCLUDED__
#define __GENIMAGETEST_H_INCLUDED__


/**
 * @file     GenImageTest.h
 * @brief    Header file of class GenImageTest
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     November 4, 2003  10:15
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete.
/* $Id: GenImageTest.h,v 1.2 2005/01/28 15:56:45 masini Exp $ */



// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>



/**
 * @class GenImageTest GenImageTest.h
 * @brief Test class for class GenImageTest.
 * 
 * Untested function members:
 * - GenImage(AbstractPbmPlusFile&)
 * - width()
 * - height()
 * - bytesPerPixel()
 * - pPixMap()
 * - save()
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 4, 2003  10:15
 * @since  Qgar 2.1.1
 */
class GenImageTest : public CppUnit::TestFixture
{
// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( GenImageTest );
  CPPUNIT_TEST( testDefaultConstructor );
  CPPUNIT_TEST( testBuildFromSize );
  CPPUNIT_TEST( testBuildFromPixmap );
  CPPUNIT_TEST( testCopyConstructor );
  CPPUNIT_TEST( testBuildFromDifferentPolicies );
  CPPUNIT_TEST( testBuildFromConvertedImage );
  CPPUNIT_TEST( testBuildFromBox );
  CPPUNIT_TEST( testBuildFromBoxCoords );
  CPPUNIT_TEST( testRow );
  CPPUNIT_TEST( testColumn );
  CPPUNIT_TEST( testPRow );
  CPPUNIT_TEST( testPColumn );
  CPPUNIT_TEST( testSetPixel );
  CPPUNIT_TEST( testSetRow );
  CPPUNIT_TEST( testSetColumn );
  CPPUNIT_TEST( testDrawSegment );
  CPPUNIT_TEST( testShallowCopy );
  CPPUNIT_TEST( testAssignment );
  CPPUNIT_TEST( testAssignFromImgWithOtherPolicies );
  CPPUNIT_TEST( testOpPlus );
  CPPUNIT_TEST( testOpPlusEqual );
  CPPUNIT_TEST( testOpMinus );
  CPPUNIT_TEST( testOpMinusEqual );
  CPPUNIT_TEST( testOpMul );
  CPPUNIT_TEST( testOpMulEqual );
  CPPUNIT_TEST( testPlus );
  CPPUNIT_TEST( testPlusEqual );
  CPPUNIT_TEST( testMinus );
  CPPUNIT_TEST( testMinusEqual );
  CPPUNIT_TEST( testTimes );
  CPPUNIT_TEST( testTimesEqual );
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
 * @brief Tests GenImageTest()
 *
 * Performed Checks:
 * - Ensure that width and height are initialized to 0.
 * - Ensure that bytePerPixel equals the size of the stored type.
 * - Ensure that the pointer to the pixmap is initialized to 0.
 */
  void testDefaultConstructor();

/**
 * @brief Tests BuildFromSize()
 *
 * Performed Tests:
 * - Ensure that width and height are correctly assigned.
 * - Ensure that bytesPerPixel equals the size of the stored type.
 */
  void testBuildFromSize();

/**
 * @brief Tests buildFromPixmap()
 *
 * Performed Tests:
 * - Ensure that width and height are correctly assigned.
 * - Ensure that bytesPerPixel equals the size of the stored type.
 * - Ensure that pixmap is correctly copied.
 */
  void testBuildFromPixmap();

/**
 * @brief Tests GenImageTest(const GenImageTest&)
 *
 * Performed Checks:
 * - Ensure that width and height are correctly copied.
 * - Ensure that bytesPerPixel is correctly copied.
 * - Ensure that pixmap is correctly duplicated.
 */
  void testCopyConstructor();

/**
 * @brief testBuildFromDifferentPolicies
 *
 * Performed Checks:
 * - Ensure that width and height are correctly duplicated.
 * - Ensure that bytesPerPixel is correctly copied.
 * - Ensure that pixmap is correctly duplicated.
 */
  void testBuildFromDifferentPolicies();

/**
 * @brief Tests buildFromConvertedImage()
 *
 * Performed Tests:
 * - Ensure that width and height are correctly duplicated.
 * - Ensure that bytesPerPixel is correctly assigned.
 * - Ensure that pixmap is correctly duplicated.
 */
  void testBuildFromConvertedImage();

/**
 * @brief Tests buildFromBox()
 *
 * Performed Tests:
 * - Ensure that width and height are correctly copied.
 * - Ensure that bytes by pixel is correctly assigned.
 * - Ensure that pixmap part is correctly duplicated.
 */
  void testBuildFromBox();

/**
 * @brief Tests buildFromBoxCoords()
 *
 * Performed Tests:
 * - Ensure that width and height are correctly copied.
 * - Ensure that bytes by pixel is correctly assigned.
 * - Ensure that pixmap part is correctly duplicated.
 */
  void testBuildFromBoxCoords();

/**
 * @brief Tests row()
 *
 * Performed Tests:
 * - Ensure that each pixel of the retrieved row matches the original
 *   one.
 */
  void testRow();

/**
 * @brief Tests Column()
 *
 * Performed Tests:
 * - Ensure that each pixel of the retrieved column matches the original
 *   one.
 */
  void testColumn();

/**
 * @brief Tests pRow()
 *
 * Performed Tests:
 * - Ensure that each pixel of the row pointed by the retrieved
 *   pointer is equal to the original one.
 */
  void testPRow();

/**
 * @brief Tests PColumn()
 *
 * Performed Tests:
 * - Ensure that each pixel of the column pointed by the retrieved
 *   pointer is equal to the original one.
 */
  void testPColumn();

/**
 * @brief Tests setPixel()
 *
 * Performed Tests:
 * - Ensure that pixel is correctly assigned.
 */
  void testSetPixel();

/**
 * @brief Tests setRow()
 *
 * Performed Tests:
 * - Ensure that row is correctly assigned.
 */
  void testSetRow();

/**
 * @brief Tests setColumn()
 *
 * Performed Tests:
 * - Ensure that column is correctly assigned.
 */
  void testSetColumn();

/**
 * @brief Tests drawSegment()
 *
 * Performed Tests:
 * - 
 */
  void testDrawSegment();

/**
 * @brief Tests shallowCopy()
 *
 * @warning No test is performed yet for this member.
 */
  void testShallowCopy();

/**
 * @brief Tests operator=(const GenImageTest&)
 *
 * Performed Checks:
 * - Ensure that width and height are correctly copied.
 * - Ensure that bytes per pixel is correclty initialized.
 * - Ensure that the rhs pixamp is correctly duplicated.
 * - Ensure that the function member returns a reference on the lhs.
 */
  void testAssignment();

/**
 * @brief Tests operator=(const GenImageTest<T, Other>&)
 *
 * Performed Checks:
 * - Ensure that width and height are correctly copied.
 * - Ensure that bytes per pixel is correclty initialized.
 * - Ensure that the rhs pixamp is correctly duplicated.
 * - Ensure that the member returns a reference on 'this'.
 */
  void testAssignFromImgWithOtherPolicies();

/**
 * @brief Tests operator+()
 *
 * Performed Tests:
 * - Ensure that each pixels of the result image is equal to the sum
 *   of the lhs and rhs pixel having the same position in the images.
 */
  void testOpPlus();

/**
 * @brief Tests operator+=()
 *
 * Performed Tests:
 * - Ensure that each pixels of the result image is equal to the sum
 *   of the lhs and rhs pixel having the same position in the images.
 * - Ensure that the function member returns a reference on the lhs.
 */
  void testOpPlusEqual();

/**
 * @brief Tests operator-()
 *
 * Performed Tests:
 * - Ensure that each pixels of the result image is equal to the
 *   difference of the lhs and rhs pixel having the same position in
 *   the images.
 */
  void testOpMinus();

/**
 * @brief Tests operator-=()
 *
 * Performed Tests:
 * - Ensure that each pixels of the result image is equal to the
 *   difference of the lhs and rhs pixel having the same position in
 *   the images.
 * - Ensure that the function member returns a reference on the lhs.
 */
  void testOpMinusEqual();

/**
 * @brief Tests operator*()
 *
 * Performed Tests:
 * - Ensure that each pixels of the result image is equal to the
 *   multiplication of the lhs and rhs pixel having the same position
 *   in the images.
 */
  void testOpMul();

/**
 * @brief Tests operator*=()
 *
 * Performed Tests:
 * - Ensure that each pixels of the result image is equal to the
 *   multiplication of the lhs and rhs pixel having the same position
 *   in the images.
 * - Ensure that the function member returns a reference on the lhs.
 */
  void testOpMulEqual();

/**
 * @brief Tests plus()
 *
 * Performed Tests:
 * - Ensure that each pixels of the result image is equal to the
 *   multiplication of the lhs and rhs pixel having the same position
 *   in the images.
 */
  void testPlus();

/**
 * @brief Tests plusEqual()
 *
 * Performed Tests:
 * - Ensure that each pixels of the result image is equal to the sum
 *   of the lhs and rhs pixel having the same position in the images.
 * - Ensure that the function member returns a reference on the lhs.
 */
  void testPlusEqual();

/**
 * @brief Tests minus()
 *
 * Performed Tests:
 * - Ensure that each pixels of the result image is equal to the
 *   difference of the lhs and rhs pixel having the same position in
 *   the images.
 */
  void testMinus();

/**
 * @brief Tests minusEqual()
 *
 * Performed Tests:
 * - Ensure that each pixels of the result image is equal to the
 *   difference of the lhs and rhs pixel having the same position in
 *   the images.
 * - Ensure that the function member returns a reference on the lhs.
 */
  void testMinusEqual();

/**
 * @brief Tests times()
 *
 * Performed Tests:
 * - Ensure that each pixels of the result image is equal to the
 *   multiplication of the lhs and rhs pixel having the same position
 *   in the images.
 */
  void testTimes();

/**
 * @brief Tests timesEqual()
 *
 * Performed Tests:
 * - Ensure that each pixels of the result image is equal to the
 *   multiplication of the lhs and rhs pixel having the same position
 *   in the images.
 * - Ensure that the function member returns a reference on the lhs.
 */
  void testTimesEqual();

//@}

// -------------------------------------------------------------------
}; // class GenImageTest


#endif /* __GENIMAGETEST_H_INCLUDED__ */
