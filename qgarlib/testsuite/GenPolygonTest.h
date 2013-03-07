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


#ifndef __GENPOLYGONTEST_H_INCLUDED__
#define __GENPOLYGONTEST_H_INCLUDED__


/**
 * @file     GenPolygonTest.h
 * @brief    Header file of class GenPolygonTest.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date     March 24, 2004  18:11
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete.
/* $Id: GenPolygonTest.h,v 1.6 2007/02/14 17:34:27 masini Exp $ */



// STL
#include <list>
// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>
// QGAR
#include <qgarlib/primitives.h>
#include <qgarlib/QgarErrorUser.h>



/**
 * @class GenPolygonTest GenPolygonTest.h
 * @brief Test class for class GenPolygon.
 * 
 * Untested function members:
 * - qgar::GenPolygon::accessVertices
 * - qgar::GenPolygon::vertices
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   March 24, 2004  18:11
 * @since  Qgar 2.1.1
 */
class GenPolygonTest

  : public CppUnit::TestFixture

{
// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( GenPolygonTest );

  // Constructors
  CPPUNIT_TEST( testDefaultConstructor );
  CPPUNIT_TEST( testCopyConstructor );
  CPPUNIT_TEST( testBuildFromQgarPolygon );
  CPPUNIT_TEST( testBuildFromPointList );
  CPPUNIT_TEST_EXCEPTION( testBuildFromPointListThrow, qgar::QgarErrorUser );

  // Copy
  CPPUNIT_TEST( testClone );

  // Operators
  CPPUNIT_TEST( testAssignment );

  // Area
  CPPUNIT_TEST( testArea );

  // Access to vertices
  CPPUNIT_TEST( testSize );
  CPPUNIT_TEST( testGetVertices );

  // Insert vertices
  CPPUNIT_TEST( testAppend );

  // Remove vertices
  CPPUNIT_TEST( testRemove );
  CPPUNIT_TEST_EXCEPTION( testRemoveThrow, qgar::QgarErrorUser );

  // Conversions of the vertices
  CPPUNIT_TEST( testToPtVect );
  CPPUNIT_TEST( testToSegList );

  //  Geometry: Translation
  CPPUNIT_TEST( testTranslate );

  // Serialization/deserialization
  CPPUNIT_TEST( testSerializeDeserialize );

  // Spurce and target updates
  CPPUNIT_TEST( testUpdateSourceTarget );

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
 * @brief Tests qgar::GenPolygon::GenPolygon().
 *
 * Performed Checks:
 * - created polygon is empty
 */
  void testDefaultConstructor();

/**
 * @brief Tests qgar::GenPolygon::GenPolygon(const qgar::GenPolygon<T>&).
 *
 * Performed Checks:
 * - vertices, source and target are correctly initialized
 */
  void testCopyConstructor();

/**
 * @brief Tests qgar::GenPolygon::GenPolygon(const qgar::GenQgarPolygon<T>&).
 *
 * Performed Tests:
 * - constructed polygon is correctly initialized
 */
  void testBuildFromQgarPolygon();

/**
 * @brief Tests qgar::GenPolygon::GenPolygon(const std::list< qgar::GenPoint<T> >&).
 *
 * Performed Tests:
 * - vertices, source and target are correctly initialized
 */
  void testBuildFromPointList();

/**
 * @brief Tests qgar::GenPolygon::GenPolygon(const std::list< qgar::GenPoint<T> >&).
 *
 * Performed Tests:
 * - exception qgar::QgarErrorUser is raised
 *   when the list includes less than 3 points
 */
  void testBuildFromPointListThrow();

//@}


/** @name Copy */
//        ====
//@{

/**
 * @brief Tests qgar::GenPolygon::clone().
 *
 * Performed Tests:
 * - vertices, source and target are correctly initialized
 */
  void testClone();

//@}


/** @name Operators */
//        =========
//@{

/**
 * @brief Tests qgar::GenPolygon::operator=(const qgar::GenPolygon<T>&).
 *
 * Performed Checks:
 * - vertices, source and target are correctly initialized
 */
  void testAssignment();

//@}


/** @name Area */
//        ====
//@{

/**
 * @brief Tests qgar::GenPolygon::area(),
 *              qgar::GenPolygon::signedArea().
 *
 * Performed Tests:
 * - returned area is correct
 */
  void testArea();

//@}


/** @name Access to vertices */
//        ==================
//@{

/**
 * @brief Tests qgar::GenPolygon::size().
 *
 * Performed Tests:
 * - returned size is correct
 */
  void testSize();

/**
 * @brief Tests qgar::GenPolygon::getVertices().
 *
 * Performed Tests:
 * - a client can directly modify the vertices of a polygon
 */
  void testGetVertices();

//@}


/** @name Insert vertices */
//        ===============
//@{

/**
 * @brief Tests qgar::GenPolygon::appendSource,
 *              qgar::GenPolygon::appendTarget,
 *              qgar::GenPolygon::append.
 *
 * Performed Tests:
 * - source, target, and vertices are correctly updated
 */
  void testAppend();

//@}


/** @name Remove vertices */
//        ===============
//@{

/**
 * @brief Tests qgar::GenPolygon::remove.
 *
 * Performed Tests:
 * - correct removal of target, source, and intermediate vertex
 * - no removal when given point is not a vertex
 */
  void testRemove();

/**
 * @brief Tests qgar::GenPolygon::remove.
 *
 * Performed Tests:
 * - a qgar::QgarErrorUser exception is raised
 *   when the polygon has 3 vertices
 */
  void testRemoveThrow();

//@}


/** @name Conversions of the vertices */
//        ===========================
//@{

/**
 * @brief Tests qgar::GenPolygon::toPointVector.
 *
 * Performed Tests:
 * - provided list of points is correct
 */
  void testToPtVect();

/**
 * @brief Tests qgar::GenPolygon::toSegList
 *          and qgar::GenPolygon::toQgarSegList.
 *
 * Performed Tests:
 * - provided lists of segments are correct
 */
  void testToSegList();

//@}


/** @name Geometry: Translation */
//        =====================
//@{

/**
 * @brief Tests qgar::GenPolygon::translate.
 *
 * Performed Tests:
 * - Giving X and Y factors for translation, new coordinates
 *   of vertices, source and target are correct
 */
  void testTranslate();

//@}


/** @name Serialization/deserialization */
//        =============================
//@{

/**
 * @brief Tests
 * std::istream& operator>> <> (std::istream&, qgar::GenPolygon<T>&)
 * and
 * std::ostream& operator<< <> (std::ostream&, const qgar::GenPolygon<T>&).
 *
 * Performed Checks:
 * - serialized and deserialized polygons are identical
 */
  void testSerializeDeserialize();

//@}


/** @name Source and target updates */
//        =========================
//@{

/**
 * @brief Tests correctness of functions 
 *   qgar::GenPolygon::updateSource(),
 *   qgar::GenPolygon::updateTarget(),
 *   and
 *   qgar::GenPolygon::updateSourceTarget().
 * when using functions
 *   qgar::GenPolygon::fixSource,
 *   qgar::GenPolygon::fixTarget,
 *   qgar::GenPolygon::fixSourceTarget,
 *   qgar::GenPolygon::fixXSource,
 *   qgar::GenPolygon::fixYSource,
 *   qgar::GenPolygon::fixXTarget,
 *   and
 *   qgar::GenPolygon::fixYTarget.
 *
 * Performed Tests:
 * - source and target modifications are propagated into vertices list
 */
  void testUpdateSourceTarget();

//@}


// -------------------------------------------------------------------
// P R O T E C T E D   M E M B E R S
// -------------------------------------------------------------------
protected:

  qgar::IPoint _iPt0;
  qgar::IPoint _iPt1;
  qgar::IPoint _iPt2;
  qgar::IPoint _iPt3;

  std::list<qgar::IPoint> _iPtList;

  qgar::FPoint _fPt0;
  qgar::FPoint _fPt1;
  qgar::FPoint _fPt2;
  qgar::FPoint _fPt3;

  std::list<qgar::FPoint> _fPtList;

  qgar::DPoint _dPt0;
  qgar::DPoint _dPt1;
  qgar::DPoint _dPt2;
  qgar::DPoint _dPt3;

  std::list<qgar::DPoint> _dPtList;


// -------------------------------------------------------------------

}; // class GenPolygonTest


#endif /* __GENPOLYGONTEST_H_INCLUDED__ */
