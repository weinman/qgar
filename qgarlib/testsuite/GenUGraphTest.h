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


#ifndef __GENUGRAPHTEST_H_INCLUDED__
#define __GENUGRAPHTEST_H_INCLUDED__


/**
 * @file   GenUGraphTest.h
 * @brief  Header file of class GenUGraphTest.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   September 21, 2004  16:47
 * @since  Qgar 2.1.2
 */


// For RCS/CVS use: Do not delete.
/* $Id: GenUGraphTest.h,v 1.2 2005/01/28 15:56:46 masini Exp $ */



// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>



/**
 * @class GenUGraphTest GenUGraphTest.h
 * @brief Test class for class qgar::GenUGraph.
 * 
 * Untested function members:
 * - qgar::GenUGraph::accessEdges()
 * - qgar::GenUGraph::accessNodes()
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   September 21, 2004  16:47
 * @since  Qgar 2.1.2
 */
class GenUGraphTest

  : public CppUnit::TestFixture

{
// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( GenUGraphTest );

  // Constructors
  // ------------
  CPPUNIT_TEST( testConstructors );

  // Operations on nodes
  // -------------------
  CPPUNIT_TEST( testJustAddNode );
  CPPUNIT_TEST( testAddNodeToAnEdge );
  CPPUNIT_TEST( testAddNodeBetween2Edges );
  CPPUNIT_TEST( testAddNodeSourceAndTarget );

  // Operations on edges
  // -------------------
  CPPUNIT_TEST( testJustAddEdge );
  CPPUNIT_TEST( testAddEdgeToANode );
  CPPUNIT_TEST( testAddEdgeBetween2Nodes );
  CPPUNIT_TEST( testAddEdgeSourceAndTarget );

  // Graph global features
  // ---------------------
  CPPUNIT_TEST( testGraphFeatures );

  // Removals
  // --------
  CPPUNIT_TEST( testRemoveNode );
  CPPUNIT_TEST( testRemoveEdge );

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


/** @name Tests of constructors */
//        =====================
//@{

/**
 * @brief Tests all constructors.
 *
 * Performed tests:
 * - default constructor
 * - constructor from a pointer to a node
 * - constructor from a pointer to an edge
 */
  void testConstructors();
  
//@}


/** @name Tests of operations on nodes */
//        ============================
//@{

/**
 * @brief Tests
 * qgar::GenUGraph<TNODE,TEDGE>::addNode(const TNODE&, short int),
 * qgar::GenUGraph<TNODE,TEDGE>::addNode(GenNode<TNODE,TEDGE>* const).
 *
 * Performed tests:
 * - just insert a node created from given data and flag in the graph
 * - just insert (a pointer to) a node in the graph
 */
void testJustAddNode();

/**
 * @brief Tests
 * qgar::GenUGraph<TNODE,TEDGE>::addNode(GenEdge<TNODE,TEDGE>* const, const TNODE&, short int),
 * qgar::GenUGraph<TNODE,TEDGE>::addNode(GenEdge<TNODE,TEDGE>* const, const TNODE&, short int aFlag).
 *
 * Performed tests:
 * - insert a node created from given data and flag so that it is adjacent to
 *   the given edge
 * - insert (a pointer to) a node so that it is adjacent to the given edge
 */
void testAddNodeToAnEdge();

/**
 * @brief Tests
 * qgar::GenUGraph<TNODE,TEDGE>::addNode(GenEdge<TNODE,TEDGE>* const, GenEdge<TNODE,TEDGE>* const, const TNODE&, short int),
 * qgar::GenUGraph<TNODE,TEDGE>::addNode(GenNode<TNODE,TEDGE>* const, GenEdge<TNODE,TEDGE>* const, GenEdge<TNODE,TEDGE>* const).
 *
 * Performed tests:
 * - insert a node created from given data and flag
 *   between two edges of the graph
 * - insert (a pointer to) a node between two edges of the graph
 */
void testAddNodeBetween2Edges();

/**
 * @brief Tests qgar::GenUGraph<TNODE,TEDGE>::addNodeAtSource
 * and qgar::GenUGraph<TNODE,TEDGE>::addNodeAtTarget.
 *
 * Performed tests:
 * - insert a node in the graph, as source
 *   of a given (pointer to an) edge
 * - insert a node in the graph, as target
 *   of a given (pointer to an) edge
 */
void testAddNodeSourceAndTarget();

  //@}


/** @name Tests of operations on edges */
//        ============================
//@{

/**
 * @brief Tests
 * qgar::GenUGraph<TNODE,TEDGE>::addEdge(const TEDGE&, short int),
 * qgar::GenUGraph<TNODE,TEDGE>::addEdge(GenEdge<TNODE,TEDGE>* const).
 *
 * Performed tests:
 * - just insert an edge created from data and flag in the graph
 * - just insert (a pointer to) an edge in the graph
 */
void testJustAddEdge();

/**
 * @brief Tests
 * qgar::GenUGraph<TNODE,TEDGE>::addEdge(GenNode<TNODE,TEDGE>* const, const TEDGE&, short int),
 *  qgar::GenUGraph<TNODE,TEDGE>::addEdge(const TEDGE&, GenNode<TNODE,TEDGE>* const, GenNode<TNODE,TEDGE>* const, short int).
 *
 * Performed tests:
 * - insert a new edge so as the edge is adjacent
 *   to a node of the graph
 * - insert (a pointer to) an edge so as the edge
 *   is adjacent to a node of the graph
 */
void testAddEdgeToANode();

/**
 * @brief Tests
 * qgar::GenUGraph<TNODE,TEDGE>::addEdge(GenEdge<TNODE,TEDGE>* const, GenNode<TNODE,TEDGE>* const),
 * qgar::GenUGraph<TNODE,TEDGE>::addEdge(GenNode<TNODE,TEDGE>* const, GenNode<TNODE,TEDGE>* const, const TEDGE&, short int).
 *
 * Performed Tests:
 * - insert a new edge between 2 nodes of the graph
 * - insert (a pointer to) an edge between 2 nodes of the graph
 */
void testAddEdgeBetween2Nodes();

/**
 * @brief Tests qgar::GenUGraph<TNODE,TEDGE>::addEdgeBySource
 * and qgar::GenUGraph<TNODE,TEDGE>::addEdgeByTarget.
 *
 * Performed tests:
 * - Insert given (pointer to) edge in the graph,
 *   so as given (pointed) node becomes its source
 * - Insert given (pointer to) edge in the graph,
 *   so as given (pointed) node becomes its target
 */
void testAddEdgeSourceAndTarget();

//@}


/** @name Tests of graph features */
//        =======================
//@{

/**
 * @brief Tests
 *  qgar::GenUGraph<TNODE,TEDGE>::empty,
 *  qgar::GenUGraph<TNODE,TEDGE>::sizeNodes,
 *  qgar::GenUGraph<TNODE,TEDGE>::pEntryNode,
 *  qgar::GenUGraph<TNODE,TEDGE>::getNodes,
 *  qgar::GenUGraph<TNODE,TEDGE>::nodes,
 *  qgar::GenUGraph<TNODE,TEDGE>::sizeEdges,
 *  qgar::GenUGraph<TNODE,TEDGE>::pEntryEdge,
 *  qgar::GenUGraph<TNODE,TEDGE>::getEdges,
 *  qgar::GenUGraph<TNODE,TEDGE>::edges.
 *
 * Performed tests:
 * - Construction of a graph
 * - Is the new graph empty?
 * - Get size, in nodes and edges, of the new graph
 * - Get entry node and edge of the graph
 * - Access to nodes and edges lists of the graph
 */
  void testGraphFeatures();
  
//@}


/** @name Tests of removals */
//        =================
//@{

/**
 * @brief Tests
 *   qgar::GenUGraph<TNODE,TEDGE>::remove(GenNode<TNODE,TEDGE>* const)
 * and qgar::GenUGraph<TNODE,TEDGE>::remove(typename std::list< GenNode<TNODE,TEDGE>* >::iterator).
 *
 * Performed tests:
 * - remove a pointed node
 * - remove a node at a given position in the nodes list
 */
void testRemoveNode();

/**
 * @brief Tests
 *   qgar::GenUGraph<TNODE,TEDGE>::remove(GenEdge<TNODE,TEDGE>* const)
 * and qgar::GenUGraph<TNODE,TEDGE>::remove(typename std::list< GenEdge<TNODE,TEDGE>* >::iterator).
 *
 * Performed tests:
 * - remove a pointed edge
 * - remove an edge at a given position in the nodes list
 */
void testRemoveEdge();

  //@}


// -------------------------------------------------------------------
}; // class GenUGraphTest


#endif /* __GENUGRAPHTEST_H_INCLUDED__ */
