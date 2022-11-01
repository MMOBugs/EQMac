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

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x510
#define DIRECTINPUT_VERSION 0x800

#if !defined(CINTERFACE)
#error /DCINTERFACE
#endif

#define DBG_SPEW

#include "MQ2Main.h"


typedef struct _OurDetours {
    unsigned int addr;
    unsigned int count;
    unsigned char array[50];
	PBYTE pfDetour;
	PBYTE pfTrampoline;

	struct _OurDetours *pNext;
	struct _OurDetours *pLast;
} OurDetours;

OurDetours *ourdetours=0;
CRITICAL_SECTION gDetourCS;

OurDetours *FindDetour(DWORD address)
{
	OurDetours *pDetour=ourdetours;
	while(pDetour)
	{
		if (pDetour->addr==address)
			return pDetour;
		pDetour=pDetour->pNext;
	}
	return 0;
}

BOOL AddDetour(DWORD address, PBYTE pfDetour, PBYTE pfTrampoline, DWORD Count)
{
	CAutoLock Lock(&gDetourCS);
	BOOL Ret=TRUE;
	DebugSpew("AddDetour(0x%X,0x%X,0x%X)",address,pfDetour,pfTrampoline);
	if (FindDetour(address))
	{

		DebugSpew("Already detoured.");
		return FALSE;
	}
	OurDetours *detour = new OurDetours;
	detour->addr=address;
	detour->count=Count;
	memcpy(detour->array,(char *)address, Count);
	detour->pNext=ourdetours;
	if (ourdetours)
		ourdetours->pLast=detour;
	detour->pLast=0;
    if (pfDetour && !DetourFunctionWithEmptyTrampoline(pfTrampoline, 
         (PBYTE)address, 
         pfDetour))
	{
		detour->pfDetour=0;
		detour->pfTrampoline=0;
		Ret=FALSE;
		DebugSpew("Detour failed.");
	}
	else
	{
		detour->pfDetour=pfDetour;
		detour->pfTrampoline=pfTrampoline;
		DebugSpew("Detour success.");
	}
	ourdetours=detour;
	return Ret;
}

void AddDetourf(DWORD address, ...)
{
	va_list marker;
	int i=0;
	va_start(marker, address);
	DWORD Parameters[3];
	DWORD nParameters=0;
	while (i!=-1) 
	{
		if (nParameters<3)
		{
			Parameters[nParameters]=i;
			nParameters++;
		}
		i = va_arg(marker,int);
	}
	va_end(marker);
	if (nParameters==3)
	{
		AddDetour(address,(PBYTE)Parameters[1],(PBYTE)Parameters[2],20);
	}
	else
	{
		DebugSpew("Illegal AddDetourf call");
	}
}

void RemoveDetour(DWORD address)
{
	CAutoLock Lock(&gDetourCS);
	DebugSpew("RemoveDetour(%X)",address);
	OurDetours *detour = ourdetours;
	while (detour)
	{
		if (detour->addr==address)
		{
			if (detour->pfDetour)
			{
		      DetourRemove(detour->pfTrampoline, 
				detour->pfDetour); 		
			}
			  if (detour->pLast)
				detour->pLast->pNext=detour->pNext;
			  else
				  ourdetours=detour->pNext;

			  if (detour->pNext)
				  detour->pNext->pLast=detour->pLast;
			delete detour;
			  DebugSpew("Detour removed.");
			  return;
		}
		detour=detour->pNext;
	}
	DebugSpew("Detour not found in RemoveDetour()");
}

void RemoveOurDetours()
{
	CAutoLock Lock(&gDetourCS);
	DebugSpew("RemoveOurDetours()");
	if (!ourdetours)
		return;
	while (ourdetours)
	{
		if (ourdetours->pfDetour)
		{
			DebugSpew("RemoveOurDetours() -- Removing %X",ourdetours->addr);
			DetourRemove(ourdetours->pfTrampoline,ourdetours->pfDetour); 				
		}

		OurDetours *pNext=ourdetours->pNext;
		delete ourdetours;
		ourdetours=pNext;
	}
}


// this is the memory checker key struct
struct mckey {
    union {
        int x;
        unsigned char a[4];
        char sa[4];
    };
};

// pointer to encryption pad for memory checker
unsigned int *extern_array = NULL;
unsigned int *extern_array1 = NULL;
unsigned int *extern_array2 = NULL;
unsigned int *extern_array3 = NULL;

DETOUR_TRAMPOLINE_EMPTY(VOID memcheck5_tramp(PVOID,DWORD,PCHAR,DWORD,BOOL)); 
VOID datatostr(PCHAR szOut,PBYTE Data,DWORD Length, DWORD Max_Length)
{
	DWORD i=0,j=0;
    for (;i<Length&&j<Max_Length-1;i++,j+=2) {
		if (*(Data+i)/0x10<0xA)
			szOut[j]=(*(Data+i)/0x10)+0x30;
		else 
			szOut[j]=(*(Data+i)/0x10)+55;
		if ((*(Data+i)&(0x0F))<0xA)
			szOut[j+1]=(*(Data+i)&(0x0F))+0x30;
		else
			szOut[j+1]=(*(Data+i)&(0x0F))+55;
		szOut[j+2]=' '; j++;
	}
	szOut[j++]=' ';
	for (i=0;i<Length&&j<Max_Length-1;i++,j++) {
		if (*(Data+i)<32) szOut[j]='.';
		else szOut[j]=*(Data+i);
	}
	szOut[j]='\0';
}
CHAR szOutBuff[30000] = {0};
VOID memcheck5(PVOID A,DWORD B,PCHAR C,DWORD D,BOOL E)
{
#ifdef _DEBUG
	//if (B==0x40d1) {
		//datatostr(szOutBuff,(PBYTE)C,D,30000);
		//WriteChatf("Got OP_Trade %s len is %d",szOutBuff,D);
	//}
	//SafeSpewFile("SEND (opcode=%x) buf(len=%d) = %s",B,D,szOutBuff);
#endif
	if (B==0x00F4)
	{
		int Pos = 4 + strlen(&C[4])+ 1;
		int End = Pos + (int)(71.0*rand()/(RAND_MAX+1.0));
		for (Pos ; Pos < End ; Pos++)
			C[Pos]=0;

		int t;
		for (Pos ; Pos < 1024 ; Pos++)
		{
			t = (int)(397.0*rand()/(RAND_MAX+1.0));
			C[Pos]=(t <= 255) ? (char)t : 0;
		}
	} else if(B==0x4135) {
		bExeChecksumrequested = 1;
	} else if(B==EQ_BEGIN_ZONE) {
		//PluginsBeginZone(); 
	} else if (B==EQ_END_ZONE) {
		PluginsZoned();
		PluginsSetGameState(gGameState);//do this to get gzoned reset...
	}
	memcheck5_tramp(A,B,C,D,E);
}

// ***************************************************************************
// Function:    HookMemChecker
// Description: Hook MemChecker
// ***************************************************************************
int (__cdecl *memcheck0_tramp)(unsigned char *buffer, int count, struct mckey key);
int (__cdecl *memcheck4_tramp)(unsigned char *buffer, int count, struct mckey key);
int __cdecl memcheck0(unsigned char *buffer, int count, struct mckey key);
//int __cdecl memcheck4(unsigned char *buffer, int count, struct mckey key);

VOID HookMemChecker(BOOL Patch)
{
    // hit the debugger if we don't hook this
    // take no chances
    if ((!EQADDR_MEMCHECK0)) {
        _asm int 3
    }
    DebugSpew("HookMemChecker - %satching",(Patch)?"P":"Unp");
    if (Patch) {

		AddDetour((DWORD)EQADDR_MEMCHECK0);
        (*(PBYTE*)&memcheck0_tramp) = DetourFunction( (PBYTE) EQADDR_MEMCHECK0,(PBYTE) memcheck0);
		//AddDetour((DWORD)EQADDR_MEMCHECK4);
        //(*(PBYTE*)&memcheck4_tramp) = DetourFunction( (PBYTE) EQADDR_MEMCHECK4,(PBYTE) memcheck4);
		EzDetour(send_message,memcheck5,memcheck5_tramp);
    } else {
        DetourRemove((PBYTE) memcheck0_tramp,(PBYTE) memcheck0);
        memcheck0_tramp = NULL;
		RemoveDetour(EQADDR_MEMCHECK0);
        //DetourRemove((PBYTE) memcheck4_tramp,(PBYTE) memcheck4);
        //memcheck4_tramp = NULL;
		//RemoveDetour(EQADDR_MEMCHECK4);
		RemoveDetour((DWORD)send_message);
    }
}
VOID HookInlineChecks(BOOL Patch)
{
    return;
    DWORD oldperm = 0, tmp = 0;
	BYTE NewData = 0;
	LPVOID address = (LPVOID)(DWORD)0x42C52F;
    if (Patch)
    {
        NewData = 0xEB;
            AddDetour((DWORD)address, NULL, NULL, 1);
            VirtualProtectEx(GetCurrentProcess(), address, 1, PAGE_EXECUTE_READWRITE, &oldperm);
            WriteProcessMemory(GetCurrentProcess(), address, &NewData, 1, NULL);
            VirtualProtectEx(GetCurrentProcess(), address, 1, oldperm, &tmp);
	}
    else
    {
        NewData = 0x7E;
        VirtualProtectEx(GetCurrentProcess(), address, 1, PAGE_EXECUTE_READWRITE, &oldperm);
        WriteProcessMemory(GetCurrentProcess(), address, &NewData, 1, NULL);
        VirtualProtectEx(GetCurrentProcess(), address, 1, oldperm, &tmp);
        RemoveDetour((DWORD)address);
    }
}
// ***************************************************************************
// ***************************************************************************
// ***************************************************************************
// ***************************************************************************
// ***************************************************************************
// ***************************************************************************
// ***************************************************************************
// ***************************************************************************
// ***************************************************************************
// ***************************************************************************
// ***************************************************************************
// ***************************************************************************
// ***************************************************************************
// ***************************************************************************


//  004F7D24: 55                 push        ebp
//  004F7D25: 8B EC              mov         ebp,esp
//  004F7D27: 8A 45 10           mov         al,byte ptr [ebp+10h]
//  004F7D2A: 56                 push        esi


int __cdecl memcheck0(unsigned char *buffer, int count, struct mckey key)
{
    unsigned int x, i;
    unsigned int ecx;
    unsigned int eax = ~key.a[0] & 0xff;

    if (!extern_array) {
        if (!EQADDR_ENCRYPTPAD) {
            //_asm int 3
        } else {
          extern_array = (unsigned int *)EQADDR_ENCRYPTPAD;
        }
    }

//  004F7D2B: F6 D0              not         al
//  004F7D2D: 0F B6 C0           movzx       eax,al
    unsigned int edx = key.a[1] & 0xff;
//  004F7D30: 0F B6 55 11        movzx       edx,byte ptr [ebp+11h]
//  004F7D34: 8B 04 85 6C 7B 5C  mov         eax,dword ptr [eax*4+005C7B6Ch]
//            00

    eax = extern_array[eax];

//  004F7D3B: BE FF FF FF 00     mov         esi,0FFFFFFh
//  004F7D40: 33 C6              xor         eax,esi
    eax ^= 0xffffff;

//  004F7D42: 57                 push        edi
//  004F7D43: 8B C8              mov         ecx,eax
//  004F7D45: BF FF 00 00 00     mov         edi,0FFh

//  004F7D4A: 23 CF              and         ecx,edi
    ecx = eax & 0xff;
//  004F7D4C: 33 CA              xor         ecx,edx
    ecx ^= edx;
//  004F7D4E: 0F B6 55 12        movzx       edx,byte ptr [ebp+12h]
    edx = key.a[2] & 0xff;

//  004F7D52: 8B 0C 8D 6C 7B 5C  mov         ecx,dword ptr [ecx*4+005C7B6Ch]
//            00
    ecx = extern_array[ecx];

//  004F7D59: C1 F8 08           sar         eax,8
//  004F7D5C: 23 C6              and         eax,esi
    eax = ((int)eax>>8) & 0xffffff;

//  004F7D5E: 33 C8              xor         ecx,eax
    ecx ^= eax;

//  004F7D60: 8B C1              mov         eax,ecx
//  004F7D62: 23 C7              and         eax,edi
//  004F7D64: 33 C2              xor         eax,edx
    eax = (ecx & 0xff) ^ edx;

//  004F7D66: C1 F9 08           sar         ecx,8
    ecx = (int)ecx >> 8;

//  004F7D69: 8B 14 85 6C 7B 5C  mov         edx,dword ptr [eax*4+005C7B6Ch]
//            00
    edx = extern_array[eax];

//  004F7D70: 23 CE              and         ecx,esi
//  004F7D72: 33 D1              xor         edx,ecx
    edx ^= ecx & 0xffffff;

//  004F7D74: 0F B6 4D 13        movzx       ecx,byte ptr [ebp+13h]
    ecx = key.a[3] & 0xff;

//  004F7D78: 8B C2              mov         eax,edx
//  004F7D7A: 23 C7              and         eax,edi
//  004F7D7C: 33 C1              xor         eax,ecx
//  004F7D7E: 8B 4D 08           mov         ecx,dword ptr [ebp+8]
//  004F7D81: C1 FA 08           sar         edx,8
//  004F7D84: 8B 04 85 6C 7B 5C  mov         eax,dword ptr [eax*4+005C7B6Ch]
//            00

    eax = extern_array[(edx & 0xff) ^ ecx];

//  004F7D8B: 23 D6              and         edx,esi
//  004F7D8D: 33 C2              xor         eax,edx
    eax ^= ((int)edx>>8) & 0xffffff;

//  004F7D8F: 8B 55 0C           mov         edx,dword ptr [ebp+0Ch]
//  004F7D92: 03 D1              add         edx,ecx
//  004F7D94: 89 4D 10           mov         dword ptr [ebp+10h],ecx
//  004F7D97: 3B CA              cmp         ecx,edx
//  004F7D99: 73 24              jae         004F7DBF
    if (count == 0) return ~eax;

//  004F7D9B: 53                 push        ebx
//  004F7D9C: 8B 5D 10           mov         ebx,dword ptr [ebp+10h]
//  004F7D9F: 8B C8              mov         ecx,eax
//  004F7DA1: 23 CF              and         ecx,edi
//  004F7DA3: 0F B6 1B           movzx       ebx,byte ptr [ebx]
//  004F7DA6: 33 CB              xor         ecx,ebx
//  004F7DA8: C1 F8 08           sar         eax,8
//  004F7DAB: 8B 0C 8D 6C 7B 5C  mov         ecx,dword ptr [ecx*4+005C7B6Ch]
//            00
//  004F7DB2: 23 C6              and         eax,esi
//  004F7DB4: 33 C1              xor         eax,ecx
//  004F7DB6: FF 45 10           inc         dword ptr [ebp+10h]
//  004F7DB9: 39 55 10           cmp         dword ptr [ebp+10h],edx
//  004F7DBC: 72 DE              jb          004F7D9C

//  004F7DBE: 5B                 pop         ebx
//  004F7DBF: 5F                 pop         edi
//  004F7DC0: 5E                 pop         esi
//  004F7DC1: F7 D0              not         eax
//  004F7DC3: 5D                 pop         ebp
//  004F7DC4: C3                 ret

    for (i=0;i<(unsigned int)count;i++) {
        unsigned char tmp;
		OurDetours *detour = ourdetours;
        unsigned int b=(int) &buffer[i];
		while(detour)
		{
			if (detour->count && (b >= detour->addr) &&
                 (b < detour->addr+detour->count) ) {
                 tmp = detour->array[b - detour->addr];
                 break;
            }
			detour=detour->pNext;
		}
        if (!detour) tmp = buffer[i];
        x = (int)tmp ^ (eax & 0xff);
        eax = ((int)eax >> 8) & 0xffffff;
        x = extern_array[x];
        eax ^= x;
    }
    return ~eax;
}


VOID __cdecl CrashDetected_Trampoline(DWORD,DWORD,DWORD,DWORD,DWORD); 
VOID __cdecl CrashDetected_Detour(DWORD a,DWORD b,DWORD c,DWORD d,DWORD e) 
{ 
	MessageBox(0,"MacroQuest2 is blocking the 'send Sony crash info?' box for your safety and privacy.  Crashes are usually bugs either in EQ or in MacroQuest2.  It is generally not something that you yourself did, unless you have custom MQ2 plugins loaded.  If you want to submit a bug report to the MacroQuest2 message boards, please follow the instructions on how to submit a crash bug report at the top of the MQ2::Bug Reports forum.","EverQuest Crash Detected",MB_OK);
} 
DETOUR_TRAMPOLINE_EMPTY(VOID CrashDetected_Trampoline(DWORD,DWORD,DWORD,DWORD,DWORD)); 

void InitializeMQ2Detours()
{
	InitializeCriticalSection(&gDetourCS);
	HookMemChecker(TRUE);
	HookInlineChecks(TRUE);
	EzDetour(CrashDetected,CrashDetected_Detour,CrashDetected_Trampoline);
}

void ShutdownMQ2Detours()
{
	HookInlineChecks(FALSE);
	HookMemChecker(FALSE);
	RemoveDetour(CrashDetected);
	RemoveOurDetours();
	DeleteCriticalSection(&gDetourCS);
}
