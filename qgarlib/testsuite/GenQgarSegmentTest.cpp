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
 * @file  GenQgarSegmentTest.cpp
 * @brief Implementation of class GenQgarSegmentTest
 *
 *        See file GenQgarSegmentTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 24, 2003  09:40
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenQgarSegmentTest.cpp,v 1.10 2005/09/14 10:53:38 masini Exp $ */



// QGAR
#include <qgarlib/math.h>
#include <qgarlib/primitives.h>
// QGAR TESTS
#include "GenQgarSegmentTest.h"



using namespace qgar;



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
GenQgarSegmentTest::setUp()
{
  /* EMPTY */
}

void
GenQgarSegmentTest::tearDown()
{
  /* EMPTY */
}


// ------------------------------------------------------------------
// C O N S T R U C T O R S
// ------------------------------------------------------------------


void
GenQgarSegmentTest::testDefaultConstructor()
{
  // ------
  // Set Up
  // ------

  IQgarSegment iqSeg0;
  IQgarSegment iqSeg(2);
  FQgarSegment fqSeg(2, QGE_COLOR_BLUE);
  DQgarSegment dqSeg(2, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_LS);

  IPoint iPt0(0,0);
  FPoint fPt0(0.f,0.f);
  DPoint dPt0(0.,0.);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqSeg0.source()              == iPt0                );
  CPPUNIT_ASSERT( iqSeg0.target()              == iPt0                );
  CPPUNIT_ASSERT( iqSeg0.thickness()           == 1                   );
  CPPUNIT_ASSERT( iqSeg0.color()               == QGE_COLOR_DEFAULT   );
  CPPUNIT_ASSERT( iqSeg0.outline()             == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( iqSeg0.accessGeomStructure() == ISegment()          );

  CPPUNIT_ASSERT( iqSeg.source()              == iPt0                );
  CPPUNIT_ASSERT( iqSeg.target()              == iPt0                );
  CPPUNIT_ASSERT( iqSeg.thickness()           == 2                   );
  CPPUNIT_ASSERT( iqSeg.color()               == QGE_COLOR_DEFAULT   );
  CPPUNIT_ASSERT( iqSeg.outline()             == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( iqSeg.accessGeomStructure() == ISegment()          );

  CPPUNIT_ASSERT( fqSeg.source()              == fPt0                );
  CPPUNIT_ASSERT( fqSeg.target()              == fPt0                );
  CPPUNIT_ASSERT( fqSeg.thickness()           == 2                   );
  CPPUNIT_ASSERT( fqSeg.color()               == QGE_COLOR_BLUE      );
  CPPUNIT_ASSERT( fqSeg.outline()             == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( fqSeg.accessGeomStructure() == FSegment()          );

  CPPUNIT_ASSERT( dqSeg.source()              == dPt0                );
  CPPUNIT_ASSERT( dqSeg.target()              == dPt0                );
  CPPUNIT_ASSERT( dqSeg.thickness()           == 2                   );
  CPPUNIT_ASSERT( dqSeg.color()               == QGE_COLOR_BLUE      );
  CPPUNIT_ASSERT( dqSeg.outline()             == QGE_OUTLINE_DASH_LS );
  CPPUNIT_ASSERT( dqSeg.accessGeomStructure() == DSegment()          );
}


void 
GenQgarSegmentTest::testBuildFromSegment()
{
  // ------
  // Set Up
  // ------
  
  int ix0 = 91;
  int iy0 = -4;
  int ix1 = 46;
  int iy1 = 12;  
  IPoint iPt0(ix0,iy0);
  IPoint iPt1(ix1,iy1);
  ISegment iSeg(ix0, iy0, ix1, iy1);

  float fx0 = 0.81F;
  float fy0 = -2.425F;
  float fx1 = 1905.2F;
  float fy1 = 1.10F;  
  FPoint fPt0(fx0,fy0);
  FPoint fPt1(fx1,fy1);
  FSegment fSeg(fx0, fy0, fx1, fy1);

  double dx0 = 13.1348;
  double dy0 = -24.41;
  double dx1 = 45.5;
  double dy1 = 1.05953;  
  DPoint dPt0(dx0,dy0);
  DPoint dPt1(dx1,dy1);
  DSegment dSeg(dx0, dy0, dx1, dy1);

  // -------
  // Process
  // -------

  IQgarSegment iqSeg0(iSeg);
  IQgarSegment iqSeg (iSeg, 2);
  FQgarSegment fqSeg (fSeg, 2, QGE_COLOR_BLUE);
  DQgarSegment dqSeg (dSeg, 2, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqSeg0.source()              == iPt0                );
  CPPUNIT_ASSERT( iqSeg0.target()              == iPt1                );
  CPPUNIT_ASSERT( iqSeg0.thickness()           == 1                   );
  CPPUNIT_ASSERT( iqSeg0.color()               == QGE_COLOR_DEFAULT   );
  CPPUNIT_ASSERT( iqSeg0.outline()             == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( iqSeg0.accessGeomStructure() == iSeg                );

  CPPUNIT_ASSERT( iqSeg.source()              == iPt0                );
  CPPUNIT_ASSERT( iqSeg.target()              == iPt1                );
  CPPUNIT_ASSERT( iqSeg.thickness()           == 2                   );
  CPPUNIT_ASSERT( iqSeg.color()               == QGE_COLOR_DEFAULT   );
  CPPUNIT_ASSERT( iqSeg.outline()             == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( iqSeg.accessGeomStructure() == iSeg                );

  CPPUNIT_ASSERT( fqSeg.source()              == fPt0                );
  CPPUNIT_ASSERT( fqSeg.target()              == fPt1                );
  CPPUNIT_ASSERT( fqSeg.thickness()           == 2                   );
  CPPUNIT_ASSERT( fqSeg.color()               == QGE_COLOR_BLUE      );
  CPPUNIT_ASSERT( fqSeg.outline()             == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( fqSeg.accessGeomStructure() == fSeg                );

  CPPUNIT_ASSERT( dqSeg.source()              == dPt0                );
  CPPUNIT_ASSERT( dqSeg.target()              == dPt1                );
  CPPUNIT_ASSERT( dqSeg.thickness()           == 2                   );
  CPPUNIT_ASSERT( dqSeg.color()               == QGE_COLOR_BLUE      );
  CPPUNIT_ASSERT( dqSeg.outline()             == QGE_OUTLINE_DASH_SS );
  CPPUNIT_ASSERT( dqSeg.accessGeomStructure() == dSeg                );
}


void
GenQgarSegmentTest::testBuildFromTwoPoints()
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

  IQgarSegment iqSeg0(iPt0, iPt1);
  IQgarSegment iqSeg (iPt0, iPt1, 3, QGE_COLOR_BLUE);
  FQgarSegment fqSeg (fPt0, fPt1, 3, QGE_COLOR_BLUE);
  DQgarSegment dqSeg (dPt0, dPt1, 3, QGE_COLOR_BLUE, QGE_OUTLINE_DOT);

  // -----
  // Check
  // -----
  
  CPPUNIT_ASSERT( iqSeg0.source()              == iPt0                );
  CPPUNIT_ASSERT( iqSeg0.target()              == iPt1                );
  CPPUNIT_ASSERT( iqSeg0.thickness()           == 1                   );
  CPPUNIT_ASSERT( iqSeg0.color()               == QGE_COLOR_DEFAULT   );
  CPPUNIT_ASSERT( iqSeg0.outline()             == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( iqSeg0.accessGeomStructure() == ISegment(iPt0,iPt1) );

  CPPUNIT_ASSERT( iqSeg.source()              == iPt0                );
  CPPUNIT_ASSERT( iqSeg.target()              == iPt1                );
  CPPUNIT_ASSERT( iqSeg.thickness()           == 3                   );
  CPPUNIT_ASSERT( iqSeg.color()               == QGE_COLOR_BLUE      );
  CPPUNIT_ASSERT( iqSeg.outline()             == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( iqSeg.accessGeomStructure() == ISegment(iPt0,iPt1) );

  CPPUNIT_ASSERT( fqSeg.source()              == fPt0                );
  CPPUNIT_ASSERT( fqSeg.target()              == fPt1                );
  CPPUNIT_ASSERT( fqSeg.thickness()           == 3                   );
  CPPUNIT_ASSERT( fqSeg.color()               == QGE_COLOR_BLUE      );
  CPPUNIT_ASSERT( fqSeg.outline()             == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( fqSeg.accessGeomStructure() == FSegment(fPt0,fPt1) );

  CPPUNIT_ASSERT( dqSeg.source()              == dPt0                );
  CPPUNIT_ASSERT( dqSeg.target()              == dPt1                );
  CPPUNIT_ASSERT( dqSeg.thickness()           == 3                   );
  CPPUNIT_ASSERT( dqSeg.color()               == QGE_COLOR_BLUE      );
  CPPUNIT_ASSERT( dqSeg.outline()             == QGE_OUTLINE_DOT     );
  CPPUNIT_ASSERT( dqSeg.accessGeomStructure() == DSegment(dPt0,dPt1) );
}


void
GenQgarSegmentTest::testBuildFromCoords()
{

  // ------
  // Set Up
  // ------

  int ix0 = 4;
  int iy0 = -1;
  int ix1 = 12;
  int iy1 = 31;
  IPoint iPt0(ix0, iy0);
  IPoint iPt1(ix1, iy1);

  float fx0 = 8.3F;
  float fy0 = -14.1F;
  float fx1 = 21.212F;
  float fy1 = -41.74861F;  
  FPoint fPt0(fx0, fy0);
  FPoint fPt1(fx1, fy1);

  double dx0 = 1.444001;
  double dy0 = -10.0001;
  double dx1 = 20.0;
  double dy1 = 7.21;
  DPoint dPt0(dx0, dy0);
  DPoint dPt1(dx1, dy1);

  // -------
  // Process
  // -------

  IQgarSegment iqSeg0(ix0, iy0, ix1, iy1);
  IQgarSegment iqSeg (ix0, iy0, ix1, iy1, 4, QGE_COLOR_RED);
  FQgarSegment fqSeg (fx0, fy0, fx1, fy1, 4, QGE_COLOR_RED);
  DQgarSegment dqSeg (dx0, dy0, dx1, dy1, 4, QGE_COLOR_RED, QGE_OUTLINE_DASH_LS);

  // -----
  // Check
  // -----
  
  CPPUNIT_ASSERT( iqSeg0.source()              == iPt0                );
  CPPUNIT_ASSERT( iqSeg0.target()              == iPt1                );
  CPPUNIT_ASSERT( iqSeg0.thickness()           == 1                   );
  CPPUNIT_ASSERT( iqSeg0.color()               == QGE_COLOR_DEFAULT   );
  CPPUNIT_ASSERT( iqSeg0.outline()             == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( iqSeg0.accessGeomStructure() == ISegment(iPt0,iPt1) );

  CPPUNIT_ASSERT( iqSeg.source()              == iPt0                );
  CPPUNIT_ASSERT( iqSeg.target()              == iPt1                );
  CPPUNIT_ASSERT( iqSeg.thickness()           == 4                   );
  CPPUNIT_ASSERT( iqSeg.color()               == QGE_COLOR_RED       );
  CPPUNIT_ASSERT( iqSeg.outline()             == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( iqSeg.accessGeomStructure() == ISegment(iPt0,iPt1) );

  CPPUNIT_ASSERT( fqSeg.source()              == fPt0                );
  CPPUNIT_ASSERT( fqSeg.target()              == fPt1                );
  CPPUNIT_ASSERT( fqSeg.thickness()           == 4                   );
  CPPUNIT_ASSERT( fqSeg.color()               == QGE_COLOR_RED       );
  CPPUNIT_ASSERT( fqSeg.outline()             == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( fqSeg.accessGeomStructure() == FSegment(fPt0,fPt1) );

  CPPUNIT_ASSERT( dqSeg.source()              == dPt0                );
  CPPUNIT_ASSERT( dqSeg.target()              == dPt1                );
  CPPUNIT_ASSERT( dqSeg.thickness()           == 4                   );
  CPPUNIT_ASSERT( dqSeg.color()               == QGE_COLOR_RED       );
  CPPUNIT_ASSERT( dqSeg.outline()             == QGE_OUTLINE_DASH_LS );
  CPPUNIT_ASSERT( dqSeg.accessGeomStructure() == DSegment(dPt0,dPt1) );
}


void
GenQgarSegmentTest::testCopyConstructor()
{
  // ------
  // Set Up
  // ------

  IQgarSegment iqSeg( IPoint(3, 9),           IPoint(1, 5) );
  FQgarSegment fqSeg( FPoint(1.31f, 55.3f),   FPoint(12.31f, -6.1f) );
  DQgarSegment dqSeg( DPoint(0.0031, 1.1243), DPoint(1.56, 9.21) );

  // -------
  // Process
  // -------
  
  IQgarSegment iqDupSeg(iqSeg);
  FQgarSegment fqDupSeg(fqSeg);
  DQgarSegment dqDupSeg(dqSeg);

  // -----
  // Check
  // -----

  // Ensure that source and target are equal.
  CPPUNIT_ASSERT( iqDupSeg.source() == iqSeg.source() );
  CPPUNIT_ASSERT( iqDupSeg.target() == iqSeg.target() );
  
  CPPUNIT_ASSERT( fqDupSeg.source() == fqSeg.source() );
  CPPUNIT_ASSERT( fqDupSeg.target() == fqSeg.target() );
  
  CPPUNIT_ASSERT( dqDupSeg.source() == dqSeg.source() );
  CPPUNIT_ASSERT( dqDupSeg.target() == dqSeg.target() );

  // Ensure that color, thickness, and outline are equal
  CPPUNIT_ASSERT( iqDupSeg.thickness() == iqSeg.thickness() );
  CPPUNIT_ASSERT( iqDupSeg.color()     == iqSeg.color() );
  CPPUNIT_ASSERT( iqDupSeg.outline()   == iqSeg.outline() );

  CPPUNIT_ASSERT( fqDupSeg.thickness() == fqSeg.thickness() );
  CPPUNIT_ASSERT( fqDupSeg.color()     == fqSeg.color() );
  CPPUNIT_ASSERT( fqDupSeg.outline()   == fqSeg.outline() );

  CPPUNIT_ASSERT( dqDupSeg.thickness() == dqSeg.thickness() );
  CPPUNIT_ASSERT( dqDupSeg.color()     == dqSeg.color() );
  CPPUNIT_ASSERT( dqDupSeg.outline()   == dqSeg.outline() );

  // Ensure that both geometrical structure are equal.
  CPPUNIT_ASSERT( iqDupSeg.accessGeomStructure() == iqSeg.accessGeomStructure() );
  CPPUNIT_ASSERT( fqDupSeg.accessGeomStructure() == fqSeg.accessGeomStructure() );
  CPPUNIT_ASSERT( dqDupSeg.accessGeomStructure() == dqSeg.accessGeomStructure() );
}


// ------------------------------------------------------------------
// C O P Y
// ------------------------------------------------------------------


void 
GenQgarSegmentTest::testClone()
{
  // ------
  // Set Up
  // ------

  IQgarSegment iqSeg( IPoint(3, 9),           IPoint(1, 5) );
  FQgarSegment fqSeg( FPoint(1.31f, 55.3f),   FPoint(12.31f, -6.1f) );
  DQgarSegment dqSeg( DPoint(0.0031, 1.1243), DPoint(1.56, 9.21) );

  // -------
  // Process
  // -------
  
  IQgarSegment* iqDupSeg = iqSeg.clone();
  FQgarSegment* fqDupSeg = fqSeg.clone();
  DQgarSegment* dqDupSeg = dqSeg.clone();

  // -----
  // Check
  // -----

  // Ensure that source and target are equal.
  CPPUNIT_ASSERT( iqDupSeg->source() == iqSeg.source() );
  CPPUNIT_ASSERT( iqDupSeg->target() == iqSeg.target() );
  
  CPPUNIT_ASSERT( fqDupSeg->source() == fqSeg.source() );
  CPPUNIT_ASSERT( fqDupSeg->target() == fqSeg.target() );
  
  CPPUNIT_ASSERT( dqDupSeg->source() == dqSeg.source() );
  CPPUNIT_ASSERT( dqDupSeg->target() == dqSeg.target() );
  
  // Ensure that color, thickness, and outline are equal
  CPPUNIT_ASSERT( iqDupSeg->thickness() == iqSeg.thickness() );
  CPPUNIT_ASSERT( iqDupSeg->color()     == iqSeg.color() );
  CPPUNIT_ASSERT( iqDupSeg->outline()   == iqSeg.outline() );

  CPPUNIT_ASSERT( fqDupSeg->thickness() == fqSeg.thickness() );
  CPPUNIT_ASSERT( fqDupSeg->color()     == fqSeg.color() );
  CPPUNIT_ASSERT( fqDupSeg->outline()   == fqSeg.outline() );

  CPPUNIT_ASSERT( dqDupSeg->thickness() == dqSeg.thickness() );
  CPPUNIT_ASSERT( dqDupSeg->color()     == dqSeg.color() );
  CPPUNIT_ASSERT( dqDupSeg->outline()   == dqSeg.outline() );

  // Ensure that both geometrical structure are equal.
  CPPUNIT_ASSERT( iqDupSeg->accessGeomStructure() == iqSeg.accessGeomStructure() );
  CPPUNIT_ASSERT( fqDupSeg->accessGeomStructure() == fqSeg.accessGeomStructure() );
  CPPUNIT_ASSERT( dqDupSeg->accessGeomStructure() == dqSeg.accessGeomStructure() );

  // ---------
  // Tear Down
  // ---------

  delete iqDupSeg;
  delete fqDupSeg;
  delete dqDupSeg;
}


// ------------------------------------------------------------------
// ACCESS TO GEOMETRICAL FEATURES
// ------------------------------------------------------------------


void
GenQgarSegmentTest::testLength()
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
  IQgarSegment iqSeg(ix0, iy0, ix1, iy1);

  float fx0 = 51.3f;
  float fy0 = -14.1521f;
  float fx1 = 1.212f;
  float fy1 = -0.74861f;  
  FPoint fPt0(fx0, fy0);
  FPoint fPt1(fx1, fy1);
  FQgarSegment fqSeg(fx0, fy0, fx1, fy1);

  double dx0 = 11.564001;
  double dy0 = -0.0101;
  double dx1 = 20;
  double dy1 = 71.211;
  DPoint dPt0(dx0, dy0);
  DPoint dPt1(dx1, dy1);
  DQgarSegment dqSeg(dx0, dy0, dx1, dy1);

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
  DQgarSegment dqSegAB(dxA, dyA, dxB, dyB);
  DQgarSegment dqSegBC(dxB, dyB, dxC, dyC);
  DQgarSegment dqSegAC(dxA, dyA, dxC, dyC);

  // -----
  // Check
  // -----
  
  // Compare the length to the distance between the source
  // and the target computed by the appropriate global function
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iqSeg.length(), qgDist(iPt0,iPt1), 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fqSeg.length(), qgDist(fPt0,fPt1), 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dqSeg.length(), qgDist(dPt0,dPt1), 0.0001);

  // Trivial cases
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dqSegAB.length(), 3., 0.000001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dqSegBC.length(), 4., 0.000001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dqSegAC.length(), 5., 0.000001);  
}



void
GenQgarSegmentTest::testSqrLength()
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
  IQgarSegment iqSeg(ix0, iy0, ix1, iy1);

  float fx0 = 51.3f;
  float fy0 = -14.1521f;
  float fx1 = 1.212f;
  float fy1 = -0.74861f;  
  FPoint fPt0(fx0, fy0);
  FPoint fPt1(fx1, fy1);
  FQgarSegment fqSeg(fx0, fy0, fx1, fy1);

  double dx0 = 11.564001;
  double dy0 = -0.0101;
  double dx1 = 20;
  double dy1 = 71.211;
  DPoint dPt0(dx0, dy0);
  DPoint dPt1(dx1, dy1);
  DQgarSegment dqSeg(dx0, dy0, dx1, dy1);

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
  DQgarSegment dqSegAB(dxA, dyA, dxB, dyB);
  DQgarSegment dqSegBC(dxB, dyB, dxC, dyC);
  DQgarSegment dqSegAC(dxA, dyA, dxC, dyC);

  // -----
  // Check
  // -----
  
  // Compare the squared length to the distance between the source
  // and the target computed by the appropriate global function
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iqSeg.sqr_length(), qgSqr_dist(iPt0,iPt1), 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fqSeg.sqr_length(), qgSqr_dist(fPt0,fPt1), 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dqSeg.sqr_length(), qgSqr_dist(dPt0,dPt1), 0.0001);

  // Trivial cases
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dqSegAB.sqr_length(),  9., 0.000001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dqSegBC.sqr_length(), 16., 0.000001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dqSegAC.sqr_length(), 25., 0.000001);  
}



void
GenQgarSegmentTest::testRho()
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

  IQgarSegment iqSegX0 (0,100, 0,101);    // X = 0
  IQgarSegment iqSegX00(0,101, 0,100);    // Opposite orientation

  IQgarSegment iqSegX1(20,1, 20,7);       // X = 20
  IQgarSegment iqSegX10(20,7, 20,3);      // Opposite orientation

  IQgarSegment iqSegX2(2,-5, 2,-2);       // X = 2
  IQgarSegment iqSegX20(2,-2, 2,-5);      // Opposite orientation

  IQgarSegment iqSegX3(-30,5, -30,6);     // X = -30
  IQgarSegment iqSegX30(-30,6, -30,5);    // Opposite orientation

  IQgarSegment iqSegX4(-9,-5, -9,1000);   // X = -9
  IQgarSegment iqSegX40(-9,1000, -9,-5);  // Opposite orientation

  /* Segments parallel to the X axis
   *
   *               Y
   *               ^
   *               |
   *       fqSegY1  |
   *     +-------->+
   *               |
   *               |   fqSegY0
   * -+------------------>---------> X
   *              0|
   *              +---->
   *               | fqSegY2
   *               |
   *               |
   */

  FQgarSegment fqSegY0(-100000.876f,0.f, 29.56237f,0.f);     // Y = 0
  FQgarSegment fqSegY00(29.56237f,0.f, -100000.876f,0.f);    // Opposite orientation

  FQgarSegment fqSegY1(-5.f,4.1436f, 0.f,4.1436f);           // Y = 4.1436
  FQgarSegment fqSegY10(0.f,4.1436f, -5.f,4.1436f);          // Opposite orientation

  FQgarSegment fqSegY2(-0.0002f,-897.354f, 2.f,-897.354f);   // Y = -897.354
  FQgarSegment fqSegY20(2.f,-897.354f, -0.0002f,-897.354f);  // Opposite orientation

  // rho ==  2 * sqrt(2)
  DQgarSegment dqSeg2neg(5.,1., 7.,3.);

  // rho ==  2 * sqrt(2)
  DQgarSegment dqSeg2pos(4.,0., -1.,5.);

  // rho ==  4 * sqrt(2)
  DQgarSegment dqSeg4neg(-4.,-4., -2.,-6.);

  // rho ==  4 * sqrt(2)
  DQgarSegment dqSeg4pos(-2.,6., -4.,4);

  // rho == 0
  DQgarSegment dqSeg0(-5.,-1., 5.,1.);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_DOUBLES_EQUAL(iqSegX0.rho(),    0., 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iqSegX00.rho(),   0., 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iqSegX1.rho(),   20., 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iqSegX10.rho(),  20., 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iqSegX2.rho(),    2., 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iqSegX20.rho(),   2., 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iqSegX3.rho(),   30., 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iqSegX30.rho(),  30., 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iqSegX4.rho(),    9., 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iqSegX40.rho(),   9., 0.0001);  

  CPPUNIT_ASSERT_DOUBLES_EQUAL(fqSegY0.rho(),       0., 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fqSegY00.rho(),      0., 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fqSegY1.rho(),   4.1436, 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fqSegY10.rho(),  4.1436, 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fqSegY2.rho(),  897.354, 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fqSegY20.rho(), 897.354, 0.0001);  

  CPPUNIT_ASSERT_DOUBLES_EQUAL(dqSeg2neg.rho(), 2. * Math::QG_SQRT_2, 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dqSeg2pos.rho(), 2. * Math::QG_SQRT_2, 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dqSeg4neg.rho(), 4. * Math::QG_SQRT_2, 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dqSeg4pos.rho(), 4. * Math::QG_SQRT_2, 0.0001);  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dqSeg0.rho(),                      0., 0.0001);
}



void
GenQgarSegmentTest::testAngles()
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

  FQgarSegment qsegXP(   12.11, 48.845,    19.19,  48.845);
  FQgarSegment qsegXN(    800., -36.75,    2.732,  -36.75);
  FQgarSegment qsegYP(-1024.33,   0.51, -1024.33, 7853.64);
  FQgarSegment qsegYN(  -0.004,  -12.3,   -0.004,   -127.);

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

  FQgarSegment qsegP1(1.1, 1.1, 80764.32, 80764.32);
  FQgarSegment qsegP2(0., 0., -433.2, 433.2);
  FQgarSegment qsegP3(-89.615, -89.615, -90., -90.);
  FQgarSegment qsegP4(545.76, -545.76, 667.32, -667.32);

  // -------
  // Process
  // -------

  double tXP  = qsegXP.theta();         // 0
  double tXPd = qsegXP.thetaDegrees();  // 0
  double aXP  = qsegXP.angle();         // 0
  double aXPd = qsegXP.angleDegrees();  // 0
  double sXP  = qsegXP.slope();         // 0
  double sXPd = qsegXP.slopeDegrees();  // 0

  double tXN  = qsegXN.theta();         // PI
  double tXNd = qsegXN.thetaDegrees();  // 180
  double aXN  = qsegXN.angle();         // PI
  double aXNd = qsegXN.angleDegrees();  // 180
  double sXN  = qsegXN.slope();         // 0
  double sXNd = qsegXN.slopeDegrees();  // 0

  double tYP  = qsegYP.theta();         // PI/2
  double tYPd = qsegYP.thetaDegrees();  // 90
  double aYP  = qsegYP.angle();         // PI/2
  double aYPd = qsegYP.angleDegrees();  // 90
  double sYP  = qsegYP.slope();         // PI/2
  double sYPd = qsegYP.slopeDegrees();  // 90

  double tYN  = qsegYN.theta();         // 3PI/2
  double tYNd = qsegYN.thetaDegrees();  // 270
  double aYN  = qsegYN.angle();         // 3PI/2
  double aYNd = qsegYN.angleDegrees();  // 270
  double sYN  = qsegYN.slope();         // PI/2
  double sYNd = qsegYN.slopeDegrees();  // 90

  double tP1  = qsegP1.theta();         // PI/4
  double tP1d = qsegP1.thetaDegrees();  // 45
  double aP1  = qsegP1.angle();         // PI/4
  double aP1d = qsegP1.angleDegrees();  // 45
  double sP1  = qsegP1.slope();         // PI/4
  double sP1d = qsegP1.slopeDegrees();  // 45

  double tP2  = qsegP2.theta();         // 3PI/4
  double tP2d = qsegP2.thetaDegrees();  // 135
  double aP2  = qsegP2.angle();         // 3PI/4
  double aP2d = qsegP2.angleDegrees();  // 135
  double sP2  = qsegP2.slope();         // 3PI/4
  double sP2d = qsegP2.slopeDegrees();  // 135

  double tP3  = qsegP3.theta();         // 5PI/4
  double tP3d = qsegP3.thetaDegrees();  // 225
  double aP3  = qsegP3.angle();         // 5PI/4
  double aP3d = qsegP3.angleDegrees();  // 225
  double sP3  = qsegP3.slope();         // PI/4
  double sP3d = qsegP3.slopeDegrees();  // 45

  double tP4  = qsegP4.theta();         // 7PI/4
  double tP4d = qsegP4.thetaDegrees();  // 315
  double aP4  = qsegP4.angle();         // 7PI/4
  double aP4d = qsegP4.angleDegrees();  // 315
  double sP4  = qsegP4.slope();         // 3PI/4
  double sP4d = qsegP4.slopeDegrees();  // 135

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
GenQgarSegmentTest::testContains()
{
  // ------
  // Set Up
  // ------

  // A Qgar segment defining the line y = 3x + 1
  IQgarSegment iS1(1,  4, 8, 25);
  IQgarSegment iS2(8, 25, 1,  4);      // Reverse orientation
  DQgarSegment dS1(1.,  4., 8., 25.);
  DQgarSegment dS2(8., 25., 1.,  4.);  // Reverse orientation

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
GenQgarSegmentTest::testAssignmentOp()
{
  // ------
  // Set Up
  // ------
  
  int ix0 = 46;
  int iy0 = -1;
  int ix1 = 12;
  int iy1 = 157;
  IQgarSegment iqSeg(ix0, iy0, ix1, iy1);

  float fx0 = 51.3f;
  float fy0 = -14.1521f;
  float fx1 = 1.212f;
  float fy1 = -0.74861f;  
  FQgarSegment fqSeg(fx0, fy0, fx1, fy1);

  double dx0 = 11.564001;
  double dy0 = -0.0101;
  double dx1 = 20;
  double dy1 = 71.211;
  DQgarSegment dqSeg(dx0, dy0, dx1, dy1);

  // -------
  // Process
  // -------

  IQgarSegment iDupqSeg;
  FQgarSegment fDupqSeg;
  DQgarSegment dDupqSeg;
  
  iDupqSeg = iqSeg;
  fDupqSeg = fqSeg;
  dDupqSeg = dqSeg;

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT(iDupqSeg.xSource() == ix0);
  CPPUNIT_ASSERT(iDupqSeg.ySource() == iy0);
  CPPUNIT_ASSERT(iDupqSeg.xTarget() == ix1);
  CPPUNIT_ASSERT(iDupqSeg.yTarget() == iy1);

  CPPUNIT_ASSERT(fDupqSeg.xSource() == fx0);
  CPPUNIT_ASSERT(fDupqSeg.ySource() == fy0);
  CPPUNIT_ASSERT(fDupqSeg.xTarget() == fx1);
  CPPUNIT_ASSERT(fDupqSeg.yTarget() == fy1);

  CPPUNIT_ASSERT(dDupqSeg.xSource() == dx0);
  CPPUNIT_ASSERT(dDupqSeg.ySource() == dy0);
  CPPUNIT_ASSERT(dDupqSeg.xTarget() == dx1);
  CPPUNIT_ASSERT(dDupqSeg.yTarget() == dy1);
}



void
GenQgarSegmentTest::testEqualOp()
{
  // ------
  // Set Up
  // ------

  int ix0 = 46;
  int iy0 = -1;
  int ix1 = 12;
  int iy1 = 157;
  IQgarSegment iqSeg0(ix0, iy0, ix1, iy1);
  IQgarSegment iqSeg1(ix0, iy0 + 1, ix1 + 1, iy1 + 1);

  float fx0 = 51.3f;
  float fy0 = -14.1521f;
  float fx1 = 1.212f;
  float fy1 = -0.74861f;  
  FQgarSegment fqSeg0(fx0, fy0, fx1, fy1);
  FQgarSegment fqSeg1(fx0 + 1., fy0, fx1, fy1);

  double dx0 = 11.564001;
  double dy0 = -0.0101;
  double dx1 = 20;
  double dy1 = 71.211;
  DQgarSegment dqSeg0(dx0, dy0, dx1, dy1);
  DQgarSegment dqSeg1(dx0, dy0 + 1., dx1, dy1 + 1.);

  // -----
  // Check
  // -----

  // Check operator reflexivity
  CPPUNIT_ASSERT( iqSeg0 == iqSeg0 );
  CPPUNIT_ASSERT( fqSeg0 == fqSeg0 );
  CPPUNIT_ASSERT( dqSeg0 == dqSeg0 );

  // Check if a segment is equal to a copy of itself
  CPPUNIT_ASSERT( iqSeg0 == IQgarSegment(iqSeg0) );
  CPPUNIT_ASSERT( fqSeg0 == FQgarSegment(fqSeg0) );
  CPPUNIT_ASSERT( dqSeg0 == DQgarSegment(dqSeg0) );

  // Check that a segment is not equal to another, different segment
  CPPUNIT_ASSERT( !(iqSeg0 == iqSeg1) );
  CPPUNIT_ASSERT( !(fqSeg0 == fqSeg1) );
  CPPUNIT_ASSERT( !(dqSeg0 == dqSeg1) );
}



void
GenQgarSegmentTest::testNotEqualOp()
{
  // ------
  // Set Up
  // ------

  int ix0 = 46;
  int iy0 = -1;
  int ix1 = 12;
  int iy1 = 157;
  IQgarSegment iqSeg0(ix0, iy0, ix1, iy1);
  IQgarSegment iqSeg1(ix0 + 1, iy0, ix1, iy1 + 1);

  float fx0 = 51.3f;
  float fy0 = -14.1521f;
  float fx1 = 1.212f;
  float fy1 = -0.74861f;  
  FQgarSegment fqSeg0(fx0, fy0, fx1, fy1);
  FQgarSegment fqSeg1(fx0, fy0 + 1., fx1, fy1 + 1.);

  double dx0 = 11.564001;
  double dy0 = -0.0101;
  double dx1 = 20;
  double dy1 = 71.211;
  DQgarSegment dqSeg0(dx0, dy0, dx1, dy1);
  DQgarSegment dqSeg1(dx0 + 1., dy0 + 1., dx1 + 1., dy1 + 1.);

  // -----
  // Check
  // -----

  // Check if a segment is equal to itself using operator not equal
  CPPUNIT_ASSERT( !(iqSeg0 != iqSeg0) );
  CPPUNIT_ASSERT( !(fqSeg0 != fqSeg0) );
  CPPUNIT_ASSERT( !(dqSeg0 != dqSeg0) );

  // Check if a segment is equal to its copy using operator not equal
  CPPUNIT_ASSERT( !(iqSeg0 != IQgarSegment(iqSeg0)) );
  CPPUNIT_ASSERT( !(fqSeg0 != FQgarSegment(fqSeg0)) );
  CPPUNIT_ASSERT( !(dqSeg0 != DQgarSegment(dqSeg0)) );

  // Check if two different segments are not equal
  CPPUNIT_ASSERT( iqSeg0 != iqSeg1 );
  CPPUNIT_ASSERT( fqSeg0 != fqSeg1 );
  CPPUNIT_ASSERT( dqSeg0 != dqSeg1 );
}


// ------------------------------------------------------------------
// F U N C T I O N A L   O P E R A T O R S
// ------------------------------------------------------------------


void
GenQgarSegmentTest::testEq()
{
  // ------
  // Set Up
  // ------

  int ix0 = 46;
  int iy0 = -1;
  int ix1 = 12;
  int iy1 = 157;
  IQgarSegment iqSeg0(ix0, iy0, ix1, iy1, 6, QGE_COLOR_CYAN, QGE_OUTLINE_DOT);
  IQgarSegment iqSeg1(ix1, iy1, ix0, iy0, 6, QGE_COLOR_CYAN, QGE_OUTLINE_DOT);
  IQgarSegment iqSeg2(ix0, iy0, ix1, iy1, 2, QGE_COLOR_BLUE, QGE_OUTLINE_DOT);
  IQgarSegment iqSeg3(ix0, iy1, ix1, iy0, 6, QGE_COLOR_CYAN, QGE_OUTLINE_DASH_LSS);
  IQgarSegment iqSeg4(ix0, iy0, ix1, iy1, 6, QGE_COLOR_CYAN, QGE_OUTLINE_DOT);

  // -----
  // Check
  // -----

  // Check operator reflexivity
  CPPUNIT_ASSERT( iqSeg0.eq(iqSeg0) );
  CPPUNIT_ASSERT( iqSeg0.equal(iqSeg0) );

  // Check if a segment is equal to a copy of itself
  CPPUNIT_ASSERT( iqSeg0.eq(IQgarSegment(iqSeg0)) );
  CPPUNIT_ASSERT( iqSeg0.equal(IQgarSegment(iqSeg0)) );

  // Check partial and full equality
  CPPUNIT_ASSERT( !(iqSeg0.eq(iqSeg1)) );
  CPPUNIT_ASSERT( !(iqSeg0.equal(iqSeg1)) );

  CPPUNIT_ASSERT( iqSeg0.eq(iqSeg2) );
  CPPUNIT_ASSERT( !(iqSeg0.equal(iqSeg2)) );

  CPPUNIT_ASSERT( !(iqSeg0.eq(iqSeg3)) );
  CPPUNIT_ASSERT( !(iqSeg0.equal(iqSeg3)) );

  CPPUNIT_ASSERT( iqSeg0.eq(iqSeg4) );
  CPPUNIT_ASSERT( iqSeg0.equal(iqSeg4) );
}



void
GenQgarSegmentTest::testNotEq()
{
  // ------
  // Set Up
  // ------

  int ix0 = 46;
  int iy0 = -1;
  int ix1 = 12;
  int iy1 = 157;
  IQgarSegment iqSeg0(ix0, iy0, ix1, iy1, 6, QGE_COLOR_CYAN, QGE_OUTLINE_DOT);
  IQgarSegment iqSeg1(ix1, iy1, ix0, iy0, 6, QGE_COLOR_CYAN, QGE_OUTLINE_DOT);
  IQgarSegment iqSeg2(ix0, iy0, ix1, iy1, 2, QGE_COLOR_BLUE, QGE_OUTLINE_DOT);
  IQgarSegment iqSeg3(ix0, iy1, ix1, iy0, 6, QGE_COLOR_CYAN, QGE_OUTLINE_DASH_LSS);
  IQgarSegment iqSeg4(ix0, iy0, ix1, iy1, 6, QGE_COLOR_CYAN, QGE_OUTLINE_DOT);

  // -----
  // Check
  // -----

  // Check if a segment is equal to itself using operator not equal
  CPPUNIT_ASSERT( !(iqSeg0.notEq(iqSeg0)) );
  CPPUNIT_ASSERT( !(iqSeg0.notEqual(iqSeg0)) );

  // Check if a segment is equal to its copy using operator not equal
  CPPUNIT_ASSERT( !(iqSeg0.notEq(IQgarSegment(iqSeg0))) );
  CPPUNIT_ASSERT( !(iqSeg0.notEqual(IQgarSegment(iqSeg0))) );

  // Check partial and full inequality
  CPPUNIT_ASSERT( iqSeg0.notEq(iqSeg1)    );
  CPPUNIT_ASSERT( iqSeg0.notEqual(iqSeg1) );

  CPPUNIT_ASSERT( !(iqSeg0.notEq(iqSeg2)) );
  CPPUNIT_ASSERT( iqSeg0.notEqual(iqSeg2) );

  CPPUNIT_ASSERT( iqSeg0.notEq(iqSeg3)    );
  CPPUNIT_ASSERT( iqSeg0.notEqual(iqSeg3) );

  CPPUNIT_ASSERT( !(iqSeg0.notEq(iqSeg4))    );
  CPPUNIT_ASSERT( !(iqSeg0.notEqual(iqSeg4)) );
}


// ------------------------------------------------------------------
// G E O M E T R Y :   T R A N S L A T I O N
// ------------------------------------------------------------------


void
GenQgarSegmentTest::testTranslate()
{
  // ------
  // Set Up
  // ------

  int ix0 = 46;
  int iy0 = -1;
  int ix1 = 12;
  int iy1 = 157;
  IQgarSegment iqSeg(ix0, iy0, ix1, iy1);

  float fx0 = 51.3f;
  float fy0 = -14.1521f;
  float fx1 = 1.212f;
  float fy1 = -0.74861f;  
  FQgarSegment fqSeg(fx0, fy0, fx1, fy1);

  double dx0 = 11.564001;
  double dy0 = -0.0101;
  double dx1 = 20;
  double dy1 = 71.211;
  DQgarSegment dqSeg(dx0, dy0, dx1, dy1);

  // -------
  // Process
  // -------

  iqSeg.translate(18, 9965);
  fqSeg.translate(0., 8756.2341);
  dqSeg.translate(-0.004, -58435.1581123);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( iqSeg.xSource(), ix0 + 18 );
  CPPUNIT_ASSERT_EQUAL( iqSeg.ySource(), iy0 + 9965 );
  CPPUNIT_ASSERT_EQUAL( iqSeg.xTarget(), ix1 + 18 );
  CPPUNIT_ASSERT_EQUAL( iqSeg.yTarget(), iy1 + 9965 );

  CPPUNIT_ASSERT_DOUBLES_EQUAL( fqSeg.xSource(), fx0,             0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( fqSeg.ySource(), fy0 + 8756.2341, 0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( fqSeg.xTarget(), fx1,             0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( fqSeg.yTarget(), fy1 + 8756.2341, 0.001 );

  CPPUNIT_ASSERT_DOUBLES_EQUAL( dqSeg.xSource(), dx0 - 0.004,         0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( dqSeg.ySource(), dy0 - 58435.1581123, 0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( dqSeg.xTarget(), dx1 - 0.004,         0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( dqSeg.yTarget(), dy1 - 58435.1581123, 0.001 );
}


// ------------------------------------------------------------------
// S E R I A L I Z A T I O N
// ------------------------------------------------------------------


void 
GenQgarSegmentTest::testSerializeDeserialize()
{
  // ------
  // Set Up
  // ------
  
  int ix0 = 98;
  int iy0 = -24;
  int ix1 = 16;
  int iy1 = 91;  
  IQgarSegment iqSeg(ix0, iy0, ix1, iy1, 6);
  IQgarSegment iOutInSeg;
  
  float fx0 = 0.8f;
  float fy0 = -2.425f;
  float fx1 = 1905.2f;
  float fy1 = 1.0f;  
  FQgarSegment fqSeg(fx0, fy0, fx1, fy1, 6, QGE_COLOR_GREEN);
  FQgarSegment fOutInSeg;

  double dx0 = 13.1348;
  double dy0 = -24.41;
  double dx1 = 1145.5;
  double dy1 = 91.05953;  
  DQgarSegment dqSeg(dx0, dy0, dx1, dy1, 6, QGE_COLOR_GREEN, QGE_OUTLINE_DASH_LSS);
  DQgarSegment dOutInSeg;

  // -------
  // Process
  // -------
  
  std::stringstream ss;
  
  ss << iqSeg;
  ss >> iOutInSeg;
  ss.flush();
  
  ss << fqSeg;
  ss >> fOutInSeg;
  ss.flush();

  ss << dqSeg;
  ss >> dOutInSeg;
  ss.flush();

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT(iqSeg.source()    == iOutInSeg.source());
  CPPUNIT_ASSERT(iqSeg.target()    == iOutInSeg.target());
  CPPUNIT_ASSERT(iqSeg.thickness() == iOutInSeg.thickness());
  CPPUNIT_ASSERT(iqSeg.color()     == iOutInSeg.color());
  CPPUNIT_ASSERT(iqSeg.outline()   == iOutInSeg.outline());

  CPPUNIT_ASSERT_DOUBLES_EQUAL(fqSeg.xSource(), fOutInSeg.xSource(), 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fqSeg.ySource(), fOutInSeg.ySource(), 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fqSeg.xTarget(), fOutInSeg.xTarget(), 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fqSeg.yTarget(), fOutInSeg.yTarget(), 0.0001);
  CPPUNIT_ASSERT(fqSeg.thickness() == fOutInSeg.thickness());
  CPPUNIT_ASSERT(fqSeg.color()     == fOutInSeg.color());
  CPPUNIT_ASSERT(fqSeg.outline()   == fOutInSeg.outline());

  CPPUNIT_ASSERT_DOUBLES_EQUAL(dqSeg.xSource(), dOutInSeg.xSource(), 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dqSeg.ySource(), dOutInSeg.ySource(), 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dqSeg.xTarget(), dOutInSeg.xTarget(), 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dqSeg.yTarget(), dOutInSeg.yTarget(), 0.0001);
  CPPUNIT_ASSERT(dqSeg.thickness() == dOutInSeg.thickness());
  CPPUNIT_ASSERT(dqSeg.color()     == dOutInSeg.color());
  CPPUNIT_ASSERT(dqSeg.outline()   == dOutInSeg.outline());
}

// ----------------------------------------------------------------------
