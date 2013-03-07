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


#ifndef __QGAPPPARAMINPUTINT_H_INCLUDED__
#define __QGAPPPARAMINPUTINT_H_INCLUDED__


/**
 * @file     QGAppParamInputInt.h
 * @brief    Header file of class QGAppParamInputInt
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     June 10, 2003  17:18
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGAppParamInputInt.h,v 1.3 2005/07/13 16:30:27 masini Exp $ */



// QGUI
#include "QGAbstractAppParamInput.h"
class QGAppDialogMediator;
// QT
class QSpinBox;



/**
 * @class QGAppParamInputInt QGAppParamInputInt.h
 * @brief Input widget for Qgar application parameter whose value is an
 * integer.
 * 
 * <p>
 * This class is an extension of QGAbstractAppParamInput providing
 * extra widgets and features for inputting an interger value for a
 * given parameter. It provides a QSpinBox allowing the user to easily
 * input the value. It also provides some control over the provided
 * data, checking the bounds of the given value.
 * </p>
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   June 10, 2003  17:18
 * @since  Qgar 2.1.1
 */
class QGAppParamInputInt

  : public QGAbstractAppParamInput

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
 * @param descr      The instance holding the description of a
 *                   parameter. 
 * @param med        A pointer to the dialog mediator.
 * @param parent     The parent-to-be of this widget.
 */
QGAppParamInputInt(qgar::QgarAppParamDescr * descr,
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
virtual ~QGAppParamInputInt();
//@}


  // Inherithed from QGAppParamInputInt
  virtual void reset();

/** @name Access */
//        ======
//@{

/**
 * @brief Retrieve the input value for this param line
 *
 * @return the value inputted by the user for this parameter.
 */
  virtual std::string value() const;
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
  virtual void setValue(const std::string& value);
//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// A spinbox allowing the update of the parameter value.
  QSpinBox * _spinBox;



// -------------------------------------------------------------------
// P R O T E C T E D    S L O T    M E M B E R S
// -------------------------------------------------------------------
protected slots:


/**
 * @brief Notifies the dialog mediator that the parameter value has
 * been updated. 
 *
 * This slot is connected to the valueChanged() signal of the QSpinBox
 * #_spinBox. It informs the dialog mediator that the value of the
 * integer inputted for the parameter has been modified.
 */
  void valueChanged();


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
  QGAppParamInputInt(const QGAppParamInputInt& other);

/**
 * @brief Assignment operator.
 * @param rhs an instance of the class
 */
  QGAppParamInputInt& operator=(const QGAppParamInputInt& rhs);

//@}

// -------------------------------------------------------------------
}; // class QGAppParamInputInt

#endif /* __QGAPPPARAMINPUTINT_H_INCLUDED__ */
