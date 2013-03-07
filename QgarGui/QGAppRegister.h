/*---------------------------------------------------------------------*
 | Graphical user interface QgarGui                                    |
 | Copyright (C) 2003  Qgar Project, LORIA                             |
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


#ifndef __QGAPPREGISTER_H_INCLUDED__
#define __QGAPPREGISTER_H_INCLUDED__


/**
 * @file     QGAppRegister.h
 * @brief    Header file of class QGAppRegister
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     June 23, 2003  11:13
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGAppRegister.h,v 1.3 2006/05/03 17:12:51 rendek Exp $ */


// SAX
#include <qgarlib/sax/DefaultHandler.h>
#include <qgarlib/sax/InputSource.h>
namespace qgxml
{
  class Attributes;
  class SAXParseException;
}
// QGUI
class QGApplicationEntry;
// STL
#include <string>
#include <vector>
// STD
#include <stdexcept>



/**
 * @class QGAppRegister QGAppRegister.h
 * @brief Manages the QgarApps registration file.
 * 
 * <p>
 * This class is a transfer class for the QgarApps registration file.
 * This file store data on all the QgarApp that can be called from the
 * application.
 * </p>
 * Instance of this class reads a registration file and make the data
 * available to the rest of the application. It also can save the
 * modification to disk.
 * </p>
 * <p>
 * This class uses the XML interface provided in QgarLib to read the
 * configuration files.
 * </p>
 * 
 * @todo implement the save() function member.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   June 23, 2003  11:13
 * @since  Qgar 2.1.1
 */
class QGAppRegister

  : public qgxml::DefaultHandler

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name TAGs */
//        ====
//@{
  static const char * const ELT_QGARGUICFG;
  static const char * const ELT_QGARAPPS;
  static const char * const ELT_ENTRY;
  static const char * const ELT_NAME;
  static const char * const ELT_DESCR_PATH;
  static const char * const ELT_APPLICATION_PATH;
//@}


/** @name Constructors */
//        ============
//@{
/**
 * @brief Default constructor.
 *
 * @param filename The fullpath to the configuration file to load.
 * 
 * @throw std::runtime_error if an error occured while loading the
 * configuration file.
 */
  QGAppRegister(const char * filename) throw (std::runtime_error);

//@}


/** @name Destructor */
//        ==========
//@{
/**
 * @brief Virtual destructor.
 */
  virtual ~QGAppRegister();
//@}


/** @name DefaultHandler Redefinitions */
//        ============================
//@{
  virtual void characters(const char * ch, 
                          const unsigned int start, 
                          const unsigned int length);

  virtual void startElement(const std::string& uri,
			    const std::string& localName,
			    const std::string& qName,
			    const qgxml::Attributes& atts);
  
  virtual void endElement(const std::string& uri,
			  const std::string& localName, 
			  const std::string& qName);

  virtual void fatalError(const qgxml::SAXParseException& exception);
  
//@}


/** @name File Related Methods */
//        ====================
//@{

/**
 * @brief Reloads a configuration file this instance has been created
 * from.
 *
 * @throw std::runtime_error if an error occured while reading the
 * file.
 */
  void load() throw (std::runtime_error);


/**
 * @brief Loads a configuration file.
 *
 * This loads data from a configuration file that can be different
 * from the one the instance has been created from. Previous data is
 * discarded and any non-saved modification is lost.
 *
 * @param filename the name of the file to load.
 *
 * @throw std::runtime_error if an error occured while reading the
 * file.
 */
  void load(const char * filename) throw (std::runtime_error);

/**
 * @brief Saves the current configuration.
 *
 * The data is saved in the file the instance has been created from.
 *
 * @throw std::runtime_error if an error occured while saving the
 * file.
 */
  void save() throw (std::runtime_error);

/**
 * @brief Saves the current configuration in a given file
 *
 * The instance is then attached to this new file. Further call to
 * load() or save() will use this new file.
 *
 * @param filename the fullpath of the file to save the data in.
 *
 * @throw std::runtime_error if an error occured while saving the
 * file.
 */
  void save(const char * filename) throw (std::runtime_error);
  
//@}
  
  
/** @name Access */
//        ======
//@{

/**
 * @brief A vector of all the application entries read from the
 * configuration file
 */
  std::vector<QGApplicationEntry *> entryVect() const;

//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

/** @name Methods used for parsing elements */
//        =================================
//@{

/**
 * @brief Function member called when then end element of ELT_ENTRY is
 * reached.
 */
  void endEntry();

/**
 * @brief Function member called when then end tag of ELT_NAME is
 * reached.
 */
  void endName();
  
/**
 * @brief Function member called when then end tag of ELT_DESCR_PATH is
 * reached.
 */
  void endDescrPath();

/**
 * @brief Function member called when then end tag of
 * ELT_APPLICATION_PATH is reached.
 */
  void endAppPath();

//@}


/** @name Data Used for Parsing */
//        =====================
//@{
  /**
   * @brief Structure used to store temporary data while parsing the
   * configuration file.
   */
  struct ParseData {
    std::string name;     ///< The name of the application being parsed
    std::string descrPath;///< The path to the application description
    std::string appPath;  ///< The path to the application binary.

    std::string buffer;   ///< A buffer to store read characters.
  } * _parseData;
//@}


  /// The name of the file this instance is linked to.
  const std::string _filename;

  /// A vector of all application entries loaded from the config file.
  std::vector<QGApplicationEntry *> _entryVect;


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

//
/** @name Disabled */
//        ========
//@{
/**
 * @brief Disabeld copy-constructor.
 */
  QGAppRegister(const QGAppRegister& other);

/**
 * @brief Disabled assignment operator.
 */
  QGAppRegister& operator=(const QGAppRegister& rhs);
//@}

// -------------------------------------------------------------------
}; // class QGAppRegister

#endif /* __QGAPPREGISTER_H_INCLUDED__ */
