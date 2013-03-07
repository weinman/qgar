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
 |   LORIA - équipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-lès-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/

/**
 * @file   nsis_install.nsi
 * @brief  Nullsoft installer generator script.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Vitor Vasconcelos">Vitor Vasconcelos</a>
 * @date   July 2, 2007  20:00 - Modified December 17, 2007  18:20
 * @since  Qgar 3.0
 */

# ---------------------------------------------------------------------
#
#
#
# H O W   D O E S   T H I S   S C R I P T   W O R K S ?
#
#
#
# READ CAREFULLY
# --------------
#
# This NSIS scrips will generate a Windows executable file containing
# packed Qgar files aimed to easily install Qgar on Windows plataforms.
#
# WHO CAN DO IT?
# --------------
#
# Any developer with basic knowledge about CMake SOURCE and BINARY
# directories concepts.
#
#
# HOW TO DO IT?
# -------------
#
# [ DIAGRAM 1] Simply compile the Qgar source using CMake. After compile Qgar, the 
# install must be executed - make install (with MinGW) - to create 
# all directories/files and copy them in the right location.
#
# At this point, the binary Qgar is available, along other files 
# (xml, README, etc).
#
# Then is enough to copy all QGAR BINARY DIR (Qgar base directory) 
# under 'winstaller'directory of QGAR SOURCE DIR.
#
# [ DIAGRAM 2 ] Since Qgar documentation needs both docbook and doxygen, 
# it can be only generated on Linux environments. So, to be able to generate 
# the Windows install, the documentation MUST be generated on LINUX 
# before. To do it, just type 'make doc' at the CMake's binary dir
# and the documentation will be generated in the SOURCE DIR. 
# Now, NSIS can find the documentation html files.
#
# It's possible to use the same source tree to generate binary 
# versions both for Windows and Linux. A special attention must 
# be payed on to be sure the last CMake call was in the correct 
# system.
# 
# If by any means the documentation cannot be generated (on Windows), 
# is enough to copy the QgarDoc/html generated on Linux to the
# SOURCE dir on Windows.
#
# With this procedure, the NSIS script is able to find all files it 
# needs to pack the Windows executable.
#
# EXAMPLE QGAR TREE to use NSIS
# -----------------------------
#
# Qgar
#   |____ qgardevlib/
#   |____ qgarlib/
#   |____ QgarApps/...   
#   |____ QgarDoc
#   |         |___ src/..
#   |         |
#   |         |___ html/   *** DIAGRAM 2 ***
#   |                |
#   |                |__ main/...
#   |
#   |____ QgarGui/
#   |____ cmake_adds/
#   |____ winstaller/nsis_install.nsi *** this file ***
#            |
#            |
# - - - - -  | - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
#            |
#            |____ Qgar_install/  *** DIAGRAM 1 ***
#                        |
#                        |______ bin/
#                        |______ include/..   
#                        |______ lib/                
#                        |______ share/..
#
#
#
# EXTERNAL FILES
# --------------
#
# QgarGui needs some Qt DLL's. These files can be in different locations
# on each machine used to generate a setup.
# Fill the correct path in QgarGUI section of this script
# (the value on last install is: c:\Qt\4.3.4\bin
# the file are:
#
# - qtCore4.dll
# - qtGui4.dll
# - qtXml4.dll
# - mingwm10.dll
#
#-----------------------------------------------------------------------


# ------------------------------------------------------------------------


# /////////////////////////////////////////////////////////////////
!include WriteEnvStr.nsh # Defines environment variables
!include WordFunc.nsh # Word manipulation
# ////////////////////////////////////////////////////////////////
!insertMacro WordAdd
!insertMacro WordReplace

# ---------------------------------------------------------------------
#
# General Installer configuration
#
# ----------------------------------------------------------------------

# ----------------------------------------------------------------------
# It's possible to choose between three compression methods:
# - zlib
# - bzip2
# -lzma : slow compression, fast decompression, good compression ratios
# /SOLID : All installer data is compressed in one block, resulting in 
#          greater compression ratios
#
SetCompressor /SOLID lzma

# -----------------------------------------------------------------------
# set the name of the installer as a standard Windows name
outfile "setup.exe"

# -----------------------------------------------------------------------
# The Name command sets the installer windows title
Name "Qgar Software"

# -----------------------------------------------------------------------
# The BrandingText command sets the text in the bottom part of the 
# installer. When passed one space string, the default Nullsoft text is 
# supprimed. ATENTION: if passed an empty string, nothing happens.
BrandingText " "

# -----------------------------------------------------------------------
# Sets the default install Dir. 
# $PROGRAMFILES is a system variable that contains Windoes default 
# programs directory It's value depends on version of Windows used.
# The string QGAR is not appended to it but used as default install dir 
# by the installDir command. Due to windows space paths and the problems
# associated to read these paths, we avoid this directory
#
# Environment variables are set, but they don't work neither
# with spaces in paths
#
#installDir $PROGRAMFILES\Qgar
installDir  C:\Qgar

# -----------------------------------------------------------------------
# The NSIS script works by means of sessions. They're used to separate 
# common tasks and components in this script.
# The sections can be labeled if necessary.


# -------------------------------------------------------------------------
# Components Sections:
#
# There are four sections, one for each instalable component
#
# 1) Qgar Core: installs libs, .h and .tcc files both for qgarlib and
#               qgardevlib. It's mandatory.
#
# 2) Doc: All documentation files in html format. They're installed in
#         the same relative paths as on Linux. /Qgar/share/html/..
#
# 3) Source Code: .cpp files.
#
# 4) Applications: All Qgar Executables. Qgar/bin dir. 
#
# 5) QgarGui: .exe file, .xml files (applications and guiconfig).
#             The Gui install forces all applications install.
#                  
#--------------------------------------------------------------------------
# Description of NSIS packing directories:
#
# [files]
# Qgar_install/
#	  lib / [libqgarwin.a]
#	  lib / [libqgardev.a]
#	  bin / [QAapplicationName.exe] *
#	  bin / [QgarGui.exe]
#         include / qgardevlib / 
#	         .h, .cpp, .tcc, etc. All files in include.
#         include / qgarlib / 
#             .h, .cpp, .tcc, etc. All files in include.
#             sax / (SAX interface .h files)
#             qtimpl / (Qt SAX implementation files)
#         share / qgar
#	      / QA* (.xml, .cpp and CMakeLists of each application)
#
# Qgar/
#     [qgar_files]
#     QgarDoc /
#	      src / (Documentation source files)
#	      html / (All html generated files, .css, images, etc.)
#
# [files] -> WriteEnvStr.nsh (NSIS included file)
#	  -> qgar.ico
#	  -> nsis_install.nsi
#	  -> LICENSE.QPL
#	  -> LICENSE.LGPL
#
# [qgar_files] -> NEWS
#	       -> LICENSE.QPL
#	       -> LICENSE.LGPL
#              -> INSTALL
#              -> COPYING
#              -> CMakeLists.txt (Qgar project main CMake script)
#              -> ChangeLog
#              -> qgar.in
#              -> qgar-mdk.specs.in
#
#--------------------------------------------------------------------------
# Install Sections - QgarCore
#
# The ! before the section makes its exibithion in bold letters
# -------------------------------------------------------------------------

  Section "!Qgar Core Library" Id_core
    SetOutPath $INSTDIR\lib
    File Qgar_install\lib\libqgarwin.a
    File Qgar_install\lib\libqgardev.a

    SetOutPath $INSTDIR\include\qgarlib
    File Qgar_install\include\qgarlib\*.h 
    File Qgar_install\include\qgarlib\*.tcc 

    SetOutPath $INSTDIR\include\qgardevlib
    File Qgar_install\include\qgardevlib\*.h 

  SectionEnd

#----------------------------------------------------------------------------
# Install Section - QgarGUI
#
# In this section are installed QgarGui.exe, all xml configuration file
# and all needed dlls
#----------------------------------------------------------------------------
Section "Graphical Interface" Id_gui

  #QgarGui
  SetOutPath $INSTDIR\bin
  File Qgar_install\bin\QgarGui.exe

  # Associated DLL's
  SetOutPath $INSTDIR\bin
  File c:\Qt\4.3.4\bin\QtCore4.dll
  File c:\Qt\4.3.4\bin\QtGui4.dll
  File c:\Qt\4.3.4\bin\QtXml4.dll
  File c:\Qt\4.3.4\bin\mingwm10.dll
  # .bat file
  File ..\QgarGui\qgarwin.bat.in
  Rename $INSTDIR\bin\qgarwin.bat.in $INSTDIR\bin\qgarwin.bat

  # Third party macro, must be called 1 time for each substitution

  # ------------------------------------------------------------------------
  #
  # qgarwin.bat.in - string replacement
  #
  # ------------------------------------------------------------------------


  # -------------------------------------------------------------
  #
  # ATTENTION: Windows paths with spaces are not well recognized
  # by C++ io functions like getenv() used in QGAR.
  # Here we replace "Program Files" by "Progra~1" to allow users
  # to execute QgarGui even after installing in Program Files.
  # It's mandatory to avoid it and install in the base path.
  #
  # To avoid this problem, the user can define it's own variable
  # called QGARSHARE and puth the complete path without commas.
  # 
  # --------------------------------------------------------------
  Push @install_prefix@                      #text to be replaced
  Push $INSTDIR 	                     #replace with
  Push all                                   #replace all occurrences
  Push all                                   #replace all occurrences
  Push $INSTDIR\bin\qgarwin.bat              #file to replace in
  Call AdvReplaceInFile                      #call find and replace function

  StrCpy $0 "\share"
  #  ${WordAdd} $0 " " '+"$\n' $R0 
  Push @install_xml@                         #text to be replaced
  Push $0	                             #replace with
  Push all                                   #replace all occurrences
  Push all                                   #replace all occurrences
  Push $INSTDIR\bin\qgarwin.bat              #file to replace in
  Call AdvReplaceInFile                      #call find and replace function

  StrCpy $1 "\bin"
  #  ${WordAdd} $1 " " '+"$\n' $R1
  Push @install_bin@                         #text to be replaced
  Push $1                                    #replace with
  Push all                                   #replace all occurrences
  Push all                                   #replace all occurrences
  Push $INSTDIR\bin\qgarwin.bat              #file to replace in
  Call AdvReplaceInFile                      #call find and replace function

  # ------------------------------------------------------------------------
  #
  # qgarguicfg.xml.in - string replacement
  #
  # ------------------------------------------------------------------------
  # Configuration file
  SetOutPath $INSTDIR\share
  File ..\QgarApps\qgarguicfg.xml.in
  Rename $INSTDIR\share\qgarguicfg.xml.in $INSTDIR\share\qgarguicfg.xml

  StrCpy $8 $INSTDIR
  ${WordReplace} $8 "\" "/" "+" $R8
  ${WordAdd} $R8 "/" "+bin" $8

  # Replace Customer Name in config.properties
  Push @bin_install_dir@                     #text to be replaced
  Push $8                                    #replace with
  Push all                                   #replace all occurrences
  Push all                                   #replace all occurrences
  Push $INSTDIR\share\qgarguicfg.xml    #file to replace in
  Call AdvReplaceInFile                      #call find and replace function
 
  StrCpy $6 $INSTDIR
  ${WordReplace} $6 "\" "/" "+" $R6
  ${WordAdd} $R6 "/" "+share" $6

  # Replace Customer Name in config.properties
  Push @xml_install_dir@                     #text to be replaced
  Push $6                                   #replace with
  Push all                                   #replace all occurrences
  Push all                                   #replace all occurrences
  Push $INSTDIR\share\qgarguicfg.xml    #file to replace in
  Call AdvReplaceInFile                      #call find and replace function

  # --------------------------------------------------------------------------
  # Write environment variables
  Push "QGARSHARE"
  Push $6
  Call WriteEnvStr

SectionEnd


#----------------------------------------------------------------------------
# Install Section - Applications
#
# All applications are separated inside the own sections and grouped in 
# one grouped section. It allows selections of only some applications.
#----------------------------------------------------------------------------
SectionGroup "Applications" Id_apps

  Section "Skeletonization34" Secdist34Skeletonization
    SetOutPath $INSTDIR\bin
    File /r Qgar_install\bin\QAdist34Skeletonization.exe
    SetOutPath $INSTDIR\share
    File Qgar_install\share\qgar\QAdist34Skeletonization_descr.xml
  SectionEnd

  Section "Canny Edge Detector" SecCanny
    SetOutPath $INSTDIR\bin
    File /r Qgar_install\bin\QAedgesCanny.exe
    SetOutPath $INSTDIR\share
    File /r Qgar_install\share\qgar\QAedgesCanny_descr.xml
  SectionEnd

  Section "Deriche Edge Detector" SecDeriche
    SetOutPath $INSTDIR\bin
    File /r Qgar_install\bin\QAedgesDeriche.exe
    SetOutPath $INSTDIR\share
    File /r Qgar_install\share\qgar\QAedgesDeriche_descr.xml
  SectionEnd

  Section "Kanungo Statistical Degradation" SecKanungo
    SetOutPath $INSTDIR\bin
    File /r Qgar_install\bin\QAkanungoDegrade.exe
    SetOutPath $INSTDIR\share
    File /r Qgar_install\share\qgar\QAkanungoDegrade_descr.xml
  SectionEnd

  Section "Morphological Closing" SecMorphoClosing
    SetOutPath $INSTDIR\bin
    File /r Qgar_install\bin\QAmorphoClosing.exe
    SetOutPath $INSTDIR\share
    File /r Qgar_install\share\qgar\QAmorphoClosing_descr.xml
  SectionEnd

  Section "Morphological Opening" SecMorphoOpening
    SetOutPath $INSTDIR\bin
    File /r Qgar_install\bin\QAmorphoOpening.exe
    SetOutPath $INSTDIR\share
    File /r Qgar_install\share\qgar\QAmorphoOpening_descr.xml
  SectionEnd

  Section "Prune Small Connected Components" SecPrune
    SetOutPath $INSTDIR\bin
    File /r Qgar_install\bin\QApruneSmallCC.exe
    SetOutPath $INSTDIR\share
    File /r Qgar_install\share\qgar\QApruneSmallCC_descr.xml
  SectionEnd

  Section "Text Extraction" SecTextExtraction
    SetOutPath $INSTDIR\bin
    File /r Qgar_install\bin\QAtextExtraction.exe
    SetOutPath $INSTDIR\share
    File /r Qgar_install\share\qgar\QAtextExtraction_descr.xml
  SectionEnd

  Section "Text Graphic Separation" SecTextGraphicSeparation
    SetOutPath $INSTDIR\bin
    File /r Qgar_install\bin\QAtextGraphicSeparation.exe
    SetOutPath $INSTDIR\share
    File /r Qgar_install\share\qgar\QAtextGraphicSeparation_descr.xml
  SectionEnd

  Section "Thick Thin Separation" SecThickThinSeparation
    SetOutPath $INSTDIR\bin
    File /r Qgar_install\bin\QAthickThinSeparation.exe
    SetOutPath $INSTDIR\share
    File /r Qgar_install\share\qgar\QAthickThinSeparation_descr.xml
  SectionEnd

  Section "Constant Treshold Binarization" SecThrsBinarization
    SetOutPath $INSTDIR\bin
    File /r Qgar_install\bin\QAthrsBinarization.exe
    SetOutPath $INSTDIR\share
    File /r Qgar_install\share\qgar\QAthrsBinarization_descr.xml
  SectionEnd

  Section "Tier and Taxt's Binarization" SecTrierBinarization
    SetOutPath $INSTDIR\bin
    File /r Qgar_install\bin\QAtrierBinarization.exe    
    SetOutPath $INSTDIR\share
    File /r Qgar_install\share\qgar\QAtrierBinarization_descr.xml
  SectionEnd

  Section "Vectorization" SecVectorization
    SetOutPath $INSTDIR\bin
    File /r Qgar_install\bin\QAvectorizationRW.exe
    SetOutPath $INSTDIR\share
    File /r Qgar_install\share\qgar\QAvectorizationRW_descr.xml
  SectionEnd

SectionGroupEnd


#--------------------------------------------------------------------------
# Install Section - Doc
#
# The File command puts all selected files in the installer package.
# Some wildcards are allowed. Make sure the directories pointed by 
# all File commands really contains the correct files.
#
# ATENTION: The Qgar tree is used, but the directories must not contain
# any building files, otherwise all them will be added to the package. 
# -------------------------------------------------------------------------
Section "Documentation" Id_doc
  
  SetOutPath $INSTDIR\QgarDoc\html
  File /r ..\QgarDoc\html\main

  SetOutPath $INSTDIR\QgarDoc\html
  File /r ..\QgarDoc\html\installation

  SetOutPath $INSTDIR\QgarDoc\html
  File /r ..\QgarDoc\html\developer

  SetOutPath $INSTDIR\QgarDoc\html
  File /r ..\QgarDoc\html\design

  SetOutPath $INSTDIR\QgarDoc\html
  File /r ..\QgarDoc\html\bibliography

  SetOutPath $INSTDIR\QgarDoc\html
  File /r ..\QgarDoc\html\api

SectionEnd

# ---------------------------------------------------------------------------
# Creates the Uninstaller
# ---------------------------------------------------------------------------
Section
    # Defines the file name
    WriteUninstaller $INSTDIR\Uninstall.exe
SectionEnd

#-------------------------------------------------------------------
# License page
#-------------------------------------------------------------------

 PageEx license
   LicenseData ..\LICENSE.LGPL
 PageExEnd

 PageEx license
   LicenseData ..\LICENSE.QPL
 PageExEnd

#-------------------------------------------------------------------
# Directory page
#-------------------------------------------------------------------
# The default directory is local Program Files\Qgar
# The Page command is a default NSIS page the asks the users if
# he wants to chose the install directory
Page directory

#-------------------------------------------------------------------
# Components page
#
# The components page create the page that exibiths all sections
# to users.
#-------------------------------------------------------------------
Page components

#-------------------------------------------------------------------
# Install page
#
# The default page that performs the install. It has an elapsed 
# install bar and a button to detail the install process.
#-------------------------------------------------------------------
Page instfiles

# ------------------------------------------------------------------
# ------------------------------------------------------------------
#
# VARIABLES
#
# ------------------------------------------------------------------
# ------------------------------------------------------------------

Var /GLOBAL flag_doc
Var /GLOBAL flag_apps
Var /GLOBAL flag_gui


# ------------------------------------------------------------------
# ------------------------------------------------------------------
#
# FUNCTIONS
#
# ------------------------------------------------------------------
# ------------------------------------------------------------------
#
# The NSIS allows the use of global (and section) functions. It's 
# possible to create personal functions or use some functions (and 
# their associated callbacks) to control some install aspects.




# ------------------------------------------------------------------

Function AdvReplaceInFile
         Exch $0 ;file to replace in
         Exch
         Exch $1 ;number to replace after
         Exch
         Exch 2
         Exch $2 ;replace and onwards
         Exch 2
         Exch 3
         Exch $3 ;replace with
         Exch 3
         Exch 4
         Exch $4 ;to replace
         Exch 4
         Push $5 ;minus count
         Push $6 ;universal
         Push $7 ;end string
         Push $8 ;left string
         Push $9 ;right string
         Push $R0 ;file1
         Push $R1 ;file2
         Push $R2 ;read
         Push $R3 ;universal
         Push $R4 ;count (onwards)
         Push $R5 ;count (after)
         Push $R6 ;temp file name
         GetTempFileName $R6
         FileOpen $R1 $0 r ;file to search in
         FileOpen $R0 $R6 w ;temp file
                  StrLen $R3 $4
                  StrCpy $R4 -1
                  StrCpy $R5 -1
        loop_read:
         ClearErrors
         FileRead $R1 $R2 ;read line
         IfErrors exit
         StrCpy $5 0
         StrCpy $7 $R2
 
        loop_filter:
         IntOp $5 $5 - 1
         StrCpy $6 $7 $R3 $5 ;search
         StrCmp $6 "" file_write2
         StrCmp $6 $4 0 loop_filter
 
         StrCpy $8 $7 $5 ;left part
         IntOp $6 $5 + $R3
         StrCpy $9 $7 "" $6 ;right part
         StrCpy $7 $8$3$9 ;re-join
 
         IntOp $R4 $R4 + 1
         StrCmp $2 all file_write1
         StrCmp $R4 $2 0 file_write2
         IntOp $R4 $R4 - 1
 
         IntOp $R5 $R5 + 1
         StrCmp $1 all file_write1
         StrCmp $R5 $1 0 file_write1
         IntOp $R5 $R5 - 1
         Goto file_write2
 
        file_write1:
         FileWrite $R0 $7 ;write modified line
         Goto loop_read
 
        file_write2:
         FileWrite $R0 $R2 ;write unmodified line
         Goto loop_read
 
        exit:
         FileClose $R0
         FileClose $R1
 
         SetDetailsPrint none
         Delete $0
         Rename $R6 $0
         Delete $R6
         SetDetailsPrint both
 
         Pop $R6
         Pop $R5
         Pop $R4
         Pop $R3
         Pop $R2
         Pop $R1
         Pop $R0
         Pop $9
         Pop $8
         Pop $7
         Pop $6
         Pop $5
         Pop $4
         Pop $3
         Pop $2
         Pop $1
         Pop $0
FunctionEnd

# ------------------------------------------------------------------

# ------------------------------------------------------------------
# .onInit function
# 
# Get the values in the beggining to avoid
# blank variables and mark the core library as read-only
# ------------------------------------------------------------------
Function .onInit
  # The intOp command "sums" bit values
  # keep section "Qgar Core Libary" selected and read-only
  # 1 - SELECTED
  # 16 - READ_ONLY
  IntOp $0 1 | 16

  # The section id is used here to mark the Core Libraries section
  # as readonly, so its installation is mandatory
  SectionSetFlags ${Id_core} $0

  IntOp $1 $0 | 2
  SectionSetFlags ${Id_apps} $1

FunctionEnd


# ------------------------------------------------------------------
# .onGUIInit function
# 
# Set the doc and application sections as selected.
# The apps sections has a slightly different value, because it's 
# formed as a grouped section. Check the NSIS documentation for 
# more complete explanations.
# ------------------------------------------------------------------
Function .onGUIInit
  IntOp $flag_doc @flag_doc + 1
  IntOp $flag_apps 1 + 2
  IntOp $flag_gui @flag_gui + 1
FunctionEnd

# ------------------------------------------------------------------
# .onSelChange function
# 
# This function only gets the components values and hold it until
# the next change. Those values are global and are used to check if
# is needed to create Start Menu ShortCuts.
# It also checks if the Gui is selected, making all applications
# also selected

Function .onSelChange
 
  SectionGetFlags ${Id_doc} $flag_doc
  SectionGetFlags ${Id_apps} $flag_apps
  SectionGetFlags ${Id_gui} $flag_gui

#  SectionGetFlags ${Id_apps} $5

#  IntCmp $flag_gui 1 is3 lessThan3 moreThan3
#  is3:
      # 1 - SELECTED
      # 2 - SELECTION GROUP
      # 16 - READONLY
#      IntOp $0 1 | 2
#      IntOp $1 $0 | 16
#      SectionSetFlags ${Id_apps} $1
#      Goto done
#  lessThan3:
#      IntOp $6 $5 - 16
#      SectionSetFlags ${Id_apps} $6 
#      Goto done
#  moreThan3:
#      Goto done
#  done:
  

FunctionEnd



# -----------------------------------------------------------------------------------
# Shorcuts Section
#
# Create a shortcut to QgarApps
# It opens a COMMAND Window in the directory where QgarApps were installed
# -----------------------------------------------------------------------------------
section

MessageBox MB_YESNO "Do you want to create shortcuts in Start Menu (recommended)?" IDYES true IDNO false

true:
 
    # Copy the icon file to the icon directory
    # it will be used in the shortcut creation
    SetOutPath $INSTDIR
    File qgar.ico

    # create a shortcut named "Qgar" in the start menu programs directory
    # presently, the new shortcut doesn't call anything (the second field is blank)
    createDirectory "$SMPROGRAMS\Qgar"

    # Creates the shortcut to DOS with applications
    #
    # ATENTION: ***********************************************************************************************
    #
    # The IntCmp is used as an if, to compare integer values. The values compared are stored in $flag_apps, $flag_doc 
    # and $flag_gui variables. They're set inside .onSelChange system function.
    # The control structure below just verify if the applications and/or doc links must be created.
    #
    #
    # *********************************************************************************************************


    # Gui
    # ---------------------------------------------------------------------------------------------------------
    #
    # The Gui uses the applications installed. So, if the Gui is selected, all applications are automatically
    # marked to install.
    #
    #
    #
    #

    IntCmp $flag_gui 1 isGuiEqual1 done_gui done_gui
    isGuiEqual1:

	createShortCut "$SMPROGRAMS\Qgar\QgarGUI.lnk" "$INSTDIR\bin\QgarGui.exe" "" "$INSTDIR\qgar.ico" 0 SW_SHOWNORMAL    
    done_gui:  

    # Apps
    # ---------------------------------------------------------------------------------------------------------
    #
    # This weird structure works as this:
    # The $flag_apps value can be: 
    # 2 -> The entire Application Group is unselected;
    # 3 -> The entire Application Group is selected;
    # 98 -> The Application Groups is unselected, but one or more components inside it are selected.
    #
    # So, the variable is compared to 3. If it's equal, it goes to the first label (isEqual3). If it's less 
    # than 3, it goes to done_apps label, which means to not create the link. Finally, if it's greater 
    # than 3, it goes to isEqual98 label.
    #
    IntCmp $flag_apps 3 isEqual3 done_apps IsEqual98
    isEqual3:
        createShortCut "$SMPROGRAMS\Qgar\Applications.lnk" "cmd" "cd $INSTDIR\bin"
	Goto done_apps
    isEqual98:
        createShortCut "$SMPROGRAMS\Qgar\Applications.lnk" "cmd" "cd $INSTDIR\bin"
        Goto done_apps
    done_apps:
 
    # Doc
    # ---------------------------------------------------------------------------------------------------------
    #
    # The only possible values to $flag_doc are 0 or 1. So, it's compared to 1. If true, the program follows
    # the idDocEqual1 and the link is created. Otherwise, if it's less or greater than 1, the flux follows the
    # done_doc label that performs no operation.
    #
    # Creates the shortcut to the browser to use the doc
    IntCmp $flag_doc 1 isDocEqual1 done_doc done_doc
    isDocEqual1:
        createShortCut "$SMPROGRAMS\Qgar\Documentation.lnk" "$INSTDIR\QgarDoc\html\main\index.html" 
        Goto done_doc
    done_doc:

    # Creates the shortcut to Unistall
    createShortCut "$SMPROGRAMS\Qgar\Uninstall.lnk "$INSTDIR\Uninstall.exe" "" "" 0
    
false: 

# If the response to the MessageBox is false, nothing is done in this section
sectionEnd



# -------------------------------------------------------------------------------------
# UNINSTALL Pages
# -------------------------------------------------------------------------------------

UninstPage uninstConfirm
UninstPage instfiles


# --------------------------------------------------------------------
# Uninstall Section
#
# This section is used only by the uninstaller and controls the 
# tasks performed by the unistall executable.
# The uninstall is always installed with its shortcut. 
# --------------------------------------------------------------------
Section "Uninstall"

  #-------------------------------------------------------------------
  # Remove $QGARDIR and @QGARLIBDIR variables
  #-------------------------------------------------------------------
  # remove the variables
  Push QGARDIR
  Call un.DeleteEnvStr
  Push QGARLIB
  Call un.DeleteEnvStr

  # ------------------------------------------------------------------
  # Delete specific installed files
  Delete $INSTDIR\Uninstall.exe
  Delete $INSTDIR\*.exe
  Delete $INSTDIR\qgar.ico

  # ------------------------------------------------------------------
  # Remove each directory copied
  RMDir /r $INSTDIR\bin
  RMDir /r $INSTDIR\QgarDoc
  RMDir /r $INSTDIR\include
  RMDir /r $INSTDIR\share
  RMDir /r $INSTDIR\lib
  

  # ------------------------------------------------------------------
  # Delete the shortcuts created in user's startmenu
  Delete "$SMPROGRAMS\Qgar\Applications.lnk"
  Delete "$SMPROGRAMS\Qgar\QgarGUI.lnk"
  Delete "$SMPROGRAMS\Qgar\Documentation.lnk"
  Delete "$SMPROGRAMS\Qgar\Uninstall.lnk"
  RMDir "$SMPROGRAMS\Qgar"

  # Remove the Qgar dir only if it's empty. 
  # Otherwise, it's kept with no Qgar contents
  # (possible user files).
  RMDir $INSTDIR

SectionEnd
