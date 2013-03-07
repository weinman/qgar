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


#ifndef __QGEVENTREDIRECTOR_H_INCLUDED__
#define __QGEVENTREDIRECTOR_H_INCLUDED__


/**
 * @file     QGEventRedirector.h
 * @brief    Header file of class QGEventRedirector
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 31, 2002  15:25
 * @since    Qgar 2.1
 */


/* $Id: QGEventRedirector.h,v 1.7 2005/07/13 16:30:27 masini Exp $ */



// QT
#include <QObject>



/**
 * @class QGEventRedirector QGEventRedirector.h "QGEventRedirector.h"
 * @brief Template event filter object that redirects events to an
 * object given method.
 *
 * <p>
 * This template purpose is to overcome the fact that a QObject can
 * only define one eventFilter() method. This can be troublesome when
 * a filter object events has a different behavior over time (object
 * has different states).<br>
 * It also allows to redirects events to a class that does not inherit
 * from QObject.
 * </p>
 * <p>
 * This template creates QObject instances where the eventFilter()
 * function member simply redirects the event to a dedicated function
 * member of another QObject. The receiving object and function
 * member are defined on creation.<br>
 * The target function member must have the same signature as
 * QObject::eventFilter().
 * <pre>
 * bool (TargetClass::* filter) (QObject *, QEvent *);
 * </pre>
 *
 * To retrieve the events of a QObject in a given class simply
 * instanciate the template and use the instance as parameter in
 * QObject::installEventFilter(), QObject::removeEventFilter()
 * methods.
 * </p>
 * <p>
 * Example:<br>
 * Let <i>MonitorClass</i> the class of the object we wish to trap the events
 * from.<br>
 * Let <i>monitoredObject</i> an instance of that class.<br>
 * Let <i>TargetClass</i> the class of the object finally processing
 * the event.<br>
 * Let <i>filter</i> a function member with a signature matching the
 * one of eventFilter() to which we wish to redirect the events.<br>
 * <i>TargetClass</i> has the following definition:
@verbatim
class TargetClass
{
  public:

  bool filter(QObject *, QEvent *);
}
@endverbatim
 *
 * To redirect the monitoredObject events:
@verbatim
MonitoredClass* monitoredObject;
TargetClass* targetObject;

// Create the redirector
QEventRedirector<TargetClass>* redirector;
redirector = new QGEventRedirector<TargetClass>(targetObject, &TargetClass::filter);

// Install it as a monitoredObject event filter
monitoredObject->installEventFilter(redirector);
...
@endverbatim
 * </p>
 * 
 * @warning Specializations of this template are not meant to be
 * subclassed.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 31, 2002  15:25
 * @since  Qgar 2.1
 */
template<class T>
class QGEventRedirector

  : public QObject

{
// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  /// The type of the filter callback function.
  typedef bool (T::* Filter)( QObject *, QEvent *);

  /// The class in which the events will be redirected
  T * _target;

  /// The method in which the events will be redirected
  Filter _filter;


/** @name Disabled */
//        ========
//@{

/**
 * @brief Copy-constructor
 */
  QGEventRedirector(const QGEventRedirector&);

/**
 * @brief Assignment operator
 */
  QGEventRedirector& operator=(const QGEventRedirector&);

//@}

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name Constructors */
//        ============
//@{

/**
 * @brief Default constructor
 *
 * @param target A pointer to the object the events will be redirected
 * to.
 * @param filter The function member of <i>target</i> that will be
 * called to redirect the events.
 */
  QGEventRedirector(T * target, Filter filter) 
    : _target(target), _filter(filter)
  {
    // VOID
  }
    

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 *
 * This destructor is NOT virtual by purpose. Subclassing this class
 * is of no interest.
 */
  ~QGEventRedirector()
  {
    // VOID
  }

//@}


  bool eventFilter(QObject * obj, QEvent * evt)
  {
    return (_target->*_filter)(obj, evt);
  }

// -------------------------------------------------------------------
}; // class QGEventRedirector


#endif /* __QGEVENTREDIRECTOR_H_INCLUDED__ */
