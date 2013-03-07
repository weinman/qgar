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
 * @file  QGAppDialogMediator.cpp
 * @brief Implementation of class QGAppDialogMediator.
 *
 *        See file QGAppDialogMediator.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   June 13, 2003  15:08
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGAppDialogMediator.cpp,v 1.6 2005/07/13 16:30:26 masini Exp $ */


// QGUI
#include "QGAppDialogMediator.h"
#include "QGAppCmdLinePanel.h"
#include "QGAppDescrPanel.h"
#include "QGApplicationEntry.h"
#include "QGAbstractAppParamInput.h"
#include "QGAppParamPanel.h"
#include "QGLayerIf.h"
#include "QGMainWindow.h"
#include "QGMultiLayerDoc.h"
// QGAR
#include <qgarlib/QgarAppParamDescr.h>
// QT
#include <QDialog>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QTabWidget>
#include <QWhatsThis>

#include <QtDebug>

using namespace std;
using namespace qgar;


// ------------------------------------------------------------------
// U N N A M E D   N A M E S P A C E
// ------------------------------------------------------------------
namespace {
  bool isOutputFile(QgarAppParamDescr * descr)
  {
    return ( (descr->type() == QgarAppParamDescr::QGE_IMAGE)
	     && (descr->passingMode() != QgarAppParamDescr::QGE_IN) );
  }
}



// ------------------------------------------------------------------
// C O N S T R U C T O R S
// ------------------------------------------------------------------

// Default constructor
QGAppDialogMediator::QGAppDialogMediator(const QGApplicationEntry& entry,
					 QGMainWindow * main)
  : _entry(entry), _inputFileLine(0)
{
  _main = main;
  createWidgets(main); // Widget are created here and not in
                       // showDialog() to avoid client using access
		       // method such cmdLine() on uncreated objects.
}


// ------------------------------------------------------------------
// D E S T R U C T O R
// ------------------------------------------------------------------

QGAppDialogMediator::~QGAppDialogMediator()
{
  //  delete _dialog; // Since _dialog is the ancestor of all allocated
		  // objects, Qt will delete them for us.
}


// -------------------------------------------------------------------
// A C C E S S
// -------------------------------------------------------------------

QString
QGAppDialogMediator::defaultFileStem() const
{
  return _defaultFileStem;
}

// -------------------------------------------------------------------

QVector<QString>
QGAppDialogMediator::resultFiles() const
{
  return _resultFiles;
}


// -------------------------------------------------------------------
//
// -------------------------------------------------------------------

void
QGAppDialogMediator::createWidgets(QGMainWindow * main)
{
  // Create Dialog
  _dialog = new QDialog(main);
  _dialog->setModal(true);


  _layout = new QVBoxLayout(_dialog);
  _layout->setSpacing(5);

  // Create Title widget
  QString appName = "<h1>" + QString(_entry.descr().name().c_str()) + "</h1>";
  QLabel * titleLabel = new QLabel(appName, _dialog);

  // Create Bottom Buttons  
  QWidget * buttonBar = createButtonBar();

  // Create TabWidget
  _tabWidget = new QTabWidget(_dialog);

  // Create command line panel  
  _cmdLinePanel = new QGAppCmdLinePanel(_entry, _tabWidget);
  initCmdLinePanel();  

  // Create parameter panel.
  _paramPanel = new QGAppParamPanel(_tabWidget);
  createParamLines(main);

  // Create application description panel
  _descrPanel = new QGAppDescrPanel(_entry.descr(), _tabWidget);
  
  // Add Panels to Tab Widget
  _tabWidget->addTab(_paramPanel, QObject::tr("Call Parameters"));
  _tabWidget->addTab(_cmdLinePanel, QObject::tr("Command Line"));
  _tabWidget->addTab(_descrPanel, QObject::tr("Description"));


  // Add Widgets to dialog layout
  _layout->addWidget(titleLabel);
  _layout->addWidget(_tabWidget);
  _layout->addWidget(buttonBar);

}

// -------------------------------------------------------------------

QWidget *
QGAppDialogMediator::createButtonBar()
{
  // Create widget and layout
  QWidget * buttonBar = new QWidget(_dialog);
  buttonBar->setGeometry( QRect(20, 20, 280, 40));
  QHBoxLayout * buttonLayout = new QHBoxLayout(buttonBar);


  // Create Buttons
  _helpButton   = new QPushButton(buttonBar);  
  _okButton     = new QPushButton(buttonBar);
  _cancelButton = new QPushButton(buttonBar);

  _helpButton->setText(QObject::tr("&Help"));
  _okButton->setText(QObject::tr("&Launch"));
  _cancelButton->setText(QObject::tr("&Cancel"));

  // Set buttons options
  _helpButton->setAutoDefault(true);

  _okButton->setDefault(true);
  _okButton->setAutoDefault(true);

  _cancelButton->setAutoDefault(true);


  // Add items to the button widget layout:
  // [ [Help] {spacer} [Ok] [Cancel] ]
  QSpacerItem * spacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, 
					 QSizePolicy::Minimum);
  buttonLayout->addWidget(_helpButton);
  buttonLayout->addItem(spacer);
  buttonLayout->addWidget(_okButton);
  buttonLayout->addWidget(_cancelButton);

  // Connect buttons to dialog slots
  QObject::connect(_okButton, 
		   SIGNAL(clicked()), 
		   _dialog,
		   SLOT(accept()));

  QObject::connect(_cancelButton, 
		   SIGNAL(clicked()), 
		   _dialog,
		   SLOT(reject()));

  return buttonBar;
}

// ----------------------------------------------------------------------

void
QGAppDialogMediator::createParamLines(QGMainWindow * main)
{
  vector<QgarAppParamDescr *> vect = _entry.descr().paramVect();
  vector<QgarAppParamDescr *>::iterator it;

  for (it = vect.begin(); it != vect.end(); ++it) {

    QGAbstractAppParamInput * line = _paramPanel->addParameter(*it, this);
    
    // Store a pointer to the created line.
    _paramLines.push_back(line);
    
    // Check if parameter is the lead input parameter.

    if ( ((*it)->passingMode() != QgarAppParamDescr::QGE_OUT )
	 && ( (*it)->format() ==
	      main->getCurrentDoc()->activeLayer()->format())) {
      
      _inputFileLine = line;
      _defaultFileStem = QString(main->getCurrentDoc()->fileName());
      
      // Strip file extension
      int pos = _defaultFileStem.lastIndexOf('.');
      if (pos != -1)
	_defaultFileStem = _defaultFileStem.left(pos);
      
      line->setValue(main->getCurrentDoc()->fileName().toStdString());
    }
  }
}

// ----------------------------------------------------------------------

void
QGAppDialogMediator::initCmdLinePanel()
{
  vector<QgarAppParamDescr *> vect = _entry.descr().paramVect();
  vector<QgarAppParamDescr *>::iterator it;
  
  for (it = vect.begin(); it != vect.end(); ++it) {
    if ( (*it)->required() )
      _cmdLinePanel->setParamValue((*it)->flag(), (*it)->defaultValue());
  }
}

// ----------------------------------------------------------------------


bool
QGAppDialogMediator::showDialog()
{
  bool ok = _dialog->exec();

  // Retrieve the list of ouput image file.
  _resultFiles.clear();
  if (ok) {
    
    vector<QgarAppParamDescr *>::const_iterator it;
    vector<QgarAppParamDescr *> vect = _entry.descr().paramVect();

    for (it = vect.begin(); it != vect.end(); ++it) {
      
      if (isOutputFile(*it)) {
	_resultFiles.push_back( (_cmdLinePanel->paramValue((*it)->flag())).c_str() );
      }
    }

    // Remove empty strings
    _resultFiles.erase(remove(_resultFiles.begin(),
			      _resultFiles.end(),
			      ""), _resultFiles.end());
				 
  }    

  return ok;
}

// ----------------------------------------------------------------------

void
QGAppDialogMediator::reset()
{
  std::vector<QGAbstractAppParamInput *>::iterator it;

  QString nome = _main->getCurrentDoc()->fileName();
  _inputFileLine->setValue("/users/qgar/vasconv/studies/QgarGui");
  _inputFileLine->setValue(nome.toStdString());
  
  _defaultFileStem = QString(nome);      
  // Strip file extension
  int pos = _defaultFileStem.lastIndexOf('.');
  if (pos != -1)
    _defaultFileStem = _defaultFileStem.left(pos);
  
  
  for ( it = _paramLines.begin(); it != _paramLines.end(); ++it )
    {
      QgarAppParamDescr * descr = (*it)->descr();      
      if ( *it != _inputFileLine ) 
	if (descr->type() != QgarAppParamDescr::QGE_NUM) {
	  (*it)->reset();
	}
    }
}

// ----------------------------------------------------------------------

void
QGAppDialogMediator::widgetChanged(QGAbstractAppParamInput * widget)
{
  if (widget->enabled())
    _cmdLinePanel->setParamValue(widget->descr()->flag(), 
    				 widget->value());
  
    else 
      _cmdLinePanel->setParamValue(widget->descr()->flag(), "");
}

// ----------------------------------------------------------------------

void
QGAppDialogMediator::jumpToAnchor(const QString& anchor)
{
  _tabWidget->setCurrentIndex(2); // 2 is the application description tab
  _descrPanel->scrollToAnchor(anchor);
}

// ----------------------------------------------------------------------

QString
QGAppDialogMediator::cmdLine()
{
  return _cmdLinePanel->cmdLine();
}

// ----------------------------------------------------------------------

