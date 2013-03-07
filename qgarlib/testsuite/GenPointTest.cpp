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
 * @file  GenPointTest.cpp
 * @brief Implementation of class GenPointTest
 *
 *        See file GenPointTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 3, 2003  17:17
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenPointTest.cpp,v 1.12 2005/07/13 16:29:34 masini Exp $ */



// For debugging only
//#include <iostream>



// STD
#include <algorithm>
#include <limits>
// QGAR
#include <qgarlib/math.h>
#include <qgarlib/primitives.h>
// QGAR TESTS
#include "GenPointTest.h"



using namespace std;
using namespace qgar;



// ------------------------------------------------------------------
// U N N A M E D   N A M E S P A C E
// ------------------------------------------------------------------

namespace
{


template<class T>
double dotProduct(const GenSegment<T>& s1,
		  const GenSegment<T>& s2)
{
  return   ( (double)s1.dx() * (double)s2.dx() )
         + ( (double)s1.dy() * (double)s2.dy() );
}


template<class T>
double dotProduct(const GenQgarSegment<T>& s1,
		  const GenQgarSegment<T>& s2)
{
  return dotProduct(s1.accessGeomStructure(), s2.accessGeomStructure());
}


} // unnamed namespace

// ------------------------------------------------------------------
// T E S T F I X T U R E   I M P L
// ------------------------------------------------------------------

void
GenPointTest::setUp()
{
  /* EMPTY */
}

// ------------------------------------------------------------------

void
GenPointTest::tearDown()
{
  /* EMPTY */
}


// ------------------------------------------------------------------
// C O N S T R U C T O R S
// ------------------------------------------------------------------

void
GenPointTest::testDefaultConstructor()
{
  // ------
  // Set Up
  // ------

  IPoint p1;
  FPoint p2;
  DPoint p3;

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL(p1.x(), 0);
  CPPUNIT_ASSERT_EQUAL(p1.y(), 0);

  CPPUNIT_ASSERT_EQUAL(p2.x(), 0.0F);
  CPPUNIT_ASSERT_EQUAL(p2.y(), 0.0F);

  CPPUNIT_ASSERT_EQUAL(p3.x(), 0.0);
  CPPUNIT_ASSERT_EQUAL(p3.y(), 0.0);
}

// ----------------------------------------------------------------------

void
GenPointTest::testCopyConstructor()
{
  // ------
  // Set Up
  // ------

  IPoint intPt(1, 2);
  IPoint dupIntPt = IPoint(intPt);

  FPoint floatPt(0.1F, 0.2F);
  FPoint dupFloatPt = FPoint(floatPt);

  DPoint doublePt(1.1, 2.2);
  DPoint dupDoublePt = DPoint(doublePt);
  
  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL(intPt,    dupIntPt);
  CPPUNIT_ASSERT_EQUAL(floatPt,  dupFloatPt);
  CPPUNIT_ASSERT_EQUAL(doublePt, dupDoublePt);
}

// ----------------------------------------------------------------------

void
GenPointTest::testBuildFromCoordsConstructor()
{
  // ------
  // Set Up
  // ------

  IPoint intP(1, 2);
  FPoint floatP(0.1F, 0.2F);
  DPoint doubleP(1.1, 2.2);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL(intP.x(), 1);
  CPPUNIT_ASSERT_EQUAL(intP.y(), 2);

  CPPUNIT_ASSERT_EQUAL(floatP.x(), 0.1F);
  CPPUNIT_ASSERT_EQUAL(floatP.y(), 0.2F);

  CPPUNIT_ASSERT_EQUAL(doubleP.x(), 1.1);
  CPPUNIT_ASSERT_EQUAL(doubleP.y(), 2.2);    
}

// ----------------------------------------------------------------------

void
GenPointTest::testBuildFromOtherPoint()
{
  // ------
  // Set Up
  // ------

  IPoint iPt(1, 2);
  FPoint fPt(10.999f, 20.897f);
  DPoint dPt(100.4561, 200.7895);

  // -------
  // Process
  // -------

  IPoint ip(dPt);
  FPoint fp(iPt);
  DPoint dp(fPt);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL(ip.x(), 100);
  CPPUNIT_ASSERT_EQUAL(ip.y(), 200);

  CPPUNIT_ASSERT_EQUAL(fp.x(), 1.f);
  CPPUNIT_ASSERT_EQUAL(fp.y(), 2.f);

  CPPUNIT_ASSERT_DOUBLES_EQUAL(dp.x(), 10.999, 0.00001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dp.y(), 20.897, 0.00001);    
}

// ------------------------------------------------------------------
// A C C E S S   T O   C O O R D I N A T E S
// ------------------------------------------------------------------

void
GenPointTest::testRho()
{
  // ------
  // Set Up
  // ------

  int xi = 1;
  int yi = 2;
  float xf = 0.1F;
  float yf = 0.2F;
  double xd = 1.1;
  double yd = 2.2;

  IPoint intPt(xi, yi);
  FPoint floatPt(xf, yf);
  DPoint doublePt(xd, yd);

  // -------
  // Process
  // -------

  double intRho    = sqrt(static_cast<double>((xi * xi) + (yi * yi)));
  double floatRho  = sqrt(static_cast<double>((xf * xf) + (yf * yf)));
  double doubleRho = sqrt( (xd * xd) + (yd * yd) );

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_DOUBLES_EQUAL(intRho,    intPt.rho(),    0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(floatRho,  floatPt.rho(),  0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(doubleRho, doublePt.rho(), 0.0001);
}

// ----------------------------------------------------------------------

void
GenPointTest::testTheta()
{
  // ------
  // Set Up
  // ------

  int xi = 1;
  int yi = 2;
  float xf = 0.1F;
  float yf = 0.2F;
  double xd = 1.1;
  double yd = 2.2;

  IPoint intPt(xi, yi);
  FPoint floatPt(xf, yf);
  DPoint doublePt(xd, yd);

  // -------
  // Process
  // -------

  double intTheta    = atan2(static_cast<double>(yi), static_cast<double>(xi));
  double floatTheta  = atan2(static_cast<double>(yf), static_cast<double>(xf)); 
  double doubleTheta = atan2(yd, xd);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_DOUBLES_EQUAL(intTheta,    intPt.theta(),    0.0001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL(floatTheta,  floatPt.theta(),  0.0001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL(doubleTheta, doublePt.theta(), 0.0001 );
}


// ------------------------------------------------------------------
// S E T   C O O R D I N A T E S
// ------------------------------------------------------------------

void
GenPointTest::testSetX()
{
  // ------
  // Set Up
  // ------

  int    xi = 10;
  float  xf = 9.3F;
  double xd = 656523.2985267835;

  IPoint iPt;
  FPoint fPt;
  DPoint dPt;

  // -------
  // Process
  // -------
  iPt.setX(xi);
  fPt.setX(xf);
  dPt.setX(xd);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL(xi, iPt.x());
  CPPUNIT_ASSERT_EQUAL(xf, fPt.x());
  CPPUNIT_ASSERT_EQUAL(xd, dPt.x());
}

// ----------------------------------------------------------------------

void
GenPointTest::testSetY()
{
  // ------
  // Set Up
  // ------

  int    yi = 35661;
  float  yf = 2.5672561F;
  double yd = 55255619.44472;

  IPoint iPt;
  FPoint fPt;
  DPoint dPt;

  // -------
  // Process
  // -------

  iPt.setY(yi);
  fPt.setY(yf);
  dPt.setY(yd);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL(yi, iPt.y());
  CPPUNIT_ASSERT_EQUAL(yf, fPt.y());
  CPPUNIT_ASSERT_EQUAL(yd, dPt.y());
}

// ----------------------------------------------------------------------

void
GenPointTest::testSetXY()
{
  // ------
  // Set Up
  // ------

  int    xi = 67826864;
  int    yi = 35661;
  float  xf = 31345.5421058F;
  float  yf = 2.5672561F;
  double xd = -209.82984;
  double yd = 55255619.44472;

  IPoint iPt;
  FPoint fPt;
  DPoint dPt;

  // -------
  // Process
  // -------

  iPt.setXY(xi, yi);
  fPt.setXY(xf, yf);
  dPt.setXY(xd, yd);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL(xi, iPt.x());
  CPPUNIT_ASSERT_EQUAL(yi, iPt.y());

  CPPUNIT_ASSERT_EQUAL(yf, fPt.y());
  CPPUNIT_ASSERT_EQUAL(xf, fPt.x());

  CPPUNIT_ASSERT_EQUAL(xd, dPt.x());
  CPPUNIT_ASSERT_EQUAL(yd, dPt.y());
}

// ----------------------------------------------------------------------
// O P E R A T O R S
// ----------------------------------------------------------------------

void
GenPointTest::testAssignment()
{
  // ------
  // Set Up
  // ------

  IPoint iPt0(409, 497);
  FPoint fPt0(982.2F, -63.0002F);
  DPoint dPt0(98489.98, 15665.3);

  // -------
  // Process
  // -------

  IPoint iPt1; 
  FPoint fPt1;
  DPoint dPt1;
  
  iPt1 = iPt0;
  fPt1 = fPt0;
  dPt1 = dPt0;

  // -----
  // Check
  // -----

  // Check that values are correctly assigned
  CPPUNIT_ASSERT_EQUAL( iPt0.x(), iPt1.x() );
  CPPUNIT_ASSERT_EQUAL( iPt0.y(), iPt1.y() );

  CPPUNIT_ASSERT_EQUAL( fPt0.x(), fPt1.x() );
  CPPUNIT_ASSERT_EQUAL( fPt0.y(), fPt1.y() );

  CPPUNIT_ASSERT_EQUAL( dPt0.x(), dPt1.x() );
  CPPUNIT_ASSERT_EQUAL( dPt0.y(), dPt1.y() );

  // Check if operator returns a correct ref. on 'this'
  CPPUNIT_ASSERT( &iPt0 == &(iPt0 = iPt1) );
}

// ----------------------------------------------------------------------

void
GenPointTest::testOpPlus()
{
  // ------
  // Set Up
  // ------

  int ix0 = -421;
  int iy0 = -345;
  int ix1 = 2424;
  int iy1 = -2895;
  IPoint iPt0(ix0, iy0);
  IPoint iPt1(ix1, iy1);

  float fx0 = 8865.9894F;
  float fy0 = -14.014689F;
  float fx1 = 168.07F;
  float fy1 = 884.118F;
  FPoint fPt0(fx0, fy0);
  FPoint fPt1(fx1, fy1);

  double dx0 = 10.5682;
  double dy0 = 20.2849;
  double dx1 = -138.884;
  double dy1 = 110.00037746;
  DPoint dPt0(dx0, dy0);
  DPoint dPt1(dx1, dy1);

  // -------
  // Process
  // -------
  
  IPoint iRetVal = iPt0 + iPt1;
  FPoint fRetVal = fPt0 + fPt1;
  DPoint dRetVal = dPt0 + dPt1;

  // -----
  // Check 
  // -----

  // Values
  CPPUNIT_ASSERT_EQUAL( iRetVal.x(), ix0 + ix1 );
  CPPUNIT_ASSERT_EQUAL( iRetVal.y(), iy0 + iy1 );

  CPPUNIT_ASSERT_EQUAL( fRetVal.x(), fx0 + fx1 );
  CPPUNIT_ASSERT_EQUAL( fRetVal.y(), fy0 + fy1 );

  CPPUNIT_ASSERT_EQUAL( dRetVal.x(), dx0 + dx1 );
  CPPUNIT_ASSERT_EQUAL( dRetVal.y(), dy0 + dy1 );
}

// ----------------------------------------------------------------------

void
GenPointTest::testOpPlusEqual()
{
  // ------
  // Set Up
  // ------

  int ix0 = 11;
  int iy0 = -2423;
  int ix1 = 24;
  int iy1 = -984;
  IPoint iPt0(ix0, iy0);
  IPoint iPt1(ix1, iy1);

  float fx0 = 85.9894F;
  float fy0 = 4.689F;
  float fx1 = 28.27F;
  float fy1 = 1424.218F;
  FPoint fPt0(fx0, fy0);
  FPoint fPt1(fx1, fy1);

  double dx0 = 14.5622;
  double dy0 = 246.2849;
  double dx1 = -1628.884;
  double dy1 = 11.037746;
  DPoint dPt0(dx0, dy0);
  DPoint dPt1(dx1, dy1);

  // -------
  // Process
  // -------
  
  iPt1 += iPt0;
  fPt1 += fPt0;
  dPt1 += dPt0;

  // -----
  // Check
  // -----

  // Test is addition is correct
  CPPUNIT_ASSERT_EQUAL( iPt1.x(), ix0 + ix1 );
  CPPUNIT_ASSERT_EQUAL( iPt1.y(), iy0 + iy1 );

  CPPUNIT_ASSERT_EQUAL( fPt1.x(), fx0 + fx1 );
  CPPUNIT_ASSERT_EQUAL( fPt1.y(), fy0 + fy1 );

  CPPUNIT_ASSERT_EQUAL( dPt1.x(), dx0 + dx1 );
  CPPUNIT_ASSERT_EQUAL( dPt1.y(), dy0 + dy1 );


  // Check if operator returns a correct ref. on 'this'
  CPPUNIT_ASSERT( &iPt0 == &(iPt0 += iPt1) );  
}

// ----------------------------------------------------------------------

void
GenPointTest::testOpMinus()
{
  // ------
  // Set Up
  // ------

  int ix0 = 21;
  int iy0 = -4523;
  int ix1 = 2;
  int iy1 = 895;
  IPoint iPt0(ix0, iy0);
  IPoint iPt1(ix1, iy1);

  float fx0 = 825.9894F;
  float fy0 = -14.014689F;
  float fx1 = 148.57F;
  float fy1 = 814.218F;
  FPoint fPt0(fx0, fy0);
  FPoint fPt1(fx1, fy1);

  double dx0 = 14.5682;
  double dy0 = 25.2849;
  double dx1 = -138.884;
  double dy1 = 1.0037746;
  DPoint dPt0(dx0, dy0);
  DPoint dPt1(dx1, dy1);

  // -------
  // Process
  // -------
  
  IPoint iRetVal = iPt0 - iPt1;
  FPoint fRetVal = fPt0 - fPt1;
  DPoint dRetVal = dPt0 - dPt1;

  // -----
  // Check 
  // -----

  CPPUNIT_ASSERT_EQUAL( iRetVal.x(), ix0 - ix1 );
  CPPUNIT_ASSERT_EQUAL( iRetVal.y(), iy0 - iy1 );

  CPPUNIT_ASSERT_EQUAL( fRetVal.x(), fx0 - fx1 );
  CPPUNIT_ASSERT_EQUAL( fRetVal.y(), fy0 - fy1 );

  CPPUNIT_ASSERT_EQUAL( dRetVal.x(), dx0 - dx1 );
  CPPUNIT_ASSERT_EQUAL( dRetVal.y(), dy0 - dy1 );
}

// ----------------------------------------------------------------------

void
GenPointTest::testOpMinusEqual()
{
  // ------
  // Set Up
  // ------

  int ix0 = -98;
  int iy0 = -23;
  int ix1 = 4;
  int iy1 = -9084;
  IPoint iPt0(ix0, iy0);
  IPoint iPt1(ix1, iy1);

  float fx0 = 782.0894F;
  float fy0 = 9108.89F;
  float fx1 = -0.27F;
  float fy1 = 24.1813F;
  FPoint fPt0(fx0, fy0);
  FPoint fPt1(fx1, fy1);

  double dx0 = 142.5622;
  double dy0 = 66.2849;
  double dx1 = -8.884;
  double dy1 = -91.46;
  DPoint dPt0(dx0, dy0);
  DPoint dPt1(dx1, dy1);

  // -------
  // Process
  // -------
  
  iPt1 -= iPt0;
  fPt1 -= fPt0;
  dPt1 -= dPt0;

  // -----
  // Check
  // -----

  // Test is addition is correct
  CPPUNIT_ASSERT_EQUAL( iPt1.x(), ix1 - ix0 );
  CPPUNIT_ASSERT_EQUAL( iPt1.y(), iy1 - iy0 );

  CPPUNIT_ASSERT_EQUAL( fPt1.x(), fx1 - fx0 );
  CPPUNIT_ASSERT_EQUAL( fPt1.y(), fy1 - fy0 );

  CPPUNIT_ASSERT_EQUAL( dPt1.x(), dx1 - dx0 );
  CPPUNIT_ASSERT_EQUAL( dPt1.y(), dy1 - dy0 );

  // Check if operator returns a correct ref. on 'this'
  CPPUNIT_ASSERT( &iPt0 == &(iPt0 -= iPt1) );  
}

// ----------------------------------------------------------------------

void
GenPointTest::testOpEqual()
{
  // ------
  // Set Up
  // ------

  int ix0 = -98;
  int iy0 = -23;
  IPoint iPt0(ix0, iy0);

  float fx0 = 782.0894F;
  float fy0 = 9108.89F;
  FPoint fPt0(fx0, fy0);

  double dx0 = 142.5622;
  double dy0 = 66.2849;
  DPoint dPt0(dx0, dy0);

  // -----
  // Check
  // -----

  // Reflexivity
  CPPUNIT_ASSERT( iPt0 == iPt0 );
  CPPUNIT_ASSERT( fPt0 == fPt0 );
  CPPUNIT_ASSERT( dPt0 == dPt0 );

  // Values: Check if a point is equal to a copy of itself
  CPPUNIT_ASSERT( iPt0 == IPoint(iPt0) );
  CPPUNIT_ASSERT( fPt0 == FPoint(fPt0) );
  CPPUNIT_ASSERT( dPt0 == DPoint(dPt0) );
}

// ----------------------------------------------------------------------

void
GenPointTest::testOpNotEqual()
{
  // ------
  // Set Up
  // ------

  int ix0 = -98;
  int iy0 = -23;
  IPoint iPt0(ix0, iy0);

  float fx0 = 782.0894F;
  float fy0 = 9108.89F;
  FPoint fPt0(fx0, fy0);

  double dx0 = 142.5622;
  double dy0 = 66.2849;
  DPoint dPt0(dx0, dy0);

  // -----
  // Check
  // -----

  // Values: Check if a point is equal to a copy of itself
  CPPUNIT_ASSERT(! (iPt0 != IPoint(iPt0)) );
  CPPUNIT_ASSERT(! (fPt0 != FPoint(fPt0)) );
  CPPUNIT_ASSERT(! (dPt0 != DPoint(dPt0)) );

  // Check if two different points are not equal
  CPPUNIT_ASSERT( iPt0 != (iPt0 + IPoint(1, 1)) );
  CPPUNIT_ASSERT( fPt0 != (fPt0 + FPoint(1.1F, 1.1F)) );
  CPPUNIT_ASSERT( dPt0 != (dPt0 + DPoint(1.1, 1.1)) );
}

// ----------------------------------------------------------------------
// F U N C T I O N A L   O P E R A T O R S
// ----------------------------------------------------------------------

void
GenPointTest::testPlus()
{
  // ------
  // Set Up
  // ------

  int ix0 = -11;
  int iy0 = -33;
  int ix1 = 524;
  int iy1 = -2;
  IPoint iPt0(ix0, iy0);
  IPoint iPt1(ix1, iy1);

  float fx0 = 5.9894F;
  float fy0 = -4.689F;
  float fx1 = 142.7F;
  float fy1 = 1.14118F;
  FPoint fPt0(fx0, fy0);
  FPoint fPt1(fx1, fy1);

  double dx0 = 140.552;
  double dy0 = 12.3521;
  double dx1 = -738.83584;
  double dy1 = 130.46;
  DPoint dPt0(dx0, dy0);
  DPoint dPt1(dx1, dy1);

  // -------
  // Process
  // -------
  
  IPoint iRetVal = iPt0.plus(iPt1);
  FPoint fRetVal = fPt0.plus(fPt1);
  DPoint dRetVal = dPt0.plus(dPt1);

  // -----
  // Check 
  // -----

  CPPUNIT_ASSERT_EQUAL( iRetVal.x(), ix0 + ix1 );
  CPPUNIT_ASSERT_EQUAL( iRetVal.y(), iy0 + iy1 );

  CPPUNIT_ASSERT_EQUAL( fRetVal.x(), fx0 + fx1 );
  CPPUNIT_ASSERT_EQUAL( fRetVal.y(), fy0 + fy1 );

  CPPUNIT_ASSERT_EQUAL( dRetVal.x(), dx0 + dx1 );
  CPPUNIT_ASSERT_EQUAL( dRetVal.y(), dy0 + dy1 );
}

// ----------------------------------------------------------------------

void
GenPointTest::testPlusEqual()
{
  // ------
  // Set Up
  // ------

  int ix0 = 94;
  int iy0 = -10;
  int ix1 = 49;
  int iy1 = -11;
  IPoint iPt0(ix0, iy0);
  IPoint iPt1(ix1, iy1);

  float fx0 = 843.9894F;
  float fy0 = 41.689F;
  float fx1 = 25.27F;
  float fy1 = 1624.218F;
  FPoint fPt0(fx0, fy0);
  FPoint fPt1(fx1, fy1);

  double dx0 = 13.5622;
  double dy0 = 25.2849;
  double dx1 = -29.884;
  double dy1 = 192.037746;
  DPoint dPt0(dx0, dy0);
  DPoint dPt1(dx1, dy1);

  // -------
  // Process
  // -------
  
  iPt1.plusEqual(iPt0);
  fPt1.plusEqual(fPt0);
  dPt1.plusEqual(dPt0);

  // -----
  // Check
  // -----

  // Test is addition is correct
  CPPUNIT_ASSERT_EQUAL( iPt1.x(), ix0 + ix1 );
  CPPUNIT_ASSERT_EQUAL( iPt1.y(), iy0 + iy1 );

  CPPUNIT_ASSERT_EQUAL( fPt1.x(), fx0 + fx1 );
  CPPUNIT_ASSERT_EQUAL( fPt1.y(), fy0 + fy1 );

  CPPUNIT_ASSERT_EQUAL( dPt1.x(), dx0 + dx1 );
  CPPUNIT_ASSERT_EQUAL( dPt1.y(), dy0 + dy1 );

  // Check if function returns a correct ref. on 'this'
  CPPUNIT_ASSERT( &iPt0 == &(iPt0.plusEqual(iPt1)) );  
}

// ----------------------------------------------------------------------

void
GenPointTest::testMinus()
{
  // ------
  // Set Up
  // ------

  int ix0 = -18;
  int iy0 = -48;
  int ix1 = 52;
  int iy1 = -98;
  IPoint iPt0(ix0, iy0);
  IPoint iPt1(ix1, iy1);

  float fx0 = 12.5894F;
  float fy0 = -41.6289F;
  float fx1 = 136.7F;
  float fy1 = 11.13518F;
  FPoint fPt0(fx0, fy0);
  FPoint fPt1(fx1, fy1);

  double dx0 = 1520.552;
  double dy0 = 12.3521;
  double dx1 = -758.83584;
  double dy1 = 12.46;
  DPoint dPt0(dx0, dy0);
  DPoint dPt1(dx1, dy1);

  // -------
  // Process
  // -------
  
  IPoint iRetVal = iPt0.minus(iPt1);
  FPoint fRetVal = fPt0.minus(fPt1);
  DPoint dRetVal = dPt0.minus(dPt1);

  // -----
  // Check 
  // -----

  CPPUNIT_ASSERT_EQUAL( iRetVal.x(), ix0 - ix1 );
  CPPUNIT_ASSERT_EQUAL( iRetVal.y(), iy0 - iy1 );

  CPPUNIT_ASSERT_EQUAL( fRetVal.x(), fx0 - fx1 );
  CPPUNIT_ASSERT_EQUAL( fRetVal.y(), fy0 - fy1 );

  CPPUNIT_ASSERT_EQUAL( dRetVal.x(), dx0 - dx1 );
  CPPUNIT_ASSERT_EQUAL( dRetVal.y(), dy0 - dy1 );
}

// ----------------------------------------------------------------------

void
GenPointTest::testMinusEqual()
{
  // ------
  // Set Up
  // ------

  int ix0 = 193;
  int iy0 = 995;
  int ix1 = 1;
  int iy1 = -84;
  IPoint iPt0(ix0, iy0);
  IPoint iPt1(ix1, iy1);

  float fx0 = 0.0044F;
  float fy0 = 10.89F;
  float fx1 = -130.27F;
  float fy1 = 224.1813F;
  FPoint fPt0(fx0, fy0);
  FPoint fPt1(fx1, fy1);

  double dx0 = 12.5622;
  double dy0 = 626.2849;
  double dx1 = 16.884;
  double dy1 = -1.46;
  DPoint dPt0(dx0, dy0);
  DPoint dPt1(dx1, dy1);

  // -------
  // Process
  // -------
  
  iPt1.minusEqual(iPt0);
  fPt1.minusEqual(fPt0);
  dPt1.minusEqual(dPt0);

  // -----
  // Check
  // -----

  // Test is addition is correct
  CPPUNIT_ASSERT_EQUAL( iPt1.x(), ix1 - ix0 );
  CPPUNIT_ASSERT_EQUAL( iPt1.y(), iy1 - iy0 );

  CPPUNIT_ASSERT_EQUAL( fPt1.x(), fx1 - fx0 );
  CPPUNIT_ASSERT_EQUAL( fPt1.y(), fy1 - fy0 );

  CPPUNIT_ASSERT_EQUAL( dPt1.x(), dx1 - dx0 );
  CPPUNIT_ASSERT_EQUAL( dPt1.y(), dy1 - dy0 );

  // Check if operator returns a correct ref. on 'this'
  CPPUNIT_ASSERT( &iPt0 == &(iPt0.minusEqual(iPt1)) );  
}

// ----------------------------------------------------------------------

void
GenPointTest::testEq()
{
  // ------
  // Set Up
  // ------

  int ix0 = -98;
  int iy0 = -23;
  IPoint iPt0(ix0, iy0);

  float fx0 = 782.0894F;
  float fy0 = 9108.89F;
  FPoint fPt0(fx0, fy0);

  double dx0 = 142.5622;
  double dy0 = 66.2849;
  DPoint dPt0(dx0, dy0);

  // -----
  // Check
  // -----

  // Reflexivity
  CPPUNIT_ASSERT( iPt0.eq(iPt0) );
  CPPUNIT_ASSERT( fPt0.eq(fPt0) );
  CPPUNIT_ASSERT( dPt0.eq(dPt0) );

  // Values: Check if a point is equal to a copy of itself
  CPPUNIT_ASSERT( iPt0.eq(IPoint(iPt0)) );
  CPPUNIT_ASSERT( fPt0.eq(FPoint(fPt0)) );
  CPPUNIT_ASSERT( dPt0.eq(DPoint(dPt0)) );
}

// ----------------------------------------------------------------------

void
GenPointTest::testNotEq()
{
  // ------
  // Set Up
  // ------

  int ix0 = -98;
  int iy0 = -23;
  IPoint iPt0(ix0, iy0);

  float fx0 = 782.0894F;
  float fy0 = 9108.89F;
  FPoint fPt0(fx0, fy0);

  double dx0 = 142.5622;
  double dy0 = 66.2849;
  DPoint dPt0(dx0, dy0);

  // -----
  // Check
  // -----

  // Values: Check if a point is equal to a copy of itself
  CPPUNIT_ASSERT(! (iPt0.notEq(IPoint(iPt0))) );
  CPPUNIT_ASSERT(! (fPt0.notEq(FPoint(fPt0))) );
  CPPUNIT_ASSERT(! (dPt0.notEq(DPoint(dPt0))) );

  // Check if two different points are not equal
  CPPUNIT_ASSERT( iPt0.notEq((iPt0 + IPoint(1, 1))) );
  CPPUNIT_ASSERT( fPt0.notEq((fPt0 + FPoint(1.1F, 1.1F))) );
  CPPUNIT_ASSERT( dPt0.notEq((dPt0 + DPoint(1.1, 1.1))) );
}

// ----------------------------------------------------------------------
// G E O M E T R Y :   P R O J E C T I O N
// ----------------------------------------------------------------------

void
GenPointTest::testProject()
{
   // ------
   // Set Up
   // ------

   DPoint dPt (  1.45, -91.4);
   DPoint dPt0( 18.,    21.);
   DPoint dPt1(-21.,   -27.);

   DSegment dSeg(dPt0, dPt1);

   DPoint d1Pt ( -0.689,   2.58);
   DPoint d1Pt0( 18.1198, 16.1);
   DPoint d1Pt1(-39.1,     0.013);

   DQgarSegment dqSeg(d1Pt0, d1Pt1);

   // -------
   // Process
   // -------
  
   DPoint dPtSave(dPt);
   dPt.project(dSeg);

   DPoint d1PtSave(d1Pt);
   d1Pt.project(dqSeg);

   // -----
   // Check
   // -----
  
   // Check if segments are perpendicular
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.,
 			       dotProduct(dSeg, DSegment(dPt,dPtSave)),
 			       0.0001 );

   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.,
 			       dotProduct(dqSeg, DQgarSegment(d1Pt,d1PtSave)),
 			       0.0001 );

   // =============
   // TRIVIAL CASES
   // =============

   // ------
   // Set Up
   // ------

   DPoint ptO( 0.,  0.);
   DPoint ptA( 0., 20.);
   DPoint ptB(20., 20.);
   DPoint ptC(10., 10.);
   DPoint ptD(20.,  0.);

   DSegment sOA(ptO, ptA);
   DSegment sOB(ptO, ptB);
   DSegment sOD(ptO, ptD);
   DSegment sAD(ptA, ptD);
   DSegment sAB(ptA, ptB);

   // -------
   // Process
   // -------
  
   DPoint ptA_OA(ptA);
   ptA_OA.project(sOA);

   DPoint ptA_OB(ptA);
   ptA_OB.project(sOB);

   DPoint ptA_OD(ptA);
   ptA_OD.project(sOD);

   DPoint ptB_OA(ptB);
   ptB_OA.project(sOA);

   DPoint ptB_AD(ptB);
   ptB_AD.project(sAD);

   DPoint ptB_OD(ptB);
   ptB_OD.project(sOD);

   DPoint ptC_AD(ptC);
   ptC_AD.project(sAD);

   DPoint ptC_OA(ptC);
   ptC_OA.project(sOA);

   DPoint ptC_OD(ptC);
   ptC_OD.project(sOD);

   DPoint ptC_AB(ptC);
   ptC_AB.project(sAB);

   // -----
   // Check
   // -----
  
   /*      ^
    *      |A     B
    *   20 +     +
    *      |\   /
    *      | \ /
    *   10 |  + C
    *      | / \
    *      |/   \ D
    *      +-----+----->
    *     0  10 20
    */

   CPPUNIT_ASSERT_DOUBLES_EQUAL( ptA_OA.x(),  0., 0.0001 );
   CPPUNIT_ASSERT_DOUBLES_EQUAL( ptA_OA.y(), 20., 0.0001 );
   CPPUNIT_ASSERT_DOUBLES_EQUAL( ptA_OB.x(), 10., 0.0001 );
   CPPUNIT_ASSERT_DOUBLES_EQUAL( ptA_OB.y(), 10., 0.0001 );
   CPPUNIT_ASSERT_DOUBLES_EQUAL( ptA_OD.x(),  0., 0.0001 );
   CPPUNIT_ASSERT_DOUBLES_EQUAL( ptA_OD.y(),  0., 0.0001 );
   CPPUNIT_ASSERT_DOUBLES_EQUAL( ptB_OA.x(),  0., 0.0001 );
   CPPUNIT_ASSERT_DOUBLES_EQUAL( ptB_OA.y(), 20., 0.0001 );
   CPPUNIT_ASSERT_DOUBLES_EQUAL( ptB_AD.x(), 10., 0.0001 );
   CPPUNIT_ASSERT_DOUBLES_EQUAL( ptB_AD.y(), 10., 0.0001 );
   CPPUNIT_ASSERT_DOUBLES_EQUAL( ptB_OD.x(), 20., 0.0001 );
   CPPUNIT_ASSERT_DOUBLES_EQUAL( ptB_OD.y(),  0., 0.0001 );
   CPPUNIT_ASSERT_DOUBLES_EQUAL( ptC_AD.x(), 10., 0.0001 );
   CPPUNIT_ASSERT_DOUBLES_EQUAL( ptC_AD.y(), 10., 0.0001 );
   CPPUNIT_ASSERT_DOUBLES_EQUAL( ptC_OA.x(),  0., 0.0001 );
   CPPUNIT_ASSERT_DOUBLES_EQUAL( ptC_OA.y(), 10., 0.0001 );
   CPPUNIT_ASSERT_DOUBLES_EQUAL( ptC_OD.x(), 10., 0.0001 );
   CPPUNIT_ASSERT_DOUBLES_EQUAL( ptC_OD.y(),  0., 0.0001 );
   CPPUNIT_ASSERT_DOUBLES_EQUAL( ptC_AB.x(), 10., 0.0001 );
   CPPUNIT_ASSERT_DOUBLES_EQUAL( ptC_AB.y(), 20., 0.0001 );
}

// ----------------------------------------------------------------------
// G E O M E T R Y :   T R A N S L A T I O N
// ----------------------------------------------------------------------

void
GenPointTest::testTranslate()
{
   // ------
   // Set Up
   // ------

   int ix  = 33259;
   int iy  = -193;
   int idx = 1894;
   int idy = -22;
   IPoint iPt(ix,iy);

   float fx  = -122554.9894F;
   float fy  = -9813.001F;
   float fdx = -0.00247F;
   float fdy = 7874.8928F;
   FPoint fPt(fx,fy);

   double dx  = 0.000000024787;
   double dy  = -468724.849;
   double ddx = -88849898938.884;
   double ddy = 0.00037746;
   DPoint dPt(dx,dy);

   // -------
   // Process
   // -------

   iPt.translate(idx,idy);
   fPt.translate(fdx,fdy);
   dPt.translate(ddx,ddy);

   // -----
   // Check
   // -----

   CPPUNIT_ASSERT_EQUAL( iPt.x(), (ix + idx) );
   CPPUNIT_ASSERT_EQUAL( iPt.y(), (iy + idy) );

   CPPUNIT_ASSERT_EQUAL( fPt.x(), (fx + fdx) );
   CPPUNIT_ASSERT_EQUAL( fPt.y(), (fy + fdy) );

   CPPUNIT_ASSERT_EQUAL( dPt.x(), (dx + ddx) );
   CPPUNIT_ASSERT_EQUAL( dPt.y(), (dy + ddy) );
}

// ----------------------------------------------------------------------
// S E R I A L I Z A T I O N
// ----------------------------------------------------------------------

void 
GenPointTest::testSerializeDeserialize()
{
  // ------
  // Set Up
  // ------

  IPoint iPt(1, 2);
  FPoint fPt(0.1F, 0.2F);
  DPoint dPt(1.1, 2.2);

  IPoint iOutInPt;
  FPoint fOutInPt;
  DPoint dOutInPt;

  // -------
  // Process
  // -------
  
  std::stringstream ss;

  ss << iPt;
  ss >> iOutInPt;
  ss.flush();

  ss << fPt;
  ss >> fOutInPt;
  ss.flush();

  ss << dPt;
  ss >> dOutInPt;
  ss.flush();

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL(iPt, iOutInPt);
  CPPUNIT_ASSERT_EQUAL(fPt, fOutInPt);
  CPPUNIT_ASSERT_EQUAL(dPt, dOutInPt);
}

// ----------------------------------------------------------------------
