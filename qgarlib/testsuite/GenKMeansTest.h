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


#ifndef __GENKMEANSTEST_H_INCLUDED__
#define __GENKMEANSTEST_H_INCLUDED__


/**
 * @file     GenKMeansTest.h
 * @brief    Header file of class GenKMeansTest
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 24, 2004  18:05
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete.
/* $Id: GenKMeansTest.h,v 1.4 2005/10/14 17:06:36 masini Exp $ */



// STD
#include <list>
// CPPUNIT
#include <cppunit/extensions/HelperMacros.h>
// QGAR
#include <qgarlib/primitives.h>
#include <qgarlib/QgarErrorAlgorithm.h>



/**
 * @class GenKMeansTest GenKMeansTest.h
 * @brief Test class for class GenKMeans.
 * 
 * Untested function members:
 * - clusterCnt()
 * - clusterSizes() 
 * - clusterCenters()
 * - clusters()
 * - accessClusters()
 * - clusterElts()
 * - accessClusterElts()
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 24, 2004  18:05
 * @since  Qgar 2.1.1
 */
class GenKMeansTest

  : public CppUnit::TestFixture

{
// -------------------------------------------------------------------
// T E S T   R E G I S T R A T I O N
// -------------------------------------------------------------------

  CPPUNIT_TEST_SUITE( GenKMeansTest );

  CPPUNIT_TEST( testKMeans );
  CPPUNIT_TEST( testKMeansFixedSeeds );
  CPPUNIT_TEST_EXCEPTION( testMoreClusterThanPointsException, qgar::QgarErrorAlgorithm);
  CPPUNIT_TEST( testClusterDefaultConstructor );
  CPPUNIT_TEST( testClusterCopyConstructor );
  CPPUNIT_TEST( testClusterAssigmentOp );

  CPPUNIT_TEST_SUITE_END();

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name CONSTANTS */
//        =========
//@{
  static const int NB_POINTS;
  static const int NB_CLUSTERS;
//@}


/** @name TestFixture Impl */
//        ================
//@{

  virtual void setUp();

  virtual void tearDown();

//@}


/** @name Test Functions */
//        ==============
//@{

/**
 * @brief Tests GenKMeans()
 *
 * Partitions NB_POINTS random points into NB_CLUSTERS clusters. 
 *
 * Performed Checks:
 * - Ensure that no cluster is empty.
 * - Ensure that each point of a cluster is closer to its center than
 *   to any other cluster center.
 * - Ensure that partitioning N points into N clusters leads to N
 *   clusters containing a point.
 */
  void testKMeans();
/**
 * @brief Tests KMeansFixedSeeds()
 *
 * Performed Tests:
 * - Ensure that partitioning N points into N clusters creates N
 *   clusters each containing the initial seed passed.
 */
  void testKMeansFixedSeeds();

/**
 * @brief Tests MoreClusterThanPointsException()
 *
 * Performed Tests:
 * - Ensure that partitionning N points into N+1 clusters raises a
 *   qgar::QgarErrorAlgorithm exception.
 */
  void testMoreClusterThanPointsException();

/**
 * @brief Tests DefaultConstructor()
 *
 * Performed Tests:
 * - 
 */
  void testClusterDefaultConstructor();

/**
 * @brief Tests ClusterCopyConstructor()
 *
 * Performed Tests:
 * - 
 */
  void testClusterCopyConstructor();

/**
 * @brief Tests ClusterAssigmentOp()
 *
 * Performed Tests:
 * - 
 */
  void testClusterAssigmentOp();

//@}


// -------------------------------------------------------------------
// P R O T E C T E D
// -------------------------------------------------------------------
protected:

  std::vector<qgar::DPoint> _pointVect;
  

// -------------------------------------------------------------------
}; // class GenKMeansTest


#endif /* __GENKMEANSTEST_H_INCLUDED__ */
