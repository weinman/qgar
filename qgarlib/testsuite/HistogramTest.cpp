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


/**
 * @file  HistogramTest.cpp
 * @brief Implementation of class HistogramTest
 *
 * See file HistogramTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 5, 2003  17:25
 * @since  Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: HistogramTest.cpp,v 1.4 2005/07/13 16:29:34 masini Exp $ */



// QGAR
#include <qgarlib/GenImage.h>
#include <qgarlib/Histogram.h>
#include <qgarlib/QgarErrorDomain.h>
// QGAR TESTS
#include "HistogramTest.h"



using namespace qgar;
using namespace std;



// -------------------------------------------------------------------
// U N N A M E D   N A M E S P A C E
// -------------------------------------------------------------------

namespace
{


// Checks if a range of cells are set to a given value
void assertFrequenciesEqual(Histogram& aHstg,
			     int aLowerBnd,
			     int anUpperBnd,
			     int aValue)
{
  for (int idx = aLowerBnd ; idx <= anUpperBnd ; idx++)
    {
      CPPUNIT_ASSERT_EQUAL( aHstg[idx], aValue );
    }
}


} // unnamed namespace


// -------------------------------------------------------------------
// S T A T I C    M E M B E R S
// -------------------------------------------------------------------


// 256 X 10 grey-level image to perform the tests
GreyLevelImage HistogramTest::_testImg = GreyLevelImage(256, 10);


// ------------------------------------------------------------------
// T E S T   F I X T U R E   I M P L E M E N T A T I O N
// ------------------------------------------------------------------


void
HistogramTest::setUp()
{
  // Set test image columns with grey values from 0 to 255
  for (int xdx = 0 ; xdx < 256 ; ++xdx)
    {
      for (int ydx = 0 ; ydx < 10 ; ++ydx)
	{
	  _testImg.setPixel(xdx, ydx, xdx);
	}
    }
}


void
HistogramTest::tearDown()
{
  /* EMPTY */
}


// -------------------------------------------------------------------
// T E S T   F U N C T I O N S
// -------------------------------------------------------------------


void
HistogramTest::testDefaultConstructor()
{
  Histogram hstg;

  // -----
  // Check
  // -----

  // Ensure that sampling rate is initialized to 1.
  CPPUNIT_ASSERT_EQUAL( hstg.samplingRate(), 1 );
  // Ensure that lower bound is initialized to 0.
  CPPUNIT_ASSERT_EQUAL( hstg.lowerBnd(),     0 );
  // Ensure that upper bound is initialized to 0.
  CPPUNIT_ASSERT_EQUAL( hstg.upperBnd(),     0 );
}

// -------------------------------------------------------------------

void
HistogramTest::testRandomAccessOpThrowLowerBnd()
{
  Histogram hstg;

  // Accesse to a sample < lower bound
  // Should throw a QgarErrorDomain exception
  hstg[-10];
  hstg[10];
}

// -------------------------------------------------------------------

void
HistogramTest::testRandomAccessOpThrowUpperBnd()
{
  Histogram hstg;

  // Accesse to a sample > upper bound
  // Should throw a QgarErrorDomain exception
  hstg[10];
}

// -------------------------------------------------------------------

void
HistogramTest::testBuildFromBndSampRate()
{
  // -------
  // Process
  // -------
  
  // Histograms with various bounds and sampling rates
  Histogram hstg1(1, 10);
  Histogram hstg2(-15, -6);
  Histogram hstg3(-10, 10, 2);
  Histogram hstg4(0, 10, 20);

  // -----
  // Check
  // -----

  // Ensure that sampling rate is correctly initialized
  CPPUNIT_ASSERT_EQUAL( hstg1.samplingRate(), 1 );
  CPPUNIT_ASSERT_EQUAL( hstg2.samplingRate(), 1 );
  CPPUNIT_ASSERT_EQUAL( hstg3.samplingRate(), 2 );
  CPPUNIT_ASSERT_EQUAL( hstg4.samplingRate(), 20 );

  // Ensure that lower bound is correctly initialized
  CPPUNIT_ASSERT_EQUAL( hstg1.lowerBnd(), 1 );
  CPPUNIT_ASSERT_EQUAL( hstg2.lowerBnd(), -15 );
  CPPUNIT_ASSERT_EQUAL( hstg3.lowerBnd(), -10 );
  CPPUNIT_ASSERT_EQUAL( hstg4.lowerBnd(), 0 );

  // Ensure that upper bound is correctly initialized
  CPPUNIT_ASSERT_EQUAL( hstg1.upperBnd(), 10 );
  CPPUNIT_ASSERT_EQUAL( hstg2.upperBnd(), -6 );
  CPPUNIT_ASSERT_EQUAL( hstg3.upperBnd(), 10 );
  CPPUNIT_ASSERT_EQUAL( hstg4.upperBnd(), 10 );

  // Ensure that all cells are initialized to 0
  assertFrequenciesEqual(hstg1, hstg1.lowerBnd(), hstg1.upperBnd(), 0);
  assertFrequenciesEqual(hstg2, hstg2.lowerBnd(), hstg2.upperBnd(), 0);
  assertFrequenciesEqual(hstg3, hstg3.lowerBnd(), hstg3.upperBnd(), 0);
  assertFrequenciesEqual(hstg4, hstg4.lowerBnd(), hstg4.upperBnd(), 0);
}

// -------------------------------------------------------------------

void
HistogramTest::testBuildFromBndSampRateThrowBnds()
{
  // Should throw a QgarErrorDomain exception
  // Cannot be created with lower boud > upper bound
  Histogram hstg(10, -10);
}

// -------------------------------------------------------------------

void
HistogramTest::testBuildFromBndSampRateThrowRate()
{
  // Should throw a QgarErrorDomain exception
  // Cannot be created with sampling rate equal to zero
  Histogram hstg(1, 10, 0);
}

// -------------------------------------------------------------------

void
HistogramTest::testBuildFromGreylevelImg()
{
  // SAMPLING RATE = 1
  Histogram hstg1(_testImg, 0, 255);
  // Ensure that sampling rate is correctly initialized
  CPPUNIT_ASSERT_EQUAL( hstg1.samplingRate(), 1 );
  // Ensure that lower bound is correctly initialized
  CPPUNIT_ASSERT_EQUAL( hstg1.lowerBnd(), 0);
  // Ensure that upper bound is correctly initialized
  CPPUNIT_ASSERT_EQUAL( hstg1.upperBnd(), 255 );
  // Ensure that all frequencies are set to 10
  assertFrequenciesEqual(hstg1, 0, 255, 10);

  // SAMPLING RATE = 2
  Histogram hstg2(_testImg, 0, 255, 2);
  // Ensure that sampling rate is correctly initialized
  CPPUNIT_ASSERT_EQUAL( hstg2.samplingRate(), 2 );
  // Ensure that lower bound is correctly initialized
  CPPUNIT_ASSERT_EQUAL( hstg2.lowerBnd(), 0);
  // Ensure that upper bound is correctly initialized
  CPPUNIT_ASSERT_EQUAL( hstg2.upperBnd(), 255 );
  // Ensure that all frequencies are set to 20
  assertFrequenciesEqual(hstg2, 0, 255, 20);

  // SAMPLING RATE = 3
  Histogram hstg3(_testImg, 0, 255, 3);
  // Ensure that sampling rate is correctly initialized
  CPPUNIT_ASSERT_EQUAL( hstg3.samplingRate(), 3 );
  // Ensure that lower bound is correctly initialized
  CPPUNIT_ASSERT_EQUAL( hstg3.lowerBnd(), 0);
  // Ensure that upper bound is correctly initialized
  CPPUNIT_ASSERT_EQUAL( hstg3.upperBnd(), 255 );
  // Ensure that all frequencies are set to 30,
  // except the last one, that should be set to 20
  assertFrequenciesEqual(hstg3, 0, 254, 30);
  CPPUNIT_ASSERT_EQUAL( hstg3[255], 10 );

  // SAMPLING RATE = 256
  Histogram hstg256(_testImg, 0, 255, 256);
  // Ensure that sampling rate is correctly initialized
  CPPUNIT_ASSERT_EQUAL( hstg256.samplingRate(), 256 );
  // Ensure that lower bound is correctly initialized
  CPPUNIT_ASSERT_EQUAL( hstg256.lowerBnd(), 0);
  // Ensure that upper bound is correctly initialized
  CPPUNIT_ASSERT_EQUAL( hstg256.upperBnd(), 255 );
  // Ensure that all frequencies are set to 2560
  assertFrequenciesEqual(hstg256, 0, 255, 2560);
}

// -------------------------------------------------------------------

void
HistogramTest::testBuildFromGreylevelImgThrowBnds()
{
  Histogram hstg(_testImg, 5, 1);
}


// -------------------------------------------------------------------

void
HistogramTest::testBuildFromGreylevelImgThrowRate()
{
  Histogram hstg(_testImg, 1, 5, 0);
}

// -------------------------------------------------------------------

void
HistogramTest::testCopyConstructor()
{
  // An histogram
  Histogram hstg(_testImg, 0, 255);
  // A copy of the previous one
  Histogram hcpy(hstg);

  // Ensure that both histograms are quite similar
  // sampling rate
  CPPUNIT_ASSERT_EQUAL( hstg.samplingRate(), hcpy.samplingRate() );
  // lower bound
  CPPUNIT_ASSERT_EQUAL( hstg.lowerBnd(), hcpy.lowerBnd() );
  // upper bound
  CPPUNIT_ASSERT_EQUAL( hstg.upperBnd(), hcpy.upperBnd() );
  // frequencies
  for (int idx = hstg.lowerBnd() ; idx <= hstg.upperBnd() ; idx++)
    {
      CPPUNIT_ASSERT_EQUAL( hstg[idx], hcpy[idx] );
    }
}

// -------------------------------------------------------------------

void
HistogramTest::testAssignment()
{
  // An histogram
  Histogram hstg(_testImg, 0, 255, 5);
  // A copy of the previous one
  Histogram hcpy = hstg;

  // Ensure that both histograms are quite similar
  // sampling rate
  CPPUNIT_ASSERT_EQUAL( hstg.samplingRate(), hcpy.samplingRate() );
  // lower bound
  CPPUNIT_ASSERT_EQUAL( hstg.lowerBnd(), hcpy.lowerBnd() );
  // upper bound
  CPPUNIT_ASSERT_EQUAL( hstg.upperBnd(), hcpy.upperBnd() );
  // frequencies
  for (int idx = hstg.lowerBnd() ; idx <= hstg.upperBnd() ; idx++)
    {
      CPPUNIT_ASSERT_EQUAL( hstg[idx], hcpy[idx] );
    }
}

// -------------------------------------------------------------------

void
HistogramTest::testLowerBnd()
{
  // NO TEST
}

// -------------------------------------------------------------------

void
HistogramTest::testUpperBnd()
{
  // NO TEST
}

// -------------------------------------------------------------------

void
HistogramTest::testSamplingRate()
{
  // NO TEST
}

// -------------------------------------------------------------------

void
HistogramTest::testPlus()
{
  // An histogram with sample rate = 1
  Histogram hstg1(_testImg, 0, 255);
  // An histogram with sample rate = 5
  Histogram hstg5(_testImg, 0, 255, 5);

  // Increment frequencies
  hstg1.plus(0);
  hstg5.plus(0, 10);
  hstg5.plus(1, 10);
  hstg5.plus(2, 10);
  hstg5.plus(3, 10);
  hstg5.plus(4, 10);
  hstg5.plus(5, 5);

  // Ensure that frequencies are correctly incremented
  CPPUNIT_ASSERT_EQUAL( hstg1[0], 11);
  CPPUNIT_ASSERT_EQUAL( hstg5[0], 100);
  CPPUNIT_ASSERT_EQUAL( hstg5[1], 100);
  CPPUNIT_ASSERT_EQUAL( hstg5[2], 100);
  CPPUNIT_ASSERT_EQUAL( hstg5[3], 100);
  CPPUNIT_ASSERT_EQUAL( hstg5[4], 100);
  CPPUNIT_ASSERT_EQUAL( hstg5[5], 55);

  // Ensure other frequencies are not changed
  assertFrequenciesEqual(hstg1, 1,  255, 10);
  assertFrequenciesEqual(hstg5, 5,  9,   55);
  assertFrequenciesEqual(hstg5, 10, 254, 50);
  CPPUNIT_ASSERT_EQUAL( hstg5[255], 10);
}

// -------------------------------------------------------------------

void
HistogramTest::testMinus()
{
  // An histogram with sample rate = 1
  Histogram hstg1(_testImg, 0, 255);
  // An histogram with sample rate = 5
  Histogram hstg5(_testImg, 0, 255, 5);

  // Increment frequencies
  hstg1.minus(0);
  hstg5.minus(0, 5);
  hstg5.minus(1, 10);
  hstg5.minus(2, 10);
  hstg5.minus(3, 10);
  hstg5.minus(4, 10);
  hstg5.minus(5, 5);

  // Ensure that frequencies are correctly incremented
  CPPUNIT_ASSERT_EQUAL( hstg1[0], 9);
  CPPUNIT_ASSERT_EQUAL( hstg5[0], 5);
  CPPUNIT_ASSERT_EQUAL( hstg5[1], 5);
  CPPUNIT_ASSERT_EQUAL( hstg5[2], 5);
  CPPUNIT_ASSERT_EQUAL( hstg5[3], 5);
  CPPUNIT_ASSERT_EQUAL( hstg5[4], 5);
  CPPUNIT_ASSERT_EQUAL( hstg5[5], 45);

  // Ensure other frequencies are not changed
  assertFrequenciesEqual(hstg1, 1,  255, 10);
  assertFrequenciesEqual(hstg5, 5,  9,   45);
  assertFrequenciesEqual(hstg5, 10, 254, 50);
  CPPUNIT_ASSERT_EQUAL( hstg5[255], 10);
}

// -------------------------------------------------------------------

void
HistogramTest::testMaxSample()
{
  // An histogram with sample rate = 1
  Histogram hstg(_testImg, 0, 255);

  // Add 3 maxima
  hstg.plus(100, 100);
  hstg.plus(150, 100);
  hstg.plus(200, 100);

  // Ensure the lower maximum sample can be found
  CPPUNIT_ASSERT_EQUAL( hstg.maxSample(), 100);
}

// -------------------------------------------------------------------

void
HistogramTest::testMaxSampleStartingFromBnd()
{
  // An histogram with sample rate = 1
  Histogram hstg(_testImg, 0, 255);

  // Add 3 maxima
  hstg.plus(100, 100);
  hstg.plus(150, 100);
  hstg.plus(200, 100);

  // Ensure the lower maximum sample can be found in each case
  CPPUNIT_ASSERT_EQUAL( hstg.maxSample(5),   100);
  CPPUNIT_ASSERT_EQUAL( hstg.maxSample(100), 100);
  CPPUNIT_ASSERT_EQUAL( hstg.maxSample(125), 150);
  CPPUNIT_ASSERT_EQUAL( hstg.maxSample(199), 200);
  CPPUNIT_ASSERT_EQUAL( hstg.maxSample(210), 210);
  CPPUNIT_ASSERT_EQUAL( hstg.maxSample(255), 255);
}

// -------------------------------------------------------------------

void
HistogramTest::testMinSample()
{
  // An histogram with sample rate = 1
  Histogram hstg(_testImg, 0, 255);

  // Add 3 minima
  hstg.minus(100, 5);
  hstg.minus(150, 5);
  hstg.minus(200, 5);

  // Ensure the lower minimum sample can be found
  CPPUNIT_ASSERT_EQUAL( hstg.minSample(), 100);
}

// -------------------------------------------------------------------

void
HistogramTest::testMinSampleStartingFromBnd()
{
  // An histogram with sample rate = 1
  Histogram hstg(_testImg, 0, 255);

  // Add 3 minima
  hstg.minus(100, 9);
  hstg.minus(150, 9);
  hstg.minus(200, 9);

  // Ensure the lower minimum sample can be found in each case
  CPPUNIT_ASSERT_EQUAL( hstg.minSample(5),   100);
  CPPUNIT_ASSERT_EQUAL( hstg.minSample(100), 100);
  CPPUNIT_ASSERT_EQUAL( hstg.minSample(125), 150);
  CPPUNIT_ASSERT_EQUAL( hstg.minSample(199), 200);
  CPPUNIT_ASSERT_EQUAL( hstg.minSample(210), 210);
  CPPUNIT_ASSERT_EQUAL( hstg.minSample(255), 255);
}

// -------------------------------------------------------------------

void
HistogramTest::testPartialSum()
{
  // Histogram with sample rate = 1
  Histogram hstg1(_testImg, 0, 255);
  // Ensure resulting accumulated histogram is correctly computed
  hstg1.partialSum();
  int sum = 10;
  for (int idx = 0 ; idx < 256 ; idx++)
    {
      CPPUNIT_ASSERT_EQUAL( hstg1[idx], sum );
      sum += 10;
    }

  // Histogram with sample rate = 10
  Histogram hstg10(_testImg, 0, 255, 10);
  // Ensure resulting accumulated histogram is correctly computed
  hstg10.partialSum();
  sum = 100;
  for (int idx = 0 ; idx < 250 ; idx += 10)
    {
      // Samples corresponding to the sampling rate
      for (int jdx = idx ; jdx < (idx + 10) ; jdx++)
	{
	  CPPUNIT_ASSERT_EQUAL( hstg10[jdx], sum );
	}
      sum += 100;
    }
  // 6 last samples
  sum = 2560;
  for (int idx = 250 ; idx < 256 ; idx++)
    {
      CPPUNIT_ASSERT_EQUAL( hstg10[idx], sum );
    }
}

// -------------------------------------------------------------------

void
HistogramTest::testSmooth()
{
  Histogram hstg(_testImg, 0, 255);
  Histogram hcpy(hstg);

  // Ensure smoothing a flat histogram has no effect
  hstg.smooth(6);
  for (int idx = 0 ; idx < 256 ; idx++)
    {
      CPPUNIT_ASSERT_EQUAL( hstg[idx], hcpy[idx] );
    }

  Histogram hstg1(1, 11);
  hstg1.plus(1,  10);
  hstg1.plus(2,  20);
  hstg1.plus(3,  30);
  hstg1.plus(4,  40);
  hstg1.plus(5,  30);
  hstg1.plus(6,  20);
  hstg1.plus(7,  30);
  hstg1.plus(8,  40);
  hstg1.plus(9,  50);
  hstg1.plus(10, 25);
  Histogram hcpy1(hstg1);
  // Ensure smoothing with a window size = 1 has no effect
  hstg1.smooth(1);
  for (int idx = 1 ; idx < 12 ; idx++)
    {
      CPPUNIT_ASSERT_EQUAL( hstg1[idx], hcpy1[idx] );
    }

  // Smooth using a window of size = 2
  hstg1.smooth(2);
  // Ensure smoothing is correctly performed
  CPPUNIT_ASSERT_EQUAL( hstg1[1],  10 );
  CPPUNIT_ASSERT_EQUAL( hstg1[2],  15 );
  CPPUNIT_ASSERT_EQUAL( hstg1[3],  25 );
  CPPUNIT_ASSERT_EQUAL( hstg1[4],  35 );
  CPPUNIT_ASSERT_EQUAL( hstg1[5],  35 );
  CPPUNIT_ASSERT_EQUAL( hstg1[6],  25 );
  CPPUNIT_ASSERT_EQUAL( hstg1[7],  25 );
  CPPUNIT_ASSERT_EQUAL( hstg1[8],  35 );
  CPPUNIT_ASSERT_EQUAL( hstg1[9],  45 );
  CPPUNIT_ASSERT_EQUAL( hstg1[10], 37 );
  CPPUNIT_ASSERT_EQUAL( hstg1[11], 12 );
}

// -------------------------------------------------------------------

void
HistogramTest::testSmoothThrowEqual()
{
  Histogram hstg(-10, 10, 2);
  // Smooth using a too large window
  // Should throw a QgarErrorDomain exception
  hstg.smooth(11);
}

// -------------------------------------------------------------------

void
HistogramTest::testSmoothThrowTooLarge()
{
  Histogram hstg(1, 10);
  // Smooth using a window of the same size as the histogram
  // Should throw a QgarErrorDomain exception
  hstg.smooth(20);
}

// -------------------------------------------------------------------

void
HistogramTest::testSmoothThrowZero()
{
  Histogram hstg(1, 10);
  // Smooth using a size equal to 0
  // Should throw a QgarErrorDomain exception
  hstg.smooth(0);  
}

// ----------------------------------------------------------------------
