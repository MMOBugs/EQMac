/*****************************************************************************
    MQ2Main.dll: MacroQuest2's extension DLL for EverQuest
    Copyright (C) 2002-2003 Plazmic, 2003-2004 Lax

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License, version 2, as published by
    the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
******************************************************************************/

#define VersionString "EqMac PC Edition"
#define DebugHeader "[MQ2 (EqMac]"
#define LoadedString "MQ2 (EqMac) Loaded."
#define ToUnloadString "MQ2 (EqMac) Unloading..."
#define UnloadedString "MQ2 (EqMac) Unloaded."

#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x510
#define DIRECTINPUT_VERSION 0x800

// uncomment this line to turn off the single-line benchmark macro
// #define DISABLE_BENCHMARKS

#pragma warning(disable:4786)
#pragma warning(disable:4530)
// Windows Header Files:
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "..\Dxsdk81\include\dinput.h"
#include <time.h>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <winsock.h>
#include <math.h>
#include <map>
#include <string>
#include <algorithm>
using namespace std;
#include "..\Detours\inc\detours.h" 
#include "eqgame.h"

#ifdef EQLIB_EXPORTS
#define EQLIB_API extern "C" __declspec(dllexport)
#define EQLIB_VAR extern "C" __declspec(dllexport)
#define EQLIB_OBJECT __declspec(dllexport)
#else
#define EQLIB_API extern "C" __declspec(dllimport)
#define EQLIB_VAR extern "C" __declspec(dllimport)
#define EQLIB_OBJECT __declspec(dllimport)
#endif

#ifdef MQ2PLUGIN
#define FromPlugin 1
#else
#define FromPlugin 0
#endif

// Lax/Blech event support *READY*
#define USEBLECHEVENTS

#include "..\Blech\Blech.h"

// reroute malloc/free
EQLIB_API VOID *MQ2Malloc(size_t size);
EQLIB_API VOID MQ2Free(VOID *memblock);
/*
#ifdef MQ2PLUGIN
#define malloc(x) MQ2Malloc(x)
#define free(x) MQ2Free(x)
#else
#ifdef DEBUG_ALLOC
#define malloc(x) MQ2Malloc(x)
#define free(x) MQ2Free(x)
#endif
#endif
*/
#ifdef DEBUG_ALLOC
extern DWORD CountMallocs;
extern DWORD CountFrees;
#endif

#define FUNCTION_AT_ADDRESS(function,offset) __declspec(naked) function\
{\
	__asm{mov eax, offset};\
	__asm{jmp eax};\
}

#define FUNCTION_AT_VARIABLE_ADDRESS(function,variable) __declspec(naked) function\
{\
	__asm{mov eax, variable};\
	__asm{lea eax, [eax]};\
	__asm{mov eax, [eax]};\
	__asm{jmp eax};\
}

#define FUNCTION_AT_VIRTUAL_ADDRESS(function,virtualoffset) __declspec(naked) function\
{\
	__asm{mov eax, [ecx]};\
	__asm{lea eax, [eax+virtualoffset]};\
	__asm{mov eax, [eax]};\
	__asm{jmp eax};\
}

#define PreserveRegisters(code) \
{\
	__asm {push eax};\
	__asm {push ebx};\
	__asm {push ecx};\
	__asm {push edx};\
	__asm {push esi};\
	__asm {push edi};\
	code;\
	__asm {pop edi};\
	__asm {pop esi};\
	__asm {pop edx};\
	__asm {pop ecx};\
	__asm {pop ebx};\
	__asm {pop eax};\
}

#define SetWndNotification(thisclass) \
{\
	int (thisclass::*pfWndNotification)(CXWnd *pWnd, unsigned int Message, void *unknown)=&thisclass::WndNotification;\
	SetvfTable(33,*(DWORD*)&pfWndNotification);\
}

#define EzDetour(offset,detour,trampoline) AddDetourf((DWORD)offset,detour,trampoline)
#ifndef DOUBLE
typedef double DOUBLE;
#endif
#ifndef THIS_
#define THIS_                   INTERFACE FAR* This,
#endif

// DEBUGGING
//#ifndef DEBUG_TRY
//#define DEBUG_TRY
//#endif
#ifdef DEBUG_TRY
#define DebugTry(x) DebugSpew("Trying %s",#x);x;DebugSpew("%s complete",#x)
#else
#define DebugTry(x) x
#endif

#define MakeLower(yourstring) transform (yourstring.begin(),yourstring.end(), yourstring.begin(), tolower);

#define MAX_VARNAME 64
#define MAX_STRING            2048


#include "EQData.h"
#include "EQUIStructs.h"

//class CXMLData *GetXMLData(class CXWnd *pWnd)

#include "EQClasses.h"

#include "MQ2Prototypes.h"
#include "MQ2Internal.h"
#include "MQ2Globals.h"



/* BENCHMARKING */
#ifdef DISABLE_BENCHMARKS
#define Benchmark(BMHandle,code) code
#else
#define Benchmark(BMHandle,code) {EnterMQ2Benchmark(BMHandle);code;ExitMQ2Benchmark(BMHandle);}
#endif
EQLIB_API VOID ShutdownMQ2Benchmarks();
EQLIB_API VOID InitializeMQ2Benchmarks();
EQLIB_API BOOL GetMQ2Benchmark(DWORD BMHandle, MQBENCH &Dest);
EQLIB_API VOID ExitMQ2Benchmark(DWORD BMHandle);
EQLIB_API VOID EnterMQ2Benchmark(DWORD BMHandle);
EQLIB_API VOID RemoveMQ2Benchmark(DWORD BMHandle);
EQLIB_API DWORD AddMQ2Benchmark(PCHAR Name);

/* SPAWN HANDLING */
EQLIB_API VOID InitializeMQ2Spawns();
EQLIB_API VOID ShutdownMQ2Spawns();
EQLIB_API VOID ProcessPendingGroundItems();
EQLIB_API VOID UpdateMQ2SpawnSort();
EQLIB_API BOOL SetNameSpriteState(PSPAWNINFO pSpawn, bool Show);

/* WINDOWS */
EQLIB_API VOID InitializeMQ2Windows();
EQLIB_API VOID ShutdownMQ2Windows();
EQLIB_API void RemoveXMLFile(const char *filename);
EQLIB_API void AddXMLFile(const char *filename);
EQLIB_API bool SendWndClick(PCHAR WindowName, PCHAR ScreenID, PCHAR ClickNotification);
EQLIB_API bool SendWndNotification(PCHAR WindowName, PCHAR ScreenID, DWORD Notification, VOID *Data=0);
EQLIB_API void AddWindow(char *WindowName, CXWnd **ppWindow);
EQLIB_API void RemoveWindow(char *WindowName);
EQLIB_API CXWnd *FindMQ2Window(PCHAR Name);

EQLIB_API VOID CreateMQ2NewsWindow();
EQLIB_API VOID DeleteMQ2NewsWindow();

/* CHAT HOOK */
EQLIB_API VOID InitializeChatHook();
EQLIB_API VOID ShutdownChatHook();
EQLIB_API VOID dsp_chat_no_events(const char *,int,bool);

/* DETOURING API */
EQLIB_API VOID InitializeMQ2Detours();
EQLIB_API VOID ShutdownMQ2Detours();
EQLIB_API BOOL AddDetour(DWORD address, PBYTE pfDetour=0, PBYTE pfTrampoline=0, DWORD Count=20);
EQLIB_API VOID AddDetourf(DWORD address, ...);
EQLIB_API VOID RemoveDetour(DWORD address);

/* PLUGIN HANDLING */
EQLIB_API VOID InitializeMQ2Plugins();
EQLIB_API DWORD LoadMQ2Plugin(const PCHAR pszFilename);
EQLIB_API BOOL UnloadMQ2Plugin(const PCHAR pszFilename);
EQLIB_API VOID UnloadMQ2Plugins();
EQLIB_API VOID ShutdownMQ2Plugins();
EQLIB_API VOID WriteChatf(PCHAR Format, ...);
EQLIB_API VOID WriteChatColor(PCHAR Line, DWORD Color=USERCOLOR_DEFAULT, DWORD Filter=0);
EQLIB_API VOID PulsePlugins();
EQLIB_API VOID PluginsZoned();
EQLIB_API BOOL PluginsIncomingChat(PCHAR Line, DWORD Color);
EQLIB_API VOID RewriteMQ2Plugins(VOID);
EQLIB_API VOID PluginsCleanUI();
EQLIB_API VOID PluginsReloadUI();
EQLIB_API VOID PluginsSetGameState(DWORD GameState);
EQLIB_API VOID PluginsDrawHUD();
EQLIB_API VOID PluginsAddSpawn(PSPAWNINFO pNewSpawn);
EQLIB_API VOID PluginsRemoveSpawn(PSPAWNINFO pSpawn);
EQLIB_API VOID PluginsAddGroundItem(PGROUNDITEM pNewGroundItem);
EQLIB_API VOID PluginsRemoveGroundItem(PGROUNDITEM pGroundItem);
EQLIB_API VOID PluginsDamaged(PSPAWNINFO pOffender,PSPAWNINFO pDefender,DWORD Damage);

/* DIRECT INPUT */
EQLIB_API VOID InitializeMQ2DInput();
EQLIB_API VOID ShutdownMQ2DInput();

/* CLEAN UI */
EQLIB_API VOID InitializeDisplayHook();
EQLIB_API VOID ShutdownDisplayHook();
EQLIB_API VOID DrawHUD();

/* COMMAND HANDLING */
EQLIB_API VOID InitializeMQ2Commands();
EQLIB_API VOID ShutdownMQ2Commands();
EQLIB_API VOID AddCommand(PCHAR Command, fEQCommand Function, BOOL EQ=0, BOOL Parse=1, BOOL InGame=0);
EQLIB_API VOID AddAlias(PCHAR ShortCommand, PCHAR LongCommand);
EQLIB_API BOOL RemoveAlias(PCHAR ShortCommand);
EQLIB_API VOID AddSubstitute(PCHAR Original, PCHAR Substitution);
EQLIB_API BOOL RemoveSubstitute(PCHAR Original);
EQLIB_API BOOL RemoveCommand(PCHAR Command);
EQLIB_API VOID DoTimedCommands();
EQLIB_API VOID TimedCommand(PCHAR Command, DWORD msDelay);

/* MACRO COMMANDS */
EQLIB_API VOID DumpStack                           (PSPAWNINFO,PCHAR);
EQLIB_API VOID EndMacro                            (PSPAWNINFO,PCHAR);
EQLIB_API VOID Echo									(PSPAWNINFO,PCHAR);


/* MACRO PARSING */
#ifdef USEBLECHEVENTS
void __stdcall EventBlechCallback(unsigned int ID, void * pData, PBLECHVALUE pValues);
#endif
#define PMP_ERROR_BADPARM 10000
EQLIB_API PCHAR ParseMacroParameter(PSPAWNINFO pChar, PCHAR szOriginal);
EQLIB_API VOID FailIf(PSPAWNINFO pChar, PCHAR szCommand, PMACROBLOCK pStartLine, BOOL All=FALSE);
EQLIB_API VOID InitializeParser();
EQLIB_API VOID ShutdownParser();

EQLIB_API VOID InitializeMQ2DataTypes();
EQLIB_API VOID ShutdownMQ2DataTypes();
EQLIB_API VOID InitializeMQ2Data();
EQLIB_API VOID ShutdownMQ2Data();
EQLIB_API BOOL ParseMacroData(PCHAR szOriginal);
EQLIB_API BOOL ParseMacroVariables(PCHAR szOriginal);
EQLIB_API BOOL AddMQ2Data(PCHAR szName, fMQData Function);
EQLIB_API BOOL RemoveMQ2Data(PCHAR szName);
EQLIB_API MQ2Type *FindMQ2DataType(PCHAR szName);
EQLIB_API PMQ2DATAITEM FindMQ2Data(PCHAR szName);
EQLIB_API PDATAVAR FindMQ2DataVariable(PCHAR szName);
EQLIB_API BOOL ParseMQ2DataPortion(PCHAR szOriginal, MQ2TYPEVAR &Result);


/* MOUSE */
EQLIB_API BOOL IsMouseWaiting(VOID);
EQLIB_API BOOL IsMouseWaitingForButton();

/* KEY BINDS */
EQLIB_API VOID InitializeMQ2KeyBinds();
EQLIB_API VOID ShutdownMQ2KeyBinds();
EQLIB_API BOOL PressMQ2KeyBind(PCHAR name, BOOL Hold);
EQLIB_API BOOL SetMQ2KeyBind(PCHAR name, BOOL Alternate, KeyCombo &Combo);
EQLIB_API BOOL AddMQ2KeyBind(PCHAR name, fMQExecuteCmd Function);
EQLIB_API BOOL RemoveMQ2KeyBind(PCHAR name);
EQLIB_API BOOL GetMQ2KeyBind(PCHAR name, BOOL Alt, KeyCombo &Combo);
EQLIB_API BOOL DumpBinds(PCHAR Filename);
EQLIB_API BOOL MQ2HandleKeyDown(class KeyCombo const &Combo,bool mqcall = 0);
EQLIB_API BOOL MQ2HandleKeyUp(class KeyCombo const &Combo,bool mqcall = 0);

/* PULSING */
EQLIB_API VOID InitializeMQ2Pulse();
EQLIB_API VOID ShutdownMQ2Pulse();
EQLIB_API DWORD GetGameState();

/* OTHER IMPORTED FROM EQ */
EQLIB_API int CastRay(PSPAWNINFO,float y,float x,float z);

/* UTILITIES */
EQLIB_API VOID ConvertCR(PCHAR Text);
EQLIB_API VOID DrawHUDText(PCHAR Text, DWORD X, DWORD Y, DWORD Argb);
EQLIB_API VOID FixStringTable();
EQLIB_API VOID SafeSpewFile(PCHAR szFormat, ...);
EQLIB_API VOID DebugSpew(PCHAR szFormat, ...);
EQLIB_API VOID DebugSpewAlways(PCHAR szFormat, ...);
EQLIB_API VOID DebugSpewNoFile(PCHAR szFormat, ...);
EQLIB_API PSTR GetNextArg(PCSTR szLine, DWORD dwNumber = 1, BOOL CSV = FALSE, CHAR Separator = 0);
EQLIB_API PSTR GetArg(PSTR szDest, PCSTR szSrc, DWORD dwNumber, BOOL LeaveQuotes = FALSE, BOOL ToParen = FALSE, BOOL CSV = FALSE, CHAR Separator = 0, BOOL AnyNonAlphaNum = FALSE);
EQLIB_API VOID AddCustomEvent(PEVENTLIST pEList, PCHAR szLine);
EQLIB_API FLOAT DistanceToSpawn(PSPAWNINFO pChar, PSPAWNINFO pSpawn);
EQLIB_API PCHAR GetEQPath(PCHAR szBuffer);
#define DoCommand(pspawninfo,commandtoexecute) HideDoCommand(pspawninfo,commandtoexecute,FromPlugin)
EQLIB_API VOID HideDoCommand(PSPAWNINFO pChar, PCHAR szLine, BOOL delayed);
#define EzCommand(commandtoexecute) DoCommand((PSPAWNINFO)pLocalPlayer,commandtoexecute)

EQLIB_API VOID AppendCXStr(PCXSTR *cxstr, PCHAR text); 
EQLIB_API VOID SetCXStr(PCXSTR *cxstr, PCHAR text); 
EQLIB_API DWORD GetCXStr(PCXSTR pCXStr, PCHAR szBuffer, DWORD maxlen=MAX_STRING);
EQLIB_API DWORD MQToSTML(PCHAR in, PCHAR out, DWORD maxlen=MAX_STRING, DWORD ColorOverride=0xFFFFFF);
EQLIB_API VOID StripMQChat(PCHAR in, PCHAR out);
EQLIB_API VOID STMLToPlainText(PCHAR in, PCHAR out);
EQLIB_API PCHAR GetSubFromLine(PMACROBLOCK pLine, PCHAR szSub);
EQLIB_API PCHAR GetFilenameFromFullPath(PCHAR Filename);
EQLIB_API BOOL CompareTimes(PCHAR RealTime, PCHAR ExpectedTime);
EQLIB_API VOID AddFilter(PCHAR szFilter, DWORD Length, PBOOL pEnabled);
EQLIB_API VOID DefaultFilters(VOID);
EQLIB_API PCHAR ConvertHotkeyNameToKeyName(PCHAR szName);
EQLIB_API VOID CheckChatForEvent(PCHAR szMsg);
EQLIB_API VOID ConvertItemTags(CXStr &cxstr, BOOL Tag=TRUE);
EQLIB_API BOOL ParseKeyCombo(PCHAR text, KeyCombo &Dest);
EQLIB_API PCHAR DescribeKeyCombo(KeyCombo &Combo, PCHAR szDest);
EQLIB_API int FindInvSlotForContents(PITEMINFO pContents);
EQLIB_API int FindInvSlot(PCHAR Name, BOOL Exact);
EQLIB_API int FindNextInvSlot(PCHAR Name, BOOL Exact);
EQLIB_API int FindMappableCommand(const char *name);

EQLIB_API int GetLanguageIDByName(PCHAR szName);
EQLIB_API PCHAR GetSpellNameByID(DWORD dwSpellID);
EQLIB_API PSPELL GetSpellByName(PCHAR szName);
#include "MQ2Inlines.h"
#include "MQ2DataTypes.h"

EQLIB_API PMACROBLOCK AddMacroLine(PCHAR szLine);
EQLIB_API PCHAR GetLightForSpawn(PSPAWNINFO pSpawn);
EQLIB_API DWORD GetSpellDuration(PSPELL pSpell, PSPAWNINFO pSpawn);
EQLIB_API DWORD GetDeityTeamByID(DWORD DeityID);
EQLIB_API DWORD ConColor(PSPAWNINFO pSpawn);
EQLIB_API PCHAR GetGuildByID(DWORD GuildID);
EQLIB_API DWORD GetGuildIDByName(PCHAR szGuild);
EQLIB_API PITEMINFO GetEnviroContainer();
EQLIB_API PEQCONTAINERWINDOW FindContainerForContents(PITEMINFO pContents);
EQLIB_API FLOAT FindSpeed(PSPAWNINFO pSpawn);
EQLIB_API VOID GetItemLinkHash(PITEMINFO Item, PCHAR Buffer);
EQLIB_API VOID GetItemLink(PITEMINFO Item, PCHAR Buffer);
EQLIB_API VOID SendEQMessage(DWORD PacketType, PVOID pData, DWORD Length);
EQLIB_API PCHAR GetLoginName();
EQLIB_API FLOAT DistanceToPoint(PSPAWNINFO pSpawn, FLOAT xLoc, FLOAT yLoc);
EQLIB_API PCHAR ShowSpellSlotInfo(PSPELL pSpell, PCHAR szBuffer);
EQLIB_API VOID SlotValueCalculate(PCHAR szBuff, PSPELL pSpell, int i, double mp);
EQLIB_API PCHAR GetSpellEffectName(WORD EffectID, PCHAR szBuffer);
EQLIB_API VOID GetGameDate(int* Month, int* Day, int* Year);
EQLIB_API VOID GetGameTime(int* Hour, int* Minute, int* Night);
EQLIB_API VOID SyntaxError(PCHAR szFormat, ...);
EQLIB_API VOID MacroError(PCHAR szFormat, ...);
EQLIB_API VOID FatalError(PCHAR szFormat, ...);
EQLIB_API VOID MQ2DataError(PCHAR szFormat, ...);

/* MQ2DATAVARS */
EQLIB_API PCHAR GetFuncParam(PCHAR szMacroLine, DWORD ParamNum, PCHAR szParamName, PCHAR szParamType);
EQLIB_API PDATAVAR FindMQ2DataVariable(PCHAR Name);
EQLIB_API BOOL AddMQ2DataVariable(PCHAR Name, PCHAR Index, MQ2Type *pType, PDATAVAR *ppHead, PCHAR Default);
EQLIB_API PDATAVAR *FindVariableScope(PCHAR Name);
EQLIB_API BOOL DeleteMQ2DataVariable(PCHAR Name);
EQLIB_API VOID ClearMQ2DataVariables(PDATAVAR *ppHead);
EQLIB_API VOID NewDeclareVar(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID NewDeleteVarCmd(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID NewVarset(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID NewVarcalc(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID NewVardata(PSPAWNINFO pChar, PCHAR szLine);

EQLIB_API VOID DropTimers(VOID);

/*                 */

EQLIB_API BOOL LoadCfgFile(PCHAR Filename, BOOL Delayed=FromPlugin);
EQLIB_API PCHAR GetFriendlyNameForGroundItem(PGROUNDITEM pItem, PCHAR szName);
EQLIB_API VOID ClearSearchSpawn(PSEARCHSPAWN pSearchSpawn);
EQLIB_API PSPAWNINFO NthNearestSpawn(PSEARCHSPAWN pSearchSpawn, DWORD Nth, PSPAWNINFO pOrigin, BOOL IncludeOrigin=FALSE);
EQLIB_API DWORD CountMatchingSpawns(PSEARCHSPAWN pSearchSpawn, PSPAWNINFO pOrigin, BOOL IncludeOrigin=FALSE);
EQLIB_API PSPAWNINFO SearchThroughSpawns(PSEARCHSPAWN pSearchSpawn, PSPAWNINFO pChar);
EQLIB_API BOOL SpawnMatchesSearch(PSEARCHSPAWN pSearchSpawn, PSPAWNINFO pChar, PSPAWNINFO pSpawn);
EQLIB_API PCHAR ParseSearchSpawnArgs(PCHAR szArg, PCHAR szRest, PSEARCHSPAWN pSearchSpawn);
EQLIB_API VOID ParseSearchSpawn(PCHAR Buffer, PSEARCHSPAWN pSearchSpawn);
EQLIB_API PCHAR FormatSearchSpawn(PCHAR Buffer, PSEARCHSPAWN pSearchSpawn);
EQLIB_API BOOL IsPCNear(PSPAWNINFO pSpawn, FLOAT Radius);
EQLIB_API BOOL IsInGroup(PSPAWNINFO pSpawn);
EQLIB_API BOOL IsAlert(PSPAWNINFO pChar, PSPAWNINFO pSpawn, DWORD List);

EQLIB_API VOID        OverwriteTable          (DWORD Address);
EQLIB_API DWORD       Include                 (PCHAR szFile);
EQLIB_API PCHAR       GetFullZone             (DWORD ZoneID);
EQLIB_API DWORD       GetZoneID               (PCHAR ZoneShortName);
EQLIB_API PCHAR       GetShortZone            (DWORD ZoneID);
EQLIB_API PCHAR       CleanupName             (PCHAR szName, BOOL Article = TRUE);
//EQLIB_API VOID        SwapSWho                (PSWHOSORT pSWho1, PSWHOSORT pSWho2);
//EQLIB_API VOID        SortSWho                (PSWHOSORT pSWhoSort, DWORD SpawnCount, DWORD SortBy = 0);
//EQLIB_API VOID        SuperWhoFindPets        (PSPAWNINFO pChar, WORD SpawnID);
//EQLIB_API VOID        SuperWhoDisplay         (PSPAWNINFO pChar, PSEARCHSPAWN pFilter, PSPAWNINFO psTarget, WORD Padding = 0, DWORD Color = 0);
EQLIB_API FLOAT       DistanceToSpawn3D       (PSPAWNINFO pChar, PSPAWNINFO pSpawn);
EQLIB_API FLOAT       EstimatedDistanceToSpawn(PSPAWNINFO pChar, PSPAWNINFO pSpawn);
EQLIB_API PMACROBLOCK AddMacroLine            (PCHAR szLine);
EQLIB_API PSPAWNINFO  GetClosestAlert         (PSPAWNINFO pChar,DWORD List, DWORD* pdwCount);
EQLIB_API VOID        FreeAlertList           (PALERTLIST pAlertList);
EQLIB_API DWORD WINAPI InsertCommands         (LPVOID lpParameter);
EQLIB_API VOID        UpdateMonitoredSpawns   (VOID);
EQLIB_API PCHAR       GetModel                (PSPAWNINFO pSpawn, DWORD Slot);
//EQLIB_API PSPAWNINFO  GetPet                  (DWORD OwnerID);
//EQLIB_API BOOL        IfCompare               (PCHAR szCond);
EQLIB_API FLOAT StateHeightMultiplier(DWORD StandState);

EQLIB_API bool        InHoverState();

EQLIB_API BOOL Calculate(PCHAR szFormula, DOUBLE& Dest);

/* DATA ITEMS */
EQLIB_API BOOL dataSpawn(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataTarget(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataCharacter(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataSpell(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataSwitch(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataGroundItem(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataMerchant(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataWindow(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataMacro(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataMacroQuest(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataMath(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataZone(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataGroup(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataString(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataInt(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataBool(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataFloat(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataCorpse(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataIf(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataCursor(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataNearestSpawn(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataGameTime(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataTime(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataIni(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataHeading(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataDefined(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataLastSpawn(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataInvSlot(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataFindItem(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataSelectedItem(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataFindItemBank(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataFindItemCount(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataFindItemBankCount(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataGroupLeader(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataGroupLeaderName(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataSkill(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataAltAbility(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataRaid(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataNamingSpawn(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataSpawnCount(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataLineOfSight(PCHAR szIndex, MQ2TYPEVAR &Ret);
EQLIB_API BOOL dataPlugin(PCHAR szIndex, MQ2TYPEVAR &Ret);

/* COMMANDS */
EQLIB_API VOID NoModKeyCmd(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID CaptionColorCmd(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID NoParseCmd(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID CaptionCmd(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID HudCmd(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID DropCmd(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID CombineCmd(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID EnviroCloseCmd(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID ClearErrorsCmd(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID DeleteVarCmd(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID NewIf(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID DoTimedCmd(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID DoShiftCmd(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID DoCtrlCmd(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID DoAltCmd(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID DoCommandCmd(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID SquelchCommand(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID DumpBindsCommand(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID LoadCfgCommand(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID do_ranged(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID DoMappable(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID MQ2KeyBindCommand(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID MultilineCommand(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID Alert                               (PSPAWNINFO,PCHAR);
EQLIB_API VOID Alias                               (PSPAWNINFO,PCHAR);
EQLIB_API VOID BankList                            (PSPAWNINFO,PCHAR);
EQLIB_API VOID Breakin                             (PSPAWNINFO,PCHAR);
EQLIB_API VOID BuyItem                             (PSPAWNINFO,PCHAR);
EQLIB_API VOID Call                                (PSPAWNINFO,PCHAR);
EQLIB_API VOID CharInfo                            (PSPAWNINFO,PCHAR);
EQLIB_API VOID Cast                                (PSPAWNINFO,PCHAR);
EQLIB_API VOID Cleanup                             (PSPAWNINFO,PCHAR);
EQLIB_API VOID Click                               (PSPAWNINFO,PCHAR);
EQLIB_API VOID DebugSpewFile                       (PSPAWNINFO,PCHAR);
EQLIB_API VOID DeclareVar                          (PSPAWNINFO,PCHAR);
EQLIB_API VOID Delay                               (PSPAWNINFO,PCHAR);
EQLIB_API VOID EQDestroyHeldItemOrMoney				(PSPAWNINFO,PCHAR);
EQLIB_API VOID DisplayLoginName						(PSPAWNINFO,PCHAR);
EQLIB_API VOID DoAbility                           (PSPAWNINFO,PCHAR);
EQLIB_API VOID DoEvents                            (PSPAWNINFO,PCHAR);
EQLIB_API VOID DoSocial                           (PSPAWNINFO,PCHAR);
EQLIB_API VOID Doors                               (PSPAWNINFO,PCHAR);
EQLIB_API VOID DoorTarget                          (PSPAWNINFO,PCHAR);
EQLIB_API VOID DumpStack                           (PSPAWNINFO,PCHAR);
EQLIB_API VOID Echo                                (PSPAWNINFO,PCHAR);
EQLIB_API VOID EditMacro                           (PSPAWNINFO,PCHAR);
EQLIB_API VOID EndMacro                            (PSPAWNINFO,PCHAR);
EQLIB_API VOID Exec                                (PSPAWNINFO,PCHAR); 
EQLIB_API VOID Face                                (PSPAWNINFO,PCHAR);
EQLIB_API VOID Filter                              (PSPAWNINFO,PCHAR);
EQLIB_API VOID For                                 (PSPAWNINFO,PCHAR);
EQLIB_API VOID Goto                                (PSPAWNINFO,PCHAR);
EQLIB_API VOID Help                                (PSPAWNINFO,PCHAR);
EQLIB_API VOID Hotkey                              (PSPAWNINFO,PCHAR);
EQLIB_API VOID Identify                            (PSPAWNINFO,PCHAR);
EQLIB_API VOID IniOutput                           (PSPAWNINFO,PCHAR);
EQLIB_API VOID Items                               (PSPAWNINFO,PCHAR);
EQLIB_API VOID ItemTarget                          (PSPAWNINFO,PCHAR);
EQLIB_API VOID KeepKeys                            (PSPAWNINFO,PCHAR);
EQLIB_API VOID WindowState							(PSPAWNINFO,PCHAR);
EQLIB_API VOID ListMacros                          (PSPAWNINFO,PCHAR);
EQLIB_API VOID LoadSpells                          (PSPAWNINFO,PCHAR);
EQLIB_API VOID Location                            (PSPAWNINFO,PCHAR);
EQLIB_API VOID Look                                (PSPAWNINFO,PCHAR);
EQLIB_API VOID Macro                               (PSPAWNINFO,PCHAR);
EQLIB_API VOID MacroBeep                           (PSPAWNINFO,PCHAR);
EQLIB_API VOID MacroLog                            (PSPAWNINFO,PCHAR);
EQLIB_API VOID MacroPause                          (PSPAWNINFO,PCHAR);
EQLIB_API VOID MemSpell                            (PSPAWNINFO,PCHAR);
EQLIB_API VOID MouseTo                             (PSPAWNINFO,PCHAR);
EQLIB_API VOID MQMsgBox                            (PSPAWNINFO,PCHAR);
EQLIB_API VOID Next                                (PSPAWNINFO,PCHAR);
EQLIB_API VOID PluginCommand						(PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API VOID Return                              (PSPAWNINFO,PCHAR);
EQLIB_API VOID SellItem                            (PSPAWNINFO,PCHAR);
EQLIB_API VOID SetAutoRun                          (PSPAWNINFO,PCHAR);
EQLIB_API VOID SetError                            (PSPAWNINFO,PCHAR);
EQLIB_API VOID Skills                              (PSPAWNINFO,PCHAR);
EQLIB_API VOID Substitute						   (PSPAWNINFO,PCHAR);
EQLIB_API VOID SuperWho                            (PSPAWNINFO,PCHAR);
EQLIB_API VOID SuperWhoTarget                      (PSPAWNINFO,PCHAR);
EQLIB_API VOID SWhoFilter							(PSPAWNINFO,PCHAR);
EQLIB_API VOID Target                              (PSPAWNINFO,PCHAR);
EQLIB_API VOID Unload                              (PSPAWNINFO,PCHAR);
EQLIB_API VOID UpdateItemInfo                      (PSPAWNINFO,PCHAR);
EQLIB_API VOID Where                               (PSPAWNINFO,PCHAR);
EQLIB_API VOID ZapVars                             (PSPAWNINFO,PCHAR);
EQLIB_API VOID PopupText                           (PSPAWNINFO,PCHAR);
EQLIB_API void DisplayOverlayText(PCHAR szText, DWORD dwColor, DWORD dwTransparency, DWORD msFadeIn, DWORD msFadeOut, DWORD msHold);

// OTHER SHIT

#define LIGHT_COUNT     13
#define MAX_COMBINES    52
#define MAX_ITEMTYPES   53

#define GAMESTATE_CHARSELECT    1
#define GAMESTATE_SOMETHING     4
#define GAMESTATE_INGAME        5
#define GAMESTATE_PRECHARSELECT 6
#define GAMESTATE_LOGGINGIN     253
#define GAMESTATE_UNLOADING     255
//ok ive only done XWM_HISTORY for eqmac the rest needs checking
#define XWM_LCLICK				1
#define XWM_LMOUSEUP			2
#define XWM_RCLICK				3
#define XWM_HITENTER			6
#define XWM_CLOSE				10
#define XWM_NEWVALUE	        14
#define XWM_UNKNOWN				0x13//calls this trigger: ChannelServerApi__GetChannelName,CListWnd__GetItemAtPoint
#define XWM_MOUSEOVER			0x19
#define XWM_HISTORY				0x15//for eqmac
#define XWM_RCLICKHOLD			0x17
#define XWM_ALLCHATHERE			0x2b //Your chat input will go to the current active chat window.

#define XKF_SHIFT				1
#define XKF_CTRL				2
#define XKF_LALT				4
#define XKF_RALT				8

#define MAX_ITEM4xx			416

#define MAX_WEAPONS		0x000000ff

#define MQ2AUTH(z) EQLIB_API VOID z(DWORD x);
#include "MQ2Auth0.h"

EQLIB_API VOID memcheck5_tramp(PVOID,DWORD,PCHAR,DWORD,BOOL); 
EQLIB_API VOID memcheck5(PVOID,DWORD,PCHAR,DWORD,BOOL);
EQLIB_API int memcheck0(unsigned char *, int, struct mckey);
