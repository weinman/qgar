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


/**
 * @file  QGAppDescrPanel.cpp
 * @brief Implementation of class QGAppDescrPanel
 *
 *        See file QGAppDescrPanel.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   June 11, 2003  10:04
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGAppDescrPanel.cpp,v 1.4 2005/07/13 16:30:26 masini Exp $ */



// QT
#include "QGAppDescrPanel.h"
// QGAR
#include <qgarlib/QgarAppDescr.h>
#include <qgarlib/QgarAppParamDescr.h>
#include <qgarlib/stl.h>
// STL
#include <iostream>



using namespace std;
using namespace qgar;



// ------------------------------------------------------------------
// U N N A M E D   N A M E S P A C E 
// ------------------------------------------------------------------
namespace
{

  /* 
   * Creates a HTML string for level 2 headers 
   *  
   * The title is inserted between a H2 tag and its color is changed. 
   */
  string h2(const string& title)
  {    
    string retval;

    retval += "<font color=\"#03249b\">";
    retval += "<h2>" + title + "</h2>";
    retval += "</font>";
    
    return retval;
  }


  /* Creates a HTML string for level 3 headers 
   *
   * The title color is set to white and a background-color is set to
   * #EF995F (Qgar color chart).
   */
  string h3(const string& title, 
	    string color = "white",
	    string bgcolor = "#ef995f") 
  {

    string retval;

    // Create title string
    retval += "<table bgcolor=\"" + bgcolor + "\" width=\"100%\">";
    retval += "<tr><td><font color=\"" + color + "\"><b>";
    retval += title;
    retval += "</b></font></td></tr></table>";

    return retval;
  }

} // unnamed namespace


// ------------------------------------------------------------------
// S T A T I C   M E M B E R   I N I T
// ------------------------------------------------------------------

// WARNING: REMEBER TO CHANGE DOCUMENTATION IN HEADER IF YOU ALTER
// THESE VALUES

const char * const QGAppDescrPanel::BGCOLOR                  = "#e2dad5";
const char * const QGAppDescrPanel::SECTION_TITLE_COLOR      = "#03249b";
const char * const QGAppDescrPanel::SUBSECTION_TITLE_COLOR   = "white";
const char * const QGAppDescrPanel::SUBSECTION_TITLE_BGCOLOR = "#ef995f";


// ------------------------------------------------------------------
// C O N S T R U C T O R S
// ------------------------------------------------------------------

// Default constructor
QGAppDescrPanel::QGAppDescrPanel(const QgarAppDescr& descr, 
				 QWidget * parent, 
				 const char * name)
  : QTextBrowser(parent), _descr(descr)
{
  // Set Object name (the former constructor in version 3.3 allowed this)
  setObjectName(name);
  
  // Create documentation for the application and display it.
  setText(descrToHtml());
}


// ------------------------------------------------------------------
// D E S T R U C T O R
// ------------------------------------------------------------------

QGAppDescrPanel::~QGAppDescrPanel()
{
  /* EMPTY */
}


// ------------------------------------------------------------------
// P U B L I C A T I O N   M E T H O D S 
// ------------------------------------------------------------------

QString
QGAppDescrPanel::descrToHtml() const
{
  QString retval;

  //-- Write application description.

  retval += "<qt bgcolor=\"" + QString(BGCOLOR) + "\">"; 
  retval += h2(_descr.name()).c_str();


  // Table with name and copyright
  retval += "<strong>Author: </strong>";
  retval += _descr.author().c_str();
  retval += "<br>";

  retval += "&copy; ";
  retval += _descr.copyright().c_str();
  retval += "<br><br>";

  // Application Documentation
  retval += _descr.briefDoc().c_str();
  retval += "<p>";
  retval += _descr.longDoc().c_str();
  retval += "</p>";


  //-- Write parameter description

  // Title of this section
  retval += h2("Parameters Description").c_str();

  
  // For each parameter create parameter description document
  vector<QgarAppParamDescr *>::const_iterator it;

  int i;
  for(it = _descr.accessParamVect().begin(), i = 0; 
      it != _descr.accessParamVect().end();
      ++it, ++i) {

    string id = (*it)->flag();
    retval += paramToHtml(*it, id);
    retval += "<p></p>";
  }
  

  retval += "</qt>";

  return retval;
}

// ----------------------------------------------------------------------

QString 
QGAppDescrPanel::paramToHtml(QgarAppParamDescr * param, 
			     const string& id) const
{
  string retval;

  //-- Create title and anchor for this parameter.

  retval += "<a name=\"" + id + "\">" + h3(param->name()) + "</a>";


  //-- Create summary table of the parameter data

  retval += "<table cellspacing=\"0\">";

  // Flag
  retval +="<tr><td><table>";
  retval += "<tr>";
  retval += "<td><strong>Flag</strong></td>";
  retval += "<td>-" + param->flag() + "</td>";

  // Required ?
  retval += "<td><strong>Required</strong></td>";
  
  if (param->required())
    retval += "<td>yes</td>";
  else
    retval += "<td>no</td>";

  // Parameter Passing
  retval += "<td><strong>Passing Mode</strong></td>";
  
  if (param->passingMode() == QgarAppParamDescr::QGE_IN)
    retval += "<td>in</td>";

  else if (param->passingMode() == QgarAppParamDescr::QGE_INOUT)
    retval += "<td>inout</td>";
  
  else
    retval += "<td>out</td>";

  retval += "</tr>";
  retval += "<tr>";


  // Parameter type
  retval += "<td><strong>Type: </strong></td>";
  if (param->type() == QgarAppParamDescr::QGE_NUM)
    retval += "<td>numeric</td>";
  else
    retval += "<td>image</td>";


  // Parameter format
  retval += "<td><strong>Format: </strong></td>";
  if (param->format() == QgarAppParamDescr::QGE_PBM)
    retval += "<td>PBM</td>";

  else if (param->format() == QgarAppParamDescr::QGE_PPM)
    retval += "<td>PPM</td>";

  else if (param->format() == QgarAppParamDescr::QGE_PPM)
    retval += "<td>PPM</td>";

  else if (param->format() == QgarAppParamDescr::QGE_PGM)
    retval += "<td>PGM</td>";

  else if (param->format() == QgarAppParamDescr::QGE_DXF)
    retval += "<td>DXF</td>";

  else if (param->format() == QgarAppParamDescr::QGE_SVG)
    retval += "<td>SVG</td>";

  else if (param->format() == QgarAppParamDescr::QGE_INT)
    retval += "<td>integer</td>";

  else
    retval += "<td>real</td>";

  retval += "</tr>";


  retval += "</table></td></tr>";

  retval +="<tr><td>";


  //--  Parameter documentation.   

  // Brief documentation
  retval += "<p>";
  retval += param->briefDoc();
  retval += "</p>";

  // Verbose documentation.
  retval += "<p>";
  retval += param->longDoc();
  retval += "</p>";

  retval +="</td></tr>";
  retval += "</table>";  
   
  return QString(retval.c_str());
}

// ----------------------------------------------------------------------


