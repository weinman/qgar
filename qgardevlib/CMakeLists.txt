 
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
# @brief Configuration file of qgardevlib development library directory: /Qgar/qgardevlib
#
# @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Vitor Vasconcelos">Vitor Vasconcelos</a>
# @date   June 6, 2007  17:22
# @since  Qgar 3.0
#

# Set a project to contain de library file to be generated
PROJECT(qgardevlib)

# Inclusion of all modules needed by this project
INCLUDE (CheckIncludeFiles)
INCLUDE (CheckLibraryExists)

# VARIABLES SECTION
# -------------------------------------------------------------------------
# Brief description of all variables used in this script
#
# ${LIBSOURCE}: List of source files (no .H files are explicitaly include) of qgar library.
# ${PROJECT_SOURCE_ROOT}: Directory one level above qgardevlib.
# ${PROJECT_SOURCE_DIR}: Directory of qgardevlib, automaticaly set by CMake configuration.
# ${CMAKE_SYSTEM_NAME}: CMake variable that contais the name of Operational System.

# All variables are in uppercase and there are no flag 
# to differentiate CMake variables and script created variables

# The command below stores all source files names to a variable
# ${LIBSOURCE} to be used later on

  SET(LIBSOURCE BresenhamLine.cpp BresenhamCircle.cpp)

# Define the include directories:
#
# All library files includes a directory one level above, like #include <qgardevlib/FILE>. So, we MUST
# include this directory.
# 
# This is done by using the PROJECT_SOURCE_DIR variable, that contais the project directory,
# removing the ggarlib directory at the end using with the STRING command.
# Then, the new string is included by the INCLUDE_DIRECTORIES command

STRING (REGEX REPLACE "/qgardevlib" "" PROJECT_SOURCE_ROOT ${PROJECT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_ROOT})

# The line below defines what the project is doing.
# We're generating the qgar library (libqgar) as a static library based on all source files
# The ADD_LIBRARY command allows other types of libraries STATIC, SHARED or MODULE.
#
# The lib prefix is automatically preppended to qgar name.
#
# 
# See CMake documentation to know more about it.
ADD_LIBRARY (qgardev STATIC ${LIBSOURCE})

# Install commands to qgardevlib
# It consists in copy the lib to the correct location
# in the install system.

INSTALL (TARGETS qgardev ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
INSTALL (FILES BresenhamLine.h BresenhamCircle.h
	 DESTINATION ${CMAKE_INSTALL_PREFIX}/include/qgardevlib)

# These commands install the development library in a qgar-x.y.z directory
# to packaging purposes
#INSTALL (TARGETS qgardev ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/${QGAR_NAME_VERSION}/qgardevlib)
#INSTALL (FILES BresenhamLine.h BresenhamCircle.h
#	 DESTINATION ${CMAKE_INSTALL_PREFIX}/${QGAR_NAME_VERSION}/qgardevlib)




