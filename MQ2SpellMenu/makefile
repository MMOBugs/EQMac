!include "../global.mak"

ALL : "$(OUTDIR)\MQ2SpellMenu.dll"

CLEAN :
	-@erase "$(INTDIR)\MQ2SpellMenu.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\MQ2SpellMenu.dll"
	-@erase "$(OUTDIR)\MQ2SpellMenu.exp"
	-@erase "$(OUTDIR)\MQ2SpellMenu.lib"
	-@erase "$(OUTDIR)\MQ2SpellMenu.pdb"


LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ..\Detours\lib60\detours.lib ..\Release\MQ2Main.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\MQ2SpellMenu.pdb" /debug /machine:I386 /out:"$(OUTDIR)\MQ2SpellMenu.dll" /implib:"$(OUTDIR)\MQ2SpellMenu.lib" /OPT:NOICF /OPT:NOREF 
LINK32_OBJS= \
	"$(INTDIR)\MQ2SpellMenu.obj" \
	"$(OUTDIR)\MQ2Main.lib"

"$(OUTDIR)\MQ2SpellMenu.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) $(LINK32_FLAGS) $(LINK32_OBJS)


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("MQ2SpellMenu.dep")
!INCLUDE "MQ2SpellMenu.dep"
!ELSE 
!MESSAGE Warning: cannot find "MQ2SpellMenu.dep"
!ENDIF 
!ENDIF 


SOURCE=.\MQ2SpellMenu.cpp

"$(INTDIR)\MQ2SpellMenu.obj" : $(SOURCE) "$(INTDIR)"

