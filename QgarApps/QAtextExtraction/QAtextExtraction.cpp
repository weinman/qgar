/*---------------------------------------------------------------------*
 | Library QgarApps, graphics analysis and recognition applications    |
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
 * @file  QAtextExtraction.cpp
 *
 * @brief Extract textual parts from a binary image
 * which exclusively includes textual components.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar">Karl Tombre, Philippe Dosch & Bart Lamiroy</a>
 * @date  August 8,  1999  1:50
 * @since Qgar 1.0
 */



// STD
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <map>
#include <set>
#include <vector>
// QGAR
#include <qgarlib/BoundingBox.h>
#include <qgarlib/Component.h>
#include <qgarlib/ConnectedComponents.h>
#include <qgarlib/DxfFile.h>
#include <qgarlib/File.h>
#include <qgarlib/GenImage.h>
#include <qgarlib/GenTree.h>
#include <qgarlib/math.h>
#include <qgarlib/PbmFile.h>
#include <qgarlib/primitives.h>
#include <qgarlib/QgarApp.h>



#define MAJOR_VERSION 1
#define MINOR_VERSION 0



using namespace std;
using namespace qgar;



// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TYPEDEF
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
 

/**
 * @ingroup TEXT_STRINGS
 *
 * @brief Pointer to a component tree node (representing a component).
 */
typedef ConnectedComponents::node_type QGTnode;


/**
 * @ingroup TEXT_STRINGS
 *
 * @brief Label type.
 */
typedef Component::label_type QGTlabel;


// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT




// -------------------------------------------------------------------
// -------------------------------------------------------------------
// L A B E L E D   P O I N T S
// -------------------------------------------------------------------
// -------------------------------------------------------------------


/**
 * @ingroup TEXT_STRINGS
 *
 * @class LabeledPoint
 *
 * @brief A point associated with a label.
 *
 * @todo To be documented!...
 */

class LabeledPoint

  : public GenPoint<int>

{
public:

  /// Default constructor
  LabeledPoint() : Point(0,0), _label(0)
  {
    // VOID
  }

  /// Construct from point and label
  LabeledPoint(Point& p, Component::label_type l)

    : Point(p),
      _label(l)

  {
    // void
  }

  /// Construct from abscissa, ordinate and label
  LabeledPoint(int x, int y, Component::label_type l)

    : Point(x,y),
      _label(l)

  {
    // VOID
  }

  /// Copy-constructor
  LabeledPoint(const LabeledPoint& lp)

    : Point(lp.x_, lp.y_),
      _label(lp._label)

  {
    // VOID
  }

  /// Destructor
  ~LabeledPoint()
  {
    // VOID
  }

  /// Get label
  Component::label_type label() const
  {
    return _label;
  }

  /// Equality operator
  bool operator==(const LabeledPoint& lp) const
  {
    return(_label == lp._label);
  }

  /// Inequality operator
  bool operator!=(const LabeledPoint& lp) const
  {
    return(_label != lp._label);
  }

  /// Operator greater than
  bool operator>(const LabeledPoint& lp) const
  {
    return(_label > lp._label);
  }

  /// Operator less than
  bool operator<(const LabeledPoint& lp) const
  {
    return(_label < lp._label);
  }

protected:

  /// Representation of a labeled point
  Component::label_type _label;
};


// SET OF LABELED POINTS
// =====================


/**
 * @ingroup TEXT_STRINGS
 *
 * @brief Comparison of labels.
 */

struct lessLabel

  : std::binary_function<QGTlabel, QGTlabel, bool>

{
  bool operator()(const QGTlabel& aX, const QGTlabel& aY) const
  {
    return (aX < aY);
  }
};


/**
 * @ingroup TEXT_STRINGS
 *
 * @brief Set of integers.
 *
 * Just a redefinition of an instance of STL template class <b>set</b>.
 */
typedef std::set<QGTlabel, lessLabel> QGTlabSet;


/**
 * @ingroup TEXT_STRINGS
 *
 * @brief Comparison of labeled points.
 */

struct lessLabeledPoints

  : std::binary_function<LabeledPoint, LabeledPoint, bool>

{
  bool operator()(const LabeledPoint& aX,
		  const LabeledPoint& aY) const 
    {
      return aX < aY;
    }
};


/**
 * @ingroup TEXT_STRINGS
 *
 * @brief Set of labeled points.
 *
 * Just a redefinition of an instance of STL template class <b>set</b>.
 */
typedef std::set<LabeledPoint, lessLabeledPoints> LabeledPointSet;


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// C O M P O N E N T S
// -------------------------------------------------------------------
// -------------------------------------------------------------------


/**
 * @ingroup TEXT_STRINGS
 *
 * @brief Get black component from a component tree.
 *
 * @param aPNode 
 * @param aSet   
 *
 * @todo To be documented!...
 */
void
qaGetBlackCC(QGTnode* aPNode, QGTlabSet& aSet)
{
  if (aPNode != 0)
    {
      Component* cc = aPNode->data();

      if (cc->color() == QGE_BW_BLACK)
	{
	  aSet.insert(cc->label());
	}

    QGTnode* p = aPNode->pFirstChild();

    while (p != 0)
      {
	qaGetBlackCC(p, aSet);
	p = p->pRSibling();
      }
    } // END if
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// B O U N D I N G   B O X E S
// -------------------------------------------------------------------
// -------------------------------------------------------------------


/**
 * @ingroup TEXT_STRINGS
 *
 * @brief Get X (resp. Y) coordinate of the center point of a
 *  vertical (resp. horizontal) bounding box.
 *
 * @param aBB  
 * @param aDir 
 *
 * @todo To be documented!...
 */
inline int
qaGetCenterCoord(const BoundingBox& aBB, QGEorientation aDir)
{
  if (aDir == QGE_ORIENTATION_HOR)
    {
      return (aBB.yTopLeft() + aBB.yBottomRight()) / 2;
    }
  else
    {
      return (aBB.xTopLeft() + aBB.xBottomRight()) / 2;
    }
}


/**
 * @ingroup TEXT_STRINGS
 *
 * @brief To horizontally sort bounding boxes
 *   using Y coordinate of top left corners.
 */
struct LabelOrderingHoriz
{
private:

  const ConnectedComponents& _cc;

public:

  LabelOrderingHoriz(const ConnectedComponents& anImg)

    : _cc(anImg)

  {
    // VOID
  }

  bool operator()(QGTlabel aLab1, QGTlabel aLab2) const
  {
    return   (_cc[aLab1].accessBoundingBox()).yTopLeft()
	   < (_cc[aLab2].accessBoundingBox()).yTopLeft();
  }
};
  

/**
 * @ingroup TEXT_STRINGS
 *
 * @brief To vertically sort bounding boxes
 *   using X coordinate of top left corners.
 */
struct LabelOrderingVerti
{
private:

  const ConnectedComponents& _cc;

public:

  LabelOrderingVerti(const ConnectedComponents& anImg)
    : _cc(anImg)
  {
    // VOID
  }

  bool operator()(QGTlabel lab1, QGTlabel lab2) const
  {
    return    (_cc[lab1].accessBoundingBox()).xTopLeft()
	    < (_cc[lab2].accessBoundingBox()).xTopLeft();
  }
};


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// W O R D S
// -------------------------------------------------------------------
// -------------------------------------------------------------------


/**
 * @ingroup TEXT_STRINGS
 *
 * @brief Get component chains representing words.
 *
 * @param aLabelSet  
 * @param anAngle    
 * @param aResList   
 * @param aGap       
 * @param aCC        
 *
 * @todo To be documented!...
 */
void
qaGetWords(const QGTlabSet& aLabelSet,
	   int anAngle,
	   list<QGTlabSet>& aResList,
	   float aGap,
	   const ConnectedComponents& aCC)
{
  QGEorientation const sortOrientation
    = ((anAngle < 45) || (anAngle > 135))
      ? QGE_ORIENTATION_HOR
      : QGE_ORIENTATION_VER;

  // Create vector 'theLabels' of labels from the given set of labels

  vector<QGTlabel> theLabels;
  theLabels.reserve(aLabelSet.size());

  for (QGTlabSet::const_iterator itLS = aLabelSet.begin(); 
       itLS != aLabelSet.end();
       ++itLS)
    {
      theLabels.push_back(*itLS);
    }

  // Sorting labels top-down / left-right wrt to the topleft Bbox angle

  LabelOrderingHoriz const horizSortFunctor(aCC);
  LabelOrderingVerti const vertiSortFunctor(aCC);

  if (sortOrientation == QGE_ORIENTATION_HOR)
    {
      sort(theLabels.begin(), theLabels.end(), horizSortFunctor);
    }
  else
    {
      sort(theLabels.begin(), theLabels.end(), vertiSortFunctor);
    }
  
  //  Compute average height of components in set

  long int sumHeights = 0;
  vector<QGTlabel>::const_iterator itV; // itV is used further on...

  if (sortOrientation == QGE_ORIENTATION_HOR)
    {
      for(itV = theLabels.begin();
	  itV != theLabels.end();
	  ++itV)
	{
	  sumHeights += (aCC[*itV].accessBoundingBox()).height();
	}
    }
  else
    {
      for(itV = theLabels.begin();
	  itV != theLabels.end();
	  ++itV)
	{
	  sumHeights += (aCC[*itV].accessBoundingBox()).length();
	}
    }

  // Set gap threshold according to average height
  const float averageHeight = ((float)sumHeights) / theLabels.size();
  int gapThres = (int) (aGap * averageHeight);
  

  // FIND THE WORDS OF THE TEXTUAL PARTS
  // - store first character in the current word (currWord)
  // - run through all other characters.
  // - IF the distance (according to sortOrientation) lies under aGapThres
  //   THEN aggregate current character to current word
  //   ELSE
  //     * add current word to final list
  //     * create new current word with current character

  // 1. Initializations
  itV = theLabels.begin();
  QGTlabSet* currWord = new QGTlabSet;

  // 2. Add first character to the current word
  currWord->insert(*itV);

  int lastCoord = 0;
  int newCoord  = 0;
  int totalsize = 0;

  lastCoord = qaGetCenterCoord(aCC[*itV].accessBoundingBox(),
			       sortOrientation);

  // 3. Run through all other characters
  for (++itV ; itV != theLabels.end(); ++itV)
    {

      // Take next reference position
      newCoord = qaGetCenterCoord(aCC[*itV].accessBoundingBox(),
				  sortOrientation);
    
      // Compute distance with current reference position
      // Note that the current vector is sorted: No absolute value required
      if ((newCoord - lastCoord) < gapThres)
	{
	  // add to current word
	  currWord->insert(*itV);
	}
      else
	{
	  // Store current word in result list
	  aResList.push_back(*currWord);

	  totalsize += currWord->size();

	  delete currWord;
	  currWord = new QGTlabSet;

	  // add current label to new word
	  currWord->insert(*itV);
	}
    
      // update current reference position
      lastCoord = newCoord;

    } // END for 3


  // store last word in result list
  aResList.push_back(*currWord);

  totalsize += currWord->size();

  delete currWord;
}


/**
 * @ingroup TEXT_STRINGS
 *
 * @brief Get average word angle.
 *
 * Very simple algorithm: There is no need for least squares
 * or stuff like that... Everything <i>is</i> nicely aligned.
 *
 * @param aWord 
 * @param aCC   
 *
 * @todo To be documented!...
 */
inline double
computeAngle(QGTlabSet& aWord,
	     const ConnectedComponents& aCC)
{
  double       meanAngle = 0.;
  unsigned int counter   = 0;

  for(QGTlabSet::iterator itW1 = aWord.begin(); itW1 != aWord.end() ; )
  {   
      QGTlabSet::iterator itWCurr = itW1;
      ++itW1;

      for(QGTlabSet::iterator itW2 = itW1; 
	  itW2 != aWord.end();
	  ++itW2)
	{
      
	  meanAngle +=
	    qgAngle(aCC[*itWCurr].accessBoundingBox().bottomRight() +
		    aCC[*itWCurr].accessBoundingBox().accessTopLeft(),
	            aCC[*itW2].accessBoundingBox().bottomRight() +
                    aCC[*itW2].accessBoundingBox().accessTopLeft());

	  ++counter;
	}
    }

  return meanAngle / counter;
}


/**
 * @ingroup TEXT_STRINGS
 *
 * @brief Get the list of labels making up words.
 *
 * Each label is associated the word in which it occurs.
 *
 * @param aWordList 
 * @param aCC       
 * @param aGap      
 *
 * @todo To be documented!...
 */
void
filterWords(list<QGTlabSet>& aWordList,
	    const ConnectedComponents& aCC,
	    float aGap)
{
  set<QGTlabel> theLabels;
  multimap<QGTlabel, QGTlabSet*> characterMap;
  set<QGTlabSet*> wordSet;

  for(list<QGTlabSet>::iterator itW = aWordList.begin(); 
      itW != aWordList.end();
      ++itW)
    {
      QGTlabSet* currentWord = &*itW;
      wordSet.insert(currentWord);

      for(QGTlabSet::iterator itWin = currentWord->begin();
	  itWin != itW->end();
	  ++itWin)
	{
	  if(theLabels.count(*itWin) == 0)
	    {
	      theLabels.insert(*itWin);
	    }

	  characterMap.insert(pair<QGTlabel,QGTlabSet*>(*itWin, currentWord));
	}
    }

  // At this point, wordSet contains a set of words possibly sharing
  // the same characters. We are now going to filter out multiple
  // occurences of the same letter in different words.

  // In normal cases a label appearing in several words should
  // belong to only one word with length > 1 ... this is an
  // assumption that needs a verification.
  // Current heuristic: assign label to longest word
  // (current algorithm will not work with cross-word like
  // constructions, furthermore, the result depends on the order in
  // which the letters are considered ... this is bad !)

  // splitSet will contain the list of words from which labels are to
  // be removed and which have length >= 3
  set<QGTlabSet*> splitSet;

  // For all Labels :
  // - Find the words to which it belongs
  // - Select the longest word
  // - Remove the label from all other words, and mark the words that
  //   risk to be split in two sub words by removing the label.

  for (set<QGTlabel>::const_iterator itL = theLabels.begin() ; 
       itL != theLabels.end();
       ++itL)
    {
      unsigned int maxWordLength = 0;
      QGTlabSet* longestWord = 0;

      // Select the set of words to which the label belongs
      pair<multimap<QGTlabel, QGTlabSet*>::iterator,
	   multimap<QGTlabel, QGTlabSet*>::iterator>
	range = characterMap.equal_range(*itL); 

      for (multimap<QGTlabel, QGTlabSet*>::iterator itMap = range.first; 
	   itMap != range.second;
	   ++itMap)
	{
	  // ... assign label to longest word i.e. 
	  // remove label from other words and mark words for splitting in
	  // sub-words where necessary 
	  QGTlabSet* currentWord = itMap->second;

	  if(currentWord->size() > maxWordLength)
	    {
	      if(maxWordLength > 3)
		{
		  splitSet.insert(longestWord);
		  longestWord->erase(*itL);
		}

	      maxWordLength = currentWord->size();
	      longestWord = currentWord;
	    }
	  else
	    {
	      if(currentWord->size() > maxWordLength)
		{
		  splitSet.insert(currentWord);
		}

	      currentWord->erase(*itL);
	    } //

	} // END for multimap

  } // END for


  // At this stage each label belongs to a unique word, however, the
  // words in wordSet may be empty or may need to be split up in sub
  // words

  list<QGTlabSet> finalResList; 

  for(set<QGTlabSet*>::iterator itLS = wordSet.begin();
      itLS != wordSet.end();
      ++itLS)
    {
      // if the word is not empty
      QGTlabSet* currentWord = *itLS;
      unsigned int wordSize = currentWord->size();

      if(wordSize != 0)
	{      
	  // check if the word is referenced in splitSet
	  if((wordSize > 1) && (splitSet.count(currentWord) != 0))
	    {
	      int angle = (int) computeAngle(*currentWord, aCC);

	      list<QGTlabSet> tmpList;

	      qaGetWords(*currentWord, angle, tmpList, aGap, aCC);

	      finalResList.merge(tmpList);
	    }
	  else
	    {
	      finalResList.push_back(*currentWord);
	    }
	}
    } // END for

  aWordList = finalResList;

} // END function


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// H O U G H   T R A N S F O R M
// -------------------------------------------------------------------
// -------------------------------------------------------------------


/**
 * @ingroup TEXT_STRINGS
 *
 * @brief Hough transform.
 *
 * Common Hough parameterization consists in associating a point (x,y)
 * with all lines passing by it. In polar coordinates, the equation
 * of a line is:
@verbatim
x cos(theta) + y sin(theta) = rho
@endverbatim
 * rho is the distance from the line to the origin of the coordinate
 * system, theta is the angle perpendicular to the line orientation.
 *
 * @param aResolution 
 * @param aMaxDim     
 * @param anAngleSet  
 * @param aPointSet   
 * @param aMaxRTC     
 * @param aMinRTC     
 * @param aResList    
 * @param aGap        
 * @param aCC         
 *
 * @todo To be documented!...
 */

void
qaHough(float aResolution,
	int aMaxDim, 
	const QGTlabSet& anAngleSet,
	const LabeledPointSet& aPointSet,
	int aMaxRTC,
	int aMinRTC,
	list<QGTlabSet>& aResList,
	float aGap,
	ConnectedComponents const& aCC)
{
  // Initialization: Creation of the Hough table

  unsigned int const MAX_THETA = 181;
  unsigned int const numrho = (unsigned int) ((2 * aMaxDim - 1) / aResolution) + 1;
  int* counters[MAX_THETA];

  for (unsigned int idx = 0 ; idx < MAX_THETA ; ++idx)
    {
      int* p = counters[idx] = new int [numrho];
      for(int* pIter = p + numrho; pIter != p; *--pIter = 0)
	{
	  // VOID
	}
    }


  // Apply Hough transform to all components
  // for horizontal and vertical directions
  
  LabeledPointSet pointSetCopy(aPointSet);

  for (LabeledPointSet::const_iterator itPT = pointSetCopy.begin(); 
       itPT != pointSetCopy.end();
       ++itPT)
    {
      // *itPT gives a point (x,y)
      double const x = (double) itPT->x();
      double const y = (double) itPT->y();

      for (unsigned int theta = 0 ; theta < MAX_THETA ; ++theta)
	{
	  if (anAngleSet.count(theta) != 0)
	    {
	      int rho = (int) (x * cos(qgDegreesToRadians(theta)) +
			       y * sin(qgDegreesToRadians(theta)));

	      // Voting for (theta,rho): increment counters[theta][rho_index]
	      ++counters[theta][(int) ((rho + aMaxDim - 1) / aResolution)];
	    }
	} // END for theta
    }


  
  // Set running threshold

  for (int rtc = aMaxRTC ; rtc >= aMinRTC ; --rtc)
    {
      // 4. For each cell having a count greater than rtc

      for (unsigned int i = 0 ; i < MAX_THETA ; ++i)
	{
	  if (anAngleSet.count(i) != 0) // not necessary to check for others
	    {
	      int* p = counters[i];

	      for (unsigned int j = 0 ; j < numrho ; j++)
		{
		  if (*p++ > rtc)
		    {
		      QGTlabSet aLabelSet;
		      
		      // 5. Form a cluster of 11 rho cells centered around primary cell
		      int minrho = (int) (max(0, (int) j-5) * aResolution) - aMaxDim + 1;
		      int maxrho = (int) (min((int) j+5, (int) numrho-1) * aResolution) - aMaxDim + 1;

		      list<LabeledPointSet::iterator> removalList;

		      // 6. Find corresponding components
		      for (LabeledPointSet::iterator itPT = pointSetCopy.begin();
			   itPT != pointSetCopy.end();
			   ++itPT)
			{
			  // *itPT gives a point (x,y)
			  double x = (double) (*itPT).x();
			  double y = (double) (*itPT).y();

			  int rho = (int) (x * cos(qgDegreesToRadians(i)) +
					   y * sin(qgDegreesToRadians(i)));

			  if ((rho >= minrho) && (rho <= maxrho))
			    {
			      // I have found one
			      // Insert in current set of labels
			      aLabelSet.insert((*itPT).label());
			      removalList.push_back(itPT);

			      // Delete contribution of this component to the HT
			      for (unsigned int theta = 0 ; theta < MAX_THETA ; ++theta)
				{
				  if (anAngleSet.count(theta) != 0)
				    {
				      int rho = (int) (x * cos(qgDegreesToRadians(theta)) +
						       y * sin(qgDegreesToRadians(theta)));

				      // Voting for (theta,rho):
				      // increment counters[theta][rho_index]
				      --counters[theta][(int) ((rho + aMaxDim - 1) / aResolution)];
				    }
				} // END for theta
			    }
			} // END for itP


// ##############################################################################################
#if ( MAJOR_VERSION == 1 )

		      for(list<LabeledPointSet::iterator>::iterator element = removalList.begin();
			  element != removalList.end() ; ++element)
			{
			  pointSetCopy.erase(*element);
			}

#endif
// ##############################################################################################


		      // Perform string segmentation on aLabelSet
		      if (aLabelSet.size() > 0)  // should always be the case
			{
			  qaGetWords(aLabelSet, i, aResList, aGap, aCC);
			}
		    }
		} // END for j

	    }
	  
	} // END for i

    }

  // Cleanup: Delete Hough table

  for (unsigned int idx = 0 ; idx < MAX_THETA ; ++idx)
    {
      delete [] counters[idx];
    }

}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// M A I N
// -------------------------------------------------------------------
// -------------------------------------------------------------------

/**
 * @ingroup TEXT_STRINGS
 *
 * @brief  Extract character strings from a binary image
 *   including only textual components.
 *
 * Character strings, formed by closely positioned and similarly
 * oriented components, are constructed by a 2D Hough Transform.
 * The bounding boxes of the strings are saved in a file for
 * display purposes. The features of each string
 * (corners of its bounding box, number of characters,
 * corners of the bounding box of each character) are saved
 * in a separate file for further use.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar">Karl Tombre,
 *   Philippe Dosch & Bart Lamiroy</a>
 * @date   August 8, 1999  1:50
 * @since  Qgar 1.0
 */

int
main(int argc, char *argv[])
{
  QgarApp app;

  // PARAMETERS DESCRIPTION
  // ======================

  // Source image
  app.addParameter("-in",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEIN,
		   "source image:");

  // Features of the bounding boxes of the strings (ASCII)
  app.addParameter("-outxt",
  		   QgarArgs::REQPARAM,
  		   QgarArgs::FILEOUT,
  		   "ASCII file to store string features:",
  		   ".bbox.txt");

  // Bounding boxes of the strings for display purpose (DXF)
  app.addParameter("-outbb",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEOUTDS,
		   "DXF file to store string bounding boxes:",
		   ".bbox.dxf");

  // Maximum tolerated gap between characters
  app.addParameter("-char",
		   QgarArgs::REQPARAM,
		   QgarArgs::FLOAT,
		   "maximum character spacing:",
		   0,
		   "2.5");

  // Samplig rate of the Hough space
  app.addParameter("-hough",
		   QgarArgs::REQPARAM,
		   QgarArgs::FLOAT,
		   "Hough space sampling rate:",
		   0,
		   "0.2");

  app.setDescription("Text extraction", QgarArgs::PBM);

  // COMMAND LINE ANALYSIS
  // =====================

  app.analyzeLine(argc, argv);

  // Error while parsing parameters?
  if (app.isError())
    {
      return app._CODE_ERROR;
    }

  // Application invoked with flag '-gui'?
  if (app.isExit())
    {
      return app._CODE_GUI;
    }

  app.showProgressBar();
  app.setProgressBar(0);

  // GET PARAMETERS AND SOURCE IMAGE
  // ===============================

  cout << "Loading source image..." << endl;

  PbmFile sourceFile((char *) app.getStringOption("-in"));
  BinaryImage sourceImg = sourceFile.read();

  // Maximum gap tolerated between characters in a word.
  // Actually, it is a fraction of the average character height.
  float intraWordGap = atof(app.getStringOption("-char"));

  float chdr = atof(app.getStringOption("-hough"));

  app.setProgressBar(10);

  // GET BLACK COMPONENTS FROM SOURCE IMAGE
  // ======================================

  cout << "Extracting black components..." << endl;

  ConnectedComponents cc(sourceImg);

  QGTlabSet aSet;
  qaGetBlackCC(cc.pRoot(), aSet);

  app.setProgressBar(30);

  // COMPUTE AVERAGE HEIGHT OF COMPONENTS
  // ====================================

  // At the same time, create a set of labeled points
  // corresponding to centers of components

  // aSet contains the set of components corresponding to textual parts

  cout << "Computing average height of components..." << endl;
  
  // WARNING: Coordinates are switched here!
  LabeledPointSet centerPointSet;

  list<BoundingBox> listOrigCar;

  long int sumHeights = 0;

  QGTlabSet::const_iterator setIter = aSet.begin();
  while (setIter != aSet.end())
    {
      BoundingBox cRect = cc[*setIter].boundingBox();
      sumHeights += cRect.height();

      LabeledPoint midP(cRect.xTopLeft() + cRect.length()/2,
			sourceImg.height() - 1 - cRect.yBottomRight() + cRect.height()/2,
			(Component::label_type) *setIter);
      // Add to set
      centerPointSet.insert(midP);
      listOrigCar.push_back(cRect);

      ++setIter;
    }

  float averageBboxHeight = (float) (sumHeights) / (float) (aSet.size());

  app.setProgressBar(50);

  // HOUGH TRANSFORM FOR STRAIGHT (HORIZONTAL AND VERTICAL) ALIGNMENTS
  // =================================================================

  cout << "Performing Hough transform to get straight alignments..." << endl;

  // Hough domain resolution
  float houghResolution = averageBboxHeight * chdr;

  // Discrete angles corresponding to "straight" alignments
  QGTlabSet rightSet;
  int theta = 0;
  while (theta <= 180)
    {
      rightSet.insert(theta);
      ++theta;
    }
  
  int imageDiagonal =
    (int) hypot((double) sourceImg.height(), (double) sourceImg.width());

  // Hough Transform for straight (horizontal and vertical) alignments:
  // It produces a list of *strings* (aggregateList) formed by closely
  // positioned and similarly oriented components. 

  list<QGTlabSet> aggregateList;
  
  static unsigned int const maxrtc = 20;
  static unsigned int const minrtc = 0;

  qaHough(houghResolution,
	  imageDiagonal,
	  rightSet, 
	  centerPointSet, 
	  maxrtc,
	  minrtc,
	  aggregateList,
	  intraWordGap,
	  cc);

  app.setProgressBar(90);


// #######################################################################
#if ( MAJOR_VERSION == 2 )

  // After the Hough transform grouping, labels may belong to several
  // strings. filterWords assigns every label to a single string 
  filterWords(aggregateList, cc, intraWordGap);

#endif
// #######################################################################


  // SAVE RESULTS
  // ============

  cout << "Saving results..." << endl;

  DxfFile resultDXFfile(app.getStringOption("-outbb"));
  resultDXFfile.openWONLY();
  resultDXFfile.writeHeader();

  File resultTXTfile(app.getStringOption("-outxt"));
  resultTXTfile.openWONLY();

  for (list<QGTlabSet>::const_iterator itAL = aggregateList.begin();
       itAL != aggregateList.end();
       ++itAL)
    {

      list<BoundingBox> listCar;
      BoundingBox bbox = cc[*((*itAL).begin())].boundingBox();
    
      for (QGTlabSet::const_iterator itLS = (*itAL).begin(); 
	   itLS != (*itAL).end();
	   ++itLS)
	{
	  const BoundingBox& cRect = cc[*itLS].accessBoundingBox();

	  listCar.push_back(cRect);
      
	  bbox.setTopLeft(BoundingBox(bbox.topLeft(), cRect.topLeft()).topLeft());
	  bbox.setBottomRight(BoundingBox(bbox.bottomRight(), cRect.bottomRight()).bottomRight());
	}

      // Save DXF bounding box

      resultDXFfile.write(bbox, 1, QGE_COLOR_RED);
    
      // Save ASCII bounding box

      resultTXTfile.fstream() << "CHAIN\n";

      resultTXTfile.fstream() << bbox.xTopLeft()
			      << ' '
			      << bbox.yTopLeft()
			      << ' '
			      << bbox.xBottomRight()
			      << ' '
			      << bbox.yBottomRight()
			      << endl;

      resultTXTfile.fstream() << listCar.size() << endl;

      for(list<BoundingBox>::iterator itLC = listCar.begin();
	  itLC != listCar.end();
	  ++itLC)
	{
	  resultTXTfile.fstream() << (*itLC).xTopLeft()
				  << ' '
				  << (*itLC).yTopLeft()
				  << ' '
				  << (*itLC).xBottomRight()
				  << ' '
				  << (*itLC).yBottomRight()
				  << endl;
	}

    } // END for itAL

  resultDXFfile.writeFooter();
  resultDXFfile.close();

  resultTXTfile.close();

  // DISPLAY RESULT
  // ==============

  app.setProgressBar(100);
  cout << "Text extraction done." << endl;
  app.closeProgressBar();

  app.showPicture((char *)app.getStringOption("-outbb"));

  // NORMAL TERMINATION
  // ==================

  return app._CODE_END;

} // END main

// -------------------------------------------------------------------
// -------------------------------------------------------------------
