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


#ifndef __GENPOINTCHAINTEST_H_INCLUDED__
#define __GENPOINTCHAINTEST_H_INCLUDED__


/**
 * @file     GenPointChainTest.h
 * @brief    Header file of class GenPointChainTest
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date     December 16, 2003  15:45
 * @since    Qgar 2.1
 */


// For RCS/CVS use: Do not delete.
/* $Id: GenPointChainTest.h,v 1.3 2005/01/28 15:56:46 masini Exp $ */



// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>
// QGAR
#include <qgarlib/primitives.h>



/**
 * @class GenPointChainTest GenPointChainTest.h
 * @brief Test class for class GenPointChain.
 * 
 * Untested function members:
 * - qgar::GenPointChain::back
 * - qgar::GenPointChain::empty
 * - qgar::GenPointChain::front
 * - qgar::GenPointChain::size
 * - qgar::GenPointChain::setToBegin
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 16, 2003  15:45
 * @since  Qgar 2.1
 */
class GenPointChainTest : public CppUnit::TestFixture
{
// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( GenPointChainTest );
  // No test
  CPPUNIT_TEST( testEmpty );
  CPPUNIT_TEST( testSize );
  CPPUNIT_TEST( testFront );
  CPPUNIT_TEST( testBack );
  CPPUNIT_TEST( testSetToBegin );
  // Effective tests
  CPPUNIT_TEST( testDefaultConstructor );
  CPPUNIT_TEST( testBuildFromPoint );
  CPPUNIT_TEST( testPush_front );
  CPPUNIT_TEST( testPush_back );
  CPPUNIT_TEST( testAccessFront );
  CPPUNIT_TEST( testToPointList );
  CPPUNIT_TEST( testAccessPointList );
  CPPUNIT_TEST( testNext );
  CPPUNIT_TEST( testAccessNext );
  CPPUNIT_TEST( testPrevious );
  CPPUNIT_TEST( testAccessPrevious );
  CPPUNIT_TEST( testCurrent );
  CPPUNIT_TEST( testAccessCurrent );
  CPPUNIT_TEST( testSetToEnd );
  CPPUNIT_TEST( testMoveNext );
  CPPUNIT_TEST( testMovePrevious );
  CPPUNIT_TEST( testHasNext );
  CPPUNIT_TEST( testHasPrevious );
  CPPUNIT_TEST( testAccessBack );
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
 * @brief Tests qgar::GenPointChain::empty()
 *
 * Performed Tests:
 * - none : The function is assumed to be correct!
 */
  void testEmpty();

/**
 * @brief Tests qgar::GenPointChain::size()
 *
 * Performed Tests:
 * - none : The function is assumed to be correct!
 */
  void testSize();

/**
 * @brief Tests qgar::GenPointChain::front()
 *
 * Performed Tests:
 * - none : The function is assumed to be correct!
 */
  void testFront();

/**
 * @brief Tests qgar::GenPointChain::back()
 *
 * Performed Tests:
 * - none : The function is assumed to be correct!
 */
  void testBack();

/**
 * @brief Tests qgar::GenPointChain::setToBegin()
 *
 * Performed Tests:
 * - none : The function is assumed to be correct!
 */
  void testSetToBegin();

// ===================================================================

/**
 * @brief Tests qgar::GenPointChain::GenPointChain()
 *
 * Performed Checks:
 * - chain is empty
 */
  void testDefaultConstructor();

/**
 * @brief Tests qgar::GenPointChain::GenPointChain(const GenPoint<T>&)
 *
 * Performed Tests (for each type of point):
 * - the new chain includes only 1 point
 * - this point has correct coordinates
 * - functions qgar::GenPointChain<T>::front
 *   and qgar::GenPointChain<T>::back returns the same result
 *   when there is only point in the chain
 *
 * @warning The internal iterator is supposed to be set
 *          to the beginning of the chain.
 */
  void testBuildFromPoint();

/**
 * @brief Tests qgar::GenPointChain::push_front()
 *
 * Performed Tests:
 * - pushed element becomes first element in chain
 * - last element is not changed
 */
  void testPush_front();

/**
 * @brief Tests qgar::GenPointChain::push_back()
 *
 * Performed Tests:
 * - pushed element becomes last element in chain
 * - first element is not changed
 */
  void testPush_back();

/**
 * @brief Tests qgar::GenPointChain::accessFront()
 *
 * Performed Tests:
 * - first point in chain is correctly accessed
 */
  void testAccessFront();

/**
 * @brief Tests qgar::GenPointChain::toPointList()
 *
 * Performed Tests:
 * - the returned chain includes the same points as the initial chain,
 *   in the same order
 */
  void testToPointList();

/**
 * @brief Tests qgar::GenPointChain::accessPointList()
 *
 * Performed Tests:
 * - (STL) point list can be correctly accessed
 */
  void testAccessPointList();

/**
 * @brief Tests qgar::GenPointChain::next()
 *
 * Performed Tests:
 * - effectively return the successor to the current point
 * - the validity of the internal iterator is preserved by
 *   functions qgar::GenPointChain<T>::push_back
 *   and qgar::GenPointChain<T>::push_front
 *
 * @warning The chain is supposed not to be empty,
 * and the iterator is supposed not to point to the last point.
 */
  void testNext();

/**
 * @brief Tests qgar::GenPointChain::accessNext()
 *
 * Performed Tests:
 * - effectively return the successor to the current point
 * - the validity of the internal iterator is preserved by
 *   functions qgar::GenPointChain<T>::push_back
 *   and qgar::GenPointChain<T>::push_front
 *
 * @warning The chain is supposed not to be empty,
 * and the iterator is supposed not to point to the last point.
 */
  void testAccessNext();

/**
 * @brief Tests qgar::GenPointChain::previous()
 *
 * Performed Tests:
 * - effectively return the predecessor to the current point
 * - the validity of the internal iterator is preserved by
 *   functions qgar::GenPointChain<T>::push_back
 *   and qgar::GenPointChain<T>::push_front
 *
 * @warning The chain is supposed not to be empty,
 * and the iterator is supposed not to point to the first point.
 */
  void testPrevious();

/**
 * @brief Tests qgar::GenPointChain::accessPrevious()
 *
 * Performed Tests:
 * - effectively return the predecessor to the current point
 * - the validity of the internal iterator is preserved by
 *   functions qgar::GenPointChain<T>::push_back
 *   and qgar::GenPointChain<T>::push_front
 *
 * @warning The chain is supposed not to be empty,
 * and the iterator is supposed not to point to the first point.
 */
  void testAccessPrevious();

/**
 * @brief Tests qgar::GenPointChain::current()
 *
 * Performed Tests:
 * - return effectively the current point
 * - the validity of the internal iterator is preserved by
 *   functions qgar::GenPointChain<T>::push_back
 *   and qgar::GenPointChain<T>::push_front
 *
 * @warning The chain is supposed not to be empty.
 */
  void testCurrent();

/**
 * @brief Tests qgar::GenPointChain::accessCurrent()
 *
 * Performed Tests:
 * - return effectively the current point
 * - the validity of the internal iterator is preserved by
 *   functions qgar::GenPointChain<T>::push_back
 *   and qgar::GenPointChain<T>::push_front
 *
 * @warning The chain is supposed not to be empty.
 */
  void testAccessCurrent();

/**
 * @brief Tests qgar::GenPointChain::moveNext()
 *
 * Performed Tests:
 * - set iterator to next point, that becomes the current point 
 *
 * @warning The chain is supposed not to be empty.
 */
  void testMoveNext();

/**
 * @brief Tests qgar::GenPointChain::movePrevious()
 *
 * Performed Tests:
 * - set iterator to previous point, that becomes the current point 
 *
 * @warning The chain is supposed not to be empty.
 */
  void testMovePrevious();

/**
 * @brief Tests qgar::GenPointChain::hasNext()
 *
 * Performed Tests:
 * - Return true when there is effectively a successor to the current point.
 *
 * @warning The chain is supposed not to be empty.
 */
  void testHasNext();

/**
 * @brief Tests qgar::GenPointChain::hasPrevious()
 *
 * Performed Tests:
 * - Return true when there is effectively a predecessor to the current point.
 *
 * @warning The chain is supposed not to be empty.
 */
  void testHasPrevious();

/**
 * @brief Tests qgar::GenPointChain::accessBack()
 *
 * Performed Tests:
 * - last point in chain is correctly accessed
 */
  void testAccessBack();

/**
 * @brief Tests qgar::GenPointChain::setToEnd()
 *
 * Performed Tests:
 * - the internal iterator points to the last point
 */
  void testSetToEnd();

/**
 * @brief Tests qgar::GenPointChain::reverse()
 *
 * Performed Tests:
 * - an empty chain can be reversed
 * - a non-empty chain is correctly reversed
 *   and the internal iterator remains valid
 */
  void testReverse();

/**
 * @brief Tests qgar::GenPointChain::GenPointChain(const GenPointChain<T>&)
 *
 * Performed Checks:
 * - an empty chain is correctly copied
 * - a non-empty chain is correctly copied and the internal iterator
 *   points to the beginning of the chain
 */
  void testCopyConstructor();

/**
 * @brief Tests qgar::GenPointChain::operator=(const GenPointChain<T>&)
 *
 * Performed Checks: Same as the copy-constructor
 */
  void testAssignment();

///**
// * @brief Tests qgar::GenPointChain::merge()
// *
// * Performed Tests:
// * - 
// */
//  void testMerge();

//@}

// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

/** @name Data for the tests */
//        ==================
//@{
/**
 * @brief Integer point.
 */
qgar::Point _ip1;
/**
 * @brief Integer point.
 */
qgar::Point _ip2;
/**
 * @brief Integer point.
 */
qgar::Point _ip3;
/**
 * @brief Integer point.
 */
qgar::Point _ip4;

/**
 * @brief Float point.
 */
qgar::FPoint _fp1;
/**
 * @brief Float point.
 */
qgar::FPoint _fp2;
/**
 * @brief Float point.
 */
qgar::FPoint _fp3;
/**
 * @brief Float point.
 */
qgar::FPoint _fp4;

/**
 * @brief Double point.
 */
qgar::DPoint _dp1;
/**
 * @brief Double point.
 */
qgar::DPoint _dp2;
/**
 * @brief Double point.
 */
qgar::DPoint _dp3;
/**
 * @brief Double point.
 */
qgar::DPoint _dp4;

//@}

// -------------------------------------------------------------------
}; // class GenPointChainTest


#endif /* __GENPOINTCHAINTEST_H_INCLUDED__ */
