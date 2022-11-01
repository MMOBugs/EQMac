// MQ2EQBugFix.cpp : Defines the entry point for the DLL application.
//

// PLUGIN_API is only to be used for callbacks.  All existing callbacks at this time
// are shown below. Remove the ones your plugin does not use.  Always use Initialize
// and Shutdown for setup and cleanup, do NOT do it in DllMain.



#include "../MQ2Plugin.h"


PreSetup("MQ2EQBugFix");
BOOL cleandone = 0;
typedef void (__cdecl *t3dReleaseDevice)(void);
HMODULE hdx8 = 0;
DWORD AltTabHandleAddr = 0;
DWORD anaddress = 0;
typedef void (__cdecl *t3dUpdateDisplay)(void);
DWORD AltTabHandler_Trampoline(DWORD, DWORD, DWORD, DWORD, DWORD);
DWORD AltTabHandler_Hook(DWORD A, DWORD B, DWORD C, DWORD D, DWORD E)
{
	if(anaddress) {
		DWORD ptr = *(DWORD *)anaddress;
		BOOL done = 0;
		while(ptr==0) {
			Beep(1000,50);
			Sleep(1000);//something is going on...
			//DWORD anaddre = (DWORD)hdx8 + 0x6BCA0;
			//t3dUpdateDisplay func = (t3dUpdateDisplay)anaddre;
			//if(func) {
			//	func();
			//}
			//
			if(pDisplay && done==0) {
				done = 1;
				pDisplay->CleanUpDDraw();
				pDisplay->InitDDraw();

			}
			ptr = *(DWORD *)anaddress;
		}
		if(done==1) {
			Beep(800,50);
			Sleep(1000);
			//A=ptr;
			return 0;
		}
		if(ptr) {
			return AltTabHandler_Trampoline(A,B,C,D,E);
		}
	}
	return 0;
}
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
	szOut[j] = '\0';
}
//CHAR szOutBuff[30000] = {0};

CHAR szrecvBuffer[30000] = {0};
int __cdecl msg_send_corpse_equip(class EQ_Equipment *);
FUNCTION_AT_ADDRESS(int __cdecl msg_send_corpse_equip(class EQ_Equipment *),0x4DF03D);
class Eqmachooks {
public:
	int is_3dON_Trampoline();   
    int is_3dON_Detour()
    {
        if(!this)
        {
			Beep(500,100);
            DebugSpew("MQ2EQBugFix::Crash avoided!");
            return 0;
        }
        return is_3dON_Trampoline();
    }
	void CDisplay__RealRender_World_Trampoline(void);
	void CDisplay__RealRender_World_Hook(void)
	{
		if(anaddress) {
			DWORD ptr = *(DWORD *)anaddress;
			/*while(ptr==0) {
				Beep(1000,50);
				Sleep(1000);//something is going on...
				ptr = *(DWORD *)anaddress;
			}*/
			if(ptr) { 
				cleandone = 0;
				return CDisplay__RealRender_World_Trampoline();
			} else {
				if(cleandone==0) {
					//*(DWORD *)0x7F9574 = 0;//fake a disconnect
					//DWORD thedisp = (DWORD)pDisplay;
					//DWORD don = thedisp+0x2CA4;
					//*(DWORD *)don = 0;
					//6EBE0 t3dSwitchD3DVideoMode
					DWORD callthis = (DWORD)hdx8+0x6EBE0;
					cleandone = 1;
					Beep(1000,50);
					t3dReleaseDevice dosomething = (t3dReleaseDevice)callthis;
					dosomething();
					//t3dReleaseDevice ReleaseDevice = (t3dReleaseDevice)*(DWORD*)0x7F9AA4;
					//ReleaseDevice();
					//t3dReleaseDevice ReinitializeDevice = (t3dReleaseDevice)*(DWORD*)0x7F9AA0;
					//ReinitializeDevice();
					//*(DWORD*)__ScreenMode = 0;
					//pDisplay->ChangeVideoMode();
					//pDisplay->DDrawUpdateDisplay();
					//pDisplay->ChangeVideoMode();
					//pDisplay->StopWorldDisplay();
					//pEverQuest->Camp();
					//pDisplay->CleanUpDDraw();
					//pDisplay->InitDDraw();
				}
				//pDisplay->ResetRenderWindow();
				//pDisplay->ChangeVideoMode();
				//pDisplay->DDrawUpdateDisplay();
			}
		} else {
			Beep(800,70);
			if(!hdx8) {
				hdx8 = GetModuleHandle("EQGfx_Dx8.dll");
			}
			if(hdx8) {
				anaddress = (DWORD)hdx8 + 0x6378F0;
			}
		}
	}
	void SendMessage_Tramp(DWORD * *,unsigned __int32,void *,unsigned __int32,bool);
	void SendMessage_Detour(DWORD * *A,unsigned __int32 B,void *C,unsigned __int32 D,bool E)
	{
		CHAR szOut[2048] = {0};
		datatostr(szOut,(PBYTE)C,D,1024);
		DebugSpewAlways("SEND (opcode=%x) buf(len=%d) = %s",B,D,szOut);
		return SendMessage_Tramp(A,B,C,D,E);
	}
	unsigned __int32 net_connect_Tramp(struct connection_t * *,char *,short);
	unsigned __int32 net_connect_Detour(struct connection_t * *A,char *B,short C)
	{

		return net_connect_Tramp(A,B,C);
	}
	DWORD rdp_receive_Tramp(DWORD, DWORD);
	DWORD rdp_receive_Detour(DWORD Buffer, DWORD Bufflen)//seems to be 10000 always?
	{
		//CHAR szOut[MAX_STRING] = {0};
		//datatostr(szOut,(PBYTE)Buffer,100,MAX_STRING);
		//DebugSpewAlways("RECV pre decode buf %s",szOut);
		//datatostr(szrecvBuffer,(PBYTE)Buffer,0x64,0x256);
		//SafeSpewFile("RECV post decode buf = %s",szrecvBuffer);
		DWORD retbuf = rdp_receive_Tramp(Buffer,Bufflen);
		//if(ret) {
			//DWORD eaxptr = 0;
			//__asm {mov eaxptr, eax};
			//recv(
			if(retbuf) {
				WORD plen = *(WORD*)(retbuf+0x24);
				if(plen) {
					if(plen>500)
						plen=500;
					memcpy(szrecvBuffer,&retbuf,plen);
				}
				//if(plen)
				//	datatostr(szrecvBuffer,(PBYTE)retbuf,plen-1,0x256);
				//SafeSpewFile("RECV post decode buf = %s",szrecvBuffer);
				//SafeSpewFile("RECV post eax = %x plen = %d",eaxptr,plen);
			}
		//}
		return retbuf;
	}
	PBYTE wait_message_Tramp(void);
	PBYTE wait_message_Detour()//seems to be 10000 always?
	{
		//CHAR szOut[MAX_STRING] = {0};
		//datatostr(szOut,(PBYTE)Buffer,100,MAX_STRING);
		//DebugSpewAlways("RECV pre decode buf %s",szOut);
		//datatostr(szrecvBuffer,(PBYTE)Buffer,0x64,0x256);
		//SafeSpewFile("RECV post decode buf = %s",szrecvBuffer);
		PBYTE retbuf = wait_message_Tramp();
		//if(ret) {
			//DWORD eaxptr = 0;
			//__asm {mov eaxptr, eax};
			//recv(
			if(retbuf) {
				WORD plen = *(WORD*)(retbuf+0x24);
				if(plen) {
					if(plen>500)
						plen=500;
					//datatostr(szrecvBuffer,(PBYTE)retbuf,plen+0x24,0x512);
					//SafeSpewFile("RECV decode buf = %s",szrecvBuffer);
					//memcpy(szrecvBuffer,retbuf,plen);
				}
				//if(plen)
				//	datatostr(szrecvBuffer,(PBYTE)retbuf,plen-1,0x256);
				//SafeSpewFile("RECV post decode buf = %s",szrecvBuffer);
				//SafeSpewFile("RECV post eax = %x plen = %d",eaxptr,plen);
			}
		//}
		return retbuf;
	}
	unsigned char CEverQuest__HandleWorldMessage_Trampoline(struct connection_t *,unsigned __int32,char *,unsigned __int32);
	unsigned char CEverQuest__HandleWorldMessage_Detour(struct connection_t *con,unsigned __int32 Opcode,char *Buffer,unsigned __int32 len)
	{
		if(Opcode==0x4052) {//OP_ItemOnCorpse
			return msg_send_corpse_equip((EQ_Equipment*)Buffer);
		}
#ifdef _DEBUG
		switch(Opcode)
		{
			case 0x40b2:
			case 0x4157:
			case 0x409f:
			case 0x4029:
			{
				break;
			}
			case 0x4058://npc hits a pc/other npc
			{
				////spawn 0a5e gets hit by a jackal with id 004a for 3 points of damage
				//RECV: (4058) len=24 5E 0A 4A 00 1C 00 FF FF 03 00 00 00 CD CC CC 3D D7 B3 DA 43 00 00 00 00
				struct _AttackPacket
				{
					WORD DefenderID;
					WORD OffenderID;
					WORD Unknown0x04;
					WORD Unknown0x06;
					DWORD Damage;
					FLOAT Range;//0.10
					FLOAT Heading;//437.40
					DWORD Unknown0x14;
				} AttackPacket;
				memcpy(&AttackPacket,Buffer,sizeof(AttackPacket));
				PSPAWNINFO pOffender = (PSPAWNINFO)GetSpawnByID(AttackPacket.OffenderID);
				PSPAWNINFO pDefender = (PSPAWNINFO)GetSpawnByID(AttackPacket.DefenderID);
				if(pOffender && pDefender)
					DebugTry(Benchmark(bmPluginsDamaged,PluginsDamaged(pOffender,pDefender,AttackPacket.Damage)));
			}
			case 0x404a:
			default:
			{
				//datatostr(szrecvBuffer,(PBYTE)Buffer,len,30000);
				//SafeSpewFile("RECV: (%04x) len=%d %s",Opcode,len,szrecvBuffer);
			}
		}
		#endif
		return CEverQuest__HandleWorldMessage_Trampoline(con,Opcode,Buffer,len);
	}
};


DETOUR_TRAMPOLINE_EMPTY(int Eqmachooks::is_3dON_Trampoline());
DETOUR_TRAMPOLINE_EMPTY(DWORD AltTabHandler_Trampoline(DWORD, DWORD, DWORD, DWORD, DWORD));
DETOUR_TRAMPOLINE_EMPTY(void Eqmachooks::CDisplay__RealRender_World_Trampoline(void));
DETOUR_TRAMPOLINE_EMPTY(unsigned __int32 Eqmachooks::net_connect_Tramp(struct connection_t * *,char *,short)); 
DETOUR_TRAMPOLINE_EMPTY(void Eqmachooks::SendMessage_Tramp(DWORD * *,unsigned __int32,void *,unsigned __int32,bool)); 
DETOUR_TRAMPOLINE_EMPTY(DWORD Eqmachooks::rdp_receive_Tramp(DWORD,DWORD)); 
DETOUR_TRAMPOLINE_EMPTY(PBYTE Eqmachooks::wait_message_Tramp(void)); 
DETOUR_TRAMPOLINE_EMPTY(DWORD WINAPI GetModuleFileNameA_tramp(HMODULE,LPTSTR,DWORD)); 
DETOUR_TRAMPOLINE_EMPTY(unsigned char Eqmachooks::CEverQuest__HandleWorldMessage_Trampoline(struct connection_t *,unsigned __int32,char *,unsigned __int32)); 

DWORD WINAPI GetModuleFileNameA_detour(HMODULE hMod,LPTSTR outstring,DWORD nSize)
{
	DWORD allocsize = nSize;
	DWORD ret = GetModuleFileNameA_tramp(hMod,outstring,nSize);
	if(bExeChecksumrequested) {
		if(strstr(outstring,"eqgame.exe")) {
			bExeChecksumrequested=0;
			PCHAR szProcessName = 0;
			szProcessName = strrchr(outstring,'\\');
			szProcessName[0] = '\0';
			sprintf_s(outstring,allocsize,"%s\\eqmac.exe",outstring);
		}
	}
	return ret;
}


FARPROC gmfadress = 0;
// Called once, when the plugin is to initialize
PLUGIN_API VOID InitializePlugin(VOID)
{
	//i dont actually do anything with this yet, its a work in progress to stop eq from crashing on
	//alt tab
	DebugSpewAlways("Initializing MQ2EQBugFix");
	HMODULE heqgamedllMod = GetModuleHandle("eqgame.dll");
	if(!heqgamedllMod) {
		HMODULE hkernel32Mod = GetModuleHandle("kernel32.dll");
		gmfadress = GetProcAddress(hkernel32Mod,"GetModuleFileNameA");
		EzDetour(gmfadress,GetModuleFileNameA_detour,GetModuleFileNameA_tramp);
		EzDetour(CEverQuest__HandleWorldMessage,&Eqmachooks::CEverQuest__HandleWorldMessage_Detour,&Eqmachooks::CEverQuest__HandleWorldMessage_Trampoline);
	}
	//EzDetour(CDisplay__is_3dON, &Eqmachooks::is_3dON_Detour, &Eqmachooks::is_3dON_Trampoline);
	//EzDetour(0x54CFB3,&Eqmachooks::net_connect_Detour,&Eqmachooks::net_connect_Tramp);
	//EzDetour(__SendMessage,&Eqmachooks::SendMessage_Detour,&Eqmachooks::SendMessage_Tramp);
	//EzDetour(0x55DEF0,&Eqmachooks::rdp_receive_Detour,&Eqmachooks::rdp_receive_Tramp);
	//EzDetour(0x54CEA7,&Eqmachooks::wait_message_Detour,&Eqmachooks::wait_message_Tramp);
	//54CEA7 ; int __cdecl wait_message()
}

// Called once, when the plugin is to shutdown
PLUGIN_API VOID ShutdownPlugin(VOID)
{
	DebugSpewAlways("Shutting down MQ2EQBugFix");
	if(gmfadress) {
		RemoveDetour((DWORD)gmfadress);
		RemoveDetour((DWORD)CEverQuest__HandleWorldMessage);
	}
	//RemoveDetour(CDisplay__is_3dON);
	//RemoveDetour(0x54CFB3);
	//RemoveDetour(__SendMessage);
	//rdpRemoveDetour(0x55DEF0);
	//RemoveDetour(0x54CEA7);
}

