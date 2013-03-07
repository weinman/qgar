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


#ifndef __QGINTERACTORBARFACTORY_H_INCLUDED__
#define __QGINTERACTORBARFACTORY_H_INCLUDED__


/**
 * @file    QGInteractorBarFactory.h
 * @brief   Header file of class QGInteractorBarFactory.
 *
 * @author  <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date    October 28, 2002  09:46
 * @since   Qgar 2.1
 */


/* $Id: QGInteractorBarFactory.h,v 1.6 2005/07/13 16:30:28 masini Exp $ */



// QGUI
class QGMainWindow;
// QT
class QString;
class QToolBar;



/**
 * @class QGInteractorBarFactory QGInteractorBarFactory.h "QGInteractorBarFactory.h"
 * @brief Factory that builds toolbars containing all interactors
 * related to an image type.
 *
 * <p>
 * This factory allows to customize the main window interface. It
 * creates a toolbar where each button activate an interactor
 * compatible with a given image type. Its typical use is to create
 * the appropriate tool bar when the document displayed in the main
 * window is changed.
 * </p>
 * <p>
 * This class is implemented as a Singleton. It cannot directly be
 * instanciated. Use the instance() function member to access to the
 * unique instance.
 * </p>
 *
 * @warning Current implementation of the singleton is not thread
 * safe.
 *
 * @see QGPixmapInteractorBar
 * @see QGVectInteractorBar
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 28, 2002  09:46
 * @since  Qgar 2.1
 */
class QGInteractorBarFactory 
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
  virtual ~QGInteractorBarFactory();
//@}


/** @name Access */
//        ======
//@{

/**
 * @brief Access to the singleton.
 *
 * @return the unique instance of this class.
 */
  static QGInteractorBarFactory * instance();

//@}


/**
 * @brief Creates the interactor toolbar according to the image type
 *
 * @param main A pointer to the main window. This window will become
 * the father of the created toolbar.
 *
 * @param imageType The id referencing the type of image to create the
 * toolbar for.
 */
  QToolBar * createInteractorBar(QGMainWindow * main, 
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
 *
 * This class is a Singleton. Client classes may never create
 * explicitly an instance of this class.
 */
  QGInteractorBarFactory();

//@}


/**
 * @brief Sets the toolbar properties for all created interactor
 * toolbars.
 *
 * Current properties set are:
 * - setMovingEnabled(false)
 * - setFrameShadow(QFrame::Raised)
 *
 *
 * @param toolbar The toolbar to set properties for
 *
 * @see QToolBar
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
 * @brief Disabled copy-constructor/
 */
  QGInteractorBarFactory(const QGInteractorBarFactory&);

/**
 * @brief Disabled assignment operator.
 */
  QGInteractorBarFactory& operator=(const QGInteractorBarFactory&);

//@}

// -------------------------------------------------------------------
}; // class QGInteractorBarFactory


#endif /* __QGINTERACTORBARFACTORY_H_INCLUDED__ */
