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
 * @file  BresenhamCircle.h
 *
 * @brief Implementation file of class qgar::BresenhamCircle.
 *
 *        See file BresenhamCircle.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Laurent Fritz">Laurent Fritz</a>
 * @date   May 16, 2007  18:19
 * @since  Qgar 3.0
 */

#include <qgardevlib/BresenhamCircle.h>

namespace qgar
{

  // --------------------------------------------------------------------
  // CONSTRUCTORS
  // --------------------------------------------------------------------

  // CONSTRUCT FROM ONE GIVEN POINT AND ITS RAY
  BresenhamCircle::BresenhamCircle(const qgar::Point &_center,int _ray) 
    : center(_center),ray(_ray)
  {
    A.setXY(center.x(),center.y() + ray);
  }

} // namespace qgar
