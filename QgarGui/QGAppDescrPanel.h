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


#ifndef __QGAPPDESCRPANEL_H_INCLUDED__
#define __QGAPPDESCRPANEL_H_INCLUDED__


/**
 * @file     QGAppDescrPanel.h
 * @brief    Header file of class QGAppDescrPanel
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     June 11, 2003  10:04
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGAppDescrPanel.h,v 1.2 2005/07/13 16:30:26 masini Exp $ */



// QGAR
namespace qgar
{
  class QgarAppDescr;
  // class QgarAppParamDescr;
}
#include <qgarlib/QgarAppParamDescr.h>
// QT
#include <QTextBrowser>
class QWidget;



/**
 * @class QGAppDescrPanel QGAppDescrPanel.h
 * @brief Widget part of a QgarApp dialog displaying the documentation
 * on the application in HTML format.
 *
 * <p>
 * This widget is a part of the dialog raised when the user wishes to
 * launch a QgarApp. This dialog has two purposes:
 * - Acquire the application parameters.
 * - Provide online help on the application and its parameters.
 *
 * </p>
 * <p>
 * This widget retrieves all the documentation contained in the
 * qgar::QgarAppDescr instance and build an HTML representation of it
 * that it displays, acting as a web browser.
 * </p>
 * <p>
 * Each parameter description section is introduced by a HTML anchor
 * whose name is the parameter flag. This anchor is used to scroll
 * the application description text up to a given parameter section.
 * </p>
 * <p>
 * This mechanism is used in particular by the QGAppDialogMediator to
 * provide contextual help while filling a QGAppParamPanel instance.
 * </p>
 * 
 * @see QGAppDialogMediator
 * @see QGAppParamPanel
 * @see QGAppCmdLinePanel
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   June 11, 2003  10:04
 * @since  Qgar 2.1.1
 */
class QGAppDescrPanel

  : public QTextBrowser
  
{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:


/** @name Color Chart */
//        ===========
//@{

  /**
   * @brief The background color of the documentation.
   *
   * Current value: #e2dad5 (Qgar Color Chart).
   */
  static const char * const BGCOLOR;

  /**
   * @brief The font color of the documentation top level titles.
   *
   * Current value: #03249b (Qgar Color Chart).
   */ 
  static const char * const SECTION_TITLE_COLOR;

  /**
   * @brief The font color of the documentation second level titles.
   *
   * Current value: white (Qgar Color Chart).
   */
  static const char * const SUBSECTION_TITLE_COLOR;

  /**
   * @brief The background color the second level title
   *
   * Current value: #ef995f (Qgar Color Chart).
   */
  static const char * const SUBSECTION_TITLE_BGCOLOR;

//@}


/** @name Constructors */
//        ============
//@{

/**
 * @brief Default constructor.
 *
 * Creates a description panel for a given application description.
 *
 * @param descr  The application description to document.
 * @param parent The parent widget for this widget
 * @param name   The name of this widget.
 */
  explicit QGAppDescrPanel(const qgar::QgarAppDescr& descr,
			   QWidget * parent = 0, 
			   const char * name = 0);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Virtual destructor.
 */
  virtual ~QGAppDescrPanel();

//@}


/**
 * @brief Extracts the documentation data and builds its HTML
 * representation.
 *
 * This function member collects all the documentation data contained
 * in the application description passed to the constructor. This data
 * is then translated into an HTML representation and returned as a
 * QString.
 *
 * @return A QString holding the HTML representation of the
 * documentation.
 */
  QString descrToHtml() const;


/**
 * @brief Creates the HTML description of an application parameter.
 *
 * This function member is called by descrToHtml() on each parameter
 * of the application. For each of these parameters, it builds the
 * HTML representation of its documentation.
 *
 * @param descr The description of the parameter to issue HTML
 * documentation for.
 *
 * @param anchorName The name of the HTML anchor that will prefix the
 * parameter documentation.
 *
 * @return A QString holding the HTML representation of the
 * documentation of the parameter.
 */
  QString paramToHtml(qgar::QgarAppParamDescr * descr, 
		      const std::string& anchorName) const;


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /**
   * @brief The application description whose documentation is to be
   * displayed.
   */
  const qgar::QgarAppDescr& _descr;


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
  QGAppDescrPanel(const QGAppDescrPanel& other);

/**
 * @brief Assignment operator.
 * @param rhs an instance of the class
 */
  QGAppDescrPanel& operator=(const QGAppDescrPanel& rhs);

//@}

// -------------------------------------------------------------------
}; // class QGAppDescrPanel


#endif /* __QGAPPDESCRPANEL_H_INCLUDED__ */
