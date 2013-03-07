 
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
# @brief Configuration file of Qgar Applications base directory: /Qgar/QgarApps
#
# @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Vitor Vasconcelos">Vitor Vasconcelos</a>
# @date   June 6, 2007  17:22
# @since  Qgar 3.0
#

# Set a project that contains all applications.
# This project only calls CMakeLists.txt from each "son".
PROJECT (QgarApps)

# Define the include directories:
#
# All library files includes a directory one level above, like #include <qgarlib/FILE>. So, we MUST
# include this directory.
# 
# This is done by using the PROJECT_SOURCE_DIR variable, that contais the project directory,
# removing the unwanted directories at the end using with STRING command.
# Then, the new string is included by the INCLUDE_DIRECTORIES command
# Variables are defined in QgarApps CMakeLists and are
# inherited from all ADD_SUBDIRECTORY file

STRING (REGEX REPLACE "QgarApps" "" PROJECT_SOURCE_MAIN ${PROJECT_SOURCE_DIR})
STRING (REGEX REPLACE "QgarApps" "qgarlib" PROJECT_SOURCE_QGARLIB ${PROJECT_SOURCE_DIR})

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_MAIN})

# Since the QgarApps directory is not below qgarlib
# the qgarlibrary name definition is added here
IF(WIN32)
  SET(LIBQGAR_NAME "qgarwin")
ELSE(WIN32)
  SET(LIBQGAR_NAME "qgar")
ENDIF(WIN32)

# The library directory must be included to allow
# targets link with the qgarlib
IF (UNIX)
#    INCLUDE_DIRECTORIES(${PROJECT_SOURCE_QGARLIB})
    LINK_DIRECTORIES(${PROJECT_SOURCE_QGARLIB})
ENDIF (UNIX)

    SET(QGARLIB ${PROJECT_SOURCE_QGARLIB}/${LIBQGAR_NAME})

IF (WIN32)
    STRING (REGEX REPLACE "QgarApps" "qgarlib" LIBQGAR_LOCATION ${PROJECT_BINARY_DIR})
    LINK_DIRECTORIES(${LIBQGAR_LOCATION})
    SET(QGARLIB ${LIBQGAR_LOCATION}/${LIBQGAR_NAME})
ENDIF (WIN32)

# Search for qgarlib in Linux systems
IF (UNIX)
    FIND_LIBRARY (QGARLIB ${LIBQGAR_NAME}
        PATH
	${PROJECT_SOURCE_QGARLIB}
	/usr/lib
	/usr/local/lib 
    )
ENDIF (UNIX)

IF (WIN32)

   # On Windows there are no default directory to libs. We use the QGAR tree structure
   # supposing all plataform are delivered in one package.
   #   STRING (REGEX REPLACE "QgarApps" "qgarlib/Release" LIBQGAR_LOCATION ${PROJECT_BINARY_DIR})

   FIND_LIBRARY (QGARLIB ${LIBQGAR_NAME}
	PATH
	${LIBQGAR_LOCATION}
   )

ENDIF (WIN32)

  IF (QGARLIB)
     SET(QGARLIB_FOUND "Yes")
  ELSE (QGARLIB)
     SET(QGARLIB_FOUND "No")
  ENDIF (QGARLIB)

MESSAGE(STATUS "QGARLIB_FOUND " ${QGARLIB_FOUND})

IF (QGARLIB_FOUND)

  # After all configurations, call the subdirectories
  ADD_SUBDIRECTORY(QAedgesCanny)
  ADD_SUBDIRECTORY(QAedgesDeriche)
  ADD_SUBDIRECTORY(QAdist34Skeletonization)
  ADD_SUBDIRECTORY(QAkanungoDegrade)
  ADD_SUBDIRECTORY(QAmorphoClosing)
  ADD_SUBDIRECTORY(QAmorphoOpening)
  ADD_SUBDIRECTORY(QApruneSmallCC)
  ADD_SUBDIRECTORY(QAtextExtraction)
  ADD_SUBDIRECTORY(QAtextGraphicSeparation)
  ADD_SUBDIRECTORY(QAthickThinSeparation)
  ADD_SUBDIRECTORY(QAthrsBinarization)
  ADD_SUBDIRECTORY(QAtrierBinarization)
  ADD_SUBDIRECTORY(QAvectorizationRW)

ENDIF (QGARLIB_FOUND)	

# Configure the qgarguicfg.xml file with correct files locations
SET(xml_install_dir ${CMAKE_INSTALL_PREFIX}${XML_INSTALL_DIR})
SET(bin_install_dir ${CMAKE_INSTALL_PREFIX}${EXEC_INSTALL_DIR})

# Variables replacement
CONFIGURE_FILE( ${PROJECT_SOURCE_DIR}/qgarguicfg.xml.in 
      	        ${PROJECT_BINARY_DIR}/qgarguicfg.xml
		@ONLY ) 

# Install (copy) the qgarguicfg.xml file in the right directory
INSTALL ( FILES ${PROJECT_BINARY_DIR}/qgarguicfg.xml
	  DESTINATION ${CMAKE_INSTALL_PREFIX}${XML_INSTALL_DIR} )

