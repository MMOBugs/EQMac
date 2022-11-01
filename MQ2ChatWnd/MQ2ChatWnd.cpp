// MQ2ChatWnd.cpp : Defines the entry point for the DLL application.
//

// Single-window MQ Chat

//#define DEBUG_TRY 1
#define MAX_CHAT_SIZE 700
#define LINES_PER_FRAME 3
#include "../MQ2Plugin.h"
#include <vector>
#include <map>
PreSetup("MQ2ChatWnd");

struct ChatBuffer
{
	CHAR Text[MAX_STRING];
	ChatBuffer *pNext;
	ChatBuffer *pPrev;
};

ChatBuffer* pPendingChat=0;
ChatBuffer* pPendingChatTail=0;

const unsigned int CMD_HIST_MAX=50;

DWORD bmStripFirstStmlLines=0;
DWORD PendingChatLines=0;



void SaveChatToINI(PCSIDLWND pWindow);
void CreateChatWindow();
class CMQChatWnd;
CMQChatWnd *MQChatWnd=0;

VOID DoMQ2ChatBind(PCHAR Name,BOOL Down);

class CMQChatWnd : public CCustomWnd
{
private:
    vector<string> sCmdHistory;
    int iCurrentCmd;
public:
	CMQChatWnd():CCustomWnd("ChatWindow")
	{
		DebugSpew("CMQChatWnd()");
		SetWndNotification(CMQChatWnd);
		InputBox=(CTextEntryWnd*)GetChildItem("CWChatInput");
		InputBox->WindowStyle|=0x800C0;
		BitOff(WindowStyle,CWS_CLOSE);
		InputBox->UnknownCW|=0xFFFFFFFF;
		InputBox->SetMaxChars(512);
		OutputBox=(CStmlWnd*)GetChildItem("CWChatOutput");
		OutBoxLines=0;
		*(DWORD*)&(((PCHAR)OutputBox)[EQ_CHAT_HISTORY_OFFSET])=0x190;
	}

	~CMQChatWnd()
	{
	}

	int WndNotification(CXWnd *pWnd, unsigned int Message, void *data)
	{	
		if (pWnd==(CXWnd*)InputBox)
		{
			switch (Message)
			{
				case XWM_HITENTER:
				{
					char szBuffer[2048];
					GetCXStr((PCXSTR)InputBox->InputText,szBuffer,2047);
					if (szBuffer[0])
					{
						if (!sCmdHistory.size() || sCmdHistory.front().compare(szBuffer))
						{
							if (sCmdHistory.size()>CMD_HIST_MAX)
							{
								sCmdHistory.pop_back();
							}
							sCmdHistory.insert(sCmdHistory.begin(),string(szBuffer));
						}
						iCurrentCmd=-1;
						//OutputBox->AppendSTML(&Whatever,szBuffer);
						SetCXStr(&InputBox->InputText,"");
						if (szBuffer[0]=='/')
						{
							DoCommand(((PCHARINFO)pCharData)->pSpawn,szBuffer); 
						}
						else
						{
							Echo(((PCHARINFO)pCharData)->pSpawn,szBuffer); 
						}
					}
					((CXWnd*)InputBox)->ClrFocus();
					break;
				}
				case XWM_HISTORY:
				{
					if (data)
					{
						int* pInt=(int*)data;
						int iKeyPress=pInt[1];
						if (iKeyPress==0xc8) // KeyUp
						{
							if (sCmdHistory.size()>0)
							{
								iCurrentCmd++;
								if (iCurrentCmd<((int)sCmdHistory.size()) && iCurrentCmd>=0)
								{
									string s=(string)sCmdHistory.at(iCurrentCmd);
									((CXWnd*)InputBox)->SetWindowTextA(CXStr(s.c_str()));
								}
								else
								{
									iCurrentCmd=((int)sCmdHistory.size())-1;
								}
							}
						}
						else if (iKeyPress==0xd0) // KeyDown
						{
							if (sCmdHistory.size()>0)
							{
								iCurrentCmd--;
								if (iCurrentCmd>=0 && sCmdHistory.size()>0)
								{
									string s=(string)sCmdHistory.at(iCurrentCmd);
									((CXWnd*)InputBox)->SetWindowTextA(CXStr(s.c_str()));
								}
								else if (iCurrentCmd<0)
								{
									iCurrentCmd=-1;
									SetCXStr(&InputBox->InputText,"");
								}
							}
						}
					}
					break;
				}
				default:
				{	
					DebugSpew("InputBox message %Xh, value: %Xh",Message,data);
					break;
				}
			}
		}
//		else if (pWnd==(CXWnd*)OutputBox)
//		{
//			DebugSpew("OutputBox message %Xh, value: %Xh",Message,unknown);
//		}
		else if (pWnd==0)
		{
			if (Message==XWM_CLOSE)
			{
				dShow=1;
				return 1;
				//SaveChatToINI((PCSIDLWND)MQChatWnd);
				//MQChatWnd=0;
				// automatically gets deleted, dont try to delete it here..

//				DoCommand((PSPAWNINFO)pCharSpawn,"/plugin mq2chatwnd unload");
			}
//			DebugSpew("CMQChatWnd message %Xh, value: %Xh",Message,unknown);
		}
		else
		{
//			DebugSpew("Wnd: 0x%X, Msg: 0x%X, value: %Xh",pWnd,Message,unknown);
		}
		return CSidlScreenWnd::WndNotification(pWnd,Message,data);
	};

	CTextEntryWnd *InputBox;
	CStmlWnd *OutputBox;
	DWORD OutBoxLines;
};


PLUGIN_API VOID OnCleanUI(VOID);
PLUGIN_API VOID SetGameState(DWORD GameState);

CHAR szChatINISection[MAX_STRING] = {0};
void LoadChatFromINI(PCSIDLWND pWindow)
{
	CHAR Buffer[MAX_STRING] = {0};
    sprintf(szChatINISection,"%s.%s",EQADDR_SERVERNAME,((PCHARINFO)pCharData)->Name);
	pWindow->Location.top		= GetPrivateProfileInt(szChatINISection,"ChatTop",    10,INIFileName);
	pWindow->Location.bottom	= GetPrivateProfileInt(szChatINISection,"ChatBottom",210,INIFileName);
	pWindow->Location.left		= GetPrivateProfileInt(szChatINISection,"ChatLeft",   10,INIFileName);
	pWindow->Location.right 	= GetPrivateProfileInt(szChatINISection,"ChatRight", 410,INIFileName);
	pWindow->Locked			 	= GetPrivateProfileInt(szChatINISection,"Locked",	   0,INIFileName);
	*(DWORD*)&(((PCHAR)MQChatWnd->OutputBox)[EQ_FONT_SIZE_OFFSET])		= GetPrivateProfileInt(szChatINISection,"FontSize",	   4,INIFileName);

	pWindow->Fades			 	= GetPrivateProfileInt(szChatINISection,"Fades",	   1,INIFileName);
	pWindow->TimeMouseOver	 	= GetPrivateProfileInt(szChatINISection,"Delay",	 2000,INIFileName);
	pWindow->FadeDuration	 	= GetPrivateProfileInt(szChatINISection,"Duration",	   500,INIFileName);
	pWindow->Alpha				= GetPrivateProfileInt(szChatINISection,"Alpha",	   255,INIFileName);
	pWindow->FadeToAlpha		= GetPrivateProfileInt(szChatINISection,"FadeToAlpha",	   255,INIFileName);
	pWindow->BGType				= GetPrivateProfileInt(szChatINISection,"BGType",	   1,INIFileName);
	pWindow->BGColor.R				= GetPrivateProfileInt(szChatINISection,"BGTint.red",	   255,INIFileName);
	pWindow->BGColor.G				= GetPrivateProfileInt(szChatINISection,"BGTint.green",	   255,INIFileName);
	pWindow->BGColor.B				= GetPrivateProfileInt(szChatINISection,"BGTint.blue",	   255,INIFileName);

	GetPrivateProfileString(szChatINISection,"WindowTitle","MQ2 for eqmac",Buffer,MAX_STRING,INIFileName);
	SetCXStr(&pWindow->WindowText,Buffer);
	/**/
}

void SaveChatToINI(PCSIDLWND pWindow)
{
	CHAR szTemp[MAX_STRING] = {0};
	if (pWindow->Minimized)
	{
		WritePrivateProfileString(szChatINISection,"ChatTop",	itoa(pWindow->OldLocation.top,		szTemp,10),INIFileName);
		WritePrivateProfileString(szChatINISection,"ChatBottom",itoa(pWindow->OldLocation.bottom,	szTemp,10),INIFileName);
		WritePrivateProfileString(szChatINISection,"ChatLeft",	itoa(pWindow->OldLocation.left,		szTemp,10),INIFileName);
		WritePrivateProfileString(szChatINISection,"ChatRight",	itoa(pWindow->OldLocation.right,	szTemp,10),INIFileName);
	}
	else
	{
		WritePrivateProfileString(szChatINISection,"ChatTop",	itoa(pWindow->Location.top,		szTemp,10),INIFileName);
		WritePrivateProfileString(szChatINISection,"ChatBottom",itoa(pWindow->Location.bottom,	szTemp,10),INIFileName);
		WritePrivateProfileString(szChatINISection,"ChatLeft",	itoa(pWindow->Location.left,	szTemp,10),INIFileName);
		WritePrivateProfileString(szChatINISection,"ChatRight",	itoa(pWindow->Location.right,	szTemp,10),INIFileName);
	}
	WritePrivateProfileString(szChatINISection,"Locked",	itoa(pWindow->Locked,			szTemp,10),INIFileName);

	GetCXStr(pWindow->WindowText,szTemp);
	WritePrivateProfileString(szChatINISection,"WindowTitle",	szTemp				  ,INIFileName);

	WritePrivateProfileString(szChatINISection,"Fades",	itoa(pWindow->Fades,			szTemp,10),INIFileName);
	WritePrivateProfileString(szChatINISection,"Delay",	itoa(pWindow->MouseOver,			szTemp,10),INIFileName);
	WritePrivateProfileString(szChatINISection,"Duration",	itoa(pWindow->FadeDuration,			szTemp,10),INIFileName);
	WritePrivateProfileString(szChatINISection,"Alpha",	itoa(pWindow->Alpha,			szTemp,10),INIFileName);
	WritePrivateProfileString(szChatINISection,"FadeToAlpha",	itoa(pWindow->FadeToAlpha,			szTemp,10),INIFileName);
	WritePrivateProfileString(szChatINISection,"BGType",	itoa(pWindow->BGType,			szTemp,10),INIFileName);
	WritePrivateProfileString(szChatINISection,"BGTint.red",	itoa(pWindow->BGColor.R,			szTemp,10),INIFileName);
	WritePrivateProfileString(szChatINISection,"BGTint.green",	itoa(pWindow->BGColor.G,			szTemp,10),INIFileName);
	WritePrivateProfileString(szChatINISection,"BGTint.blue",	itoa(pWindow->BGColor.B,			szTemp,10),INIFileName);
//=0xFFFFFFFE;
	WritePrivateProfileString(szChatINISection,"FontSize",	_itoa(*(DWORD*)&(((PCHAR)MQChatWnd->OutputBox)[EQ_FONT_SIZE_OFFSET]),			szTemp,10),INIFileName);
	/**/
}


VOID Style(PSPAWNINFO pChar, PCHAR szLine)
{
	if (!szLine || szLine[0]==0)
	{
		char out[256];
		sprintf(out,"Style 0x%X",MQChatWnd->WindowStyle);
		WriteChatColor(out);
		return;
	}
	if (szLine[0]=='!')
	{
		int TurnOff;
		sscanf(&szLine[1],"%x",&TurnOff);
		BitOff(MQChatWnd->WindowStyle,TurnOff);
	}
	else
	{
		int TurnOn;
		sscanf(&szLine[0],"%x",&TurnOn);
		BitOn(MQChatWnd->WindowStyle,TurnOn);
	}
	char out[256];
	sprintf(out,"Style 0x%X",MQChatWnd->WindowStyle);
	WriteChatColor(out);
}

VOID MQChatFont(PSPAWNINFO pChar, PCHAR Line)
{
	if (MQChatWnd)
	{
		if (Line[0])
		{
			*(DWORD*)&(((PCHAR)MQChatWnd->OutputBox)[EQ_FONT_SIZE_OFFSET])=atoi(Line);
			SaveChatToINI((PCSIDLWND)MQChatWnd);
		}
		WriteChatf("MQ2ChatWnd Font Size=%d",*(DWORD*)&(((PCHAR)MQChatWnd->OutputBox)[EQ_FONT_SIZE_OFFSET]));
	}
}

PLUGIN_API VOID InitializePlugin(VOID)
{
	DebugSpewAlways("Initializing MQ2ChatWnd");
	// Add commands, macro parameters, hooks, etc.
	AddCommand("/style",Style,0,1,0);
	AddCommand("/mqfont",MQChatFont);

	AddMQ2KeyBind("MQ2CHAT",DoMQ2ChatBind);
	bmStripFirstStmlLines=AddMQ2Benchmark("StripFirstStmlLines");
}

PLUGIN_API VOID ShutdownPlugin(VOID)
{
	DebugSpewAlways("Shutting down MQ2ChatWnd");
	while(pPendingChat)
	{
		ChatBuffer *pNext=pPendingChat->pNext;
		delete pPendingChat;
		pPendingChat=pNext;
	}
	pPendingChatTail=0;
	PendingChatLines=0;

	// Remove commands, macro parameters, hooks, etc.
	RemoveCommand("/style");
	RemoveCommand("/mqfont");
	RemoveMQ2KeyBind("MQ2CHAT");
	RemoveMQ2Benchmark(bmStripFirstStmlLines);
	OnCleanUI();
}


// This is called every time WriteChatColor is called by MQ2Main or any plugin,
// IGNORING FILTERS, IF YOU NEED THEM MAKE SURE TO IMPLEMENT THEM. IF YOU DONT
// CALL CEverQuest::dsp_chat MAKE SURE TO IMPLEMENT EVENTS HERE
PLUGIN_API DWORD OnWriteChatColor(PCHAR Line, DWORD Color, DWORD Filter)
{
//	DebugSpewAlways("MQ2ChatWnd::OnWriteChatColor(%s)",Line);
	if (!MQChatWnd)
	{
		if (gGameState==GAMESTATE_INGAME)
		{
			SetGameState(gGameState);
		}
		if (!MQChatWnd)
			return 0; 
	}
	MQChatWnd->dShow=1;
	PFILTER pFilter = gpFilters; 

	while (pFilter) { 
		if (!pFilter->pEnabled || (*pFilter->pEnabled)) { 
			if (!strnicmp(Line,pFilter->FilterText,pFilter->Length)) {return 0;}
		} 
		pFilter = pFilter->pNext; 
	} 
	Color=pChatManager->GetRGBAFromIndex(Color);

	CHAR szProcessed[MAX_STRING];
	MQToSTML(Line,szProcessed,MAX_STRING,Color);
	strcat_s(szProcessed,"<br>");
	CXStr NewText(szProcessed);
	DebugTry(ConvertItemTags(NewText,0));

	ChatBuffer *pNewBuffer = new ChatBuffer;
	GetCXStr(NewText.Ptr,pNewBuffer->Text,MAX_STRING);
	pNewBuffer->pPrev=pPendingChatTail;
	pNewBuffer->pNext=0;
	if (pPendingChatTail)
		pPendingChatTail->pNext=pNewBuffer;
	else
		pPendingChat=pNewBuffer;
	pPendingChatTail=pNewBuffer;
	PendingChatLines++;
/**/

//	CXSize Whatever;
//	MQChatWnd->OutBoxLines++;
//	if (MQChatWnd->OutBoxLines>400)
//	{
//		MQChatWnd->OutputBox->StripFirstSTMLLines(1); //<---- SLOW
//		MQChatWnd->OutBoxLines-=1;
//	}
//	DebugTry(MQChatWnd->OutputBox->AppendSTML(&Whatever,NewText));
//	DebugTry(((CXWnd*)MQChatWnd->OutputBox)->SetVScrollPos(MQChatWnd->OutputBox->VScrollMax));
	/**/
	return 0;
}

// Called once directly before shutdown of the cleanui system, and also
// every time the game calls CDisplay::CleanGameUI()
PLUGIN_API VOID OnCleanUI(VOID)
{
	DebugSpewAlways("MQ2ChatWnd::OnCleanUI()");
	if (MQChatWnd)
	{
		SaveChatToINI((PCSIDLWND)MQChatWnd);
		delete MQChatWnd;
		MQChatWnd=0;
	}
}

// Called once directly after initialization, and then every time the gamestate changes
PLUGIN_API VOID SetGameState(DWORD GameState)
{
	DebugSpew("MQ2ChatWnd::SetGameState()");
	if (GameState==GAMESTATE_CHARSELECT)
	{
		AddMQ2KeyBind("MQ2CSCHAT",DoMQ2ChatBind);
		KeyCombo Combo;
		ParseKeyCombo("/",Combo);
		SetMQ2KeyBind("MQ2CSCHAT",0,Combo);
	}
	else
	{
		RemoveMQ2KeyBind("MQ2CSCHAT");
		if (GameState==GAMESTATE_INGAME && !MQChatWnd)
		{
			// we entered the game, set up shop
			DebugTry(CreateChatWindow());
		}
	}
}

PLUGIN_API VOID OnPulse(VOID)
{
	//DebugSpew("MQ2ChatWnd::OnPulse()");
	if (gGameState==GAMESTATE_CHARSELECT && !MQChatWnd)
	{
		CreateChatWindow();
	}

	if (MQChatWnd && PendingChatLines)
	{
		DWORD ThisPulse=PendingChatLines;
		if (ThisPulse>LINES_PER_FRAME)
			ThisPulse=LINES_PER_FRAME;
		PendingChatLines-=ThisPulse;
		MQChatWnd->OutBoxLines+=ThisPulse;
		if (MQChatWnd->OutBoxLines>MAX_CHAT_SIZE)
		{
			DWORD Diff=(MQChatWnd->OutBoxLines-MAX_CHAT_SIZE)+LINES_PER_FRAME;
			MQChatWnd->OutBoxLines-=Diff;
			Benchmark(bmStripFirstStmlLines,MQChatWnd->OutputBox->StripFirstSTMLLines(Diff));
		}

		CXSize Whatever;
		for (DWORD N = 0 ; N < ThisPulse ; N++)
		{
			DebugTry(MQChatWnd->OutputBox->AppendSTML(&Whatever,pPendingChat->Text));
			ChatBuffer *pNext=pPendingChat->pNext;
			delete pPendingChat;
			pPendingChat=pNext;
		}
		if (!pPendingChat)
			pPendingChatTail=0;
		DebugTry(((CXWnd*)MQChatWnd->OutputBox)->SetVScrollPos(MQChatWnd->OutputBox->VScrollMax));
	}
	/*
	if (MQChatWnd)
	{
		if (MQChatWnd->OutBoxLines>750)
		{
			MQChatWnd->OutputBox->StripFirstSTMLLines(1);
			MQChatWnd->OutBoxLines--;
//			((CXWnd*)MQChatWnd->OutputBox)->OnResize(0,0);
		}
	}
	/**/
}

void CreateChatWindow()
{
	DebugSpew("MQ2ChatWnd::CreateChatWindow()");
	if (!MQChatWnd) {
		MQChatWnd = new CMQChatWnd();
		if (!MQChatWnd)
			return;
		LoadChatFromINI((PCSIDLWND)MQChatWnd);
		SaveChatToINI((PCSIDLWND)MQChatWnd); // A) we're masochists, B) this creates the file if its not there..
	}
}

VOID DoMQ2ChatBind(PCHAR Name,BOOL Down)
{
	if (!Down)
	{
		if (MQChatWnd)
		{
			CXRect rect= ((CXWnd*)MQChatWnd->InputBox)->GetScreenRect();
			CXPoint pt=rect.CenterPoint();
			((CXWnd*)MQChatWnd->InputBox)->HandleLButtonDown(pt,0x20000);
			((CXWnd*)MQChatWnd->InputBox)->SetWindowTextA("/");
		}
	}
}
