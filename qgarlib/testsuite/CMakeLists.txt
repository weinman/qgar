 
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
# @brief Configuration file of qgarlib testsuite directory: /Qgar/qgarlib/testsuite
#
# @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Vitor Vasconcelos">Vitor Vasconcelos</a>
# @date   June 6, 2007  17:22
# @since  Qgar 3.0
#

# The cppunit lib is not a project. This file is called by Cmake script that builds
# the libqgar.
# It depends on external library [cppunit] that has to be present.
# If it's not found, the testsuite compilation is skipped.
PROJECT(testsuite)

# VARIABLES SECTION
# ------------------------------------------------------
# Brief description of all variables used in this script

# PROJECT variables
# -----------------------------------------------------------------------------------------------------------
# ${TESTSUITE_SOURCES}: List of source files (no .h files are explicitaly include) of qgar testsuite files.
# ${TESTSUITE_FILES}: List of files needed to execute all tests.
# ${PROJECT_SOURCE_ROOT}: Directory of QGAR project (root of qgarlib/testsuite).
# ${PROJECT_SOURCE_DIR}: Directory testsuite, automaticaly set by CMake configuration.
# ${EXECUTABLE_NAME}: Name of executable file to be generated.
# ${TEST_NAME}: Name of the test set to be executed. 

# CPPUNIT Related variables
# ------------------------------------------------------------------------------------------------------------
# ${CPPUNIT_LIB}: Directory and name of cppunit library. This variable is set by the FIND_LIBRARY command.
# ${CPPUNIT_FOUND}: Variable set to TRUE if Cppunit files are found, FALSE otherwise. 
#		    It follows the CMake default behavior of _FOUND variables.
# ${CPPUNIT_INCLUDE_DIRS}: Path of files to be included by the project.
# ${CPPUNIT_DIRECTORY}: On WINDOWS we had to include explicitaly the directory of include files. 
#			It's not simple to find those files in Windows systems, due to the fact that there 
#			are no default instalation directory. So, most of times, the user MUST select 
#			it in CMake GUI configuration on Windows. 
# ${CPPUNIT_INCLUDE_FILES}: Header files of Cppunit used by test source files of qgar testsuite.

# CMAKE variables
# ------------------------------------------------------------------------------------------------------------
# ${WIN32}: Internal CMake variable set to TRUE if the system is WINDOWS.
# ${CMAKE_CONFIGURATION_TYPES}: CMake cache variable. Sets the source to be of a type. We explicitaly set it 
#				to RELEASE in WINDOWS compilation.
# ${CMAKE_CXX_WARNING_LEVEL}: CMake cache variable. Sets the Warning level. The default of our project 
#			      is -Wall on Linux. In WINDOWS it's changed and forced to be /W0.

# ------------------------------------------------------------------------------------------------------------ 
# All variables are in uppercase and there are no flag 
# to differentiate CMake variables and script created variables


SET (TESTSUITE_SOURCES 
    AbstractGenPrimitiveTest.cpp	    GenPointTest.cpp
    AbstractGenQgarPrimitiveTest.cpp  GenPolygonTest.cpp
    BoundingBoxTest.cpp               GenPolylineTest.cpp
    ConnectedComponentsTest.cpp       GenQgarArcTest.cpp
    FreemanChainTest.cpp              GenQgarPolygonTest.cpp
    FreemanCodeTest.cpp               GenQgarPolylineTest.cpp
    GenArcTest.cpp                    GenQgarSegmentTest.cpp
    GenConvexHullTest.cpp             GenSegmentTest.cpp
    GenConvolImageTest.cpp            GenTreeTest.cpp
    GenEdgeGenNodeTest.cpp            GenUGraphTest.cpp
    GenImageTest.cpp                  GlobalFunctionsTest.cpp
    GenKMeansTest.cpp                 HistogramTest.cpp
    GenMask1dTest.cpp		    GenMask2dTest.cpp
    GenPointChainTest.cpp		    unitTester.cpp
)

# The files used by test executable
     SET (TESTSUITE_FILES
	 ConnectedComponentsTest.contours_00.qgar  
	 ConnectedComponentsTest.contours_01.qgar  
	 ConnectedComponentsTest.contours_02.qgar  
	 ConnectedComponentsTest.contours_03.qgar
	 ConnectedComponentsTest.contours_04.qgar  
	 ConnectedComponentsTest.contours_05.qgar  
	 ConnectedComponentsTest.contours_06.qgar
	 ConnectedComponentsTest.contours_07.qgar
	 ConnectedComponentsTest.contours_08.qgar
	 ConnectedComponentsTest.contours_09.qgar
	 ConnectedComponentsTest.contours_10.qgar
	 ConnectedComponentsTest.img_00.pbm
	 ConnectedComponentsTest.img_01.pbm
	 ConnectedComponentsTest.img_02.pbm
	 ConnectedComponentsTest.img_03.pbm
	 ConnectedComponentsTest.img_04.pbm
	 ConnectedComponentsTest.img_05.pbm
	 ConnectedComponentsTest.img_06.pbm
	 ConnectedComponentsTest.img_07.pbm
	 ConnectedComponentsTest.img_08.pbm
	 ConnectedComponentsTest.img_09.pbm
	 ConnectedComponentsTest.img_10.pbm
     )

# Include the ggarlib directory and qgar directory referenced by library
# source files

STRING (REGEX REPLACE "/qgarlib/testsuite" "" PROJECT_SOURCE_ROOT ${PROJECT_SOURCE_DIR})

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_ROOT})

IF (WIN32)
     
  FIND_LIBRARY (CPPUNIT_LIB cppunit
      PATH 
      "C:/Program Files/" 
      "C:/" 
      "C:/Program Files/cppunit-1.12.0/lib"
      "$ENV{ProgramFiles}/cppunit-1.12.0/lib"
      DOC "CppUnit testing framework (http://cppunit.sourcefourge.net)"
  )

  FIND_PATH (CPPUNIT_INCLUDE_DIRS ${CPPUNIT_INCLUDE_FILES}
      "C:/Program Files/"
      "C:/"
      "C:/Program Files/cppunit-1.12.0/include/cppunit"
      "C:/Program Files/cppunit-1.12.0/include"
      "$ENV{ProgramFiles}/cppunit-1.12.0/include"
      "$ENV{ProgramFiles}/cppunit-1.12.0/include/cppunit"
  )

  # Set some project properties to maximum automatization
  IF (CMAKE_BUILD_TOOL MATCHES msdev OR CMAKE_BUILD_TOOL MATCHES devenv)
      SET(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "The tests are built only in RELEASE version" FORCE)
      SET(CMAKE_CXX_WARNING_LEVEL "0" CACHE STRING "No WARNINGS on Windows" )
  ENDIF (CMAKE_BUILD_TOOL MATCHES msdev OR CMAKE_BUILD_TOOL MATCHES devenv)


  # Remove the library name from the path variable to include only the directory
  # to the Windows project
  STRING (REGEX REPLACE "/cppunit.lib" "" CPPUNIT_DIRECTORY ${CPPUNIT_LIB})

  # The line below FORCES the include directory assuming the cppunit include files in a specific directory.
  # This cannot be done to external versions. The user MUST enter it by hand in the CMake interface if the include 
  # directory was not detected
  SET(CPPUNIT_INCLUDE_DIRS "C:/Program Files/cppunit-1.12.0/include" CACHE PATH "Mandatory directory off cppunit INCLUDE files" FORCE)

  # Explicitely includes the directories from cppunit to the project. It is done only in Windows, because in Linux
  # the directories are corrected found and set
  INCLUDE_DIRECTORIES(${CPPUNIT_INCLUDE_DIRS})
  LINK_DIRECTORIES(${CPPUNIT_DIRECTORY})

  #
ENDIF (WIN32)

IF (UNIX)

# All commands in this block are used to find the cppunit lib under Windows

  # This command just create the CPPUNIT_INCLUDE_FILES variable containing
  # the files names to be search for.
  SET (CPPUNIT_INCLUDE_FILES
  HelperMacros.h CompilerOutputter.h TestFactoryRegistry.h TestRunner.h
  )

  # The FIND_LIBRARY command searches the cppunit lib (it's not necessary to include
  # any file extension) in the follow directories as PATHs
  FIND_LIBRARY (CPPUNIT_LIB cppunit
      PATH /usr/local/lib /usr/lib
      DOC "CppUnit testing framework (http://cppunit.sourcefourge.net)"
  )

  # Find the directories where the files (defined in the variable CPPUNIT_INCLUDE_FILES 
  # above and put them in the CPPUNIT_INCLUDE_DIRS. After all they will be used to
  # link the tests executable with these sources
  FIND_PATH (CPPUNIT_INCLUDE_DIRS ${CPPUNIT_INCLUDE_FILES}
      /usr/local/include
      /usr/include
      /usr/local/include/cppunit
      /usr/include/cppunit
      /usr/local/include/cppunit/extensions
      /usr/include/cppunit/extensions
      /usr/local/include/cppunit/ui/text
      /usr/include/cppunit/ui/text
  )

ENDIF (UNIX)

  # If the IF is evaluate to TRUE, the variable CPPUNIT_LIB contains the
  # lib information. Othewise it's blank, and we can perform all workaround
  IF (CPPUNIT_LIB)
     SET(CPPUNIT_FOUND "Yes")
  ELSE (CPPUNIT_LIB)
     SET(CPPUNIT_FOUND "No")
  ENDIF (CPPUNIT_LIB)

  # Until version 1.12.0, cppunit is not compatible with MingW in Windows. So, we desable 
  # all tests if using MingW. The lines below verify if the build tool
  # is mingW.
  STRING (TOUPPER ${CMAKE_BUILD_TOOL} MINGW_TOOL)
  STRING (REGEX MATCH "MINGW" IS_MINGW_EMPTY ${MINGW_TOOL})

  IF(NOT IS_MINGW_EMPTY)
  # ----------------------------------------------------------------------------------
  # Quit Cppunit execution
  # ----------------------------------------------------------------------------------

IF (CPPUNIT_FOUND)

  # Building files
  SET(EXECUTABLE_NAME "unitTester")
  ADD_EXECUTABLE (${EXECUTABLE_NAME} ${TESTSUITE_SOURCES})

  # The qgarlib MUST be included here, of course. This CMakeFile.txt
  # file MUST be executed by the one of library directory. There is no 
  # sense in test the library without build it.
  TARGET_LINK_LIBRARIES (${EXECUTABLE_NAME} cppunit ${LIBQGAR_NAME}) 

  # The tests are started
  # It's possible to chose an install directory. This will be tried later...

  # It's possible to write tests directly, but by the moment, we just need to execute
  # the unitTester file and verify the results.

  # Chose the test's name - we can have as many as we wish
  # Realy create the test that will be performed - called by CTest tool.
  SET (TEST_NAME "unitTester")

  # ATTENTION
  #
  # On Windows, the binary directory can be chosen by user. So we MUST copy the files
  # needed by tests to testsuite directory. We use the PROJECT_BINARY_DIR appended with
  # testsuite string to copy files.
  # The code below will copy the .pbm and .qgar files to testsuite directory. It will
  # make RUN_TESTS inside Visual Studio project locate files and properly execute tests

  # Convertion from Unix style path to Windows path
  FILE(TO_NATIVE_PATH ${PROJECT_SOURCE_DIR} TESTSUITE_SOURCE_DIR_WINDOWS)
  FILE(TO_NATIVE_PATH ${PROJECT_BINARY_DIR} TESTSUITE_BINARY_DIR_WINDOWS)

  # Tests are not installed, but only executed.

  FOREACH(FILE ${TESTSUITE_FILES})
  # Copy all files needed to test
  # The ${FILE} variable has it's scope only inside the loop
  EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy 
		     ${TESTSUITE_SOURCE_DIR_WINDOWS}/${FILE} 
		     ${TESTSUITE_BINARY_DIR_WINDOWS}/${FILE} )

  IF(WIN32)
#      EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy 
#		     ${TESTSUITE_SOURCE_DIR_WINDOWS}\\testsuite\\${FILE} 
#		     ${TESTSUITE_BINARY_DIR_WINDOWS}\\testsuite\\${FILE} )
  ENDIF(WIN32)

  ENDFOREACH(FILE ${TESTSUITE_FILES})

  ADD_TEST (${TEST_NAME} ${EXECUTABLE_NAME})

  # -----------------------------------------------------------------
  # 
  # INSTALL
  #
  # -----------------------------------------------------------------

  # The commands below copy all targets in a directory qgar-x.y.z
  # they're not include by default, but only for packaging purposes
  #INSTALL(FILES ${TESTSUITE_SOURCES} ${TESTSUITE_FILES} DESTINATION ${QGAR_NAME_VERSION}/qgarlib/testsuite)
  #INSTALL(TARGETS ${EXECUTABLE_NAME} RUNTIME DESTINATION ${QGAR_NAME_VERSION}/qgarlib/testsuite)

ELSE (CPPUNIT_FOUND)

  MESSAGE( STATUS "cppunit library not found. The unit tests cannot be
  included in this build.")

ENDIF (CPPUNIT_FOUND)

# --------------------------------------------------------------------------------
# Nothing happens if we have Mingw Compiler
ENDIF(NOT IS_MINGW_EMPTY)


