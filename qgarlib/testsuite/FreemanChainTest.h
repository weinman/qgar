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


#ifndef __FREEMANCHAINTEST_H_INCLUDED__
#define __FREEMANCHAINTEST_H_INCLUDED__


/**
 * @file     FreemanChainTest.h
 * @brief    Header file of class FreemanChainTest
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date     January 29, 2004  17:05
 * @since    Qgar 2.1
 */


// For RCS/CVS use: Do not delete.
/* $Id: FreemanChainTest.h,v 1.3 2005/07/13 16:29:34 masini Exp $ */



// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>
// QGAR
#include <qgarlib/primitives.h>



/**
 * @class FreemanChainTest FreemanChainTest.h
 * @brief Test class for class FreemanChain.
 * 
 * Untested function members:
 * - qgar::FreemanChain::accessBack
 * - qgar::FreemanChain::accessCodesList
 * - qgar::FreemanChain::accessCurrent
 * - qgar::FreemanChain::accessFront
 * - qgar::FreemanChain::current
 * - qgar::FreemanChain::empty
 * - qgar::FreemanChain::front
 * - qgar::FreemanChain::hasNext
 * - qgar::FreemanChain::hasPrevious
 * - qgar::FreemanChain::size
 * - qgar::FreemanChain::setToBegin
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   January 29, 2004  17:05
 * @since  Qgar 2.1
 */
class FreemanChainTest : public CppUnit::TestFixture
{
// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( FreemanChainTest );

  // No test
  CPPUNIT_TEST( testEmpty );
  CPPUNIT_TEST( testSize );
  CPPUNIT_TEST( testAccessFront );
  CPPUNIT_TEST( testFront );
  CPPUNIT_TEST( testAccessBack );
  CPPUNIT_TEST( testBack );
  CPPUNIT_TEST( testSetToBegin );
  CPPUNIT_TEST( testAccessCurrent );
  CPPUNIT_TEST( testCurrent );
  CPPUNIT_TEST( testAccessCodesList );
  CPPUNIT_TEST( testHasNext );
  CPPUNIT_TEST( testHasPrevious );

  // Effective tests
  CPPUNIT_TEST( testBuildFromPoint );
  CPPUNIT_TEST( testPush_frontPoint );
  CPPUNIT_TEST( testPush_frontCode );
  CPPUNIT_TEST( testPush_backPoint );
  CPPUNIT_TEST( testPush_backCode );
  CPPUNIT_TEST( testSetToEnd );
  CPPUNIT_TEST( testMoveNext );
  CPPUNIT_TEST( testMovePrevious );
  CPPUNIT_TEST( testNext );
  CPPUNIT_TEST( testPrevious );
  CPPUNIT_TEST( testToPointList );
  CPPUNIT_TEST( testReverse );
  CPPUNIT_TEST( testCopyConstructor );
  CPPUNIT_TEST( testAssignment );
  //CPPUNIT_TEST( testMerge );

  CPPUNIT_TEST_SUITE_END();

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name TestFixture Impl */
//        ================
//@{

/**
 * @brief Initialize the data for the tests.
 */
  virtual void setUp();

  virtual void tearDown();

//@}


/** @name Test Functions */
//        ==============
//@{

/**
 * @brief Tests empty()
 *
 * Performed tests:
 * - none : The function is assumed to be correct!
 */
  void testEmpty();

/**
 * @brief Tests size()
 *
 * Performed tests:
 * - none : The function is assumed to be correct!
 */
  void testSize();

/**
 * @brief Tests accessFront()
 *
 * Performed tests:
 * - none : The function is assumed to be correct!
 */
  void testAccessFront();

/**
 * @brief Tests front()
 *
 * Performed tests:
 * - none : The function is assumed to be correct!
 */
  void testFront();

/**
 * @brief Tests accessCurrent()
 *
 * Performed tests:
 * - none : The function is assumed to be correct!
 */
  void testAccessCurrent();

/**
 * @brief Tests current()
 *
 * Performed tests:
 * - none : The function is assumed to be correct!
 */
  void testCurrent();

/**
 * @brief Tests accessBack()
 *
 * Performed tests:
 * - none : The function is assumed to be correct!
 */
  void testAccessBack();

/**
 * @brief Tests back()
 *
 * Performed tests:
 * - none : The function is assumed to be correct!
 */
  void testBack();

/**
 * @brief Tests accessCodesList()
 *
 * Performed tests:
 * - none : The function is assumed to be correct!
 */
  void testAccessCodesList();

/**
 * @brief Tests hasNext()
 *
 * Performed tests:
 * - none : The function is assumed to be correct!
 */
  void testHasNext();

/**
 * @brief Tests hasPrevious()
 *
 * Performed tests:
 * - none : The function is assumed to be correct!
 */
  void testHasPrevious();

/**
 * @brief Tests setToBegin()
 *
 * Performed tests:
 * - none : The function is assumed to be correct!
 */
  void testSetToBegin();

/**
 * @brief Tests qgar::FreemanChain::FreemanChain(const GenPoint<int>&)
 *
 * Performed tests (for each type of point):
 * - the new chain includes only 1 point
 * - no previous and next points
 * - front, current and last points are correctly set
 */
  void testBuildFromPoint();

/**
 * @brief Tests qgar::FreemanChain::push_front(const GenPoint<int>&)
 *
 * Performed tests:
 * - push on an empty chain
 * - push on a chain including a single point
 * - push on a chain including at least two points
 * - first, current and last points are correctly set in all cases
 * - existence of previous and next points are correctly detected
 *   after each push 
 */
  void testPush_frontPoint();

/**
 * @brief Tests qgar::FreemanChain::push_front(QGEdirection, unsigned int)
 *
 * Performed tests:
 * - push on an empty chain
 * - push on a chain including a single point
 * - push on a chain including at least two points
 * - first, current and last points are correctly set in all cases
 * - existence of previous and next points are correctly detected
 *   after each push 
 */
  void testPush_frontCode();

/**
 * @brief Tests qgar::FreemanChain::push_back(const GenPoint<int>&)
 *
 * Performed tests:
 * - push on an empty chain
 * - push on a chain including a single point
 * - push on a chain including at least two points
 * - first, current and last points are correctly set in all cases
 * - existence of previous and next points are correctly detected
 *   after each push 
 */
  void testPush_backPoint();

/**
 * @brief Tests qgar::FreemanChain::push_back(QGEdirection, unsigned int)
 *
 * Performed tests:
 * - push on an empty chain
 * - push on a chain including a single point
 * - push on a chain including at least two points
 * - first, current and last points are correctly set in all cases
 * - existence of previous and next points are correctly detected
 *   after each push 
 */
  void testPush_backCode();

/**
 * @brief Tests qgar::FreemanChain::setToEnd()
 *
 * Performed tests:
 * - iterator is correctly set to end, but also to beginning of chain
 * - first, current and last points are correctly set in all cases
 * - existence of previous and next points are correctly detected
 */
  void testSetToEnd();

/**
 * @brief Tests qgar::FreemanChain::moveNext()
 *
 * Performed tests:
 * - iterator is set to next point
 * - first, current and last points are correctly set in all cases
 * - existence of previous and next points are correctly detected
 *
 * @warning The chain is supposed not to be empty.
 */
  void testMoveNext();

/**
 * @brief Tests qgar::FreemanChain::movePrevious()
 *
 * Performed tests:
 * - iterator is set to previous point
 * - first, current and last points are correctly set in all cases
 * - existence of previous and next points are correctly detected
 *
 * @warning The chain is supposed not to be empty.
 */
  void testMovePrevious();

/**
 * @brief Tests qgar::FreemanChain::next()
 *        and qgar::FreemanChain::accessNext()
 *
 * Performed tests:
 * - next point is returned
 * - first, current and last points are correctly set in all cases
 * - existence of previous and next points are correctly detected
 *
 * @warning The chain is supposed not to be empty,
 * and the iterator is supposed not to point to the last point.
 */
  void testNext();

/**
 * @brief Tests qgar::FreemanChain::previous()
 *        and qgar::FreemanChain::accessPrevious()
 *
 * Performed tests:
 * - previous point is returned
 * - first, current and last points are correctly set in all cases
 * - existence of previous and next points are correctly detected
 *
 * @warning The chain is supposed not to be empty,
 * and the iterator is supposed not to point to the last point.
 */
  void testPrevious();

/**
 * @brief Tests qgar::FreemanChain::toPointList()
 *
 * Performed tests:
 * - the returned chain includes the points coded in the Freeman
 *   chain, in the same order
 * - the returned chain is empty is the Freeman chain is empty
 */
  void testToPointList();

/**
 * @brief Tests qgar::FreemanChain::reverse()
 *
 * Performed tests:
 * - an empty chain can be reversed
 * - a non-empty chain is correctly reversed
 *   and the internal iterator remains valid
 */
  void testReverse();

/**
 * @brief Tests qgar::FreemanChain::FreemanChain(const FreemanChain&)
 *
 * Performed Checks:
 * - an empty chain is correctly copied
 * - a non-empty chain is correctly copied and the internal iterators
 *   of both chains point to the same position
 */
  void testCopyConstructor();

/**
 * @brief Tests qgar::FreemanChain::operator=(const FreemanChain&)
 *
 * Performed Checks: Same as the copy-constructor
 */
  void testAssignment();

///**
// * @brief Tests qgar::FreemanChain::merge()
// *
// * Performed tests:
// * - 
// */
//  void testMerge();

//@}

// -------------------------------------------------------------------
}; // class FreemanChainTest


#endif /* __FREEMANCHAINTEST_H_INCLUDED__ */
