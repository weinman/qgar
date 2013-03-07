/*---------------------------------------------------------------------+
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


#ifndef __QGCANVASELLIPSE_H_INCLUDED__
#define __QGCANVASELLIPSE_H_INCLUDED__


/**
 * @file   QGCanvasEllipse.h
 * @brief  Header file of class QGCanvasEllipse.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   2001
 * @since  Qgar 2.0
 */



// QT
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
// QGUI
#include "QGVectItem.h"
// QGAR
namespace qgar
{
  template <class T> class GenQgarArc;
}



#define QGAR_ARC_ACCURACY 16



/**
 * @brief An ellipse on a canvas, customized for Qgar.
 *
 * @todo implement the resize() function members.
 *
 * @warning No assignement constructor is provided nor destructor.
 * The clone() method simply calls the copy constructor that simply
 * call default QGraphicsEllipse and puts the new object in the scene.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   2001
 * @since  Qgar 2.0
 */
class QGCanvasEllipse

  : public QGraphicsEllipseItem, 
    public QGVectItem

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  static const int RTTI_ELLIPSE;
  
/** @name Constructors */
//        ============
//@{

/**
 * @brief Creates a degenerated (null) ellipse and attach it to a
 * canvas.
 *
 * This constructor is used when the user does not wish to input the
 * ellipse coordinates on creation. These coordinates can be filled in
 * later.
 *
 * @param canvas The canvas this ellipse will be attached to.
 * @param width  The thickness of this ellipse.
 */
  QGCanvasEllipse(QGraphicsScene * canvas, int width = 0);

/**
 * @brief Creates an ellipse and attach
 *
 * @param ptx        The x coordinate.
 * @param pty        The y coordinate.
 * @param width      The width of the rectangle bounding the ellipse. 
 * @param height     The height of the rectangle bounding the ellipse
 * @param startangle The angle at whicj the drawing of the ellipse
 *                   begins when only a segment of the ellipse is
 *                   drawn. 
 * @param angle      The angle at whicj the drawing of the ellipse
 *                   ends when only a segment of the ellipse is
 *                   drawn. 
 * @param canvas     The canvas this ellipse will be attached to.
 * @param widthArc   The thickness of this ellipse.
 */
   QGCanvasEllipse(int ptx, int pty, int width, int height, int startangle, 
 		  int angle, QGraphicsScene * canvas, int widthArc = 0); 

/*   QGCanvasEllipse(int width, int height, int startangle, */
/* 		  int angle, QGraphicsScene * canvas, int widthArc = 0); */


/**
 * @brief Converts a GenQgarArc into a QGCanvasEllipse.
 *
 * @param arc The GenQgarArc instance to convert.
 */
  QGCanvasEllipse(const qgar::GenQgarArc<int>& arc);

/**
 * @brief Copy constructor.
 *
 * @param obj QGCanvasEllipse object to be copied.
 */
  QGCanvasEllipse(const QGCanvasEllipse & obj);

//@}


// ------------------------  
// USING DEFAULT DESTRUCTOR
// ------------------------

/**
 * @brief Return the type of the primitive (1002).
 */
  int rtti() const {return RTTI_ELLIPSE;}



/** @name QGVectItem Implementation */
//        =========================
//@{

/** 
 * @brief Turn the line into skeleton mode.
 *
 * The thickness of the ellipse is temporary set to 1.
 */
  virtual void skelMode();


/** 
 * @brief Turn the line into normal mode.
 *
 * The real thickness of the ellipse is restored.
 */
  virtual void normalMode();

/** 
 * @brief Set the Pen of the ellipse.
 *
 * @param A pen with desired thickness.
 */
  virtual void setPen(QPen p);

  /**
   * @brief Return the width (thickness) of the ellipse.
   *
   * @return The width (thickness) of the ellipse.
   */
  virtual int width() const {return _realWidth;};

  /**
   * @brief Return the original width (thickness) of the ellipse.
   *
   * @return The original width (thickness) of the ellipse.
   */
  virtual int originalWidth() const {return _originalWidth;};

  
/**
 * @brief Sets the width (thickness) of the ellipse.
 *
 * @param width The new width of the ellipse.
 */
  virtual void setWidth(int width);
  

/**
 * @brief Resizes the ellipse by performing an homothetie of rate k
 *
 * @param kx the rate of the homothetie
 * @param ky the rate of the homothetie
 */
  virtual void resize(double kx, double ky);


/**
 * @brief Resizes the ellipse by performing an homothetie of rate k
 *
 * @param k The rate of the homothetie
 */
  virtual void resize(double k);


/** 
 * @brief Returns the enclosing rect of the QGCanvasEllipse.
 *
 * @return The bounding rectangle of the ellipse.
 */
  virtual QRect coordsSelectionRectangle();


/**
 * @brief Duplicates the object.
 *
 * @return A copy of this instance.
 */
  virtual QGVectItem * clone();

//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// The width (thickness) of the ellipse.
  int _realWidth;

  /// The original width (thickness) of the ellipse.
  int _originalWidth;

 /// Used for resize 
  QPoint _center;

 /// Used for resize 
  QRect _initialRect;

 /// Used for resize 
  bool _isResizing;

  /** Redefined method to correct the outline problem.
      Up to at least Qt 3.0.5, the ellipse's outlines are
      not drawn by Qt. It is a real problem, as it the only
      part we use within an ellipse...
  */
  void paint(QPainter & p, const QStyleOptionGraphicsItem* opt, QWidget * widget = 0);

// -------------------------------------------------------------------
}; // class QGCanvasEllipse


#endif /* __QGCANVASELLIPSE_H_INCLUDED__ */
