# DpkgDeb : Create debian packages for your projects and sub projects. Written by Mehdi Rabah
# Was heavily inspired by UseDebian (Mathieu Malaterre) and UseRPMTools (TSP Team) modules

# need /usr/bin/dpkg

# USAGE : ADD_DEBIAN_PACKAGE ( DEB_TARGET_NAME [CONTROL_FILE] )  
# You need to set the control file either by setting these variables
# or by giving as second parameter the path to the control file you want to use
# If you choose to set the variables, you must set the mandatory variables:
# (see man 5 deb-control for more details)
#
# -- MANDATORY Variables
# Package: ${PACKAGE_NAME}. Must be a lowercase string
# Version: ${PACKAGE_VERSION}. Like 1.1.0
# Release: ${PACKAGE_RELEASE}. A number beetween 0 and 9
# Maintainer: ${PACKAGE_MAINTAINER_NAME} and ${PACKAGE_MAINTAINER_EMAIL}. 
# Description summary: ${PACKAGE_DESCRIPTION_SUMMARY}. Project summary
# Description : ${PACKAGE_DESCRIPTION}. Warning : for now, use of special characters (>, (, ', ... ) is not allowed
#
# -- OPTIONAL Variables 
# Architecture: ${DEBIAN_ARCHITECTURE}, by default i386 for intel on debian like
# Depends: ${PACKAGE_DEPENDS}
# Section: ${PACKAGE_SECTION}
# Priority: ${PACKAGE_PRIORITY}
# Essential: ${PACKAGE_ESSENTIAL}
# Source: ${PACKAGE_SOURCE}
# Pre-Depends: ${PACKAGE_PREDEPENDS}
# Recommends: ${PACKAGE_RECOMMENDS}
# Suggests: ${PACKAGE_SUGGESTS}
# Breaks: ${PACKAGE_BREAKS}
# Conflicts: ${PACKAGE_CONFLICTS}
# Replaces: ${PACKAGE_REPLACES}
# Provides: ${PACKAGE_PROVIDES}

# TODO: Make clean does not clean the DEBIAN_DIR folder
# TODO: use objdump -p to automatically generate depedencies (cf dh_makeshlibs)

FIND_PROGRAM(DPKG
    NAMES dpkg-deb
    PATHS "/usr/bin")

IF ( DPKG )
    GET_FILENAME_COMPONENT(DPKG_PATH ${DPKG} ABSOLUTE)
    MESSAGE(STATUS "DEBIAN MODULE -- Found dpkg-deb : ${DPKG_PATH}")
    SET(DPKG_FOUND "YES")
ELSE ( DPKG ) 
    MESSAGE(STATUS "DEBIAN MODULE -- dpkg-deb NOT found. deb generation will not be available")
    SET(DPKG_FOUND "NO")
ENDIF ( DPKG )

# Main and only command of this module. For more details, visit this webpage
# http://tldp.org/HOWTO/Debian-Binary-Package-Building-HOWTO/
MACRO(ADD_DEBIAN_PACKAGE DEBNAME)

  SET ( CONTROL_FILE ${PROJECT_BINARY_DIR}/control_${PROJECT_NAME} )
  #  MESSAGE ( STATUS "---- DEBIAN MODULE -- Setting rules for ${CONTROL_FILE}" )
  # First choice for control file : user defined variables 
  IF ("${ARGV1}" STREQUAL "")

      # Check if the mandatory variables are here
      IF(NOT PACKAGE_NAME OR NOT PACKAGE_VERSION OR NOT DEFINED PACKAGE_RELEASE OR
         NOT PACKAGE_MAINTAINER_NAME OR NOT PACKAGE_MAINTAINER_EMAIL OR 
         NOT PACKAGE_DESCRIPTION_SUMMARY OR NOT PACKAGE_DESCRIPTION )
         MESSAGE ( FATAL_ERROR "ADD_DEBIAN_PACKAGE command was not correctly configured for ${PROJECT_NAME}. See the documentation for more details" )
      ENDIF(NOT PACKAGE_NAME OR NOT PACKAGE_VERSION OR NOT DEFINED PACKAGE_RELEASE OR
         NOT PACKAGE_MAINTAINER_NAME OR NOT PACKAGE_MAINTAINER_EMAIL OR 
         NOT PACKAGE_DESCRIPTION_SUMMARY OR NOT PACKAGE_DESCRIPTION )

      IF(NOT DEBIAN_ARCHITECTURE)
        SET(DEBIAN_ARCHITECTURE i386) #dpkg --print-architecture is always i386 on intel
      ENDIF(NOT DEBIAN_ARCHITECTURE)

      # Writing the control file
      # see man 5 deb-control for more details
	  
	#  MESSAGE ( STATUS "---- DEBIAN MODULE -- First custom command" )
      ADD_CUSTOM_COMMAND(
        OUTPUT ${CONTROL_FILE}
        COMMAND   ${CMAKE_COMMAND} -E echo 
         "Package: ${PACKAGE_NAME}" > ${CONTROL_FILE}
         
        COMMAND   ${CMAKE_COMMAND} -E echo
         "Version: ${PACKAGE_VERSION}" >> ${CONTROL_FILE}
        
        COMMAND   ${CMAKE_COMMAND} -E echo
         "Maintainer: ${PACKAGE_MAINTAINER_NAME}"
         \"<"${PACKAGE_MAINTAINER_EMAIL}\">" >> ${CONTROL_FILE}

        COMMAND   ${CMAKE_COMMAND}
        ARGS      -E echo "Architecture: ${DEBIAN_ARCHITECTURE}" >> ${CONTROL_FILE}
      )   

	#  MESSAGE ( "---- DEBIAN MODULE -- Second custom command" )
      IF ( DEFINED PACKAGE_DEPENDS )
        ADD_CUSTOM_COMMAND( OUTPUT ${CONTROL_FILE}
          COMMAND   ${CMAKE_COMMAND} -E echo
           "Depends: ${PACKAGE_DEPENDS}" >> ${CONTROL_FILE}
          APPEND )   
      ENDIF ( DEFINED PACKAGE_DEPENDS )
	  
	#  MESSAGE ( "---- DEBIAN MODULE -- Done!" )
	  
      IF ( DEFINED PACKAGE_SECTION )
        ADD_CUSTOM_COMMAND( OUTPUT ${CONTROL_FILE}
          COMMAND   ${CMAKE_COMMAND} -E echo
           "Section: ${PACKAGE_SECTION}" >> ${CONTROL_FILE}
          APPEND )   
      ENDIF ( DEFINED PACKAGE_SECTION)
      
      IF ( DEFINED PACKAGE_PRIORITY )
        ADD_CUSTOM_COMMAND( OUTPUT ${CONTROL_FILE}
          COMMAND   ${CMAKE_COMMAND} -E echo
           "Priority: ${PACKAGE_PRIORITY}" >> ${CONTROL_FILE}
          APPEND)   
      ENDIF ( DEFINED PACKAGE_PRIORITY)

      IF ( DEFINED PACKAGE_ESSENTIAL )
        ADD_CUSTOM_COMMAND( OUTPUT ${CONTROL_FILE}
          COMMAND   ${CMAKE_COMMAND} -E echo
           "Essential: ${PACKAGE_ESSENTIAL}" >> ${CONTROL_FILE}
          APPEND)   
      ENDIF ( DEFINED PACKAGE_ESSENTIAL)

      IF ( DEFINED PACKAGE_SOURCE )
        ADD_CUSTOM_COMMAND( OUTPUT ${CONTROL_FILE}
          COMMAND   ${CMAKE_COMMAND} -E echo
           "Source: ${PACKAGE_SOURCE}" >> ${CONTROL_FILE}
          APPEND)   
      ENDIF ( DEFINED PACKAGE_SOURCE)

      IF ( DEFINED PACKAGE_PREDEPENDS )
        ADD_CUSTOM_COMMAND( OUTPUT ${CONTROL_FILE}
          COMMAND   ${CMAKE_COMMAND} -E echo
           "Pre-Depends: ${PACKAGE_PREDEPENDS}" >> ${CONTROL_FILE}
          APPEND)   
      ENDIF ( DEFINED PACKAGE_PREDEPENDS )

      IF ( DEFINED PACKAGE_RECOMMENDS )
        ADD_CUSTOM_COMMAND( OUTPUT ${CONTROL_FILE}
          COMMAND   ${CMAKE_COMMAND} -E echo
           "Recommends: ${PACKAGE_RECOMMENDS}" >> ${CONTROL_FILE}
          APPEND)   
      ENDIF ( DEFINED PACKAGE_RECOMMENDS)

      IF ( DEFINED PACKAGE_SUGGESTS )
        ADD_CUSTOM_COMMAND( OUTPUT ${CONTROL_FILE}
          COMMAND   ${CMAKE_COMMAND} -E echo
           "Suggests: ${PACKAGE_SUGGESTS}" >> ${CONTROL_FILE}
          APPEND)   
      ENDIF ( DEFINED PACKAGE_SUGGESTS )

      IF ( DEFINED PACKAGE_BREAKS )
        ADD_CUSTOM_COMMAND( OUTPUT ${CONTROL_FILE}
          COMMAND   ${CMAKE_COMMAND} -E echo
           "Breaks: ${PACKAGE_BREAKS}" >> ${CONTROL_FILE}
          APPEND)   
      ENDIF ( DEFINED PACKAGE_BREAKS )

      IF ( DEFINED PACKAGE_CONFLICTS )
        ADD_CUSTOM_COMMAND( OUTPUT ${CONTROL_FILE}
          COMMAND   ${CMAKE_COMMAND} -E echo
           "Conflicts: ${PACKAGE_CONFLICTS}" >> ${CONTROL_FILE}
          APPEND)   
      ENDIF ( DEFINED PACKAGE_CONFLICTS )

      IF ( DEFINED PACKAGE_REPLACES )
        ADD_CUSTOM_COMMAND( OUTPUT ${CONTROL_FILE}
          COMMAND   ${CMAKE_COMMAND} -E echo
           "Replaces: ${PACKAGE_REPLACES}" >> ${CONTROL_FILE}
          APPEND)   
      ENDIF ( DEFINED PACKAGE_REPLACES )

      IF ( DEFINED PACKAGE_PROVIDES )
        ADD_CUSTOM_COMMAND( OUTPUT ${CONTROL_FILE}
          COMMAND   ${CMAKE_COMMAND} -E echo
           "Provides: ${PACKAGE_PROVIDES}" >> ${CONTROL_FILE}
          APPEND)   
      ENDIF ( DEFINED PACKAGE_PROVIDES )
      
      ADD_CUSTOM_COMMAND( OUTPUT ${CONTROL_FILE}
        COMMAND   ${CMAKE_COMMAND} -E echo
         "Description: ${PACKAGE_DESCRIPTION_SUMMARY}" >> ${CONTROL_FILE}
        COMMAND   ${CMAKE_COMMAND} -E echo
         " ." >> ${CONTROL_FILE}
        COMMAND   ${CMAKE_COMMAND} -E echo
         " ${PACKAGE_DESCRIPTION}" >> ${CONTROL_FILE}
        COMMAND   ${CMAKE_COMMAND} -E echo
         " ." >> ${CONTROL_FILE}
        COMMAND   ${CMAKE_COMMAND} -E echo
         "" >> ${CONTROL_FILE}
        COMMENT   "Generating control file"
        APPEND
      )
  ELSE ("${ARGV1}" STREQUAL "")
     ADD_CUSTOM_COMMAND(
        OUTPUT    ${CONTROL_FILE}
        COMMAND   ${CMAKE_COMMAND} -E copy "${ARGV1}" ${CONTROL_FILE}
        COMMENT "Copying user specified control file : ${ARGV1}"
      )
  ENDIF("${ARGV1}" STREQUAL "")
  
  # let's create a directory to call 'make install DESTDIR=...' into:
  SET ( DEBIAN_DIR  ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}_${PACKAGE_VERSION}-${PACKAGE_RELEASE}_${DEBIAN_ARCHITECTURE} )

  FILE ( REMOVE ${DEBIAN_DIR} )
  FILE ( MAKE_DIRECTORY ${DEBIAN_DIR} )
  FILE ( MAKE_DIRECTORY ${DEBIAN_DIR}/DEBIAN )


  # String manipulation to allow to copy the documentation directory
  # to the Debian directory and later into the package 
  STRING(REGEX REPLACE "/html" "" GENERAL_DOC_DIR ${DOC_INSTALL_DIR})

  # Calling "make install DESTDIR=${DEBIAN_DIR}"
  # 
  # -------------------- ATTENTION -----------------------
  #
  # The CMAKE_INSTALL_PREFIX must be changed to the correct location. Otherwise,
  # the source will be installed in the defined place, no default place
  SET ( TEMP ${CMAKE_INSTALL_PREFIX})
  SET ( CMAKE_INSTALL_PREFIX ${DEBIAN_INSTALL_PREFIX} CACHE STRING "" FORCE )

  ADD_CUSTOM_TARGET(deb_dir_install
     COMMAND ${CMAKE_MAKE_PROGRAM} install DESTDIR=${DEBIAN_DIR}

    # Force the Documentation generation
    COMMAND ${CMAKE_MAKE_PROGRAM} doc DESTDIR=${DEBIAN_DIR}/doc/${QGAR_NAME_VERSION}

    # Copy all documentation from QgarDoc/html into DEBIAN_DIR

    COMMAND ${CMAKE_COMMAND} -E make_directory ${DEBIAN_DIR}${DEBIAN_INSTALL_PREFIX}/doc/${QGAR_NAME_VERSION}
    COMMAND cp -r ${PROJECT_SOURCE_DIR}/QgarDoc/html ${DEBIAN_DIR}${DEBIAN_INSTALL_PREFIX}/doc/${QGAR_NAME_VERSION}

##    COMMAND ${CMAKE_COMMAND} -E make_directory ${DEBIAN_DIR}${DEBIAN_INSTALL_PREFIX}${DOC_INSTALL_DIR}
##    COMMAND cp -r ${PROJECT_SOURCE_DIR}/QgarDoc/html ${DEBIAN_DIR}${DEBIAN_INSTALL_PREFIX}${GENERAL_DOC_DIR}

    # Copy the XML description files to share directory and Application binaries
    COMMAND ${CMAKE_COMMAND} -E make_directory ${DEBIAN_DIR}${DEBIAN_INSTALL_PREFIX}${XML_INSTALL_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${DEBIAN_DIR}${DEBIAN_INSTALL_PREFIX}/bin

    COMMAND cp -r ${PROJECT_SOURCE_DIR}/QgarApps/QAdist34Skeletonization/QAdist34Skeletonization_descr.xml ${DEBIAN_DIR}${DEBIAN_INSTALL_PREFIX}${XML_INSTALL_DIR}
    COMMAND cp -r ${PROJECT_SOURCE_DIR}/QgarApps/QAedgesCanny/QAedgesCanny_descr.xml ${DEBIAN_DIR}${DEBIAN_INSTALL_PREFIX}${XML_INSTALL_DIR}
    COMMAND cp -r ${PROJECT_SOURCE_DIR}/QgarApps/QAedgesDeriche/QAedgesDeriche_descr.xml ${DEBIAN_DIR}${DEBIAN_INSTALL_PREFIX}${XML_INSTALL_DIR}
    COMMAND cp -r ${PROJECT_SOURCE_DIR}/QgarApps/QAkanungoDegrade/QAkanungoDegrade_descr.xml ${DEBIAN_DIR}${DEBIAN_INSTALL_PREFIX}${XML_INSTALL_DIR}
    COMMAND cp -r ${PROJECT_SOURCE_DIR}/QgarApps/QAmorphoClosing/QAmorphoClosing_descr.xml ${DEBIAN_DIR}${DEBIAN_INSTALL_PREFIX}${XML_INSTALL_DIR}
    COMMAND cp -r ${PROJECT_SOURCE_DIR}/QgarApps/QAmorphoOpening/QAmorphoOpening_descr.xml ${DEBIAN_DIR}${DEBIAN_INSTALL_PREFIX}${XML_INSTALL_DIR}
    COMMAND cp -r ${PROJECT_SOURCE_DIR}/QgarApps/QApruneSmallCC/QApruneSmallCC_descr.xml ${DEBIAN_DIR}${DEBIAN_INSTALL_PREFIX}${XML_INSTALL_DIR}
    COMMAND cp -r ${PROJECT_SOURCE_DIR}/QgarApps/QAtextExtraction/QAtextExtraction_descr.xml ${DEBIAN_DIR}${DEBIAN_INSTALL_PREFIX}${XML_INSTALL_DIR}
    COMMAND cp -r ${PROJECT_SOURCE_DIR}/QgarApps/QAtextGraphicSeparation/QAtextGraphicSeparation_descr.xml ${DEBIAN_DIR}${DEBIAN_INSTALL_PREFIX}${XML_INSTALL_DIR}
    COMMAND cp -r ${PROJECT_SOURCE_DIR}/QgarApps/QAthickThinSeparation/QAthickThinSeparation_descr.xml ${DEBIAN_DIR}${DEBIAN_INSTALL_PREFIX}${XML_INSTALL_DIR}
    COMMAND cp -r ${PROJECT_SOURCE_DIR}/QgarApps/QAthrsBinarization/QAthrsBinarization_descr.xml ${DEBIAN_DIR}${DEBIAN_INSTALL_PREFIX}${XML_INSTALL_DIR}
    COMMAND cp -r ${PROJECT_SOURCE_DIR}/QgarApps/QAtrierBinarization/QAtrierBinarization_descr.xml ${DEBIAN_DIR}${DEBIAN_INSTALL_PREFIX}${XML_INSTALL_DIR}
    COMMAND cp -r ${PROJECT_SOURCE_DIR}/QgarApps/QAvectorizationRW/QAvectorizationRW_descr.xml ${DEBIAN_DIR}${DEBIAN_INSTALL_PREFIX}${XML_INSTALL_DIR}

    # Copy QgarGui binary
    DEPENDS ${CMAKE_BINARY_DIR}/cmake_install.cmake	  
    COMMENT "Installing with DESTDIR = ${DEBIAN_DIR}"
  )

  # ---------------------------------------------------------------------------------------------------------------------------------------------------
  #

  ADD_DEPENDENCIES(deb_dir_install all preinstall)
  
  # Calling dpkg --build 
  ADD_CUSTOM_COMMAND(
    OUTPUT  ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}_${PACKAGE_VERSION}-${PACKAGE_RELEASE}_${DEBIAN_ARCHITECTURE}.deb
    COMMAND ${CMAKE_COMMAND} -E copy ${CONTROL_FILE} ${DEBIAN_DIR}/DEBIAN/control
    COMMAND ${DPKG_PATH} --build ${DEBIAN_DIR}
    # removing control, so its (re)generated each time we need to build the package
    COMMAND ${CMAKE_COMMAND} -E remove ${CONTROL_FILE}
    DEPENDS ${CONTROL_FILE}
    COMMENT   "Generating deb package"
  )

  # the final target:
  ADD_CUSTOM_TARGET(${DEBNAME}_deb
    DEPENDS ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}_${PACKAGE_VERSION}-${PACKAGE_RELEASE}_${DEBIAN_ARCHITECTURE}.deb
  )
  
  ADD_DEPENDENCIES(${DEBNAME}_deb deb_dir_install)

ENDMACRO(ADD_DEBIAN_PACKAGE DEBNAME)
