// MQ2Map.cpp : Defines the entry point for the DLL application.
//

// PLUGIN_API is only to be used for callbacks.  All existing callbacks at this time
// are shown below. Remove the ones your plugin does not use.  Always use Initialize
// and Shutdown for setup and cleanup, do NOT do it in DllMain.



#include "../MQ2Plugin.h"
#include "MQ2Map.h"
PreSetup("MQ2Map");




unsigned long bmMapRefresh=0;

DWORD HighlightColor=0xFF700070;

CHAR MapSpecialClickString[16][MAX_STRING]=
{
	"",// unused, will always target
	"",//SHIFT
	"/maphide id %i",//CTRL
	"",//CTRL|SHIFT
	"/maphighlight id %i",//LALT
	"",//LALT|SHIFT
	"",//LALT|CTRL
	"",//LALT|SHIFT|CTRL
	"",//RALT
	"",//RALT|SHIFT
	"",//RALT|CTRL
	"",//RALT|SHIFT|CTRL
	"",//RALT|LALT
	"",//RALT|LALT|SHIFT
	"",//RALT|LALT|CTRL
	"" //RALT|LALT|SHIFT|CTRL
};

CHAR MapNameString[MAX_STRING]={"%N"};
CHAR MapTargetNameString[MAX_STRING]={"%N"};
SEARCHSPAWN MapFilterCustom = {0};
MAPFILTER MapFilterOptions[] = {
    {"All",          TRUE,-1,         TRUE,MAPFILTER_Invalid,TRUE,   "Enables/disables map functions"},
    {"PC",           FALSE,0xFF00FF,   TRUE,MAPFILTER_All,TRUE,   "Displays PCs"},
    {"PCConColor",   FALSE,-1,         TRUE,MAPFILTER_PC,FALSE,   "Displays PCs in consider colors"},
	{"Group",		 FALSE,0x0080C0,         TRUE,MAPFILTER_PC,FALSE,   "Displays group members in a specific color"},
    {"Mount",        FALSE,0x707070,   TRUE,MAPFILTER_All,TRUE,   "Displays mounts"},
    {"NPC",          FALSE,0x404040,   TRUE,MAPFILTER_All,TRUE,   "Displays NPCs"},
    {"NPCConColor",  FALSE,-1,         TRUE,MAPFILTER_NPC,FALSE,   "Displays NPCs in consider colors"},
    {"Untargetable", FALSE,0x404040,   TRUE,MAPFILTER_All,TRUE,   "Displays Untargetable NPCs"},
    {"Pet",          FALSE,0x707070,   TRUE,MAPFILTER_All,TRUE,   "Displays pets"},
    {"Corpse",       FALSE,0x00C000,   TRUE,MAPFILTER_All,TRUE,   "Displays corpses"},
    {"Chest",        FALSE,0xC08000,   TRUE,MAPFILTER_All,TRUE,   "Displays chestesses"},
    {"Trigger",      FALSE,0xC08000,   TRUE,MAPFILTER_All,TRUE,   "Displays hidden triggers"},
    {"Trap",		 FALSE,0xC08000,   TRUE,MAPFILTER_All,TRUE,    "Displays hidden traps"},
    {"Timer",	     FALSE,0xC08000,   TRUE,MAPFILTER_All,TRUE,   "Displays hidden timers"},
    {"Ground",       FALSE,0xC0C0C0,   TRUE,MAPFILTER_All,TRUE,   "Displays ground items"},
    {"Target",       FALSE,0xC00000,   TRUE,MAPFILTER_All,FALSE,   "Displays your target"},
    {"TargetLine",   FALSE,0x808080,   TRUE,MAPFILTER_Target,FALSE,  "Displays a line to your target"},
    {"TargetRadius", FALSE,0x808080,   FALSE,MAPFILTER_Target,FALSE,  "Sets radius of a circle around your target to # (omit or set to 0 to disable)"},
	{"TargetMelee",  FALSE,0xFF8080,   FALSE,MAPFILTER_Target,FALSE,  "Draws a melee-range circle around your target"},
    {"Vector",       FALSE,-1,         TRUE,MAPFILTER_All,TRUE,   "Displays heading vectors"},
    {"Custom",       FALSE,-1,         FALSE,MAPFILTER_All,TRUE,  "Sets custom filter (omit to disable)"},
    {"CastRadius",   FALSE,0x808080,   FALSE,MAPFILTER_All,FALSE,  "Sets radius of casting circle to # (omit or set to 0 to disable)"},
    {"NormalLabels", 0,-1,         TRUE,MAPFILTER_Invalid,FALSE,   "Toggles non-MQ2 label display"},
    {"Menu",         FALSE,-1,         TRUE,MAPFILTER_Invalid,FALSE,   "Allows display of right-click context menu"},
    {NULL,           FALSE,-1,         FALSE,MAPFILTER_Invalid,FALSE,  NULL}
};





PCSIDLWNDVFTABLE CMyMapViewWnd__OldvfTable=0;
DWORD CMyMapViewWnd__OldDestructor=0;
DWORD CMyMapViewWnd__OldHandleRButtonDown=0;
DWORD CMyMapViewWnd__OldPostDraw=0;

DWORD __declspec(naked) CMyMapViewWnd__Destructor(bool Deallocate)
{
   __asm {   
   push ecx;
   push eax;
   push edx;
   }
	if (CMyMapViewWnd__OldvfTable) { 
	   delete (*ppMapViewWnd)->pvfTable;
		(*ppMapViewWnd)->pvfTable=CMyMapViewWnd__OldvfTable;
		CMyMapViewWnd__OldvfTable=0;
		DebugSpewAlways("MQ2Map::CMyMapViewWnd__Destructor %x",pMapViewWnd);
	}
   __asm
   {
   pop edx;
   pop eax;
   pop ecx;
      jmp [CMyMapViewWnd__OldDestructor];
   }
}

bool RButtonDown()
{
	CHAR szOut[MAX_STRING]={0};
	if (pCurrentMapLabel)
	{
		MapSelectTarget();
		return false;
	}
	if (!IsOptionEnabled(MAPFILTER_ContextMenu))
		return false;
	return true;
}
//public: virtual int __thiscall CSidlScreenWnd::HandleRButtonDown(class CXPoint,unsigned __int32)
int __declspec(naked) CMyMapViewWnd__HandleRButtonDown(class CXPoint point, unsigned __int32 pData)
{
   __asm {   
   push ecx;
   push eax;
  }
	if (RButtonDown())
	{
	   __asm {
	   pop eax;
	   pop ecx;
	   jmp [CMyMapViewWnd__OldHandleRButtonDown];
	   };
	}
	else
	{
		__asm {
			pop eax;
			pop ecx;
			xor eax, eax;
			retn 0Ch;
		}
	}
} 


VOID __declspec(naked) CMyMapViewWnd__PostDraw()
{
	__asm {
	
	push esi;
	mov esi, ecx;

	call [MapUpdate];
	call [MapAttach];

	mov ecx, esi;
	call [CMyMapViewWnd__OldPostDraw];
	push eax;

	call [MapDetach];
	pop eax;
	mov ecx, esi;
	pop esi;
	ret;
	};
}

class CMyMapViewWnd
{
public:
	DWORD Constructor_Trampoline(class CXWnd *);
	DWORD Constructor_Detour(class CXWnd *wnd)
	{
		CMapViewWnd *pWnd=(CMapViewWnd*)this;
		DWORD Ret=Constructor_Trampoline(wnd);
		PCSIDLWNDVFTABLE pvfTable = new CSIDLWNDVFTABLE; 
		*pvfTable=*pWnd->pvfTable;

		CMyMapViewWnd__OldvfTable=pWnd->pvfTable;
		pWnd->pvfTable=pvfTable;
		CMyMapViewWnd__OldPostDraw=(DWORD)pWnd->pvfTable->PostDraw2;
		CMyMapViewWnd__OldHandleRButtonDown=(DWORD)pWnd->pvfTable->HandleRButtonDown;
		CMyMapViewWnd__OldDestructor=(DWORD)pWnd->pvfTable->vector_deleting_destructor;
		pWnd->pvfTable->vector_deleting_destructor=CMyMapViewWnd__Destructor;
		pWnd->pvfTable->HandleRButtonDown=CMyMapViewWnd__HandleRButtonDown; 
		pWnd->pvfTable->PostDraw2=CMyMapViewWnd__PostDraw; 
		return Ret;
	}

	static void StealVFTable()
	{
		if (CMapViewWnd *pWnd=(CMapViewWnd*)pMapViewWnd)
		{
			PCSIDLWNDVFTABLE pvfTable = new CSIDLWNDVFTABLE; 
			*pvfTable=*pWnd->pvfTable;

			CMyMapViewWnd__OldvfTable=pWnd->pvfTable;
			pWnd->pvfTable=pvfTable;
			CMyMapViewWnd__OldPostDraw=(DWORD)pWnd->pvfTable->PostDraw2;
			CMyMapViewWnd__OldHandleRButtonDown=(DWORD)pWnd->pvfTable->HandleRButtonDown;
			CMyMapViewWnd__OldDestructor=(DWORD)pWnd->pvfTable->vector_deleting_destructor;
			pWnd->pvfTable->vector_deleting_destructor=CMyMapViewWnd__Destructor;
			pWnd->pvfTable->HandleRButtonDown=CMyMapViewWnd__HandleRButtonDown; 
			pWnd->pvfTable->PostDraw2=CMyMapViewWnd__PostDraw; 
		}
	}

	static void RestoreVFTable()
	{
		if(CMyMapViewWnd__OldvfTable && ppMapViewWnd && *ppMapViewWnd) {
			if (CMapViewWnd *pWnd=(CMapViewWnd*)pMapViewWnd)
			{
				if (CMyMapViewWnd__OldvfTable) { 
					delete pWnd->pvfTable;
					pWnd->pvfTable=CMyMapViewWnd__OldvfTable;
				}
			}
		}
	}
};

DETOUR_TRAMPOLINE_EMPTY(DWORD CMyMapViewWnd::Constructor_Trampoline(class CXWnd *)); 

bool Update=true;
PLUGIN_API VOID OnPulse(VOID)
{
	if (gGameState==GAMESTATE_INGAME && ppMapViewWnd && *ppMapViewWnd && !CMyMapViewWnd__OldvfTable)
	{
		DebugSpewAlways("MQ2Map::OnPulse Doing Init %x",pMapViewWnd);
		//if(pMapViewWnd->pvfTable!=
		if (CMapViewWnd *pWnd=(CMapViewWnd*)pMapViewWnd)
		{
			PCSIDLWNDVFTABLE pvfTable = new CSIDLWNDVFTABLE; 
			*pvfTable=*pWnd->pvfTable;

			CMyMapViewWnd__OldvfTable=pWnd->pvfTable;
			pWnd->pvfTable=pvfTable;
			CMyMapViewWnd__OldPostDraw=(DWORD)pWnd->pvfTable->PostDraw2;
			CMyMapViewWnd__OldHandleRButtonDown=(DWORD)pWnd->pvfTable->HandleRButtonDown;
			CMyMapViewWnd__OldDestructor=(DWORD)pWnd->pvfTable->vector_deleting_destructor;
			pWnd->pvfTable->vector_deleting_destructor=CMyMapViewWnd__Destructor;
			pWnd->pvfTable->HandleRButtonDown=CMyMapViewWnd__HandleRButtonDown; 
			pWnd->pvfTable->PostDraw2=CMyMapViewWnd__PostDraw; 
		}
	}
	/*if (gGameState==GAMESTATE_CHARSELECT && !g_pMapToolbarWnd)
	{
		CreateMapToolbarWindow();
	}
	if (gGameState==GAMESTATE_CHARSELECT && !g_pMapViewWnd)
	{
		CreateMapWindow();
	}*/
}

// Called once, when the plugin is to initialize
PLUGIN_API VOID InitializePlugin(VOID)
{
	DebugSpewAlways("Initializing MQ2Map");

	bmMapRefresh=AddMQ2Benchmark("Map Refresh");
	unsigned long i;
	CHAR szBuffer[MAX_STRING]={0};
    for (i=0;MapFilterOptions[i].szName;i++) {
        sprintf(szBuffer,"%s-Color",MapFilterOptions[i].szName);
        MapFilterOptions[i].Enabled = GetPrivateProfileInt("Map Filters",MapFilterOptions[i].szName,MapFilterOptions[i].Default,INIFileName);
       MapFilterOptions[i].Color = GetPrivateProfileInt("Map Filters",szBuffer,MapFilterOptions[i].DefaultColor,INIFileName) | 0xFF000000;
    }
	MapInit();
	GetPrivateProfileString("Naming Schemes","Normal","%N",MapNameString,MAX_STRING,INIFileName);
	GetPrivateProfileString("Naming Schemes","Target","%N",MapTargetNameString,MAX_STRING,INIFileName);

	for (i=1;i<16;i++)
	{
		sprintf(szBuffer,"KeyCombo%d",i);
		GetPrivateProfileString("Right Click",szBuffer,MapSpecialClickString[i],MapSpecialClickString[i],MAX_STRING,INIFileName);
	}

	// Do not use Custom, since the string isn't stored
    MapFilterOptions[MAPFILTER_Custom].Enabled = 0;


	AddCommand("/mapfilter",MapFilters,0,1,1);
	AddCommand("/maphide",MapHideCmd,0,1,1);
	AddCommand("/mapshow",MapShowCmd,0,1,1);
	AddCommand("/highlight",MapHighlightCmd,0,1,1);
	AddCommand("/mapnames",MapNames,0,1,1);
	AddCommand("/mapclick",MapClickCommand,0,1,0);

//	EasyClassDetour(CMapViewWnd__CMapViewWnd,CMyMapViewWnd,Constructor_Detour,DWORD,(CXWnd*),Constructor_Trampoline);
	//EzDetour(CMapViewWnd__CMapViewWnd,&CMyMapViewWnd::Constructor_Detour,&CMyMapViewWnd::Constructor_Trampoline);
	//CMyMapViewWnd::StealVFTable();

	AddMQ2Data("MapSpawn",dataMapSpawn);
}

// Called once, when the plugin is to shutdown
PLUGIN_API VOID ShutdownPlugin(VOID)
{
	DebugSpewAlways("Shutting down MQ2Map");
	Update=false;
	RemoveMQ2Data("MapSpawn");

//	RemoveDetour(CMapViewWnd__CMapViewWnd);

	MapClear();
	CMyMapViewWnd::RestoreVFTable();
	
	RemoveMQ2Benchmark(bmMapRefresh);
	RemoveCommand("/maphide");
	RemoveCommand("/mapshow");
	RemoveCommand("/mapfilter");
	RemoveCommand("/highlight");
	RemoveCommand("/mapnames");
	RemoveCommand("/mapclick");
	CMyMapViewWnd__OldvfTable=0;
}

// This is called each time a spawn is added to a zone (inserted into EQ's list of spawns),
// or for each existing spawn when a plugin first initializes
// NOTE: When you zone, these will come BEFORE OnZoned
PLUGIN_API VOID OnAddSpawn(PSPAWNINFO pNewSpawn)
{
	//DebugSpewAlways("MQ2Map::OnAddSpawn(%s)",pNewSpawn->Name);
	if (Update)
		AddSpawn(pNewSpawn);
}

// This is called each time a spawn is removed from a zone (removed from EQ's list of spawns).
// It is NOT called for each existing spawn when a plugin shuts down.
PLUGIN_API VOID OnRemoveSpawn(PSPAWNINFO pSpawn)
{
	//DebugSpewAlways("MQ2Map::OnRemoveSpawn(%s)",pSpawn->Name);
	if (Update)
		RemoveSpawn(pSpawn);
}

PLUGIN_API VOID SetGameState(DWORD GameState)
{
	if (GameState==3)
	{
		MapClear();
	}
}

// This is called each time a ground item is added to a zone
// or for each existing ground item when a plugin first initializes
// NOTE: When you zone, these will come BEFORE OnZoned
PLUGIN_API VOID OnAddGroundItem(PGROUNDITEM pNewGroundItem)
{
	//DebugSpewAlways("MQ2Map::OnAddGroundItem(%d)",pNewGroundItem->DropID);
	if (Update)
		AddGroundItem(pNewGroundItem);
}

// This is called each time a ground item is removed from a zone
// It is NOT called for each existing ground item when a plugin shuts down.
PLUGIN_API VOID OnRemoveGroundItem(PGROUNDITEM pGroundItem)
{
	//DebugSpewAlways("MQ2Map::OnRemoveGroundItem(%d)",pGroundItem->DropID);
	if (Update)
		RemoveGroundItem(pGroundItem);
}

