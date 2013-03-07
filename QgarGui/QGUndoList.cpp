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
 * @file  QGUndoList.cpp
 * @brief Implementation of class QGUndoList.
 *
 * See file QGUndoList.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 4, 2002  15:48
 * @since    Qgar 2.1
 */



// QGUI
#include "QGUndoList.h"
#include "QGUndoableCommandIf.h"
#include "QGUndoObserverIf.h"
#include <qgarlib/stl.h>
// STL
#include <algorithm>
#include <functional>
#include <stdexcept>



using namespace qgar;
using namespace std;



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QGUndoList::QGUndoList(unsigned int depth)
{
  _depth = depth;
}



// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

// Default constructor
QGUndoList::~QGUndoList() 
{
  clear();
}


// -------------------------------------------------------------------
// A C C E S S 
// -------------------------------------------------------------------

bool
QGUndoList::hasUndo() const
{
  return !(_cmdVect.empty());
}

// ---------------------------------------------------------------------

bool
QGUndoList::hasRedo() const
{
  return !(_undoVect.empty());
}

// ---------------------------------------------------------------------
// T R A N S F O R M A T I O N
// ----------------------------------------------------------------------

void
QGUndoList::clear()
{
  for_each(_cmdVect.begin(), _cmdVect.end(), qstlDeleteObject());
  for_each(_undoVect.begin(), _undoVect.end(), qstlDeleteObject());
}

// ----------------------------------------------------------------------

void
QGUndoList::undo()
{
  // Perform undo.
  _cmdVect.back()->undo();

  // Remove last command from the command list and store it in 
  // the undo vector
  _undoVect.push_back(_cmdVect.back());
  _cmdVect.pop_back();

  notify();
}

// ----------------------------------------------------------------------

void
QGUndoList::redo()
{
  if (_undoVect.back() == 0)
    throw runtime_error("Null pointer");

  // Execute last undone command
  _undoVect.back()->execute();

  // Remove command from the undo vector and store it in the 
  // command vector
  _cmdVect.push_back(_undoVect.back());
  _undoVect.pop_back();

  notify();
}

// ----------------------------------------------------------------------

void
QGUndoList::registerCommand(const QGUndoableCommandIf& cmd)
{
  // Clear the redo vector.
  if (hasRedo())
    cleanUndoVect();

  // Check if the undo depth is reach. Drop oldest command
  // if it is the case.
  if (_cmdVect.size() == _depth) {
    delete _cmdVect.front();
    _cmdVect.erase(_cmdVect.begin());
  }
  
  // Store our OWN COPY of the command in the command vector
  _cmdVect.push_back(cmd.clone());

  // Clean the redo vector
  notify();
}

// ----------------------------------------------------------------------

void
QGUndoList::cleanUndoVect()
{
  for_each(_undoVect.begin(), _undoVect.end(), qstlDeleteObject());

  _undoVect.clear();

  notify();
}


// -------------------------------------------------------------------
// Q G U N D O S U B J E C T I F     I M P L 
// -------------------------------------------------------------------

void 
QGUndoList::attach(QGUndoObserverIf * obs)
{
  vector<QGUndoObserverIf*>::iterator it;

  it = std::find(_obsVect.begin(), _obsVect.end(), obs);
  
  // If not found, insert observer
  if( it == _obsVect.end()) 
     _obsVect.push_back(obs);
}

// ----------------------------------------------------------------------

void
QGUndoList::detach(QGUndoObserverIf * obs)
{
  // Remove all occurences of obs in the observer vector.
  _obsVect.erase(remove(_obsVect.begin(), _obsVect.end(), obs),
		 _obsVect.end());
}

// ----------------------------------------------------------------------

void
QGUndoList::notify()
{
  for_each(_obsVect.begin(), _obsVect.end(),
	   mem_fun(&QGUndoObserverIf::undoChanged));
}

// ----------------------------------------------------------------------


