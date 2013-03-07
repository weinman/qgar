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


#ifndef __QGAPPPARAMPANEL_H_INCLUDED__
#define __QGAPPPARAMPANEL_H_INCLUDED__


/**
 * @file     QGAppParamPanel.h
 * @brief    Header file of class QGAppParamPanel
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     June 3, 2003  14:49
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGAppParamPanel.h,v 1.3 2005/07/13 16:30:27 masini Exp $ */



// QGUI
class QGAppDialogMediator;
class QGAbstractAppParamInput;
// QGAR
#include <qgarlib/QgarAppParamDescr.h>
namespace qgar
{
  class QgarAppDescr;
}
// QT
#include <QWidget>
class QVBoxLayout;
class QGroupBox;
class QGridLayout;

/**
 * @class QGAppParamPanel QGAppParamPanel.h
 * @brief Panel part of the QgarApp launching dialog displaying the
 * parameters of the application and allowing to update their value.
 * 
 * <p>
 * This widget displays all the parameters of a qgar application. Its
 * purpose is to allow a guided tuning of the application. For each
 * parameter an object extending QGAbstractAppParamInput is created
 * allowing to view and modify its value.
 * </p>
 * <p>
 * The QGAbstractAppParamInput instances are displayed in two separate
 * QGroupBoxes. The first embeds the application input parameters. The
 * latter regroups the application output parameters.
 * </p>
 * <p>
 * This class does not build the QGAbstractAppParamInput instances on
 * its own. It does it on request via the addParameter() function
 * member. Therefore it possesses no reference on the application
 * description nor on the dialog mediator. Its only role is to display
 * the attached child widgets.
 * </p>
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   June 3, 2003  14:49
 * @since  Qgar 2.1.1
 */
class QGAppParamPanel

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
 * @param parent The father of this widget.
 * @param name   The name of this widget
 * @param f      The creation flag for this widget.
 */
  QGAppParamPanel(QWidget * parent = 0, 
		  const char * name = 0, 
		  Qt::WindowFlags f = 0 );
//@}

/** @name Destructor */
//        ==========
//@{
/**
 * @brief Virtual destructor.
 */
  virtual ~QGAppParamPanel();
//@}
  

/**
 * @brief Creates the proper instance of a subclass of
 * QGAbstractAppParamInput and add it in the appropriate group box.
 *
 * @param descr a pointer on the description of the parameter to add
 * a line for.
 *
 * @param med An optional pointer to the mediator managing the dialog
 * this instance is part of.
 *
 * @return a pointer on the created widget.
 */
  QGAbstractAppParamInput * addParameter(qgar::QgarAppParamDescr * descr,
					 QGAppDialogMediator * med = 0);


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

/**
 * @brief Builds and initializes this widget.
 */
  void init();


/**
 * @brief Build a instance of a subclass of QGAbstractAppParamInput
 * according to the parameter format.
 *
 * @param descr The description of the parameter to build a line to.
 * @param med   An optional pointer to the mediator managing the
 * dialog.
 * @param parent The father of the created widget.
 *
 * @return a pointer on the created widget.
 */
  static QGAbstractAppParamInput * buildLine(qgar::QgarAppParamDescr * descr,
					     QGAppDialogMediator * med = 0,
					     QWidget * parent = 0,
					     QGridLayout * layout = 0);

  /// This widget layout
  QVBoxLayout * _layout;

  /// The groupbox describing the input parameters
  QGroupBox * _inputBox;

  /// The groupbox describing the output parameter
  QGroupBox * _outputBox;

  /// The layout associated to the output GroupBox
  QGridLayout * _outputLayout;

  /// The layout associated to the input GroupBox
  QGridLayout * _inputLayout;


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
  QGAppParamPanel(const QGAppParamPanel&);

/**
 * @brief Disabled assignment operator.
 */
  QGAppParamPanel& operator=(const QGAppParamPanel&);

//@}

// -------------------------------------------------------------------
}; // class QGAppParamPanel


#endif /* __QGAPPPARAMPANEL_H_INCLUDED__ */
