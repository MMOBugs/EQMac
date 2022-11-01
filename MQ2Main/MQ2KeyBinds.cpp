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
#include "MQ2Main.h"
#include <map>
#include <string>
#include <algorithm>
using namespace std;

void InjectMQ2Binds(COptionsWnd *pWnd);
void EjectMQ2Binds(COptionsWnd *pWnd);

struct MQ2KeyBind
{
	char Name[32];
	KeyCombo Normal;
	KeyCombo Alt;
	fMQExecuteCmd Function;
	BOOL State;
};

CIndex<MQ2KeyBind*> BindList(10);
map<string,unsigned long> BindNameMap;

inline MQ2KeyBind *KeyBindByName(char *Name)
{
	string Lwr=Name;
	MakeLower(Lwr);
	unsigned long N=BindNameMap[Lwr];
	if (!N)
		return 0;
	return BindList[--N];
}

inline void SetKeyBindNameMap(char *Name, unsigned long Number)
{
	string Lwr=Name;
	MakeLower(Lwr);
	BindNameMap[Lwr]=Number+1;
}

inline void RemoveKeyBindNameMap(char *Name)
{
	string Lwr=Name;
	MakeLower(Lwr);
	BindNameMap[Lwr]=0;
}

BOOL SetEQKeyBindByNumber(DWORD N, BOOL Alternate, KeyCombo &Combo)
{
	if (N<nEQMappableCommands)
	{
		if (Alternate)
			pKeypressHandler->AltKey[N] = Combo;
		else
			pKeypressHandler->NormalKey[N] = Combo;

		if(N < gnNormalEQMappableCommands)
			pKeypressHandler->SaveKeymapping( N, Combo, Alternate );
		return TRUE;
	}
	return FALSE;
}

inline BOOL SetEQKeyBind(PCHAR name, BOOL Alternate, KeyCombo &Combo )
{
   return SetEQKeyBindByNumber(FindMappableCommand(name),Alternate,Combo);
} 

BOOL MQ2HandleKeyDown(class KeyCombo const &Combo,bool mqcall)
{
	unsigned long N;
	bool Ret=false;
	DWORD thekey = Combo.GetKey();
	DWORD normalkey = 0;
	DWORD alternativekey = 0;
	//can call KeypressHandler__IsReservedKey if we like...
	if(mqcall) {//lets let eq take care of its own binds unless its us calling from mq we dont have to do it here...
		for ( N = 0 ; N < nEQMappableCommands ; N++)
		{
			normalkey = pKeypressHandler->NormalKey[N].GetKey();
			alternativekey = pKeypressHandler->AltKey[N].GetKey();
			if (normalkey==thekey || alternativekey==thekey)
			{
				//WriteChatf("EQ keycombo DOWN %x",thekey);
				BYTE oldchatmode = *(BYTE*)__InChatMode;//i know its stupid, it should be called __NotInChatMode
				*(BYTE*)__InChatMode = 1;
				ExecuteCmd(N,1,0);
				*(BYTE*)__InChatMode = oldchatmode;
				//pKeypressHandler->CommandState[N]=0;
				Ret=true;
			}
		}
	}

	for ( N = 0 ; N < BindList.Size ; N++)
    {
        if (MQ2KeyBind *pBind=BindList[N])
        {
			normalkey = pBind->Normal.GetKey();
			alternativekey = pBind->Alt.GetKey();
            if (pBind->State==0 && (normalkey==thekey || alternativekey==thekey))
            {
				//WriteChatf("MQ keycombo DOWN %x",thekey);
				BYTE oldchatmode = *(BYTE*)__InChatMode;//i know its stupid, it should be called __NotInChatMode
				*(BYTE*)__InChatMode = 1;
                pBind->Function(pBind->Name,true);
				*(BYTE*)__InChatMode = oldchatmode;
                pBind->State=1;
                Ret=true;
            }
        }
    }
	return Ret;
}

BOOL MQ2HandleKeyUp(class KeyCombo const &Combo,bool mqcall)
{
	unsigned long N;
	bool Ret=false;
	DWORD thekey = Combo.GetKey();
	DWORD normalkey = 0;
	DWORD alternativekey = 0;
	if(mqcall) { //lets let eq take care of its own binds we dont have to do it here...
		for ( N = 0 ; N < nEQMappableCommands ; N++)
		{
			normalkey = pKeypressHandler->NormalKey[N].GetKey();
			alternativekey = pKeypressHandler->AltKey[N].GetKey();
			if (normalkey==thekey || alternativekey==thekey)
			{
				//WriteChatf("EQ keycombo UP %x",thekey);
				BYTE oldchatmode = *(BYTE*)__InChatMode;//i know its stupid, it should be called __NotInChatMode
				*(BYTE*)__InChatMode = 1;
				ExecuteCmd(N,0,0);
				*(BYTE*)__InChatMode = oldchatmode;
				//pKeypressHandler->CommandState[N]=0;
				Ret=true;
			}
		}
	}
	for ( N = 0 ; N < BindList.Size ; N++)
    {
        if (MQ2KeyBind *pBind=BindList[N])
        {
			normalkey = pBind->Normal.GetKey();
			alternativekey = pBind->Alt.GetKey();
			if (pBind->State==1 && (normalkey==thekey || alternativekey==thekey))
            {
				//WriteChatf("MQ keycombo UP %x",thekey);
				BYTE oldchatmode = *(BYTE*)__InChatMode;//i know its stupid, it should be called __NotInChatMode
				*(BYTE*)__InChatMode = 1;
                pBind->Function(pBind->Name,false);
				*(BYTE*)__InChatMode = oldchatmode;
                pBind->State=0;
                Ret=true;
            }
        }
    }
	return Ret;
}
class KeypressHandlerHook
{
public:
	void ClearCommandStateArray_Trampoline(void);
	void ClearCommandStateArray_Hook(void)
	{
		unsigned long N;
		for (N = 0 ; N < BindList.Size ; N++)
		if (MQ2KeyBind *pBind=BindList[N])
		{
			pBind->State=false;
		}
//		ZeroMemory(&pKeypressHandler->CommandState[0],sizeof(pKeypressHandler->CommandState));
	}
	int  HandleKeyboardMsg_Trampoline(unsigned __int32,bool);
	int  HandleKeyboardMsg_Hook(unsigned __int32 Combo,bool flag)
	{
		int ret =  HandleKeyboardMsg_Trampoline(Combo,flag);
		//DebugSpew("HandleKeyboardMsg_Hook Combo = %x flag = %x ret = %x",Combo,flag,ret);
		return ret;
	}
};
int HandleKeyDown_Trampoline(unsigned __int32 Combo,unsigned char);
int HandleKeyUp_Trampoline(unsigned __int32 Combo);

DETOUR_TRAMPOLINE_EMPTY(int KeypressHandlerHook::HandleKeyboardMsg_Trampoline(unsigned __int32,bool));
//DETOUR_TRAMPOLINE_EMPTY(void KeypressHandlerHook::ClearCommandStateArray_Trampoline(void));
//DETOUR_TRAMPOLINE_EMPTY(BOOL KeypressHandlerHook::HandleKeyDown_Trampoline(unsigned __int32,unsigned __int32));
//DETOUR_TRAMPOLINE_EMPTY(BOOL KeypressHandlerHook::HandleKeyUp_Trampoline(unsigned __int32));
DETOUR_TRAMPOLINE_EMPTY(int HandleKeyDown_Trampoline(unsigned __int32,unsigned char));
DETOUR_TRAMPOLINE_EMPTY(int HandleKeyUp_Trampoline(unsigned __int32));

int HandleKeyDown_Hook(unsigned __int32 Combo,unsigned char asciikey)
{
	int ret = 0;
	//KeyCombo makecombo = Combo;
	//makecombo.Data[0] = asciikey;
	if(Combo==200||Combo==208) {//forward or backward
		PCHARINFO pChar = GetCharInfo();
		if(pChar) {
			if(pChar->standstate==STANDSTATE_SIT) {
				DoCommand(pChar->pSpawn,"/stand");
			}
		}
	}
	ret = HandleKeyDown_Trampoline(Combo,asciikey);
	//if(*(BYTE*)__InChatMode==1) {//we ARE NOT in chatmode when 1 (retarded)
	//and when thats the case, dont call this its just unesacary...
	//WriteChatf("HandleKeyDown_Hook key = %x flag = %x ret = %x",Combo,asciikey,ret);
	if(ret==asciikey) {//this means it was not handled if ret is 0xffffffff it was...
		ret = MQ2HandleKeyDown(Combo);
		//WriteChatf("MQ2HandleKeyDown called key = %x flag = %x ret = %x",Combo,asciikey,ret);
	}
	return ret;
}

int HandleKeyUp_Hook(unsigned __int32 Combo)
{
	int ret = HandleKeyUp_Trampoline(Combo);
	//if(*(BYTE*)__InChatMode==1) {//we ARE NOT in chatmode when 1 (retarded)
	//and when thats the case, dont call this its just unesacary...
	//WriteChatf("HandleKeyUp_Hook key = %x ret = %x",Combo,ret);

	if(!ret) {//if ret is 0 in this function it means it wasn't handled...
		ret = MQ2HandleKeyUp(Combo);
		//WriteChatf("MQ2HandleKeyUp key = %x ret = %x",Combo,ret);
	}
	return ret;
}

/*
class COptionsWndHook
{
public:
	void RefreshCurrentKeyboardAssignmentList_Trampoline();
	void RefreshCurrentKeyboardAssignmentList_Hook()
	{
		RefreshCurrentKeyboardAssignmentList_Trampoline();
	}

	void InitKeyboardAssignments_Trampoline();
	void InitKeyboardAssignments_Hook()
	{
		InitKeyboardAssignments_Trampoline();
		InjectMQ2Binds((COptionsWnd*)this);
	}
};
/**/
VOID DoRangedBind(PCHAR Name,BOOL Down);

void InitializeMQ2KeyBinds()
{
/*
	if (pOptionsWnd)
	{
		InjectMQ2Binds(pOptionsWnd);
	}
/**/
	AddMQ2KeyBind("RANGED",DoRangedBind);

	//EzDetour(KeypressHandler__ClearCommandStateArray,&KeypressHandlerHook::ClearCommandStateArray_Hook,&KeypressHandlerHook::ClearCommandStateArray_Trampoline);
//	EzDetour(KeypressHandler__HandleKeyDown,&KeypressHandlerHook::HandleKeyDown_Hook,&KeypressHandlerHook::HandleKeyDown_Trampoline);
//	EzDetour(KeypressHandler__HandleKeyUp,&KeypressHandlerHook::HandleKeyUp_Hook,&KeypressHandlerHook::HandleKeyUp_Trampoline);
	EzDetour(KeypressHandler__HandleKeyDown,HandleKeyDown_Hook,HandleKeyDown_Trampoline);
	EzDetour(KeypressHandler__HandleKeyUp,HandleKeyUp_Hook,HandleKeyUp_Trampoline);
	EzDetour(CXWndManager__HandleKeyboardMsg,&KeypressHandlerHook::HandleKeyboardMsg_Hook,&KeypressHandlerHook::HandleKeyboardMsg_Trampoline);
}

void ShutdownMQ2KeyBinds()
{
	BindList.Cleanup();
	//RemoveDetour(KeypressHandler__ClearCommandStateArray);
	RemoveDetour(KeypressHandler__HandleKeyDown);
	RemoveDetour(KeypressHandler__HandleKeyUp);
	RemoveDetour(CXWndManager__HandleKeyboardMsg);
}

BOOL AddMQ2KeyBind(PCHAR name, fMQExecuteCmd Function)
{
	DebugSpew("AddMQ2KeyBind(%s)",name);
	if (KeyBindByName(name))
	{
		DebugSpew("AddMQ2KeyBind(%s) - Name already in use",name);
		return false;
	}

	MQ2KeyBind* pBind = new MQ2KeyBind;
	pBind->State=false;
	strncpy(pBind->Name,name,32);
	pBind->Name[31]=0;
	CHAR szBuffer[MAX_STRING]={0};
	CHAR szName[MAX_STRING]={0};
	
	sprintf(szName,"%s_%s",pBind->Name,"Nrm");
	GetPrivateProfileString("Key Binds",szName,"-------",szBuffer,MAX_STRING,gszINIFilename);	
	ParseKeyCombo(szBuffer,pBind->Normal);
	sprintf(szName,"%s_%s",pBind->Name,"Alt");
	GetPrivateProfileString("Key Binds",szName,"-------",szBuffer,MAX_STRING,gszINIFilename);	
	ParseKeyCombo(szBuffer,pBind->Alt);

	pBind->Function=Function;

	unsigned long N=BindList.GetUnused();
	BindList[N]=pBind;
	SetKeyBindNameMap(name,N);
	
	return true;
}

BOOL GetMQ2KeyBind(PCHAR name, BOOL Alt, KeyCombo &Combo)
{
	if (MQ2KeyBind *pBind=KeyBindByName(name))
	{
		if (Alt)
			Combo=pBind->Alt;
		else
			Combo=pBind->Normal;
		return true;
	}
	return false;
}

BOOL RemoveMQ2KeyBind(PCHAR name)
{
	DebugSpew("RemoveMQ2KeyBind(%s)",name);
	string Lwr=name;
	MakeLower(Lwr);
	unsigned long N=BindNameMap[Lwr];
	if (!N)
		return false;
	--N;
	if (MQ2KeyBind* pBind=BindList[N])
	{
		BindNameMap[Lwr]=0;
		BindList[N]=0;
		delete pBind;
		return true;
	}
	return false;
}

BOOL PressMQ2KeyBind(PCHAR name, BOOL Hold)
{
	if (MQ2KeyBind *pBind=KeyBindByName(name))
	{
		pBind->Function(pBind->Name,true);
		if (!Hold)
			pBind->Function(pBind->Name,false);
		return true;
	}
	return false;
}

BOOL SetMQ2KeyBind(PCHAR name, BOOL Alternate, KeyCombo &Combo)
{
	if (MQ2KeyBind *pBind=KeyBindByName(name))
	{
		CHAR szName[MAX_STRING]={0};
		CHAR szBuffer[MAX_STRING]={0};
		if (!Alternate)
		{
			sprintf(szName,"%s_Nrm",pBind->Name);
			pBind->Normal=Combo;
		}
		else
		{
			sprintf(szName,"%s_Alt",pBind->Name);
			pBind->Alt=Combo;
		}
		WritePrivateProfileString("Key Binds",szName,DescribeKeyCombo(Combo,szBuffer),gszINIFilename);
		return true;
	}
	return false;
}

VOID MQ2KeyBindCommand(PSPAWNINFO pChar, PCHAR szLine)
{
	if (szLine[0]==0)
	{
		WriteChatColor("Usage: /bind <list|eqlist|[~]name <combo|clear>>");
		return;
	}
	CHAR szBuffer[MAX_STRING];
    CHAR szArg1[MAX_STRING] = {0};
    GetArg(szArg1,szLine,1);
    PCHAR szRest = GetNextArg(szLine);
	PCHAR szArg=&szArg1[0];
	bool AltKey=false;
	if (szArg[0]=='~')
	{
		AltKey=true;
		szArg=&szArg1[1];
	}
	unsigned long i;
	if (!stricmp(szArg,"list"))
	{
		// list binds
		CHAR szNormal[MAX_STRING]={0};
		CHAR szAlt[MAX_STRING]={0};
		WriteChatColor("MQ2 Binds");
		WriteChatColor("--------------");
		for (i = 0 ; i < BindList.Size ; i++)
		{
			if (MQ2KeyBind *pBind = BindList[i])
			{
				sprintf(szArg1,"[\ay%s\ax] Nrm:\at%s\ax Alt:\at%s\ax",pBind->Name,DescribeKeyCombo(pBind->Normal,szNormal),DescribeKeyCombo(pBind->Alt,szAlt));
				WriteChatColor(szArg1);			
			}
		}
		WriteChatColor("--------------");
		WriteChatColor("End MQ2 Binds");
		return;
	}
	if (!stricmp(szArg,"eqlist"))
	{
		CHAR szNormal[MAX_STRING]={0};
		CHAR szAlt[MAX_STRING]={0};
		// list eq binds
		WriteChatColor("EQ Binds");
		WriteChatColor("--------------");
		for (i = 0 ; i < nEQMappableCommands ; i++)
		{
			sprintf(szArg1,"[\ay%s\ax] Nrm:\at%s\ax Alt:\at%s\ax",szEQMappableCommands[i],DescribeKeyCombo(pKeypressHandler->NormalKey[i],szNormal),DescribeKeyCombo(pKeypressHandler->AltKey[i],szAlt));
			WriteChatColor(szArg1);			
		}
		WriteChatColor("--------------");
		WriteChatColor("End EQ Binds");
		return;
	}

	KeyCombo NewCombo;
	if (!ParseKeyCombo(szRest,NewCombo))
	{
		WriteChatColor("Invalid key combination");
		return;
	}

   if (!stricmp(szArg,"clearcombo")) 
   {
        KeyCombo ClearCombo;
        // mq2 binds
        for (i = 0; i < BindList.Size; i++) 
		{
            MQ2KeyBind* pBind = BindList[i];
            if (pBind) 
			{
                if (pBind->Alt == NewCombo && SetMQ2KeyBind(pBind->Name,true,ClearCombo)) 
				{
					sprintf(szArg1,"Alternate %s cleared",pBind->Name);
					WriteChatColor(szArg1);
                }
                if (pBind->Normal == NewCombo && SetMQ2KeyBind(pBind->Name,false,ClearCombo))
				{
					sprintf(szArg1,"Normal %s cleared",pBind->Name);
					WriteChatColor(szArg1);
                }
            }
        }

        // eq binds
        for (i = 0; i < nEQMappableCommands; i++) 
		{
            if (pKeypressHandler->AltKey[i] == NewCombo && SetEQKeyBindByNumber(i,true,ClearCombo)) 
			{
				sprintf(szArg1,"Alternate %s cleared",szEQMappableCommands[i] );
				WriteChatColor(szArg1);
            }
            if (pKeypressHandler->NormalKey[i] == NewCombo && SetEQKeyBindByNumber(i,false,ClearCombo))
			{
				sprintf(szArg1,"Normal %s cleared", szEQMappableCommands[i]);
				WriteChatColor(szArg1);
            }
        }
        return;
    } 



	if (SetMQ2KeyBind(szArg,AltKey,NewCombo))
	{
		MQ2KeyBind *pBind=KeyBindByName(szArg);
		sprintf(szArg1,"%s %s now bound as %s",AltKey?"Alternate":"Normal",pBind->Name,DescribeKeyCombo(NewCombo,szBuffer));
		WriteChatColor(szArg1);			
		return;
	}

	int N=FindMappableCommand(szArg);
	if (N<0)
	{
		WriteChatColor("Unknown bind command name");
		return;
	}

    if (SetEQKeyBindByNumber(N,AltKey,NewCombo))
	{
		sprintf( szArg1,"%s %s now bound as %s", 
			(AltKey)?("Alternate"):("Normal"), 
			szEQMappableCommands[N],
			DescribeKeyCombo((AltKey)?(pKeypressHandler->AltKey[N]):(pKeypressHandler->NormalKey[N]),szBuffer));
	}
}

VOID DoRangedBind(PCHAR Name,BOOL Down)
{
	if (Down && pTarget && gbRangedAttackReady)
	{
		pLocalPlayer->DoAttack(0x0B,0,pTarget);
		gbRangedAttackReady=0;
	}
}

BOOL DumpBinds(PCHAR Filename)
{
	CHAR szFilename[MAX_STRING]={0};
	sprintf(szFilename,"%s\\Configs\\%s",gszINIPath,Filename);
	if (!strchr(Filename,'.'))
		strcat_s(szFilename,".cfg");
	FILE *file=fopen(szFilename,"wt");
	if (!file)
	{
		return false;
	}
	CHAR szBuffer[MAX_STRING]={0};
	unsigned long N;
	for ( N = 0 ; N < nEQMappableCommands ; N++)
	{
		fprintf(file,"/bind %s %s\n",szEQMappableCommands[N],DescribeKeyCombo(pKeypressHandler->NormalKey[N],szBuffer));
		fprintf(file,"/bind ~%s %s\n",szEQMappableCommands[N],DescribeKeyCombo(pKeypressHandler->AltKey[N],szBuffer));
	}
	for ( N = 0 ; N < BindList.Size ; N++)
	{
		if (MQ2KeyBind *pBind=BindList[N])
		{
			fprintf(file,"/bind %s %s\n",pBind->Name,DescribeKeyCombo(pBind->Normal,szBuffer));
			fprintf(file,"/bind ~%s %s\n",pBind->Name,DescribeKeyCombo(pBind->Alt,szBuffer));
		}
	}
	fclose(file);
	return true;
}


