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


#ifndef __HISTOGRAMTEST_H_INCLUDED__
#define __HISTOGRAMTEST_H_INCLUDED__


/**
 * @file     HistogramTest.h
 * @brief    Header file of class HistogramTest
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date     December 5, 2003  17:25
 * @since    Qgar 2.1
 */


// For RCS/CVS use: Do not delete.
/* $Id: HistogramTest.h,v 1.5 2005/07/13 16:29:34 masini Exp $ */



// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>
// QGAR
#include <qgarlib/GenImage.h>
#include <qgarlib/QgarErrorDomain.h>



/**
 * @class HistogramTest HistogramTest.h
 * @brief Test class for class Histogram.
 * 
 * Untested function members:
 * - 
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 5, 2003  17:25
 * @since  Qgar 2.1
 */
class HistogramTest : public CppUnit::TestFixture
{
// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( HistogramTest );

  CPPUNIT_TEST( testDefaultConstructor );
  CPPUNIT_TEST_EXCEPTION( testRandomAccessOpThrowLowerBnd, qgar::QgarErrorDomain );
  CPPUNIT_TEST_EXCEPTION( testRandomAccessOpThrowUpperBnd, qgar::QgarErrorDomain );
  CPPUNIT_TEST( testBuildFromBndSampRate );
  CPPUNIT_TEST_EXCEPTION( testBuildFromBndSampRateThrowBnds, qgar::QgarErrorDomain );
  CPPUNIT_TEST_EXCEPTION( testBuildFromBndSampRateThrowRate, qgar::QgarErrorDomain );
  CPPUNIT_TEST( testBuildFromGreylevelImg );
  CPPUNIT_TEST_EXCEPTION( testBuildFromGreylevelImgThrowBnds, qgar::QgarErrorDomain );
  CPPUNIT_TEST_EXCEPTION( testBuildFromGreylevelImgThrowRate, qgar::QgarErrorDomain );
  CPPUNIT_TEST( testCopyConstructor );
  CPPUNIT_TEST( testAssignment );
  CPPUNIT_TEST( testLowerBnd );
  CPPUNIT_TEST( testUpperBnd );
  CPPUNIT_TEST( testSamplingRate );
  CPPUNIT_TEST( testPlus );
  CPPUNIT_TEST( testMinus );
  CPPUNIT_TEST( testMaxSample );
  CPPUNIT_TEST( testMaxSampleStartingFromBnd );
  CPPUNIT_TEST( testMinSample );
  CPPUNIT_TEST( testMinSampleStartingFromBnd );
  CPPUNIT_TEST( testPartialSum );
  CPPUNIT_TEST( testSmooth );
  CPPUNIT_TEST_EXCEPTION( testSmoothThrowEqual, qgar::QgarErrorDomain );
  CPPUNIT_TEST_EXCEPTION( testSmoothThrowTooLarge, qgar::QgarErrorDomain );
  CPPUNIT_TEST_EXCEPTION( testSmoothThrowZero, qgar::QgarErrorDomain );

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
 * @brief Tests qgar::Histogram::Histogram()
 *
 * Performed Checks:
 * - sampling rate initialized to 1
 * - lower bound initialized to 0
 * - upper bound initialized to 0
 */
  void testDefaultConstructor();

/**
 * @brief Tests qgar::Histogram::operator[](int)
 *
 * Performed Tests:
 * - access to a sample < lower bound throws a qgar::QgarErrorDomain exception
 */
  void testRandomAccessOpThrowLowerBnd();

/**
 * @brief Tests qgar::Histogram::operator[](int)
 *
 * Performed Tests:
 * - access to a sample > upper bound throws a qgar::QgarErrorDomain exception
 */
  void testRandomAccessOpThrowUpperBnd();

/**
 * @brief Tests qgar::Histogram::Histogram(int, int, unsigned int)
 *
 * Performed Tests:
 * - bounds are correctly initialized
 * - sampling rate is correctly initialized
 * - all cells are initialized to 0
 */
  void testBuildFromBndSampRate();

/**
 * @brief Tests qgar::Histogram::Histogram(int, int, unsigned int)
 *
 * Performed Tests:
 * - creation of a histogram with lower boud > upper bound
 *   throws a qgar::QgarErrorDomain exception
 */
  void testBuildFromBndSampRateThrowBnds();

/**
 * @brief Tests qgar::Histogram::Histogram(int, int, unsigned int)
 *
 * Performed Tests:
 * - creation of a histogram with a sampling rate == 0
 *   throws a qgar::QgarErrorDomain exception
 */
  void testBuildFromBndSampRateThrowRate();

/**
 * @brief Tests
 * qgar::Histogram::Histogram(const GreyLevelImage&, int, int,unsigned int)
 *
 * Performed Tests:
 * - histograms constructed from the test image,
 *   with sampling rates set to 1, 2, 3, and 256,
 *   are correctly initialized
 */
  void testBuildFromGreylevelImg();

/**
 * @brief Tests
 * qgar::Histogram::Histogram(const GreyLevelImage&, int, int,unsigned int)
 *
 * Performed Tests:
 * - creation of a histogram from an image and a lower boud > upper bound
 *   throws a qgar::QgarErrorDomain exception
 */
  void testBuildFromGreylevelImgThrowBnds();

/**
 * @brief
 * qgar::Histogram::Histogram(const GreyLevelImage&, int, int,unsigned int)
 *
 * Performed Tests:
 * - creation of a histogram from an image and a sampling rate == 0
 *   throws a qgar::QgarErrorDomain exception
 */
  void testBuildFromGreylevelImgThrowRate();

/**
 * @brief Tests qgar::Histogram::Histogram(const Histogram&)
 *
 * Performed Checks:
 * - sampling rate is correctly copied
 * - bounds are correctly copied
 * - frequencies are correctly copied
 */
  void testCopyConstructor();

/**
 * @brief Tests qgar::Histogram::operator=(const Histogram&)
 *
 * Performed Checks:
 * - sampling rate is correctly copied
 * - bounds are correctly copied
 * - frequencies are correctly copied
 */
  void testAssignment();

/**
 * @brief Tests qgar::Histogram::lowerBnd()
 *
 * @warning This function is not tested 
 */
  void testLowerBnd();

/**
 * @brief Tests qgar::Histogram::upperBnd()
 *
 * @warning This function is not tested 
 */
  void testUpperBnd();

/**
 * @brief Tests qgar::Histogram::samplingRate()
 *
 * @warning This function is not tested 
 */
  void testSamplingRate();

/**
 * @brief Tests qgar::Histogram::plus(int, unsigned int)
 *
 * Performed Tests:
 * - frequencies are correctly incremented
 *   in case of sampling rates equal to 1 and 5
 */
  void testPlus();

/**
 * @brief Tests qgar::Histogram::minus(int, unsigned int)
 *
 * Performed Tests:
 * - frequencies are correctly decremented
 *   in case of sampling rates equal to 1 and 5
 */
  void testMinus();

/**
 * @brief Tests qgar::Histogram::maxSample()
 *
 * Performed Tests:
 * - the lower maximum sample can be found
 */
  void testMaxSample();

/**
 * @brief Tests qgar::Histogram::maxSample(int)
 *
 * Performed Tests:
 * - the lower maximum sample can be found
 *   when starting from a given lower bound
 */
  void testMaxSampleStartingFromBnd();

/**
 * @brief Tests qgar::Histogram::minSample()
 *
 * Performed Tests:
 * - the lower minimum sample can be found
 */
  void testMinSample();

/**
 * @brief Tests qgar::Histogram::minSample(int)
 *
 * Performed Tests:
 * - the lower minimum sample can be found
 *   when starting from a given lower bound
 */
  void testMinSampleStartingFromBnd();

/**
 * @brief Tests qgar::Histogram::partialSum()
 *
 * Performed Tests:
 * - Accumulated histogram is correctly computed from histograms
 *   with sampling rates = 1 and 10
 */
  void testPartialSum();

/**
 * @brief Tests qgar::Histogram::smooth(unsigned int)
 *
 * Performed Tests:
 * - smoothing a flat histogram has no effect
 * - smoothing using a window of size = 1 has no effect
 * - smoothing using a window of size = 2 provides
 *   a correct result on a small histogram of 11 samples
 */
  void testSmooth();

/**
 * @brief Tests qgar::Histogram::smooth(unsigned int)
 *
 * Performed Tests:
 * - smoothing using a window of the same size as the histogram
 *   throws a qgar::QgarErrorDomain exception
 */
  void testSmoothThrowEqual();

/**
 * @brief Tests qgar::Histogram::smooth(unsigned int)
 *
 * Performed Tests:
 * - smoothing using a window larger than the size of the histogram
 *   throws a qgar::QgarErrorDomain exception
 */
  void testSmoothThrowTooLarge();

/**
 * @brief Tests qgar::Histogram::smooth(unsigned int)
 *
 * Performed Tests:
 * - smoothing using a window with a size = 0
 *   throws a qgar::QgarErrorDomain exception
 */
  void testSmoothThrowZero();
//@}

// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

/** @name Data for the tests */
//        ==================
//@{

/**
 * @brief 256 X 10 grey-level image.
 */
static qgar::GreyLevelImage _testImg;

//@}

// -------------------------------------------------------------------
}; // class HistogramTest


#endif /* __HISTOGRAMTEST_H_INCLUDED__ */
