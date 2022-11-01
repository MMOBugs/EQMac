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

namespace MQ2Prototypes
{
typedef PCHAR   (__stdcall *fEQGetStringByID)(DWORD);
typedef VOID    (__cdecl *fEQCommand)(PSPAWNINFO, PCHAR);
typedef HRESULT (__stdcall *fGetDeviceState)(THIS_ DWORD, LPVOID);
typedef DWORD   (__stdcall *fEQScreenItem)(DWORD, DWORD, DWORD);
typedef DWORD   (__stdcall *fEQScreenSpawn)(DWORD, DWORD);
typedef PCHAR   (__stdcall *fEQNewUIINI)(VOID);
typedef VOID    (__cdecl   *fEQMemSpell)(DWORD,DWORD);
typedef VOID    (__cdecl *fEQLoadSpells)(PSPELLFAVORITE,DWORD);
typedef VOID    (__cdecl *fEQSelectItem)(int,DWORD);//public: void __thiscall CMerchantWnd::SelectBuySellSlot(int,class CTextureAnimation *)
typedef VOID    (__cdecl *fEQBuyItem)(int);//private: void __thiscall CMerchantWnd::RequestBuyItem(int)
typedef VOID    (__cdecl *fEQSellItem)(int);//private: void __thiscall CMerchantWnd::RequestSellItem(int)
typedef VOID    (__cdecl *fEQWriteMapfile)(PCHAR, int);//void __thiscall ZZZ::WriteMapfile(PCHAR zonename, int Layer);
typedef BOOL    (__cdecl *fEQProcGameEvts)(VOID);
typedef VOID    (__cdecl *fEQSendMessage)(PVOID,DWORD,PVOID,DWORD,BOOL);
typedef FLOAT    (__cdecl *fEQGetMelee)(class EQPlayer *,class EQPlayer *);
typedef BOOL    (__cdecl *fEQExecuteCmd)(DWORD,BOOL,PVOID);
typedef VOID    (__cdecl *fMQExecuteCmd)(PCHAR Name,BOOL Down);
typedef DWORD (__cdecl *fMQParm)(PCHAR, PCHAR, PSPAWNINFO);

/* PLUGINS */
typedef DWORD   (__cdecl *fMQWriteChatColor)(PCHAR Line, DWORD Color, DWORD Filter);
typedef VOID  (__cdecl *fMQPulse)(VOID);
typedef DWORD  (__cdecl *fMQIncomingChat)(PCHAR Line, DWORD Color);
typedef VOID  (__cdecl *fMQInitializePlugin)(VOID);
typedef VOID  (__cdecl *fMQShutdownPlugin)(VOID);
typedef VOID  (__cdecl *fMQZoned)(VOID);
typedef VOID  (__cdecl *fMQReloadUI)(VOID);
typedef VOID  (__cdecl *fMQCleanUI)(VOID);
typedef VOID  (__cdecl *fMQDrawHUD)(VOID);
typedef VOID  (__cdecl *fMQSetGameState)(DWORD GameState);
typedef VOID  (__cdecl *fMQSpawn)(PSPAWNINFO);
typedef VOID  (__cdecl *fMQGroundItem)(PGROUNDITEM);
typedef VOID  (__cdecl *fMQDamaged)(PSPAWNINFO,PSPAWNINFO,DWORD);
};
using namespace MQ2Prototypes;