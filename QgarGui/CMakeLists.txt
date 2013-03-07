 
#######################################################################
# Library QgarLib, graphics analysis and recognition                  #
# Copyright (C) 2002  Qgar Project, LORIA                             #
#                                                                     #
# This library is free software; you can redistribute it and/or       #
# modify it under the terms of the GNU Lesser General Public          #
# License version 2.1, as published by the Free Software Foundation.  #
#                                                                     #
# This library is distributed in the hope that it will be useful,     #
# but WITHOUT ANY WARRANTY; without even the implied warranty of      #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                #
# See the GNU Lesser General Public License for more details.         #
#                                                                     #
# The GNU Lesser General Public License is included in the file       #
# LICENSE.LGPL, in the root directory of the Qgar packaging. See      #
# http://www.gnu.org/licenses/lgpl.html for the terms of the licence. #
# To receive a paper copy, write to the Free Software Foundation,     #
# Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.       #
#                                                                     #
# Contact Project Qgar for any information:                           #
#   LORIA - équipe Qgar                                               #
#   B.P. 239, 54506 Vandoeuvre-lès-Nancy Cedex, France                #
#   email: qgar-contact@loria.fr                                      #
#   http://www.qgar.org/                                              #
#######################################################################



# @file CMakiLists.txt
# 
# @brief Configuration file of Qgar Graphical User Interface directory: /Qgar/QgarGui
#
# @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Vitor Vasconcelos">Vitor Vasconcelos</a>
# @date   October 20, 2008  20:57
# @since  Qgar 4.0
#

CMAKE_MINIMUM_REQUIRED(VERSION 2.4.7)

PROJECT(QgarGui)

INCLUDE ( CheckIncludeFiles ) 
INCLUDE ( CheckLibraryExists )

FIND_PACKAGE ( Qt4 )
   
ADD_DEFINITIONS (-DQT_STATIC)
   
INCLUDE_DIRECTORIES ( ${QT_INCLUDE_DIR} )
INCLUDE_DIRECTORIES ( ${QT_QTCORE_INCLUDE_DIR} )
INCLUDE_DIRECTORIES ( ${QT_QTGUI_INCLUDE_DIR} )
INCLUDE_DIRECTORIES ( ${QT_QTXML_INCLUDE_DIR} )

# Include de directory Qgar
# equivalent to use -I../ with g++
INCLUDE_DIRECTORIES ( "../" )

LINK_DIRECTORIES ( ${QT_LIBRARY_DIR} )

# Configuration the scripts to execute Qgar
SET(install_prefix ${CMAKE_INSTALL_PREFIX})
SET(install_xml ${XML_INSTALL_DIR})
SET(install_bin ${EXEC_INSTALL_DIR})

IF(WIN32)
    CONFIGURE_FILE( ${PPOJECT_SOURCE_DIR}qgarwin.bat.in 
                    ${PROJECT_BINARY_DIR}/qgarwin.bat
		    @ ONLY)
ELSE(WIN32)
    CONFIGURE_FILE( ${PPOJECT_SOURCE_DIR}qgar.in
                    ${PROJECT_BINARY_DIR}/qgar
		    @ ONLY)
ENDIF(WIN32)


MESSAGE(STATUS "Project : " ${PROJECT_SOURCE_DIR}${QGARGUICFG_WIN})

SET ( GUI_SOURCES
       QGAbstractLayer.cpp
       QGDocViewer.cpp
       QGImageLoader.cpp
       QGMainWindow.cpp
       QGMainWindowSubjectIf.cpp
       QGMultiLayerDoc.cpp
       QGPixmapLayer.cpp
       QGMenu.cpp
       QGFileMenu.cpp
       QGRecentFileMenu.cpp
       QGAbstractMainWindowCommand.cpp
       QGOpenImageCommand.cpp
       QGCloseImageCommand.cpp
       QGEditMenu.cpp
       QGZoomCommand.cpp
       QGCommandToolBar.cpp
       QGMainToolBar.cpp
       QGUndoList.cpp
       QGMainToolsToolBar.cpp
       QGMouseTracker.cpp
       QGSIModeCommand.cpp
       QGHelpMenu.cpp
       QGShowAboutCommand.cpp
       QGAboutDialog.cpp
       QGOptionMenu.cpp
       QGStyleMenu.cpp
       QGViewMenu.cpp
       QGImageMenu.cpp
       QGAlgoMenuFactory.cpp
       QGApplicationEntry.cpp
       QGAppRegister.cpp
       QGLaunchBatchCommand.cpp
       QGAppDialogMediator.cpp       
       QGAbstractAppParamInput.cpp       
       QGAppCmdLinePanel.cpp
       QGAppParamPanel.cpp
       QGAppParamInputFile.cpp
       QGAppParamInputInt.cpp
       QGAppParamInputReal.cpp
       QGAppParamInputUnknown.cpp
       QGAppDescrPanel.cpp
       QGAppLauncher.cpp
       QGAppTracker.cpp
       QGAlgoMenu.cpp
       QGVectorialLayer.cpp
       QGVectItem.cpp
       QGDxfLayer.cpp   
       QGDxfFile.cpp
       QGCanvasEllipse.cpp
       QGCanvasLine.cpp
       QGCanvasPolyline.cpp
       QGCanvasRectangle.cpp
       QGVectUtilityBar.cpp
       QGSkelModeCommand.cpp
       QGInfoWindowCommand.cpp
       QGInfoWindow.cpp
       QGUtilityBarFactory.cpp
       QGAbstractDocViewerInteractor.cpp
       QGSetInteractorCommand.cpp
       QGSwapImagesCommand.cpp
       QGScribbleInteractor.cpp
       QGMoveToInteractor.cpp
       QGInfoLayer.cpp
       QGHelpers.cpp
       QGPixmapInteractorBar.cpp
       QGEllipseDrawerInteractor.cpp
       QGInsertVectItemCommand.cpp
       QGLineDrawerInteractor.cpp
       QGDeleteVectItemCommand.cpp
       QGMoveVectItemCommand.cpp
       QGModifyInteractor.cpp
       QGPolylineDrawerInteractor.cpp
       QGSvgLayer.cpp
       QGar.cpp
       QGSwitchVectItemCommand.cpp
       QGVectInteractorBar.cpp
       QGInteractorBarFactory.cpp)

       INCLUDE_DIRECTORIES ( ${PROJECT_SOURCE_DIR} )

   SET ( QT_EXECUTABLE_NAME "QgarGui" )
   ADD_EXECUTABLE ( ${QT_EXECUTABLE_NAME} ${GUI_SOURCES} )

IF(WIN32)
# Set aditional link libraries to MinGW Windows
    SET(LIBQGAR_NAME "qgarwin")
    SET(MINGW32_LIBS uuid ole32 ws2_32 
    gdi32 comdlg32 oleaut32 imm32 winmm winspool user32 advapi32
    shell32 comdlg32 mingw32 qtmain)
ELSE(WIN32)
    SET(LIBQGAR_NAME "qgar")
ENDIF(WIN32)

SET(QGARLIB ${PROJECT_SOURCE_QGARLIB}${LIBQGAR_NAME})

FIND_LIBRARY(QGARLIB ${LIBQGAR_NAME}
	${PROJECT_SOURCE_QGARLIB}
	NO_DEFAULT_PATH
	NO_SYSTEM_ENVIRONMENT_PATH
	)


TARGET_LINK_LIBRARIES ( ${QT_EXECUTABLE_NAME}
		      ${QGARLIB}
		      ${QT_QTCORE_LIBRARY} 
		      ${QT_QTGUI_LIBRARY} 
		      ${QT_QTXML_LIBRARY}
		      ${MINGW32_LIBS}
		      )

# Install files
INSTALL (TARGETS ${QT_EXECUTABLE_NAME} RUNTIME 
	DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

IF(WIN32)
    INSTALL ( FILES ${PROJECT_BINARY_DIR}/qgarwin.bat
	     DESTINATION ${CMAKE_INSTALL_PREFIX}${EXEC_INSTALL_DIR}
	     PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ
			 GROUP_EXECUTE WORLD_READ WORLD_EXECUTE )
ELSE(WIN32)
    INSTALL ( FILES ${PROJECT_BINARY_DIR}/qgar
	     DESTINATION ${CMAKE_INSTALL_PREFIX}${EXEC_INSTALL_DIR}
	     PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ
			 GROUP_EXECUTE WORLD_READ WORLD_EXECUTE )
ENDIF(WIN32)
