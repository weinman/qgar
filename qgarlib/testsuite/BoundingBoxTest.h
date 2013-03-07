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


#ifndef __BOUNDINGBOXTEST_H_INCLUDED__
#define __BOUNDINGBOXTEST_H_INCLUDED__


/**
 * @file BoundingBoxTest.h
 * @brief Header file of class BoundingBoxTest
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   February 19, 2004  17:17
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete.
/* $Id: BoundingBoxTest.h,v 1.6 2007/02/14 17:34:27 masini Exp $ */



// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>
// QGAR
#include <qgarlib/BoundingBox.h>
#include <qgarlib/primitives.h>



/**
 * @class BoundingBoxTest BoundingBoxTest.h
 * @brief Test class for class BoundingBox.
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   February 19, 2004  17:17
 * @since  Qgar 2.1.1
 */
class BoundingBoxTest

  : public CppUnit::TestFixture

{
// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------


  CPPUNIT_TEST_SUITE( BoundingBoxTest );

  // Constructors
  CPPUNIT_TEST( testDefaultConstructor );
  CPPUNIT_TEST( testBuildFromTwoPoints );
  CPPUNIT_TEST( testBuildFrom4Coords );
  CPPUNIT_TEST( testBuildFromTopLeftWidthAndHeight );
  CPPUNIT_TEST_EXCEPTION( testBuildFromTopLeftWidthAndHeightBadWidth,
			  qgar::QgarErrorDomain);
  CPPUNIT_TEST_EXCEPTION( testBuildFromTopLeftWidthAndHeightBadHeight,
			  qgar::QgarErrorDomain);
  CPPUNIT_TEST( testBuildFromWidthHeightAndBottomRight );
  CPPUNIT_TEST_EXCEPTION( testBuildFromWidthHeightAndBottomRightBadWidth,
			  qgar::QgarErrorDomain);
  CPPUNIT_TEST_EXCEPTION( testBuildFromWidthHeightAndBottomRightBadHeight, 
			  qgar::QgarErrorDomain);
  CPPUNIT_TEST( testCopyConstructor );

  // Access to corners
  CPPUNIT_TEST( testAccessCorners );

  // Access to dimensions
  CPPUNIT_TEST( testLength );
  CPPUNIT_TEST( testWidth );
  CPPUNIT_TEST( testHeight );
  CPPUNIT_TEST( testArea );

  // Set corners
  CPPUNIT_TEST( testSetTopLeft );
  CPPUNIT_TEST_EXCEPTION( testSetTopLeftExc, qgar::QgarErrorDomain );
  CPPUNIT_TEST( testSetBottomRight );
  CPPUNIT_TEST_EXCEPTION( testSetBottomRightExc, qgar::QgarErrorDomain);
  CPPUNIT_TEST( testSetCornersFrom2Points );
  CPPUNIT_TEST( testSetCornersFrom4Coords );

  // Geometrical predicates
  CPPUNIT_TEST( testContainsPoint );
  CPPUNIT_TEST( testContainsBox );
  CPPUNIT_TEST( testIntersects );

  // Geometrical operations
  CPPUNIT_TEST( testIntersection );

  // Operators
  CPPUNIT_TEST( testAssignment );
  CPPUNIT_TEST( testInEquality );

  // Serialization/deserialization
  CPPUNIT_TEST( testSerializeDeserialize );

  CPPUNIT_TEST_SUITE_END();


// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:


/** @name Test Fixture Implementation */
//        ===========================
//@{

  virtual void setUp();

  virtual void tearDown();

//@}


/** @name Constructors */
//        ============
//@{

/**
 * @brief Tests qgar::BoundingBox::BoundingBox()
 *
 * Performed Checks:
 * - Ensure that both corner are set to (0,0)
 */
  void testDefaultConstructor();

/**
 * @brief Tests qgar::BoundingBox::BoundingBox(const GenPoint&, const GenPoint&)
 *
 * Performed Tests:
 * - Ensure that corner points are correctly computed
 */
  void testBuildFromTwoPoints();

/**
 * @brief Tests qgar::BoundingBox::BoundingBox(T, T, T, T)
 *
 * Performed Tests:
 * - Ensure that corner points are correctly computed
 */
  void testBuildFrom4Coords();

/**
 * @brief Tests qgar::BoundingBox::BoundingBox(const GenPoint&, T, T)
 *
 * Performed Tests:
 * - Ensure that top left point is correctly assigned
 * - Ensure that length and height are correctly assigned
 */
  void testBuildFromTopLeftWidthAndHeight();

/**
 * @brief Tests qgar::BoundingBox::BoundingBox(const GenPoint&, T, T)
 *
 * Performed Tests:
 * - Ensure that giving a null or negative width raises a
 *   qgar::QgarErrorDomain exception.
 */
  void testBuildFromTopLeftWidthAndHeightBadWidth();

/**
 * @brief Tests qgar::BoundingBox::BoundingBox(const GenPoint&, T, T)
 *
 * Performed Tests:
 * - Ensure that giving a null or negative height raises a
 *   qgar::QgarErrorDomain exception.
 */
  void testBuildFromTopLeftWidthAndHeightBadHeight();

/**
 * @brief Tests qgar::BoundingBox::BoundingBox(T, T, const GenPoint&)
 *
 * Performed Tests:
 * - Ensure that bottom right point is correctly copied.
 */
  void testBuildFromWidthHeightAndBottomRight();

/**
 * @brief Tests qgar::BoundingBox::BoundingBox(T, T, const GenPoint&)
 *
 * Performed Tests:
 * - Ensure that giving a null or negative width raises a
 *   qgar::QgarErrorDomain exception.
 */
  void testBuildFromWidthHeightAndBottomRightBadWidth();

/**
 * @brief Tests qgar::BoundingBox::BoundingBox(T, T, const GenPoint&)
 *
 * Performed Tests:
 * - Ensure that giving a null or negative height raises a
 *   qgar::QgarErrorDomain exception.
 */
  void testBuildFromWidthHeightAndBottomRightBadHeight();

/**
 * @brief Tests BoundingBox(const BoundingBox&)
 *
 * Performed Checks:
 * - Ensure that corner points are correctly copied
 */
  void testCopyConstructor();

//@}


/** @name Acces to corners */
//        ================
//@{

/**
 * @brief Tests:
 * - qgar::BoundingBox::accessTopLeft()
 * - qgar::BoundingBox::topLeft()
 * - qgar::BoundingBox::accessBottomRight()
 * - qgar::BoundingBox::bottomRight()
 * - qgar::BoundingBox::xTopLeft()
 * - qgar::BoundingBox::yTopLeft()
 * - qgar::BoundingBox::xBottomRight()
 * - qgar::BoundingBox::yBottomRight()
 *
 * Performed Tests:
 * - Ensure that corners are correctly accessed
 */
  void testAccessCorners();

//@}


/** @name Acces to dimensions */
//        ===================
//@{

/**
 * @brief Tests qgar::BoundingBox::length()
 *
 * Performed Tests:
 * - Compare the returned result to the value computed using the
 *   corners coordinates.
 */
  void testLength();

/**
 * @brief Tests qgar::BoundingBox::width()
 *
 * Performed Tests:
 * - Compare the returned result to the value computed using the
 *   corners coordinates.
 */
  void testWidth();

/**
 * @brief Tests qgar::BoundingBox::height()
 *
 * Performed Tests:
 * - Compare the returned result to the value computed using the
 *   corners coordinates.
 */
  void testHeight();

/**
 * @brief Tests qgar::BoundingBox::area()
 *
 * Performed Tests:
 * - Compare the returned result to the value computed using the
 *   corners coordinates.
 */
  void testArea();

//@}


/** @name Set corners */
//        ===========
//@{

/**
 * @brief Tests
 *         qgar::BoundingBox::setTopLeft(const GenPoint&)
 *     and qgar::BoundingBox::setTopLeft(T, T).
 *
 * Performed Tests:
 * - Ensure that the top left corner of the box is correctly
 *   assigned.
 */
  void testSetTopLeft();

/**
 * @brief Tests qgar::BoundingBox::setTopLeft(const GenPoint&)
 *
 * Performed Tests:
 * - Ensure that giving a bad left corner point (i.e. a point that is
 *   located more to the "bottom" or the "right" than the existing *
 *   bottom right corner) raises a qgar::QgarErrorDomain exception.
 */
  void testSetTopLeftExc();

/**
 * @brief Tests
 *         qgar::BoundingBox::setBottomRight(const GenPoint&)
 *     and qgar::BoundingBox::setBottomRight(T, T).
 *
 * Performed Tests:
 * - Ensure that the bottom right corner of the box is correctly
 *   assigned.
 */
  void testSetBottomRight();

/**
 * @brief Tests qgar::BoundingBox::setBottomRight(const GenPoint&)
 *
 * Performed Tests:
 * - Ensure that giving a bad lef corner point (i.e. a point that is
 *   located more to the "bottom" or the "right" than the existing
 *   bottom right corner) raises a qgar::QgarErrorDomain exception.
 */
  void testSetBottomRightExc();

/**
 * @brief Tests qgar::BoundingBox::setCorners(const GenPoint&, const GenPoint&)
 *
 * Performed Tests:
 * - Ensure that new box corners are correctly computed from the
 *   coordinates of the given points.
 */
  void testSetCornersFrom2Points();

/**
 * @brief Tests qgar::BoundingBox::setCorners(T, T, T, T)
 *
 * Performed Tests:
 * - Ensure that new box corners are correctly computed from the
 *   coordinates of the passed coordinates.
 */
  void testSetCornersFrom4Coords();

//@}


/** @name Geometrical predicates */
//        ======================
//@{

/**
 * @brief Tests
 *   qgar::BoundingBox::contains(const GenPoint<int>&),
 *   qgar::BoundingBox::contains(int, int).
 *
 * Performed Tests:
 * - Ensure that a point is correctly considered as being inside
 *   the box and outside of the box.
 * - Ensure that a border point is considered as being inside the box.
 */
  void testContainsPoint();

/**
 * @brief Tests qgar::BoundingBox::contains(const BoundingBox&).
 *
 * Performed Tests:
 * - Ensure that true is returned if and only if the current
 *   bounding box includes the given bounding box
 */
  void testContainsBox();

/**
 * @brief Tests qgar::BoundingBox::intersects(const BoundingBox&).
 *
 * Performed Tests:
 * - Ensure that true is returned if and only if the two
 *   bounding boxes intersect.
 */
  void testIntersects();

//@}


/** @name Geometrical operations */
//        ======================
//@{

/**
 * @brief Tests the intersection between two bounding boxes.
 *
 * Performed Tests:
 * - When bounding boxes do not intersect,
 *   ensure that a null pointer is returned 
 * - When bounding boxes intersect, ensure that the returned
 *   bounding box represents the intersection
 */
  void testIntersection();

//@}


/** @name Operators */
//        =========
//@{

/**
 * @brief Tests qgar::BoundingBox::operator=(const BoundingBox&)
 *
 * Performed Checks:
 * - Ensure that corner points are correctly assigned
 */
  void testAssignment();

/**
 * @brief Tests
 *   qgar::BoundingBox::operator==(const BoundingBox&),
 *   qgar::BoundingBox::eq(const BoundingBox&),
 *   qgar::BoundingBox::notEq(const BoundingBox&),
 *   qgar::BoundingBox::operator!=(const BoundingBox&).
 *
 * Performed Checks:
 * - Ensure that (in)equality is correctly tested using appropriate
 *   operators and functional operators.
 */
  void testInEquality();

//@}


/** @name Serialization/deserialization */
//        =============================
//@{

/**
 * @brief Tests qgar::BoundingBox::operator<<()
 *        and qgar::BoundingBox::operator>>()
 *
 * Performed Tests:
 * - Serialize and deserialize a BoundingBox and make sure it is
 *   identical to the original.
 */
  void testSerializeDeserialize();

//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  
/** @name Testing Values */
//        ==============
//@{

  /// Top left point x coordinate
  int _ix0;

  /// Top left point y coordinate
  int _iy0;

  /// Bottom right point x coordinate
  int _ix1;

  /// Bottom right point y coordinate
  int _iy1;

  /// Top left point of the test bounding box for int values
  qgar::Point _iTopLeft;

  /// Top right point of the test bounding box for int values
  qgar::Point _iTopRight;

  /// Bottom left point of the test bounding box for int values
  qgar::Point _iBottomLeft;

  /// Bottom right point of the test bounding box for int values
  qgar::Point _iBottomRight;

  /// Int bounding box created from _iTopLeft and _iBottomRight
  qgar::BoundingBox _iBox;

//@}


// -------------------------------------------------------------------
}; // class BoundingBoxTest


#endif /* __BOUNDINGBOXTEST_H_INCLUDED__ */
