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
 * @file  GenMask2dTest.cpp
 * @brief Implementation of class GenMask2dTest
 *
 *        See file GenMask2dTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   December 15, 2003  15:03
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenMask2dTest.cpp,v 1.3 2005/01/28 15:56:45 masini Exp $ */



// STL
#include <iostream>
// QGAR
#include <qgarlib/GenMask2d.h>
// QGAR TESTS
#include "GenMask2dTest.h"



using namespace qgar;
using namespace std;



// ------------------------------------------------------------------
// U N N A M E D   N A M E S P A C E
// ------------------------------------------------------------------
namespace 
{

/**
 * @brief Creates an array of values of a given size.
 *
 * 
 * @param width  The width of the array to create.
 * @param height The heigth of the array to create.
 * @param mask   A pointer to return the array in.
 */
template<typename T>
void createMaskArray(int width, int height, T*& mask)
{
  try {
    mask = new T[width * height];
  }
  catch(...) {
    cout << "[GenImageTest] Fatal error L" << __LINE__ 
	 << " Could not allocate mask " << endl;

    throw;
  }
  
  T val = static_cast<T>(0);
  
  for(int i = 0; i < (width * height); ++i) {
    mask[i] = val++;
  }
}


/**
 * @brief Compares two masks of equal dimensions.
 *
 * @param lhs The first mask.
 * @param rhs The second mask.
 */
template<typename T>
bool compare(const GenMask2d<T>& lhs, const GenMask2d<T>& rhs)
{
  bool match = true;
  
  int width  = lhs.width();
  int height = lhs.height();

  for (int j=0; j < height; ++j)
    for(int i=0; (i < width) && match; ++i)
      match = (lhs.coeff(i, j) == rhs.coeff(i, j));

  return match;
}


} // unnamed namespace



// ------------------------------------------------------------------
// T E S T F I X T U R E   I M P L
// ------------------------------------------------------------------

void
GenMask2dTest::setUp()
{
  /* EMPTY */
}

// -------------------------------------------------------------------

void
GenMask2dTest::tearDown()
{
  /* EMPTY */
}


// -------------------------------------------------------------------
// T E S T   F U N C T I O N S
// -------------------------------------------------------------------

void
GenMask2dTest::testDefaultConstructor()
{
  // -------
  // Process
  // -------

  IMask2d iMask;
  FMask2d fMask;
  DMask2d dMask;
  

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( 0, iMask.width() );
  CPPUNIT_ASSERT_EQUAL( 0, iMask.height() );
  CPPUNIT_ASSERT( iMask.pCoeffMap() == 0 );

  CPPUNIT_ASSERT_EQUAL( 0, fMask.width() );
  CPPUNIT_ASSERT_EQUAL( 0, fMask.height() );
  CPPUNIT_ASSERT( fMask.pCoeffMap() == 0 );

  CPPUNIT_ASSERT_EQUAL( 0, dMask.width() );
  CPPUNIT_ASSERT_EQUAL( 0, dMask.height() );
  CPPUNIT_ASSERT( dMask.pCoeffMap() == 0 );
}

// -------------------------------------------------------------------

void
GenMask2dTest::testCopyConstructor()
{
  // ------
  // Set Up
  // ------

  const int MASK_WIDTH  = 50;
  const int MASK_HEIGHT = 50; 

  int    * iArray;
  float  * fArray;
  double * dArray;
  
  createMaskArray(MASK_WIDTH, MASK_HEIGHT, iArray);
  createMaskArray(MASK_WIDTH, MASK_HEIGHT, fArray);
  createMaskArray(MASK_WIDTH, MASK_HEIGHT, dArray);


  IMask2d iMask(MASK_WIDTH, MASK_HEIGHT, iArray);
  FMask2d fMask(MASK_WIDTH, MASK_HEIGHT, fArray);
  DMask2d dMask(MASK_WIDTH, MASK_HEIGHT, dArray);



  // -------
  // Process
  // -------

  IMask2d iDupMask(iMask);
  FMask2d fDupMask(fMask);
  DMask2d dDupMask(dMask);


  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( iMask.width(), iDupMask.width() );
  CPPUNIT_ASSERT_EQUAL( iMask.height(), iDupMask.height() );
  CPPUNIT_ASSERT( compare(iMask, iDupMask) );

  CPPUNIT_ASSERT_EQUAL( fMask.width(), fDupMask.width() );
  CPPUNIT_ASSERT_EQUAL( fMask.height(), fDupMask.height() );
  CPPUNIT_ASSERT( compare(fMask, fDupMask) );

  CPPUNIT_ASSERT_EQUAL( dMask.width(), dDupMask.width() );
  CPPUNIT_ASSERT_EQUAL( dMask.height(), dDupMask.height() );
  CPPUNIT_ASSERT( compare(dMask, dDupMask) );


  // ---------
  // Tear Down
  // ---------

  delete[] iArray; 
  delete[] fArray;
  delete[] dArray; 
}

// -------------------------------------------------------------------

void
GenMask2dTest::testAssignment()
{
  // ------
  // Set Up
  // ------

  const int MASK_WIDTH  = 50;
  const int MASK_HEIGHT = 20; 

  int    * iArray;
  float  * fArray;
  double * dArray;
  
  createMaskArray(MASK_WIDTH, MASK_HEIGHT, iArray);
  createMaskArray(MASK_WIDTH, MASK_HEIGHT, fArray);
  createMaskArray(MASK_WIDTH, MASK_HEIGHT, dArray);


  IMask2d iMask(MASK_WIDTH, MASK_HEIGHT, iArray);
  FMask2d fMask(MASK_WIDTH, MASK_HEIGHT, fArray);
  DMask2d dMask(MASK_WIDTH, MASK_HEIGHT, dArray);



  // -------
  // Process
  // -------

  IMask2d iDupMask;
  FMask2d fDupMask;
  DMask2d dDupMask;

  iDupMask = iMask;
  fDupMask = fMask;
  dDupMask = dMask;


  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( iMask.width(), iDupMask.width() );
  CPPUNIT_ASSERT_EQUAL( iMask.height(), iDupMask.height() );
  CPPUNIT_ASSERT( compare(iMask, iDupMask) );
  CPPUNIT_ASSERT( &iDupMask == &(iDupMask = iMask) );
  
  CPPUNIT_ASSERT_EQUAL( fMask.width(), fDupMask.width() );
  CPPUNIT_ASSERT_EQUAL( fMask.height(), fDupMask.height() );
  CPPUNIT_ASSERT( compare(fMask, fDupMask) );
  CPPUNIT_ASSERT( &fDupMask == &(fDupMask = fMask) );

  CPPUNIT_ASSERT_EQUAL( dMask.width(), dDupMask.width() );
  CPPUNIT_ASSERT_EQUAL( dMask.height(), dDupMask.height() );
  CPPUNIT_ASSERT( compare(dMask, dDupMask) );
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
GenMask2dTest::testBuildWithDefaultValue()
{
  // -------
  // Process
  // -------

  const int MASK_WIDTH  = 50;
  const int MASK_HEIGHT = 20; 

  int    iVal = 912;
  float  fVal = 32.2F;
  double dVal = 2.134;

  IMask2d iMask(MASK_WIDTH, MASK_HEIGHT, iVal);
  FMask2d fMask(MASK_WIDTH, MASK_HEIGHT, fVal);
  DMask2d dMask(MASK_WIDTH, MASK_HEIGHT, dVal);


  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( MASK_WIDTH, iMask.width() );
  CPPUNIT_ASSERT_EQUAL( MASK_HEIGHT, iMask.height() );
  for (int j=0; j < MASK_HEIGHT; ++j)
    for (int i=0; i <MASK_WIDTH; ++i)
      CPPUNIT_ASSERT_EQUAL( iVal, iMask.coeff(i, j) );

  CPPUNIT_ASSERT_EQUAL( MASK_WIDTH, fMask.width() );
  CPPUNIT_ASSERT_EQUAL( MASK_HEIGHT, fMask.height() );
  for (int j=0; j < MASK_HEIGHT; ++j)
    for (int i=0; i <MASK_WIDTH; ++i)
      CPPUNIT_ASSERT_EQUAL( fVal, fMask.coeff(i, j) );

  CPPUNIT_ASSERT_EQUAL( MASK_WIDTH, dMask.width() );
  CPPUNIT_ASSERT_EQUAL( MASK_HEIGHT, dMask.height() );
  for (int j=0; j < MASK_HEIGHT; ++j)
    for (int i=0; i <MASK_WIDTH; ++i)
      CPPUNIT_ASSERT_EQUAL( dVal, dMask.coeff(i, j) );
}

// -------------------------------------------------------------------

void
GenMask2dTest::testBuildFromValArray()
{
  // ------
  // Set Up
  // ------

  const int MASK_WIDTH  = 50;
  const int MASK_HEIGHT = 20; 

  int    * iArray;
  float  * fArray;
  double * dArray;
  
  createMaskArray(MASK_WIDTH, MASK_HEIGHT, iArray);
  createMaskArray(MASK_WIDTH, MASK_HEIGHT, fArray);
  createMaskArray(MASK_WIDTH, MASK_HEIGHT, dArray);


  // -------
  // Process
  // -------

  IMask2d iMask(MASK_WIDTH, MASK_HEIGHT, iArray);
  FMask2d fMask(MASK_WIDTH, MASK_HEIGHT, fArray);
  DMask2d dMask(MASK_WIDTH, MASK_HEIGHT, dArray);
  

  // -----
  // Check 
  // -----

  CPPUNIT_ASSERT_EQUAL( MASK_WIDTH, iMask.width() );
  CPPUNIT_ASSERT_EQUAL( MASK_HEIGHT, iMask.height() );
  for (int j=0; j < MASK_HEIGHT; ++j)
    for (int i=0; i <MASK_WIDTH; ++i)
      CPPUNIT_ASSERT_EQUAL( iArray[MASK_WIDTH * j + i], 
			    iMask.coeff(i, j) );

  CPPUNIT_ASSERT_EQUAL( MASK_WIDTH, fMask.width() );
  CPPUNIT_ASSERT_EQUAL( MASK_HEIGHT, fMask.height() );
  for (int j=0; j < MASK_HEIGHT; ++j)
    for (int i=0; i <MASK_WIDTH; ++i)
      CPPUNIT_ASSERT_EQUAL( fArray[MASK_WIDTH * j + i], 
			    fMask.coeff(i, j) );

  CPPUNIT_ASSERT_EQUAL( MASK_WIDTH, dMask.width() );
  CPPUNIT_ASSERT_EQUAL( MASK_HEIGHT, dMask.height() );
  for (int j=0; j < MASK_HEIGHT; ++j)
    for (int i=0; i <MASK_WIDTH; ++i)
      CPPUNIT_ASSERT_EQUAL( dArray[MASK_WIDTH * j + i], 
			    dMask.coeff(i, j) );
  
  // ---------
  // Tear Down
  // ---------

  delete[] iArray; 
  delete[] fArray;
  delete[] dArray;
}

// ----------------------------------------------------------------------
void
GenMask2dTest::testPCoeffMap()
{
  // ------
  // Set Up
  // ------

  const int MASK_WIDTH  = 50;
  const int MASK_HEIGHT = 20; 

  int    * iArray;
  float  * fArray;
  double * dArray;
  
  createMaskArray(MASK_WIDTH, MASK_HEIGHT, iArray);
  createMaskArray(MASK_WIDTH, MASK_HEIGHT, fArray);
  createMaskArray(MASK_WIDTH, MASK_HEIGHT, dArray);

  IMask2d iMask(MASK_WIDTH, MASK_HEIGHT, iArray);
  FMask2d fMask(MASK_WIDTH, MASK_HEIGHT, fArray);
  DMask2d dMask(MASK_WIDTH, MASK_HEIGHT, dArray);


  // -------
  // Process
  // -------

  int    * iPtr = iMask.pCoeffMap();
  float  * fPtr = fMask.pCoeffMap();
  double * dPtr = dMask.pCoeffMap();


  // -----
  // Check
  // -----

  for (int i=0; i < MASK_WIDTH * MASK_HEIGHT; ++i)
    CPPUNIT_ASSERT_EQUAL( iArray[i], iPtr[i] );

  for (int i=0; i < MASK_WIDTH * MASK_HEIGHT; ++i)
    CPPUNIT_ASSERT_EQUAL( fArray[i], fPtr[i] );

  for (int i=0; i < MASK_WIDTH * MASK_HEIGHT; ++i)
    CPPUNIT_ASSERT_EQUAL( dArray[i], dPtr[i] );


  // ---------
  // Tear Down
  // ---------

  delete[] iArray; 
  delete[] fArray;
  delete[] dArray;
}

// -------------------------------------------------------------------

void
GenMask2dTest::testSetCoeff()
{
  // ------
  // Set Up
  // ------

  const int MASK_WIDTH  = 50;
  const int MASK_HEIGHT = 20; 

  int    * iArray;
  float  * fArray;
  double * dArray;
  
  createMaskArray(MASK_WIDTH, MASK_HEIGHT, iArray);
  createMaskArray(MASK_WIDTH, MASK_HEIGHT, fArray);
  createMaskArray(MASK_WIDTH, MASK_HEIGHT, dArray);

  IMask2d iMask(MASK_WIDTH, MASK_HEIGHT, iArray);
  FMask2d fMask(MASK_WIDTH, MASK_HEIGHT, fArray);
  DMask2d dMask(MASK_WIDTH, MASK_HEIGHT, dArray);


  const int LINE = 12;
  const int COL  = 3;
  
  int    iVal = 12;
  float  fVal = 3.14F;
  double dVal = 12.12;
  

  // -------
  // Process
  // -------

  iMask.setCoeff(LINE, COL, iVal);
  fMask.setCoeff(LINE, COL, fVal);
  dMask.setCoeff(LINE, COL, dVal);
  

  // -----
  // Check
  // -----
  
  CPPUNIT_ASSERT_EQUAL( iVal, iMask.coeff(LINE, COL) );
  CPPUNIT_ASSERT_EQUAL( fVal, fMask.coeff(LINE, COL) );
  CPPUNIT_ASSERT_EQUAL( dVal, dMask.coeff(LINE, COL) );

  // ---------
  // Tear Down
  // ---------

  delete[] iArray; 
  delete[] fArray;
  delete[] dArray;
}

// -------------------------------------------------------------------

void
GenMask2dTest::testShallowCopy()
{
  // ------
  // Set Up
  // ------

  const int MASK_WIDTH  = 50;
  const int MASK_HEIGHT = 50; 

  int    * iArray;
  float  * fArray;
  double * dArray;
  
  createMaskArray(MASK_WIDTH, MASK_HEIGHT, iArray);
  createMaskArray(MASK_WIDTH, MASK_HEIGHT, fArray);
  createMaskArray(MASK_WIDTH, MASK_HEIGHT, dArray);


  IMask2d iMask(MASK_WIDTH, MASK_HEIGHT, iArray);
  FMask2d fMask(MASK_WIDTH, MASK_HEIGHT, fArray);
  DMask2d dMask(MASK_WIDTH, MASK_HEIGHT, dArray);



  // -------
  // Process
  // -------

  IMask2d iDupMask = iMask.shallowCopy();
  FMask2d fDupMask = fMask.shallowCopy();
  DMask2d dDupMask = dMask.shallowCopy();


  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( iMask.width(), iDupMask.width() );
  CPPUNIT_ASSERT_EQUAL( iMask.height(), iDupMask.height() );
  CPPUNIT_ASSERT( compare(iMask, iDupMask) );
  CPPUNIT_ASSERT_EQUAL( iMask.pCoeffMap(), iDupMask.pCoeffMap() );

  CPPUNIT_ASSERT_EQUAL( fMask.width(), fDupMask.width() );
  CPPUNIT_ASSERT_EQUAL( fMask.height(), fDupMask.height() );
  CPPUNIT_ASSERT( compare(fMask, fDupMask) );
  CPPUNIT_ASSERT_EQUAL( iMask.pCoeffMap(), iDupMask.pCoeffMap() );

  CPPUNIT_ASSERT_EQUAL( dMask.width(), dDupMask.width() );
  CPPUNIT_ASSERT_EQUAL( dMask.height(), dDupMask.height() );
  CPPUNIT_ASSERT( compare(dMask, dDupMask) );
  CPPUNIT_ASSERT_EQUAL( iMask.pCoeffMap(), iDupMask.pCoeffMap() );


  // ---------
  // Tear Down
  // ---------

  delete[] iArray; 
  delete[] fArray;
  delete[] dArray; 
}

// -------------------------------------------------------------------
