/*---------------------------------------------------------------------*
 | Graphical user interface QgarGui                                    |
 | Copyright (C) 2004  Qgar Project, LORIA                             |
 |                                                                     |
 | This file may be distributed under the terms of the Q Public        |
 | License as defined by Trolltech AS of Norway and appearing in the   |
 | file LICENSE.QPL included in root directory of the Qgar packaging.  |
 |                                                                     |
 | Licensees holding valid Qt Enterprise Edition or Qt Professional    |
 | Edition licenses may use this file in accordance with the Qt        |
 | Commercial License Agreement provided with the Software.            |
 |                                                                     |
 | This file is provided AS IS with NO WARRANTY OF ANY KIND,           |
 | INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS       |
 | FOR A PARTICULAR PURPOSE.                                           |
 |                                                                     |
 | See http://www.trolltech.com/pricing.html                           |
 | or email sales@trolltech.com for information about Qt Commercial    |
 | License Agreements.                                                 |
 | See http://www.trolltech.com/qpl/ for QPL licensing information.    |
 |                                                                     |
 | Contact info@trolltech.com if any conditions of this licensing are  |
 | not clear to you.                                                   |
 |                                                                     |
 | Contact Project Qgar for any information:                           |
 |   LORIA - équipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-lès-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/


#ifndef __QGINFOLAYER_H_INCLUDED__
#define __QGINFOLAYER_H_INCLUDED__


/**
 * @file     QGInfoLayer.h
 * @brief    Header file of class QGInfoLayer.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     April 30, 2004  16:42
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGInfoLayer.h,v 1.3 2005/07/13 16:30:28 masini Exp $ */




// QGAR
#include <qgarlib/QgarAppParamDescr.h>
// QGUI
#include <QGVectorialLayer.h>
// QT
#include <QPoint>
#include <QVector>


/**
 * @class QGInfoLayer QGInfoLayer.h "QGInfoLayer.h"
 * @brief Class QGInfoLayer.
 *
 * @todo Documentation to be completed... 
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   April 30, 2004  16:42
 * @since  Qgar 2.1.1
 */
class QGInfoLayer

  : public QGVectorialLayer

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:


/** @name Constructors */
//        ============
//@{

/**
 * @brief Default constructor.
 */
QGInfoLayer();

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Virtual destructor.
 */
virtual ~QGInfoLayer();

//@}

  virtual QPoint loadItems(const QString& filename, 
			   QVector<QGraphicsItem *>& vect) 
    throw(std::runtime_error)
  {
    return QPoint();
  }

  const char* type() const
  {
    return 0;
  }

  qgar::QgarAppParamDescr::ParamFormat format() const 
  {
    return qgar::QgarAppParamDescr::QGE_UNKNOWN_FORMAT;
  }

// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

//
/** @name Disabled */
//        ========
//@{

/**
 * @brief Disabled copy-constructor.
 */
QGInfoLayer(const QGInfoLayer& other);

/**
 * @brief Disabled assignment operator.
 */
QGInfoLayer& operator=(const QGInfoLayer& rhs);

//@}

// -------------------------------------------------------------------
}; // class QGInfoLayer

#endif /* __QGINFOLAYER_H_INCLUDED__ */
