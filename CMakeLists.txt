 
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
# @brief Configuration file of main Qgar directory: /Qgar
#
# @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Vitor Vasconcelos">Vitor Vasconcelos</a>
# @date   June 6, 2007  17:22
# @since  Qgar 3.0
#

# CMake 2.6.0 forces to explicitly define the minimum
# working version to the project
CMAKE_MINIMUM_REQUIRED(VERSION 2.4.7)

# Set a project to contain de library file to be generated
PROJECT(Qgar)

# A variable with the last version
# NOTE: Due to directory structure, the variable replacement
# is not performed in Doxygen.in file. It must be set inside it.
# Check QgarDoc CmakeLists.txt.
#
# EXAMPLES
# USE: QGAR_NAME_VERSION: qgar-4.0.0
#      QGAR_VERSION: 4.0.0 
#
#      QGAR_MAJOR: 4
#      QGAR_MINOR: 0
#      QGAR_PATCH: 0
#
# Only modify the number variables and QGAR_NAME_VERSION and 
# QGAR_VERSION are automaticaly assembled.
#
SET(QGAR_MAJOR 4)
SET(QGAR_MINOR 0)
SET(QGAR_PATCH 0)
SET(QGAR_VERSION ${QGAR_MAJOR}.${QGAR_MINOR}.${QGAR_PATCH})
SET(QGAR_NAME_VERSION qgar-${QGAR_VERSION})

# Set two variables, with Qgar Source and Qgar Binary directories
# They will be inehrited and used in the Qgar build tree
SET(${DEFAULT_QGAR_SOURCE_DIR} ${PROJECT_SOURCE_DIR})
SET(${DEFAULT_QGAR_BINARY_DIR} ${PROJECT_BINARY_DIR})

# Shows the plataform being used
MESSAGE(STATUS "Qgar running on... " ${CMAKE_SYSTEM_NAME})

# --------------------------------------------------------------------
#
# VARIABLES
#
#---------------------------------------------------------------------

# The variables defined below constrols the installation 
# directories. They're used in "make install" command. It's important 
# note that the packages install (RPM, debian, etc) calls the same 
# command in it's install process.
# It's not used in Windows build.

# The value of those variables are appended to the CMAKE_INSTALL_PREFIX
# that defines by default /usr/local as install directory.

# -------------
# LIBS
# -------------
# The libqgar and libqgardev will be installed in the directory below
SET (LIB_INSTALL_DIR /lib)

# ------------------
# INCLUDE
# ------------------
# The .h files will be put in the directory below
# WARNING: the qgarlib path is mandatory, so the 
# Install rule in its CMakeLists file does it.
SET (INCLUDE_INSTALL_DIR /include)

# ------------------
# BINARY
# ------------------
# Executables
# Installed phisically in /lib but symbolic links to /bin
SET (EXEC_INSTALL_DIR /bin)

# ------------------
# SOURCES
# ------------------
# Sources
SET (SRC_INSTALL_DIR /doc/qgar/src)

# ------------------
# DOCUMENTATION
# ------------------
# Documentation source
SET (DOC_INSTALL_DIR /doc/qgar/html)

# ------------------
# XML
# ------------------
# XML Applications description files
SET (XML_INSTALL_DIR /share/qgar)

# General project configuration are done here.
# They should be inherited, but it's not applying
# to Visual Studio configuration.
IF (WIN32)

  # Set some project properties to maximum automatization
  # WARNING: The configuration type only works for make based generators.
  # In Visual Studio, we must set it by hand.

  # If the compiler is g++, we don't set the warning level to zero.
  # Only for Visual Studio project.
  STRING (REGEX MATCH "g\\+\\+" COMPILER_GCC ${CMAKE_CXX_COMPILER})
  IF (NOT COMPILER_GCC) 
    SET(CMAKE_CXX_WARNING_LEVEL "0" CACHE STRING "No WARNINGS on Windows" FORCE)
  ENDIF (NOT COMPILER_GCC)

ENDIF(WIN32)

# This command MUST be in root directory source
ENABLE_TESTING()

# Calls all project subdirectories
ADD_SUBDIRECTORY(qgarlib)
ADD_SUBDIRECTORY(qgardevlib)
ADD_SUBDIRECTORY(QgarApps)
ADD_SUBDIRECTORY(QgarDoc)
ADD_SUBDIRECTORY(QgarGui)

# Uninstall procedure
#
# It's used only in Linux makefiles. Used to remove automatically 
# all installed files. Used by Debian packages and available to 
# be used as any make "command".

#ADD_CUSTOM_TARGET(uninstall COMMAND rm -f ${CMAKE_INSTALL_PREFIX}/lib/*qgar*
#			    COMMAND echo ${CMAKE_INSTALL_PREFIX}"/lib... cleaned."
#			     COMMAND rm -rf ${CMAKE_INSTALL_PREFIX}/share/qgar/QA*_descr.xml
#			    COMMAND echo ${CMAKE_INSTALL_PREFIX}"/share/xml files... cleaned."
#			     COMMAND rm -f ${CMAKE_INSTALL_PREFIX}/bin/QA*
#			    COMMAND echo ${CMAKE_INSTALL_PREFIX}"/bin... cleaned."
#			     COMMAND rm -rf ${CMAKE_INSTALL_PREFIX}/include/qgar*
#			    COMMAND echo ${CMAKE_INSTALL_PREFIX}"/include... cleaned.")


# --------------------------------------------------------------------
#
# CPACK CONFIGURATION
#
#---------------------------------------------------------------------

# Set a variable used to ignore non-package file
SET(COMMON_IGNORE_FILES '/CMakeFiles/' '/.svn/' '_CPack_Packages/' 
    '.cmake$' '~' '.swp' '.log' '.gz' '.directory$' 'CMakeCache.txt')

IF(WIN32)
    SET(CPACK_GENERATOR "NSIS")
ELSE(WIN32)
    SET(CPACK_GENERATOR "STGZ")
ENDIF(WIN32)

SET(CPACK_PACKAGE_INSTALL_DIRECTORY "Qgar")
#${PROJECT_NAME})
SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY ${QGAR_NAME_VERSION})
#${PACKAGE_VERSION})
SET(CPACK_PACKAGE_NAME 	"Qgar")
SET(CPACK_PACKAGE_VENDOR "Qgar Development Team")
SET(CPACK_PACKAGE_VERSION_MAJOR "4")
SET(CPACK_PACKAGE_VERSION_MINOR "0")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
SET(CPACK_SOURCE_GENERATOR "TGZ;ZIP")
SET(CPACK_SOURCE_IGNORE_FILES ${COMMON_IGNORE_FILES})
SET(CPACK_SOURCE_PACKAGE_FILE_NAME ${QGAR_NAME_VERSION})
# SET(CPACK_SOURCE_STRIP_FILES) ?
# SET(CPACK_STRIP_FILES) ?
SET(CPACK_SYSTEM_NAME ${CMAKE_SYSTEM_NAME})
SET(CPACK_RESOURCE_FILE_LICENSE ${PROJECT_SOURCE_DIR}/LICENSE_QPL_LGPL.txt)
SET(CPACK_PACKAGE_VERSION ${QGAR_VERSION})
#${PACKAGE_VERSION})

INCLUDE(CPack)


# --------------------------------------------------------------------
#
# EXTERNAL MODULES
#
#---------------------------------------------------------------------

# The modules DpkgDeb and Rpmbuild are external modules download from
# Cycab project (https://gforge.inria.fr/projects/cycabtk/). They allow
# the generation of Debian packages if the "dpkg" command is available 
# and RPM packages if "rpmbuild" is available.


# Package generation

# ----------------------------------------------------------------------
#
# DEBIAN
#
# ----------------------------------------------------------------------

INCLUDE ( cmake_adds/Dpkg-deb2.cmake )

# Install location
#
# This variable defines the directory where the package will be installed
# by default: /usr/local

SET(DEBIAN_INSTALL_PREFIX "/usr/local" CACHE PATH "Debian package base location")

set ( PACKAGE_NAME ${PROJECT_NAME} )
set ( PACKAGE_VERSION ${QGAR_VERSION} )
set ( PACKAGE_RELEASE 1 )
set ( PACKAGE_MAINTAINER_NAME "Project Qgar" )
set ( PACKAGE_MAINTAINER_EMAIL "qgar-develop@loria.fr" )
set ( PACKAGE_DESCRIPTION "The Qgar software system is aimed at the design of document analysis applications and is currently developed inside the QGAR Project at LORIA, France." )
set ( PACKAGE_DESCRIPTION_SUMMARY "Qgar library and applications" )
set ( PACKAGE_DEPENDS "libqt4-gui" )

SET (QGAR_BASE_DIR ${CMAKE_BINARY_DIR})
MESSAGE (STATUS ${QGAR_BASE_DIR})

if ( DPKG_FOUND )
   # This command can only be called if the CMAKE_INSTALL_PREFIX is /usr/local /usr
   # This constraint is due to third party script which calls 'make install'.
   # Otherwise, a debian package installing in home directories would be generated
   IF ( CMAKE_INSTALL_PREFIX MATCHES "/usr/local" OR 
        CMAKE_INSTALL_PREFIX MATCHES	"/usr")
	   add_debian_package ( ${PROJECT_NAME} )
   ENDIF ( CMAKE_INSTALL_PREFIX MATCHES "/usr/local" OR 
        CMAKE_INSTALL_PREFIX MATCHES	"/usr")
endif ( DPKG_FOUND )

# ----------------------------------------------------------------------
#
# RPM packages
#
# ----------------------------------------------------------------------
INCLUDE ( cmake_adds/Rpmbuild.cmake )

# RPM - variables included to the former list
# Install location
#
# This variable defines the directory where the package will be installed
# by default: /usr/local

SET(${RPM_INSTALL_PREFIX} /usr/local TYPE PATH DOCSTRING "RPM package base location"})

set ( PACKAGE_GROUP "Development/Libraries" )

set ( PACKAGE_GROUP "Multimidia" )
set ( PACKAGE_LICENSE "LGPL and QPL" )
set ( PACKAGE_DEPENDENCY "qt4" )
set ( PACKAGE_DEPENDENCY_VERSION "4.0" )

if ( RPMBUILD_FOUND )
   # This command can only be called if the CMAKE_INSTALL_PREFIX is /usr/local /usr
   # This constraint is due to third party script which calls 'make install'.
   # Otherwise, a debian package installing in home directories would be generated
   IF ( CMAKE_INSTALL_PREFIX MATCHES "/usr/local" OR 
        CMAKE_INSTALL_PREFIX MATCHES "/usr" )

	   add_rpm ( ${PROJECT_NAME} )

   ENDIF ( CMAKE_INSTALL_PREFIX MATCHES "/usr/local" OR 
           CMAKE_INSTALL_PREFIX MATCHES	"/usr" )
endif ( RPMBUILD_FOUND )


# --------------------------------------------------------------------
#
# INSTALL Configuration
#
# --------------------------------------------------------------------

INCLUDE(InstallRequiredSystemLibraries)

# All files at the main directory will be copied to
# version named directory
#INSTALL ( FILES README LICENSE_QPL_LGPL.txt changelog.html AUTHORS NEWS CMakeLists.txt
#	 DESTINATION ${QGAR_NAME_VERSION} )

