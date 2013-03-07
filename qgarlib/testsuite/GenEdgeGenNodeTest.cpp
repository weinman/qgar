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
 * @file  GenEdgeGenNodeTest.cpp
 * @brief Implementation of class qgar::GenEdgeGenNodeTest.
 *
 * See file GenEdgeGenNodeTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   September 17, 2004  16:52
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenEdgeGenNodeTest.cpp,v 1.3 2005/01/28 15:56:45 masini Exp $ */



// STD
#include <list>
// QGAR
#include <qgarlib/GenEdge.h>
#include <qgarlib/GenNode.h>
// QGAR TESTS
#include "GenEdgeGenNodeTest.h"



using namespace qgar;
using namespace std;



// ------------------------------------------------------------------
// T E S T F I X T U R E   I M P L
// ------------------------------------------------------------------


void
GenEdgeGenNodeTest::setUp()
{
  /* EMPTY */
}


void
GenEdgeGenNodeTest::tearDown()
{
  /* EMPTY */
}


// -------------------------------------------------------------------
// T E S T   F U N C T I O N S   F O R   E D G E S
// -------------------------------------------------------------------


void
GenEdgeGenNodeTest::testEdgeConstructors()
{
  // DEFAULT CONSTRUCTOR
  // -------------------

  GenEdge<int,double> e0;
  GenEdge<int,double> e1((short int)100);

  CPPUNIT_ASSERT_EQUAL( e0.flag(), (short int)0 );
  CPPUNIT_ASSERT_EQUAL( e1.flag(), (short int)100 );
  CPPUNIT_ASSERT( e0.pSource() == 0 );
  CPPUNIT_ASSERT( e1.pSource() == 0 );
  CPPUNIT_ASSERT( e0.pTarget() == 0 );
  CPPUNIT_ASSERT( e1.pTarget() == 0 );

  // CONSTRUCTOR FROM DATA & FLAG
  // ----------------------------

  GenEdge<int,double> e2(2.);
  GenEdge<int,double> e3(3.,(short int)300);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( e2.data(), 2., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( e3.data(), 3., 0. );
  CPPUNIT_ASSERT_EQUAL( e2.flag(), (short int)0 );
  CPPUNIT_ASSERT_EQUAL( e3.flag(), (short int)300 );
  CPPUNIT_ASSERT( e2.pSource() == 0 );
  CPPUNIT_ASSERT( e3.pSource() == 0 );
  CPPUNIT_ASSERT( e2.pTarget() == 0 );
  CPPUNIT_ASSERT( e3.pTarget() == 0 );

  // CONSTRUCTOR FROM SOURCE, TARGET, & FLAG
  // ---------------------------------------

  GenNode<int,double>* pn1 = new GenNode<int,double>();
  GenNode<int,double>* pn2 = new GenNode<int,double>();
  GenNode<int,double>* pn3 = new GenNode<int,double>();
  GenNode<int,double>* pn4 = new GenNode<int,double>();

  GenEdge<int,double> e4(pn1, pn2);
  GenEdge<int,double> e5(pn3, pn4, (short int)500);

  CPPUNIT_ASSERT_EQUAL( e4.flag(), (short int)0 );
  CPPUNIT_ASSERT_EQUAL( e5.flag(), (short int)500 );
  CPPUNIT_ASSERT( e4.pSource() == pn1 );
  CPPUNIT_ASSERT( e5.pSource() == pn3 );
  CPPUNIT_ASSERT( e4.pTarget() == pn2 );
  CPPUNIT_ASSERT( e5.pTarget() == pn4 );

  // CONSTRUCTOR FROM SOURCE, TARGET, DATA & FLAG
  // --------------------------------------------

  GenEdge<int,double> e6(pn1, pn3, 6.);
  GenEdge<int,double> e7(pn4, pn2, 7., (short int)700);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( e6.data(), 6., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( e7.data(), 7., 0. );
  CPPUNIT_ASSERT_EQUAL( e6.flag(), (short int)0 );
  CPPUNIT_ASSERT_EQUAL( e7.flag(), (short int)700 );
  CPPUNIT_ASSERT( e6.pSource() == pn1 );
  CPPUNIT_ASSERT( e7.pSource() == pn4 );
  CPPUNIT_ASSERT( e6.pTarget() == pn3 );
  CPPUNIT_ASSERT( e7.pTarget() == pn2 );

  // COPY-CONSTRUCTOR
  // ----------------

  GenEdge<int,double> ec7(e7);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( ec7.data(), e7.data(), 0. );
  CPPUNIT_ASSERT_EQUAL( ec7.flag(), e7.flag() );
  CPPUNIT_ASSERT( ec7.pSource() == e7.pSource() );
  CPPUNIT_ASSERT( ec7.pTarget() == e7.pTarget() );

  // DELETIONS
  // ---------
  delete pn1;
  delete pn2;
  delete pn3;
  delete pn4;
}


void
GenEdgeGenNodeTest::testEdgeSet()
{

  // SET EDGE DATA
  // -------------

  GenEdge<int,double> e1(1.,10);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( e1.data(),       1., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( e1.accessData(), 1., 0. );
  CPPUNIT_ASSERT_EQUAL( e1.flag(), (short int)10 );
  CPPUNIT_ASSERT( e1.pSource() == 0 );
  CPPUNIT_ASSERT( e1.pTarget() == 0 );

  e1.setData(2.);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( e1.data(),       2., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( e1.accessData(), 2., 0. );
  CPPUNIT_ASSERT_EQUAL( e1.flag(),       (short int)10 );
  CPPUNIT_ASSERT( e1.pSource() == 0 );
  CPPUNIT_ASSERT( e1.pTarget() == 0 );

  // SET EDGE FLAG
  // -------------

  e1.setFlag(11);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( e1.data(), 2., 0. );
  CPPUNIT_ASSERT_EQUAL( e1.flag(), (short int)11 );
  CPPUNIT_ASSERT( e1.pSource() == 0 );
  CPPUNIT_ASSERT( e1.pTarget() == 0 );

  // SET (POINTER TO) SOURCE NODE
  // ----------------------------

  GenNode<int,double>* psn = new GenNode<int,double>(100,200);
  e1.setPSource(psn);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( e1.data(),       2., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( e1.accessData(), 2., 0. );
  CPPUNIT_ASSERT_EQUAL( e1.flag(),       (short int)11 );

  GenNode<int,double>* pgsn = e1.pSource();
  CPPUNIT_ASSERT( e1.pTarget() == 0 );
  CPPUNIT_ASSERT( pgsn         == psn );
  CPPUNIT_ASSERT_EQUAL( pgsn->data(), 100 );
  CPPUNIT_ASSERT_EQUAL( pgsn->flag(), (short int)200 );

  // SET (POINTER TO) TARGET NODE
  // ----------------------------

  GenNode<int,double>* ptn = new GenNode<int,double>(101,201);
  e1.setPTarget(ptn);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( e1.data(),       2., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( e1.accessData(), 2., 0. );
  CPPUNIT_ASSERT_EQUAL( e1.flag(),       (short int)11 );

  CPPUNIT_ASSERT( e1.pSource() == psn );
  CPPUNIT_ASSERT( e1.pTarget() == ptn );
  CPPUNIT_ASSERT_EQUAL( (e1.pSource())->data(), 100 );
  CPPUNIT_ASSERT_EQUAL( (e1.pSource())->flag(), (short int)200 );
  CPPUNIT_ASSERT_EQUAL( (e1.pTarget())->data(), 101 );
  CPPUNIT_ASSERT_EQUAL( (e1.pTarget())->flag(), (short int)201 );

  // SET (POINTER TO) SOURCE NODE OR TARGET NODE
  // -------------------------------------------

  GenEdge<int,double> e2(2.,20);

  // Set source (as source is void)

  GenNode<int,double>* pstn = new GenNode<int,double>(102,202);
  e2.setPNode(pstn);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( e2.data(),       2., 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( e2.accessData(), 2., 0. );
  CPPUNIT_ASSERT_EQUAL( e2.flag(),       (short int)20 );

  CPPUNIT_ASSERT( e2.pSource() == pstn );
  CPPUNIT_ASSERT( e2.pTarget() == 0 );
  CPPUNIT_ASSERT_EQUAL( pstn->data(), 102 );
  CPPUNIT_ASSERT_EQUAL( pstn->flag(), (short int)202 );

  // Set target (as source is not void)

  e2.setPNode(ptn);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( e2.data(), 2., 0. );
  CPPUNIT_ASSERT_EQUAL( e2.flag(),       (short int)20 );

  CPPUNIT_ASSERT( e2.pSource() == pstn );
  CPPUNIT_ASSERT( e2.pTarget() == ptn );
  CPPUNIT_ASSERT_EQUAL( pstn->data(), 102 );
  CPPUNIT_ASSERT_EQUAL( pstn->flag(), (short int)202 );
  CPPUNIT_ASSERT_EQUAL( ptn->data(), 101 );
  CPPUNIT_ASSERT_EQUAL( ptn->flag(), (short int)201 );

  // Set target (as source and target are not void)

  e2.setPNode(psn);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( e2.data(), 2., 0. );
  CPPUNIT_ASSERT_EQUAL( e2.flag(),       (short int)20 );

  CPPUNIT_ASSERT( e2.pSource() == pstn );
  CPPUNIT_ASSERT( e2.pTarget() == psn );
  CPPUNIT_ASSERT_EQUAL( pstn->data(), 102 );
  CPPUNIT_ASSERT_EQUAL( pstn->flag(), (short int)202 );
  CPPUNIT_ASSERT_EQUAL( psn->data(), 100 );
  CPPUNIT_ASSERT_EQUAL( psn->flag(), (short int)200 );

  // DELETIONS
  // ---------
  delete psn;
  delete ptn;
  delete pstn;
}


void
GenEdgeGenNodeTest::testEdgeSourceTarget()
{
  GenNode<int,double>* psn = new GenNode<int,double>(10,100);
  GenNode<int,double>* ptn = new GenNode<int,double>(20,200);
  GenEdge<int,double> e(psn, ptn, 1., 2);

  // GET SOURCE AND TARGET NODES
  // ---------------------------

  const GenNode<int,double>& rsn = e.accessSource();
  CPPUNIT_ASSERT_EQUAL( rsn.data(), 10 );
  CPPUNIT_ASSERT_EQUAL( rsn.flag(), (short int)100 );
  CPPUNIT_ASSERT( (rsn.accessEdges()).empty() );

  const GenNode<int,double>& rtn = e.accessTarget();
  CPPUNIT_ASSERT_EQUAL( rtn.data(), 20 );
  CPPUNIT_ASSERT_EQUAL( rtn.flag(), (short int)200 );
  CPPUNIT_ASSERT( (rtn.accessEdges()).empty() );

  psn->setData(11);
  psn->setFlag(101);
  ptn->setData(21);
  ptn->setFlag(201);

  CPPUNIT_ASSERT_EQUAL( rsn.data(), 11 );
  CPPUNIT_ASSERT_EQUAL( rsn.flag(), (short int)101 );
  CPPUNIT_ASSERT( (rsn.accessEdges()).empty() );

  CPPUNIT_ASSERT_EQUAL( rtn.data(), 21 );
  CPPUNIT_ASSERT_EQUAL( rtn.flag(), (short int)201 );
  CPPUNIT_ASSERT( (rtn.accessEdges()).empty() );

  // GET A COPY OF SOURCE AND TARGET NODES
  // -------------------------------------

  GenNode<int,double> csn = e.accessSource();
  CPPUNIT_ASSERT_EQUAL( csn.data(), 11 );
  CPPUNIT_ASSERT_EQUAL( csn.flag(), (short int)101 );
  CPPUNIT_ASSERT( (csn.accessEdges()).empty() );

  GenNode<int,double> ctn = e.accessTarget();
  CPPUNIT_ASSERT_EQUAL( ctn.data(), 21 );
  CPPUNIT_ASSERT_EQUAL( ctn.flag(), (short int)201 );
  CPPUNIT_ASSERT( (ctn.accessEdges()).empty() );

  psn->setData(12);
  psn->setFlag(102);
  ptn->setData(22);
  ptn->setFlag(202);

  CPPUNIT_ASSERT_EQUAL( csn.data(), 11 );
  CPPUNIT_ASSERT_EQUAL( csn.flag(), (short int)101 );
  CPPUNIT_ASSERT( (csn.accessEdges()).empty() );

  CPPUNIT_ASSERT_EQUAL( ctn.data(), 21 );
  CPPUNIT_ASSERT_EQUAL( ctn.flag(), (short int)201 );
  CPPUNIT_ASSERT( (ctn.accessEdges()).empty() );

  CPPUNIT_ASSERT_EQUAL( rsn.data(), 12 );
  CPPUNIT_ASSERT_EQUAL( rsn.flag(), (short int)102 );
  CPPUNIT_ASSERT( (rsn.accessEdges()).empty() );

  CPPUNIT_ASSERT_EQUAL( rtn.data(), 22 );
  CPPUNIT_ASSERT_EQUAL( rtn.flag(), (short int)202 );
  CPPUNIT_ASSERT( (rtn.accessEdges()).empty() );

  // DELETIONS
  // ---------
  delete psn;
  delete ptn;
}


void
GenEdgeGenNodeTest::testEdgeOperators()
{
  GenNode<int,double>* psn = new GenNode<int,double>(10,100);
  GenNode<int,double>* ptn = new GenNode<int,double>(20,200);
  GenEdge<int,double> e1(psn, ptn, 1., 2);

  // ASSIGNMENT
  // ----------

  GenEdge<int,double> ec1 = e1;

  CPPUNIT_ASSERT_DOUBLES_EQUAL( ec1.data(), 1., 0. );
  CPPUNIT_ASSERT_EQUAL( ec1.flag(), (short int)2 );

  // SHALLOW COPY:

  CPPUNIT_ASSERT( ec1.pSource() == psn );
  CPPUNIT_ASSERT( ec1.pTarget() == ptn );

  // EQUALITY AND INEQUALITY
  // -----------------------

  GenEdge<int,double> ee1(psn, ptn, 1., 2000);
  GenEdge<int,double> ee1000(psn, ptn, 1000., 2);

  CPPUNIT_ASSERT( ec1 == e1 );
  CPPUNIT_ASSERT( !(ec1 != e1) );

  CPPUNIT_ASSERT( ee1 == e1 );
  CPPUNIT_ASSERT( !(ee1 != e1) );

  CPPUNIT_ASSERT( ee1 == ec1 );
  CPPUNIT_ASSERT( !(ee1 != ec1) );

  CPPUNIT_ASSERT( e1 != ee1000 );
  CPPUNIT_ASSERT( !(e1 == ee1000) );

  CPPUNIT_ASSERT( ec1 != ee1000 );
  CPPUNIT_ASSERT( !(ec1 == ee1000) );

  CPPUNIT_ASSERT( ee1 != ee1000 );
  CPPUNIT_ASSERT( !(ee1 == ee1000) );

  // DELETIONS
  // ---------
  delete psn;
  delete ptn;
}


// -------------------------------------------------------------------
// T E S T   F U N C T I O N S   F O R   N O D E S
// -------------------------------------------------------------------


void
GenEdgeGenNodeTest::testNodeConstructors()
{
  // DEFAULT CONSTRUCTOR
  // -------------------

  GenNode<int,double> n0;
  GenNode<int,double> n1((short int)10);

  CPPUNIT_ASSERT_EQUAL( n0.flag(), (short int)0 );
  CPPUNIT_ASSERT_EQUAL( n1.flag(), (short int)10 );
  CPPUNIT_ASSERT( (n0.accessEdges()).empty() );
  CPPUNIT_ASSERT( (n1.accessEdges()).empty() );

  // CONSTRUCTOR FROM DATA & FLAG
  // ----------------------------

  GenNode<int,double> n2(2);
  GenNode<int,double> n3(3,(short int)30);

  CPPUNIT_ASSERT_EQUAL( n2.data(), 2 );
  CPPUNIT_ASSERT_EQUAL( n3.data(), 3 );
  CPPUNIT_ASSERT_EQUAL( n2.flag(), (short int)0 );
  CPPUNIT_ASSERT_EQUAL( n3.flag(), (short int)30 );
  CPPUNIT_ASSERT( (n0.accessEdges()).empty() );
  CPPUNIT_ASSERT( (n1.accessEdges()).empty() );

  // CONSTRUCTOR FROM DATA & FLAG, AND 1 EDGE
  // ----------------------------------------

  GenEdge<int,double>* pe4 = new GenEdge<int,double>(4000.);
  GenEdge<int,double>* pe5 = new GenEdge<int,double>(5000.);

  GenNode<int,double> n4(pe4, 4);
  GenNode<int,double> n5(pe5, 5, (short int)50);

  CPPUNIT_ASSERT_EQUAL( n4.data(), 4 );
  CPPUNIT_ASSERT_EQUAL( n5.data(), 5 );
  CPPUNIT_ASSERT_EQUAL( n4.flag(), (short int)0 );
  CPPUNIT_ASSERT_EQUAL( n5.flag(), (short int)50 );

  const list<GenEdge<int,double>*>& le4 = n4.accessEdges();
  const list<GenEdge<int,double>*>& le5 = n5.accessEdges();

  CPPUNIT_ASSERT_EQUAL( (int)le4.size() , 1 );
  CPPUNIT_ASSERT_EQUAL( (int)le5.size() , 1 );
  CPPUNIT_ASSERT( le4.front() == pe4 );
  CPPUNIT_ASSERT( le5.front() == pe5 );

  // CONSTRUCTOR FROM DATA & FLAG, AND 2 EDGES
  // -----------------------------------------

  GenEdge<int,double>* pe6 = new GenEdge<int,double>(6000.);
  GenEdge<int,double>* pe7 = new GenEdge<int,double>(7000.);

  GenNode<int,double> n6(pe6, pe7, 6);
  GenNode<int,double> n7(pe7, pe6, 7, (short int)70);

  CPPUNIT_ASSERT_EQUAL( n6.data(), 6 );
  CPPUNIT_ASSERT_EQUAL( n7.data(), 7 );
  CPPUNIT_ASSERT_EQUAL( n6.flag(), (short int)0 );
  CPPUNIT_ASSERT_EQUAL( n7.flag(), (short int)70 );

  const list<GenEdge<int,double>*>& le6 = n6.accessEdges();
  const list<GenEdge<int,double>*>& le7 = n7.accessEdges();

  CPPUNIT_ASSERT_EQUAL( (int)le6.size() , 2 );
  CPPUNIT_ASSERT_EQUAL( (int)le7.size() , 2 );
  CPPUNIT_ASSERT( le6.front() == pe6 );
  CPPUNIT_ASSERT( le6.back()  == pe7 );
  CPPUNIT_ASSERT( le7.front() == pe7 );
  CPPUNIT_ASSERT( le7.back()  == pe6 );

  // CONSTRUCTOR FROM DATA & FLAG, AND 3 EDGES
  // -----------------------------------------

  GenEdge<int,double>* pe8  = new GenEdge<int,double>(8000.);
  GenEdge<int,double>* pe9  = new GenEdge<int,double>(9000.);
  GenEdge<int,double>* pe10 = new GenEdge<int,double>(10000.);

  GenNode<int,double> n8(pe8, pe9,  pe10, 8);
  GenNode<int,double> n9(pe9, pe10, pe8,  9, (short int)90);

  CPPUNIT_ASSERT_EQUAL( n8.data(),  8 );
  CPPUNIT_ASSERT_EQUAL( n9.data(),  9 );
  CPPUNIT_ASSERT_EQUAL( n8.flag(),  (short int)0 );
  CPPUNIT_ASSERT_EQUAL( n9.flag(),  (short int)90 );

  const list<GenEdge<int,double>*>& le8 = n8.accessEdges();
  const list<GenEdge<int,double>*>& le9 = n9.accessEdges();

  CPPUNIT_ASSERT_EQUAL( (int)le8.size() , 3 );
  CPPUNIT_ASSERT_EQUAL( (int)le9.size() , 3 );
  list<GenEdge<int,double>*>::const_iterator it8 = le8.begin();
  list<GenEdge<int,double>*>::const_iterator it9 = le9.begin();
  CPPUNIT_ASSERT( *it8 == pe8 );
  CPPUNIT_ASSERT( *it9 == pe9 );
  ++it8;
  ++it9;
  CPPUNIT_ASSERT( *it8 == pe9 );
  CPPUNIT_ASSERT( *it9 == pe10 );
  ++it8;
  ++it9;
  CPPUNIT_ASSERT( *it8 == pe10 );
  CPPUNIT_ASSERT( *it9 == pe8 );

  // COPY-CONSTRUCTOR
  // ----------------

  GenNode<int,double> nc5(n5);

  CPPUNIT_ASSERT_EQUAL( nc5.data(), n5.data() );
  CPPUNIT_ASSERT_EQUAL( nc5.flag(), n5.flag() );

  const list<GenEdge<int,double>*>& lnc5 = nc5.accessEdges();
  CPPUNIT_ASSERT( lnc5.front() == le5.front() );

  // DELETIONS
  // ---------
  delete pe4;
  delete pe5;
  delete pe6;
  delete pe7;
  delete pe8;
  delete pe9;
  delete pe10;
}


void
GenEdgeGenNodeTest::testNodeSet()
{
  // SET NODE DATA
  // -------------

  GenNode<int,double> n(1, 10);
  CPPUNIT_ASSERT_EQUAL( n.data(),       1 );
  CPPUNIT_ASSERT_EQUAL( n.accessData(), 1 );
  CPPUNIT_ASSERT_EQUAL( n.flag(),       (short int)10 );
  CPPUNIT_ASSERT( (n.accessEdges()).empty() );

  n.setData(2);
  CPPUNIT_ASSERT_EQUAL( n.data(),       2 );
  CPPUNIT_ASSERT_EQUAL( n.accessData(), 2 );
  CPPUNIT_ASSERT_EQUAL( n.flag(),       (short int)10 );
  CPPUNIT_ASSERT( (n.accessEdges()).empty() );

  // SET NODE FLAG
  // -------------

  n.setFlag(11);
  CPPUNIT_ASSERT_EQUAL( n.data(), 2 );
  CPPUNIT_ASSERT_EQUAL( n.flag(), (short int)11 );
  CPPUNIT_ASSERT( (n.accessEdges()).empty() );
}



void
GenEdgeGenNodeTest::testNodeSetEdgesList()
{
  GenNode<int,double> n1(1,10);
  GenNode<int,double> n2(2,20);

  GenEdge<int,double>* pe1 = new GenEdge<int,double>(1.,10);
  GenEdge<int,double>* pe2 = new GenEdge<int,double>(2.,20);
  GenEdge<int,double>* pe3 = new GenEdge<int,double>(3.,30);

  // ADD (A POINTER TO) AN EDGE
  // --------------------------

  // ADD TO AN EMPTY EDGES LIST

  n1.addEdge(pe1);
  const list<GenEdge<int,double>*>& lea = n1.accessEdges();

  CPPUNIT_ASSERT_EQUAL( n1.data(), 1 );
  CPPUNIT_ASSERT_EQUAL( n1.flag(), (short int)10 );
  CPPUNIT_ASSERT_EQUAL( (int)lea.size(), 1 );
  CPPUNIT_ASSERT( lea.front() == pe1 );

  n2.addEdgeFront(pe2);
  const list<GenEdge<int,double>*>& le2 = n2.accessEdges();

  CPPUNIT_ASSERT_EQUAL( n2.data(), 2 );
  CPPUNIT_ASSERT_EQUAL( n2.flag(), (short int)20 );
  CPPUNIT_ASSERT_EQUAL( (int)le2.size(), 1 );
  CPPUNIT_ASSERT( le2.front() == pe2 );

  // ADD AT BACK AND FRONT
  //
  // *->*->*
  // |  |  |
  // v  v  v
  // 3  1  2

  n1.addEdge(pe2);
  n1.addEdgeFront(pe3);

  CPPUNIT_ASSERT_EQUAL( n1.data(), 1 );
  CPPUNIT_ASSERT_EQUAL( n1.flag(), (short int)10 );
  CPPUNIT_ASSERT_EQUAL( (int)lea.size(), 3 );

  list<GenEdge<int,double>*>::const_iterator itEA = lea.begin();
  CPPUNIT_ASSERT( *itEA == pe3 );
  ++itEA;
  CPPUNIT_ASSERT( *itEA == pe1 );
  ++itEA;
  CPPUNIT_ASSERT( *itEA == pe2 );

  // REMOVE EDGE AT GIVEN POSITION
  // -----------------------------

  list<GenEdge<int,double>*>& leg = n1.getEdges();

  // REMOVE EDGE 1

  list<GenEdge<int,double>*>::iterator itEG = leg.begin();
  ++itEG;
  GenEdge<int,double>* pre = n1.removeEdge(itEG);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pre->data(), 1., 0. );
  CPPUNIT_ASSERT_EQUAL( pre->flag(), (short int)10 );

  CPPUNIT_ASSERT_EQUAL( n1.data(), 1 );
  CPPUNIT_ASSERT_EQUAL( n1.flag(), (short int)10 );
  CPPUNIT_ASSERT_EQUAL( (int)leg.size(), 2 );
  itEG = leg.begin();
  CPPUNIT_ASSERT( *itEG == pe3 );
  ++itEG;
  CPPUNIT_ASSERT( *itEG == pe2 );

  // REMOVE EDGE 2

  pre = n1.removeEdge(itEG);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pre->data(), 2., 0. );
  CPPUNIT_ASSERT_EQUAL( pre->flag(), (short int)20 );

  CPPUNIT_ASSERT_EQUAL( n1.data(), 1 );
  CPPUNIT_ASSERT_EQUAL( n1.flag(), (short int)10 );
  CPPUNIT_ASSERT_EQUAL( (int)leg.size(), 1 );
  itEG = leg.begin();
  CPPUNIT_ASSERT( *itEG == pe3 );

  // REMOVE EDGE 3

  pre = n1.removeEdge(itEG);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pre->data(), 3., 0. );
  CPPUNIT_ASSERT_EQUAL( pre->flag(), (short int)30 );

  CPPUNIT_ASSERT_EQUAL( n1.data(), 1 );
  CPPUNIT_ASSERT_EQUAL( n1.flag(), (short int)10 );
  CPPUNIT_ASSERT_EQUAL( (int)leg.size(), 0 );

  // REMOVE "END"

  itEG = leg.end();
  pre = n1.removeEdge(itEG);

  CPPUNIT_ASSERT_EQUAL( n1.data(), 1 );
  CPPUNIT_ASSERT_EQUAL( n1.flag(), (short int)10 );
  CPPUNIT_ASSERT_EQUAL( (int)leg.size(), 0 );

  // REMOVE POINTERS TO EDGE
  // -----------------------

  // *->*->*
  // |  |  |
  // v  v  v
  // 1  2  2

  n1.addEdge(pe1);
  n1.addEdge(pe2);
  n1.addEdge(pe2);

  // REMOVE 2

  pre = n1.removeEdge(pe2);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pre->data(), 2., 0. );
  CPPUNIT_ASSERT_EQUAL( pre->flag(), (short int)20 );

  CPPUNIT_ASSERT_EQUAL( n1.data(), 1 );
  CPPUNIT_ASSERT_EQUAL( n1.flag(), (short int)10 );
  CPPUNIT_ASSERT_EQUAL( (int)leg.size(), 2 );

  itEG = leg.begin();
  CPPUNIT_ASSERT( *itEG == pe1 );
  ++itEG;
  CPPUNIT_ASSERT( *itEG == pe2 );

  // REMOVE 2 AGAIN

  pre = n1.removeEdge(pe2);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pre->data(), 2., 0. );
  CPPUNIT_ASSERT_EQUAL( pre->flag(), (short int)20 );

  CPPUNIT_ASSERT_EQUAL( n1.data(), 1 );
  CPPUNIT_ASSERT_EQUAL( n1.flag(), (short int)10 );
  CPPUNIT_ASSERT_EQUAL( (int)leg.size(), 1 );

  itEG = leg.begin();
  CPPUNIT_ASSERT( *itEG == pe1 );

  // REMOVE NULL POINTER

  pre = n1.removeEdge(0);

  CPPUNIT_ASSERT( pre == 0 );

  CPPUNIT_ASSERT_EQUAL( n1.data(), 1 );
  CPPUNIT_ASSERT_EQUAL( n1.flag(), (short int)10 );
  CPPUNIT_ASSERT_EQUAL( (int)leg.size(), 1 );

  itEG = leg.begin();
  CPPUNIT_ASSERT( *itEG == pe1 );

  // REMOVE 1

  pre = n1.removeEdge(pe1);

  CPPUNIT_ASSERT_DOUBLES_EQUAL( pre->data(), 1., 0. );
  CPPUNIT_ASSERT_EQUAL( pre->flag(), (short int)10 );

  CPPUNIT_ASSERT_EQUAL( n1.data(), 1 );
  CPPUNIT_ASSERT_EQUAL( n1.flag(), (short int)10 );
  CPPUNIT_ASSERT_EQUAL( (int)leg.size(), 0 );

  // REMOVE IN EMPTY EDGES LIST

  pre = n1.removeEdge(pe3);

  CPPUNIT_ASSERT( pre == 0 );

  CPPUNIT_ASSERT_EQUAL( n1.data(), 1 );
  CPPUNIT_ASSERT_EQUAL( n1.flag(), (short int)10 );
  CPPUNIT_ASSERT_EQUAL( (int)leg.size(), 0 );

  // DELETIONS
  // ---------
  delete pe1;
  delete pe2;
  delete pe3;
}



void
GenEdgeGenNodeTest::testNodeAccessEdgesList()
{
  GenEdge<int,double>* pe1 = new GenEdge<int,double>(1.,10);
  GenEdge<int,double>* pe2 = new GenEdge<int,double>(2.,20);
  GenEdge<int,double>* pe3 = new GenEdge<int,double>(3.,30);

  GenNode<int,double> n(1,10);

  // *->*->*
  // |  |  |
  // v  v  v
  // 1  2  3

  n.addEdge(pe1);
  n.addEdge(pe2);
  n.addEdge(pe3);

  // GET THE EDGES LIST
  // ------------------

  list<GenEdge<int,double>*>& le = n.getEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le.size(), 3 );

  list<GenEdge<int,double>*>::iterator itE = le.begin();
  CPPUNIT_ASSERT( *itE == pe1 );
  ++itE;
  CPPUNIT_ASSERT( *itE == pe2 );
  ++itE;
  CPPUNIT_ASSERT( *itE == pe3 );

  // REMOVE 3 FROM THE LIST

  le.erase(itE);
  CPPUNIT_ASSERT_EQUAL( (int)le.size(), 2 );

  // THE EDGES OF THE NODE IS ALTERED

  const list<GenEdge<int,double>*>& le1 = n.accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le1.size(), 2 );

  list<GenEdge<int,double>*>::const_iterator ictE1 = le1.begin();
  CPPUNIT_ASSERT( *ictE1 == pe1 );
  ++ictE1;
  CPPUNIT_ASSERT( *ictE1 == pe2 );

  // REMOVE 1 FROM THE LIST

  le.remove(pe1);
  CPPUNIT_ASSERT_EQUAL( (int)le.size(), 1 );

  // THE EDGES OF THE NODE IS ALTERED

  const list<GenEdge<int,double>*> le2 = n.accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le2.size(), 1 );

  list<GenEdge<int,double>*>::const_iterator ictE2 = le2.begin();
  CPPUNIT_ASSERT( *ictE2 == pe2 );

  // GET A COPY OF THE EDGES LIST
  // ----------------------------

  GenNode<int,double> nc(1,10);

  // *->*->*
  // |  |  |
  // v  v  v
  // 1  2  3

  nc.addEdge(pe1);
  nc.addEdge(pe2);
  nc.addEdge(pe3);

  list<GenEdge<int,double>*> lec = nc.edges();
  CPPUNIT_ASSERT_EQUAL( (int)lec.size(), 3 );

  list<GenEdge<int,double>*>::iterator itEC = lec.begin();
  CPPUNIT_ASSERT( *itEC == pe1 );
  ++itEC;
  CPPUNIT_ASSERT( *itEC == pe2 );
  ++itEC;
  CPPUNIT_ASSERT( *itEC == pe3 );

  // REMOVE 3 FROM THE COPIED LIST

  lec.erase(itEC);

  CPPUNIT_ASSERT_EQUAL( (int)lec.size(), 2 );
  itEC = lec.begin();
  CPPUNIT_ASSERT( *itEC == pe1 );
  ++itEC;
  CPPUNIT_ASSERT( *itEC == pe2 );

  // THE EDGES LIST OF THE NODE IS UNCHANGED

  const list<GenEdge<int,double>*>& le3 = nc.accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le3.size(), 3 );

  list<GenEdge<int,double>*>::const_iterator ictEC = le3.begin();
  CPPUNIT_ASSERT( *ictEC == pe1 );
  ++ictEC;
  CPPUNIT_ASSERT( *ictEC == pe2 );
  ++ictEC;
  CPPUNIT_ASSERT( *ictEC == pe3 );

  // DELETIONS
  // ---------
  delete pe1;
  delete pe2;
  delete pe3;
}



void
GenEdgeGenNodeTest::testNodeOperators()
{
  GenEdge<int,double>* pe1 = new GenEdge<int,double>(1.,10);
  GenEdge<int,double>* pe2 = new GenEdge<int,double>(2.,20);

  GenNode<int,double> n1(1,10);

  // *->*
  // |  |
  // v  v
  // 1  2

  n1.addEdge(pe1);
  n1.addEdge(pe2);

  // ASSIGNMENT
  // ----------

  GenNode<int,double> nc1 = n1;

  CPPUNIT_ASSERT_EQUAL( nc1.data(), 1 );
  CPPUNIT_ASSERT_EQUAL( nc1.flag(), (short int)10 );

  const list<GenEdge<int,double>*>& le1 = nc1.accessEdges();
  CPPUNIT_ASSERT_EQUAL( (int)le1.size(), 2 );

  // SHALLOW COPY

  list<GenEdge<int,double>*>::const_iterator itE = le1.begin();
  CPPUNIT_ASSERT( *itE == pe1 );
  ++itE;
  CPPUNIT_ASSERT( *itE == pe2 );

  // EQUALITY AND INEQUALITY
  // -----------------------

  GenNode<int,double> nn1(1,20);
  GenNode<int,double> nn1000(1000,20);

  CPPUNIT_ASSERT( nc1 == n1 );
  CPPUNIT_ASSERT( !(nc1 != n1) );

  CPPUNIT_ASSERT( nc1 == nn1 );
  CPPUNIT_ASSERT( !(nc1 != nn1) );

  CPPUNIT_ASSERT( n1 == nn1 );
  CPPUNIT_ASSERT( !(n1 != nn1) );

  CPPUNIT_ASSERT( nn1000 != n1 );
  CPPUNIT_ASSERT( !(nn1000 == n1) );

  CPPUNIT_ASSERT( nn1000 != nn1 );
  CPPUNIT_ASSERT( !(nn1000 == nn1) );

  CPPUNIT_ASSERT( nn1000 != nc1 );
  CPPUNIT_ASSERT( !(nn1000 == nc1) );
}

// ----------------------------------------------------------------------
