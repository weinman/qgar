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
 * @file  GenMask1dTest.cpp
 * @brief Implementation of class GenMask1dTest
 *
 *        See file GenMask1dTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   December 12, 2003  10:50
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenMask1dTest.cpp,v 1.4 2005/01/28 15:56:45 masini Exp $ */



// STD
#include <iostream>
// QGAR
#include <qgarlib/GenMask1d.h>
// QGAR TESTS
#include "GenMask1dTest.h"



using namespace std;
using namespace qgar;



// ------------------------------------------------------------------
// U N N A M E D   N A M E S P A C E
// ------------------------------------------------------------------
namespace
{

/**
 * @brief Create an array of value of a given size.
 *
 * The values are initialized so that val[i] = i.
 *
 * @param width the desired size of the array.
 * @param mask a pointer to store the created array in.
 */
template<typename T>
void createMaskArray(int width, T*& mask)
{
  try {
    mask = new T[width];
  }
  catch(...) {
    cout << "[GenImageTest] Fatal error L" << __LINE__ 
	 << " Could not allocate pixmap " << endl;

    throw;
  }
  
  T val = static_cast<T>(0);
  
  for(int i = 0; i < (width); ++i) {
    mask[i] = val++;
  }
}


/**
 * @brief Compares two 1D masks of equal size.
 *
 * @return true if both mask values are identical.
 */
template<typename T>
bool compare(const GenMask1d<T>& lhs, 
	     const GenMask1d<T>& rhs)
{
  bool match = (lhs.width() == rhs.width());
  
  int width = lhs.width();

  for (int i=0; (i < width) && match; ++i) {
    
    match = (lhs.coeff(i) == rhs.coeff(i));
  }

  return match;
}

} // unnamed namespace.


// ------------------------------------------------------------------
// T E S T F I X T U R E   I M P L
// ------------------------------------------------------------------

void
GenMask1dTest::setUp()
{
  /* EMPTY */
}

// -------------------------------------------------------------------

void
GenMask1dTest::tearDown()
{
  /* EMPTY */
}


// -------------------------------------------------------------------
// T E S T   F U N C T I O N S
// -------------------------------------------------------------------

void
GenMask1dTest::testDefaultConstructor()
{
  // -------
  // Process
  // -------

  IMask1d iMask;
  FMask1d fMask;
  DMask1d dMask;
  

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( 0, iMask.width() );
  CPPUNIT_ASSERT( iMask.pCoeffMap()==0 );
  
  CPPUNIT_ASSERT_EQUAL( 0, fMask.width() );
  CPPUNIT_ASSERT( fMask.pCoeffMap() == 0 );
  
  CPPUNIT_ASSERT_EQUAL( 0, dMask.width() );
  CPPUNIT_ASSERT( dMask.pCoeffMap()==0 );
}

// -------------------------------------------------------------------

void
GenMask1dTest::testCopyConstructor()
{
  // ------
  // Set Up
  // ------

  const int MASK_WIDTH = 50;

  int    * iArray;
  float  * fArray;
  double * dArray;
  
  createMaskArray(MASK_WIDTH, iArray);
  createMaskArray(MASK_WIDTH, fArray);
  createMaskArray(MASK_WIDTH, dArray);

  IMask1d iMask(MASK_WIDTH, iArray);
  FMask1d fMask(MASK_WIDTH, fArray);
  DMask1d dMask(MASK_WIDTH, dArray);

   
  // -------
  // Process
  // -------

  IMask1d iDupMask(iMask);
  FMask1d fDupMask(fMask);
  DMask1d dDupMask(dMask);


  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( MASK_WIDTH, iDupMask.width() );
  CPPUNIT_ASSERT( compare(iDupMask, iMask) );

  CPPUNIT_ASSERT_EQUAL( MASK_WIDTH, fDupMask.width() );
  CPPUNIT_ASSERT( compare(fDupMask, fMask) );

  CPPUNIT_ASSERT_EQUAL( MASK_WIDTH, dDupMask.width() );
  CPPUNIT_ASSERT( compare(dDupMask, dMask) );
		   
  // ---------
  // Tear Down
  // ---------

  delete[] iArray;
  delete[] fArray;
  delete[] dArray;
}

// -------------------------------------------------------------------

void
GenMask1dTest::testConversionConstructor()
{
  // ------
  // Set Up
  // ------

  const int MASK_WIDTH = 50;

  int    * iArray;
  float  * fArray;
  double * dArray;
  
  createMaskArray(MASK_WIDTH, iArray);
  createMaskArray(MASK_WIDTH, fArray);
  createMaskArray(MASK_WIDTH, dArray);

  IMask1d iMask(MASK_WIDTH, iArray);
  FMask1d fMask(MASK_WIDTH, fArray);
  DMask1d dMask(MASK_WIDTH, dArray);

   
  // -------
  // Process
  // -------

  IMask1d ftoiConvMask(fMask);
  IMask1d dtoiConvMask(dMask);

  FMask1d itofConvMask(iMask);
  FMask1d dtofConvMask(dMask);

  DMask1d itodConvMask(iMask);
  DMask1d ftodConvMask(fMask);


  // -----
  // Check
  // -----

  // int
  for (int i=0; i < MASK_WIDTH; ++i) {
    CPPUNIT_ASSERT(ftoiConvMask.coeff(i) 
		   == static_cast<int>(fMask.coeff(i)));
  }
  for (int i=0; i < MASK_WIDTH; ++i) {
    CPPUNIT_ASSERT(dtoiConvMask.coeff(i) 
		   == static_cast<int>(dMask.coeff(i)));
  }


  // float
  for (int i=0; i < MASK_WIDTH; ++i) {
    CPPUNIT_ASSERT(itofConvMask.coeff(i) 
		   == static_cast<float>(iMask.coeff(i)));
  }
  for (int i=0; i < MASK_WIDTH; ++i) {
    CPPUNIT_ASSERT(dtofConvMask.coeff(i) 
		   == static_cast<float>(dMask.coeff(i)));
  }

  // double
  for (int i=0; i < MASK_WIDTH; ++i) {
    CPPUNIT_ASSERT(itodConvMask.coeff(i) 
		   == static_cast<double>(iMask.coeff(i)));
  }
  for (int i=0; i < MASK_WIDTH; ++i) {
    CPPUNIT_ASSERT(ftodConvMask.coeff(i) 
		   == static_cast<double>(fMask.coeff(i)));
  }


  // ---------
  // Tear Down
  // ---------

  delete[] iArray;
  delete[] fArray;
  delete[] dArray;
}

// -------------------------------------------------------------------

void
GenMask1dTest::testAssignment()
{
  // ------
  // Set Up
  // ------

  const int MASK_WIDTH = 50;

  int    * iArray;
  float  * fArray;
  double * dArray;
  
  createMaskArray(MASK_WIDTH, iArray);
  createMaskArray(MASK_WIDTH, fArray);
  createMaskArray(MASK_WIDTH, dArray);

  IMask1d iMask(MASK_WIDTH, iArray);
  FMask1d fMask(MASK_WIDTH, fArray);
  DMask1d dMask(MASK_WIDTH, dArray);

  
  // -------
  // Process
  // -------

  IMask1d iDupMask;
  FMask1d fDupMask;
  DMask1d dDupMask;

  iDupMask = iMask;
  fDupMask = fMask;
  dDupMask = dMask;


  // -----
  // Check
  // -----
  
  CPPUNIT_ASSERT_EQUAL( MASK_WIDTH, iDupMask.width() );
  CPPUNIT_ASSERT( compare(iDupMask, iMask) );
  CPPUNIT_ASSERT( &iDupMask == &(iDupMask = iMask) );

  CPPUNIT_ASSERT_EQUAL( MASK_WIDTH, fDupMask.width() );
  CPPUNIT_ASSERT( compare(fDupMask, fMask) );
  CPPUNIT_ASSERT( &fDupMask == &(fDupMask = fMask) );

  CPPUNIT_ASSERT_EQUAL( MASK_WIDTH, dDupMask.width() );
  CPPUNIT_ASSERT( compare(dDupMask, dMask) );
  CPPUNIT_ASSERT( &dDupMask == &(dDupMask = dMask) );
  

  // ---------
  // Tear Down
  // ---------

  delete[] iArray;
  delete[] fArray;
  delete[] dArray;

}

// -------------------------------------------------------------------

void
GenMask1dTest::testBuildWithDefaultValue()
{
  // ------
  // Set Up
  // ------

  const int MASK_SIZE = 20;

  int    iVal = 19;
  float  fVal = 24.52F;
  double dVal = 13.94913;


  // -------
  // Process
  // -------

  IMask1d iMask(MASK_SIZE, iVal);
  FMask1d fMask(MASK_SIZE, fVal);
  DMask1d dMask(MASK_SIZE, dVal);
  

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( MASK_SIZE, iMask.width() );
  for (int i=0; i < MASK_SIZE; ++i) {
    CPPUNIT_ASSERT_EQUAL( iVal, iMask.coeff(i) );
  }
  
  CPPUNIT_ASSERT_EQUAL( MASK_SIZE, fMask.width() );
  for (int i=0; i < MASK_SIZE; ++i) {
    CPPUNIT_ASSERT_EQUAL( fVal, fMask.coeff(i) );
  }
  
  CPPUNIT_ASSERT_EQUAL( MASK_SIZE, dMask.width() );
  for (int i=0; i < MASK_SIZE; ++i) {
    CPPUNIT_ASSERT_EQUAL( dVal, dMask.coeff(i) );
  }
}

// -------------------------------------------------------------------

void
GenMask1dTest::testBuildFromValArray()
{
  // ------
  // Set Up
  // ------
  
  const int MASK_WIDTH = 50;
 
  int    * iArray;
  float  * fArray;
  double * dArray;
  
  createMaskArray(MASK_WIDTH, iArray);
  createMaskArray(MASK_WIDTH, fArray);
  createMaskArray(MASK_WIDTH, dArray);

  // -------
  // Process
  // -------

  IMask1d iMask(MASK_WIDTH, iArray);
  FMask1d fMask(MASK_WIDTH, fArray);
  DMask1d dMask(MASK_WIDTH, dArray);

  
  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( MASK_WIDTH, iMask.width() );
  for (int i=0; i < MASK_WIDTH; ++i) {
    CPPUNIT_ASSERT_EQUAL( iArray[i], iMask.coeff(i) );
  }
  
  CPPUNIT_ASSERT_EQUAL( MASK_WIDTH, fMask.width() );
  for (int i=0; i < MASK_WIDTH; ++i) {
    CPPUNIT_ASSERT_EQUAL( fArray[i], fMask.coeff(i) );
  }

  CPPUNIT_ASSERT_EQUAL( MASK_WIDTH, dMask.width() );
  for (int i=0; i < MASK_WIDTH; ++i) {
    CPPUNIT_ASSERT_EQUAL( dArray[i], dMask.coeff(i) );
  }


  // ---------
  // Tear Down
  // ---------

  delete[] iArray;
  delete[] fArray;
  delete[] dArray;
}

// ----------------------------------------------------------------------
void
GenMask1dTest::testPCoeffMap()
{
  // ------
  // Set Up
  // ------
  
  const int MASK_WIDTH = 50;
 
  int    * iArray;
  float  * fArray;
  double * dArray;
  
  createMaskArray(MASK_WIDTH, iArray);
  createMaskArray(MASK_WIDTH, fArray);
  createMaskArray(MASK_WIDTH, dArray);

  IMask1d iMask(MASK_WIDTH, iArray);
  FMask1d fMask(MASK_WIDTH, fArray);
  DMask1d dMask(MASK_WIDTH, dArray);


  // -----
  // Check
  // -----

  for (int i=0; i < MASK_WIDTH; i++) {
    CPPUNIT_ASSERT_EQUAL(iArray[i], iMask.pCoeffMap()[i]);
  }

  for (int i=0; i < MASK_WIDTH; i++) {
    CPPUNIT_ASSERT_EQUAL(fArray[i], fMask.pCoeffMap()[i]);
  }

  for (int i=0; i < MASK_WIDTH; i++) {
    CPPUNIT_ASSERT_EQUAL(dArray[i], dMask.pCoeffMap()[i]);
  }
}

// -------------------------------------------------------------------

void
GenMask1dTest::testSetCoeff()
{
  // ------
  // Set Up
  // ------

  const int MASK_WIDTH = 50;

  int    * iArray;
  float  * fArray;
  double * dArray;
  
  createMaskArray(MASK_WIDTH, iArray);
  createMaskArray(MASK_WIDTH, fArray);
  createMaskArray(MASK_WIDTH, dArray);

  IMask1d iMask(MASK_WIDTH, iArray);
  FMask1d fMask(MASK_WIDTH, fArray);
  DMask1d dMask(MASK_WIDTH, dArray);

  int    iCoef = 22;
  float  fCoef = 2.2F;
  double dCoef = 93.13;

  const int COL = 20;
  
  // -------
  // Process
  // -------

  iMask.setCoeff(COL, iCoef);
  fMask.setCoeff(COL, fCoef);
  dMask.setCoeff(COL, dCoef);


  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL(iMask.coeff(COL), iCoef);
  CPPUNIT_ASSERT_EQUAL(fMask.coeff(COL), fCoef);
  CPPUNIT_ASSERT_EQUAL(dMask.coeff(COL), dCoef);

  // ---------
  // Tear Down
  // ---------

  delete[] iArray;
  delete[] fArray;
  delete[] dArray;
}

// -------------------------------------------------------------------

void
GenMask1dTest::testShallowCopy()
{
  // ------
  // Set Up
  // ------
  
  const int MASK_WIDTH = 50;

  int    * iArray;
  float  * fArray;
  double * dArray;
  
  createMaskArray(MASK_WIDTH, iArray);
  createMaskArray(MASK_WIDTH, fArray);
  createMaskArray(MASK_WIDTH, dArray);

  IMask1d iMask(MASK_WIDTH, iArray);
  FMask1d fMask(MASK_WIDTH, fArray);
  DMask1d dMask(MASK_WIDTH, dArray);

  
  // -------
  // Process
  // -------

  IMask1d * iDupMask = iMask.shallowCopy();
  FMask1d * fDupMask = fMask.shallowCopy();
  DMask1d * dDupMask = dMask.shallowCopy();


  // -----
  // Check
  // -----
  
  CPPUNIT_ASSERT_EQUAL( MASK_WIDTH, iDupMask->width() );
  CPPUNIT_ASSERT( compare(*iDupMask, iMask) );

  CPPUNIT_ASSERT_EQUAL( MASK_WIDTH, fDupMask->width() );
  CPPUNIT_ASSERT( compare(*fDupMask, fMask) );

  CPPUNIT_ASSERT_EQUAL( MASK_WIDTH, dDupMask->width() );
  CPPUNIT_ASSERT( compare(*dDupMask, dMask) );
  

  // ---------
  // Tear Down
  // ---------

  delete[] iArray;
  delete[] fArray;
  delete[] dArray;
}

// -------------------------------------------------------------------
