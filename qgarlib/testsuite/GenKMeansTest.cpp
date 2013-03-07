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
 * @file  GenKMeansTest.cpp
 * @brief Implementation of class GenKMeansTest
 *
 *        See file GenKMeansTest.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 24, 2004  18:05
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenKMeansTest.cpp,v 1.5 2005/10/14 17:06:36 masini Exp $ */



// STD
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <numeric>
// QGAR
#include <qgarlib/GenKMeans.h>
// QGAR TESTS
#include "GenKMeansTest.h"


using namespace qgar;
using namespace std;



// ------------------------------------------------------------------
// U N N A M E D   N A M E S P A C E
// ------------------------------------------------------------------
namespace
{


  // Creates a random double point whose coordinates are in [0..999]

  DPoint createPoint()
  {
    double x, y;
    x = double(rand()) / RAND_MAX * 1000;
    y = double(rand()) / RAND_MAX * 1000;
    return DPoint(x, y);
  }


  // Computes the euclidian distance between two points

  double euclidianDist(const DPoint& a, const DPoint& b) 
  {
    return qgDist(a,b);
  }


  // Checks that each point of each cluster is closer to the center
  // of the cluster it belongs to, than to any other cluster center.

  void checkClusters(const GenKMeans<DPoint>& means)
  {
    for(int i=0; i < means.clusterCnt(); i++)  // For each cluster
      {
	vector<const DPoint*> currentClu= means.clusterElts()[i];

	for(vector<const DPoint*>::iterator it = currentClu.begin();
	    it != currentClu.end();
	    ++it)
	  {
	    double distToCenter = euclidianDist(**it, *means.clusterCenters()[i]);
	    for(int j=0; j < means.clusterCnt(); j++)
	      {
		CPPUNIT_ASSERT
		  (euclidianDist(**it, *means.clusterCenters()[j]) >= distToCenter);
	      } // END for j
	  } // END for it
      } // END for i
  }


} // unnamed namespace


// ------------------------------------------------------------------
// S T A T I C   M E M B E R   I N I T
// ------------------------------------------------------------------

const int GenKMeansTest::NB_POINTS = 200;

const int GenKMeansTest::NB_CLUSTERS = 3;

// ------------------------------------------------------------------
// T E S T F I X T U R E   I M P L
// ------------------------------------------------------------------

void
GenKMeansTest::setUp()
{
  for (int i = 0; i < NB_POINTS; ++i) 
    {
      _pointVect.push_back(createPoint());
    }
}

// -------------------------------------------------------------------

void
GenKMeansTest::tearDown()
{
  /* EMPTY */
}


// -------------------------------------------------------------------
// T E S T   F U N C T I O N S
// -------------------------------------------------------------------

void
GenKMeansTest::testKMeans()
{
  // -------
  // Process
  // -------

  GenKMeans<DPoint> means(_pointVect, 
			  euclidianDist,
			  NB_CLUSTERS);


  // -----
  // Check
  // -----

  // Ensure that all points have been distributed into the clusters

  vector<int> csize = means.clusterSizes();
  CPPUNIT_ASSERT_EQUAL(int(_pointVect.size()), 
		       accumulate(csize.begin(), csize.end(), 0));

  // Ensure that no cluster is empty
  for (int i=0; i < means.clusterCnt(); ++i) {
    CPPUNIT_ASSERT(! (means.clusterElts())[i].empty() );
  }


  // Ensure that each point of a cluster is closer to its centers than
  // to any other center.
  checkClusters(means);

  // Ensure that sorting N points in N clusters leads to N clusters
  // each containing a point.
  GenKMeans<DPoint> means2(_pointVect, euclidianDist, NB_POINTS);
  CPPUNIT_ASSERT_EQUAL(NB_POINTS, means2.clusterCnt());

  for (int i=0; i < means2.clusterCnt(); ++i)
    {
      CPPUNIT_ASSERT_EQUAL(size_t(1), means2.clusterElts()[i].size());
    }
}

// -------------------------------------------------------------------

void
GenKMeansTest::testKMeansFixedSeeds()
{
  // Ensure that a clustering of N points in N cluster given N seeds
  // yields a cluster of 1 elt: the passed seed.

  // -----
  // Setup
  // -----

  vector<DPoint> centerVect(_pointVect);


  // -------
  // Process
  // -------  
  
  GenKMeans<DPoint> means(_pointVect,
			  euclidianDist,
			  centerVect,
			  NB_POINTS);
  
  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL(NB_POINTS, means.clusterCnt());

  for (int i=0; i < means.clusterCnt(); ++i) 
    {
      CPPUNIT_ASSERT_EQUAL(centerVect[i], * means.clusterCenters()[i]);
    }
}

// -------------------------------------------------------------------

void
GenKMeansTest::testMoreClusterThanPointsException()
{
  // Try to create more clusters than passed points.
  GenKMeans<DPoint> means(_pointVect, euclidianDist, NB_POINTS + 1);
}

// -------------------------------------------------------------------

void
GenKMeansTest::testClusterDefaultConstructor()
{
  // ------
  // Set up
  // ------

  vector<DPoint> vect;
  copy(_pointVect.begin(), _pointVect.end(), back_inserter(vect));


  // -------
  // Process
  // -------

  GenCluster<DPoint> cluster(vect, vect.front());


  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL(vect.size(), cluster.size());

  for (unsigned int i=0; i < vect.size(); ++i)
    {
      CPPUNIT_ASSERT_EQUAL(vect[i], cluster.elements()[i]);
    }
  CPPUNIT_ASSERT_EQUAL(vect.front(), cluster.center());
}

// -------------------------------------------------------------------

void
GenKMeansTest::testClusterCopyConstructor()
{
  // ------
  // Set up
  // ------

  vector<DPoint> vect;
  copy(_pointVect.begin(), _pointVect.end(), back_inserter(vect));
  GenCluster<DPoint> cluster(vect, vect.front());


  // -------
  // Process
  // -------

  GenCluster<DPoint> dupCluster(cluster);


  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL(cluster.size(), dupCluster.size());
  
  CPPUNIT_ASSERT_EQUAL(cluster.center(), dupCluster.center());
  for(unsigned int i=0; i < cluster.size(); ++i) 
    {
      CPPUNIT_ASSERT_EQUAL(cluster.elements()[i],
			   dupCluster.elements()[i]);
    }
}

// -------------------------------------------------------------------

void
GenKMeansTest::testClusterAssigmentOp()
{
  // ------
  // Set up
  // ------

  vector<DPoint> vect;
  copy(_pointVect.begin(), _pointVect.end(), back_inserter(vect));
  GenCluster<DPoint> cluster(vect, vect.front());

  GenCluster<DPoint> dupCluster(vect, DPoint());


  // -------
  // Process
  // -------

  dupCluster = cluster;


  // -----
  // Check
  // -----

  CPPUNIT_ASSERT_EQUAL(cluster.size(), dupCluster.size());
  
  CPPUNIT_ASSERT_EQUAL(cluster.center(), dupCluster.center());
  for(unsigned int i=0; i < cluster.size(); ++i) 
    {
      CPPUNIT_ASSERT_EQUAL(cluster.elements()[i],
			   dupCluster.elements()[i]);
    }

  CPPUNIT_ASSERT( &dupCluster == &(dupCluster = cluster) );
}

// -------------------------------------------------------------------
