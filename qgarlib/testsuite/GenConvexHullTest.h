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


#ifndef __GENCONVEXHULLTEST_H_INCLUDED__
#define __GENCONVEXHULLTEST_H_INCLUDED__


/**
 * @file     GenConvexHullTest.h
 * @brief    Header file of class GenConvexHullTest.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date     April 2, 2004  17:10
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete.
/* $Id: GenConvexHullTest.h,v 1.3 2005/01/28 15:56:45 masini Exp $ */



// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>



/**
 * @class GenConvexHullTest GenConvexHullTest.h
 * @brief Test class for class GenConvexHull.
 * 
 * Untested function members:
 * - 
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   April 2, 2004  17:10
 * @since  Qgar 2.1.1
 */
class GenConvexHullTest : public CppUnit::TestFixture
{
// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( GenConvexHullTest );

  // No test
  // -------

  CPPUNIT_TEST( testPivot );
  CPPUNIT_TEST( testAccessPivot );
  CPPUNIT_TEST( testEmpty );
  CPPUNIT_TEST( testSize );

  // Effective tests
  // ---------------

  CPPUNIT_TEST( testDefaultConstructor );
  CPPUNIT_TEST( testBuildFromPointList );
  CPPUNIT_TEST( testCopyConstructor );
  CPPUNIT_TEST( testAssignment );
  CPPUNIT_TEST( testSerializeDeserialize );

  CPPUNIT_TEST_SUITE_END();

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name TestFixture Impl */
//        ================
//@{

  virtual void setUp();

  virtual void tearDown();

//@}


/** @name Non-tested functions */
//        ====================
//@{

/**
 * @brief Tests qgar::GenConvexHull::pivot()
 *
 * Performed Checks:
 * - none : The function is assumed to be correct!
 */
  void testPivot();

/**
 * @brief Tests qgar::GenConvexHull::accessPivot()
 *
 * Performed Checks:
 * - none : The function is assumed to be correct!
 */
  void testAccessPivot();

/**
 * @brief Tests qgar::GenConvexHull::empty()
 *
 * Performed Checks:
 * - none : The function is assumed to be correct!
 */
  void testEmpty();

/**
 * @brief Tests qgar::GenConvexHull::size()
 *
 * Performed Checks:
 * - none : The function is assumed to be correct!
 */
  void testSize();

//@}


/** @name Tested functions */
//        ================
//@{

/**
 * @brief Tests qgar::GenConvexHull::GenConvexHull()
 *
 * Performed Checks:
 * - the list of vertices is empty
 * - the list of pairs sorted according to increasing angles about the pivot
 *   is not checked
 */
  void testDefaultConstructor();

/**
 * @brief qgar::GenConvexHull::GenConvexHull(const std::list< qgar::GenPoint<T> >&)
 *
 * Performed Tests:
 * - initial list of 0, 1, 2, 3 and more points
 * - 

 * @warning <b>Checks about resulting hulls take Graham's scan specificity
 * into account: They vertices of a given hull are supposed to be arranged
 * in a certain order, and they are checked to conform to this order.</b>
 */
  void testBuildFromPointList();

/**
 * @brief Tests qgar::GenConvexHull::GenConvexHull(const GenConvexHull<T>&)
 *
 * Performed Checks:
 * - given and new hulls are identical
 */
  void testCopyConstructor();

/**
 * @brief Tests qgar::GenConvexHull::operator=(const GenConvexHull<T>&)
 *
 * Performed Checks:
 * - initial and new hulls are identical
 */
  void testAssignment();

/**
 * @brief Tests std::istream& operator>>(std::istream&, GenConvexHull<T>&);
 * and std::ostream& operator<< <> (std::ostream&, const GenConvexHull<T>&).
 *
 * Performed Checks:
 * - serialize and deserialize a hull and check deserialized hull
 *   is identical to the original hull
 */
  void testSerializeDeserialize();

//@}

// -------------------------------------------------------------------
}; // class GenConvexHullTest


#endif /* __GENCONVEXHULLTEST_H_INCLUDED__ */
