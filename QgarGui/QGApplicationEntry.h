/*---------------------------------------------------------------------+
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


#ifndef __QGAPPLICATIONENTRY_H_INCLUDED__
#define __QGAPPLICATIONENTRY_H_INCLUDED__


/**
 * @file   QGApplicationEntry.h
 * @brief  Header file of class QGApplicationEntry.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   November 2, 2000  17:17
 * @since  Qgar 2.1.1
 */


/* $Id: QGApplicationEntry.h,v 1.6 2005/07/13 16:30:27 masini Exp $ */



// QGAR
#include <qgarlib/QgarAppDescr.h>
// STL
#include <stdexcept>
#include <string>
// QT
#include <QString>
class QGTemplateDialog;


/** 
 * @class QGApplicationEntry QGApplicationEntry.h "QGApplicationEntry.h"
 * @brief Class storing data about a QgarApp required to it from the GUI.
 *
 * <p>
 * This class represents a QgarApp declared in the QgarGUI.
 * It embeds the data needed within the application to call a Qgar
 * application.
 * </p>
 * <p>
 * The stored data is:
 * - The name of the application within the UI. This name can be
 *   different from the real application name.
 * - The absolute path to de XML description file of the application.
 * - The absolute path to the application binary.
 * - The application description stored as a qgar::QgarAppDescr
 *   instance.
 *
 * This data is retrieved from the QgarGUI configuration file (see
 * QGAppRegister for details).
 * </p>
 * <p>
 * This class only goal is to provide storage and therefore is not
 * meant to be extended. 
 * </p>
 *
 * @warning This class is not meant to be extended.
 *
 * @see qgar::QgarAppDescr
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   November 2, 2000  17:17
 * @since  Qgar 2.1.1
 */
class QGApplicationEntry
{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:


/** @name Constructors */
//        ============
//@{

/**
 * @brief Default Constructor
 *
 * Creates an application entry.
 * The application name within the application and both paths are
 * stored. A qgar::QgarAppDescr is created from the application
 * description file given using the qgar::QgarAppDescr(const string&)
 * constructor.
 *
 * @param name            The name of this application within qgarGui
 * @param descrPath       Path to the description file of this app
 * @param applicationPath Path to the executable file
 *
 * @throw std::runtime_error This exception is raised if the
 * application description file refered by descrPath cannot be
 * properly loaded.
 */
  QGApplicationEntry(std::string name,
		     std::string descrPath,
		     std::string applicationPath) 
    throw(std::runtime_error);
//@}


/****************************************************************
 * USING DEFAULT COPY CONSTRUCTOR, DESTRUCTOR AND ASSIGNMENT OP *
 ****************************************************************/


/** @name Access */
//        ======
//@{

/**
 * @brief Access to the name of this entry within QgarGUI
 *
 * @return The name of this entry
 */
  QString name() const;


/**
 * @brief Access to the full path to the application description file
 *
 * @return The full path to the application description file
 */
  std::string descrPath() const;


/**
 * @brief Access to the full path to the application
 *
 * @return The full path to the application
 */
  std::string applicationPath() const;


/**
 * @brief Access to the description object of the application
 * 
 * @return A copy of the description of the application
 */
  qgar::QgarAppDescr descr() const;


/**
 * @brief Access to the description object of the applicaition
 * 
 * @return The description of the application
 */
  const qgar::QgarAppDescr& accessDescr() const;

//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// The name of the application within QgarGui
  QString _name;

  /// The absolute path to the application description file
  std::string _descrPath;

  /// The absolute path to the application
  std::string _applicationPath;

  /// The application description object (loaded from _descrPath)
  qgar::QgarAppDescr _descr;

// -------------------------------------------------------------------
}; // class QGApplicationEntry


#endif /* __QGAPPLICATIONENTRY_H_INCLUDED__ */
