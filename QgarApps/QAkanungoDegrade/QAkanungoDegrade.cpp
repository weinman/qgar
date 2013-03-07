/*---------------------------------------------------------------------*
 | Library QgarLib, graphics analysis and recognition                  |
 | Copyright (C) 2004  Qgar Project, LORIA                             |
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
 | http://www.gnu.org/licenses/lgpl.html for the terms of the license. |
 | To receive a paper copy, write to the Free Software Foundation,     |
 | Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.       |
 |                                                                     |
 | Contact Project Qgar for any information:                           |
 |   LORIA - équipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-lès-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/


/**
 * @file QAkanungoDegrade.cpp
 *
 * @brief Image degradation, using Kanungo's method.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Perrin & Kheder">Julien Perrin & Sami Kheder</a>
 * @date   March 24, 2003  16:16
 * @since  Qgar 2.1.1
 */



// QGAR
#include <qgarlib/GenImage.h>
#include <qgarlib/KanungoBinaryImage.h>
#include <qgarlib/PbmFile.h>
#include <qgarlib/QgarApp.h>



using namespace std;
using namespace qgar;



/**
 * @ingroup IMG_KANUNGO
 *
 * @brief Degradation of a binary image, using Kanungo <em>et al</em>&nbsp;'s method.
 *
 * See
 * [<a href="Bibliography.html#Kanungo-et-al-2000">Kanungo&nbsp;et&nbsp;al,&nbsp;2000</a>]
 * for full details about the method.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Perrin & Kheder">Julien Perrin & Sami Kheder</a>
 * @date   March 24, 2003  16:16
 * @since  Qgar 2.1.1
 */

int
main(int argc, char * argv[])
{
  QgarApp app;

  // PARAMETERS DESCRIPTION
  // ======================

  // Full pathname of the source file
  app.addParameter("-in",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEIN,
		   "source image:");

  //
  app.addParameter("-out",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEOUTD,
		   "result image:",
		   ".degraded.pbm");

  //
  app.addParameter("-a0",
		   QgarArgs::REQPARAM,
		   QgarArgs::INT,
		   "alpha0:",
		   0,
		   "1");

  //
  app.addParameter("-a",
		   QgarArgs::REQPARAM,
		   QgarArgs::INT,
		   "alpha:",
		   0,
		   "2");

  //
  app.addParameter("-b0",
		   QgarArgs::REQPARAM,
		   QgarArgs::INT,
		   "beta0:",
		   0,
		   "1");

  //
  app.addParameter("-b",
		   QgarArgs::REQPARAM,
		   QgarArgs::INT,
		   "beta:",
		   0,
		   "2");

  //
  app.addParameter("-eta",
		   QgarArgs::REQPARAM,
		   QgarArgs::INT,
		   "eta:",
		   0,
		   "0");

  // Size of the square structural element for the final closing
  app.addParameter("-size",
		   QgarArgs::REQPARAM,
		   QgarArgs::INT,
		   "erosion width:",
		   0,
		   "3");

  app.setDescription("Image degadation", QgarArgs::PBM);

  // ANALYZE THE COMMAND LINE
  // ========================

  app.analyzeLine(argc, argv);

  // Error while parsing parameters?
  if (app.isError())
    {
      return app._CODE_ERROR;
    }

  // Application invoked with flag '-gui'?
  if (app.isExit())
    {
      return app._CODE_GUI;
    }

  app.showProgressBar();
  app.setProgressBar(0);

  // GET SOURCE IMAGE
  // ================

  cout << "Loading source image..." << endl; 
 
  PbmFile sourceFile((char*) app.getStringOption("-in"));
  BinaryImage sourceImg = sourceFile.read();

  app.setProgressBar(20);

  // DEGRADE IMAGE
  // =============

  cout << "Image degradation..." << endl; 

  qgKanungoDegradation(sourceImg, 
		       atof(app.getStringOption("-a0")), 
		       atof(app.getStringOption("-a")), 
		       atof(app.getStringOption("-b0")), 
		       atof(app.getStringOption("-b")), 
		       atof(app.getStringOption("-eta")), 
		       atoi(app.getStringOption("-size")));
 
  app.setProgressBar(80);

  // SAVE RESULT
  // ===========

  cout << "Saving degraded image..." << endl;

  PbmFile resultFile((char*) app.getStringOption("-out"));
  resultFile.write(sourceImg);

  app.setProgressBar(100);

  // DISPLAY RESULT
  // ==============

  cout << "Degradation done." << endl;
  app.closeProgressBar();

  app.showPicture((char*) app.getStringOption("-out"));

  // NORMAL TERMINATION
  // ==================

  return app._CODE_END;
}
