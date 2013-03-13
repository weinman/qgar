/*---------------------------------------------------------------------+
 | Library QgarLib, graphics analysis and recognition                  |
 | Copyright (C) 2002  Qgar Project, LORIA                             |
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
 | http://www.gnu.org/licenses/lgpl.html for the terms of the licence. |
 | To receive a paper copy, write to the Free Software Foundation,     |
 | Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.       |
 |                                                                     |
 | Contact Project Qgar for any information:                           |
 |   LORIA - йquipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-lиs-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/


/**
 * @file   Maer.cpp
 * @brief  Implementation of class qgar::Maer.
 *
 * See file Maer.h for the interface.
 *
 * @author <a href="mailto:chesnokov.yuriy@gmail.com?subject=Qgar fwd Chesnokov Yuriy">Chesnokov Yuriy</a>
 * @date   Mar 12, 2013 10:00
 * @since  Qgar 4.0.0 
 */



// STD
#include <cmath>
#include <limits>
#include <list>
// QGAR
#include <qgarlib/FreemanChain.h>
#include <qgarlib/GenConvexHull.h>
#include <qgarlib/Maer.h>
#include <qgarlib/math.h>
#include <qgarlib/primitives.h>
#include <qgarlib/QgarErrorDeveloper.h>



namespace qgar
{


/**
 * @ingroup TOOL_MAER
 *
 * @class ThetasComparer Maer.cpp "qgarlib/Maer.cpp"
 *
 * @brief Thetas comparer functor
 *
 * Compares thetas at a given error tolerance
 *
 * @author <a href="mailto:chesnokov.yuriy@gmail.com?subject=Qgar fwd Chesnokov Yuriy">Chesnokov Yuriy</a>
 * @date   Mar 12, 2013 10:00
 * @since  Qgar 4.0.0
 */
class ThetasComparer : public std::unary_function<double, bool>
{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Create thetas comparer functor
   *
   * @param aTheta      angle to compare to
   * @param aTolerance  comparison error tolerance
   */
  ThetasComparer(double aTheta, double aTolerance = Math::epsilonRadian())
    {
      theta_ = aTheta;
      tolerance_ = aTolerance;
    }

  //@}

  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief 
   *
   * @param aValue  a theta value to compare to
   */
  bool operator()(double aValue)
    {
      return qgEqRadian(theta_, aValue);
    }

  //@}

// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  /** @name Private data */
  //        ============
  //@{

  /**
   * @brief Theta angle to compare to.
   */
  double theta_;

  /**
   * @brief Comparison error tolerance.
   */
  double tolerance_;

  //@}

// -------------------------------------------------------------------
};  // class ThetaComparer



// -------------------------------------------------------------------
// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// ___________________________________________________________________
//
// WARNING: the default constructor belongs to the private section
// so that clients cannot use it

Maer::Maer()
{
  throw QgarErrorDeveloper(__FILE__, __LINE__,
			   "qgar::Maer::Maer()",
			   "Disabled constructor: should not be used!");
}
// ___________________________________________________________________


// CREATE FROM A FREEMAN CHAIN

Maer::Maer(const FreemanChain& aCh)
{
  PRIVATEcomputeMaer(aCh.toDPointList());
}


// COPY CONSTRUCTOR

Maer::Maer(const Maer& aMaer)

  : vertices_  (aMaer.vertices_),
    areaPx_    (aMaer.areaPx_)

{
  // VOID
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// D E S T R U C T O R
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// NON-VIRTUAL DESTRUCTOR

Maer::~Maer()
{
  // VOID
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// A C C E S S   T O   C O R N E R S
// -------------------------------------------------------------------
// -------------------------------------------------------------------

// GET THE LIST INCLUDING THE 4 CORNERS OF THE MAER

const std::list<DPoint>&
Maer::accessVertices() const
{
  return vertices_;
}
  
// GET A COPY OF THE LIST INCLUDING THE 4 CORNERS OF THE MAER

std::list<DPoint>
Maer::vertices() const
{
  return vertices_;
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// O P E R A T O R S
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// ASSIGNMENT

Maer&
Maer::operator=(const Maer& aMaer)
{
  // Are left hand side and right hand side different objects?
  if (this != &aMaer)
    {
      vertices_ = aMaer.vertices_;
      areaPx_   = aMaer.areaPx_;
    }

  return *this;
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// C O N S T R U C T I O N   O F   T H E   M A E R   (PRIVATE)
// -------------------------------------------------------------------
// -------------------------------------------------------------------


void
Maer::PRIVATEcomputeMaer(const std::list<DPoint>& aPtList)
{
  // THE CONVEX HULL OF THE GIVEN POINTS
  // ===================================

  DConvexHull hull(aPtList);

  // THE COMPONENT IS A SINGLE POINT: DEGENERATED MAER
  // =================================================

  if (hull.size() == 1)
    {
      // 4 same corners and null area
      vertices_.push_back(hull.accessPivot());
      vertices_.push_back(hull.accessPivot());
      vertices_.push_back(hull.accessPivot());
      vertices_.push_back(hull.accessPivot());
      areaPx_ = 1.;
      return;
    }  

  // COMPUTE THE DIFFERENT RECTANGLES AND SELECT THE MINIMAL ONE
  // ===========================================================  

  // Current minimum area
  areaPx_ = Math::QG_DOUBLE_MAX;

  // List of the vertices of the hull
  const std::list<DPoint>& vList = hull.accessVertices();

  // List of unique angles between 2 consecutive points of the hull
  std::list<double> thetas;

  // 2 consecutive points of the hull
  std::list<DPoint>::const_iterator itPrev = vList.begin();
  std::list<DPoint>::const_iterator itCurr = itPrev;
  itCurr++;

  // Consider each consecutive pair of hull vertices
  // and compute the corresponding rectangle
  // WARNING: The last pair includes the last and first vertices

  do    
    {
      // Direction of the vector joining previous and current points 
      double theta = atan2(itCurr->y() - itPrev->y(), itCurr->x() - itPrev->x());
      // Move the angle into the first quadrant with matlab mod implementation
      theta = theta - floor(theta / Math::QG_PI_2) * Math::QG_PI_2;

      // Check if similar angle was not processed before      
      if (!IsThetaPresent(theta, thetas))
        {
          thetas.push_back(theta);

          // Sinus and cosinus
          double cosTheta = cos(-theta);
          double sinTheta = sin(-theta);

          // Initializations
          double minX = Math::QG_DOUBLE_MAX;
          double maxX = -Math::QG_DOUBLE_MAX;
          double minY = Math::QG_DOUBLE_MAX;
          double maxY = -Math::QG_DOUBLE_MAX;
      
          // Minimum and maximum X and Y
          for (std::list<DPoint>::const_iterator itV = vList.begin(); itV != vList.end(); ++itV)
            { 
              // Rotate the data through -theta
              double x = itV->x() * cosTheta + itV->y() * (-sinTheta);
              double y = itV->x() * sinTheta + itV->y() * cosTheta;	  
	  
	      // Update coordinates min's and max's
	      if (x < minX)
	        {
	          minX = x;
	        }
	      else if (x > maxX)
	        {
	          maxX = x;
	        }

	      if (y < minY)
	        {
	          minY = y;
	        }
	      else if (y > maxY)
	        {
	          maxY = y;
	        }
            }
      
          // Current area
          double currArea = ((maxX - minX) + 1) * ((maxY - minY) + 1);

          if (currArea < areaPx_)
            {
              areaPx_ = currArea;

              vertices_.clear();          
              // Unrotate coordinates
              vertices_.push_back(DPoint(minX * cosTheta + minY * sinTheta, minX * (-sinTheta) + minY * cosTheta));
              vertices_.push_back(DPoint(maxX * cosTheta + minY * sinTheta, maxX * (-sinTheta) + minY * cosTheta));
              vertices_.push_back(DPoint(maxX * cosTheta + maxY * sinTheta, maxX * (-sinTheta) + maxY * cosTheta));
              vertices_.push_back(DPoint(minX * cosTheta + maxY * sinTheta, minX * (-sinTheta) + maxY * cosTheta));
            }
        }      

      // Next vertices pair
      // WARNING: The last pair includes the last and first vertices
      itPrev = itCurr;
      itCurr++;
      if (itCurr == vList.end())
	{
	  itCurr = vList.begin();
	}
    }
  while (itPrev != vList.begin());
}


// CHECKS THETA ANGLE PRESENSE


bool
Maer::IsThetaPresent(double aTheta, const std::list<double>& aThetasList, double aTolerance)
{
  return std::find_if(aThetasList.begin(), aThetasList.end(), ThetasComparer(aTheta, aTolerance)) != aThetasList.end();
}


// -------------------------------------------------------------------

} // namespace qgar
