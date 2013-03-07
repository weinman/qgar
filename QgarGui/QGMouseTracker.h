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


#ifndef __QGMOUSETRACKER_H_INCLUDED__
#define __QGMOUSETRACKER_H_INCLUDED__


/**
 * @file     QGMouseTracker.h
 * @brief    Header file of class QGMouseTracker.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     May 12, 2004  17:11
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGMouseTracker.h,v 1.3 2005/07/13 16:30:28 masini Exp $ */



// QGUI
class QGDocViewer;
// QT
#include <QLabel>



/**
 * @class QGMouseTracker QGMouseTracker.h "QGMouseTracker.h"
 * @brief Class QGMouseTracker.
 *
 * @todo Documentation to be completed... 
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   May 12, 2004  17:11
 * @since  Qgar 2.1.1
 */
class QGMouseTracker

  : public QLabel

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
  QGMouseTracker(QWidget * parent, QGDocViewer * _viewer);
//@}


/** @name Destructor */
//        ==========
//@{
/**
 * @brief Virtual destructor.
 */
  virtual ~QGMouseTracker();
//@}

  /**
   * @brief The event filter function member
   *
   * @param watched The QObject monitored
   * @param e       The event.
   */
  virtual bool eventFilter (QObject * watched, QEvent * e);

// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// The document viewer to monitor.
  QGDocViewer * _viewer;

  /// A widget to hold viewer's viewport
  QWidget *_wd;

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
  QGMouseTracker(const QGMouseTracker& other);

/**
 * @brief Disabled assignment operator.
 */
  QGMouseTracker& operator=(const QGMouseTracker& rhs);
//@}

// -------------------------------------------------------------------
}; // class QGMouseTracker


#endif /* __QGMOUSETRACKER_H_INCLUDED__ */
