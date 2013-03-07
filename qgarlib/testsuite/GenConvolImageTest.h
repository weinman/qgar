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


#ifndef __GENCONVOLIMAGETEST_H_INCLUDED__
#define __GENCONVOLIMAGETEST_H_INCLUDED__


/**
 * @file     GenConvolImageTest.h
 * @brief    Header file of class GenConvolImageTest
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     January 5, 2004  16:05
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete.
/* $Id: GenConvolImageTest.h,v 1.2 2005/01/28 15:56:45 masini Exp $ */



// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>



/**
 * @class GenConvolImageTest GenConvolImageTest.h
 * @brief Test class for class GenConvolImage.
 * 
 * Untested function members:
 * - None
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   January 5, 2004  16:05
 * @since  Qgar 2.1.1
 */
class GenConvolImageTest : public CppUnit::TestFixture
{
// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( GenConvolImageTest );
  CPPUNIT_TEST( test1DConvolConstructor );
  CPPUNIT_TEST( test2DConvolConstructor );
  CPPUNIT_TEST( testCopyConstructor );
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
 * @brief Tests GenConvolImage(GenImage&, Gen1dMask&, QGEaxis)
 *
 * Performed Checks:
 * - Ensure that the convolution is correctly performed for the inner
 *   values ( from (mask_size/2, mask_size/2) to (width - mask_size/2,
 *   height - mask_size/2) ).
 */
  void test1DConvolConstructor();

/**
 * @brief Tests GenConvolImage(GenImage&, Gen2dMask&)
 *
 * Performed Checks:
 * - Ensure that the convolution is correctly performed for the inner
 *   values ( from (mask_size/2, mask_size/2) to (width - mask_size/2,
 *   height - mask_size/2) ).
 */
  void test2DConvolConstructor();

/**
 * @brief Tests GenConvolImage(const GenConvolImage&)
 *
 * Performed Checks:
 * - Ensure that width and height are correctly assigned.
 * - Ensure that the pixmap is correctly duplicated.
 */
  void testCopyConstructor();


//@}

// -------------------------------------------------------------------
}; // class GenConvolImageTest


#endif /* __GENCONVOLIMAGETEST_H_INCLUDED__ */
