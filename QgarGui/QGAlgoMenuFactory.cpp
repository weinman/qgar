/*---------------------------------------------------------------------*
 | Graphical user interface QgarGui                                    |
 | Copyright (C) 2002  Qgar Project, LORIA                             |
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
 * @file  QGAlgoMenuFactory.cpp
 * @brief Implementation of class QGAlgoMenuFactory.
 *
 *        See file QGAlgoMenuFactory.h for the interface.
 *
 * @todo remove debug method call
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 14, 2002  09:28
 * @since  Qgar 2.1
 */



// QGUI
#include "QGAlgoMenuFactory.h"
#include "QGApplicationEntry.h"
#include "QGAppRegister.h"
#include "QGLaunchBatchCommand.h"
#include "QGMainWindow.h"
#include "QGAlgoMenu.h"

// QGAR
#include <qgarlib/QgarAppDescr.h>
#include <qgarlib/QgarAppParamDescr.h>
#include <qgarlib/stl.h>
// STD
#include <iostream>
#include <cstring>
// STL
#include <functional>
// QT
#include <QDir>
#include <QFileInfo>
#include <QStringList>
#include <QString>
#include <QVector>
#include <QAction>
#include <QApplication>

using namespace std;
using namespace qgar;
using namespace qgxml;



// -------------------------------------------------------------------
// U N N A M E D   N A M E S P A C E
// -------------------------------------------------------------------

namespace
{

  /*
   * Returns true if the parameter is an image 
   * and its passing mode is either in or inout.
   */
  bool isInputImage(const QgarAppParamDescr& param)
  {
    return ( (param.passingMode() != QgarAppParamDescr::QGE_OUT) &&
	     (param.type() == QgarAppParamDescr::QGE_IMAGE));
  }


  /*
   * Returns true if the parameter is an image 
   * and its passing mode is out.
   */
  bool isNotInputImage(QgarAppParamDescr * param)
  {
    return ( (param->type()        != QgarAppParamDescr::QGE_IMAGE) ||
	     (param->passingMode() == QgarAppParamDescr::QGE_OUT) );
  }


/**
 * @brief Checks if a file exists in a given directory.
 *
 * @param filename The name of the file to check the existence.
 * @param dir      The directory in which to search for the file.
 *
 * @return True if the file was found in the directory, false
 * otherwise.
 */
  bool findInDir(const QString& filename, const QDir& dir)
  {
    bool found = false;
    for (unsigned int i=0; (!found && (i < dir.count())); i++)
      {
      QFileInfo file(dir.canonicalPath(), dir[i]);
      found = (file.isReadable() && (file.fileName() == filename));
    }
    return found;
  }

}


/**
 * @brief functor deleting the second element of a pair
 */
struct DeleteSecondFromPair {
  template <class T, class U> 
  void operator()(pair<T, U> p) const {
    delete p.second;
  }
};

// -------------------------------------------------------------------
// S T A T I C   M E M B E R   I N I T
// -------------------------------------------------------------------

const char * const 
QGAlgoMenuFactory::QGAR_DIRNAME = ".qgar";

const char * const
QGAlgoMenuFactory::QGAR_CFG_FILENAME = "qgarguicfg.xml";


// -------------------------------------------------------------------
// I N T E R N A L     M E T H O D S 
// -------------------------------------------------------------------

QVector< pair<QAction*, QGLaunchBatchCommand*> >
QGAlgoMenuFactory::buildActions(QGMainWindow * main,
				QgarAppParamDescr::ParamFormat format) 
{
  QVector< pair<QAction*, QGLaunchBatchCommand*> > ret;

  DescrMap::iterator itm;
  // Retrieve application entries vector associated with the imageType
  itm = _descrMap.find(format);

  // If the format is known, generate the actions and commands
  // for each algorithim
  if(itm != _descrMap.end())
  {
    vector<QGApplicationEntry>::iterator it;

    // For each entry, create a command item launching the 
    // application

    for (it = (*itm).second.begin(); it != (*itm).second.end(); ++it) {
      
      // Create the action and make any initalization necessary
      QAction * act = new QAction((*it).name(), main);  

      QGLaunchBatchCommand * cmd = new QGLaunchBatchCommand(main, (*it));

      // Insert values into the vector
      ret.push_back(make_pair(act, cmd));
    }
    
  }
  return ret;
}

// -------------------------------------------------------------------

void
QGAlgoMenuFactory::insertAppDescr(const QGApplicationEntry& entry)
{
  //-- Retrieve application parameter description

  vector<QgarAppParamDescr *> paramVect = entry.descr().paramVect();

  //-- Remove all non input parameters

  paramVect.erase(remove_if(paramVect.begin(), paramVect.end(), 
			    ptr_fun(isNotInputImage)), paramVect.end());


  //-- Create a vector containing all the parameter formats

  vector<QgarAppParamDescr::ParamFormat> formats;
  insert_iterator<vector<QgarAppParamDescr::ParamFormat> > 
    ii(formats, formats.begin());

  transform(paramVect.begin(), paramVect.end(), ii, 
 	    mem_fun(&QgarAppParamDescr::format));

  //-- Keep one parameter per format in the vector

  // Sort the vector in order to be able to use unique() algo  
  sort(formats.begin(), formats.end());

  // Apply unique()
  vector<QgarAppParamDescr::ParamFormat>::iterator unique_end;
  vector<QgarAppParamDescr::ParamFormat>::iterator format_it;

  unique_end = unique(formats.begin(), formats.end());

  // For each unique param per format, register application
  for( format_it = formats.begin(); format_it != unique_end; ++format_it) {

    DescrMap::iterator it;
    vector<QGApplicationEntry> vect;
    
    // Check if a application entry vector is already associated with
    // this type
    it = _descrMap.find(*format_it);
    
    if (it == _descrMap.end()) { // first application for this type
      
      // Create a new vector, and insert it in the map with Key = Type
      vect.clear();
      DescrMap::value_type value((*format_it), vect);
      pair< DescrMap::iterator, bool > result = 
	_descrMap.insert(value);
      
      // Make it point at the new created vector (used below)
      it = result.first;
      
    } // end if -- vector created
    
    // insert entry in the vector whose Key = Type in the map
    (*it).second.push_back(entry);

  } // end for
}

// ---------------------------------------------------------------------

void
QGAlgoMenuFactory::buildDescrMap(const QGAppRegister& reg)
{
  const vector<QGApplicationEntry *>& vect = reg.entryVect();
  vector<QGApplicationEntry *>::const_iterator it;
  
  for(it = vect.begin(); it != vect.end(); ++it) {
    insertAppDescr(*(*it));
  }
}


// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGAlgoMenuFactory::QGAlgoMenuFactory() {

  // Change cursor to 'wait' while reading file information
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

  //-- Locate configuration file
  QDir qgarDir = QDir(getenv("HOME") + QString("/") + QGAR_DIRNAME);  

  // Check if a the file exists in the users home
  if (! findInDir(QGAR_CFG_FILENAME, qgarDir) ) {
    qgarDir = QDir(getenv("QGARSHARE"));
  }


  // Check if a .qgar exists in the qgar shared directory.
  else if (! findInDir(QGAR_CFG_FILENAME, qgarDir) ) {
    return; // No config file found, return without further
    // processing.
  }


  QString filename = qgarDir.canonicalPath() + "/" + QGAR_CFG_FILENAME;

  // Load application entries from config file.
  QGAppRegister reg(filename.toLatin1());
  buildDescrMap(reg);

  QApplication::restoreOverrideCursor();

}



// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------



QGAlgoMenuFactory::~QGAlgoMenuFactory() 
{ 
  // delete create menus
  for_each(_actionMap.begin(), _actionMap.end(),
 	   DeleteSecondFromPair());
}



// -------------------------------------------------------------------
// A C C E S S
// -------------------------------------------------------------------

QGAlgoMenuFactory * 
QGAlgoMenuFactory::instance()
{
  static QGAlgoMenuFactory instance;

  return &instance;
}


// -------------------------------------------------------------------
// D E B U G     M E T H O D S
// -------------------------------------------------------------------

void
QGAlgoMenuFactory::dumpAppEntryMap() {

  cout << "Applications Found: " << endl;

  DescrMap::iterator it;
  
  for(it = _descrMap.begin(); it != _descrMap.end(); ++it) {

    cout << "+ Entries for: " << (*it).first << endl;
    
    const vector<QGApplicationEntry>&  vect = (*it).second;

    for (vector<QGApplicationEntry>::const_iterator it2 = vect.begin();
	 it2 != vect.end(); ++it2) 
      {
 	cout << "    - " << (*it2).descr().name() << endl;
	
      }
  }

}



// ----------------------------------------------------------------------

