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


#ifndef __GENEDGEGENNODETEST_H_INCLUDED__
#define __GENEDGEGENNODETEST_H_INCLUDED__


/**
 * @file   GenEdgeGenNodeTest.h
 * @brief  Header file of class GenEdgeGenNodeTest.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   September 17, 2004  16:52
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete.
/* $Id: GenEdgeGenNodeTest.h,v 1.2 2004/10/05 16:18:04 masini Exp $ */


#include <cppunit/extensions/HelperMacros.h>


/**
 * @class GenEdgeGenNodeTest GenEdgeGenNodeTest.h
 * @brief Test class for classes qgar::GenEdge and qgar::GenNode.
 * 
 * Untested function members of class qgar::GenEdge:
 *
 * - qgar::GenEdge<TNODE,TEDGE>::accessData()
 * - qgar::GenEdge<TNODE,TEDGE>::data() 
 * - qgar::GenEdge<TNODE,TEDGE>::flag()
 * - qgar::GenEdge<TNODE,TEDGE>::pSource()
 * - qgar::GenEdge<TNODE,TEDGE>::pTarget()
 *
 * 
 * Untested function members of class qgar::GenNode:
 *
 * - qgar::GenNode<TNODE,TEDGE>::accessData()
 * - qgar::GenNode<TNODE,TEDGE>::data()
 * - qgar::GenNode<TNODE,TEDGE>::flag()
 * - qgar::GenNode<TNODE,TEDGE>::accessEdges()
 *
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   September 17, 2004  16:52
 * @since  Qgar 2.1.1
 */
class GenEdgeGenNodeTest

  : public CppUnit::TestFixture

{
// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( GenEdgeGenNodeTest );

  // Class qgar::GenEdge

  CPPUNIT_TEST( testEdgeConstructors );
  CPPUNIT_TEST( testEdgeSet );
  CPPUNIT_TEST( testEdgeSourceTarget );
  CPPUNIT_TEST( testEdgeOperators );

  // Class qgar::GenNode

  CPPUNIT_TEST( testNodeConstructors );
  CPPUNIT_TEST( testNodeSet );
  CPPUNIT_TEST( testNodeSetEdgesList );
  CPPUNIT_TEST( testNodeAccessEdgesList );
  CPPUNIT_TEST( testNodeOperators );

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


/** @name Functions to test edges */
//        =======================
//@{

/**
 * @brief Tests all constructors of class qgar::GenEdge.
 *
 * Performed checks:
 * - default constructor 
 * - copy-constructor 
 * - constructor from data and flag
 * - constructor from data, flag, source and target
 */
  void testEdgeConstructors();

/**
 * @brief Tests transformation functions.
 *
 * Performed checks:
 * - set edge data
 * - set edge flag
 * - set (pointer to) source node
 * - set (pointer to the) target node
 * - set (pointer to the) source node or target node
 */
  void testEdgeSet();

/**
 * @brief Tests access to edge source and target.
 *
 * Performed Tests:
 * - get source node
 * - get a copy of source node
 * - get target node
 * - get a copy of target node
 */
void testEdgeSourceTarget();

/**
 * @brief Tests operators on edges.
 *
 * Performed Tests:
 * - assignment
 * - equality and inequality
 */
void testEdgeOperators();

//@}


/** @name Functions to test nodes */
//        =======================
//@{

/**
 * @brief Tests all constructors of class qgar::GenNode.
 *
 * Performed Checks:
 * - default constructor 
 * - copy-constructor 
 * - constructor from data and flag
 * - constructor from data, flag, and pointers to edges
 */
  void testNodeConstructors();

/**
 * @brief Tests transformation functions.
 *
 * Performed checks:
 * - set node data
 * - set node flag
 */
void testNodeSet();

/**
 * @brief Tests edge insertions and removals.
 *
 * Performed Tests:
 * - add (a pointer to) an edge at front and back of the edges list
 * - remove an edge at given position in the edges list
 * - remove a pointer to an edge in the edges list
 */
void testNodeSetEdgesList();

/**
 * @brief Tests access to edges list.
 *
 * Performed Tests:
 * - get edges list
 * - get a copy of edges list
 */
void testNodeAccessEdgesList();

/**
 * @brief Tests operators on nodes.
 *
 * Performed Tests:
 * - assignment
 * - equality and inequality
 */
void testNodeOperators();

//@}


// -------------------------------------------------------------------
}; // class GenEdgeGenNodeTest


#endif /* __GENEDGEGENNODETEST_H_INCLUDED__ */
