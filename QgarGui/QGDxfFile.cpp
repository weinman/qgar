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


/**
 * @file  QGDxfFile.cpp
 * @brief Implementation of class QGDxfFile.
 *
 * See file QGDxfFile.h for the interface.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     October 26, 2000  14:29
 * @since    Qgar 2.0
 */



// QGUI
#include <QGDxfFile.h>
#include <QGCanvasEllipse.h>
#include <QGCanvasLine.h>
#include <QGCanvasPolyline.h>
// QT
#include <QMessageBox>
#include <QFile>
#include <QPen>
#include <QPolygon> 
#include <QFont>
#include <QGraphicsSimpleTextItem>
#include <QAbstractGraphicsShapeItem>
// STD
#include <iostream>



using namespace std;




// ---------------------------------------------------------------------
// C O N S T A N T S
// ---------------------------------------------------------------------

// int QGDxfFile::_DXF_COLORS[] = {
//   7,   // BLACK
//   8,   // DARK_GRAY        (NOT DEFINED -> GRAY)
//   8,   // GRAY
//   8,   // LIGHT GRAY       (NOT DEFINED -> GRAY)
//   15,  // WHITE
//   6,   // MAGENTA
//   7,   // PURPLE           (NOT DEFINED -> BLACK)
//   4,   // CYAN
//   5,   // MEDIUM_BLUE      (NOT DEFINED -> BLUE)
//   5,   // BLUE
//   3,   // OLIVE_GREEN      (NOT DEFINED -> GREEN)
//   3,   // DARK_GREEN       (NOT DEFINED -> GREEN)
//   3,   // GREEN
//   2,   // YELLOW
//   1,   // ORANGE           (NOT DEFINED -> RED)
//   1,   // RED
//   1,   // PINK             (NOT DEFINED -> RED)
//   1,   // SALMON_PINK      (NOT DEFINED -> RED)
//   7,   // BROWN            (NOT DEFINED -> BLACK)
//   7    // CHOCOLATE_BROWN  (NOT DEFINED -> BLACK)
// };

const int QGDxfFile::_DXF_COLORS[] =
{  
  250,   // QGE_COLOR_NONE,
  250,   // QGE_COLOR_DEFAULT,
  250,   // QGE_COLOR_BLACK,
  8,     // QGE_COLOR_DARK_GRAY,
  8,     // QGE_COLOR_GRAY,
  252,   // QGE_COLOR_LIGHT_GRAY,
  7,     // QGE_COLOR_WHITE,
  6,     // QGE_COLOR_MAGENTA,
  6,     // QGE_COLOR_PURPLE,
  4,     // QGE_COLOR_CYAN,
  5,     // QGE_COLOR_MEDIUM_BLUE,
  5,     // QGE_COLOR_BLUE,
  3,     // QGE_COLOR_OLIVE_GREEN,
  3,     // QGE_COLOR_DARK_GREEN,
  3,     // QGE_COLOR_GREEN,
  2,     // QGE_COLOR_YELLOW,
  23,    // QGE_COLOR_ORANGE,
  1,     // QGE_COLOR_RED,
  2,     // QGE_COLOR_PINK,
  2,     // QGE_COLOR_SALMON_PINK,
  250,   // QGE_COLOR_BROWN,
  250    // QGE_COLOR_CHOCOLATE_BROWN
 };

// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

QGDxfFile::QGDxfFile(QString fichier, QGraphicsScene * canvas)
  : _canvas(canvas)
{
  QFile f(fichier);

  _width = 0;
  _height = 0;
  _nbSeg = 0;
  _nbArc = 0;
  _nbPoly = 0;
  _nbAutre = 0;

  if (f.open(QIODevice::ReadOnly)) {
    _t = new QTextStream(&f);
    readHeader();
    readEntities();

    f.close();
  }
}

// ---------------------------------------------------------------------
// O T H E R   M E T H O D S
// ---------------------------------------------------------------------

int
QGDxfFile::getGroup()
{
  QString buf;
  int code;

  // We read the code and the value of the group.
  buf = _t->readLine();
  code = buf.toInt();
  buf = _t->readLine();

  // If the read group is a comment, we read the next one.
  if (code == DXFFILE_COM)
    return(getGroup());
  else {
    _code = code;
    _value = buf;
    return(code);
  }
}

// ---------------------------------------------------------------------

void
QGDxfFile::readHeader()
{
  if (getGroup() == DXFFILE_IDENT)
    if(_value==DXFFILE_LBLSEC)
      while(1) {
	while ((getGroup() != DXFFILE_NAME) && (_code != DXFFILE_IDENT))
	  ;
	if ((_code == DXFFILE_NAME) && (_value == DXFFILE_LBLENT)) {
	  getGroup();
	  return;
	}
	if ((_code == DXFFILE_IDENT) && (_value == DXFFILE_LBLEOF))
	  break;
      }
     QMessageBox::critical(0, QObject::tr("Qgar error"), QObject::tr("Qgar header"), QObject::tr("Ok"));
}

// ---------------------------------------------------------------------

void
QGDxfFile::readEntities()
{
  bool endReached = false;

  // Here, Isadora entities are recognized by determining
  // the category of DXF entities
  while(!endReached)
    if (_code == DXFFILE_IDENT)
      if (_value== DXFFILE_LBLSEG)
	readSegEntity();

      else if (_value == DXFFILE_LBLARC)
	readArcEntity();

      else if (_value == DXFFILE_LBLPOL)
	readPolyEntity();

      else if (_value == DXFFILE_LBLTXT)
	readTextEntity();

      else if (_value == DXFFILE_LBLEOF)
	endReached = true;

      else if (_value == DXFFILE_LBLEND)
	endReached = true;

      else {
	QMessageBox::critical(0, QObject::tr("Qgar error"), QObject::tr("ReadEntities Error"), QObject::tr("Ok"));

	break;
      }
    else
      getGroup();
}
// ---------------------------------------------------------------------

void
QGDxfFile::readTextEntity()
{
  QGraphicsSimpleTextItem * txt;

  if (getGroup() == DXFFILE_LYNME)
    if (_value== DXFFILE_NMETXT) {
      getGroup();
      txt = readText();
      recordObjet(txt);
    }
    else
      QMessageBox::critical(0, QObject::tr("Qgar error ReadTextEntity"), QObject::tr("Text"), QObject::tr("Ok"));
  else {
    txt = readText();
    recordObjet(txt);
  }
}

// ---------------------------------------------------------------------

void
QGDxfFile::readSegEntity()
{
  QGCanvasLine * seg;

  if (getGroup() == DXFFILE_LYNME)
    if (_value== DXFFILE_NMEPRM) {
      getGroup();
      seg = readSegment();
      recordObjet(seg);
      _nbSeg++;
    } 

    else if (_value== DXFFILE_NMEDWA)
      readDividingWall();
  
    else if (_value== DXFFILE_NMEBWA)
      readBearingWall();
	
    else if (_value== DXFFILE_NMESWI)
	    readSimpleWindow();
	
    else if (_value==DXFFILE_NMEDWI)
      readDoubleWindow();
    
    else if (_value== DXFFILE_NMEDOO)
      readDoor();
    
    else
      QMessageBox::critical(0, QObject::tr("Qgar error ReadSegEntity"), QObject::tr("Drawings"), QObject::tr("Ok"));

  else {
    seg = readSegment();
    recordObjet(seg);
    _nbSeg++;
  }
}

// ---------------------------------------------------------------------

void
QGDxfFile::readArcEntity() {
  QGCanvasEllipse* arc;

  if (getGroup() == DXFFILE_LYNME)
    if (_value== DXFFILE_NMEPRM) {
      getGroup();
      arc = readArc();
      recordObjet(arc);
      _nbArc++;
      //theArcs.push_back(readArc());
    }
    else
      QMessageBox::critical(0, QObject::tr("Qgar error ReadArcEntity"), QObject::tr("Drawings"), QObject::tr("Ok"));
  else
    // theArcs.push_back(readArc());
    ;
}

// ---------------------------------------------------------------------

void
QGDxfFile::readPolyEntity()
{
  if (getGroup() == DXFFILE_LYNME)
    if (_value== DXFFILE_NMESTA) {
      //theSymbols.push_back(readStairs());
      readStairs();
    }
  
    else if (_value== DXFFILE_NMEPIP) {
      //	theSymbols.push_back(readPipe());
      readPipe();
    }
    
    else if (_value== DXFFILE_NMECHN) {
      //	  theChains.push_back(readChain());
      readChain();
    }
	
    else if (_value== DXFFILE_NMEPOL) {
      // thePolylines.push_back(readIsaPolyline());
      readIsaPolyline();
    }

    else
      QMessageBox::critical(0, QObject::tr("Qgar error"), QObject::tr("ReadPolyEntity"), QObject::tr("Ok"));
 
  else
    QMessageBox::critical(0, QObject::tr("Qgar error"), QObject::tr("ReadPolyEntity"), QObject::tr("Ok"));
}

// ---------------------------------------------------------------------

QGCanvasLine *
QGDxfFile::readSegment()
{
  QGCanvasLine* seg;
  QPoint p1;
  QPoint p2;
  int width = 1;
  int color = 7;

  while (_code != DXFFILE_IDENT) {
    switch (_code) {
    case DXFFILE_X1:
      p1.setX(_value.toInt());
      break;
    case DXFFILE_Y1:
      p1.setY(_value.toInt());
      break;
    case DXFFILE_X2:
      p2.setX(_value.toInt());
      break;
    case DXFFILE_Y2:
      p2.setY(_value.toInt());
      break;
    case DXFFILE_THICK:
      width = _value.toInt();
      break;
    case DXFFILE_COLOR:
      color = _value.toInt();
      break;
    default:
      break;
    }
    getGroup();
  } 

  seg = new QGCanvasLine(_canvas, width);
  seg->setLine(p1.x(), p1.y(), p2.x(), p2.y());

  //  changeColor(seg, color);
  // WARNING:
  // QGCanvasLine inherits direct from QGraphicsItem and not QGraphicsAbstractItem
  // The color of its pen is changed without calling QGCanvasLine.
  // This is a temporary solution.
  QPen p = seg->pen();

  if (color != 7)
    switch (color) {

    case 1:
      p.setColor(QColor("red"));
      break;

    case 2:
      p.setColor(QColor("yellow"));
      break;
    
    case 3:
      p.setColor(QColor("green"));
      break;
      
    case 4:
      p.setColor(QColor("cyan"));
      break;
      
    case 5:
      p.setColor(QColor("blue"));
      break;
      
    case 6:
      p.setColor(QColor("magenta"));
      break;
      
    case 8:
      p.setColor(QColor("gray"));
      break;
      
    case 15:
      p.setColor(QColor("white"));
      break;
    }

  seg->setPen(p);
  return(seg);
}

// ---------------------------------------------------------------------

QGraphicsSimpleTextItem *
QGDxfFile::readText()
{
  QGraphicsSimpleTextItem * txt;
  QPoint p1;
  int height;
  int color;
  QString msg;

  while (_code != DXFFILE_IDENT) {
    switch (_code) {
    case DXFFILE_X1:
      p1.setX(_value.toInt());
      break;
    case DXFFILE_Y1:
      p1.setY(_value.toInt());
      break;
    case DXFFILE_TXTHGHT:
      height = _value.toInt();
      break;
    case DXFFILE_COLOR:
      color = _value.toInt();
      break;
    case DXFFILE_TXTVAL:
      msg = _value;
      break;
    default:
      break;
    }
    getGroup();
  } 

  txt = new QGraphicsSimpleTextItem(msg);
  txt->setFont(QFont("helvetica", height));
  txt->setPos(p1.x(), p1.y());

  _canvas->addItem(txt);

  if (color != 7)
    switch (color) {
      
    case 1:
      txt->setBrush(QBrush(QColor("red"), Qt::SolidPattern));
      break;

    case 2:
      txt->setBrush(QBrush(QColor("yellow"), Qt::SolidPattern));
      break;
    
    case 3:
      txt->setBrush(QBrush(QColor("green"), Qt::SolidPattern));
      break;
      
    case 4:
      txt->setBrush(QBrush(QColor("cyan"), Qt::SolidPattern));
      break;
      
    case 5:
      txt->setBrush(QBrush(QColor("blue"), Qt::SolidPattern));
      break;
      
    case 6:
      txt->setBrush(QBrush(QColor("magenta"), Qt::SolidPattern));
      break;
      
    case 8:
      txt->setBrush(QBrush(QColor("gray"), Qt::SolidPattern));
      break;
      
    case 15:
      txt->setBrush(QBrush(QColor("white"), Qt::SolidPattern));
      break;
    }
  
  return(txt);
}

// ---------------------------------------------------------------------

void
QGDxfFile::readDividingWall()
{
  QGCanvasLine* seg = readSegment();
  delete seg;
  //IsaSegment* aSeg = readSegment();
  //IsaDividingWall* aWall = new IsaDividingWall(*aSeg);
  //delete aSeg;
  //return(aWall);
}

// ---------------------------------------------------------------------

void
QGDxfFile::readBearingWall()
{
  QGCanvasLine *seg = readSegment();
  delete seg;
  //  IsaSegment* aSeg = readSegment();
  //IsaBearingWall* aWall = new IsaBearingWall(*aSeg);
  //delete aSeg;
  //return(aWall);
}

// ---------------------------------------------------------------------

void
QGDxfFile::readSimpleWindow()
{
  QGCanvasLine* seg = readSegment();
  delete seg;
//  IsaSegment* aSeg = readSegment();
 // IsaSimpleWindow* aWindow = new IsaSimpleWindow(*aSeg);
  //delete aSeg;
  //return(aWindow);
}

// ---------------------------------------------------------------------

void
QGDxfFile::readDoubleWindow()
{
  QGCanvasLine* seg = readSegment();
  delete seg;
  //  IsaSegment* aSeg = readSegment();
  //  IsaDoubleWindow* aWindow = new IsaDoubleWindow(*aSeg);
  //delete aSeg;
  //return(aWindow);
}

// ---------------------------------------------------------------------

void
QGDxfFile::readDoor()
{
  QGCanvasLine* seg = readSegment();
  delete seg;
  //  IsaSegment* aSeg = readSegment();
  // IsaDoor* aDoor = new IsaDoor(*aSeg);
  //delete aSeg;
  //return(aDoor);
}

// ---------------------------------------------------------------------

QGCanvasEllipse*
QGDxfFile::readArc()
{
  QGCanvasEllipse* arc;
  QPoint pt;
  double radius;
  double startAngle;
  double endAngle;
  int width = 1;
  int color = 7;

  while (_code != DXFFILE_IDENT) {
    switch (_code) {
    case DXFFILE_X1:
      pt.setX(_value.toInt());
      break;
    case DXFFILE_Y1:
      pt.setY(_value.toInt());
      break;
    case DXFFILE_RAD:
      radius = _value.toDouble();
      break;
    case DXFFILE_STRT:
      startAngle = _value.toDouble();
      break;
    case DXFFILE_END:
      endAngle = _value.toDouble();
      break;
    case DXFFILE_THICK:
      width = _value.toInt();
      break;
    case DXFFILE_COLOR:
      color = _value.toInt();
      break;
    default:
      break;
    }
    getGroup();
  }

  arc = new QGCanvasEllipse(pt.x(), pt.y(), 
			    (int) (radius * 2.), (int) (radius * 2.),
 			    (int) (startAngle * QGAR_ARC_ACCURACY),
 			    (int) (endAngle * QGAR_ARC_ACCURACY),
 			    _canvas, width);
  changeColor(arc, color);

  return(arc);
}

// ---------------------------------------------------------------------

void
QGDxfFile::readStairs()
{
  //QList<QPoint> theEdges;
  //int unusedWidth;
  QGCanvasPolyline* poly = readPolyline();
  delete poly;
  //return(new IsaStairs(theEdges));
}

// ---------------------------------------------------------------------

void
QGDxfFile::readPipe()
{
  //  QList<QPoint> theEdges;
  //int unusedWidth;
  QGCanvasPolyline* poly = readPolyline();
  delete poly;
  //return(new IsaPipe(theEdges));
}

// ---------------------------------------------------------------------

void
QGDxfFile::readChain()
{
  //  QList<QPoint> thePoints;
  //QList<QPoint>::iterator itP;
  //GenLinkedChain<int>* theChain;
  //int unusedWidth;
  QGCanvasPolyline* poly = readPolyline();
  delete poly;
  //theChain = new GenLinkedChain<int>();

  //for (itP = thePoints.begin(); itP != thePoints.end(); itP++)
  //  theChain->push_back(*itP);

  //return (theChain);
}

// ---------------------------------------------------------------------

void
QGDxfFile::readIsaPolyline()
{
  //QList<QPoint> thePoints;
  //QList<QPoint>::iterator itP;
  //IsaPolyline* thePolyline;
  //QPoint firstPoint;
  //QPoint secondPoint;
  //int width;
  
  QGCanvasPolyline* poly = readPolyline();
  recordObjet(poly);
  _nbPoly++;
  //  itP = thePoints.begin();
  // firstPoint = *itP;
  //itP++;
  //secondPoint = *itP;
  //itP++;
  //IsaSegment firstSeg(firstPoint, secondPoint, width);
  //thePolyline = new IsaPolyline(firstSeg);
  //while (itP != thePoints.end()) {
  //  thePolyline->push_back(*itP);
  //  itP++;
  //}
  //return (thePolyline);
}

// ---------------------------------------------------------------------

QGCanvasPolyline*
QGDxfFile::readPolyline()
{

  QGCanvasPolyline* poly = new QGCanvasPolyline(_canvas);
  QPolygon thePoints;
  QPoint pt;  

  getGroup();

  if (_code == DXFFILE_THICK) 
    poly->setWidth(_value.toInt());

  while (_code != DXFFILE_IDENT)
    getGroup();
  while (_value== DXFFILE_LBLVER) {
    while (getGroup() != DXFFILE_IDENT)
      switch (_code) {
      case DXFFILE_X1:
	pt.setX(_value.toInt());
	break;
      case DXFFILE_Y1:
	pt.setY(_value.toInt());
	break;
      default:
	break;
      }
    
    thePoints.resize(thePoints.size() + 1);
    thePoints.setPoint(thePoints.size() - 1, pt);
  }

  if (_value== DXFFILE_LBLESQ)
    getGroup();

  poly->setPoints(thePoints);

  // Set the position in the canvas (QGraphicsScene)
  //  poly->setPos(poly->mapToScene(thePoints.point(0)));

  return(poly);
}

// ---------------------------------------------------------------------

void
QGDxfFile::recordObjet(QGraphicsItem* obj)
{
  qreal max;

  if (obj) {
    _objectsList.push_back(obj);
    obj->show();

    max = obj->boundingRect().right();

    if (max > _width)
      _width = (int)max;

    max = obj->boundingRect().bottom();
    
    if (max > _height)
      _height = (int)max;
  }
}

// ---------------------------------------------------------------------

void
QGDxfFile::changeColor(QAbstractGraphicsShapeItem * item, int color)
{
  QPen p = item->pen();

  if (color != 7)
    switch (color) {

    case 1:
      p.setColor(QColor("red"));
      break;

    case 2:
      p.setColor(QColor("yellow"));
      break;
    
    case 3:
      p.setColor(QColor("green"));
      break;
      
    case 4:
      p.setColor(QColor("cyan"));
      break;
      
    case 5:
      p.setColor(QColor("blue"));
      break;
      
    case 6:
      p.setColor(QColor("magenta"));
      break;
      
    case 8:
      p.setColor(QColor("gray"));
      break;
      
    case 15:
      p.setColor(QColor("white"));
      break;
    }

  item->setPen(p);
}

// ---------------------------------------------------------------------
