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


/**
 * @file  GenConvolImageTest.cpp
 * @brief Implementation of class GenConvolImageTest
 *
 *        See file GenConvolImageTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   January 5, 2004  16:05
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenConvolImageTest.cpp,v 1.9 2005/10/14 17:06:36 masini Exp $ */



// STD
#include <iostream>
// QGAR
#include <qgarlib/GenConvolImage.h>
#include <qgarlib/image.h>
#include <qgarlib/math.h>
// QGAR TESTS
#include "GenConvolImageTest.h"



using namespace qgar;
using namespace std;



// -------------------------------------------------------------------
// U N N A M E D   N A M E S P A C E
// -------------------------------------------------------------------
namespace
{

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



/**
 * @brief Compares two images by applying a pixel to pixel comparison.
 *
 * Both images must have the same dimensions.
 *
 * @param width  The width of the images.
 * @param height The height of the images.
 * @param lhs    The left hand side image of the comparison.
 * @param rhs    The right hand side image of the comparison.
 */
template<typename T>
bool compare(const GenImage<T>& lhs, 
	     const GenImage<T>& rhs)
{
  bool match = true;

  for (int i=0; (i < rhs.width()) && match; ++i) {

    for (int j=0; (j < rhs.height()) && match; ++j) 
      match = ( lhs.pixel(i,  j) 
		== rhs.pixel(i,j) );
  }
  return match;
}

/**
 * @brief Create an array of value of a given size.
 *
 * The values are initialized so that val[i] = i.
 *
 * @param width the desired size of the array.
 * @param mask a pointer to store the created array in.
 */
template<typename T>
void create1DMaskArray(int width, T*& mask)
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
 * @brief Creates an array of values of a given size.
 *
 * 
 * @param width  The width of the array to create.
 * @param height The heigth of the array to create.
 * @param mask   A pointer to return the array in.
 */
template<typename T>
void create2DMaskArray(int width, int height, T*& mask)
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
 * @brief Applies a horizontal 1D mask.
 *
 * @param ptr  A pointer on the pixmap where the left end of the mask
 *             is applied.
 * @param mask The mask to apply.
 */
template<typename T>
double applyHorizMask(T* ptr, const DMask1d& mask)
{
  double sum = 0.;

  for (int i=0; i < mask.width(); ++i) {
    sum += ptr[i] * mask.coeff(i);
  }

  return sum;
}


/**
 * @brief Applies a vertical 1D mask.
 *
 * @param ptr  A pointer on the pixmap where the top end of the mask
 *             is applied.
 * @param mask The mask to apply.
 */
template<typename T>
double applyVertMask(int width, T* img, const DMask1d& mask)
{
  double sum = 0.;

  for (int i=0; i < mask.width(); ++i) {
    sum += img[i*width] * mask.coeff(i);
  }

  return sum;
}


/**
 * @brief Applies a 2D mask.
 *
 * @param ptr  A pointer on the pixmap where the left top end of the
 *             mask is applied.
 * @param mask The mask to apply.
 */
template<typename T>
double apply2DMask(int width, T* img, const DMask2d& mask)
{
  double sum = 0;
  
  for (int j=0; j < mask.height(); ++j) {

    for (int i=0; i < mask.width(); ++i) {
      sum += double(img[j*width + i]) * mask.coeff(i, j);
    }
  }

  return sum;
}

template <class T>
void
dump(const T* ptr, int width, int height)
{
  cout << endl;
  for(int j=0; j < height; j++) {
    for (int i=0; i < width; i++) {

      cout << (*ptr++) << " ";
    }
    cout << endl;
  }
}

} // unnamed namespace


// ------------------------------------------------------------------
// T E S T F I X T U R E   I M P L
// ------------------------------------------------------------------

void
GenConvolImageTest::setUp()
{
  /* EMPTY */
}

// -------------------------------------------------------------------

void
GenConvolImageTest::tearDown()
{
  /* EMPTY */
}


// -------------------------------------------------------------------
// T E S T   F U N C T I O N S
// -------------------------------------------------------------------

void
GenConvolImageTest::test1DConvolConstructor()
{
  // ------
  // Set Up
  // ------

  // Create images  

  const int IMG_WIDTH  = 100;
  const int IMG_HEIGHT = 80;  

  unsigned char* bPixMap;
  int*    iPixMap;
  float*  fPixMap;
  double* dPixMap;

  createPixmap(IMG_WIDTH, IMG_HEIGHT, bPixMap);
  createPixmap(IMG_WIDTH, IMG_HEIGHT, iPixMap);
  createPixmap(IMG_WIDTH, IMG_HEIGHT, fPixMap);
  createPixmap(IMG_WIDTH, IMG_HEIGHT, dPixMap);

  BinaryImage bImg(IMG_WIDTH, IMG_HEIGHT, bPixMap);
  IntImage    iImg(IMG_WIDTH, IMG_HEIGHT, iPixMap);
  FloatImage  fImg(IMG_WIDTH, IMG_HEIGHT, fPixMap);
  DoubleImage dImg(IMG_WIDTH, IMG_HEIGHT, dPixMap);


  // Create masks

  const int MASK_WIDTH  = 10;

  int    * iArray;
  float  * fArray;
  double * dArray;
  
  create1DMaskArray(MASK_WIDTH, iArray);
  create1DMaskArray(MASK_WIDTH, fArray);
  create1DMaskArray(MASK_WIDTH, dArray);

  IMask1d iMask(MASK_WIDTH, iArray);
  FMask1d fMask(MASK_WIDTH, fArray);
  DMask1d dMask(MASK_WIDTH, dArray);


  // -------
  // Process
  // -------


  // X-AXIS CONVOLUTIONS
 
  //-- char image, double mask

  // Check the 'inside' result
  DConvolImage cdConvolX(bImg, dMask, QGE_AXIS_X);
  for (int j=0; j < bImg.height(); ++j) {
    
    for (int i=MASK_WIDTH/2; i < (bImg.width() - MASK_WIDTH/2); ++i) {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(applyHorizMask(bImg.pRow(j) + i - MASK_WIDTH/2,
						  dMask),
				   cdConvolX.pixel(i,j),
				   Math::epsilonD());
	}
  }


  //-- int image, double mask

  // Check the 'inside' result
  DConvolImage idConvolX(iImg, dMask, QGE_AXIS_X);
  for (int j=0; j < iImg.height(); ++j) {
    
    for (int i=MASK_WIDTH/2; i < (iImg.width() - MASK_WIDTH/2); ++i) {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(applyHorizMask(iImg.pRow(j) + i - MASK_WIDTH/2,
						  dMask),
				   idConvolX.pixel(i,j),
				   Math::epsilonD());
	}
  }


  //-- float image, double mask

  // Check the 'inside' result
  DConvolImage fdConvolX(fImg, dMask, QGE_AXIS_X);
  for (int j=0; j < fImg.height(); ++j) {
    
    for (int i=MASK_WIDTH/2; i < (fImg.width() - MASK_WIDTH/2); ++i) {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(applyHorizMask(fImg.pRow(j) + i - MASK_WIDTH/2,
						  dMask),
				   fdConvolX.pixel(i,j),
				   Math::epsilonD());
	}
  }



  // Y-AXIS CONVOLUTIONS
 
  //-- char image, double mask

  // Check the 'inside' result
  DConvolImage cdConvolY(bImg, dMask, QGE_AXIS_Y);
  for (int j=MASK_WIDTH/2; j < (bImg.height() - MASK_WIDTH/2); ++j) {
    
    for (int i=0; i < bImg.width(); ++i) {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(applyVertMask(IMG_WIDTH,
						 bImg.pRow(j - MASK_WIDTH/2) + i,
						 dMask),
				   cdConvolY.pixel(i,j),
				   Math::epsilonD());
    }
  }


  //-- int image, double mask

  // Check the 'inside' result
  DConvolImage idConvolY(iImg, dMask, QGE_AXIS_Y);
  for (int j=MASK_WIDTH/2; j < (iImg.height() - MASK_WIDTH/2); ++j) {
    
    for (int i=0; i < iImg.width(); ++i) {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(applyVertMask(IMG_WIDTH,
						 iImg.pRow(j - MASK_WIDTH/2) + i,
						 dMask),
				   idConvolY.pixel(i,j),
				   Math::epsilonD());
	}
  }


  //-- float image, double mask

  // Check the 'inside' result
  DConvolImage fdConvolY(fImg, dMask, QGE_AXIS_Y);
  for (int j=MASK_WIDTH/2; j < (fImg.height() - MASK_WIDTH/2); ++j) {
    
    for (int i=0; i < fImg.width(); ++i) {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(applyVertMask(IMG_WIDTH,
						 fImg.pRow(j - MASK_WIDTH/2) + i,
						 dMask),
				   fdConvolY.pixel(i,j),
				   Math::epsilonD());
	}
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
GenConvolImageTest::testCopyConstructor()
{
  // ------
  // Set Up
  // ------

  // Create images  

  const int IMG_WIDTH  = 100;
  const int IMG_HEIGHT = 80;  

  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(IMG_WIDTH, IMG_HEIGHT, bPixMap);
  createPixmap(IMG_WIDTH, IMG_HEIGHT, iPixMap);
  createPixmap(IMG_WIDTH, IMG_HEIGHT, fPixMap);
  createPixmap(IMG_WIDTH, IMG_HEIGHT, dPixMap);

  BinaryImage bImg(IMG_WIDTH, IMG_HEIGHT, bPixMap);
  IntImage    iImg(IMG_WIDTH, IMG_HEIGHT, iPixMap);
  FloatImage  fImg(IMG_WIDTH, IMG_HEIGHT, fPixMap);
  DoubleImage dImg(IMG_WIDTH, IMG_HEIGHT, dPixMap);


  // Create masks

  const int MASK_WIDTH  = 10;
  double * dArray;  

  create1DMaskArray(MASK_WIDTH, dArray);
  DMask1d dMask(MASK_WIDTH, dArray);


  // Perform convolutions.

  DConvolImage bConv(bImg, dMask, QGE_AXIS_X);
  DConvolImage iConv(iImg, dMask, QGE_AXIS_X);
  DConvolImage fConv(fImg, dMask, QGE_AXIS_X);
  DConvolImage dConv(dImg, dMask, QGE_AXIS_X);


  // -------
  // Process
  // -------

  DConvolImage bDupImg(bConv);
  DConvolImage iDupImg(iConv);
  DConvolImage fDupImg(fConv);
  DConvolImage dDupImg(dConv);


  // -----
  // Check
  // -----
  CPPUNIT_ASSERT_EQUAL( bConv.width(),  bDupImg.width() );
  CPPUNIT_ASSERT_EQUAL( bConv.height(), bDupImg.height() );
  CPPUNIT_ASSERT( compare(bConv,  bDupImg) );

  CPPUNIT_ASSERT_EQUAL( iConv.width(),  iDupImg.width() );
  CPPUNIT_ASSERT_EQUAL( iConv.height(), iDupImg.height() );
  CPPUNIT_ASSERT( compare(iConv,  iDupImg) );

  CPPUNIT_ASSERT_EQUAL( fConv.width(),  fDupImg.width() );
  CPPUNIT_ASSERT_EQUAL( fConv.height(), fDupImg.height() );
  CPPUNIT_ASSERT( compare(fConv,  fDupImg) );

  CPPUNIT_ASSERT_EQUAL( dConv.width(),  dDupImg.width() );
  CPPUNIT_ASSERT_EQUAL( dConv.height(), dDupImg.height() );
  CPPUNIT_ASSERT( compare(dConv,  dDupImg) );



  // ---------
  // Tear Down
  // ---------

  delete[] dArray;
}

// -------------------------------------------------------------------

void
GenConvolImageTest::test2DConvolConstructor()
{
  // ------
  // Set Up
  // ------

  // Create images  

  const int IMG_WIDTH  = 89;
  const int IMG_HEIGHT = 58;  

  unsigned char * bPixMap;
  int    * iPixMap;
  float  * fPixMap;
  double * dPixMap;

  createPixmap(IMG_WIDTH, IMG_HEIGHT, bPixMap);
  createPixmap(IMG_WIDTH, IMG_HEIGHT, iPixMap);
  createPixmap(IMG_WIDTH, IMG_HEIGHT, fPixMap);
  createPixmap(IMG_WIDTH, IMG_HEIGHT, dPixMap);

  BinaryImage bImg(IMG_WIDTH, IMG_HEIGHT, bPixMap);
  IntImage    iImg(IMG_WIDTH, IMG_HEIGHT, iPixMap);
  FloatImage  fImg(IMG_WIDTH, IMG_HEIGHT, fPixMap);
  DoubleImage dImg(IMG_WIDTH, IMG_HEIGHT, dPixMap);


  // Create mask

  const int MASK_WIDTH  = 10;
  const int MASK_HEIGHT = 6;

  double * dArray;
  
  create2DMaskArray(MASK_WIDTH, MASK_HEIGHT, dArray);
  DMask2d dMask(MASK_WIDTH, MASK_HEIGHT, dArray);




  // -------
  // Process
  // -------

  //-- char image, double mask

  // Check the 'inside' result
  DConvolImage cdConvol(bImg, dMask);

  for (int j=MASK_HEIGHT/2; j < (IMG_HEIGHT - MASK_HEIGHT/2); ++j) {    
    for (int i=MASK_WIDTH/2; i < (IMG_WIDTH - MASK_WIDTH/2); ++i) {

      CPPUNIT_ASSERT_DOUBLES_EQUAL(apply2DMask(IMG_WIDTH, 
 					       bImg.pRow(j - MASK_HEIGHT/2) 
 					       + i - MASK_WIDTH/2, dMask),
 				   cdConvol.pixel(i,j),
 				   Math::epsilonD());
    }
  }


  //-- int image, double mask.

  // Check the 'inside' result
  DConvolImage idConvol(iImg, dMask);
  
  for (int j=MASK_HEIGHT/2; j < (IMG_HEIGHT - MASK_HEIGHT/2); ++j) {    
    for (int i=MASK_WIDTH/2; i < (IMG_WIDTH - MASK_WIDTH/2); ++i) {
      
      CPPUNIT_ASSERT_DOUBLES_EQUAL(apply2DMask(IMG_WIDTH, 
 					       iImg.pRow(j - MASK_HEIGHT/2) 
 					       + i - MASK_WIDTH/2, dMask),
 				   idConvol.pixel(i,j),
 				   Math::epsilonD());
    }
  }


  //-- float image, double mask

  // Check the 'inside' result
  DConvolImage fdConvol(fImg, dMask);

  for (int j=MASK_HEIGHT/2; j < (IMG_HEIGHT - MASK_HEIGHT/2); ++j) {    
    for (int i=MASK_WIDTH/2; i < (IMG_WIDTH - MASK_WIDTH/2); ++i) {

      CPPUNIT_ASSERT_DOUBLES_EQUAL(apply2DMask(IMG_WIDTH, 
 					       fImg.pRow(j - MASK_HEIGHT/2) 
 					       + i - MASK_WIDTH/2, dMask),
 				   fdConvol.pixel(i,j),
 				   Math::epsilonD());
    }
  }


  //-- double image, double mask.

  // Check the 'inside' result
  DConvolImage ddConvol(dImg, dMask);

  for (int j=MASK_HEIGHT/2; j < (IMG_HEIGHT - MASK_HEIGHT/2); ++j) {    
    for (int i=MASK_WIDTH/2; i < (IMG_WIDTH - MASK_WIDTH/2); ++i) {

      CPPUNIT_ASSERT_DOUBLES_EQUAL(apply2DMask(IMG_WIDTH, 
					       dImg.pRow(j - MASK_HEIGHT/2) 
					       + i - MASK_WIDTH/2, dMask),
				   ddConvol.pixel(i,j),
				   Math::epsilonD());
    }
  }
}

// -------------------------------------------------------------------

