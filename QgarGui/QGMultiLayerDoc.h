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


#ifndef __QGMULTILAYERDOC_H_INCLUDED__
#define __QGMULTILAYERDOC_H_INCLUDED__


/**
 * @file     QGMultiLayerDoc.h
 * @brief    Header file of class QGMultiLayerDoc
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 17, 2002  16:04
 * @since    Qgar 2.1
 */


/* $Id: QGMultiLayerDoc.h,v 1.9 2005/07/13 16:30:28 masini Exp $ */



// QGUI
class QGInfoLayer;
class QGLayerIf;
class QGUndoList;
class QGUndoableCommandIf;
class QGDocViewer;

// QT
#include <QVector>
#include <QPixmap>
#include <QString>
#include <QGraphicsScene>
class QPainter;
class QGraphicsItem;



/**
 * @class QGMultiLayerDoc QGMultiLayerDoc.h "QGMultiLayerDoc.h"
 * @brief A document composed of one or more layers.
 *
 * This class is the base class of all documents viewed in the
 * application. It has three purposes:
 * - Manage a set of image layers: visibles layers, depths of the
 *   layers, active layer.
 * - Draw the document in a QPainter or a Pixmap.
 * - Manage the undo list of all reversible action performed on the
 *   document.
 * .
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   October 17, 2002  16:04
 * @since  Qgar 2.1
 */
class QGMultiLayerDoc
{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name Constructor */
//        ===========
//@{

/**
 * @brief Default constructor
 *
 * Creates an empty document.
 */
  QGMultiLayerDoc();

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~QGMultiLayerDoc();
//@}



/** @name Access */
//        ======
//@{
/**
 * @brief Retrieves the width of the document.
 *
 * @return The width of the document.
 */
  QGInfoLayer * infoLayer() const;

/**
 * @brief Retrieves the width of the document.
 *
 * @return The width of the document.
 */
  int layerNumber() const;

/**
 * @brief Retrieves the width of the document.
 *
 * @return The width of the document.
 */
  int width() const;


/**
 * @brief Retrieves the height of the document.
 *
 * @return The height of the document.
 */
  int height() const;


/**
 * @brief Checks if the document has been modified.
 *
 * @return True if the document has been modified.
 */
  bool modified() const;


/**
 * @brief Retrieves the current zoom factor with which the document is
 * viewed.
 *
 * @return The current zoom factor.
 */
  float zoom() const;


/**
 * @brief Retrieves the name of the file this document is currently
 * attached to.
 *
 * @return The name of the file the document is attached to.
 */
  QString fileName() const;


/**
 * @brief Retrieves the name of the document.
 *
 * @return The name of the document.
 */
  QString name() const;


/**
 * @brief Retrieves a handle on the document undo list.
 *
 * @return The document undo list.
 */
  QGUndoList * undoList() const;


/**
 * @brief Retrieves the active layer of this document.
 *
 * For now only the bottom layer of the document can be the active
 * layer.
 *
 * @return The document active layer.
 */
  QGLayerIf * activeLayer() const;

/**
 * @brief Sets the superimpose mode.
 *
 * @param status True to turn on, false to turn off.
 */
  inline bool isSuperimposeMode() {return _superimposeMode;}

//@}



/** @name Mutators */
//        ========
//@{

/**
 * @brief Sets the superimpose mode.
 *
 * @param status True to turn on, false to turn off.
 */
  inline void setSuperimposeMode(bool status) {_superimposeMode = status;}

/**
 * @brief Sets the width of the document.
 *
 * @param width The new width.
 */
  void setWidth(int width);


/**
 * @brief Sets the height of the document.
 *
 * @param height The height to be set.
 */
  void setHeight(int height);


/**
 * @brief Changes the modified flag of the document.
 *
 * @param mod The new modify flag state.
 */
  void setModified(bool mod);


/**
 * @brief Sets the zoom level at which this document is to be view.
 *
 * @param zoom The new zoom level.
 */
  void setZoom(float zoom);


/**
 * @brief Sets the name of the file this document is attached to.
 *
 * @param fileName The new name of the file.
 */
  void setFileName(const QString& fileName);


/**
 * @brief Sets the name of the document.
 *
 * @param docName The new document name.
 */
  void setName(const QString& docName);

//@}



/** @name Undo Management */
//        ===============
//@{

  /// Undoes the last reversible action performed on the document.
  void undo();

  /// Reexecutes the last undone command.
  void redo();

/**
 * @brief Registers an executed command in the document undo list.
 *
 * @param command The command to be registered.
 */
  void registerCommand(const QGUndoableCommandIf& command);

//@}



/** @name Layer Management */
//        ================
//@{

/**
 * @brief Add a layer at a given depth.
 *
 * If the layer already exists in the document, nothing will be
 * done.
 *
 * @param layer The layer to be added.
 * @param depth The depth at which the layer is to be added.
 */
  void addLayer(QGLayerIf * layer, int depth);


/**
 * @brief Remove the given layer
 *
 * @param layer The layer to be removed.
 */
  void removeLayer(QGLayerIf * layer);


/**
 * @brief Access the layer at the given depth.
 *
 * @param depth The depth to be accessed
 *
 * @return A pointer to the found layer or 0 if no layer exists at
 * this depth.
 */
  QGLayerIf * layerAt(int depth);


/**
 * @brief Query the number of layer in the document
 *
 * @return The number of layer in the document.
 */
  int layerCount() const;

//@}


/** @name Information Layer Management */
//        ============================
//@{
/**
 * @brief Add an item to the document information layer.
 *
 * @param item The item to be added.
 */
  void addToInfoLayer(QGraphicsItem * item);

/**
 * @brief Remove an item from the document information layer.
 *
 * @param item The item to be removed
 */
  void removeFromInfoLayer(QGraphicsItem * item);
//@}

/** @name Drawing Function Member */
//        =======================
//@{

/**
 * @brief Draws a rectangular region of the document using a given
 * painter.
 *
 * The layer are painter according to their depth using a logical AND
 * between them.
 *
 * @param cx The rectangle origin x coordinates.
 * @param cy The rectangle origin y coordinates.
 * @param cw The rectangle width.
 * @param ch The rectangle height.
 * @param p  The painter to be used.
 *
 */
  int drawArea(int cx, int cy, int cw, int ch, QPainter * p);


 /**
 * @brief Draws a rectangular region of the document in a given
 * pixmap.
 *
 * The layer are painter according to their depth using a logical AND
 * between them.
 *
 * @warning This function member assumes that the given pixmap size is big
 * enough to embed the rectangle to be painted. Invalid size may lead
 * to undefined behavior.
 *
 * @param cx  The rectangle origin x coordinates.
 * @param cy  The rectangle origin y coordinates.
 * @param cw  The rectangle width.
 * @param ch  The rectangle height.
 * @param pix The pixmap to draw in.
 */
 int drawArea(int cx, int cy, int cw, int ch, QPixmap * pix);

 /**
 * @brief Draws a rectangular region of the document in a given
 * pixmap.
 *
 * The layer are painter according to their depth using a logical AND
 * between them.
 *
 * @warning This function member assumes that the given pixmap size is big
 * enough to embed the rectangle to be painted. Invalid size may lead
 * to undefined behavior.
 *
 * @param cx  The rectangle origin x coordinates.
 * @param cy  The rectangle origin y coordinates.
 * @param cw  The rectangle width.
 * @param ch  The rectangle height.
 * @param pix The pixmap to draw in.
 *
 * @return The number of items added to th
 */
 int drawArea(int cx, int cy, int cw, int ch, QGraphicsScene * scene);

//@}




// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// The information layer
 QGInfoLayer * _infoLayer;

/** @name Properties */
//        ==========
//@{

  /// The width of the document, in pixel.
  int _width;

  

  /// The width of the document, in pixel.
  int _height;


  /// Flag set when the doc as been modified
  bool _modified;


  /// The zoom level of this document.
  float _zoom;


  /// The name of the file the document is bound to.
  QString _fileName;


  /// The name of the document.
  QString _name;

  /// Superimpose mode
  bool _superimposeMode;

//@}


  /// A vector holding a pointer to all layers forming the document.
  QVector<QGLayerIf *> _layerVect;

  /// The document undo list.
  QGUndoList * _undoList;

// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:


/** @name Disabled */
//        ========
//@{

/**
 * @brief Copy-constructor
 */
  QGMultiLayerDoc(const QGMultiLayerDoc&);


/**
 * @brief Assignment operator
 */
  QGMultiLayerDoc& operator=(const QGMultiLayerDoc&);

//@}


// -------------------------------------------------------------------
}; // class QGMultiLayerDoc


#endif /* __QGMULTILAYERDOC_H_INCLUDED__ */
