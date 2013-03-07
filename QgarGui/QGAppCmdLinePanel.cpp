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
 * @file  QGAppCmdLinePanel.cpp
 * @brief Implementation of class QGAppCmdLinePanel
 *
 *        See file QGAppCmdLinePanel.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   June 16, 2003  14:31
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGAppCmdLinePanel.cpp,v 1.3 2005/07/13 16:30:26 masini Exp $ */



//QGUI
#include "QGAppCmdLinePanel.h"
#include "QGApplicationEntry.h"
//QGAR
#include <qgarlib/QgarAppParamDescr.h>
// QT
#include <QFileInfo>
#include <QGroupBox>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QTextBrowser>

#include <QtDebug>

using namespace qgar;
using namespace std;



// ------------------------------------------------------------------
// C O N S T R U C T O R S
// ------------------------------------------------------------------

// Default constructor
QGAppCmdLinePanel::QGAppCmdLinePanel(const QGApplicationEntry& entry,
				     QWidget * parent)
  : QWidget(parent), _entry(entry)
{
  init();
}

// ------------------------------------------------------------------
// D E S T R U C T O R
// ------------------------------------------------------------------

QGAppCmdLinePanel::~QGAppCmdLinePanel()
{ 
  // Qt deletes all subwidgets for us
}


// ------------------------------------------------------------------
// A C C E S S
// ------------------------------------------------------------------

QString
QGAppCmdLinePanel::cmdLine() const 
{
  return _cmdLine->text();
}

// ------------------------------------------------------------------

string 
QGAppCmdLinePanel::paramValue(const string& flag) const
{
  //  return (_flagMap.find(flag)).value();
  return (*(_flagMap.find(flag))).second;
}

// ------------------------------------------------------------------
// O T H E R
// ------------------------------------------------------------------

void
QGAppCmdLinePanel::init()
{
  // --------------
  // Initialize Map
  // --------------
  vector<QgarAppParamDescr *>::const_iterator it = 
    _entry.descr().accessParamVect().begin();

//   qDebug() << "QGAppCmdLinePanel::init()";  
//   for(it = _entry.descr().accessParamVect().begin();
//       it != _entry.descr().accessParamVect().begin();
//       //      it != _entry.descr().accessParamVect().end();
//       ++it)
//     {
//       qDebug() << "_flagMap[(*it)->flag()] = ";  
//       _flagMap[(*it)->flag()] = "";
//     }
  
  // --------------
  // Create Widgets
  // --------------
  QVBoxLayout * layout = new QVBoxLayout(this);
  QGroupBox * box1 = new QGroupBox(QObject::tr("Parameters Specs"), this);
  QVBoxLayout * layoutBox1 = new QVBoxLayout(box1);

  _label = new QLabel(buildLabel(), box1);

  layout->addWidget(box1);

  // Add Spacer to keep command line at the bottom of the panel
  QSpacerItem * spacer = new QSpacerItem(10, 10, QSizePolicy::Minimum, 
					 QSizePolicy::Expanding);
  layout->addItem(spacer);

  layoutBox1->addWidget(_label);

  box1->setLayout(layoutBox1);

  // Create line edit displaying the complete command line.
  QGroupBox * box2 =  new QGroupBox(QObject::tr("Call preview"), this);
  QVBoxLayout * layoutBox2 = new QVBoxLayout(box2);

  _cmdLine = new QLineEdit(QString(_entry.applicationPath().c_str()), box2);
  _cmdLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

  layout->addWidget(box2);
  layoutBox2->addWidget(_cmdLine);
  box2->setLayout(layoutBox2);

}

// ----------------------------------------------------------------------

QString
QGAppCmdLinePanel::buildLabel()
{
  QString retval;

  retval += "<qt>";
  retval += "<table border=\"0\" cellspacing=\"0\" cellpadding=\"3\" <width=\"100%\">>";

  const QgarAppDescr& descr = _entry.descr();  
  vector<QgarAppParamDescr *>::const_iterator it;

  for(it = descr.accessParamVect().begin(); 
      it != descr.accessParamVect().end();
      ++it)
    {
      retval += buildParamLabel(*it);

      retval += "<tr><td colspan=\"2\"></td></tr>";
    }

  retval += "</table>";
  retval += "</qt>";

  return retval;
}

// ----------------------------------------------------------------------

QString
QGAppCmdLinePanel::buildParamLabel(QgarAppParamDescr * param)
{
  string retval;
  retval += "<tr>";

  retval += "<td><strong>-" + param->flag() + "</strong></td>";
  retval += "<td>" + param->name() +"</td>";

  // Info on parameter passing
  retval += "<td align=\"center\">";
  if (param->passingMode() == QgarAppParamDescr::QGE_IN) 
    retval += "input";

  else if (param->passingMode() == QgarAppParamDescr::QGE_INOUT)
    retval += "in/output";

  else 
    retval += "output";
  retval += "</td>";

  // Info on parameter format

  retval += "<td align=\"center\">";
  switch (param->format()) {
  case QgarAppParamDescr::QGE_PBM:
    retval += "PBM";
    break;
    
  case QgarAppParamDescr::QGE_PPM:
    retval += "PPM";
    break;
      
  case QgarAppParamDescr::QGE_PGM:
    retval += "PGM";
    break;

  case QgarAppParamDescr::QGE_DXF:
    retval += "DXF";
    break;
     
  case QgarAppParamDescr::QGE_SVG:
    retval += "SVG";
    break;
      
  case QgarAppParamDescr::QGE_INT:
    retval += "int";
    break;

  case QgarAppParamDescr::QGE_REAL:
    retval += "real";
    break;

  default:
    retval += "unknown";    
  }
  retval += "</td>";

  retval += "<td align=\"center\">";

  // Info on if the param required
  if (param->required())
    retval += "required";

  else 
    retval += "optional";

  retval += "</td>";
  retval += "<tr>";
  retval += "</p>";

  return QString(retval.c_str());
}

// ----------------------------------------------------------------------

void 
QGAppCmdLinePanel::setParamValue(string flag, string value)
{
  // Set param value
  _flagMap[flag] = value;

  // Update command line
  _cmdLine->setText(buildCmdLine());
}

// ----------------------------------------------------------------------

QString
QGAppCmdLinePanel::buildCmdLine()
{
  // Command line
  string retval;

  // Append application fullpath
  retval += _entry.applicationPath();

  // Append all defined parameters.
  map<string, string>::const_iterator it;
  for(it = _flagMap.begin(); it != _flagMap.end(); ++it)
    {
      if ( (*it).second != "" )
	{
	  retval += " -" + (*it).first + " " + (*it).second;
	}
    }
  
  QString ret = retval.c_str();
  return ret;
}

// ----------------------------------------------------------------------
