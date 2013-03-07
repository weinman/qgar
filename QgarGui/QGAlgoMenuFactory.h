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


#ifndef __QGALGOMENUFACTORY_H_INCLUDED__
#define __QGALGOMENUFACTORY_H_INCLUDED__


/**
 * @file     QGAlgoMenuFactory.h
 * @brief    Header file of class QGAlgoMenuFactory.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 14, 2002  09:28
 * @since    Qgar 2.1
 */


/* $Id: QGAlgoMenuFactory.h,v 1.9 2005/07/13 16:30:26 masini Exp $ */



// QGAR
#include <qgarlib/QgarAppParamDescr.h>
namespace qgar
{
  class QgarAppDescr;
}
// QGUI
#include "QGLaunchBatchCommand.h"
class QGAppRegister;
class QGMenu;

// STL
#include <map>
#include <vector>

// QT
#include <QVector>
#include <QMap>
#include <QAction>
class QMenu;
class QGApplicationEntry;
class QGMainWindow;



/**
 * @class QGAlgoMenuFactory QGAlgoMenuFactory.h
 * @brief Creates menus containing all the available applications
 * appliable to a given image type.
 *
 * <p>
 * This factory is implemented as a singleton. The first call to the
 * instance() method will cause the unique instance to be created.
 * </p>
 * <p>
 * On creation all directories declared in both QGARRC and QGARUSERAPP
 * environment variables are scanned, looking for valid a
 * configuration file named <code>qgarguicfg.xml</code>
 * </p>
 * <p>
 * Once this file is found, it is loaded via the creation of a
 * QGAppRegister instance (@see QGAppRegister). This configuration
 * file holds the mapping between the path to an executable that can
 * be called by the GUI and its XML description file.
 * </p>
 * <p>
 * This file being loaded, clients of this class can create menus
 * where all entries will trigger a dialog allowing to call an
 * associated application (see buildActions(QGMainWindow * main,
 * qgar::QGEparamFormat format)).
 * </p>
 *
 * @warning Current implementation version only supports ONE directory declared
 * per environment variable.
 *
 * @warning This implementation of the singleton pattern is not
 * thead-safe. It defines the instance as a local static variable of
 * the instance() method.
 *
 * @see QGMenu
 * @see QGLaunchBatchCommand
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 14, 2002  09:28
 *
 * @since Qgar 2.1
 */
class QGAlgoMenuFactory
{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:


/** @name Constants */
//        =========
//@{

  /// The name of the directory containing the qgar configuration files.
  static const char * const QGAR_DIRNAME;

  /// The name of the main qgar configuration file.
  static const char * const QGAR_CFG_FILENAME;

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGAlgoMenuFactory();
//@}


/** @name Access */
//        ======
//@{

/**
 * @brief Access to the unique instance of this class.
 *
 * @return The singleton.
 */
  static QGAlgoMenuFactory * instance() ;

//@}


/**
 * @brief Creates a vector containing pairs of QActoins and commands.
 *
 * This method returns a QVector containing a QAction* to be inserted
 * in the menu and the correpondent QGLaunchBatchCommand* to execute
 * the algorithim associated to the action.
 *
 * The command is executed after a click in the action at the menu.
 * 
 * @param main A pointer to a QGMainWindow instance that will act as
 * parent widget when the menu is created.
 *
 * @param format The QgarAppParamDescr that will define which algorithims
 * are available to this format.
 *
 * @return A QVector containing actions and their respective commands whose 
 * will launch their assigned application.
 *
 * @see QAlgoMenu
 */
  QVector< pair<QAction*, QGLaunchBatchCommand*> > buildActions
    (QGMainWindow * main, qgar::QgarAppParamDescr::ParamFormat format);

// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

/**
 * @brief Typedef for the container storing the application
 * descriptions.
 *
 * The map assigns to each image format a vector of
 * qgar::QgarAppDescr. Meaning that given an image format, we can
 * access the list of the applications in which this image can be
 * processed as an input.
 */
  typedef std::map< qgar::QgarAppParamDescr::ParamFormat,
		    std::vector<QGApplicationEntry> > DescrMap;


  /// The map of application descriptions.
  DescrMap _descrMap;

/**
 * @brief Typedef.
 */
  typedef std::map< qgar::QgarAppParamDescr::ParamFormat, 
		    QAction *> ActionMap;
  
  /// A map associating an algorithm menu to an image type
  ActionMap _actionMap;


/**
 * @brief Insert all application entries for reg into the _descrMap
 * instance.
 *
 * All application enties retrieve using the
 * QGAppRegister::entryVect() methods are inserted in the _descrMap
 * instance variable using the insertAppDescr() function member.
 *
 * @param reg The QGAppRegister instance whose application entries
 * are to be inserted.
 */
  void buildDescrMap(const QGAppRegister& reg);


/**
 * @brief inserts an application description in the _descrMap
 *
 * The application entry is inserted in each vector whose key in the
 * map is an input parameter type for the application.
 *
 * @param descr the description to insert.
 */
  void insertAppDescr(const QGApplicationEntry& descr);

/**
 * @brief Debug method dumping the application entry map.
 *
 * Dumps the list of application the parseApplication() method as
 * found on the standard output. Entries are sorted by the image type
 * they may be applied to.
 */
  void dumpAppEntryMap();

/**
 * @brief Typedef.
 */
  pair<QAction*, QGLaunchBatchCommand*> _actionCouple;

/** @name Constructors */
//        ============
//@{

/**
 * @brief Default constructor.
 *
 * <p>
 * The constructor seeks the qgarGui configuration file
 * (qgarguicfg.xml). This search is made by checking if the directory
 * set in the QGARRC environment variable contains a readable file of
 * this name.<br>
 * If this is not the case, the search will take place in the current
 * directory (".").
 * </p>
 * <p>
 * Constructor is declared protected since this class implements a
 * Singleton pattern.
 * </p>
 */
  QGAlgoMenuFactory();

//@}

  
// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

/** @name Disabled */
//        ========
//@{

/**
 * @brief Copy-constructor.
 *
 * No Copy Constructor needed for a singleton class.
 */
  QGAlgoMenuFactory(const QGAlgoMenuFactory&);

/**
 * @brief Assignment operator
 *
 * No Assignment Operatror needed for a singleton class.
 */
  QGAlgoMenuFactory& operator=(const QGAlgoMenuFactory&);

//@}

// -------------------------------------------------------------------
}; // class QGAlgoMenuFactory


#endif /* __QGALGOMENUFACTORY_H_INCLUDED__ */
