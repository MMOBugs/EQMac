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
#if !defined(CINTERFACE)
#error /DCINTERFACE
#endif

#define DBG_SPEW

//#define DEBUG_TRY 1
#include "MQ2Main.h"



PMQGROUNDPENDING pPendingGrounds=0;
CRITICAL_SECTION csPendingGrounds;
BOOL ProcessPending=false;

void AddGroundItem()
{
	PGROUNDITEM pGroundItem=(PGROUNDITEM)pItemList;
	EnterCriticalSection(&csPendingGrounds);
	PMQGROUNDPENDING pPending=new MQGROUNDPENDING;
	pPending->pGroundItem=pGroundItem;
	pPending->pNext=pPendingGrounds;
	pPending->pLast=0;
	if (pPendingGrounds)
		pPendingGrounds->pLast=pPending;
	pPendingGrounds=pPending;
	LeaveCriticalSection(&csPendingGrounds);
}

void RemoveGroundItem(PGROUNDITEM pGroundItem)
{
	if (pPendingGrounds)
	{
		EnterCriticalSection(&csPendingGrounds);
		PMQGROUNDPENDING pPending=pPendingGrounds;
		while(pPending)
		{
			if (pGroundItem==pPending->pGroundItem)
			{
				if (pPending->pNext)
					pPending->pNext->pLast=pPending->pLast;
				if (pPending->pLast)
					pPending->pLast->pNext=pPending->pNext;
				else
					pPendingGrounds=pPending->pNext;
				delete pPending;
				break;
			}
			pPending=pPending->pNext;
		}
		LeaveCriticalSection(&csPendingGrounds);
	}
	PluginsRemoveGroundItem((PGROUNDITEM)pGroundItem);
}

class EQItemListHook
{
public:
	VOID EQItemList_Trampoline();
	VOID EQItemList_Detour()
	{
		VOID (EQItemListHook::*tmp)(void) = &EQItemListHook::EQItemList_Trampoline; 
		__asm {
			call [tmp];
			push eax;
			push ebx;
			push ecx;
			push edx;
			push esi;
			push edi;
			call AddGroundItem;
			pop edi;
			pop esi;
			pop edx;
			pop ecx;
			pop ebx;
			pop eax;
		};
	}

	void dEQItemList_Trampoline();
	void dEQItemList_Detour()
	{
		void (EQItemListHook::*tmp)(void) = &EQItemListHook::dEQItemList_Trampoline;
		__asm {
			push ecx;
			push ecx;
			call RemoveGroundItem;
			pop ecx;
			pop ecx;
			call [tmp];
		};
	}
};

DETOUR_TRAMPOLINE_EMPTY(VOID EQItemListHook::EQItemList_Trampoline(VOID)); 
DETOUR_TRAMPOLINE_EMPTY(VOID EQItemListHook::dEQItemList_Trampoline(VOID)); 

VOID SetNameSpriteTint(PSPAWNINFO pSpawn);



class EQPlayerHook
{
public:

	
	void EQPlayer_ExtraDetour(PSPAWNINFO pSpawn)
	{// note: we need to keep the original registers.
		__asm {push eax};
		__asm {push ebx};
		__asm {push ecx};
		__asm {push edx};
		__asm {push esi};
		__asm {push edi};
		PluginsAddSpawn(pSpawn);
		__asm {pop edi};
		__asm {pop esi};
		__asm {pop edx};
		__asm {pop ecx};
		__asm {pop ebx};
		__asm {pop eax};
	}
	/**/

	void EQPlayer_Trampoline(class EQPlayer *,unsigned char,unsigned int,unsigned char,char *);
	void EQPlayer_Detour(class EQPlayer *a,unsigned char b,unsigned int c,unsigned char d,char *e)
	{
		PSPAWNINFO pSpawn = 0;
		__asm {mov [pSpawn], ecx};
		EQPlayer_Trampoline(a,b,c,d,e);
		//doing some code fu here so
		//we dont mess with the stack
		__asm {
			cmp byte ptr [eax],0x3;
			jne dontcallifnull;
			push		edx;
			push		ecx;
			mov         edx,dword ptr [pSpawn];
			push        edx;
			mov         ecx,dword ptr [this];
			call        EQPlayerHook::EQPlayer_ExtraDetour;
			pop			edx;
			pop			ecx;
			pop			edx;
			dontcallifnull:
		};
		//EQPlayer_ExtraDetour(pSpawn);
//returnifnull:;
		//Sleep(0);
		//returnifnull:
		/**/
	}

	VOID dEQPlayer_Trampoline();
	VOID dEQPlayer_Detour()
	{
		VOID (EQPlayerHook::*tmp)(void) = &EQPlayerHook::dEQPlayer_Trampoline; 
		__asm {
			push ecx;
			push ecx;
			call PluginsRemoveSpawn;
			pop ecx;
			pop ecx;
			call [tmp];
		};
	}

	int SetNameSpriteState_Trampoline(PSPAWNINFO pSpawn,bool Show);
	int SetNameSpriteState_Detour(PSPAWNINFO pSpawn,bool Show)
	{
		if (gGameState!=GAMESTATE_INGAME || !Show)
			return SetNameSpriteState_Trampoline(pSpawn,Show);
		return 1;
	}
	//ecx should be pinstCDisplay
	bool SetNameSpriteTint_Trampoline(PSPAWNINFO pSpawn);
	bool SetNameSpriteTint_Detour(PSPAWNINFO pSpawn)
	{
		if (gGameState!=GAMESTATE_INGAME)
			return SetNameSpriteTint_Trampoline(pSpawn);
		return 1;
	}
	int ChangeBoneStringSprite_Trampoline(struct T3D_DAG *A,struct T3D_DAG *B,char *C);
	int ChangeBoneStringSprite_Detour(struct T3D_DAG *A,struct T3D_DAG *B,char *C)
	{
		//DWORD myoffset = 0;
		//__asm{mov myoffset, ecx};
		//DebugSpew(" ECX = %x A=%x B=%x C=%s",myoffset,A,B,C);
		if (gGameState!=GAMESTATE_INGAME) {
			return ChangeBoneStringSprite_Trampoline(A,B,C);
		}
		return 1;
	}
};

class CActorEx
{
public:
	bool CanSetName(DWORD);
	int SetNameColor(DWORD *sprite,DWORD *Color);
	//struct S3D_STRINGSPRITE * EQPlayer::ChangeBoneStringSprite(struct T3D_DAG *,char *);
};

FUNCTION_AT_VIRTUAL_ADDRESS(bool CActorEx::CanSetName(DWORD),0x140);
FUNCTION_AT_VARIABLE_ADDRESS(int CActorEx::SetNameColor(DWORD *sprite,DWORD *Color),0x7F9880);

typedef struct _CAPTIONCOLOR {
	PCHAR szName;
	PCHAR szDescription;
	BOOL Enabled;
	BOOL ToggleOnly;
	DWORD Color;
} CAPTIONCOLOR, PCAPTIONCOLOR;

#define CC_PC			    0
#define CC_PCConColor	    1
#define CC_PCPVPTeamColor   2
#define CC_PCRaidColor      3
#define CC_PCClassColor     4
#define CC_PCGroupColor     5
#define CC_PCTrader		    6
#define CC_NPC			    7
#define CC_NPCConColor      8
#define CC_NPCClassColor    9
#define CC_NPCMerchant      10
#define CC_NPCBanker        11
#define CC_NPCAssist        12 
#define CC_PetNPC		    14
#define CC_PetPC		    15
#define CC_PetConColor		16
#define CC_PetClassColor    17
#define CC_Corpse		    18
#define CC_CorpseClassColor 19


CAPTIONCOLOR CaptionColors[]=
{
	{
/*name*/"PC",
/*desc*/"Default color for PCs",
/* on */0,
/*togl*/0,
/*clr */0x00FF00FF,
	},
	{
/*name*/"PCCon",
/*desc*/"PCs by con color",
/* on */0,
/*togl*/1,
/*clr */0,
	},
	{
/*name*/"PCPVPTeam",
/*desc*/"PCs by PVP team color",
/* on */0,
/*togl*/1,
/*clr */0,
	},
	{
/*name*/"PCRaid",
/*desc*/"Raid members",
/* on */0,
/*togl*/0,
/*clr */0x0000FF7F,
	},
	{
/*name*/"PCClass",
/*desc*/"PCs by class color(raid settings)",
/* on */0,
/*togl*/1,
/*clr */0,
	},
	{
/*name*/"PCGroup",
/*desc*/"Group members",
/* on */0,
/*togl*/0,
/*clr */0x00FFFF00,
	},
	{
/*name*/"PCTrader",
/*desc*/"Traders",
/* on */1,
/*togl*/0,
/*clr */0x00FF7F00,
	},
	{
/*name*/"NPC",
/*desc*/"NPC default color",
/* on */0,
/*togl*/0,
/*clr */0x00FF0000,
	},
	{
/*name*/"NPCCon",
/*desc*/"NPCs by con color",
/* on */1,
/*togl*/1,
/*clr */0,
	},
	{
/*name*/"NPCClass",
/*desc*/"NPCs by class color (raid settings)",
/* on */0,
/*togl*/1,
/*clr */0,
	},
	{
/*name*/"NPCMerchant",
/*desc*/"NPC Merchants",
/* on */1,
/*togl*/0,
/*clr */0x00FF7F00,
	},
	{
/*name*/"NPCBanker",
/*desc*/"NPC Bankers",
/* on */1,
/*togl*/0,
/*clr */0x00C800FF,
	},
	{
/*name*/"NPCAssist",
/*desc*/"NPCs from main assist",
/* on */1,
/*togl*/0,
/*clr */0x00FFFF00,
	},
	{
/*name*/"PetNPC",
/*desc*/"Pet with NPC owner",
/* on */0,
/*togl*/0,
/*clr */0x00FF0000,
	},
	{
/*name*/"PetPC",
/*desc*/"Pet with PC owner",
/* on */0,
/*togl*/0,
/*clr */0x00FFFF00,
	},
	{
/*name*/"PetClass",
/*desc*/"Pet by class color (raid settings)",
/* on */0,
/*togl*/0,
/*clr */0x00FF0000,
	},
	{
/*name*/"Corpse",
/*desc*/"Corpses",
/* on */0,
/*togl*/0,
/*clr */0x00FF0000,
	},
	{
/*name*/"CorpseClass",
/*desc*/"Corpse by class color (raid settings)",
/* on */0,
/*togl*/0,
/*clr */0x00FF0000,
	},

	{
/*name*/"",
/*desc*/"",
/* on */0,
/*togl*/0,
/*clr */0,
	},
};

VOID SetNameSpriteTint(PSPAWNINFO pSpawn)
{
	int GameState = -1;
	GameState = GetGameState();
	if (GameState!=GAMESTATE_INGAME)
		return;
	if (!pSpawn->pActorInfo || !pSpawn->pActorInfo->pActorEx)
		return;
	DWORD spawntype = GetSpawnType(pSpawn);
	//DebugSpew("SetNameSpriteTint(%s) spawntype = %d",pSpawn->Name,spawntype);
	//CActorEx *pActorEx=(CActorEx *)pSpawn->pActorInfo->pActorEx;
	DWORD NewColor = 0;
	switch(spawntype)
	{
		case PC:
		{	/*
			#define CC_PC			    0
			#define CC_PCConColor	    1
			#define CC_PCPVPTeamColor   2
			#define CC_PCRaidColor      3
			#define CC_PCClassColor     4
			#define CC_PCGroupColor     5
			#define CC_PCTrader		    6
			/**/
			if (pSpawn->pActorInfo->Trader && CaptionColors[CC_PCTrader].Enabled)
				NewColor=CaptionColors[CC_PCTrader].Color;
			else if (CaptionColors[CC_PCGroupColor].Enabled && IsGroupMember(pSpawn))
				NewColor=CaptionColors[CC_PCGroupColor].Color;
			else if (CaptionColors[CC_PCClassColor].Enabled)
				NewColor=((PEQRAIDWINDOW)pRaidWnd)->ClassColors[ClassInfo[pSpawn->Class].RaidColorOrder];
			else if (CaptionColors[CC_PCRaidColor].Enabled && IsRaidMember(pSpawn))
				NewColor=CaptionColors[CC_PCRaidColor].Color;
			else if (CaptionColors[CC_PCPVPTeamColor].Enabled)
			{
				// TODO
			}
			else if (CaptionColors[CC_PCConColor].Enabled)
				NewColor=ConColorToARGB(ConColor(pSpawn));
			else if (CaptionColors[CC_PC].Enabled)
				NewColor=CaptionColors[CC_PC].Color;
			else
			{
				((EQPlayerHook*)pDisplay)->SetNameSpriteTint_Trampoline(pSpawn);
				return;
			}
			break;
		}
		case NPC:
		{
			/*
			#define CC_NPC			    7
			#define CC_NPCConColor      8
			#define CC_NPCClassColor    9
			#define CC_NPCMerchant      10
			#define CC_NPCBanker        11
			#define CC_NPCAssist        12 
			/**/
			if (CaptionColors[CC_NPCBanker].Enabled && pSpawn->Class==40)
				NewColor=CaptionColors[CC_NPCBanker].Color;
			else if (CaptionColors[CC_NPCMerchant].Enabled && (pSpawn->Class==41 || pSpawn->Class==61))
				NewColor=CaptionColors[CC_NPCMerchant].Color;
			else if (CaptionColors[CC_NPCClassColor].Enabled && pSpawn->Class<0x10)
				NewColor=((PEQRAIDWINDOW)pRaidWnd)->ClassColors[ClassInfo[pSpawn->Class].RaidColorOrder];
			else if (CaptionColors[CC_NPCConColor].Enabled)
				NewColor=ConColorToARGB(ConColor(pSpawn));
			else if (CaptionColors[CC_NPC].Enabled)
				NewColor=CaptionColors[CC_NPC].Color;
			else
			{
				((EQPlayerHook*)pDisplay)->SetNameSpriteTint_Trampoline(pSpawn);
				return;
			}
			break;
		}
		case CORPSE:
		{
			if (CaptionColors[CC_CorpseClassColor].Enabled)
				NewColor=((PEQRAIDWINDOW)pRaidWnd)->ClassColors[ClassInfo[pSpawn->Class].RaidColorOrder];
			else if (CaptionColors[CC_Corpse].Enabled)
				NewColor=CaptionColors[CC_Corpse].Color;
			else
			{
				((EQPlayerHook*)pDisplay)->SetNameSpriteTint_Trampoline(pSpawn);
				return;
			}
			break;
		}
		case PET:
		{
			if (CaptionColors[CC_PetClassColor].Enabled)
				NewColor=((PEQRAIDWINDOW)pRaidWnd)->ClassColors[ClassInfo[pSpawn->Class].RaidColorOrder];
			else if (CaptionColors[CC_PetConColor].Enabled)
				NewColor=ConColorToARGB(ConColor(pSpawn));
			else if (CaptionColors[CC_PetNPC].Enabled && ((PSPAWNINFO)GetSpawnByID(pSpawn->MasterID))->Type==SPAWN_NPC)
				NewColor=CaptionColors[CC_PetNPC].Color;
			else if (CaptionColors[CC_PetPC].Enabled && ((PSPAWNINFO)GetSpawnByID(pSpawn->MasterID))->Type==SPAWN_PLAYER)
				NewColor=CaptionColors[CC_PetPC].Color;
			else
			{
				((EQPlayerHook*)pDisplay)->SetNameSpriteTint_Trampoline(pSpawn);
				return;
			}
			break;
		}
	}
	//7F9880
	//first call t3dGetDagSprite
	// then use that pointer as a param to SetNameColor
	//like this:
	 //.text:004B115E                 mov     eax, [edi+84h] ; /*0x084*/   struct  _ACTORINFO   *pActorInfo;
	/*.text:004B1164                 test    eax, eax
	.text:004B1166                 jz      loc_4B1434
	.text:004B116C                 mov     eax, [eax+288h]
	.text:004B1172                 test    eax, eax
	.text:004B1174                 jz      loc_4B1434
	.text:004B117A                 push    eax
	.text:004B117B                 call    __imp__t3dGetDagSprite
	*/
	DWORD dag = (DWORD)pSpawn->pActorInfo->pActorTint;//mov     eax, [eax+288h]
	DWORD sprite = *(DWORD*)(dag+0x8);
	//DebugSpew("%s pre oldcolor = %x newColor = %x",pSpawn->Name,*(DWORD*)(sprite+0x48),NewColor);
	*(DWORD*)(sprite+0x48) = NewColor;
	//if we call this we mess up ebx... so instead we do what the asm does, see below (taken from EQGfx_Dx8.dll (2012-02-18 obviously hacked, i dont know original version...)
	//pActorEx->SetNameColor((DWORD *)sprite,(DWORD *)&NewColor);
	//DebugSpew("%s post oldcolor = %x newColor = %x",pSpawn->Name,*(DWORD*)(sprite+0x48),NewColor);
	/*s3dSetStringSpriteTint proc near
.text:10021700
.text:10021700 arg_0           = dword ptr  4
.text:10021700 arg_4           = dword ptr  8
.text:10021700
.text:10021700                 mov     eax, [esp+arg_4]
.text:10021704                 mov     edx, [esp+arg_0]
.text:10021708                 mov     ecx, [eax]
.text:1002170A                 xor     eax, eax
.text:1002170C                 mov     [edx+48h], ecx
.text:1002170F                 retn
.text:1002170F s3dSetStringSpriteTint endp

*/
}
//first arg for ChangeBoneStringSprite is edi+288 which is same as : pSpawn->pActorInfo->pActorTint
//second is [pinstCDisplay+2E08h]
//third arg is the string for sure!
int SetCaption(PSPAWNINFO pSpawn,char *CaptionString)
{
	if (CaptionString[0])
	{
		CHAR NewCaption[MAX_STRING]={0};
		strcpy(NewCaption,CaptionString);
		pNamingSpawn=pSpawn;
		ParseMacroParameter(GetCharInfo()->pSpawn,NewCaption);
		pNamingSpawn=0;
		DWORD dag = *(DWORD *)(pDisplay+0x2e08);
		if(pSpawn->pActorInfo->pActorTint!=0) {
			//DebugSpew("pSpawn->pActorInfo->pActorTint = %x dag=%x I want to call ChangeBoneStringSprite(%s) ",pSpawn->pActorInfo->pActorTint,dag,NewCaption);

			//((EQPlayer*)pSpawn)->ChangeBoneStringSprite(pSpawn->pActorInfo->pActorTint,(T3D_DAG *)dag,NewCaption);
			((EQPlayerHook*)pDisplay)->ChangeBoneStringSprite_Trampoline(pSpawn->pActorInfo->pActorTint,(T3D_DAG *)dag,NewCaption);
			//pDisplay->ChangeBoneStringSprite(pSpawn->pActorInfo->pActorTint,(T3D_DAG *)dag,"hello there");
			//return 1;
		}
	}
	return 0;
}
BOOL SetNameSpriteState(PSPAWNINFO pSpawn, bool Show)
{
	//DebugSpew("SetNameSpriteState(%s) --race %d body %d)",pSpawn->Name,pSpawn->Race,pSpawn->BodyType);
	if (!Show)
	{
		//ecx should be pinstCDisplay
		((EQPlayerHook*)pDisplay)->SetNameSpriteState_Trampoline(pSpawn,Show);
	}
//first arg for ChangeBoneStringSprite is edi+288 which is same as : pSpawn->pActorInfo->pActorTint
//second is [pinstCDisplay+2E08h]
//third arg is the string for sure!
/*#define SetCaption(CaptionString) \
		{\
			if (CaptionString[0])\
			{\
				strcpy(NewCaption,CaptionString);\
				pNamingSpawn=pSpawn;\
				ParseMacroParameter(GetCharInfo()->pSpawn,NewCaption);\
				pNamingSpawn=0;\
				((EQPlayer*)pSpawn)->ChangeBoneStringSprite(pSpawn->pActorInfo->pActorTint,(T3D_DAG *)(*(DWORD *)(pDisplay+0x2e08)),NewCaption);\
				return 1;\
			}\
		}*/
		//CHAR NewCaption[MAX_STRING]={0};

		/*if (pSpawn->pActorInfo->pActorEx && !((CActorEx*)pSpawn->pActorInfo->pActorEx)->CanSetName(0))
		{
//			DebugSpew("CanSetName==0 - %s .. race %d body %d",pSpawn->Name,pSpawn->Race,pSpawn->BodyType);
			return 1;
		};*/
		
		switch(GetSpawnType(pSpawn))
		{
		case NPC:
			SetCaption(pSpawn,gszSpawnNPCName);
			break;
		case PC:
			if (!gPCNames && pSpawn!=(PSPAWNINFO)pTarget) 
				return 0;
			SetCaption(pSpawn,gszSpawnPlayerName[gShowNames]);
			break;
		case CORPSE:
			SetCaption(pSpawn,gszSpawnCorpseName);
			break;
		case CHEST:
		case UNTARGETABLE:
		case TRAP:
		case TIMER:
		case TRIGGER:// trigger names make it crash!
			return 0;
		case MOUNT://mount names make it crash!
			return 0;
		case PET:
			SetCaption(pSpawn,gszSpawnPetName);
			break;
		}
//		DebugSpew("Returning default from SetNameSpriteState");
		//ecx should be pinstCDisplay
		return ((EQPlayerHook*)pDisplay)->SetNameSpriteState_Trampoline(pSpawn,Show);
//#undef SetCaption
}

VOID UpdateSpawnCaptions()
{
//	DebugSpew("UpdateSpawnCaptions()");
	int distN = 0;
	int capCount=0;
	for (; distN < 120 ; distN++)
	{
		if (PSPAWNINFO pSpawn=(PSPAWNINFO)EQP_DistArray[distN].VarPtr.Ptr) {
			if (pSpawn!=(PSPAWNINFO)pTarget) {
				if (EQP_DistArray[distN].Value.Float<=80.0f)
				{
					if (SetNameSpriteState(pSpawn,true))
					{
						SetNameSpriteTint(pSpawn);
						capCount++;
						if (capCount>=(int)gMaxSpawnCaptions)
						{
							return;
						}
					}
				} else {
					return;
				}
			}
		}
	}
}

DETOUR_TRAMPOLINE_EMPTY(int EQPlayerHook::ChangeBoneStringSprite_Trampoline(struct T3D_DAG *A,struct T3D_DAG *B,char *C));
DETOUR_TRAMPOLINE_EMPTY(bool EQPlayerHook::SetNameSpriteTint_Trampoline(PSPAWNINFO pSpawn));
DETOUR_TRAMPOLINE_EMPTY(int EQPlayerHook::SetNameSpriteState_Trampoline(PSPAWNINFO pSpawn,bool Show));
DETOUR_TRAMPOLINE_EMPTY(VOID EQPlayerHook::dEQPlayer_Trampoline(VOID)); 
DETOUR_TRAMPOLINE_EMPTY(VOID EQPlayerHook::EQPlayer_Trampoline(class EQPlayer *,unsigned char,unsigned int,unsigned char,char *)); 
//DETOUR_TRAMPOLINE_EMPTY(VOID EQSwitchHook::UseSwitch_Trampoline(unsigned int,int,int)); 

VOID InitializeMQ2Spawns()
{
	DebugSpew("Initializing Spawn-related Hooks");
	bmUpdateSpawnSort=AddMQ2Benchmark("UpdateSpawnSort");
	bmUpdateSpawnCaptions=AddMQ2Benchmark("UpdateSpawnCaptions");

	EzDetour(EQPlayer__EQPlayer,&EQPlayerHook::EQPlayer_Detour,&EQPlayerHook::EQPlayer_Trampoline);
	EzDetour(EQPlayer__dEQPlayer,&EQPlayerHook::dEQPlayer_Detour,&EQPlayerHook::dEQPlayer_Trampoline);
	EzDetour(EQPlayer__SetNameSpriteState,&EQPlayerHook::SetNameSpriteState_Detour,&EQPlayerHook::SetNameSpriteState_Trampoline);
	EzDetour(EQPlayer__SetNameSpriteTint,&EQPlayerHook::SetNameSpriteTint_Detour,&EQPlayerHook::SetNameSpriteTint_Trampoline);
	EzDetour(EQItemList__EQItemList,&EQItemListHook::EQItemList_Detour,&EQItemListHook::EQItemList_Trampoline);
	EzDetour(EQItemList__dEQItemList,&EQItemListHook::dEQItemList_Detour,&EQItemListHook::dEQItemList_Trampoline);
	EzDetour(EQPlayer__ChangeBoneStringSprite,&EQPlayerHook::ChangeBoneStringSprite_Detour,&EQPlayerHook::ChangeBoneStringSprite_Trampoline);
	//EzDetour(EQSwitch__UseSwitch,&EQSwitchHook::UseSwitch_detour,&EQSwitchHook::UseSwitch_Trampoline);
	InitializeCriticalSection(&csPendingGrounds);
	ProcessPending=true;
	ZeroMemory(&EQP_DistArray,sizeof(EQP_DistArray));
	gSpawnCount=0;

	CHAR Temp[MAX_STRING]={0};
	CHAR Name[MAX_STRING]={0};
	// load custom spawn caption colors
	DWORD N;
	for (N = 0 ; CaptionColors[N].szName[0] ; N++)
	{
		if (GetPrivateProfileString("Caption Colors",CaptionColors[N].szName,"",Temp,MAX_STRING,gszINIFilename))
		{
			if (!stricmp(Temp,"on") || !stricmp(Temp,"1"))
				CaptionColors[N].Enabled=1;
			else
				CaptionColors[N].Enabled=0;
		}
		sprintf(Name,"%s-Color",CaptionColors[N].szName);
		if (GetPrivateProfileString("Caption Colors",Name,"",Temp,MAX_STRING,gszINIFilename))
		{
			sscanf(Temp,"%x",&CaptionColors[N].Color);
		}
	}
	// write custom spawn caption colors
	for (N = 0 ; CaptionColors[N].szName[0] ; N++)
	{
		WritePrivateProfileString("Caption Colors",CaptionColors[N].szName,CaptionColors[N].Enabled?"ON":"OFF",gszINIFilename);
		if (!CaptionColors[N].ToggleOnly)
		{
			sprintf(Temp,"%x",CaptionColors[N].Color);
			sprintf(Name,"%s-Color",CaptionColors[N].szName);
			WritePrivateProfileString("Caption Colors",Name,Temp,gszINIFilename);
		}
	}
}

VOID ShutdownMQ2Spawns()
{
	DebugSpew("Shutting Down Spawn-related Hooks");
	RemoveDetour(EQPlayer__EQPlayer);
	RemoveDetour(EQPlayer__dEQPlayer);
	RemoveDetour(EQItemList__EQItemList);
	RemoveDetour(EQItemList__dEQItemList);
	RemoveDetour(EQPlayer__SetNameSpriteState);
	RemoveDetour(EQPlayer__SetNameSpriteTint);
	
	ProcessPending=false;
	EnterCriticalSection(&csPendingGrounds);
	DeleteCriticalSection(&csPendingGrounds);
	while(pPendingGrounds)
	{
		PMQGROUNDPENDING pNext=pPendingGrounds->pNext;
		delete pPendingGrounds;
		pPendingGrounds=pNext;
	}
	ZeroMemory(EQP_DistArray,sizeof(EQP_DistArray));
	gSpawnCount=0;
	RemoveMQ2Benchmark(bmUpdateSpawnSort);
	RemoveMQ2Benchmark(bmUpdateSpawnCaptions);
}

VOID ProcessPendingGroundItems()
{
	if (ProcessPending && pPendingGrounds)
	{
		EnterCriticalSection(&csPendingGrounds);
		while(pPendingGrounds)
		{
			PMQGROUNDPENDING pNext=pPendingGrounds->pNext;
			PluginsAddGroundItem(pPendingGrounds->pGroundItem);
			delete pPendingGrounds;
			pPendingGrounds=pNext;
		}
		LeaveCriticalSection(&csPendingGrounds);
	}
}

VOID UpdateMQ2SpawnSort()
{
	int GameState = -1;
	GameState = GetGameState();
	if(GameState!=GAMESTATE_INGAME)
		return;
	EnterMQ2Benchmark(bmUpdateSpawnSort);
	ZeroMemory(EQP_DistArray,sizeof(EQP_DistArray));
	gSpawnCount=0;
	PSPAWNINFO pSpawn=(PSPAWNINFO)pSpawnList;
	while(pSpawn)
	{
		EQP_DistArray[gSpawnCount].VarPtr.Ptr=pSpawn;
		EQP_DistArray[gSpawnCount].Value.Float=GetDistance(pSpawn->X,pSpawn->Y);
		gSpawnCount++;
		pSpawn=pSpawn->pPrev;
	}
	// quicksort!
	qsort(&EQP_DistArray[0],gSpawnCount,sizeof(MQRANK),MQRankFloatCompare);
	ExitMQ2Benchmark(bmUpdateSpawnSort);
	static unsigned long nCaptions=100;
	static unsigned long LastTarget=0;
	++nCaptions;
	if (LastTarget)
	{
		if (PSPAWNINFO pSpawn=(PSPAWNINFO)GetSpawnByID(LastTarget))
		{
			if (pSpawn!=(PSPAWNINFO)pTarget)
			{
				SetNameSpriteState(pSpawn,false);
			}
		}
		LastTarget=0;
	}
	if (GameState==GAMESTATE_INGAME && nCaptions>7)
	{
		nCaptions=0;
		Benchmark(bmUpdateSpawnCaptions,UpdateSpawnCaptions());
	}
	if (pTarget)
	{
		LastTarget=((PSPAWNINFO)pTarget)->SpawnID;
		((EQPlayerHook*)pDisplay)->SetNameSpriteTint_Trampoline((PSPAWNINFO)pTarget);
		SetNameSpriteState((PSPAWNINFO)pTarget,true);
	}
}

VOID CaptionColorCmd(PSPAWNINFO pChar, PCHAR szLine)
{
	if (!szLine[0])
	{
		SyntaxError("Usage: /captioncolor <list|<name off|on|#>>");
		return;
	}
	CHAR Arg1[MAX_STRING]={0};
	CHAR Arg2[MAX_STRING]={0};
	GetArg(Arg1,szLine,1);
	GetArg(Arg2,szLine,2);

	if (!stricmp(Arg1,"list"))
	{
		WriteChatColor("Caption Color Settings");
		WriteChatColor("----------------------");
		for (DWORD N = 0 ; CaptionColors[N].szName[0] ; N++)
		{
			if (!CaptionColors[N].Enabled || CaptionColors[N].ToggleOnly)
				WriteChatf("%s %s (%s)",CaptionColors[N].szName,CaptionColors[N].Enabled?"ON":"OFF",CaptionColors[N].szDescription);
			else
			{
				ARGBCOLOR Color;
				Color.ARGB=CaptionColors[N].Color;
				WriteChatf("%s ON Color: %d %d %d. (%s)",CaptionColors[N].szName,Color.R,Color.G,Color.B,CaptionColors[N].szDescription);
			}
		}
		return;
	}
	for (DWORD N = 0 ; CaptionColors[N].szName[0] ; N++)
	if (!stricmp(Arg1,CaptionColors[N].szName))
	{
		if (Arg2[0])
		{
			if (!stricmp(Arg2,"on"))
				CaptionColors[N].Enabled=1;
			else if (!stricmp(Arg2,"off"))
				CaptionColors[N].Enabled=0;
			else if (CaptionColors[N].Enabled && !CaptionColors[N].ToggleOnly)
			{
				ARGBCOLOR NewColor;
				NewColor.A=0;
				NewColor.R=atoi(Arg2);
				NewColor.G=atoi(GetArg(Arg2,szLine,3));
				NewColor.B=atoi(GetArg(Arg2,szLine,4));
				CaptionColors[N].Color=NewColor.ARGB;
			}
			else
			{
				MacroError("Invalid option '%s' while '%s' is off.",Arg2,Arg1);
				return;
			}
		}

		if (!CaptionColors[N].Enabled || CaptionColors[N].ToggleOnly)
			WriteChatf("%s %s (%s)",CaptionColors[N].szName,CaptionColors[N].Enabled?"ON":"OFF",CaptionColors[N].szDescription);
		else
		{
			ARGBCOLOR Color;
			Color.ARGB=CaptionColors[N].Color;
			WriteChatf("%s ON Color: %d %d %d. (%s)",CaptionColors[N].szName,Color.R,Color.G,Color.B,CaptionColors[N].szDescription);
		}
		WritePrivateProfileString("Caption Colors",CaptionColors[N].szName,CaptionColors[N].Enabled?"ON":"OFF",gszINIFilename);
		if (!CaptionColors[N].ToggleOnly)
		{
			sprintf(Arg2,"%x",CaptionColors[N].Color);
			sprintf(Arg1,"%s-Color",CaptionColors[N].szName);
			WritePrivateProfileString("Caption Colors",Arg1,Arg2,gszINIFilename);
		}
		return;
	}
}

