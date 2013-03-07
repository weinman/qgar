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

/**
 * @file  BresenhamLine.h
 *
 * @brief Implementation file of class qgar::BresenhamLine.
 *
 *        See file BresenhamLine.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Laurent Fritz">Laurent Fritz</a>
 * @date   May 16, 2007  18:19
 * @since  Qgar 3.0
 */

#include <qgardevlib/BresenhamLine.h>

namespace qgar
{

  // --------------------------------------------------------------------
  // CONSTRUCTORS
  // --------------------------------------------------------------------

  // CONSTRUCT FROM TWO GIVEN POINTS
  BresenhamLine::BresenhamLine(const Point &_A, const Point &_B) 
    : A(_A),B(_B),ix(1),iy(1),incr1(xincr),incr2(yincr)
  {
    int dx = B.x() - A.x();
    int dy = B.y() - A.y();
    if (dx < 0) ix = -1,dx = -dx;
    if (dy < 0) iy = -1,dy = -dy;
    if (dx < dy)
    {
      swap(ix,iy);
      swap(dx,dy);
      swap(incr1,incr2);
    }
    horiz = 2*dy;
    diago = 2*(dy - dx);
    e0 = 2*dy - dx;
  }

} // namespace qgar
