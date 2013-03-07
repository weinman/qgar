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


#ifndef __GENQGARPOLYGONTEST_H_INCLUDED__
#define __GENQGARPOLYGONTEST_H_INCLUDED__


/**
 * @file     GenQgarPolygonTest.h
 * @brief    Header file of class GenQgarPolygonTest.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date     March 24, 2004  18:11
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete.
/* $Id: GenQgarPolygonTest.h,v 1.5 2005/07/13 16:29:34 masini Exp $ */



// STL
#include <list>
// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>
// QGAR
#include <qgarlib/primitives.h>
#include <qgarlib/QgarErrorUser.h>



/**
 * @class GenQgarPolygonTest GenQgarPolygonTest.h
 * @brief Test class for class GenQgarPolygon.
 * 
 * Untested function members:
 * - qgar::GenQgarPolygon::accessVertices
 * - qgar::GenQgarPolygon::vertices
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   March 24, 2004  18:11
 * @since  Qgar 2.1.1
 */
class GenQgarPolygonTest : public CppUnit::TestFixture
{
// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( GenQgarPolygonTest );

  // Constructors
  CPPUNIT_TEST( testDefaultConstructor );
  CPPUNIT_TEST( testCopyConstructor );
  CPPUNIT_TEST( testBuildFromPolygon );
  CPPUNIT_TEST( testBuildFromPointList );
  CPPUNIT_TEST_EXCEPTION( testBuildFromPointListExc, qgar::QgarErrorUser );

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
  CPPUNIT_TEST( testRemoveVertex );
  CPPUNIT_TEST_EXCEPTION( testRemoveVertexExc, qgar::QgarErrorUser );

  // Conversions
  CPPUNIT_TEST( testToPtVect );
  CPPUNIT_TEST( testToSegList );

  // Geometry: Translation
  CPPUNIT_TEST( testTranslate );

  // Serialization/deserialization
  CPPUNIT_TEST( testSerializeDeserialize );

  // Source and target updates
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
 * @brief Tests qgar::GenQgarPolygon::GenQgarPolygon().
 *
 * Performed Checks:
 * - created polygon is empty
 */
  void testDefaultConstructor();

/**
 * @brief Tests qgar::GenQgarPolygon::GenQgarPolygon(const qgar::GenQgarPolygon<T>&).
 *
 * Performed Checks:
 * - vertices, source, target, and attributes are correctly initialized
 */
  void testCopyConstructor();

/**
 * @brief Tests qgar::GenQgarPolygon::GenQgarPolygon(const qgar::GenPolygon<T>&).
 *
 * Performed Tests:
 * - vertices, source and target, and attributes are correctly initialized
 */
  void testBuildFromPolygon();

/**
 * @brief Tests qgar::GenQgarPolygon::GenQgarPolygon(const std::list< qgar::GenPoint<T> >&).
 *
 * Performed Tests:
 * - vertices, source and target, and attributes are correctly initialized
 */
  void testBuildFromPointList();

/**
 * @brief Tests qgar::GenQgarPolygon::GenQgarPolygon(const std::list< qgar::GenPoint<T> >&).
 *
 * Performed Tests:
 * - a qgar::QgarErrorUser exception is raised
 *   when the list has not at least 3 points
 */
  void testBuildFromPointListExc();

//@}


/** @name Copy */
//        ====
//@{

/**
 * @brief Tests qgar::GenQgarPolygon::clone().
 *
 * Performed Tests:
 * - vertices, source, target, and attributes are correctly initialized
 */
  void testClone();

//@}


/** @name Operators */
//        =========
//@{

/**
 * @brief Tests qgar::GenQgarPolygon::operator=(const qgar::GenQgarPolygon<T>&).
 *
 * Performed Checks:
 * - vertices, source, target, and attributes are correctly initialized
 */
  void testAssignment();

//@}


/** @name Area */
//        ====
//@{

/**
 * @brief Tests qgar::GenQgarPolygon::area(),
 *              qgar::GenQgarPolygon::signedArea().
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
 * @brief Tests qgar::GenQgarPolygon::size().
 *
 * Performed Tests:
 * - returned size is correct
 */
  void testSize();

/**
 * @brief Tests qgar::GenQgarPolygon::getVertices().
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
 * @brief Tests qgar::GenQgarPolygon::appendSource(),
 *              qgar::GenQgarPolygon::appendTarget(),
 *              qgar::GenQgarPolygon::append().
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
 * @brief Tests qgar::GenQgarPolygon::remove(const GenPoint<T>&)
 *
 * Performed Tests:
 * - correct removal of target, source, and intermediate vertex
 * - no removal when given point is not a vertex
 */
  void testRemoveVertex();

/**
 * @brief Tests qgar::GenQgarPolygon::remove(const GenPoint<T>&)
 *
 * Performed Tests:
 * - a qgar::QgarErrorUser exception is raised
 *   when the polygon has 3 v ertices
 */
  void testRemoveVertexExc();

//@}


/** @name Conversions of the vertices */
//        ===========================
//@{

/**
 * @brief Tests qgar::GenQgarPolygon::toPointVector().
 *
 * Performed Tests:
 * - provided list of points is correct
 */
  void testToPtVect();

/**
 * @brief Tests qgar::GenQgarPolygon::toSegList(),
 *              qgar::GenQgarPolygon::toQgarSegList().
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
 * @brief Tests qgar::GenQgarPolygon:translate(T,T).
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
 * std::istream& operator>> <> (std::istream&, qgar::GenQgarPolygon<T>&)
 * and
 * std::ostream& operator<< <> (std::ostream&, const qgar::GenQgarPolygon<T>&).
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
 *   qgar::GenQgarPolygon::updateSource(),
 *   qgar::GenQgarPolygon::updateTarget(),
 *   and
 *   qgar::GenQgarPolygon::updateSourceTarget().
 * when using functions
 *   qgar::GenQgarPolygon::fixSource,
 *   qgar::GenQgarPolygon::fixTarget,
 *   qgar::GenQgarPolygon::fixSourceTarget,
 *   qgar::GenQgarPolygon::fixXSource,
 *   qgar::GenQgarPolygon::fixYSource,
 *   qgar::GenQgarPolygon::fixXTarget,
 *   and
 *   qgar::GenQgarPolygon::fixYTarget.
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

}; // class GenQgarPolygonTest


#endif /* __GENQGARPOLYGONTEST_H_INCLUDED__ */
