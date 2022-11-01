# Microsoft Developer Studio Generated NMAKE File, Based on MQ2MoveUtils.dsp
!IF "$(CFG)" == ""
CFG=MQ2MoveUtils - Win32 Release
!MESSAGE No configuration specified. Defaulting to MQ2MoveUtils - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "MQ2MoveUtils - Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MQ2MoveUtils.mak" CFG="MQ2MoveUtils - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MQ2MoveUtils - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

OUTDIR=.\../Release
INTDIR=.\Intermediate
# Begin Custom Macros
OutDir=.\../Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\MQ2MoveUtils.dll"

!ELSE 

ALL : "MQ2Main - Win32 Release" "macroquest - Win32 Release" "$(OUTDIR)\MQ2MoveUtils.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"macroquest - Win32 ReleaseCLEAN" "MQ2Main - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\MQ2MoveUtils.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\MQ2MoveUtils.dll"
	-@erase "$(OUTDIR)\MQ2MoveUtils.exp"
	-@erase "$(OUTDIR)\MQ2MoveUtils.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /Zp1 /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CINTERFACE" /Fp"$(INTDIR)\MQ2MoveUtils.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MQ2MoveUtils.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ..\Detours\lib60\detours.lib ..\Release\MQ2Main.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\MQ2MoveUtils.pdb" /machine:I386 /out:"$(OUTDIR)\MQ2MoveUtils.dll" /implib:"$(OUTDIR)\MQ2MoveUtils.lib" /OPT:ICF 
LINK32_OBJS= \
	"$(INTDIR)\MQ2MoveUtils.obj" \
	"$(OUTDIR)\MQ2Main.lib"

"$(OUTDIR)\MQ2MoveUtils.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("MQ2MoveUtils.dep")
!INCLUDE "MQ2MoveUtils.dep"
!ELSE 
!MESSAGE Warning: cannot find "MQ2MoveUtils.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "MQ2MoveUtils - Win32 Release"
SOURCE=.\MQ2MoveUtils.cpp

"$(INTDIR)\MQ2MoveUtils.obj" : $(SOURCE) "$(INTDIR)"


!IF  "$(CFG)" == "MQ2MoveUtils - Win32 Release"

"macroquest - Win32 Release" : 
   cd "\mq2\macroquest2\MacroQuest"
   $(MAKE) /$(MAKEFLAGS) /F .\MacroQuest.mak CFG="macroquest - Win32 Release" 
   cd "..\MQ2MoveUtils"

"macroquest - Win32 ReleaseCLEAN" : 
   cd "\mq2\macroquest2\MacroQuest"
   $(MAKE) /$(MAKEFLAGS) /F .\MacroQuest.mak CFG="macroquest - Win32 Release" RECURSE=1 CLEAN 
   cd "..\MQ2MoveUtils"

!ENDIF 

!IF  "$(CFG)" == "MQ2MoveUtils - Win32 Release"

"MQ2Main - Win32 Release" : 
   cd "\mq2\macroquest2\MQ2Main"
   $(MAKE) /$(MAKEFLAGS) /F .\MQ2Main.mak CFG="MQ2Main - Win32 Release" 
   cd "..\MQ2MoveUtils"

"MQ2Main - Win32 ReleaseCLEAN" : 
   cd "\mq2\macroquest2\MQ2Main"
   $(MAKE) /$(MAKEFLAGS) /F .\MQ2Main.mak CFG="MQ2Main - Win32 Release" RECURSE=1 CLEAN 
   cd "..\MQ2MoveUtils"

!ENDIF 


!ENDIF 

