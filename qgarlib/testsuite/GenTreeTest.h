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


#ifndef __GENTREETEST_H_INCLUDED__
#define __GENTREETEST_H_INCLUDED__


/**
 * @file     GenTreeTest.h
 * @brief    Header file of class GenTreeTest
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date     March 1, 2004  22:05
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete.
/* $Id: GenTreeTest.h,v 1.3 2005/01/28 15:56:46 masini Exp $ */



// STD
#include <vector>
// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>
// QGAR
#include <qgarlib/GenTree.h>
#include <qgarlib/QgarErrorUser.h>



using namespace qgar;
using namespace std;



/**
 * @class GenTreeTest GenTreeTest.h
 * @brief Test class for classes qgar::GenTree and qgar::GenTreeNode.
 * 
 * Class GenTreeNode:
 * Only functions to access and store data are tested:
 * - qgar::GenTreeNode::accessData
 * - qgar::GenTreeNode::data
 * - qgar::GenTreeNode::setData
 *
 * Untested function members of class GenTree:
 * - qgar::GenTree::pRoot
 * - qgar::GenTree::pCurrent
 * - qgar::GenTree::pFather
 * - qgar::GenTree::pLSibling
 * - qgar::GenTree::pRSibling
 * - qgar::GenTree::pFirstChild
 * - qgar::GenTree::setPRoot
 * - qgar::GenTree::setPCurrent
 * - qgar::GenTree::setPFather
 * - qgar::GenTree::setPLSibling
 * - qgar::GenTree::setPRSibling
 * - qgar::GenTree::setPFirstChild
 * - qgar::GenTree::gotoRoot
 * - qgar::GenTree::gotoParent
 * - qgar::GenTree::gotoLSibling
 * - qgar::GenTree::gotoRSibling
 * - qgar::GenTree::gotoFirstChild
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   March 1, 2004  22:05
 * @since  Qgar 2.1.1
 */
class GenTreeTest : public CppUnit::TestFixture
{
// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( GenTreeTest );

  // Class GenTreeNode
  // -----------------

  CPPUNIT_TEST( testNodeData );

  // Class GenTree
  // -------------

  // No test
  CPPUNIT_TEST( testEmpty );
  CPPUNIT_TEST( testPRoot );
  CPPUNIT_TEST( testPCurrent );
  CPPUNIT_TEST( testPParent );
  CPPUNIT_TEST( testPLSibling );
  CPPUNIT_TEST( testPRSibling );
  CPPUNIT_TEST( testPFirstChild );
  CPPUNIT_TEST( testSetPRoot );
  CPPUNIT_TEST( testSetPCurrent );
  CPPUNIT_TEST( testSetPParent );
  CPPUNIT_TEST( testSetPLSibling );
  CPPUNIT_TEST( testSetPRSibling );
  CPPUNIT_TEST( testSetPFirstChild );

  // Effective tests
  CPPUNIT_TEST( testDefaultConstructor );
  CPPUNIT_TEST( testBuildFromData );
  CPPUNIT_TEST( testData );
  CPPUNIT_TEST( testInsertNode );
  CPPUNIT_TEST_EXCEPTION( testInsertLSiblingThrow, qgar::QgarErrorUser );
  CPPUNIT_TEST_EXCEPTION( testInsertRSiblingThrow, qgar::QgarErrorUser );
  CPPUNIT_TEST( testCopyConstructor );
  CPPUNIT_TEST( testAssignment );
  CPPUNIT_TEST( testBuildFromNode );
  CPPUNIT_TEST( testMergeLSibling );
  CPPUNIT_TEST_EXCEPTION( testMergeLSiblingThrow, qgar::QgarErrorUser );
  CPPUNIT_TEST( testMergeRSibling );
  CPPUNIT_TEST_EXCEPTION( testMergeRSiblingThrow, qgar::QgarErrorUser );
  CPPUNIT_TEST( testMergeFirstChild );
  CPPUNIT_TEST( testRemove );

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


/** @name Test functions for a node */
//        =========================
//@{
/**
 * @brief Tests
 * qgar::GenTreeNode::data,
 * qgar::GenTreeNode::accessData,
 * qgar::GenTreeNode::setData.
 *
 * Performed Tests:
 * - can set data to node
 * - correct access to data stored in node
 * - data is effectively copied when using function data()
 */
  void testNodeData();
//@}


/** @name Test functions for a tree */
//        =========================
//@{

// =======
// NO TEST
// =======

/**
 * @brief Tests qgar::GenTree::empty()
 *
 * Performed Tests:
 * - none : The function is assumed to be correct!
 */
  void testEmpty();

/**
 * @brief Tests qgar::GenTree::pRoot()
 *
 * Performed Tests:
 * - none : The function is assumed to be correct!
 */
  void testPRoot();

/**
 * @brief Tests qgar::GenTree::pCurrent()
 *
 * Performed Tests:
 * - none : The function is assumed to be correct!
 */
  void testPCurrent();

/**
 * @brief Tests qgar::GenTree::pParent()
 *
 * Performed Tests:
 * - none : The function is assumed to be correct!
 */
  void testPParent();

/**
 * @brief Tests qgar::GenTree::pLSibling()
 *
 * Performed Tests:
 * - none : The function is assumed to be correct!
 */
  void testPLSibling();

/**
 * @brief Tests qgar::GenTree::pRSibling()
 *
 * Performed Tests:
 * - none : The function is assumed to be correct!
 */
  void testPRSibling();

/**
 * @brief Tests qgar::GenTree::pFirstChild()
 *
 * Performed Tests:
 * - none : The function is assumed to be correct!
 */
  void testPFirstChild();

/**
 * @brief Tests qgar::GenTree::pRoot()
 *
 * Performed Tests:
 * - none : The function is assumed to be correct!
 */
  void testSetPRoot();

/**
 * @brief Tests qgar::GenTree::pCurrent()
 *
 * Performed Tests:
 * - none : The function is assumed to be correct!
 */
  void testSetPCurrent();

/**
 * @brief Tests qgar::GenTree::pParent()
 *
 * Performed Tests:
 * - none : The function is assumed to be correct!
 */
  void testSetPParent();

/**
 * @brief Tests qgar::GenTree::pLSibling()
 *
 * Performed Tests:
 * - none : The function is assumed to be correct!
 */
  void testSetPLSibling();

/**
 * @brief Tests qgar::GenTree::pRSibling()
 *
 * Performed Tests:
 * - none : The function is assumed to be correct!
 */
  void testSetPRSibling();

/**
 * @brief Tests qgar::GenTree::pFirstChild()
 *
 * Performed Tests:
 * - none : The function is assumed to be correct!
 */
  void testSetPFirstChild();

/**
 * @brief Tests qgar::GenTree::gotoRoot()
 *
 * Performed Tests:
 * - none : The function is assumed to be correct!
 */
  void testGotoRoot();

/**
 * @brief Tests qgar::GenTree::gotoParent()
 *
 * Performed Tests:
 * - none : The function is assumed to be correct!
 */
  void testGotoParent();

/**
 * @brief Tests qgar::GenTree::gotoLSibling()
 *
 * Performed Tests:
 * - none : The function is assumed to be correct!
 */
  void testGotoLSibling();

/**
 * @brief Tests qgar::GenTree::gotoRSibling()
 *
 * Performed Tests:
 * - none : The function is assumed to be correct!
 */
  void testGotoRSibling();

/**
 * @brief Tests qgar::GenTree::gotoFirstChild()
 *
 * Performed Tests:
 * - none : The function is assumed to be correct!
 */
  void testGotoFirstChild();

// ===============
// EFFECTIVE TESTS
// ===============

/**
 * @brief Tests qgar::GenTree::GenTree()
 *
 * Performed Checks:
 * - pointers to root and current node are equal to <b>0</b>
 */
  void testDefaultConstructor();

/**
 * @brief Tests qgar::GenTree::GenTree(const T&)
 *
 * Performed Tests:
 * - tree includes a single node
 * - pointers to root and current node are correctly initialized
 * - given data is stored in current node, which is root
 */
  void testBuildFromData();

/**
 * @brief Tests:
 * qgar::GenTree::accessData,
 * qgar::GenTree::data,
 * qgar::GenTree::setData.
 *
 * Performed Tests:
 * - can set data to node
 * - correct access to data stored in node
 * - data is effectively copied when using function data()
 */
  void testData();

/**
 * @brief Tests:
 * qgar::GenTree::insertParent,
 * qgar::GenTree::insertLSibling,
 * qgar::GenTree::insertRSibling,
 * qgar::GenTree::insertFirstChild.
 *
 * Performed Tests:
 * - construct a test tree using the enumerated functions
 */
  void testInsertNode();

/**
 * @brief Tests qgar::GenTree::insertLSibling
 *
 * Performed Tests:
 * - throw a user exception when providing a sibling to root
 */
  void testInsertLSiblingThrow();

/**
 * @brief Tests qgar::GenTree::insertRSibling
 *
 * Performed Tests:
 * - throw a user exception when providing a sibling to root
 */
  void testInsertRSiblingThrow();

/**
 * @brief Tests qgar::GenTree::GenTree(const GenTree<T>&)
 *
 * Performed Checks:
 * - construct a tree, duplicate it using copy-construction,
 *   and then check deep copy (the two trees are identical
 *   and do not share any node)
 */
  void testCopyConstructor();

/**
 * @brief Tests qgar::GenTree::operator=(const GenTree<T>&)
 *
 * Performed Checks:
 * - same as function testCopyConstructor()
 */
  void testAssignment();

/**
 * @brief Tests qgar::GenTree::GenTree(GenTreeNode<T>*)
 *
 * Performed Checks:
 * - construct a tree from a (sub)tree whose root is given node
 * - check that resulting tree and given (sub)tree do not share
 *   any node
 */
  void testBuildFromNode();

/**
 * @brief Tests qgar::GenTree::mergeLSibling(const Gentree<T>&)
 *
 * Performed Tests:
 * - merging an empty tree has no effect
 * - merges are correctly performed
 * - tree is copied before being merged
 */
  void testMergeLSibling();

/**
 * @brief Tests qgar::GenTree::mergeLSibling(const Gentree<T>&)
 *
 * Performed Tests:
 * - throw a user exception when providing sibling to root
 */
  void testMergeLSiblingThrow();

/**
 * @brief Tests qgar::GenTree::mergeRSibling(const Gentree<T>&)
 *
 * Performed Tests:
 * - merging an empty tree has no effect
 * - merges are correctly performed
 * - tree is copied before being merged
 */
  void testMergeRSibling();

/**
 * @brief Tests qgar::GenTree::mergeRSibling(const Gentree<T>&)
 *
 * Performed Tests:
 * - throw a user exception when providing sibling to root
 */
  void testMergeRSiblingThrow();

/**
 * @brief Tests qgar::GenTree::mergeFirstChild(const Gentree<T>&)
 *
 * Performed Tests:
 * - merging an empty tree has no effect
 * - merges are correctly performed
 * - tree is copied before being merged
 */
  void testMergeFirstChild();

/**
 * @brief Tests remove()
 *
 * Performed Tests:
 * - remove from an empty tree has no effect
 * - removals are correctly performed
 * - removed parts are not deleted
 */
  void testRemove();
//@}

// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

/** @name Tree construction */
//        =================
//@{
/**
 * @brief Construct the test tree.
 */
  void constructTree();
//@}

/** @name Tree search */
//        ===========
//@{
/**
 * @brief Breadth-first search.
 * @param aPRoot   pointer to the root node of the tree to be searched.
 * @param aVNodes  vector including the information associated with the
 *                 visited nodes, in the order they have been visited
 */
  void breadthFirst(GenTreeNode<int>* aPRoot, vector<int>& aVNode);

/**
 * @brief Depth-first search.
 * @param aPRoot  pointer to the root node of the tree to be searched.
 * @param aVNodes  vector including the information associated with the
 *                 visited nodes, in the order they have been visited
 */
  void depthFirst(GenTreeNode<int>* aPRoot, vector<int>& aVNode);
//@}


// -------------------------------------------------------------------
}; // class GenTreeTest


#endif /* __GENTREETEST_H_INCLUDED__ */
