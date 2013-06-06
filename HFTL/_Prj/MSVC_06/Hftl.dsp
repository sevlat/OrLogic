# Microsoft Developer Studio Project File - Name="Hftl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Hftl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Hftl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Hftl.mak" CFG="Hftl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Hftl - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Hftl - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Hftl - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\_Output\MSVC_06\Release\Hftl"
# PROP Intermediate_Dir "..\..\..\..\_Output\MSVC_06\Release\Hftl"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../../../" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Hftl - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\_Output\MSVC_06\Debug\Hftl"
# PROP Intermediate_Dir "..\..\..\..\_Output\MSVC_06\Debug\Hftl"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../../../" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "Hftl - Win32 Release"
# Name "Hftl - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\Z.cpp
# SUBTRACT CPP /YX
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\Grid\g_Ruler.h
# End Source File
# Begin Source File

SOURCE=..\..\Main\m_Angle.h
# End Source File
# Begin Source File

SOURCE=..\..\Main\m_Compare.h
# End Source File
# Begin Source File

SOURCE=..\..\Main\m_Consts.h
# End Source File
# Begin Source File

SOURCE=..\..\Main\m_Function.h
# End Source File
# Begin Source File

SOURCE=..\..\Main\m_iplSegPoint.h
# End Source File
# Begin Source File

SOURCE=..\..\Main\m_iplTrans.h
# End Source File
# Begin Source File

SOURCE=..\..\Main\m_iplTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\Main\m_Memory.h
# End Source File
# Begin Source File

SOURCE=..\..\Main\m_MinMax.h
# End Source File
# Begin Source File

SOURCE=..\..\Main\m_Optional.h
# End Source File
# Begin Source File

SOURCE=..\..\Main\m_OptionalTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\Main\m_Scale.h
# End Source File
# Begin Source File

SOURCE=..\..\Main\m_SegPoint.h
# End Source File
# Begin Source File

SOURCE=..\..\Main\m_stlUtils.h
# End Source File
# Begin Source File

SOURCE=..\..\Main\m_Trans.h
# End Source File
# Begin Source File

SOURCE=..\..\Main\m_Utils.h
# End Source File
# Begin Source File

SOURCE=..\..\Win\w_Gdi.h
# End Source File
# Begin Source File

SOURCE=..\..\Win\w_iplDcUtils.h
# End Source File
# Begin Source File

SOURCE=..\..\Win\w_iplDrawing.h
# End Source File
# Begin Source File

SOURCE=..\..\Win\w_iplUtils.h
# End Source File
# Begin Source File

SOURCE=..\..\Win\w_iplWndUtils.h
# End Source File
# Begin Source File

SOURCE=..\..\Win\w_Utils.h
# End Source File
# Begin Source File

SOURCE=..\..\Extra\x_ErsatzValue.h
# End Source File
# End Group
# End Target
# End Project
