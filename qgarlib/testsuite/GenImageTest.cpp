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
 * @file  GenImageTest.cpp
 * @brief Implementation of class GenImageTest
 *
 *        See file GenImageTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 4, 2003  10:15
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenImageTest.cpp,v 1.5 2005/01/28 15:56:45 masini Exp $ */



// STD
#include <iostream>
// QGAR
#include <qgarlib/GenImage.h>
// QGAR TESTS
#include "GenImageTest.h"



using namespace std;
using namespace qgar;



// -------------------------------------------------------------------
// U N N A M E D   N A M E S P A C E
// -------------------------------------------------------------------
namespace {

/**
 * @brief Creates and initializes a pixmap
 *
 * @param width  The width of the pixmap to be created.
 * @param height The height of the pixmap to be created.
 * @param pixmap A reference on the pointer that will point to the
 *               pixmap.
 */
template<typename T>
void createPixmap(int width, int height, T*& pixmap)
{
  try {
    pixmap = new T[width * height];
  }
  catch(...) {
    cout << "[GenImageTest] Fatal error L" << __LINE__ 
	 << " Could not allocate pixmap " << endl;

    throw;
  }
  
  T val = static_cast<T>(0);
  
  for(int i = 0; i < (width * height); ++i) {
    pixmap[i] = val++;
  }
}


template<typename T, typename U>
bool compare(int width, int height, T* lhs, U* rhs)
{
  bool match = true;

  for (int i=0; (i < (width * height)) && match; ++i) {
    match = ( lhs[i] == rhs[i] );
  }

  return match;
}


// Test if rhs is part of the lhs image starting at (x,y)
template<typename T>
bool compare(int x, int y, 
	     const GenImage<T>& lhs, 
	     const GenImage<T>& rhs)
{
  bool match = true;

  for (int i=0; (i < rhs.width()) && match; ++i) {

    for (int j=0; (j < rhs.height()) && match; ++j) 
      match = ( lhs.pixel(x + i,  y + j) 
		== rhs.pixel(i,j) );
  }
  return match;
}

/**
 * @brief A dummy checking policy class used to test class GenImage.
 *
 * @author Jan Rendek
 * @date   December 4, 2003 17:02
 * @since  Qgar 2.1.1
 */
template <typename T> class TestPolicy
{
public:
  void checkRange(const T* const, int, const BoundingBox&)
  {
    _counter++;
  }

  int callCounter() 
  {
    return _counter;
  }

private:
  int _counter;
};
}

// ------------------------------------------------------------------
// T E S T F I X T U R E   I M P L
// ------------------------------------------------------------------

void
GenImageTest::setUp()
{
  /* EMPTY */
}

// -------------------------------------------------------------------

void
GenImageTest::tearDown()
{
  /* EMPTY */
}


// -------------------------------------------------------------------
// T E S T   F U N C T I O N S
// -------------------------------------------------------------------

void
GenImageTest::testDefaultConstructor()
{
  // -------
  // Process
  // -------
  
  BinaryImage bImg;
  IntImage    iImg;
  FloatImage  fImg;
  DoubleImage dImg;
  

  // -----
  // Check
  // -----
  // Ensure that width and height are initialized to 0.
  // Ensure that bytePerPixel equals the size of the stored type.
  // Ensure that the pointer to the pixmap is initialized to 0.

  CPPUNIT_ASSERT( bImg.width()  == 0 );
  CPPUNIT_ASSERT( bImg.height() == 0 );
  CPPUNIT_ASSERT( bImg.bytesPerPixel() == sizeof(char) );
  CPPUNIT_ASSERT( bImg.pPixMap() == 0 );

  CPPUNIT_ASSERT( iImg.width()  == 0 );
  CPPUNIT_ASSERT( iImg.height() == 0 );
  CPPUNIT_ASSERT( iImg.bytesPerPixel() == sizeof(int) );
  CPPUNIT_ASSERT( iImg.pPixMap() == 0 );

  CPPUNIT_ASSERT( fImg.width()  == 0 );
  CPPUNIT_ASSERT( fImg.height() == 0 );
  CPPUNIT_ASSERT( fImg.bytesPerPixel() == sizeof(float) );
  CPPUNIT_ASSERT( fImg.pPixMap() == 0 );

  CPPUNIT_ASSERT( dImg.width()  == 0 );
  CPPUNIT_ASSERT( dImg.height() == 0 );
  CPPUNIT_ASSERT( dImg.bytesPerPixel() == sizeof(double) );
  CPPUNIT_ASSERT( dImg.pPixMap() == 0 );
}

// -------------------------------------------------------------------

void
GenImageTest::testBuildFromSize()
{
  // ------
  // Set Up
  // ------

  int width  = 400;
  int height = 300;


  // -------
  // Process
  // -------

  BinaryImage bImg(width, height);
  IntImage    iImg(width, height);
  FloatImage  fImg(width, height);
  DoubleImage dImg(width, height);

  
  // -----
  // Check
  // -----
  // Ensure that width and height are correctly initialized
  // Ensure that bytePerPixel equals the size of the stored type.

  CPPUNIT_ASSERT( bImg.width()  == width );
  CPPUNIT_ASSERT( bImg.height() == height );
  CPPUNIT_ASSERT( bImg.bytesPerPixel() == sizeof(char) );

  CPPUNIT_ASSERT( iImg.width()  == width );
  CPPUNIT_ASSERT( iImg.height() == height );
  CPPUNIT_ASSERT( iImg.bytesPerPixel() == sizeof(int) );

  CPPUNIT_ASSERT( fImg.width()  == width );
  CPPUNIT_ASSERT( fImg.height() == height );
  CPPUNIT_ASSERT( fImg.bytesPerPixel() == sizeof(float) );

  CPPUNIT_ASSERT( dImg.width()  == width );
  CPPUNIT_ASSERT( dImg.height() == height );
  CPPUNIT_ASSERT( dImg.bytesPerPixel() == sizeof(double) );
}

// -------------------------------------------------------------------

void
GenImageTest::testBuildFromPixmap()
{
  // ------
  // Set Up
  // ------
  
  int width  = 400;
  int height = 300;
  
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);


  // -------
  // Process
  // -------

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);
  

  // -----
  // Check
  // -----

  // Ensure that width and height are correctly initialized.
  // Ensure that bytes per pixel is correctly initialized.
  // Ensure that the pointer to the image pixmap is equal to the one
  //   used to created it.
  // Ensure that pixmap is equal to the original one.
  CPPUNIT_ASSERT_EQUAL( width,  bImg.width() );
  CPPUNIT_ASSERT_EQUAL( height, bImg.height() );
  CPPUNIT_ASSERT( bImg.bytesPerPixel() == sizeof(char) );
  CPPUNIT_ASSERT( compare(width, height, bImg.pPixMap(), bPixMap) );

  CPPUNIT_ASSERT_EQUAL( width,  bImg.width() );
  CPPUNIT_ASSERT_EQUAL( height, bImg.height() );
  CPPUNIT_ASSERT( iImg.bytesPerPixel() == sizeof(int) );
  CPPUNIT_ASSERT( compare(width, height, iImg.pPixMap(), iPixMap) );

  CPPUNIT_ASSERT_EQUAL( width,  fImg.width() );
  CPPUNIT_ASSERT_EQUAL( height, fImg.height() );
  CPPUNIT_ASSERT( fImg.bytesPerPixel() == sizeof(float) );
  CPPUNIT_ASSERT( compare(width, height, fImg.pPixMap(), fPixMap) );

  CPPUNIT_ASSERT_EQUAL( width,  dImg.width() );
  CPPUNIT_ASSERT_EQUAL( height, dImg.height() );
  CPPUNIT_ASSERT( dImg.bytesPerPixel() == sizeof(double) );
  CPPUNIT_ASSERT( compare(width, height, dImg.pPixMap(), dPixMap) );
}

// -------------------------------------------------------------------

void
GenImageTest::testCopyConstructor()
{
  // ------
  // Set Up
  // ------
  
  int width  = 400;
  int height = 300;
  
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);
  
 
 
  // -------
  // Process
  // -------

  BinaryImage bDupImg(bImg);
  IntImage    iDupImg(iImg);
  FloatImage  fDupImg(fImg);
  DoubleImage dDupImg(dImg);


  // -----
  // Check
  // -----
  // Ensure that width and height are correctly copied.
  // Ensure that bytes per pixel is correctly initialized.
  // Ensure that pixmap of both images are equivalent.
  CPPUNIT_ASSERT_EQUAL( bImg.width(),  bDupImg.width() );
  CPPUNIT_ASSERT_EQUAL( bImg.height(), bDupImg.height() );
  CPPUNIT_ASSERT_EQUAL( bImg.bytesPerPixel(), bDupImg.bytesPerPixel() );
  CPPUNIT_ASSERT( compare(width, height, 
			  bImg.pPixMap(), bDupImg.pPixMap()) );

  CPPUNIT_ASSERT_EQUAL( iImg.width(),  iDupImg.width() );
  CPPUNIT_ASSERT_EQUAL( iImg.height(), iDupImg.height() );
  CPPUNIT_ASSERT_EQUAL( iImg.bytesPerPixel(), iDupImg.bytesPerPixel() );
  CPPUNIT_ASSERT( compare(width, height, 
			  iImg.pPixMap(), iDupImg.pPixMap()) );

  CPPUNIT_ASSERT_EQUAL( fImg.width(),  fDupImg.width() );
  CPPUNIT_ASSERT_EQUAL( fImg.height(), fDupImg.height() );
  CPPUNIT_ASSERT_EQUAL( fImg.bytesPerPixel(), fDupImg.bytesPerPixel() );
  CPPUNIT_ASSERT( compare(width, height, 
			  fImg.pPixMap(), fDupImg.pPixMap()) );

  CPPUNIT_ASSERT_EQUAL( dImg.width(),  dDupImg.width() );
  CPPUNIT_ASSERT_EQUAL( dImg.height(), dDupImg.height() );
  CPPUNIT_ASSERT_EQUAL( dImg.bytesPerPixel(), dDupImg.bytesPerPixel() );
  CPPUNIT_ASSERT( compare(width, height, 
			  dImg.pPixMap(), dDupImg.pPixMap()) );
}

// -------------------------------------------------------------------

void
GenImageTest::testBuildFromDifferentPolicies()
{
  // ------
  // Set Up
  // ------
  
  int width  = 400;
  int height = 300;
  
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);
  
 
 
  // -------
  // Process
  // -------

  GenImage<unsigned char, TestPolicy>  bDupImg(bImg);
  GenImage<int,    TestPolicy> iDupImg(iImg);
  GenImage<float,  TestPolicy> fDupImg(fImg);
  GenImage<double, TestPolicy> dDupImg(dImg);


  // -----
  // Check
  // -----
  // Ensure that width and height are correctly copied.
  // Ensure that bytes per pixel is correctly initialized.
  // Ensure that pixmap of both images are equivalent.
  CPPUNIT_ASSERT_EQUAL( bImg.width(),  bDupImg.width() );
  CPPUNIT_ASSERT_EQUAL( bImg.height(), bDupImg.height() );
  CPPUNIT_ASSERT_EQUAL( bImg.bytesPerPixel(), bDupImg.bytesPerPixel() );
  CPPUNIT_ASSERT( compare(width, height, 
			  bImg.pPixMap(), bDupImg.pPixMap()) );

  CPPUNIT_ASSERT_EQUAL( iImg.width(),  iDupImg.width() );
  CPPUNIT_ASSERT_EQUAL( iImg.height(), iDupImg.height() );
  CPPUNIT_ASSERT_EQUAL( iImg.bytesPerPixel(), iDupImg.bytesPerPixel() );
  CPPUNIT_ASSERT( compare(width, height, 
			  iImg.pPixMap(), iDupImg.pPixMap()) );

  CPPUNIT_ASSERT_EQUAL( fImg.width(),  fDupImg.width() );
  CPPUNIT_ASSERT_EQUAL( fImg.height(), fDupImg.height() );
  CPPUNIT_ASSERT_EQUAL( fImg.bytesPerPixel(), fDupImg.bytesPerPixel() );
  CPPUNIT_ASSERT( compare(width, height, 
			  fImg.pPixMap(), fDupImg.pPixMap()) );

  CPPUNIT_ASSERT_EQUAL( dImg.width(),  dDupImg.width() );
  CPPUNIT_ASSERT_EQUAL( dImg.height(), dDupImg.height() );
  CPPUNIT_ASSERT_EQUAL( dImg.bytesPerPixel(), dDupImg.bytesPerPixel() );
  CPPUNIT_ASSERT( compare(width, height, 
			  dImg.pPixMap(), dDupImg.pPixMap()) );
}

// -------------------------------------------------------------------

void
GenImageTest::testBuildFromConvertedImage()
{
  // ------
  // Set Up
  // ------

  // Warning: For conversion tests to be correct, image size must be
  // less than 256 pixels. (byte limit).
  int width  = 32;
  int height = 8;
  
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);


  // -------
  // Process
  // -------
  
  // Conversion to int
  IntImage b2iImg(bImg);
  
  // Conversion to float
  FloatImage b2fImg(bImg);
  FloatImage i2fImg(iImg);

  // Conversion to double
  DoubleImage b2dImg(bImg);
  DoubleImage i2dImg(iImg);
  DoubleImage f2dImg(fImg);

  
  // -----
  // Check
  // -----
  
  // Check char -> int.
  CPPUNIT_ASSERT_EQUAL( bImg.width(),  b2iImg.width() );
  CPPUNIT_ASSERT_EQUAL( bImg.height(), b2iImg.height() );
  CPPUNIT_ASSERT( b2iImg.bytesPerPixel() == sizeof(int) );
  CPPUNIT_ASSERT( compare(width, height, 
			  b2iImg.pPixMap(), bImg.pPixMap()) );

  // Check char -> float
  CPPUNIT_ASSERT_EQUAL( fImg.width(),  b2fImg.width() );
  CPPUNIT_ASSERT_EQUAL( fImg.height(), b2fImg.height() );
  CPPUNIT_ASSERT( b2fImg.bytesPerPixel() == sizeof(float) );
  CPPUNIT_ASSERT( compare(width, height, 
			  b2fImg.pPixMap(), fImg.pPixMap()) );
  
  // Check int -> float
  CPPUNIT_ASSERT_EQUAL( fImg.width(),  i2fImg.width() );
  CPPUNIT_ASSERT_EQUAL( fImg.height(), i2fImg.height() );
  CPPUNIT_ASSERT( i2fImg.bytesPerPixel() == sizeof(float) );
  CPPUNIT_ASSERT( compare(width, height, 
			  i2fImg.pPixMap(), fImg.pPixMap()) );
  
  // Check char -> double
  CPPUNIT_ASSERT_EQUAL( dImg.width(),  b2dImg.width() );
  CPPUNIT_ASSERT_EQUAL( dImg.height(), b2dImg.height() );
  CPPUNIT_ASSERT( b2dImg.bytesPerPixel() == sizeof(double) );
  CPPUNIT_ASSERT( compare(width, height, 
			  b2dImg.pPixMap(), dImg.pPixMap()) );
  

  // Check int -> double
  CPPUNIT_ASSERT_EQUAL( dImg.width(),  i2dImg.width() );
  CPPUNIT_ASSERT_EQUAL( dImg.height(), i2dImg.height() );
  CPPUNIT_ASSERT( i2dImg.bytesPerPixel() == sizeof(double) );
  CPPUNIT_ASSERT( compare(width, height, 
			  i2dImg.pPixMap(), dImg.pPixMap()) );

  // Check float -> double
  CPPUNIT_ASSERT_EQUAL( dImg.width(),  f2dImg.width() );
  CPPUNIT_ASSERT_EQUAL( dImg.height(), f2dImg.height() );
  CPPUNIT_ASSERT( f2dImg.bytesPerPixel() == sizeof(double) );
  CPPUNIT_ASSERT( compare(width, height, 
			  f2dImg.pPixMap(), dImg.pPixMap()) );
}


// -------------------------------------------------------------------

void
GenImageTest::testBuildFromBox()
{
  // ------
  // Set Up
  // ------
  
  // Image size
  int width = 300;
  int height = 200;


  // Box
  int x0 = 2;
  int y0 = 5;
  int x1 = 98;
  int y1 = 29;
  BoundingBox box(x0, y0, x1, y1);
    

  // Create images
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);


  // -------
  // Process
  // -------

  BinaryImage bBoxImg(bImg, box);
  IntImage    iBoxImg(iImg, box);
  FloatImage  fBoxImg(fImg, box);
  DoubleImage dBoxImg(dImg, box);

  
  // -----
  // Check
  // -----

  // char img
  CPPUNIT_ASSERT_EQUAL( bBoxImg.width(),  box.width() );
  CPPUNIT_ASSERT_EQUAL( bBoxImg.height(), box.height() );
  CPPUNIT_ASSERT( bBoxImg.bytesPerPixel() == sizeof(char) );
  CPPUNIT_ASSERT( compare(x0, y0, bImg, bBoxImg) );

  // Int img
  CPPUNIT_ASSERT_EQUAL( iBoxImg.width(),  box.width() );
  CPPUNIT_ASSERT_EQUAL( iBoxImg.height(), box.height() );
  CPPUNIT_ASSERT( iBoxImg.bytesPerPixel() == sizeof(int) );
  CPPUNIT_ASSERT( compare(x0, y0, iImg, iBoxImg) );

  // float img
  CPPUNIT_ASSERT_EQUAL( fBoxImg.width(),  box.width() );
  CPPUNIT_ASSERT_EQUAL( fBoxImg.height(), box.height() );
  CPPUNIT_ASSERT( fBoxImg.bytesPerPixel() == sizeof(float) );
  CPPUNIT_ASSERT( compare(x0, y0, fImg, fBoxImg) );

  // double img
  CPPUNIT_ASSERT_EQUAL( dBoxImg.width(),  box.width() );
  CPPUNIT_ASSERT_EQUAL( dBoxImg.height(), box.height() );
  CPPUNIT_ASSERT( dBoxImg.bytesPerPixel() == sizeof(double) );
  CPPUNIT_ASSERT( compare(x0, y0, dImg, dBoxImg) );
}

// -------------------------------------------------------------------

void
GenImageTest::testBuildFromBoxCoords()
{
  // ------
  // Set Up
  // ------
  
  // Image size
  int width = 300;
  int height = 200;


  // Box
  int x0 = 25;
  int y0 = 10;
  int x1 = 100;
  int y1 = 89;
    

  // Create images
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);


  // -------
  // Process
  // -------

  BinaryImage bBoxImg(bImg, x0, y0, x1, y1);
  IntImage    iBoxImg(iImg, x0, y0, x1, y1);
  FloatImage  fBoxImg(fImg, x0, y0, x1, y1);
  DoubleImage dBoxImg(dImg, x0, y0, x1, y1);

  
  // -----
  // Check
  // -----

  // char img
  CPPUNIT_ASSERT_EQUAL( bBoxImg.width(),  (x1 - x0 + 1) );
  CPPUNIT_ASSERT_EQUAL( bBoxImg.height(), (y1 - y0 + 1) );
  CPPUNIT_ASSERT( bBoxImg.bytesPerPixel() == sizeof(char) );
  CPPUNIT_ASSERT( compare(x0, y0, bImg, bBoxImg) );

  // Int img
  CPPUNIT_ASSERT_EQUAL( iBoxImg.width(),  (x1 - x0 + 1) );
  CPPUNIT_ASSERT_EQUAL( iBoxImg.height(), (y1 - y0 + 1) );
  CPPUNIT_ASSERT( iBoxImg.bytesPerPixel() == sizeof(int) );
  CPPUNIT_ASSERT( compare(x0, y0, iImg, iBoxImg) );

  // float img
  CPPUNIT_ASSERT_EQUAL( fBoxImg.width(),  (x1 - x0 + 1)  );
  CPPUNIT_ASSERT_EQUAL( fBoxImg.height(), (y1 - y0 + 1) );
  CPPUNIT_ASSERT( fBoxImg.bytesPerPixel() == sizeof(float) );
  CPPUNIT_ASSERT( compare(x0, y0, fImg, fBoxImg) );

  // double img
  CPPUNIT_ASSERT_EQUAL( dBoxImg.width(),  (x1 - x0 + 1) );
  CPPUNIT_ASSERT_EQUAL( dBoxImg.height(), (y1 - y0 + 1) );
  CPPUNIT_ASSERT( dBoxImg.bytesPerPixel() == sizeof(double) );
  CPPUNIT_ASSERT( compare(x0, y0, dImg, dBoxImg) );
}

// -------------------------------------------------------------------

void
GenImageTest::testRow()
{
  // ------
  // Set Up
  // ------

  // Copied row
  const int rowNb = 5;

  // Image size
  const int width = 300;
  const int height = 200;


  // Create images
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);

  // Create Empty rows
  unsigned char bRow[width];
  int    iRow[width];
  float  fRow[width];
  double dRow[width];


  // -------
  // Process
  // -------

  bImg.row(rowNb, bRow);
  iImg.row(rowNb, iRow);
  fImg.row(rowNb, fRow);
  dImg.row(rowNb, dRow);
  

  // -----
  // Check
  // -----

  // Byte images
  for(int i=0; i < width; ++i) {
    CPPUNIT_ASSERT_EQUAL( bRow[i], bImg.pixel(i, rowNb) );
  }

  // Int images
  for(int i=0; i < width; ++i) {
    CPPUNIT_ASSERT_EQUAL( iRow[i], iImg.pixel(i, rowNb) );
  }

  // Float images
  for(int i=0; i < width; ++i) {
    CPPUNIT_ASSERT_EQUAL( fRow[i], fImg.pixel(i, rowNb) );
  }

  // Double images
  for(int i=0; i < width; ++i) {
    CPPUNIT_ASSERT_EQUAL( dRow[i], dImg.pixel(i, rowNb) );
  }
}

// -------------------------------------------------------------------

void
GenImageTest::testColumn()
{
  // ------
  // Set Up
  // ------

  // Copied col
  const int colNb = 24;

  // Image size
  const int width = 300;
  const int height = 200;


  // Create images
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);

  // Create Empty cols
  unsigned char bCol[height];
  int    iCol[height];
  float  fCol[height];
  double dCol[height];


  // -------
  // Process
  // -------

  bImg.column(colNb, bCol);
  iImg.column(colNb, iCol);
  fImg.column(colNb, fCol);
  dImg.column(colNb, dCol);
  

  // -----
  // Check
  // -----

  // Byte images
  for(int i=0; i < height; ++i) {
    CPPUNIT_ASSERT_EQUAL( bCol[i], bImg.pixel(colNb, i) );
  }

  // Int images
  for(int i=0; i < height; ++i) {
    CPPUNIT_ASSERT_EQUAL( iCol[i], iImg.pixel(colNb, i) );
  }

  // Float images
  for(int i=0; i < height; ++i) {
    CPPUNIT_ASSERT_EQUAL( fCol[i], fImg.pixel(colNb, i) );
  }

  // Double images
  for(int i=0; i < height; ++i) {
    CPPUNIT_ASSERT_EQUAL( dCol[i], dImg.pixel(colNb, i) );
  }
}

// -------------------------------------------------------------------

void
GenImageTest::testPRow()
{
  // ------
  // Set Up
  // ------

  // Copied row
  const int rowNb = 5;

  // Image size
  const int width = 300;
  const int height = 200;


  // Create images
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);


  // -------
  // Process
  // -------

  unsigned char * bpRow = bImg.pRow(rowNb);
  int    * ipRow = iImg.pRow(rowNb);
  float  * fpRow = fImg.pRow(rowNb);
  double * dpRow = dImg.pRow(rowNb);
  

  // -----
  // Check
  // -----

  // Byte images
  for(int i=0; i < width; ++i) {
    CPPUNIT_ASSERT_EQUAL( bpRow[i], bImg.pixel(i, rowNb) );
  }

  // Int images
  for(int i=0; i < width; ++i) {
    CPPUNIT_ASSERT_EQUAL( ipRow[i], iImg.pixel(i, rowNb) );
  }

  // Float images
  for(int i=0; i < width; ++i) {
    CPPUNIT_ASSERT_EQUAL( fpRow[i], fImg.pixel(i, rowNb) );
  }

  // Double images
  for(int i=0; i < width; ++i) {
    CPPUNIT_ASSERT_EQUAL( dpRow[i], dImg.pixel(i, rowNb) );
  }
}

// -------------------------------------------------------------------

void
GenImageTest::testPColumn()
{
  // ------
  // Set Up
  // ------

  // Copied col
  const int colNb = 24;

  // Image size
  const int width = 300;
  const int height = 200;


  // Create images
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);


  // -------
  // Process
  // -------

  // Create Empty cols
  unsigned char * bpCol = bImg.pColumn(colNb);
  int    * ipCol = iImg.pColumn(colNb);
  float  * fpCol = fImg.pColumn(colNb);
  double * dpCol = dImg.pColumn(colNb);


  // -----
  // Check
  // -----

  // Byte images
  for(int i=0; i < height; ++i) {
    CPPUNIT_ASSERT_EQUAL( bpCol[i*width], bImg.pixel(colNb, i) );
  }

  // Int images
  for(int i=0; i < height; ++i) {
    CPPUNIT_ASSERT_EQUAL( ipCol[i*width], iImg.pixel(colNb, i) );
  }

  // Float images
  for(int i=0; i < height; ++i) {
    CPPUNIT_ASSERT_EQUAL( fpCol[i*width], fImg.pixel(colNb, i) );
  }

  // Double images
  for(int i=0; i < height; ++i) {
    CPPUNIT_ASSERT_EQUAL( dpCol[i*width], dImg.pixel(colNb, i) );
  }
}

// -------------------------------------------------------------------

void
GenImageTest::testSetPixel()
{
  // ------
  // Set Up
  // ------

  // Image size
  const int width = 300;
  const int height = 200;

  // Create images
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);


  // Pixel position
  int col  = 217;
  int line = 100;

  // Pix Value
  unsigned char bPix = 47;
  int    iPix = 9874;
  float  fPix = 1.9084F;
  double dPix = 4.982;


  // -------
  // Process
  // -------
  
  bImg.setPixel(col, line, bPix);
  iImg.setPixel(col, line, iPix);
  fImg.setPixel(col, line, fPix);
  dImg.setPixel(col, line, dPix);

  
  // -----
  // Check
  // -----
  
  CPPUNIT_ASSERT_EQUAL( bPix, bImg.pixel(col, line) );
  CPPUNIT_ASSERT_EQUAL( iPix, iImg.pixel(col, line) );
  CPPUNIT_ASSERT_EQUAL( fPix, fImg.pixel(col, line) );
  CPPUNIT_ASSERT_EQUAL( dPix, dImg.pixel(col, line) );
}

// -------------------------------------------------------------------

void
GenImageTest::testSetRow()
{
  // ------
  // Set Up
  // ------

  // Row to be updated
  const int rowNb = 51;

  // Image size
  const int width = 300;
  const int height = 200;

  // Create images
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);

  // Create rows
  unsigned char * bRow;
  int    * iRow;
  float  * fRow;
  double * dRow;

  createPixmap(width, 1, bRow);
  createPixmap(width, 1, iRow);
  createPixmap(width, 1, fRow);
  createPixmap(width, 1, dRow);


  // -------
  // Process
  // -------

  bImg.setRow(rowNb, bRow);
  iImg.setRow(rowNb, iRow);
  fImg.setRow(rowNb, fRow);
  dImg.setRow(rowNb, dRow);
  

  // -----
  // Check
  // -----

  // Byte images
  for(int i=0; i < width; ++i) {
    CPPUNIT_ASSERT_EQUAL( bRow[i], bImg.pixel(i, rowNb) );
  }

  // Int images
  for(int i=0; i < width; ++i) {
    CPPUNIT_ASSERT_EQUAL( iRow[i], iImg.pixel(i, rowNb) );
  }

  // Float images
  for(int i=0; i < width; ++i) {
    CPPUNIT_ASSERT_EQUAL( fRow[i], fImg.pixel(i, rowNb) );
  }

  // Double images
  for(int i=0; i < width; ++i) {
    CPPUNIT_ASSERT_EQUAL( dRow[i], dImg.pixel(i, rowNb) );
  }
  

  // ---------
  // Tear Down
  // ---------

  delete[] bRow;
  delete[] iRow;
  delete[] fRow;
  delete[] dRow;
}

// -------------------------------------------------------------------

void
GenImageTest::testSetColumn()
{
  // ------
  // Set Up
  // ------

  // Col to be updated
  const int colNb = 51;

  // Image size
  const int width = 300;
  const int height = 200;

  // Create images
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);

  // Create cols
  unsigned char * bCol;
  int    * iCol;
  float  * fCol;
  double * dCol;

  createPixmap(height, 1, bCol);
  createPixmap(height, 1, iCol);
  createPixmap(height, 1, fCol);
  createPixmap(height, 1, dCol);


  // -------
  // Process
  // -------

  bImg.setColumn(colNb, bCol);
  iImg.setColumn(colNb, iCol);
  fImg.setColumn(colNb, fCol);
  dImg.setColumn(colNb, dCol);
  

  // -----
  // Check
  // -----

  // Byte images
  for(int i=0; i < height; ++i) {
    CPPUNIT_ASSERT_EQUAL( bCol[i], bImg.pixel(colNb, i) );
  }

  // Int images
  for(int i=0; i < height; ++i) {
    CPPUNIT_ASSERT_EQUAL( iCol[i], iImg.pixel(colNb, i) );
  }

  // Float images
  for(int i=0; i < height; ++i) {
    CPPUNIT_ASSERT_EQUAL( fCol[i], fImg.pixel(colNb, i) );
  }

  // Double images
  for(int i=0; i < height; ++i) {
    CPPUNIT_ASSERT_EQUAL( dCol[i], dImg.pixel(colNb, i) );
  }
  

  // ---------
  // Tear Down
  // ---------

  delete[] bCol;
  delete[] iCol;
  delete[] fCol;
  delete[] dCol;

}

// -------------------------------------------------------------------

void
GenImageTest::testDrawSegment()
{
  // ------
  // Set Up
  // ------

  // -------
  // Process
  // -------
  
  // -----
  // Check
  // -----
//   CPPUNIT_FAIL("Not implemented");
}

// -------------------------------------------------------------------

void
GenImageTest::testShallowCopy()
{
  // ------
  // Set Up
  // ------
  
  int width  = 400;
  int height = 300;
  
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);
  
 
 
  // -------
  // Process
  // -------

  BinaryImage bDupImg = bImg.shallowCopy();
  IntImage    iDupImg = iImg.shallowCopy();
  FloatImage  fDupImg = fImg.shallowCopy();
  DoubleImage dDupImg = dImg.shallowCopy();


  // -----
  // Check
  // -----
  // Ensure that width and height are correctly copied.
  // Ensure that bytes per pixel is correctly initialized.
  // Ensure that pixmap of both images are equivalent.
  CPPUNIT_ASSERT_EQUAL( bImg.width(),  bDupImg.width() );
  CPPUNIT_ASSERT_EQUAL( bImg.height(), bDupImg.height() );
  CPPUNIT_ASSERT_EQUAL( bImg.bytesPerPixel(), bDupImg.bytesPerPixel() );
  CPPUNIT_ASSERT( compare(width, height, 
			  bImg.pPixMap(), bDupImg.pPixMap()) );

  CPPUNIT_ASSERT_EQUAL( iImg.width(),  iDupImg.width() );
  CPPUNIT_ASSERT_EQUAL( iImg.height(), iDupImg.height() );
  CPPUNIT_ASSERT_EQUAL( iImg.bytesPerPixel(), iDupImg.bytesPerPixel() );
  CPPUNIT_ASSERT( compare(width, height, 
			  iImg.pPixMap(), iDupImg.pPixMap()) );

  CPPUNIT_ASSERT_EQUAL( fImg.width(),  fDupImg.width() );
  CPPUNIT_ASSERT_EQUAL( fImg.height(), fDupImg.height() );
  CPPUNIT_ASSERT_EQUAL( fImg.bytesPerPixel(), fDupImg.bytesPerPixel() );
  CPPUNIT_ASSERT( compare(width, height, 
			  fImg.pPixMap(), fDupImg.pPixMap()) );

  CPPUNIT_ASSERT_EQUAL( dImg.width(),  dDupImg.width() );
  CPPUNIT_ASSERT_EQUAL( dImg.height(), dDupImg.height() );
  CPPUNIT_ASSERT_EQUAL( dImg.bytesPerPixel(), dDupImg.bytesPerPixel() );
  CPPUNIT_ASSERT( compare(width, height, 
			  dImg.pPixMap(), dDupImg.pPixMap()) );
}

// -------------------------------------------------------------------

void
GenImageTest::testAssignment()
{
  // ------
  // Set Up
  // ------
  
  int width  = 400;
  int height = 300;
  
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);
  
  
  // -------
  // Process
  // -------

  BinaryImage bDupImg;
  IntImage    iDupImg;
  FloatImage  fDupImg;
  DoubleImage dDupImg;

  bDupImg = bImg;
  iDupImg = iImg;
  fDupImg = fImg;
  dDupImg = dImg;


  // -----
  // Check
  // -----
  // Ensure that width and height are correctly copied.
  // Ensure that bytes per pixel is correctly initialized.
  // Ensure that pixmap of both images are equivalent.
  CPPUNIT_ASSERT_EQUAL( bImg.width(),  bDupImg.width() );
  CPPUNIT_ASSERT_EQUAL( bImg.height(), bDupImg.height() );
  CPPUNIT_ASSERT_EQUAL( bImg.bytesPerPixel(), bDupImg.bytesPerPixel() );
  CPPUNIT_ASSERT( compare(width, height, 
			  bImg.pPixMap(), bDupImg.pPixMap()) );
  CPPUNIT_ASSERT( &bDupImg == &(bDupImg = bImg) );

  CPPUNIT_ASSERT_EQUAL( iImg.width(),  iDupImg.width() );
  CPPUNIT_ASSERT_EQUAL( iImg.height(), iDupImg.height() );
  CPPUNIT_ASSERT_EQUAL( iImg.bytesPerPixel(), iDupImg.bytesPerPixel() );
  CPPUNIT_ASSERT( compare(width, height, 
			  iImg.pPixMap(), iDupImg.pPixMap()) );
  CPPUNIT_ASSERT( &iDupImg == &(iDupImg = iImg) );

  CPPUNIT_ASSERT_EQUAL( fImg.width(),  fDupImg.width() );
  CPPUNIT_ASSERT_EQUAL( fImg.height(), fDupImg.height() );
  CPPUNIT_ASSERT_EQUAL( fImg.bytesPerPixel(), fDupImg.bytesPerPixel() );
  CPPUNIT_ASSERT( compare(width, height, 
			  fImg.pPixMap(), fDupImg.pPixMap()) );
  CPPUNIT_ASSERT( &fDupImg == &(fDupImg = fImg) );

  CPPUNIT_ASSERT_EQUAL( dImg.width(),  dDupImg.width() );
  CPPUNIT_ASSERT_EQUAL( dImg.height(), dDupImg.height() );
  CPPUNIT_ASSERT_EQUAL( dImg.bytesPerPixel(), dDupImg.bytesPerPixel() );
  CPPUNIT_ASSERT( compare(width, height, 
			  dImg.pPixMap(), dDupImg.pPixMap()) );
  CPPUNIT_ASSERT( &fDupImg == &(fDupImg = fImg) );
}

// -------------------------------------------------------------------

void
GenImageTest::testAssignFromImgWithOtherPolicies()
{
  // ------
  // Set Up
  // ------
  
  int width  = 400;
  int height = 300;
  
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  GenImage<unsigned char, TestPolicy> bImg(width, height, bPixMap);
  GenImage<int,    TestPolicy> iImg(width, height, iPixMap);
  GenImage<float,  TestPolicy> fImg(width, height, fPixMap);
  GenImage<double, TestPolicy> dImg(width, height, dPixMap);
  
  
  // -------
  // Process
  // -------

  BinaryImage bDupImg;
  IntImage    iDupImg;
  FloatImage  fDupImg;
  DoubleImage dDupImg;

  bDupImg = bImg;
  iDupImg = iImg;
  fDupImg = fImg;
  dDupImg = dImg;


  // -----
  // Check
  // -----
  // Ensure that width and height are correctly copied.
  // Ensure that bytes per pixel is correctly initialized.
  // Ensure that pixmap of both images are equivalent.
  CPPUNIT_ASSERT_EQUAL( bImg.width(),  bDupImg.width() );
  CPPUNIT_ASSERT_EQUAL( bImg.height(), bDupImg.height() );
  CPPUNIT_ASSERT_EQUAL( bImg.bytesPerPixel(), bDupImg.bytesPerPixel() );
  CPPUNIT_ASSERT( compare(width, height, 
			  bImg.pPixMap(), bDupImg.pPixMap()) );
  CPPUNIT_ASSERT( &bDupImg == &(bDupImg = bImg) );

  CPPUNIT_ASSERT_EQUAL( iImg.width(),  iDupImg.width() );
  CPPUNIT_ASSERT_EQUAL( iImg.height(), iDupImg.height() );
  CPPUNIT_ASSERT_EQUAL( iImg.bytesPerPixel(), iDupImg.bytesPerPixel() );
  CPPUNIT_ASSERT( compare(width, height, 
			  iImg.pPixMap(), iDupImg.pPixMap()) );
  CPPUNIT_ASSERT( &iDupImg == &(iDupImg = iImg) );

  CPPUNIT_ASSERT_EQUAL( fImg.width(),  fDupImg.width() );
  CPPUNIT_ASSERT_EQUAL( fImg.height(), fDupImg.height() );
  CPPUNIT_ASSERT_EQUAL( fImg.bytesPerPixel(), fDupImg.bytesPerPixel() );
  CPPUNIT_ASSERT( compare(width, height, 
			  fImg.pPixMap(), fDupImg.pPixMap()) );
  CPPUNIT_ASSERT( &fDupImg == &(fDupImg = fImg) );

  CPPUNIT_ASSERT_EQUAL( dImg.width(),  dDupImg.width() );
  CPPUNIT_ASSERT_EQUAL( dImg.height(), dDupImg.height() );
  CPPUNIT_ASSERT_EQUAL( dImg.bytesPerPixel(), dDupImg.bytesPerPixel() );
  CPPUNIT_ASSERT( compare(width, height, 
			  dImg.pPixMap(), dDupImg.pPixMap()) );
  CPPUNIT_ASSERT( &fDupImg == &(fDupImg = fImg) );
}

// -------------------------------------------------------------------

void
GenImageTest::testOpPlus()
{
  // ------
  // Set Up
  // ------
  
  int width  = 50;
  int height = 20;
  
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);


  // -------
  // Process
  // -------
  
  BinaryImage bResImg = bImg + bImg;
  IntImage    iResImg = iImg + iImg;
  FloatImage  fResImg = fImg + fImg;
  DoubleImage dResImg = dImg + dImg;


  // -----
  // Check
  // -----

  // Byte images
  unsigned char * bpResPix = bResImg.pPixMap();
  for (int i=0; i < width * height; ++i)
    CPPUNIT_ASSERT_EQUAL(*bpResPix++, 
 			 static_cast<unsigned char>(bPixMap[i] + bPixMap[i]));

  // Int images
  int * ipResPix = iResImg.pPixMap();
  for (int i=0; i < width * height; ++i)
    CPPUNIT_ASSERT_EQUAL(*ipResPix++, 
			 static_cast<int>(iPixMap[i] + iPixMap[i]));

  // Byte images
  float * fpResPix = fResImg.pPixMap();
  for (int i=0; i < width * height; ++i)
    CPPUNIT_ASSERT_EQUAL(*fpResPix++, 
 			 static_cast<float>(fPixMap[i] + fPixMap[i]));

  // Byte images
  double * dpResPix = dResImg.pPixMap();
  for (int i=0; i < width * height; ++i)
    CPPUNIT_ASSERT_EQUAL(*dpResPix++, 
 			 static_cast<double>(dPixMap[i] + dPixMap[i]));
}

// -------------------------------------------------------------------

void
GenImageTest::testOpPlusEqual()
{
  // ------
  // Set Up
  // ------
  
  int width  = 50;
  int height = 20;
  
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);

  // Duplicate images
  BinaryImage bDupImg(bImg);
  IntImage    iDupImg(iImg);
  FloatImage  fDupImg(fImg);
  DoubleImage dDupImg(dImg);


  // -------
  // Process
  // -------
  
  bImg += bImg;
  iImg += iImg;
  fImg += fImg;
  dImg += dImg;


  // -----
  // Check
  // -----

  // Byte images
  unsigned char * bpResPix = bDupImg.pPixMap();
  for (int i=0; i < width * height; ++i, bpResPix++)
    CPPUNIT_ASSERT_EQUAL(static_cast<unsigned char>(*bpResPix + *bpResPix), 
 			 bPixMap[i]);
  
  // Int images
  int * ipResPix = iDupImg.pPixMap();
  for (int i=0; i < width * height; ++i, ipResPix++)
    CPPUNIT_ASSERT_EQUAL( static_cast<int>(*ipResPix + *ipResPix), 
			  iPixMap[i]);

  // Float images
  float * fpResPix = fDupImg.pPixMap();
  for (int i=0; i < width * height; ++i, fpResPix++)
    CPPUNIT_ASSERT_EQUAL( static_cast<float>(*fpResPix + *fpResPix), 
			  fPixMap[i]);

  // Double images
  double * dpResPix = dDupImg.pPixMap();
  for (int i=0; i < width * height; ++i, dpResPix++)
    CPPUNIT_ASSERT_EQUAL( static_cast<double>(*dpResPix + *dpResPix), 
			  dPixMap[i]);

  // Ensure that function member returns a valid reference on 'this'
  CPPUNIT_ASSERT( &bDupImg == &(bDupImg += bImg) );
}

// -------------------------------------------------------------------

void
GenImageTest::testOpMinus()
{
  // ------
  // Set Up
  // ------
  
  int width  = 50;
  int height = 20;
  
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);


  // -------
  // Process
  // -------
  
  BinaryImage bResImg = bImg - bImg;
  IntImage    iResImg = iImg - iImg;
  FloatImage  fResImg = fImg - fImg;
  DoubleImage dResImg = dImg - dImg;


  // -----
  // Check
  // -----

  // Byte images
  unsigned char * bpResPix = bResImg.pPixMap();
  for (int i=0; i < width * height; ++i)
    CPPUNIT_ASSERT_EQUAL(*bpResPix++, 
 			 static_cast<unsigned char>(bPixMap[i] - bPixMap[i]));

  // Int images
  int * ipResPix = iResImg.pPixMap();
  for (int i=0; i < width * height; ++i)
    CPPUNIT_ASSERT_EQUAL(*ipResPix++, 
			 static_cast<int>(iPixMap[i] - iPixMap[i]));

  // Byte images
  float * fpResPix = fResImg.pPixMap();
  for (int i=0; i < width * height; ++i)
    CPPUNIT_ASSERT_EQUAL(*fpResPix++, 
 			 static_cast<float>(fPixMap[i] - fPixMap[i]));

  // Byte images
  double * dpResPix = dResImg.pPixMap();
  for (int i=0; i < width * height; ++i)
    CPPUNIT_ASSERT_EQUAL(*dpResPix++, 
 			 static_cast<double>(dPixMap[i] - dPixMap[i]));
}

// -------------------------------------------------------------------

void
GenImageTest::testOpMinusEqual()
{
  // ------
  // Set Up
  // ------
  
  int width  = 50;
  int height = 20;
  
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);

  // Duplicate images
  BinaryImage bDupImg(bImg);
  IntImage    iDupImg(iImg);
  FloatImage  fDupImg(fImg);
  DoubleImage dDupImg(dImg);


  // -------
  // Process
  // -------
  
  bImg -= bImg;
  iImg -= iImg;
  fImg -= fImg;
  dImg -= dImg;


  // -----
  // Check
  // -----

  // Byte images
  unsigned char * bpResPix = bDupImg.pPixMap();
  for (int i=0; i < width * height; ++i, bpResPix++)
    CPPUNIT_ASSERT_EQUAL(static_cast<unsigned char>(*bpResPix - *bpResPix), 
 			 bPixMap[i]);
  
  // Int images
  int * ipResPix = iDupImg.pPixMap();
  for (int i=0; i < width * height; ++i, ipResPix++)
    CPPUNIT_ASSERT_EQUAL( static_cast<int>(*ipResPix - *ipResPix), 
			  iPixMap[i]);

  // Float images
  float * fpResPix = fDupImg.pPixMap();
  for (int i=0; i < width * height; ++i, fpResPix++)
    CPPUNIT_ASSERT_EQUAL( static_cast<float>(*fpResPix - *fpResPix), 
			  fPixMap[i]);

  // Double images
  double * dpResPix = dDupImg.pPixMap();
  for (int i=0; i < width * height; ++i, dpResPix++)
    CPPUNIT_ASSERT_EQUAL( static_cast<double>(*dpResPix - *dpResPix), 
			  dPixMap[i]);

  // Ensure that function member returns a valid reference on 'this'
  CPPUNIT_ASSERT( &bDupImg == &(bDupImg -= bImg) );
}

// -------------------------------------------------------------------

void
GenImageTest::testOpMul()
{
  // ------
  // Set Up
  // ------
  
  int width  = 50;
  int height = 20;
  
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);


  // -------
  // Process
  // -------
  
  BinaryImage bResImg = bImg * bImg;
  IntImage    iResImg = iImg * iImg;
  FloatImage  fResImg = fImg * fImg;
  DoubleImage dResImg = dImg * dImg;


  // -----
  // Check
  // -----

  // Byte images
  unsigned char * bpResPix = bResImg.pPixMap();
  for (int i=0; i < width * height; ++i)
    CPPUNIT_ASSERT_EQUAL(*bpResPix++, 
 			 static_cast<unsigned char>(bPixMap[i] * bPixMap[i]));

  // Int images
  int * ipResPix = iResImg.pPixMap();
  for (int i=0; i < width * height; ++i)
    CPPUNIT_ASSERT_EQUAL(*ipResPix++, 
			 static_cast<int>(iPixMap[i] * iPixMap[i]));

  // Byte images
  float * fpResPix = fResImg.pPixMap();
  for (int i=0; i < width * height; ++i)
    CPPUNIT_ASSERT_EQUAL(*fpResPix++, 
 			 static_cast<float>(fPixMap[i] * fPixMap[i]));

  // Byte images
  double * dpResPix = dResImg.pPixMap();
  for (int i=0; i < width * height; ++i)
    CPPUNIT_ASSERT_EQUAL(*dpResPix++, 
 			 static_cast<double>(dPixMap[i] * dPixMap[i]));
}

// -------------------------------------------------------------------

void
GenImageTest::testOpMulEqual()
{
  // ------
  // Set Up
  // ------
  
  int width  = 50;
  int height = 20;
  
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);

  // Duplicate images
  BinaryImage bDupImg(bImg);
  IntImage    iDupImg(iImg);
  FloatImage  fDupImg(fImg);
  DoubleImage dDupImg(dImg);


  // -------
  // Process
  // -------
  
  bImg *= bImg;
  iImg *= iImg;
  fImg *= fImg;
  dImg *= dImg;


  // -----
  // Check
  // -----

  // Byte images
  unsigned char * bpResPix = bDupImg.pPixMap();
  for (int i=0; i < width * height; ++i, bpResPix++)
    CPPUNIT_ASSERT_EQUAL(static_cast<unsigned char>(*bpResPix * *bpResPix), 
 			 bPixMap[i]);
  
  // Int images
  int * ipResPix = iDupImg.pPixMap();
  for (int i=0; i < width * height; ++i, ipResPix++)
    CPPUNIT_ASSERT_EQUAL( static_cast<int>(*ipResPix * *ipResPix), 
			  iPixMap[i]);

  // Float images
  float * fpResPix = fDupImg.pPixMap();
  for (int i=0; i < width * height; ++i, fpResPix++)
    CPPUNIT_ASSERT_EQUAL( static_cast<float>(*fpResPix * *fpResPix), 
			  fPixMap[i]);

  // Double images
  double * dpResPix = dDupImg.pPixMap();
  for (int i=0; i < width * height; ++i, dpResPix++)
    CPPUNIT_ASSERT_EQUAL( static_cast<double>(*dpResPix * *dpResPix), 
			  dPixMap[i]);

  // Ensure that function member returns a valid reference on 'this'
  CPPUNIT_ASSERT( &bDupImg == &(bDupImg *= bImg) );
}

// -------------------------------------------------------------------

void
GenImageTest::testPlus()
{
  // ------
  // Set Up
  // ------
  
  int width  = 50;
  int height = 20;
  
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);


  // -------
  // Process
  // -------
  
  BinaryImage bResImg = bImg.plus(bImg);
  IntImage    iResImg = iImg.plus(iImg);
  FloatImage  fResImg = fImg.plus(fImg);
  DoubleImage dResImg = dImg.plus(dImg);


  // -----
  // Check
  // -----

  // Byte images
  unsigned char * bpResPix = bResImg.pPixMap();
  for (int i=0; i < width * height; ++i)
    CPPUNIT_ASSERT_EQUAL(*bpResPix++, 
 			 static_cast<unsigned char>(bPixMap[i] + bPixMap[i]));

  // Int images
  int * ipResPix = iResImg.pPixMap();
  for (int i=0; i < width * height; ++i)
    CPPUNIT_ASSERT_EQUAL(*ipResPix++, 
			 static_cast<int>(iPixMap[i] + iPixMap[i]));

  // Byte images
  float * fpResPix = fResImg.pPixMap();
  for (int i=0; i < width * height; ++i)
    CPPUNIT_ASSERT_EQUAL(*fpResPix++, 
 			 static_cast<float>(fPixMap[i] + fPixMap[i]));

  // Byte images
  double * dpResPix = dResImg.pPixMap();
  for (int i=0; i < width * height; ++i)
    CPPUNIT_ASSERT_EQUAL(*dpResPix++, 
 			 static_cast<double>(dPixMap[i] + dPixMap[i]));
}

// -------------------------------------------------------------------

void
GenImageTest::testPlusEqual()
{
  // ------
  // Set Up
  // ------
  
  int width  = 50;
  int height = 20;
  
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);

  // Duplicate images
  BinaryImage bDupImg(bImg);
  IntImage    iDupImg(iImg);
  FloatImage  fDupImg(fImg);
  DoubleImage dDupImg(dImg);


  // -------
  // Process
  // -------
  
  bImg.plusEqual(bImg);
  iImg.plusEqual(iImg);
  fImg.plusEqual(fImg);
  dImg.plusEqual(dImg);


  // -----
  // Check
  // -----

  // Byte images
  unsigned char * bpResPix = bDupImg.pPixMap();
  for (int i=0; i < width * height; ++i, bpResPix++)
    CPPUNIT_ASSERT_EQUAL(static_cast<unsigned char>(*bpResPix + *bpResPix), 
 			 bPixMap[i]);
  
  // Int images
  int * ipResPix = iDupImg.pPixMap();
  for (int i=0; i < width * height; ++i, ipResPix++)
    CPPUNIT_ASSERT_EQUAL( static_cast<int>(*ipResPix + *ipResPix), 
			  iPixMap[i]);

  // Float images
  float * fpResPix = fDupImg.pPixMap();
  for (int i=0; i < width * height; ++i, fpResPix++)
    CPPUNIT_ASSERT_EQUAL( static_cast<float>(*fpResPix + *fpResPix), 
			  fPixMap[i]);

  // Double images
  double * dpResPix = dDupImg.pPixMap();
  for (int i=0; i < width * height; ++i, dpResPix++)
    CPPUNIT_ASSERT_EQUAL( static_cast<double>(*dpResPix + *dpResPix), 
			  dPixMap[i]);

  // Ensure that function member returns a valid reference on 'this'
  CPPUNIT_ASSERT( &bDupImg == &(bDupImg.plusEqual(bImg)) );
}

// -------------------------------------------------------------------

void
GenImageTest::testMinus()
{
  // ------
  // Set Up
  // ------
  
  int width  = 50;
  int height = 20;
  
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);


  // -------
  // Process
  // -------
  
  BinaryImage bResImg = bImg.minus(bImg);
  IntImage    iResImg = iImg.minus(iImg);
  FloatImage  fResImg = fImg.minus(fImg);
  DoubleImage dResImg = dImg.minus(dImg);


  // -----
  // Check
  // -----

  // Byte images
  unsigned char * bpResPix = bResImg.pPixMap();
  for (int i=0; i < width * height; ++i)
    CPPUNIT_ASSERT_EQUAL(*bpResPix++, 
 			 static_cast<unsigned char>(bPixMap[i] - bPixMap[i]));

  // Int images
  int * ipResPix = iResImg.pPixMap();
  for (int i=0; i < width * height; ++i)
    CPPUNIT_ASSERT_EQUAL(*ipResPix++, 
			 static_cast<int>(iPixMap[i] - iPixMap[i]));

  // Byte images
  float * fpResPix = fResImg.pPixMap();
  for (int i=0; i < width * height; ++i)
    CPPUNIT_ASSERT_EQUAL(*fpResPix++, 
 			 static_cast<float>(fPixMap[i] - fPixMap[i]));

  // Byte images
  double * dpResPix = dResImg.pPixMap();
  for (int i=0; i < width * height; ++i)
    CPPUNIT_ASSERT_EQUAL(*dpResPix++, 
 			 static_cast<double>(dPixMap[i] - dPixMap[i]));
}

// -------------------------------------------------------------------

void
GenImageTest::testMinusEqual()
{
  // ------
  // Set Up
  // ------
  
  int width  = 50;
  int height = 20;
  
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);

  // Duplicate images
  BinaryImage bDupImg(bImg);
  IntImage    iDupImg(iImg);
  FloatImage  fDupImg(fImg);
  DoubleImage dDupImg(dImg);


  // -------
  // Process
  // -------
  
  bImg.minusEqual(bImg);
  iImg.minusEqual(iImg);
  fImg.minusEqual(fImg);
  dImg.minusEqual(dImg);


  // -----
  // Check
  // -----

  // Byte images
  unsigned char * bpResPix = bDupImg.pPixMap();
  for (int i=0; i < width * height; ++i, bpResPix++)
    CPPUNIT_ASSERT_EQUAL(static_cast<unsigned char>(*bpResPix - *bpResPix), 
 			 bPixMap[i]);
  
  // Int images
  int * ipResPix = iDupImg.pPixMap();
  for (int i=0; i < width * height; ++i, ipResPix++)
    CPPUNIT_ASSERT_EQUAL( static_cast<int>(*ipResPix - *ipResPix), 
			  iPixMap[i]);

  // Float images
  float * fpResPix = fDupImg.pPixMap();
  for (int i=0; i < width * height; ++i, fpResPix++)
    CPPUNIT_ASSERT_EQUAL( static_cast<float>(*fpResPix - *fpResPix), 
			  fPixMap[i]);

  // Double images
  double * dpResPix = dDupImg.pPixMap();
  for (int i=0; i < width * height; ++i, dpResPix++)
    CPPUNIT_ASSERT_EQUAL( static_cast<double>(*dpResPix - *dpResPix), 
			  dPixMap[i]);

  // Ensure that function member returns a valid reference on 'this'
  CPPUNIT_ASSERT( &bDupImg == &(bDupImg.minusEqual(bImg)) );
}

// -------------------------------------------------------------------

void
GenImageTest::testTimes()
{
  // ------
  // Set Up
  // ------
  
  int width  = 50;
  int height = 20;
  
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);


  // -------
  // Process
  // -------
  
  BinaryImage bResImg = bImg.times(bImg);
  IntImage    iResImg = iImg.times(iImg);
  FloatImage  fResImg = fImg.times(fImg);
  DoubleImage dResImg = dImg.times(dImg);


  // -----
  // Check
  // -----

  // Byte images
  unsigned char * bpResPix = bResImg.pPixMap();
  for (int i=0; i < width * height; ++i)
    CPPUNIT_ASSERT_EQUAL(*bpResPix++, 
 			 static_cast<unsigned char>(bPixMap[i] * bPixMap[i]));

  // Int images
  int * ipResPix = iResImg.pPixMap();
  for (int i=0; i < width * height; ++i)
    CPPUNIT_ASSERT_EQUAL(*ipResPix++, 
			 static_cast<int>(iPixMap[i] * iPixMap[i]));

  // Byte images
  float * fpResPix = fResImg.pPixMap();
  for (int i=0; i < width * height; ++i)
    CPPUNIT_ASSERT_EQUAL(*fpResPix++, 
 			 static_cast<float>(fPixMap[i] * fPixMap[i]));

  // Byte images
  double * dpResPix = dResImg.pPixMap();
  for (int i=0; i < width * height; ++i)
    CPPUNIT_ASSERT_EQUAL(*dpResPix++, 
 			 static_cast<double>(dPixMap[i] * dPixMap[i]));
}

// -------------------------------------------------------------------

void
GenImageTest::testTimesEqual()
{
  // ------
  // Set Up
  // ------
  
  int width  = 50;
  int height = 20;
  
  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(width, height, bPixMap);
  createPixmap(width, height, iPixMap);
  createPixmap(width, height, fPixMap);
  createPixmap(width, height, dPixMap);

  BinaryImage bImg(width, height, bPixMap);
  IntImage    iImg(width, height, iPixMap);
  FloatImage  fImg(width, height, fPixMap);
  DoubleImage dImg(width, height, dPixMap);

  // Duplicate images
  BinaryImage bDupImg(bImg);
  IntImage    iDupImg(iImg);
  FloatImage  fDupImg(fImg);
  DoubleImage dDupImg(dImg);


  // -------
  // Process
  // -------
  
  bImg.timesEqual(bImg);
  iImg.timesEqual(iImg);
  fImg.timesEqual(fImg);
  dImg.timesEqual(dImg);


  // -----
  // Check
  // -----

  // Byte images
  unsigned char * bpResPix = bDupImg.pPixMap();
  for (int i=0; i < width * height; ++i, bpResPix++)
    CPPUNIT_ASSERT_EQUAL(static_cast<unsigned char>(*bpResPix * *bpResPix), 
 			 bPixMap[i]);
  
  // Int images
  int * ipResPix = iDupImg.pPixMap();
  for (int i=0; i < width * height; ++i, ipResPix++)
    CPPUNIT_ASSERT_EQUAL( static_cast<int>(*ipResPix * *ipResPix), 
			  iPixMap[i]);

  // Float images
  float * fpResPix = fDupImg.pPixMap();
  for (int i=0; i < width * height; ++i, fpResPix++)
    CPPUNIT_ASSERT_EQUAL( static_cast<float>(*fpResPix * *fpResPix), 
			  fPixMap[i]);

  // Double images
  double * dpResPix = dDupImg.pPixMap();
  for (int i=0; i < width * height; ++i, dpResPix++)
    CPPUNIT_ASSERT_EQUAL( static_cast<double>(*dpResPix * *dpResPix), 
			  dPixMap[i]);

  // Ensure that function member returns a valid reference on 'this'
  CPPUNIT_ASSERT( &bDupImg == &(bDupImg.timesEqual(bImg)) );
}

// -------------------------------------------------------------------

