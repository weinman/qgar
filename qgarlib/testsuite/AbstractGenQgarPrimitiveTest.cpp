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
 * @file  AbstractGenQgarPrimitiveTest.cpp
 * @brief Implementation of class AbstractGenQgarPrimitiveTest
 *
 *        See file AbstractGenQgarPrimitiveTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 29, 2003  16:12
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: AbstractGenQgarPrimitiveTest.cpp,v 1.5 2005/07/13 16:29:34 masini Exp $ */



// QGAR TESTS
#include "AbstractGenQgarPrimitiveTest.h"
// QGAR
#include <qgarlib/primitives.h>



using namespace qgar;


namespace
{

// ------------------------------------------------------------------
// U N N A M E D   N A M E S P A C E
// ------------------------------------------------------------------


/**
 * @brief Class implementing AbstractGenQgarPrimitive<T> defined for
 * testing purpose.
 *
 * <p>
 * This class is used to test the AbstractGenQgarPrimitive<T> class.
 * Since the latter class is abstract, it cannot directly be tested.
 * </p>
 * <p>
 * This class provide the minimal implementation of the abstraction.
 * It thus provides a constructor for each constructors of the base
 * class and implements all base class virtual function member.
 * </p>
 */
template <class T> 
class GenQgarPrimitiveImpl : public AbstractGenQgarPrimitive<T>
{
public:

  /**
   * @brief Constructor from coordinates.
   */
  GenQgarPrimitiveImpl<T>(T XSource,
			  T YSource,
			  T XTarget,
			  T YTarget,
			  int        aThickness = 1,
			  QGEcolor   aColor     = QGE_COLOR_BLACK,
			  QGEoutline anOutline  = QGE_OUTLINE_SOLID)
    : AbstractGenQgarPrimitive<T>(aThickness, aColor, anOutline),
      _seg(XSource, YSource, XTarget, YTarget)
  {
    /* EMPTY */
  }

  /**
   * @brief Default Constructor.
   */
  GenQgarPrimitiveImpl<T>(int        aThickness = 1,
			  QGEcolor   aColor     = QGE_COLOR_BLACK,
			  QGEoutline anOutline  = QGE_OUTLINE_SOLID)
    : AbstractGenQgarPrimitive<T>(aThickness, aColor, anOutline)
  {
    /* EMPTY */
  }

  /**
   * @brief Copy constructor
   */
  GenQgarPrimitiveImpl<T>(const GenQgarPrimitiveImpl<T>& other)
    : AbstractGenQgarPrimitive<T>(other)
  {
    /* EMPTY */
  }

  virtual const AbstractGenPrimitive<T>& accessGeomStructure() const
  {
    return _seg;
  }

  virtual AbstractGenQgarPrimitive<T>* clone() const
  {
    return 0;
  }

  virtual AbstractGenPrimitive<T>& getGeomStructure()
  {
    return _seg;
  }

private:
  
  GenSegment<T> _seg;
};


// Handy typedefs.
typedef GenQgarPrimitiveImpl<int>    IQgarPrimitiveImpl;
typedef GenQgarPrimitiveImpl<float>  FQgarPrimitiveImpl;
typedef GenQgarPrimitiveImpl<double> DQgarPrimitiveImpl;

} // unnamed namespace


// ------------------------------------------------------------------
// T E S T F I X T U R E   I M P L
// ------------------------------------------------------------------


void
AbstractGenQgarPrimitiveTest::setUp()
{
  /* EMPTY */
}


void
AbstractGenQgarPrimitiveTest::tearDown()
{
  /* EMPTY */
}


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// ------------------------------------------------------------------


void
AbstractGenQgarPrimitiveTest::testDefaultConstructor()
{
  // -------
  // Process
  // -------
  
  IQgarPrimitiveImpl iqPrim(2, QGE_COLOR_BLUE, QGE_OUTLINE_DOT);
  FQgarPrimitiveImpl fqPrim(2, QGE_COLOR_BLUE, QGE_OUTLINE_DOT);
  DQgarPrimitiveImpl dqPrim(2, QGE_COLOR_BLUE, QGE_OUTLINE_DOT);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqPrim.thickness() == 2);
  CPPUNIT_ASSERT( iqPrim.color()     == QGE_COLOR_BLUE );
  CPPUNIT_ASSERT( iqPrim.outline()   == QGE_OUTLINE_DOT );
  CPPUNIT_ASSERT( iqPrim.source()    == IPoint(0,0) );
  CPPUNIT_ASSERT( iqPrim.target()    == IPoint(0,0) );

  CPPUNIT_ASSERT( fqPrim.thickness() == 2);
  CPPUNIT_ASSERT( fqPrim.color()     == QGE_COLOR_BLUE );
  CPPUNIT_ASSERT( fqPrim.outline()   == QGE_OUTLINE_DOT );
  CPPUNIT_ASSERT( fqPrim.source()    == FPoint(0.F,0.F) );
  CPPUNIT_ASSERT( fqPrim.target()    == FPoint(0.F,0.F) );

  CPPUNIT_ASSERT( dqPrim.thickness() == 2);
  CPPUNIT_ASSERT( dqPrim.color()     == QGE_COLOR_BLUE );
  CPPUNIT_ASSERT( dqPrim.outline()   == QGE_OUTLINE_DOT );
  CPPUNIT_ASSERT( dqPrim.source()    == DPoint(0.0,0.0) );
  CPPUNIT_ASSERT( dqPrim.target()    == DPoint(0.0,0.0) );
}


void
AbstractGenQgarPrimitiveTest::testCopyConstructor()
{
  // ------
  // Set Up
  // ------

  IQgarPrimitiveImpl iqPrim(2, QGE_COLOR_BLUE, QGE_OUTLINE_DOT);
  FQgarPrimitiveImpl fqPrim(2, QGE_COLOR_BLUE, QGE_OUTLINE_DOT);
  DQgarPrimitiveImpl dqPrim(2, QGE_COLOR_BLUE, QGE_OUTLINE_DOT);

  // -------
  // Process
  // -------

  IQgarPrimitiveImpl iqDupPrim(iqPrim);
  FQgarPrimitiveImpl fqDupPrim(fqPrim);
  DQgarPrimitiveImpl dqDupPrim(dqPrim);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqPrim.thickness() == iqDupPrim.thickness() );
  CPPUNIT_ASSERT( iqPrim.color() == iqDupPrim.color() );
  CPPUNIT_ASSERT( iqPrim.outline() == iqDupPrim.outline() );

  CPPUNIT_ASSERT( fqPrim.thickness() == fqDupPrim.thickness() );
  CPPUNIT_ASSERT( fqPrim.color() == fqDupPrim.color() );
  CPPUNIT_ASSERT( fqPrim.outline() == fqDupPrim.outline() );

  CPPUNIT_ASSERT( dqPrim.thickness() == dqDupPrim.thickness() );
  CPPUNIT_ASSERT( dqPrim.color() == dqDupPrim.color() );
  CPPUNIT_ASSERT( dqPrim.outline() == dqDupPrim.outline() );
}


// -------------------------------------------------------------------
// A C C E S S   T O   C O O R D I N A T E S
// -------------------------------------------------------------------


void
AbstractGenQgarPrimitiveTest::testCoordinatesCoherency()
{
  // ------
  // Set Up
  // ------
  
  IQgarPrimitiveImpl iqPrim;
  FQgarPrimitiveImpl fqPrim;
  DQgarPrimitiveImpl dqPrim;

  iqPrim.setSource(IPoint(0, 3));
  iqPrim.setTarget(IPoint(3, 6));

  fqPrim.setSource(FPoint(0.489F, 3.984F));
  fqPrim.setTarget(FPoint(3, 6));

  dqPrim.setSource(DPoint(0.004, 3.298));
  dqPrim.setTarget(DPoint(9.874, 6.487));

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqPrim.xSource() == iqPrim.source().x() );
  CPPUNIT_ASSERT( iqPrim.ySource() == iqPrim.source().y() );  
  CPPUNIT_ASSERT( iqPrim.xTarget() == iqPrim.target().x() );
  CPPUNIT_ASSERT( iqPrim.yTarget() == iqPrim.target().y() );

  CPPUNIT_ASSERT( fqPrim.xSource() == fqPrim.source().x() );
  CPPUNIT_ASSERT( fqPrim.ySource() == fqPrim.source().y() );  
  CPPUNIT_ASSERT( fqPrim.xTarget() == fqPrim.target().x() );
  CPPUNIT_ASSERT( fqPrim.yTarget() == fqPrim.target().y() );

  CPPUNIT_ASSERT( dqPrim.xSource() == dqPrim.source().x() );
  CPPUNIT_ASSERT( dqPrim.ySource() == dqPrim.source().y() );  
  CPPUNIT_ASSERT( dqPrim.xTarget() == dqPrim.target().x() );
  CPPUNIT_ASSERT( dqPrim.yTarget() == dqPrim.target().y() );

  CPPUNIT_ASSERT( iqPrim.source() == iqPrim.accessSource() );
  CPPUNIT_ASSERT( iqPrim.target() == iqPrim.accessTarget() );

  CPPUNIT_ASSERT( fqPrim.source() == fqPrim.accessSource() );
  CPPUNIT_ASSERT( fqPrim.target() == fqPrim.accessTarget() );

  CPPUNIT_ASSERT( dqPrim.source() == dqPrim.accessSource() );
  CPPUNIT_ASSERT( dqPrim.target() == dqPrim.accessTarget() );
}


// -------------------------------------------------------------------
// ACCESS TO GEOMETRICAL CHARACTERISTICS
// -------------------------------------------------------------------


void
AbstractGenQgarPrimitiveTest::testDxDy()
{
  // ------
  // Set Up
  // ------

  int ix0 = 843;
  int iy0 = -51;
  int ix1 = 22;
  int iy1 = 71;

  float fx0 = 8.3F;
  float fy0 = -5.1F;
  float fx1 = 21.212F;
  float fy1 = -31.74861F;  

  double dx0 = 1.444001;
  double dy0 = -0.0001;
  double dx1 = 2980;
  double dy1 = 7.21;

  IQgarPrimitiveImpl iqPrim(ix0, iy0, ix1, iy1);
  FQgarPrimitiveImpl fqPrim(fx0, fy0, fx1, fy1);
  DQgarPrimitiveImpl dqPrim(dx0, dy0, dx1, dy1);

  // -----
  // Check
  // -----
  
  CPPUNIT_ASSERT_EQUAL( (ix1 - ix0), iqPrim.dx() );
  CPPUNIT_ASSERT_EQUAL( (fx1 - fx0), fqPrim.dx() );
  CPPUNIT_ASSERT_EQUAL( (dx1 - dx0), dqPrim.dx() );

  CPPUNIT_ASSERT_EQUAL( (iy1 - iy0), iqPrim.dy() );
  CPPUNIT_ASSERT_EQUAL( (fy1 - fy0), fqPrim.dy() );
  CPPUNIT_ASSERT_EQUAL( (dy1 - dy0), dqPrim.dy() );
}


// -------------------------------------------------------------------
// S E T   A T T R I B U T E S
// -------------------------------------------------------------------


void
AbstractGenQgarPrimitiveTest::testSetColor()
{
  // ------
  // Set Up
  // ------
  
  IQgarPrimitiveImpl iqPrim;

  // -------
  // Process
  // -------
  
  iqPrim.setColor(QGE_COLOR_BLUE);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqPrim.color() == QGE_COLOR_BLUE );
}


void
AbstractGenQgarPrimitiveTest::testSetThickness()
{
  // ------
  // Set Up
  // ------

  int thick = 10;
  IQgarPrimitiveImpl iqPrim;

  // -------
  // Process
  // -------
  
  iqPrim.setThickness(thick);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqPrim.thickness() == thick );
}


void
AbstractGenQgarPrimitiveTest::testSetOutline()
{
  // ------
  // Set Up
  // ------

  int thick = 10;
  IQgarPrimitiveImpl iqPrim;

  // -------
  // Process
  // -------
  
  iqPrim.setThickness(thick);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqPrim.thickness() == thick );
}


// -------------------------------------------------------------------
// O P E R A T O R S
// -------------------------------------------------------------------


void
AbstractGenQgarPrimitiveTest::testAssignment()
{
  // ------
  // Set Up
  // ------

  IQgarPrimitiveImpl iqPrim(2, QGE_COLOR_BLUE, QGE_OUTLINE_DOT);
  FQgarPrimitiveImpl fqPrim(2, QGE_COLOR_BLUE, QGE_OUTLINE_DOT);
  DQgarPrimitiveImpl dqPrim(2, QGE_COLOR_BLUE, QGE_OUTLINE_DOT);

  // -------
  // Process
  // -------

  IQgarPrimitiveImpl iqDupPrim;
  FQgarPrimitiveImpl fqDupPrim;
  DQgarPrimitiveImpl dqDupPrim;

  iqDupPrim = iqPrim;
  fqDupPrim = fqPrim;
  dqDupPrim = dqPrim;

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqPrim.color()     == iqDupPrim.color() );
  CPPUNIT_ASSERT( iqPrim.thickness() == iqDupPrim.thickness() );
  CPPUNIT_ASSERT( iqPrim.outline()   == iqDupPrim.outline() );

  CPPUNIT_ASSERT( fqPrim.color()     == fqDupPrim.color() );
  CPPUNIT_ASSERT( fqPrim.thickness() == fqDupPrim.thickness() );
  CPPUNIT_ASSERT( fqPrim.outline()   == fqDupPrim.outline() );

  CPPUNIT_ASSERT( dqPrim.color()     == dqDupPrim.color() );
  CPPUNIT_ASSERT( dqPrim.thickness() == dqDupPrim.thickness() );
  CPPUNIT_ASSERT( dqPrim.outline()   == dqDupPrim.outline() );

  // Ensure that function returns a valid reference on 'this'.
  CPPUNIT_ASSERT( &iqDupPrim == &(iqDupPrim = iqPrim) );
  CPPUNIT_ASSERT( &fqDupPrim == &(fqDupPrim = fqPrim) );
  CPPUNIT_ASSERT( &dqDupPrim == &(dqDupPrim = dqPrim) );
}


// -------------------------------------------------------------------
// SET SOURCE AND/OR TARGET WITHOUT UPDATE
// -------------------------------------------------------------------


void
AbstractGenQgarPrimitiveTest::testSetSource()
{
  // ------
  // Set Up
  // ------
  
  IPoint iPt(0, 3);
  FPoint fPt(0.489F, 3.984F);
  DPoint dPt(0.004, 3.298);

  IQgarPrimitiveImpl iqPrim;
  FQgarPrimitiveImpl fqPrim;
  DQgarPrimitiveImpl dqPrim;

  // -------
  // Process
  // -------

  iqPrim.setSource(iPt);
  fqPrim.setSource(fPt);
  dqPrim.setSource(dPt);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqPrim.source() == iPt );
  CPPUNIT_ASSERT( fqPrim.source() == fPt );
  CPPUNIT_ASSERT( dqPrim.source() == dPt );
}


void
AbstractGenQgarPrimitiveTest::testSetTarget()
{
  // ------
  // Set Up
  // ------
  
  IPoint iPt(0, 3);
  FPoint fPt(0.489F, 3.984F);
  DPoint dPt(0.004, 3.298);

  IQgarPrimitiveImpl iqPrim;
  FQgarPrimitiveImpl fqPrim;
  DQgarPrimitiveImpl dqPrim;

  // -------
  // Process
  // -------

  iqPrim.setTarget(iPt);
  fqPrim.setTarget(fPt);
  dqPrim.setTarget(dPt);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqPrim.target() == iPt );
  CPPUNIT_ASSERT( fqPrim.target() == fPt );
  CPPUNIT_ASSERT( dqPrim.target() == dPt );
}


void
AbstractGenQgarPrimitiveTest::testSetSourceTarget()
{
  // ------
  // Set Up
  // ------
  
  IPoint iPtSource(0, 3);
  IPoint iPtTarget(2, 5);
  FPoint fPtSource(0.45F, 3.024F);
  FPoint fPtTarget(2.982F, 5.85F);
  DPoint dPtSource(10.842, 3.984);
  DPoint dPtTarget(2.982, 5.984);

  IQgarPrimitiveImpl iqPrim;
  FQgarPrimitiveImpl fqPrim;
  DQgarPrimitiveImpl dqPrim;

  // -------
  // Process
  // -------

  iqPrim.setSourceTarget(iPtSource, iPtTarget);
  fqPrim.setSourceTarget(fPtSource, fPtTarget);
  dqPrim.setSourceTarget(dPtSource, dPtTarget);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqPrim.source() == iPtSource );
  CPPUNIT_ASSERT( fqPrim.source() == fPtSource );
  CPPUNIT_ASSERT( dqPrim.source() == dPtSource );

  CPPUNIT_ASSERT( iqPrim.target() == iPtTarget );
  CPPUNIT_ASSERT( fqPrim.target() == fPtTarget );
  CPPUNIT_ASSERT( dqPrim.target() == dPtTarget );
}


void
AbstractGenQgarPrimitiveTest::testSetXSource()
{
  // ------
  // Set Up
  // ------
  
  int    ix = 4;
  float  fx = 9.24F;
  double dx = 0.4;
    
  IQgarPrimitiveImpl iqPrim;
  FQgarPrimitiveImpl fqPrim;
  DQgarPrimitiveImpl dqPrim;

  // -------
  // Process
  // -------

  iqPrim.setXSource(ix);
  fqPrim.setXSource(fx);
  dqPrim.setXSource(dx);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( ix, iqPrim.xSource() );
  CPPUNIT_ASSERT_EQUAL( fx, fqPrim.xSource() );
  CPPUNIT_ASSERT_EQUAL( dx, dqPrim.xSource() );
}


void
AbstractGenQgarPrimitiveTest::testSetYSource()
{
  // ------
  // Set Up
  // ------
  
  int    iy = 4;
  float  fy = 9.24F;
  double dy = 0.4;
    
  IQgarPrimitiveImpl iqPrim;
  FQgarPrimitiveImpl fqPrim;
  DQgarPrimitiveImpl dqPrim;

  // -------
  // Process
  // -------

  iqPrim.setYSource(iy);
  fqPrim.setYSource(fy);
  dqPrim.setYSource(dy);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( iy, iqPrim.ySource() );
  CPPUNIT_ASSERT_EQUAL( fy, fqPrim.ySource() );
  CPPUNIT_ASSERT_EQUAL( dy, dqPrim.ySource() );
}


void
AbstractGenQgarPrimitiveTest::testSetXTarget()
{
  // ------
  // Set Up
  // ------
  
  int    ix = 4;
  float  fx = 9.24F;
  double dx = 0.4;
    
  IQgarPrimitiveImpl iqPrim;
  FQgarPrimitiveImpl fqPrim;
  DQgarPrimitiveImpl dqPrim;

  // -------
  // Process
  // -------

  iqPrim.setXTarget(ix);
  fqPrim.setXTarget(fx);
  dqPrim.setXTarget(dx);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( ix, iqPrim.xTarget() );
  CPPUNIT_ASSERT_EQUAL( fx, fqPrim.xTarget() );
  CPPUNIT_ASSERT_EQUAL( dx, dqPrim.xTarget() );
}


void
AbstractGenQgarPrimitiveTest::testSetYTarget()
{
  // ------
  // Set Up
  // ------
  
  int    iy = 4;
  float  fy = 9.24F;
  double dy = 0.4;
    
  IQgarPrimitiveImpl iqPrim;
  FQgarPrimitiveImpl fqPrim;
  DQgarPrimitiveImpl dqPrim;

  // -------
  // Process
  // -------

  iqPrim.setYTarget(iy);
  fqPrim.setYTarget(fy);
  dqPrim.setYTarget(dy);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( iy, iqPrim.yTarget() );
  CPPUNIT_ASSERT_EQUAL( fy, fqPrim.yTarget() );
  CPPUNIT_ASSERT_EQUAL( dy, dqPrim.yTarget() );
}


void
AbstractGenQgarPrimitiveTest::testSetXYSource()
{
  // ------
  // Set Up
  // ------
  
  int    ix = 4;
  int    iy = 2;
  float  fx = 9.24F;
  float  fy = 4.25F;
  double dx = 0.4;
  double dy = -98.27;
    
  IQgarPrimitiveImpl iqPrim;
  FQgarPrimitiveImpl fqPrim;
  DQgarPrimitiveImpl dqPrim;

  // -------
  // Process
  // -------

  iqPrim.setSource(ix, iy);
  fqPrim.setSource(fx, fy);
  dqPrim.setSource(dx, dy);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( ix, iqPrim.xSource() );
  CPPUNIT_ASSERT_EQUAL( fx, fqPrim.xSource() );
  CPPUNIT_ASSERT_EQUAL( dx, dqPrim.xSource() );

  CPPUNIT_ASSERT_EQUAL( iy, iqPrim.ySource() );
  CPPUNIT_ASSERT_EQUAL( fy, fqPrim.ySource() );
  CPPUNIT_ASSERT_EQUAL( dy, dqPrim.ySource() );
}


void
AbstractGenQgarPrimitiveTest::testSetXYTarget()
{
  // ------
  // Set Up
  // ------
  
  int    ix = 4;
  int    iy = 2;
  float  fx = 9.24F;
  float  fy = 4.25F;
  double dx = 0.4;
  double dy = -98.27;
    
  IQgarPrimitiveImpl iqPrim;
  FQgarPrimitiveImpl fqPrim;
  DQgarPrimitiveImpl dqPrim;

  // -------
  // Process
  // -------

  iqPrim.setTarget(ix, iy);
  fqPrim.setTarget(fx, fy);
  dqPrim.setTarget(dx, dy);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( ix, iqPrim.xTarget() );
  CPPUNIT_ASSERT_EQUAL( fx, fqPrim.xTarget() );
  CPPUNIT_ASSERT_EQUAL( dx, dqPrim.xTarget() );

  CPPUNIT_ASSERT_EQUAL( iy, iqPrim.yTarget() );
  CPPUNIT_ASSERT_EQUAL( fy, fqPrim.yTarget() );
  CPPUNIT_ASSERT_EQUAL( dy, dqPrim.yTarget() );
}


void
AbstractGenQgarPrimitiveTest::testSetXYSourceTarget()
{
  // ------
  // Set Up
  // ------

  int ixs = 2;
  int iys = 5;
  int ixt = 4;
  int iyt = 1;

  float fxs = 3.1f;
  float fys = 5.082f;
  float fxt = 1.4f;
  float fyt = 5.252f;

  double dxs = 2.24;
  double dys = 5.5902;
  double dxt = 5.2145;
  double dyt = 0.4111;

  IPoint iPt0(ixs,iys);
  IPoint iPt1(ixt,iyt);
  FPoint fPt0(fxs,fys);
  FPoint fPt1(fxt,fyt);
  DPoint dPt0(dxs,dys);
  DPoint dPt1(dxt,dyt);
  
  IQgarPrimitiveImpl iqPrim;
  FQgarPrimitiveImpl fqPrim;
  DQgarPrimitiveImpl dqPrim;

  // -------
  // Process
  // -------
  
  iqPrim.setSourceTarget(ixs, iys, ixt, iyt);
  fqPrim.setSourceTarget(fxs, fys, fxt, fyt);
  dqPrim.setSourceTarget(dxs, dys, dxt, dyt);

  // -----
  // Check
  // -----

  // Ensure that the source has correctly been assigned.
  CPPUNIT_ASSERT( iqPrim.source() == iPt0 );
  CPPUNIT_ASSERT( fqPrim.source() == fPt0 );
  CPPUNIT_ASSERT( dqPrim.source() == dPt0 );
  
  // Ensure that the target as correctly been assigned.
  CPPUNIT_ASSERT( iqPrim.target() == iPt1 );
  CPPUNIT_ASSERT( fqPrim.target() == fPt1 );
  CPPUNIT_ASSERT( dqPrim.target() == dPt1 );
}


// -------------------------------------------------------------------
// SET SOURCE AND/OR TARGET WITH UPDATE
// -------------------------------------------------------------------


void
AbstractGenQgarPrimitiveTest::testFixSource()
{
  // ------
  // Set Up
  // ------
  
  IPoint iPt(0, 3);
  FPoint fPt(0.489F, 3.984F);
  DPoint dPt(0.004, 3.298);

  IQgarPrimitiveImpl iqPrim;
  FQgarPrimitiveImpl fqPrim;
  DQgarPrimitiveImpl dqPrim;

  // -------
  // Process
  // -------

  iqPrim.fixSource(iPt);
  fqPrim.fixSource(fPt);
  dqPrim.fixSource(dPt);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqPrim.source() == iPt );
  CPPUNIT_ASSERT( fqPrim.source() == fPt );
  CPPUNIT_ASSERT( dqPrim.source() == dPt );
}


void
AbstractGenQgarPrimitiveTest::testFixTarget()
{
  // ------
  // Set Up
  // ------
  
  IPoint iPt(0, 3);
  FPoint fPt(0.489F, 3.984F);
  DPoint dPt(0.004, 3.298);

  IQgarPrimitiveImpl iqPrim;
  FQgarPrimitiveImpl fqPrim;
  DQgarPrimitiveImpl dqPrim;

  // -------
  // Process
  // -------

  iqPrim.fixTarget(iPt);
  fqPrim.fixTarget(fPt);
  dqPrim.fixTarget(dPt);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqPrim.target() == iPt );
  CPPUNIT_ASSERT( fqPrim.target() == fPt );
  CPPUNIT_ASSERT( dqPrim.target() == dPt );
}


void
AbstractGenQgarPrimitiveTest::testFixSourceTarget()
{
  // ------
  // Set Up
  // ------
  
  IPoint iPtSource(0, 3);
  IPoint iPtTarget(2, 5);
  FPoint fPtSource(0.45F, 3.024F);
  FPoint fPtTarget(2.982F, 5.85F);
  DPoint dPtSource(10.842, 3.984);
  DPoint dPtTarget(2.982, 5.984);

  IQgarPrimitiveImpl iqPrim;
  FQgarPrimitiveImpl fqPrim;
  DQgarPrimitiveImpl dqPrim;

  // -------
  // Process
  // -------

  iqPrim.fixSourceTarget(iPtSource, iPtTarget);
  fqPrim.fixSourceTarget(fPtSource, fPtTarget);
  dqPrim.fixSourceTarget(dPtSource, dPtTarget);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iqPrim.source() == iPtSource );
  CPPUNIT_ASSERT( fqPrim.source() == fPtSource );
  CPPUNIT_ASSERT( dqPrim.source() == dPtSource );

  CPPUNIT_ASSERT( iqPrim.target() == iPtTarget );
  CPPUNIT_ASSERT( fqPrim.target() == fPtTarget );
  CPPUNIT_ASSERT( dqPrim.target() == dPtTarget );
}


void
AbstractGenQgarPrimitiveTest::testFixXSource()
{
  // ------
  // Set Up
  // ------
  
  int    ix = 4;
  float  fx = 9.24F;
  double dx = 0.4;
    
  IQgarPrimitiveImpl iqPrim;
  FQgarPrimitiveImpl fqPrim;
  DQgarPrimitiveImpl dqPrim;

  // -------
  // Process
  // -------

  iqPrim.fixXSource(ix);
  fqPrim.fixXSource(fx);
  dqPrim.fixXSource(dx);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( ix, iqPrim.xSource() );
  CPPUNIT_ASSERT_EQUAL( fx, fqPrim.xSource() );
  CPPUNIT_ASSERT_EQUAL( dx, dqPrim.xSource() );
}


void
AbstractGenQgarPrimitiveTest::testFixYSource()
{
  // ------
  // Set Up
  // ------
  
  int    iy = 4;
  float  fy = 9.24F;
  double dy = 0.4;
    
  IQgarPrimitiveImpl iqPrim;
  FQgarPrimitiveImpl fqPrim;
  DQgarPrimitiveImpl dqPrim;

  // -------
  // Process
  // -------

  iqPrim.fixYSource(iy);
  fqPrim.fixYSource(fy);
  dqPrim.fixYSource(dy);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( iy, iqPrim.ySource() );
  CPPUNIT_ASSERT_EQUAL( fy, fqPrim.ySource() );
  CPPUNIT_ASSERT_EQUAL( dy, dqPrim.ySource() );
}


void
AbstractGenQgarPrimitiveTest::testFixXTarget()
{
  // ------
  // Set Up
  // ------
  
  int    ix = 4;
  float  fx = 9.24F;
  double dx = 0.4;
    
  IQgarPrimitiveImpl iqPrim;
  FQgarPrimitiveImpl fqPrim;
  DQgarPrimitiveImpl dqPrim;

  // -------
  // Process
  // -------

  iqPrim.fixXTarget(ix);
  fqPrim.fixXTarget(fx);
  dqPrim.fixXTarget(dx);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( ix, iqPrim.xTarget() );
  CPPUNIT_ASSERT_EQUAL( fx, fqPrim.xTarget() );
  CPPUNIT_ASSERT_EQUAL( dx, dqPrim.xTarget() );
}


void
AbstractGenQgarPrimitiveTest::testFixYTarget()
{
  // ------
  // Set Up
  // ------
  
  int    iy = 4;
  float  fy = 9.24F;
  double dy = 0.4;
    
  IQgarPrimitiveImpl iqPrim;
  FQgarPrimitiveImpl fqPrim;
  DQgarPrimitiveImpl dqPrim;

  // -------
  // Process
  // -------

  iqPrim.fixYTarget(iy);
  fqPrim.fixYTarget(fy);
  dqPrim.fixYTarget(dy);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( iy, iqPrim.yTarget() );
  CPPUNIT_ASSERT_EQUAL( fy, fqPrim.yTarget() );
  CPPUNIT_ASSERT_EQUAL( dy, dqPrim.yTarget() );
}


void
AbstractGenQgarPrimitiveTest::testFixXYSource()
{
  // ------
  // Set Up
  // ------
  
  int    ix = 4;
  int    iy = 2;
  float  fx = 9.24F;
  float  fy = 4.25F;
  double dx = 0.4;
  double dy = -98.27;
    
  IQgarPrimitiveImpl iqPrim;
  FQgarPrimitiveImpl fqPrim;
  DQgarPrimitiveImpl dqPrim;

  // -------
  // Process
  // -------

  iqPrim.fixSource(ix, iy);
  fqPrim.fixSource(fx, fy);
  dqPrim.fixSource(dx, dy);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( ix, iqPrim.xSource() );
  CPPUNIT_ASSERT_EQUAL( fx, fqPrim.xSource() );
  CPPUNIT_ASSERT_EQUAL( dx, dqPrim.xSource() );

  CPPUNIT_ASSERT_EQUAL( iy, iqPrim.ySource() );
  CPPUNIT_ASSERT_EQUAL( fy, fqPrim.ySource() );
  CPPUNIT_ASSERT_EQUAL( dy, dqPrim.ySource() );
}


void
AbstractGenQgarPrimitiveTest::testFixXYTarget()
{
  // ------
  // Set Up
  // ------
  
  int    ix = 4;
  int    iy = 2;
  float  fx = 9.24F;
  float  fy = 4.25F;
  double dx = 0.4;
  double dy = -98.27;
    
  IQgarPrimitiveImpl iqPrim;
  FQgarPrimitiveImpl fqPrim;
  DQgarPrimitiveImpl dqPrim;

  // -------
  // Process
  // -------

  iqPrim.fixTarget(ix, iy);
  fqPrim.fixTarget(fx, fy);
  dqPrim.fixTarget(dx, dy);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( ix, iqPrim.xTarget() );
  CPPUNIT_ASSERT_EQUAL( fx, fqPrim.xTarget() );
  CPPUNIT_ASSERT_EQUAL( dx, dqPrim.xTarget() );

  CPPUNIT_ASSERT_EQUAL( iy, iqPrim.yTarget() );
  CPPUNIT_ASSERT_EQUAL( fy, fqPrim.yTarget() );
  CPPUNIT_ASSERT_EQUAL( dy, dqPrim.yTarget() );
}


void
AbstractGenQgarPrimitiveTest::testFixXYSourceTarget()
{
  // ------
  // Set Up
  // ------

  int ixs = 2;
  int iys = 5;
  int ixt = 4;
  int iyt = 1;

  float fxs = 3.1f;
  float fys = 5.082f;
  float fxt = 1.4f;
  float fyt = 5.252f;

  double dxs = 2.24;
  double dys = 5.5902;
  double dxt = 5.2145;
  double dyt = 0.4111;

  IPoint iPt0(ixs,iys);
  IPoint iPt1(ixt,iyt);
  FPoint fPt0(fxs,fys);
  FPoint fPt1(fxt,fyt);
  DPoint dPt0(dxs,dys);
  DPoint dPt1(dxt,dyt);
  
  IQgarPrimitiveImpl iqPrim;
  FQgarPrimitiveImpl fqPrim;
  DQgarPrimitiveImpl dqPrim;

  // -------
  // Process
  // -------
  
  iqPrim.fixSourceTarget(ixs, iys, ixt, iyt);
  fqPrim.fixSourceTarget(fxs, fys, fxt, fyt);
  dqPrim.fixSourceTarget(dxs, dys, dxt, dyt);

  // -----
  // Check
  // -----

  // Ensure that the source has correctly been assigned.
  CPPUNIT_ASSERT( iqPrim.source() == iPt0 );
  CPPUNIT_ASSERT( fqPrim.source() == fPt0 );
  CPPUNIT_ASSERT( dqPrim.source() == dPt0 );
  
  // Ensure that the target as correctly been assigned.
  CPPUNIT_ASSERT( iqPrim.target() == iPt1 );
  CPPUNIT_ASSERT( fqPrim.target() == fPt1 );
  CPPUNIT_ASSERT( dqPrim.target() == dPt1 );
}

// ----------------------------------------------------------------------
