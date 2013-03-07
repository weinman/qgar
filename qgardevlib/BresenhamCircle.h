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
 |   LORIA - équipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-lès-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/

#ifndef __BRESENHAMCIRCLE_H_INCLUDED__
#define __BRESENHAMCIRCLE_H_INCLUDED__

/**
 * @file BresenhamCircle.h
 *
 * @class BresenhamCircle BresenhamCircle.h "qgardev/BresenhamCircle.h"
 * 
 * @brief Header file of class qgar::BresenhamCircle.
 *
 * <b>Warning: This is an experimental version. NO GARANTEE about bugs, errors
 * or any problems of it's use. Please, report problems to class author.</b>
 *
 * @todo Unit tests, Qgar code restrictions conformance. The Qgar syntatical rules are
 * @todo not followed in none of classes in files BresenhamCircle.h and BresenhamCircle.cpp
 * 
 * @warning The BresenhamCircle class has no user defined copy-constructor
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Laurent Fritz">Laurent Fritz</a>
 * @date   May 16, 2007  20:08
 * @since  Qgar 3.0
 */

// STL
#include <iterator>

// Qgar
#include <qgarlib/primitives.h>

namespace qgar
{

/**
 * @ingroup GRAPHPROC_DRAW
 *
 * @class BresenhamCircle BresenhamCircle.h "qgardevlib/BresenhamCircle.h"
 *
 * @brief Bresenham circle drawing algorithm.
 *
 * No information about code sources.
 * The original algorithm was published in Jack E. Bresenham, 
 * Algorithm for Computer Control of a Digital Plotter, 
 * IBM Systems Journal, 4(1):25-30, 1965.
 *
 * <b>Warning: This is an experimental version. NO GARANTEE about bugs, errors
 * or any problems of it's use. Please, report problems to class author.</b>
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Laurent Fritz">Laurent Fritz</a>
 * @date   May 16,  2007  20:08
 * @since  Qgar 3.0
 */

class BresenhamCircle
{
private:
  qgar::Point center, A;
  int ray;

public:

  // --------------------------------------------------------------------
  // CONSTRUCTORS
  // --------------------------------------------------------------------

  // CONSTRUCT FROM ONE GIVEN POINT AND ITS RAY
  BresenhamCircle(const qgar::Point &, int);

public:
  class const_iterator;
  class iterator;
  iterator begin() { return iterator(A,*this);}
  iterator end() { return iterator(*this);}
  const_iterator begin() const { return const_iterator(A,*this);}
  const_iterator end() const { return const_iterator(*this);}

  // ------------------------------------------------------------------------------
  // NESTED CLASSES MEMBERS IMPLEMENTATION
  // ------------------------------------------------------------------------------
public:

  class const_iterator : public std::iterator<std::input_iterator_tag,qgar::Point> 
  {
  private:
    int x,y,d;
    qgar::Point M[8];
    const BresenhamCircle &algo;
  public:
    const_iterator(const BresenhamCircle &a) 
      : algo(a),x(1),y(0),d(0),octant(0)
    {
      M[0] = algo.center;
    }
    const_iterator(const qgar::Point &M0,const BresenhamCircle &a) 
      : algo(a),x(0),y(a.ray),d(1 - a.ray),octant(0) 
    { 
      M[0] = M0;
      M[1].setXY(algo.center.x() + y,algo.center.y());
      M[3].setXY(algo.center.x(),algo.center.y() - y);
      M[6].setXY(algo.center.x() - y,algo.center.y());
    }
  public:
    int octant;
    qgar::Point operator*() const { return M[octant];}
    const qgar::Point *operator->() const { return &M[octant];}
  public:
    bool operator==(const const_iterator &it) const { return !(*this != it);}
    bool operator!=(const const_iterator &it) const
    {
      return (octant != it.octant || M[0] != it.M[0] || algo.center != it.algo.center);
    }
  public:
    const_iterator operator++(int) { const_iterator tmp = *this; ++(*this);	return tmp;}
    const_iterator &operator++() // Prefix increment operator
    { 
      if (y < x) return *this;

      static int next1[] = { 1,3,0,6,0,0,0,0 };
      static int next2[] = { 3,0,0,4,7,0,0,0 };
      static int next3[] = { 1,2,3,4,5,6,7,0 };
      octant = (x == 0 ? next1[octant] : (x == y ? next2[octant] : next3[octant]));

      if (octant == 0) 
      {
        d += (d < 0 ? 2*(++x) + 1 : 2*(++x - --y) + 1); 
        // <=> if (d < -0.25 /*and d integer*/) d += 2x + 3, ++x; 
        //     else d += 2(x - y) + 5, y--, ++x;
        //
        //     \4 | 3/            octant 0 : M0 in Oxy
        //      \ | /             octant 1 : M1 = symmetry/x=y(M0)
        //    5  \|/  2      x    octant 2 : M2 = symmetry/x=0(M1)
        // ------------------>    octant 3 : M3 = symmetry/x=0(M0)
        //    6  /|\  1           octant 4 : M4 = symmetry/y=0(M3)
        //      / | \             octant 5 : M5 = symmetry/y=0(M2)
        //     /7 | 0\            octant 6 : M6 = symmetry/y=0(M1)
        //        |               octant 7 : M7 = symmetry/y=0(M0)
        //        V y             
        if (y < x) 
        {
          M[0] = algo.center;
        }
        else
        {
          M[0].setXY(algo.center.x() + x,algo.center.y() + y);
          M[1].setXY(algo.center.x() + y,algo.center.y() + x);
          M[2].setXY(algo.center.x() + y,algo.center.y() - x);
          M[3].setXY(algo.center.x() + x,algo.center.y() - y);
          M[4].setXY(algo.center.x() - x,algo.center.y() - y);
          M[5].setXY(algo.center.x() - y,algo.center.y() - x);
          M[6].setXY(algo.center.x() - y,algo.center.y() + x);
          M[7].setXY(algo.center.x() - x,algo.center.y() + y);
        }
      }
      return *this;
    }
};
public:
  class iterator : public const_iterator 
  {
  public:
    iterator(const BresenhamCircle &a) : const_iterator(a) {}
    iterator(const qgar::Point &M0,const BresenhamCircle &a) : const_iterator(M0,a) {}
  };

}; // class BresenhamCircle

} // namespace qgar

#endif /* __BRESENHAMCIRCLE_H_INCLUDED__ */
