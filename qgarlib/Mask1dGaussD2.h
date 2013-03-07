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
 |   LORIA - �quipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-l�s-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/


#ifndef __MASK1DGAUSSD2_H_INCLUDED__
#define __MASK1DGAUSSD2_H_INCLUDED__


/**
 * @file Mask1dGaussD2.h
 *
 * @brief Header file of class qgar::Mask1dGaussD2.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 03, 2001  10:27
 * @since  Qgar 1.0
 */


// For RCS/CVS use: Do not delete
/* $Id: Mask1dGaussD2.h,v 1.10 2006/03/31 09:32:17 gerald Exp $ */



// QGAR
#include <qgarlib/GenMask1d.h>



namespace qgar
{

/**
 * @ingroup DS_MASK
 *
 * @class Mask1dGaussD2 Mask1dGaussD2.h "qgarlib/Mask1dGaussD2.h"
 *
 * @brief Second derivative of a 1D Gaussian mask.
 *
 * The code implementing this class is an adaptation of code written by
 * Carsten Steger at TU Muenchen, Germany. Here is the copyright notice
 * from his code:
 *
@verbatim
 +----------------------------------------------------------------------+
 | Copyright (C) 1996 Carsten Steger                                    |
 |                                                                      |
 | This program is free software; you can redistribute it and/or modify |
 | it under the terms of the GNU General Public License as published by |
 | the Free Software Foundation; either version 2, or (at your option)  |
 | any later version.                                                   |
 |                                                                      |
 | This program is distributed in the hope that it will be useful, but  |
 | WITHOUT ANY WARRANTY; without even the implied warranty of           |
 | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    |
 | General Public License for more details.                             |
 |                                                                      |
 | You should have received a copy of the GNU General Public License    |
 | along with this program; if not, write to the Free Software          |
 | Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.            |
 +----------------------------------------------------------------------+
@endverbatim
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 03, 2001  10:27
 * @since  Qgar 1.0
 */
class Mask1dGaussD2

  : public DMask1d

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Copy constructor.
   *
   * See also qgar::Mask1dGaussD2::operator=,
   *          qgar::GenMask1d::deepCopy,
   *      and qgar::GenMask1d::shallowCopy.
   *
   * @warning Perform a <b>deep copy</b>:
   * the coefficent map of the source mask is duplicated.
   */
  Mask1dGaussD2(const Mask1dGaussD2& aMask);

  /**
   * @brief Initialize from given sigma (default <b>1.0</b>).
   *
   * @param aSigma sigma of the Gaussian
   */
  explicit Mask1dGaussD2(double aSigma = 1.0);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~Mask1dGaussD2();

  //@}


  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Assignment.
   *
   * See also qgar::Mask1dGaussD2(Mask1dGaussD2&),
   *          qgar::GenMask1d::deepCopy,
   *      and qgar::GenMask1d::shallowCopy.
   *
   * @param aMask mask to assign
   *
   * @warning Perform a <b>deep copy</b>: the coefficient map 
   * of the source mask is duplicated. Before the copy is performed, 
   * the destination mask is not supposed to have the same size
   * as the source mask.
   */
  Mask1dGaussD2& operator=(const Mask1dGaussD2& aMask);

  //@}

// -------------------------------------------------------------------
}; // class Mask1dGaussD2


} // namespace qgar 

#endif /* __MASK1DGAUSSD2_H_INCLUDED__ */
