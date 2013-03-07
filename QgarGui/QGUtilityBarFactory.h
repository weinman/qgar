/*---------------------------------------------------------------------*
 | Graphical user interface QgarGui                                    |
 | Copyright (C) 2002  Qgar Project, LORIA                             |
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


#ifndef __QGUTILITYBARFACTORY_H_INCLUDED__
#define __QGUTILITYBARFACTORY_H_INCLUDED__


/**
 * @file     QGUtilityBarFactory.h
 * @brief    Header file of class QGUtilityBarFactory.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 28, 2002  16:51
 * @since    Qgar 2.1
 */


/* $Id: QGUtilityBarFactory.h,v 1.4 2005/07/13 16:30:29 masini Exp $ */



// QGUI
class QToolBar;
class QGMainWindow;



/**
 * @class QGUtilityBarFactory QGUtilityBarFactory.h "QGUtilityBarFactory.h"
 * @brief A factory creating command toolbars regrouping a set of
 * action appliable to a given image type.
 * 
 * @warning This implementation of the singleton pattern is not
 * thead-safe. It defines the instance as a local static variable of
 * the instance() method.
 *
 * @see QGVectUtilityBar
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 28, 2002  16:51
 * @since  Qgar 2.1
 */
class QGUtilityBarFactory
{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGUtilityBarFactory();
//@}


/** @name Access */
//        ======
//@{

  /**
   * @brief Access to the singleton instance
   */
  static QGUtilityBarFactory * instance();

//@}


/**
 * @brief Creates the utility toolbar for a given image type.
 *
 * @param main      A pointer to the main window.
 * @param imageType A string identifying the image format to create a
 * toolbar for.
 */
  QToolBar * createUtilityBar(QGMainWindow * main,
			      const char * imageType);


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

/** @name Constructor */
//        ===========
//@{

/**
 * @brief Default constructor
 */
  QGUtilityBarFactory();

//@}


/**
 * @brief Set the properties common to all created toolbars.
 *
 * @param toolbar The toolbar to set the properties for.
 */
  void setToolBarProperties(QToolBar* toolbar) const;



// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

/** @name Disabled */
//        ========
//@{

/**
 * @brief Disabled copy-constructor
 */
  QGUtilityBarFactory(const QGUtilityBarFactory&);

/**
 * @brief Disabled assignment operator
 */
  QGUtilityBarFactory& operator=(const QGUtilityBarFactory&);

//@}

// -------------------------------------------------------------------
}; // class QGUtilityBarFactory


#endif /* __QGUTILITYBARFACTORY_H_INCLUDED__ */
