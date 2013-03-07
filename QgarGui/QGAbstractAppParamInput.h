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


#ifndef __QGABSTRACTAPPPARAMINPUT_H_INCLUDED__
#define __QGABSTRACTAPPPARAMINPUT_H_INCLUDED__


/**
 * @file     QGAbstractAppParamInput.h
 * @brief    Header file of class QGAbstractAppParamInput
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     June 3, 2003  18:07
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGAbstractAppParamInput.h,v 1.3 2005/07/13 16:30:26 masini Exp $ */


// QT
#include <QWidget>
// QGUI
class QGAppDialogMediator;
// QGAR
namespace qgar
{
  class QgarAppParamDescr;
}
// QT
class QCheckBox;
class QLabel;
class QLayout;
class QLineEdit;
class QGridLayout;
class QPushButton;
class QToolButton;



#include <QWhatsThis>



/**
 * @class QGAbstractAppParamInput QGAbstractAppParamInput.h
 * @brief An input widget used to set the value of a QgarApp parameter.
 * 
 * <p>
 * This class is the base class of the input widget contained in a
 * QGAppParamPanel. It represents the input line for a parameter
 * value. It creates a basic set of widgets common to all input
 * parameter lines and factorizes the lines features. It acts as a
 * colleague of QGAppDialogMediator in a mediator pattern.
 * </p>
 * <p>
 * Derived classes need to add their specific widgets especially
 * provide an input widget matching the parameter type (such as a
 * textfield for a filename for instance). They are also responsible
 * for managing the input value and therefore are requested to
 * implement a value()/setValue() pair.
 * </p>
 * <p>
 * The widgets created by this class are:
 * - A push button with a question mark icon triggering the contextual
 *   help on the parameter.
 * - A check box allowing to enable or disable the line if the
 *   parameter is optional (if the parameter is required, no checkbox
 *   is created).
 * - A label displaying the name of the parameter.
 *
 * </p>
 * <p>
 * The features offered by this abstraction are:
 * - Keeping a pointer on the dialog mediator. Allowing subclasses to
 *   report when their status has been changed.
 * - An enable/disable system, activating all the widgets relative to
 *   an optional parameter whether it is used or not.
 * - A contextual help system, displaying a brief help on the
 *   parameter on user request.
 * </p>
 *
 * @see QGAppDialogMediator
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   June 3, 2003  18:07
 * @since  Qgar 2.1.1
 */
class QGAbstractAppParamInput

  : public QWidget

{

  Q_OBJECT


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
 * Creates an instance given a parameter description, a pointer to a
 * mediator and an optional parent widget.
 *
 * @param descr  The instance holding the description of a parameter.
 * @param med    A pointer to the dialog mediator.
 * @param parent The parent-to-be of this widget.
 * @param layout The parent's layout.
 */
  QGAbstractAppParamInput(qgar::QgarAppParamDescr * descr,
			  QGAppDialogMediator * med,
			  QWidget * parent = 0,
			  QGridLayout * layout = 0);
//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Virtual destructor.
 */
  virtual ~QGAbstractAppParamInput();

//@}


/**
 * @brief Restore the default value for this parameter (if any).
 */
  virtual void reset() = 0;


/** @name Access */
//        ======
//@{

/**
 * @brief Access to the description of the parameter.
 *
 * @return A pointer to the parameter description.
 */
  qgar::QgarAppParamDescr * descr();

/**
 * @brief Query if this widget is enabled.
 *
 * @return true if the widget is enabled.
 */
  bool enabled() const;

/**
 * @brief Retrieve the value inputted for the parameter.
 *
 * @return the value inputted for this parameter.
 */
  virtual std::string value() const = 0;

//@}


/** @name Transformation */
//        ==============
//@{

/**
 * @brief Enables or disables this parameter line
 *
 * @param enable boolean set to 'true' if this widget is to be
 * enabled, 'false' otherwise
 */
  virtual void setEnabled(bool enable);

/**
 * @brief Sets the value of the parameter.
 *
 * @param value The new value of the parameter in string format.
 */
  virtual void setValue(const std::string& value) = 0;

//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

/**
 * @brief Builds this widget and performs all initializations.
 *
 * Creates the widget and perform the required signal/slot
 * connection.
 * By default optional parameters are not enabled on creation.
 */
  virtual void init();

  /// QWhatsThis event handler
  bool event(QEvent*);

  /// A pointer to the parameter description.
  qgar::QgarAppParamDescr * _descr;

  /// A pointer to the dialog mediator.
  QGAppDialogMediator * _mediator;

  /// A flag, true if the widgets of this line are enabled.
  bool _enabled;

  /// A checkbox activating the line if the parameter is optional.
  QCheckBox * _optionBox;
  
  /// A label whose text is the name of the parameter.
  QLabel * _nameLabel;

  /// Columns counters.
  int _colCounter;
  
  /// Rows counter.
  int _rowCounter;

/**
 * @brief A push button triggering the online help display for the
 * parameter 
 */
  QPushButton * _helpButton;

  /// Holder of parent's layout.
  QGridLayout * _layout;

// -------------------------------------------------------------------
// P R O T E C T E D   S L O T S
// -------------------------------------------------------------------
protected slots:


/**
 * @brief Slot called when checkbox is clicked.
 *
 * This toggles the enable/disable state of all widgets created by
 * this one.
 */
  void enableClicked();


/**
 * @brief Slot called when the help button is pressed
 *
 * <p>
 * This slot displays the online help associated with the
 * parameter. The help message is the brief help retrieved from the
 * parameter description using the briefDoc() function member.
 * </p>
 * <p>
 * The contextual help is shown using a QWhatsThis popup.
 * </p>
 *
 * @see qgar::QgarAppParamDescr::briefDoc()
 * @see QWhatsThis
 */
  void helpClicked();

#if 0
// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  QWhatsThis _what;

  // -------------------
  // PRIVATE INNER CLASS 
  // -------------------
  /**
   * @brief Extension of QWhatsThis used to display online help on an
   * application parameter.
   *
   * <p>
   * This class extends QWhatsThis to take benefit on its popup
   * displaying system to provide a contextual help on a parameter.
   * </p>
   * <p>
   * When the online help on a parameter is requested, a popup will
   * open and display a brief HTML help text on it. Clicking on
   * hyperlinks in this text can trigger further help (see clicked()
   * function member).
   * </p>
   *
   * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a> 
   * @date June 3, 2003 18:07 
   * @since Qgar 2.1.1
   */
  class HelpWhatsThis : public QWhatsThis {
  public:

    /**
     * @brief Default constructor
     *
     * @param parent The parent of this WhatsThis
     * @param med    A pointer to the mediator of the dialog.
     */
    HelpWhatsThis(QWidget * parent, QGAppDialogMediator * med);
    
    /**
     * @brief Notify the mediator that an hyperlink of the online help
     * text has been clicked.
     *
     * This overloaded method allows the user to request a more
     * extended help on the parameter. Clicking on an hyperlink in
     * the help message will notify the mediator that further help has
     * been requested. The target of the hyperlink is passed to the
     * mediator that will update the dialog accordingly.
     *
     * @see QGAppDialogMediator::jumpToAnchor()
     */
    bool clicked(const QString& href);

  private:
    /// A pointer to the dialog mediator.
    QGAppDialogMediator * _med;

  };// end of inner class MyWhatsThis
  // -------------------

#endif

/** @name Disabled */
//        ========
//@{

/**
 * @brief Disabled copy-constructor.
 */
  QGAbstractAppParamInput(const QGAbstractAppParamInput& other);

/**
 * @brief Disabled assignment operator.
 */
  QGAbstractAppParamInput& operator=(const QGAbstractAppParamInput& rhs);

//@}


// -------------------------------------------------------------------
}; // class QGAbstractAppParamInput

#endif /* __QGABSTRACTAPPPARAMINPUT_H_INCLUDED__ */
