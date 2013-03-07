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


#ifndef __QGDXFFILE_H_INCLUDED__
#define __QGDXFFILE_H_INCLUDED__


/**
 * @file     QGDxfFile.h
 * @brief    Header file of class QGDxfFile.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 26, 2000  14:29
 * @since    Qgar 2.0
 */


/* $Id: QGDxfFile.h,v 1.6 2005/07/13 16:30:27 masini Exp $ */



// QT
#include <QList>
#include <QTextStream>
// QGUI
class QGCanvasPolyline;
class QGCanvasLine;
class QGCanvasEllipse;
class QGraphicsItem;
class QGraphicsScene;
class QGraphicsSimpleTextItem;
class QAbstractGraphicsShapeItem;

// -------------------------------------------------------------------
// D X F   C O D E S
// -------------------------------------------------------------------

#define DXFFILE_COM     999   // Comment
#define DXFFILE_IDENT   0     // Identifier
#define DXFFILE_NAME    2     // Name
#define DXFFILE_COLOR   62    // Color
#define DXFFILE_X1      10    // X1
#define DXFFILE_X2      11    // X2
#define DXFFILE_Y1      20    // Y1
#define DXFFILE_Y2      21    // Y2
#define DXFFILE_THICK   39    // Thickness
#define DXFFILE_RAD     40    // Radius / Total pattern length 
#define DXFFILE_STRT    50    // Start angle
#define DXFFILE_END     51    // End angle
#define DXFFILE_FLAG    70    // Standard flag value
#define DXFFILE_LINTP   3     // Descriptive text for linetype
#define DXFFILE_ALGT    72    // Alignment code
#define DXFFILE_DASH    73    // Number of dash length items
#define DXFFILE_LTPNME  6     // Ltype name
#define DXFFILE_LYNME   8     // Layer name
#define DXFFILE_ELEV    38    // Elevation
#define DXFFILE_VERFLA  66    // Vertices flag
#define DXFFILE_TXTHGHT 40    // Text height
#define DXFFILE_TXTVAL  1     // Text value

#define DXFFILE_LBLSEC  "SECTION"
#define DXFFILE_LBLTBS  "TABLES"
#define DXFFILE_LBLTBL  "TABLE"
#define DXFFILE_LBLLAY  "LAYER"
#define DXFFILE_LBLLTP  "LTYPE"
#define DXFFILE_LBLENT  "ENTITIES"
#define DXFFILE_LBLARC  "ARC"
#define DXFFILE_LBLSEG  "LINE"
#define DXFFILE_LBLPOL  "POLYLINE"
#define DXFFILE_LBLVER  "VERTEX"
#define DXFFILE_LBLEOF  "EOF"
#define DXFFILE_LBLEND  "ENDSEC"
#define DXFFILE_LBLETB  "ENDTAB"
#define DXFFILE_LBLESQ  "SEQEND"
#define DXFFILE_LBLTXT  "TEXT"

#define DXFFILE_COMCREA "*** Created by Qgar on "
#define DXFFILE_COMDEF  "** Definitions"
#define DXFFILE_COMLTP  "** Linetype definitions"
#define DXFFILE_COMLAY  "** Layer definitions"
#define DXFFILE_COMENT  "** Entities"
#define DXFFILE_COMSEG  "** Segment"
#define DXFFILE_COMARC  "** Arc"
#define DXFFILE_COMDWA  "** Dividing wall"
#define DXFFILE_COMBWA  "** Bearing wall"
#define DXFFILE_COMSWI  "** Simple window"
#define DXFFILE_COMDWI  "** Double window"
#define DXFFILE_COMDOO  "** Door"
#define DXFFILE_COMSTA  "** Stairs"
#define DXFFILE_COMPIP  "** Pipe"
#define DXFFILE_COMCHN  "** Chaine"
#define DXFFILE_COMPOL  "** Polyline"
#define DXFFILE_COMTXT  "** Texte"

#define DXFFILE_VALCON  "CONTINUOUS"  // Linetype for LTYPE
#define DXFFILE_VALDLTP "----"        // Descriptive for LTYPE
#define DXFFILE_VALLTP  1             // Number of LTYPE
#define DXFFILE_VALFLY  2             // Flag value for LAYER
#define DXFFILE_VALLAY  8             // Number of LAYERS
#define DXFFILE_VALFLT  64            // Flag value for LTYPE
#define DXFFILE_VALALG  65            // Aligment value for LTYPE
#define DXFFILE_VALDASH 0             // Dash length for LTYPE
#define DXFFILE_VALPAT  0.0           // Total length pattern for LTYPE
#define DXFFILE_VALWPO  1             // Default width for POLYLINE
#define DXFFILE_VALVFG  1             // Vertices follow POLYLINE definition
#define DXFFILE_VALPFGO 0             // The polylines are opened
#define DXFFILE_VALPFGC 1             // The polylines are closed

#define DXFFILE_NMEPRM  "PRIMITIVE"
#define DXFFILE_NMEDWA  "DIVWALL"
#define DXFFILE_NMEBWA  "BEARWALL"
#define DXFFILE_NMESWI  "SIMWIN"
#define DXFFILE_NMEDWI  "DOUWIN"
#define DXFFILE_NMEDOO  "DOOR"
#define DXFFILE_NMESTA  "STAIRS"
#define DXFFILE_NMEPIP  "PIPE"
#define DXFFILE_NMECHN  "CHAINE"
#define DXFFILE_NMEPOL  "POLYLINE"
#define DXFFILE_NMETXT  "TEXT"



/**
 * @brief Handle the DXF files.
 *
 * This class reads a DXF file and extracts all vector items it
 * contains. The Vector items are stored in QGraphicsItem subclasses.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 26, 2000  14:29
 * @since    Qgar 2.0
 */
class QGDxfFile
{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:


/** @name Constructor */
//        ===========
//@{

/**
 * @brief Constructor.
 *
 * Reads all the entities from a given DXF, creates the matching
 * QGraphicsItem instances and attaches them to a given canvas.
 *
 * @param filename The name of the DXF file to read.
 * @param canvas The canvas to attach the extracted features to.
 */
  QGDxfFile(QString filename, QGraphicsScene * scene);

//@}


// ------------------------
// USING DEFAULT DESTRUCTOR
// ------------------------



/** @name Accessor */
//        ========
//@{

/**
 * @brief Access to the list of vectorial items.
 *
 * @return A reference on the list of vectorial items.
 */
  const QList<QGraphicsItem *>& getList() const
  { return _objectsList; }


/**
 * @brief Query the number of segments contained in the file.
 *
 * @return The number of segments in the file.
 */
  int getNbSeg() const { return _nbSeg; }


/**
 * @brief Query the number of arcs contained in the file.
 *
 * @return The number of arcs in the file.
 */
  int getNbArc() const { return _nbArc; }


/**
 * @brief Query the number of polylines contained in the file.
 *
 * @return The number of polylines in the file.
 */
  int getNbPoly() const { return _nbPoly; }


/**
 * @brief Query the number of polylines contained in the file.
 *
 * @return The number of polylines in the file.
 */
  int getNbAutre() const { return _nbAutre; }


/** 
 * @brief Retrieve the Width of the image..
 *
 * @return The width of the image.
 */
  int getWidth() const { return _width; }

/** 
 * @brief Retrieve the height of the image.
 *
 * @return The height of the image.
 */
  int getHeight() const { return _height; }

//@}


/** 
 * @brief Adds an vectorial item to the item list and update the image
 * bounds.
 *
 * If the item coordinates is out of the current image bounds the size
 * of the image is recomputed.
 *
 * @param item The item to be added.
 */
  void recordObjet(QGraphicsItem * item);

// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------

protected:

  /// The canvas the vectorial items are bound to.
  QGraphicsScene * _canvas;

  /// The list of the vectorial items.
  QList<QGraphicsItem*> _objectsList;

  /// The input stream used while reading the file.
  QTextStream *_t;

  /// The number of segments contained in the vectorial item list.
  int _nbSeg;

  /// The number of arcs contained in the vectorial item list.
  int _nbArc;

  /// The number of polylines  contained in the vectorial item list.
  int _nbPoly;

/**
 * @brief The number of items, other than segment, arc or polylines,
 * contained in the vectorial item list.
 */
  int _nbAutre;

  /// The image width.
  int _width;

  /// The image height.
  int _height;

  /// The DXF color index.
  static const int _DXF_COLORS[];

  int _code;
  QString _value;


/** @name Parsing Function Members */
//        ========================
//@{

/**
 * @brief Internal function to parse a DXF file.
 */
  int getGroup();


/**
 * @brief Internal function to parse a DXF file.
 */
  void readHeader();


/**
 * @brief Internal function to parse a DXF file.
 */
  void readEntities();


/**
 * @brief Reads a segment entity.
 */
  void readSegEntity();


/**
 * @brief Reads an arc entity.
 */
  void readArcEntity();


/**
 * @brief Reads a polyline entity.
 */
  void readPolyEntity();


/**
 * @brief Reads a text entity.
 */
  void readTextEntity();

/** 
 * @brief Reads a dividing wall.
 */
  void readDividingWall();

/**
 * @brief Reads a bearing wall.
 */
  void readBearingWall();


/**
 * @brief Reads a simple window.
 */
  void readSimpleWindow();

/**
 * @brief Reads a double window.
 */
  void readDoubleWindow();


/**
 * @brief Reads a door.
 */
  void readDoor();


/**
 * @brief Reads stairs.
 */
  void readStairs();


/**
 * @brief Reads a pipe.
 */
  void readPipe();


/**
 * @brief Reads a chain.
 */
  void readChain();


/**
 * @brief Reads an IsaPolyline.
 */
  void readIsaPolyline();


/**
 * @brief Reads a segment.
 *
 * @return A pointer to the matching QGraphicsItem
 */
  QGCanvasLine * readSegment();


/**
 * @brief Reads an arc.
 *
 * @return A pointer to the matching QGraphicsItem
 */
  QGCanvasEllipse * readArc();


/**
 * @brief Reads a polyline.
 *
 * @return A pointer to the matching QGraphicsItem
 */
  QGCanvasPolyline * readPolyline();


/**
 * @brief Reads text.
 *
 * @return A pointer to the matching QGraphicsItem
 */
  QGraphicsSimpleTextItem * readText();

//@}


/**
 * @brief Changes the color of a primitive.
 *
 * @param item  The item the color of which is to be changed.
 * @param color The index of the new color.
 */
  void changeColor(QAbstractGraphicsShapeItem * item, int color);

// -------------------------------------------------------------------
}; // class QGDxfFile


#endif /* __QGDXFFILE_H_INCLUDED__ */
