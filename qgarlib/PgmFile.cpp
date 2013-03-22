/*---------------------------------------------------------------------+
 | Library QgarLib, graphics analysis and recognition                  |
 | Copyright (C) 2002  Qgar Project, LORIA                             |
 |                                                                     |
 | This library is free software; you can redistribute it and/or       |
 | modify it under the terms of the GNU Lesser General Public          |
 | License version 2.1, as published by the Free Software Foundation.  |
 |                                                                     |
 | This library is distributed in the hope that it will be useful,     |
 | but WITHOUT ANY WARRANTY; without even the implied warranty of      |
 | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                |
 | See the GNU Lesser General Public License for more details.         |
 |                                                                     |
 | The GNU Lesser General Public License is included in the file       |
 | LICENSE.LGPL, in the root directory of the Qgar packaging. See      |
 | http://www.gnu.org/licenses/lgpl.html for the terms of the licence. |
 | To receive a paper copy, write to the Free Software Foundation,     |
 | Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.       |
 |                                                                     |
 | Contact Project Qgar for any information:                           |
 |   LORIA - йquipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-lиs-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/


/**
 * @file PgmFile.cpp
 *
 * @brief Implementation of class qgar::PgmFile.
 *
 * See file PgmFile.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gйrald Masini">Karl Tombre & Gйrald Masini</a>
 * @date   Jul 3, 2001  16:57
 * @since  Qgar 1.0
 */


// STD
#include <cstring>
#include <iostream>
#include <limits>
#include <sstream>
// QGAR
#include <qgarlib/AbstractPbmPlusFile.h>
#include <qgarlib/GenImage.h>
#include <qgarlib/PgmFile.h>
#include <qgarlib/qgar.h>
#include <qgarlib/QgarErrorIO.h>



using namespace std;



namespace qgar
{


// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// S T A T I C   M E M B E R S
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS


// MAXIMUM LENGTH OF A LINE OF THE FILE HEADER
const int PgmFile::s_pgm_header_line_size_       = 255;

// CHARACTER FOR FORMAT plain IN THE MAGIC NUMBER
const unsigned char  PgmFile::s_pgm_magic_plain_ = '2';

// CHARACTER FOR FORMAT raw IN THE MAGIC NUMBER
const unsigned char  PgmFile::s_pgm_magic_raw_   = '5';


// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// E N D   O F   S T A T I C   M E M B E R S
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS




// -------------------------------------------------------------------
// C O N S T R U C T O R S 
// -------------------------------------------------------------------


// ====================================
// INITIALIZE FROM FILE NAME AND FORMAT
// ====================================


PgmFile::PgmFile(const char* aFileName, QGEpbm aPbm)

  : AbstractPbmPlusFile(aFileName, aPbm),
    inBuf_(new char[s_pgm_header_line_size_ + 1]),
    maxPixel_(0),
    rowCnt_(0),
    colCnt_(0)
{
  // VOID  
}


// -------------------------------------------------------------------
// D E S T R U C T O R
// -------------------------------------------------------------------


PgmFile::~PgmFile()
{
  // Delete I/O buffer
  delete [] inBuf_;
}


// -------------------------------------------------------------------
// I N P U T 
// -------------------------------------------------------------------


// ===========================
// READ AN IMAGE FROM THE FILE
// ===========================


GreyLevelImage
PgmFile::read()
{
  // Open file in read-only mode
  openRONLY();

  // Read file header
  readHeader();

  // Create the pixel map according to the file header
  int             size = colCnt_ * rowCnt_;
  GreyLevelPixel* pMap = new GreyLevelPixel[size];
  istringstream iss1(string((const char*)inBuf_), istringstream::in);

  if (format_ == QGE_PBM_RAW)

    {
      // _____________________________________________________________
      //
      // FILE FORMAT IS raw
      // _____________________________________________________________

      GreyLevelPixel* pm = pMap;

      for (int iCnt = 0 ; iCnt < (colCnt_ * rowCnt_) ; ++iCnt, ++pm)
	{
	  *pm = (GreyLevelPixel) fstream_.get();
	}
      // _____________________________________________________________
    }

  else

    {
      // _____________________________________________________________
      //
      // FILE FORMAT IS plain
      // _____________________________________________________________

      GreyLevelPixel* pm = pMap;

      for (int iCnt = 0 ; iCnt < (colCnt_ * rowCnt_) ; ++iCnt, ++pm)
	{
	  int i;
	  fstream_ >> i;
	  *pm = (GreyLevelPixel) i;
	}
      // _____________________________________________________________
      //
    } // END if format_


  // Close file
  close();

  // Return image
  return GreyLevelImage(colCnt_, rowCnt_, pMap);
}


// -------------------------------------------------------------------
// O U T P U T 
// -------------------------------------------------------------------


// ==========================
// WRITE AN IMAGE IN THE FILE
// ==========================


void
PgmFile::write(const GreyLevelImage& anImg)
{
  // Open file in write-only mode
  openWONLY();

  // Get image characteristics
  colCnt_   = anImg.width();
  rowCnt_   = anImg.height();
  maxPixel_ = numeric_limits<GreyLevelPixel>::max();

  // Write file header
  writeHeader();

  GreyLevelPixel* pMap = anImg.pPixMap();   // pointer to pixel map
  int             size = colCnt_ * rowCnt_; // image size

  if (format_ == QGE_PBM_RAW)

    {
      // _____________________________________________________________
      //
      // FILE FORMAT IS raw
      // _____________________________________________________________

      for (int iCnt = 0 ; iCnt < size ; ++iCnt, ++pMap)
	{
	  fstream_.put(*pMap);
	}
      // _____________________________________________________________
    }

  else

    {
      // _____________________________________________________________
      //
      // FILE FORMAT IS plain
      // _____________________________________________________________

      for (int iCnt = 0 ; iCnt < (size - 1) ; ++iCnt, ++pMap)
	{
	  fstream_ << (int) *pMap << ' ';
	}

      fstream_ << (int) *pMap << endl;
      // _____________________________________________________________
      //
    } // END if format_


  // Close file
  close();
}


// ===========================
// WRITE INT IMAGE IN THE FILE
// ===========================


void
PgmFile::write(const IntImage& anImg)
{
  // Open file in write-only mode
  openWONLY();

  // Get image characteristics
  colCnt_   = anImg.width();
  rowCnt_   = anImg.height();
  maxPixel_ = numeric_limits<unsigned short>::max();

  // Write file header
  writeHeader();

  
  IntImage::pointer pMap = anImg.pPixMap();   // pointer to pixel map
  int               size = colCnt_ * rowCnt_; // image size

  if (format_ == QGE_PBM_RAW)

    {
      // _____________________________________________________________
      //
      // FILE FORMAT IS raw
      // _____________________________________________________________

      for (int iCnt = 0 ; iCnt < size ; ++iCnt, ++pMap)
	{          
          unsigned short px = (unsigned short)(*pMap % maxPixel_);
          // Write in big endian
          fstream_.put((px & 0xFF00) >> 8);
          fstream_.put((px & 0x00FF));
	}
      // _____________________________________________________________
    }

  else

    {
      // _____________________________________________________________
      //
      // FILE FORMAT IS plain
      // _____________________________________________________________

      for (int iCnt = 0 ; iCnt < (size - 1) ; ++iCnt, ++pMap)
	{
	  fstream_ << (int) (*pMap % maxPixel_) << ' ';
	}

      fstream_ << (int) (*pMap % maxPixel_) << endl;
      // _____________________________________________________________
      //
    } // END if format_


  // Close file
  close();
}


// -------------------------------------------------------------------
// H E A D E R
// -------------------------------------------------------------------


// ================
// READ FILE HEADER
// ================

void
PgmFile::readHeader()
{  

  // READ THE FIRST LINE AND GET THE MAGIC NUMBER

  fstream_.getline(inBuf_, s_pgm_header_line_size_);
  int charsRead = fstream_.gcount();
  bool imDimReadFlag = false;

  unsigned char m1 = inBuf_[0];
  unsigned char m2 = inBuf_[1];

  // Check if there is more than the Magic Number in the first line
  if (charsRead > 4)
    {
      fstream_.seekg(0);
      istringstream iss(string((const char*)inBuf_), istringstream::in);

      string tmp;
      iss >> tmp; // Re-read the Magic Number and discard it

      iss >> colCnt_;
      iss >> rowCnt_;
      iss >> maxPixel_;
      //////////////////////////////////////////////////////////////////////////////
      std::cout << "--> NB col = " << colCnt_
		<< "    NB lig = " << rowCnt_ 
                << "    NB max = " << maxPixel_ << std::endl;
      //////////////////////////////////////////////////////////////////////////////

      // SET the dimensions read FLAG
      imDimReadFlag = true;
    }

  // CHECK MAGIC NUMBER

  if ((m1 != s_pbm_magic_) ||
      ((m2 != s_pgm_magic_plain_) && (m2 != s_pgm_magic_raw_)))
    {
      ostringstream os;
      os << "Bad magic number in header of file "
	 << name_
	 << ": " << m1 << m2;
      throw QgarErrorIO(__FILE__, __LINE__,
			"void qgar::PgmFile::readHeader()", os.str());
    }

  // SET FILE FORMAT

  if (m2 == s_pgm_magic_plain_)
    {
      format_ = QGE_PBM_PLAIN;
    }
  else
    {
      format_ = QGE_PBM_RAW;
    }

  // SKIP POSSIBLE COMMENTS AND BLANK LINES

  do
    {
      fstream_.getline(inBuf_, s_pgm_header_line_size_);
//////////////////////////////////////////////////////////////////////////////
      std::cout << "--> line (" << inBuf_
		<< ") inBuf_[0] = (" << inBuf_[0] << ')' << std::endl;
//////////////////////////////////////////////////////////////////////////////
    }
  while (inBuf_[0] == s_pbm_comment_ ||
         inBuf_[0] == '\0');


  // GET IMAGE SIZE if it's not yet gotten
  if(!imDimReadFlag)
    {
      // Store current line in a string stream
      istringstream iss(string((const char*)inBuf_));
      iss >> colCnt_;
      iss >> rowCnt_;

      // GET MAX PIXEL VALUE

      // Next line
      fstream_.getline(inBuf_, s_pgm_header_line_size_);

      // Store current line in the string stream
      // WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
      // WARNING: the last read from the stream may have hit the end
      // of the stream and put the stream in an EOF state. In this case,
      // nothing more will work on the stream until state EOF is cleared.
      // WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
      iss.clear();
      // WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
      iss.str(string((const char*)inBuf_));
  
      iss >> maxPixel_;
    }


  // CHECK MAX PIXEL VALUE

  if (maxPixel_ > (int) numeric_limits<GreyLevelPixel>::max())
    {
      ostringstream os;
      os << "Bad max pixel value in header of file "
	 << name_
	 << ": " << maxPixel_;
      throw QgarErrorIO(__FILE__, __LINE__,
			"void qgar::PgmFile::readHeader()", os.str());
    }
  
}


// =================
// WRITE FILE HEADER
// =================


void
PgmFile::writeHeader()
{
  // MAGIC NUMBER

  fstream_ << s_pbm_magic_;

  if (format_ == QGE_PBM_RAW)
    {
      fstream_ << s_pgm_magic_raw_;    // RAW
    }
  else
    {
      fstream_ << s_pgm_magic_plain_;  // PLAIN
    }

  // QGAR VERSION (COMMENT)

  fstream_ << endl
	   << "# Created by "
	   << qgVersion()
	   << endl;

  // IMAGE FEATURES

  fstream_ << colCnt_    // image width
	   << ' '
	   << rowCnt_    // image height
	   << endl
	   << maxPixel_  // max pixel value
	   << endl;
}


// -------------------------------------------------------------------


} // namespace qgar
