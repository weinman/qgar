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


#ifndef __QGAPPPARAMINPUTUNKNOWN_H_INCLUDED__
#define __QGAPPPARAMINPUTUNKNOWN_H_INCLUDED__


/**
 * @file     QGAppParamInputUnknown.h
 * @brief    Header file of class QGAppParamInputUnknown
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     July 10, 2003  10:43
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGAppParamInputUnknown.h,v 1.3 2005/07/13 16:30:27 masini Exp $ */



// QGUI
#include "QGAbstractAppParamInput.h"
class QGAppDialogMediator;
// QT
class QLineEdit;



/**
 * @class QGAppParamInputUnknown QGAppParamInputUnknown.h
 * @brief Input widget for Qgar application parameter whose type is
 * not registered.
 * 
 * This class is an extension of QGAbstractAppParamInput providing a
 * textfield to input a parameter value whose type is not known by the
 * application.  Since no type is identified, no help on input nor
 * validation can be provided. The value is used as 'raw'.
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   July 10, 2003  10:43
 * @since  Qgar 2.1.1
 */
class QGAppParamInputUnknown : public QGAbstractAppParamInput
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
 * @param descr  The instance holding the description of a parameter.
 * @param med    A pointer to the dialog mediator.
 * @param parent The parent-to-be of this widget.
 */
  QGAppParamInputUnknown(qgar::QgarAppParamDescr * descr,
			 QGAppDialogMediator * med,
			 QWidget * parent,
			 QGridLayout * layout);

//@}


/** @name Destructor */
//        ==========
//@{
/**
 * @brief Virtual destructor.
 */
  virtual ~QGAppParamInputUnknown();
//@}


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


  virtual void reset();


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

  /// The line edit used to input the parameter value
  QLineEdit * _value;


// -------------------------------------------------------------------
// P R O T E C T E D    S L O T S
// -------------------------------------------------------------------
protected slots:


/**
 * @brief Notifies the dialog mediator that _value has been updated 
 *
 * This slot is connected to the textChanged() signal of the QLineEdit
 * #_value. It informs the dialog mediator that the value of the
 * filename inputted for the parameter has been modified.
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
 * @brief Disabled copy-constructor.
 * @param other another instance of the class
 */
  QGAppParamInputUnknown(const QGAppParamInputUnknown& other);

/**
 * @brief Disabled assignment operator.
 * @param rhs an instance of the class
 */
  QGAppParamInputUnknown& operator=(const QGAppParamInputUnknown& rhs);

//@}

// -------------------------------------------------------------------
}; // class QGAppParamInputUnknown


#endif /* __QGAPPPARAMINPUTUNKNOWN_H_INCLUDED__ */
