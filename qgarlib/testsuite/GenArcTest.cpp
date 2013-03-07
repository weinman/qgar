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
 * @file  GenArcTest.cpp
 * @brief Implementation of class GenArcTest
 *
 *        See file GenArcTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 14, 2003  17:45
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenArcTest.cpp,v 1.11 2005/10/14 17:06:36 masini Exp $ */



// STD
#include <sstream>
// QGAR
#include <qgarlib/math.h>
#include <qgarlib/primitives.h>
// QGAR TESTS
#include "GenArcTest.h"



using namespace qgar;



// ------------------------------------------------------------------
// U N N A M E D   N A M E S P A C E
// ------------------------------------------------------------------

namespace
{

template<typename T>
void
cmpArcs(const GenArc<T>& a1, const GenArc<T>& a2)
{
  CPPUNIT_ASSERT( a1.source() == a2.source() );
  CPPUNIT_ASSERT( a1.target() == a2.target() );
  CPPUNIT_ASSERT( a1.center() == a2.center() );
}

} // unnamed namespace


// ------------------------------------------------------------------
// F I X T U R E   I M P L E M E N T A T I O N
// ------------------------------------------------------------------

void
GenArcTest::setUp()
{
  /* EMPTY */
}

void
GenArcTest::tearDown()
{
  /* EMPTY */
}


// ------------------------------------------------------------------
// C O N S T R U C T O R S
// ------------------------------------------------------------------

void
GenArcTest::testDefaultConstructor()
{
  // ------
  // Set Up
  // ------

  IArc iArc;
  FArc fArc;
  DArc dArc;

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iArc.source() == IPoint(0,0) );
  CPPUNIT_ASSERT( iArc.target() == IPoint(0,0) );
  CPPUNIT_ASSERT( iArc.center() == IPoint(0,0) );

  CPPUNIT_ASSERT( fArc.source() == FPoint(0.f,0.f) );
  CPPUNIT_ASSERT( fArc.target() == FPoint(0.f,0.f) );
  CPPUNIT_ASSERT( fArc.center() == FPoint(0.f,0.f) );

  CPPUNIT_ASSERT( dArc.source() == DPoint(0.,0.) );
  CPPUNIT_ASSERT( dArc.target() == DPoint(0.,0.) );
  CPPUNIT_ASSERT( dArc.center() == DPoint(0.,0.) );
}


void
GenArcTest::testBuildFrom3Points()
{
  // ------
  // Set Up
  // ------

  IPoint iPt0(14,-1);
  IPoint iPt1(47, 7);
  IPoint iCenter(-1, 10);

  FPoint fPt0(14.f,-1.f);
  FPoint fPt1(47.f, 7.f);
  FPoint fCenter(-1, 10.f);

  DPoint dPt0(14.,-1.);
  DPoint dPt1(47., 7.);
  DPoint dCenter(-1., 10.);

  // -------
  // Process
  // -------

  IArc iArc(iPt0, iPt1, iCenter);
  FArc fArc(fPt0, fPt1, fCenter);
  DArc dArc(dPt0, dPt1, dCenter);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iArc.source() == iPt0 );
  CPPUNIT_ASSERT( iArc.target() == iPt1 );
  CPPUNIT_ASSERT( iArc.center() == iCenter );

  CPPUNIT_ASSERT( fArc.source() == fPt0 );
  CPPUNIT_ASSERT( fArc.target() == fPt1 );
  CPPUNIT_ASSERT( fArc.center() == fCenter );

  CPPUNIT_ASSERT( dArc.source() == dPt0 );
  CPPUNIT_ASSERT( dArc.target() == dPt1 );
  CPPUNIT_ASSERT( dArc.center() == dCenter );
}


void
GenArcTest::testCopyConstructor()
{
  // ------
  // Set Up
  // ------

  IArc iArc(IPoint(-3,1),       IPoint(0,-2),       IPoint(-1,0));
  FArc fArc(FPoint(-3.1f,1.1f), FPoint(0.1f,-2.1f), FPoint(-1.1f,0.1f));
  DArc dArc(DPoint(-3.2,1.2),   DPoint(0.2,-2.2),   DPoint(-1.2,0.2));

  // -------
  // Process
  // -------
  
  IArc iDupArc(iArc);
  FArc fDupArc(fArc);
  DArc dDupArc(dArc);
  
  // -----
  // Check
  // -----

  cmpArcs(iArc, iDupArc);
  cmpArcs(fArc, fDupArc);
  cmpArcs(dArc, dDupArc);
}


void 
GenArcTest::testBuildFromQgarArc()
{
  // ------
  // Set Up
  // ------

  IQgarArc iqArc(IPoint(-3,1), IPoint(0,-2), IPoint(-1,0),
		 2, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);
  FQgarArc fqArc(FPoint(-3.1f,1.1f), FPoint(0.1f,-2.1f), FPoint(-1.1f,0.1f),
		 2, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);
  DQgarArc dqArc(DPoint(-3.2,1.2), DPoint(0.2,-2.2), DPoint(-1.2,0.2),
		 2, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);

  // -------
  // Process
  // -------

  IArc iArc(iqArc);
  FArc fArc(fqArc);
  DArc dArc(dqArc);

  // -----
  // Check
  // -----

  cmpArcs(iArc, iqArc.accessGeomStructure());
  cmpArcs(fArc, fqArc.accessGeomStructure());
  cmpArcs(dArc, dqArc.accessGeomStructure());
}


// ----------------------------------------------------------------------
// C O P Y
// ----------------------------------------------------------------------


void
GenArcTest::testClone()
{
  // ------
  // Set Up
  // ------

  IArc iArc(IPoint(-3,1),       IPoint(0,-2),       IPoint(-1,0));
  FArc fArc(FPoint(-3.1f,1.1f), FPoint(0.1f,-2.1f), FPoint(-1.1f,0.1f));
  DArc dArc(DPoint(-3.2,1.2),   DPoint(0.2,-2.2),   DPoint(-1.2,0.2));

  // -------
  // Process
  // -------
  
  IArc* iClone = iArc.clone();
  FArc* fClone = fArc.clone();
  DArc* dClone = dArc.clone();

  // -----
  // Check
  // -----

  cmpArcs(iArc, *iClone);
  cmpArcs(fArc, *fClone);
  cmpArcs(dArc, *dClone);

  // ---------
  // Tear Down
  // ---------

  delete iClone;
  delete fClone;
  delete dClone;
}


// ----------------------------------------------------------------------
// ACCESS TO GEOMETRICAL FEATURES
// ----------------------------------------------------------------------


void
GenArcTest:: testRadius()
{
  // ------
  // Set Up
  // ------
   
  int icx = 2;
  int icy = 2;
  int isx = 2;
  int isy = 5;
  int itx = 5;
  int ity = 2;

  IArc iarc(IPoint(isx,isy), IPoint(itx,ity), IPoint(icx,icy));

  float fcx = -1.f;
  float fcy = -2.f;
  float fsx = 2.f;
  float fsy = -6.f;
  float ftx = -4.f;
  float fty = 2.f;

  FArc farc(FPoint(fsx,fsy), FPoint(ftx,fty), FPoint(fcx,fcy));

  double dcx = -10001.;
  double dcy = -10000.;
  double dsx = -10000.;
  double dsy = -10002.;
  double dtx = -10002.;
  double dty = -10002.;

  DArc darc(DPoint(dsx,dsy), DPoint(dtx,dty), DPoint(dcx,dcy));

  // -----
  // Check
  // -----
  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iarc.radius(), 3.,  Math::epsilonD());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(farc.radius(), 5.f, Math::epsilonF());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(darc.radius(),
			       2.23606797749979,   // == sqrt(5)
			       Math::epsilonD()); 

}


void
GenArcTest:: testLength()
{
  // ------
  // Set Up
  // ------
   
  double cx = -1.;
  double cy =  0.;

  double sx = -3.;
  double sy = -1.;

  double tx = 0.;
  double ty = -2.;

  DArc dArc(DPoint(sx,sy), DPoint(tx,ty), DPoint(cx,cy));
  
  double sAng = dArc.sourceAngle();
  double tAng = dArc.targetAngle();
  double r    = dArc.radius();
  double l    = dArc.length();

  // -----
  // Check
  // -----
  
  if (sAng > tAng)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(r * (Math::QG_2PI - sAng + tAng),
				   l,
				   Math::epsilonD());
    }
  else
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(r * (tAng - sAng),
				   l,
				   Math::epsilonD());
    }    
}


void
GenArcTest:: testAngles()
{
  // ------
  // Set Up
  // ------

  IPoint iSource(-3,  1);
  IPoint iTarget( 0, -2);
  IPoint iCenter(-1,  0);
  IArc iArc(iSource, iTarget, iCenter);

  FPoint fSource(0.f, 3.f);
  FPoint fTarget(4.f, 1.f);
  FPoint fCenter(1.f, 0.f);
  FArc fArc(fSource, fTarget, fCenter);

  DPoint dSource( 4.5, 2.5);
  DPoint dTarget(-0.5, 2.5);
  DPoint dCenter( 2. , 0. );
  DArc dArc(dSource, dTarget, dCenter);
  
  // -------
  // Process
  // --------

  double isAng    = qgAngle(iCenter, iSource);
  double isAngDeg = qgRadiansToDegrees(isAng);
  double itAng    = qgAngle(iCenter, iTarget);
  double itAngDeg = qgRadiansToDegrees(itAng);
  double iAng     = itAng - isAng;
  if (isAng > itAng)
    {
      iAng += Math::QG_2PI;
    }
  double iAngDeg = qgRadiansToDegrees(iAng);

  double fsAng    = qgAngle(fCenter, fSource);
  double fsAngDeg = qgRadiansToDegrees(fsAng);
  double ftAng    = qgAngle(fCenter, fTarget);
  double ftAngDeg = qgRadiansToDegrees(ftAng);
  double fAng     = ftAng - fsAng;
  if (fsAng > ftAng)
    {
      fAng += Math::QG_2PI;
    }
  double fAngDeg = qgRadiansToDegrees(fAng);

  double dsAng    = qgAngle(dCenter, dSource);
  double dsAngDeg = qgRadiansToDegrees(dsAng);
  double dtAng    = qgAngle(dCenter, dTarget);
  double dtAngDeg = qgRadiansToDegrees(dtAng);
  double dAng     = dtAng - dsAng;
  if (dsAng > dtAng)
    {
      dAng += Math::QG_2PI;
    }
  double dAngDeg = qgRadiansToDegrees(dAng);

  // -----
  // Check
  // -----
  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iArc.sourceAngle(),
			       isAng,
			       Math::epsilonRadian());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iArc.sourceAngleDegrees(),
			       isAngDeg,
			       Math::epsilonDegree());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iArc.targetAngle(),
			       itAng,
			       Math::epsilonRadian());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iArc.targetAngleDegrees(),
			       itAngDeg,
			       Math::epsilonDegree());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iArc.angle(),
			       iAng,
			       Math::epsilonRadian());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iArc.angleDegrees(),
			       iAngDeg,
			       Math::epsilonDegree());

  CPPUNIT_ASSERT_DOUBLES_EQUAL(fArc.sourceAngle(),
			       fsAng,
			       Math::epsilonRadian());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fArc.sourceAngleDegrees(),
			       fsAngDeg,
			       Math::epsilonDegree());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fArc.targetAngle(),
			       ftAng,
			       Math::epsilonRadian());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fArc.targetAngleDegrees(),
			       ftAngDeg,
			       Math::epsilonDegree());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fArc.angle(),
			       fAng,
			       Math::epsilonRadian());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fArc.angleDegrees(),
			       fAngDeg,
			       Math::epsilonDegree());

  CPPUNIT_ASSERT_DOUBLES_EQUAL(dArc.sourceAngle(),
			       dsAng,
			       Math::epsilonRadian());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dArc.sourceAngleDegrees(),
			       dsAngDeg,
			       Math::epsilonDegree());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dArc.targetAngle(),
			       dtAng,
			       Math::epsilonRadian());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dArc.targetAngleDegrees(),
			       dtAngDeg,
			       Math::epsilonDegree());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dArc.angle(),
			       dAng,
			       Math::epsilonRadian());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dArc.angleDegrees(),
			       dAngDeg,
			       Math::epsilonDegree());
}


// ----------------------------------------------------------------------
// C E N T E R
// ----------------------------------------------------------------------


void
GenArcTest::testCenter()
{
  // ------
  // Set Up
  // ------
   
  int icx = 2;
  int icy = 4;
  
  IPoint ic(icx, icy);
  IPoint is(2, 8);
  IPoint it(6, 4);

  IArc ia(is, it, ic);

  // ----------------------
  // Get center coordinates
  // ----------------------

  CPPUNIT_ASSERT_EQUAL( ia.xCenter(), icx );
  CPPUNIT_ASSERT_EQUAL( ia.yCenter(), icy );

  // ----------------------
  // Set center coordinates
  // ----------------------

  ia.setXCenter(icx - 3);
  CPPUNIT_ASSERT_EQUAL( ia.xCenter(), icx - 3 );

  ia.setYCenter(icy - 3);
  CPPUNIT_ASSERT_EQUAL( ia.yCenter(), icy - 3 );

  ia.setCenter(icx + 2, icy + 2);
  CPPUNIT_ASSERT_EQUAL( ia.xCenter(), icx + 2 );
  CPPUNIT_ASSERT_EQUAL( ia.yCenter(), icy + 2 );

  ia.setCenter(ic);
  CPPUNIT_ASSERT_EQUAL( ia.xCenter(), icx );
  CPPUNIT_ASSERT_EQUAL( ia.yCenter(), icy );

  // ------------------------
  // Get a copy of the center
  // ------------------------

  IPoint icopy = ia.center();
  CPPUNIT_ASSERT_EQUAL( icopy.x(), icx );
  CPPUNIT_ASSERT_EQUAL( icopy.y(), icy );

  // Initial center is not modified when modifying copy
  icopy.setX(0);
  icopy.setY(0);
  CPPUNIT_ASSERT_EQUAL( ia.xCenter(), icx );
  CPPUNIT_ASSERT_EQUAL( ia.yCenter(), icy );
  CPPUNIT_ASSERT_EQUAL( icopy.x(),    0   );
  CPPUNIT_ASSERT_EQUAL( icopy.y(),    0   );

  // --------------
  // Get the center
  // --------------

  const IPoint& icenter = ia.accessCenter();
  CPPUNIT_ASSERT_EQUAL( icenter.x(), icx );
  CPPUNIT_ASSERT_EQUAL( icenter.y(), icy );

  // Initial center is modified when modifying reference
  ia.setXCenter(0);
  ia.setYCenter(0);
  CPPUNIT_ASSERT_EQUAL( ia.xCenter(), 0 );
  CPPUNIT_ASSERT_EQUAL( ia.yCenter(), 0 );
  CPPUNIT_ASSERT_EQUAL( icenter.x(),  0 );
  CPPUNIT_ASSERT_EQUAL( icenter.y(),  0 );
}


// ----------------------------------------------------------------------
// O P E R A T O R S
// ----------------------------------------------------------------------

void 
GenArcTest::testAssignment()
{
  // ------
  // Set Up
  // ------

  IArc iArc(IPoint(-3,1),       IPoint(0,-2),       IPoint(-1,0));
  FArc fArc(FPoint(-3.1f,1.1f), FPoint(0.1f,-2.1f), FPoint(-1.1f,0.1f));
  DArc dArc(DPoint(-3.2,1.2),   DPoint(0.2,-2.2),   DPoint(-1.2,0.2));

  // -------
  // Process
  // -------

  IArc iDupArc;
  FArc fDupArc;
  DArc dDupArc;

  iDupArc = iArc;
  fDupArc = fArc;
  dDupArc = dArc;

  // -----
  // Check
  // -----

  cmpArcs(iArc, iDupArc);
  cmpArcs(fArc, fDupArc);
  cmpArcs(dArc, dDupArc);

  // Ensure operator returns a correct reference on 'this'
  CPPUNIT_ASSERT( &iDupArc == &(iDupArc = iArc) );
  CPPUNIT_ASSERT( &fDupArc == &(fDupArc = fArc) );
  CPPUNIT_ASSERT( &dDupArc == &(dDupArc = dArc) );
}


void
GenArcTest::testIn_Equality()
{
  // ------
  // Set Up
  // ------

  IPoint iSource(-3,  1);
  IPoint iTarget( 0, -2);
  IPoint iCenter(-1,  0);
  IArc ia(iSource, iTarget, iCenter);
  IArc ib(iTarget, iSource, iCenter);

  FPoint fSource(0.f, 3.f);
  FPoint fTarget(4.f, 1.f);
  FPoint fCenter(1.f, 0.f);
  FArc fa(fSource, fTarget, fCenter);
  FArc fb(fTarget, fSource, fCenter);

  DPoint dSource( 4.5, 2.5);
  DPoint dTarget(-0.5, 2.5);
  DPoint dCenter( 2. , 0. );
  DArc da(dSource, dTarget, dCenter);
  DArc db(dTarget, dSource, dCenter);

  // -----
  // Check
  // -----

  // EQUALITY

  // Check operator reflexivity
  CPPUNIT_ASSERT( ia == ia );
  CPPUNIT_ASSERT( fa == fa );
  CPPUNIT_ASSERT( da == da );

  CPPUNIT_ASSERT( ia.eq(ia) );
  CPPUNIT_ASSERT( fa.eq(fa) );
  CPPUNIT_ASSERT( da.eq(da) );

  // Check if an arc is equal to a copy of itself
  CPPUNIT_ASSERT( ia == IArc(ia) );
  CPPUNIT_ASSERT( fa == FArc(fa) );
  CPPUNIT_ASSERT( da == DArc(da) );

  CPPUNIT_ASSERT( ia.eq(IArc(ia)) );
  CPPUNIT_ASSERT( fa.eq(FArc(fa)) );
  CPPUNIT_ASSERT( da.eq(DArc(da)) );

  // Check that an arc is not equal to another, differentarc
  CPPUNIT_ASSERT( !(ia == ib) );
  CPPUNIT_ASSERT( !(fa == fb) );
  CPPUNIT_ASSERT( !(da == db) );

  CPPUNIT_ASSERT( !(ia.eq(ib)) );
  CPPUNIT_ASSERT( !(fa.eq(fb)) );
  CPPUNIT_ASSERT( !(da.eq(db)) );

  // INEQUALITY

  // Check if an arc is equal to itself using operator not equal
  CPPUNIT_ASSERT( !(ia != ia) );
  CPPUNIT_ASSERT( !(fa != fa) );
  CPPUNIT_ASSERT( !(da != da) );

  CPPUNIT_ASSERT( !(ia.notEq(ia)) );
  CPPUNIT_ASSERT( !(fa.notEq(fa)) );
  CPPUNIT_ASSERT( !(da.notEq(da)) );

  // Check if an arc is equal to its copy using operator not equal
  CPPUNIT_ASSERT( !(ia != IArc(ia)) );
  CPPUNIT_ASSERT( !(fa != FArc(fa)) );
  CPPUNIT_ASSERT( !(da != DArc(da)) );

  CPPUNIT_ASSERT( !(ia.notEq(IArc(ia))) );
  CPPUNIT_ASSERT( !(fa.notEq(FArc(fa))) );
  CPPUNIT_ASSERT( !(da.notEq(DArc(da))) );

  // Check if two different arcs are not equal
  CPPUNIT_ASSERT( ia != ib );
  CPPUNIT_ASSERT( fa != fb );
  CPPUNIT_ASSERT( da != db );

  CPPUNIT_ASSERT( ia.notEq(ib) );
  CPPUNIT_ASSERT( fa.notEq(fb) );
  CPPUNIT_ASSERT( da.notEq(db) );
}


// ----------------------------------------------------------------------
// G E O M E T R Y :   T R A N S L A T I O N
// ----------------------------------------------------------------------


void
GenArcTest::testTranslate()
{
  // ------
  // Set Up
  // ------

  int isx = -3;
  int isy = 1;
  int itx = 0;
  int ity = -2;
  int icx = -1;
  int icy = 0;
  IArc iarc(IPoint(isx,isy), IPoint(itx,ity), IPoint(icx,icy));
  int itslx = 18;
  int itsly = 9965;

  float fsx = 0.f;
  float fsy = 3.f;
  float ftx = 4.f;
  float fty = 1.f;
  float fcx = 1.f;
  float fcy = 0.f;
  FArc farc(FPoint(fsx,fsy), FPoint(ftx,fty), FPoint(fcx,fcy));
  float ftslx = 0.f;
  float ftsly = 8756.2341f;

  double dsx = 4.5;
  double dsy = 2.5;
  double dtx = -0.5;
  double dty = 2.5;
  double dcx = 2.;
  double dcy = 0.;
  DArc darc(DPoint(dsx,dsy), DPoint(dtx,dty), DPoint(dcx,dcy));
  double dtslx = -0.004;
  double dtsly = -58435.1581123;

  // -------
  // Process
  // -------

  iarc.translate(itslx,itsly);
  farc.translate(ftslx,ftsly);
  darc.translate(dtslx,dtsly);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( iarc.xSource(), isx + itslx );
  CPPUNIT_ASSERT_EQUAL( iarc.ySource(), isy + itsly );
  CPPUNIT_ASSERT_EQUAL( iarc.xTarget(), itx + itslx );
  CPPUNIT_ASSERT_EQUAL( iarc.yTarget(), ity + itsly );
  CPPUNIT_ASSERT_EQUAL( iarc.xCenter(), icx + itslx );
  CPPUNIT_ASSERT_EQUAL( iarc.yCenter(), icy + itsly );

  CPPUNIT_ASSERT_DOUBLES_EQUAL( farc.xSource(), fsx + ftslx, 0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( farc.ySource(), fsy + ftsly, 0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( farc.xTarget(), ftx + ftslx, 0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( farc.yTarget(), fty + ftsly, 0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( farc.xCenter(), fcx + ftslx, 0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( farc.yCenter(), fcy + ftsly, 0.001 );

  CPPUNIT_ASSERT_DOUBLES_EQUAL( darc.xSource(), dsx + dtslx, 0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( darc.ySource(), dsy + dtsly, 0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( darc.xTarget(), dtx + dtslx, 0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( darc.yTarget(), dty + dtsly, 0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( darc.xCenter(), dcx + dtslx, 0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( darc.yCenter(), dcy + dtsly, 0.001 );
}


// ----------------------------------------------------------------------
// ( D E ) S E R I A L I Z A T I O N
// ----------------------------------------------------------------------


void 
GenArcTest::testSerializeDeserialize()
{
  // ------
  // Set Up
  // ------

  IArc iArc(IPoint(-3,1),       IPoint(0,-2),       IPoint(-1,0));
  FArc fArc(FPoint(-3.1f,1.1f), FPoint(0.1f,-2.1f), FPoint(-1.1f,0.1f));
  DArc dArc(DPoint(-3.2,1.2),   DPoint(0.2,-2.2),   DPoint(-1.2,0.2));

  IArc iOutInArc;
  FArc fOutInArc;
  DArc dOutInArc;
  

  // -------
  // Process
  // -------
  
  std::stringstream ss;

  ss << iArc;
  ss >> iOutInArc;
  ss.flush();

  ss << fArc;
  ss >> fOutInArc;
  ss.flush();

  ss << dArc;
  ss >> dOutInArc;
  ss.flush();

  // -----
  // Check
  // -----

  cmpArcs(iArc, iOutInArc);
  cmpArcs(fArc, fOutInArc);
  cmpArcs(dArc, dOutInArc);
}

// ----------------------------------------------------------------------
