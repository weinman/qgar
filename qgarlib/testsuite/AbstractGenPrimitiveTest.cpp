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
 * @file  AbstractGenPrimitiveTest.cpp
 * @brief Implementation of class AbstractGenPrimitiveTest
 *
 *        See file AbstractGenPrimitiveTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 25, 2003  11:53
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: AbstractGenPrimitiveTest.cpp,v 1.6 2005/07/13 16:29:34 masini Exp $ */



// QGAR
#include <qgarlib/primitives.h>
// QGAR TESTS
#include "AbstractGenPrimitiveTest.h"



using namespace qgar;


namespace
{

// ------------------------------------------------------------------
// U N N A M E D   N A M E S P A C E
// ------------------------------------------------------------------

/// Error message for AbstractGenPrimitive::updateSource
const char* messSource =
  "QGAR TESTS >>> Wrong use of AbstractGenPrimitive::updateSource()";

/// Error message for AbstractGenPrimitive::updateTarget
const char* messTarget =
  "QGAR TESTS >>> Wrong use of AbstractGenPrimitive::updateTarget()";

/// Error message for AbstractGenPrimitive::updateSourceTarget
const char* messSourceTarget =
  "QGAR TESTS >>> Wrong use of AbstractGenPrimitive::updateSourceTarget()";


/**
 * @brief Class implementing AbstractGenPrimitive<T> defined for
 * testing purpose.
 *
 * <p>
 * This class is used to test the AbstractGenPrimitive<T> class.
 * Since the latter class is abstract, it cannot directly be tested.
 * </p>
 * <p>
 * This class provide the minimal implementation of the abstraction.
 * It thus provides a constructor for each constructors of the base
 * class and implements all base class virtual function member.
 * </p>
 */
template <class T> 
class GenPrimitiveImpl

  : public AbstractGenPrimitive<T>

{
public:

  /**
   * @brief Default Constructor.
   */
  GenPrimitiveImpl<T>()
    : AbstractGenPrimitive<T>(),
      _updateSourceCallCnt(0),
      _updateTargetCallCnt(0),
      _updateSourceTargetCallCnt(0)
  {
    /* EMPTY */
  }

  /**
   * @brief Copy constructor
   */
  GenPrimitiveImpl<T>(const GenPrimitiveImpl<T>& other)
    : AbstractGenPrimitive<T>(other),
      _updateSourceCallCnt(0),
      _updateTargetCallCnt(0),
      _updateSourceTargetCallCnt(0)
  {
    /* EMPTY */
  }

  /**
   * @brief Create a primitive from two points.
   */
  GenPrimitiveImpl<T>(const GenPoint<T>& source, 
		      const GenPoint<T>& target)
    : AbstractGenPrimitive<T>(source, target),
      _updateSourceCallCnt(0),
      _updateTargetCallCnt(0),
      _updateSourceTargetCallCnt(0)
  {
    /* EMPTY */
  }

  /**
   * @brief Creates a primitive from four coordinates.
   */
  GenPrimitiveImpl<T>(T x0, T y0, T x1, T y1)
    : AbstractGenPrimitive<T>(x0, y0, x1, y1),
      _updateSourceCallCnt(0),
      _updateTargetCallCnt(0),
      _updateSourceTargetCallCnt(0)
  {
    /* EMPTY */
  }

  /**
   * @brief Empty implementation.
   */
  virtual GenPrimitiveImpl<T>* clone() const
  {
    return new GenPrimitiveImpl<T>(*this);
  }

  /**
   * @brief Empty implementation.
   */
  virtual void translate(T aTransX, T aTransY)
  {
    // VOID
  }

  /**
   * @brief Empty implementation. A counter tracing the number of
   * calls made to that function is incremented.
   */
  virtual void updateSource()
  {
    ++_updateSourceCallCnt;
  }

  /**
   * @brief Empty implementation. A counter tracing the number of
   * calls made to that function is incremented.
   */
  virtual void updateTarget()
  {
    ++_updateTargetCallCnt;
  }

  /**
   * @brief Empty implementation. A counter tracing the number of
   * calls made to that function is incremented.
   */
  virtual void updateSourceTarget()
  {
    ++_updateSourceTargetCallCnt;
  }

  /// Counts the number of calls made to updateSouce()
  int _updateSourceCallCnt;

  /// Counts the number of calls made to updateTarget()
  int _updateTargetCallCnt;

  /// Counts the number of calls made to updateSouceTarget()
  int _updateSourceTargetCallCnt;
};


// Handy typedefs.
typedef GenPrimitiveImpl<int>    IPrimitiveImpl;
typedef GenPrimitiveImpl<float>  FPrimitiveImpl;
typedef GenPrimitiveImpl<double> DPrimitiveImpl;

} // unnamed namespace



// ------------------------------------------------------------------
// T E S T F I X T U R E   I M P L
// ------------------------------------------------------------------

void
AbstractGenPrimitiveTest::setUp()
{
  /* EMPTY */
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::tearDown()
{
  /* EMPTY */
}


// -------------------------------------------------------------------
// T E S T   F U N C T I O N S
// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testDefaultConstructor()
{
  // ------
  // Set Up
  // ------
  
  IPrimitiveImpl iPrim;
  FPrimitiveImpl fPrim;
  DPrimitiveImpl dPrim;


  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iPrim.source() == IPoint(0,0) );
  CPPUNIT_ASSERT( iPrim.target() == IPoint(0,0) );

  CPPUNIT_ASSERT( fPrim.source() == FPoint(0,0) );
  CPPUNIT_ASSERT( fPrim.target() == FPoint(0,0) );

  CPPUNIT_ASSERT( dPrim.source() == DPoint(0,0) );
  CPPUNIT_ASSERT( dPrim.target() == DPoint(0,0) );
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testCopyConstructor()
{
  // ------
  // Set Up
  // ------
  
  IPoint iPt0(1, 4);
  IPoint iPt1(-2, 5);
  IPrimitiveImpl iPrim(iPt0, iPt1);

  FPoint fPt0(1.984F, 4.27F);
  FPoint fPt1(-2.94F, 5.169F);
  FPrimitiveImpl fPrim(fPt0, fPt1);

  DPoint dPt0(0.04, 14.94);
  DPoint dPt1(-3.94, 1.48);
  DPrimitiveImpl dPrim(dPt0, dPt1);


  // -------
  // Process
  // -------

  IPrimitiveImpl iDupPrim(iPrim);
  FPrimitiveImpl fDupPrim(fPrim);
  DPrimitiveImpl dDupPrim(dPrim);


  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iPrim.source() == iPt0 );
  CPPUNIT_ASSERT( iPrim.target() == iPt1 );

  CPPUNIT_ASSERT( fPrim.source() == fPt0 );
  CPPUNIT_ASSERT( fPrim.target() == fPt1 );

  CPPUNIT_ASSERT( dPrim.source() == dPt0 );
  CPPUNIT_ASSERT( dPrim.target() == dPt1 );
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testAssignment()
{
  // ------
  // Set Up
  // ------
  
  IPoint iPt0(1, 4);
  IPoint iPt1(-2, 5);
  IPrimitiveImpl iPrim(iPt0, iPt1);

  FPoint fPt0(1.984F, 4.27F);
  FPoint fPt1(-2.94F, 5.169F);
  FPrimitiveImpl fPrim(fPt0, fPt1);

  DPoint dPt0(0.04, 14.94);
  DPoint dPt1(-3.94, 1.48);
  DPrimitiveImpl dPrim(dPt0, dPt1);


  // -------
  // Process
  // -------
  
  IPrimitiveImpl iDupPrim;
  FPrimitiveImpl fDupPrim;
  DPrimitiveImpl dDupPrim;

  iDupPrim = iPrim;
  fDupPrim = fPrim;
  dDupPrim = dPrim;


  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iPrim.source() == iPt0 );
  CPPUNIT_ASSERT( iPrim.target() == iPt1 );

  CPPUNIT_ASSERT( fPrim.source() == fPt0 );
  CPPUNIT_ASSERT( fPrim.target() == fPt1 );

  CPPUNIT_ASSERT( dPrim.source() == dPt0 );
  CPPUNIT_ASSERT( dPrim.target() == dPt1 );

  // Ensure that function return a valid reference on 'this'
  CPPUNIT_ASSERT( &iDupPrim == &(iDupPrim = iPrim) );
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testBuildFromTwoPoints()
{
  // ------
  // Set Up
  // ------
  
  IPoint iPt0(1, 4);
  IPoint iPt1(-2, 5);
  IPrimitiveImpl iPrim(iPt0, iPt1);

  FPoint fPt0(1.984F, 4.27F);
  FPoint fPt1(-2.94F, 5.169F);
  FPrimitiveImpl fPrim(fPt0, fPt1);

  DPoint dPt0(0.04, 14.94);
  DPoint dPt1(-3.94, 1.48);
  DPrimitiveImpl dPrim(dPt0, dPt1);


  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iPrim.source() == iPt0 );
  CPPUNIT_ASSERT( iPrim.target() == iPt1 );

  CPPUNIT_ASSERT( fPrim.source() == fPt0 );
  CPPUNIT_ASSERT( fPrim.target() == fPt1 );

  CPPUNIT_ASSERT( dPrim.source() == dPt0 );
  CPPUNIT_ASSERT( dPrim.target() == dPt1 );
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testBuildFrom4Coords()
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

  // -------
  // Process
  // -------
  
  IPrimitiveImpl iPrim(ix0, iy0, ix1, iy1);
  FPrimitiveImpl fPrim(fx0, fy0, fx1, fy1);
  DPrimitiveImpl dPrim(dx0, dy0, dx1, dy1);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT( iPrim.xSource() == ix0 );
  CPPUNIT_ASSERT( iPrim.ySource() == iy0 );
  CPPUNIT_ASSERT( iPrim.xTarget() == ix1 );
  CPPUNIT_ASSERT( iPrim.yTarget() == iy1 );

  CPPUNIT_ASSERT( fPrim.xSource() == fx0 );
  CPPUNIT_ASSERT( fPrim.ySource() == fy0 );
  CPPUNIT_ASSERT( fPrim.xTarget() == fx1 );
  CPPUNIT_ASSERT( fPrim.yTarget() == fy1 );

  CPPUNIT_ASSERT( dPrim.xSource() == dx0 );
  CPPUNIT_ASSERT( dPrim.ySource() == dy0 );
  CPPUNIT_ASSERT( dPrim.xTarget() == dx1 );
  CPPUNIT_ASSERT( dPrim.yTarget() == dy1 );
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testDx()
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

  IPrimitiveImpl iPrim(ix0, iy0, ix1, iy1);
  FPrimitiveImpl fPrim(fx0, fy0, fx1, fy1);
  DPrimitiveImpl dPrim(dx0, dy0, dx1, dy1);

  // -----
  // Check
  // -----
  
  CPPUNIT_ASSERT_EQUAL( (ix1 - ix0), iPrim.dx() );
  CPPUNIT_ASSERT_EQUAL( (fx1 - fx0), fPrim.dx() );
  CPPUNIT_ASSERT_EQUAL( (dx1 - dx0), dPrim.dx() );
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testDy()
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

  IPrimitiveImpl iPrim(ix0, iy0, ix1, iy1);
  FPrimitiveImpl fPrim(fx0, fy0, fx1, fy1);
  DPrimitiveImpl dPrim(dx0, dy0, dx1, dy1);

  // -----
  // Check
  // -----
  
  CPPUNIT_ASSERT_EQUAL( (iy1 - iy0), iPrim.dy() );
  CPPUNIT_ASSERT_EQUAL( (fy1 - fy0), fPrim.dy() );
  CPPUNIT_ASSERT_EQUAL( (dy1 - dy0), dPrim.dy() );
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testSetSource()
{
  // ------
  // Set Up
  // ------

  IPoint iPt(2, 5);
  FPoint fPt(3.1F, 5.082F);
  DPoint dPt(2.24, 5.5902);  
  
  IPrimitiveImpl iPrim;
  FPrimitiveImpl fPrim;
  DPrimitiveImpl dPrim;

  // -------
  // Process
  // -------
  
  iPrim.setSource(iPt);
  fPrim.setSource(fPt);
  dPrim.setSource(dPt);

  // -----
  // Check
  // -----

  // Ensure that the source has correctly been assigned.
  CPPUNIT_ASSERT( iPrim.source() == iPt );
  CPPUNIT_ASSERT( fPrim.source() == fPt );
  CPPUNIT_ASSERT( dPrim.source() == dPt );

  // Ensure that updateSource() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSource, iPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, fPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, dPrim._updateSourceCallCnt == 0);

  // Ensure that updateTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messTarget, iPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, fPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, dPrim._updateTargetCallCnt == 0);

  // Ensure that updateSourceTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, iPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, fPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, dPrim._updateSourceTargetCallCnt == 0);
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testSetTarget()
{
  // ------
  // Set Up
  // ------

  IPoint iPt(2, 5);
  FPoint fPt(3.1F, 5.082F);
  DPoint dPt(2.24, 5.5902);  
  
  IPrimitiveImpl iPrim;
  FPrimitiveImpl fPrim;
  DPrimitiveImpl dPrim;

  // -------
  // Process
  // -------
  
  iPrim.setTarget(iPt);
  fPrim.setTarget(fPt);
  dPrim.setTarget(dPt);

  // -----
  // Check
  // -----

  // Ensure that the target has correctly been assigned.
  CPPUNIT_ASSERT( iPrim.target() == iPt );
  CPPUNIT_ASSERT( fPrim.target() == fPt );
  CPPUNIT_ASSERT( dPrim.target() == dPt );

  // Ensure that updateSource() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSource, iPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, fPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, dPrim._updateSourceCallCnt == 0);

  // Ensure that updateTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messTarget, iPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, fPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, dPrim._updateTargetCallCnt == 0);

  // Ensure that updateSourceTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, iPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, fPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, dPrim._updateSourceTargetCallCnt == 0);
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testSetSourceTarget()
{
  // ------
  // Set Up
  // ------

  IPoint iPt0(2, 5);
  IPoint iPt1(4, 1);
  FPoint fPt0(3.1F, 5.082F);
  FPoint fPt1(1.4F, 5.252F);
  DPoint dPt0(2.24, 5.5902); 
  DPoint dPt1(5.2145, 0.4111);
  
  IPrimitiveImpl iPrim;
  FPrimitiveImpl fPrim;
  DPrimitiveImpl dPrim;

  // -------
  // Process
  // -------
  
  iPrim.setSourceTarget(iPt0, iPt1);
  fPrim.setSourceTarget(fPt0, fPt1);
  dPrim.setSourceTarget(dPt0, dPt1);

  // -----
  // Check
  // -----

  // Ensure that the source has correctly been assigned.
  CPPUNIT_ASSERT( iPrim.source() == iPt0 );
  CPPUNIT_ASSERT( fPrim.source() == fPt0 );
  CPPUNIT_ASSERT( dPrim.source() == dPt0 );
  
  // Ensure that the target as correctly been assigned.
  CPPUNIT_ASSERT( iPrim.target() == iPt1 );
  CPPUNIT_ASSERT( fPrim.target() == fPt1 );
  CPPUNIT_ASSERT( dPrim.target() == dPt1 );

  // Ensure that updateSource() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSource, iPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, fPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, dPrim._updateSourceCallCnt == 0);

  // Ensure that updateTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messTarget, iPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, fPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, dPrim._updateTargetCallCnt == 0);

  // Ensure that updateSourceTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, iPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, fPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, dPrim._updateSourceTargetCallCnt == 0);
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testSetXSource()
{
  // ------
  // Set Up
  // ------
  
  int    ix = 2;
  float  fx = 3.24F;
  double dx = 1.4;
    
  IPrimitiveImpl iPrim;
  FPrimitiveImpl fPrim;
  DPrimitiveImpl dPrim;

  // -------
  // Process
  // -------

  iPrim.setXSource(ix);
  fPrim.setXSource(fx);
  dPrim.setXSource(dx);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( ix, iPrim.xSource() );
  CPPUNIT_ASSERT_EQUAL( fx, fPrim.xSource() );
  CPPUNIT_ASSERT_EQUAL( dx, dPrim.xSource() );

  // Ensure that updateSource() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSource, iPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, fPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, dPrim._updateSourceCallCnt == 0);

  // Ensure that updateTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messTarget, iPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, fPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, dPrim._updateTargetCallCnt == 0);

  // Ensure that updateSourceTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, iPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, fPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, dPrim._updateSourceTargetCallCnt == 0);
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testSetXTarget()
{
  // ------
  // Set Up
  // ------
  
  int    ix = 11;
  float  fx = 0.24F;
  double dx = 6.532;
    
  IPrimitiveImpl iPrim;
  FPrimitiveImpl fPrim;
  DPrimitiveImpl dPrim;

  // -------
  // Process
  // -------

  iPrim.setXTarget(ix);
  fPrim.setXTarget(fx);
  dPrim.setXTarget(dx);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( ix, iPrim.xTarget() );
  CPPUNIT_ASSERT_EQUAL( fx, fPrim.xTarget() );
  CPPUNIT_ASSERT_EQUAL( dx, dPrim.xTarget() );

  // Ensure that updateSource() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSource, iPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, fPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, dPrim._updateSourceCallCnt == 0);

  // Ensure that updateTarget() is correctly called.
  CPPUNIT_ASSERT_MESSAGE(messTarget, iPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, fPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, dPrim._updateTargetCallCnt == 0);

  // Ensure that updateSourceTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, iPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, fPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, dPrim._updateSourceTargetCallCnt == 0);
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testSetYSource()
{
  // ------
  // Set Up
  // ------
  
  int    iy = 4;
  float  fy = 9.24F;
  double dy = 0.4;
    
  IPrimitiveImpl iPrim;
  FPrimitiveImpl fPrim;
  DPrimitiveImpl dPrim;

  // -------
  // Process
  // -------

  iPrim.setYSource(iy);
  fPrim.setYSource(fy);
  dPrim.setYSource(dy);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( iy, iPrim.ySource() );
  CPPUNIT_ASSERT_EQUAL( fy, fPrim.ySource() );
  CPPUNIT_ASSERT_EQUAL( dy, dPrim.ySource() );

  // Ensure that updateSource() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSource, iPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, fPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, dPrim._updateSourceCallCnt == 0);

  // Ensure that updateTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messTarget, iPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, fPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, dPrim._updateTargetCallCnt == 0);

  // Ensure that updateSourceTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, iPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, fPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, dPrim._updateSourceTargetCallCnt == 0);
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testSetYTarget()
{
  // ------
  // Set Up
  // ------
  
  int    iy = 4;
  float  fy = 9.24F;
  double dy = 0.4;
    
  IPrimitiveImpl iPrim;
  FPrimitiveImpl fPrim;
  DPrimitiveImpl dPrim;

  // -------
  // Process
  // -------

  iPrim.setYTarget(iy);
  fPrim.setYTarget(fy);
  dPrim.setYTarget(dy);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( iy, iPrim.yTarget() );
  CPPUNIT_ASSERT_EQUAL( fy, fPrim.yTarget() );
  CPPUNIT_ASSERT_EQUAL( dy, dPrim.yTarget() );

  // Ensure that updateSource() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSource, iPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, fPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, dPrim._updateSourceCallCnt == 0);

  // Ensure that updateTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messTarget, iPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, fPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, dPrim._updateTargetCallCnt == 0);

  // Ensure that updateSourceTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, iPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, fPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, dPrim._updateSourceTargetCallCnt == 0);
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testSetXYSource()
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
    
  IPrimitiveImpl iPrim;
  FPrimitiveImpl fPrim;
  DPrimitiveImpl dPrim;

  // -------
  // Process
  // -------

  iPrim.setSource(ix, iy);
  fPrim.setSource(fx, fy);
  dPrim.setSource(dx, dy);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( ix, iPrim.xSource() );
  CPPUNIT_ASSERT_EQUAL( fx, fPrim.xSource() );
  CPPUNIT_ASSERT_EQUAL( dx, dPrim.xSource() );

  CPPUNIT_ASSERT_EQUAL( iy, iPrim.ySource() );
  CPPUNIT_ASSERT_EQUAL( fy, fPrim.ySource() );
  CPPUNIT_ASSERT_EQUAL( dy, dPrim.ySource() );

  // Ensure that updateSource() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSource, iPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, fPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, dPrim._updateSourceCallCnt == 0);

  // Ensure that updateTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messTarget, iPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, fPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, dPrim._updateTargetCallCnt == 0);

  // Ensure that updateSourceTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, iPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, fPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, dPrim._updateSourceTargetCallCnt == 0);
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testSetXYTarget()
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
    
  IPrimitiveImpl iPrim;
  FPrimitiveImpl fPrim;
  DPrimitiveImpl dPrim;

  // -------
  // Process
  // -------

  iPrim.setTarget(ix, iy);
  fPrim.setTarget(fx, fy);
  dPrim.setTarget(dx, dy);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( ix, iPrim.xTarget() );
  CPPUNIT_ASSERT_EQUAL( fx, fPrim.xTarget() );
  CPPUNIT_ASSERT_EQUAL( dx, dPrim.xTarget() );

  CPPUNIT_ASSERT_EQUAL( iy, iPrim.yTarget() );
  CPPUNIT_ASSERT_EQUAL( fy, fPrim.yTarget() );
  CPPUNIT_ASSERT_EQUAL( dy, dPrim.yTarget() );

  // Ensure that updateSource() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSource, iPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, fPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, dPrim._updateSourceCallCnt == 0);

  // Ensure that updateTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messTarget, iPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, fPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, dPrim._updateTargetCallCnt == 0);

  // Ensure that updateSourceTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, iPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, fPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, dPrim._updateSourceTargetCallCnt == 0);
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testSetXYSourceTarget()
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
  
  IPrimitiveImpl iPrim;
  FPrimitiveImpl fPrim;
  DPrimitiveImpl dPrim;

  // -------
  // Process
  // -------
  
  iPrim.setSourceTarget(ixs, iys, ixt, iyt);
  fPrim.setSourceTarget(fxs, fys, fxt, fyt);
  dPrim.setSourceTarget(dxs, dys, dxt, dyt);

  // -----
  // Check
  // -----

  // Ensure that the source has correctly been assigned.
  CPPUNIT_ASSERT( iPrim.source() == iPt0 );
  CPPUNIT_ASSERT( fPrim.source() == fPt0 );
  CPPUNIT_ASSERT( dPrim.source() == dPt0 );
  
  // Ensure that the target as correctly been assigned.
  CPPUNIT_ASSERT( iPrim.target() == iPt1 );
  CPPUNIT_ASSERT( fPrim.target() == fPt1 );
  CPPUNIT_ASSERT( dPrim.target() == dPt1 );

  // Ensure that updateSource() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSource, iPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, fPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, dPrim._updateSourceCallCnt == 0);

  // Ensure that updateTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messTarget, iPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, fPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, dPrim._updateTargetCallCnt == 0);

  // Ensure that updateSourceTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, iPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, fPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, dPrim._updateSourceTargetCallCnt == 0);
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testFixSource()
{
  // ------
  // Set Up
  // ------

  IPoint iPt(2, 5);
  FPoint fPt(3.1F, 5.082F);
  DPoint dPt(2.24, 5.5902);  
  
  IPrimitiveImpl iPrim;
  FPrimitiveImpl fPrim;
  DPrimitiveImpl dPrim;

  // -------
  // Process
  // -------
  
  iPrim.fixSource(iPt);
  fPrim.fixSource(fPt);
  dPrim.fixSource(dPt);

  // -----
  // Check
  // -----

  // Ensure that the source has correctly been assigned.
  CPPUNIT_ASSERT( iPrim.source() == iPt );
  CPPUNIT_ASSERT( fPrim.source() == fPt );
  CPPUNIT_ASSERT( dPrim.source() == dPt );

  // Ensure that updateSource() is correctly called.
  CPPUNIT_ASSERT_MESSAGE(messSource, iPrim._updateSourceCallCnt == 1);
  CPPUNIT_ASSERT_MESSAGE(messSource, fPrim._updateSourceCallCnt == 1);
  CPPUNIT_ASSERT_MESSAGE(messSource, dPrim._updateSourceCallCnt == 1);

  // Ensure that updateTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messTarget, iPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, fPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, dPrim._updateTargetCallCnt == 0);

  // Ensure that updateSourceTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, iPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, fPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, dPrim._updateSourceTargetCallCnt == 0);
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testFixTarget()
{
  // ------
  // Set Up
  // ------

  IPoint iPt(2, 5);
  FPoint fPt(3.1F, 5.082F);
  DPoint dPt(2.24, 5.5902);  
  
  IPrimitiveImpl iPrim;
  FPrimitiveImpl fPrim;
  DPrimitiveImpl dPrim;

  // -------
  // Process
  // -------
  
  iPrim.fixTarget(iPt);
  fPrim.fixTarget(fPt);
  dPrim.fixTarget(dPt);

  // -----
  // Check
  // -----

  // Ensure that the target has correctly been assigned.
  CPPUNIT_ASSERT( iPrim.target() == iPt );
  CPPUNIT_ASSERT( fPrim.target() == fPt );
  CPPUNIT_ASSERT( dPrim.target() == dPt );

  // Ensure that updateSource() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSource, iPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, fPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, dPrim._updateSourceCallCnt == 0);

  // Ensure that updateTarget() is correctly called.
  CPPUNIT_ASSERT_MESSAGE(messTarget, iPrim._updateTargetCallCnt == 1);
  CPPUNIT_ASSERT_MESSAGE(messTarget, fPrim._updateTargetCallCnt == 1);
  CPPUNIT_ASSERT_MESSAGE(messTarget, dPrim._updateTargetCallCnt == 1);

  // Ensure that updateSourceTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, iPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, fPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, dPrim._updateSourceTargetCallCnt == 0);
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testFixSourceTarget()
{
  // ------
  // Set Up
  // ------

  IPoint iPt0(2, 5);
  IPoint iPt1(4, 1);
  FPoint fPt0(3.1F, 5.082F);
  FPoint fPt1(1.4F, 5.252F);
  DPoint dPt0(2.24, 5.5902); 
  DPoint dPt1(5.2145, 0.4111);
  
  IPrimitiveImpl iPrim;
  FPrimitiveImpl fPrim;
  DPrimitiveImpl dPrim;

  // -------
  // Process
  // -------
  
  iPrim.fixSourceTarget(iPt0, iPt1);
  fPrim.fixSourceTarget(fPt0, fPt1);
  dPrim.fixSourceTarget(dPt0, dPt1);

  // -----
  // Check
  // -----

  // Ensure that the source has correctly been assigned.
  CPPUNIT_ASSERT( iPrim.source() == iPt0 );
  CPPUNIT_ASSERT( fPrim.source() == fPt0 );
  CPPUNIT_ASSERT( dPrim.source() == dPt0 );
  
  // Ensure that the target as correctly been assigned.
  CPPUNIT_ASSERT( iPrim.target() == iPt1 );
  CPPUNIT_ASSERT( fPrim.target() == fPt1 );
  CPPUNIT_ASSERT( dPrim.target() == dPt1 );

  // Ensure that updateSource() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSource, iPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, fPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, dPrim._updateSourceCallCnt == 0);

  // Ensure that updateTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messTarget, iPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, fPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, dPrim._updateTargetCallCnt == 0);

  // Ensure that updateSourceTarget() is correctly called.
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, iPrim._updateSourceTargetCallCnt == 1);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, fPrim._updateSourceTargetCallCnt == 1);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, dPrim._updateSourceTargetCallCnt == 1);
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testFixXSource()
{
  // ------
  // Set Up
  // ------
  
  int    ix = 2;
  float  fx = 3.24F;
  double dx = 1.4;
    
  IPrimitiveImpl iPrim;
  FPrimitiveImpl fPrim;
  DPrimitiveImpl dPrim;

  // -------
  // Process
  // -------

  iPrim.fixXSource(ix);
  fPrim.fixXSource(fx);
  dPrim.fixXSource(dx);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( ix, iPrim.xSource() );
  CPPUNIT_ASSERT_EQUAL( fx, fPrim.xSource() );
  CPPUNIT_ASSERT_EQUAL( dx, dPrim.xSource() );

  // Ensure that updateSource() is correctly called.
  CPPUNIT_ASSERT_MESSAGE(messSource, iPrim._updateSourceCallCnt == 1);
  CPPUNIT_ASSERT_MESSAGE(messSource, fPrim._updateSourceCallCnt == 1);
  CPPUNIT_ASSERT_MESSAGE(messSource, dPrim._updateSourceCallCnt == 1);

  // Ensure that updateTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messTarget, iPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, fPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, dPrim._updateTargetCallCnt == 0);

  // Ensure that updateSourceTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, iPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, fPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, dPrim._updateSourceTargetCallCnt == 0);
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testFixXTarget()
{
  // ------
  // Set Up
  // ------
  
  int    ix = 11;
  float  fx = 0.24F;
  double dx = 6.532;
    
  IPrimitiveImpl iPrim;
  FPrimitiveImpl fPrim;
  DPrimitiveImpl dPrim;

  // -------
  // Process
  // -------

  iPrim.fixXTarget(ix);
  fPrim.fixXTarget(fx);
  dPrim.fixXTarget(dx);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( ix, iPrim.xTarget() );
  CPPUNIT_ASSERT_EQUAL( fx, fPrim.xTarget() );
  CPPUNIT_ASSERT_EQUAL( dx, dPrim.xTarget() );

  // Ensure that updateSource() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSource, iPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, fPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, dPrim._updateSourceCallCnt == 0);

  // Ensure that updateTarget() is correctly called.
  CPPUNIT_ASSERT_MESSAGE(messTarget, iPrim._updateTargetCallCnt == 1);
  CPPUNIT_ASSERT_MESSAGE(messTarget, fPrim._updateTargetCallCnt == 1);
  CPPUNIT_ASSERT_MESSAGE(messTarget, dPrim._updateTargetCallCnt == 1);

  // Ensure that updateSourceTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, iPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, fPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, dPrim._updateSourceTargetCallCnt == 0);
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testFixYSource()
{
  // ------
  // Set Up
  // ------
  
  int    iy = 4;
  float  fy = 9.24F;
  double dy = 0.4;
    
  IPrimitiveImpl iPrim;
  FPrimitiveImpl fPrim;
  DPrimitiveImpl dPrim;

  // -------
  // Process
  // -------

  iPrim.fixYSource(iy);
  fPrim.fixYSource(fy);
  dPrim.fixYSource(dy);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( iy, iPrim.ySource() );
  CPPUNIT_ASSERT_EQUAL( fy, fPrim.ySource() );
  CPPUNIT_ASSERT_EQUAL( dy, dPrim.ySource() );

  // Ensure that updateSource() is correctly called.
  CPPUNIT_ASSERT_MESSAGE(messSource, iPrim._updateSourceCallCnt == 1);
  CPPUNIT_ASSERT_MESSAGE(messSource, fPrim._updateSourceCallCnt == 1);
  CPPUNIT_ASSERT_MESSAGE(messSource, dPrim._updateSourceCallCnt == 1);

  // Ensure that updateTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messTarget, iPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, fPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, dPrim._updateTargetCallCnt == 0);

  // Ensure that updateSourceTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, iPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, fPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, dPrim._updateSourceTargetCallCnt == 0);
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testFixYTarget()
{
  // ------
  // Set Up
  // ------
  
  int    iy = 4;
  float  fy = 9.24F;
  double dy = 0.4;
    
  IPrimitiveImpl iPrim;
  FPrimitiveImpl fPrim;
  DPrimitiveImpl dPrim;

  // -------
  // Process
  // -------

  iPrim.fixYTarget(iy);
  fPrim.fixYTarget(fy);
  dPrim.fixYTarget(dy);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( iy, iPrim.yTarget() );
  CPPUNIT_ASSERT_EQUAL( fy, fPrim.yTarget() );
  CPPUNIT_ASSERT_EQUAL( dy, dPrim.yTarget() );

  // Ensure that updateSource() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSource, iPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, fPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, dPrim._updateSourceCallCnt == 0);

  // Ensure that updateTarget() is correctly called.
  CPPUNIT_ASSERT_MESSAGE(messTarget, iPrim._updateTargetCallCnt == 1);
  CPPUNIT_ASSERT_MESSAGE(messTarget, fPrim._updateTargetCallCnt == 1);
  CPPUNIT_ASSERT_MESSAGE(messTarget, dPrim._updateTargetCallCnt == 1);

  // Ensure that updateSourceTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, iPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, fPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, dPrim._updateSourceTargetCallCnt == 0);
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testFixXYSource()
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
    
  IPrimitiveImpl iPrim;
  FPrimitiveImpl fPrim;
  DPrimitiveImpl dPrim;

  // -------
  // Process
  // -------

  iPrim.fixSource(ix, iy);
  fPrim.fixSource(fx, fy);
  dPrim.fixSource(dx, dy);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( ix, iPrim.xSource() );
  CPPUNIT_ASSERT_EQUAL( fx, fPrim.xSource() );
  CPPUNIT_ASSERT_EQUAL( dx, dPrim.xSource() );

  CPPUNIT_ASSERT_EQUAL( iy, iPrim.ySource() );
  CPPUNIT_ASSERT_EQUAL( fy, fPrim.ySource() );
  CPPUNIT_ASSERT_EQUAL( dy, dPrim.ySource() );

  // Ensure that updateSource() is correctly called.
  CPPUNIT_ASSERT_MESSAGE(messSource, iPrim._updateSourceCallCnt == 1);
  CPPUNIT_ASSERT_MESSAGE(messSource, fPrim._updateSourceCallCnt == 1);
  CPPUNIT_ASSERT_MESSAGE(messSource, dPrim._updateSourceCallCnt == 1);

  // Ensure that updateTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messTarget, iPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, fPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, dPrim._updateTargetCallCnt == 0);

  // Ensure that updateSourceTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, iPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, fPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, dPrim._updateSourceTargetCallCnt == 0);
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testFixXYTarget()
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
    
  IPrimitiveImpl iPrim;
  FPrimitiveImpl fPrim;
  DPrimitiveImpl dPrim;

  // -------
  // Process
  // -------

  iPrim.fixTarget(ix, iy);
  fPrim.fixTarget(fx, fy);
  dPrim.fixTarget(dx, dy);

  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL( ix, iPrim.xTarget() );
  CPPUNIT_ASSERT_EQUAL( fx, fPrim.xTarget() );
  CPPUNIT_ASSERT_EQUAL( dx, dPrim.xTarget() );

  CPPUNIT_ASSERT_EQUAL( iy, iPrim.yTarget() );
  CPPUNIT_ASSERT_EQUAL( fy, fPrim.yTarget() );
  CPPUNIT_ASSERT_EQUAL( dy, dPrim.yTarget() );

  // Ensure that updateSource() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSource, iPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, fPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, dPrim._updateSourceCallCnt == 0);

  // Ensure that updateTarget() is correctly called.
  CPPUNIT_ASSERT_MESSAGE(messTarget, iPrim._updateTargetCallCnt == 1);
  CPPUNIT_ASSERT_MESSAGE(messTarget, fPrim._updateTargetCallCnt == 1);
  CPPUNIT_ASSERT_MESSAGE(messTarget, dPrim._updateTargetCallCnt == 1);

  // Ensure that updateSourceTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, iPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, fPrim._updateSourceTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, dPrim._updateSourceTargetCallCnt == 0);
}

// -------------------------------------------------------------------

void
AbstractGenPrimitiveTest::testFixXYSourceTarget()
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

  IPrimitiveImpl iPrim;
  FPrimitiveImpl fPrim;
  DPrimitiveImpl dPrim;

  // -------
  // Process
  // -------
  
  iPrim.fixSourceTarget(ixs, iys, ixt, iyt);
  fPrim.fixSourceTarget(fxs, fys, fxt, fyt);
  dPrim.fixSourceTarget(dxs, dys, dxt, dyt);

  // -----
  // Check
  // -----

  // Ensure that the source has correctly been assigned.
  CPPUNIT_ASSERT( iPrim.source() == iPt0 );
  CPPUNIT_ASSERT( fPrim.source() == fPt0 );
  CPPUNIT_ASSERT( dPrim.source() == dPt0 );
  
  // Ensure that the target as correctly been assigned.
  CPPUNIT_ASSERT( iPrim.target() == iPt1 );
  CPPUNIT_ASSERT( fPrim.target() == fPt1 );
  CPPUNIT_ASSERT( dPrim.target() == dPt1 );

  // Ensure that updateSource() is not called.
  CPPUNIT_ASSERT_MESSAGE(messSource, iPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, fPrim._updateSourceCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messSource, dPrim._updateSourceCallCnt == 0);

  // Ensure that updateTarget() is not called.
  CPPUNIT_ASSERT_MESSAGE(messTarget, iPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, fPrim._updateTargetCallCnt == 0);
  CPPUNIT_ASSERT_MESSAGE(messTarget, dPrim._updateTargetCallCnt == 0);

  // Ensure that updateSourceTarget() is correctly called.
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, iPrim._updateSourceTargetCallCnt == 1);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, fPrim._updateSourceTargetCallCnt == 1);
  CPPUNIT_ASSERT_MESSAGE(messSourceTarget, dPrim._updateSourceTargetCallCnt == 1);
}

// ----------------------------------------------------------------------
