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
//#define DEBUG_TRY

#include "MQ2Main.h"
#include <map>
#include <string>
#include <algorithm>
using namespace std;

map<string,unsigned long> WindowMap;



PCHAR szClickNotification[] = { 
	"leftmouse",		//0
	"leftmouseup",		//1
	"leftmouseheld",	//2
	"leftmouseheldup",	//3
	"rightmouse",		//4
	"rightmouseup",		//5
	"rightmouseheld",	//6
	"rightmouseheldup",	//7
}; 

struct _WindowInfo
{
	char Name[128];
	CXWnd *pWnd;
	CXWnd **ppWnd;
};

CIndex <_WindowInfo*> WindowList(10);



bool GenerateMQUI();
void DestroyMQUI();

class SetScreenHook
{
public:
	void SetScreen_Detour(class CXStr *pName)
	{
		CHAR Name[MAX_STRING]={0};
		GetCXStr((PCXSTR)pName,Name,MAX_STRING);
		string WindowName=Name;
		MakeLower((WindowName));

		unsigned long N=WindowMap[WindowName];
		if (N)
		{
			N--;
			_WindowInfo *pWnd = WindowList[N];
			pWnd->pWnd=(CXWnd*)this;
			pWnd->ppWnd=0;
			DebugSpew("Updating WndNotification target '%s'",Name);
		}
		else
		{
			_WindowInfo *pWnd = new _WindowInfo;
			strcpy(pWnd->Name,Name);
			pWnd->pWnd=(CXWnd*)this;
			pWnd->ppWnd=0;
			
			N=WindowList.GetUnused();
			WindowList[N]=pWnd;

			WindowMap[WindowName]=N+1;
			DebugSpew("Adding WndNotification target '%s'",Name);
		}
		SetScreen_Trampoline(pName);
	}
	void SetScreen_Trampoline(class CXStr*);
};
DETOUR_TRAMPOLINE_EMPTY(void SetScreenHook::SetScreen_Trampoline(class CXStr*));

class CXWndManagerHook
{
public:
	int RemoveWnd_Detour(class CXWnd *pWnd)
	{
		if (pWnd)
		{
			for (unsigned long N = 0 ; N < WindowList.Size ; N++)
				if (_WindowInfo* pInfo=WindowList[N])
				{
					if (pWnd==pInfo->pWnd)
					{
						DebugSpew("Removing WndNotification target '%s'",pInfo->Name);
						string Name=pInfo->Name;
						MakeLower(Name);
						WindowMap[Name]=0;
						delete pInfo;
						WindowList[N]=0;
						break;
					}
				}
		}
		return RemoveWnd_Trampoline(pWnd);
	}
	int RemoveWnd_Trampoline(class CXWnd *);

};
DETOUR_TRAMPOLINE_EMPTY(int CXWndManagerHook::RemoveWnd_Trampoline(class CXWnd *));


class CXMLSOMDocumentBaseHook
{
public:
	int XMLRead(CXStr *A, CXStr *B, CXStr *C)
	{
		char Temp[256]={0};
		GetCXStr((PCXSTR)C,Temp,256);
		DebugSpew("XMLRead(%s)",Temp);
		if (!stricmp("EQUI.xml",Temp))
		{
			if (GenerateMQUI())
			{
				SetCXStr((PCXSTR*)&C,"MQUI.xml");
				int Ret=XMLRead_Trampoline(A,B,C);
				DestroyMQUI();
				return Ret;
			}
		}
		return XMLRead_Trampoline(A,B,C);
	}
	int XMLRead_Trampoline(CXStr *A, CXStr *B, CXStr *C);
};
DETOUR_TRAMPOLINE_EMPTY(int CXMLSOMDocumentBaseHook::XMLRead_Trampoline(CXStr *A, CXStr *B, CXStr *C)); 



VOID ListWindows(PSPAWNINFO pChar, PCHAR szLine);
VOID WndNotify(PSPAWNINFO pChar, PCHAR szLine);
VOID ItemNotify(PSPAWNINFO pChar, PCHAR szLine);
VOID ListItemSlots(PSPAWNINFO pChar, PCHAR szLine);

void InitializeMQ2Windows()
{
        int i;
	DebugSpew("Initializing MQ2 Windows");
        
    extern PCHAR szItemSlot[];

    for(i=0;i<MAX_INV_SIZE;i++)
        ItemSlotMap[szItemSlot[i]]=i;
	
	CHAR szOut[MAX_STRING]={0};

#define AddSlotArray(name,count,start)	\
	for (i = 0 ; i < count ; i++)\
	{\
	sprintf(szOut,#name"%d",i+1);\
		ItemSlotMap[szOut]=start+i;\
	}
	AddSlotArray(bank,8,2000);
	//AddSlotArray(sharedbank,2,2500);
	AddSlotArray(trade,8,3000);
	AddSlotArray(world,10,4000);
	AddSlotArray(enviro,10,4000);
	AddSlotArray(loot,31,5000);
	AddSlotArray(merchant,80,6000);
	AddSlotArray(bazaar,80,7000);
	AddSlotArray(inspect,31,8000);
#undef AddSlotArray

	EzDetour(CXMLSOMDocumentBase__XMLRead,&CXMLSOMDocumentBaseHook::XMLRead,&CXMLSOMDocumentBaseHook::XMLRead_Trampoline);
	EzDetour(CSidlScreenWnd__SetScreen,&SetScreenHook::SetScreen_Detour,&SetScreenHook::SetScreen_Trampoline);
	EzDetour(CXWndManager__RemoveWnd,&CXWndManagerHook::RemoveWnd_Detour,&CXWndManagerHook::RemoveWnd_Trampoline);


	AddCommand("/windows",ListWindows,false,true,false);
	AddCommand("/notify",WndNotify,false,true,false);
	AddCommand("/itemnotify",ItemNotify,false,true,false);
	AddCommand("/itemslots",ListItemSlots,false,true,false);

	if (pWndMgr)
	{
		CHAR Name[MAX_STRING]={0};
		PCSIDLWND pWnd=((_CXWNDMGR*)pWndMgr)->pWindows;
		while(pWnd)
		{
			if(IsBadReadPtr(pWnd,4))
				break;
			// process window
			if (CXMLData *pXMLData=((CXWnd*)pWnd)->GetXMLData())
			{
					if (pXMLData->Type==UI_Screen)
					{
						GetCXStr(pXMLData->Name.Ptr,Name,MAX_STRING);
						string WindowName=Name;
						MakeLower((WindowName));

						unsigned long N=WindowMap[WindowName];
						if (N)
						{
							N--;
							_WindowInfo *pNewWnd = WindowList[N];
							pNewWnd->pWnd=(CXWnd*)pWnd;
							pNewWnd->ppWnd=0;
							DebugSpew("Updating WndNotification target '%s'",Name);
						}
						else
						{
							_WindowInfo *pNewWnd = new _WindowInfo;
							strcpy(pNewWnd->Name,Name);
							pNewWnd->pWnd=(CXWnd*)pWnd;
							pNewWnd->ppWnd=0;
							
							N=WindowList.GetUnused();
							WindowList[N]=pNewWnd;

							WindowMap[WindowName]=N+1;
							DebugSpew("Adding WndNotification target '%s'",Name);
						}




					}
			}




			if (CXWnd *pTemp=((CXWnd*)pWnd)->GetFirstChildWnd())
			{
				pWnd=(PCSIDLWND)pTemp;
			}
			else
			{
				while(1)
				{
					if (CXWnd *pTemp=((CXWnd*)pWnd)->GetNextSib())
					{
						pWnd=(PCSIDLWND)pTemp;
						break;
					}
					pWnd=pWnd->pParentWindow;
					if (!pWnd)
					{
						break;
					}
				}
			}
		}




	}
}

void ShutdownMQ2Windows()
{
	DebugSpew("Shutting down MQ2 Windows");
	RemoveCommand("/windows");
	RemoveCommand("/notify");
	RemoveCommand("/itemnotify");
	RemoveCommand("/itemslots");
	RemoveDetour(CXMLSOMDocumentBase__XMLRead);
	RemoveDetour(CSidlScreenWnd__SetScreen);
	RemoveDetour(CXWndManager__RemoveWnd);
	WindowList.Cleanup();
}

bool GenerateMQUI()
{
	// create EverQuest\uifiles\default\MQUI.xml
	if (!pXMLFiles)
	{
		DebugSpew("GenerateMQUI::Not Generating MQUI.xml, no files in our list");
		return false;
	}
	DebugSpew("GenerateMQUI::Generating MQUI.xml");
	CHAR szOrgFilename[MAX_PATH]={0};
	CHAR szFilename[MAX_PATH]={0};
	sprintf(szOrgFilename,"%s\\uifiles\\default\\EQUI.xml",gszEQPath);
	sprintf(szFilename,"%s\\uifiles\\default\\MQUI.xml",gszEQPath);
	char Buffer[2048];
	FILE *forg=fopen(szOrgFilename,"rt");
	if (!forg)
	{
		DebugSpew("GenerateMQUI::could not open %s",szOrgFilename);
		return false;
	}
	FILE *fnew=fopen(szFilename,"wt");
	if (!fnew)
	{
		DebugSpew("GenerateMQUI::could not open %s",szFilename);
		fclose(forg);
		return false;
	}
	while(fgets(Buffer,2048,forg))
	{
		if (strstr(Buffer,"</Composite>"))
		{
//			DebugSpew("GenerateMQUI::Inserting our xml files");
			PMQXMLFILE pFile=pXMLFiles;
			while(pFile)
			{
//				DebugSpew("GenerateMQUI::Inserting %s",pFile->szFilename);
				fprintf(fnew,"<Include>%s</Include>\n",pFile->szFilename);
				pFile=pFile->pNext;
			}
		}
		fprintf(fnew,"%s",Buffer);
	}
	fclose(fnew);
	fclose(forg);
	return true;
}

void DestroyMQUI()
{
	// delete EverQuest\uifiles\default\MQUI.xml
	CHAR szFilename[MAX_PATH];
	sprintf(szFilename,"%s\\uifiles\\default\\MQUI.xml",gszEQPath);
	remove(szFilename);
}

void AddXMLFile(const char *filename)
{
	PMQXMLFILE pFile=pXMLFiles;
	PMQXMLFILE pLast=0;
	while(pFile)
	{
		if (!stricmp(pFile->szFilename,filename))
			return; // already there.
		pLast=pFile;
		pFile=pFile->pNext;
	}
	CHAR szBuffer[MAX_PATH]={0};
	sprintf(szBuffer,"%s\\uifiles\\default\\%s",gszEQPath,filename);
	if (!_FileExists(szBuffer))
	{
		WriteChatf("UI file %s not found in uifiles\\default.  Please copy it there, reload the UI, and reload this plugin.",filename);
		return;
	}

	DebugSpew("Adding XML File %s",filename);
	if (gGameState==GAMESTATE_INGAME)
	{
		WriteChatf("UI file %s added, you must reload your UI for this to take effect.",filename);
	}

	pFile = new MQXMLFILE;
	pFile->pLast=pLast;
	if (pLast)
		pLast->pNext=pFile;
	else
		pXMLFiles=pFile;
	pFile->pNext=0;
	strcpy(pFile->szFilename,filename);
}

void RemoveXMLFile(const char *filename)
{
	PMQXMLFILE pFile=pXMLFiles;
	while(pFile)
	{
		if (!stricmp(pFile->szFilename,filename))
		{
			DebugSpew("Removing XML File %s",filename);
			if (pFile->pLast)
				pFile->pLast->pNext=pFile->pNext;
			else
				pXMLFiles=pFile->pNext;
			if (pFile->pNext)
				pFile->pNext=pFile->pLast->pNext;
			delete pFile;
			return;
		}
		pFile=pFile->pNext;
	}
}

CXWnd *FindMQ2Window(PCHAR WindowName)
{
	_WindowInfo *pInfo = NULL;

	string Name=WindowName;
	MakeLower(Name);

	unsigned long N = WindowMap[Name];
	if (!N)
	{
		PITEMINFO pPack=0;
		if (!strnicmp(WindowName,"bank",4))
		{
			unsigned long nPack=atoi(&WindowName[4]);
			if (nPack && nPack<=NUM_BANK_SLOTS)
			{
				pPack=((PCHARINFO)pCharData)->Bank[nPack-1];
			}
		}
		else if (!strnicmp(WindowName,"pack",4))
		{
			unsigned long nPack=atoi(&WindowName[4]);
			if (nPack && nPack<=8)
			{
				pPack=((PCHARINFO)pCharData)->Inventory.Pack[nPack-1];
			}
		}
		else if (!stricmp(WindowName,"enviro"))
		{
			pPack=((PEQ_CONTAINERWND_MANAGER)pContainerMgr)->pWorldItems;
		}
		if (!pPack)
		{
			MQ2TYPEVAR pvar;
			dataFindItem(WindowName,pvar);
			PITEMINFO pitem = (PITEMINFO)pvar.Ptr;
			if(pitem)
				return (CXWnd*)FindContainerForContents(pitem);
			return 0;
		}
		return (CXWnd*)FindContainerForContents(pPack);
		
	}
	N--;

	pInfo=WindowList[N];
	if (!pInfo)
	{
		WindowMap[Name]=0;
		return 0;
	}
	
	if (pInfo->pWnd)
	{
		return pInfo->pWnd;
	}
	else
	{
		if (pInfo->ppWnd)
		{
			return *pInfo->ppWnd;
		}
		else
		{
			WindowMap[Name]=0;
			delete pInfo;
			WindowList[N]=0;
			WindowMap[Name]=0;
			return 0;
		}
	}

	return 0;
}

bool SendWndClick(CXWnd *pWnd, PCHAR ClickNotification)
{
	if (!pWnd)
		return false;
	for (unsigned long i = 0 ; i < 8 ; i++)
	{
		if (!stricmp(szClickNotification[i],ClickNotification))
		{
			DebugTry(CXRect rect= pWnd->GetScreenRect());
			DebugTry(CXPoint pt=rect.CenterPoint());
			switch(i)
			{
			case 0:
				DebugTry(pWnd->HandleLButtonDown(pt,0x20000));
				return true;
			case 1:
				DebugTry(pWnd->HandleLButtonDown(pt,0x20000));
				DebugTry(pWnd->HandleLButtonUp(pt,0));
				return true;
			case 2:
				DebugTry(pWnd->HandleLButtonDown(pt,0x20000));
				DebugTry(pWnd->HandleLButtonHeld(pt,0));
				return true;
			case 3:
				DebugTry(pWnd->HandleLButtonDown(pt,0x20000));
				DebugTry(pWnd->HandleLButtonHeld(pt,0));
				DebugTry(pWnd->HandleLButtonUpAfterHeld(pt,0));
				return true;
			case 4:
				DebugTry(pWnd->HandleRButtonDown(pt,0));
				return true;
			case 5:
				DebugTry(pWnd->HandleRButtonDown(pt,0));
				DebugTry(pWnd->HandleRButtonUp(pt,0));
				return true;
			case 6:
				DebugTry(pWnd->HandleRButtonDown(pt,0));
				DebugTry(pWnd->HandleRButtonHeld(pt,0));
				return true;
			case 7:
				DebugTry(pWnd->HandleRButtonDown(pt,0));
				DebugTry(pWnd->HandleRButtonHeld(pt,0));
				DebugTry(pWnd->HandleRButtonUpAfterHeld(pt,0));
				return true;
			};
		}
	}
	return false;
}

bool SendWndClick(PCHAR WindowName, PCHAR ScreenID, PCHAR ClickNotification)
{
	CXWnd *pWnd=FindMQ2Window(WindowName);
	if (!pWnd)
	{
		MacroError("Window '%s' not available.",WindowName);
		return false;
	}
	if (ScreenID && ScreenID[0] && ScreenID[0]!='0')
	{
		CXWnd *pButton=((CSidlScreenWnd*)(pWnd))->GetChildItem(ScreenID);
		if (!pButton)
		{
			MacroError("Window '%s' child '%s' not found.",WindowName,ScreenID);
			return false;
		}
		pWnd=pButton;
	}

	for (unsigned long i = 0 ; i < 8 ; i++)
	{
		if (!stricmp(szClickNotification[i],ClickNotification))
		{
			CXRect rect= pWnd->GetScreenRect();
			CXPoint pt=rect.CenterPoint();
			switch(i)
			{
			case 0:
				pWnd->HandleLButtonDown(pt,0x20000);
				return true;
			case 1:
				pWnd->HandleLButtonDown(pt,0x20000);
				pWnd->HandleLButtonUp(pt,0);
				return true;
			case 2:
				pWnd->HandleLButtonHeld(pt,0);
				return true;
			case 3:
				pWnd->HandleLButtonDown(pt,0x20000);
				pWnd->HandleLButtonHeld(pt,0);
				pWnd->HandleLButtonUpAfterHeld(pt,0);
				return true;
			case 4:
				pWnd->HandleRButtonDown(pt,0);
				return true;
			case 5:
				pWnd->HandleRButtonDown(pt,0);
				pWnd->HandleRButtonUp(pt,0);
				return true;
			case 6:
				pWnd->HandleRButtonDown(pt,0);
				pWnd->HandleRButtonHeld(pt,0);
				return true;
			case 7:
				pWnd->HandleRButtonDown(pt,0);
				pWnd->HandleRButtonHeld(pt,0);
				pWnd->HandleRButtonUpAfterHeld(pt,0);
				return true;
			};
		}
	}
	return false;
}

bool SendListSelect(PCHAR WindowName, PCHAR ScreenID, DWORD Value)
{
	CXWnd *pWnd=FindMQ2Window(WindowName);
	if (!pWnd)
	{
		MacroError("Window '%s' not available.",WindowName);
		return false;
	}
	if (ScreenID && ScreenID[0] && ScreenID[0]!='0')
	{
		CListWnd *pList=(CListWnd*)((CSidlScreenWnd*)(pWnd))->GetChildItem(ScreenID);
		if (!pList)
		{
			MacroError("Window '%s' child '%s' not found.",WindowName,ScreenID);
			return false;
		}
		if (((CXWnd*)pList)->GetType()==UI_Listbox)
			pList->SetCurSel(Value);
		else if (((CXWnd*)pList)->GetType()==UI_Combobox)
			((CComboWnd*)pList)->SetChoice(Value);
		else
		{
			MacroError("Window '%s' child '%s' cannot accept this notification.",WindowName,ScreenID);
			return false;
		}
		return true;
	}
	return false;
}

bool SendWndNotification(PCHAR WindowName, PCHAR ScreenID, DWORD Notification, VOID *Data)
{
	CHAR szOut[MAX_STRING] = {0};
	CXWnd *pWnd=FindMQ2Window(WindowName);
	if (!pWnd)
	{
		sprintf(szOut,"Window '%s' not available.",WindowName);
		return false;
	}
	CXWnd *pButton=0;
	if (ScreenID && ScreenID[0])
	{
		pButton=((CSidlScreenWnd*)(pWnd))->GetChildItem(ScreenID);
		if (!pButton)
		{
			sprintf(szOut,"Window '%s' child '%s' not found.",WindowName,ScreenID);
			WriteChatColor(szOut,USERCOLOR_DEFAULT);
			return false;
		}
	}
	
	((CXWnd*)(pWnd))->WndNotification(pButton,Notification,Data);

	return true;
}

void AddWindow(char *WindowName, CXWnd **ppWindow)
{
	string Name=WindowName;
	MakeLower(Name);

	unsigned long N=WindowMap[Name];
	if (N)
	{
		N--;
		_WindowInfo *pWnd = WindowList[N];
		pWnd->pWnd=0;
		pWnd->ppWnd=ppWindow;
		DebugSpew("Updating WndNotification target '%s'",WindowName);
	}
	else
	{
		_WindowInfo *pWnd = new _WindowInfo;
		strcpy(pWnd->Name,WindowName);
		pWnd->pWnd=0;
		pWnd->ppWnd=ppWindow;
		
		N=WindowList.GetUnused();
		WindowList[N]=pWnd;

		WindowMap[WindowName]=N+1;
		DebugSpew("Adding WndNotification target '%s'",Name);
	}

}

void RemoveWindow(char *WindowName)
{
	string Name=WindowName;
	MakeLower(Name);

	unsigned long N=WindowMap[Name];
	if (N)
	{
		N--;
		WindowMap[Name]=0;
		if (_WindowInfo *pInfo=WindowList[N])
		{
			delete pInfo;
			WindowList[N]=0;
		}
	}
}

VOID ListWindows(PSPAWNINFO pChar, PCHAR szLine)
{
	CHAR Name[MAX_STRING]={0};
	CHAR AltName[MAX_STRING]={0};
	CHAR Type[MAX_STRING]={0};
	unsigned long Count=0;
	if (!szLine || !szLine[0])
	{
		WriteChatColor("List of available windows");
		WriteChatColor("-------------------------");
		for (unsigned long N = 0 ; N < WindowList.Size ; N++)
			if (_WindowInfo *pInfo=WindowList[N])
			{
				WriteChatf("%s",pInfo->Name);
				Count++;
			}
		WriteChatf("%d available windows",Count);
	}
	else
	{
		// list children of..
		string WindowName=szLine;
		MakeLower(WindowName);
		unsigned long N = WindowMap[WindowName];
		if (!N)
		{
			WriteChatf("Window '%s' not available",szLine);
			return;
		}
		N--;
		WriteChatf("Listing child windows of '%s'",szLine);
		WriteChatColor("-------------------------");
		if (_WindowInfo *pInfo=WindowList[N])
		{
			PCSIDLWND pWnd;//=pInfo->pWnd->pChildren;
			if (pInfo->pWnd->HasChildren)
				pWnd=(PCSIDLWND)pInfo->pWnd->pChildren;
			else
				pWnd=(PCSIDLWND)pWndMgr->GetFirstChildWnd(pInfo->pWnd);

			while(pWnd)
			{
				if (CXMLData *pXMLData=((CXWnd*)pWnd)->GetXMLData())
				{
					Count++;
					GetCXStr(pXMLData->TypeName.Ptr,Type,MAX_STRING);
					GetCXStr(pXMLData->Name.Ptr,Name,MAX_STRING);
					GetCXStr(pXMLData->ScreenID.Ptr,AltName,MAX_STRING);
					if (AltName[0] && stricmp(Name,AltName))
						WriteChatf("[\ay%s\ax] [\at%s\ax] [Custom UI-specific: \at%s\ax]",Type,Name,AltName);
					else
						WriteChatf("[\ay%s\ax] [\at%s\ax]",Type,Name);
				}
				pWnd=(PCSIDLWND)pInfo->pWnd->GetNextChildWnd((CXWnd*)pWnd);
			}
			WriteChatf("%d child windows",Count);
		}
	}
}

PCHAR szWndNotification[] = { 
	0,			//0 
	"leftmouse",	//1
	"leftmouseup",	//2
	"rightmouse",		//3
	0,		//4
	0,		//5
	"enter",		//6
	0,		//7
	0,		//8
	0,		//9
	"close",		//10
	0,		//11
	0,		//12
	0,		//13
	"newvalue",		//14
	0,		//15
	0,		//16
	0,		//17
	0,		//18
	0,		//19
	0,		//20
	"mouseover",	//21
	"history",		//22
	"leftmousehold",	//23
	0,		//24
	0,		//25
	0,		//26
	0,		//27
	0,		//28
	0,		//29
}; 

VOID WndNotify(PSPAWNINFO pChar, PCHAR szLine)
{
	CHAR szArg1[MAX_STRING] = {0}; 
	CHAR szArg2[MAX_STRING] = {0}; 
	CHAR szArg3[MAX_STRING] = {0}; 
	CHAR szArg4[MAX_STRING] = {0}; 

	GetArg(szArg1, szLine, 1);
	GetArg(szArg2, szLine, 2);
	GetArg(szArg3, szLine, 3);
	GetArg(szArg4, szLine, 4);

	if (!szArg3[0])
	{
		SyntaxError("Syntax: /notify <window|\"item\"> <control|0> <notification> [notification data]");
		return;
	}
	unsigned long Data=0;
	if (szArg4[0])
		Data=atoi(szArg4);

	if (Data==0 && SendWndClick(szArg1,szArg2,szArg3))
		return;
	if (!stricmp(szArg3,"listselect"))
	{
		SendListSelect(szArg1,szArg2,Data-1);
		return;
	}

	for (unsigned long i = 0 ; i < 30 ; i++)
	{
		if (szWndNotification[i] && !stricmp(szWndNotification[i],szArg3))
		{
			if (szArg2[0]=='0')
			{
				if (!SendWndNotification(szArg1,0,i,(void*)Data))
				{
					MacroError("Could not send notification to %s %s",szArg1,szArg2);
				}
			}
			else if (!SendWndNotification(szArg1,szArg2,i,(void*)Data))
			{
				MacroError("Could not send notification to %s %s",szArg1,szArg2);
			}
			return;
		}
	}
	MacroError("Invalid notification '%s'",szArg3);
}

// item slots:
// 2000-2015 bank window
// 2500-2501 shared bank
// 5000-5031 loot window
// 3000-3008 trade window (including npc)
// 4000-4008 world container window
// 6000-6080 merchant window
// 7000-7080 bazaar window
// 8000-8031 inspect window



VOID ItemNotify(PSPAWNINFO pChar, PCHAR szLine)
{
	CHAR szArg1[MAX_STRING] = {0}; 
	CHAR szArg2[MAX_STRING] = {0}; 
//	CHAR szOut[MAX_STRING] = {0};

	PCHAR pNotification=&szArg2[0];

	GetArg(szArg1, szLine, 1);
	GetArg(szArg2, szLine, 2);
	CInvSlot *pSlot=0;
	if (!szArg2[0])
	{
		WriteChatColor("Syntax: /itemnotify [<itemname> OR <slot|#>] <notification>");
		WriteChatColor("Syntax to drop INTO a slot inside a bag: /itemnotify in [<bagname> OR <bagslot#>] [optional <slot#>]");
		WriteChatColor("if slot# is NOT specified it will be placed in first empty slot it finds");
		return;
	}
	if (!stricmp(szArg1,"in"))
	{
		CHAR szArg3[MAX_STRING] = {0};
		CHAR szArg4[MAX_STRING] = {0};

		GetArg(szArg3, szLine, 3);
		GetArg(szArg4, szLine, 4);
		if (!szArg2[0])
		{
			WriteChatColor("Syntax to drop into a slot inside a bag: /itemnotify in [<bagname> OR <bagslot#>] [optional <slot#>]");
			WriteChatColor("if slot# is NOT specified it will be placed in first empty slot it finds");
			return;
		}

		PITEMINFO pPack=0;
		if (!strnicmp(szArg2,"bank",4))
		{
			unsigned long nPack=atoi(&szArg2[4]);
			if (nPack && nPack<=NUM_BANK_SLOTS)
			{
				pPack=pChar->pCharInfo->Bank[nPack-1];
			}
		}
		else if (!strnicmp(szArg2,"sharedbank",4))
		{
			unsigned long nPack=atoi(&szArg2[4]);
			if (nPack && nPack<=2)
			{
				pPack=pChar->pCharInfo->Bank[16+nPack-1];
			}
		}
		else if (!strnicmp(szArg2,"pack",4))
		{
			unsigned long nPack=atoi(&szArg2[4]);
			if (nPack && nPack<=8)
			{
				pPack=pChar->pCharInfo->Inventory.Pack[nPack-1];
			}
		}
		else if (!stricmp(szArg2,"enviro"))
		{
			pPack=((PEQ_CONTAINERWND_MANAGER)pContainerMgr)->pWorldItems;
		}
		else {
			MQ2TYPEVAR pvar;
			if(dataFindItem(szArg2,pvar)) {
				pPack = (PITEMINFO)pvar.Ptr;
			}
		}
		if (!pPack)
		{
			WriteChatf("No item at '%s'",szArg2);
			return;
		}
		PEQCONTAINERWINDOW pWnd=FindContainerForContents(pPack);
		if (!pWnd)
		{
			WriteChatf("%s not found or open",szArg2);
			return;
		}
		if (szArg3[0]) {
			unsigned long nSlot=atoi(szArg3);
			if(nSlot && nSlot <= pPack->Container.Slots)
			{
				PEQINVSLOTWND pSlotWnd=(PEQINVSLOTWND)pWnd->pSlots[nSlot-1];
				pSlot=pInvSlotMgr->FindInvSlot(pSlotWnd->InvSlot);
			}
			if (szArg4[0]) {
				pNotification=&szArg4[0];
			} else {
				pNotification="leftmouseup";
			}
			goto justclickit;
		} else { //no slot specified, so see if there is an empty one
			//but first lets check if there is something on the cursor
			//to actually drop into the bag
			if(pChar && pChar->pCharInfo && pChar->pCharInfo->Cursor) {
				for(int nSlot=0;nSlot<pPack->Container.Slots;nSlot++) {
					if(!pPack->Container.Contents[nSlot]) {//its empty
						PEQINVSLOTWND pSlotWnd=(PEQINVSLOTWND)pWnd->pSlots[nSlot];
						if(pSlotWnd) {
							pSlot = pInvSlotMgr->FindInvSlot(pSlotWnd->InvSlot);
							break;
						}
					}
				}
				if(!pSlot) {
					WriteChatf("The %s does not have any empty slots to drop the %s in",pPack->Name,pChar->pCharInfo->Cursor->Name);
					return;
				}
				pNotification="leftmouseup";
				goto justclickit;
			} else {
				WriteChatf("Your cursor is empty.");
				return;
			}
		}
	}
	else
	{
		unsigned long Slot=atoi(szArg1);
		if (Slot==0)
		{
			Slot=ItemSlotMap[strlwr(szArg1)];
		}
		if (Slot==0 && szArg1[0]!='0' && stricmp(szArg1,"charm"))
		{
			WriteChatf("Invalid item slot '%s'",szArg1);
			return;
		}
		DebugTry(pSlot=pInvSlotMgr->FindInvSlot(Slot));
	}
justclickit:
	if (!pSlot)
	{
		WriteChatf("Could not send notification to %s %s",szArg1,szArg2);
		return;
	}
	DebugSpew("ItemNotify: Calling SendWndClick");
	if (!SendWndClick((CXWnd*)((PEQINVSLOT)pSlot)->pInvSlotWnd,pNotification))
	{
		WriteChatf("Could not send notification to %s %s",szArg1,szArg2);
	}
}

VOID ListItemSlots(PSPAWNINFO pChar, PCHAR szLine)
{
	PEQINVSLOTMGR pMgr=(PEQINVSLOTMGR)pInvSlotMgr;
	if (!pMgr)
		return;
//	CHAR szOut[MAX_STRING]={0};
	if (!szLine || !szLine[0])
	{
		unsigned long Count=0;
		WriteChatColor("List of available item slots");
		WriteChatColor("-------------------------");
		for (unsigned long N = 0 ; N < 0x1C2 ; N++)
			if (PEQINVSLOT pSlot=pMgr->SlotArray[N])
			{
				if (pSlot->pInvSlotWnd)
				{
					WriteChatf("inv slot %d",pSlot->pInvSlotWnd->InvSlot);
					Count++;
				}
			}
		WriteChatf("%d available item slots",Count);
	}
}
