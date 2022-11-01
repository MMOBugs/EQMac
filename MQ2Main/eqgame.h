/* ***************************************************************************** 
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
#ifdef PRIVATE 
#include "eqgame-private.h" 
#endif 

//809478 ChatserverOffset
#define __ClientName                                      "eqgame" 
#define __ExpectedVersionDate                         "GetDataAddresses" 
#define __ExpectedVersionTime                         "one" 
#define __ActualVersionDate                                0x61A324
#define __ActualVersionTime                                0x61A33C

#define __ClientOverride                       0 
#define __MacroQuestWinClassName                 "__MacroQuestTray" 
#define __MacroQuestWinName                           "MacroQuest" 

// Memory Protection 
#define __MemChecker0                                      0x555243//*
#define __MemChecker1                                      0x0//*
#define __MemChecker2                                      0x0
#define __EncryptPad0                                      0x623188
#define __EncryptPad1                                      0x0
#define __EncryptPad2                                      0x0
#define __EncryptPad4                                      0x62698C

#define DI8__Main                                          0x8092DC
#define DI8__Keyboard                                      0x8092E0
#define DI8__Mouse                                         0x8092E4

#define __LastTell                                         0x7CE45C
#define __Guilds                                           0x7F9C94
#define __Mouse                                            0x8092E8
#define __Attack                                           0x7F6FFE
#define __InChatMode                                       0x79856C
#define __gWorld                                           0x7952FC
#define __GroupCount                                       0x7912B0
#define __CommandList                                      0x609AF8
#define __DoAbilityList                                    0x7D0264
#define __DoAbilityAvailable                               0x7CD7E0
#define __ServerHost                                       0x798424
//not implemented in eqmac get it from chatserver instead
//#define __ServerName                                       0x8072C0
#define __HWnd                                             0x798540
#define __Clicks                                           0x798614
#define __ScreenX                                          0x798548
#define __ScreenY                                          0x79854A
#define __ScreenMode                                       0x63B918
#define __MouseLook                                        0x7985EA
#define __EQP_IDArray                                      0x78C47C
//no map in eqmac...
#define __CurrentMapLabel                                  0x0
#define __BindList                                         0x611220//0x6F9C10
#define __RangeAttackReady                                 0x7CD844
#define __AltTimerReady                                    0x7CD846
#define __Socials                                          0x7D02F0
#define __HotkeyPage                                       0x7F69F6
#define __CurrentSocial                                    0x605438
#define __GroupLeader                                      0x79140C
#define __SkillDict                                        0x7F7AEC
#define __DrawHandler                                      0x630398//g_SuiteTextureLoader
#define __FriendsList                                      0x7CF2DC
#define __IgnoreList                                       0x7CFA5C
#define __NetStatusToggle                                  0x7985EC
#define __ShowNames                                        0x7D01E4
#define __PCNames                                          0x798AF4
#define __RunWalkState									   0x63D8E0
//// 
//Section 1: Vital Offsets 
//// 
#define pinstCSidlManager                                  0x809DBC

#define pinstCDisplay                                      0x7F9510
#define pinstCEverQuest                                    0x809478
#define pinstPCData                                        0x7F94E8
#define pinstCharData                                      0x7F94E8
#define pinstCharSpawn                                     0x7F94E0
#define pinstControlledPlayer                              0x7F94E0
#define pinstSpawnList                                     0x7F9498
#define pinstLocalPlayer                                   0x7F94CC
#define pinstWorldData                                     0x7F9494
#define pinstSpellManager                                  0x805CB0
#define pinstTradeTarget                                   0x7F94C8
#define pinstActiveMerchant                                0x7F94F8
#define pinstActiveBanker                                  0x7F94FC
#define pinstActiveCorpse                                  0x7F9500
#define pinstActiveGMaster                                 0x7F9504
//dump this and get it from invslot manager instead
//#define pinstSelectedItem                                  0x897E68
#define pinstGroup                                         0x7913F8
#define pinstTarget                                        0x7F94EC
//ok its actually the footer but we can pPrev back through it
#define pinstSwitchManager                                 0x7F94B8
#define pinstEQItemList                                    0x7F949C
//no such thing in eqmac
#define pinstSpellSets                                     0x0
#define instEQZoneInfo                                     0x798784
#define pinstCXWndManager                                  0x809DB4
//do this one last
#define instKeypressHandler                                0x7CD84C
#define pinstStringTable                                   0x7F9490
#define pinstAltAdvManager                                 0x63D724
#define instCRaid                                          0x7914D0

//// 
//Section 2:  UI Related Offsets 
//// 
//#define pinstCTextOverlay                                  0x0
#define pinstCharacterSelect                               0x63D5D8
#define pinstCFacePick                                     0x63D5DC
// removed 4-14 exe #define pinstCTextMessageWnd                                
#define pinstCNoteWnd                                      0x63D5E4
#define pinstCHelpWnd                                      0x63D5E8
#define pinstCBookWnd                                      0x63D5EC
#define pinstCPetInfoWnd                                   0x63D5F0
#define pinstCTrainWnd                                     0x63D5F4
#define pinstCSkillsWnd                                    0x63D5F8
#define pinstCSkillsSelectWnd                              0x63D5FC
#define pinstCCombatSkillSelectWnd                         0x0
#define pinstCFriendsWnd                                   0x63D600
#define pinstCAAWnd                                        0x63D604
#define pinstCGroupSearchFiltersWnd                        0x0
#define pinstCLoadskinWnd                                  0x63D60C
#define pinstCAlarmWnd                                     0x63D610
#define pinstCMusicPlayerWnd                               0x63D614
#define pinstCRaidWnd                                      0x63D618
#define pinstCRaidOptionsWnd                               0x63D61C
#define pinstCBreathWnd                                    0x63D620
#define pinstCMapViewWnd                                   0x0
#define pinstCMapToolbarWnd                                0x0
#define pinstCEditLabelWnd                                 0x0
#define pinstCTargetWnd                                    0x63D624
#define pinstCHotButtonWnd                                 0x63D628
#define pinstCColorPickerWnd                               0x63D62C
#define pinstCPlayerWnd                                    0x63D630
#define pinstCOptionsWnd                                   0x63D634
#define pinstCBuffWindowNORMAL                             0x63D638
#define pinstCBuffWindowSHORT                              0x0
#define pinstCharacterCreation                             0x63D63C
#define pinstCCursorAttachment                             0x63D640
#define pinstCCastingWnd                                   0x63D644
#define pinstCCastSpellWnd                                 0x63D648
#define pinstCSpellBookWnd                                 0x63D64C
#define pinstCInventoryWnd                                 0x63D650
#define pinstCBankWnd                                      0x63D654
#define pinstCQuantityWnd                                  0x63D658
#define pinstCLootWnd                                      0x63D65C
#define pinstCActionsWnd                                   0x63D660
#define pinstCCombatAbilityWnd                             0x0
#define pinstCMerchantWnd                                  0x63D664
#define pinstCTradeWnd                                     0x63D668
#define pinstCSelectorWnd                                  0x63D66C
#define pinstCBazaarWnd                                    0x63D670
#define pinstCBazaarSearchWnd                              0x63D674
#define pinstCGiveWnd                                      0x63D678
#define pinstCTrackingWnd                                  0x63D67C
#define pinstCInspectWnd                                   0x63D680
#define pinstCSocialEditWnd                                0x63D684
#define pinstCFeedbackWnd                                  0x63D688
#define pinstCBugReportWnd                                 0x63D68C
#define pinstCVideoModesWnd                                0x63D690
#define pinstCTextEntryWnd                                 0x63D694
#define pinstCFileSelectionWnd                             0x63D698
#define pinstCCompassWnd                                   0x63D69C
#define pinstCPlayerNotesWnd                               0x63D6A0
#define pinstCGemsGameWnd                                  0x63D6A4
#define pinstCTimeLeftWnd                                  0x63D6A8
#define pinstCPetitionQWnd                                 0x63D6AC
#define pinstCSoulmarkWnd                                  0x63D6B0
#define pinstCStoryWnd                                     0x0
#define pinstCJournalTextWnd                               0x0
#define pinstCJournalCatWnd                                0x0
#define pinstCBodyTintWnd                                  0x0
#define pinstCInvSlotMgr                                   0x63D6B4
#define pinstCContainerMgr                                 0x63D6B8
#define pinstCAdventureLeaderboardWnd                      0x0
#define pinstCAdventureMerchantWnd                         0x0
#define pinstCAdventureRequestWnd                          0x0
#define pinstCAdventureStatsWnd                            0x0
#define pinstCChatManager                                  0x63D5D0
#define pinstCDynamicZoneWnd                               0x0
#define pinstCFindLocationWnd                              0x0
#define pinstCGroupSearchWnd                               0x0
#define pinstCGroupWnd                                     0x63D608
#define pinstCGuildMgmtWnd                                 0x0
#define pinstCItemDisplayManager                           0x63D5E0
#define pinstCLeadershipWnd                                0x0
#define pinstCPopupWndManager                              0x0
#define pinstCSystemInfoDialogBox                          0x0
#define pinstCTargetOfTargetWnd                            0x0
#define pinstCTipWndOFDAY                                  0x0
#define pinstCTipWndCONTEXT                                0x0
#define pinstCTradeskillWnd                                0x0
#define pinstCTributeBenefitWnd                            0x0
#define pinstCTributeMasterWnd                             0x0
#define pinstCContextMenuManager                           0x63D5CC
// unknown window added 4-14 exe 0x79A234 


//// 
// Section 3: Miscellaneous Offsets 
//// 
#define DrawNetStatus                                      0x54D3AE
#define CrashDetected                                      0x558AFF
#define __ProcessGameEvents                                0x52437F
#define __ConvertItemTags                                  0x502322
#define __SendMessage                                      0x54E51A
#define __NewUIINI                                         0x437481
#define __ExecuteCmd                                       0x54050C
#define __GetGaugeValueFromEQ                              0x43600D
#define __get_melee_range                                  0x4F3898
#define __CastRay                                          0x4F20DB
#define __LoadStringFromUIIniFile						   0x437542
#define __SaveToUIIniFile								   0x4374FA



// EQ_LoadingS 
#define EQ_LoadingS__WriteTextHD                           0x452DE9


//// 
// Section 4: Function Offsets 
//// 
// CEverQuest 
#define CEverQuest__dsp_chat                               0x537F99
#define CEverQuest__ClickedPlayer                          0x547182
#define CEverQuest__EnterZone                              0x53D2C4
#define CEverQuest__GetBodyTypeDesc                        0x52D856
#define CEverQuest__GetClassDesc                           0x52D5F1
#define CEverQuest__GetClassThreeLetterCode                0x42534C
#define CEverQuest__GetDeityDesc                           0x52EA51
#define CEverQuest__GetRaceDesc                            0x52EA51
#define CEverQuest__GetTitleDesc                           0x52EB69
#define CEverQuest__InterpretCmd                           0x54572F
#define CEverQuest__LeftClickedOnPlayer                    0x53271E
#define CEverQuest__RightClickedOnPlayer                   0x532949
//#define CEverQuest__SetGameState                           0x481038
#define CEverQuest__DropHeldItemOnGround                   0x530D7E

// StringTable 
#define StringTable__getString                             0x550EFE

// AltAdvManager 
#define AltAdvManager__IsAbilityReady                      0x4B755B

// CXWndManager 
#define CXWndManager__RemoveWnd                            0x59E610
#define CXWndManager__GetKeyboardFlags                     0x59E6F0
#define CXWndManager__HandleKeyboardMsg                    0x59E780
#define CXWndManager__DrawWindows                          0x59E000
#define CXWndManager__DrawCursor                           0x59E320
#define CXWndManager__GetFirstChildWnd                     0x5A0CC0

// KeyPressHandler 
#define KeypressHandler__HandleKeyDown                     0x5257FA
#define KeypressHandler__HandleKeyUp                       0x52462A
#define KeypressHandler__AttachKeyToEqCommand              0x0
#define KeypressHandler__AttachAltKeyToEqCommand           0x0
#define KeypressHandler__SaveKeymapping                    0x0
#define KeypressHandler__ClearCommandStateArray            0x0

// EQ_Character 
//get it directly from charinfo... 
//movsx   eax, byte ptr [eax+2BD4h] in testeqgame.exe
#define EQ_Character__Max_Endurance                        0x0
#define EQ_Character__Max_Mana                             0x4B9483
#define EQ_Character__Max_HP                               0x4B92EC
#define EQ_Character__Cur_HP                               0x4B912F
#define EQ_Character__GetFocusCastingTimeModifier          0x4C4071
#define EQ_Character__GetAACastingTimeModifier             0x4C5FB2
#define EQ_Character__CastSpell                            0x4C483B
#define EQ_Character__GetAbility                           0x4C3FB0

// EQPlayer 
#define EQPlayer__EQPlayer                                 0x506802
#define EQPlayer__dEQPlayer                                0x50723D
#define EQPlayer__DoAttack                                 0x50A0F8
#define EQPlayer__ChangeBoneStringSprite                   0x4B0AA8
#define EQPlayer__SetNameSpriteState                       0x4B0BD9
#define EQPlayer__SetNameSpriteTint                        0x4B114D
#define EQPlayer__GetPlayerFromName						   0x5081DB
// EQSwitch
#define EQSwitch__UseSwitch								   0x521D91
// CXStr 
// WARNING:  Be sure that none of these offsets are identical! 
// 
// Note:  dCXStr, CXStr1, & CXStr3 can be found in the 'BookWindow' constructor. 
#define CXStr__CXStr                                       0x40221D
#define CXStr__CXStr1                                      0x408BA8
#define CXStr__CXStr3                                      0x575F30
#define CXStr__dCXStr                                      0x402247
#define CXStr__operator_plus_equal1                        0x577310
#define CXStr__operator_equal1                             0x576190

// CChatWindow 
#define CChatWindow__CChatWindow                           0x4137C9

// CChatManager 
#define CChatManager__GetRGBAFromIndex                     0x4116B8
#define CChatManager__InitContextMenu                      0x41179C

// CInvSlotMgr 
#define CInvSlotMgr__FindInvSlot                           0x423010
#define CInvSlotMgr__MoveItem                              0x422B1C

// CItemDisplayWnd 
#define CItemDisplayWnd__SetItem                           0x423640
#define CItemDisplayWnd__SetSpell                          0x425957

// CHotButtonWnd 
#define CHotButtonWnd__DoHotButton                         0x4209BD

// CLabel 
#define CLabel__Draw                                       0x5A8340

// CDisplay 
#define CDisplay__ReloadUI                                 0x4A1465
#define CDisplay__CleanGameUI                              0x4A6EBC
#define CDisplay__GetClickedActor                          0x4B008A
#define CDisplay__WriteTextHD2                             0x4AA5AA
#define CDisplay__GetWorldFilePath                         0x4A7D09
#define CDisplay__GetUserDefinedColor                      0x4AA2C1

#define CTextureFont__DrawWrappedText                      0x5A4970

// EQ_Item 
//doesnt exist in eqmac
//#define EQ_Item__GetItemLinkHash                           0x0
#define EQ_Item__CanDrop                                   0x4EF773


// CBazaarSearchWnd 
#define CBazaarSearchWnd__HandleBazaarMsg                  0x4060B5

// CMerchantWnd 
#define CMerchantWnd__SelectBuySellSlot                    0x427614
#define CMerchantWnd__RequestBuyItem                       0x427902
#define CMerchantWnd__RequestSellItem                      0x427C83
#define CMerchantWnd__DisplayBuyOrSellPrice                0x427735


// EQItemList 
#define EQItemList__EQItemList							   0x4EED9D
#define EQItemList__dEQItemList                            0x4EEE66

// EQ_PC 
#define EQ_PC__DestroyHeldItemOrMoney                      0x4D0D88

// CContainerWnd 
#define CContainerWnd__HandleCombine                       0x416E5B
#define CContainerWnd__vftable                             0x5E4920

// CSidlScreenWnd 
#define CSidlScreenWnd__CSidlScreenWnd1                    0x56E1E0
#define CSidlScreenWnd__dCSidlScreenWnd                    0x56E680
#define CSidlScreenWnd__CreateChildrenFromSidl             0x56F4F0
#define CSidlScreenWnd__WndNotification                    0x56E920
#define CSidlScreenWnd__CalculateHSBRange                  0x56EA50
#define CSidlScreenWnd__CalculateVSBRange                  0x56E9A0
#define CSidlScreenWnd__ConvertToRes                       0x5702A0
#define CSidlScreenWnd__CSidlScreenWnd2                    0x56E2B0
#define CSidlScreenWnd__DrawSidlPiece                      0x56ED00
#define CSidlScreenWnd__EnableIniStorage                   0x570250
#define CSidlScreenWnd__GetSidlPiece                       0x56EFB0
#define CSidlScreenWnd__Init1                              0x56E510
#define CSidlScreenWnd__LoadIniInfo                        0x56F5A0
#define CSidlScreenWnd__LoadIniListWnd                     0x570440
#define CSidlScreenWnd__LoadSidlScreen                     0x56E810
#define CSidlScreenWnd__SetScreen                          0x56E7A0
#define CSidlScreenWnd__StoreIniInfo                       0x56FE10

// CSidlManager 
#define CSidlManager__FindScreenPieceTemplate1             0x59B410

// CXMLDataManager 
#define CXMLDataManager__GetXMLData                        0x5A9720

// CXMLSOMDocumentBase 
#define CXMLSOMDocumentBase__XMLRead                       0x58DA10

// CXRect 
#define CXRect__CenterPoint                                0x404D76
//#define CXRect__CXRect1									   0x57ABC0//void
// CXWnd
#define CXWnd__CXWnd									   0x570E20
#define CXWnd__BringToTop                                  0x573A80
#define CXWnd__Center                                      0x574A80
#define CXWnd__ClrFocus                                    0x5722C0
#define CXWnd__DoAllDrawing                                0x573FB0
#define CXWnd__DrawChildren                                0x574330
#define CXWnd__DrawColoredRect                             0x574380
#define CXWnd__DrawColoredRect1							   0x435804
#define CXWnd__DrawTooltipAtPoint                          0x574800
#define CXWnd__GetBorderFrame                              0x575020
#define CXWnd__GetChildWndAt                               0x573C80

#define CXWnd__SetTooltip								   0x408365

#define CXWnd__GetClientClipRect                           0x574C10
#define CXWnd__GetFirstChildWnd                            0x573D10
#define CXWnd__GetNextChildWnd                             0x573C60
#define CXWnd__GetNextSib                                  0x573D30
#define CXWnd__GetScreenClipRect                           0x574D30
#define CXWnd__GetScreenRect                               0x5751C0
#define CXWnd__GetTooltipRect                              0x5746F0
#define CXWnd__GetWindowTextA                              0x4082F6
#define CXWnd__GetXMLTooltip                               0x5757F0
#define CXWnd__IsActive                                    0x574E40
#define CXWnd__IsDescendantOf                              0x574E50
#define CXWnd__IsReallyVisible                             0x573C30
#define CXWnd__IsType                                      0x571300
#define CXWnd__Move                                        0x573560
#define CXWnd__Move1                                       0x573600
#define CXWnd__ProcessTransition                           0x573780
#define CXWnd__Refade                                      0x573550
#define CXWnd__Resize                                      0x5752A0
#define CXWnd__Right                                       0x5C4000
#define CXWnd__SetFirstChildPointer                        0x5756B0
#define CXWnd__SetFocus                                    0x572290
#define CXWnd__SetKeyTooltip                               0x5756F0
#define CXWnd__SetMouseOver                                0x5756D0
#define CXWnd__SetNextSibPointer                           0x5756C0
#define CXWnd__StartFade                                   0x573AF0
#define CXWnd__Show										   0x572310
// CSliderWnd 
#define CSliderWnd__GetValue                               0x5A6D80
#define CSliderWnd__SetValue                               0x5A6C70
#define CSliderWnd__UpdateThumb                            0x5A6D00

// CEditBaseWnd 
#define CEditBaseWnd__SetMaxChars                          0x40401C
#define CEditBaseWnd__SetSel                               0x5A74F0

// CComboWnd 
#define CComboWnd__DeleteAll                               0x5A18E0
#define CComboWnd__Draw                                    0x5A1AD0
#define CComboWnd__GetButtonRect                           0x5A1910
#define CComboWnd__GetCurChoice                            0x5A18A0
#define CComboWnd__GetListRect                             0x5A16C0
#define CComboWnd__GetTextRect                             0x5A1970
#define CComboWnd__InsertChoice                            0x5A1750
#define CComboWnd__SetColors                               0x5A1720
#define CComboWnd__SetChoice                               0x5A1860

// CListWnd 
#define CListWnd__AddColumn                                0x579FF0
#define CListWnd__AddColumn1                               0x57A070
#define CListWnd__AddLine                                  0x579570
#define CListWnd__AddString                                0x5797A0
#define CListWnd__CalculateFirstVisibleLine                0x57BA10
#define CListWnd__CalculateVSBRange                        0x57B8F0
#define CListWnd__ClearAllSel                              0x579CC0
#define CListWnd__CloseAndUpdateEditWindow                 0x57C530
#define CListWnd__Compare                                  0x57CD10
#define CListWnd__Draw                                     0x57B370
#define CListWnd__DrawColumnSeparators                     0x57ABD0
#define CListWnd__DrawHeader                               0x57AD80
#define CListWnd__DrawItem                                 0x57A2E0
#define CListWnd__DrawLine                                 0x57A830
#define CListWnd__DrawSeparator                            0x57ACA0
#define CListWnd__EnsureVisible                            0x57BA60
#define CListWnd__ExtendSel                                0x579BE0
#define CListWnd__GetColumnFlags                           0x579030
#define CListWnd__GetColumnJustification                   0x579270
#define CListWnd__GetColumnMinWidth                        0x579200
#define CListWnd__GetColumnWidth                           0x579090
#define CListWnd__GetCurSel                                0x578E40
#define CListWnd__GetHeaderRect                            0x57CF00
#define CListWnd__GetItemAtPoint                           0x57BD00
#define CListWnd__GetItemAtPoint1                          0x57BD70
#define CListWnd__GetItemData                              0x578E80
#define CListWnd__GetItemHeight                            0x57B6D0
#define CListWnd__GetItemIcon                              0x578F70
#define CListWnd__GetItemRect                              0x57BB40
#define CListWnd__GetItemText                              0x578ED0
#define CListWnd__GetSeparatorRect                         0x57C7D0
#define CListWnd__IsLineEnabled                            0x579F40
//#define CListWnd__RemoveLine                               0x568D50
#define CListWnd__SetColors                                0x57C7B0
#define CListWnd__SetColumnWidth                           0x579120
#define CListWnd__SetColumnJustification                   0x5792D0
#define CListWnd__SetCurSel                                0x579AF0
//#define CListWnd__SetItemColor                             0x5686C0
#define CListWnd__SetItemData                              0x579D70
#define CListWnd__SetItemText                              0x579DC0
#define CListWnd__ShiftColumnSeparator                     0x579170
#define CListWnd__Sort                                     0x57CB00
#define CListWnd__ToggleSel                                0x579B10
#define CListWnd__WndNotification                          0x57D090
#define CListWnd__CListWnd								   0x578A60
// CEditWnd 
#define CEditWnd__DrawCaret                                0x5A2F40
//#define CEditWnd__GetCharIndexPt                           0x57B8E0
//#define CEditWnd__GetDisplayString                         0x57ABF0
//#define CEditWnd__GetHorzOffset                            0x57AE60
//#define CEditWnd__GetLineForPrintableChar                  0x57B380
//#define CEditWnd__GetSelStartPt                            0x57BB20
//#define CEditWnd__GetSTMLSafeText                          0x57B040
//#define CEditWnd__PointFromPrintableChar                   0x57B490
//#define CEditWnd__SelectableCharFromPoint                  0x57B610
//#define CEditWnd__SetEditable                              0x57B010

// CGaugeWnd 
//#define CGaugeWnd__CalcFillRect                            0x4DBBDA
//#define CGaugeWnd__CalcLinesFillRect                       0x4DBC36
#define CGaugeWnd__Draw                                    0x5C2080

// CStmlWnd 
#define CStmlWnd__AppendSTML                               0x587090
//#define CStmlWnd__CalculateHSBRange                        0x55BCB0
//#define CStmlWnd__CalculateVSBRange                        0x55BC50
//#define CStmlWnd__CanBreakAtCharacter                      0x55BDF0
//#define CStmlWnd__CanGoBackward                            0x55BE70
//#define CStmlWnd__FastForwardToEndOfTag                    0x55CBC0
//#define CStmlWnd__GetNextChar                              0x55C2D0
//#define CStmlWnd__GetNextTagPiece                          0x55C9C0
//#define CStmlWnd__GetSTMLText                              0x4CF36F
//#define CStmlWnd__GetThisChar                              0x55BB10
//#define CStmlWnd__GetVisiableText                          0x55E390
//#define CStmlWnd__InitializeWindowVariables                0x560190
//#define CStmlWnd__MakeStmlColorTag                         0x55B2C0
//#define CStmlWnd__MakeWndNotificationTag                   0x55B360
#define CStmlWnd__StripFirstSTMLLines                      0x586D70
//#define CStmlWnd__UpdateHistoryString                      0x55E7D0

// CTabWnd 
#define CTabWnd__Draw                                      0x593D60
//#define CTabWnd__DrawCurrentPage                           0x5797D0
//#define CTabWnd__DrawTab                                   0x579550
//#define CTabWnd__GetCurrentPage                            0x579100
//#define CTabWnd__GetCurrentTabIndex                        0x578E50
//#define CTabWnd__GetNumTabs                                0x578F50
//#define CTabWnd__GetPageClientRect                         0x578E60
//#define CTabWnd__GetPageFromTabIndex                       0x578F80
//#define CTabWnd__GetPageInnerRect                          0x578EC0
//#define CTabWnd__GetTabInnerRect                           0x579210
//#define CTabWnd__GetTabRect                                0x579110
//#define CTabWnd__IndexInBounds                             0x578F60
//#define CTabWnd__InsertPage                                0x579BD0
//#define CTabWnd__SetPage                                   0x5792B0
//#define CTabWnd__SetPageRect                               0x5793C0
//#define CTabWnd__UpdatePage                                0x579470

// CTextOverlay doent exist in eqmac 
//#define CTextOverlay__DisplayText                          0x40159A
#define CSidlScreenWnd__GetChildItem						 0x570320
/* 
CListWnd__GetCurCol 
*/
#define CContextMenuManager__GetDefaultMenuIndex			 0x4137C2
#define CContextMenuManager__AddMenu						 0x417ED4
#define CContextMenuManager__CreateDefaultMenu				 0x41837E
#define CContextMenu__CContextMenu							 0x417785
#define CContextMenu__dCContextMenu							 0x417905
#define CContextMenu__AddMenuItem							 0x417910
#define CContextMenu__AddSeparator							 0x417A41
#define CContextMenu__RemoveAllMenuItems					 0x417A7F
#define CContextMenu__Activate								 0x417BF1
#define CContextMenu__CheckMenuItem							 0x417AE8
#define CContextMenuManager__PopupMenu						 0x41822D
#define CContextMenuManager__RemoveMenu						 0x417E1B
#define CSpellBookWnd__StartSpellMemorization				 0x434A05
#define CCastSpellWnd__RefreshSpellGemButtons				 0x40A7D3
#define CSpellBookWnd__FinishMemorizing						 0x434B38
#define CSpellBookWnd__GetSpellMemTicksLeft					 0x434C05
#define CCastSpellWnd__WndNotification						 0x40A32A
#define CSpellGemWnd__HandleRButtonUp						 0x5A67B0
#define CXWndManager__GetFont1								 0x538EAA
#define CEverQuest__Camp									 0x530C7B
#define CampingInProgress									 0x798738
//these added to get mapwindow to work
#define CTextureFont__GetHeight								 0x5A4930
#define CTextureFont__GetTextExtent							 0x5A48B0
#define EQUtil__build_token_string_PARAM					 0x4EF2D8
#define CXWnd__DrawLasso									 0x5741B0
#define CXRect__operator_and								 0x437651
#define CButtonWnd__SetCheck								 0x595790
#define CXWnd__GetRelativeRect								 0x5750C0
#define EQWorldData__GetGeometryNameFromIndex				 0x523F73
#define CXStr__ConvertToInt									 0x577FE0
#define CXStr__FreeRep										 0x575DC0
#define EQWorldData__IsNewbieZone							 0x523F15
#define CXWnd__OnProcessFrame								 0x573490
//these added to get maptoolbar window to work
#define CColorPickerWnd__Activate							 0x414F2A
#define CConfirmationDialog__Activate						 0x415A80
#define CEverQuest__dsp_chat1								 0x5380FD
#define CXStr__operator_char_p								 0x577E80
//need a detour on this to add a couple map confirmations...
#define CConfirmationDialog__ProcessYes						 0x415C27
//and this to add our hotkey
#define COptionsWnd__AddKeyboardAssignment					 0x42B21D
#define CXWndManager__UpdateChildAndSiblingInfo				 0x59E720
#define CDisplay__ClearScreen								 0x4ADF0C
#define CDisplay__InitDDraw									 0x4A5171
#define CDisplay__ChangeVideoMode							 0x4ACC0F
#define CDisplay__CleanUpDDraw								 0x4A954B
#define CDisplay__RealRender_World							 0x4AAA1B
#define CDisplay__DDrawUpdateDisplay						 0x4AC9ED
#define CDisplay__ResetRenderWindow							 0x49F5D8
#define CDisplay__StopWorldDisplay							 0x4A91DC
#define CDisplay__is_3dON									 0x4A3CA8
#define CSpellBookWnd__Activate								 0x43441F

//fix loot
#define CEverQuest__HandleWorldMessage						 0x4E829F
#define CLootWnd__AddEquipmentToLootArray					 0x4267B8

#define CXWnd__sm_pMgr										 0x809C34
#define CChatWindow__SetChatFont							 0x414B55 
#define CChatWindow__Clear									 0x414C1E
/**/ 
