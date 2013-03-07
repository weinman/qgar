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


#ifndef __QGAPPCMDLINEPANEL_H_INCLUDED__
#define __QGAPPCMDLINEPANEL_H_INCLUDED__


/**
 * @file     QGAppCmdLinePanel.h
 * @brief    Header file of class QGAppCmdLinePanel
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     June 16, 2003  14:31
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGAppCmdLinePanel.h,v 1.3 2005/07/13 16:30:26 masini Exp $ */



// QGUI
class QGApplicationEntry;
// QGAR
namespace qgar
{
  class QgarAppParamDescr;
}
// STL
#include <map>
// QT
#include <QWidget>
#include <QMap>

class QLabel;
class QLineEdit;



/**
 * @class QGAppCmdLinePanel QGAppCmdLinePanel.h
 * @brief Widget part of a QgarApp dialog representing the command
 * line passed to the application.
 *
 * <p>
 * This widget is a part of the dialog raised when the user wishes to
 * launch a QgarApp. This dialog has two purposes:
 * - Acquire the application parameters.
 * - Provide online help on the application and its parameters.
 *
 * </p>
 * <p>
 * This widget shows to the user the command line that will be used to
 * call the external application. It also allows the user to directly
 * modify this line. Data is retrieved from the QgarAppDescr embedded
 * in the QGApplicationEntry reference passed to the constructor.
 * </p>
 * <p>
 * This widget also includes a reminder of the various flags that can
 * be passed to the application along with a brief explaination on
 * what they represent.
 * </p>
 * <p>
 * Internally this classs uses a std::map to store the value set for
 * each parameter. The parameter flag being the key to this map.
 * </p>
 * 
 * @see QGAppDialogMediator
 * @see QGAppDescrPanel
 * @see QGAppParamPanel
 *
 * @todo This class does not interact with the QGAppParamPanel. This
 * means that altering the value of the command line, will not alter
 * the parameter panel in return. This should be corrected in future releases.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   June 16, 2003  14:31
 * @since  Qgar 2.1.1
 */
class QGAppCmdLinePanel

  : public QWidget

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
 *
 * Creates the widget for the given application entry with parent
 * widget parent.
 *
 * @param entry  The application entry this widget is passed on.
 *
 * @param parent The widget that will act as parent widget for this
 * instance.
 */
  explicit QGAppCmdLinePanel(const QGApplicationEntry& entry,
			     QWidget * parent = 0);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Virtual destructor.
 */
  virtual ~QGAppCmdLinePanel();

//@}


/**
 * @brief Initializes the data structures and creates the all UI sub
 * items.
 */  
  virtual void init();


/**
 * @brief Sets the value of a parameter knowing its flag.
 *
 * This function member sets the value of the application parameter,
 * identified by its flag.
 *
 * @param flag The flag of the parameter whose value is to be modified
 * or set.
 *
 * @param value The new value for this parameter.
 */
  void setParamValue(std::string flag, std::string value);



/** @name Access */
//        ======
//@{

/**
 * @brief Retrieves the actual value of the displayed command line.
 *
 * @return the command line as a QString.
 */
  QString cmdLine() const;

/**
 * @brief Retrieve the value stored for a parameter identified by its
 * flag.
 *
 * @param flag the flag identifying the parameter.
 *
 * @return The current value of the parameter.
 */
  std::string paramValue(const std::string& flag) const;

//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

/**
 * @brief Build the label displaying the various application flag and
 * meaning.
 */
  virtual QString buildLabel();


/**
 * @brief Build the line showing for a parameter its flag and its
 * brief description.
 *
 * This method is called by buildLabel() on each parameter of the
 * application description to document each parameter.
 *
 * @param param the application parameter to be documented.
 */
  virtual QString buildParamLabel(qgar::QgarAppParamDescr * param);


/**
 * @brief Builds the command line to trigger the application.
 *
 * <p>
 * This function member gather all information needed to build the
 * command line call to the application.
 * </p>
 * <p>
 * The needed data is the full path to the exectutable and the value
 * of the various paramters. The full path is provided in  _entry and
 * the parameter values set using setParamValue() are stored in the
 * _flagMap map.
 * </p>
 */
  QString buildCmdLine();


/**
 * @brief The QGApplicationEntry this widget will retrieve its data
 * from.
 */
  const QGApplicationEntry& _entry;


/**
 * @brief A map associating for each parameter flags its value.
 *
 * This map holds the value set for each application
 * parameters. Values are set and changed using the
 * setParameterValue() function member.
 */
  std::map<std::string, std::string> _flagMap;
//  QMap<std::string, std::string> _flagMap;


/**
 * @brief The label displaying the available parameters their flag and
 * their documentation.
 */
  QLabel * _label;


/**
 * @brief QLineEdit displaying the command line and allowing direct
 * modification.
 */
  QLineEdit * _cmdLine;


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

//
/** @name Disabled */
//        ========
//@{

/**
 * @brief Copy-constructor.
 * @param other another instance of the class
 */
  QGAppCmdLinePanel(const QGAppCmdLinePanel& other);

/**
 * @brief Assignment operator.
 * @param rhs an instance of the class
 */
  QGAppCmdLinePanel& operator=(const QGAppCmdLinePanel& rhs);

//@}

// -------------------------------------------------------------------
}; // class QGAppCmdLinePanel


#endif /* __QGAPPCMDLINEPANEL_H_INCLUDED__ */
