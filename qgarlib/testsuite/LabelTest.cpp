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
 * @file  LabelTest.cpp
 * @brief Implementation of class LabelTest
 *
 *        See file LabelTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   February 16, 2004  18:16
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: LabelTest.cpp,v 1.6 2005/01/28 15:56:46 masini Exp $ */



// STD
#include <limits>
// QGAR
#include <qgarlib/Label.h>
// QGAR TESTS
#include "LabelTest.h"



using namespace qgar;



// ------------------------------------------------------------------
// T E S T F I X T U R E   I M P L
// ------------------------------------------------------------------

void
LabelTest::setUp()
{
  /* EMPTY */
}

// -------------------------------------------------------------------

void
LabelTest::tearDown()
{
  /* EMPTY */
}

// -------------------------------------------------------------------
// N O T   T E S T E D    F U N C T I O N S
// -------------------------------------------------------------------

void
LabelTest::testCastIntoInt()
{
  // NO TEST
}

// -------------------------------------------------------------------
// T E S T E D   F U N C T I O N S
// -------------------------------------------------------------------

void
LabelTest::testDefaultConstructor()
{
  // Label is initialized to 0
  Label l;
  CPPUNIT_ASSERT_EQUAL( (int)l, 0 );
}

// -------------------------------------------------------------------

void
LabelTest::testBuildFromUShort()
{
  Label l0(0);
  CPPUNIT_ASSERT_EQUAL( (int)l0, 0 );

  Label l732(732);
  CPPUNIT_ASSERT_EQUAL( (int)l732, 732 );

  Label lmax(Label::_MAX_LABEL);
  CPPUNIT_ASSERT_EQUAL( (int)lmax, (int)Label::_MAX_LABEL );
}

// -------------------------------------------------------------------

void
LabelTest::testCopyConstructor()
{
  Label l0;
  Label cl0(l0);
  CPPUNIT_ASSERT_EQUAL( (int)l0,  0 );
  CPPUNIT_ASSERT_EQUAL( (int)cl0, 0 );

  Label l256(256);
  Label cl256(l256);
  CPPUNIT_ASSERT_EQUAL( (int)l256,  256 );
  CPPUNIT_ASSERT_EQUAL( (int)cl256, 256 );

  Label lmax(Label::_MAX_LABEL);
  Label clmax(lmax);
  CPPUNIT_ASSERT_EQUAL( (int)lmax,  (int)Label::_MAX_LABEL );
  CPPUNIT_ASSERT_EQUAL( (int)clmax, (int)Label::_MAX_LABEL );
}

// -------------------------------------------------------------------

void
LabelTest::testAssignment()
{
  Label l0;
  Label cl = l0;
  CPPUNIT_ASSERT_EQUAL( (int)l0, 0 );
  CPPUNIT_ASSERT_EQUAL( (int)cl, 0 );
  CPPUNIT_ASSERT_EQUAL( (int)cl, (int)l0 );

  Label l1024(1024);
  cl = l1024;
  CPPUNIT_ASSERT_EQUAL( (int)l1024, 1024 );
  CPPUNIT_ASSERT_EQUAL( (int)cl,    1024 );
  CPPUNIT_ASSERT_EQUAL( (int)cl, (int)l1024 );

  Label lmax(Label::_MAX_LABEL);
  cl = lmax;
  CPPUNIT_ASSERT_EQUAL( (int)lmax, (int)Label::_MAX_LABEL );
  CPPUNIT_ASSERT_EQUAL( (int)cl,   (int)Label::_MAX_LABEL );
  CPPUNIT_ASSERT_EQUAL( (int)cl,   (int)lmax );
}

// -------------------------------------------------------------------

void
LabelTest::testMaxLabel()
{
  CPPUNIT_ASSERT_EQUAL( (int)Label::_MAX_LABEL,
			std::numeric_limits<unsigned short>::max() - 2);
}

// -------------------------------------------------------------------

void
LabelTest::testPrefixedPP()
{
  Label l2(2);
  CPPUNIT_ASSERT_EQUAL( (int)(++l2), 3 );
  
  Label l100(100);
  ++l100;
  CPPUNIT_ASSERT_EQUAL( (int)l100, 101 );

  // Ensure that operator returns a valid reference on 'this'
  Label l(10);
  CPPUNIT_ASSERT(&l == &(++l));
}

// -------------------------------------------------------------------

void
LabelTest::testPrefixedPPThrow()
{
  Label lmax(Label::_MAX_LABEL);
  // Should throw a qgar::QgarErrorAlgorithm exception
  ++lmax;
}

// -------------------------------------------------------------------

void
LabelTest::testPostfixedPP()
{
  Label l2(2);
  CPPUNIT_ASSERT_EQUAL( (int)(l2++), 2 );
  
  Label l100(100);
  l100++;
  CPPUNIT_ASSERT_EQUAL( (int)l100, 101 );
}

// -------------------------------------------------------------------

void
LabelTest::testPostfixedPPThrow()
{
  Label lmax(Label::_MAX_LABEL);
  // Should throw a qgar::QgarErrorAlgorithm exception
  lmax++;
}

// -------------------------------------------------------------------

void
LabelTest::testPrefixedMM()
{
  Label l5(5);
  CPPUNIT_ASSERT_EQUAL( (int)(--l5), 4 );
  
  Label l80(80);
  --l80;
  CPPUNIT_ASSERT_EQUAL( (int)l80, 79 );

  // Ensure that operator returns a valid reference on 'this'
  Label l(10);
  CPPUNIT_ASSERT(&l == &(--l));
}

// -------------------------------------------------------------------

void
LabelTest::testPrefixedMMThrow()
{
  Label l0(0);
  // Should throw a qgar::QgarErrorUser exception
  --l0;
}

// -------------------------------------------------------------------

void
LabelTest::testPostfixedMM()
{
  Label l5(5);
  CPPUNIT_ASSERT_EQUAL( (int)(l5--), 5 );
  
  Label l80(80);
  l80--;
  CPPUNIT_ASSERT_EQUAL( (int)l80, 79 );
}

// -------------------------------------------------------------------

void
LabelTest::testPostfixedMMThrow()
{
  Label l0(0);
  // Should throw a qgar::QgarErrorUser exception
  l0--;
}

// -------------------------------------------------------------------

void
LabelTest::testEqualityOp()
{
  Label l0;
  Label l_0(0);
  CPPUNIT_ASSERT( l0 == l_0 );

  Label l123(123);
  Label l_123(123);
  CPPUNIT_ASSERT( l123 == l_123 );
  
  Label lmax(Label::_MAX_LABEL);
  CPPUNIT_ASSERT( lmax == Label::_MAX_LABEL );  
}

// -------------------------------------------------------------------

void
LabelTest::testNequalityOp()
{
  Label l0;
  Label ll(33);
  CPPUNIT_ASSERT( l0 != ll );

  ll++;
  CPPUNIT_ASSERT( ll != Label::_MAX_LABEL );  
}

// -------------------------------------------------------------------

void
LabelTest::testGreaterOp()
{
  Label l0(0);
  Label l707(707);
  CPPUNIT_ASSERT( l707 > l0 );
  
  CPPUNIT_ASSERT( Label::_MAX_LABEL > l0 );  
  CPPUNIT_ASSERT( Label::_MAX_LABEL > l707 );  
}

// -------------------------------------------------------------------

void
LabelTest::testGreaterOrEqOp()
{
  Label l(4);
  Label ll(4);
  CPPUNIT_ASSERT( ll >= l );
  
  ll++;
  CPPUNIT_ASSERT( ll >= l );
  CPPUNIT_ASSERT( Label::_MAX_LABEL >= l );  
  CPPUNIT_ASSERT( Label::_MAX_LABEL >= ll );  
}

// -------------------------------------------------------------------

void
LabelTest::testLessOp()
{
  Label l706(706);
  Label l707(707);
  CPPUNIT_ASSERT( l706 < l707 );
  CPPUNIT_ASSERT( l706 < Label::_MAX_LABEL );  
  CPPUNIT_ASSERT( l707 < Label::_MAX_LABEL );  
}

// -------------------------------------------------------------------

void
LabelTest::testLessOrEqOp()
{
  Label l706(706);
  Label l707(707);
  CPPUNIT_ASSERT( l706 <= l707 );
  CPPUNIT_ASSERT( l706 <= Label::_MAX_LABEL );  
  CPPUNIT_ASSERT( l707 <= Label::_MAX_LABEL );

  l707--;
  CPPUNIT_ASSERT( l706 <= l707 );
  l707--;
  CPPUNIT_ASSERT( !(l706 <= l707) );
}

// -------------------------------------------------------------------

void
LabelTest::testMin()
{
  Label l0(0);
  Label l200(200);
  Label lmin = l0.min(l200);
  CPPUNIT_ASSERT_EQUAL( (int)lmin, 0 );
  lmin = l200.min(l0);
  CPPUNIT_ASSERT_EQUAL( (int)lmin, 0 );

  Label l13(13);
  Label l888(888);
  lmin = l13.min(l888);
  CPPUNIT_ASSERT_EQUAL( (int)lmin, 13 );
  lmin = l888.min(l13);
  CPPUNIT_ASSERT_EQUAL( (int)lmin, 13 );

  lmin = Label::_MAX_LABEL.min(l13);
  CPPUNIT_ASSERT_EQUAL( (int)lmin,  13 );
  lmin = l888.min(Label::_MAX_LABEL);
  CPPUNIT_ASSERT_EQUAL( (int)lmin, 888 );
}

// -------------------------------------------------------------------

void
LabelTest::testMax()
{
  Label l0(0);
  Label l200(200);
  Label lmax = l0.max(l200);
  CPPUNIT_ASSERT_EQUAL( (int)lmax, 200 );
  lmax = l200.max(l0);
  CPPUNIT_ASSERT_EQUAL( (int)lmax, 200 );

  Label l13(13);
  Label l888(888);
  lmax = l13.max(l888);
  CPPUNIT_ASSERT_EQUAL( (int)lmax, 888 );
  lmax = l888.max(l13);
  CPPUNIT_ASSERT_EQUAL( (int)lmax, 888 );

  lmax = Label::_MAX_LABEL.max(l13);
  CPPUNIT_ASSERT_EQUAL( (int)lmax, (int)Label::_MAX_LABEL );
  lmax = l888.max(Label::_MAX_LABEL);
  CPPUNIT_ASSERT_EQUAL( (int)lmax, (int)Label::_MAX_LABEL );
}

// ----------------------------------------------------------------------
