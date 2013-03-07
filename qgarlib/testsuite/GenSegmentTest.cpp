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
 * @file  GenSegmentTest.cpp
 * @brief Implementation of class GenSegmentTest
 *
 *        See file GenSegmentTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   October 8, 2003  15:46
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenSegmentTest.cpp,v 1.12 2005/09/14 10:53:38 masini Exp $ */




// For debugging only
//#include <cstdio>

// QGAR
#include <qgarlib/math.h>
#include <qgarlib/primitives.h>
// QGAR TESTS
#include "GenSegmentTest.h"



using namespace qgar;
using namespace std;



// ------------------------------------------------------------------
// U N N A M E D   N A M E S P A C E
// ------------------------------------------------------------------

namespace
{


template <class T> 
double
dotProduct(T x0, T y0, T x1, T y1)
{
  return double(x0) * double(x1) + double(y0) * double(y1);
}


template<class T>
double
dotProduct(const GenSegment<T>& s1, const GenSegment<T>& s2)
{
  return dotProduct(s1.dx(), s1.dy(), s2.dx(), s2.dy());
}


} // unnamed namespace

// ------------------------------------------------------------------
// T E S T F I X T U R E   I M P L
// ------------------------------------------------------------------

void
GenSegmentTest::setUp()
{
  /* EMPTY */
}

void
GenSegmentTest::tearDown()
{
  /* EMPTY */
}


// ------------------------------------------------------------------
// C O N S T R U C T O R S
// ------------------------------------------------------------------


void
GenSegmentTest::testDefaultConstructor()
{
  // ------
  // Set Up
  // ------
  
  ISegment iSeg;
  FSegment fSeg;
  DSegment dSeg;

  IPoint iPt0(0,0);
  FPoint fPt0(0.f,0.f);
  DPoint dPt0(0.,0.);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT(iSeg.source() == iPt0);
  CPPUNIT_ASSERT(iSeg.target() == iPt0);

  CPPUNIT_ASSERT(fSeg.source() == fPt0);
  CPPUNIT_ASSERT(fSeg.target() == fPt0);

  CPPUNIT_ASSERT(dSeg.source() == dPt0);
  CPPUNIT_ASSERT(dSeg.target() == dPt0);
}


void 
GenSegmentTest::testBuildFromQgarSegment()
{
  // ------
  // Set Up
  // ------
  
  int ix0 = 12;
  int iy0 = -4;
  int ix1 = 416;
  int iy1 = 9;  
  IQgarSegment iqSeg(ix0, iy0, ix1, iy1);

  float fx0 = 0.13f;
  float fy0 = -21.25f;
  float fx1 = 15.2f;
  float fy1 = 1.130f;  
  FQgarSegment fqSeg(fx0, fy0, fx1, fy1);

  double dx0 = 143.1348;
  double dy0 = -54.41;
  double dx1 = 45.5;
  double dy1 = 1.05953;  
  DQgarSegment dqSeg(dx0, dy0, dx1, dy1);

  // -------
  // Process
  // -------
  
  ISegment iSeg(iqSeg);
  FSegment fSeg(fqSeg);
  DSegment dSeg(dqSeg);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT(iSeg.xSource() == ix0);
  CPPUNIT_ASSERT(iSeg.ySource() == iy0);
  CPPUNIT_ASSERT(iSeg.xTarget() == ix1);
  CPPUNIT_ASSERT(iSeg.yTarget() == iy1);

  CPPUNIT_ASSERT(fSeg.xSource() == fx0);
  CPPUNIT_ASSERT(fSeg.ySource() == fy0);
  CPPUNIT_ASSERT(fSeg.xTarget() == fx1);
  CPPUNIT_ASSERT(fSeg.yTarget() == fy1);

  CPPUNIT_ASSERT(dSeg.xSource() == dx0);
  CPPUNIT_ASSERT(dSeg.ySource() == dy0);
  CPPUNIT_ASSERT(dSeg.xTarget() == dx1);
  CPPUNIT_ASSERT(dSeg.yTarget() == dy1);
}


void
GenSegmentTest::testBuildFromTwoPoints()
{
  // ------
  // Set Up
  // ------

  IPoint iPt0(84, 11);
  IPoint iPt1(-24, 21);

  FPoint fPt0(3.1f, 24.1f);
  FPoint fPt1(-2.13f, 213.1f);

  DPoint dPt0(84.894, 1.0002741);
  DPoint dPt1(-2424, 21.984);

  // -------
  // Process
  // -------

  ISegment iSeg(iPt0, iPt1);
  FSegment fSeg(fPt0, fPt1);
  DSegment dSeg(dPt0, dPt1);

  // -----
  // Check
  // -----
  
  CPPUNIT_ASSERT(iSeg.source() == iPt0);
  CPPUNIT_ASSERT(iSeg.target() == iPt1);

  CPPUNIT_ASSERT(fSeg.source() == fPt0);
  CPPUNIT_ASSERT(fSeg.target() == fPt1);

  CPPUNIT_ASSERT(dSeg.source() == dPt0);
  CPPUNIT_ASSERT(dSeg.target() == dPt1);
}


void
GenSegmentTest::testBuildFrom4Coords()
{
  // ------
  // Set Up
  // ------

  int ix0 = 843;
  int iy0 = -51;
  int ix1 = 22;
  int iy1 = 71;

  float fx0 = 8.3f;
  float fy0 = -5.1f;
  float fx1 = 21.212f;
  float fy1 = -31.74861f;  

  double dx0 = 1.444001;
  double dy0 = -0.0001;
  double dx1 = 2980;
  double dy1 = 7.21;

  // -------
  // Process
  // -------

  ISegment iSeg(ix0, iy0, ix1, iy1);
  FSegment fSeg(fx0, fy0, fx1, fy1);
  DSegment dSeg(dx0, dy0, dx1, dy1);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT(iSeg.xSource() == ix0);
  CPPUNIT_ASSERT(iSeg.ySource() == iy0);
  CPPUNIT_ASSERT(iSeg.xTarget() == ix1);
  CPPUNIT_ASSERT(iSeg.yTarget() == iy1);

  CPPUNIT_ASSERT(fSeg.xSource() == fx0);
  CPPUNIT_ASSERT(fSeg.ySource() == fy0);
  CPPUNIT_ASSERT(fSeg.xTarget() == fx1);
  CPPUNIT_ASSERT(fSeg.yTarget() == fy1);

  CPPUNIT_ASSERT(dSeg.xSource() == dx0);
  CPPUNIT_ASSERT(dSeg.ySource() == dy0);
  CPPUNIT_ASSERT(dSeg.xTarget() == dx1);
  CPPUNIT_ASSERT(dSeg.yTarget() == dy1);
}


void
GenSegmentTest::testCopyConstructor()
{
  // ------
  // Set Up
  // ------
  
  int ix0 = 98;
  int iy0 = -24;
  int ix1 = 16;
  int iy1 = 91;  
  ISegment iSeg(ix0, iy0, ix1, iy1);

  float fx0 = 0.8f;
  float fy0 = -2.425f;
  float fx1 = 1905.2f;
  float fy1 = 1.0f;  
  FSegment fSeg(fx0, fy0, fx1, fy1);

  double dx0 = 13.1348;
  double dy0 = -24.41;
  double dx1 = 1145.5;
  double dy1 = 91.05953;  
  DSegment dSeg(dx0, dy0, dx1, dy1);

  // -------
  // Process
  // -------
  
  ISegment iDupSeg(iSeg);
  FSegment fDupSeg(fSeg);
  DSegment dDupSeg(dSeg);
  
  // -----
  // Check
  // -----

  CPPUNIT_ASSERT(iSeg.xSource() == ix0);
  CPPUNIT_ASSERT(iSeg.ySource() == iy0);
  CPPUNIT_ASSERT(iSeg.xTarget() == ix1);
  CPPUNIT_ASSERT(iSeg.yTarget() == iy1);

  CPPUNIT_ASSERT(fSeg.xSource() == fx0);
  CPPUNIT_ASSERT(fSeg.ySource() == fy0);
  CPPUNIT_ASSERT(fSeg.xTarget() == fx1);
  CPPUNIT_ASSERT(fSeg.yTarget() == fy1);

  CPPUNIT_ASSERT(dSeg.xSource() == dx0);
  CPPUNIT_ASSERT(dSeg.ySource() == dy0);
  CPPUNIT_ASSERT(dSeg.xTarget() == dx1);
  CPPUNIT_ASSERT(dSeg.yTarget() == dy1);
}


// ------------------------------------------------------------------
// C O P Y
// ------------------------------------------------------------------

void 
GenSegmentTest::testClone()
{
  // ------
  // Set Up
  // ------
  
  int ix0 = 14;
  int iy0 = -4;
  int ix1 = 56;
  int iy1 = 61;  
  ISegment iSeg(ix0, iy0, ix1, iy1);

  float fx0 = 0.81f;
  float fy0 = -32.425f;
  float fx1 = 15.2f;
  float fy1 = 14.0f;  
  FSegment fSeg(fx0, fy0, fx1, fy1);

  double dx0 = 3.1348;
  double dy0 = -124.41;
  double dx1 = 145.5;
  double dy1 = 61.05953;  
  DSegment dSeg(dx0, dy0, dx1, dy1);

  // -------
  // Process
  // -------
  
  ISegment* iClone = iSeg.clone();
  FSegment* fClone = fSeg.clone();
  DSegment* dClone = dSeg.clone();

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT(iClone->xSource() == ix0);
  CPPUNIT_ASSERT(iClone->ySource() == iy0);
  CPPUNIT_ASSERT(iClone->xTarget() == ix1);
  CPPUNIT_ASSERT(iClone->yTarget() == iy1);

  CPPUNIT_ASSERT(fClone->xSource() == fx0);
  CPPUNIT_ASSERT(fClone->ySource() == fy0);
  CPPUNIT_ASSERT(fClone->xTarget() == fx1);
  CPPUNIT_ASSERT(fClone->yTarget() == fy1);

  CPPUNIT_ASSERT(dClone->xSource() == dx0);
  CPPUNIT_ASSERT(dClone->ySource() == dy0);
  CPPUNIT_ASSERT(dClone->xTarget() == dx1);
  CPPUNIT_ASSERT(dClone->yTarget() == dy1);

  // ---------
  // Tear Down
  // ---------

  delete iClone;
  delete fClone;
  delete dClone;
}


// ------------------------------------------------------------------
// ACCESS TO GEOMETRICAL FEATURES
// ------------------------------------------------------------------


void
GenSegmentTest::testLength()
{
  // ------
  // Set Up
  // ------
  
  int ix0 = 46;
  int iy0 = -1;
  int ix1 = 12;
  int iy1 = 157;
  IPoint iPt0(ix0, iy0);
  IPoint iPt1(ix1, iy1);
  ISegment iSeg(ix0, iy0, ix1, iy1);

  float fx0 = 51.3f;
  float fy0 = -14.1521f;
  float fx1 = 1.212f;
  float fy1 = -0.74861f;  
  FPoint fPt0(fx0, fy0);
  FPoint fPt1(fx1, fy1);
  FSegment fSeg(fx0, fy0, fx1, fy1);

  double dx0 = 11.564001;
  double dy0 = -0.0101;
  double dx1 = 20;
  double dy1 = 71.211;
  DPoint dPt0(dx0, dy0);
  DPoint dPt1(dx1, dy1);
  DSegment dSeg(dx0, dy0, dx1, dy1);

  // Trivial cases

  /*
   *   ^
   *   |     A
   * 5 |     +
   *   |     |\
   *   | l=3 | \ l=5
   *   |     |  \
   * 2 |   B +---+ C
   *   |      l=4
   *   |
   *   +-------------->
   *        13   17
   */

  double dxA = 13.;
  double dyA = 5.;
  double dxB = 13.;
  double dyB = 2.;
  double dxC = 17.;
  double dyC = 2.;
  DSegment dSegAB(dxA, dyA, dxB, dyB);
  DSegment dSegBC(dxB, dyB, dxC, dyC);
  DSegment dSegAC(dxA, dyA, dxC, dyC);

  // -----
  // Check
  // -----
  
  // Compare the length to the distance between the source
  // and the target computed by the appropriate global function
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iSeg.length(), qgDist(iPt0,iPt1), 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fSeg.length(), qgDist(fPt0,fPt1), 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dSeg.length(), qgDist(dPt0,dPt1), 0.0001);

  // Trivial cases
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dSegAB.length(), 3., 0.000001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dSegBC.length(), 4., 0.000001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dSegAC.length(), 5., 0.000001);  
}


void
GenSegmentTest::testSqrLength()
{
  // ------
  // Set Up
  // ------
  
  int ix0 = 46;
  int iy0 = -1;
  int ix1 = 12;
  int iy1 = 157;
  IPoint iPt0(ix0, iy0);
  IPoint iPt1(ix1, iy1);
  ISegment iSeg(ix0, iy0, ix1, iy1);

  float fx0 = 51.3f;
  float fy0 = -14.1521f;
  float fx1 = 1.212f;
  float fy1 = -0.74861f;  
  FPoint fPt0(fx0, fy0);
  FPoint fPt1(fx1, fy1);
  FSegment fSeg(fx0, fy0, fx1, fy1);

  double dx0 = 11.564001;
  double dy0 = -0.0101;
  double dx1 = 20;
  double dy1 = 71.211;
  DPoint dPt0(dx0, dy0);
  DPoint dPt1(dx1, dy1);
  DSegment dSeg(dx0, dy0, dx1, dy1);

  // Trivial cases

  /*
   *   ^
   *   |     A
   * 5 |     +
   *   |     |\
   *   | l=3 | \ l=5
   *   |     |  \
   * 2 |   B +---+ C
   *   |      l=4
   *   |
   *   +-------------->
   *        13   17
   */

  double dxA = 13.;
  double dyA = 5.;
  double dxB = 13.;
  double dyB = 2.;
  double dxC = 17.;
  double dyC = 2.;
  DSegment dSegAB(dxA, dyA, dxB, dyB);
  DSegment dSegBC(dxB, dyB, dxC, dyC);
  DSegment dSegAC(dxA, dyA, dxC, dyC);

  // -----
  // Check
  // -----
  
  // Compare the squared length to the distance between the source
  // and the target computed by the appropriate global function
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iSeg.sqr_length(), qgSqr_dist(iPt0,iPt1), 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fSeg.sqr_length(), qgSqr_dist(fPt0,fPt1), 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dSeg.sqr_length(), qgSqr_dist(dPt0,dPt1), 0.0001);

  // Trivial cases
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dSegAB.sqr_length(),  9., 0.000001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dSegBC.sqr_length(), 16., 0.000001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dSegAC.sqr_length(), 25., 0.000001);  
}


void
GenSegmentTest::testRho()
{
  // ------
  // Set Up
  // ------
  
  /* Segments parallel to the Y axis
   *
   *               Y
   *  iSegX3       ^
   *    ^          |           ^
   *    |      ^   ^           |
   *    |      |   | iSegX0    | iSegX1
   *    +      |   +           |
   *           |   |           +
   * ----------|---+---------------> X
   *           |  0|
   *           |   |  ^
   *    iSegX4 |   |  | iSegX2
   *           |   |  |
   *           |   |  +
   *           +   |
   */

  ISegment iSegX0 (0,100, 0,101);    // X = 0
  ISegment iSegX00(0,101, 0,100);    // Opposite orientation

  ISegment iSegX1(20,1, 20,7);       // X = 20
  ISegment iSegX10(20,7, 20,3);      // Opposite orientation

  ISegment iSegX2(2,-5, 2,-2);       // X = 2
  ISegment iSegX20(2,-2, 2,-5);      // Opposite orientation

  ISegment iSegX3(-30,5, -30,6);     // X = -30
  ISegment iSegX30(-30,6, -30,5);    // Opposite orientation

  ISegment iSegX4(-9,-5, -9,1000);   // X = -9
  ISegment iSegX40(-9,1000, -9,-5);  // Opposite orientation

  /* Segments parallel to the X axis
   *
   *               Y
   *               ^
   *               |
   *       fSegY1  |
   *     +-------->+
   *               |
   *               |   fSegY0
   * -+------------------>---------> X
   *              0|
   *              +---->
   *               | fSegY2
   *               |
   *               |
   */

  FSegment fSegY0(-100000.876f,0.f, 29.56237f,0.f);     // Y = 0
  FSegment fSegY00(29.56237f,0.f, -100000.876f,0.f);    // Opposite orientation

  FSegment fSegY1(-5.f,4.1436f, 0.f,4.1436f);           // Y = 4.1436
  FSegment fSegY10(0.f,4.1436f, -5.f,4.1436f);          // Opposite orientation

  FSegment fSegY2(-0.0002f,-897.354f, 2.f,-897.354f);   // Y = -897.354
  FSegment fSegY20(2.f,-897.354f, -0.0002f,-897.354f);  // Opposite orientation

  // rho ==  2 * sqrt(2)
  DSegment dSeg2neg(5.,1., 7.,3.);

  // rho ==  2 * sqrt(2)
  DSegment dSeg2pos(4.,0., -1.,5.);

  // rho ==  4 * sqrt(2)
  DSegment dSeg4neg(-4.,-4., -2.,-6.);

  // rho ==  4 * sqrt(2)
  DSegment dSeg4pos(-2.,6., -4.,4);

  // rho == 0
  DSegment dSeg0(-5.,-1., 5.,1.);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_DOUBLES_EQUAL(iSegX0.rho(),    0., 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iSegX00.rho(),   0., 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iSegX1.rho(),   20., 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iSegX10.rho(),  20., 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iSegX2.rho(),    2., 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iSegX20.rho(),   2., 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iSegX3.rho(),   30., 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iSegX30.rho(),  30., 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iSegX4.rho(),    9., 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iSegX40.rho(),   9., 0.0001);  

  CPPUNIT_ASSERT_DOUBLES_EQUAL(fSegY0.rho(),       0., 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fSegY00.rho(),      0., 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fSegY1.rho(),   4.1436, 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fSegY10.rho(),  4.1436, 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fSegY2.rho(),  897.354, 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fSegY20.rho(), 897.354, 0.0001);  

  CPPUNIT_ASSERT_DOUBLES_EQUAL(dSeg2neg.rho(), 2. * Math::QG_SQRT_2, 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dSeg2pos.rho(), 2. * Math::QG_SQRT_2, 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dSeg4neg.rho(), 4. * Math::QG_SQRT_2, 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dSeg4pos.rho(), 4. * Math::QG_SQRT_2, 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dSeg0.rho(),                      0., 0.0001);
}


void
GenSegmentTest::testAngles()
{
  // ------
  // Set Up
  // ------
  
  /* Segments parallel to the axis
   *
   *               Y
   *               ^
   *        +      |
   *        ^      |     segXP
   *  segYP |      |   +------->+
   *        |      |
   *        +      |
   * --------------+---------------> X
   *              0|
   *        +      |
   *        |      |  +<-------+
   *  segYN |      |     segXN
   *        v      |
   *        +      |
   */

  FSegment segXP(   12.11, 48.845,    19.19,  48.845);
  FSegment segXN(    800., -36.75,    2.732,  -36.75);
  FSegment segYP(-1024.33,   0.51, -1024.33, 7853.64);
  FSegment segYN(  -0.004,  -12.3,   -0.004,   -127.);

  /* 
   *                  Y
   *                  ^
   *         +        |      +
   *          ^       |     ^
   * segP2     \      |    / segP1
   * a == 3PI/4 \     |   /  angle == PI/4
   *             +    |  +
   * -----------------+---------------> X
   *                 0| +
   *             +    |  \
   * a == 5PI/4 /     |   \  segP4
   * segP3     /      |    v a == 7PI/4
   *          v       |     +
   *         +        |
   */

  FSegment segP1(1.1, 1.1, 80764.32, 80764.32);
  FSegment segP2(0., 0., -433.2, 433.2);
  FSegment segP3(-89.615, -89.615, -90., -90.);
  FSegment segP4(545.76, -545.76, 667.32, -667.32);

  // -------
  // Process
  // -------

  double tXP  = segXP.theta();         // 0
  double tXPd = segXP.thetaDegrees();  // 0
  double aXP  = segXP.angle();         // 0
  double aXPd = segXP.angleDegrees();  // 0
  double sXP  = segXP.slope();         // 0
  double sXPd = segXP.slopeDegrees();  // 0

  double tXN  = segXN.theta();         // PI
  double tXNd = segXN.thetaDegrees();  // 180
  double aXN  = segXN.angle();         // PI
  double aXNd = segXN.angleDegrees();  // 180
  double sXN  = segXN.slope();         // 0
  double sXNd = segXN.slopeDegrees();  // 0

  double tYP  = segYP.theta();         // PI/2
  double tYPd = segYP.thetaDegrees();  // 90
  double aYP  = segYP.angle();         // PI/2
  double aYPd = segYP.angleDegrees();  // 90
  double sYP  = segYP.slope();         // PI/2
  double sYPd = segYP.slopeDegrees();  // 90

  double tYN  = segYN.theta();         // 3PI/2
  double tYNd = segYN.thetaDegrees();  // 270
  double aYN  = segYN.angle();         // 3PI/2
  double aYNd = segYN.angleDegrees();  // 270
  double sYN  = segYN.slope();         // PI/2
  double sYNd = segYN.slopeDegrees();  // 90

  double tP1  = segP1.theta();         // PI/4
  double tP1d = segP1.thetaDegrees();  // 45
  double aP1  = segP1.angle();         // PI/4
  double aP1d = segP1.angleDegrees();  // 45
  double sP1  = segP1.slope();         // PI/4
  double sP1d = segP1.slopeDegrees();  // 45

  double tP2  = segP2.theta();         // 3PI/4
  double tP2d = segP2.thetaDegrees();  // 135
  double aP2  = segP2.angle();         // 3PI/4
  double aP2d = segP2.angleDegrees();  // 135
  double sP2  = segP2.slope();         // 3PI/4
  double sP2d = segP2.slopeDegrees();  // 135

  double tP3  = segP3.theta();         // 5PI/4
  double tP3d = segP3.thetaDegrees();  // 225
  double aP3  = segP3.angle();         // 5PI/4
  double aP3d = segP3.angleDegrees();  // 225
  double sP3  = segP3.slope();         // PI/4
  double sP3d = segP3.slopeDegrees();  // 45

  double tP4  = segP4.theta();         // 7PI/4
  double tP4d = segP4.thetaDegrees();  // 315
  double aP4  = segP4.angle();         // 7PI/4
  double aP4d = segP4.angleDegrees();  // 315
  double sP4  = segP4.slope();         // 3PI/4
  double sP4d = segP4.slopeDegrees();  // 135

  // -----
  // Check
  // -----
  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(tXP,  0.,    0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(tXPd, 0.,    0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(aXP,  0.,    0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(aXPd, 0.,    0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(sXP,  0.,    0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(sXPd, 0.,    0.001);

  CPPUNIT_ASSERT_DOUBLES_EQUAL(tXN,  Math::QG_PI, 0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(tXNd, 180.,        0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(aXN,  Math::QG_PI, 0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(aXNd, 180.,        0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(sXN,  0.,          0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(sXNd, 0.,          0.001);

  CPPUNIT_ASSERT_DOUBLES_EQUAL(tYP,  Math::QG_PI_2, 0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(tYPd, 90.,           0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(aYP,  Math::QG_PI_2, 0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(aYPd, 90.,           0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(sYP,  Math::QG_PI_2, 0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(sYPd, 90.,           0.001);

  CPPUNIT_ASSERT_DOUBLES_EQUAL(tYN,  3. * Math::QG_PI_2, 0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(tYNd, 270.,               0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(aYN,  3. * Math::QG_PI_2, 0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(aYNd, 270.,               0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(sYN,  Math::QG_PI_2,      0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(sYNd, 90.,                0.001);

  CPPUNIT_ASSERT_DOUBLES_EQUAL(tP1,  Math::QG_PI_4,     0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(tP1d, 45.,               0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(aP1,  Math::QG_PI_4,     0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(aP1d, 45.,               0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(sP1,  Math::QG_PI_4,     0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(sP1d, 45.,               0.001);

  CPPUNIT_ASSERT_DOUBLES_EQUAL(tP2,  3. * Math::QG_PI_4,  0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(tP2d, 135.,                0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(aP2,  3. * Math::QG_PI_4,  0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(aP2d, 135.,                0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(sP2,  3. * Math::QG_PI_4,  0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(sP2d, 135.,                0.001);

  CPPUNIT_ASSERT_DOUBLES_EQUAL(tP3,  5. * Math::QG_PI_4,  0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(tP3d, 225.,                0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(aP3,  5. * Math::QG_PI_4,  0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(aP3d, 225.,                0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(sP3,  Math::QG_PI_4,       0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(sP3d, 45.,                 0.001);

  CPPUNIT_ASSERT_DOUBLES_EQUAL(tP4,  7. * Math::QG_PI_4,  0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(tP4d, 315.,                0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(aP4,  7. * Math::QG_PI_4,  0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(aP4d, 315.,                0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(sP4,  3. * Math::QG_PI_4,  0.001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(sP4d, 135.,                0.001);
}


// ------------------------------------------------------------------
// G E O M E T R I C A L   P R E D I C A T E S
// ------------------------------------------------------------------


void
GenSegmentTest::testContains()
{
  // ------
  // Set Up
  // ------

  // A segment defining the line y = 3x + 1
  ISegment iS1(1,  4, 8, 25);
  ISegment iS2(8, 25, 1,  4);      // Reverse orientation
  DSegment dS1(1.,  4., 8., 25.);
  DSegment dS2(8., 25., 1.,  4.);  // Reverse orientation

  // Points exactly belonging to the segment
  IPoint i01(1,  4);
  IPoint i02(4, 13);
  IPoint i03(7, 22);
  IPoint i04(8, 25);
  DPoint d01(1.,  4.);
  DPoint d02(4., 13.);
  DPoint d03(7., 22.);
  DPoint d04(8., 25.);

  // Points at less than 1 unit far from the segment
  IPoint i11(2, 5);
  IPoint i12(2, 9);
  IPoint i13(5, 14);
  DPoint d11(2.,  5.);
  DPoint d12(2.,  9.);
  DPoint d13(5., 14.);

  // Points between 1 and 2 units far from the segment
  IPoint i21(1,   2);
  IPoint i22(10, 25);
  IPoint i23(6,  14);
  DPoint d21(1.,  2.);
  DPoint d22(10.,25.);
  DPoint d23(6., 14.);

  // Points very far from the segment
  IPoint iF1(-100,     3);
  IPoint iF2(1873, 25916);
  IPoint iF3(-783, -9858);
  DPoint dF1(-100.,     3.);
  DPoint dF2(1873., 25916.);
  DPoint dF3(-783., -9858.);

  // -----
  // Check
  // -----

  // DEFAULT DISTANCE == 0.001
  // =========================

  CPPUNIT_ASSERT( iS1.contains(i01) ); // Exact
  CPPUNIT_ASSERT( iS2.contains(i01) );
  CPPUNIT_ASSERT( iS1.contains(i02) );
  CPPUNIT_ASSERT( iS2.contains(i02) );
  CPPUNIT_ASSERT( iS1.contains(i03) );
  CPPUNIT_ASSERT( iS2.contains(i03) );
  CPPUNIT_ASSERT( iS1.contains(i04) );
  CPPUNIT_ASSERT( iS2.contains(i04) );

  CPPUNIT_ASSERT( dS1.contains(d01) ); // Exact
  CPPUNIT_ASSERT( dS2.contains(d01) );
  CPPUNIT_ASSERT( dS1.contains(d02) );
  CPPUNIT_ASSERT( dS2.contains(d02) );
  CPPUNIT_ASSERT( dS1.contains(d03) );
  CPPUNIT_ASSERT( dS2.contains(d03) );
  CPPUNIT_ASSERT( dS1.contains(d04) );
  CPPUNIT_ASSERT( dS2.contains(d04) );

  CPPUNIT_ASSERT( !iS1.contains(i11) ); // Less than 1 unit
  CPPUNIT_ASSERT( !iS2.contains(i11) );
  CPPUNIT_ASSERT( !iS1.contains(i12) );
  CPPUNIT_ASSERT( !iS2.contains(i12) );
  CPPUNIT_ASSERT( !iS1.contains(i13) );
  CPPUNIT_ASSERT( !iS2.contains(i13) );

  CPPUNIT_ASSERT( !dS1.contains(d11) ); // Less than 1 unit
  CPPUNIT_ASSERT( !dS2.contains(d11) );
  CPPUNIT_ASSERT( !dS1.contains(d12) );
  CPPUNIT_ASSERT( !dS2.contains(d12) );
  CPPUNIT_ASSERT( !dS1.contains(d13) );
  CPPUNIT_ASSERT( !dS2.contains(d13) );

  CPPUNIT_ASSERT( !iS1.contains(i21) ); // Between 1 and 2
  CPPUNIT_ASSERT( !iS2.contains(i21) );
  CPPUNIT_ASSERT( !iS1.contains(i22) );
  CPPUNIT_ASSERT( !iS2.contains(i22) );
  CPPUNIT_ASSERT( !iS1.contains(i23) );
  CPPUNIT_ASSERT( !iS2.contains(i23) );

  CPPUNIT_ASSERT( !dS1.contains(d21) ); // Between 1 and 2
  CPPUNIT_ASSERT( !dS2.contains(d21) );
  CPPUNIT_ASSERT( !dS1.contains(d22) );
  CPPUNIT_ASSERT( !dS2.contains(d22) );
  CPPUNIT_ASSERT( !dS1.contains(d23) );
  CPPUNIT_ASSERT( !dS2.contains(d23) );

  CPPUNIT_ASSERT( !iS1.contains(iF1) ); // Very far
  CPPUNIT_ASSERT( !iS2.contains(iF1) );
  CPPUNIT_ASSERT( !iS1.contains(iF2) );
  CPPUNIT_ASSERT( !iS2.contains(iF2) );
  CPPUNIT_ASSERT( !iS1.contains(iF3) );
  CPPUNIT_ASSERT( !iS2.contains(iF3) );

  CPPUNIT_ASSERT( !dS1.contains(dF1) ); // Very far
  CPPUNIT_ASSERT( !dS2.contains(dF1) );
  CPPUNIT_ASSERT( !dS1.contains(dF2) );
  CPPUNIT_ASSERT( !dS2.contains(dF2) );
  CPPUNIT_ASSERT( !dS1.contains(dF3) );
  CPPUNIT_ASSERT( !dS2.contains(dF3) );

  // DISTANCE == 1
  // =============

  CPPUNIT_ASSERT( iS1.contains(i01, 1.) ); // Exact
  CPPUNIT_ASSERT( iS2.contains(i01, 1.) );
  CPPUNIT_ASSERT( iS1.contains(i02, 1.) );
  CPPUNIT_ASSERT( iS2.contains(i02, 1.) );
  CPPUNIT_ASSERT( iS1.contains(i03, 1.) );
  CPPUNIT_ASSERT( iS2.contains(i03, 1.) );
  CPPUNIT_ASSERT( iS1.contains(i04, 1.) );
  CPPUNIT_ASSERT( iS2.contains(i04, 1.) );

  CPPUNIT_ASSERT( dS1.contains(d01, 1.) ); // Exact
  CPPUNIT_ASSERT( dS2.contains(d01, 1.) );
  CPPUNIT_ASSERT( dS1.contains(d02, 1.) );
  CPPUNIT_ASSERT( dS2.contains(d02, 1.) );
  CPPUNIT_ASSERT( dS1.contains(d03, 1.) );
  CPPUNIT_ASSERT( dS2.contains(d03, 1.) );
  CPPUNIT_ASSERT( dS1.contains(d04, 1.) );
  CPPUNIT_ASSERT( dS2.contains(d04, 1.) );

  CPPUNIT_ASSERT( iS1.contains(i11, 1.) ); // Less than 1 unit
  CPPUNIT_ASSERT( iS2.contains(i11, 1.) );
  CPPUNIT_ASSERT( iS1.contains(i12, 1.) );
  CPPUNIT_ASSERT( iS2.contains(i12, 1.) );
  CPPUNIT_ASSERT( iS1.contains(i13, 1.) );
  CPPUNIT_ASSERT( iS2.contains(i13, 1.) );

  CPPUNIT_ASSERT( dS1.contains(d11, 1.) ); // Less than 1 unit
  CPPUNIT_ASSERT( dS2.contains(d11, 1.) );
  CPPUNIT_ASSERT( dS1.contains(d12, 1.) );
  CPPUNIT_ASSERT( dS2.contains(d12, 1.) );
  CPPUNIT_ASSERT( dS1.contains(d13, 1.) );
  CPPUNIT_ASSERT( dS2.contains(d13, 1.) );

  CPPUNIT_ASSERT( !iS1.contains(i21, 1.) ); // Between 1 and 2
  CPPUNIT_ASSERT( !iS2.contains(i21, 1.) );
  CPPUNIT_ASSERT( !iS1.contains(i22, 1.) );
  CPPUNIT_ASSERT( !iS2.contains(i22, 1.) );
  CPPUNIT_ASSERT( !iS1.contains(i23, 1.) );
  CPPUNIT_ASSERT( !iS2.contains(i23, 1.) );

  CPPUNIT_ASSERT( !dS1.contains(d21, 1.) ); // Between 1 and 2
  CPPUNIT_ASSERT( !dS2.contains(d21, 1.) );
  CPPUNIT_ASSERT( !dS1.contains(d22, 1.) );
  CPPUNIT_ASSERT( !dS2.contains(d22, 1.) );
  CPPUNIT_ASSERT( !dS1.contains(d23, 1.) );
  CPPUNIT_ASSERT( !dS2.contains(d23, 1.) );

  CPPUNIT_ASSERT( !iS1.contains(iF1, 1.) ); // Very far
  CPPUNIT_ASSERT( !iS2.contains(iF1, 1.) );
  CPPUNIT_ASSERT( !iS1.contains(iF2, 1.) );
  CPPUNIT_ASSERT( !iS2.contains(iF2, 1.) );
  CPPUNIT_ASSERT( !iS1.contains(iF3, 1.) );
  CPPUNIT_ASSERT( !iS2.contains(iF3, 1.) );

  CPPUNIT_ASSERT( !dS1.contains(dF1, 1.) ); // Very far
  CPPUNIT_ASSERT( !dS2.contains(dF1, 1.) );
  CPPUNIT_ASSERT( !dS1.contains(dF2, 1.) );
  CPPUNIT_ASSERT( !dS2.contains(dF2, 1.) );
  CPPUNIT_ASSERT( !dS1.contains(dF3, 1.) );
  CPPUNIT_ASSERT( !dS2.contains(dF3, 1.) );

  // DISTANCE == 2.1
  // ===============

  CPPUNIT_ASSERT( iS1.contains(i01, 2.1) ); // Exact
  CPPUNIT_ASSERT( iS2.contains(i01, 2.1) );
  CPPUNIT_ASSERT( iS1.contains(i02, 2.1) );
  CPPUNIT_ASSERT( iS2.contains(i02, 2.1) );
  CPPUNIT_ASSERT( iS1.contains(i03, 2.1) );
  CPPUNIT_ASSERT( iS2.contains(i03, 2.1) );
  CPPUNIT_ASSERT( iS1.contains(i04, 2.1) );
  CPPUNIT_ASSERT( iS2.contains(i04, 2.1) );

  CPPUNIT_ASSERT( dS1.contains(d01, 2.1) ); // Exact
  CPPUNIT_ASSERT( dS2.contains(d01, 2.1) );
  CPPUNIT_ASSERT( dS1.contains(d02, 2.1) );
  CPPUNIT_ASSERT( dS2.contains(d02, 2.1) );
  CPPUNIT_ASSERT( dS1.contains(d03, 2.1) );
  CPPUNIT_ASSERT( dS2.contains(d03, 2.1) );
  CPPUNIT_ASSERT( dS1.contains(d04, 2.1) );
  CPPUNIT_ASSERT( dS2.contains(d04, 2.1) );

  CPPUNIT_ASSERT( iS1.contains(i11, 2.1) ); // Less than 1 unit
  CPPUNIT_ASSERT( iS2.contains(i11, 2.1) );
  CPPUNIT_ASSERT( iS1.contains(i12, 2.1) );
  CPPUNIT_ASSERT( iS2.contains(i12, 2.1) );
  CPPUNIT_ASSERT( iS1.contains(i13, 2.1) );
  CPPUNIT_ASSERT( iS2.contains(i13, 2.1) );

  CPPUNIT_ASSERT( dS1.contains(d11, 2.1) ); // Less than 1 unit
  CPPUNIT_ASSERT( dS2.contains(d11, 2.1) );
  CPPUNIT_ASSERT( dS1.contains(d12, 2.1) );
  CPPUNIT_ASSERT( dS2.contains(d12, 2.1) );
  CPPUNIT_ASSERT( dS1.contains(d13, 2.1) );
  CPPUNIT_ASSERT( dS2.contains(d13, 2.1) );

  CPPUNIT_ASSERT( iS1.contains(i21, 2.1) ); // Between 1 and 2
  CPPUNIT_ASSERT( iS2.contains(i21, 2.1) );
  CPPUNIT_ASSERT( iS1.contains(i22, 2.1) );
  CPPUNIT_ASSERT( iS2.contains(i22, 2.1) );
  CPPUNIT_ASSERT( iS1.contains(i23, 2.1) );
  CPPUNIT_ASSERT( iS2.contains(i23, 2.1) );

  CPPUNIT_ASSERT( dS1.contains(d21, 2.1) ); // Between 1 and 2
  CPPUNIT_ASSERT( dS2.contains(d21, 2.1) );
  CPPUNIT_ASSERT( dS1.contains(d22, 2.1) );
  CPPUNIT_ASSERT( dS2.contains(d22, 2.1) );
  CPPUNIT_ASSERT( dS1.contains(d23, 2.1) );
  CPPUNIT_ASSERT( dS2.contains(d23, 2.1) );

  CPPUNIT_ASSERT( !iS1.contains(iF1, 2.1) ); // Very far
  CPPUNIT_ASSERT( !iS2.contains(iF1, 2.1) );
  CPPUNIT_ASSERT( !iS1.contains(iF2, 2.1) );
  CPPUNIT_ASSERT( !iS2.contains(iF2, 2.1) );
  CPPUNIT_ASSERT( !iS1.contains(iF3, 2.1) );
  CPPUNIT_ASSERT( !iS2.contains(iF3, 2.1) );

  CPPUNIT_ASSERT( !dS1.contains(dF1, 2.1) ); // Very far
  CPPUNIT_ASSERT( !dS2.contains(dF1, 2.1) );
  CPPUNIT_ASSERT( !dS1.contains(dF2, 2.1) );
  CPPUNIT_ASSERT( !dS2.contains(dF2, 2.1) );
  CPPUNIT_ASSERT( !dS1.contains(dF3, 2.1) );
  CPPUNIT_ASSERT( !dS2.contains(dF3, 2.1) );

  // DISTANCE == 100 000
  // ===================

  CPPUNIT_ASSERT( iS1.contains(i01, 100000) ); // Exact
  CPPUNIT_ASSERT( iS2.contains(i01, 100000) );
  CPPUNIT_ASSERT( iS1.contains(i02, 100000) );
  CPPUNIT_ASSERT( iS2.contains(i02, 100000) );
  CPPUNIT_ASSERT( iS1.contains(i03, 100000) );
  CPPUNIT_ASSERT( iS2.contains(i03, 100000) );
  CPPUNIT_ASSERT( iS1.contains(i04, 100000) );
  CPPUNIT_ASSERT( iS2.contains(i04, 100000) );

  CPPUNIT_ASSERT( dS1.contains(d01, 100000) ); // Exact
  CPPUNIT_ASSERT( dS2.contains(d01, 100000) );
  CPPUNIT_ASSERT( dS1.contains(d02, 100000) );
  CPPUNIT_ASSERT( dS2.contains(d02, 100000) );
  CPPUNIT_ASSERT( dS1.contains(d03, 100000) );
  CPPUNIT_ASSERT( dS2.contains(d03, 100000) );
  CPPUNIT_ASSERT( dS1.contains(d04, 100000) );
  CPPUNIT_ASSERT( dS2.contains(d04, 100000) );

  CPPUNIT_ASSERT( iS1.contains(i11, 100000) ); // Less than 1 unit
  CPPUNIT_ASSERT( iS2.contains(i11, 100000) );
  CPPUNIT_ASSERT( iS1.contains(i12, 100000) );
  CPPUNIT_ASSERT( iS2.contains(i12, 100000) );
  CPPUNIT_ASSERT( iS1.contains(i13, 100000) );
  CPPUNIT_ASSERT( iS2.contains(i13, 100000) );

  CPPUNIT_ASSERT( dS1.contains(d11, 100000) ); // Less than 1 unit
  CPPUNIT_ASSERT( dS2.contains(d11, 100000) );
  CPPUNIT_ASSERT( dS1.contains(d12, 100000) );
  CPPUNIT_ASSERT( dS2.contains(d12, 100000) );
  CPPUNIT_ASSERT( dS1.contains(d13, 100000) );
  CPPUNIT_ASSERT( dS2.contains(d13, 100000) );

  CPPUNIT_ASSERT( iS1.contains(i21, 100000) ); // Between 1 and 2
  CPPUNIT_ASSERT( iS2.contains(i21, 100000) );
  CPPUNIT_ASSERT( iS1.contains(i22, 100000) );
  CPPUNIT_ASSERT( iS2.contains(i22, 100000) );
  CPPUNIT_ASSERT( iS1.contains(i23, 100000) );
  CPPUNIT_ASSERT( iS2.contains(i23, 100000) );

  CPPUNIT_ASSERT( dS1.contains(d21, 100000) ); // Between 1 and 2
  CPPUNIT_ASSERT( dS2.contains(d21, 100000) );
  CPPUNIT_ASSERT( dS1.contains(d22, 100000) );
  CPPUNIT_ASSERT( dS2.contains(d22, 100000) );
  CPPUNIT_ASSERT( dS1.contains(d23, 100000) );
  CPPUNIT_ASSERT( dS2.contains(d23, 100000) );

  CPPUNIT_ASSERT( iS1.contains(iF1, 100000) ); // Very far
  CPPUNIT_ASSERT( iS2.contains(iF1, 100000) );
  CPPUNIT_ASSERT( iS1.contains(iF2, 100000) );
  CPPUNIT_ASSERT( iS2.contains(iF2, 100000) );
  CPPUNIT_ASSERT( iS1.contains(iF3, 100000) );
  CPPUNIT_ASSERT( iS2.contains(iF3, 100000) );

  CPPUNIT_ASSERT( dS1.contains(dF1, 100000) ); // Very far
  CPPUNIT_ASSERT( dS2.contains(dF1, 100000) );
  CPPUNIT_ASSERT( dS1.contains(dF2, 100000) );
  CPPUNIT_ASSERT( dS2.contains(dF2, 100000) );
  CPPUNIT_ASSERT( dS1.contains(dF3, 100000) );
  CPPUNIT_ASSERT( dS2.contains(dF3, 100000) );
}


// ------------------------------------------------------------------
// O P E R A T O R S
// ------------------------------------------------------------------


void
GenSegmentTest::testAssignmentOp()
{
  // ------
  // Set Up
  // ------
  
  int ix0 = 46;
  int iy0 = -1;
  int ix1 = 12;
  int iy1 = 157;
  ISegment iSeg(ix0, iy0, ix1, iy1);

  float fx0 = 51.3f;
  float fy0 = -14.1521f;
  float fx1 = 1.212f;
  float fy1 = -0.74861f;  
  FSegment fSeg(fx0, fy0, fx1, fy1);

  double dx0 = 11.564001;
  double dy0 = -0.0101;
  double dx1 = 20;
  double dy1 = 71.211;
  DSegment dSeg(dx0, dy0, dx1, dy1);

  // -------
  // Process
  // -------

  ISegment iDupSeg;
  FSegment fDupSeg;
  DSegment dDupSeg;
  
  iDupSeg = iSeg;
  fDupSeg = fSeg;
  dDupSeg = dSeg;

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT(iDupSeg.xSource() == ix0);
  CPPUNIT_ASSERT(iDupSeg.ySource() == iy0);
  CPPUNIT_ASSERT(iDupSeg.xTarget() == ix1);
  CPPUNIT_ASSERT(iDupSeg.yTarget() == iy1);

  CPPUNIT_ASSERT(fDupSeg.xSource() == fx0);
  CPPUNIT_ASSERT(fDupSeg.ySource() == fy0);
  CPPUNIT_ASSERT(fDupSeg.xTarget() == fx1);
  CPPUNIT_ASSERT(fDupSeg.yTarget() == fy1);

  CPPUNIT_ASSERT(dDupSeg.xSource() == dx0);
  CPPUNIT_ASSERT(dDupSeg.ySource() == dy0);
  CPPUNIT_ASSERT(dDupSeg.xTarget() == dx1);
  CPPUNIT_ASSERT(dDupSeg.yTarget() == dy1);
}


void
GenSegmentTest::testEqualOp()
{
  // ------
  // Set Up
  // ------

  int ix0 = 46;
  int iy0 = -1;
  int ix1 = 12;
  int iy1 = 157;
  ISegment iSeg0(ix0, iy0, ix1, iy1);
  ISegment iSeg1(ix0, iy0 + 1, ix1 + 1, iy1 + 1);

  float fx0 = 51.3f;
  float fy0 = -14.1521f;
  float fx1 = 1.212f;
  float fy1 = -0.74861f;  
  FSegment fSeg0(fx0, fy0, fx1, fy1);
  FSegment fSeg1(fx0 + 1., fy0, fx1, fy1);

  double dx0 = 11.564001;
  double dy0 = -0.0101;
  double dx1 = 20;
  double dy1 = 71.211;
  DSegment dSeg0(dx0, dy0, dx1, dy1);
  DSegment dSeg1(dx0, dy0 + 1., dx1, dy1 + 1.);

  // -----
  // Check
  // -----

  // Check operator reflexivity
  CPPUNIT_ASSERT( iSeg0 == iSeg0 );
  CPPUNIT_ASSERT( fSeg0 == fSeg0 );
  CPPUNIT_ASSERT( dSeg0 == dSeg0 );

  // Check if a segment is equal to a copy of itself
  CPPUNIT_ASSERT( iSeg0 == ISegment(iSeg0) );
  CPPUNIT_ASSERT( fSeg0 == FSegment(fSeg0) );
  CPPUNIT_ASSERT( dSeg0 == DSegment(dSeg0) );

  // Check that a segment is not equal to another, different segment
  CPPUNIT_ASSERT( !(iSeg0 == iSeg1) );
  CPPUNIT_ASSERT( !(fSeg0 == fSeg1) );
  CPPUNIT_ASSERT( !(dSeg0 == dSeg1) );
}


void
GenSegmentTest::testNotEqualOp()
{
  // ------
  // Set Up
  // ------

  int ix0 = 46;
  int iy0 = -1;
  int ix1 = 12;
  int iy1 = 157;
  ISegment iSeg0(ix0, iy0, ix1, iy1);
  ISegment iSeg1(ix0 + 1, iy0, ix1, iy1 + 1);

  float fx0 = 51.3f;
  float fy0 = -14.1521f;
  float fx1 = 1.212f;
  float fy1 = -0.74861f;  
  FSegment fSeg0(fx0, fy0, fx1, fy1);
  FSegment fSeg1(fx0, fy0 + 1., fx1, fy1 + 1.);

  double dx0 = 11.564001;
  double dy0 = -0.0101;
  double dx1 = 20;
  double dy1 = 71.211;
  DSegment dSeg0(dx0, dy0, dx1, dy1);
  DSegment dSeg1(dx0 + 1., dy0 + 1., dx1 + 1., dy1 + 1.);

  // -----
  // Check
  // -----

  // Check if a segment is equal to itself using operator not equal
  CPPUNIT_ASSERT( !(iSeg0 != iSeg0) );
  CPPUNIT_ASSERT( !(fSeg0 != fSeg0) );
  CPPUNIT_ASSERT( !(dSeg0 != dSeg0) );

  // Check if a segment is equal to its copy using operator not equal
  CPPUNIT_ASSERT( !(iSeg0 != ISegment(iSeg0)) );
  CPPUNIT_ASSERT( !(fSeg0 != FSegment(fSeg0)) );
  CPPUNIT_ASSERT( !(dSeg0 != DSegment(dSeg0)) );

  // Check if two different segments are not equal.
  CPPUNIT_ASSERT( iSeg0 != iSeg1 );
  CPPUNIT_ASSERT( fSeg0 != fSeg1 );
  CPPUNIT_ASSERT( dSeg0 != dSeg1 );
}


// ------------------------------------------------------------------
// F U N C T I O N A L   O P E R A T O R S
// ------------------------------------------------------------------


void
GenSegmentTest::testEq()
{
  // ------
  // Set Up
  // ------

  int ix0 = 46;
  int iy0 = -1;
  int ix1 = 12;
  int iy1 = 157;
  ISegment iSeg(ix0, iy0, ix1, iy1);
  ISegment iSeg1(ix0, iy0 + 1, ix1 + 1, iy1 + 1);

  float fx0 = 51.3f;
  float fy0 = -14.1521f;
  float fx1 = 1.212f;
  float fy1 = -0.74861f;  
  FSegment fSeg(fx0, fy0, fx1, fy1);
  FSegment fSeg1(fx0 + 0.001, fy0, fx1, fy1);

  double dx0 = 11.564001;
  double dy0 = -0.0101;
  double dx1 = 20;
  double dy1 = 71.211;
  DSegment dSeg(dx0, dy0, dx1, dy1);
  DSegment dSeg1(dx0, dy0 + 1., dx1, dy1 + 1.);

  // -----
  // Check
  // -----

  // Check operator reflexivity
  CPPUNIT_ASSERT( iSeg.eq(iSeg) );
  CPPUNIT_ASSERT( fSeg.eq(fSeg) );
  CPPUNIT_ASSERT( dSeg.eq(dSeg) );

  // Check if a segment is equal to a copy of itself
  CPPUNIT_ASSERT( iSeg.eq(ISegment(iSeg)) );
  CPPUNIT_ASSERT( fSeg.eq(FSegment(fSeg)) );
  CPPUNIT_ASSERT( dSeg.eq(DSegment(dSeg)) );

  // Check that a segment is not equal to another, different segment
  CPPUNIT_ASSERT( !(iSeg.eq(iSeg1)) );
  CPPUNIT_ASSERT( !(fSeg.eq(fSeg1)) );
  CPPUNIT_ASSERT( !(dSeg.eq(dSeg1)) );
}


void
GenSegmentTest::testNotEq()
{
  // ------
  // Set Up
  // ------

  int ix0 = 46;
  int iy0 = -1;
  int ix1 = 12;
  int iy1 = 157;
  ISegment iSeg0(ix0, iy0, ix1, iy1);
  ISegment iSeg1(ix0 + 1, iy0, ix1, iy1 + 1);

  float fx0 = 51.3f;
  float fy0 = -14.1521f;
  float fx1 = 1.212f;
  float fy1 = -0.74861f;  
  FSegment fSeg0(fx0, fy0, fx1, fy1);
  FSegment fSeg1(fx0, fy0, fx1, fy1 + 0.001);

  double dx0 = 11.564001;
  double dy0 = -0.0101;
  double dx1 = 20;
  double dy1 = 71.211;
  DSegment dSeg0(dx0, dy0, dx1, dy1);
  DSegment dSeg1(dx0 + 1., dy0 + 1., dx1 + 1., dy1 + 1.);

  // -----
  // Check
  // -----

  // Check if a segment is equal to itself using operator not equal
  CPPUNIT_ASSERT( !(iSeg0.notEq(iSeg0)) );
  CPPUNIT_ASSERT( !(fSeg0.notEq(fSeg0)) );
  CPPUNIT_ASSERT( !(dSeg0.notEq(dSeg0)) );

  // Check if a segment is equal to its copy using operator not equal
  CPPUNIT_ASSERT( !(iSeg0.notEq(ISegment(iSeg0))) );
  CPPUNIT_ASSERT( !(fSeg0.notEq(FSegment(fSeg0))) );
  CPPUNIT_ASSERT( !(dSeg0.notEq(DSegment(dSeg0))) );

  // Check if two different segments are not equal.
  CPPUNIT_ASSERT( iSeg0.notEq(iSeg1) );
  CPPUNIT_ASSERT( fSeg0.notEq(fSeg1) );
  CPPUNIT_ASSERT( dSeg0.notEq(dSeg1) );
}


// ------------------------------------------------------------------
// G E O M E T R Y :   T R A N S L A T I O N
// ------------------------------------------------------------------

void
GenSegmentTest::testTranslate()
{
  // ------
  // Set Up
  // ------

  int ix0 = 46;
  int iy0 = -1;
  int ix1 = 12;
  int iy1 = 157;
  ISegment iSeg(ix0, iy0, ix1, iy1);

  float fx0 = 51.3f;
  float fy0 = -14.1521f;
  float fx1 = 1.212f;
  float fy1 = -0.74861f;  
  FSegment fSeg(fx0, fy0, fx1, fy1);

  double dx0 = 11.564001;
  double dy0 = -0.0101;
  double dx1 = 20;
  double dy1 = 71.211;
  DSegment dSeg(dx0, dy0, dx1, dy1);

  // -------
  // Process
  // -------

  iSeg.translate(18, 9965);
  fSeg.translate(0., 8756.2341);
  dSeg.translate(-0.004, -58435.1581123);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( iSeg.xSource(), ix0 + 18 );
  CPPUNIT_ASSERT_EQUAL( iSeg.ySource(), iy0 + 9965 );
  CPPUNIT_ASSERT_EQUAL( iSeg.xTarget(), ix1 + 18 );
  CPPUNIT_ASSERT_EQUAL( iSeg.yTarget(), iy1 + 9965 );

  CPPUNIT_ASSERT_DOUBLES_EQUAL( fSeg.xSource(), fx0,             0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( fSeg.ySource(), fy0 + 8756.2341, 0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( fSeg.xTarget(), fx1,             0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( fSeg.yTarget(), fy1 + 8756.2341, 0.001 );

  CPPUNIT_ASSERT_DOUBLES_EQUAL( dSeg.xSource(), dx0 - 0.004,         0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( dSeg.ySource(), dy0 - 58435.1581123, 0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( dSeg.xTarget(), dx1 - 0.004,         0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( dSeg.yTarget(), dy1 - 58435.1581123, 0.001 );
}


// ------------------------------------------------------------------
// (D E ) S E R I A L I Z A T I O N
// ------------------------------------------------------------------


void 
GenSegmentTest::testSerializeDeserialize()
{
  // ------
  // Set Up
  // ------
  
  int ix0 = 98;
  int iy0 = -24;
  int ix1 = 16;
  int iy1 = 91;  
  ISegment iSeg(ix0, iy0, ix1, iy1);
  ISegment iOutInSeg;
  
  float fx0 = 0.8f;
  float fy0 = -2.425f;
  float fx1 = 1905.2f;
  float fy1 = 1.0f;  
  FSegment fSeg(fx0, fy0, fx1, fy1);
  FSegment fOutInSeg;

  double dx0 = 13.1348;
  double dy0 = -24.41;
  double dx1 = 1145.5;
  double dy1 = 91.05953;  
  DSegment dSeg(dx0, dy0, dx1, dy1);
  DSegment dOutInSeg;

  // -------
  // Process
  // -------
  
  std::stringstream ss;
  
  ss << iSeg;
  ss >> iOutInSeg;
  ss.flush();
  
  ss << fSeg;
  ss >> fOutInSeg;
  ss.flush();

  ss << dSeg;
  ss >> dOutInSeg;
  ss.flush();

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT(iSeg.source() == iOutInSeg.source());
  CPPUNIT_ASSERT(iSeg.target() == iOutInSeg.target());

  CPPUNIT_ASSERT_DOUBLES_EQUAL(fSeg.xSource(), fOutInSeg.xSource(), 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fSeg.ySource(), fOutInSeg.ySource(), 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fSeg.xTarget(), fOutInSeg.xTarget(), 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fSeg.yTarget(), fOutInSeg.yTarget(), 0.0001);

  CPPUNIT_ASSERT_DOUBLES_EQUAL(dSeg.xSource(), dOutInSeg.xSource(), 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dSeg.ySource(), dOutInSeg.ySource(), 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dSeg.xTarget(), dOutInSeg.xTarget(), 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dSeg.yTarget(), dOutInSeg.yTarget(), 0.0001);
}

// ----------------------------------------------------------------------
