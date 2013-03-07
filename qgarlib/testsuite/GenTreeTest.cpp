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
 * @file  GenTreeTest.cpp
 * @brief Implementation of class GenTreeTest
 *
 *        See file GenTreeTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   March 1, 2004  22:05
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenTreeTest.cpp,v 1.3 2005/01/28 15:56:46 masini Exp $ */



// STD
#include <vector>
// QGAR
#include <qgarlib/primitives.h>
// QGAR TESTS
#include "GenTreeTest.h"



using namespace qgar;
using namespace std;



// ------------------------------------------------------------------
// T E S T F I X T U R E   I M P L
// ------------------------------------------------------------------

void
GenTreeTest::setUp()
{
  // VOID
}

// -------------------------------------------------------------------

void
GenTreeTest::tearDown()
{
  // VOID
}


// -------------------------------------------------------------------
// TEST FUNCTIONS FOR CLASS GENTREENODE
// -------------------------------------------------------------------

void
GenTreeTest::testNodeData()
{
  // INTEGERS

  // Access
  GenTreeNode<int> node = GenTreeNode<int>(878);

  int data  = node.accessData();
  int datac = node.data();
  CPPUNIT_ASSERT_EQUAL( data,  878);
  CPPUNIT_ASSERT_EQUAL( datac, 878);

  // Set
  node.setData(333);
  data  = node.accessData();
  datac = node.data();
  CPPUNIT_ASSERT_EQUAL( data,  333);
  CPPUNIT_ASSERT_EQUAL( datac, 333);

  // POINTS

  Point p(44, 55);
  GenTreeNode<Point> nodep(p);

   // Access
   Point pd   = nodep.data();
   CPPUNIT_ASSERT_EQUAL( pd.x(),   44 );
   CPPUNIT_ASSERT_EQUAL( pd.y(),   55 );
   Point pad = nodep.accessData();
   CPPUNIT_ASSERT_EQUAL( (nodep.accessData()).x(), 44 );
   CPPUNIT_ASSERT_EQUAL( (nodep.accessData()).y(), 55 );
   CPPUNIT_ASSERT_EQUAL( pad.x(), 44 );
   CPPUNIT_ASSERT_EQUAL( pad.y(), 55 );

   // Data is copied before storage
   p.setXY(444, 555);
   CPPUNIT_ASSERT_EQUAL( pd.x(),   44 );
   CPPUNIT_ASSERT_EQUAL( pd.y(),   55 );
   CPPUNIT_ASSERT_EQUAL( pad.x(), 44 );
   CPPUNIT_ASSERT_EQUAL( pad.y(), 55 );

   // Set
   nodep.setData(p);
   pd = nodep.data();
   CPPUNIT_ASSERT_EQUAL( p.x(),    444 );
   CPPUNIT_ASSERT_EQUAL( p.y(),    555 );
   CPPUNIT_ASSERT_EQUAL( pad.x(), 44 );
   CPPUNIT_ASSERT_EQUAL( pad.y(), 55 );
   CPPUNIT_ASSERT_EQUAL( pd.x(),   444 );
   CPPUNIT_ASSERT_EQUAL( pd.y(),   555 );
   CPPUNIT_ASSERT_EQUAL( (nodep.accessData()).x(), 444 );
   CPPUNIT_ASSERT_EQUAL( (nodep.accessData()).y(), 555 );

   // POINTERS TO POINTS

   Point* pp = new Point(1414, 1732);
   GenTreeNode<Point*> nodepp(pp);

   // Access
   Point* ppd  = nodepp.data();
   CPPUNIT_ASSERT_EQUAL( pp->x(),   1414 );
   CPPUNIT_ASSERT_EQUAL( pp->y(),   1732 );
   CPPUNIT_ASSERT_EQUAL( ppd->x(),  1414 );
   CPPUNIT_ASSERT_EQUAL( ppd->y(),  1732 );
   CPPUNIT_ASSERT_EQUAL( (nodepp.accessData())->x(), 1414 );
   CPPUNIT_ASSERT_EQUAL( (nodepp.accessData())->y(), 1732 );

   // Pointed data is not copied for storage
   pp->setXY(141, 173);
   ppd = nodepp.data();
   CPPUNIT_ASSERT_EQUAL( pp->x(),   141 );
   CPPUNIT_ASSERT_EQUAL( pp->y(),   173 );
   CPPUNIT_ASSERT_EQUAL( ppd->x(),  141 );
   CPPUNIT_ASSERT_EQUAL( ppd->y(),  173 );
   CPPUNIT_ASSERT_EQUAL( (nodepp.accessData())->x(), 141 );
   CPPUNIT_ASSERT_EQUAL( (nodepp.accessData())->y(), 173 );

   // Set
   nodepp.setData(&p);
   ppd  = nodepp.data();
   CPPUNIT_ASSERT_EQUAL( p.x(),     444 );
   CPPUNIT_ASSERT_EQUAL( p.y(),     555 );
   CPPUNIT_ASSERT_EQUAL( ppd->x(),  444 );
   CPPUNIT_ASSERT_EQUAL( ppd->y(),  555 );
   CPPUNIT_ASSERT_EQUAL( (nodepp.accessData())->x(), 444 );
   CPPUNIT_ASSERT_EQUAL( (nodepp.accessData())->y(), 555 );

   // Pointers give access to stored data
   (nodepp.accessData())->setXY(1000, 2000);
   CPPUNIT_ASSERT_EQUAL( p.x(), 1000 );
   CPPUNIT_ASSERT_EQUAL( p.y(), 2000 );
   CPPUNIT_ASSERT_EQUAL( (nodepp.accessData())->x(), 1000 );
   CPPUNIT_ASSERT_EQUAL( (nodepp.accessData())->y(), 2000 );
   CPPUNIT_ASSERT_EQUAL( ppd->x(),  1000 );
   CPPUNIT_ASSERT_EQUAL( ppd->y(),  2000 );
}

// -------------------------------------------------------------------
// TEST FUNCTIONS FOR CLASS GENTREE
// -------------------------------------------------------------------

// =======
// NO TEST
// =======

void
GenTreeTest::testEmpty()
{
  // NO TEST
}

// -------------------------------------------------------------------

void
GenTreeTest::testPRoot()
{
  // NO TEST
}

// -------------------------------------------------------------------

void
GenTreeTest::testPCurrent()
{
  // NO TEST
}

// -------------------------------------------------------------------

void
GenTreeTest::testPParent()
{
  // NO TEST
}

// -------------------------------------------------------------------

void
GenTreeTest::testPLSibling()
{
  // NO TEST
}

// -------------------------------------------------------------------

void
GenTreeTest::testPRSibling()
{
  // NO TEST
}

// -------------------------------------------------------------------

void
GenTreeTest::testPFirstChild()
{
  // NO TEST
}

// ----------------------------------------------------------------------

void
GenTreeTest::testSetPRoot()
{
  // NO TEST
}

// -------------------------------------------------------------------

void
GenTreeTest::testSetPCurrent()
{
  // NO TEST
}

// -------------------------------------------------------------------

void
GenTreeTest::testSetPParent()
{
  // NO TEST
}

// -------------------------------------------------------------------

void
GenTreeTest::testSetPLSibling()
{
  // NO TEST
}

// -------------------------------------------------------------------

void
GenTreeTest::testSetPRSibling()
{
  // NO TEST
}

// -------------------------------------------------------------------

void
GenTreeTest::testSetPFirstChild()
{
  // NO TEST
}

// -------------------------------------------------------------------

void
GenTreeTest::testGotoRoot()
{
  // NO TEST
}

// -------------------------------------------------------------------

void
GenTreeTest::testGotoParent()
{
  // NO TEST
}

// -------------------------------------------------------------------

void
GenTreeTest::testGotoLSibling()
{
  // NO TEST
}

// -------------------------------------------------------------------

void
GenTreeTest::testGotoRSibling()
{
  // NO TEST
}

// -------------------------------------------------------------------

void
GenTreeTest::testGotoFirstChild()
{
  // NO TEST
}

// ==============
// EFECTIVE TESTS
// ==============

void
GenTreeTest::testDefaultConstructor()
{
  GenTree<double> tree;

  // No root neither current node
  CPPUNIT_ASSERT( tree.pRoot()    == 0);
  CPPUNIT_ASSERT( tree.pCurrent() == 0);
}

// -------------------------------------------------------------------

void
GenTreeTest::testBuildFromData()
{
  GenTree<int> tree(99);

  // Check pointers to root and current node
  CPPUNIT_ASSERT( tree.pRoot() != 0 );
  CPPUNIT_ASSERT( tree.pRoot() == tree.pCurrent() );

  // Given data is stored in current node
  GenTreeNode<int>* pr = tree.pRoot();
  int data = pr->data();
  CPPUNIT_ASSERT_EQUAL( data, 99 );

  // Tree includes a single node
  // Check from the node
  CPPUNIT_ASSERT( pr->pParent()     == 0 );
  CPPUNIT_ASSERT( pr->pLSibling()   == 0 );
  CPPUNIT_ASSERT( pr->pRSibling()   == 0 );
  CPPUNIT_ASSERT( pr->pFirstChild() == 0 );
  CPPUNIT_ASSERT( pr->accessData()  == 99 );
  // Check from the tree (current node is root)
  CPPUNIT_ASSERT( tree.pParent()     == 0 );
  CPPUNIT_ASSERT( tree.pLSibling()   == 0 );
  CPPUNIT_ASSERT( tree.pRSibling()   == 0 );
  CPPUNIT_ASSERT( tree.pFirstChild() == 0 );
  CPPUNIT_ASSERT( tree.accessData()  == 99 );
}

// -------------------------------------------------------------------

void
GenTreeTest::testData()
{
  // TREE OF POINTS (current node is root)

  Point p12(1,2);
  GenTree<Point> treep(p12);

  // Access to data
  Point pd = treep.data();
  CPPUNIT_ASSERT_EQUAL( (treep.accessData()).x(), 1 );
  CPPUNIT_ASSERT_EQUAL( (treep.accessData()).y(), 2 );
  CPPUNIT_ASSERT_EQUAL( pd.x(),                   1 );
  CPPUNIT_ASSERT_EQUAL( pd.y(),                   2 );

  // Set data
  Point p34(3,4);
  treep.setData(p34);

  pd = treep.data();
  CPPUNIT_ASSERT_EQUAL( (treep.accessData()).x(), 3 );
  CPPUNIT_ASSERT_EQUAL( (treep.accessData()).y(), 4 );
  CPPUNIT_ASSERT_EQUAL( pd.x(),                   3 );
  CPPUNIT_ASSERT_EQUAL( pd.y(),                   4 );

  // Data is copied
  p34.setXY(4,3);
  CPPUNIT_ASSERT_EQUAL( p34.x(), 4 );
  CPPUNIT_ASSERT_EQUAL( p34.y(), 3 );

  pd = treep.data();
  CPPUNIT_ASSERT_EQUAL( (treep.accessData()).x(), 3 );
  CPPUNIT_ASSERT_EQUAL( (treep.accessData()).y(), 4 );
  CPPUNIT_ASSERT_EQUAL( pd.x(),                   3 );
  CPPUNIT_ASSERT_EQUAL( pd.y(),                   4 );

  // TREE OF POINTERS TO POINTS (current node is root)

  GenTree<Point*> treepp(&p12);

  // Access to data
  Point* ppd  = treepp.data();
  Point* ppad = treepp.accessData();
  CPPUNIT_ASSERT_EQUAL( ppd->x(),  1 );
  CPPUNIT_ASSERT_EQUAL( ppd->y(),  2 );
  CPPUNIT_ASSERT_EQUAL( ppad->x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ppad->y(), 2 );

  // Set data
  treepp.setData(&p34);

  CPPUNIT_ASSERT_EQUAL( ppd->x(),  1 );
  CPPUNIT_ASSERT_EQUAL( ppd->y(),  2 );
  CPPUNIT_ASSERT_EQUAL( ppad->x(), 1 );
  CPPUNIT_ASSERT_EQUAL( ppad->y(), 2 );
  ppd  = treepp.data();
  ppad = treepp.accessData();
  CPPUNIT_ASSERT_EQUAL( ppad->x(), 4 );
  CPPUNIT_ASSERT_EQUAL( ppad->y(), 3 );
  CPPUNIT_ASSERT_EQUAL( ppd->x(),  4 );
  CPPUNIT_ASSERT_EQUAL( ppd->y(),  3 );

  // Direct modification of data
  p34.setXY(3,4);
  CPPUNIT_ASSERT_EQUAL( p34.x(), 3 );
  CPPUNIT_ASSERT_EQUAL( p34.y(), 4 );

  CPPUNIT_ASSERT_EQUAL( ppad->x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ppad->y(), 4 );
  CPPUNIT_ASSERT_EQUAL( ppd->x(),  3 );
  CPPUNIT_ASSERT_EQUAL( ppd->y(),  4 );
  ppd  = treepp.data();
  ppad = treepp.accessData();
  CPPUNIT_ASSERT_EQUAL( ppad->x(), 3 );
  CPPUNIT_ASSERT_EQUAL( ppad->y(), 4 );
  CPPUNIT_ASSERT_EQUAL( ppd->x(),  3 );
  CPPUNIT_ASSERT_EQUAL( ppd->y(),  4 );
}

// -------------------------------------------------------------------

void
GenTreeTest::testInsertNode()
{
  // EMPTY TREES
  // -----------

  GenTree<int> tree1;
  tree1.insertParent(1);
  GenTreeNode<int>* ptr = tree1.pRoot();
  CPPUNIT_ASSERT( ptr->pParent()     == 0 );
  CPPUNIT_ASSERT( ptr->pLSibling()   == 0 );
  CPPUNIT_ASSERT( ptr->pRSibling()   == 0 );
  CPPUNIT_ASSERT( ptr->pFirstChild() == 0 );
  CPPUNIT_ASSERT_EQUAL( tree1.data(), 1 );

  GenTree<int> tree2;
  tree2.insertLSibling(2);
  ptr = tree2.pRoot();
  CPPUNIT_ASSERT( ptr->pParent()     == 0 );
  CPPUNIT_ASSERT( ptr->pLSibling()   == 0 );
  CPPUNIT_ASSERT( ptr->pRSibling()   == 0 );
  CPPUNIT_ASSERT( ptr->pFirstChild() == 0 );
  CPPUNIT_ASSERT_EQUAL( tree2.data(), 2 );

  GenTree<int> tree3;
  tree3.insertRSibling(3);
  ptr = tree3.pRoot();
  CPPUNIT_ASSERT( ptr->pParent()     == 0 );
  CPPUNIT_ASSERT( ptr->pLSibling()   == 0 );
  CPPUNIT_ASSERT( ptr->pRSibling()   == 0 );
  CPPUNIT_ASSERT( ptr->pFirstChild() == 0 );
  CPPUNIT_ASSERT_EQUAL( tree3.data(), 3 );

  GenTree<int> tree4;
  tree4.insertFirstChild(4);
  ptr = tree4.pRoot();
  CPPUNIT_ASSERT( ptr->pParent()     == 0 );
  CPPUNIT_ASSERT( ptr->pLSibling()   == 0 );
  CPPUNIT_ASSERT( ptr->pRSibling()   == 0 );
  CPPUNIT_ASSERT( ptr->pFirstChild() == 0 );
  CPPUNIT_ASSERT_EQUAL( tree4.data(), 4 );

  // CONSTRUCTION OF A NON-EMPTY TREE
  // --------------------------------

  GenTree<int> tree;

  // INSERT NODE 122
  tree.insertRSibling(122);
  CPPUNIT_ASSERT_EQUAL( tree.data(), 122 );   // Current node is 122
  // INSERT NODE 1222
  tree.insertFirstChild(1222);
  CPPUNIT_ASSERT_EQUAL( tree.data(), 122 );   // Current node is 122
  // INSERT NODE 1221
  tree.insertFirstChild(1221);
  CPPUNIT_ASSERT_EQUAL( tree.data(), 122 );   // Current node is 122

  // **********************************************************************
  /*
                       122
                       / \
                      /   \
                   1221   1222
  */
  // Root and current node
  CPPUNIT_ASSERT( (tree.pRoot())->data()    == 122 );
  CPPUNIT_ASSERT( (tree.pCurrent())->data() == 122 );
  tree.gotoRoot();
  CPPUNIT_ASSERT( (tree.pRoot())->data()    == 122 );
  CPPUNIT_ASSERT( (tree.pCurrent())->data() == 122 );
  
  // Node 122
  CPPUNIT_ASSERT( tree.data()                  == 122 );
  CPPUNIT_ASSERT( tree.pParent()               == 0 );
  CPPUNIT_ASSERT( tree.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pFirstChild())->data() == 1221 );
  // Node 1221
  tree.gotoFirstChild();
  CPPUNIT_ASSERT( tree.data()                  == 1221 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 122 );
  CPPUNIT_ASSERT( tree.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pRSibling())->data()   == 1222 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // Node 1222
  tree.gotoRSibling();
  CPPUNIT_ASSERT( tree.data()                  == 1222 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 122 );
  CPPUNIT_ASSERT( (tree.pLSibling())->data()   == 1221 );
  CPPUNIT_ASSERT( tree.pRSibling()             == 0 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // **********************************************************************

  CPPUNIT_ASSERT_EQUAL( tree.data(), 1222 );  // Current node is 1222
  tree.gotoRoot();
  CPPUNIT_ASSERT_EQUAL( tree.data(), 122 );   // Current node is 122
  // INSERT NODE 12
  tree.insertParent(12);
  CPPUNIT_ASSERT_EQUAL( tree.data(), 122 );   // Current node is 122
  // INSERT NODE 121
  tree.insertLSibling(121);
  CPPUNIT_ASSERT_EQUAL( tree.data(), 122 );   // Current node is 122

  // **********************************************************************
  /*
           12
           |\
           | \
           |  \
           |   \
          121  122
               / \
              /   \
           1221   1222
  */
  // Root and current
  CPPUNIT_ASSERT( (tree.pRoot())->data()    == 12 );
  CPPUNIT_ASSERT( (tree.pCurrent())->data() == 122 );
  tree.gotoRoot();
  CPPUNIT_ASSERT( (tree.pRoot())->data()    == 12 );
  CPPUNIT_ASSERT( (tree.pCurrent())->data() == 12 );
  // Node 12
  CPPUNIT_ASSERT( tree.data()                  == 12 );
  CPPUNIT_ASSERT( tree.pParent()               == 0 );
  CPPUNIT_ASSERT( tree.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pFirstChild())->data() == 121 );
  // Node 121
  tree.gotoFirstChild();
  CPPUNIT_ASSERT( tree.data()                  == 121 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 12 );
  CPPUNIT_ASSERT( tree.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pRSibling())->data()   == 122 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // Node 122
  tree.gotoRSibling();
  CPPUNIT_ASSERT( tree.data()                  == 122 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 12 );
  CPPUNIT_ASSERT( (tree.pLSibling())->data()   == 121 );
  CPPUNIT_ASSERT( tree.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pFirstChild())->data() == 1221 );
  // Node 1221
  tree.gotoFirstChild();
  CPPUNIT_ASSERT( tree.data()                  == 1221 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 122 );
  CPPUNIT_ASSERT( tree.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pRSibling())->data()   == 1222 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // Node 1222
  tree.gotoRSibling();
  CPPUNIT_ASSERT( tree.data()                  == 1222 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 122 );
  CPPUNIT_ASSERT( (tree.pLSibling())->data()   == 1221 );
  CPPUNIT_ASSERT( tree.pRSibling()             == 0 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // **********************************************************************

  tree.gotoRoot();
  CPPUNIT_ASSERT_EQUAL( tree.data(), 12 );    // Current node is 12
  // INSERT NODE 1
  tree.insertParent(1);
  CPPUNIT_ASSERT_EQUAL( tree.data(), 12 );   // Current node is 12
  // INSERT NODE 11
  tree.insertLSibling(11);
  CPPUNIT_ASSERT_EQUAL( tree.data(), 12 );   // Current node is 12
  // INSERT NODE 111
  tree.gotoLSibling();
  CPPUNIT_ASSERT_EQUAL( tree.data(), 11 );  // Current node is 11
  tree.insertFirstChild(111);
  // INSERT NODE 115
  tree.gotoFirstChild();
  CPPUNIT_ASSERT_EQUAL( tree.data(), 111 ); // Current node is 111
  tree.insertRSibling(115);
  // INSERT NODE 113
  CPPUNIT_ASSERT_EQUAL( tree.data(), 111 ); // Current node is 111
  tree.insertRSibling(113);
  // INSERT NODE 112
  tree.gotoRSibling();
  CPPUNIT_ASSERT_EQUAL( tree.data(), 113 ); // Current node is 113
  tree.insertLSibling(112);
  // INSERT NODE 114
  CPPUNIT_ASSERT_EQUAL( tree.data(), 113 ); // Current node is 113
  tree.insertRSibling(114);

  // **********************************************************************
  /*
               1
              /\
             /  \
            /    \
           /      \
          11      12
         /|\       |\
        / | \      | \
       /  |  \     |  \
      /       \    |   \
    111  to  115  121  122
                       / \
                      /   \
                   1221   1222
  */
  // Root and current
  CPPUNIT_ASSERT( (tree.pRoot())->data()    == 1 );
  CPPUNIT_ASSERT( (tree.pCurrent())->data() == 113 );
  tree.gotoRoot();
  CPPUNIT_ASSERT( (tree.pRoot())->data()    == 1 );
  CPPUNIT_ASSERT( (tree.pCurrent())->data() == 1 );
  // Node 1
  CPPUNIT_ASSERT( tree.data()                  == 1 );
  CPPUNIT_ASSERT( tree.pParent()               == 0 );
  CPPUNIT_ASSERT( tree.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pFirstChild())->data() == 11 );
  // Node 11
  tree.gotoFirstChild();
  CPPUNIT_ASSERT( tree.data()                  == 11 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 1  );
  CPPUNIT_ASSERT( tree.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pRSibling())->data()   == 12 );
  CPPUNIT_ASSERT( (tree.pFirstChild())->data() == 111 );
  // Node 111
  tree.gotoFirstChild();
  CPPUNIT_ASSERT( tree.data()                  == 111 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 11 );
  CPPUNIT_ASSERT( tree.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pRSibling())->data()   == 112 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // Node 112
  tree.gotoRSibling();
  CPPUNIT_ASSERT( tree.data()                  == 112 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 11 );
  CPPUNIT_ASSERT( (tree.pLSibling())->data()   == 111 );
  CPPUNIT_ASSERT( (tree.pRSibling())->data()   == 113 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // Node 113
  tree.gotoRSibling();
  CPPUNIT_ASSERT( tree.data()                  == 113 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 11 );
  CPPUNIT_ASSERT( (tree.pLSibling())->data()   == 112 );
  CPPUNIT_ASSERT( (tree.pRSibling())->data()   == 114 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // Node 114
  tree.gotoRSibling();
  CPPUNIT_ASSERT( tree.data()                  == 114 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 11 );
  CPPUNIT_ASSERT( (tree.pLSibling())->data()   == 113 );
  CPPUNIT_ASSERT( (tree.pRSibling())->data()   == 115 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // Node 115
  tree.gotoRSibling();
  CPPUNIT_ASSERT( tree.data()                  == 115 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 11 );
  CPPUNIT_ASSERT( (tree.pLSibling())->data()   == 114 );
  CPPUNIT_ASSERT( tree.pRSibling()             == 0 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
 // Node 12
  tree.gotoParent();    // go to 11
  tree.gotoRSibling();  // go to 12
  CPPUNIT_ASSERT( tree.data()                  == 12 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 1 );
  CPPUNIT_ASSERT( (tree.pLSibling())->data()   == 11 );
  CPPUNIT_ASSERT( tree.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pFirstChild())->data() == 121 );
  // Node 121
  tree.gotoFirstChild();
  CPPUNIT_ASSERT( tree.data()                  == 121 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 12 );
  CPPUNIT_ASSERT( tree.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pRSibling())->data()   == 122 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // Node 122
  tree.gotoRSibling();
  CPPUNIT_ASSERT( tree.data()                  == 122 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 12 );
  CPPUNIT_ASSERT( (tree.pLSibling())->data()   == 121 );
  CPPUNIT_ASSERT( tree.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pFirstChild())->data() == 1221 );
  // Node 1221
  tree.gotoFirstChild();
  CPPUNIT_ASSERT( tree.data()                  == 1221 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 122 );
  CPPUNIT_ASSERT( tree.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pRSibling())->data()   == 1222 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // Node 1222
  tree.gotoRSibling();
  CPPUNIT_ASSERT( tree.data()                  == 1222 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 122 );
  CPPUNIT_ASSERT( (tree.pLSibling())->data()   == 1221 );
  CPPUNIT_ASSERT( tree.pRSibling()             == 0 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // **********************************************************************

  // Last checks!
  CPPUNIT_ASSERT( (tree.pCurrent())->data() == 1222 );
  CPPUNIT_ASSERT( (tree.pRoot())->data()    == 1 );
}

// -------------------------------------------------------------------

void
GenTreeTest::testInsertLSiblingThrow()
{
  GenTree<int> tree(1);
  // Add left sibling to root: Should throw a user exception
  tree.insertLSibling(1515);
}


// -------------------------------------------------------------------

void
GenTreeTest::testInsertRSiblingThrow()
{
  GenTree<int> tree(1);
  // Add right sibling to root: Should throw a user exception
  tree.insertRSibling(1515);
}

// -------------------------------------------------------------------

void
GenTreeTest::testCopyConstructor()
{
  // CONSTRUCTION OF A NON-EMPTY TREE
  // --------------------------------

  GenTree<int> tree;

  // INSERT NODE 12
  tree.insertRSibling(12);
  CPPUNIT_ASSERT_EQUAL( tree.data(), 12 );   // Current node is 12
  // INSERT NODE 122
  tree.insertFirstChild(122);
  CPPUNIT_ASSERT_EQUAL( tree.data(), 12 );   // Current node is 12
  // INSERT NODE 121
  tree.insertFirstChild(121);
  CPPUNIT_ASSERT_EQUAL( tree.data(), 12 );   // Current node is 12
  // INSERT NODE 120
  tree.insertFirstChild(120);
  CPPUNIT_ASSERT_EQUAL( tree.data(), 12 );   // Current node is 12
  // INSERT NODE 1221
  tree.gotoFirstChild();
  tree.gotoRSibling();
  tree.gotoRSibling();
  CPPUNIT_ASSERT_EQUAL( tree.data(), 122 );  // Current node is 122
  tree.insertFirstChild(1222);
  // INSERT NODE 1221
  CPPUNIT_ASSERT_EQUAL( tree.data(), 122 );  // Current node is 122
  tree.insertFirstChild(1221);

  // CHECK TREE
  // **********************************************************************
  /*
           12
          /|\
         / | \
        /  |  \
       /   |   \
     120  121  122
               / \
              /   \
           1221   1222
  */
  // Node 12
  tree.gotoRoot();
  CPPUNIT_ASSERT( tree.data()                  == 12 );
  CPPUNIT_ASSERT( tree.pParent()               == 0 );
  CPPUNIT_ASSERT( tree.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pFirstChild())->data() == 120 );
  // Node 120
  tree.gotoFirstChild();
  CPPUNIT_ASSERT( tree.data()                  == 120 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 12 );
  CPPUNIT_ASSERT( tree.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pRSibling())->data()   == 121 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // Node 121
  tree.gotoRSibling();
  CPPUNIT_ASSERT( tree.data()                  == 121 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 12 );
  CPPUNIT_ASSERT( (tree.pLSibling())->data()   == 120 );
  CPPUNIT_ASSERT( (tree.pRSibling())->data()   == 122 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // Node 122
  tree.gotoRSibling();
  CPPUNIT_ASSERT( tree.data()                  == 122 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 12 );
  CPPUNIT_ASSERT( (tree.pLSibling())->data()   == 121 );
  CPPUNIT_ASSERT( tree.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pFirstChild())->data() == 1221 );
  // Node 1221
  tree.gotoFirstChild();
  CPPUNIT_ASSERT( tree.data()                  == 1221 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 122 );
  CPPUNIT_ASSERT( tree.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pRSibling())->data()   == 1222 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // Node 1222
  tree.gotoRSibling();
  CPPUNIT_ASSERT( tree.data()                  == 1222 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 122 );
  CPPUNIT_ASSERT( (tree.pLSibling())->data()   == 1221 );
  CPPUNIT_ASSERT( tree.pRSibling()             == 0 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // **********************************************************************

  // COPY TREE
  GenTree<int> treec(tree);

  // CHECK INITIAL TREE IS UNCHANGED
  // **********************************************************************
  /*
           12
          /|\
         / | \
        /  |  \
       /   |   \
     120  121  122
               / \
              /   \
           1221   1222
  */
  // Node 12
  tree.gotoRoot();
  CPPUNIT_ASSERT( tree.data()                  == 12 );
  CPPUNIT_ASSERT( tree.pParent()               == 0 );
  CPPUNIT_ASSERT( tree.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pFirstChild())->data() == 120 );
  // Node 120
  tree.gotoFirstChild();
  CPPUNIT_ASSERT( tree.data()                  == 120 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 12 );
  CPPUNIT_ASSERT( tree.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pRSibling())->data()   == 121 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // Node 121
  tree.gotoRSibling();
  CPPUNIT_ASSERT( tree.data()                  == 121 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 12 );
  CPPUNIT_ASSERT( (tree.pLSibling())->data()   == 120 );
  CPPUNIT_ASSERT( (tree.pRSibling())->data()   == 122 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // Node 122
  tree.gotoRSibling();
  CPPUNIT_ASSERT( tree.data()                  == 122 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 12 );
  CPPUNIT_ASSERT( (tree.pLSibling())->data()   == 121 );
  CPPUNIT_ASSERT( tree.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pFirstChild())->data() == 1221 );
  // Node 1221
  tree.gotoFirstChild();
  CPPUNIT_ASSERT( tree.data()                  == 1221 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 122 );
  CPPUNIT_ASSERT( tree.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pRSibling())->data()   == 1222 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // Node 1222
  tree.gotoRSibling();
  CPPUNIT_ASSERT( tree.data()                  == 1222 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 122 );
  CPPUNIT_ASSERT( (tree.pLSibling())->data()   == 1221 );
  CPPUNIT_ASSERT( tree.pRSibling()             == 0 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // **********************************************************************

  // CHECK COPIED TREE
  // **********************************************************************
  /*
           12
          /|\
         / | \
        /  |  \
       /   |   \
     120  121  122
               / \
              /   \
           1221   1222
  */
  // Node 12
  treec.gotoRoot();
  CPPUNIT_ASSERT( treec.data()                  == 12 );
  CPPUNIT_ASSERT( treec.pParent()               == 0 );
  CPPUNIT_ASSERT( treec.pLSibling()             == 0 );
  CPPUNIT_ASSERT( treec.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (treec.pFirstChild())->data() == 120 );
  // Node 120
  treec.gotoFirstChild();
  CPPUNIT_ASSERT( treec.data()                  == 120 );
  CPPUNIT_ASSERT( (treec.pParent())->data()     == 12 );
  CPPUNIT_ASSERT( treec.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (treec.pRSibling())->data()   == 121 );
  CPPUNIT_ASSERT( treec.pFirstChild()           == 0 );
  // Node 121
  treec.gotoRSibling();
  CPPUNIT_ASSERT( treec.data()                  == 121 );
  CPPUNIT_ASSERT( (treec.pParent())->data()     == 12 );
  CPPUNIT_ASSERT( (treec.pLSibling())->data()   == 120 );
  CPPUNIT_ASSERT( (treec.pRSibling())->data()   == 122 );
  CPPUNIT_ASSERT( treec.pFirstChild()           == 0 );
  // Node 122
  treec.gotoRSibling();
  CPPUNIT_ASSERT( treec.data()                  == 122 );
  CPPUNIT_ASSERT( (treec.pParent())->data()     == 12 );
  CPPUNIT_ASSERT( (treec.pLSibling())->data()   == 121 );
  CPPUNIT_ASSERT( treec.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (treec.pFirstChild())->data() == 1221 );
  // Node 1221
  treec.gotoFirstChild();
  CPPUNIT_ASSERT( treec.data()                  == 1221 );
  CPPUNIT_ASSERT( (treec.pParent())->data()     == 122 );
  CPPUNIT_ASSERT( treec.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (treec.pRSibling())->data()   == 1222 );
  CPPUNIT_ASSERT( treec.pFirstChild()           == 0 );
  // Node 1222
  treec.gotoRSibling();
  CPPUNIT_ASSERT( treec.data()                  == 1222 );
  CPPUNIT_ASSERT( (treec.pParent())->data()     == 122 );
  CPPUNIT_ASSERT( (treec.pLSibling())->data()   == 1221 );
  CPPUNIT_ASSERT( treec.pRSibling()             == 0 );
  CPPUNIT_ASSERT( treec.pFirstChild()           == 0 );
  // **********************************************************************

  // CHECK TREES DO NOT SHARE ANY NODE
  // **********************************************************************
  /*
           12
          /|\
         / | \
        /  |  \
       /   |   \
     120  121  122
               / \
              /   \
           1221   1222
  */
  // Node 12
  tree.gotoRoot();
  treec.gotoRoot();
  tree.setData(312);
  CPPUNIT_ASSERT_EQUAL( tree.data(),  312 );
  CPPUNIT_ASSERT_EQUAL( treec.data(), 12 );
  // Node 120
  tree.gotoFirstChild();
  treec.gotoFirstChild();
  tree.setData(3120);
  CPPUNIT_ASSERT_EQUAL( tree.data(),  3120 );
  CPPUNIT_ASSERT_EQUAL( treec.data(), 120 );
  // Node 121
  tree.gotoRSibling();
  treec.gotoRSibling();
  tree.setData(3121);
  CPPUNIT_ASSERT_EQUAL( tree.data(),  3121 );
  CPPUNIT_ASSERT_EQUAL( treec.data(), 121 );
  // Node 122
  tree.gotoRSibling();
  treec.gotoRSibling();
  tree.setData(3122);
  CPPUNIT_ASSERT_EQUAL( tree.data(),  3122 );
  CPPUNIT_ASSERT_EQUAL( treec.data(), 122 );
  // Node 1221
  tree.gotoFirstChild();
  treec.gotoFirstChild();
  tree.setData(31221);
  CPPUNIT_ASSERT_EQUAL( tree.data(),  31221 );
  CPPUNIT_ASSERT_EQUAL( treec.data(), 1221 );
  // Node 1222
  tree.gotoRSibling();
  treec.gotoRSibling();
  tree.setData(31222);
  CPPUNIT_ASSERT_EQUAL( tree.data(),  31222 );
  CPPUNIT_ASSERT_EQUAL( treec.data(), 1222 );

  // **********************************************************************
}

// -------------------------------------------------------------------

void
GenTreeTest::testAssignment()
{
  // CONSTRUCTION OF A NON-EMPTY TREE
  // --------------------------------

  GenTree<int> tree;

  // INSERT NODE 12
  tree.insertRSibling(12);
  CPPUNIT_ASSERT_EQUAL( tree.data(), 12 );   // Current node is 12
  // INSERT NODE 122
  tree.insertFirstChild(122);
  CPPUNIT_ASSERT_EQUAL( tree.data(), 12 );   // Current node is 12
  // INSERT NODE 121
  tree.insertFirstChild(121);
  CPPUNIT_ASSERT_EQUAL( tree.data(), 12 );   // Current node is 12
  // INSERT NODE 120
  tree.insertFirstChild(120);
  CPPUNIT_ASSERT_EQUAL( tree.data(), 12 );   // Current node is 12
  // INSERT NODE 1221
  tree.gotoFirstChild();
  tree.gotoRSibling();
  tree.gotoRSibling();
  CPPUNIT_ASSERT_EQUAL( tree.data(), 122 );  // Current node is 122
  tree.insertFirstChild(1222);
  // INSERT NODE 1221
  CPPUNIT_ASSERT_EQUAL( tree.data(), 122 );  // Current node is 122
  tree.insertFirstChild(1221);

  // CHECK TREE
  // **********************************************************************
  /*
           12
          /|\
         / | \
        /  |  \
       /   |   \
     120  121  122
               / \
              /   \
           1221   1222
  */
  // Node 12
  tree.gotoRoot();
  CPPUNIT_ASSERT( tree.data()                  == 12 );
  CPPUNIT_ASSERT( tree.pParent()               == 0 );
  CPPUNIT_ASSERT( tree.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pFirstChild())->data() == 120 );
  // Node 120
  tree.gotoFirstChild();
  CPPUNIT_ASSERT( tree.data()                  == 120 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 12 );
  CPPUNIT_ASSERT( tree.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pRSibling())->data()   == 121 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // Node 121
  tree.gotoRSibling();
  CPPUNIT_ASSERT( tree.data()                  == 121 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 12 );
  CPPUNIT_ASSERT( (tree.pLSibling())->data()   == 120 );
  CPPUNIT_ASSERT( (tree.pRSibling())->data()   == 122 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // Node 122
  tree.gotoRSibling();
  CPPUNIT_ASSERT( tree.data()                  == 122 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 12 );
  CPPUNIT_ASSERT( (tree.pLSibling())->data()   == 121 );
  CPPUNIT_ASSERT( tree.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pFirstChild())->data() == 1221 );
  // Node 1221
  tree.gotoFirstChild();
  CPPUNIT_ASSERT( tree.data()                  == 1221 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 122 );
  CPPUNIT_ASSERT( tree.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pRSibling())->data()   == 1222 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // Node 1222
  tree.gotoRSibling();
  CPPUNIT_ASSERT( tree.data()                  == 1222 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 122 );
  CPPUNIT_ASSERT( (tree.pLSibling())->data()   == 1221 );
  CPPUNIT_ASSERT( tree.pRSibling()             == 0 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // **********************************************************************

  // COPY TREE
  GenTree<int> treec = tree;

  // CHECK INITIAL TREE IS UNCHANGED
  // **********************************************************************
  /*
           12
          /|\
         / | \
        /  |  \
       /   |   \
     120  121  122
               / \
              /   \
           1221   1222
  */
  // Node 12
  tree.gotoRoot();
  CPPUNIT_ASSERT( tree.data()                  == 12 );
  CPPUNIT_ASSERT( tree.pParent()               == 0 );
  CPPUNIT_ASSERT( tree.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pFirstChild())->data() == 120 );
  // Node 120
  tree.gotoFirstChild();
  CPPUNIT_ASSERT( tree.data()                  == 120 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 12 );
  CPPUNIT_ASSERT( tree.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pRSibling())->data()   == 121 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // Node 121
  tree.gotoRSibling();
  CPPUNIT_ASSERT( tree.data()                  == 121 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 12 );
  CPPUNIT_ASSERT( (tree.pLSibling())->data()   == 120 );
  CPPUNIT_ASSERT( (tree.pRSibling())->data()   == 122 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // Node 122
  tree.gotoRSibling();
  CPPUNIT_ASSERT( tree.data()                  == 122 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 12 );
  CPPUNIT_ASSERT( (tree.pLSibling())->data()   == 121 );
  CPPUNIT_ASSERT( tree.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pFirstChild())->data() == 1221 );
  // Node 1221
  tree.gotoFirstChild();
  CPPUNIT_ASSERT( tree.data()                  == 1221 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 122 );
  CPPUNIT_ASSERT( tree.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pRSibling())->data()   == 1222 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // Node 1222
  tree.gotoRSibling();
  CPPUNIT_ASSERT( tree.data()                  == 1222 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 122 );
  CPPUNIT_ASSERT( (tree.pLSibling())->data()   == 1221 );
  CPPUNIT_ASSERT( tree.pRSibling()             == 0 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  // **********************************************************************

  // CHECK COPIED TREE
  // **********************************************************************
  /*
           12
          /|\
         / | \
        /  |  \
       /   |   \
     120  121  122
               / \
              /   \
           1221   1222
  */
  // Node 12
  treec.gotoRoot();
  CPPUNIT_ASSERT( treec.data()                  == 12 );
  CPPUNIT_ASSERT( treec.pParent()               == 0 );
  CPPUNIT_ASSERT( treec.pLSibling()             == 0 );
  CPPUNIT_ASSERT( treec.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (treec.pFirstChild())->data() == 120 );
  // Node 120
  treec.gotoFirstChild();
  CPPUNIT_ASSERT( treec.data()                  == 120 );
  CPPUNIT_ASSERT( (treec.pParent())->data()     == 12 );
  CPPUNIT_ASSERT( treec.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (treec.pRSibling())->data()   == 121 );
  CPPUNIT_ASSERT( treec.pFirstChild()           == 0 );
  // Node 121
  treec.gotoRSibling();
  CPPUNIT_ASSERT( treec.data()                  == 121 );
  CPPUNIT_ASSERT( (treec.pParent())->data()     == 12 );
  CPPUNIT_ASSERT( (treec.pLSibling())->data()   == 120 );
  CPPUNIT_ASSERT( (treec.pRSibling())->data()   == 122 );
  CPPUNIT_ASSERT( treec.pFirstChild()           == 0 );
  // Node 122
  treec.gotoRSibling();
  CPPUNIT_ASSERT( treec.data()                  == 122 );
  CPPUNIT_ASSERT( (treec.pParent())->data()     == 12 );
  CPPUNIT_ASSERT( (treec.pLSibling())->data()   == 121 );
  CPPUNIT_ASSERT( treec.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (treec.pFirstChild())->data() == 1221 );
  // Node 1221
  treec.gotoFirstChild();
  CPPUNIT_ASSERT( treec.data()                  == 1221 );
  CPPUNIT_ASSERT( (treec.pParent())->data()     == 122 );
  CPPUNIT_ASSERT( treec.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (treec.pRSibling())->data()   == 1222 );
  CPPUNIT_ASSERT( treec.pFirstChild()           == 0 );
  // Node 1222
  treec.gotoRSibling();
  CPPUNIT_ASSERT( treec.data()                  == 1222 );
  CPPUNIT_ASSERT( (treec.pParent())->data()     == 122 );
  CPPUNIT_ASSERT( (treec.pLSibling())->data()   == 1221 );
  CPPUNIT_ASSERT( treec.pRSibling()             == 0 );
  CPPUNIT_ASSERT( treec.pFirstChild()           == 0 );
  // **********************************************************************

  // CHECK TREES DO NOT SHARE ANY NODE
  // **********************************************************************
  /*
           12
          /|\
         / | \
        /  |  \
       /   |   \
     120  121  122
               / \
              /   \
           1221   1222
  */
  // Node 12
  tree.gotoRoot();
  treec.gotoRoot();
  tree.setData(312);
  CPPUNIT_ASSERT_EQUAL( tree.data(),  312 );
  CPPUNIT_ASSERT_EQUAL( treec.data(), 12 );
  // Node 120
  tree.gotoFirstChild();
  treec.gotoFirstChild();
  tree.setData(3120);
  CPPUNIT_ASSERT_EQUAL( tree.data(),  3120 );
  CPPUNIT_ASSERT_EQUAL( treec.data(), 120 );
  // Node 121
  tree.gotoRSibling();
  treec.gotoRSibling();
  tree.setData(3121);
  CPPUNIT_ASSERT_EQUAL( tree.data(),  3121 );
  CPPUNIT_ASSERT_EQUAL( treec.data(), 121 );
  // Node 122
  tree.gotoRSibling();
  treec.gotoRSibling();
  tree.setData(3122);
  CPPUNIT_ASSERT_EQUAL( tree.data(),  3122 );
  CPPUNIT_ASSERT_EQUAL( treec.data(), 122 );
  // Node 1221
  tree.gotoFirstChild();
  treec.gotoFirstChild();
  tree.setData(31221);
  CPPUNIT_ASSERT_EQUAL( tree.data(),  31221 );
  CPPUNIT_ASSERT_EQUAL( treec.data(), 1221 );
  // Node 1222
  tree.gotoRSibling();
  treec.gotoRSibling();
  tree.setData(31222);
  CPPUNIT_ASSERT_EQUAL( tree.data(),  31222 );
  CPPUNIT_ASSERT_EQUAL( treec.data(), 1222 );

  // **********************************************************************
}

// -------------------------------------------------------------------

void
GenTreeTest::testBuildFromNode()
{
  // CREATE AN EMPTY TREE

  GenTreeNode<int>* pE = 0;
  GenTree<int> treeE(pE);
  CPPUNIT_ASSERT( treeE.pRoot()    == 0 );
  CPPUNIT_ASSERT( treeE.pCurrent() == 0 );

  // CREATE A NON-EMPTY TREE

  /*
              1
	     /|\
            / | \
          11  12 13
              |
             121
   */
  GenTree<int> tree(1);
  tree.insertFirstChild(13);
  tree.insertFirstChild(12);
  tree.insertFirstChild(11);
  tree.gotoFirstChild();
  tree.gotoRSibling();
  tree.insertFirstChild(121);

  // Create copy of subtree 12
  GenTree<int> treec(tree.pCurrent());

  // Check copy
  CPPUNIT_ASSERT( (treec.pRoot())->data()      == 12 );
  CPPUNIT_ASSERT( (treec.pCurrent())->data()   == 12 );

  CPPUNIT_ASSERT( treec.data()                  == 12 );
  CPPUNIT_ASSERT( treec.pParent()               == 0 );
  CPPUNIT_ASSERT( treec.pLSibling()             == 0 );
  CPPUNIT_ASSERT( treec.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (treec.pFirstChild())->data() == 121 );
  // Change data
  treec.setData(712);

  treec.gotoFirstChild();
  CPPUNIT_ASSERT( treec.data()                  == 121 );
  CPPUNIT_ASSERT( (treec.pParent())->data()     == 712 );
  CPPUNIT_ASSERT( treec.pLSibling()             == 0 );
  CPPUNIT_ASSERT( treec.pRSibling()             == 0 );
  CPPUNIT_ASSERT( treec.pFirstChild()           == 0 );
  // Change data
  treec.setData(7121);

  // Check initial tree
  CPPUNIT_ASSERT( (tree.pRoot())->data()      == 1 );
  CPPUNIT_ASSERT( (tree.pCurrent())->data()   == 12 );

  tree.gotoRoot();
  CPPUNIT_ASSERT( tree.data()                  == 1 );
  CPPUNIT_ASSERT( tree.pParent()               == 0 );
  CPPUNIT_ASSERT( tree.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pFirstChild())->data() == 11 );
  tree.gotoFirstChild();
  CPPUNIT_ASSERT( tree.data()                  == 11 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 1 );
  CPPUNIT_ASSERT( tree.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (tree.pRSibling())->data()   == 12 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  tree.gotoRSibling();
  CPPUNIT_ASSERT( tree.data()                  == 12 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 1 );
  CPPUNIT_ASSERT( (tree.pLSibling())->data()   == 11 );
  CPPUNIT_ASSERT( (tree.pRSibling())->data()   == 13 );
  CPPUNIT_ASSERT( (tree.pFirstChild())->data() == 121 );
  tree.gotoFirstChild();
  CPPUNIT_ASSERT( tree.data()                  == 121 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 12 );
  CPPUNIT_ASSERT( tree.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree.pRSibling()             == 0 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
  tree.gotoParent();
  tree.gotoRSibling();
  CPPUNIT_ASSERT( tree.data()                  == 13 );
  CPPUNIT_ASSERT( (tree.pParent())->data()     == 1 );
  CPPUNIT_ASSERT( (tree.pLSibling())->data()   == 12 );
  CPPUNIT_ASSERT( tree.pRSibling()             == 0 );
  CPPUNIT_ASSERT( tree.pFirstChild()           == 0 );
}

// -------------------------------------------------------------------

void
GenTreeTest::testMergeLSibling()
{
  // Small reference tree
  GenTree<int> treeM(1);
  treeM.insertFirstChild(11);

  // MERGE AN EMPTY TREE TO AN EMPTY TREE
  // ------------------------------------

   GenTree<int> treeE1;
   GenTree<int> treeE2;

   treeE1.mergeLSibling(treeE2);

   CPPUNIT_ASSERT( treeE1.pRoot()    == 0 );
   CPPUNIT_ASSERT( treeE1.pCurrent() == 0 );
   CPPUNIT_ASSERT( treeE2.pRoot()    == 0 );
   CPPUNIT_ASSERT( treeE2.pCurrent() == 0 );

  // MERGE AN EMPTY TREE TO A NON-EMPTY TREE
  // ---------------------------------------

  treeM.gotoFirstChild();
  treeM.mergeLSibling(treeE1);

  // Check resulting tree

  CPPUNIT_ASSERT( (treeM.pRoot())->data()    == 1 );
  CPPUNIT_ASSERT( (treeM.pCurrent())->data() == 11 );

  treeM.gotoRoot();
  CPPUNIT_ASSERT( treeM.data()                  == 1 );
  CPPUNIT_ASSERT( treeM.pParent()               == 0 );
  CPPUNIT_ASSERT( treeM.pLSibling()             == 0 );
  CPPUNIT_ASSERT( treeM.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (treeM.pFirstChild())->data() == 11 );

  treeM.gotoFirstChild();
  CPPUNIT_ASSERT( treeM.data()                  == 11 );
  CPPUNIT_ASSERT( (treeM.pParent())->data()     == 1 );
  CPPUNIT_ASSERT( treeM.pLSibling()             == 0 );
  CPPUNIT_ASSERT( treeM.pRSibling()             == 0 );
  CPPUNIT_ASSERT( treeM.pFirstChild()           == 0 );

  // MERGE A NON-EMPTY TREE TO AN EMPTY TREE
  // ---------------------------------------

  treeM.gotoRoot();
  GenTree<int> treeE;
  treeE.mergeLSibling(treeM);

  // Check resulting tree

  CPPUNIT_ASSERT( (treeE.pRoot())->data()      == 1 );
  CPPUNIT_ASSERT( (treeE.pCurrent())->data()   == 1 );
  
  CPPUNIT_ASSERT( treeE.data()                  == 1 );
  CPPUNIT_ASSERT( treeE.pParent()               == 0 );
  CPPUNIT_ASSERT( treeE.pLSibling()             == 0 );
  CPPUNIT_ASSERT( treeE.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (treeE.pFirstChild())->data() == 11 );
  // Nodes have been copied
  treeE.setData(91);
  CPPUNIT_ASSERT( treeE.data()                  == 91 );
  CPPUNIT_ASSERT( treeM.data()                  == 1 );

  treeM.gotoFirstChild();
  treeE.gotoFirstChild();
  CPPUNIT_ASSERT( treeE.data()                  == 11 );
  CPPUNIT_ASSERT( (treeE.pParent())->data()     == 91 );
  CPPUNIT_ASSERT( treeE.pLSibling()             == 0 );
  CPPUNIT_ASSERT( treeE.pRSibling()             == 0 );
  CPPUNIT_ASSERT( treeE.pFirstChild()           == 0 );
  // Nodes have been copied
  treeE.setData(911);
  CPPUNIT_ASSERT( treeE.data()                  == 911 );
  CPPUNIT_ASSERT( treeM.data()                  == 11 );

  // MERGE A NON-EMPTY TREE TO A NON-EMPTY TREE
  // ------------------------------------------

  /*
             5                    5
            /|        1          /|\  
           / |   +    |    =    / | \  
          /  |        11       /  |  \ 
         6   7                1   6   7
                              |
                              11
  */
  GenTree<int> tree1(5);
  tree1.insertFirstChild(7);
  tree1.insertFirstChild(6);

  // Merge as left sibling of 6
  tree1.gotoFirstChild();
  tree1.mergeLSibling(treeM);

  // Check resulting tree

  CPPUNIT_ASSERT( (tree1.pRoot())->data()      == 5 );
  CPPUNIT_ASSERT( (tree1.pCurrent())->data()   == 6 );

  tree1.gotoRoot();
  CPPUNIT_ASSERT( tree1.data()                  == 5 );
  CPPUNIT_ASSERT( tree1.pParent()               == 0 );
  CPPUNIT_ASSERT( tree1.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree1.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree1.pFirstChild())->data() == 1 );

  tree1.gotoFirstChild();
  CPPUNIT_ASSERT( tree1.data()                  == 1 );
  CPPUNIT_ASSERT( (tree1.pParent())->data()     == 5 );
  CPPUNIT_ASSERT( tree1.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (tree1.pRSibling())->data()   == 6 );
  CPPUNIT_ASSERT( (tree1.pFirstChild())->data() == 11 );
  // Nodes have been copied
  tree1.setData(81);
  CPPUNIT_ASSERT( tree1.data()                  == 81 );
  treeM.gotoRoot();
  CPPUNIT_ASSERT( treeM.data()                  == 1 );

  tree1.gotoFirstChild();
  CPPUNIT_ASSERT( tree1.data()                  == 11 );
  CPPUNIT_ASSERT( (tree1.pParent())->data()     == 81 );
  CPPUNIT_ASSERT( tree1.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree1.pRSibling()             == 0 );
  CPPUNIT_ASSERT( tree1.pFirstChild()           == 0 );
  // Nodes have been copied
  tree1.setData(811);
  CPPUNIT_ASSERT( tree1.data()                  == 811 );
  treeM.gotoFirstChild();
  CPPUNIT_ASSERT( treeM.data()                  == 11 );

  tree1.gotoParent();
  tree1.gotoRSibling();
  CPPUNIT_ASSERT( tree1.data()                  == 6 );
  CPPUNIT_ASSERT( (tree1.pParent())->data()     == 5 );
  CPPUNIT_ASSERT( (tree1.pLSibling())->data()   == 81 );
  CPPUNIT_ASSERT( (tree1.pRSibling())->data()   == 7 );
  CPPUNIT_ASSERT( tree1.pFirstChild()           == 0 );

  tree1.gotoRSibling();
  CPPUNIT_ASSERT( tree1.data()                  == 7 );
  CPPUNIT_ASSERT( (tree1.pParent())->data()     == 5 );
  CPPUNIT_ASSERT( (tree1.pLSibling())->data()   == 6 );
  CPPUNIT_ASSERT( tree1.pRSibling()             == 0 );
  CPPUNIT_ASSERT( tree1.pFirstChild()           == 0 );

  /*
             5                    5
            /|        1          /|\  
           / |   +    |    =    / | \  
          /  |        11       /  |  \ 
         6   7                6   1   7
                                  |
                                  11
  */
  GenTree<int> tree2(5);
  tree2.insertFirstChild(7);
  tree2.insertFirstChild(6);

  // Merge as left sibling of 7
  tree2.gotoFirstChild();
  tree2.gotoRSibling();
  tree2.mergeLSibling(treeM);

  // Check resulting tree

  CPPUNIT_ASSERT( (tree2.pRoot())->data()      == 5 );
  CPPUNIT_ASSERT( (tree2.pCurrent())->data()   == 7 );

  tree2.gotoRoot();
  CPPUNIT_ASSERT( tree2.data()                  == 5 );
  CPPUNIT_ASSERT( tree2.pParent()               == 0 );
  CPPUNIT_ASSERT( tree2.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree2.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree2.pFirstChild())->data() == 6 );

  tree2.gotoFirstChild();
  CPPUNIT_ASSERT( tree2.data()                  == 6 );
  CPPUNIT_ASSERT( (tree2.pParent())->data()     == 5 );
  CPPUNIT_ASSERT( tree2.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (tree2.pRSibling())->data()   == 1 );
  CPPUNIT_ASSERT( tree2.pFirstChild()           == 0 );

  tree2.gotoRSibling();
  CPPUNIT_ASSERT( tree2.data()                  == 1 );
  CPPUNIT_ASSERT( (tree2.pParent())->data()     == 5 );
  CPPUNIT_ASSERT( (tree2.pLSibling())->data()   == 6 );
  CPPUNIT_ASSERT( (tree2.pRSibling())->data()   == 7 );
  CPPUNIT_ASSERT( (tree2.pFirstChild())->data() == 11 );
  // Nodes have been copied
  tree2.setData(81);
  CPPUNIT_ASSERT( tree2.data()                  == 81 );
  treeM.gotoRoot();
  CPPUNIT_ASSERT( treeM.data()                  == 1 );

  tree2.gotoFirstChild();
  CPPUNIT_ASSERT( tree2.data()                  == 11 );
  CPPUNIT_ASSERT( (tree2.pParent())->data()     == 81 );
  CPPUNIT_ASSERT( tree2.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree2.pRSibling()             == 0 );
  CPPUNIT_ASSERT( tree2.pFirstChild()           == 0 );
  // Nodes have been copied
  tree2.setData(811);
  CPPUNIT_ASSERT( tree2.data()                  == 811 );
  treeM.gotoFirstChild();
  CPPUNIT_ASSERT( treeM.data()                  == 11 );

  tree2.gotoParent();
  tree2.gotoRSibling();
  CPPUNIT_ASSERT( tree2.data()                  == 7 );
  CPPUNIT_ASSERT( (tree2.pParent())->data()     == 5 );
  CPPUNIT_ASSERT( (tree2.pLSibling())->data()   == 81 );
  CPPUNIT_ASSERT( tree2.pRSibling()             == 0 );
  CPPUNIT_ASSERT( tree2.pFirstChild()           == 0 );
}

// -------------------------------------------------------------------

void
GenTreeTest::testMergeLSiblingThrow()
{
  GenTree<int> tree1(1);
  GenTree<int> tree2(2);
  // Current node is the root: Should throw a user exception
  tree1.mergeLSibling(tree2);
}

// -------------------------------------------------------------------

void
GenTreeTest::testMergeRSibling()
{
  // Small reference tree
  GenTree<int> treeM(1);
  treeM.insertFirstChild(11);

  // MERGE AN EMPTY TREE TO AN EMPTY TREE
  // ------------------------------------

   GenTree<int> treeE1;
   GenTree<int> treeE2;

   treeE1.mergeRSibling(treeE2);

   CPPUNIT_ASSERT( treeE1.pRoot()    == 0 );
   CPPUNIT_ASSERT( treeE1.pCurrent() == 0 );
   CPPUNIT_ASSERT( treeE2.pRoot()    == 0 );
   CPPUNIT_ASSERT( treeE2.pCurrent() == 0 );

  // MERGE AN EMPTY TREE TO A NON-EMPTY TREE
  // ---------------------------------------

  treeM.gotoFirstChild();
  treeM.mergeRSibling(treeE1);

  // Check resulting tree

  CPPUNIT_ASSERT( (treeM.pRoot())->data()    == 1 );
  CPPUNIT_ASSERT( (treeM.pCurrent())->data() == 11 );

  treeM.gotoRoot();
  CPPUNIT_ASSERT( treeM.data()                  == 1 );
  CPPUNIT_ASSERT( treeM.pParent()               == 0 );
  CPPUNIT_ASSERT( treeM.pLSibling()             == 0 );
  CPPUNIT_ASSERT( treeM.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (treeM.pFirstChild())->data() == 11 );

  treeM.gotoFirstChild();
  CPPUNIT_ASSERT( treeM.data()                  == 11 );
  CPPUNIT_ASSERT( (treeM.pParent())->data()     == 1 );
  CPPUNIT_ASSERT( treeM.pLSibling()             == 0 );
  CPPUNIT_ASSERT( treeM.pRSibling()             == 0 );
  CPPUNIT_ASSERT( treeM.pFirstChild()           == 0 );

  // MERGE A NON-EMPTY TREE TO AN EMPTY TREE
  // ---------------------------------------

  treeM.gotoRoot();
  GenTree<int> treeE;
  treeE.mergeRSibling(treeM);

  // Check resulting tree

  CPPUNIT_ASSERT( (treeE.pRoot())->data()      == 1 );
  CPPUNIT_ASSERT( (treeE.pCurrent())->data()   == 1 );
  
  CPPUNIT_ASSERT( treeE.data()                  == 1 );
  CPPUNIT_ASSERT( treeE.pParent()               == 0 );
  CPPUNIT_ASSERT( treeE.pLSibling()             == 0 );
  CPPUNIT_ASSERT( treeE.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (treeE.pFirstChild())->data() == 11 );
  // Nodes have been copied
  treeE.setData(91);
  CPPUNIT_ASSERT( treeE.data()                  == 91 );
  CPPUNIT_ASSERT( treeM.data()                  == 1 );

  treeM.gotoFirstChild();
  treeE.gotoFirstChild();
  CPPUNIT_ASSERT( treeE.data()                  == 11 );
  CPPUNIT_ASSERT( (treeE.pParent())->data()     == 91 );
  CPPUNIT_ASSERT( treeE.pLSibling()             == 0 );
  CPPUNIT_ASSERT( treeE.pRSibling()             == 0 );
  CPPUNIT_ASSERT( treeE.pFirstChild()           == 0 );
  // Nodes have been copied
  treeE.setData(911);
  CPPUNIT_ASSERT( treeE.data()                  == 911 );
  CPPUNIT_ASSERT( treeM.data()                  == 11 );

  // MERGE A NON-EMPTY TREE TO A NON-EMPTY TREE
  // ------------------------------------------

  /*
             5                    5
            /|        1          /|\  
           / |   +    |    =    / | \  
          /  |        11       /  |  \ 
         6   7                6   7   1
                                      |
                                      11
  */
  GenTree<int> tree1(5);
  tree1.insertFirstChild(7);
  tree1.insertFirstChild(6);

  // Merge as right sibling of 7
  tree1.gotoFirstChild();
  tree1.gotoRSibling();
  tree1.mergeRSibling(treeM);

  // Check resulting tree

  CPPUNIT_ASSERT( (tree1.pRoot())->data()      == 5 );
  CPPUNIT_ASSERT( (tree1.pCurrent())->data()   == 7 );

  tree1.gotoRoot();
  CPPUNIT_ASSERT( tree1.data()                  == 5 );
  CPPUNIT_ASSERT( tree1.pParent()               == 0 );
  CPPUNIT_ASSERT( tree1.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree1.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree1.pFirstChild())->data() == 6 );

  tree1.gotoFirstChild();
  CPPUNIT_ASSERT( tree1.data()                  == 6 );
  CPPUNIT_ASSERT( (tree1.pParent())->data()     == 5 );
  CPPUNIT_ASSERT( tree1.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (tree1.pRSibling())->data()   == 7 );
  CPPUNIT_ASSERT( tree1.pFirstChild()           == 0 );

  tree1.gotoRSibling();
  CPPUNIT_ASSERT( tree1.data()                  == 7 );
  CPPUNIT_ASSERT( (tree1.pParent())->data()     == 5 );
  CPPUNIT_ASSERT( (tree1.pLSibling())->data()   == 6 );
  CPPUNIT_ASSERT( (tree1.pRSibling())->data()   == 1 );
  CPPUNIT_ASSERT( tree1.pFirstChild()           == 0 );

  tree1.gotoRSibling();
  CPPUNIT_ASSERT( tree1.data()                  == 1 );
  CPPUNIT_ASSERT( (tree1.pParent())->data()     == 5 );
  CPPUNIT_ASSERT( (tree1.pLSibling())->data()   == 7 );
  CPPUNIT_ASSERT( tree1.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree1.pFirstChild())->data() == 11 );
  // Nodes have been copied
  tree1.setData(81);
  CPPUNIT_ASSERT( tree1.data()                  == 81 );
  treeM.gotoRoot();
  CPPUNIT_ASSERT( treeM.data()                  == 1 );

  tree1.gotoFirstChild();
  CPPUNIT_ASSERT( tree1.data()                  == 11 );
  CPPUNIT_ASSERT( (tree1.pParent())->data()     == 81 );
  CPPUNIT_ASSERT( tree1.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree1.pRSibling()             == 0 );
  CPPUNIT_ASSERT( tree1.pFirstChild()           == 0 );
  // Nodes have been copied
  tree1.setData(811);
  CPPUNIT_ASSERT( tree1.data()                  == 811 );
  treeM.gotoFirstChild();
  CPPUNIT_ASSERT( treeM.data()                  == 11 );


  /*
             5                    5
            /|        1          /|\  
           / |   +    |    =    / | \  
          /  |        11       /  |  \ 
         6   7                6   1   7
                                  |
                                  11
  */
  GenTree<int> tree2(5);
  tree2.insertFirstChild(7);
  tree2.insertFirstChild(6);

  // Merge as right sibling of 6
  tree2.gotoFirstChild();
  tree2.mergeRSibling(treeM);

  // Check resulting tree

  CPPUNIT_ASSERT( (tree2.pRoot())->data()      == 5 );
  CPPUNIT_ASSERT( (tree2.pCurrent())->data()   == 6 );

  tree2.gotoRoot();
  CPPUNIT_ASSERT( tree2.data()                  == 5 );
  CPPUNIT_ASSERT( tree2.pParent()               == 0 );
  CPPUNIT_ASSERT( tree2.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree2.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree2.pFirstChild())->data() == 6 );

  tree2.gotoFirstChild();
  CPPUNIT_ASSERT( tree2.data()                  == 6 );
  CPPUNIT_ASSERT( (tree2.pParent())->data()     == 5 );
  CPPUNIT_ASSERT( tree2.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (tree2.pRSibling())->data()   == 1 );
  CPPUNIT_ASSERT( tree2.pFirstChild()           == 0 );

  tree2.gotoRSibling();
  CPPUNIT_ASSERT( tree2.data()                  == 1 );
  CPPUNIT_ASSERT( (tree2.pParent())->data()     == 5 );
  CPPUNIT_ASSERT( (tree2.pLSibling())->data()   == 6 );
  CPPUNIT_ASSERT( (tree2.pRSibling())->data()   == 7 );
  CPPUNIT_ASSERT( (tree2.pFirstChild())->data() == 11 );
  // Nodes have been copied
  tree2.setData(81);
  CPPUNIT_ASSERT( tree2.data()                  == 81 );
  treeM.gotoRoot();
  CPPUNIT_ASSERT( treeM.data()                  == 1 );

  tree2.gotoFirstChild();
  CPPUNIT_ASSERT( tree2.data()                  == 11 );
  CPPUNIT_ASSERT( (tree2.pParent())->data()     == 81 );
  CPPUNIT_ASSERT( tree2.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree2.pRSibling()             == 0 );
  CPPUNIT_ASSERT( tree2.pFirstChild()           == 0 );
  // Nodes have been copied
  tree2.setData(811);
  CPPUNIT_ASSERT( tree2.data()                  == 811 );
  treeM.gotoFirstChild();
  CPPUNIT_ASSERT( treeM.data()                  == 11 );

  tree2.gotoParent();
  tree2.gotoRSibling();
  CPPUNIT_ASSERT( tree2.data()                  == 7 );
  CPPUNIT_ASSERT( (tree2.pParent())->data()     == 5 );
  CPPUNIT_ASSERT( (tree2.pLSibling())->data()   == 81 );
  CPPUNIT_ASSERT( tree2.pRSibling()             == 0 );
  CPPUNIT_ASSERT( tree2.pFirstChild()           == 0 );
}

// -------------------------------------------------------------------

void
GenTreeTest::testMergeRSiblingThrow()
{
  GenTree<int> tree1(1);
  GenTree<int> tree2(2);
  // Current node is the root: Should throw a user exception
  tree1.mergeRSibling(tree2);
}

// -------------------------------------------------------------------

void
GenTreeTest::testMergeFirstChild()
{
  // Small reference tree
  GenTree<int> treeM(1);
  treeM.insertFirstChild(11);

  // MERGE AN EMPTY TREE TO AN EMPTY TREE
  // ------------------------------------

   GenTree<int> treeE1;
   GenTree<int> treeE2;

   treeE1.mergeFirstChild(treeE2);

   CPPUNIT_ASSERT( treeE1.pRoot()    == 0 );
   CPPUNIT_ASSERT( treeE1.pCurrent() == 0 );
   CPPUNIT_ASSERT( treeE2.pRoot()    == 0 );
   CPPUNIT_ASSERT( treeE2.pCurrent() == 0 );

  // MERGE AN EMPTY TREE TO A NON-EMPTY TREE
  // ---------------------------------------

  treeM.gotoFirstChild();
  treeM.mergeFirstChild(treeE1);

  // Check resulting tree

  CPPUNIT_ASSERT( (treeM.pRoot())->data()    == 1 );
  CPPUNIT_ASSERT( (treeM.pCurrent())->data() == 11 );

  treeM.gotoRoot();
  CPPUNIT_ASSERT( treeM.data()                  == 1 );
  CPPUNIT_ASSERT( treeM.pParent()               == 0 );
  CPPUNIT_ASSERT( treeM.pLSibling()             == 0 );
  CPPUNIT_ASSERT( treeM.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (treeM.pFirstChild())->data() == 11 );

  treeM.gotoFirstChild();
  CPPUNIT_ASSERT( treeM.data()                  == 11 );
  CPPUNIT_ASSERT( (treeM.pParent())->data()     == 1 );
  CPPUNIT_ASSERT( treeM.pLSibling()             == 0 );
  CPPUNIT_ASSERT( treeM.pRSibling()             == 0 );
  CPPUNIT_ASSERT( treeM.pFirstChild()           == 0 );

  // MERGE A NON-EMPTY TREE TO AN EMPTY TREE
  // ---------------------------------------

  treeM.gotoRoot();
  GenTree<int> treeE;
  treeE.mergeFirstChild(treeM);

  // Check resulting tree

  CPPUNIT_ASSERT( (treeE.pRoot())->data()      == 1 );
  CPPUNIT_ASSERT( (treeE.pCurrent())->data()   == 1 );
  
  CPPUNIT_ASSERT( treeE.data()                  == 1 );
  CPPUNIT_ASSERT( treeE.pParent()               == 0 );
  CPPUNIT_ASSERT( treeE.pLSibling()             == 0 );
  CPPUNIT_ASSERT( treeE.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (treeE.pFirstChild())->data() == 11 );
  // Nodes have been copied
  treeE.setData(91);
  CPPUNIT_ASSERT( treeE.data()                  == 91 );
  CPPUNIT_ASSERT( treeM.data()                  == 1 );

  treeM.gotoFirstChild();
  treeE.gotoFirstChild();
  CPPUNIT_ASSERT( treeE.data()                  == 11 );
  CPPUNIT_ASSERT( (treeE.pParent())->data()     == 91 );
  CPPUNIT_ASSERT( treeE.pLSibling()             == 0 );
  CPPUNIT_ASSERT( treeE.pRSibling()             == 0 );
  CPPUNIT_ASSERT( treeE.pFirstChild()           == 0 );
  // Nodes have been copied
  treeE.setData(911);
  CPPUNIT_ASSERT( treeE.data()                  == 911 );
  CPPUNIT_ASSERT( treeM.data()                  == 11 );

  // MERGE A NON-EMPTY TREE TO A NON-EMPTY TREE
  // ------------------------------------------

  /*
             5                    5
            /|        1          /|
           / |   +    |    =    / |
          /  |        11       /  |
         6   7                6   7
                              |
                              1
                              |
                              11
  */
  GenTree<int> tree1(5);
  tree1.insertFirstChild(7);
  tree1.insertFirstChild(6);

  // Merge as first child of 6
  tree1.gotoFirstChild();
  tree1.mergeFirstChild(treeM);

  // Check resulting tree

  CPPUNIT_ASSERT( (tree1.pRoot())->data()      == 5 );
  CPPUNIT_ASSERT( (tree1.pCurrent())->data()   == 6 );

  tree1.gotoRoot();
  CPPUNIT_ASSERT( tree1.data()                  == 5 );
  CPPUNIT_ASSERT( tree1.pParent()               == 0 );
  CPPUNIT_ASSERT( tree1.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree1.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree1.pFirstChild())->data() == 6 );

  tree1.gotoFirstChild();
  CPPUNIT_ASSERT( tree1.data()                  == 6 );
  CPPUNIT_ASSERT( (tree1.pParent())->data()     == 5 );
  CPPUNIT_ASSERT( tree1.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (tree1.pRSibling())->data()   == 7 );
  CPPUNIT_ASSERT( (tree1.pFirstChild())->data() == 1 );

  tree1.gotoFirstChild();
  CPPUNIT_ASSERT( tree1.data()                  == 1 );
  CPPUNIT_ASSERT( (tree1.pParent())->data()     == 6 );
  CPPUNIT_ASSERT( tree1.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree1.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree1.pFirstChild())->data() == 11 );
  // Nodes have been copied
  tree1.setData(81);
  CPPUNIT_ASSERT( tree1.data()                  == 81 );
  treeM.gotoRoot();
  CPPUNIT_ASSERT( treeM.data()                  == 1 );

  tree1.gotoFirstChild();
  CPPUNIT_ASSERT( tree1.data()                  == 11 );
  CPPUNIT_ASSERT( (tree1.pParent())->data()     == 81 );
  CPPUNIT_ASSERT( tree1.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree1.pRSibling()             == 0 );
  CPPUNIT_ASSERT( tree1.pFirstChild()           == 0 );
  // Nodes have been copied
  tree1.setData(811);
  CPPUNIT_ASSERT( tree1.data()                  == 811 );
  treeM.gotoFirstChild();
  CPPUNIT_ASSERT( treeM.data()                  == 11 );

  tree1.gotoParent();
  tree1.gotoParent();
  tree1.gotoRSibling();
  CPPUNIT_ASSERT( tree1.data()                  == 7 );
  CPPUNIT_ASSERT( (tree1.pParent())->data()     == 5 );
  CPPUNIT_ASSERT( (tree1.pLSibling())->data()   == 6 );
  CPPUNIT_ASSERT( tree1.pRSibling()             == 0 );
  CPPUNIT_ASSERT( tree1.pFirstChild()           == 0 );


  /*
             5                    5
            /|        1          /|\  
           / |   +    |    =    / | \  
          /  |        11       /  |  \ 
         6   7                1   6   7
                              |
                              11
  */
  GenTree<int> tree2(5);
  tree2.insertFirstChild(7);
  tree2.insertFirstChild(6);

  // Merge as first child of 5
  tree2.mergeFirstChild(treeM);

  // Check resulting tree

  CPPUNIT_ASSERT( (tree2.pRoot())->data()      == 5 );
  CPPUNIT_ASSERT( (tree2.pCurrent())->data()   == 5 );

  tree2.gotoRoot();
  CPPUNIT_ASSERT( tree2.data()                  == 5 );
  CPPUNIT_ASSERT( tree2.pParent()               == 0 );
  CPPUNIT_ASSERT( tree2.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree2.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree2.pFirstChild())->data() == 1 );

  tree2.gotoFirstChild();
  CPPUNIT_ASSERT( tree2.data()                  == 1 );
  CPPUNIT_ASSERT( (tree2.pParent())->data()     == 5 );
  CPPUNIT_ASSERT( tree2.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (tree2.pRSibling())->data()   == 6 );
  CPPUNIT_ASSERT( (tree2.pFirstChild())->data() == 11 );
  // Nodes have been copied
  tree2.setData(81);
  CPPUNIT_ASSERT( tree2.data()                  == 81 );
  treeM.gotoRoot();
  CPPUNIT_ASSERT( treeM.data()                  == 1 );

  tree2.gotoFirstChild();
  CPPUNIT_ASSERT( tree2.data()                  == 11 );
  CPPUNIT_ASSERT( (tree2.pParent())->data()     == 81 );
  CPPUNIT_ASSERT( tree2.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree2.pRSibling()             == 0 );
  CPPUNIT_ASSERT( tree2.pFirstChild()           == 0 );
  // Nodes have been copied
  tree2.setData(811);
  CPPUNIT_ASSERT( tree2.data()                  == 811 );
  treeM.gotoFirstChild();
  CPPUNIT_ASSERT( treeM.data()                  == 11 );

  tree2.gotoParent();
  tree2.gotoRSibling();
  CPPUNIT_ASSERT( tree2.data()                  == 6 );
  CPPUNIT_ASSERT( (tree2.pParent())->data()     == 5 );
  CPPUNIT_ASSERT( (tree2.pLSibling())->data()   == 81 );
  CPPUNIT_ASSERT( (tree2.pRSibling())->data()   == 7 );
  CPPUNIT_ASSERT( tree2.pFirstChild()           == 0 );

  tree2.gotoRSibling();
  CPPUNIT_ASSERT( tree2.data()                  == 7 );
  CPPUNIT_ASSERT( (tree2.pParent())->data()     == 5 );
  CPPUNIT_ASSERT( (tree2.pLSibling())->data()   == 6 );
  CPPUNIT_ASSERT( tree2.pRSibling()             == 0 );
  CPPUNIT_ASSERT( tree2.pFirstChild()           == 0 );
}

// -------------------------------------------------------------------

void
GenTreeTest::testRemove()
{
  // REMOVE FROM AN EMPTY TREE

  GenTree<int> treeE;
  treeE.remove();
  CPPUNIT_ASSERT( treeE.pRoot()    == 0 );
  CPPUNIT_ASSERT( treeE.pCurrent() == 0 );

  // REMOVE ROOT

  GenTree<int> tree1(1000);
  tree1.insertFirstChild(1001);

  GenTreeNode<int>* prem = tree1.remove();
  // Tree is empty
  CPPUNIT_ASSERT( tree1.pRoot()    == 0 );
  CPPUNIT_ASSERT( tree1.pCurrent() == 0 );

  // Remove part is still available
  CPPUNIT_ASSERT( prem->data()                  == 1000 );
  CPPUNIT_ASSERT( prem->pParent()               == 0 );
  CPPUNIT_ASSERT( prem->pLSibling()             == 0 );
  CPPUNIT_ASSERT( prem->pRSibling()             == 0 );
  CPPUNIT_ASSERT( (prem->pFirstChild())->data() == 1001 );
  prem = prem->pFirstChild();
  CPPUNIT_ASSERT( prem->data()                  == 1001 );
  CPPUNIT_ASSERT( (prem->pParent())->data()     == 1000 );
  CPPUNIT_ASSERT( prem->pLSibling()             == 0 );
  CPPUNIT_ASSERT( prem->pRSibling()             == 0 );
  CPPUNIT_ASSERT( prem->pFirstChild()           == 0 );
  // Delete removed part
  delete prem;

  // REMOVE INSIDE A TREE

  /*
              1
	     /|\
            / | \
           /  |  \
         11   12  13
          |   |   |
        111  121  131
   */
  GenTree<int> tree2(1);
  tree2.insertFirstChild(13);
  tree2.insertFirstChild(12);
  tree2.insertFirstChild(11);
  tree2.gotoFirstChild();
  tree2.insertFirstChild(111);
  tree2.gotoRSibling();
  tree2.insertFirstChild(121);
  tree2.gotoRSibling();
  tree2.insertFirstChild(131);

  // Remove node 13
  /*
              1
	     /|
            / |
           /  |
         11   12
          |   |
        111  121
   */
  // Current node is 13
  CPPUNIT_ASSERT( (tree2.pCurrent())->data() == 13 );
  prem = tree2.remove();

  // Check Removed part
  CPPUNIT_ASSERT( prem->data()                  == 13 );
  CPPUNIT_ASSERT( (prem->pParent()) ->data()    == 1 );
  CPPUNIT_ASSERT( (prem->pLSibling())->data()   == 12 );
  CPPUNIT_ASSERT( prem->pRSibling()             == 0 );
  CPPUNIT_ASSERT( (prem->pFirstChild())->data() == 131 );
  prem = prem->pFirstChild();
  CPPUNIT_ASSERT( prem->data()                  == 131 );
  CPPUNIT_ASSERT( (prem->pParent())->data()     == 13 );
  CPPUNIT_ASSERT( prem->pLSibling()             == 0 );
  CPPUNIT_ASSERT( prem->pRSibling()             == 0 );
  CPPUNIT_ASSERT( prem->pFirstChild()           == 0 );
  // Delete removed part
  delete prem;

  // Check resulting tree: Current node is root
  CPPUNIT_ASSERT( (tree2.pRoot())->data()    == 1 );
  CPPUNIT_ASSERT( (tree2.pCurrent())->data() == 1 );

  CPPUNIT_ASSERT( tree2.data()                  == 1 );
  CPPUNIT_ASSERT( tree2.pParent()               == 0 );
  CPPUNIT_ASSERT( tree2.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree2.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree2.pFirstChild())->data() == 11 );
  tree2.gotoFirstChild();
  CPPUNIT_ASSERT( tree2.data()                  == 11 );
  CPPUNIT_ASSERT( (tree2.pParent())->data()     == 1 );
  CPPUNIT_ASSERT( tree2.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (tree2.pRSibling())->data()   == 12 );
  CPPUNIT_ASSERT( (tree2.pFirstChild())->data() == 111 );
  tree2.gotoFirstChild();
  CPPUNIT_ASSERT( tree2.data()                  == 111 );
  CPPUNIT_ASSERT( (tree2.pParent())->data()     == 11 );
  CPPUNIT_ASSERT( tree2.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree2.pRSibling()             == 0 );
  CPPUNIT_ASSERT( tree2.pFirstChild()           == 0 );
  tree2.gotoParent();
  tree2.gotoRSibling();

  CPPUNIT_ASSERT( tree2.data()                  == 12 );
  CPPUNIT_ASSERT( (tree2.pParent())->data()     == 1 );
  CPPUNIT_ASSERT( (tree2.pLSibling())->data()   == 11 );
  CPPUNIT_ASSERT( tree2.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree2.pFirstChild())->data() == 121 );

  tree2.gotoFirstChild();
  CPPUNIT_ASSERT( tree2.data()                  == 121 );
  CPPUNIT_ASSERT( (tree2.pParent())->data()     == 12 );
  CPPUNIT_ASSERT( tree2.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree2.pRSibling()             == 0 );
  CPPUNIT_ASSERT( tree2.pFirstChild()           == 0 );

  // Remove node 11
  /*
              1
	      |
              |
              12
              |
              |
             121
   */
  // Current node is 121
  CPPUNIT_ASSERT( (tree2.pCurrent())->data() == 121 );
  tree2.gotoRoot();
  tree2.gotoFirstChild();  // Go to node 11
  prem = tree2.remove();

  // Check Removed part
  CPPUNIT_ASSERT( prem->data()                  == 11 );
  CPPUNIT_ASSERT( (prem->pParent()) ->data()    == 1 );
  CPPUNIT_ASSERT( prem->pLSibling()             == 0 );
  CPPUNIT_ASSERT( (prem->pRSibling())->data()   == 12 );
  CPPUNIT_ASSERT( (prem->pFirstChild())->data() == 111 );
  prem = prem->pFirstChild();
  CPPUNIT_ASSERT( prem->data()                  == 111 );
  CPPUNIT_ASSERT( (prem->pParent())->data()     == 11 );
  CPPUNIT_ASSERT( prem->pLSibling()             == 0 );
  CPPUNIT_ASSERT( prem->pRSibling()             == 0 );
  CPPUNIT_ASSERT( prem->pFirstChild()           == 0 );
  // Delete removed part
  delete prem;

  // Check resulting tree: Current node is root
  CPPUNIT_ASSERT( (tree2.pRoot())->data()    == 1 );
  CPPUNIT_ASSERT( (tree2.pCurrent())->data() == 1 );

  CPPUNIT_ASSERT( tree2.data()                  == 1 );
  CPPUNIT_ASSERT( tree2.pParent()               == 0 );
  CPPUNIT_ASSERT( tree2.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree2.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree2.pFirstChild())->data() == 12 );
  tree2.gotoFirstChild();
  CPPUNIT_ASSERT( tree2.data()                  == 12 );
  CPPUNIT_ASSERT( (tree2.pParent())->data()     == 1 );
  CPPUNIT_ASSERT( tree2.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree2.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree2.pFirstChild())->data() == 121 );
  tree2.gotoFirstChild();
  CPPUNIT_ASSERT( tree2.data()                  == 121 );
  CPPUNIT_ASSERT( (tree2.pParent())->data()     == 12 );
  CPPUNIT_ASSERT( tree2.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree2.pRSibling()             == 0 );
  CPPUNIT_ASSERT( tree2.pFirstChild()           == 0 );

  // Remove node 121
  /*
              1
	     /|\
            / | \
          20  12 21
   */
  tree2.gotoRoot();
  tree2.insertFirstChild(20);
  tree2.gotoFirstChild();
  tree2.gotoRSibling();
  tree2.insertRSibling(21);

  // Current node is 12
  CPPUNIT_ASSERT( (tree2.pCurrent())->data() == 12 );

  tree2.gotoFirstChild();  // Go to node 121
  prem = tree2.remove();

  // Check Removed part
  CPPUNIT_ASSERT( prem->data()                  == 121 );
  CPPUNIT_ASSERT( (prem->pParent())->data()     == 12 );
  CPPUNIT_ASSERT( prem->pLSibling()             == 0 );
  CPPUNIT_ASSERT( prem->pRSibling()             == 0 );
  CPPUNIT_ASSERT( prem->pFirstChild()          == 0 );
  // Delete removed part
  delete prem;

  // Check resulting tree: Current node is root
  CPPUNIT_ASSERT( (tree2.pRoot())->data()    == 1 );
  CPPUNIT_ASSERT( (tree2.pCurrent())->data() == 1 );

  CPPUNIT_ASSERT( tree2.data()                  == 1 );
  CPPUNIT_ASSERT( tree2.pParent()               == 0 );
  CPPUNIT_ASSERT( tree2.pLSibling()             == 0 );
  CPPUNIT_ASSERT( tree2.pRSibling()             == 0 );
  CPPUNIT_ASSERT( (tree2.pFirstChild())->data() == 20 );
  tree2.gotoFirstChild();
  CPPUNIT_ASSERT( tree2.data()                  == 20 );
  CPPUNIT_ASSERT( (tree2.pParent())->data()     == 1 );
  CPPUNIT_ASSERT( tree2.pLSibling()             == 0 );
  CPPUNIT_ASSERT( (tree2.pRSibling())->data()   == 12 );
  CPPUNIT_ASSERT( tree2.pFirstChild()           == 0 );
  tree2.gotoRSibling();
  CPPUNIT_ASSERT( tree2.data()                  == 12 );
  CPPUNIT_ASSERT( (tree2.pParent())->data()     == 1 );
  CPPUNIT_ASSERT( (tree2.pLSibling())->data()   == 20 );
  CPPUNIT_ASSERT( (tree2.pRSibling())->data()   == 21 );
  CPPUNIT_ASSERT( tree2.pFirstChild()           == 0 );
  tree2.gotoRSibling();
  CPPUNIT_ASSERT( tree2.data()                  == 21 );
  CPPUNIT_ASSERT( (tree2.pParent())->data()     == 1 );
  CPPUNIT_ASSERT( (tree2.pLSibling())->data()   == 12 );
  CPPUNIT_ASSERT( tree2.pRSibling()             == 0 );
  CPPUNIT_ASSERT( tree2.pFirstChild()           == 0 );
}

// -------------------------------------------------------------------
