#define MQ2PLUGIN
#include "MQ2Main/MQ2Main.h"
#include "MQ2Main/MQ2Globals.h"
#pragma warning(disable:4273) //inconsistent dll linkage warning
#pragma warning(disable:4530)
#pragma comment(lib, "MQ2Main")

#ifdef EQLIB_EXPORTS
#pragma message("EQLIB_EXPORTS")
#else
#pragma message("EQLIB_IMPORTS")
#endif

#define PLUGIN_API extern "C" __declspec(dllexport)
#define PLUGIN_VERSION(X) __declspec(dllexport) float MQ2Version = (float)X


//#define SetINIFileName(ini) sprintf(INIFileName,"%s\\%s",gszINIPath,ini);
extern CHAR INIFileName[MAX_PATH];

#define PreSetup(pluginname) CHAR INIFileName[MAX_PATH]={0};\
BOOL APIENTRY DllMain( HANDLE hModule, \
                       DWORD  ul_reason_for_call, \
                       LPVOID lpReserved\
					 )\
{\
	if (ul_reason_for_call==DLL_PROCESS_ATTACH)\
	{\
	DebugSpewAlways("%s Module Loaded",pluginname );\
	sprintf_s(INIFileName,"%s\\%s.ini",gszINIPath,pluginname);\
	}\
	else if (ul_reason_for_call==DLL_PROCESS_DETACH)\
	DebugSpewAlways("%s Module Unloaded",pluginname);\
    return TRUE;\
}