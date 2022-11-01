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

class CDisplayHook 
{ 
public: 
	VOID CleanUI_Trampoline(VOID); 
	VOID CleanUI_Detour(VOID) 
	{ 
		Benchmark(bmPluginsCleanUI,DebugTry(PluginsCleanUI()));
		DebugTry(CleanUI_Trampoline());
	} 

	VOID ReloadUI_Trampoline(bool);
	VOID ReloadUI_Detour(bool UseINI)
	{
		DebugTry(ReloadUI_Trampoline(UseINI));
		Benchmark(bmPluginsReloadUI,DebugTry(PluginsReloadUI()));
	}

	bool GetWorldFilePath_Trampoline(char *, char *);
	bool GetWorldFilePath_Detour(char *Filename, char *FullPath)
	{
		if (!stricmp(FullPath,"bmpwad8.s3d"))
		{
			sprintf(Filename,"%s\\bmpwad8.s3d",gszINIPath);
			if (_access(Filename,0)!=-1)
			{

				return 1;
			}
		}
		
		bool Ret=GetWorldFilePath_Trampoline(Filename,FullPath);
		return Ret;
	}
	int CXWnd__DoAllDrawing_Trampoline(void);
	int CXWnd__DoAllDrawing_Detour(void)
	{
		int ret = CXWnd__DoAllDrawing_Trampoline();
		return ret;
	}	
}; 

int __cdecl CDisplay__WriteTextHD2_Trampoline(char const *,int,int,COLORREF,DWORD);
int __cdecl CDisplay__WriteTextHD2_Detour(char const *text,int X,int Y,COLORREF color,DWORD unknown) 
{ 
	//WriteChatf("CDisplay__WriteTextHD2_Detour %s %d %d %x %x",text,X,Y,color,unknown);
	return CDisplay__WriteTextHD2_Trampoline(text,X,Y,color,unknown);
}
DETOUR_TRAMPOLINE_EMPTY(int CDisplay__WriteTextHD2_Trampoline(char const *,int,int,COLORREF,DWORD)); 

DWORD __cdecl DrawHUD_Trampoline(DWORD, DWORD, DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD);
DWORD __cdecl DrawHUD_Detour(DWORD a, DWORD b, DWORD c,DWORD d,DWORD e,DWORD gworld,DWORD g,DWORD h,DWORD i,DWORD j) 
{ 
	DrawHUDParams[0]=a;
	DrawHUDParams[1]=b;
	DrawHUDParams[2]=c;
	DrawHUDParams[3]=d;
	DrawHUDParams[4]=e;
	DrawHUDParams[5]=gworld;
	DrawHUDParams[6]=g;
	DrawHUDParams[7]=h;
	DrawHUDParams[8]=i;
	DrawHUDParams[9]=j;
	int Ret = 0;
	/*if (gbHUDUnderUI || gbAlwaysDrawMQHUD) {
		/*if(pDisplay) {
			pDisplay->WriteTextHD2("HELLO WORLD",100,300,0x0000F0,*(DWORD *)0x63D3B0);
			pDisplay->WriteTextHD2("HELLO WORLD 1",100,310,1,*(DWORD *)0x63D3B0);
			pDisplay->WriteTextHD2("HELLO WORLD 2",100,320,2,*(DWORD *)0x63D3B0);
			pDisplay->WriteTextHD2("HELLO WORLD 3",100,330,3,*(DWORD *)0x63D3B0);
			pDisplay->WriteTextHD2("HELLO WORLD 4",100,340,4,*(DWORD *)0x63D3B0);
			pDisplay->WriteTextHD2("HELLO WORLD 5",100,350,5,*(DWORD *)0x63D3B0);
			pDisplay->WriteTextHD2("HELLO WORLD 6",100,360,6,*(DWORD *)0x63D3B0);
			pDisplay->WriteTextHD2("HELLO WORLD 7",100,370,7,*(DWORD *)0x63D3B0);
			pDisplay->WriteTextHD2("HELLO WORLD 8",100,380,8,*(DWORD *)0x63D3B0);
		}*/
	//} else {
		Ret= DrawHUD_Trampoline(a,b,c,d,e,gworld,g,h,i,j);
		//if(pDisplay)
		//	pDisplay->WriteTextHD2("HELLO WORLD",100,100,0xF0F0F0,*(DWORD *)0x63D3B0);
		Benchmark(bmPluginsDrawHUD,PluginsDrawHUD());
		/*if (HMODULE hmEQPlayNice=GetModuleHandle("EQPlayNice.dll"))
		{
			if (fMQPulse pEQPlayNicePulse=(fMQPulse)GetProcAddress(hmEQPlayNice,"Compat_DrawIndicator"))
				pEQPlayNicePulse();
		}*/
	//}
	return Ret;
} 
DETOUR_TRAMPOLINE_EMPTY(DWORD DrawHUD_Trampoline(DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD)); 

void DrawHUD()
{
	return;
	if (gbAlwaysDrawMQHUD || (gGameState==GAMESTATE_INGAME && gbHUDUnderUI && gbShowNetStatus))
	{
		if (DrawHUDParams[0] && gGameState==GAMESTATE_INGAME && gbShowNetStatus)
		{
			DrawHUD_Trampoline(DrawHUDParams[0],DrawHUDParams[1],DrawHUDParams[2],DrawHUDParams[3],DrawHUDParams[4],DrawHUDParams[5],DrawHUDParams[6],DrawHUDParams[7],DrawHUDParams[8],DrawHUDParams[9]);
			DrawHUDParams[0]=0;
		}
		Benchmark(bmPluginsDrawHUD,PluginsDrawHUD());
		/*if (HMODULE hmEQPlayNice=GetModuleHandle("EQPlayNice.dll"))
		{
			if (fMQPulse pEQPlayNicePulse=(fMQPulse)GetProcAddress(hmEQPlayNice,"Compat_DrawIndicator"))
				pEQPlayNicePulse();
		}*/

	}
	else
		DrawHUDParams[0]=0;
}


VOID DrawHUDText(PCHAR Text, DWORD X, DWORD Y, DWORD Argb)
{

	DWORD sX=((PCXWNDMGR)pWndMgr)->ScreenExtentX;
	DWORD sY=((PCXWNDMGR)pWndMgr)->ScreenExtentY;

	CTextureFont* pFont=0;
	DWORD* ppDWord=(DWORD*)((PCXWNDMGR)pWndMgr)->font_list_ptr;
	if (ppDWord[1]<=2)
	{
		pFont=(CTextureFont*)ppDWord[0];
	}
	else
	{
		pFont=(CTextureFont*)ppDWord[2];
	}
	Argb|=0xC8000000;
	pFont->DrawWrappedText(Text,X,Y,sX-X,CXRect(X,Y,sX,sY),Argb,1,0);
}

class EQ_LoadingSHook
{
public:

	bool WriteTextHD_Trampoline(char *,int,int,int,int);
	bool WriteTextHD_Detour(char *A,int B,int C,int D,int E)
	{
		return WriteTextHD_Trampoline("MQ2: Think of it as evolution in action.",B,C,D,E);
	}
};

DETOUR_TRAMPOLINE_EMPTY(bool CDisplayHook::GetWorldFilePath_Trampoline(char *, char *)); 
DETOUR_TRAMPOLINE_EMPTY(bool EQ_LoadingSHook::WriteTextHD_Trampoline(char *,int,int,int,int)); 
DETOUR_TRAMPOLINE_EMPTY(VOID CDisplayHook::CleanUI_Trampoline(VOID)); 
DETOUR_TRAMPOLINE_EMPTY(VOID CDisplayHook::ReloadUI_Trampoline(bool)); 
//DETOUR_TRAMPOLINE_EMPTY(int CDisplayHook::CXWnd__DoAllDrawing_Trampoline(void)); 

VOID InitializeDisplayHook()
{
	DebugSpew("Initializing Display Hooks");
	EzDetour(CDisplay__CleanGameUI,&CDisplayHook::CleanUI_Detour,&CDisplayHook::CleanUI_Trampoline);
	EzDetour(CDisplay__ReloadUI,&CDisplayHook::ReloadUI_Detour,&CDisplayHook::ReloadUI_Trampoline);
	EzDetour(CDisplay__GetWorldFilePath,&CDisplayHook::GetWorldFilePath_Detour,&CDisplayHook::GetWorldFilePath_Trampoline);
	//EzDetour(CXWnd__DoAllDrawing,&CDisplayHook::CXWnd__DoAllDrawing_Detour,&CDisplayHook::CXWnd__DoAllDrawing_Trampoline);
	EzDetour(DrawNetStatus,&DrawHUD_Detour,&DrawHUD_Trampoline);
	EzDetour(EQ_LoadingS__WriteTextHD,&EQ_LoadingSHook::WriteTextHD_Detour,&EQ_LoadingSHook::WriteTextHD_Trampoline);
	EzDetour(CDisplay__WriteTextHD2,CDisplay__WriteTextHD2_Detour,CDisplay__WriteTextHD2_Trampoline);

}

VOID ShutdownDisplayHook()
{
	PluginsCleanUI();
	DebugSpew("Shutting down Display Hooks");

	RemoveDetour(CDisplay__CleanGameUI);
	RemoveDetour(CDisplay__ReloadUI);
	RemoveDetour(DrawNetStatus);
	RemoveDetour(EQ_LoadingS__WriteTextHD);
	RemoveDetour(CDisplay__GetWorldFilePath);
	RemoveDetour(CDisplay__WriteTextHD2);
	//RemoveDetour(CXWnd__DoAllDrawing);
}
