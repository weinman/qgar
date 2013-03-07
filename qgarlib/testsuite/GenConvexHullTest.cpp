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
 * @file  GenConvexHullTest.cpp
 * @brief Implementation of class GenConvexHullTest.
 *
 *        See file GenConvexHullTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   April 2, 2004  17:10
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenConvexHullTest.cpp,v 1.4 2005/01/28 15:56:45 masini Exp $ */



// STD
#include <list>
#include <set>
#include <utility>
// QGAR
#include <qgarlib/GenConvexHull.h>
#include <qgarlib/primitives.h>
// QGAR TESTS
#include "GenConvexHullTest.h"



using namespace qgar;
using namespace std;



// ------------------------------------------------------------------
// T E S T F I X T U R E   I M P L
// ------------------------------------------------------------------

void
GenConvexHullTest::setUp()
{
  /* EMPTY */
}

// -------------------------------------------------------------------

void
GenConvexHullTest::tearDown()
{
  /* EMPTY */
}


// -------------------------------------------------------------------
// N O   T E S T
// -------------------------------------------------------------------

void
GenConvexHullTest::testEmpty()
{
  // TO BE DONE
}

// -------------------------------------------------------------------

void
GenConvexHullTest::testSize()
{
  // TO BE DONE
}

// -------------------------------------------------------------------

void
GenConvexHullTest::testPivot()
{
  // TO BE DONE
}

// -------------------------------------------------------------------

void
GenConvexHullTest::testAccessPivot()
{
  // TO BE DONE
}


// -------------------------------------------------------------------
// E F F E C T I V E   T E S T S
// -------------------------------------------------------------------

void
GenConvexHullTest::testDefaultConstructor()
{
  // EMPTY HULL
  // ==========

  ConvexHull ch0;

  CPPUNIT_ASSERT( (ch0.accessVertices()).empty() );
}

// -------------------------------------------------------------------

void
GenConvexHullTest::testBuildFromPointList()
{
  // BUILD FROM AN EMPTY LIST
  // ========================

  list<Point> lp;
  ConvexHull ch0(lp);

  CPPUNIT_ASSERT_EQUAL( (int) (ch0.accessVertices()).size(), 0);

  // BUILD FROM A LIST OF 1 POINT
  // ============================

  lp.push_back(Point(2,2));
  ConvexHull ch1(lp);

  CPPUNIT_ASSERT( ch1.accessPivot() == Point(2,2) );

  const list<Point>& v1 = ch1.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (int) v1.size(), 1);
  
  list<Point>::const_iterator itV = v1.begin();
  CPPUNIT_ASSERT_EQUAL( itV->x(), 2 );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 2 );

  // BUILD FROM A LIST OF 2 POINTS
  // =============================
  /*
        X
        ^
        |
     10-|
        |
        |
        |
        |
        |
        |
        |  1                 2
      2-|   +               +
        |
      0 +---------------------- Y
            |               |
            2               10
   */
  lp.push_back(Point(10,2));
  ConvexHull ch2(lp);

  CPPUNIT_ASSERT( ch2.accessPivot() == Point(2,2) );

  const list<Point>& v2 = ch2.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (int) v2.size(), 2);
  
  itV = v2.begin();
  CPPUNIT_ASSERT_EQUAL( itV->x(), 2  );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 2  );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 10 );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 2  );

  // BUILD FROM A LIST OF 3 POINTS
  // =============================
  /*
        X
        ^
        |                    3
     10-|                   +
        |
        |
        |
        |
        |
        |
        |  1                 2
      2-|   +               +
        |
      0 +----------------------> Y
            |               |
            2               10
   */

  lp.push_back(Point(10,10));
  ConvexHull ch3(lp);

  CPPUNIT_ASSERT( ch3.accessPivot() == Point(2,2) );

  const list<Point>& v3 = ch3.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (int) v3.size(), 3);
  
  itV = v3.begin();
  CPPUNIT_ASSERT_EQUAL( itV->x(), 2  );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 2  );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 10 );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 2  );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 10 );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 10 );

  // BUILD FROM A LIST OF 4 POINTS
  // =============================
  /*
        X
        ^
        |  4                 3
     10-|   +               +
        |
        |
        |
        |
        |
        |
        |  1                 2
      2-|   +               +
        |
      0 +----------------------> Y
            |               |
            2               10
   */

  lp.push_back(Point(2,10));
  ConvexHull ch4(lp);

  CPPUNIT_ASSERT( ch4.accessPivot() == Point(2,2) );

  const list<Point>& v4 = ch4.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (int) v4.size(), 4);
  
  itV = v4.begin();
  CPPUNIT_ASSERT_EQUAL( itV->x(), 2  );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 2  );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 10 );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 2  );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 10 );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 10 );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 2  );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 10 );

  // BUILD FROM A LIST OF 5 POINTS
  // =============================
  /*
        X
        ^
        |  4                 3
     10-|   +               +
        |
        |
        |
      6-|           +
        |
        |
        |  1                 2
      2-|   +               +
        |
      0 +----------------------> Y
            |       |       |
            2       6       10
   */

  lp.push_back(Point(6,6));
  ConvexHull ch5(lp);

  CPPUNIT_ASSERT( ch5.accessPivot() == Point(2,2) );

  const list<Point>& v5 = ch5.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (int) v5.size(), 4);
  
  itV = v5.begin();
  CPPUNIT_ASSERT_EQUAL( itV->x(), 2  );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 2  );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 10 );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 2  );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 10 );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 10 );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 2  );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 10 );

  // BUILD FROM A LIST OF 10 POINTS
  // ==============================
  /*
        X
        ^
        |  4                 3
     10-|   +               +
        |  5+
        |           +
        |  6
      6-|   +   +   +   +
        |
        |           +
        |  1                 2
      2-|   +               +
        |
      0 +----------------------> Y
            |       |       |
            2       6       10
   */

  lp.push_back(Point(2,6));
  lp.push_back(Point(6,8));
  lp.push_back(Point(8,6));
  lp.push_back(Point(4,6));
  lp.push_back(Point(6,4));
  lp.push_back(Point(2,9));
  ConvexHull ch6(lp);

  CPPUNIT_ASSERT( ch6.accessPivot() == Point(2,2) );

  const list<Point>& v6 = ch6.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (int) v6.size(), 6);
  
  itV = v6.begin();
  CPPUNIT_ASSERT_EQUAL( itV->x(), 2  );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 2  );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 10 );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 2  );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 10 );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 10 );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 2  );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 10 );

  // BUILD FROM A LIST OF 21 RANDOM POINTS
  // =====================================

  lp.clear();
  lp.push_back(Point(19,14)); // 1
  lp.push_back(Point(8,13));  // 2
  lp.push_back(Point(11,21)); // 3
  lp.push_back(Point(6,19));  // 4
  lp.push_back(Point(2,6));   // 5
  lp.push_back(Point(15,4));  // 6
  lp.push_back(Point(20,7));  // 7
  lp.push_back(Point(10,5));  // 8
  lp.push_back(Point(11,12)); // 9
  lp.push_back(Point(4,12));  // 10
  lp.push_back(Point(2,8));   // 11
  lp.push_back(Point(1,1));   // 12
  lp.push_back(Point(18,2));  // 13
  lp.push_back(Point(6,-1));  // 14
  lp.push_back(Point(15,11)); // 15
  lp.push_back(Point(12,4));  // 16
  lp.push_back(Point(7,7));   // 17
  lp.push_back(Point(5,4));   // 18
  lp.push_back(Point(4,2));   // 19
  lp.push_back(Point(13,7));  // 20
  lp.push_back(Point(21,18)); // 21

  ConvexHull ch7(lp);

  CPPUNIT_ASSERT( ch7.accessPivot() == Point(6,-1) );

  const list<Point>& v7 = ch7.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (int) v7.size(), 8);
  
  itV = v7.begin();
  CPPUNIT_ASSERT_EQUAL( itV->x(),  6 );  // 1
  CPPUNIT_ASSERT_EQUAL( itV->y(), -1 );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 18 );  // 2
  CPPUNIT_ASSERT_EQUAL( itV->y(),  2 );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 20 );  // 3
  CPPUNIT_ASSERT_EQUAL( itV->y(),  7 );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 21 );  // 4
  CPPUNIT_ASSERT_EQUAL( itV->y(), 18 );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 11 );  // 5
  CPPUNIT_ASSERT_EQUAL( itV->y(), 21 );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(),  6 );  // 6
  CPPUNIT_ASSERT_EQUAL( itV->y(), 19 );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(),  2 );  // 7
  CPPUNIT_ASSERT_EQUAL( itV->y(),  8 );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(),  1 );  // 8
  CPPUNIT_ASSERT_EQUAL( itV->y(),  1 );

  // SEVERAL EQUIVALENT PIVOTS
  // =========================
  /*
        X
        ^
        |  2
     10-|   +
        |
        |
        |                5
      6-|               +  
        |
        |
        |  3     1   4       6
      2-|   +   +   +       +
        |
      0 +----------------------> Y
            |       |       |
            2       6       10
   */

  lp.clear();
  lp.push_back(Point(4,2));  // 1
  lp.push_back(Point(2,10)); // 2
  lp.push_back(Point(2,2));  // 3
  lp.push_back(Point(6,2));  // 4
  lp.push_back(Point(8,6));  // 5
  lp.push_back(Point(10,2)); // 6
  ConvexHull ch8(lp);

  CPPUNIT_ASSERT( ch8.accessPivot() == Point(2,2) );

  const list<Point>& v8 = ch8.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (int) v8.size(), 6);
  
  itV = v8.begin();
  CPPUNIT_ASSERT_EQUAL( itV->x(),  2 );
  CPPUNIT_ASSERT_EQUAL( itV->y(),  2 );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(),  4 );
  CPPUNIT_ASSERT_EQUAL( itV->y(),  2 );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(),  6 );
  CPPUNIT_ASSERT_EQUAL( itV->y(),  2 );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 10 );
  CPPUNIT_ASSERT_EQUAL( itV->y(),  2 );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(),  8 );
  CPPUNIT_ASSERT_EQUAL( itV->y(),  6 );
  itV++; 
  CPPUNIT_ASSERT_EQUAL( itV->x(),  2 );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 10 );

  // 5 POINTS HORIZONTALLY ALIGNED
  // =============================
  /*
        X
        ^
        |
        |   3   1   4    2  5
      2-|   +   +   +    +  +
        |
      0 +----------------------> Y
            |       |       |
            2       6       10
   */

  lp.clear();
  lp.push_back(Point(4,2));  // 1
  lp.push_back(Point(9,2));  // 2
  lp.push_back(Point(2,2));  // 3
  lp.push_back(Point(6,2));  // 4
  lp.push_back(Point(10,2)); // 5
  ConvexHull ch9(lp);

  // As all points are equivalent to be the pivot,
  // The point with minimum X coordinate becomes the pivot
  // Points are ordered according to increasing X coordinates
  CPPUNIT_ASSERT( ch9.accessPivot() == Point(2,2) );

  const list<Point>& v9 = ch9.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (int) v9.size(), 5);
  
  itV = v9.begin();
  CPPUNIT_ASSERT_EQUAL( itV->x(),  2 );
  CPPUNIT_ASSERT_EQUAL( itV->y(),  2 );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(),  4 );
  CPPUNIT_ASSERT_EQUAL( itV->y(),  2 );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(),  6 );
  CPPUNIT_ASSERT_EQUAL( itV->y(),  2 );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(),  9 );
  CPPUNIT_ASSERT_EQUAL( itV->y(),  2 );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 10 );
  CPPUNIT_ASSERT_EQUAL( itV->y(),  2 );

  // 5 POINTS VERTICALLY ALIGNED
  // ===========================
  /*
        X
        ^
        |
     10-|   + 3
        |
        |   + 5
        |
      6-|   + 1
        |   + 2
        |
        |
      2-|   + 4
        |
      0 +----------------------> Y
            |       |       |
            2       6       10
   */

  lp.clear();
  lp.push_back(Point(2,6));  // 1
  lp.push_back(Point(2,5));  // 2
  lp.push_back(Point(2,10)); // 3
  lp.push_back(Point(2,2));  // 4
  lp.push_back(Point(2,8));  // 5
  ConvexHull ch10(lp);

  // Points are ordered according to decreasing Y coordinates
  CPPUNIT_ASSERT( ch10.accessPivot() == Point(2,2) );

  const list<Point>& v10 = ch10.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (int) v10.size(), 5);
  
  itV = v10.begin();
  CPPUNIT_ASSERT_EQUAL( itV->x(), 2  );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 2  );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 2  );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 10 );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 2  );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 8  );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 2  );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 6  );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 2  );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 5  );

  // 5 POINTS ALONG THE POSITIVE DIAGONAL
  // ====================================
  /*
        X
        ^
        |
     10-|                 3 +
        |
        |
        |           2 +
      6-|         1 +
        |
        |     5 +
        |
      2-| 4 +
        |
      0 +----------------------> Y
            |       |       |
            2       6       10
   */

  lp.clear();
  lp.push_back(Point(6,6));   // 1
  lp.push_back(Point(7,7));   // 2
  lp.push_back(Point(10,10)); // 3
  lp.push_back(Point(2,2));   // 4
  lp.push_back(Point(4,4));   // 5
  ConvexHull ch11(lp);

  // Points are ordered according to decreasing Y coordinates
  CPPUNIT_ASSERT( ch11.accessPivot() == Point(2,2) );

  const list<Point>& v11 = ch11.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (int) v11.size(), 5);
  
  itV = v11.begin();
  CPPUNIT_ASSERT_EQUAL( itV->x(), 2  );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 2  );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 10  );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 10 );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 7  );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 7  );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 6  );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 6  );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 4  );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 4  );

  // 5 POINTS ALONG THE NEGATIVE DIAGONAL
  // ====================================
  /*
        X
        ^
        |
     10-|   + 4
        |
        |          1
        |         + 
      6-|           + 2
        |
        |               + 5
        |
      2-|                   + 3
        |
      0 +----------------------> Y
            |       |       |
            2       6       10
   */

  lp.clear();
  lp.push_back(Point(5,7));  // 1
  lp.push_back(Point(6,6));  // 2
  lp.push_back(Point(10,2)); // 3
  lp.push_back(Point(2,10)); // 4
  lp.push_back(Point(8,4));  // 5
  ConvexHull ch12(lp);

  // Points are ordered according to decreasing Y coordinates
  CPPUNIT_ASSERT( ch12.accessPivot() == Point(10,2) );

  const list<Point>& v12 = ch12.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (int) v12.size(), 5);
  
  itV = v12.begin();
  CPPUNIT_ASSERT_EQUAL( itV->x(), 10  );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 2  );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 2  );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 10 );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 5  );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 7  );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 6  );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 6  );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 8  );
  CPPUNIT_ASSERT_EQUAL( itV->y(), 4  );

  // SQUARE WITH POINTS ALIGNED
  // ==========================
  /*
        X
        ^
        |  12   11 10  9     8
     10-|   +    +  +  +    +
        |
        | 13+
        |     
      6-|           +       +7
        |
        | 14+               +6
        |
      2-|   +  +    +    +  + 
        |  1   2    3    4   5
      0 +----------------------> Y
            |       |       |
            2       6       10
   */

  lp.clear();
  lp.push_back(Point(7,10));
  lp.push_back(Point(6,2));
  lp.push_back(Point(2,8));
  lp.push_back(Point(5,10));
  lp.push_back(Point(10,10));
  lp.push_back(Point(6,6));
  lp.push_back(Point(2,10));
  lp.push_back(Point(9,2));
  lp.push_back(Point(3,2));
  lp.push_back(Point(10,6));
  lp.push_back(Point(10,4));
  lp.push_back(Point(2,4));
  lp.push_back(Point(2,2));
  lp.push_back(Point(10,2));
  lp.push_back(Point(6,10));
  ConvexHull ch13(lp);

  CPPUNIT_ASSERT( ch13.accessPivot() == Point(2,2) );

  const list<Point>& v13 = ch13.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (int) v13.size(), 14);
  
  itV = v13.begin();
  CPPUNIT_ASSERT_EQUAL( itV->x(), 2  );  // 1
  CPPUNIT_ASSERT_EQUAL( itV->y(), 2  );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 3  );  // 2
  CPPUNIT_ASSERT_EQUAL( itV->y(), 2  );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 6  );  // 3
  CPPUNIT_ASSERT_EQUAL( itV->y(), 2  );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 9  );  // 4
  CPPUNIT_ASSERT_EQUAL( itV->y(), 2  );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 10 );  // 5
  CPPUNIT_ASSERT_EQUAL( itV->y(), 2  );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 10 );  // 6
  CPPUNIT_ASSERT_EQUAL( itV->y(), 4  );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 10 );  // 7
  CPPUNIT_ASSERT_EQUAL( itV->y(), 6  );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 10 );  // 8
  CPPUNIT_ASSERT_EQUAL( itV->y(), 10 );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 7  );  // 9
  CPPUNIT_ASSERT_EQUAL( itV->y(), 10 );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 6  );  // 10
  CPPUNIT_ASSERT_EQUAL( itV->y(), 10 );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 5  );  // 11
  CPPUNIT_ASSERT_EQUAL( itV->y(), 10 );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 2  );  // 12
  CPPUNIT_ASSERT_EQUAL( itV->y(), 10 );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 2  );  // 13
  CPPUNIT_ASSERT_EQUAL( itV->y(), 8  );
  itV++;
  CPPUNIT_ASSERT_EQUAL( itV->x(), 2  );  // 14
  CPPUNIT_ASSERT_EQUAL( itV->y(), 4  );

// /////////////////////////////////////////////////
// THE ALGORITHM DOES NOT WORK WITH DUPLICATE POINTS
// /////////////////////////////////////////////////

//   // INITIAL SET OF POINTS WITH DUPLICATES
//   // =====================================
//   /*
//         X
//         ^
//         | 2 occurrences
//      10-|   +
//         |                 + 3 occurrences
//         |
//         |
//       6-|           + 2 occurrences
//         |
//         |
//         | 3 occurrences
//       2-|   +               + 2 ocurrences
//         |
//       0 +----------------------> Y
//             |       |       |
//             2       6       10
//    */

//   lp.clear();
//   lp.push_back(Point(6,6));
//   lp.push_back(Point(2,10));
//   lp.push_back(Point(9,9));
//   lp.push_back(Point(9,9));
//   lp.push_back(Point(10,2));
//   lp.push_back(Point(6,6));
//   lp.push_back(Point(2,2));
//   lp.push_back(Point(10,2));
//   lp.push_back(Point(2,10));
//   lp.push_back(Point(9,9));
//   lp.push_back(Point(2,2));
//   lp.push_back(Point(2,2));
//   ConvexHull ch14(lp);
}

// -------------------------------------------------------------------

void
GenConvexHullTest::testCopyConstructor()
{
  // EMPTY HULL
  // ==========

  ConvexHull ch0;
  ConvexHull ch0c(ch0);

  CPPUNIT_ASSERT( (ch0.accessVertices()).empty() );
  CPPUNIT_ASSERT( (ch0c.accessVertices()).empty() );

  // HULL OF 3 VERTICES
  // ==================
  /*
        X
        ^
        |                    3
     10-|                   +
        |
        |
        |
        |
        |
        |
        |  1                 2
      2-|   +               +
        |
      0 +----------------------> Y
            |               |
            2               10
   */

  list<Point> lp;
  lp.push_back(Point(10,10));
  lp.push_back(Point(10,2));
  lp.push_back(Point(2,2));

  ConvexHull ch(lp);
  ConvexHull chc(ch);

  CPPUNIT_ASSERT( ch.accessPivot()  == Point(2,2) );
  CPPUNIT_ASSERT( chc.accessPivot() == Point(2,2) );

  const list<Point>& v = ch.accessVertices();
  const list<Point>& vc = chc.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (int) v.size(),  3 );
  CPPUNIT_ASSERT_EQUAL( (int) vc.size(), 3 );
  
  list<Point>::const_iterator itV = v.begin();
  list<Point>::const_iterator itVC = vc.begin();
  CPPUNIT_ASSERT_EQUAL( itV->x(),  2  );
  CPPUNIT_ASSERT_EQUAL( itV->y(),  2  );
  CPPUNIT_ASSERT_EQUAL( itVC->x(), 2  );
  CPPUNIT_ASSERT_EQUAL( itVC->y(), 2  );
  itV++;
  itVC++;
  CPPUNIT_ASSERT_EQUAL( itV->x(),  10 );
  CPPUNIT_ASSERT_EQUAL( itV->y(),  2  );
  CPPUNIT_ASSERT_EQUAL( itVC->x(), 10 );
  CPPUNIT_ASSERT_EQUAL( itVC->y(), 2  );
  itV++;
  itVC++;
  CPPUNIT_ASSERT_EQUAL( itV->x(),  10 );
  CPPUNIT_ASSERT_EQUAL( itV->y(),  10 );
  CPPUNIT_ASSERT_EQUAL( itVC->x(), 10 );
  CPPUNIT_ASSERT_EQUAL( itVC->y(), 10 );
}

// -------------------------------------------------------------------

void
GenConvexHullTest::testAssignment()
{
  // EMPTY HULL
  // ==========

  ConvexHull ch0;
  ConvexHull ch0c = ch0;

  CPPUNIT_ASSERT( (ch0.accessVertices()).empty() );
  CPPUNIT_ASSERT( (ch0c.accessVertices()).empty() );

  // A HULL OF 3 VERTICES
  // ====================
  /*
        X
        ^
        |                    3
     10-|                   +
        |
        |
        |
        |
        |
        |
        |  1                 2
      2-|   +               +
        |
      0 +----------------------> Y
            |               |
            2               10
   */

  list<Point> lp;
  lp.push_back(Point(10,10));
  lp.push_back(Point(10,2));
  lp.push_back(Point(2,2));

  ConvexHull ch(lp);
  ConvexHull chc = ch;

  CPPUNIT_ASSERT( ch.accessPivot()  == Point(2,2) );
  CPPUNIT_ASSERT( chc.accessPivot() == Point(2,2) );

  const list<Point>& v = ch.accessVertices();
  const list<Point>& vc = chc.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (int) v.size(),  3 );
  CPPUNIT_ASSERT_EQUAL( (int) vc.size(), 3 );
  
  list<Point>::const_iterator itV = v.begin();
  list<Point>::const_iterator itVC = vc.begin();
  CPPUNIT_ASSERT_EQUAL( itV->x(),  2  );
  CPPUNIT_ASSERT_EQUAL( itV->y(),  2  );
  CPPUNIT_ASSERT_EQUAL( itVC->x(), 2  );
  CPPUNIT_ASSERT_EQUAL( itVC->y(), 2  );
  itV++;
  itVC++;
  CPPUNIT_ASSERT_EQUAL( itV->x(),  10 );
  CPPUNIT_ASSERT_EQUAL( itV->y(),  2  );
  CPPUNIT_ASSERT_EQUAL( itVC->x(), 10 );
  CPPUNIT_ASSERT_EQUAL( itVC->y(), 2  );
  itV++;
  itVC++;
  CPPUNIT_ASSERT_EQUAL( itV->x(),  10 );
  CPPUNIT_ASSERT_EQUAL( itV->y(),  10 );
  CPPUNIT_ASSERT_EQUAL( itVC->x(), 10 );
  CPPUNIT_ASSERT_EQUAL( itVC->y(), 10 );
}

// ----------------------------------------------------------------------

void 
GenConvexHullTest::testSerializeDeserialize()
{
  // EMPTY HULL
  // ==========

  ConvexHull och0;
  ConvexHull ich0;

  stringstream ss;

  ss << och0;
  ss >> ich0;
  ss.flush();

  CPPUNIT_ASSERT( (ich0.accessVertices()).empty() );
  CPPUNIT_ASSERT( (och0.accessVertices()).empty() );

  // HULL OF 3 VERTICES
  // ==================
  /*
        X
        ^
        |                    3
     10-|                   +
        |
        |
        |
        |
        |
        |
        |  1                 2
      2-|   +               +
        |
      0 +----------------------> Y
            |               |
            2               10
   */

  list<DPoint> lp;
  lp.push_back(DPoint(10.5 , 10.5));
  lp.push_back(DPoint(10.5 , 2.2));
  lp.push_back(DPoint(2.2  , 2.2));
  DConvexHull och3(lp);

  DConvexHull ich3;

  ss << och3;
  ss >> ich3;
  ss.flush();

  CPPUNIT_ASSERT( ich3.accessPivot() == DPoint(2.2 , 2.2) );
  CPPUNIT_ASSERT( och3.accessPivot() == DPoint(2.2 , 2.2) );

  const list<DPoint>& vi = ich3.accessVertices();
  const list<DPoint>& vo = och3.accessVertices();
  CPPUNIT_ASSERT_EQUAL( (int) vi.size(), 3 );
  CPPUNIT_ASSERT_EQUAL( (int) vo.size(), 3 );
  
  list<DPoint>::const_iterator itVI = vi.begin();
  list<DPoint>::const_iterator itVO = vo.begin();
  CPPUNIT_ASSERT_DOUBLES_EQUAL( itVI->x(), 2.2  , 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( itVI->y(), 2.2  , 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( itVO->x(), 2.2  , 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( itVO->y(), 2.2  , 0. );
  itVI++;
  itVO++;
  CPPUNIT_ASSERT_DOUBLES_EQUAL( itVI->x(), 10.5 , 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( itVI->y(), 2.2  , 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( itVO->x(), 10.5 , 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( itVO->y(), 2.2  , 0. );
  itVI++;
  itVO++;
  CPPUNIT_ASSERT_DOUBLES_EQUAL( itVI->x(), 10.5 , 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( itVI->y(), 10.5 , 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( itVO->x(), 10.5 , 0. );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( itVO->y(), 10.5 , 0. );
}

// ----------------------------------------------------------------------
