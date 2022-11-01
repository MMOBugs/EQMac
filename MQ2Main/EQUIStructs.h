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

namespace EQUIStructs
{


enum UIType
{
	UI_Unknown=0,
	UI_Listbox=22,
	UI_Button=23,
	UI_Gauge=24,
	UI_SpellGem=25,
	UI_InvSlot=26,
	UI_EditBox=27,
	UI_Slider=28,
	UI_Label=29,
	UI_STMLBox=30,
	UI_Combobox=31,
	UI_Page=32,
	UI_TabBox=33,
	UI_HorizontalLayoutBox=35,
	UI_VericalLayoutBox=36,
	UI_Screen=38,
};

// ***************************************************************************
// Structures
// ***************************************************************************

// 10-24-2003 Lax - Massive overhaul.
// See http://macroquest.sourceforge.net/phpBB2/viewtopic.php?t=3569 for
// standards on structures to make things easier on everyone!
// -- ONLY applies to EQ structs, not MQ structs like alerts, etc.


//5-15-2003   eqmule
typedef struct _CXSTR {
/*0x00*/   DWORD   Font;            // maybe, dont know.  04 = Window 01 = button
/*0x04*/   DWORD   MaxLength;
/*0x08*/   DWORD   Length;
/*0x0c*/   BOOL    Encoding; // 0: ASCII, 1:Unicode
/*0x10*/   PCRITICAL_SECTION pLock;
/*0x14*/   CHAR    Text[1]; // Stub, can be anywhere from Length to MaxLength (which is how much is malloc'd to this CXStr)
} CXSTR, *PCXSTR;


typedef struct _EQCURRENTSELECTION {
/*0x00*/   DWORD   Unknown;
/*0x04*/   DWORD   SelectedWnd;//address to selection in tree
/*0x08*/   DWORD   Unknownlodncrap;
/*0x0c*/   DWORD   NumberOfSlots;//merchantslots == 79
/*0x10*/   DWORD   TextureAnim;
/*0x14*/
} EQCURRENTSELECTION, *PEQCURRENTSELECTION;

// Eqmule
// Actual Size 0xFC eqmac
//CXWnd::vftable

#define VFTABLE \
/*0000*/ LPVOID IsValid; \
/*0004*/ LPVOID  vector_deleting_destructor; \
/*0008*/ LPVOID  DrawNC; \
/*000C*/ LPVOID  PostDraw; \
/*0010*/ LPVOID  PostDraw2; \
/*0014*/ LPVOID  DrawCursor; \
/*0018*/ LPVOID  OnResize; \
/*001C*/ LPVOID  PostDraw3; \
/*0020*/ LPVOID  DrawBackground; \
/*0024*/ LPVOID  DrawTooltip; \
/*0028*/ LPVOID  GetMinimizedRect; \
/*002C*/ LPVOID  DrawTitleBar; \
/*0030*/ LPVOID  GetCursorToDisplay; \
/*0034*/ LPVOID  HandleLButtonDown; \
/*0038*/ LPVOID  HandleLButtonUp; \
/*003C*/ LPVOID  HandleLButtonHeld; \
/*0040*/ LPVOID  HandleLButtonUpAfterHeld; \
/*0044*/ LPVOID  HandleRButtonDown; \
/*0048*/ LPVOID  HandleRButtonUp; \
/*004C*/ LPVOID  HandleRButtonHeld; \
/*0050*/ LPVOID  HandleRButtonUpAfterHeld; \
/*0054*/ LPVOID  HandleWheelButtonDown; \
/*0058*/ LPVOID  HandleWheelButtonUp; \
/*005C*/ LPVOID  HandleMouseMove; \
/*0060*/ LPVOID  HandleWheelMove; \
/*0064*/ LPVOID  HandleKeyboardMsg1; \
/*0068*/ LPVOID  HandleKeyboardMsg2; \
/*006C*/ LPVOID  OnDragDrop; \
/*0070*/ LPVOID  GetDragDropCursor; \
/*0074*/ LPVOID  QueryDropOK; \
/*0078*/ LPVOID  OnClickStick; \
/*007C*/ LPVOID  GetDragDropCursor2; \
/*0080*/ LPVOID  QueryClickStickDropOK; \
/*0084*/ LPVOID  WndNotification; \
/*0088*/ LPVOID  Deactivate; \
/*008C*/ LPVOID  ShowWindow; \
/*0090*/ LPVOID  OnMove; \
/*0094*/ LPVOID  OnResize2; \
/*0098*/ LPVOID  OnMinimizeBox; \
/*009C*/ LPVOID  OnTileBox; \
/*00A0*/ LPVOID  CXWnd_OnShowANDPostDraw; \
/*00A4*/ LPVOID  OnSetFocus; \
/*00A8*/ LPVOID  OnSetFocus2; \
/*00AC*/ LPVOID  OnProcessFrame; \
/*00B0*/ LPVOID  OnVScroll; \
/*00B4*/ LPVOID  OnHScroll; \
/*00B8*/ LPVOID  OnBroughtToTop; \
/*00BC*/ LPVOID  CXWnd_OnSetFocus; \
/*00C0*/ LPVOID  CXWnd_OnSetFocus2; \
/*00C4*/ LPVOID  CXWnd_RequestDockInfo; \
/*00C8*/ LPVOID  CXWnd_GetTooltip; \
/*00CC*/ LPVOID  CXWnd_HitTest; \
/*00D0*/ LPVOID  CXWnd_GetHitTestRect; \
/*00D4*/ LPVOID  CXWnd_GetInnerRect; \
/*00D8*/ LPVOID  CXWnd_GetClientRect; \
/*00DC*/ LPVOID  CXWnd_GetMinSize; \
/*00E0*/ LPVOID  CXWnd_GetUntileSize; \
/*00E4*/ LPVOID  IsPointTransparent; \
/*00E8*/ LPVOID  SetDrawTemplate; \
/*00EC*/ LPVOID  SetWindowTextA; \
/*00F0*/ LPVOID  SetVScrollPos; \
/*00F4*/ LPVOID  SetAttributesFromSidl; \
/*00F8*/ LPVOID  DefineImages; \
/*00FC*/
typedef struct _CSIDLWNDVFTABLE {
VFTABLE;
/*0x0FC*/ LPVOID  LoadIniInfo;
/*0x100*/ LPVOID  StoreIniInfo;
/*0x104*/
} CSIDLWNDVFTABLE, *PCSIDLWNDVFTABLE; 
typedef struct _CCONTEXTMENUVFTABLE {
VFTABLE;
/*0x0FC*/ LPVOID  CListWnd_OnHeaderClick;
/*0x100*/ LPVOID  CListWnd_DrawColumnSeparators;
/*0x104*/ LPVOID  CListWnd_DrawSeparator;
/*0x108*/ LPVOID  CListWnd_DrawLine;
/*0x10c*/ LPVOID  CListWnd_DrawHeader;
/*0x110*/ LPVOID  CListWnd_DrawItem;
/*0x114*/ LPVOID  CListWnd_DeleteAll;
/*0x118*/ LPVOID  CListWnd_Compare;
/*0x11c*/ LPVOID  CListWnd_Sort;
/*0x120*/
} CCONTEXTMENUVFTABLE, *PCCONTEXTMENUVFTABLE; 
typedef struct _CXWNDVFTABLE {
VFTABLE;
} CXWNDVFTABLE, *PCXWNDVFTABLE; 


#define CXW_NO_VTABLE \
/*0x004*/   DWORD   Unknown0x004; /* set to 0 in CXWnd::Refade*/ \
/*0x008*/   DWORD   TimeMouseOver; /* "Delay" in ini*/ \
/*0x00c*/   DWORD   FadeDuration; /* "Duration" in ini*/ \
/*0x010*/   BYTE    FadeToAlpha; /* set to 1 in CXWnd::Refade */ \
/*0x011*/   BYTE    Unknown0x011; /* Faded? */ \
/*0x012*/   BYTE    Locked; \
/*0x013*/   BYTE    Unknown0x013; \
/*0x014*/   BYTE    Clickable; \
/*0x015*/   BYTE    Unknown0x015; \
/*0x016*/   BYTE    Unknown0x016; \
/*0x017*/   BYTE    Unknown0x017; \
/*0x018*/   BYTE    Unknown0x018[0x04]; \
/*0x01c*/   struct  _CSIDLWND *pParentWindow; /* If this is NULL, coordinates are absolute...*/ \
/*0x020*/   struct  _CSIDLWND *pChildren; \
/*0x024*/   struct  _CSIDLWND *pSiblings;  /* its a tree.*/ \
/*0x028*/   BYTE    HasChildren; /*CXWnd__GetFirstChildWnd*/ \
/*0x029*/   BYTE    HasSiblings;/*CXWnd__GetNextSib*/ \
/*0x02a*/   BYTE    Unknown0x02a[0x2]; \
/*0x02c*/   DWORD   XMLIndex; \
/*0x030*/   RECT    Location; \
/*0x040*/   RECT    OldLocation; \
/*0x050*/   BYTE    dShow; \
/*0x051*/   BYTE    Enabled; \
/*0x052*/   BYTE    Minimized; \
/*0x053*/   BYTE    Unknown0x053; /*ontilebox*/ \
/*0x054*/   BYTE    Unknown0x054; \
/*0x055*/   BYTE    Unknown0x055; \
/*0x056*/   BYTE    MouseOver; \
/*0x057*/   BYTE    Unknown0x057; \
/*0x058*/   DWORD   WindowStyle; /* bit 1 - vertical scroll, bit 2 - horizontal scroll, bit 4 - title bar?, bit 8 - border*/ \
/*0x05c*/   DWORD   TextureFont; /*its a CTextureFont* */\
/*0x060*/   struct _CXSTR  *WindowText; \
/*0x064*/   struct _CXSTR  *Tooltip; \
/*0x068*/   DWORD   UnknownCW; /* CXWnd::SetLookLikeParent*/ \
/*0x06c*/   ARGBCOLOR BGColor; /* "BGTint.Red", green, blue*/ \
/*0x070*/   DWORD    Unknown0x070; \
/*0x074*/   BYTE    Unknown0x074[0x4]; \
/*0x078*/   FLOAT    Unknown0x078; \
/*0x07C*/   BYTE    Unknown0x07C[0x4]; \
/*0x080*/   DWORD   BGType; /* "BGType" in ini */ \
/*0x084*/   struct _CXSTR  *XMLToolTip; \
/*0x088*/   BYTE    Unknown0x088[0x14]; \
/*0x09c*/   BYTE    Alpha; /* "Alpha" in ini */ \
/*0x09d*/   BYTE    Fades; /* "Fades" in ini */ \
/*0x09e*/   BYTE    Unknown0x0aa; \
/*0x09f*/   BYTE    Unknown0x0ab; \
/*0x0a0*/   BYTE    Unknown0x0a0[0x8]; \
/*0x0a8*/   LPVOID  DrawTemplate; \
/*0x0ac*/   BYTE    Unknown0x0ac[0x4]; \
/*0x0b0*/   DWORD   ZLayer; \
/*0x0b4*/   BYTE   Unknown0x0b4[0x28]; \
/*0x0dc*/   DWORD   FadeTickCount; \
/*0x0e0*/   BYTE    Unknown0x0f8; /* CXWnd::StartFade */ \
/*0x0e1*/   BYTE    Unknown0x0f9; /* CXWnd::StartFade */ \
/*0x0e2*/   BYTE    Unknown0x0fa; \
/*0x0e3*/   BYTE    Unknown0x0fb; \
/*0x0e4*/   DWORD   Unknown0x0fc; /* CXWnd::StartFade, CXWnd::Minimize */ \
/*0x0e8*/   DWORD   VScrollMax; \
/*0x0ec*/   DWORD   VScrollPos; \
/*0x0f0*/   DWORD   HScrollMax; \
/*0x0f4*/   DWORD   HScrollPos; \
/*0x0f8*/   BYTE    ValidCXWnd; \
/*0x0f9*/   BYTE    Unused0x0f9[0x3]; \
/*0x0fc*/

#define CONTEXTW \
/*0x000*/   struct  _CCONTEXTMENUVFTABLE   *pvfTable; \
CXW_NO_VTABLE \
/*0x0fc*/   union { \
				struct _CXSTR  *SidlText; \
				DWORD Items; \
			}; \
/*0x100*/   union { \
			   struct _CXSTR  *SidlScreen; \
               DWORD   SlotID; \
         }; \
/*0x104*/   LPVOID SidlPiece; /* CScreenPieceTemplate (important) */ \
/*0x108*/   BYTE    Checked; \
/*0x109*/   BYTE    Highlighted; \
/*0x10a*/   BYTE    Unused0x10a[0x2]; \
/*0x10c*/   DWORD   TextureAnim; /* used in CSidlScreenWnd::AddButtonToRadioGroup */ \
/*0x110*/   struct _CXSTR *   InputText; \
/*0x114*/   DWORD   Selector; \
/*0x118*/   DWORD   PushToSelector; \
/*0x11c*/   DWORD   EnableINIStorage; \
/*0x120*/   union { \
				struct _CXSTR *INIStorageName; \
				struct _EQINVSLOT *pEQInvSlot; \
			}; \
/*0x124*/   DWORD   Unknown0x124; /* CTextureAnimation */ \
/*0x128*/   DWORD   Unknown0x128; /* CTextureAnimation */ \
/*0x12c*/   DWORD  ContextMenu; /* CTextureAnimation its an id for the menu*/ \
/*0x130*/	CContextMenu *Unknown0x130; /* CTextureAnimation */ \
/*0x134*/	BYTE Unknown0x134; \
/*0x135*/	BYTE Unknown0x135; \
/*0x136*/	BYTE Unknown0x136; \
/*0x137*/	BYTE Unknown0x137; \
/*0x138*/	BYTE Unknown0x138; \
/*0x139*/	BYTE Unknown0x139; \
/*0x13a*/	BYTE Unknown0x13a; \
/*0x13b*/	BYTE Unknown0x13b; \
/*0x13c*/	CContextMenu *Unknown0x13c; \
/*0x140*/	CContextMenu *Unknown0x140; \
/*0x144*/	BYTE Unknown0x144; \
/*0x145*/	BYTE Unknown0x145; \
/*0x146*/	BYTE Unknown0x146; \
/*0x147*/	BYTE Unknown0x147; \
/*0x148*/	CContextMenu * Unknown0x148; \
/*0x14c*/	DWORD Unknown0x14c; \
/*0x150*/	CContextMenu * Unknown0x150; \
/*0x154*/	DWORD Unknown0x154; \
/*0x158*/	CContextMenu * Unknown0x158; \
/*0x15c*/	DWORD Unknown0x15c; \
/*0x160*/	CContextMenu * Unknown0x160; \
/*0x164*/	DWORD Unknown0x164; \
/*0x168*/	CContextMenu * Unknown0x168; \
/*0x16c*/	DWORD Unknown0x16c; \
/*0x170*/	CContextMenu * Unknown0x170; \
/*0x174*/	DWORD Unknown0x174; \
/*0x178*/	CContextMenu * Unknown0x178; \
/*0x17c*/	DWORD Unknown0x17c; \
/*0x180*/


#define CXW \
/*0x000*/   struct  _CXWNDVFTABLE   *pvfTable; \
CXW_NO_VTABLE \
/*0x0fc*/

typedef struct _CXWND {
CXW;
} CXWND, *PCXWND;

#define CSW \
/*0x000*/   struct _CSIDLWNDVFTABLE   *pvfTable; \
CXW_NO_VTABLE; \
/*0x0fc*/   union { \
				struct _CXSTR  *SidlText; \
				DWORD Items; \
			}; \
/*0x100*/   union { \
			   struct _CXSTR  *SidlScreen; \
               DWORD   SlotID; \
         }; \
/*0x104*/   LPVOID SidlPiece; /* CScreenPieceTemplate (important) */ \
/*0x108*/   BYTE    Checked; \
/*0x109*/   BYTE    Highlighted; \
/*0x10a*/   BYTE    Unused0x10a[0x2]; \
/*0x10c*/   DWORD   TextureAnim; /* used in CSidlScreenWnd::AddButtonToRadioGroup */ \
/*0x110*/   struct _CXSTR *   InputText; \
/*0x114*/   DWORD   Selector; \
/*0x118*/   DWORD   PushToSelector; \
/*0x11c*/   DWORD   EnableINIStorage; \
/*0x120*/   union { \
				struct _CXSTR *INIStorageName; \
				struct _EQINVSLOT *pEQInvSlot; \
			}; \
/*0x124*/   DWORD   Unknown0x124; /* CTextureAnimation */ \
/*0x128*/   DWORD   Unknown0x128; /* CTextureAnimation */ \
/*0x12c*/   DWORD  ContextMenu; /* CTextureAnimation its an id for the menu*/ \
/*0x130*/	DWORD   Unknown0x130; /* CTextureAnimation */ \
/*0x134*/

#define EQ_CHAT_HISTORY_OFFSET 0x1a0
#define EQ_FONT_SIZE_OFFSET 0x154
typedef struct _CSIDLWND {
CSW;
} CSIDLWND, *PCSIDLWND;

// size 0x268  5-12-2004 lax
//eqmac fixed for eqgame.exe dec 2002
typedef struct _CSIDLMGR {
/*0x000*/	BYTE	Unknown0x000[0x114];
/*0x114*/	PVOID pXMLDataMgr;//CXWnd__GetChildItem
/*0x118*/	BYTE	Unknown0x118[0x150];
/*0x268*/
} CSIDLMGR, *PCSIDLMGR;

//eqmac fixed for eqgame.exe dec 2002
typedef struct _CXWNDMGR {
/*0x000*/ PVOID CXWndManager_vftable;
/*0x004*/ struct _CSIDLWND *pWindows; 
/*0x008*/ BYTE Unknown0x00C[0x4d];
/*0x055**/ bool KeyboardFlags[4];
/*0x059*/ BYTE Unknown0x059[0x63];
/*0x0bc**/ DWORD ScreenExtentX;//800 if in 800x600 mode
/*0x0c0**/ DWORD ScreenExtentY;//600 if in 800x600 mode
/*0x0c4***/ DWORD font_list_ptr;//jun 2013 dont know if this is correct
/*0x0c8*/ 
} CXWNDMGR, *PCXWNDMGR;


// 06-16-2004 dkaa - size is 0x404
typedef struct _EQMERCHWINDOW {
/*0x000*/   struct _CSIDLWND Wnd;
/*0x158*/   BYTE    Unknown0x150[0x8];
/*0x160*/   PITEMINFO   ItemDesc[0x50];     // the mainwindow has pointers
                                            // directly to the items in the
                                            // slots...
/*0x2a0*/   FLOAT   Markup;
/*0x2a4*/   DWORD   SelectedSlotID;
/*0x2a8*/   DWORD   AddressToPointerForSelectedItem;
/*0x2ac*/   DWORD   MW_MerchantName;
/*0x2b0*/   DWORD   MW_SelectedItem;
/*0x2b4*/   DWORD   MW_Buy_Button;
/*0x2b8*/   DWORD   MW_Sell_Button;
/*0x2bc*/   struct _CSIDLWND   *SlotsHandles[0x50];
/*0x3fc*/   DWORD   DoneButton;
/*0x400*/   DWORD   MerchantSlotsWnd;
/*0x404*/
} EQMERCHWINDOW, *PEQMERCHWINDOW;



// 10-27-2003 Lax
// Actual size 0x208 11-5-2003
typedef struct _EQCHATMGR
{
/*0x000*/ struct _EQCHATWINDOW* ChatWnd[0x20];
/*0x080*/ DWORD NumWindows;
/*0x084*/ DWORD ActiveWindow; // CChatManager::GetActiveChatWindow
/*0x088*/ DWORD LockedWindow; // CChatManager::GetActiveChatWindow
/*0x08c*/ DWORD Unknown0x08c;
/*0x090*/ struct _EQCHATWINDOW* ChannelMap[0x20];   // channel map
/*0x110*/ BYTE  Unknown0x110[0x28];
/*0x138*/ DWORD Unknown0x138;
/*0x13c*/ DWORD Unknown0x13c;
/*0x140*/ DWORD Unknown0x140;
/*0x144*/ LPVOID ChatMenu;
/*0x148*/ DWORD Unknown0x148;
/*0x14c*/ DWORD Unknown0x14c;
/*0x150*/ DWORD Unknown0x150;
/*0x154*/ DWORD Unknown0x154;
/*0x158*/ LPVOID MeleeMenu;
/*0x15c*/ DWORD Unknown0x15c;
/*0x160*/ LPVOID SpellMenu;
/*0x164*/ DWORD Unknown0x164;
/*0x168*/ DWORD Unknown0x168;
/*0x16c*/ LPVOID ChannelMenu;
/*0x170*/ LPVOID ChatMenu2;
/*0x174*/ LPVOID FilterMenu;
/*0x178*/ DWORD Unknown0x178;
/*0x17c*/ DWORD Unknown0x17c;
/*0x180*/ DWORD Unknown0x180;
/*0x184*/ LPVOID HitsModeMenu;
/*0x188*/ LPVOID MeleeMenu2;
/*0x18c*/ LPVOID HitsModeMenu2;
/*0x190*/ DWORD Unknown0x190;
/*0x194*/ LPVOID HitsModeMenu3;
/*0x198*/ DWORD Unknown0x198;
/*0x19c*/ LPVOID HitsModeMenu4;
/*0x1a0*/ DWORD Unknown0x1a0;
/*0x1a4*/ LPVOID HitsModeMenu5;
/*0x1a8*/ DWORD Unknown0x1a8;
/*0x1ac*/ LPVOID HitsModeMenu6;
/*0x1b0*/ DWORD Unknown0x1b0;
/*0x1b4*/ DWORD Unknown0x1b4; // CChatManager__UpdateTellMenus
/*0x1b8*/ DWORD Unknown0x1b8;
/*0x1bc*/ DWORD Unknown0x1bc; // CChatManager__UpdateTellMenus
/*0x1c0*/ DWORD Unknown0x1c0;
/*0x1c4*/ DWORD Unknown0x1c4; // CChatManager__UpdateTellMenus // raid
/*0x1c8*/ DWORD Unknown0x1c8;
/*0x1cc*/ DWORD Unknown0x1cc; // CChatManager__UpdateTellMenus
/*0x1d0*/ DWORD Unknown0x1d0; // CChatManager__UpdateTellMenus
/*0x1d4*/ DWORD Unknown0x1d4; // CChatManager__UpdateTellMenus
/*0x1d8*/ DWORD Unknown0x1d8;
/*0x1dc*/ DWORD Unknown0x1dc;
/*0x1e0*/ DWORD Unknown0x1e0;
/*0x1e4*/ BYTE  Unknown0x1e4[0x1c];
/*0x200*/ DWORD Unknown0x200;
/*0x204*/ DWORD Unknown0x204;
/*0x208*/
} EQCHATMGR, *PEQCHATMGR;

// Actual size 0x254 11-5-2003
// 10-27-2003 Lax
//eqmule eqmac version dec 2002
typedef struct _EQCHATWINDOW
{
/*0x000*/ struct _CSIDLWND Wnd;
/*0x134*/ struct _EQCHATMGR *ChatManager; 
/*0x138*/ struct _CSIDLWND* InputWnd;
/*0x13c*/ struct _CSIDLWND* OutputWnd;
/*0x140*/ BYTE Unknown0x140[0x50];
/*0x190**/ struct _CXSTR *CommandHistory[0x28];// CChatWindow::HistoryBack/forward has this one
/*0x230*/ DWORD Unknown0x230;       // CChatWindow::HistoryBack/forward .. maybe total or current history lines
/*0x234*/ DWORD Unknown0x234;       // CChatWindow::HistoryBack/forward .. maybe total or current history lines
/*0x238*/ DWORD FontSize;
/*0x23c*/
} EQCHATWINDOW, *PEQCHATWINDOW;

// Actual size 0x14c updated for eqmac jun 2013 eqmule
// Lax 10-24-2003
typedef struct _EQBUFFWINDOW
{
/*0x000*/ struct _CSIDLWND Wnd;
/*0x134*/ BYTE  FirstEffectSlot; //0-15 0x000
/*0x135*/ BYTE  LastEffectSlot; //0-15 0x001
/*0x136*/ BYTE  MaxBuffs;// 0x002 either 0x0F or 0x06  (normal or shortbuffs)
/*0x137*/ BYTE  Unknown0x137[0x45];// 0x003
/*0x17c*/ DWORD pBuff[0x0f];    // CButton* 0x048
/*0x1xx*/ BYTE  Unknown0x1xx[0xc8];
/*0x14C*/
} EQBUFFWINDOW, *PEQBUFFWINDOW;

// actual size 0x10c /eqmac
typedef struct _EQINVSLOTWND {
/*0x000*/   struct _CXWND Wnd;
/*0x0fc*/	DWORD Unknown0x0fc;
/*0x100*/	LONG InvSlot;
/*0x104*/   DWORD Unknown0x104;
/*0x108*/   BOOL ProcessClick;
/*0x10C*/
} EQINVSLOTWND, *PEQINVSLOTWND;

// actual size 0x14 2-18-2004 Lax
//this is correct for eqmac i think
typedef struct _EQINVSLOT {
/*0x00*/	LPVOID pvfTable; // not based on cxwnd
/*0x04*/	struct _EQINVSLOTWND *pInvSlotWnd;
/*0x08*/	DWORD Unknown0x08;
/*0x0C*/	DWORD SlotArrayIndex;
/*0x10*/	PITEMINFO pItem;
/*0x14*/
} EQINVSLOT, *PEQINVSLOT;

// actual size:.text -> 004A6190 push 714h
//fix for eqmac - eqmule
typedef struct _EQINVSLOTMGR {
/*0x0000*/	void *pvfTable;
/*0x0004*/	struct _EQINVSLOT *SlotArray[0x1C2];
/*0x070C*/	DWORD TotalSlots;
/*0x0710*/	DWORD Unknown0x0710;
/*0x0714*/
} EQINVSLOTMGR, *PEQINVSLOTMGR;


// onetimehero 09-17-03
// CContainerWnd
// Actual Size 0x17C in eqmac
typedef struct _EQCONTAINERWINDOW {
/*0x000*/ struct _CSIDLWND Wnd;
/*0x134*/ DWORD   something;     // dont know maybe type or a counter/ID?;
/*0x138*/ struct _ITEMINFO*   pIteminfo;     // Pointer to the contents of the container;// Matches the pointer in CHARINFO.Inventory/Bank/World
/*0x13c*/ struct _CSIDLWND*   pSlots[0x0a];
/*0x164*/ struct _CSIDLWND*   pCombine;
/*0x168*/ struct _CSIDLWND*   pDone;
/*0x16c*/ struct _CSIDLWND*   pIcon;
/*0x170*/ struct _CSIDLWND*   A_DragItem;
/*0x174*/ struct _CSIDLWND*   pLabel;
/*0x178*/ BYTE Unknown0x178[4];
/*0x17c*/
} EQCONTAINERWINDOW, *PEQCONTAINERWINDOW;

//pinstCContainerMgr CContainerMgr__CContainerMgr
// Actual Size 0x54  eqmac fixed
typedef struct _EQ_CONTAINERWND_MANAGER {
/*0x000*/   DWORD pvfTable; // NOT based on CXWnd.  Contains only destructor
/*0x004*/   PEQCONTAINERWINDOW pPCContainers[0x11];  // All open containers, including World, in order of opening...
/*0x048**/   PITEMINFO   pWorldItems;            // Pointer to the contents of the world   If NULL, world container isn't open;
/*0x04c*/   DWORD Unknown0x04c;            // in the future this is ID of container in zone, starts at one (zero?) and goes up.
/*0x050*/   DWORD dwTimeSpentWithWorldContainerOpen;  // Cumulative counter?
/*0x054*/
} EQ_CONTAINERWND_MANAGER, *PEQ_CONTAINERWND_MANAGER;




typedef struct _POINT3 {
    FLOAT X;
    FLOAT Y;
    FLOAT Z;
} POINT3, *PPOINT3;

// plazmic 08-17-03
// Map Window
typedef struct _MAPLABEL { // sizeof() = 0x28
/*0x00*/    struct _MAPLABEL *pNext;
/*0x04*/    struct _MAPLABEL *pPrev;
/*0x08*/    POINT3 Location;
/*0x14*/    ARGBCOLOR Color;
/*0x18*/    DWORD Size; //1-3;
/*0x1C*/    PCHAR Label;
/*0x20*/    DWORD Layer;    //0-3;
/*0x24*/    DWORD Width;
/*0x28*/    DWORD Height;
/*0x2C*/    DWORD unk_0x2c;
/*0x30*/    DWORD unk_0x30;
} MAPLABEL, *PMAPLABEL;

typedef struct _MAPLINE { // sizeof() = 0x28
    struct _MAPLINE *pNext;
    struct _MAPLINE *pPrev;
    POINT3 Start;
    POINT3 End;
    ARGBCOLOR Color;
    DWORD Layer;    //0-3;
} MAPLINE, *PMAPLINE;

typedef struct _EQLOOTWINDOW {
/*0x000*/ struct _CSIDLWND Wnd;
/*0x148*/ BYTE  Unknown0x148[0x08];
/*0x150*/ BYTE  Unknown0x150[0x84]; // This is an array of something
/*0x1d4*/ PITEMINFO   ItemDesc[0x1d]; //there can only be 29 items on a corpse since that equals 22 inv slots plus 8 bags...
/*0x24c*/
} EQLOOTWINDOW, *PEQLOOTWINDOW;

//Size: 0x2f8 (03/25/2004)
typedef struct _EQPETINFOWINDOW {
/*0x000*/ struct _CSIDLWND Wnd;
/*0x150*/ DWORD Unknown0x150;
/*0x154*/ DWORD Unknown0x154; // pet's spawnid# ??
/*0x158*/ DWORD Unknown0x158; // 1
/*0x15c*/ BYTE  Unknown0x15c[0x120];
/*0x18C*/ // unknown (one per buff)
/*0x204*/ // window (one per buff)
/*0x27c*/ int   Buff[0x1e]; // Spell ID# of each buff -- 30 total
/*0x2f4*/ DWORD Unknown0x2f4;  
} EQPETINFOWINDOW, *PEQPETINFOWINDOW;

typedef struct _EQTRADESKILLRECIPE {
/*0x00*/ DWORD Unknown0x00;
/*0x04*/ DWORD Trivial;
/*0x08*/ DWORD Unknown0x08;
/*0x0c*/ DWORD Unknown0x0c;
/*0x10*/ DWORD Unknown0x10;
/*0x14*/ CHAR  Name[0x40];
/*0x54*/ DWORD Unknown0x54;
/*0x58*/ DWORD Ingredient[0xa];  // ID# of ingredient(s)
/*0x80*/ DWORD IngredientIcon[0xa]; //Icon# of ingredient(s) (Note: 499 is blank)
} EQTRADESKILLRECIPE, *PEQTRADESKILLRECIPE;

//Size 0x3d8 (02/10/2004)
typedef struct _EQTRADESKILLWINDOW {
/*0x000*/   struct _CSIDLWND Wnd;
/*0x148*/ DWORD Unknown0x148[0x1b];  
/*0x1b4*/ PEQTRADESKILLRECIPE SearchResults[0x64]; 
/*0x344*/ DWORD	Unknown0x344;
/*0x348*/ DWORD Unknown0x348;
/*0x34c*/ DWORD Unknown0x34c;
/*0x350*/ PITEMINFO Item;
/*0x354*/ DWORD Unknown0x354;
/*0x358*/ PEQTRADESKILLRECIPE SelectedRecipe;
/*0x35c*/ DWORD Unknown0x35c;
/*0x360*/ DWORD SkillLevel;
/*0x364*/ DWORD Unknown0x364;
/*0x368*/ DWORD Unknown0x368;
/*0x36c*/ BYTE  Unknown0x36c[0x58];
/*0x3c4*/ DWORD Unknown0x3c4;
/*0x3c8*/ DWORD Unknown0x3c8;
/*0x3cc*/ BYTE  Unknonw0x3cc[0x8];
/*0x3d4*/ DWORD Unknown0x3d4;
/*0x3d8*/ DWORD Unknown0x3d8;
} EQTRADESKILLWINDOW, *PTRADESKILLWINDOW;

//Size: 0x234 (05/11/2004) 
//eqmac fixed (dec 2002 eqgame.exe)
typedef struct _EQRAIDWINDOW {
/*0x000*/ struct _CSIDLWND Wnd;
/*0x134*/ BYTE  Unknown0x134[0x20];
/*0x154*/ DWORD ClassColors[0x0f];
/*0x190*/
} EQRAIDWINDOW, *PEQRAIDWINDOW;

typedef struct _GUILDMEMBERINFO {
/*0x000*/ DWORD Unknown0x000; //pointer?
/*0x004*/ BYTE OnlineStatus; // 00=offline, 01=online
/*0x005*/ BYTE UnknownData0x005;
/*0x006*/ BYTE UnknownData0x006;
/*0x007*/ BYTE Unknown0x007;
/*0x008*/ BYTE Unknown0x008[0x8];
/*0x010*/ CHAR Name[0x40];
/*0x050*/ DWORD Level;
/*0x054*/ DWORD Class; 
/*0x058*/ DWORD Rank; //0=member, 1=officer, 2=leader
/*0x05c*/ FLOAT UnknownData0x05c;
/*0x060*/ CHAR PublicNote[0x80];
/*0x0e0*/ BYTE Unknown0x0e0[0x180];
/*0x260*/ WORD UnknownData0x260;
/*0x262*/ WORD UnknownData0x262;
/*0x264*/ WORD UnknownData0x264;
/*0x266*/ WORD UnknownData0x266;
} GUILDMEMBERINFO, *PGUILDMEMBERINFO;

//Size: 0x3d0 (02/18/2004)
typedef struct _EQGUILDWINDOW {
/*0x000*/ struct _CSIDLWND Wnd;
/*0x148*/ BYTE  Unknown0x148[0x4c];
/*0x194*/ BYTE Unknown0x194;
/*0x195*/ BYTE ShowOffline; // 01 = show offline box is checked
/*0x196*/ BYTE Unknown0x196[0x2];
/*0x198*/ struct _GUILDMEMBERINFO **pMember; // This is a pointer to the beginning of a list of pointers, 
	                                         // each representing one player in the guild.  The number of 
	                                         // pointers depends upon TotalMemberCount.
/*0x19c*/ DWORD TotalMemberCount;
/*0x1a0*/ DWORD Unknown0x1a0;  // 150?
/*0x1a4*/ DWORD Unknown0x1a4;  // 1?
/*0x1a8*/ DWORD TotalMemberCountAgain;
/*0x1ac*/ BYTE Unknown0x1ac[0x1c];
/*0x1c8*/ CHAR PersonalNotesFilePath[0x40];  // path to personal notes file
/*0x208*/ BYTE Unknown0x208[0x1c0]; // empty
/*0x3c8*/ DWORD Unknown0x3c8; // 1?
/*0x3cc*/ DWORD Unknown0x3cc; // some sort of bizaare pointer...
/*0x3d0*/
} EQGUILDWINDOW, *PEQGUILDWINDOW;

typedef struct _EQNOTESWINDOW {
/*0x000*/ struct _CSIDLWND Wnd;
/*0x148*/ BYTE  Unknown0x148[0x04];
/*0x14c*/ struct _CSIDLWND *pEditWnd;
} EQNOTESWINDOW, *PEQNOTESWINDOW;

// Lax 10-29-2003 
// Actual size 0x174 11-9-2003
typedef struct _EQITEMWINDOW 
{ 
/*0x000*/ struct _CSIDLWND Wnd; 
/*0x134*/ struct _CSIDLWND *DisplayWnd;  // 0x000
/*0x138*/ BYTE Unknown0x138[0xc]; //0x004
/*0x144*/ PCXSTR ItemInfo; // 0x010 says "Error: Item description not set" if its not set...
/*0x148*/ PCXSTR WindowTitle; // PCXSTR "item display" ??    _CSIDLWND ?? 
/*0x174*/ 
} EQITEMWINDOW, *PEQITEMWINDOW; 

// Actual Size 0x22c 10-9-2003
typedef struct _EQMAPWINDOW {
/*0x000*/ struct _CSIDLWND Wnd;
/*0x134*/ BYTE Unknown0x134[0x24];
/*0x158*/ CHAR shortzonename[0x20];
/*0x178*/ BYTE Unknown0x178[0x70];
/*0x1e8*/ PMAPLINE pLines;
/*0x1ec*/ PMAPLABEL pLabels;
/*0x1f0*/ BYTE Unknown0x1f8[0x3c];
/*0x22c*/
} EQMAPWINDOW, *PEQMAPWINDOW;

// onetimehero 09-17-03
// Individual Gems
// Actual size 0x188 10-9-2003
//fixed for eqmac dec 2002 version
typedef struct _EQCASTSPELLGEM {
/*0x000*/ struct _CSIDLWND Wnd;
/*0x134*/ BYTE Unknown0x134[0x34];
/*0x168*/ DWORD   spellicon;//same as in lucys db if this is equal to FFFFFFFF there is no spell memmed in this slot...
/*0x16c*/ DWORD   spellstate;// 1 = cast in progress or refreshtime not met or gem is empty 2 means we ducked or aborted cast, 0 means its ok to cast
/*0x170*/
} EQCASTSPELLGEM, *PEQCASTSPELLGEM;
// onetimehero 09-17-03
// Spell Window
//fixed for eqmac 2002 dec version of eqgame.exe
typedef struct _EQCASTSPELLWINDOW {
/*0x000*/ struct _CSIDLWND Wnd;
/*0x134*/ BYTE Unknown0x134[0x08];
/*0x13c*/  struct _EQCASTSPELLGEM   *SpellSlots[0x8];
/*0x140*/
} EQCASTSPELLWINDOW, *PEQCASTSPELLWINDOW;



// Actual size 0x1c4 10-9-2003
typedef struct _EQHOTBUTTONWINDOW {
/*0x000*/ struct _CSIDLWND Wnd;
/*0x148*/ BYTE Unknown0x138[0xc];
/*0x000*/ DWORD   HotButtonWndView;//0 to 9 for the different views
/*0x14c*/ struct _CSIDLWND   *HotButtons[0x0a];//these will change when you switch page...
/*0x174*/
} EQHOTBUTTONWINDOW, *PEQHOTBUTTONWINDOW;

typedef struct _LOOTCORPSE {
/*0x000*/   BYTE    Unknown0x000;   // 03 seems very common (for NPC anyway)
/*0x001*/   CHAR    Name[0x4b];
/*0x04c*/   FLOAT   Timer;  //Uncertain the equation used here, but fairly certain it's the timer
/*0x050*/   FLOAT   X;
/*0x054*/   BYTE    Unknown0x054[0x4];
/*0x058*/   FLOAT   Y;
/*0x05c*/   FLOAT   Z;
/*0x060*/   BYTE    Unknown0x060[0x24];
/*0x084*/   DWORD   Flags;
/*0x088*/   BYTE    Unknown0x088[0x4];
/*0x08c*/   DWORD   Unknown0x08c;   //256 seems very common
/*0x090*/
// I think there might be pointers at 0x0e0..but no clue what to
} LOOTCORPSE, *PLOOTCORPSE;

// size 0x180 3-10-2004
typedef struct _EQCOMPASSWINDOW {
/*0x000*/	struct _CSIDLWND Wnd;
/*0x134*/	struct _CSIDLWND *pStrip1;
/*0x14C*/	struct _CSIDLWND *pStrip2;
// in progress.
/*0x16C*/   BOOL DrawLine;
/*0x170*/   DWORD Unknown0x170;
/*0x174*/	DWORD LineRed;
/*0x178*/	DWORD LineGreen;
/*0x17C*/	DWORD LineBlue;
/*0x180*/
} EQCOMPASSWINDOW, *PEQCOMPASSWINDOW;

// used by options window
typedef struct _EQKBASSIGN
{
/*0x00*/	struct _CXSTR *pDescription;
/*0x04*/	DWORD nAssignmentNumber;
/*0x08*/
} EQKBASSIGN, *PEQKBASSIGN;

// size 0x904 3-10-2004
typedef struct _EQOPTIONSWINDOW {
/*0x000*/	struct _CSIDLWND Wnd;
/*0x134*/

/*0x264*/ struct _EQKBASSIGN Binds[0xA1];
/*0x508*/

/*0x904*/
} EQOPTIONSWINDOW, *PEQOPTIONSWINDOW;

// size 0x28 4-24-2004 Lax
typedef struct _EQGRAPHICSENGINE {
/*0x00*/ // Graphics file handler
/*0x04*/
} EQGRAPHICSENGINE, *PEQGRAPHICSENGINE;

typedef struct _CONTEXTMENU {
/*0x000*/	struct _CSIDLWND Wnd;
/*0x134*/	BYTE Unknown0x134;
/*0x135*/	BYTE Unknown0x135;
/*0x136*/	BYTE Unknown0x136;
/*0x137*/	BYTE Unknown0x137;
/*0x138*/	struct _CXWND *Unknown0x138;
/*0x13c*/	DWORD Unknown0x13c;
/*0x140*/	struct _CONTEXTMENU *Unknown0x140;
/*0x144*/	BYTE Unknown0x144;
/*0x145*/	BYTE Unknown0x145;
/*0x146*/	BYTE Unknown0x146;
/*0x147*/	BYTE Unknown0x147;
/*0x148*/	struct _CONTEXTMENU * Unknown0x148;
/*0x14c*/	DWORD Unknown0x14c;
/*0x150*/	struct _CONTEXTMENU * Unknown0x150;
/*0x154*/	DWORD Unknown0x154;
/*0x158*/	struct _CONTEXTMENU * Unknown0x158;
/*0x15c*/	DWORD Unknown0x15c;
/*0x160*/	struct _CONTEXTMENU * Unknown0x160;
/*0x164*/	DWORD Unknown0x164;
/*0x168*/	DWORD Unknown0x168;
/*0x16c*/	DWORD Unknown0x16c;
/*0x170*/	DWORD Unknown0x170;
/*0x174*/	DWORD Unknown0x174;
/*0x178*/	DWORD Unknown0x178;
/*0x17c*/	DWORD Unknown0x17c;
/*0x180*/
} CONTEXTMENU, *PCONTEXTMENU;
};


using namespace EQUIStructs;
