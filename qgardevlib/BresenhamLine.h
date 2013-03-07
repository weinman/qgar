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

#ifndef __BRESENHAMLINE_H_INCLUDED__
#define __BRESENHAMLINE_H_INCLUDED__

/**
 * @file  BresenhamLine.h
 *
 * @brief Header file of class qgar::BresenhamLine.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Laurent Fritz">Laurent Fritz</a>
 * @date   May 16, 2007  20:08
 * @since  Qgar 3.0
 */

// STL
#include <iterator>

// QGAR
#include <qgarlib/primitives.h>

namespace qgar
{

/**
 * @ingroup GRAPHPROC_DRAW
 *
 * @class BresenhamLine BresenhamLine.h "qgardevlib/BresenhamLine.h"
 *
 * @brief Bresenham line drawing algorithm.
 *
 * No information about code sources.
 * The original algorithm was published in Jack E. Bresenham, 
 * Algorithm for Computer Control of a Digital Plotter, 
 * IBM Systems Journal, 4(1):25-30, 1965.
 *
 * <b>Warning: This is an experimental version. NO GARANTEE about bugs, errors
 * or any problems of it's use. Please, report problems to class author.</b>
 *
 * @todo Unit tests, Qgar code restrictions conformance. The Qgar syntatical rules are
 * @todo not followed in none of classes in files BresenhamLine.h and BresenhamLine.cpp
 * 
 * @warning The BresenhamLine class has no user defined copy-constructor
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Laurent Fritz">Laurent Fritz</a>
 * @date   May 16,  2007  20:08
 * @since  Qgar 3.0
 */

class BresenhamLine
{
private:
  static void xincr(Point &M,int ix) { M.setX(M.x() + ix);}
  static void yincr(Point &M,int iy) { M.setY(M.y() + iy);}
  void (*incr1)(Point &,int);
  void (*incr2)(Point &,int);

  Point A,B;

  int ix;
  int iy;
  int horiz;
  int diago;
  int e0;

public:
  
  // ---------------------------------------------------------------------------------
  // CONSTRUCTORS
  // ---------------------------------------------------------------------------------

  // CONSTRUCT FROM TWO GIVEN POINTS
  BresenhamLine(const Point &, const Point &);

  class const_iterator : public std::iterator<std::input_iterator_tag, qgar::Point>
  {
  public:
    // -------------------------------------------------------------------------------
    // CONSTRUCTORS
    // -------------------------------------------------------------------------------
    
    // CONSTRUCT THE CONST ITERATOR
    const_iterator(const Point &M0, const BresenhamLine &a) : M(M0),algo(a),e(a.e0) {}

  private:
    int e;
    Point M;
    const BresenhamLine& algo;
  
    // --------------------------------------------------------------------------------
    // TRANSFORMATION
    // --------------------------------------------------------------------------------
   public:
    Point operator*() const { return M;}
    const Point *operator->() const { return &M;}
    bool operator==(const const_iterator &it) const { return !(*this != it);}
    bool operator!=(const const_iterator &it) const
      { 
      return (M != it.M || algo.A != it.algo.A || algo.B != it.algo.B);
      }
    const_iterator operator++(int) { const_iterator tmp = *this; ++(*this); return tmp;}
    const_iterator &operator++() // Prefix increment operator
      { 
      if (0 < e)
        {
        algo.incr2(M,algo.iy);
        e += algo.diago;
        }
      else
        {
        e += algo.horiz;
        }
      algo.incr1(M,algo.ix);
      return *this;
      }
  }; // class BresenhamLine::const_iterator

  class iterator : public const_iterator 
  {
  public:
    iterator(const Point &_M,const BresenhamLine &_algo) : const_iterator(_M,_algo) {}

  }; // class BresenhamLine::iterator

  iterator begin() { return iterator(A, *this);}
  iterator end() { return iterator(B, *this);}
  const_iterator begin() const { return const_iterator(A, *this);}
  const_iterator end() const { return const_iterator(B, *this);}

}; // class BresenhamLine

} // namespace qgar

#endif /* __BRESENHAMLINE_H_INCLUDED__ */
