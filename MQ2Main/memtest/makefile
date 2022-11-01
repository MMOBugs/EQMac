DXSDK=..\..\dxsdk81
INTDIR=.

all: testmem.exe

clean:
    del *.obj

testmem.obj: testmem.c ..\eqlib_memchecks.cpp


testmem.exe: testmem.obj orig.obj  orig2.obj orig3.obj
    link $**  /out:testmem.exe /debugtype:cv /pdb:testmem.pdb /debug /libpath:"..\..\Detours\lib60"

.asm.obj:
    ml.exe /c $<

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "$(DXSDK)\include" /D "_USRDLL" /D "EQLIB_EXPORTS" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "CINTERFACE" /Fp"$(INTDIR)\eqlib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c  /Zi /Zp1 /TP

.c.obj:
    $(CC) $(CPP_PROJ) $< 
