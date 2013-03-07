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


#ifndef __CONNECTEDCOMPONENTSTEST_H_INCLUDED__
#define __CONNECTEDCOMPONENTSTEST_H_INCLUDED__


/**
 * @file     ConnectedComponentsTest.h
 * @brief    Header file of class ConnectedComponentsTest
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date     April 20, 2004  15:25
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete.
/* $Id: ConnectedComponentsTest.h,v 1.3 2006/03/29 17:40:38 masini Exp $ */



// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>



/**
 * @class ConnectedComponentsTest ConnectedComponentsTest.h
 * @brief Test class for connected components.
 * 
 * Untested function members:
 * - 
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   June 21, 2004  14:44
 * @since  Qgar 2.1.1
 */
class ConnectedComponentsTest : public CppUnit::TestFixture
{
// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( ConnectedComponentsTest );

  CPPUNIT_TEST( testConnectedComponentsTest );

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



/** @name Tests with images ConnectedComponentsTest.img_*.pbm */
//        ===================================================
//@{

/**
 * @brief Tests components
 *   of images ConnectedComponentsTest.img_*.pbm.
 *
 * Performed Tests:
 * - Ensure that the number of components is correct
 * - Ensure that all data (excepting the MAER) of all components
 *   are correctly computed
 */
  void testConnectedComponentsTest();

//@}

// -------------------------------------------------------------------
}; // class ConnectedComponentsTest


#endif /* __CONNECTEDCOMPONENTSTEST_H_INCLUDED__ */
