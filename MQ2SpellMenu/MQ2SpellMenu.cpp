// MQ2SpellMenu.cpp : Defines the entry point for the DLL application.
//

#include "../MQ2Plugin.h"
#include "SpellCategories.h"
#include <vector>
#include <map>
#include <list>
PreSetup("MQ2SpellMenu");

void CreateSpellMenu();
class CMQMenuWnd;
PEQCASTSPELLGEM LastSpellGemClicked = 0;
int g_addedindex = 0;
std::map<int,CContextMenu*>MenuMap;
struct _themenu1
{
	std::string Name;
	std::string Category;
	std::string SubCategory;
	DWORD ID;
};
struct _themenu
{
	std::string Name;
	DWORD ID;
};
//Category-SubCategory
std::map<std::string,std::map<std::string,std::list<struct _themenu>>> SpellCategory;

class CMQMenuWnd : public CCustomMenu
{
public:
	CMQMenuWnd(CXRect rect):CCustomMenu(rect)
	{
		DebugSpew("CMQMenuWnd()");
		SetWndNotification(CMQMenuWnd);
	}

	~CMQMenuWnd()
	{
	}
	int WndNotification(CXWnd *pWnd, unsigned int Message, void *data)
	{	
		bool bFound = false;
		int slot=0;
		PEQCASTSPELLWINDOW addr = (PEQCASTSPELLWINDOW)pCastSpellWnd;
		for(;slot<8;slot++) {
			PEQCASTSPELLGEM address = addr->SpellSlots[slot];
			if(address==LastSpellGemClicked) {
				bFound=true;
				break;
			}
		}
		if(bFound) {
			std::string SpellName = GetSpellNameByID((DWORD)data-0x10000);
			if(SpellName=="Unknown Spell") {
				WriteChatf("ERROR: Spell not found in struct, has there been a patch?");
				return 0;
			}
			CHAR szTemp[256] = {0};
			sprintf_s(szTemp,"%d \"%s\"",slot+1,SpellName.c_str());
			MemSpell(GetCharInfo()->pSpawn,szTemp);
		} else {
			WriteChatf("ERROR: Slot not found in struct, has there been a patch?");
		}
		return 1;
	};
};


PLUGIN_API VOID OnCleanUI(VOID);
PLUGIN_API VOID SetGameState(DWORD GameState);


VOID Style(PSPAWNINFO pChar, PCHAR szLine)
{
	if (!szLine || szLine[0]==0)
	{
		char out[256];
		sprintf(out,"Style 0x%X",CategoryMenu->WindowStyle);
		WriteChatColor(out);
		return;
	}
	if (szLine[0]=='!')
	{
		int TurnOff;
		sscanf(&szLine[1],"%x",&TurnOff);
		BitOff(CategoryMenu->WindowStyle,TurnOff);
	}
	else
	{
		int TurnOn;
		sscanf(&szLine[0],"%x",&TurnOn);
		BitOn(CategoryMenu->WindowStyle,TurnOn);
	}
	char out[256];
	sprintf(out,"Style 0x%X",CategoryMenu->WindowStyle);
	WriteChatColor(out);
}
struct _BzSrchResponse {
	/* 0x00 */   short     BSSmsg;         // should be 7
	/* 0x02 */   short     BSSQuantity;   
	/* 0x04 */   short     BSSItemID;       
	/* 0x06 */   short     BSSTraderID;
	/* 0x08 */  long     BSSPrice;
	/* 0x0c */  char    BSSName[0x40];  // size is 0x58
	/* 0x4c */
};
	struct _BzFixedSrchResponse {
	/* 0x00**/   long     BSSmsg;         // should be 7
	/* 0x04*/  long    BSSItemID;
	/* 0x08 */   long     BSSTraderID;
	/* 0x0c */  long     BSSPrice;
	/* 0x10 */   long     BSSQuantity;   
	/* 0x14*/  char    BSSName[0x40];
	/* 0x50 */
};
struct _castspell
{
	std::string Name;
	int ID;
	class EQ_Item *item;
	int num;
};
DWORD __stdcall StandupThread(PVOID pData)
{
	_castspell *castspell = (_castspell *)pData;
	PCHARINFO pChar = GetCharInfo();
	if(pChar) {
		int waitcounter = 0;
		while(pChar->pSpawn->StandState!=STANDSTATE_STAND) {
			Sleep(50);
			waitcounter++;
			if(waitcounter>=100)//5 seconds... shouldnt take more even if lagged
				break;
		}
		if(pChar->pSpawn->StandState==STANDSTATE_STAND) {
			if(pCharData)
				pCharData->CastSpell(castspell->Name.c_str()[0],castspell->ID,&castspell->item,castspell->num);
		}
	}
	delete castspell;
	return 0;
}
DWORD __stdcall SitDownThread(PVOID pData)
{
	PCHARINFO pChar = (PCHARINFO)pData; 
	int waitcounter = 0;
	if(pChar) {
		while(pChar->pSpawn->StandState!=STANDSTATE_SIT) {
			Sleep(50);
			waitcounter++;
			if(waitcounter>=100)//5 seconds... shouldnt take more even if lagged
				break;
		}
		if(pChar->pSpawn->StandState==STANDSTATE_SIT) {
			if(pEverQuest)
				pEverQuest->Camp();
		}
	}
	return 1;
}
class Eqmachooks {
public:
	int CSpellGemWnd__HandleRButtonUp_Trampoline(class CXPoint,unsigned __int32);
	int CSpellGemWnd__HandleRButtonUp_Hook(class CXPoint pt,unsigned __int32 flag)
	{
		LastSpellGemClicked=(PEQCASTSPELLGEM)this;
		if(LastSpellGemClicked && LastSpellGemClicked->spellicon==0xFFFFFFFF) {
			pContextMenuManager->PopupMenu(gSpellMenuIndex,pt,(CXWnd*)CategoryMenu);
		}
		//WriteChatf("CSpellGemWnd__HandleRButtonUp_Hook called this=%x pt x=%d y=%d flag = %x",this,pt.A,pt.B,flag);
		return CSpellGemWnd__HandleRButtonUp_Trampoline(pt,flag);
	}
	unsigned char EQ_Character__CastSpell_Trampoline(unsigned char,int,class EQ_Item **,int);
	unsigned char EQ_Character__CastSpell_Hook(unsigned char Name,int ID,class EQ_Item **item,int num)
	{
		PCHARINFO pChar=(PCHARINFO)this;
		if(pChar->standstate!=STANDSTATE_STAND && pChar->pSpawn->pActorInfo->Mount==0) {
			DoCommand(pChar->pSpawn,"/stand");

			DWORD nThreadID = 0;
			_castspell *castspell = new _castspell;
			castspell->item = 0;
			castspell->Name = Name;
			castspell->ID = ID;
			if(item)
				castspell->item = *item;
			castspell->num = num;
			HANDLE hStandUp = CreateThread(NULL,0,StandupThread,castspell,0,&nThreadID);
			return 0;
		}
		if(ID!=0) {
			PSPELL pSpell = GetSpellByID(ID);
			if(pTarget==0 && pSpell->TargetType!=6 && pSpell->SpellType!=0) {//self/detrimental
				pTarget = (EQPlayer*)pChar->pSpawn;
			}
		} else {
			PITEMINFO pItem = 0;
			if(item)
				pItem = (PITEMINFO)*item;
			else if(num>=1)
				pItem = pChar->InventoryArray[num-1];
			if(pItem) {
				if(pItem->Common.SpellId!=0 && pItem->Common.SpellId!=0xFFFF) {
					PSPELL pSpell = GetSpellByID(pItem->Common.SpellId);
					if(pTarget==0 && pSpell && pSpell->SpellType!=0 && pSpell->TargetType!=6) {//detrimental/self
						pTarget = (EQPlayer*)pChar->pSpawn;
					}
				}
			}
		}
		return EQ_Character__CastSpell_Trampoline(Name,ID,item,num);
	}
	bool HandleBazaarMsg_Trampoline(PBYTE);
	bool HandleBazaarMsg_Hook(PBYTE packet)
	{
		_BzFixedSrchResponse *fixedpacket = new _BzFixedSrchResponse;
		fixedpacket->BSSmsg = ((_BzSrchResponse*)packet)->BSSmsg;
		fixedpacket->BSSItemID = ((_BzSrchResponse*)packet)->BSSItemID;
		fixedpacket->BSSPrice = ((_BzSrchResponse*)packet)->BSSPrice;
		fixedpacket->BSSTraderID = ((_BzSrchResponse*)packet)->BSSTraderID;
		fixedpacket->BSSQuantity = ((_BzSrchResponse*)packet)->BSSQuantity;
		strcpy_s(fixedpacket->BSSName,((_BzSrchResponse*)packet)->BSSName);
		bool ret =  HandleBazaarMsg_Trampoline((PBYTE)fixedpacket);
		delete fixedpacket;
		return ret;
	}

	void CLootWnd__AddEquipmentToLootArray_Trampoline(class EQ_Item *);
	void CLootWnd__AddEquipmentToLootArray_Hook(class EQ_Item *item)
	{
		return CLootWnd__AddEquipmentToLootArray_Trampoline(item);
	}
	
	void CEverQuest__Camp_Trampoline(void);
	void CEverQuest__Camp_Hook(void)
	{
		PCHARINFO pChar = GetCharInfo();
		BOOL bWait = 0;
		if(*(DWORD*)CampingInProgress) {
			DoCommand(pChar->pSpawn,"/stand");
		}
		if(pChar && pChar->pSpawn->pActorInfo->Mount) {
			DoCommand(pChar->pSpawn,"/dismount");
			DoCommand(pChar->pSpawn,"/sit");
			bWait = 1;
		} else if(pChar && pChar->standstate!=STANDSTATE_SIT) {
			DoCommand(pChar->pSpawn,"/sit");
			bWait = 1;
		}
		if(bWait) {
			DWORD nThreadID = 0;
			HANDLE hStandUp = CreateThread(NULL,0,SitDownThread,pChar,0,&nThreadID);
			return;
		}
		CEverQuest__Camp_Trampoline();
	}
	int CTextureFont__DrawWrappedText_Trampoline(class CXStr,int,int,int,class CXRect,unsigned long,unsigned short,int);
	int CTextureFont__DrawWrappedText_Hook(class CXStr Text,int X,int Y,int size,class CXRect rect,unsigned long color,unsigned short E,int F)
	{
		//CHAR szBuffer[MAX_STRING] = {0};
		//GetCXStr(Text.Ptr,szBuffer);
		//DebugSpew("DrawWrappedText %s,X=%d,Y=%d,size=%d,rect(%d,%d,%d,%d),color=%x,E=%d,F=%d",szBuffer,X,Y,size,rect.Left,rect.Top,rect.Right,rect.Bottom,color,E,F);
		return CTextureFont__DrawWrappedText_Trampoline(Text,X,Y,size,rect,color,E,F);
	}
};

DETOUR_TRAMPOLINE_EMPTY(void Eqmachooks::CEverQuest__Camp_Trampoline(void));
DETOUR_TRAMPOLINE_EMPTY(bool Eqmachooks::HandleBazaarMsg_Trampoline(PBYTE));
DETOUR_TRAMPOLINE_EMPTY(int Eqmachooks::CSpellGemWnd__HandleRButtonUp_Trampoline(class CXPoint,unsigned __int32));
DETOUR_TRAMPOLINE_EMPTY(unsigned char Eqmachooks::EQ_Character__CastSpell_Trampoline(unsigned char,int,class EQ_Item **,int));
DETOUR_TRAMPOLINE_EMPTY(int Eqmachooks::CTextureFont__DrawWrappedText_Trampoline(class CXStr,int,int,int,class CXRect,unsigned long,unsigned short,int));
DETOUR_TRAMPOLINE_EMPTY(void Eqmachooks::CLootWnd__AddEquipmentToLootArray_Trampoline(class EQ_Item *));

PLUGIN_API VOID InitializePlugin(VOID)
{
	DebugSpewAlways("Initializing MQ2SpellMenu");
	// Add commands, macro parameters, hooks, etc.
	
	EzDetour(CEverQuest__Camp,&Eqmachooks::CEverQuest__Camp_Hook,&Eqmachooks::CEverQuest__Camp_Trampoline);
	EzDetour(CSpellGemWnd__HandleRButtonUp,&Eqmachooks::CSpellGemWnd__HandleRButtonUp_Hook,&Eqmachooks::CSpellGemWnd__HandleRButtonUp_Trampoline);
	EzDetour(EQ_Character__CastSpell,&Eqmachooks::EQ_Character__CastSpell_Hook,&Eqmachooks::EQ_Character__CastSpell_Trampoline);
	EzDetour(CBazaarSearchWnd__HandleBazaarMsg,&Eqmachooks::HandleBazaarMsg_Hook,&Eqmachooks::HandleBazaarMsg_Trampoline);
	//EzDetour(CLootWnd__AddEquipmentToLootArray,&Eqmachooks::CLootWnd__AddEquipmentToLootArray_Hook,&Eqmachooks::CLootWnd__AddEquipmentToLootArray_Trampoline);
	//EzDetour(CTextureFont__DrawWrappedText,&Eqmachooks::CTextureFont__DrawWrappedText_Hook,&Eqmachooks::CTextureFont__DrawWrappedText_Trampoline);
	 
}

PLUGIN_API VOID ShutdownPlugin(VOID)
{
	DebugSpewAlways("Shutting down MQ2SpellMenu");
	OnCleanUI();
	RemoveDetour(CEverQuest__Camp);
	RemoveDetour(CSpellGemWnd__HandleRButtonUp);
	RemoveDetour(EQ_Character__CastSpell);
	RemoveDetour(CBazaarSearchWnd__HandleBazaarMsg);
	//RemoveDetour(CLootWnd__AddEquipmentToLootArray);
	//RemoveDetour(CTextureFont__DrawWrappedText);
}


// This is called every time WriteChatColor is called by MQ2Main or any plugin,
// IGNORING FILTERS, IF YOU NEED THEM MAKE SURE TO IMPLEMENT THEM. IF YOU DONT
// CALL CEverQuest::dsp_chat MAKE SURE TO IMPLEMENT EVENTS HERE
PLUGIN_API DWORD OnWriteChatColor(PCHAR Line, DWORD Color, DWORD Filter)
{
//	DebugSpewAlways("MQ2ChatWnd::OnWriteChatColor(%s)",Line);
	if (!CategoryMenu)
	{
		if (gGameState==GAMESTATE_INGAME)
		{
			SetGameState(gGameState);
		}
	}
	return 0;
}

// Called once directly before shutdown of the cleanui system, and also
// every time the game calls CDisplay::CleanGameUI()
PLUGIN_API VOID OnCleanUI(VOID)
{
	DebugSpewAlways("MQMenuWnd::OnCleanUI()");
	if(CategoryMenu)
	{
		if(pContextMenuManager) {
			//I would very much like to just call pContextMenuManager->RemoveMenu here but it crashes and i
			//havent figured out why
			//feel free to look into it... /eqmule
			for(std::map<int,CContextMenu*>::reverse_iterator i=MenuMap.rbegin();i!=MenuMap.rend();i++)
			{
				pContextMenuManager->Menus[i->first]=0;
				pContextMenuManager->MenuCount--;
				if(i->second!=CategoryMenu) {
					delete i->second;
					i->second = 0;
				}
			}
			MenuMap.clear();
			delete CategoryMenu;
			CategoryMenu=0;
		}
	}
}

// Called once directly after initialization, and then every time the gamestate changes
PLUGIN_API VOID SetGameState(DWORD GameState)
{
	DebugSpew("MQ2ChatWnd::SetGameState()");
	if (GameState==GAMESTATE_INGAME && !CategoryMenu)
	{
		// we entered the game, set up shop
		DebugTry(CreateSpellMenu());
	}
}
PLUGIN_API VOID OnDrawHUD(VOID)
{
	if(gGameState==GAMESTATE_INGAME) {
		CHARINFO *pChar = GetCharInfo();
		if(pChar) {
			CHAR szToolTip[64] = {0};
			PEQBUFFWINDOW buffwnd = (PEQBUFFWINDOW)pBuffWindow;
			CButtonWnd * button;
			WORD duration;
			WORD SpellID;
			for (int N = 0 ; N < 15 ; N++)
			{
				SpellID = pChar->Buff[N].SpellID;
				if (SpellID!=0xFFFF && SpellID!=0)
				{
					duration = pChar->Buff[N].Duration;
					if(buffwnd) {
						button = (CButtonWnd *)buffwnd->pBuff[N];
						if(button) {
							//lets split duration into hours,minutes and seconds
							int seconds = (duration*60)/6;
							int minutes = seconds/60;
							int leftoverseconds = seconds % 60;
							int leftoverminutes = minutes % 60;
							int hours = minutes / 60;
							if(hours) {
								sprintf_s(szToolTip,"%dh",hours);
							} else if(minutes) {
								sprintf_s(szToolTip,"%dm",minutes);
							} else {
								sprintf_s(szToolTip,"%ds",seconds);
							}//need one for "Permanent" as well, ill add that later
							CXRect rect = ((CXWnd*)button)->GetScreenRect();
							CXRect greyrect;
							greyrect.Left= rect.Left+20;
							greyrect.Top= rect.Top+32;
							greyrect.Right= rect.Right-2;
							greyrect.Bottom= rect.Bottom-2;
							((CXWnd*)button)->DrawColoredRect(greyrect,0x7F000000,rect);
							CTextureFont * pFont = 0;
							if(pWndMgr)
								pFont = pWndMgr->GetFont1(1);
							if(pFont) {
								pFont->DrawWrappedText(szToolTip,greyrect.Left+3,greyrect.Top-1,greyrect.Right,rect,0xFFFFFFFF,1,0);
							}
						}
					}
				}
			}
		}
	}
}
PLUGIN_API VOID OnPulse(VOID)
{
	if (gGameState==GAMESTATE_INGAME && !CategoryMenu)
	{
		CreateSpellMenu();
	}
}

void CreateSpellMenu()
{
	DebugSpew("MQMenuWnd::CreateSpellMenu()");
	if(!CategoryMenu) {
		if(pContextMenuManager) {//can only do this when we are in game...
			SpellCategory.clear();
			MenuMap.clear();
			PCHARINFO pCharInfo=GetCharInfo();
			PSPELL pSpell=0;
			for (WORD N = 0 ; N < NUM_BOOK_SLOTS ; N++) {
				if (PSPELL pTempSpell=GetSpellByID(pCharInfo->SpellBook[N]))
				{
					struct _themenu themenu;
					themenu.ID = pTempSpell->ID;
					CHAR szLevel[8] = {0};
					int Level = pTempSpell->Level[pCharInfo->Class-1];
					_itoa_s(Level,szLevel,10);
					themenu.Name = szLevel;
					themenu.Name += " - ";
					themenu.Name += pTempSpell->Name;
					DWORD categoryID = GetSpellCategory(pTempSpell->ID);
					DWORD subcategoryID = GetSpellSubCategory(pTempSpell->ID);
					std::string category = GetSpellCategoryName(categoryID);
					std::string subcategory = GetSpellSubCategoryName(subcategoryID);
					SpellCategory[category][subcategory].push_back(themenu);
				}
			}
			CXRect rc;
			rc.Left=100;
			rc.Top=100;
			rc.Right=100;
			rc.Bottom=100;
			//ok we need to know what inedx to use, so we pick up the last one used:
			int defaultindex = pContextMenuManager->GetDefaultMenuIndex();
			CategoryMenu = new CMQMenuWnd(rc);
			for(std::map<std::string,std::map<std::string,std::list<struct _themenu>>>::iterator i=SpellCategory.begin();i!=SpellCategory.end();i++)
			{
				CContextMenu *SubCategoryMenu = new CContextMenu(0,0,rc);
				for(std::map<std::string,std::list<struct _themenu>>::iterator j=i->second.begin();j!=i->second.end();j++)
				{
					CContextMenu *SpellMenu = new CContextMenu(0,0,rc);
					for(std::list<struct _themenu>::iterator k=j->second.begin();k!=j->second.end();k++)
					{
						SpellMenu->AddMenuItem(k->Name.c_str(),0x10000+k->ID,0);
					}
					int addedindex = pContextMenuManager->AddMenu(SpellMenu);
					MenuMap[addedindex]=SpellMenu;
					addedindex|=MS_EXPANDABLE;
					SubCategoryMenu->AddMenuItem(j->first.c_str(),addedindex,0);
				}
				int addedindex = pContextMenuManager->AddMenu(SubCategoryMenu);
				MenuMap[addedindex]=SubCategoryMenu;
				addedindex|=MS_EXPANDABLE;
				CategoryMenu->AddMenuItem(i->first.c_str(),addedindex,0);
			}
			gSpellMenuIndex = pContextMenuManager->AddMenu(CategoryMenu);
			MenuMap[gSpellMenuIndex]=CategoryMenu;
		}
	}
}
