 
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
# @brief Configuration file of QgarDoc directory: /Qgar/QgarDoc
#
# @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Vitor Vasconcelos">Vitor Vasconcelos</a>
# @date   June 6, 2007  17:22
# @since  Qgar 3.0
#
#

# Set a project. It defines PROJECT_SOURCE_DIR and PROJECT_BINARY_DIR
PROJECT(Doc)

# ---------------------------------------------------------------------------------------
# VARIABLES LIST
#
# ${qgar_version}: This variable MUST be set to the qgar doc version being build.
#		   It's value is write in each doc file (xml or doxygen files) before
#		   the process that uses them.
# ${WIN32}: 
# ${DOXYGEN_FOUND): Relate to doxygen

# ATENTION!
#
# Due to a bug - version 2.4 - CMake FIND_PACKAGE script for Doxygen, is not available
# in Linux. So, we do a little workaround here.
IF (WIN32)
   FIND_PACKAGE(Doxygen)
ELSE (WIN32)
   FIND_PATH(DOXYGEN_PATH doxygen
    /usr/local/bin
    /usr/bin
   )
   
   IF(DOXYGEN_PATH)
       SET(DOXYGEN_FOUND "Yes")
   ENDIF(DOXYGEN_PATH)

ENDIF (WIN32)


# Try to find the "jw" script to generate docbook entries.
# This method must be implemented in a Windows version
FIND_FILE(DOCBOOK jw /usr/bin /usr/local/bin
	      DOC "Docbook perl script.")

IF(DOCBOOK)
    SET(DOCBOOK_FOUND "Yes")
ELSE(DOCBOOK)
    SET(DOCBOOK_FOUND "No")
ENDIF(DOCBOOK)

# The execution of Doxygen is performed AFTER the generation of the library
IF (DOXYGEN_FOUND)

    # The ideia it to keep the directory structure between parts
    # of Qgar (lib, apps and gui) and generate all documentation 
    # from here.
    #
    # This script is tied to directory structure of all QGAR's doc tree
    # QgarDoc -> QgarApps
    #         -> qgarlib
    #         -> QgarGui
    #
    STRING (REGEX REPLACE "/QgarDoc" "" QGAR_SOURCE_DIR ${PROJECT_SOURCE_DIR})
	
    # DOXYGEN Section ##########################################################################
    #
    # - Doxygen files configuration;
    # - Doxygen execution to generate doc
    #
    # Obs.: On Windows doxygen default installation is unable to generate
    # any file from latex files.


    # Set the variables needed by Doxyfile and substitute it 
    # in the correct file. 

    # VERSION TEST
    SET(qgar_version ${QGAR_VERSION})
    SET(top_srcdir ${QGAR_SOURCE_DIR})

    # leftMenu.html version substitution
    CONFIGURE_FILE (${PROJECT_SOURCE_DIR}/src/main/leftMenu.html.in
		   ${PROJECT_SOURCE_DIR}/src/main/leftMenu.html
		   @ONLY)

    # qgarlib - Replace
    CONFIGURE_FILE (${PROJECT_SOURCE_DIR}/src/api/qgarlib/Doxyfile.in
	        ${PROJECT_SOURCE_DIR}/src/api/qgarlib/Doxyfile
		@ONLY)

    # WARNING 
    # The file is created but it's not invoked.
    # Points to be discussed;
    # - the both versions to lib doc will co-exist?
    # - if yes, how to chose different directories?
    # qgarlib - Replace
    CONFIGURE_FILE (${PROJECT_SOURCE_DIR}/src/api/qgarlib/Doxyfile-clientdoc.in
		   ${PROJECT_SOURCE_DIR}/src/api/qgarlib/Doxyfile-clientdoc
		   @ONLY)

    # QgarApp - Replace
    CONFIGURE_FILE (${PROJECT_SOURCE_DIR}/src/api/qgarapps/Doxyfile.in
		   ${PROJECT_SOURCE_DIR}/src/api/qgarapps/Doxyfile
		   @ONLY)
	
    # QgarGui - Replace
    CONFIGURE_FILE (${PROJECT_SOURCE_DIR}/src/api/qgargui/Doxyfile.in
    		   ${PROJECT_SOURCE_DIR}/src/api/qgargui/Doxyfile
    		   @ONLY)

    # DOCBOOK SECTION ##################################################################################
    #
    #
    
    # For each part of doc, we execute the command separetedely.
    # Compilation Guide
    
    IF(DOCBOOK_FOUND)

	# Compilation Guide
	#############################################################################################################
	# HTML Generation
	SET(args_compilation "-f" "docbook" "-b" "html" "-o" "${PROJECT_SOURCE_DIR}/Guides/Compilation" "-d" 
			       "${PROJECT_SOURCE_DIR}/DocSources_3-0/Guides/Compilation/compilationGuide.dsl#html" 
			       	 "${PROJECT_SOURCE_DIR}/DocSources_3-0/Guides/Compilation/compilationGuide.xml")

	# PDF Generation
#        EXECUTE_PROCESS(COMMAND jw -f docbook -b pdf 
#				-o ${PROJECT_SOURCE_DIR}/Guides/Compilation
#				-d ${PROJECT_SOURCE_DIR}/DocSources_3-0/Guides/Compilation/compilationGuide.dsl#print 
#				${PROJECT_SOURCE_DIR}/DocSources_3-0/Guides/Compilation/compilationGuide.xml)
	SET(args_compilation_pdf "-f" "docbook" "-b" "pdf" "-o" "${PROJECT_SOURCE_DIR}/Guides/Compilation" "-d" 
			       "${PROJECT_SOURCE_DIR}/DocSources_3-0/Guides/Compilation/compilationGuide.dsl#print" 
			       	 "${PROJECT_SOURCE_DIR}/DocSources_3-0/Guides/Compilation/compilationGuide.xml")

	# src/main
	CONFIGURE_FILE (${PROJECT_SOURCE_DIR}/src/main/main.xml.in
	        ${PROJECT_SOURCE_DIR}/src/main/main.xml
		@ONLY)

	# src/design
	CONFIGURE_FILE (${PROJECT_SOURCE_DIR}/src/design/qgarAppsDesign.xml.in
	        ${PROJECT_SOURCE_DIR}/src/design/qgarAppsDesign.xml
		@ONLY)
		
	# src/developer
	# src/developer/codingstandards
	CONFIGURE_FILE (${PROJECT_SOURCE_DIR}/src/developer/codingstandards/codingStandards.xml.in
	        ${PROJECT_SOURCE_DIR}/src/developer/codingstandards/codingStandards.xml
		@ONLY)

	# src/developer/codingstandardsabstract
	CONFIGURE_FILE (${PROJECT_SOURCE_DIR}/src/developer/codingstandardsabstract/codingStandardsAbstract.xml.in
	        ${PROJECT_SOURCE_DIR}/src/developer/codingstandardsabstract/codingStandardsAbstract.xml
		@ONLY)

	# src/developer/xemacs
	CONFIGURE_FILE (${PROJECT_SOURCE_DIR}/src/developer/xemacs/Xemacs.xml.in
	        ${PROJECT_SOURCE_DIR}/src/developer/xemacs/Xemacs.xml
		@ONLY)

	# src/developer/pkg
	CONFIGURE_FILE (${PROJECT_SOURCE_DIR}/src/developer/pkg/packagingGuide.xml.in
	        ${PROJECT_SOURCE_DIR}/src/developer/pkg/packagingGuide.xml
		@ONLY)

	#src/installation
	#src/installation/installation/installGuide
	CONFIGURE_FILE (${PROJECT_SOURCE_DIR}/src/installation/installation/installGuide.xml.in
	        ${PROJECT_SOURCE_DIR}/src/installation/installation/installGuide.xml
		@ONLY)

	#src/installation/installation/installWindows
	CONFIGURE_FILE (${PROJECT_SOURCE_DIR}/src/installation/installation/installWindows.xml.in
	        ${PROJECT_SOURCE_DIR}/src/installation/installation/installWindows.xml
		@ONLY)

	#src/installation/compilation
	CONFIGURE_FILE (${PROJECT_SOURCE_DIR}/src/installation/compilation/compilationGuide.xml.in
	        ${PROJECT_SOURCE_DIR}/src/installation/compilation/compilationGuide.xml
		@ONLY)

	#src/bibliography
	CONFIGURE_FILE (${PROJECT_SOURCE_DIR}/src/bibliography/bibliography.xml.in
	        ${PROJECT_SOURCE_DIR}/src/bibliography/bibliography.xml
		@ONLY)



# EXAMPLES #####################################################################################################
	SET(args_install "-f" "docbook" "-b" "html" "-o" "${PROJECT_SOURCE_DIR}/Guides/Install" "-d" 
			 "${PROJECT_SOURCE_DIR}/DocSources_3-0/Guides/Install/installGuide.dsl#html" 
			 "${PROJECT_SOURCE_DIR}/DocSources_3-0/Guides/Install/installGuide.xml")

	# PDF Generation
	SET(args_install_pdf "-f" "docbook" "-b" "pdf" "-o" "${PROJECT_SOURCE_DIR}/Guides/Install" "-d" 
			 "${PROJECT_SOURCE_DIR}/DocSources_3-0/Guides/Install/installGuide.dsl#print" 
			 "${PROJECT_SOURCE_DIR}/DocSources_3-0/Guides/Install/installGuide.xml")
# EXAMPLES #####################################################################################################



    ELSE(DOCBOOK_FOUND)
        MESSAGE(STATUS ${DOCBOOK} " docbook not available.")
    ENDIF(DOCBOOK_FOUND)

ELSE (DOXYGEN_FOUND)
    MESSAGE("Doxygen not found, documentation cannot be generated.")

ENDIF (DOXYGEN_FOUND)

# Try to create "make doc" command
#ADD_CUSTOM_TARGET(doc ALL
#                  COMMAND echo "doc"
#		  COMMAND jw -f docbook -b pdf 
#				-o ${PROJECT_SOURCE_DIR}/Guides/Install
#				-d ${PROJECT_SOURCE_DIR}/DocSources_3-0/Guides/Install/installGuide.dsl#print 
#				${PROJECT_SOURCE_DIR}/DocSources_3-0/Guides/Install/installGuide.xml
#                  COMMENT "Generate the documentation")


# ------------------------------------------------------------------------------------------

# All commands have their arguments stored on one variable. This is done to use the
# custom targets to build all documentation.
# The FIRST choice is:
#
# make doc = builds ALL doc sources.
# make doc-doxygen = builds only doxygen related files, i.e., API documentation.
# make doc-docbook = builds only docbook related files, i.e., Qgar website documentation.
# make doc-pdf = builds only docbook relate files but in pdf format. (*)
#
# -------------------------------------------------------------------------------------------
# IMPORTANT:
#
# The custom commands will be available only if the related tool (docbook and/or doxygen) 
# is also available.
#
# Works, but I can create the directories only when building
FILE(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/html/api/qgarlib)

# The commands are different in Windows and Linux, because the SO command calls
# On Windows, only the "make doc" version is available.
IF (WIN32 AND DOXYGEN_FOUND)
   ADD_CUSTOM_TARGET(doc COMMAND mkdir ./html/api/qgarlib
			 COMMAND doxygen ${PROJECT_SOURCE_DIR}/src/api/qgarlib/Doxyfile 
			 COMMAND mkdir ./html/api/qgarapps
			 COMMAND doxygen ${PROJECT_SOURCE_DIR}/src/api/qgarapps/Doxyfile 
			 COMMAND mkdir ./html/api/qgargui
			 COMMAND doxygen ${PROJECT_SOURCE_DIR}/src/api/qgargui/Doxyfile 
)
ENDIF (WIN32 AND DOXYGEN_FOUND)

IF (UNIX AND DOXYGEN_FOUND)
   ADD_CUSTOM_TARGET(doc-doxygen COMMAND mkdir -p html/api/qgarlib
				 COMMAND doxygen ${PROJECT_SOURCE_DIR}/src/api/qgarlib/Doxyfile 
				 COMMAND mkdir -p html/api/qgarapps
				 COMMAND doxygen ${PROJECT_SOURCE_DIR}/src/api/qgarapps/Doxyfile 
				 COMMAND mkdir -p html/api/qgargui
				 COMMAND doxygen ${PROJECT_SOURCE_DIR}/src/api/qgargui/Doxyfile 
)
ENDIF (UNIX AND DOXYGEN_FOUND)

# doc-docbook files
IF (UNIX AND DOCBOOK_FOUND)

   SET(ARGS_MAIN "-f" "docbook" "-b" "html" "-o" "${PROJECT_SOURCE_DIR}/html/main" "-d" 
		 "${PROJECT_SOURCE_DIR}/src/main/main.dsl#html" 
		 "${PROJECT_SOURCE_DIR}/src/main/main.xml")

   SET(ARGS_DESIGN "-f" "docbook" "-b" "html" "-o" "${PROJECT_SOURCE_DIR}/html/design" "-d" 
		 "${PROJECT_SOURCE_DIR}/src/design/qgarAppsDesign.dsl#html" 
		 "${PROJECT_SOURCE_DIR}/src/design/qgarAppsDesign.xml")

   SET(ARGS_DEVELOPER_CODINGSTD "-f" "docbook" "-b" "html" "-o" "${PROJECT_SOURCE_DIR}/html/developer" "-d" 
		 "${PROJECT_SOURCE_DIR}/src/developer/codingstandards/codingStandards.dsl#html" 
		 "${PROJECT_SOURCE_DIR}/src/developer/codingstandards/codingStandards.xml")

   SET(ARGS_DEVELOPER_CODSTDABS "-f" "docbook" "-b" "html" "-o" "${PROJECT_SOURCE_DIR}/html/developer" "-d" 
		 "${PROJECT_SOURCE_DIR}/src/developer/codingstandardsabstract/codingStandardsAbstract.dsl#html" 
		 "${PROJECT_SOURCE_DIR}/src/developer/codingstandardsabstract/codingStandardsAbstract.xml")

   SET(ARGS_DEVELOPER_XEMACS "-f" "docbook" "-b" "html" "-o" "${PROJECT_SOURCE_DIR}/html/developer" "-d" 
		 "${PROJECT_SOURCE_DIR}/src/developer/xemacs/Xemacs.dsl#html" 
		 "${PROJECT_SOURCE_DIR}/src/developer/xemacs/Xemacs.xml")

   SET(ARGS_DEVELOPER_PACKAGING "-f" "docbook" "-b" "html" "-o" "${PROJECT_SOURCE_DIR}/html/developer" "-d" 
		 "${PROJECT_SOURCE_DIR}/src/developer/pkg/packagingGuide.dsl#html" 
		 "${PROJECT_SOURCE_DIR}/src/developer/pkg/packagingGuide.xml")

   SET(ARGS_INSTALL_INSTALLATION "-f" "docbook" "-b" "html" "-o" "${PROJECT_SOURCE_DIR}/html/installation" "-d" 
		 "${PROJECT_SOURCE_DIR}/src/installation/installation/installGuide.dsl#html" 
		 "${PROJECT_SOURCE_DIR}/src/installation/installation/installGuide.xml")

   SET(ARGS_INSTALL_COMPILATION "-f" "docbook" "-b" "html" "-o" "${PROJECT_SOURCE_DIR}/html/installation" "-d" 
		 "${PROJECT_SOURCE_DIR}/src/installation/compilation/compilationGuide.dsl#html" 
		 "${PROJECT_SOURCE_DIR}/src/installation/compilation/compilationGuide.xml")

   SET(ARGS_INSTALL_WINDOWS "-f" "docbook" "-b" "html" "-o" "${PROJECT_SOURCE_DIR}/html/installation" "-d" 
		 "${PROJECT_SOURCE_DIR}/src/installation/installation/installWindows.dsl#html" 
		 "${PROJECT_SOURCE_DIR}/src/installation/installation/installWindows.xml")

   SET(ARGS_BIBLIOGRAPHY "-f" "docbook" "-b" "html" "-o" "${PROJECT_SOURCE_DIR}/html/bibliography" "-d" 
		 "${PROJECT_SOURCE_DIR}/src/bibliography/bibliography.dsl#html" 
		 "${PROJECT_SOURCE_DIR}/src/bibliography/bibliography.xml")



   # The html files must be copied into right place
   ADD_CUSTOM_TARGET(doc-docbook COMMAND mkdir -p html/main/images
				 COMMAND cp ${PROJECT_SOURCE_DIR}/src/main/*.html ${PROJECT_SOURCE_DIR}/html/main
				 COMMAND cp ${PROJECT_SOURCE_DIR}/src/main/images/* ${PROJECT_SOURCE_DIR}/html/main/images
				 #COMMAND mkdir -p html/design
				 #COMMAND mkdir -p html/developer
				 COMMAND mkdir -p html/installation
				 COMMAND mkdir -p html/bibliography
				 COMMAND jw ${ARGS_MAIN} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
				 COMMAND jw ${ARGS_DESIGN} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
				 COMMAND jw ${ARGS_DEVELOPER_CODINGSTD} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
				 COMMAND jw ${ARGS_DEVELOPER_CODSTDABS} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
				 COMMAND jw ${ARGS_DEVELOPER_XEMACS} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
				 COMMAND jw ${ARGS_DEVELOPER_PACKAGING} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
				 COMMAND jw ${ARGS_INSTALL_INSTALLATION} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
				 COMMAND jw ${ARGS_INSTALL_COMPILATION} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
				 COMMAND jw ${ARGS_INSTALL_WINDOWS} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
				 COMMAND jw ${ARGS_BIBLIOGRAPHY} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
				 COMMAND cp ${PROJECT_SOURCE_DIR}/src/installation/installation/*.png ${PROJECT_SOURCE_DIR}/html/installation
				 COMMAND cp ${PROJECT_SOURCE_DIR}/src/installation/compilation/*.png ${PROJECT_SOURCE_DIR}/html/installation
				 COMMAND cp ${PROJECT_SOURCE_DIR}/src/main/*.css ${PROJECT_SOURCE_DIR}/html/main
				 COMMAND cp ${PROJECT_SOURCE_DIR}/src/design/*.css ${PROJECT_SOURCE_DIR}/html/design
				 COMMAND cp ${PROJECT_SOURCE_DIR}/src/developer/xemacs/*.css ${PROJECT_SOURCE_DIR}/html/developer
				 COMMAND cp ${PROJECT_SOURCE_DIR}/src/developer/pkg/*.css ${PROJECT_SOURCE_DIR}/html/developer
				 COMMAND cp ${PROJECT_SOURCE_DIR}/src/developer/codingstandards/*.css ${PROJECT_SOURCE_DIR}/html/developer
				 COMMAND cp ${PROJECT_SOURCE_DIR}/src/developer/codingstandardsabstract/*.css ${PROJECT_SOURCE_DIR}/html/developer
				 COMMAND cp ${PROJECT_SOURCE_DIR}/src/main/main.css ${PROJECT_SOURCE_DIR}/html
				 COMMAND cp ${PROJECT_SOURCE_DIR}/src/bibliography/bibliography.css ${PROJECT_SOURCE_DIR}/html/bibliography
				 COMMAND cp ${PROJECT_SOURCE_DIR}/src/installation/installation/installGuide.css ${PROJECT_SOURCE_DIR}/html/installation
				 COMMAND cp ${PROJECT_SOURCE_DIR}/src/installation/compilation/compilationGuide.css ${PROJECT_SOURCE_DIR}/html/installation


   )

ENDIF (UNIX AND DOCBOOK_FOUND)

# Creates the "doc" target.
# ATTENTION: Only if we're in Linux, because docbook isn't yet
# supported in this version of Qgar
IF (UNIX)
    ADD_CUSTOM_TARGET(doc COMMAND make doc-doxygen
		      COMMAND make doc-docbook )
ENDIF (UNIX) 