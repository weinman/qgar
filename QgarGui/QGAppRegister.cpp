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
 * @file  QGAppRegister.cpp
 * @brief Implementation of class QGAppRegister
 *
 *        See file QGAppRegister.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   June 23, 2003  11:13
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QGAppRegister.cpp,v 1.8 2006/05/19 13:11:08 rendek Exp $ */



// QGUI
#include "QGAppRegister.h"
#include "QGApplicationEntry.h"
// QGAR
#include <qgarlib/stl.h>
// SAX
#include <qgarlib/sax/Attributes.h>
#include <qgarlib/sax/SAXParseException.h>
#include <qgarlib/sax/XMLReader.h>
#include <qgarlib/sax/XMLReaderFactory.h>
// STD
#include <fstream>
#include <sstream>

#include <QtDebug>

using namespace std;
using namespace qgar;
using namespace qgxml;



namespace 
{
  bool inElt = false;
}

// ------------------------------------------------------------------
// C O N S T R U C T O R S
// ------------------------------------------------------------------

const char * const QGAppRegister::ELT_QGARGUICFG       = "qgarguicfg";
const char * const QGAppRegister::ELT_QGARAPPS         = "qgarapps";
const char * const QGAppRegister::ELT_ENTRY            = "entry";
const char * const QGAppRegister::ELT_NAME             = "name";
const char * const QGAppRegister::ELT_DESCR_PATH       = "descr-path";
const char * const QGAppRegister::ELT_APPLICATION_PATH = "application-path";


// ------------------------------------------------------------------
// C O N S T R U C T O R S
// ------------------------------------------------------------------

// Default constructor
QGAppRegister::QGAppRegister(const char * filename)
  throw (runtime_error)
  : _parseData(0), _filename(filename)
{
  load(filename);
}


// ------------------------------------------------------------------
// D E S T R U C T O R
// ------------------------------------------------------------------

QGAppRegister::~QGAppRegister()
{
  delete _parseData;

  for_each(_entryVect.begin(), _entryVect.end(), qstlDeleteObject());
}


// ------------------------------------------------------------------
// A C C E S S
// ------------------------------------------------------------------

vector<QGApplicationEntry *> 
QGAppRegister::entryVect() const
{
  return _entryVect;
}

// ---------------------------------------------------------------------
// D E F A U L T   H A N D L E R   R E D E F I N I T I O N S
// ----------------------------------------------------------------------

void 
QGAppRegister::characters(const char * ch, 
			  const unsigned int start, 
			  const unsigned int length)
{
  // Remove carriage returns, tabs, and line feeds 
  string result;

  

  while (*ch != '\0') {
    if (! ( (*ch == '\n')
	    || (*ch == '\r')
	    || (*ch == '\t')
	    || ( (!inElt) && (*ch == ' ') ))
 	)
      result += *ch++;
	
    else	  
      ch++;
  }

  // Append parsed data to the buffer
  _parseData->buffer += result;
}

// ----------------------------------------------------------------------

void
QGAppRegister::startElement(const string& uri,
			    const string& localName,
			    const string& qName,
			    const Attributes& atts)
{
  _parseData->buffer = "";
  if (localName == ELT_NAME)
    inElt = true;
}
  
// ----------------------------------------------------------------------

void
QGAppRegister::endElement(const string& uri,
			  const string& localName, 
			  const string& qName)
{
  //-- Redirect action on the function matching the tag.
  if (localName == ELT_ENTRY) {
    endEntry();
  }
  else if (localName == ELT_NAME) {
    endName();
  }
  else if (localName == ELT_DESCR_PATH) {
    endDescrPath();
  }
  else if (localName == ELT_APPLICATION_PATH) {
    endAppPath();
  }
  else { /* EMPTY */ } 
  
  inElt = false;
}

// ----------------------------------------------------------------------

void
QGAppRegister::fatalError(const SAXParseException& exception)
{
}


// ---------------------------------------------------------------------
// F I L E   R E L A T E D   M E T H O D S
// ----------------------------------------------------------------------

void
QGAppRegister::load() throw (runtime_error)
{
  load(_filename.c_str());
}

// ----------------------------------------------------------------------

void
QGAppRegister::load(const char * filename) throw (runtime_error)
{
  //-- Perform previous data cleanup

  delete _parseData;
  for_each(_entryVect.begin(), _entryVect.end(), qstlDeleteObject());

  //-- Parse File

  _parseData = new ParseData();

  // Open input source.
  ifstream stream(filename);  
  InputSource source(stream);

  // Parse input source.
  XMLReader * parser = XMLReaderFactory::createXMLReader();
  parser->setContentHandler(this);
  parser->parse(source);

  // Clean-up.
  delete _parseData;
  _parseData = 0;
  delete parser;  
}

// ----------------------------------------------------------------------

void
QGAppRegister::save() throw (runtime_error)
{
  save(_filename.c_str());
}

// ----------------------------------------------------------------------

void
QGAppRegister::save(const char * filename) throw (runtime_error)
{
}


// -------------------------------------------------------------------
// P A R S I N G   M E T H O D S
// -------------------------------------------------------------------

void
QGAppRegister::endEntry()
{
  QGApplicationEntry * entry = 
    new QGApplicationEntry(_parseData->name,
			   _parseData->descrPath,
			   _parseData->appPath);

  _entryVect.push_back(entry);
}

// -------------------------------------------------------------------

void
QGAppRegister::endName()
{
  _parseData->name = _parseData->buffer;
}

// -------------------------------------------------------------------

void
QGAppRegister::endDescrPath()
{
  _parseData->descrPath = _parseData->buffer;
}

// -------------------------------------------------------------------

void 
QGAppRegister::endAppPath()
{
  _parseData->appPath = _parseData->buffer;
}

// -------------------------------------------------------------------
