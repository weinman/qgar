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
 * @file  GenQgarArcTest.cpp
 * @brief Implementation of class GenQgarArcTest
 *
 *        See file GenQgarArcTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 27, 2003  15:13
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenQgarArcTest.cpp,v 1.9 2005/10/14 17:06:36 masini Exp $ */



// QGAR
#include <qgarlib/primitives.h>
#include <qgarlib/math.h>
// QGAR TESTS
#include "GenQgarArcTest.h"



using namespace qgar;



// ------------------------------------------------------------------
// U N N A M E D   N A M E S P A C E
// ------------------------------------------------------------------

namespace
{


template<typename T>
bool
cmp(const GenArc<T>& a1, const GenArc<T>& a2)
{
  return
       (a1.accessSource() == a2.accessSource())
    && (a1.accessTarget() == a2.accessTarget())
    && (a1.accessCenter() == a2.accessCenter());
}


template<typename T>
bool
cmp(const GenQgarArc<T>& a1, const GenQgarArc<T>& a2)
{
  return
       (a1.color()     == a2.color())
    && (a1.thickness() == a2.thickness())
    && (a1.outline()   == a2.outline());
}


} // unnamed namespace



// ------------------------------------------------------------------
// T E S T    F I X T U R E   I M P L E M E N T A T I O N
// ------------------------------------------------------------------

void
GenQgarArcTest::setUp()
{
  /* EMPTY */
}

void
GenQgarArcTest::tearDown()
{
  /* EMPTY */
}


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------

void
GenQgarArcTest::testDefaultConstructor()
{
  // ------
  // Set Up
  // ------

  IQgarArc iqArc(2, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);
  FQgarArc fqArc(2, QGE_COLOR_BLUE);
  DQgarArc dqArc(2);
  DQgarArc dqArc0;


  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqArc.thickness() == 2 );
  CPPUNIT_ASSERT( iqArc.color()     == QGE_COLOR_BLUE );
  CPPUNIT_ASSERT( iqArc.outline()   == QGE_OUTLINE_DASH_SS );
  CPPUNIT_ASSERT( cmp(iqArc.accessGeomStructure(), IArc()) );

  CPPUNIT_ASSERT( fqArc.thickness() == 2 );
  CPPUNIT_ASSERT( fqArc.color()     == QGE_COLOR_BLUE );
  CPPUNIT_ASSERT( fqArc.outline()   == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( cmp(fqArc.accessGeomStructure(), FArc()) );

  CPPUNIT_ASSERT( dqArc.thickness() == 2 );
  CPPUNIT_ASSERT( dqArc.color()     == QGE_COLOR_DEFAULT );
  CPPUNIT_ASSERT( dqArc.outline()   == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( cmp(dqArc.accessGeomStructure(), DArc()) );

  CPPUNIT_ASSERT( dqArc0.thickness() == 1 );
  CPPUNIT_ASSERT( dqArc0.color()     == QGE_COLOR_DEFAULT );
  CPPUNIT_ASSERT( dqArc0.outline()   == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( cmp(dqArc0.accessGeomStructure(), DArc()) );
}


void
GenQgarArcTest::testBuildFrom3Points()
{
  // ------
  // Set Up
  // ------
  
  IPoint iPt0(4,-1);
  IPoint iPt1(7, 2);
  IPoint iCenter(-1, 10);

  FPoint fPt0(14.4f,-1.28f);
  FPoint fPt1(3.2f, 7.12f);
  FPoint fCenter(2, 3);

  DPoint dPt0(2.33, 0.38);
  DPoint dPt1(9.73, 3.525);
  DPoint dCenter(0.005, 20.221);

  // -------
  // Process
  // -------

  IQgarArc iqArc(iPt0, iPt1, iCenter, 2, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);
  FQgarArc fqArc(fPt0, fPt1, fCenter, 2, QGE_COLOR_BLUE);
  DQgarArc dqArc(dPt0, dPt1, dCenter, 2);
  DQgarArc dqArc0(dPt0, dPt1, dCenter);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqArc.thickness() == 2 );
  CPPUNIT_ASSERT( iqArc.color()     == QGE_COLOR_BLUE );
  CPPUNIT_ASSERT( iqArc.outline()   == QGE_OUTLINE_DASH_SS );
  CPPUNIT_ASSERT( cmp(iqArc.accessGeomStructure(), IArc(iPt0, iPt1, iCenter)) );

  CPPUNIT_ASSERT( fqArc.thickness() == 2 );
  CPPUNIT_ASSERT( fqArc.color()     == QGE_COLOR_BLUE );
  CPPUNIT_ASSERT( fqArc.outline()   == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( cmp(fqArc.accessGeomStructure(), FArc(fPt0, fPt1, fCenter)) );

  CPPUNIT_ASSERT( dqArc.thickness() == 2 );
  CPPUNIT_ASSERT( dqArc.color()     == QGE_COLOR_DEFAULT );
  CPPUNIT_ASSERT( dqArc.outline()   == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( cmp(dqArc.accessGeomStructure(), DArc(dPt0, dPt1, dCenter)) );

  CPPUNIT_ASSERT( dqArc0.thickness() == 1 );
  CPPUNIT_ASSERT( dqArc0.color()     == QGE_COLOR_DEFAULT );
  CPPUNIT_ASSERT( dqArc0.outline()   == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( cmp(dqArc0.accessGeomStructure(), DArc(dPt0, dPt1, dCenter)) );
}


void
GenQgarArcTest::testBuildFromArc()
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

  IQgarArc iqArc(iArc, 2, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);
  FQgarArc fqArc(fArc, 2, QGE_COLOR_BLUE);
  DQgarArc dqArc(dArc, 2);
  DQgarArc dqArc0(dArc);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqArc.thickness() == 2 );
  CPPUNIT_ASSERT( iqArc.color()     == QGE_COLOR_BLUE );
  CPPUNIT_ASSERT( iqArc.outline()   == QGE_OUTLINE_DASH_SS );
  CPPUNIT_ASSERT( cmp(iqArc.accessGeomStructure(), iArc) );

  CPPUNIT_ASSERT( fqArc.thickness() == 2 );
  CPPUNIT_ASSERT( fqArc.color()     == QGE_COLOR_BLUE );
  CPPUNIT_ASSERT( fqArc.outline()   == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( cmp(fqArc.accessGeomStructure(), fArc) );

  CPPUNIT_ASSERT( dqArc.thickness() == 2 );
  CPPUNIT_ASSERT( dqArc.color()     == QGE_COLOR_DEFAULT );
  CPPUNIT_ASSERT( dqArc.outline()   == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( cmp(dqArc.accessGeomStructure(), dArc) );

  CPPUNIT_ASSERT( dqArc0.thickness() == 1 );
  CPPUNIT_ASSERT( dqArc0.color()     == QGE_COLOR_DEFAULT );
  CPPUNIT_ASSERT( dqArc0.outline()   == QGE_OUTLINE_DEFAULT );
  CPPUNIT_ASSERT( cmp(dqArc0.accessGeomStructure(), dArc) );
}


void
GenQgarArcTest::testCopyConstructor()
{
  // ------
  // Set Up
  // ------

  IQgarArc iqArc(IPoint(-3,1),
		 IPoint(0,-2),
		 IPoint(-1,0),
		 3,
		 QGE_COLOR_BLUE,
		 QGE_OUTLINE_DASH_SS);

  FQgarArc fqArc(FPoint(-3.1f,1.1f),
		 FPoint(0.1f,-2.1f),
		 FPoint(-1.1f,0.1f),
		 2,
		 QGE_COLOR_BLUE,
		 QGE_OUTLINE_DASH_SS);

  DQgarArc dqArc(DPoint(-3.2,1.2),
		 DPoint(0.2,-2.2),
		 DPoint(-1.2,0.2),
		 4,
		 QGE_COLOR_BLUE,
		 QGE_OUTLINE_DASH_SS);

  // -------
  // Process
  // --------
  
  IQgarArc iDupArc(iqArc);
  FQgarArc fDupArc(fqArc);
  DQgarArc dDupArc(dqArc);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( cmp(iqArc, iDupArc) );
  CPPUNIT_ASSERT( cmp(iqArc.accessGeomStructure(), iDupArc.accessGeomStructure()) );
  CPPUNIT_ASSERT( cmp(fqArc, fDupArc) );
  CPPUNIT_ASSERT( cmp(fqArc.accessGeomStructure(), fDupArc.accessGeomStructure()) );
  CPPUNIT_ASSERT( cmp(dqArc, dDupArc) );
  CPPUNIT_ASSERT( cmp(dqArc.accessGeomStructure(), dDupArc.accessGeomStructure()) );
}


// ----------------------------------------------------------------------
// C O P Y
// ----------------------------------------------------------------------


void
GenQgarArcTest::testClone()
{
  // ------
  // Set Up
  // ------

  IQgarArc iqArc(IPoint(-3,1), IPoint(0,-2), IPoint(-1,0),
		 2, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);

  FQgarArc fqArc(FPoint(-3.1f,1.1f), FPoint(0.1f,-2.1f), FPoint(-1.1f,0.1f),
		 3, QGE_COLOR_RED, QGE_OUTLINE_DASH_LSS);

  DQgarArc dqArc(DPoint(-3.2,1.2), DPoint(0.2,-2.2), DPoint(-1.2,0.2),
		 4, QGE_COLOR_GREEN, QGE_OUTLINE_DOT);

  // -------
  // Process
  // --------
  
  IQgarArc* iDupArc = iqArc.clone();
  FQgarArc* fDupArc = fqArc.clone();
  DQgarArc* dDupArc = dqArc.clone();

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( cmp(iqArc, *iDupArc) );
  CPPUNIT_ASSERT( cmp(iqArc.accessGeomStructure(), iDupArc->accessGeomStructure()) );
  CPPUNIT_ASSERT( cmp(fqArc, *fDupArc) );
  CPPUNIT_ASSERT( cmp(fqArc.accessGeomStructure(), fDupArc->accessGeomStructure()) );
  CPPUNIT_ASSERT( cmp(dqArc, *dDupArc) );
  CPPUNIT_ASSERT( cmp(dqArc.accessGeomStructure(), dDupArc->accessGeomStructure()) );

  // ---------
  // Tear Down
  // ---------

  delete iDupArc;
  delete fDupArc;
  delete dDupArc;
}


// ----------------------------------------------------------------------
// ACCESS TO GEOMETRICAL FEATURES
// ----------------------------------------------------------------------


void
GenQgarArcTest:: testRadius()
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

  IQgarArc iqa(IPoint(isx,isy), IPoint(itx,ity), IPoint(icx,icy),
	       2, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);

  float fcx = -1.f;
  float fcy = -2.f;
  float fsx = 2.f;
  float fsy = -6.f;
  float ftx = -4.f;
  float fty = 2.f;

  FQgarArc fqa(FPoint(fsx,fsy), FPoint(ftx,fty), FPoint(fcx,fcy),
	       3, QGE_COLOR_BLUE);

  double dcx = -100001.;
  double dcy = -100000.;
  double dsx = -100000.;
  double dsy = -100002.;
  double dtx = -100002.;
  double dty = -100002.;

  DQgarArc dqa(DPoint(dsx,dsy), DPoint(dtx,dty), DPoint(dcx,dcy), 4);

  // -----
  // Check
  // -----
  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iqa.radius(), 3.,  Math::epsilonD());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fqa.radius(), 5.f, Math::epsilonF());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dqa.radius(),
			       2.23606797749979,   // sqrt(5)
			       Math::epsilonD()); 

}


void
GenQgarArcTest::testLength()
{
  // ------
  // Set Up
  // ------
   
  double cx1 = -1.;
  double cy1 =  0.;
  double sx1 = -3.;
  double sy1 = -1.;
  double tx1 = 0.;
  double ty1 = -2.;
  DQgarArc dqa1(DPoint(sx1,sy1), DPoint(tx1,ty1), DPoint(cx1,cy1));

  double cx2 = -1.;
  double cy2 = -2.;
  double sx2 = 2.;
  double sy2 = -6.;
  double tx2 = -4.;
  double ty2 = 2.;
  DQgarArc dqa2(DPoint(sx2,sy2), DPoint(tx2,ty2), DPoint(cx2,cy2));

  // -------
  // Process
  // -------

  double sAng1 = dqa1.sourceAngle();
  double tAng1 = dqa1.targetAngle();
  double r1    = dqa1.radius();
  double l1    = dqa1.length();

  double l2    = dqa2.length(); // radius == 5.

  // -----
  // Check
  // -----
  
  if (sAng1 > tAng1)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(r1 * (Math::QG_2PI - sAng1 + tAng1),
				   l1,
				   Math::epsilonD());
    }
  else
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(r1 * (tAng1 - sAng1),
				   l1,
				   Math::epsilonD());
    }    

  CPPUNIT_ASSERT_DOUBLES_EQUAL( l2, 5. * Math::QG_PI, Math::epsilonD() );
  
}


void
GenQgarArcTest::testAngles()
{
  // ------
  // Set Up
  // ------

  IPoint iSource(-3,  1);
  IPoint iTarget( 0, -2);
  IPoint iCenter(-1,  0);
  IQgarArc iqArc(iSource, iTarget, iCenter, 2, QGE_COLOR_BROWN, QGE_OUTLINE_DOT);

  FPoint fSource(0.f, 3.f);
  FPoint fTarget(4.f, 1.f);
  FPoint fCenter(1.f, 0.f);
  FQgarArc fqArc(fSource, fTarget, fCenter, 7, QGE_COLOR_GRAY);

  DPoint dSource( 4.5, 2.5);
  DPoint dTarget(-0.5, 2.5);
  DPoint dCenter( 2. , 0. );
  DQgarArc dqArc(dSource, dTarget, dCenter, 3, QGE_COLOR_ORANGE, QGE_OUTLINE_DASH_SS);
  
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
  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iqArc.sourceAngle(),
			       isAng,
			       Math::epsilonRadian());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iqArc.sourceAngleDegrees(),
			       isAngDeg,
			       Math::epsilonDegree());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iqArc.targetAngle(),
			       itAng,
			       Math::epsilonRadian());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iqArc.targetAngleDegrees(),
			       itAngDeg,
			       Math::epsilonDegree());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iqArc.angle(),
			       iAng,
			       Math::epsilonRadian());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(iqArc.angleDegrees(),
			       iAngDeg,
			       Math::epsilonDegree());

  CPPUNIT_ASSERT_DOUBLES_EQUAL(fqArc.sourceAngle(),
			       fsAng,
			       Math::epsilonRadian());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fqArc.sourceAngleDegrees(),
			       fsAngDeg,
			       Math::epsilonDegree());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fqArc.targetAngle(),
			       ftAng,
			       Math::epsilonRadian());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fqArc.targetAngleDegrees(),
			       ftAngDeg,
			       Math::epsilonDegree());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fqArc.angle(),
			       fAng,
			       Math::epsilonRadian());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(fqArc.angleDegrees(),
			       fAngDeg,
			       Math::epsilonDegree());

  CPPUNIT_ASSERT_DOUBLES_EQUAL(dqArc.sourceAngle(),
			       dsAng,
			       Math::epsilonRadian());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dqArc.sourceAngleDegrees(),
			       dsAngDeg,
			       Math::epsilonDegree());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dqArc.targetAngle(),
			       dtAng,
			       Math::epsilonRadian());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dqArc.targetAngleDegrees(),
			       dtAngDeg,
			       Math::epsilonDegree());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dqArc.angle(),
			       dAng,
			       Math::epsilonRadian());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dqArc.angleDegrees(),
			       dAngDeg,
			       Math::epsilonDegree());
}


// ----------------------------------------------------------------------
// C E N T E R
// ----------------------------------------------------------------------


void
GenQgarArcTest::testCenter()
{
  // ------
  // Set Up
  // ------
   
  int icx = 2;
  int icy = 4;
  
  IPoint ic(icx, icy);
  IPoint is(2, 8);
  IPoint it(6, 4);

  IQgarArc iqa(is, it, ic, 10, QGE_COLOR_DARK_GRAY);

  // ----------------------
  // Get center coordinates
  // ----------------------

  CPPUNIT_ASSERT_EQUAL( iqa.xCenter(), icx );
  CPPUNIT_ASSERT_EQUAL( iqa.yCenter(), icy );

  // ----------------------
  // Set center coordinates
  // ----------------------

  iqa.setXCenter(icx - 3);
  CPPUNIT_ASSERT_EQUAL( iqa.xCenter(), icx - 3 );

  iqa.setYCenter(icy - 3);
  CPPUNIT_ASSERT_EQUAL( iqa.yCenter(), icy - 3 );

  iqa.setCenter(icx + 2, icy + 2);
  CPPUNIT_ASSERT_EQUAL( iqa.xCenter(), icx + 2 );
  CPPUNIT_ASSERT_EQUAL( iqa.yCenter(), icy + 2 );

  iqa.setCenter(ic);
  CPPUNIT_ASSERT_EQUAL( iqa.xCenter(), icx );
  CPPUNIT_ASSERT_EQUAL( iqa.yCenter(), icy );

  // ------------------------
  // Get a copy of the center
  // ------------------------

  IPoint icopy = iqa.center();
  CPPUNIT_ASSERT_EQUAL( icopy.x(), icx );
  CPPUNIT_ASSERT_EQUAL( icopy.y(), icy );

  // Initial center is not modified when modifying copy
  icopy.setX(0);
  icopy.setY(0);
  CPPUNIT_ASSERT_EQUAL( iqa.xCenter(), icx );
  CPPUNIT_ASSERT_EQUAL( iqa.yCenter(), icy );
  CPPUNIT_ASSERT_EQUAL( icopy.x(),    0   );
  CPPUNIT_ASSERT_EQUAL( icopy.y(),    0   );

  // --------------
  // Get the center
  // --------------

  const IPoint& icenter = iqa.accessCenter();
  CPPUNIT_ASSERT_EQUAL( icenter.x(), icx );
  CPPUNIT_ASSERT_EQUAL( icenter.y(), icy );

  // Initial center is modified when modifying reference
  iqa.setXCenter(0);
  iqa.setYCenter(0);
  CPPUNIT_ASSERT_EQUAL( iqa.xCenter(), 0 );
  CPPUNIT_ASSERT_EQUAL( iqa.yCenter(), 0 );
  CPPUNIT_ASSERT_EQUAL( icenter.x(),  0 );
  CPPUNIT_ASSERT_EQUAL( icenter.y(),  0 );
}


// ----------------------------------------------------------------------
// O P E R A T O R S
// ----------------------------------------------------------------------


void 
GenQgarArcTest::testAssignment()
{
  // ------
  // Set Up
  // ------

  IQgarArc iqa(IPoint(-3,1), IPoint(0,-2), IPoint(-1,0),
	       3, QGE_COLOR_RED, QGE_OUTLINE_DOT);

  FQgarArc fqa(FPoint(-3.1f,1.1f), FPoint(0.1f,-2.1f), FPoint(-1.1f,0.1f),
	       5, QGE_COLOR_OLIVE_GREEN, QGE_OUTLINE_DOT);

  DQgarArc dqa(DPoint(-3.2,1.2),   DPoint(0.2,-2.2),   DPoint(-1.2,0.2),
	       2, QGE_COLOR_CHOCOLATE_BROWN, QGE_OUTLINE_DASH_SS);

  // -------
  // Process
  // -------

  IQgarArc iqaDup;
  FQgarArc fqaDup;
  DQgarArc dqaDup;

  iqaDup = iqa;
  fqaDup = fqa;
  dqaDup = dqa;

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( cmp(iqa, iqaDup) );
  CPPUNIT_ASSERT( cmp(fqa, fqaDup) );
  CPPUNIT_ASSERT( cmp(dqa, dqaDup) );

  // Ensure operator returns a correct reference on 'this'
  CPPUNIT_ASSERT( &iqaDup == &(iqaDup = iqa) );
  CPPUNIT_ASSERT( &fqaDup == &(fqaDup = fqa) );
  CPPUNIT_ASSERT( &dqaDup == &(dqaDup = dqa) );
}


void
GenQgarArcTest::testIn_Equality()
{
  // ------
  // Set Up
  // ------

  IPoint iSource(-3,  1);
  IPoint iTarget( 0, -2);
  IPoint iCenter(-1,  0);
  IQgarArc iqa(iSource, iTarget, iCenter);
  IQgarArc iqb(iTarget, iSource, iCenter);

  FPoint fSource(0.f, 3.f);
  FPoint fTarget(4.f, 1.f);
  FPoint fCenter(1.f, 0.f);
  FQgarArc fqa(fSource, fTarget, fCenter);
  FQgarArc fqb(fTarget, fSource, fCenter);

  DPoint dSource( 4.5, 2.5);
  DPoint dTarget(-0.5, 2.5);
  DPoint dCenter( 2. , 0. );
  DQgarArc dqa(dSource, dTarget, dCenter);
  DQgarArc dqb(dTarget, dSource, dCenter);

  // -----
  // Check
  // -----

  // EQUALITY

  // Check operator reflexivity
  CPPUNIT_ASSERT( iqa == iqa );
  CPPUNIT_ASSERT( fqa == fqa );
  CPPUNIT_ASSERT( dqa == dqa );

  CPPUNIT_ASSERT( iqa.eq(iqa) );
  CPPUNIT_ASSERT( fqa.eq(fqa) );
  CPPUNIT_ASSERT( dqa.eq(dqa) );

  // Check if an arc is equal to a copy of itself
  CPPUNIT_ASSERT( iqa == IArc(iqa) );
  CPPUNIT_ASSERT( fqa == FArc(fqa) );
  CPPUNIT_ASSERT( dqa == DArc(dqa) );

  CPPUNIT_ASSERT( iqa.eq(IArc(iqa)) );
  CPPUNIT_ASSERT( fqa.eq(FArc(fqa)) );
  CPPUNIT_ASSERT( dqa.eq(DArc(dqa)) );

  // Check that an arc is not equal to another, differentarc
  CPPUNIT_ASSERT( !(iqa == iqb) );
  CPPUNIT_ASSERT( !(fqa == fqb) );
  CPPUNIT_ASSERT( !(dqa == dqb) );

  CPPUNIT_ASSERT( !(iqa.eq(iqb)) );
  CPPUNIT_ASSERT( !(fqa.eq(fqb)) );
  CPPUNIT_ASSERT( !(dqa.eq(dqb)) );

  // INEQUALITY

  // Check if an arc is equal to itself using operator not equal
  CPPUNIT_ASSERT( !(iqa != iqa) );
  CPPUNIT_ASSERT( !(fqa != fqa) );
  CPPUNIT_ASSERT( !(dqa != dqa) );

  CPPUNIT_ASSERT( !(iqa.notEq(iqa)) );
  CPPUNIT_ASSERT( !(fqa.notEq(fqa)) );
  CPPUNIT_ASSERT( !(dqa.notEq(dqa)) );

  // Check if an arc is equal to its copy using operator not equal
  CPPUNIT_ASSERT( !(iqa != IArc(iqa)) );
  CPPUNIT_ASSERT( !(fqa != FArc(fqa)) );
  CPPUNIT_ASSERT( !(dqa != DArc(dqa)) );

  CPPUNIT_ASSERT( !(iqa.notEq(IArc(iqa))) );
  CPPUNIT_ASSERT( !(fqa.notEq(FArc(fqa))) );
  CPPUNIT_ASSERT( !(dqa.notEq(DArc(dqa))) );

  // Check if two different arcs are not equal
  CPPUNIT_ASSERT( iqa != iqb );
  CPPUNIT_ASSERT( fqa != fqb );
  CPPUNIT_ASSERT( dqa != dqb );

  CPPUNIT_ASSERT( iqa.notEq(iqb) );
  CPPUNIT_ASSERT( fqa.notEq(fqb) );
  CPPUNIT_ASSERT( dqa.notEq(dqb) );
}


// ----------------------------------------------------------------------
// G E O M E T R Y :   T R A N S L A T I O N
// ----------------------------------------------------------------------


void
GenQgarArcTest::testTranslate()
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
  int itslx = 18;
  int itsly = 9965;
  IQgarArc iqa(IPoint(isx,isy), IPoint(itx,ity), IPoint(icx,icy),
               8, QGE_COLOR_RED, QGE_OUTLINE_DOT);

  float fsx = 0.f;
  float fsy = 3.f;
  float ftx = 4.f;
  float fty = 1.f;
  float fcx = 1.f;
  float fcy = 0.f;
  float ftslx = 0.f;
  float ftsly = 8756.2341f;
  FQgarArc fqa(FPoint(fsx,fsy), FPoint(ftx,fty), FPoint(fcx,fcy),
	       8, QGE_COLOR_RED, QGE_OUTLINE_DOT);

  double dsx = 4.5;
  double dsy = 2.5;
  double dtx = -0.5;
  double dty = 2.5;
  double dcx = 2.;
  double dcy = 0.;
  double dtslx = -0.004;
  double dtsly = -58435.1581123;
  DQgarArc dqa(DPoint(dsx,dsy), DPoint(dtx,dty), DPoint(dcx,dcy),
               8, QGE_COLOR_RED, QGE_OUTLINE_DOT);

  // -------
  // Process
  // -------

  iqa.translate(itslx,itsly);
  fqa.translate(ftslx,ftsly);
  dqa.translate(dtslx,dtsly);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( iqa.xSource(), isx + itslx );
  CPPUNIT_ASSERT_EQUAL( iqa.ySource(), isy + itsly );
  CPPUNIT_ASSERT_EQUAL( iqa.xTarget(), itx + itslx );
  CPPUNIT_ASSERT_EQUAL( iqa.yTarget(), ity + itsly );
  CPPUNIT_ASSERT_EQUAL( iqa.xCenter(), icx + itslx );
  CPPUNIT_ASSERT_EQUAL( iqa.yCenter(), icy + itsly );

  CPPUNIT_ASSERT_DOUBLES_EQUAL( fqa.xSource(), fsx + ftslx, 0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( fqa.ySource(), fsy + ftsly, 0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( fqa.xTarget(), ftx + ftslx, 0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( fqa.yTarget(), fty + ftsly, 0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( fqa.xCenter(), fcx + ftslx, 0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( fqa.yCenter(), fcy + ftsly, 0.001 );

  CPPUNIT_ASSERT_DOUBLES_EQUAL( dqa.xSource(), dsx + dtslx, 0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( dqa.ySource(), dsy + dtsly, 0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( dqa.xTarget(), dtx + dtslx, 0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( dqa.yTarget(), dty + dtsly, 0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( dqa.xCenter(), dcx + dtslx, 0.001 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( dqa.yCenter(), dcy + dtsly, 0.001 );
}


// ----------------------------------------------------------------------
// ( D E ) S E R I A L I Z A T I O N
// ----------------------------------------------------------------------


void
GenQgarArcTest::testSerializeDeserialize()
{
  // ------
  // Set Up
  // ------

  IQgarArc iqa(IPoint(-3,1), IPoint(0,-2), IPoint(-1,0),
	       2, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);

  FQgarArc fqa(FPoint(-3.1f,1.1f), FPoint(0.1f,-2.1f), FPoint(-1.1f,0.1f),
	       2, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);

  DQgarArc dqa(DPoint(-3.2,1.2), DPoint(0.2,-2.2), DPoint(-1.2,0.2),
	       2, QGE_COLOR_BLUE, QGE_OUTLINE_DASH_SS);

  IQgarArc iqaOutIn;
  FQgarArc fqaOutIn;
  DQgarArc dqaOutIn;

  // -------
  // Process
  // -------
  
  std::stringstream ss;

  ss << iqa;
  ss >> iqaOutIn;
  ss.flush();

  ss << fqa;
  ss >> fqaOutIn;
  ss.flush();

  ss << dqa;
  ss >> dqaOutIn;
  ss.flush();

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( cmp(iqa, iqaOutIn) );
  CPPUNIT_ASSERT( cmp(iqa.accessGeomStructure(), iqaOutIn.accessGeomStructure()) );

  CPPUNIT_ASSERT( cmp(fqa, fqaOutIn) );
  CPPUNIT_ASSERT( cmp(fqa.accessGeomStructure(), fqaOutIn.accessGeomStructure()) );

  CPPUNIT_ASSERT( cmp(dqa, dqaOutIn) );
  CPPUNIT_ASSERT( cmp(dqa.accessGeomStructure(), dqaOutIn.accessGeomStructure()) );
}

// -------------------------------------------------------------------
