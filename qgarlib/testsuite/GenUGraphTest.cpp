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


/**
 * @file  GenUGraphTest.cpp
 * @brief Implementation of class qgar::GenUGraphTest.
 *
 * See file GenUGraphTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   September 21, 2004  16:47
 * @since  Qgar 2.1.1
 */



// STD
#include <list>
// QGAR
#include <qgarlib/GenEdge.h>
#include <qgarlib/GenNode.h>
#include <qgarlib/GenUGraph.h>
// QGAR TESTS
#include "GenUGraphTest.h"



using namespace qgar;
using namespace std;



// ------------------------------------------------------------------
// T E S T F I X T U R E   I M P L
// ------------------------------------------------------------------


void
GenUGraphTest::setUp()
{
  /* EMPTY */
}


void
GenUGraphTest::tearDown()
{
  /* EMPTY */
}


// -------------------------------------------------------------------
// T E S T   F U N C T I O N S
// -------------------------------------------------------------------


// ============
// ============
// CONSTRUCTORS
// ============
// ============


void
GenUGraphTest::testConstructors()
{

  // DEFAULT CONSTRUCTOR
  // -------------------

  GenUGraph<int,double> g;

  CPPUNIT_ASSERT( (g.accessEdges()).empty() );
  CPPUNIT_ASSERT( (g.accessNodes()).empty() );

  // CONSTRUCTOR FROM A POINTER TO AN EDGE
  // -------------------------------------

  GenEdge<int,double>* pe1 = new GenEdge<int,double>(1,10);
  GenUGraph<int,double> ge(pe1);

  const list<GenEdge<int,double>*>& le = ge.accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le.size(), 1 );

  GenEdge<int,double>* pe = le.front();
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe->data(), 1., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe->flag(), 10 );
  CPPUNIT_ASSERT( pe->pSource() == 0 );
  CPPUNIT_ASSERT( pe->pTarget() == 0 );

  CPPUNIT_ASSERT( (ge.accessNodes()).empty() );

  // CONSTRUCTOR FROM A POINTER TO A NODE
  // ------------------------------------

  GenNode<int,double>* pn1 = new GenNode<int,double>(1,10);
  GenUGraph<int,double> gn(pn1);

  const list<GenNode<int,double>*>& ln = gn.accessNodes();
  CPPUNIT_ASSERT_EQUAL( (int)ln.size(), 1 );

  GenNode<int,double>* pn = ln.front();
  CPPUNIT_ASSERT_EQUAL( pn->data(),      1 );
  CPPUNIT_ASSERT_EQUAL( (int)pn->flag(), 10 );
  CPPUNIT_ASSERT( (pn->accessEdges()).empty() );

  CPPUNIT_ASSERT( (gn.accessEdges()).empty() );
}


// ===================
// ===================
// INSERTIONS OF NODES
// ===================
// ===================


void
GenUGraphTest::testJustAddNode()
{
  // ************************
  // INSERT POINTERS TO NODES
  // ************************

  GenUGraph<int,double> g1;

  // INSERT A NODE
  // --------------

  GenNode<int,double>* pn1 = new GenNode<int,double>(1,10);
  GenNode<int,double>* pn = g1.addNode(pn1);

  const list<GenNode<int,double>*>& ln1 = g1.accessNodes();
  CPPUNIT_ASSERT_EQUAL( (int)ln1.size(), 1 );

  // NODES LIST OF THE GRAPH

  CPPUNIT_ASSERT( pn == pn1 );
  CPPUNIT_ASSERT( pn == ln1.front() );
  CPPUNIT_ASSERT_EQUAL( pn->data(),      1 );
  CPPUNIT_ASSERT_EQUAL( (int)pn->flag(), 10 );
  CPPUNIT_ASSERT( (pn->accessEdges()).empty() );

  // EDGES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g1.accessEdges()).empty() );

  // INSERT A SECOND NODE
  // --------------------

  GenNode<int,double>* pn2 = new GenNode<int,double>(2,20);
  pn = g1.addNode(pn2);

  const list<GenNode<int,double>*>& ln2 = g1.accessNodes();
  CPPUNIT_ASSERT_EQUAL( (int)ln2.size(), 2 );

  // FIRST NODE OF THE NODES LIST OF THE GRAPH

  GenNode<int,double>* ppn = ln2.front();
  CPPUNIT_ASSERT( ppn == pn1 );
  CPPUNIT_ASSERT_EQUAL( ppn->data(),      1 );
  CPPUNIT_ASSERT_EQUAL( (int)ppn->flag(), 10 );
  CPPUNIT_ASSERT( (ppn->accessEdges()).empty() );

  // SECOND NODE OF THE NODES LIST OF THE GRAPH

  CPPUNIT_ASSERT( pn == ln2.back() );
  CPPUNIT_ASSERT( pn == pn2 );
  CPPUNIT_ASSERT_EQUAL( pn->data(),      2 );
  CPPUNIT_ASSERT_EQUAL( (int)pn->flag(), 20 );
  CPPUNIT_ASSERT( (pn->accessEdges()).empty() );

  // EDGES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g1.accessEdges()).empty() );


  // ********************
  // INSERT CREATED NODES
  // ********************

  GenUGraph<int,double> g10;

  // INSERT A NODE
  // --------------

  pn = g10.addNode(1,10);

  const list<GenNode<int,double>*>& ln10 = g10.accessNodes();
  CPPUNIT_ASSERT_EQUAL( (int)ln10.size(), 1 );

  // NODES LIST OF THE GRAPH

  CPPUNIT_ASSERT( pn == ln10.front() );
  CPPUNIT_ASSERT_EQUAL( pn->data(),      1 );
  CPPUNIT_ASSERT_EQUAL( (int)pn->flag(), 10 );
  CPPUNIT_ASSERT( (pn->accessEdges()).empty() );

  // EDGES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g10.accessEdges()).empty() );

  // INSERT A SECOND NODE
  // --------------------

  pn = g10.addNode(2,20);

  const list<GenNode<int,double>*>& ln20 = g10.accessNodes();
  CPPUNIT_ASSERT_EQUAL( (int)ln20.size(), 2 );

  // FIRST NODE OF THE NODES LIST OF THE GRAPH

  ppn = ln20.front();
  CPPUNIT_ASSERT_EQUAL( ppn->data(),      1 );
  CPPUNIT_ASSERT_EQUAL( (int)ppn->flag(), 10 );
  CPPUNIT_ASSERT( (ppn->accessEdges()).empty() );

  // SECOND NODE OF THE NODES LIST OF THE GRAPH

  CPPUNIT_ASSERT( pn == ln20.back() );
  CPPUNIT_ASSERT_EQUAL( pn->data(),      2 );
  CPPUNIT_ASSERT_EQUAL( (int)pn->flag(), 20 );
  CPPUNIT_ASSERT( (pn->accessEdges()).empty() );

  // EDGES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g10.accessEdges()).empty() );
}



void
GenUGraphTest::testAddNodeToAnEdge()
{
  //             e1
  //     n1 S----------T n2
  //
  //             e2
  //         ----------T n2
  //
  //             e3
  //     n1 S----------
  //
  //             e20
  //     n2 S----------

  GenNode<int,double>* pn1 = new GenNode<int,double>(1,10);

  GenEdge<int,double>* pe20 = new GenEdge<int,double>(20.,200);
  GenNode<int,double>* pn2  = new GenNode<int,double>(pe20, 2, 20);

  GenNode<int,double>* pn3 = new GenNode<int,double>(3,30);

  GenEdge<int,double>* pe1 = new GenEdge<int,double>(pn1, pn2, 1., 10);
  GenEdge<int,double>* pe2 = new GenEdge<int,double>(  0, pn2, 2., 20);
  GenEdge<int,double>* pe3 = new GenEdge<int,double>(pn1,   0, 3., 30);
  

  // **************************
  // INSERT A POINTER TO A NODE
  // **************************

  GenUGraph<int,double> g;

  // INSERT NODE n1 AS TARGET OF EDGE e1
  // -----------------------------------
  //
  //             e1
  //     n1 S----------T n1
  //
  //             e2
  //         ----------T n2
  //
  //             e3
  //     n1 S----------
  //
  //             e20
  //     n2 S----------

  GenNode<int,double>* pcn = g.addNode(pn1, pe1);

  // EDGES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g.accessEdges()).empty() );

  // NODES LIST OF THE GRAPH

  const list<GenNode<int,double>*>& ln1 = g.accessNodes();
  CPPUNIT_ASSERT_EQUAL( (int)ln1.size(), 1 );

  // INSERTED NODE

  CPPUNIT_ASSERT( pcn == ln1.front() );
  CPPUNIT_ASSERT( pcn == pn1 );
  CPPUNIT_ASSERT_EQUAL( pcn->data(),      1 );
  CPPUNIT_ASSERT_EQUAL( (int)pcn->flag(), 10 );

  // Edges list of the inserted node contains e1

  const list<GenEdge<int,double>*>& le1 = pcn->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le1.size(), 1 );
  CPPUNIT_ASSERT( le1.front() == pe1 );

  // NODE n1 IS THE NEW TARGET OF EDGE e1

  CPPUNIT_ASSERT( pe1->pSource() == pn1 );
  CPPUNIT_ASSERT( pe1->pTarget() == pn1 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe1->data(), 1., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe1->flag(), 10 );

  // INSERT NODE n2 AS SOURCE OF EDGE e2
  // -----------------------------------
  //
  //             e1
  //     n1 S----------T n1
  //
  //             e2
  //     n2 S----------T n2
  //
  //             e3
  //     n1 S----------
  //
  //             e20
  //     n2 S----------

  pcn = g.addNode(pn2, pe2);
  CPPUNIT_ASSERT( pcn == pn2 );

  // EDGES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g.accessEdges()).empty() );

  // NODES LIST OF THE GRAPH

  const list<GenNode<int,double>*>& ln2 = g.accessNodes();
  CPPUNIT_ASSERT_EQUAL( (int)ln2.size(), 2 );

  // PREVIOUSLY INSERTED NODE

  CPPUNIT_ASSERT( ln2.front() == pn1 );
  CPPUNIT_ASSERT_EQUAL( pn1->data(),      1 );
  CPPUNIT_ASSERT_EQUAL( (int)pn1->flag(), 10 );

  // Edges list of the previously inserted node contains e1

  const list<GenEdge<int,double>*>& le20 = pn1->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le20.size(), 1 );
  CPPUNIT_ASSERT( le20.front() == pe1 );

  // NEWLY INSERTED NODE n2

  CPPUNIT_ASSERT( ln2.back() == pn2 );
  CPPUNIT_ASSERT_EQUAL( pn2->data(),      2 );
  CPPUNIT_ASSERT_EQUAL( (int)pn2->flag(), 20 );

  // Edges list of the newly inserted node contains pe20 & pe2 

  const list<GenEdge<int,double>*>& le21 = pn2->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le21.size(), 2 );
  CPPUNIT_ASSERT( le21.front() == pe20 );
  CPPUNIT_ASSERT( le21.back()  == pe2  );

  // NODE pn2 IS THE NEW SOURCE OF EDGE pe2

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe2->data(), 2., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe2->flag(), 20 );
  CPPUNIT_ASSERT( pe2->pSource() == pn2 );
  CPPUNIT_ASSERT( pe2->pTarget() == pn2 );

  // INSERT NODE n3 AS TARGET OF EDGE e3
  // -----------------------------------
  //
  //             e1
  //     n1 S----------T n1
  //
  //             e2
  //     n2 S----------T n2
  //
  //             e3
  //     n1 S----------T n3
  //
  //             e20
  //     n2 S----------

  pcn = g.addNode(pn3, pe3);
  CPPUNIT_ASSERT( pcn == pn3 );

  // EDGES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g.accessEdges()).empty() );

  // NODES LIST OF THE GRAPH

  const list<GenNode<int,double>*>& ln3 = g.accessNodes();
  CPPUNIT_ASSERT_EQUAL( (int)ln3.size(), 3 );

  // FIRSTLY INSERTED NODE pn1

  list<GenNode<int,double>*>::const_iterator itN = ln3.begin();

  CPPUNIT_ASSERT( (*itN) == pn1 );
  CPPUNIT_ASSERT_EQUAL( pn1->data(),      1 );
  CPPUNIT_ASSERT_EQUAL( (int)pn1->flag(), 10 );

  // Edges list of the firstly inserted node contains e1

  const list<GenEdge<int,double>*>& le30 = pn1->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le30.size(), 1 );
  CPPUNIT_ASSERT( le30.front() == pe1 );

  // SECONDLY INSERTED NODE pn2

  ++itN;
  CPPUNIT_ASSERT( (*itN) == pn2 );
  CPPUNIT_ASSERT_EQUAL( pn2->data(),      2 );
  CPPUNIT_ASSERT_EQUAL( (int)pn2->flag(), 20 );

  // Edges list of the secondly inserted node contains pe20 & pe2 

  const list<GenEdge<int,double>*>& le31 = pn2->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le31.size(), 2 );
  CPPUNIT_ASSERT( le31.front() == pe20 );
  CPPUNIT_ASSERT( le31.back()  == pe2  );

  // EDGE pe2

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe2->data(), 2., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe2->flag(), 20 );
  CPPUNIT_ASSERT( pe2->pSource() == pn2 );
  CPPUNIT_ASSERT( pe2->pTarget() == pn2 );

  // NEWLY INSERTED NODE pn3

  ++itN;
  CPPUNIT_ASSERT( (*itN) == pn3 );
  CPPUNIT_ASSERT_EQUAL( pn3->data(),      3 );
  CPPUNIT_ASSERT_EQUAL( (int)pn3->flag(), 30 );

  // Edges list of the newly inserted node contains pe3

  const list<GenEdge<int,double>*>& le32 = pn3->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le32.size(), 1 );
  CPPUNIT_ASSERT( le32.front() == pe3 );

  // NODE pn3 IS THE NEW TARGET OF EDGE pe3

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe3->data(), 3., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe3->flag(), 30 );
  CPPUNIT_ASSERT( pe3->pSource() == pn1 );
  CPPUNIT_ASSERT( pe3->pTarget() == pn3 );


  // *********************
  // INSERT A CREATED NODE
  // *********************
  //
  //             e4
  //     n40 S----------T n41
  //
  //             e5
  //          ----------T n51

  GenNode<int,double>* pn40 = new GenNode<int,double>(40,400);
  GenNode<int,double>* pn41 = new GenNode<int,double>(41,401);
  GenNode<int,double>* pn51 = new GenNode<int,double>(51,501);

  GenEdge<int,double>* pe4 = new GenEdge<int,double>(pn40, pn41, 4., 40);
  GenEdge<int,double>* pe5 = new GenEdge<int,double>(   0, pn51, 5., 50);
  
  GenUGraph<int,double> g1;

  // INSERT NODE n410 AS TARGET OF EDGE e4
  // -------------------------------------
  //
  //              e4
  //     n40 S----------T n410
  //
  //              e5
  //          ----------T n51

  GenNode<int,double>* pcn410 = g1.addNode(pe4, 410, 4100);

  // EDGES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g1.accessEdges()).empty() );

  // NODES LIST OF THE GRAPH

  const list<GenNode<int,double>*>& ln10 = g1.accessNodes();
  CPPUNIT_ASSERT_EQUAL( (int)ln10.size(), 1 );

  // INSERTED NODE

  CPPUNIT_ASSERT( pcn410 == ln10.front() );
  CPPUNIT_ASSERT_EQUAL( pcn410->data(),      410 );
  CPPUNIT_ASSERT_EQUAL( (int)pcn410->flag(), 4100 );

  // Edges list of node n410 contains e4

  const list<GenEdge<int,double>*>& le10 = pcn410->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le10.size(), 1 );
  CPPUNIT_ASSERT( le10.front() == pe4 );

  // NODE n410 IS THE NEW TARGET OF EDGE e4

  CPPUNIT_ASSERT( pe4->pSource() == pn40 );
  CPPUNIT_ASSERT( pe4->pTarget() == pcn410 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe4->data(), 4., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe4->flag(), 40 );

  // INSERT NODE n50 AS SOURCE OF EDGE e5
  // ------------------------------------
  //
  //              e4
  //     n40 S----------T n410
  //
  //              e5
  //     n50 S----------T n51

  GenNode<int,double>* pcn50 = g1.addNode(pe5, 50, 500);

  // EDGES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g1.accessEdges()).empty() );

  // NODES LIST OF THE GRAPH

  const list<GenNode<int,double>*>& ln20 = g1.accessNodes();
  CPPUNIT_ASSERT_EQUAL( (int)ln20.size(), 2 );

  // PREVIOUSLY INSERTED NODE

  CPPUNIT_ASSERT( ln20.front() == pcn410 );
  CPPUNIT_ASSERT_EQUAL( pcn410->data(), 410 );
  CPPUNIT_ASSERT_EQUAL( (int)pcn410->flag(), 4100 );

  // Edges list of the previously inserted node contains e4

  const list<GenEdge<int,double>*>& le200 = pcn410->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le200.size(), 1 );
  CPPUNIT_ASSERT( le200.front() == pe4 );

  // NEWLY INSERTED NODE n50

  CPPUNIT_ASSERT( ln20.back() == pcn50 );
  CPPUNIT_ASSERT_EQUAL( pcn50->data(),      50 );
  CPPUNIT_ASSERT_EQUAL( (int)pcn50->flag(), 500 );

  // Edges list of the newly inserted node contains e5

  const list<GenEdge<int,double>*>& le210 = pcn50->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le210.size(), 1 );
  CPPUNIT_ASSERT( le210.front() == pe5 );

  // NODE n500 IS THE NEW SOURCE OF EDGE e5

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe5->data(), 5., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe5->flag(), 50 );
  CPPUNIT_ASSERT( pe5->pSource() == pcn50 );
  CPPUNIT_ASSERT( pe5->pTarget() == pn51 );

  //
  //             e6
  //         ---------
  //

  GenEdge<int,double>* pe6 = new GenEdge<int,double>(6., 60);
  GenUGraph<int,double> g2;

  // INSERT NODE n61 AS TARGET OF EDGE e6
  // ------------------------------------
  //
  //             e6
  //         ---------T n61
  //

  GenNode<int,double>* pcn61 = g2.addNodeAtTarget(pe6, 61, 610);

  // EDGES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g2.accessEdges()).empty() );

  // NODES LIST OF THE GRAPH

  const list<GenNode<int,double>*>& ln210 = g2.accessNodes();
  CPPUNIT_ASSERT_EQUAL( (int)ln210.size(), 1 );

  // INSERTED NODE

  CPPUNIT_ASSERT( pcn61 == ln210.front() );
  CPPUNIT_ASSERT_EQUAL( pcn61->data(),      61  );
  CPPUNIT_ASSERT_EQUAL( (int)pcn61->flag(), 610 );

  // Edges list of node n61 contains e6

  const list<GenEdge<int,double>*>& le211 = pcn61->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le211.size(), 1 );
  CPPUNIT_ASSERT( le211.front() == pe6 );

  // NODE n61 IS THE NEW TARGET OF EDGE e6

  CPPUNIT_ASSERT( pe6->pSource() == 0 );
  CPPUNIT_ASSERT( pe6->pTarget() == pcn61 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe6->data(), 6., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe6->flag(), 60 );

  // INSERT NODE n60 AS SOURCE OF EDGE e6
  // ------------------------------------
  //
  //              e6
  //     n60 S---------T n61

  GenNode<int,double>* pcn60 = g2.addNodeAtSource(pe6, 60, 600);

  // EDGES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g2.accessEdges()).empty() );

  // NODES LIST OF THE GRAPH

  const list<GenNode<int,double>*>& ln310 = g2.accessNodes();
  CPPUNIT_ASSERT_EQUAL( (int)ln310.size(), 2 );
  CPPUNIT_ASSERT( pcn61 == ln310.front() );
  CPPUNIT_ASSERT( pcn60 == ln310.back() );

  // INSERTED NODE

  CPPUNIT_ASSERT_EQUAL( pcn60->data(),      60  );
  CPPUNIT_ASSERT_EQUAL( (int)pcn60->flag(), 600 );

  // Edges list of node n61 contains e6

  const list<GenEdge<int,double>*>& le310 = pcn61->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le310.size(), 1 );
  CPPUNIT_ASSERT( le310.front() == pe6 );

  // Edges list of node n60 contains e6

  const list<GenEdge<int,double>*>& le311 = pcn60->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le311.size(), 1 );
  CPPUNIT_ASSERT( le311.front() == pe6 );

  // NODE n60 IS THE NEW SOURCE OF EDGE e6

  CPPUNIT_ASSERT( pe6->pSource() == pcn60 );
  CPPUNIT_ASSERT( pe6->pTarget() == pcn61 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe6->data(), 6., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe6->flag(), 60 );

  // DELETIONS
  // ---------

  delete pe1;
  delete pe20;
  delete pe2;
  delete pe3;
  delete pe4;
  delete pe5;
  delete pe6;

  delete pn40;
  delete pn41;
  delete pn51;
}



void
GenUGraphTest::testAddNodeBetween2Edges()
{
  // *************************************
  // INSERT A CREATED NODE BETWEEN 2 EDGES
  // *************************************

  //              e1
  //     n10 S----------T n11
  //
  //              e2
  //          ----------T n21
  //
  //              e3
  //     n30 S----------

  GenUGraph<int,double> g1;

  GenNode<int,double>* pn10 = new GenNode<int,double>(10, 100);
  GenNode<int,double>* pn11 = new GenNode<int,double>(11, 110);
  GenNode<int,double>* pn21 = new GenNode<int,double>(21, 210);
  GenNode<int,double>* pn30 = new GenNode<int,double>(30, 300);

  GenEdge<int,double>* pe1  = new GenEdge<int,double>(pn10,  pn11, 1.);
  GenEdge<int,double>* pe2  = new GenEdge<int,double>(   0,  pn21, 2.);
  GenEdge<int,double>* pe3  = new GenEdge<int,double>(pn30,     0, 3.);


  // INSERT NODE n1 BEWTEEN e1 AND e2
  // --------------------------------
  //
  //              e1
  //     n10 S----------T n1
  //
  //              e2
  //     n1  S----------T n21
  //
  //              e3
  //     n30 S----------

  GenNode<int,double>* pcn1 = g1.addNode(pe1, pe2, 1, 10);

  // EDGES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g1.accessEdges()).empty() );

  // NODES LIST OF THE GRAPH

  const list<GenNode<int,double>*>& ln1 = g1.accessNodes();
  CPPUNIT_ASSERT_EQUAL( (int)ln1.size(), 1 );
  CPPUNIT_ASSERT( pcn1 == ln1.front() );

  // INSERTED NODE

  CPPUNIT_ASSERT_EQUAL( pcn1->data(),      1 );
  CPPUNIT_ASSERT_EQUAL( (int)pcn1->flag(), 10 );

  // Edges list of the inserted node contains e1 & e2

  const list<GenEdge<int,double>*>& le1 = pcn1->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le1.size(), 2 );
  CPPUNIT_ASSERT( le1.front() == pe1 );
  CPPUNIT_ASSERT( le1.back()  == pe2 );

  // NODE n1 IS THE NEW TARGET OF EDGE e1

  CPPUNIT_ASSERT( pe1->pSource() == pn10 );
  CPPUNIT_ASSERT( pe1->pTarget() == pcn1 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe1->data(), 1., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe1->flag(), 0 );

  // NODE n1 IS THE NEW SOURCE OF EDGE e2

  CPPUNIT_ASSERT( pe2->pSource() == pcn1 );
  CPPUNIT_ASSERT( pe2->pTarget() == pn21 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe2->data(), 2., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe2->flag(), 0 );

  // INSERT NODE n2 BEWTEEN e2 AND e3
  // --------------------------------
  //
  //              e1
  //     n10 S----------T n1
  //
  //              e2
  //     n1  S----------T n2
  //
  //              e3
  //     n30 S----------T n2

  GenNode<int,double>* pcn2 = g1.addNode(pe2, pe3, 2, 20);

  // EDGES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g1.accessEdges()).empty() );

  // NODES LIST OF THE GRAPH

  const list<GenNode<int,double>*>& ln10 = g1.accessNodes();
  CPPUNIT_ASSERT_EQUAL( (int)ln10.size(), 2 );
  CPPUNIT_ASSERT( pcn1 == ln10.front() );
  CPPUNIT_ASSERT( pcn2 == ln10.back() );

  // INSERTED NODE

  CPPUNIT_ASSERT_EQUAL( pcn2->data(),      2 );
  CPPUNIT_ASSERT_EQUAL( (int)pcn2->flag(), 20 );

  // Edges list n2 contains e2 & e3

  const list<GenEdge<int,double>*>& le10 = pcn2->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le10.size(), 2 );
  CPPUNIT_ASSERT( le10.front() == pe2 );
  CPPUNIT_ASSERT( le10.back()  == pe3 );

  // NODE n2 IS THE NEW TARGET OF EDGE e2

  CPPUNIT_ASSERT( pe2->pSource() == pcn1 );
  CPPUNIT_ASSERT( pe2->pTarget() == pcn2  );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe2->data(), 2., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe2->flag(), 0 );

  // NODE n2 IS THE NEW TARGET OF EDGE e3

  CPPUNIT_ASSERT( pe3->pSource() == pn30 );
  CPPUNIT_ASSERT( pe3->pTarget() == pcn2  );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe3->data(), 3., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe3->flag(), 0 );

  // ******************************************
  // INSERT A POINTER TO A NODE BETWEEN 2 EDGES
  // ******************************************
  //
  //              e1
  //     n10 S----------T n1
  //
  //              e2
  //          ----------T n2
  //
  //              e3
  //     n30 S----------

  GenUGraph<int,double> g2;

  GenNode<int,double>* pn3 = new GenNode<int,double>(3, 30);
  GenNode<int,double>* pn4 = new GenNode<int,double>(4, 40);

  pe2->setPSource(0);
  pe3->setPTarget(0);

  // INSERT NODE n3 BEWTEEN e1 AND e2
  // --------------------------------
  //
  //              e1
  //     n10 S----------T n3
  //
  //              e2
  //     n3  S----------T n2
  //
  //              e3
  //     n30 S----------

  GenNode<int,double>* pcn3 = g2.addNode(pn3, pe1, pe2);
  CPPUNIT_ASSERT( pcn3 == pn3 );

  // EDGES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g2.accessEdges()).empty() );

  // NODES LIST OF THE GRAPH

  const list<GenNode<int,double>*>& ln100 = g2.accessNodes();
  CPPUNIT_ASSERT_EQUAL( (int)ln100.size(), 1 );
  CPPUNIT_ASSERT( pcn3 == ln100.front() );

  // INSERTED NODE

  CPPUNIT_ASSERT_EQUAL( pcn3->data(),      3  );
  CPPUNIT_ASSERT_EQUAL( (int)pcn3->flag(), 30 );

  // Edges list of n3 contains e1 & e2

  const list<GenEdge<int,double>*>& le100 = pcn3->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le100.size(), 2 );
  CPPUNIT_ASSERT( le100.front() == pe1 );
  CPPUNIT_ASSERT( le100.back()  == pe2 );

  // NODE n3 IS THE NEW TARGET OF EDGE e1

  CPPUNIT_ASSERT( pe1->pSource() == pn10 );
  CPPUNIT_ASSERT( pe1->pTarget() == pcn3 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe1->data(), 1., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe1->flag(), 0 );

  // NODE n3 IS THE NEW SOURCE OF EDGE e2

  CPPUNIT_ASSERT( pe2->pSource() == pcn3 );
  CPPUNIT_ASSERT( pe2->pTarget() == pcn2  );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe2->data(), 2., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe2->flag(), 0 );

  // INSERT NODE n4 BEWTEEN e2 AND e3
  // --------------------------------
  //
  //              e1
  //     n10 S----------T n3
  //
  //              e2
  //     n3  S----------T n4
  //
  //              e3
  //     n30 S----------T n4

  GenNode<int,double>* pcn4 = g2.addNode(pn4, pe2, pe3);
  CPPUNIT_ASSERT( pcn4 == pn4 );

  // EDGES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g2.accessEdges()).empty() );

  // NODES LIST OF THE GRAPH

  const list<GenNode<int,double>*>& ln1000 = g2.accessNodes();
  CPPUNIT_ASSERT_EQUAL( (int)ln1000.size(), 2 );
  CPPUNIT_ASSERT( pcn3 == ln1000.front() );
  CPPUNIT_ASSERT( pcn4 == ln1000.back() );

  // INSERTED NODE

  CPPUNIT_ASSERT_EQUAL( pcn4->data(),      4 );
  CPPUNIT_ASSERT_EQUAL( (int)pcn4->flag(), 40 );

  // Edges list of n4 contains e2 & e3

  const list<GenEdge<int,double>*>& le1000 = pcn4->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le1000.size(), 2 );
  CPPUNIT_ASSERT( le1000.front() == pe2 );
  CPPUNIT_ASSERT( le1000.back()  == pe3 );

  // NODE n4 IS THE NEW TARGET OF EDGE e2

  CPPUNIT_ASSERT( pe2->pSource() == pn3 );
  CPPUNIT_ASSERT( pe2->pTarget() == pn4 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe2->data(), 2., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe2->flag(), 0 );

  // NODE n4 IS THE NEW TARGET OF EDGE e3

  CPPUNIT_ASSERT( pe3->pSource() == pn30 );
  CPPUNIT_ASSERT( pe3->pTarget() == pn4  );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe3->data(), 3., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe3->flag(), 0 );

  // DELETIONS
  // ---------

  delete pn10;
  delete pn11;
  delete pn21;
  delete pn30;

  delete pe1;
  delete pe2;
  delete pe3;
}



void
GenUGraphTest::testAddNodeSourceAndTarget()
{
  //             e1
  //     n1 S----------T n2
  //
  //             e2
  //     n3 S----------T n2
  //
  //             e3
  //     n1 S----------T n4
  //
  //             e20
  //     n2 S----------

  GenNode<int,double>* pn1  = new GenNode<int,double>(1,10);
  GenEdge<int,double>* pe20 = new GenEdge<int,double>(20.,200);
  GenNode<int,double>* pn2  = new GenNode<int,double>(pe20, 2, 20);
  GenNode<int,double>* pn3  = new GenNode<int,double>(3,30);
  GenNode<int,double>* pn4  = new GenNode<int,double>(4,40);

  GenEdge<int,double>* pe1 = new GenEdge<int,double>(pn1, pn2, 1., 10);
  GenEdge<int,double>* pe2 = new GenEdge<int,double>(pn3, pn2, 2., 20);
  GenEdge<int,double>* pe3 = new GenEdge<int,double>(pn1, pn4, 3., 30);
  
  GenUGraph<int,double> g;

  // INSERT NODE n3 AS TARGET OF EDGE e1
  // -----------------------------------
  //
  //             e1
  //     n1 S----------T n3
  //
  //             e2
  //     n3 S----------T n2
  //
  //             e3
  //     n1 S----------T n4
  //
  //             e20
  //     n2 S----------

  GenNode<int,double>* pcn = g.addNodeAtTarget(pn3, pe1);
  CPPUNIT_ASSERT( pcn == pn3 );

  // EDGES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g.accessEdges()).empty() );

  // NODES LIST OF THE GRAPH

  const list<GenNode<int,double>*>& ln1 = g.accessNodes();
  CPPUNIT_ASSERT_EQUAL( (int)ln1.size(), 1 );

  // INSERTED NODE

  GenNode<int,double>* pn = ln1.front();
  CPPUNIT_ASSERT( pn == pn3 );
  CPPUNIT_ASSERT_EQUAL( pn->data(),      3 );
  CPPUNIT_ASSERT_EQUAL( (int)pn->flag(), 30 );

  // Edges list of the inserted node contains pe1

  const list<GenEdge<int,double>*>& le1 = pn->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le1.size(), 1 );
  CPPUNIT_ASSERT( le1.front() == pe1 );

  // NODE pn3 IS THE NEW TARGET OF EDGE pe1

  CPPUNIT_ASSERT( pe1->pSource() == pn1 );
  CPPUNIT_ASSERT( pe1->pTarget() == pn3 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe1->data(), 1., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe1->flag(), 10 );

  // INSERT NODE n4 AS SOURCE OF EDGE e2
  // -----------------------------------
  //
  //             e1
  //     n1 S----------T n3
  //
  //             e2
  //     n4 S----------T n2
  //
  //             e3
  //     n1 S----------T n4
  //
  //             e20
  //     n2 S----------

  pcn = g.addNodeAtSource(pn4, pe2);
  CPPUNIT_ASSERT( pcn == pn4 );

  // EDGES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g.accessEdges()).empty() );

  // NODES LIST OF THE GRAPH

  const list<GenNode<int,double>*>& ln2 = g.accessNodes();
  CPPUNIT_ASSERT_EQUAL( (int)ln2.size(), 2 );

  // PREVIOUSLY INSERTED NODE

  pn = ln2.front();
  CPPUNIT_ASSERT( pn == pn3 );
  CPPUNIT_ASSERT_EQUAL( pn->data(),      3 );
  CPPUNIT_ASSERT_EQUAL( (int)pn->flag(), 30 );

  // Edges list of the previously inserted node contains pe2

  const list<GenEdge<int,double>*>& le20 = pn->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le20.size(), 1 );
  CPPUNIT_ASSERT( le20.front() == pe1 );

  // NEWLY INSERTED NODE pn4

  CPPUNIT_ASSERT( ln2.back() == pn4 );
  CPPUNIT_ASSERT_EQUAL( pn4->data(),      4 );
  CPPUNIT_ASSERT_EQUAL( (int)pn4->flag(), 40 );

  // Edges list of the newly inserted node contains pe2 

  const list<GenEdge<int,double>*>& le21 = pn4->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le21.size(), 1 );
  CPPUNIT_ASSERT( le21.front() == pe2 );

  // NODE pn4 IS THE NEW SOURCE OF EDGE pe2

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe2->data(), 2., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe2->flag(), 20 );
  CPPUNIT_ASSERT( pe2->pSource() == pn4 );
  CPPUNIT_ASSERT( pe2->pTarget() == pn2 );

  // INSERT NODE n2 AS TARGET OF EDGE e3
  // -----------------------------------
  //
  //             e1
  //     n1 S----------T n3
  //
  //             e2
  //     n4 S----------T n2
  //
  //             e3
  //     n1 S----------T n2
  //
  //             e20
  //     n2 S----------

  pcn = g.addNodeAtTarget(pn2, pe3);
  CPPUNIT_ASSERT( pcn == pn2 );

  // EDGES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g.accessEdges()).empty() );

  // NODES LIST OF THE GRAPH

  const list<GenNode<int,double>*>& ln3 = g.accessNodes();
  CPPUNIT_ASSERT_EQUAL( (int)ln3.size(), 3 );

  list<GenNode<int,double>*>::const_iterator itN = ln3.begin();

  // FIRSTLY INSERTED NODE pn3

  pn = *itN;
  CPPUNIT_ASSERT( pn == pn3 );
  CPPUNIT_ASSERT_EQUAL( pn->data(),      3 );
  CPPUNIT_ASSERT_EQUAL( (int)pn->flag(), 30 );

  // Edges list of the node contains pe3

  const list<GenEdge<int,double>*>& le30 = pn->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le30.size(), 1 );
  CPPUNIT_ASSERT( le30.front() == pe1 );

  // NODE pn3 IS THE NEW TARGET OF EDGE pe1

  CPPUNIT_ASSERT( pe1->pSource() == pn1 );
  CPPUNIT_ASSERT( pe1->pTarget() == pn3 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe1->data(), 1., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe1->flag(), 10 );

  // SECONDLY INSERTED NODE pn4

  ++itN;
  pn = *itN;
  CPPUNIT_ASSERT( pn == pn4 );
  CPPUNIT_ASSERT_EQUAL( pn->data(),      4 );
  CPPUNIT_ASSERT_EQUAL( (int)pn->flag(), 40 );

  // Edges list of the newly inserted node contains pe2 

  const list<GenEdge<int,double>*>& le31 = pn->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le31.size(), 1 );
  CPPUNIT_ASSERT( le31.front() == pe2 );

  // NODE pn4 IS THE NEW SOURCE OF EDGE pe2

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe2->data(), 2., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe2->flag(), 20 );
  CPPUNIT_ASSERT( pe2->pSource() == pn4 );
  CPPUNIT_ASSERT( pe2->pTarget() == pn2 );

  // NEWLY INSERTED NODE pn2

  ++itN;
  pn = *itN;
  CPPUNIT_ASSERT( pn == pn2 );
  CPPUNIT_ASSERT_EQUAL( pn->data(),      2 );
  CPPUNIT_ASSERT_EQUAL( (int)pn->flag(), 20 );

  // Edges list of the newly inserted node contains pe20 & pe3

  const list<GenEdge<int,double>*>& le32 = pn->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le32.size(), 2 );
  CPPUNIT_ASSERT( le32.front() == pe20 );
  CPPUNIT_ASSERT( le32.back()  == pe3 );

  // NODE pn2 IS THE NEW TARGET OF EDGE pe3

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe3->data(), 3., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe3->flag(), 30 );
  CPPUNIT_ASSERT( pe3->pSource() == pn1 );
  CPPUNIT_ASSERT( pe3->pTarget() == pn2 );

  // DELETIONS
  // ---------

  delete pe1;
  delete pe20;
  delete pe2;
  delete pe3;
}


// ===================
// ===================
// INSERTIONS OF EDGES
// ===================
// ===================


void
GenUGraphTest::testJustAddEdge()
{
  // ***************************
  // INSERT A POINTER TO AN EDGE
  // ***************************

  GenUGraph<int,double> g1;

  // INSERT AN EDGE
  // --------------

  GenEdge<int,double>* pe1 = new GenEdge<int,double>(1.,10);
  GenEdge<int,double>* pce = g1.addEdge(pe1);
  CPPUNIT_ASSERT( pce == pe1 );

  // EDGES LIST OF THE GRAPH

  const list<GenEdge<int,double>*>& le1 = g1.accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le1.size(), 1 );

  CPPUNIT_ASSERT( pce == le1.front() );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pce->data(), 1., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pce->flag(), 10 );
  CPPUNIT_ASSERT( pce->pSource() == 0 );
  CPPUNIT_ASSERT( pce->pTarget() == 0 );

  // NODES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g1.accessNodes()).empty() );

  // INSERT A SECOND EDGE
  // --------------------

  GenEdge<int,double>* pe2 = new GenEdge<int,double>(2.,20);
  pce = g1.addEdge(pe2);
  CPPUNIT_ASSERT( pce == pe2 );

  const list<GenEdge<int,double>*>& le2 = g1.accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le2.size(), 2 );

  // FIRST EDGE OF THE EDGES LIST OF THE GRAPH

  GenEdge<int,double>* pe = le2.front();
  CPPUNIT_ASSERT( pe == pe1 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe->data(), 1., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe->flag(), 10 );
  CPPUNIT_ASSERT( pe->pSource() == 0 );
  CPPUNIT_ASSERT( pe->pTarget() == 0 );

  // SECOND EDGE OF THE EDGES LIST OF THE GRAPH

  CPPUNIT_ASSERT( pce == le2.back() );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pce->data(), 2., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pce->flag(), 20 );
  CPPUNIT_ASSERT( pce->pSource() == 0 );
  CPPUNIT_ASSERT( pce->pTarget() == 0 );

  // NODES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g1.accessNodes()).empty() );


  // *********************
  // INSERT A CREATED EDGE
  // *********************

  GenUGraph<int,double> g10;

  // INSERT AN EDGE
  // --------------

  pce = g10.addEdge(1.,10);

  // EDGES LIST OF THE GRAPH

  const list<GenEdge<int,double>*>& le10 = g10.accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le10.size(), 1 );

  CPPUNIT_ASSERT( pce == le10.front() );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pce->data(), 1., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pce->flag(), 10 );
  CPPUNIT_ASSERT( pce->pSource() == 0 );
  CPPUNIT_ASSERT( pce->pTarget() == 0 );

  // NODES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g10.accessNodes()).empty() );

  // INSERT A SECOND EDGE
  // --------------------

  pce = g10.addEdge(2.,20);

  const list<GenEdge<int,double>*>& le20 = g10.accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le20.size(), 2 );

  // FIRST EDGE OF THE EDGES LIST OF THE GRAPH

  pe = le20.front();
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe->data(), 1., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe->flag(), 10 );
  CPPUNIT_ASSERT( pe->pSource() == 0 );
  CPPUNIT_ASSERT( pe->pTarget() == 0 );

  // SECOND EDGE OF THE EDGES LIST OF THE GRAPH

  CPPUNIT_ASSERT( pce == le20.back() );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pce->data(), 2., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pce->flag(), 20 );
  CPPUNIT_ASSERT( pce->pSource() == 0 );
  CPPUNIT_ASSERT( pce->pTarget() == 0 );

  // NODES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g10.accessNodes()).empty() );
}



void
GenUGraphTest::testAddEdgeToANode()
{
  // *********************
  // INSERT A CREATED EDGE
  // *********************

  GenNode<int,double>* pn1 = new GenNode<int,double>(1,10);
  GenUGraph<int,double> g1;


  // INSERT A FIRST EDGE
  // -------------------

  GenEdge<int,double>* pe1 = g1.addEdge(pn1, 1., 10);

  // EDGES LIST OF THE GRAPH

  const list<GenEdge<int,double>*>& le1 = g1.accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le1.size(), 1 );
  CPPUNIT_ASSERT( le1.front() == pe1 );

  // NEW EDGE e1

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe1->data(), 1., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe1->flag(), 10 );
  CPPUNIT_ASSERT( pe1->pSource() == pn1 );
  CPPUNIT_ASSERT( pe1->pTarget() == 0 );

  // EDGES LIST OF NODE n1 CONTAINS e1

  CPPUNIT_ASSERT_EQUAL( pn1->data(),      1 );
  CPPUNIT_ASSERT_EQUAL( (int)pn1->flag(), 10 );

  const list<GenEdge<int,double>*>& len1 = pn1->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)len1.size(), 1 );
  CPPUNIT_ASSERT( len1.front() == pe1 );

  // NODES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g1.accessNodes()).empty() );

  // INSERT A SECOND EDGE
  // --------------------

  GenEdge<int,double>* pe2 = g1.addEdge(pn1, 2., 20);

  // EDGES LIST OF THE GRAPH

  const list<GenEdge<int,double>*>& le2 = g1.accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le2.size(), 2 );
  CPPUNIT_ASSERT( le2.front() == pe1 );
  CPPUNIT_ASSERT( le2.back()  == pe2 );

  // NEW EDGE e2

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe2->data(), 2., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe2->flag(), 20 );
  CPPUNIT_ASSERT( pe2->pSource() == pn1 );
  CPPUNIT_ASSERT( pe2->pTarget() == 0 );

  // EDGES LIST OF NODE n1 CONTAINS e1 & e2

  CPPUNIT_ASSERT_EQUAL( pn1->data(),      1 );
  CPPUNIT_ASSERT_EQUAL( (int)pn1->flag(), 10 );

  const list<GenEdge<int,double>*>& len12 = pn1->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)len12.size(), 2 );
  CPPUNIT_ASSERT( len12.front() == pe1 );
  CPPUNIT_ASSERT( len12.back()  == pe2 );

  // NODES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g1.accessNodes()).empty() );


  // ***************************
  // INSERT A POINTER TO AN EDGE
  // ***************************
  //
  //              e10
  //     n10 S----------T n11
  //
  //              e20
  //          ----------T n21
  //
  //              e30
  //     n30 S----------

  GenUGraph<int,double> g2;
  GenNode<int,double>* pn2 = new GenNode<int,double>(2,20);

  GenNode<int,double>* pn10 = new GenNode<int,double>(10, 100);
  GenNode<int,double>* pn11 = new GenNode<int,double>(11, 110);
  GenNode<int,double>* pn21 = new GenNode<int,double>(21, 210);
  GenNode<int,double>* pn30 = new GenNode<int,double>(30, 300);

  GenEdge<int,double>* pe10  = new GenEdge<int,double>(pn10,  pn11, 10.);
  GenEdge<int,double>* pe20  = new GenEdge<int,double>(   0,  pn21, 20.);
  GenEdge<int,double>* pe30  = new GenEdge<int,double>(pn30,     0, 30.);

  // EDGE e10 WITH NODE n2 AS TARGET
  // -------------------------------
  //
  //              e10
  //     n10 S----------T n2
  //
  //              e20
  //          ----------T n21
  //
  //              e30
  //     n30 S----------

  GenEdge<int,double>* pce10 = g2.addEdge(pe10, pn2);
  CPPUNIT_ASSERT( pce10 == pe10 );

  // EDGES LIST OF THE GRAPH

  const list<GenEdge<int,double>*>& le20 = g2.accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le20.size(), 1 );
  CPPUNIT_ASSERT( le20.front() == pce10 );

  // NEW EDGE e10

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pce10->data(), 10., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pce10->flag(), 0 );
  CPPUNIT_ASSERT( pce10->pSource() == pn10 );
  CPPUNIT_ASSERT( pce10->pTarget() == pn2 );

  // EDGES LIST OF NODE n2 CONTAINS e10

  CPPUNIT_ASSERT_EQUAL( pn2->data(),      2 );
  CPPUNIT_ASSERT_EQUAL( (int)pn2->flag(), 20 );

  const list<GenEdge<int,double>*>& len21 = pn2->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)len21.size(), 1 );
  CPPUNIT_ASSERT( len21.front() == pe10 );

  // NODES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g2.accessNodes()).empty() );

  // EDGE e20 WITH NODE n2 AS SOURCE
  // -------------------------------
  //
  //              e10
  //     n10 S----------T n2
  //
  //              e20
  //     n2  S----------T n21
  //
  //              e30
  //     n30 S----------

  GenEdge<int,double>* pce20 = g2.addEdge(pe20, pn2);
  CPPUNIT_ASSERT( pce20 == pe20 );

  // EDGES LIST OF THE GRAPH

  const list<GenEdge<int,double>*>& le22 = g2.accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le22.size(), 2 );
  CPPUNIT_ASSERT( le22.front() == pce10 );
  CPPUNIT_ASSERT( le22.back()  == pce20 );

  // FIRST EDGE e10

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe10->data(), 10., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe10->flag(), 0 );
  CPPUNIT_ASSERT( pe10->pSource() == pn10 );
  CPPUNIT_ASSERT( pe10->pTarget() == pn2 );

  // NEW EDGE e20

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pce20->data(), 20., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pce20->flag(), 0 );
  CPPUNIT_ASSERT( pce20->pSource() == pn2 );
  CPPUNIT_ASSERT( pce20->pTarget() == pn21 );

  // EDGES LIST OF NODE n2 CONTAINS e10 & e20

  CPPUNIT_ASSERT_EQUAL( pn2->data(),      2 );
  CPPUNIT_ASSERT_EQUAL( (int)pn2->flag(), 20 );

  const list<GenEdge<int,double>*>& len23 = pn2->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)len23.size(), 2 );
  CPPUNIT_ASSERT( len23.front() == pe10 );
  CPPUNIT_ASSERT( len23.back()  == pe20 );

  // NODES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g2.accessNodes()).empty() );

  // EDGE e30 WITH NODE n2 AS TARGET
  // -------------------------------
  //
  //              e10
  //     n10 S----------T n2
  //
  //              e20
  //     n2  S----------T n21
  //
  //              e30
  //     n30 S----------T n2

  GenEdge<int,double>* pce30 = g2.addEdge(pe30, pn2);
  CPPUNIT_ASSERT( pce30 == pe30 );

  // EDGES LIST OF THE GRAPH

  const list<GenEdge<int,double>*>& le24 = g2.accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le24.size(), 3 );
  list<GenEdge<int,double>*>::const_iterator itGE = le24.begin();
  CPPUNIT_ASSERT( *itGE == pce10 );
  ++itGE;
  CPPUNIT_ASSERT( *itGE == pce20 );
  ++itGE;
  CPPUNIT_ASSERT( *itGE == pce30 );

  // FIRST EDGE e10

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe10->data(), 10., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe10->flag(), 0 );
  CPPUNIT_ASSERT( pe10->pSource() == pn10 );
  CPPUNIT_ASSERT( pe10->pTarget() == pn2 );

  // SECOND EDGE e20

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pce20->data(), 20., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pce20->flag(), 0 );
  CPPUNIT_ASSERT( pce20->pSource() == pn2 );
  CPPUNIT_ASSERT( pce20->pTarget() == pn21 );

  // NEW EDGE e20

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pce30->data(), 30., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pce30->flag(), 0 );
  CPPUNIT_ASSERT( pce30->pSource() == pn30 );
  CPPUNIT_ASSERT( pce30->pTarget() == pn2  );

  // EDGES LIST OF NODE n2 CONTAINS e10 - e20 - e30

  CPPUNIT_ASSERT_EQUAL( pn2->data(),      2 );
  CPPUNIT_ASSERT_EQUAL( (int)pn2->flag(), 20 );

  const list<GenEdge<int,double>*>& len25 = pn2->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)len25.size(), 3 );
  list<GenEdge<int,double>*>::const_iterator itGN = len25.begin();
  CPPUNIT_ASSERT( *itGN == pce10 );
  ++itGN;
  CPPUNIT_ASSERT( *itGN == pce20 );
  ++itGN;
  CPPUNIT_ASSERT( *itGN == pce30 );

  // NODES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g2.accessNodes()).empty() );

  // DELETIONS
  // ---------

  delete pn1;
  delete pn10;
  delete pn11;
  delete pn21;
  delete pn30;
}



void
GenUGraphTest::testAddEdgeBetween2Nodes()
{
  GenNode<int,double>* pn1 = new GenNode<int,double>(1,10);
  GenNode<int,double>* pn2 = new GenNode<int,double>(2,20);

  // *********************************
  // INSERT A NEW EDGE BETWEEN 2 NODES
  // *********************************

  GenUGraph<int,double> g1;

  // INSERT NEW EDGE e10 BETWEEN NODES n1 & n2
  // -----------------------------------------
  //
  //             e10
  //     n1 S----------T n2

  GenEdge<int,double>* pce10 = g1.addEdge(pn1, pn2, 10., 100);

  // EDGES LIST OF THE GRAPH

  const list<GenEdge<int,double>*>& le1 = g1.accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le1.size(), 1 );
  CPPUNIT_ASSERT( pce10 == le1.front() );

  // NEW EDGE e10

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pce10->data(), 10., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pce10->flag(), 100 );
  CPPUNIT_ASSERT( pce10->pSource() == pn1 );
  CPPUNIT_ASSERT( pce10->pTarget() == pn2 );

  // NODE n1

  CPPUNIT_ASSERT_EQUAL( pn1->data(),      1  );
  CPPUNIT_ASSERT_EQUAL( (int)pn1->flag(), 10 );

  const list<GenEdge<int,double>*>& len1 = pn1->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)len1.size(), 1 );
  CPPUNIT_ASSERT( len1.front() == pce10 );

  // NODE n2

  CPPUNIT_ASSERT_EQUAL( pn2->data(),      2  );
  CPPUNIT_ASSERT_EQUAL( (int)pn2->flag(), 20 );

  const list<GenEdge<int,double>*>& len2 = pn2->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)len2.size(), 1 );
  CPPUNIT_ASSERT( len2.front() == pce10 );

  // NODES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g1.accessNodes()).empty() );

  // ***************************************
  // INSERT AN EXISTING EDGE BETWEEN 2 NODES
  // ***************************************
  //
  //              e1
  //     n10 S----------T n11
  //
  //              e10
  //     n1  S----------T n2

  GenNode<int,double>* pn10 = new GenNode<int,double>(10, 100);
  GenNode<int,double>* pn11 = new GenNode<int,double>(11, 110);

  GenEdge<int,double>* pe1  = new GenEdge<int,double>(pn10,  pn11, 1.);

  GenUGraph<int,double> g2;

  // INSERT NEW EDGE e1 BETWEEN NODES n2 & n1
  // ----------------------------------------
  //
  //             e1
  //     n2 S----------T n1
  //
  //             e10
  //     n1 S----------T n2

  GenEdge<int,double>* pce1 = g2.addEdge(pe1, pn2, pn1);
  CPPUNIT_ASSERT( pce1 == pe1 );

  // EDGES LIST OF THE GRAPH

  const list<GenEdge<int,double>*>& le10 = g2.accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le10.size(), 1 );
  CPPUNIT_ASSERT( pce1  == le10.back() );

  // EDGE e1

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pce1->data(), 1., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pce1->flag(), 0 );
  CPPUNIT_ASSERT( pce1->pSource() == pn2 );
  CPPUNIT_ASSERT( pce1->pTarget() == pn1 );

  // NODE n1

  CPPUNIT_ASSERT_EQUAL( pn1->data(),      1  );
  CPPUNIT_ASSERT_EQUAL( (int)pn1->flag(), 10 );

  const list<GenEdge<int,double>*>& len10 = pn1->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)len10.size(), 2 );
  CPPUNIT_ASSERT( len10.front() == pce10 );
  CPPUNIT_ASSERT( len10.back()  == pce1  );

  // NODE n2

  CPPUNIT_ASSERT_EQUAL( pn2->data(),      2  );
  CPPUNIT_ASSERT_EQUAL( (int)pn2->flag(), 20 );

  const list<GenEdge<int,double>*>& len20 = pn2->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)len20.size(), 2 );
  CPPUNIT_ASSERT( len20.front() == pce10 );
  CPPUNIT_ASSERT( len20.back()  == pce1  );

  // NODES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g1.accessNodes()).empty() );

  // DELETIONS
  // ---------

  delete pn1;
  delete pn2;
}



void
GenUGraphTest::testAddEdgeSourceAndTarget()
{
  //              e1
  //     n1  S----------T n10
  //
  //              e2
  //          ----------T n20
  //
  //              e3
  //     n3  S----------

  GenNode<int,double>* pn1  = new GenNode<int,double>(1,  10);
  GenNode<int,double>* pn10 = new GenNode<int,double>(10, 100);

  GenNode<int,double>* pn20 = new GenNode<int,double>(20, 200);

  GenNode<int,double>* pn3  = new GenNode<int,double>(3,  30);

  GenNode<int,double>* pn100 = new GenNode<int,double>(100, 1000);
  GenNode<int,double>* pn300 = new GenNode<int,double>(300, 3000);

  GenEdge<int,double>* pe1  = new GenEdge<int,double>(pn1, pn10, 1., 10);
  GenEdge<int,double>* pe2  = new GenEdge<int,double>(  0, pn20, 2., 20);
  GenEdge<int,double>* pe3  = new GenEdge<int,double>(pn3,    0, 3., 30);

  GenUGraph<int,double> g;

  // EDGE e1 WITH NODE n100 AS TARGET
  // --------------------------------
  //
  //              e1
  //     n1  S----------T n100
  //
  //              e2
  //          ----------T n20
  //
  //              e3
  //     n3  S----------

  GenEdge<int,double>* pce = g.addEdgeByTarget(pe1, pn100);
  CPPUNIT_ASSERT( pce == pe1 );

  // EDGES LIST OF THE GRAPH

  const list<GenEdge<int,double>*>& le1 = g.accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le1.size(), 1 );

  // NEW EDGE e1

  GenEdge<int,double>* pe = le1.front();
  CPPUNIT_ASSERT( pe == pe1 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe->data(), 1., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe->flag(), 10 );
  CPPUNIT_ASSERT( pe->pSource() == pn1 );
  CPPUNIT_ASSERT( pe->pTarget() == pn100 );

  // EDGES LIST OF NODE n100 CONTAINS e1

  CPPUNIT_ASSERT_EQUAL( pn100->data(),      100 );
  CPPUNIT_ASSERT_EQUAL( (int)pn100->flag(), 1000 );

  const list<GenEdge<int,double>*>& len100 = pn100->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)len100.size(), 1 );
  CPPUNIT_ASSERT( len100.front() == pe1 );

  // NODES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g.accessNodes()).empty() );

  // EDGE e2 WITH NODE n1 AS SOURCE
  // ------------------------------
  //
  //              e1
  //     n1  S----------T n100
  //
  //              e2
  //     n1  S----------T n20
  //
  //              e3
  //     n3  S----------

  pce = g.addEdgeBySource(pe2, pn1);
  CPPUNIT_ASSERT( pce == pe2 );

  // EDGES LIST OF THE GRAPH

  const list<GenEdge<int,double>*>& le2 = g.accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le2.size(), 2 );

  // PREVIOUSLY INSERTED EDGE e1

  pe = le1.front();
  CPPUNIT_ASSERT( pe == pe1 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe->data(), 1., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe->flag(), 10 );
  CPPUNIT_ASSERT( pe->pSource() == pn1 );
  CPPUNIT_ASSERT( pe->pTarget() == pn100 );

  // Edges list of node n100 contains e1

  CPPUNIT_ASSERT_EQUAL( pn100->data(),      100 );
  CPPUNIT_ASSERT_EQUAL( (int)pn100->flag(), 1000 );

  const list<GenEdge<int,double>*>& len101 = pn100->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)len101.size(), 1 );
  CPPUNIT_ASSERT( len101.front() == pe1 );

  // NEWLY INSERTED EDGE e2: n1 IS THE SOURCE

  CPPUNIT_ASSERT( le2.back() == pe2 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe2->data(), 2., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe2->flag(), 20 );
  CPPUNIT_ASSERT( pe2->pSource() == pn1   );
  CPPUNIT_ASSERT( pe2->pTarget() == pn20  );

  // Edges list of node n1 contains e2

  CPPUNIT_ASSERT_EQUAL( pn1->data(),      1  );
  CPPUNIT_ASSERT_EQUAL( (int)pn1->flag(), 10 );

  const list<GenEdge<int,double>*>& len102 = pn1->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)len102.size(), 1 );
  CPPUNIT_ASSERT( len102.back()  == pe2 );

  // NODES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g.accessNodes()).empty() );

  // EDGE e3 WITH NODE n300 AS TARGET
  // --------------------------------
  //
  //              e1
  //     n1  S----------T n100
  //
  //              e2
  //     n1  S----------T n20
  //
  //              e3
  //     n3  S----------T n300

  pce = g.addEdgeByTarget(pe3, pn300);
  CPPUNIT_ASSERT( pce == pe3 );

  // EDGES LIST OF THE GRAPH

  const list<GenEdge<int,double>*>& le3 = g.accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le3.size(), 3 );
  list<GenEdge<int,double>*>::const_iterator itE = le3.begin();

  // FIRSTLY INSERTED EDGE e1

  pe = *itE;
  CPPUNIT_ASSERT( pe == pe1 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe->data(), 1., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe->flag(), 10 );
  CPPUNIT_ASSERT( pe->pSource() == pn1 );
  CPPUNIT_ASSERT( pe->pTarget() == pn100 );

  // Edges list of node n100 contains e1

  CPPUNIT_ASSERT_EQUAL( pn100->data(),      100 );
  CPPUNIT_ASSERT_EQUAL( (int)pn100->flag(), 1000 );

  const list<GenEdge<int,double>*>& len103 = pn100->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)len103.size(), 1 );
  CPPUNIT_ASSERT( len103.front() == pe1 );

  // SECONDLY INSERTED EDGE e2

  ++itE;
  pe = *itE;
  CPPUNIT_ASSERT( pe == pe2 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe->data(), 2., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe->flag(), 20 );
  CPPUNIT_ASSERT( pe->pSource() == pn1   );
  CPPUNIT_ASSERT( pe->pTarget() == pn20  );

  // Edges list of node n1 contains e2

  CPPUNIT_ASSERT_EQUAL( pn1->data(),      1  );
  CPPUNIT_ASSERT_EQUAL( (int)pn1->flag(), 10 );

  const list<GenEdge<int,double>*>& len104 = pn1->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)len104.size(), 1 );
  CPPUNIT_ASSERT( len104.back()  == pe2 );

  // NEWLY INSERTED EDGE e3

  ++itE;
  pe = *itE;
  CPPUNIT_ASSERT( pe == pe3 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe->data(), 3., 0. );
  CPPUNIT_ASSERT_EQUAL( (int)pe->flag(), 30 );
  CPPUNIT_ASSERT( pe->pSource() == pn3   );
  CPPUNIT_ASSERT( pe->pTarget() == pn300  );

  // Node n3

  CPPUNIT_ASSERT_EQUAL( pn3->data(),      3  );
  CPPUNIT_ASSERT_EQUAL( (int)pn3->flag(), 30 );
  CPPUNIT_ASSERT( (pn3->accessEdges()).empty() );

  // Edge e3 is in the edges list of node n300

  CPPUNIT_ASSERT_EQUAL( pn300->data(),      300  );
  CPPUNIT_ASSERT_EQUAL( (int)pn300->flag(), 3000 );

  const list<GenEdge<int,double>*>& len300 = pn300->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)len300.size(), 1 );
  CPPUNIT_ASSERT( len300.front() == pe3 );

  // NODES LIST OF THE GRAPH

  CPPUNIT_ASSERT( (g.accessNodes()).empty() );

  // DELETIONS
  // ---------

  delete pn1;
  delete pn3;
  delete pn10;
  delete pn20;
  delete pn100;
  delete pn300;
}


// ==============
// ==============
// GRAPH FEATURES
// ==============
// ==============


void
GenUGraphTest::testGraphFeatures()
{
  // EMPTY GRAPH
  // -----------

  GenUGraph<int,double> g;
  CPPUNIT_ASSERT( g.empty() );
  CPPUNIT_ASSERT( (g.getNodes()).empty() );
  CPPUNIT_ASSERT( (g.nodes()).empty() );
  CPPUNIT_ASSERT( (g.getEdges()).empty() );
  CPPUNIT_ASSERT( (g.edges()).empty() );

  // CONSTRUCTION OF A GRAPH
  // -----------------------
  //
  //          e12  n2   e42   n4
  //    n1 O-------O----------O      O n5
  //        \     /
  //     e13 \   / e23
  //          \ / 
  //           O
  //           n3
  //
  // NODES LIST = n5  -> n4  -> n2  -> n1  -> n3
  // EDGES LIST = e42 -> e12 -> e23 -> e13
  //
  // edges list of n1 = e12 -> e13
  // edges list of n2 = e42 -> e12 -> e23
  // edges list of n3 = e23 -> e13
  // edges list of n4 = e42
  // edges list of n5 = NIL

  GenNode<int,double>* pn5 = g.addNode(5,50);

  // Nodes and edges sizes, entry node and edge
  CPPUNIT_ASSERT( !(g.empty()) );
  CPPUNIT_ASSERT_EQUAL( g.sizeNodes(), 1 );
  CPPUNIT_ASSERT_EQUAL( g.sizeEdges(), 0 );
  CPPUNIT_ASSERT( g.pEntryNode() == pn5 );
  CPPUNIT_ASSERT( g.pEntryEdge() == 0   );

  GenNode<int,double>* pn4  = g.addNode(4,40);
  CPPUNIT_ASSERT( !(g.empty()) );
  CPPUNIT_ASSERT_EQUAL( g.sizeNodes(), 2 );
  CPPUNIT_ASSERT_EQUAL( g.sizeEdges(), 0 );
  CPPUNIT_ASSERT( g.pEntryNode() == pn5 );
  CPPUNIT_ASSERT( g.pEntryEdge() == 0   );

  GenNode<int,double>* pn2  = g.addNode(2,20);
  CPPUNIT_ASSERT( !(g.empty()) );
  CPPUNIT_ASSERT_EQUAL( g.sizeNodes(), 3 );
  CPPUNIT_ASSERT_EQUAL( g.sizeEdges(), 0 );
  CPPUNIT_ASSERT( g.pEntryNode() == pn5 );
  CPPUNIT_ASSERT( g.pEntryEdge() == 0   );

  GenEdge<int,double>* pe42 = g.addEdge(pn4, pn2, 42., 420);
  CPPUNIT_ASSERT( !(g.empty()) );
  CPPUNIT_ASSERT_EQUAL( g.sizeNodes(), 3 );
  CPPUNIT_ASSERT_EQUAL( g.sizeEdges(), 1 );
  CPPUNIT_ASSERT( g.pEntryNode() == pn5  );
  CPPUNIT_ASSERT( g.pEntryEdge() == pe42 );

  GenEdge<int,double>* pe12 = new GenEdge<int,double>(12., 120);
  g.addEdgeByTarget(pe12, pn2);
  CPPUNIT_ASSERT( !(g.empty()) );
  CPPUNIT_ASSERT_EQUAL( g.sizeNodes(), 3 );
  CPPUNIT_ASSERT_EQUAL( g.sizeEdges(), 2 );
  CPPUNIT_ASSERT( g.pEntryNode() == pn5  );
  CPPUNIT_ASSERT( g.pEntryEdge() == pe42 );

  GenEdge<int,double>* pe23 = new GenEdge<int,double>(23., 230);
  g.addEdgeBySource(pe23, pn2);
  CPPUNIT_ASSERT( !(g.empty()) );
  CPPUNIT_ASSERT_EQUAL( g.sizeNodes(), 3 );
  CPPUNIT_ASSERT_EQUAL( g.sizeEdges(), 3 );
  CPPUNIT_ASSERT( g.pEntryNode() == pn5  );
  CPPUNIT_ASSERT( g.pEntryEdge() == pe42 );

  GenNode<int,double>* pn1 = g.addNode(pe12, 1,10);
  CPPUNIT_ASSERT( !(g.empty()) );
  CPPUNIT_ASSERT_EQUAL( g.sizeNodes(), 4 );
  CPPUNIT_ASSERT_EQUAL( g.sizeEdges(), 3 );
  CPPUNIT_ASSERT( g.pEntryNode() == pn5  );
  CPPUNIT_ASSERT( g.pEntryEdge() == pe42 );

  GenNode<int,double>* pn3 = g.addNode(pe23, 3,30);
  CPPUNIT_ASSERT( !(g.empty()) );
  CPPUNIT_ASSERT_EQUAL( g.sizeNodes(), 5 );
  CPPUNIT_ASSERT_EQUAL( g.sizeEdges(), 3 );
  CPPUNIT_ASSERT( g.pEntryNode() == pn5  );
  CPPUNIT_ASSERT( g.pEntryEdge() == pe42 );

  GenEdge<int,double>* pe13 = g.addEdge(pn1, pn3, 13., 130);
  CPPUNIT_ASSERT( !(g.empty()) );
  CPPUNIT_ASSERT_EQUAL( g.sizeNodes(), 5 );
  CPPUNIT_ASSERT_EQUAL( g.sizeEdges(), 4 );
  CPPUNIT_ASSERT( g.pEntryNode() == pn5  );
  CPPUNIT_ASSERT( g.pEntryEdge() == pe42 );

  // EDGES LIST OF THE GRAPH
  // -----------------------

  // Get edges list

  list<GenEdge<int,double>*>& leg = g.getEdges();
  list<GenEdge<int,double>*>::iterator itEG = leg.begin();

  CPPUNIT_ASSERT( *itEG == pe42 );
  ++itEG;
  CPPUNIT_ASSERT( *itEG == pe12 );
  ++itEG;
  CPPUNIT_ASSERT( *itEG == pe23 );
  ++itEG;
  CPPUNIT_ASSERT( *itEG == pe13 );
  ++itEG;
  CPPUNIT_ASSERT(  itEG == leg.end() );

  // Get a copy of the edges list

  list<GenEdge<int,double>*> lecg = g.edges();
  list<GenEdge<int,double>*>::iterator itECG = lecg.begin();

  CPPUNIT_ASSERT( *itECG == pe42 );
  ++itECG;
  CPPUNIT_ASSERT( *itECG == pe12 );
  ++itECG;
  CPPUNIT_ASSERT( *itECG == pe23 );
  ++itECG;
  CPPUNIT_ASSERT( *itECG == pe13 );
  ++itECG;
  CPPUNIT_ASSERT(  itECG == lecg.end() );

  // Modify the copy
  itECG = lecg.begin();
  lecg.erase(itECG);

  // Check copy is modified
  itECG = lecg.begin();
  CPPUNIT_ASSERT( *itECG == pe12 );
  ++itECG;
  CPPUNIT_ASSERT( *itECG == pe23 );
  ++itECG;
  CPPUNIT_ASSERT( *itECG == pe13 );
  ++itECG;
  CPPUNIT_ASSERT( itECG == lecg.end() );

  // Check edges list of the graph is unchanged
  itEG = leg.begin();
  CPPUNIT_ASSERT( *itEG == pe42 );
  ++itEG;
  CPPUNIT_ASSERT( *itEG == pe12 );
  ++itEG;
  CPPUNIT_ASSERT( *itEG == pe23 );
  ++itEG;
  CPPUNIT_ASSERT( *itEG == pe13 );
  ++itEG;
  CPPUNIT_ASSERT(  itEG == leg.end() );
 
  // Modify the edges list of the graph
  itEG = leg.begin();
  ++itEG;
  leg.erase(itEG);

  // Check edges list of the graph is unchanged
  itEG = leg.begin();
  CPPUNIT_ASSERT( *itEG == pe42 );
  ++itEG;
  CPPUNIT_ASSERT( *itEG == pe23 );
  ++itEG;
  CPPUNIT_ASSERT( *itEG == pe13 );
  ++itEG;
  CPPUNIT_ASSERT(  itEG == leg.end() );
 
  // Check copy is unchanged
  itECG = lecg.begin();
  CPPUNIT_ASSERT( *itECG == pe12 );
  ++itECG;
  CPPUNIT_ASSERT( *itECG == pe23 );
  ++itECG;
  CPPUNIT_ASSERT( *itECG == pe13 );
  ++itECG;
  CPPUNIT_ASSERT( itECG == lecg.end() );

  // NODES LIST OF THE GRAPH
  // -----------------------

  // Get nodes list

  list<GenNode<int,double>*>& lng = g.getNodes();
  list<GenNode<int,double>*>::iterator itNG = lng.begin();

  CPPUNIT_ASSERT( *itNG == pn5 );
  ++itNG;
  CPPUNIT_ASSERT( *itNG == pn4 );
  ++itNG;
  CPPUNIT_ASSERT( *itNG == pn2 );
  ++itNG;
  CPPUNIT_ASSERT( *itNG == pn1 );
  ++itNG;
  CPPUNIT_ASSERT( *itNG == pn3 );
  ++itNG;
  CPPUNIT_ASSERT(  itNG == lng.end() );

  // Get a copy of the nodes list

  list<GenNode<int,double>*> lncg = g.nodes();
  list<GenNode<int,double>*>::iterator itNCG = lncg.begin();

  CPPUNIT_ASSERT( *itNCG == pn5 );
  ++itNCG;
  CPPUNIT_ASSERT( *itNCG == pn4 );
  ++itNCG;
  CPPUNIT_ASSERT( *itNCG == pn2 );
  ++itNCG;
  CPPUNIT_ASSERT( *itNCG == pn1 );
  ++itNCG;
  CPPUNIT_ASSERT( *itNCG == pn3 );
  ++itNCG;
  CPPUNIT_ASSERT(  itNCG == lncg.end() );

  // Modify the copy
  itNCG = lncg.begin();
  ++itNCG;
  ++itNCG;
  lncg.erase(itNCG);

  // Check copy is modified
  itNCG = lncg.begin();
  CPPUNIT_ASSERT( *itNCG == pn5 );
  ++itNCG;
  CPPUNIT_ASSERT( *itNCG == pn4 );
  ++itNCG;
  CPPUNIT_ASSERT( *itNCG == pn1 );
  ++itNCG;
  CPPUNIT_ASSERT( *itNCG == pn3 );
  ++itNCG;
  CPPUNIT_ASSERT(  itNCG == lncg.end() );

  // Check nodes list of the graph is unchanged
  itNG = lng.begin();
  CPPUNIT_ASSERT( *itNG == pn5 );
  ++itNG;
  CPPUNIT_ASSERT( *itNG == pn4 );
  ++itNG;
  CPPUNIT_ASSERT( *itNG == pn2 );
  ++itNG;
  CPPUNIT_ASSERT( *itNG == pn1 );
  ++itNG;
  CPPUNIT_ASSERT( *itNG == pn3 );
  ++itNG;
  CPPUNIT_ASSERT(  itNG == lng.end() );

  // Modify the nodes list of the graph
  itNG = lng.begin();
  lng.erase(itNG);

  // Check nodes list of the graph is modified
  itNG = lng.begin();
  CPPUNIT_ASSERT( *itNG == pn4 );
  ++itNG;
  CPPUNIT_ASSERT( *itNG == pn2 );
  ++itNG;
  CPPUNIT_ASSERT( *itNG == pn1 );
  ++itNG;
  CPPUNIT_ASSERT( *itNG == pn3 );
  ++itNG;
  CPPUNIT_ASSERT(  itNG == lng.end() );

  // Check copy is unchanged
  itNCG = lncg.begin();
  CPPUNIT_ASSERT( *itNCG == pn5 );
  ++itNCG;
  CPPUNIT_ASSERT( *itNCG == pn4 );
  ++itNCG;
  CPPUNIT_ASSERT( *itNCG == pn1 );
  ++itNCG;
  CPPUNIT_ASSERT( *itNCG == pn3 );
  ++itNCG;
  CPPUNIT_ASSERT(  itNCG == lncg.end() );

  // NODE n1
  // -------

  CPPUNIT_ASSERT_EQUAL( pn1->data(), 1  );
  CPPUNIT_ASSERT_EQUAL( (int)pn1->flag(), 10 );
  
  const list<GenEdge<int,double>*>& ln1 = pn1->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)ln1.size(), 2 );
  CPPUNIT_ASSERT( ln1.front() == pe12 );
  CPPUNIT_ASSERT( ln1.back()  == pe13 );

  // NODE n2
  // -------

  CPPUNIT_ASSERT_EQUAL( pn2->data(), 2  );
  CPPUNIT_ASSERT_EQUAL( (int)pn2->flag(), 20 );
  
  const list<GenEdge<int,double>*>& ln2 = pn2->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)ln2.size(), 3 );

  list<GenEdge<int,double>*>::const_iterator itE2 = ln2.begin();
  CPPUNIT_ASSERT( *itE2 == pe42 );
  ++itE2;
  CPPUNIT_ASSERT( *itE2 == pe12 );
  ++itE2;
  CPPUNIT_ASSERT( *itE2 == pe23 );

  // NODE n3
  // -------

  CPPUNIT_ASSERT_EQUAL( pn3->data(), 3  );
  CPPUNIT_ASSERT_EQUAL( (int)pn3->flag(), 30 );
  
  const list<GenEdge<int,double>*>& ln3 = pn3->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)ln3.size(), 2 );
  CPPUNIT_ASSERT( ln3.front() == pe23 );
  CPPUNIT_ASSERT( ln3.back()  == pe13 );

  // NODE n4
  // -------

  CPPUNIT_ASSERT_EQUAL( pn4->data(), 4  );
  CPPUNIT_ASSERT_EQUAL( (int)pn4->flag(), 40 );
  
  const list<GenEdge<int,double>*>& ln4 = pn4->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)ln4.size(), 1 );
  CPPUNIT_ASSERT( ln4.front() == pe42 );

  // NODE n5
  // -------

  CPPUNIT_ASSERT_EQUAL( pn5->data(), 5  );
  CPPUNIT_ASSERT_EQUAL( (int)pn5->flag(), 50 );
  
  const list<GenEdge<int,double>*>& ln5 = pn5->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)ln5.size(), 0 );

  // EDGE e12
  // --------

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe12->data(), 12., 0.  );
  CPPUNIT_ASSERT_EQUAL( (int)pe12->flag(), 120 );
  CPPUNIT_ASSERT( pe12->pSource() == pn1 );
  CPPUNIT_ASSERT( pe12->pTarget() == pn2 );

  // EDGE e13
  // --------

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe13->data(), 13., 0.  );
  CPPUNIT_ASSERT_EQUAL( (int)pe13->flag(), 130 );
  CPPUNIT_ASSERT( pe13->pSource() == pn1 );
  CPPUNIT_ASSERT( pe13->pTarget() == pn3 );

  // EDGE e23
  // --------

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe23->data(), 23., 0.  );
  CPPUNIT_ASSERT_EQUAL( (int)pe23->flag(), 230 );
  CPPUNIT_ASSERT( pe23->pSource() == pn2 );
  CPPUNIT_ASSERT( pe23->pTarget() == pn3 );

  // EDGE e42
  // --------

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe42->data(), 42., 0.  );
  CPPUNIT_ASSERT_EQUAL( (int)pe42->flag(), 420 );
  CPPUNIT_ASSERT( pe42->pSource() == pn4 );
  CPPUNIT_ASSERT( pe42->pTarget() == pn2 );
}



// ========
// ========
// REMOVALS
// ========
// ========


void
GenUGraphTest::testRemoveNode()
{
  GenUGraph<int,double> g;

  // CONSTRUCTION OF A GRAPH
  // -----------------------
  //
  //          e12  n2   e42   n4
  //    n1 O-------O----------O      O n5
  //        \     /
  //     e13 \   / e23
  //          \ / 
  //           O
  //           n3
  //
  // NODES LIST = n5  -> n4  -> n2  -> n1  -> n3
  // EDGES LIST = e42 -> e12 -> e23 -> e13
  //
  // edges list of n1 = e12 -> e13
  // edges list of n2 = e42 -> e12 -> e23
  // edges list of n3 = e23 -> e13
  // edges list of n4 = e42
  // edges list of n5 = NIL

  // The graph is constructed in a way different
  // from that of function testGraphFeatures,
  // but the its structure should be the same

  GenNode<int,double>* pn5  = g.addNode(5, 50);
  GenNode<int,double>* pn4  = g.addNode(4, 40);
  GenNode<int,double>* pn2  = g.addNode(2, 20);
  GenEdge<int,double>* pe42 = g.addEdge(pn4, pn2, 42., 420);
  GenNode<int,double>* pn1  = g.addNode(1, 10);
  GenEdge<int,double>* pe12 = g.addEdge(pn1, pn2, 12., 120);
  GenNode<int,double>* pn3  = g.addNode(3, 30);
  GenEdge<int,double>* pe23 = g.addEdge(pn2, pn3, 23., 230);
  GenEdge<int,double>* pe13 = g.addEdge(pn1, pn3, 13., 130);

  // Edges list of the graph

  list<GenEdge<int,double>*>& leg = g.getEdges();

  list<GenEdge<int,double>*>::iterator itEG = leg.begin();
  CPPUNIT_ASSERT( *itEG == pe42 );
  ++itEG;
  CPPUNIT_ASSERT( *itEG == pe12 );
  ++itEG;
  CPPUNIT_ASSERT( *itEG == pe23 );
  ++itEG;
  CPPUNIT_ASSERT( *itEG == pe13 );
  ++itEG;
  CPPUNIT_ASSERT(  itEG == leg.end() );

  list<GenNode<int,double>*>& lng = g.getNodes();

  list<GenNode<int,double>*>::iterator itNG = lng.begin();
  CPPUNIT_ASSERT( *itNG == pn5 );
  ++itNG;
  CPPUNIT_ASSERT( *itNG == pn4 );
  ++itNG;
  CPPUNIT_ASSERT( *itNG == pn2 );
  ++itNG;
  CPPUNIT_ASSERT( *itNG == pn1 );
  ++itNG;
  CPPUNIT_ASSERT( *itNG == pn3 );
  ++itNG;
  CPPUNIT_ASSERT(  itNG == lng.end() );

  // REMOVE NODE n5
  // --------------

  GenNode<int,double>* prn5 = g.remove(pn5);
  CPPUNIT_ASSERT( prn5 == pn5 );
  CPPUNIT_ASSERT( (prn5->accessEdges()).empty() );

  delete pn5;

  //          e12  n2   e42   n4
  //    n1 O-------O----------O
  //        \     /
  //     e13 \   / e23
  //          \ / 
  //           O
  //           n3
  //
  // NODES LIST = n4  -> n2  -> n1  -> n3
  // EDGES LIST = e42 -> e12 -> e23 -> e13
  //
  // edges list of n1 = e12 -> e13
  // edges list of n2 = e42 -> e12 -> e23
  // edges list of n3 = e23 -> e13
  // edges list of n4 = e42
  //
  // REMOVED NODE n5 : edges list = NIL

  // Edges list of the graph

  const list<GenEdge<int,double>*>& len5 = g.accessEdges();

  list<GenEdge<int,double>*>::const_iterator itE5 = len5.begin();
  CPPUNIT_ASSERT( *itE5 == pe42 );
  ++itE5;
  CPPUNIT_ASSERT( *itE5 == pe12 );
  ++itE5;
  CPPUNIT_ASSERT( *itE5 == pe23 );
  ++itE5;
  CPPUNIT_ASSERT( *itE5 == pe13 );
  ++itE5;
  CPPUNIT_ASSERT(  itE5 == len5.end() );

  // Nodes list of the graph
  // -----------------------

  const list<GenNode<int,double>*>& lnn5 = g.accessNodes();

  list<GenNode<int,double>*>::const_iterator itN5 = lnn5.begin();
  CPPUNIT_ASSERT( *itN5 == pn4 );
  ++itN5;
  CPPUNIT_ASSERT( *itN5 == pn2 );
  ++itN5;
  CPPUNIT_ASSERT( *itN5 == pn1 );
  ++itN5;
  CPPUNIT_ASSERT( *itN5 == pn3 );
  ++itN5;
  CPPUNIT_ASSERT(  itN5 == lnn5.end() );

  // NODE n1
  // -------

  CPPUNIT_ASSERT_EQUAL( pn1->data(), 1  );
  CPPUNIT_ASSERT_EQUAL( (int)pn1->flag(), 10 );
  
  const list<GenEdge<int,double>*>& ln1 = pn1->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)ln1.size(), 2 );
  CPPUNIT_ASSERT( ln1.front() == pe12 );
  CPPUNIT_ASSERT( ln1.back()  == pe13 );

  // NODE n2
  // -------

  CPPUNIT_ASSERT_EQUAL( pn2->data(), 2  );
  CPPUNIT_ASSERT_EQUAL( (int)pn2->flag(), 20 );
  
  const list<GenEdge<int,double>*>& ln2 = pn2->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)ln2.size(), 3 );

  list<GenEdge<int,double>*>::const_iterator itE2 = ln2.begin();
  CPPUNIT_ASSERT( *itE2 == pe42 );
  ++itE2;
  CPPUNIT_ASSERT( *itE2 == pe12 );
  ++itE2;
  CPPUNIT_ASSERT( *itE2 == pe23 );

  // NODE n3
  // -------

  CPPUNIT_ASSERT_EQUAL( pn3->data(), 3  );
  CPPUNIT_ASSERT_EQUAL( (int)pn3->flag(), 30 );
  
  const list<GenEdge<int,double>*>& ln3 = pn3->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)ln3.size(), 2 );
  CPPUNIT_ASSERT( ln3.front() == pe23 );
  CPPUNIT_ASSERT( ln3.back()  == pe13 );

  // NODE n4
  // -------

  CPPUNIT_ASSERT_EQUAL( pn4->data(), 4  );
  CPPUNIT_ASSERT_EQUAL( (int)pn4->flag(), 40 );
  
  const list<GenEdge<int,double>*>& ln4 = pn4->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)ln4.size(), 1 );
  CPPUNIT_ASSERT( ln4.front() == pe42 );

  // EDGE e12
  // --------

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe12->data(), 12., 0.  );
  CPPUNIT_ASSERT_EQUAL( (int)pe12->flag(), 120 );
  CPPUNIT_ASSERT( pe12->pSource() == pn1 );
  CPPUNIT_ASSERT( pe12->pTarget() == pn2 );

  // EDGE e13
  // --------

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe13->data(), 13., 0.  );
  CPPUNIT_ASSERT_EQUAL( (int)pe13->flag(), 130 );
  CPPUNIT_ASSERT( pe13->pSource() == pn1 );
  CPPUNIT_ASSERT( pe13->pTarget() == pn3 );

  // EDGE e23
  // --------

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe23->data(), 23., 0.  );
  CPPUNIT_ASSERT_EQUAL( (int)pe23->flag(), 230 );
  CPPUNIT_ASSERT( pe23->pSource() == pn2 );
  CPPUNIT_ASSERT( pe23->pTarget() == pn3 );

  // EDGE e42
  // --------

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe42->data(), 42., 0.  );
  CPPUNIT_ASSERT_EQUAL( (int)pe42->flag(), 420 );
  CPPUNIT_ASSERT( pe42->pSource() == pn4 );
  CPPUNIT_ASSERT( pe42->pTarget() == pn2 );

  // REMOVE NODE n3
  // --------------

  list<GenNode<int,double>*>& len = g.getNodes();
  list<GenNode<int,double>*>::iterator itN = len.begin();
  ++itN;  // -> n2
  ++itN;  // -> n1
  ++itN;  // -> n3
  CPPUNIT_ASSERT( *itN == pn3 );
  
  GenNode<int,double>* prn3 = g.remove(itN);
  CPPUNIT_ASSERT( prn3 == pn3 );
  CPPUNIT_ASSERT( (prn3->accessEdges()).empty() );

  delete pn3;

  //          e12  n2   e42   n4
  //    n1 O-------O----------O
  //
  //
  // NODES LIST = n4  -> n2  -> n1
  // EDGES LIST = e42 -> e12
  //
  // edges list of n1 = e12
  // edges list of n2 = e42 -> e12
  // edges list of n4 = e42
  //
  // edges list of n3 = NIL

  // Edges list of the graph

  const list<GenEdge<int,double>*>& len3 = g.accessEdges();

  list<GenEdge<int,double>*>::const_iterator itE3 = len3.begin();
  CPPUNIT_ASSERT( *itE3 == pe42 );
  ++itE3;
  CPPUNIT_ASSERT( *itE3 == pe12 );
  ++itE3;
  CPPUNIT_ASSERT(  itE3 == len3.end() );

  // Nodes list of the graph
  // -----------------------

  const list<GenNode<int,double>*>& lnn3 = g.accessNodes();

  list<GenNode<int,double>*>::const_iterator itN3 = lnn3.begin();
  CPPUNIT_ASSERT( *itN3 == pn4 );
  ++itN3;
  CPPUNIT_ASSERT( *itN3 == pn2 );
  ++itN3;
  CPPUNIT_ASSERT( *itN3 == pn1 );
  ++itN3;
  CPPUNIT_ASSERT(  itN3 == lnn3.end() );

  // NODE n1
  // -------

  CPPUNIT_ASSERT_EQUAL( pn1->data(), 1  );
  CPPUNIT_ASSERT_EQUAL( (int)pn1->flag(), 10 );
  
  const list<GenEdge<int,double>*>& ln10 = pn1->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)ln10.size(), 1 );
  CPPUNIT_ASSERT( ln10.front() == pe12 );

  // NODE n2
  // -------

  CPPUNIT_ASSERT_EQUAL( pn2->data(), 2  );
  CPPUNIT_ASSERT_EQUAL( (int)pn2->flag(), 20 );
  
  const list<GenEdge<int,double>*>& ln20 = pn2->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)ln20.size(), 2 );
  CPPUNIT_ASSERT( ln20.front() == pe42 );
  CPPUNIT_ASSERT( ln20.back()  == pe12 );

  // NODE n4
  // -------

  CPPUNIT_ASSERT_EQUAL( pn4->data(), 4  );
  CPPUNIT_ASSERT_EQUAL( (int)pn4->flag(), 40 );
  
  const list<GenEdge<int,double>*>& ln40 = pn4->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)ln40.size(), 1 );
  CPPUNIT_ASSERT( ln40.front() == pe42 );

  // EDGE e12
  // --------

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe12->data(), 12., 0.  );
  CPPUNIT_ASSERT_EQUAL( (int)pe12->flag(), 120 );
  CPPUNIT_ASSERT( pe12->pSource() == pn1 );
  CPPUNIT_ASSERT( pe12->pTarget() == pn2 );

  // EDGE e42
  // --------

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe42->data(), 42., 0.  );
  CPPUNIT_ASSERT_EQUAL( (int)pe42->flag(), 420 );
  CPPUNIT_ASSERT( pe42->pSource() == pn4 );
  CPPUNIT_ASSERT( pe42->pTarget() == pn2 );
}



void
GenUGraphTest::testRemoveEdge()
{
  GenUGraph<int,double> g;

  // CONSTRUCTION OF A GRAPH
  // -----------------------
  //
  //          e12  n2   e42   n4
  //    n1 O-------O----------O      O n5
  //        \     /
  //     e13 \   / e23
  //          \ / 
  //           O
  //           n3
  //
  // NODES LIST = n5  -> n4  -> n2  -> n1  -> n3
  // EDGES LIST = e42 -> e12 -> e23 -> e13
  //
  // edges list of n1 = e12 -> e13
  // edges list of n2 = e42 -> e12 -> e23
  // edges list of n3 = e23 -> e13
  // edges list of n4 = e42
  // edges list of n5 = NIL

  // The graph is constructed in a way different
  // from that of function testGraphFeatures and of function testRemoveNode,
  // but its structure should be the same

  GenNode<int,double>* pn5  = g.addNode(5, 50);
  GenEdge<int,double>* pe42 = g.addEdge(42., 420);
  GenNode<int,double>* pn4  = g.addNodeAtSource(pe42, 4, 40);
  GenNode<int,double>* pn2  = g.addNodeAtTarget(pe42, 2, 20);
  GenNode<int,double>* pn1  = g.addNode(1, 10);
  GenEdge<int,double>* pe12 = g.addEdge(pn1, pn2, 12., 120);
  GenNode<int,double>* pn3  = g.addNode(3, 30);
  GenEdge<int,double>* pe23 = g.addEdge(pn2, pn3, 23., 230);
  GenEdge<int,double>* pe13 = g.addEdge(pn1, pn3, 13., 130);

  // Edges list of the graph

  list<GenEdge<int,double>*>& leg = g.getEdges();

  list<GenEdge<int,double>*>::iterator itEG = leg.begin();
  CPPUNIT_ASSERT( *itEG == pe42 );
  ++itEG;
  CPPUNIT_ASSERT( *itEG == pe12 );
  ++itEG;
  CPPUNIT_ASSERT( *itEG == pe23 );
  ++itEG;
  CPPUNIT_ASSERT( *itEG == pe13 );
  ++itEG;
  CPPUNIT_ASSERT(  itEG == leg.end() );

  list<GenNode<int,double>*>& lng = g.getNodes();

  list<GenNode<int,double>*>::iterator itNG = lng.begin();
  CPPUNIT_ASSERT( *itNG == pn5 );
  ++itNG;
  CPPUNIT_ASSERT( *itNG == pn4 );
  ++itNG;
  CPPUNIT_ASSERT( *itNG == pn2 );
  ++itNG;
  CPPUNIT_ASSERT( *itNG == pn1 );
  ++itNG;
  CPPUNIT_ASSERT( *itNG == pn3 );
  ++itNG;
  CPPUNIT_ASSERT(  itNG == lng.end() );

  // REMOVE EDGE e12
  // ---------------

  GenEdge<int,double>* pre12 = g.remove(pe12);
  CPPUNIT_ASSERT( pre12 == pe12 );

  delete pe12;

  //
  //               n2   e42   n4
  //    n1 O       O----------O      O n5
  //        \     /
  //     e13 \   / e23
  //          \ / 
  //           O
  //           n3
  //
  // NODES LIST = n5  -> n4  -> n2  -> n1  -> n3
  // EDGES LIST = e42 -> e23 -> e13
  //
  // edges list of n1 = e13
  // edges list of n2 = e42 -> e23
  // edges list of n3 = e23 -> e13
  // edges list of n4 = e42
  // edges list of n5 = NIL
  //
  // REMOVE EDGE = e12

  // Get edges list

  list<GenEdge<int,double>*>& ler12 = g.getEdges();
  list<GenEdge<int,double>*>::iterator itE12 = ler12.begin();

  CPPUNIT_ASSERT( *itE12 == pe42 );
  ++itE12;
  CPPUNIT_ASSERT( *itE12 == pe23 );
  ++itE12;
  CPPUNIT_ASSERT( *itE12 == pe13 );
  ++itE12;
  CPPUNIT_ASSERT(  itE12 == ler12.end() );

  // Get nodes list

  list<GenNode<int,double>*>& ln12 = g.getNodes();
  list<GenNode<int,double>*>::iterator itN12 = ln12.begin();

  CPPUNIT_ASSERT( *itN12 == pn5 );
  ++itN12;
  CPPUNIT_ASSERT( *itN12 == pn4 );
  ++itN12;
  CPPUNIT_ASSERT( *itN12 == pn2 );
  ++itN12;
  CPPUNIT_ASSERT( *itN12 == pn1 );
  ++itN12;
  CPPUNIT_ASSERT( *itN12 == pn3 );
  ++itN12;
  CPPUNIT_ASSERT(  itN12 == ln12.end() );

  // NODE n1
  // -------

  CPPUNIT_ASSERT_EQUAL( pn1->data(), 1  );
  CPPUNIT_ASSERT_EQUAL( (int)pn1->flag(), 10 );
  
  const list<GenEdge<int,double>*>& ln1 = pn1->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)ln1.size(), 1 );
  CPPUNIT_ASSERT( ln1.back()  == pe13 );

  // NODE n2
  // -------

  CPPUNIT_ASSERT_EQUAL( pn2->data(), 2  );
  CPPUNIT_ASSERT_EQUAL( (int)pn2->flag(), 20 );
  
  const list<GenEdge<int,double>*>& ln2 = pn2->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)ln2.size(), 2 );
  CPPUNIT_ASSERT( ln2.front()  == pe42 );
  CPPUNIT_ASSERT( ln2.back()   == pe23 );

  // NODE n3
  // -------

  CPPUNIT_ASSERT_EQUAL( pn3->data(), 3  );
  CPPUNIT_ASSERT_EQUAL( (int)pn3->flag(), 30 );
  
  const list<GenEdge<int,double>*>& ln3 = pn3->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)ln3.size(), 2 );
  CPPUNIT_ASSERT( ln3.front() == pe23 );
  CPPUNIT_ASSERT( ln3.back()  == pe13 );

  // NODE n4
  // -------

  CPPUNIT_ASSERT_EQUAL( pn4->data(), 4  );
  CPPUNIT_ASSERT_EQUAL( (int)pn4->flag(), 40 );
  
  const list<GenEdge<int,double>*>& ln4 = pn4->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)ln4.size(), 1 );
  CPPUNIT_ASSERT( ln4.front() == pe42 );

  // NODE n5
  // -------

  CPPUNIT_ASSERT_EQUAL( pn5->data(), 5  );
  CPPUNIT_ASSERT_EQUAL( (int)pn5->flag(), 50 );
  CPPUNIT_ASSERT( (pn5->accessEdges()).empty() );

  // EDGE e13
  // --------

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe13->data(), 13., 0.  );
  CPPUNIT_ASSERT_EQUAL( (int)pe13->flag(), 130 );
  CPPUNIT_ASSERT( pe13->pSource() == pn1 );
  CPPUNIT_ASSERT( pe13->pTarget() == pn3 );

  // EDGE e23
  // --------

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe23->data(), 23., 0.  );
  CPPUNIT_ASSERT_EQUAL( (int)pe23->flag(), 230 );
  CPPUNIT_ASSERT( pe23->pSource() == pn2 );
  CPPUNIT_ASSERT( pe23->pTarget() == pn3 );

  // EDGE e42
  // --------

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe42->data(), 42., 0.  );
  CPPUNIT_ASSERT_EQUAL( (int)pe42->flag(), 420 );
  CPPUNIT_ASSERT( pe42->pSource() == pn4 );
  CPPUNIT_ASSERT( pe42->pTarget() == pn2 );

  // REMOVE EDGE e13
  // ---------------

  GenEdge<int,double>* pre13 = g.remove(pe13);
  CPPUNIT_ASSERT( pre13 == pe13 );

  delete pe13;

  //
  //               n2   e42   n4
  //    n1 O       O----------O      O n5
  //              /
  //             / e23
  //            / 
  //           O
  //           n3
  //
  // NODES LIST = n5  -> n4  -> n2  -> n1  -> n3
  // EDGES LIST = e42 -> e23
  //
  // edges list of n1 = NIL
  // edges list of n2 = e42 -> e23
  // edges list of n3 = e23
  // edges list of n4 = e42
  // edges list of n5 = NIL
  //
  // REMOVE EDGE = e13

  // Get edges list

  list<GenEdge<int,double>*>& ler13 = g.getEdges();
  list<GenEdge<int,double>*>::iterator itE13 = ler13.begin();

  CPPUNIT_ASSERT( *itE13 == pe42 );
  ++itE13;
  CPPUNIT_ASSERT( *itE13 == pe23 );
  ++itE13;
  CPPUNIT_ASSERT(  itE13 == ler13.end() );

  // Get nodes list

  list<GenNode<int,double>*>& ln13 = g.getNodes();
  list<GenNode<int,double>*>::iterator itN13 = ln13.begin();

  CPPUNIT_ASSERT( *itN13 == pn5 );
  ++itN13;
  CPPUNIT_ASSERT( *itN13 == pn4 );
  ++itN13;
  CPPUNIT_ASSERT( *itN13 == pn2 );
  ++itN13;
  CPPUNIT_ASSERT( *itN13 == pn1 );
  ++itN13;
  CPPUNIT_ASSERT( *itN13 == pn3 );
  ++itN13;
  CPPUNIT_ASSERT(  itN13 == ln13.end() );

  // NODE n1
  // -------

  CPPUNIT_ASSERT_EQUAL( pn1->data(), 1  );
  CPPUNIT_ASSERT_EQUAL( (int)pn1->flag(), 10 );
  CPPUNIT_ASSERT( (pn1->accessEdges()).empty() );

  // NODE n2
  // -------

  CPPUNIT_ASSERT_EQUAL( pn2->data(), 2  );
  CPPUNIT_ASSERT_EQUAL( (int)pn2->flag(), 20 );
  
  const list<GenEdge<int,double>*>& ln20 = pn2->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)ln20.size(), 2 );
  CPPUNIT_ASSERT( ln2.front()  == pe42 );
  CPPUNIT_ASSERT( ln2.back()   == pe23 );

  // NODE n3
  // -------

  CPPUNIT_ASSERT_EQUAL( pn3->data(), 3  );
  CPPUNIT_ASSERT_EQUAL( (int)pn3->flag(), 30 );
  
  const list<GenEdge<int,double>*>& ln30 = pn3->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)ln30.size(), 1 );
  CPPUNIT_ASSERT( ln3.front() == pe23 );

  // NODE n4
  // -------

  CPPUNIT_ASSERT_EQUAL( pn4->data(), 4  );
  CPPUNIT_ASSERT_EQUAL( (int)pn4->flag(), 40 );
  
  const list<GenEdge<int,double>*>& ln40 = pn4->accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)ln40.size(), 1 );
  CPPUNIT_ASSERT( ln40.front() == pe42 );

  // NODE n5
  // -------

  CPPUNIT_ASSERT_EQUAL( pn5->data(), 5  );
  CPPUNIT_ASSERT_EQUAL( (int)pn5->flag(), 50 );
  CPPUNIT_ASSERT( (pn5->accessEdges()).empty() );

  // EDGE e23
  // --------

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe23->data(), 23., 0.  );
  CPPUNIT_ASSERT_EQUAL( (int)pe23->flag(), 230 );
  CPPUNIT_ASSERT( pe23->pSource() == pn2 );
  CPPUNIT_ASSERT( pe23->pTarget() == pn3 );

  // EDGE e42
  // --------

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pe42->data(), 42., 0.  );
  CPPUNIT_ASSERT_EQUAL( (int)pe42->flag(), 420 );
  CPPUNIT_ASSERT( pe42->pSource() == pn4 );
  CPPUNIT_ASSERT( pe42->pTarget() == pn2 );
}


// ----------------------------------------------------------------------
