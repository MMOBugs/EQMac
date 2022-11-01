
        TITLE CMapViewWnd.asm
        .386P

include listing.inc
.model   flat
INCLUDELIB MQ2Main.lib

PUBLIC _CMapViewWnd_StoreIniInfo
PUBLIC _CMapViewWnd_LoadIniInfo
PUBLIC _MapViewMap_Clear
PUBLIC _MapViewMap_ClearActiveLayer
PUBLIC _MapViewMap_SetCurrentColor
PUBLIC _MapViewMap_SetMarkedLine
PUBLIC _MapViewMap_AddLabel
PUBLIC _MapViewMap_SetMarkedLineColor
PUBLIC new
PUBLIC operator__delete
PUBLIC _MapViewMap_RecalcLabelExtents
PUBLIC _MapViewMap_StartLine
PUBLIC _MapViewMap_EndLine
PUBLIC _MapViewMap_AddPoint
PUBLIC _MapViewMap_RemoveLine
PUBLIC _MapViewMap_RemoveLine_0
PUBLIC _MapViewMap_RemoveLabel_0
PUBLIC _MapViewMap_MoveLabel
PUBLIC _MapViewMap_Save
PUBLIC _MapViewMap_JoinLinesAtIntersect
PUBLIC _MapViewMap_GetCurrentColor
PUBLIC _MapViewMap_GetMarkedLineColor
PUBLIC _CMapViewWnd_ActivateAutoMapping
PUBLIC _CMapViewWnd_DeactivateAutoMapping
PUBLIC _CMapViewWnd_IsMappingEnabled
PUBLIC _CMapViewWnd_HandleLButtonDown
PUBLIC _CMapViewWnd_HandleLButtonUp
PUBLIC _CMapViewWnd_HandleLButtonHeld
PUBLIC _CMapViewWnd_HandleLButtonUpAfterHeld
PUBLIC _CMapViewWnd_HandleWheelMove
PUBLIC _CMapViewWnd_WndNotification
PUBLIC _CMapViewWnd_Deactivate
PUBLIC _CMapViewWnd_Activate
PUBLIC _CMapViewWnd_OnProcessFrame
PUBLIC _CMapViewWnd_PostDraw
PUBLIC _CMapViewWnd_CMapViewWnd
PUBLIC __MapViewMap__SetZoneExtents
PUBLIC __MapViewMap__MapViewMap
PUBLIC __MapViewMap__dMapViewMap
PUBLIC __MapViewMap__SetZoom
PUBLIC __CMapViewWnd__Init
PUBLIC __MapViewMap__GetMinZ
PUBLIC __MapViewMap__GetMaxZ
PUBLIC __CMapViewWnd__SetCurrentZone
EXTRN _g_pMapToolbarWnd:DWORD
EXTRN _CurrentMapLabel:DWORD
EXTRN ?SaveToUIIniFile@MQ2Globals@@YAXPAD00@Z:PROC ; __SaveToUIIniFile
EXTRN ?LoadStringFromUIIniFile@MQ2Globals@@YAXPAD000H@Z:PROC ; __LoadStringFromUIIniFile
EXTRN ?_NewUIINI@MQ2Globals@@YAPADXZ:PROC ; __NewUIINI
EXTRN ?operatorp@CXStr@EQClasses@@QBEXXZ:PROC ; CXStr__operator_char_p
EXTRN ?LoadIniInfo@CSidlScreenWnd@EQClasses@@QAEXXZ:PROC ; CSidlScreenWnd__LoadIniInfo
EXTRN ?StoreIniInfo@CSidlScreenWnd@EQClasses@@QAEXXZ:PROC ; CSidlScreenWnd__StoreIniInfo
EXTRN ?dsp_chat@CEverQuest@EQClasses@@QAEXPBD@Z:PROC ; CEverQuest__dsp_chat1
EXTRN ?getString@StringTable@EQClasses@@QAEPADKPA_N@Z:PROC ; StringTable__getString
EXTRN ??0CXStr@EQClasses@@QAE@PBD@Z:PROC ; CXStr__CXStr3
EXTRN ?DrawWrappedText@CTextureFont@EQClasses@@QBEHVCXStr@2@HHHVCXRect@2@KGH@Z:PROC
EXTRN ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z:PROC ; CSidlScreenWnd__GetChildItem
EXTRN ?CreateChildrenFromSidl@CSidlScreenWnd@EQClasses@@QAEXXZ:PROC ; CSidlScreenWnd__CreateChildrenFromSidl
EXTRN ??0CSidlScreenWnd@EQClasses@@QAE@PAVCXWnd@1@VCXStr@1@HPAD@Z:PROC ; CSidlScreenWnd__CSidlScreenWnd1
EXTRN ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z:PROC ; CButtonWnd__SetCheck
EXTRN ?GetRelativeRect@CXWnd@EQClasses@@QBE?AVCXRect@2@XZ:PROC ; CXWnd__GetRelativeRect
EXTRN ?GetKeyboardFlags@CXWndManager@EQClasses@@QBEIXZ:PROC ; CXWndManager__GetKeyboardFlags
EXTRN ?WndNotification@CSidlScreenWnd@EQClasses@@QAEHPAVCXWnd@2@IPAX@Z:PROC ; CSidlScreenWnd__WndNotification
EXTRN ?FreeRep@CXStr@EQClasses@@QAEXPAUCStrRep@2@@Z:PROC ; CXStr__FreeRep
EXTRN ?ConvertToInt@CXStr@EQClasses@@QAEHXZ:PROC ; CXStr__ConvertToInt
EXTRN ?GetGeometryNameFromIndex@EQWorldData@EQClasses@@QBE_NW4EQZoneIndex@2@PAD@Z:PROC ; EQWorldData__GetGeometryNameFromIndex
EXTRN ?Show@CXWnd@EQClasses@@QAEH_N0@Z:PROC ; CXWnd__Show
EXTRN ?IsNewbieZone@EQWorldData@EQClasses@@QBE_NW4EQZoneIndex@2@@Z:PROC ; EQWorldData__IsNewbieZone
EXTRN __ftol:PROC
EXTRN __EH_prolog:PROC
EXTRN ___CxxFrameHandler:PROC
EXTRN ??ICXRect@EQClasses@@QBE?AV01@V01@@Z:PROC ; CXRect__operator_and
EXTRN ??1CXStr@EQClasses@@QAE@XZ:PROC ; CXStr__dCXStr
EXTRN _DebugSpew:PROC

EXTRN _atoi:PROC
EXTRN _sqrt:PROC
EXTRN _fabs:PROC
EXTRN _abs:PROC
EXTRN _free:PROC
EXTRN _malloc:PROC
EXTRN _sprintf:PROC
EXTRN _fopen:PROC
EXTRN _fprintf:PROC
EXTRN _strlen:PROC
EXTRN _strcpy:PROC
EXTRN _fclose:PROC
EXTRN _sscanf:PROC
EXTRN _toupper:PROC
EXTRN _fgets:PROC
EXTRN __ftol2:PROC

EXTRN ?DrawLasso@CXWnd@EQClasses@@SAHVCXRect@2@K0@Z:PROC
EXTRN _itoa:PROC
EXTRN ?build_token_string_PARAM@EQUtil@EQClasses@@QAAPADPADH000000000@Z:PROC
EXTRN ?GetTextExtent@CTextureFont@EQClasses@@QBEHVCXStr@2@@Z:PROC ; CTextureFont__GetTextExtent
EXTRN ?GetHeight@CTextureFont@EQClasses@@QBEHXZ:PROC ; int EQClasses::CTextureFont::GetHeight(void)
EXTRN ??1CSidlScreenWnd@EQClasses@@QAE@XZ:PROC ; CSidlScreenWnd__dCSidlScreenWnd
EXTRN ?OnProcessFrame@CXWnd@EQClasses@@QAEHXZ:PROC ; CXWnd__OnProcessFrame

__imp__t3dDeferLine EQU 7F98ECh
__imp__t3dFloatFastSine EQU 7F9994h
__imp__t3dFloatFastCosine EQU 7F9990h
EQADDR_NUMBUFFER1 EQU 806154h
_DATA   SEGMENT PARA USE32 PUBLIC 'DATA'

_bMappingEnabled BYTE 1
byte_5DF7DA BYTE 0
dword_5DF7A8 dword 0
dword_5DF7AC dword 0
byte_5DF7D9 byte 0
byte_5DF7D8 byte 0
dword_5DF7D0 dword 0
dword_5DF7E8 dword 0
dword_70436C dword 0
byte_5DF7E4     db 0
dword_5DF7DC    dd 0
dword_5DF7E0    dd 0
;vftable
CMapViewWnd     dd offset 0
                                         ; DATA XREF: CMapViewWnd__CMapViewWnd+53o
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset _CMapViewWnd_PostDraw
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset _CMapViewWnd_HandleLButtonDown
	dd offset _CMapViewWnd_HandleLButtonUp
	dd offset _CMapViewWnd_HandleLButtonHeld
	dd offset _CMapViewWnd_HandleLButtonUpAfterHeld
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset _CMapViewWnd_HandleWheelMove
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset _CMapViewWnd_WndNotification
	dd offset _CMapViewWnd_Deactivate
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset _CMapViewWnd_OnProcessFrame
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0
	dd offset 0




__real@4@3ffea000000000000000 REAL4 0.625000 ; can be picked up from eqgame
__real@4@00000000000000000000 REAL4 0.0 ; can be picked up from eqgame
__real@4@3fff8000000000000000 REAL4 1.0 ; can be picked up from eqgame
__real@4@3fffc000000000000000 REAL4 1.5 ; can be picked up from eqgame
__real@4@40008000000000000000 REAL4 2.0 ; can be picked up from eqgame
__real@4@4000c000000000000000 REAL4 3.0 ; can be picked up from eqgame
__real@4@40018000000000000000 REAL4 4.0 ; can be picked up from eqgame
__real@4@4001a000000000000000 REAL4 5.0 ; can be picked up from eqgame
__real@4@4001c000000000000000 REAL4 6.0 ; can be picked up from eqgame
__real@4@3ffe8000000000000000 REAL4 0.50 ; can be picked up from eqgame
__real@4@3ffeaaaaaaaaaaaaa800 REAL4 0.666667
__real@4@3ff7a3d70a3d70a3d800 REAL4 0.005000
__real@4@3fff8ccccd0000000000 REAL4 1.1 ;(confirmed)
__real@4@3ffee8ba2e37021dc000 REAL4 0.909091
__real@8@bffe8000000000000000 REAL8 -0.500000 ; can be picked up from eqgame (confirmed)
__real@8@3ffcccccccccccccd000 REAL8 0.20 ; (confirmed)
__real@8@3ffee666660000000000 REAL8 0.900000 ;(confirmed)
__real@8@c00b9c40000000000000 REAL8 -5000.0 ;(confirmed)
__real@8@3ffe8000000000000000 REAL8 0.50 ;(confirmed)
dbl_5ACD60 REAL8 -5000.0 ; (confirmed)
flt_5ACD6C REAL4 -424242.0 ; (confirmed)
;flt_5ACD70 REAL4 -424242.0
flt_5ACD70 REAL4 -424242.0
dword_5ACD74 REAL4 -424242.0
__real@4@c011cf26400000000000 REAL4 -424242.0
unk_5ACD60 REAL8 -5000.0 ;(confirmed)
__real@8@4019bebc200000000000 REAL8 100000000.0 ;(confirmed)
__real@8@3ff583126f0000000000 dq 3f50624de0000000h ;(could not confirm as double so... hack it...)
__real@8@3ff7a3d70a0000000000 dq 3f747ae140000000h ; see above...
__real@8@4008e100000000000000 REAL8 900.0 ;(confirmed)
__real@8@3ff8a3d70a0000000000 REAL8 0.01 ;(confirmed)
__real@8@4007c800000000000000 REAL8 400.0 ;(confirmed)
__real@8@3ffacccccd0000000000 REAL8 0.05 ;(confirmed)
__real@8@4005c800000000000000 REAL8 100.0 ; (confirmed)
__real@8@40018000000000000000 REAL8 4.0 ; (confirmed)
__real@4@4010f424000000000000 REAL4 250000.0
__real@8@3ff1d1b71758e2196800 dq 3F1A36E2EB1C432Dh ; DATA XREF: _FindIntersect+45r (hacked it to qword
__real@4@407effffff0000000000 dd 7F7FFFFFh

;for our new zoom func:
dword_640FEC REAL4 0.2
EXTRN _unk_5DF7B0:DWORD
EXTRN _unk_5DF7C0:DWORD

dword_5DF7CC    dd 0
usedinactivatemap DWORD 7B9648h
pinstCEverQuest DWORD 809478h
pinstCharData DWORD 7F94E8h
pinstCXWndManager DWORD 809DB4h
pinstStringTable DWORD 7F9490h
pinstLocalPlayer DWORD 7F94CCh
__real@4@4007e800000000000000 REAL4 464.0
__real@4@4004c000000000000000 REAL4 48.0
pinstWorldData DWORD 7F9494h
aMapsS_D_txt    db 'maps\%s_%d.txt',0
aMapsS_txt      db 'maps\%s.txt',0
aFFFFFFDDD      db '%f, %f, %f,  %f, %f, %f,  %d, %d, %d',0
aFFFDDDD256s    db '%f, %f, %f,  %d, %d, %d,  %d,  %256s',0
aWt             db 'wt',0
aL0_4f0_4f0_4f0 db 'L %0.4f, %0.4f, %0.4f,  %0.4f, %0.4f, %0.4f,  %d, %d, %d',0Ah,0
aP0_4f0_4f0_4fD db 'P %0.4f, %0.4f, %0.4f,  %d, %d, %d,  %d,  %s',0Ah,0
aFailedToOpenSF db 'Failed to open %s for writing in MapViewMap::SaveEx()',0Ah,0
aRt             db 'rt',0
aTrue           db 'true',0
aFalse          db 'false',0
aS              db '%s',0
aD_0            db '%d',0
aHeighthigh     db 'HeightHigh',0       ; DATA XREF: CMapViewWnd__LoadIniInfo+1A8o
aHeightlow      db 'HeightLow',0        ; DATA XREF: CMapViewWnd__LoadIniInfo+150o
aHeightfilter   db 'HeightFilter',0     ; DATA XREF: CMapViewWnd__LoadIniInfo+E2o
aLabelsactive   db 'LabelsActive',0


_TEXT   SEGMENT PARA USE32 PUBLIC 'CODE'
ASSUME fs:NOTHING

_MapViewMap_SetCurrentColor proc near   ; CODE XREF: CMapToolbarWnd__WndNotification+79p
                                         ; do_map+19Ap

 arg_0           = dword ptr  4

                 mov     eax, [esp+arg_0] ; public: void __thiscall MapViewMap::SetCurrentColor(unsigned long
                 or      byte ptr [ecx+5Bh], 0FFh
                 mov     edx, eax
                 mov     [ecx+58h], al
                 shr     edx, 10h
                 mov     [ecx+5Ah], dl
                 mov     edx, eax
                 shr     edx, 8
                 mov     [ecx+59h], dl
                 retn    4
_MapViewMap_SetCurrentColor endp

_MapViewMap_ClearActiveLayer proc near  ; CODE XREF: CConfirmationDialog__ProcessYes+498p
                 push    esi             ; public: void __thiscall MapViewMap::ClearActiveLayer(void
                 mov     esi, ecx
                 push    edi
                 mov     eax, [esi+40h]
                 test    eax, eax
                 jz      short loc_43825B

 loc_438243:                             ; CODE XREF: MapViewMap__ClearActiveLayer+21j
                 mov     ecx, [eax+24h]
                 mov     edi, [eax]
                 cmp     ecx, [esi+68h]
                 jnz     short loc_438255
                 push    eax
                 mov     ecx, esi
                 call    _MapViewMap_RemoveLine

 loc_438255:                             ; CODE XREF: MapViewMap__ClearActiveLayer+13j
                 test    edi, edi
                 mov     eax, edi
                 jnz     short loc_438243

 loc_43825B:                             ; CODE XREF: MapViewMap__ClearActiveLayer+9j
                 mov     eax, [esi+44h]
                 test    eax, eax
                 jz      short loc_43827A

 loc_438262:                             ; CODE XREF: MapViewMap__ClearActiveLayer+40j
                 mov     ecx, [eax+20h]
                 mov     edi, [eax]
                 cmp     ecx, [esi+68h]
                 jnz     short loc_438274
                 push    eax
                 mov     ecx, esi
                 call    _MapViewMap_RemoveLabel

 loc_438274:                             ; CODE XREF: MapViewMap__ClearActiveLayer+32j
                 test    edi, edi
                 mov     eax, edi
                 jnz     short loc_438262

 loc_43827A:                             ; CODE XREF: MapViewMap__ClearActiveLayer+28j
                 pop     edi
                 pop     esi
                 retn
_MapViewMap_ClearActiveLayer endp

_MapViewMap_RemoveLabel proc near       ; CODE XREF: MapViewMap__ClearActiveLayer+37p

 arg_0           = dword ptr  4

                 push    esi             ; public: void __thiscall MapViewMap::RemoveLabel(struct _mapviewlabel *
                 mov     esi, [esp+4+arg_0]
                 mov     edx, [esi+4]
                 mov     eax, [esi]
                 test    edx, edx
                 jz      short loc_4382CD
                 test    eax, eax
                 mov     [edx], eax
                 jz      short loc_4382E0
                 mov     [eax+4], edx
                 jmp     short loc_4382E0
 ; ---------------------------------------------------------------------------

 loc_4382CD:                             ; CODE XREF: MapViewMap__RemoveLabel+Cj
                 test    eax, eax
                 jz      short loc_4382DC
                 and     dword ptr [eax+4], 0
                 mov     eax, [esi]
                 mov     [ecx+44h], eax
                 jmp     short loc_4382E0
 ; ---------------------------------------------------------------------------

 loc_4382DC:                             ; CODE XREF: MapViewMap__RemoveLabel+1Bj
                 and     dword ptr [ecx+44h], 0

 loc_4382E0:                             ; CODE XREF: MapViewMap__RemoveLabel+12j
                                         ; MapViewMap__RemoveLabel+17j ...
                 push    dword ptr [esi+1Ch]
                 call    operator__delete
                 and     dword ptr [esi+1Ch], 0
                 push    esi
                 call    operator__delete
                 pop     ecx
                 pop     ecx
                 pop     esi
                 retn    4
_MapViewMap_RemoveLabel endp

_MapViewMap_RemoveLine proc near        ; CODE XREF: MapViewMap__ClearActiveLayer+18p

 arg_0           = dword ptr  4

                 mov     eax, [esp+arg_0] ; public: void __thiscall MapViewMap::RemoveLine(struct _mapviewline *
                 mov     edx, [eax+4]
                 test    edx, edx
                 jz      short loc_438295
                 mov     ecx, [eax]
                 test    ecx, ecx
                 mov     [edx], ecx
                 jz      short loc_4382AA
                 mov     [ecx+4], edx
                 jmp     short loc_4382AA
 ; ---------------------------------------------------------------------------

 loc_438295:                             ; CODE XREF: MapViewMap__RemoveLine+9j
                 mov     edx, [eax]
                 test    edx, edx
                 jz      short loc_4382A6
                 and     dword ptr [edx+4], 0
                 mov     edx, [eax]
                 mov     [ecx+40h], edx
                 jmp     short loc_4382AA
 ; ---------------------------------------------------------------------------

 loc_4382A6:                             ; CODE XREF: MapViewMap__RemoveLine+1Cj
                 and     dword ptr [ecx+40h], 0

 loc_4382AA:                             ; CODE XREF: MapViewMap__RemoveLine+11j
                                         ; MapViewMap__RemoveLine+16j ...
                 push    eax
                 call    operator__delete
                 pop     ecx
                 retn    4
_MapViewMap_RemoveLine endp

_MapViewMap_RemoveLine_0 proc near      ; CODE XREF: CMapToolbarWnd__WndNotification+258p
                 push    esi             ; public: void __thiscall MapViewMap::RemoveLine(void
                 mov     esi, ecx
                 mov     ecx, [esi+5Ch]
                 test    ecx, ecx
                 jz      short loc_436170
                 push    edi

 loc_436133:                             ; CODE XREF: MapViewMap__RemoveLine_0+45j
                 mov     eax, [ecx+4]
                 mov     edi, [ecx]
                 mov     edx, [eax+4]
                 mov     eax, [eax]
                 test    edx, edx
                 jz      short loc_43614C
                 test    eax, eax
                 mov     [edx], eax
                 jz      short loc_436162
                 mov     [eax+4], edx
                 jmp     short loc_436162
 ; ---------------------------------------------------------------------------

 loc_43614C:                             ; CODE XREF: MapViewMap__RemoveLine_0+17j
                 test    eax, eax
                 jz      short loc_43615E
                 and     dword ptr [eax+4], 0
                 mov     eax, [ecx+4]
                 mov     eax, [eax]
                 mov     [esi+40h], eax
                 jmp     short loc_436162
 ; ---------------------------------------------------------------------------

 loc_43615E:                             ; CODE XREF: MapViewMap__RemoveLine_0+26j
                 and     dword ptr [esi+40h], 0

 loc_436162:                             ; CODE XREF: MapViewMap__RemoveLine_0+1Dj
                                         ; MapViewMap__RemoveLine_0+22j ...
                 push    ecx
                 call    operator__delete
                 pop     ecx
                 test    edi, edi
                 mov     ecx, edi
                 jnz     short loc_436133
                 pop     edi

 loc_436170:                             ; CODE XREF: MapViewMap__RemoveLine_0+8j
                 and     dword ptr [esi+5Ch], 0
                 pop     esi
                 retn
_MapViewMap_RemoveLine_0 endp


_MapViewMap_RemoveLabel_0 proc near     ; CODE XREF: CMapToolbarWnd__WndNotification+37Ep
                 push    esi             ; public: void __thiscall MapViewMap::RemoveLabel(void
                 mov     esi, ecx
                 mov     eax, [esi+60h]
                 test    eax, eax
                 jz      short loc_436366
                 mov     ecx, [eax+4]
                 mov     eax, [eax]
                 test    ecx, ecx
                 jz      short loc_436330
                 test    eax, eax
                 mov     [ecx], eax
                 jz      short loc_436346
                 mov     [eax+4], ecx
                 jmp     short loc_436346
 ; ---------------------------------------------------------------------------

 loc_436330:                             ; CODE XREF: MapViewMap__RemoveLabel_0+11j
                 test    eax, eax
                 jz      short loc_436342
                 and     dword ptr [eax+4], 0
                 mov     eax, [esi+60h]
                 mov     eax, [eax]
                 mov     [esi+44h], eax
                 jmp     short loc_436346
 ; ---------------------------------------------------------------------------

 loc_436342:                             ; CODE XREF: MapViewMap__RemoveLabel_0+20j
                 and     dword ptr [esi+44h], 0

 loc_436346:                             ; CODE XREF: MapViewMap__RemoveLabel_0+17j
                                         ; MapViewMap__RemoveLabel_0+1Cj ...
                 mov     eax, [esi+60h]
                 push    dword ptr [eax+1Ch]
                 call    operator__delete
                 mov     eax, [esi+60h]
                 and     dword ptr [eax+1Ch], 0
                 push    dword ptr [esi+60h]
                 call    operator__delete
                 and     dword ptr [esi+60h], 0
                 pop     ecx
                 pop     ecx

 loc_436366:                             ; CODE XREF: MapViewMap__RemoveLabel_0+8j
                 pop     esi
                 retn
 _MapViewMap_RemoveLabel_0 endp


_MapViewMap_MoveLabel proc near         ; CODE XREF: CMapToolbarWnd__WndNotification+366p

 arg_0           = dword ptr  4
 arg_4           = dword ptr  8
 arg_8           = dword ptr  0Ch
 arg_C           = dword ptr  10h

                 mov     eax, [esp+arg_0] ; public: void __thiscall MapViewMap::MoveLabel(struct _mapviewlabel *,float,float,float
                 mov     ecx, [esp+arg_8]
                 fld     [esp+arg_4]
                 mov     [eax+0Ch], ecx
                 mov     ecx, [esp+arg_C]
                 fstp    dword ptr [eax+8]
                 mov     [eax+10h], ecx
                 retn    10h
_MapViewMap_MoveLabel endp


_FindIntersect  proc near               ; CODE XREF: MapViewMap__JoinLinesAtIntersect+84p

 var_18          = qword ptr -18h
 var_10          = qword ptr -10h
 var_8           = qword ptr -8
 arg_0           = qword ptr  8
 arg_8           = qword ptr  10h
 arg_10          = qword ptr  18h
 arg_18          = qword ptr  20h
 arg_20          = qword ptr  28h
 arg_28          = qword ptr  30h
 arg_30          = qword ptr  38h
 arg_38          = qword ptr  40h
 arg_40          = dword ptr  48h
 arg_44          = dword ptr  4Ch

                 push    ebp             ; bool __cdecl _FindIntersect(double,double,double,double,double,double,double,double,float *,float *
                 mov     ebp, esp
                 sub     esp, 10h
                 fld     [ebp+arg_10]
                 fsub    [ebp+arg_0]
                 push    ecx
                 push    ecx
                 fstp    [ebp+var_8]
                 fld     [ebp+arg_38]
                 fsub    [ebp+arg_28]
                 fstp    [ebp+arg_38]
                 fld     [ebp+arg_18]
                 fsub    [ebp+arg_8]
                 fstp    [ebp+var_10]
                 fld     [ebp+arg_30]
                 fsub    [ebp+arg_20]
                 fstp    [ebp+arg_10]
                 fld     [ebp+arg_38]
                 fmul    [ebp+var_8]
                 fld     [ebp+arg_10]
                 fmul    [ebp+var_10]
                 fsubp   st(1), st
                 fst     [ebp+arg_18]
                 fstp    [esp+18h+var_18]
                 call    _fabs
                 fcomp   ds:__real@8@3ff1d1b71758e2196800 ; __real@8@3ff1d1b71758e219680
                 pop     ecx
                 pop     ecx
                 fnstsw  ax
                 sahf
                 jnb     short loc_4385E0
                 xor     al, al
                 leave
                 retn
 ; ---------------------------------------------------------------------------

 loc_4385E0:                             ; CODE XREF: _FindIntersect+50j
                 fld     [ebp+arg_8]
                 fsub    [ebp+arg_28]
                 mov     eax, [ebp+arg_40]
                 fmul    [ebp+arg_10]
                 fld     [ebp+arg_0]
                 fsub    [ebp+arg_20]
                 fmul    [ebp+arg_38]
                 fsubp   st(1), st
                 fdiv    [ebp+arg_18]
                 fld     [ebp+var_8]
                 fmul    st, st(1)
                 fadd    [ebp+arg_0]
                 fstp    dword ptr [eax]
                 fld     [ebp+var_10]
                 mov     eax, [ebp+arg_44]
                 fmul    st, st(1)
                 fadd    [ebp+arg_8]
                 fstp    dword ptr [eax]
                 mov     al, 1
                 fstp    st
                 leave
                 retn
 _FindIntersect  endp


_MapViewMap_JoinLinesAtIntersect proc near
                                         ; CODE XREF: CMapToolbarWnd__WndNotification+41Ep

 var_60          = qword ptr -60h
 var_58          = qword ptr -58h
 var_50          = qword ptr -50h
 var_48          = qword ptr -48h
 var_40          = qword ptr -40h
 var_38          = qword ptr -38h
 var_30          = qword ptr -30h
 var_28          = qword ptr -28h
 var_C           = dword ptr -0Ch
 var_8           = dword ptr -8
 var_4           = dword ptr -4
 arg_0           = dword ptr  8

                 push    ebp             ; public: void __thiscall MapViewMap::JoinLinesAtIntersect(bool
                 mov     ebp, esp
                 sub     esp, 0Ch
                 mov     eax, [ecx+5Ch]
                 push    ebx
                 xor     ebx, ebx
                 push    esi
                 cmp     eax, ebx
                 push    edi
                 jz      loc_438583
                 mov     ecx, [eax]
                 cmp     ecx, ebx
                 jz      loc_438566
                 cmp     [ecx], ebx
                 jnz     loc_438566
                 mov     edi, [eax+4]
                 mov     eax, ecx
                 fld     ds:__real@4@407effffff0000000000 ; __real@4@407effffff000000000
                 mov     esi, [eax+4]
                 lea     eax, [ebp+var_4]
                 fst     [ebp+var_8]
                 fstp    [ebp+var_4]
                 fld     dword ptr [edi+18h]
                 push    eax             ; int
                 lea     eax, [ebp+var_8]
                 push    eax             ; int
                 push    ecx
                 push    ecx             ; double
                 fstp    [esp+28h+var_28]
                 fld     dword ptr [edi+14h]
                 push    ecx
                 push    ecx             ; double
                 fstp    [esp+30h+var_30]
                 fld     dword ptr [edi+0Ch]
                 push    ecx
                 push    ecx             ; double
                 fstp    [esp+38h+var_38]
                 fld     dword ptr [edi+8]
                 push    ecx
                 push    ecx             ; double
                 fstp    [esp+40h+var_40]
                 fld     dword ptr [esi+18h]
                 push    ecx
                 push    ecx             ; double
                 fstp    [esp+48h+var_48]
                 fld     dword ptr [esi+14h]
                 push    ecx
                 push    ecx             ; double
                 fstp    [esp+50h+var_50]
                 fld     dword ptr [esi+0Ch]
                 push    ecx
                 push    ecx             ; double
                 fstp    [esp+58h+var_58]
                 fld     dword ptr [esi+8]
                 push    ecx
                 push    ecx             ; double
                 fstp    [esp+60h+var_60]
                 call    _FindIntersect
                 add     esp, 48h
                 test    al, al
                 jz      loc_43855E
                 fld     dword ptr [esi+0Ch]
                 fsub    [ebp+var_4]
                 cmp     byte ptr [ebp+arg_0], bl
                 fstp    [ebp+var_C]
                 fld     [ebp+var_8]
                 fld     dword ptr [esi+8]
                 fsub    st, st(1)
                 fld     st
                 fmul    st, st(1)
                 fld     [ebp+var_C]
                 fmul    [ebp+var_C]
                 faddp   st(1), st
                 fstp    st(1)
                 fld     dword ptr [esi+18h]
                 fsub    [ebp+var_4]
                 fld     dword ptr [esi+14h]
                 fsub    st, st(3)
                 fld     st
                 fmul    st, st(1)
                 fld     st(2)
                 fmul    st, st(3)
                 faddp   st(1), st
                 fstp    st(2)
                 fstp    st
                 jnz     loc_438515
                 fld     dword ptr [edi+0Ch]
                 fsub    [ebp+var_4]
                 fld     dword ptr [edi+8]
                 fsub    st, st(4)
                 fld     st
                 fmul    st, st(1)
                 fld     st(2)
                 fmul    st, st(3)
                 faddp   st(1), st
                 fstp    [ebp+arg_0]
                 fstp    st
                 fstp    st
                 fld     dword ptr [edi+18h]
                 fsub    [ebp+var_4]
                 fld     dword ptr [edi+14h]
                 fsub    st, st(4)
                 fld     st
                 fmul    st, st(1)
                 fld     st(2)
                 fmul    st, st(3)
                 faddp   st(1), st
                 fstp    [ebp+var_C]
                 fstp    st
                 fstp    st
                 fld     ds:__real@4@4010f424000000000000 ; __real@4@4010f42400000000000
                 fld     st(2)
                 fcomp   st(1)
                 fnstsw  ax
                 sahf
                 jbe     short loc_4384CE
                 fld     st(1)
                 fcomp   st(1)
                 fnstsw  ax
                 sahf
                 jbe     short loc_4384CE
                 fld     [ebp+arg_0]
                 fcomp   st(1)
                 fnstsw  ax
                 sahf
                 jbe     short loc_4384CE
                 fld     [ebp+var_C]
                 fcomp   st(1)
                 fnstsw  ax
                 sahf
                 fstp    st
                 jbe     short loc_4384D0
                 jmp     short loc_43852D
 ; ---------------------------------------------------------------------------

 loc_4384CE:                             ; CODE XREF: MapViewMap__JoinLinesAtIntersect+11Aj
                                         ; MapViewMap__JoinLinesAtIntersect+123j ...
                 fstp    st

 loc_4384D0:                             ; CODE XREF: MapViewMap__JoinLinesAtIntersect+139j
                 fld     st(1)
                 fcomp   st(1)
                 fnstsw  ax
                 fstp    st
                 sahf
                 fstp    st
                 jnb     short loc_4384E8
                 fstp    dword ptr [esi+8]
                 mov     eax, [ebp+var_4]
                 mov     [esi+0Ch], eax
                 jmp     short loc_4384F1
 ; ---------------------------------------------------------------------------

 loc_4384E8:                             ; CODE XREF: MapViewMap__JoinLinesAtIntersect+14Aj
                 fstp    dword ptr [esi+14h]
                 mov     eax, [ebp+var_4]
                 mov     [esi+18h], eax

 loc_4384F1:                             ; CODE XREF: MapViewMap__JoinLinesAtIntersect+155j
                 fld     [ebp+arg_0]
                 fcomp   [ebp+var_C]
                 fnstsw  ax
                 sahf
                 mov     eax, [ebp+var_8]
                 jnb     short loc_43850A
                 mov     [edi+8], eax
                 mov     eax, [ebp+var_4]
                 mov     [edi+0Ch], eax
                 jmp     short loc_438583
 ; ---------------------------------------------------------------------------

 loc_43850A:                             ; CODE XREF: MapViewMap__JoinLinesAtIntersect+16Cj
                 mov     [edi+14h], eax
                 mov     eax, [ebp+var_4]
                 mov     [edi+18h], eax
                 jmp     short loc_438583
 ; ---------------------------------------------------------------------------

 loc_438515:                             ; CODE XREF: MapViewMap__JoinLinesAtIntersect+CFj
                 fld     st(1)
                 fcomp   ds:__real@4@4010f424000000000000 ; __real@4@4010f42400000000000
                 fnstsw  ax
                 sahf
                 jbe     short loc_43853B
                 fcom    ds:__real@4@4010f424000000000000 ; __real@4@4010f42400000000000
                 fnstsw  ax
                 sahf
                 jbe     short loc_43853B

 loc_43852D:                             ; CODE XREF: MapViewMap__JoinLinesAtIntersect+13Bj
                 fstp    st
                 fstp    st
                 push    ebx
                 push    3ACEh
                 fstp    st
                 jmp     short loc_43856C
 ; ---------------------------------------------------------------------------

 loc_43853B:                             ; CODE XREF: MapViewMap__JoinLinesAtIntersect+18Fj
                                         ; MapViewMap__JoinLinesAtIntersect+19Aj
                 fld     st(1)
                 fcomp   st(1)
                 fnstsw  ax
                 fstp    st
                 sahf
                 fstp    st
                 jnb     short loc_438553
                 fstp    dword ptr [esi+8]
                 mov     eax, [ebp+var_4]
                 mov     [esi+0Ch], eax
                 jmp     short loc_438583
 ; ---------------------------------------------------------------------------

 loc_438553:                             ; CODE XREF: MapViewMap__JoinLinesAtIntersect+1B5j
                 fstp    dword ptr [esi+14h]
                 mov     eax, [ebp+var_4]
                 mov     [esi+18h], eax
                 jmp     short loc_438583
 ; ---------------------------------------------------------------------------

 loc_43855E:                             ; CODE XREF: MapViewMap__JoinLinesAtIntersect+8Ej
                 push    ebx
                 push    3ACFh
                 jmp     short loc_43856C
 ; ---------------------------------------------------------------------------

 loc_438566:                             ; CODE XREF: MapViewMap__JoinLinesAtIntersect+1Aj
                                         ; MapViewMap__JoinLinesAtIntersect+22j
                 push    ebx
                 push    3AD0h

 loc_43856C:                             ; CODE XREF: MapViewMap__JoinLinesAtIntersect+1A8j
                                         ; MapViewMap__JoinLinesAtIntersect+1D3j
                 mov     ecx, pinstStringTable
                 mov     ecx, [ecx] ; added
                 call    ?getString@StringTable@EQClasses@@QAEPADKPA_N@Z
                 mov     ecx, pinstCEverQuest
                 mov     ecx, [ecx] ; added
                 push    eax             ; Str
                 call    ?dsp_chat@CEverQuest@EQClasses@@QAEXPBD@Z ; CEverQuest__dsp_chat1

 loc_438583:                             ; CODE XREF: MapViewMap__JoinLinesAtIntersect+10j
                                         ; MapViewMap__JoinLinesAtIntersect+177j ...
                 pop     edi
                 pop     esi
                 pop     ebx
                 leave
                 retn    4
 _MapViewMap_JoinLinesAtIntersect endp


_MapViewMap_GetCurrentColor proc near   ; CODE XREF: CMapToolbarWnd__WndNotification+48Cp
                 xor     eax, eax        ; public: unsigned long __thiscall MapViewMap::GetCurrentColor(void
                 mov     ah, [ecx+5Ah]
                 mov     al, [ecx+59h]
                 movzx   ecx, byte ptr [ecx+58h]
                 shl     eax, 8
                 or      eax, ecx
                 retn
_MapViewMap_GetCurrentColor endp

_CMapViewWnd_Activate proc near         ; CODE XREF: CDisplay__ActivateMainUI+6Cp
                                         ; __ExecuteCmd:loc_49AA2Ep
                 cmp     dword_70436C, 0 ; public: void __thiscall CMapViewWnd::Activate(void
                 push    esi
                 mov     esi, ecx
                 jnz     short loc_434FCA
                 push    usedinactivatemap
                 mov     ecx, pinstWorldData ; class EQWorldData * EQTimeDat
                 mov     ecx, [ecx] ; added
                 call    ?IsNewbieZone@EQWorldData@EQClasses@@QBE_NW4EQZoneIndex@2@@Z
                 ;test    al, al
                 ;jz      short loc_434FED

 loc_434FCA:                             ; CODE XREF: CMapViewWnd__Activate+Aj
                 mov     eax, [esi]
                 mov     ecx, esi
                 ;call    dword ptr [eax+0F8h] ; its a call to CMapViewWnd__LoadIniInfo
                 call    dword ptr [eax+0FCh] ; its a call to CMapViewWnd__LoadIniInfo
                 push    1
                 push    1
                 mov     ecx, esi
                 call    ?Show@CXWnd@EQClasses@@QAEH_N0@Z
                 mov     ecx, esi
                 mov     byte ptr [esi+134h], 1
                 call    __CMapViewWnd__Init

 loc_434FED:                             ; CODE XREF: CMapViewWnd__Activate+1Fj
                 pop     esi
                 retn
_CMapViewWnd_Activate endp

_CMapViewWnd_Deactivate proc near       ; DATA XREF: .rdata:00593D94o
                 push    ebx             ; public: virtual void __thiscall CMapViewWnd::Deactivate(void
                 push    esi
                 mov     esi, ecx
                 call    __CMapViewWnd__Init
                 xor     ebx, ebx

 loc_434FFA:                             ; CODE XREF: CMapViewWnd__Deactivate+1Bj
                                         ; CMapViewWnd__Deactivate+20j
                 mov     eax, pinstCXWndManager ; class CXWndManager * g_pwndmg
                 mov     eax, [eax]
                 cmp     [eax+34h], esi
                 jnz     short loc_435011
                 dec     dword ptr [eax+44h]
                 cmp     [eax+44h], ebx
                 jg      short loc_434FFA
                 mov     [eax+34h], ebx
                 jmp     short loc_434FFA
 ; ---------------------------------------------------------------------------

 loc_435011:                             ; CODE XREF: CMapViewWnd__Deactivate+13j
                 mov     ecx, _g_pMapToolbarWnd ; class CMapToolbarWnd * g_pMapToolbarWn
                 cmp     ecx, ebx
                 jz      short loc_43502B
                 cmp     [ecx+170h], bl
                 jz      short loc_43502B
                 mov     eax, [ecx]
                 call    dword ptr [eax+88h] ; CXWnd__Deactivate (changed)

 loc_43502B:                             ; CODE XREF: CMapViewWnd__Deactivate+2Aj
                                         ; CMapViewWnd__Deactivate+32j
                 push    1
                 mov     byte_5DF7DA, bl
                 mov     byte_5DF7D8, bl
                 push    ebx
                 mov     ecx, esi
                 mov     [esi+134h], bl
                 call    ?Show@CXWnd@EQClasses@@QAEH_N0@Z
                 pop     esi
                 pop     ebx
                 retn
_CMapViewWnd_Deactivate endp
_MapViewMap_AddPoint proc near          ; CODE XREF: CMapToolbarWnd__WndNotification+29Ap
                                         ; CMapViewWnd__OnProcessFrame+184p ...

 var_14          = qword ptr -14h
 var_4           = dword ptr -4
 arg_0           = dword ptr  8
 arg_4           = dword ptr  0Ch
 arg_8           = dword ptr  10h

                 push    ebp             ; public: void __thiscall MapViewMap::AddPoint(float,float,float
                 mov     ebp, esp
                 push    ecx
                 push    ebx
                 mov     ebx, ecx
                 push    esi
                 cmp     byte ptr [ebx+48h], 1
                 jnz     loc_436219
                 fld     [ebp+arg_0]
                 fadd    dword ptr [ebx+8]
                 lea     esi, [ebx+4Ch]
                 push    ecx
                 push    ecx
                 mov     [ebp+var_4], esi
                 fsubr   dword ptr [esi]
                 fstp    [esp+14h+var_14]
                 call    _fabs
                 fcomp   qword ptr ds:__real@8@3ffee666660000000000 ; 0.900000 confirmed 
                 pop     ecx
                 pop     ecx
                 fnstsw  ax
                 sahf
                 ja      short loc_4361CD
                 fld     [ebp+arg_4]
                 fadd    dword ptr [ebx+0Ch]
                 push    ecx
                 push    ecx
                 fsubr   dword ptr [ebx+50h]
                 fstp    [esp+14h+var_14]
                 call    _fabs
                 fcomp   qword ptr ds:__real@8@3ffee666660000000000 ; 0.900000 confirmed 
                 pop     ecx
                 pop     ecx
                 fnstsw  ax
                 sahf
                 jbe     short loc_436219

 loc_4361CD:                             ; CODE XREF: MapViewMap__AddPoint+35j
                 push    28h             ; unsigned int
                 call    new
                 and     dword ptr [eax+4], 0
                 pop     ecx
                 mov     ecx, [ebx+40h]
                 mov     [eax], ecx
                 mov     ecx, [ebx+40h]
                 test    ecx, ecx
                 jz      short loc_4361E8
                 mov     [ecx+4], eax

 loc_4361E8:                             ; CODE XREF: MapViewMap__AddPoint+6Dj
                 push    edi
                 lea     edi, [eax+8]
                 mov     [ebx+40h], eax
                 mov     ecx, [ebp+arg_0]
                 movsd
                 movsd
                 movsd
                 lea     esi, [eax+14h]
                 mov     edi, [ebp+var_4]
                 mov     [esi], ecx
                 mov     ecx, [ebp+arg_4]
                 mov     [eax+18h], ecx
                 mov     ecx, [ebp+arg_8]
                 mov     [eax+1Ch], ecx
                 mov     ecx, [ebx+58h]
                 mov     [eax+20h], ecx
                 mov     ecx, [ebx+68h]
                 mov     [eax+24h], ecx
                 movsd
                 movsd
                 movsd
                 pop     edi

 loc_436219:                             ; CODE XREF: MapViewMap__AddPoint+Cj
                                         ; MapViewMap__AddPoint+55j
                 pop     esi
                 pop     ebx
                 leave
                 retn    0Ch
_MapViewMap_AddPoint endp

_CMapViewWnd_OnProcessFrame proc near   ; DATA XREF: .rdata:00593DB8o

 var_34          = dword ptr -34h
 var_30          = qword ptr -30h
 var_24          = qword ptr -24h
 var_1C          = qword ptr -1Ch
 var_14          = qword ptr -14h
 var_C           = dword ptr -0Ch
 var_8           = dword ptr -8
 var_4           = dword ptr -4

                 push    ebp
                 mov     ebp, esp
                 sub     esp, 24h
                 push    esi
                 mov     esi, ecx
                 cmp     byte ptr [esi+134h], 0
                 jz      loc_435257
                 cmp     byte ptr [esi+135h], 1
                 jnz     loc_43520F
                 mov     eax, pinstLocalPlayer ; class EQPlayer * LocalPlaye
                 mov     eax, [eax]
                 test    eax, eax
                 jz      loc_43520F
				 ;fld     dword ptr [eax+50h]
                 fld     dword ptr [eax+4Ch] ; X
                 fchs
                 fst     [ebp+var_C]
                 ;fld     dword ptr [eax+58h]
                 fld     dword ptr [eax+48h] ; Y
                 fchs
                 fst     [ebp+var_4]
                 fld     dword ptr [eax+0F0h] ; changed i think this is height
                 fmul    ds:__real@4@3ffea000000000000000 ; __real@4@3ffea00000000000000
                 ;fsubr   dword ptr [eax+5Ch]
                 fsubr   dword ptr [eax+50h] ; Z
                 fstp    [ebp+var_8]
                 fld     flt_5ACD6C
                 fcomp   ds:__real@4@c011cf26400000000000 ; __real@4@c011cf2640000000000
                 fnstsw  ax
                 sahf
                 jnz     short loc_4350C5
                 mov     eax, [ebp+var_8]
                 fld     st(1)
                 mov     dword_5ACD74, eax
                 fstp    flt_5ACD6C
                 fstp    flt_5ACD70
                 jmp     short loc_4350C7
 ; ---------------------------------------------------------------------------

 loc_4350C5:                             ; CODE XREF: CMapViewWnd__OnProcessFrame+61j
                 fstp    st

 loc_4350C7:                             ; CODE XREF: CMapViewWnd__OnProcessFrame+79j
                 fld     dword ptr [esi+1F4h]
                 fsub    st, st(1)
                 push    ecx
                 push    ecx
                 fstp    [esp+30h+var_30]
                 fstp    st
                 call    _fabs
                 fstp    [ebp+var_14]
                 fld     dword ptr [esi+1F8h]
                 fsub    [ebp+var_4]
                 fstp    [esp+30h+var_30]
                 call    _fabs
                 fld     st
                 fmul    st, st(1)
                 fld     [ebp+var_14]
                 fmul    [ebp+var_14]
                 pop     ecx
                 pop     ecx
                 faddp   st(1), st
                 fcom    ds:__real@8@40018000000000000000 ; __real@8@4001800000000000000
                 fnstsw  ax
                 sahf
                 jbe     loc_4351F1
                 fcom    ds:__real@8@4005c800000000000000 ; __real@8@4005c80000000000000
                 fnstsw  ax
                 sahf
                 jnb     short loc_435121
                 fstp    st
                 fld     ds:__real@8@3ffacccccd0000000000 ; __real@8@3ffacccccd000000000
                 jmp     short loc_43514F
 ; ---------------------------------------------------------------------------

 loc_435121:                             ; CODE XREF: CMapViewWnd__OnProcessFrame+CBj
                 fcom    ds:__real@8@4007c800000000000000 ; __real@8@4007c80000000000000
                 fnstsw  ax
                 sahf
                 jnb     short loc_435136
                 fstp    st
                 fld     ds:__real@8@3ff8a3d70a0000000000 ; __real@8@3ff8a3d70a000000000
                 jmp     short loc_43514F
 ; ---------------------------------------------------------------------------

 loc_435136:                             ; CODE XREF: CMapViewWnd__OnProcessFrame+E0j
                 fcomp   ds:__real@8@4008e100000000000000 ; __real@8@4008e10000000000000
                 fnstsw  ax
                 sahf
                 jnb     short loc_435149
                 fld     ds:__real@8@3ff7a3d70a0000000000 ; __real@8@3ff7a3d70a000000000
                 jmp     short loc_43514F
 ; ---------------------------------------------------------------------------

 loc_435149:                             ; CODE XREF: CMapViewWnd__OnProcessFrame+F5j
                 fld     ds:__real@8@3ff583126f0000000000 ; __real@8@3ff583126f000000000

 loc_43514F:                             ; CODE XREF: CMapViewWnd__OnProcessFrame+D5j
                                         ; CMapViewWnd__OnProcessFrame+EAj ...
                 fstp    [ebp+var_1C]
                 fld     ds:__real@8@4019bebc200000000000 ; __real@8@4019bebc20000000000
                 fstp    [ebp+var_24]
                 fld     [ebp+var_14]
                 fcomp   ds:__real@8@3ffe8000000000000000 ; __real@8@3ffe800000000000000
                 fnstsw  ax
                 sahf
                 jbe     short loc_435171
                 fdiv    [ebp+var_14]
                 fstp    [ebp+var_24]
                 jmp     short loc_435173
 ; ---------------------------------------------------------------------------

 loc_435171:                             ; CODE XREF: CMapViewWnd__OnProcessFrame+11Dj
                 fstp    st

 loc_435173:                             ; CODE XREF: CMapViewWnd__OnProcessFrame+125j
                 fld     qword ptr unk_5ACD60
                 fcomp   qword ptr ds:__real@8@c00b9c40000000000000 ; __real@8@c00b9c4000000000000
                 fnstsw  ax
                 sahf
                 jz      short loc_4351E6
                 fld     qword ptr unk_5ACD60
                 fsub    [ebp+var_24]
                 push    ecx
                 push    ecx
                 fstp    [esp+30h+var_30]
                 call    _fabs
                 fcomp   [ebp+var_1C]
                 pop     ecx
                 pop     ecx
                 fnstsw  ax
                 sahf
                 jbe     short loc_4351D5
                 fld     [ebp+var_24]
                 push    ecx             ; int
                 fstp    qword ptr unk_5ACD60
                 fld     dword_5ACD74
                 fstp    dword ptr [esp+2Ch+var_30+4]
                 fld     flt_5ACD70
                 push    ecx             ; float
                 fstp    dword ptr [esp+30h+var_30]
                 fld     flt_5ACD6C
                 push    ecx             ; float
                 lea     ecx, [esi+1A8h]
                 fstp    [esp+34h+var_34]
                 call    _MapViewMap_AddPoint
                 jmp     short loc_4351F5
 ; ---------------------------------------------------------------------------

 loc_4351D5:                             ; CODE XREF: CMapViewWnd__OnProcessFrame+155j
                 fld     qword ptr unk_5ACD60
                 fcomp   qword ptr ds:__real@8@c00b9c40000000000000 ; __real@8@c00b9c4000000000000
                 fnstsw  ax
                 sahf
                 jnz     short loc_4351F5

 loc_4351E6:                             ; CODE XREF: CMapViewWnd__OnProcessFrame+138j
                 fld     [ebp+var_24]
                 fstp    qword ptr unk_5ACD60
                 jmp     short loc_4351F5
 ; ---------------------------------------------------------------------------

 loc_4351F1:                             ; CODE XREF: CMapViewWnd__OnProcessFrame+BCj
                 fstp    st
                 fstp    st

 loc_4351F5:                             ; CODE XREF: CMapViewWnd__OnProcessFrame+189j
                                         ; CMapViewWnd__OnProcessFrame+19Aj ...
                 mov     eax, [ebp+var_C]
                 mov     flt_5ACD6C, eax
                 mov     eax, [ebp+var_4]
                 mov     flt_5ACD70, eax
                 mov     eax, [ebp+var_8]
                 mov     dword_5ACD74, eax
                 jmp     short loc_435227
 ; ---------------------------------------------------------------------------

 loc_43520F:                             ; CODE XREF: CMapViewWnd__OnProcessFrame+1Dj
                                         ; CMapViewWnd__OnProcessFrame+2Aj
                 fld     ds:__real@4@c011cf26400000000000 ; __real@4@c011cf2640000000000
                 fst     flt_5ACD6C
                 fst     flt_5ACD70
                 fstp    dword_5ACD74

 loc_435227:                             ; CODE XREF: CMapViewWnd__OnProcessFrame+1C3j
                 cmp     byte_5DF7DA, 1
                 jnz     short loc_435257
                 mov     eax, pinstCXWndManager ; class CXWndManager * g_pwndmg
                 mov     eax, [eax]
                 mov     edx, dword_5DF7E0
                 mov     ecx, [eax+4Ch] ;checked and its fine
                 mov     eax, [eax+50h] ;checked and its fine
                 add     eax, edx
                 mov     edx, dword_5DF7DC
                 add     edx, ecx
                 mov     [esi+1C8h], edx
                 mov     [esi+1CCh], eax

 loc_435257:                             ; CODE XREF: CMapViewWnd__OnProcessFrame+10j
                                         ; CMapViewWnd__OnProcessFrame+1E4j
                 mov     ecx, esi
                 call    ?OnProcessFrame@CXWnd@EQClasses@@QAEHXZ
                 pop     esi
                 leave
                 retn
_CMapViewWnd_OnProcessFrame endp

_MapViewMap_AddLabel proc near          ; CODE XREF: CMapToolbarWnd__WndNotification+10Ap

 arg_0           = dword ptr  8
 arg_4           = dword ptr  0Ch
 arg_8           = dword ptr  10h
 arg_C           = dword ptr  14h
 arg_10          = dword ptr  18h
 Source          = dword ptr  1Ch

                 push    ebp             ; public: void __thiscall MapViewMap::AddLabel(float,float,float,unsigned long,int,char *
                 mov     ebp, esp
                 push    esi
                 push    edi
                 mov     edi, ecx
                 push    34h             ; unsigned int
                 call    new
                 mov     esi, eax
                 pop     ecx
                 and     dword ptr [esi+4], 0
                 mov     eax, [edi+44h]
                 mov     [esi], eax
                 mov     eax, [edi+44h]
                 test    eax, eax
                 jz      short loc_436243
                 mov     [eax+4], esi

 loc_436243:                             ; CODE XREF: MapViewMap__AddLabel+1Fj
                 mov     eax, [ebp+arg_0]
                 mov     [edi+44h], esi
                 mov     [esi+8], eax
                 mov     eax, [ebp+arg_4]
                 mov     [esi+0Ch], eax
                 mov     eax, [ebp+arg_8]
                 mov     [esi+10h], eax
                 mov     eax, [ebp+arg_C]
                 mov     ecx, eax
                 push    [ebp+Source]    ; Str
                 shr     ecx, 18h
                 mov     [esi+17h], cl
                 mov     ecx, eax
                 shr     ecx, 10h
                 mov     [esi+16h], cl
                 mov     ecx, eax
                 shr     ecx, 8
                 mov     [esi+15h], cl
                 mov     [esi+14h], al
                 call    _strlen
                 inc     eax
                 push    eax             ; unsigned int
                 call    new
                 mov     ecx, [ebp+arg_10]
                 push    [ebp+Source]    ; Source
                 mov     [esi+1Ch], eax
                 mov     [esi+18h], ecx
                 mov     ecx, [edi+68h]
                 push    eax             ; Dest
                 mov     [esi+20h], ecx
                 call    _strcpy
                 add     esp, 10h
                 mov     ecx, edi
                 push    esi
                 call    _MapViewMap_RecalcLabelExtents
                 and     dword ptr [esi+2Ch], 0
                 and     dword ptr [esi+30h], 0
                 pop     edi
                 pop     esi
                 pop     ebp
                 retn    18h
 _MapViewMap_AddLabel endp


_MapViewMap_RecalcLabelExtents proc near
                                         ; CODE XREF: CMapToolbarWnd__WndNotification+197p
                                         ; MapViewMap__AddLabel+84p ...

 arg_0           = dword ptr  8

                 push    ebp             ; public: void __thiscall MapViewMap::RecalcLabelExtents(struct _mapviewlabel *
                 mov     ebp, esp
                 mov     eax, pinstCXWndManager ; class CXWndManager * g_pwndmg
                 mov     eax, [eax]
                 push    esi
                 mov     esi, [ebp+arg_0]
                 push    edi
                 mov     ecx, [esi+18h]
                 dec     ecx
                 cmp     ecx, [eax+0C8h]
                 jge     short loc_4362E2
                 test    ecx, ecx
                 jl      short loc_4362E2
                 mov     edx, [eax+0C4h]
                 test    edx, edx
                 jz      short loc_4362E2
                 lea     eax, [edx+ecx*4]
                 jmp     short loc_4362E8
 ; ---------------------------------------------------------------------------

 loc_4362E2:                             ; CODE XREF: MapViewMap__RecalcLabelExtents+17j
                                         ; MapViewMap__RecalcLabelExtents+1Bj ...
                 mov     eax, [eax+0C4h]

 loc_4362E8:                             ; CODE XREF: MapViewMap__RecalcLabelExtents+2Aj
                 mov     edi, [eax]
                 push    ecx
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    dword ptr [esi+1Ch]
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, edi
                 call    ?GetTextExtent@CTextureFont@EQClasses@@QBEHVCXStr@2@@Z
                 mov     ecx, edi
                 mov     [esi+24h], eax
                 call    ?GetHeight@CTextureFont@EQClasses@@QBEHXZ
                 mov     [esi+28h], eax
                 pop     edi
                 pop     esi
                 pop     ebp
                 retn    4
_MapViewMap_RecalcLabelExtents endp



_MapViewMap_Clear proc near             ; CODE XREF: CConfirmationDialog__ProcessYes+4AAp
                                         ; CMapViewWnd__SetCurrentZone+ADp
                 push    ebx             ; public: void __thiscall MapViewMap::Clear(void
                 push    esi
                 mov     esi, ecx
                 xor     ebx, ebx
                 push    edi
                 cmp     [esi+40h], ebx
                 jz      short loc_436033

 loc_436020:                             ; CODE XREF: MapViewMap__Clear+1Dj
                 mov     eax, [esi+40h]
                 push    eax
                 mov     edi, [eax]
                 call    operator__delete
                 cmp     edi, ebx
                 pop     ecx
                 mov     [esi+40h], edi
                 jnz     short loc_436020

 loc_436033:                             ; CODE XREF: MapViewMap__Clear+Aj
                 cmp     [esi+44h], ebx
                 jz      short loc_436056

 loc_436038:                             ; CODE XREF: MapViewMap__Clear+40j
                 mov     eax, [esi+44h]
                 push    dword ptr [eax+1Ch]
                 mov     edi, [eax]
                 call    operator__delete
                 push    dword ptr [esi+44h]
                 call    operator__delete
                 pop     ecx
                 cmp     edi, ebx
                 pop     ecx
                 mov     [esi+44h], edi
                 jnz     short loc_436038

 loc_436056:                             ; CODE XREF: MapViewMap__Clear+22j
                 mov     [esi+48h], bl
                 mov     [esi+5Ch], ebx
                 mov     [esi+60h], ebx
                 pop     edi
                 pop     esi
                 pop     ebx
                 retn
_MapViewMap_Clear endp

_MapViewMap_EndLine proc near           ; CODE XREF: CMapToolbarWnd__WndNotification+240p
                                         ; CMapViewWnd__DeactivateAutoMapping+43p ...

 var_10          = qword ptr -10h
 arg_0           = dword ptr  8
 arg_4           = dword ptr  0Ch
 arg_8           = dword ptr  10h

                 push    ebp             ; public: void __thiscall MapViewMap::EndLine(float,float,float
                 mov     ebp, esp
                 push    ebx
                 mov     ebx, ecx
                 push    esi
                 cmp     byte ptr [ebx+48h], 1
                 jnz     loc_43611E
                 fld     [ebp+arg_0]
                 fadd    dword ptr [ebx+8]
                 lea     esi, [ebx+4Ch]
                 push    ecx
                 push    ecx
                 fsubr   dword ptr [esi]
                 fstp    [esp+10h+var_10]
                 call    _fabs
                 fcomp   ds:__real@8@3ffee666660000000000 ; 0.900000 confirmed 
                 pop     ecx
                 pop     ecx
                 fnstsw  ax
                 sahf
                 ja      short loc_4360D2
                 fld     [ebp+arg_4]
                 fadd    dword ptr [ebx+0Ch]
                 push    ecx
                 push    ecx
                 fsubr   dword ptr [ebx+50h]
                 fstp    [esp+10h+var_10]
                 call    _fabs
                 fcomp   ds:__real@8@3ffee666660000000000 ; 0.900000 confirmed 
                 pop     ecx
                 pop     ecx
                 fnstsw  ax
                 sahf
                 jbe     short loc_43611E

 loc_4360D2:                             ; CODE XREF: MapViewMap__EndLine+31j
                 push    28h             ; unsigned int
                 call    new
                 and     dword ptr [eax+4], 0
                 pop     ecx
                 mov     ecx, [ebx+40h]
                 mov     [eax], ecx
                 mov     ecx, [ebx+40h]
                 test    ecx, ecx
                 jz      short loc_4360ED
                 mov     [ecx+4], eax

 loc_4360ED:                             ; CODE XREF: MapViewMap__EndLine+69j
                 push    edi
                 lea     edi, [eax+8]
                 mov     [ebx+40h], eax
                 mov     ecx, [ebp+arg_0]
                 movsd
                 movsd
                 movsd
                 lea     esi, [eax+14h]
                 lea     edi, [ebx+4Ch]
                 mov     [esi], ecx
                 mov     ecx, [ebp+arg_4]
                 mov     [eax+18h], ecx
                 mov     ecx, [ebp+arg_8]
                 mov     [eax+1Ch], ecx
                 mov     ecx, [ebx+58h]
                 mov     [eax+20h], ecx
                 mov     ecx, [ebx+68h]
                 mov     [eax+24h], ecx
                 movsd
                 movsd
                 movsd
                 pop     edi

 loc_43611E:                             ; CODE XREF: MapViewMap__EndLine+Bj
                                         ; MapViewMap__EndLine+51j
                 and     byte ptr [ebx+48h], 0
                 pop     esi
                 pop     ebx
                 pop     ebp
                 retn    0Ch
_MapViewMap_EndLine endp

CMapToolbarWnd__SetAutoMapButton proc near
                                         ; CODE XREF: CMapViewWnd__DeactivateAutoMapping+59p

 arg_0           = dword ptr  4

                 mov     ecx, [ecx+14Ch] ; public: void __thiscall CMapToolbarWnd::SetAutoMapButton(bool
                 test    ecx, ecx
                 jz      short locret_434956
                 push    [esp+arg_0]
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z

 locret_434956:                          ; CODE XREF: CMapToolbarWnd__SetAutoMapButton+8j
                 retn    4
 CMapToolbarWnd__SetAutoMapButton endp


_CMapViewWnd_DeactivateAutoMapping proc near
                                         ; CODE XREF: CMapToolbarWnd__WndNotification:loc_43492Bp
                                         ; CMapViewWnd__Init+1Aj ...

 var_10          = dword ptr -10h
 var_C           = dword ptr -0Ch
 var_8           = dword ptr -8

                 push    esi             ; public: void __thiscall CMapViewWnd::DeactivateAutoMapping(void
                 mov     esi, ecx
                 cmp     byte ptr [esi+135h], 1
                 jnz     short loc_43530C
                 and     byte ptr [esi+135h], 0
                 mov     eax, pinstLocalPlayer ; class EQPlayer * LocalPlaye
                 mov     eax, [eax]
                 push    ecx             ; int
                 fld     dword ptr [eax+0F0h] ; changed i think this is height
                 fmul    ds:__real@4@3ffea000000000000000 ; __real@4@3ffea00000000000000
                 fsubr   dword ptr [eax+50h] ; Z
                 fstp    [esp+8+var_8]
                 fld     dword ptr [eax+48h] ; Y
                 push    ecx             ; float
                 fchs
                 fstp    [esp+0Ch+var_C]
                 fld     dword ptr [eax+4Ch] ; X
                 push    ecx             ; float
                 lea     ecx, [esi+1A8h]
                 fchs
                 fstp    [esp+10h+var_10]
                 call    _MapViewMap_EndLine

 loc_43530C:                             ; CODE XREF: CMapViewWnd__DeactivateAutoMapping+Aj
                 mov     ecx, _g_pMapToolbarWnd ; class CMapToolbarWnd * g_pMapToolbarWn
				 test    ecx, ecx
                 jz      short loc_435322
                 mov     al, [esi+135h]
                 push    eax
                 call    CMapToolbarWnd__SetAutoMapButton

 loc_435322:                             ; CODE XREF: CMapViewWnd__DeactivateAutoMapping+50j
                 pop     esi
                 retn
_CMapViewWnd_DeactivateAutoMapping endp

_MapViewMap_StartLine proc near         ; CODE XREF: CMapToolbarWnd__WndNotification+1FEp
                                         ; CMapViewWnd__ActivateAutoMapping+49p ...

 arg_0           = dword ptr  4
 arg_4           = dword ptr  8
 arg_8           = dword ptr  0Ch

                 mov     eax, [esp+arg_0] ; public: void __thiscall MapViewMap::StartLine(float,float,float
                 mov     byte ptr [ecx+48h], 1
                 mov     [ecx+4Ch], eax
                 mov     eax, [esp+arg_4]
                 mov     [ecx+50h], eax
                 mov     eax, [esp+arg_8]
                 mov     [ecx+54h], eax
                 retn    0Ch
_MapViewMap_StartLine endp

_CMapViewWnd_ActivateAutoMapping proc near
                                         ; CODE XREF: CMapToolbarWnd__WndNotification+4E4p
                                         ; do_map:loc_4A5AC4p

 var_10          = dword ptr -10h
 var_C           = dword ptr -0Ch
 var_8           = dword ptr -8

                 push    esi             ; public: void __thiscall CMapViewWnd::ActivateAutoMapping(void
                 mov     esi, ecx
                 cmp     byte ptr [esi+135h], 0
                 jnz     short loc_4352C2
                 mov     eax, pinstLocalPlayer ; class EQPlayer * LocalPlaye
                 mov     eax, [eax] ; added
				 test    eax, eax
                 jz      short loc_4352C2
                 cmp     byte ptr [esi+1F0h], 1
                 jz      short loc_4352AF
                 fld     dword ptr [eax+0F0h] ; changed to F0 since its Unknown0x0f0
                 fmul    ds:__real@4@3ffea000000000000000 ; __real@4@3ffea00000000000000
                 push    ecx
                 fsubr   dword ptr [eax+50h] ; changed
                 fstp    [esp+8+var_8]
                 fld     dword ptr [eax+48h] ; Y
                 push    ecx
                 fchs
                 fstp    [esp+0Ch+var_C]
                 fld     dword ptr [eax+4Ch] ; X
                 push    ecx
                 lea     ecx, [esi+1A8h]
                 fchs
                 fstp    [esp+10h+var_10]
                 call    _MapViewMap_StartLine

 loc_4352AF:                             ; CODE XREF: CMapViewWnd__ActivateAutoMapping+1Cj
                 fld     qword ptr ds:__real@8@c00b9c40000000000000 ; __real@8@c00b9c4000000000000
                 mov     byte ptr [esi+135h], 1
                 fstp    qword ptr dbl_5ACD60

 loc_4352C2:                             ; CODE XREF: CMapViewWnd__ActivateAutoMapping+Aj
                                         ; CMapViewWnd__ActivateAutoMapping+13j
                 pop     esi
                 retn
_CMapViewWnd_ActivateAutoMapping endp

CMapToolbarWnd__Activate proc near      ; CODE XREF: CMapViewWnd__WndNotification+FCp
                                         ; CDisplay__ActivateMainUI+96p
                 push    esi
                 mov     esi, ecx
                 push    1
                 push    1
                 mov     byte ptr [esi+170h], 1
                 call    ?Show@CXWnd@EQClasses@@QAEH_N0@Z
                 pop     esi
                 retn
 CMapToolbarWnd__Activate endp

sub_5870B0      proc near               ; DATA XREF: .rdata:0059C83Co
                 lea     ecx, [ebp-10h]
                 jmp     ??1CXStr@EQClasses@@QAE@XZ
sub_5870B0      endp

sub_5870B8      proc near               ; DATA XREF: .rdata:0059C844o
                 lea     ecx, [ebp+8]
                 jmp     ??1CXStr@EQClasses@@QAE@XZ
sub_5870B8      endp

stru_59C818     dd 19930520h            ; DATA XREF: sub_5870C0o
                 dd 2
                 dd offset dword_59C838
                 dd 0
                 dd 0
                 dd 0
                 dd 0
                 dd 0
 dword_59C838    dd 0FFFFFFFFh           ; DATA XREF: .rdata:0059C820o
                 dd offset sub_5870B0
                 dd 0FFFFFFFFh
                 dd offset sub_5870B8

sub_5870C0      proc near               ; DATA XREF: CMapViewWnd__WndNotificationo
                 mov     eax, offset stru_59C818
                 jmp     ___CxxFrameHandler
sub_5870C0      endp

_CMapViewWnd_WndNotification proc near  ; DATA XREF: .rdata:00593D90o
 
 var_20          = dword ptr -20h
 var_1C          = dword ptr -1Ch
 var_10          = dword ptr -10h
 var_C           = dword ptr -0Ch
 var_4           = dword ptr -4
 arg_0           = dword ptr  8
 arg_4           = dword ptr  0Ch
 arg_8           = dword ptr  10h

				 push    ebp
				 mov     ebp, esp
				 push    0FFFFFFFFh ; we push this as well as 
                 push    eax ; a few of theese to fake the stack the ehprolog would populate 
                 push    eax ; since I had to rip it out...
                 push	 eax ; I should probably add a local exception handler at some point / mule
				 push    ecx 
                 push    esi
                 mov     esi, ecx
                 mov     al, [esi+134h]
                 test    al, al
                 jz      loc_435678
                 call    _CMapViewWnd_IsMappingEnabled
                 test    al, al
                 jz      loc_435678
                 cmp     [ebp+arg_4], 6
                 jz      loc_435678
                 cmp     [ebp+arg_4], 0Dh
                 push    ebx
                 mov     ebx, [ebp+arg_0]
                 jnz     loc_435406
                 mov     ecx, [esi+17Ch]
                 cmp     ebx, ecx
                 jnz     short loc_4353B2
                 mov     eax, [ecx]
                 lea     edx, [ebp+var_10]
                 push    edx
				 ;call    dword ptr [eax+110h]
                 call    dword ptr [eax+114h] ; CEditWnd__GetWindowtexta (changed)
                 and     [ebp+var_4], 0
                 lea     ecx, [ebp+var_10]
                 call    ?ConvertToInt@CXStr@EQClasses@@QAEHXZ
                 or      [ebp+var_4], 0FFFFFFFFh
                 cmp     [ebp+var_10], 0
                 mov     [esi+214h], eax
                 mov     byte ptr [esi+229h], 1
                 jz      loc_435667
                 push    [ebp+var_10]
                 lea     ecx, [ebp+var_10]
                 call    ?FreeRep@CXStr@EQClasses@@QAEXPAUCStrRep@2@@Z
                 jmp     loc_435667
 ; ---------------------------------------------------------------------------

 loc_4353B2:                             ; CODE XREF: CMapViewWnd__WndNotification+49j
                 mov     ecx, [esi+180h]
                 cmp     ebx, ecx
                 jnz     loc_435667
                 mov     eax, [ecx]
                 lea     edx, [ebp+arg_0]
                 push    edx
                 call    dword ptr [eax+114h] ; CEditWnd__GetWindowTextA (changed)
                 lea     ecx, [ebp+arg_0]
                 mov     [ebp+var_4], 1
                 call    ?ConvertToInt@CXStr@EQClasses@@QAEHXZ
                 or      [ebp+var_4], 0FFFFFFFFh
                 cmp     [ebp+arg_0], 0
                 mov     [esi+218h], eax
                 mov     byte ptr [esi+229h], 1
                 jz      short loc_4353FD
                 push    [ebp+arg_0]
                 lea     ecx, [ebp+arg_0]
                 call    ?FreeRep@CXStr@EQClasses@@QAEXPAUCStrRep@2@@Z

 loc_4353FD:                             ; CODE XREF: CMapViewWnd__WndNotification+CCj
                 and     [ebp+arg_0], 0
                 jmp     loc_435667
 ; ---------------------------------------------------------------------------

 loc_435406:                             ; CODE XREF: CMapViewWnd__WndNotification+3Bj
                 push    1
                 pop     ecx
                 cmp     [ebp+arg_4], ecx
                 jnz     loc_435667
                 cmp     ebx, [esi+154h]
                 jnz     short loc_43542A
                 mov     ecx, _g_pMapToolbarWnd ; class CMapToolbarWnd * g_pMapToolbarWn
				 test	 ecx,ecx
				 jz		 loc_435667
                 call    CMapToolbarWnd__Activate
                 jmp     loc_435667
 ; ---------------------------------------------------------------------------

 loc_43542A:                             ; CODE XREF: CMapViewWnd__WndNotification+F4j
                 cmp     ebx, [esi+14Ch]
                 jnz     short loc_435452
                 fld     dword ptr [esi+220h]
                 fmul    ds:__real@4@3fff8ccccd0000000000 ; __real@4@3fff8ccccd000000000

 loc_43543E:                             ; CODE XREF: CMapViewWnd__WndNotification+16Cj
                 push    ecx             ; float
                 lea     ecx, [esi+1A8h]
                 fstp    [esp+1Ch+var_1C]
                 call    __MapViewMap__SetZoom
                 jmp     loc_435667
 ; ---------------------------------------------------------------------------

 loc_435452:                             ; CODE XREF: CMapViewWnd__WndNotification+10Cj
                 cmp     ebx, [esi+150h]
                 jnz     short loc_435492
                 fld     dword ptr [esi+220h]
                 push    edi
                 lea     edi, [esi+220h]
                 fmul    ds:__real@4@3ffee8ba2e37021dc000 ; __real@4@3ffee8ba2e37021dc00
                 lea     ecx, [esi+1A8h]
                 push    ecx             ; float
                 fstp    [esp+20h+var_20]
                 call    __MapViewMap__SetZoom
                 fld     dword ptr [edi]
                 fcomp   ds:__real@4@3fff8000000000000000 ; __real@4@3fff800000000000000
                 pop     edi
                 fnstsw  ax
                 sahf
                 jnb     loc_435667
                 fld1
                 jmp     short loc_43543E
 ; ---------------------------------------------------------------------------

 loc_435492:                             ; CODE XREF: CMapViewWnd__WndNotification+134j
                 cmp     ebx, [esi+140h]
                 jnz     short loc_4354A6
                 add     dword ptr [esi+1CCh], 5
                 jmp     loc_435667
 ; ---------------------------------------------------------------------------

 loc_4354A6:                             ; CODE XREF: CMapViewWnd__WndNotification+174j
                 cmp     ebx, [esi+144h]
                 jnz     short loc_4354BA
                 add     dword ptr [esi+1CCh], 0FFFFFFFBh
                 jmp     loc_435667
 ; ---------------------------------------------------------------------------

 loc_4354BA:                             ; CODE XREF: CMapViewWnd__WndNotification+188j
                 cmp     ebx, [esi+138h]
                 jnz     short loc_4354CE
                 add     dword ptr [esi+1C8h], 5
                 jmp     loc_435667
 ; ---------------------------------------------------------------------------

 loc_4354CE:                             ; CODE XREF: CMapViewWnd__WndNotification+19Cj
                 cmp     ebx, [esi+13Ch]
                 jnz     short loc_4354E2
                 add     dword ptr [esi+1C8h], 0FFFFFFFBh
                 jmp     loc_435667
 ; ---------------------------------------------------------------------------

 loc_4354E2:                             ; CODE XREF: CMapViewWnd__WndNotification+1B0j
                 cmp     ebx, [esi+148h]
                 jnz     short loc_4354FD
                 and     dword ptr [esi+1C8h], 0
                 and     dword ptr [esi+1CCh], 0
                 jmp     loc_435667
 ; ---------------------------------------------------------------------------

 loc_4354FD:                             ; CODE XREF: CMapViewWnd__WndNotification+1C4j
                 cmp     ebx, [esi+198h]
                 jnz     short loc_435510
                 mov     [esi+210h], ecx
                 jmp     loc_435667
 ; ---------------------------------------------------------------------------

 loc_435510:                             ; CODE XREF: CMapViewWnd__WndNotification+1DFj
                 cmp     ebx, [esi+19Ch]
                 jnz     short loc_435527
                 mov     dword ptr [esi+210h], 2
                 jmp     loc_435667
 ; ---------------------------------------------------------------------------

 loc_435527:                             ; CODE XREF: CMapViewWnd__WndNotification+1F2j
                 cmp     ebx, [esi+1A0h]
                 jnz     short loc_43553E
                 mov     dword ptr [esi+210h], 3
                 jmp     loc_435667
 ; ---------------------------------------------------------------------------

 loc_43553E:                             ; CODE XREF: CMapViewWnd__WndNotification+209j
                 mov     eax, [esi+188h]
                 cmp     ebx, eax
                 jnz     short loc_435568
                 cmp     byte ptr [eax+108h], 0
                 jz      short loc_43555C
                 or      [esi+20Ch], ecx
                 jmp     loc_43561C
 ; ---------------------------------------------------------------------------

 loc_43555C:                             ; CODE XREF: CMapViewWnd__WndNotification+22Bj
                 and     dword ptr [esi+20Ch], 0FFFFFFFEh
                 jmp     loc_43561C
 ; ---------------------------------------------------------------------------

 loc_435568:                             ; CODE XREF: CMapViewWnd__WndNotification+222j
                 mov     eax, [esi+18Ch]
                 cmp     ebx, eax
                 jnz     short loc_435593
                 cmp     byte ptr [eax+108h], 0
                 jz      short loc_435587
                 or      dword ptr [esi+20Ch], 2
                 jmp     loc_43561C
 ; ---------------------------------------------------------------------------

 loc_435587:                             ; CODE XREF: CMapViewWnd__WndNotification+255j
                 and     dword ptr [esi+20Ch], 0FFFFFFFDh
                 jmp     loc_43561C
 ; ---------------------------------------------------------------------------

 loc_435593:                             ; CODE XREF: CMapViewWnd__WndNotification+24Cj
                 mov     eax, [esi+190h]
                 cmp     ebx, eax
                 jnz     short loc_4355B8
                 cmp     byte ptr [eax+108h], 0
                 jz      short loc_4355AF
                 or      dword ptr [esi+20Ch], 4
                 jmp     short loc_43561C
 ; ---------------------------------------------------------------------------

 loc_4355AF:                             ; CODE XREF: CMapViewWnd__WndNotification+280j
                 and     dword ptr [esi+20Ch], 0FFFFFFFBh
                 jmp     short loc_43561C
 ; ---------------------------------------------------------------------------

 loc_4355B8:                             ; CODE XREF: CMapViewWnd__WndNotification+277j
                 mov     eax, [esi+194h]
                 cmp     ebx, eax
                 jnz     short loc_4355DD
                 cmp     byte ptr [eax+108h], 0
                 jz      short loc_4355D4
                 or      dword ptr [esi+20Ch], 8
                 jmp     short loc_43561C
 ; ---------------------------------------------------------------------------

 loc_4355D4:                             ; CODE XREF: CMapViewWnd__WndNotification+2A5j
                 and     dword ptr [esi+20Ch], 0FFFFFFF7h
                 jmp     short loc_43561C
 ; ---------------------------------------------------------------------------

 loc_4355DD:                             ; CODE XREF: CMapViewWnd__WndNotification+29Cj
                 mov     eax, [esi+184h] ; MVW_ZFilterButton
                 cmp     ebx, eax
                 jnz     short loc_435602
                 cmp     byte ptr [eax+108h], 0 ; Checked in CXW_NO_VTABLE
                 jz      short loc_4355F9
                 mov     byte ptr [esi+21Ch], 1
                 jmp     short loc_43561C
 ; ---------------------------------------------------------------------------

 loc_4355F9:                             ; CODE XREF: CMapViewWnd__WndNotification+2CAj
                 and     byte ptr [esi+21Ch], 0
                 jmp     short loc_43561C
 ; ---------------------------------------------------------------------------

 loc_435602:                             ; CODE XREF: CMapViewWnd__WndNotification+2C1j
                 mov     eax, [esi+178h]
                 cmp     ebx, eax
                 jnz     short loc_43562E
                 cmp     byte ptr [eax+108h], 0
                 jz      short loc_435625
                 mov     byte ptr [esi+228h], 1

 loc_43561C:                             ; CODE XREF: CMapViewWnd__WndNotification+233j
                                         ; CMapViewWnd__WndNotification+23Fj ...
                 mov     byte ptr [esi+229h], 1
                 jmp     short loc_435667
 ; ---------------------------------------------------------------------------

 loc_435625:                             ; CODE XREF: CMapViewWnd__WndNotification+2EFj
                 and     byte ptr [esi+228h], 0
                 jmp     short loc_43561C
 ; ---------------------------------------------------------------------------

 loc_43562E:                             ; CODE XREF: CMapViewWnd__WndNotification+2E6j
                 cmp     ebx, [esi+1A4h]
                 jnz     short loc_435667
                 mov     eax, _CurrentMapLabel
                 test    eax, eax
                 jz      short loc_435647
                 mov     [esi+208h], eax
                 jmp     short loc_43564E
 ; ---------------------------------------------------------------------------

 loc_435647:                             ; CODE XREF: CMapViewWnd__WndNotification+319j
                 and     dword ptr [esi+208h], 0

 loc_43564E:                             ; CODE XREF: CMapViewWnd__WndNotification+321j
                 mov     eax, dword_5DF7D0
                 test    eax, eax
                 jz      short loc_43565A
                 push    eax
                 jmp     short loc_43565C
 ; ---------------------------------------------------------------------------

 loc_43565A:                             ; CODE XREF: CMapViewWnd__WndNotification+331j
                 push    0

 loc_43565C:                             ; CODE XREF: CMapViewWnd__WndNotification+334j
                 lea     ecx, [esi+1A8h]
                 call    _MapViewMap_SetMarkedLine

 loc_435667:                             ; CODE XREF: CMapViewWnd__WndNotification+78j
                                         ; CMapViewWnd__WndNotification+89j ...
                 push    [ebp+arg_8]
                 mov     ecx, esi
                 push    [ebp+arg_4]
                 push    ebx
                 call    ?WndNotification@CSidlScreenWnd@EQClasses@@QAEHPAVCXWnd@2@IPAX@Z
                 pop     ebx
                 jmp     short loc_43567A
 ; ---------------------------------------------------------------------------

 loc_435678:                             ; CODE XREF: CMapViewWnd__WndNotification+16j
                                         ; CMapViewWnd__WndNotification+23j ...
                 xor     eax, eax

 loc_43567A:                             ; CODE XREF: CMapViewWnd__WndNotification+352j
                 mov     ecx, [ebp+var_C]
                 pop     esi
                 leave
                 retn	 0Ch
_CMapViewWnd_WndNotification endp

_MapViewMap_Save proc near              ; CODE XREF: CMapToolbarWnd__WndNotification+3B1p
                                         ; CMapViewWnd__SetCurrentZone+27p

 File            = dword ptr  4

                 push    esi             ; public: void __thiscall MapViewMap::Save(char *
                 push    edi
                 push    1
                 mov     edi, ecx
                 pop     esi

 loc_437D4F:                             ; CODE XREF: MapViewMap__Save+17j
                 push    esi             ; int
                 mov     ecx, edi
                 push    [esp+0Ch+File]  ; File
                 call    MapViewMap__SaveEx
                 inc     esi
                 cmp     esi, 3
                 jle     short loc_437D4F
                 pop     edi
                 pop     esi
                 retn    4
_MapViewMap_Save endp

MapViewMap__SaveEx proc near            ; CODE XREF: MapViewMap__Save+Ep

 var_248         = qword ptr -248h
 var_240         = qword ptr -240h
 var_238         = qword ptr -238h
 var_230         = qword ptr -230h
 var_228         = qword ptr -228h
 var_220         = qword ptr -220h
 Args            = byte ptr -200h
 aStr             = byte ptr -100h
 File            = dword ptr  8
 arg_4           = dword ptr  0Ch

                 push    ebp             ; public: void __thiscall MapViewMap::SaveEx(char *,int
                 mov     ebp, esp
                 sub     esp, 200h
                 push    ebx
                 mov     ebx, [ebp+arg_4]
                 push    edi
                 mov     edi, ecx
                 test    ebx, ebx
                 jz      short loc_437D94
                 push    ebx
                 lea     eax, [ebp+Args]
                 push    [ebp+File]
                 push    offset aMapsS_D_txt ; "maps\\%s_%d.txt"
                 push    eax             ; Dest
                 call    _sprintf
                 add     esp, 10h
                 jmp     short loc_437DAB
 ; ---------------------------------------------------------------------------

 loc_437D94:                             ; CODE XREF: MapViewMap__SaveEx+12j
                 push    [ebp+File]
                 lea     eax, [ebp+Args]
                 push    offset aMapsS_txt ; "maps\\%s.txt"
                 push    eax             ; Dest
                 call    _sprintf
                 add     esp, 0Ch

 loc_437DAB:                             ; CODE XREF: MapViewMap__SaveEx+2Cj
                 lea     eax, [ebp+Args]
                 push    offset aWt      ; "wt"
                 push    eax             ; Filename
                 call    _fopen
                 pop     ecx
                 mov     [ebp+File], eax
                 test    eax, eax
                 pop     ecx
                 jz      loc_437EDB
                 push    esi
                 mov     esi, [edi+40h]

 loc_437DCD:                             ; CODE XREF: MapViewMap__SaveEx+C1j
                 test    esi, esi
                 jz      short loc_437E29
                 cmp     [esi+24h], ebx
                 jnz     short loc_437E25
                 movzx   eax, byte ptr [esi+20h]
                 fld     dword ptr [esi+1Ch]
                 push    eax
                 movzx   eax, byte ptr [esi+21h]
                 push    eax
                 movzx   eax, byte ptr [esi+22h]
                 push    eax
                 push    ecx
                 push    ecx
                 fstp    [esp+220h+var_220]
                 fld     dword ptr [esi+18h]
                 push    ecx
                 push    ecx
                 fstp    [esp+228h+var_228]
                 fld     dword ptr [esi+14h]
                 push    ecx
                 push    ecx
                 fstp    [esp+230h+var_230]
                 fld     dword ptr [esi+10h]
                 push    ecx
                 push    ecx
                 fstp    [esp+238h+var_238]
                 fld     dword ptr [esi+0Ch]
                 push    ecx
                 push    ecx
                 fstp    [esp+240h+var_240]
                 fld     dword ptr [esi+8]
                 push    ecx
                 push    ecx
                 fstp    [esp+248h+var_248]
                 push    offset aL0_4f0_4f0_4f0 ; "L %0.4f, %0.4f, %0.4f,  %0.4f, %0.4f, %"...
                 push    [ebp+File]      ; File
                 call    _fprintf
                 add     esp, 44h

 loc_437E25:                             ; CODE XREF: MapViewMap__SaveEx+6Ej
                 mov     esi, [esi]
                 jmp     short loc_437DCD
 ; ---------------------------------------------------------------------------

 loc_437E29:                             ; CODE XREF: MapViewMap__SaveEx+69j
                 mov     esi, [edi+44h]

 loc_437E2C:                             ; CODE XREF: MapViewMap__SaveEx+164j
                 test    esi, esi
                 jz      loc_437ECF
                 cmp     [esi+20h], ebx
                 jnz     loc_437EC8
                 push    dword ptr [esi+1Ch] ; Source
                 lea     eax, [ebp+aStr]
                 push    eax             ; Dest
                 call    _strcpy
                 lea     eax, [ebp+aStr]
                 xor     edi, edi
                 push    eax             ; Str
                 call    _strlen
                 add     esp, 0Ch
                 test    eax, eax
                 jbe     short loc_437E87

 loc_437E61:                             ; CODE XREF: MapViewMap__SaveEx+11Fj
                 cmp     [ebp+edi+aStr], 20h
                 lea     eax, [ebp+edi+aStr]
                 jnz     short loc_437E75
                 mov     byte ptr [eax], 5Fh

 loc_437E75:                             ; CODE XREF: MapViewMap__SaveEx+10Aj
                 lea     eax, [ebp+aStr]
                 inc     edi
                 push    eax             ; Str
                 call    _strlen
                 cmp     edi, eax
                 pop     ecx
                 jb      short loc_437E61

 loc_437E87:                             ; CODE XREF: MapViewMap__SaveEx+F9j
                 lea     eax, [ebp+aStr]
                 push    eax
                 movzx   eax, byte ptr [esi+14h]
                 fld     dword ptr [esi+10h]
                 push    dword ptr [esi+18h]
                 push    eax
                 movzx   eax, byte ptr [esi+15h]
                 push    eax
                 movzx   eax, byte ptr [esi+16h]
                 push    eax
                 push    ecx
                 push    ecx
                 fstp    [esp+228h+var_228]
                 fld     dword ptr [esi+0Ch]
                 push    ecx
                 push    ecx
                 fstp    [esp+230h+var_230]
                 fld     dword ptr [esi+8]
                 push    ecx
                 push    ecx
                 fstp    [esp+238h+var_238]
                 push    offset aP0_4f0_4f0_4fD ; "P %0.4f, %0.4f, %0.4f,  %d, %d, %d,  %d"...
                 push    [ebp+File]      ; File
                 call    _fprintf
                 add     esp, 34h

 loc_437EC8:                             ; CODE XREF: MapViewMap__SaveEx+D1j
                 mov     esi, [esi]
                 jmp     loc_437E2C
 ; ---------------------------------------------------------------------------

 loc_437ECF:                             ; CODE XREF: MapViewMap__SaveEx+C8j
                 push    [ebp+File]      ; File
                 call    _fclose
                 pop     ecx
                 pop     esi
                 jmp     short loc_437EEE
 ; ---------------------------------------------------------------------------

 loc_437EDB:                             ; CODE XREF: MapViewMap__SaveEx+5Dj
                 lea     eax, [ebp+Args]
                 push    eax             ; Args
                 push    offset aFailedToOpenSF ; "Failed to open %s for writing in MapVie"...
                 call    _DebugSpew
                 pop     ecx
                 pop     ecx

 loc_437EEE:                             ; CODE XREF: MapViewMap__SaveEx+173j
                 pop     edi
                 pop     ebx
                 leave
                 retn    8
 MapViewMap__SaveEx endp


 ; =============== S U B R O U T I N E =======================================


 MapViewMap__Load proc near              ; CODE XREF: CMapViewWnd__SetCurrentZone+1AEp

 arg_0           = dword ptr  4

                 push    esi             ; public: void __thiscall MapViewMap::Load(char *
                 push    edi
                 mov     edi, ecx
                 xor     esi, esi

 loc_437EFA:                             ; CODE XREF: MapViewMap__Load+16j
                 push    esi
                 mov     ecx, edi
                 push    [esp+0Ch+arg_0]
                 call    MapViewMap__LoadEx
                 inc     esi
                 cmp     esi, 3
                 jle     short loc_437EFA
                 mov     byte ptr [edi+81h], 1
                 pop     edi
                 pop     esi
                 retn    4
 MapViewMap__Load endp


 ; =============== S U B R O U T I N E =======================================

 ; Attributes: bp-based frame

 MapViewMap__LoadEx proc near            ; CODE XREF: MapViewMap__Load+Dp

 Buf             = byte ptr -60Ch
 Src             = byte ptr -60Ah
 var_20D         = byte ptr -20Dh
 Filename        = byte ptr -20Ch
 Source          = byte ptr -10Ch
 var_D           = byte ptr -0Dh
 var_C           = dword ptr -0Ch
 var_8           = dword ptr -8
 var_4           = dword ptr -4
 arg_0           = dword ptr  8
 arg_4           = dword ptr  0Ch

                 push    ebp             ; public: bool __thiscall MapViewMap::LoadEx(char *,int
                 mov     ebp, esp
                 sub     esp, 60Ch
                 cmp     [ebp+arg_4], 0
                 push    ebx
                 push    edi
                 mov     edi, ecx
                 jz      short loc_437F47
                 push    [ebp+arg_4]
                 lea     eax, [ebp+Filename]
                 push    [ebp+arg_0]
                 push    offset aMapsS_D_txt ; "maps\\%s_%d.txt"
                 push    eax             ; Dest
                 call    _sprintf
                 add     esp, 10h
                 jmp     short loc_437F5E
 ; ---------------------------------------------------------------------------

 loc_437F47:                             ; CODE XREF: MapViewMap__LoadEx+11j
                 push    [ebp+arg_0]
                 lea     eax, [ebp+Filename]
                 push    offset aMapsS_txt ; "maps\\%s.txt"
                 push    eax             ; Dest
                 call    _sprintf
                 add     esp, 0Ch

 loc_437F5E:                             ; CODE XREF: MapViewMap__LoadEx+2Dj
                 lea     eax, [ebp+Filename]
                 push    offset aRt      ; "rt"
                 push    eax             ; Filename
                 call    _fopen
                 mov     ebx, eax
                 pop     ecx
                 test    ebx, ebx
                 pop     ecx
                 mov     [ebp+var_C], ebx
                 jz      loc_43814C
                 test    byte ptr [ebx+0Ch], 10h
                 jnz     loc_438141
                 push    esi

 loc_437F89:                             ; CODE XREF: MapViewMap__LoadEx+222j
                 xor     eax, eax
                 push    ebx             ; File
                 and     [ebp+var_20D], al
                 and     [ebp+Buf], al
                 mov     [ebp+arg_0], eax
                 mov     [ebp+var_4], eax
                 mov     [ebp+var_8], eax
                 lea     eax, [ebp+Buf]
                 push    3FEh            ; MaxCount
                 push    eax             ; Buf
                 call    _fgets
                 movsx   eax, [ebp+Buf]
                 push    eax             ; C
                 call    _toupper
                 add     esp, 10h
                 cmp     eax, 4Ch
                 jnz     short loc_438040
                 push    28h             ; unsigned int
                 call    new
                 mov     esi, eax
                 pop     ecx
                 and     dword ptr [esi+4], 0
                 mov     eax, [edi+40h]
                 mov     [esi], eax
                 mov     eax, [edi+40h]
                 test    eax, eax
                 jz      short loc_437FE4
                 mov     [eax+4], esi

 loc_437FE4:                             ; CODE XREF: MapViewMap__LoadEx+C7j
                 lea     eax, [ebp+var_8]
                 mov     [edi+40h], esi
                 push    eax
                 lea     eax, [ebp+var_4]
                 push    eax
                 lea     eax, [ebp+arg_0]
                 push    eax
                 lea     eax, [esi+1Ch]
                 push    eax
                 lea     eax, [esi+18h]
                 push    eax
                 lea     eax, [esi+14h]
                 push    eax
                 lea     eax, [esi+10h]
                 push    eax
                 lea     eax, [esi+0Ch]
                 push    eax
                 lea     eax, [esi+8]
                 push    eax
                 lea     eax, [ebp+Src]
                 push    offset aFFFFFFDDD ; "%f, %f, %f,  %f, %f, %f,  %d, %d, %d"
                 push    eax             ; Src
                 call    _sscanf
                 mov     al, byte ptr [ebp+arg_0]
                 add     esp, 2Ch
                 mov     [esi+22h], al
                 mov     al, byte ptr [ebp+var_4]
                 mov     [esi+21h], al
                 mov     al, byte ptr [ebp+var_8]
                 or      byte ptr [esi+23h], 0FFh
                 mov     [esi+20h], al
                 mov     eax, [ebp+arg_4]
                 mov     [esi+24h], eax
                 jmp     loc_438136
 ; ---------------------------------------------------------------------------

 loc_438040:                             ; CODE XREF: MapViewMap__LoadEx+ADj
                 movsx   eax, [ebp+Buf]
                 push    eax             ; C
                 call    _toupper
                 cmp     eax, 50h
                 pop     ecx
                 jnz     loc_438136
                 push    34h             ; unsigned int
                 call    new
                 mov     esi, eax
                 xor     ebx, ebx
                 pop     ecx
                 mov     [esi+4], ebx
                 mov     eax, [edi+44h]
                 mov     [esi], eax
                 mov     eax, [edi+44h]
                 cmp     eax, ebx
                 jz      short loc_438075
                 mov     [eax+4], esi

 loc_438075:                             ; CODE XREF: MapViewMap__LoadEx+158j
                 lea     eax, [ebp+Source]
                 mov     [edi+44h], esi
                 push    eax
                 lea     eax, [esi+18h]
                 push    eax
                 lea     eax, [ebp+var_8]
                 push    eax
                 lea     eax, [ebp+var_4]
                 push    eax
                 lea     eax, [ebp+arg_0]
                 push    eax
                 lea     eax, [esi+10h]
                 push    eax
                 lea     eax, [esi+0Ch]
                 push    eax
                 lea     eax, [esi+8]
                 push    eax
                 lea     eax, [ebp+Src]
                 push    offset aFFFDDDD256s ; "%f, %f, %f,  %d, %d, %d,  %d,  %256s"
                 push    eax             ; Src
                 call    _sscanf
                 mov     al, byte ptr [ebp+arg_0]
                 mov     [esi+16h], al
                 mov     al, byte ptr [ebp+var_4]
                 mov     [esi+15h], al
                 mov     al, byte ptr [ebp+var_8]
                 or      byte ptr [esi+17h], 0FFh
                 mov     [esi+14h], al
                 and     [ebp+var_D], 0
                 lea     eax, [ebp+Source]
                 push    eax             ; Str
                 call    _strlen
                 add     esp, 2Ch
                 test    eax, eax
                 jbe     short loc_4380FF

 loc_4380D9:                             ; CODE XREF: MapViewMap__LoadEx+1E5j
                 cmp     [ebp+ebx+Source], 5Fh
                 lea     eax, [ebp+ebx+Source]
                 jnz     short loc_4380ED
                 mov     byte ptr [eax], 20h

 loc_4380ED:                             ; CODE XREF: MapViewMap__LoadEx+1D0j
                 lea     eax, [ebp+Source]
                 inc     ebx
                 push    eax             ; Str
                 call    _strlen
                 cmp     ebx, eax
                 pop     ecx
                 jb      short loc_4380D9

 loc_4380FF:                             ; CODE XREF: MapViewMap__LoadEx+1BFj
                 lea     eax, [ebp+Source]
                 push    eax             ; Str
                 call    _strlen
                 inc     eax
                 push    eax             ; unsigned int
                 call    new
                 lea     ecx, [ebp+Source]
                 mov     [esi+1Ch], eax
                 push    ecx             ; Source
                 push    eax             ; Dest
                 call    _strcpy
                 mov     eax, [ebp+arg_4]
                 add     esp, 10h
                 mov     ecx, edi
                 mov     [esi+20h], eax
                 push    esi
                 call    _MapViewMap_RecalcLabelExtents
                 mov     ebx, [ebp+var_C]

 loc_438136:                             ; CODE XREF: MapViewMap__LoadEx+123j
                                         ; MapViewMap__LoadEx+139j
                 test    byte ptr [ebx+0Ch], 10h
                 jz      loc_437F89
                 pop     esi

 loc_438141:                             ; CODE XREF: MapViewMap__LoadEx+6Aj
                 push    ebx             ; File
                 call    _fclose
                 pop     ecx
                 mov     al, 1
                 jmp     short loc_43814E
 ; ---------------------------------------------------------------------------

 loc_43814C:                             ; CODE XREF: MapViewMap__LoadEx+60j
                 xor     al, al

 loc_43814E:                             ; CODE XREF: MapViewMap__LoadEx+232j
                 pop     edi
                 pop     ebx
                 leave
                 retn    8
 MapViewMap__LoadEx endp
__CMapViewWnd__Init proc near             ; CODE XREF: CMapViewWnd__CMapViewWnd+457p
                                         ; CMapViewWnd__Activate+3Fp ...
                 fld     ds:__real@8@c00b9c40000000000000 ; private: void __thiscall CMapViewWnd::Init(void
                 and     dword_5DF7D0, 0
                 and     _CurrentMapLabel, 0
                 fstp    dbl_5ACD60
                 jmp     _CMapViewWnd_DeactivateAutoMapping
__CMapViewWnd__Init endp

_MapViewMap_SetMarkedLineColor proc near
                                         ; CODE XREF: CMapToolbarWnd__WndNotification+43p

 var_4           = dword ptr -4
 arg_0           = dword ptr  8

                 push    ebp             ; public: void __thiscall MapViewMap::SetMarkedLineColor(unsigned long
                 mov     ebp, esp
                 push    ecx
                 mov     ecx, [ecx+5Ch]
                 test    ecx, ecx
                 jz      short locret_438216
                 mov     edx, [ebp+arg_0]
                 push    ebx
                 mov     [ebp+arg_0], edx
                 mov     [ebp+var_4], edx
                 shr     [ebp+arg_0], 10h
                 shr     [ebp+var_4], 8
                 push    esi

 loc_4381EF:                             ; CODE XREF: MapViewMap__SetMarkedLineColor+41j
                 mov     esi, [ecx+4]
                 lea     eax, [ecx+4]
                 mov     bl, byte ptr [ebp+arg_0]
                 or      byte ptr [esi+23h], 0FFh
                 mov     esi, [eax]
                 mov     [esi+22h], bl
                 mov     esi, [eax]
                 mov     bl, byte ptr [ebp+var_4]
                 mov     [esi+21h], bl
                 mov     eax, [eax]
                 mov     [eax+20h], dl
                 mov     ecx, [ecx]
                 test    ecx, ecx
                 jnz     short loc_4381EF
                 pop     esi
                 pop     ebx

 locret_438216:                          ; CODE XREF: MapViewMap__SetMarkedLineColor+9j
                 leave
                 retn    4
_MapViewMap_SetMarkedLineColor endp


_MapViewMap_GetMarkedLineColor proc near
                                         ; CODE XREF: CMapToolbarWnd__WndNotification+4CAp
                 mov     ecx, [ecx+5Ch]  ; public: unsigned long __thiscall MapViewMap::GetMarkedLineColor(void
                 xor     eax, eax
                 test    ecx, ecx
                 jz      short locret_438237
                 mov     eax, [ecx+4]
                 xor     ecx, ecx
                 mov     ch, [eax+22h]
                 mov     cl, [eax+21h]
                 movzx   eax, byte ptr [eax+20h]
                 shl     ecx, 8
                 or      eax, ecx

 locret_438237:                          ; CODE XREF: MapViewMap__GetMarkedLineColor+7j
                 retn
_MapViewMap_GetMarkedLineColor endp

__CMapViewWnd__SetCurrentZone proc near   ; CODE XREF: CMapViewWnd__CMapViewWnd+50Ep
                                         ; CDisplay__ReloadUI+1B0p ...

 var_108         = byte ptr -108h
 var_8           = dword ptr -8
 var_4           = dword ptr -4
 arg_0           = dword ptr  8
 arg_4           = dword ptr  0Ch
 arg_8           = dword ptr  10h

                 push    ebp             ; public: void __thiscall CMapViewWnd::SetCurrentZone(enum EQZoneIndex,struct T3D_XYZ *,struct T3D_XYZ *
                 mov     ebp, esp
                 sub     esp, 108h
                 push    ebx
                 push    esi
                 push    edi
                 mov     edi, ecx
                 cmp     byte ptr [edi+158h], 0
                 lea     esi, [edi+158h]
                 mov     [ebp+var_4], esi
                 jz      short loc_435A47
                 push    esi             ; File
                 lea     ecx, [edi+1A8h]
                 call    _MapViewMap_Save

 loc_435A47:                             ; CODE XREF: CMapViewWnd__SetCurrentZone+1Ej
                 mov     eax, [ebp+arg_0]
                 mov     ecx, 3E8h
                 cmp     eax, ecx
                 jle     short loc_435A58
                 and     eax, 0FFFFh

 loc_435A58:                             ; CODE XREF: CMapViewWnd__SetCurrentZone+36j
                 xor     ebx, ebx
                 cmp     eax, ebx
                 jle     short loc_435A6E
                 cmp     eax, ecx
                 jg      short loc_435A6E
                 mov     ecx, pinstWorldData ; class EQWorldData * EQTimeDat
                 mov     ecx, [ecx]
                 mov     eax, [ecx+eax*4+18h] ; used to be 1c (changed)
                 jmp     short loc_435A70
 ; ---------------------------------------------------------------------------

 loc_435A6E:                             ; CODE XREF: CMapViewWnd__SetCurrentZone+41j
                                         ; CMapViewWnd__SetCurrentZone+45j
                 xor     eax, eax

 loc_435A70:                             ; CODE XREF: CMapViewWnd__SetCurrentZone+51j
                 cmp     eax, ebx
                 jz      short loc_435AB1
                 push    ebx
                 push    ebx
                 push    ebx
                 push    ebx
                 push    ebx
                 push    ebx
                 push    ebx
                 add     eax, 8Dh ; long zone name (confirmed)
                 push    ebx
                 push    eax
                 lea     eax, [ebp+var_108]
                 push    1A49h
                 push    eax
                 call    ?build_token_string_PARAM@EQUtil@EQClasses@@QAAPADPADH000000000@Z
                 add     esp, 28h
                 lea     eax, [ebp+var_108]
                 mov     ecx, esp
                 mov     [ebp+var_8], esp
                 push    eax
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     eax, [edi]
                 mov     ecx, edi
                 call    dword ptr [eax+0ECh] ; CEditWnd__SetWindowTextA

 loc_435AB1:                             ; CODE XREF: CMapViewWnd__SetCurrentZone+57j
                 mov     ecx, pinstWorldData ; class EQWorldData * EQTimeDat
                 mov     ecx, [ecx]
                 push    esi             ; Dest
                 push    [ebp+arg_0]     ; int
                 call    ?GetGeometryNameFromIndex@EQWorldData@EQClasses@@QBE_NW4EQZoneIndex@2@PAD@Z
                 lea     esi, [edi+1A8h]
                 mov     ecx, esi
                 call    _MapViewMap_Clear
                 mov     ecx, edi
                 call    _CMapViewWnd_DeactivateAutoMapping
                 or      dword ptr [esi+64h], 1 ; esi at this point: 0x03F6909C       -1299.00000      -2998.00000       1499.00000       867.000000  .`¢Ä.`;Å.`»D.ÀXD
												;					 0x03F690AC        472.000000       360.000000       20.0000000       20.0000000  ..ìC..´C.. A.. A
                 mov     byte ptr [esi+81h], 1 ; this is full esi :
												;0x03F6909C  00 60 a2 c4 00 60 3b c5 00 60 bb 44 00 c0 58 44  .`¢Ä.`;Å.`»D.ÀXD
												;0x03F690AC  00 00 ec 43 00 00 b4 43 00 00 a0 41 00 00 a0 41  ..ìC..´C.. A.. A
												;0x03F690BC  00 00 00 00 00 00 00 00 63 68 6f 72 54 6f 54 6f  ........chorToTo
												;0x03F690CC  70 3e 74 72 75 65 3c 2f 54 6f 70 41 6e 63 68 6f  p>true</TopAncho
												;0x03F690DC  00 00 00 00 00 00 00 00 00 09 09 3c 42 6f 74 74  ...........<Bott
												;0x03F690EC  6f 6d 41 6e 63 68 6f 72 00 00 00 ff 00 00 00 00  omAnchor...ÿ....
												;0x03F690FC  00 00 00 00 0f 00 00 00 01 00 00 00 0a 00 00 00  ................
												;0x03F6910C  0a 00 00 00 00 3e 0d 0a 00 00 80 3f ee 0a 00 00  .....>....€?î...
												;0x03F6911C  00 01 01 6f 03 00 00 00 65 66 74 3e c7 c2 df 1c  ...o....eft>ÇÂß.
												;0x03F6912C  be 12 10 08 60 9f 65 00 00 10 ab 12 00 00 00 00  ....`Ÿe...«.....
												;0x03F6913C  d0 07 00 00 f4 01 00 00 ff 01 00 01 01 00 5f 62  Ð...ô...ÿ....._b
												;0x03F6914C  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................

                 or      dword ptr [esi+64h], 2
                 mov     byte ptr [esi+81h], 1
                 or      dword ptr [esi+64h], 4
                 mov     byte ptr [esi+81h], 1
                 or      dword ptr [esi+64h], 8
                 mov     byte ptr [esi+81h], 1
                 mov     ecx, [edi+188h]
                 cmp     ecx, ebx
                 jz      short loc_435B11
                 push    1
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z

 loc_435B11:                             ; CODE XREF: CMapViewWnd__SetCurrentZone+EDj
                 mov     ecx, [edi+18Ch]
                 cmp     ecx, ebx
                 jz      short loc_435B22
                 push    1
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z

 loc_435B22:                             ; CODE XREF: CMapViewWnd__SetCurrentZone+FEj
                 mov     ecx, [edi+190h]
                 cmp     ecx, ebx
                 jz      short loc_435B33
                 push    1
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z

 loc_435B33:                             ; CODE XREF: CMapViewWnd__SetCurrentZone+10Fj
                 mov     ecx, [edi+194h]
                 cmp     ecx, ebx
                 jz      short loc_435B44
                 push    1
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z

 loc_435B44:                             ; CODE XREF: CMapViewWnd__SetCurrentZone+120j
                 push    1
                 pop     eax
                 mov     [edi+210h], eax
                 mov     ecx, [edi+198h]
                 cmp     ecx, ebx
                 jz      short loc_435B5D
                 push    eax
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z

 loc_435B5D:                             ; CODE XREF: CMapViewWnd__SetCurrentZone+13Aj
                 mov     ecx, [edi+19Ch]
                 cmp     ecx, ebx
                 jz      short loc_435B6D
                 push    ebx
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z

 loc_435B6D:                             ; CODE XREF: CMapViewWnd__SetCurrentZone+14Aj
                 mov     ecx, [edi+1A0h]
                 cmp     ecx, ebx
                 jz      short loc_435B7D
                 push    ebx
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z

 loc_435B7D:                             ; CODE XREF: CMapViewWnd__SetCurrentZone+15Aj
                 mov     ebx, [ebp+arg_8]
                 fld     dword ptr [ebx]
                 call    __ftol
                 push    eax
                 mov     eax, [ebp+arg_4]
                 fld     dword ptr [eax]
                 call    __ftol
                 fld     dword ptr [ebx+4]
                 push    eax
                 call    __ftol
                 push    eax
                 mov     eax, [ebp+arg_4]
                 fld     dword ptr [eax+4]
                 call    __ftol
                 push    eax ; its 0xfffffaed
                 mov     ecx, esi
                 call    __MapViewMap__SetZoneExtents
                 mov     ecx, edi
                 call    __CMapViewWnd__Init
                 push    [ebp+var_4]
                 and     dword ptr [edi+1C8h], 0
                 and     dword ptr [edi+1CCh], 0
                 mov     ecx, esi
                 call    MapViewMap__Load
                 pop     edi
                 pop     esi
                 pop     ebx
                 leave
                 retn    0Ch
__CMapViewWnd__SetCurrentZone endp


__MapViewMap__dMapViewMap proc near       ; CODE XREF: CMapViewWnd__dCMapViewWnd+1Bp
                                         ; sub_587084+9j
                 push    ebx             ; public: __thiscall MapViewMap::~MapViewMap(void
                 push    esi
                 mov     esi, ecx
                 xor     ebx, ebx
                 push    edi
                 cmp     [esi+40h], ebx
                 jz      short loc_435FD1

 loc_435FBE:                             ; CODE XREF: MapViewMap__dMapViewMap+1Dj
                 mov     eax, [esi+40h]
                 push    eax
                 mov     edi, [eax]
                 call    operator__delete
                 cmp     edi, ebx
                 pop     ecx
                 mov     [esi+40h], edi
                 jnz     short loc_435FBE

 loc_435FD1:                             ; CODE XREF: MapViewMap__dMapViewMap+Aj
                 cmp     [esi+44h], ebx
                 jz      short loc_435FF4

 loc_435FD6:                             ; CODE XREF: MapViewMap__dMapViewMap+40j
                 mov     eax, [esi+44h]
                 push    dword ptr [eax+1Ch]
                 mov     edi, [eax]
                 call    operator__delete
                 push    dword ptr [esi+44h]
                 call    operator__delete
                 pop     ecx
                 cmp     edi, ebx
                 pop     ecx
                 mov     [esi+44h], edi
                 jnz     short loc_435FD6

 loc_435FF4:                             ; CODE XREF: MapViewMap__dMapViewMap+22j
                 mov     [esi+48h], bl
                 mov     [esi+5Ch], ebx
                 mov     [esi+64h], ebx
                 mov     [esi+68h], ebx
                 mov     [esi+6Ch], ebx
                 mov     [esi+70h], ebx
                 mov     [esi+74h], bl
                 mov     byte ptr [esi+80h], 1
                 pop     edi
                 pop     esi
                 pop     ebx
                 retn
 __MapViewMap__dMapViewMap endp

__MapViewMap__SetZoneExtents proc near    ; CODE XREF: CMapViewWnd__CMapViewWnd+400p
                                         ; CMapViewWnd__SetCurrentZone+18Fp

 var_18          = qword ptr -18h
 var_8           = dword ptr -8
 var_4           = dword ptr -4
 arg_0           = dword ptr  8
 arg_4           = dword ptr  0Ch
 arg_8           = dword ptr  10h
 arg_C           = dword ptr  14h

                 push    ebp             ; public: void __thiscall MapViewMap::SetZoneExtents(int,int,int,int
                 mov     ebp, esp
                 push    ecx
                 push    ecx
                 push    esi
                 mov     esi, ecx
                 push    edi ; 867.656250 1499.40625 779.687500
                 fld     dword ptr [esi+78h] ; 1.0
                 fcomp   ds:__real@4@00000000000000000000 ; __real@4@0000000000000000000
                 fnstsw  ax ; 0xfaed -> 0x0037
                 sahf
                 jnz     short loc_438696
                 mov     eax, [ebp+arg_4]
                 sub     eax, [ebp+arg_0]
                 push    eax             ; X
                 call    _abs
                 mov     [ebp+var_4], eax
                 pop     ecx
                 fild    [ebp+var_4]
                 mov     dword ptr [esi+7Ch], 0C8h
                 fmul    ds:__real@4@3ff7a3d70a3d70a3d800 ; __real@4@3ff7a3d70a3d70a3d80
                 fstp    dword ptr [esi+78h]
                 jmp     loc_438721
 ; ---------------------------------------------------------------------------

 loc_438696:                             ; CODE XREF: MapViewMap__SetZoneExtents+15j
                 fld     dword ptr [esi+78h]
                 fcomp   ds:__real@4@3fff8000000000000000 ; __real@4@3fff800000000000000
                 fnstsw  ax
                 sahf
                 jz      short loc_438701
                 fld     dword ptr [esi+8]
                 fsub    dword ptr [esi]
                 push    ecx
                 push    ecx
                 fstp    [esp+18h+var_18]
                 call    _fabs
                 fdiv    dword ptr [esi+78h]
                 mov     edi, [ebp+arg_4]
                 sub     edi, [ebp+arg_0]
                 push    edi             ; X
                 fstp    [ebp+var_4]
                 call    _abs
                 mov     [ebp+var_8], eax
                 add     esp, 0Ch
                 fild    [ebp+var_8]
                 fcomp   [ebp+var_4]
                 fnstsw  ax
                 sahf
                 jbe     short loc_4386F3
                 push    edi             ; X
                 call    _abs
                 mov     [ebp+var_8], eax
                 pop     ecx
                 fild    [ebp+var_8]
                 fdiv    [ebp+var_4]
                 fstp    dword ptr [esi+78h]
                 fld     [ebp+var_4]
                 call    __ftol
                 jmp     short loc_43871E
 ; ---------------------------------------------------------------------------

 loc_4386F3:                             ; CODE XREF: MapViewMap__SetZoneExtents+7Dj
                 fld1
                 push    edi             ; X
                 fstp    dword ptr [esi+78h]
                 call    _abs
                 pop     ecx
                 jmp     short loc_43871E
 ; ---------------------------------------------------------------------------

 loc_438701:                             ; CODE XREF: MapViewMap__SetZoneExtents+4Bj
                 mov     eax, [ebp+arg_4]
                 push    ecx
                 sub     eax, [ebp+arg_0]
                 push    ecx
                 mov     [ebp+var_8], eax
                 fild    [ebp+var_8]
                 fstp    [esp+18h+var_18]
                 call    _fabs
                 pop     ecx
                 pop     ecx
                 call    __ftol

 loc_43871E:                             ; CODE XREF: MapViewMap__SetZoneExtents+9Aj
                                         ; MapViewMap__SetZoneExtents+A8j
                 mov     [esi+7Ch], eax

 loc_438721:                             ; CODE XREF: MapViewMap__SetZoneExtents+3Aj
                 fild    [ebp+arg_0]
                 mov     byte ptr [esi+81h], 1
                 pop     edi
                 fstp    dword ptr [esi]
                 fild    [ebp+arg_4]
                 fstp    dword ptr [esi+8]
                 fild    [ebp+arg_8]
                 fstp    dword ptr [esi+4]
                 fild    [ebp+arg_C]
                 fstp    dword ptr [esi+0Ch]
                 pop     esi
                 leave
                 retn    10h
__MapViewMap__SetZoneExtents endp

__MapViewMap__SetZoom proc near           ; CODE XREF: CMapViewWnd__HandleWheelMove+5Fp
                                        ; CMapViewWnd__HandleWheelMove+7Bp ...

var_C           = qword ptr -0Ch
arg_0           = dword ptr  4

                fld     ds:__real@4@3fff8000000000000000
                mov     eax, [esp+arg_0]
                fld     [esp+arg_0]
                push    esi
                fucompp
                mov     esi, ecx
                mov     [esi+78h], eax
                fnstsw  ax
                test    ah, 44h
                jnp     short loc_531E1D
                fld     ds:__real@4@00000000000000000000
                fld     [esp+4+arg_0]
                fucompp
                fnstsw  ax
                test    ah, 44h
                jnp     short loc_531E1D
                fld     dword ptr [esi+8]
                push    ecx
                fsub    dword ptr [esi]
                push    ecx             ; double
                fstp    [esp+0Ch+var_C]
                call    _fabs
                fdiv    dword ptr [esi+78h]
                pop     ecx
                pop     ecx
                call    __ftol2
                cmp     eax, 5
                mov     [esi+7Ch], eax
                jge     short loc_531E36
                fld     dword ptr [esi+8]
                push    ecx
                fsub    dword ptr [esi]
                push    ecx             ; double
                fstp    [esp+0Ch+var_C]
                call    _fabs
                fmul    ds:dword_640FEC
                pop     ecx
                pop     ecx
                fstp    dword ptr [esi+78h]
                mov     dword ptr [esi+7Ch], 5
                jmp     short loc_531E36
; ---------------------------------------------------------------------------

loc_531E1D:                             ; CODE XREF: MapViewMap__SetZoom+1Bj
                                        ; MapViewMap__SetZoom+2Ej
                fld     dword ptr [esi+8]
                push    ecx
                fsub    dword ptr [esi]
                push    ecx             ; double
                fstp    [esp+0Ch+var_C]
                call    _fabs
                pop     ecx
                pop     ecx
                call    __ftol2
                mov     [esi+7Ch], eax

loc_531E36:                             ; CODE XREF: MapViewMap__SetZoom+4Fj
                                        ; MapViewMap__SetZoom+72j
                mov     byte ptr [esi+81h], 1
                pop     esi
                retn    4
__MapViewMap__SetZoom endp


__MapViewMap__SetZoomOld proc near           ; CODE XREF: CMapViewWnd__CMapViewWnd+40Dp
                                         ; CMapViewWnd__WndNotification+124p ...

 var_C           = qword ptr -0Ch
 arg_0           = dword ptr  4

                 fld     [esp+arg_0]     ; public: void __thiscall MapViewMap::SetZoom(float
                 fcom    ds:__real@4@3fff8000000000000000 ; __real@4@3fff800000000000000
                 push    esi
                 mov     esi, ecx
                 fst     dword ptr [esi+78h]
                 fnstsw  ax
                 sahf
                 jz      short loc_4387A9
                 fcomp   ds:__real@4@00000000000000000000 ; __real@4@0000000000000000000
                 fnstsw  ax
                 sahf
                 jz      short loc_4387AB
                 fld     dword ptr [esi+8]
                 fsub    dword ptr [esi]
                 push    ecx
                 push    ecx
                 fstp    [esp+0Ch+var_C]
                 call    _fabs
                 fdiv    dword ptr [esi+78h]
                 pop     ecx
                 pop     ecx
                 call    __ftol
                 cmp     eax, 5
                 mov     [esi+7Ch], eax
                 jge     short loc_4387C4
                 fld     dword ptr [esi+8]
                 fsub    dword ptr [esi]
                 push    ecx
                 push    ecx
                 fstp    [esp+0Ch+var_C]
                 call    _fabs
                 fmul    ds:__real@8@3ffcccccccccccccd000 ; __real@8@3ffcccccccccccccd00
                 pop     ecx
                 mov     dword ptr [esi+7Ch], 5
                 pop     ecx
                 fstp    dword ptr [esi+78h]
                 jmp     short loc_4387C4
 ; ---------------------------------------------------------------------------

 loc_4387A9:                             ; CODE XREF: MapViewMap__SetZoom+13j
                 fstp    st

 loc_4387AB:                             ; CODE XREF: MapViewMap__SetZoom+1Ej
                 fld     dword ptr [esi+8]
                 fsub    dword ptr [esi]
                 push    ecx
                 push    ecx
                 fstp    [esp+0Ch+var_C]
                 call    _fabs
                 pop     ecx
                 pop     ecx
                 call    __ftol
                 mov     [esi+7Ch], eax

 loc_4387C4:                             ; CODE XREF: MapViewMap__SetZoom+3Fj
                                         ; MapViewMap__SetZoom+62j
                 mov     byte ptr [esi+81h], 1
                 pop     esi
                 retn    4
 __MapViewMap__SetZoomOld endp


 ; =============== S U B R O U T I N E =======================================


__MapViewMap__GetMinZ proc near           ; CODE XREF: CMapViewWnd__CMapViewWnd+498p
                                         ; CMapViewWnd__LoadIniInfo+211p
                 mov     eax, [ecx+6Ch]  ; public: int __thiscall MapViewMap::GetMinZ(void
                 retn
__MapViewMap__GetMinZ endp


 ; =============== S U B R O U T I N E =======================================


__MapViewMap__GetMaxZ proc near           ; CODE XREF: CMapViewWnd__CMapViewWnd+4CEp
                                         ; CMapViewWnd__LoadIniInfo+24Bp
                 mov     eax, [ecx+70h]  ; public: int __thiscall MapViewMap::GetMaxZ(void
                 retn
__MapViewMap__GetMaxZ endp

MapViewMap__PointInMapViewArea proc near
                                         ; CODE XREF: CMapViewWnd__HandleLButtonDown+32p
                                         ; CMapViewWnd__HandleWheelMove+32p

 var_10          = dword ptr -10h
 var_C           = dword ptr -0Ch
 arg_0           = dword ptr  8
 arg_4           = dword ptr  0Ch
 arg_8           = dword ptr  10h
 arg_C           = dword ptr  14h

                 push    ebp             ; public: bool __thiscall MapViewMap::PointInMapViewArea(class CXPoint,class CXRect
                 mov     ebp, esp
                 sub     esp, 10h
                 fild    [ebp+arg_C]
                 push    ebx
                 push    esi
                 mov     esi, ecx
                 push    edi
                 fadd    dword ptr [esi+18h]
                 call    __ftol
                 fild    [ebp+arg_8]
                 mov     ebx, eax
                 mov     [ebp+var_C], ebx
                 fadd    dword ptr [esi+1Ch]
                 call    __ftol
                 fild    [ebp+var_C]
                 mov     [ebp+var_10], eax
                 fadd    dword ptr [esi+14h]
                 call    __ftol
                 fild    [ebp+var_10]
                 mov     edi, eax
                 fadd    dword ptr [esi+10h]
                 call    __ftol
                 mov     ecx, [ebp+arg_0]
                 cmp     ecx, [ebp+var_10]
                 jl      short loc_436CDE
                 cmp     ecx, eax
                 jge     short loc_436CDE
                 cmp     [ebp+arg_4], ebx
                 jl      short loc_436CDE
                 cmp     [ebp+arg_4], edi
                 jge     short loc_436CDE
                 mov     al, 1
                 jmp     short loc_436CE0
 ; ---------------------------------------------------------------------------

 loc_436CDE:                             ; CODE XREF: MapViewMap__PointInMapViewArea+47j
                                         ; MapViewMap__PointInMapViewArea+4Bj ...
                 xor     al, al

 loc_436CE0:                             ; CODE XREF: MapViewMap__PointInMapViewArea+59j
                 pop     edi
                 pop     esi
                 pop     ebx
                 leave
                 retn    18h
 MapViewMap__PointInMapViewArea endp

_CMapViewWnd_IsMappingEnabled proc near ; CODE XREF: CMapToolbarWnd__OnProcessFrame+Dp
                                         ; CMapViewWnd__WndNotification+1Cp ...
                 mov     al, _bMappingEnabled ; public: bool __thiscall CMapViewWnd::IsMappingEnabled(void
                 retn
_CMapViewWnd_IsMappingEnabled endp


_CMapViewWnd_HandleLButtonDown proc near ; DATA XREF: .rdata:00593D44o

 var_10          = byte ptr -10h
 arg_0           = dword ptr  8
 arg_4           = dword ptr  0Ch
 arg_8           = dword ptr  10h

                 push    ebp             ; public: virtual int __thiscall CMapViewWnd::HandleLButtonDown(class CXPoint,unsigned __int32
                 mov     ebp, esp
                 sub     esp, 10h
                 push    ebx
                 mov     ebx, ecx
                 push    esi
                 lea     ecx, [ebp+var_10]
                 mov     eax, [ebx]
                 push    edi
                 push    ecx
                 mov     ecx, ebx
                 call    dword ptr [eax+0D8h] ; CXWnd__GetClientRect (changed)
                 sub     esp, 10h
                 mov     esi, eax
                 mov     edi, esp
                 movsd
                 movsd
                 push    [ebp+arg_4]
                 movsd
                 push    [ebp+arg_0]
                 movsd
                 lea     esi, [ebx+1A8h]
                 mov     ecx, esi
                 call    MapViewMap__PointInMapViewArea
                 test    al, al
                 jz      loc_4357BE
                 mov     ecx, ebx
                 call    _CMapViewWnd_IsMappingEnabled
                 cmp     al, 1
                 jnz     loc_4357BE
                 mov     ecx, pinstCXWndManager ; class CXWndManager * g_pwndmg
                 mov     ecx, [ecx] ; added
                 call    ?GetKeyboardFlags@CXWndManager@EQClasses@@QBEIXZ
                 test    al, 2
                 jnz     short loc_43575E ; changed from jnz     short loc_43575E
                 mov     eax, _g_pMapToolbarWnd ; class CMapToolbarWnd * g_pMapToolbarWn
                 test    eax,eax ; added
				 jz      short loc_43575E ; added
				 xor     ecx, ecx
                 cmp     [eax+170h], cl
                 jz      short loc_43572E
                 mov     eax, _CurrentMapLabel
                 cmp     eax, ecx
                 jz      short loc_43570D
                 mov     [ebx+208h], eax

 loc_435704:                             ; CODE XREF: CMapViewWnd__HandleLButtonDown+9Bj
                                         ; CMapViewWnd__HandleLButtonDown+114j ...
                 xor     eax, eax

 loc_435706:                             ; CODE XREF: CMapViewWnd__HandleLButtonDown+14Ej
                 pop     edi
                 pop     esi
                 pop     ebx
                 leave
                 retn    0Ch
 ; ---------------------------------------------------------------------------

 loc_43570D:                             ; CODE XREF: CMapViewWnd__HandleLButtonDown+73j
                 mov     [ebx+208h], ecx
                 mov     eax, dword_5DF7D0
                 cmp     eax, ecx
                 jz      short loc_435726
                 push    eax
                 mov     ecx, esi
                 call    _MapViewMap_SetMarkedLine
                 jmp     short loc_435704
 ; ---------------------------------------------------------------------------

 loc_435726:                             ; CODE XREF: CMapViewWnd__HandleLButtonDown+91j
                 push    ecx
                 mov     ecx, esi
                 call    _MapViewMap_SetMarkedLine

 loc_43572E:                             ; CODE XREF: CMapViewWnd__HandleLButtonDown+6Aj
                 mov     eax, pinstCXWndManager ; class CXWndManager * g_pwndmg
                 mov     eax, [eax]
                 mov     byte_5DF7DA, 1
                 mov     esi, [ebx+1C8h]
                 mov     ecx, [eax+4Ch]
                 mov     edx, [eax+50h]
                 sub     esi, ecx
                 mov     dword_5DF7DC, esi
                 mov     ecx, [ebx+1CCh]
                 sub     ecx, edx
                 mov     dword_5DF7E0, ecx
                 jmp     short loc_43579A
 ; ---------------------------------------------------------------------------

 loc_43575E:                             ; CODE XREF: CMapViewWnd__HandleLButtonDown+5Bj
                 xor     ecx, ecx
                 cmp     byte_5DF7D8, cl
                 jnz     short loc_435795
                 mov     eax, _g_pMapToolbarWnd ; class CMapToolbarWnd * g_pMapToolbarWn
                 test eax,eax ;  added
				 jz short loc_435795 ; added
				 cmp     [eax+170h], cl
                 jz      short loc_435795
                 mov     eax, pinstCXWndManager ; class CXWndManager * g_pwndmg
                 mov	 eax, [eax] ; added
				 mov     ecx, [eax+4Ch]
                 mov     edx, [eax+50h]
                 mov     dword_5DF7A8, ecx
                 mov     dword_5DF7AC, edx
                 mov     byte_5DF7D8, 1
                 jmp     short loc_43579A
 ; ---------------------------------------------------------------------------

 loc_435795:                             ; CODE XREF: CMapViewWnd__HandleLButtonDown+DDj
                                         ; CMapViewWnd__HandleLButtonDown+EAj
                 mov     eax, pinstCXWndManager ; class CXWndManager * g_pwndmg
                 mov     eax, [eax]

 loc_43579A:                             ; CODE XREF: CMapViewWnd__HandleLButtonDown+D3j
                                         ; CMapViewWnd__HandleLButtonDown+10Aj
                 cmp     [eax+34h], ebx
                 jz      loc_435704
                 cmp     [eax+34h], ebx
                 lea     ecx, [eax+34h]
                 jz      short loc_4357B4
                 mov     dword ptr [eax+44h], 1
                 jmp     short loc_4357B7
 ; ---------------------------------------------------------------------------

 loc_4357B4:                             ; CODE XREF: CMapViewWnd__HandleLButtonDown+120j
                 inc     dword ptr [eax+44h]

 loc_4357B7:                             ; CODE XREF: CMapViewWnd__HandleLButtonDown+129j
                 mov     [ecx], ebx
                 jmp     loc_435704
 ; ---------------------------------------------------------------------------

 loc_4357BE:                             ; CODE XREF: CMapViewWnd__HandleLButtonDown+39j
                                         ; CMapViewWnd__HandleLButtonDown+48j
                 mov     ecx, [ebx+1Ch]
                 test    ecx, ecx
                 jz      loc_435704
                 push    [ebp+arg_8]
                 mov     eax, [ecx]
                 push    [ebp+arg_4]
                 push    [ebp+arg_0]
                 call    dword ptr [eax+34h] ; CXWnd__HandleLButtonDown?
                 jmp     loc_435706
_CMapViewWnd_HandleLButtonDown endp


 ; =============== S U B R O U T I N E =======================================


_CMapViewWnd_HandleLButtonUp proc near  ; CODE XREF: CMapViewWnd__HandleLButtonUp+11j
                                         ; CMapViewWnd__HandleLButtonUp+17j
                                         ; DATA XREF: ...

 arg_0           = dword ptr  4
 arg_4           = dword ptr  8
 arg_8           = dword ptr  0Ch

                 mov     eax, pinstCXWndManager ; public: virtual int __thiscall CMapViewWnd::HandleLButtonUp(class CXPoint,unsigned __int32
                 mov	 eax, [eax] ; added
				 cmp     [eax+34h], ecx
                 jnz     short loc_4357F5
                 dec     dword ptr [eax+44h]
                 cmp     dword ptr [eax+44h], 0
                 jg      short _CMapViewWnd_HandleLButtonUp
                 and     dword ptr [eax+34h], 0
                 jmp     short _CMapViewWnd_HandleLButtonUp
 ; ---------------------------------------------------------------------------

 loc_4357F5:                             ; CODE XREF: CMapViewWnd__HandleLButtonUp+8j
                 cmp     byte_5DF7DA, 1
                 jnz     short loc_43580A
                 and     byte_5DF7DA, 0

 loc_435805:                             ; CODE XREF: CMapViewWnd__HandleLButtonUp+3Ej
                                         ; CMapViewWnd__HandleLButtonUp+45j
                 xor     eax, eax

 locret_435807:                          ; CODE XREF: CMapViewWnd__HandleLButtonUp+58j
                 retn    0Ch
 ; ---------------------------------------------------------------------------

 loc_43580A:                             ; CODE XREF: CMapViewWnd__HandleLButtonUp+20j
                 cmp     byte_5DF7D8, 1
                 jnz     short loc_43581C
                 mov     byte_5DF7D9, 1
                 jmp     short loc_435805
 ; ---------------------------------------------------------------------------

 loc_43581C:                             ; CODE XREF: CMapViewWnd__HandleLButtonUp+35j
                 mov     ecx, [ecx+1Ch]
                 test    ecx, ecx
                 jz      short loc_435805
                 push    [esp+arg_8]
                 mov     eax, [ecx]
                 push    [esp+4+arg_4]
                 push    [esp+8+arg_0]
                 call    dword ptr [eax+38h] ; CXWnd__HandleLButtonUp?
                 jmp     short locret_435807
_CMapViewWnd_HandleLButtonUp endp


 ; =============== S U B R O U T I N E =======================================


_CMapViewWnd_HandleLButtonHeld proc near ; DATA XREF: .rdata:00593D4Co

 arg_0           = dword ptr  4
 arg_4           = dword ptr  8
 arg_8           = dword ptr  0Ch

                 mov     ecx, [ecx+1Ch]  ; public: virtual int __thiscall CMapViewWnd::HandleLButtonHeld(class CXPoint,unsigned __int32
                 test    ecx, ecx
                 jz      short loc_435850
                 push    [esp+arg_8]
                 mov     eax, [ecx]
                 push    [esp+4+arg_4]
                 push    [esp+8+arg_0]
                 call    dword ptr [eax+3Ch] ; CXWnd__HandleLButtonHeld?
                 jmp     short locret_435852
 ; ---------------------------------------------------------------------------

 loc_435850:                             ; CODE XREF: CMapViewWnd__HandleLButtonHeld+5j
                 xor     eax, eax

 locret_435852:                          ; CODE XREF: CMapViewWnd__HandleLButtonHeld+18j
                 retn    0Ch
_CMapViewWnd_HandleLButtonHeld endp


 ; =============== S U B R O U T I N E =======================================


_CMapViewWnd_HandleLButtonUpAfterHeld proc near
                                         ; CODE XREF: CMapViewWnd__HandleLButtonUpAfterHeld+11j
                                         ; CMapViewWnd__HandleLButtonUpAfterHeld+17j
                                         ; DATA XREF: ...

 arg_0           = dword ptr  4
 arg_4           = dword ptr  8
 arg_8           = dword ptr  0Ch

                 mov     eax, pinstCXWndManager ; public: virtual int __thiscall CMapViewWnd::HandleLButtonUpAfterHeld(class CXPoint,unsigned __int32
                 mov	 eax, [eax] ; added
				 cmp     [eax+34h], ecx
                 jnz     short loc_43586E
                 dec     dword ptr [eax+44h]
                 cmp     dword ptr [eax+44h], 0
                 jg      short _CMapViewWnd_HandleLButtonUpAfterHeld
                 and     dword ptr [eax+34h], 0
                 jmp     short _CMapViewWnd_HandleLButtonUpAfterHeld
 ; ---------------------------------------------------------------------------

 loc_43586E:                             ; CODE XREF: CMapViewWnd__HandleLButtonUpAfterHeld+8j
                 cmp     byte_5DF7DA, 1
                 jnz     short loc_435883
                 and     byte_5DF7DA, 0

 loc_43587E:                             ; CODE XREF: CMapViewWnd__HandleLButtonUpAfterHeld+3Ej
                                         ; CMapViewWnd__HandleLButtonUpAfterHeld+45j
                 xor     eax, eax

 locret_435880:                          ; CODE XREF: CMapViewWnd__HandleLButtonUpAfterHeld+58j
                 retn    0Ch
 ; ---------------------------------------------------------------------------

 loc_435883:                             ; CODE XREF: CMapViewWnd__HandleLButtonUpAfterHeld+20j
                 cmp     byte_5DF7D8, 1
                 jnz     short loc_435895
                 mov     byte_5DF7D9, 1
                 jmp     short loc_43587E
 ; ---------------------------------------------------------------------------

 loc_435895:                             ; CODE XREF: CMapViewWnd__HandleLButtonUpAfterHeld+35j
                 mov     ecx, [ecx+1Ch]
                 test    ecx, ecx
                 jz      short loc_43587E
                 push    [esp+arg_8]
                 mov     eax, [ecx]
                 push    [esp+4+arg_4]
                 push    [esp+8+arg_0]
                 call    dword ptr [eax+40h] ; CXWnd__HandleLButtonUpAfterHeld?
                 jmp     short locret_435880
_CMapViewWnd_HandleLButtonUpAfterHeld endp


 ; =============== S U B R O U T I N E =======================================

 ; Attributes: bp-based frame

_CMapViewWnd_HandleWheelMove proc near  ; DATA XREF: .rdata:00593D70o

 var_20          = dword ptr -20h
 var_10          = byte ptr -10h
 arg_0           = dword ptr  8
 arg_4           = dword ptr  0Ch
 arg_8           = dword ptr  10h

                 push    ebp             ; public: virtual int __thiscall CMapViewWnd::HandleWheelMove(class CXPoint,int,unsigned __int32
                 mov     ebp, esp
                 sub     esp, 10h
                 push    ebx
                 mov     ebx, ecx
                 push    esi
                 lea     ecx, [ebp+var_10]
                 mov     eax, [ebx]
                 push    edi
                 push    ecx
                 mov     ecx, ebx
                 call    dword ptr [eax+0D8h] ; ; CXWnd__GetClientRect (changed)
                 sub     esp, 10h
                 mov     esi, eax
                 mov     edi, esp
                 movsd
                 movsd
                 push    [ebp+arg_4]
                 movsd
                 push    [ebp+arg_0]
                 movsd
                 lea     esi, [ebx+1A8h]
                 mov     ecx, esi
                 call    MapViewMap__PointInMapViewArea
                 test    al, al
                 jz      short loc_435939
                 cmp     [ebp+arg_8], 0
                 jle     short loc_4358FE
                 fld     dword ptr [ebx+220h]
                 fmul    ds:__real@4@3fffc000000000000000 ; __real@4@3fffc00000000000000
                 jmp     short loc_43592A
 ; ---------------------------------------------------------------------------

 loc_4358FE:                             ; CODE XREF: CMapViewWnd__HandleWheelMove+3Fj
                 fld     dword ptr [ebx+220h]
                 add     ebx, 220h
                 push    ecx             ; float
                 fmul    ds:__real@4@3ffeaaaaaaaaaaaaa800 ; __real@4@3ffeaaaaaaaaaaaaa80
                 mov     ecx, esi
                 fstp    [esp+20h+var_20]
                 call    __MapViewMap__SetZoom
                 fld     dword ptr [ebx]
                 fcomp   ds:__real@4@3fff8000000000000000 ; __real@4@3fff800000000000000
                 fnstsw  ax
                 sahf
                 jnb     short loc_435935
                 fld1

 loc_43592A:                             ; CODE XREF: CMapViewWnd__HandleWheelMove+4Dj
                 push    ecx             ; float
                 mov     ecx, esi
                 fstp    [esp+20h+var_20]
                 call    __MapViewMap__SetZoom

 loc_435935:                             ; CODE XREF: CMapViewWnd__HandleWheelMove+77j
                 xor     eax, eax
                 jmp     short loc_43593C
 ; ---------------------------------------------------------------------------

 loc_435939:                             ; CODE XREF: CMapViewWnd__HandleWheelMove+39j
                 push    1
                 pop     eax

 loc_43593C:                             ; CODE XREF: CMapViewWnd__HandleWheelMove+88j
                 pop     edi
                 pop     esi
                 pop     ebx
                 leave
                 retn    10h
_CMapViewWnd_HandleWheelMove endp

_CheckRects     proc near               ; CODE XREF: MapViewMap__CalcLabelRenderOffsets:loc_436B7Bp
                                         ; MapViewMap__CalcLabelRenderOffsets+237p ...

 var_18          = byte ptr -18h
 var_8           = dword ptr -8
 var_4           = dword ptr -4

                 push    ebp             ; void __cdecl _CheckRects(void
                 mov     ebp, esp
                 sub     esp, 18h
                 push    ebx
                 mov     ebx, dword_5DF7E8
                 push    esi
                 push    edi

 loc_436BC7:                             ; CODE XREF: _CheckRects+A4j
                 test    ebx, ebx
                 jz      loc_436C61
                 cmp     byte ptr [ebx+18h], 0
                 jz      loc_436C5A
                 push    ebx
                 lea     esi, [ebx+4]
                 sub     esp, 10h
                 mov     edi, esp
                 movsd
                 movsd
                 movsd
                 movsd
                 call    _CountRectIntersectIgnoreSelf
                 mov     ecx, [ebx+14h]
                 mov     esi, [ebx+4]
                 mov     edi, [ebx+8]
                 push    eax
                 sub     esi, [ecx+2Ch]
                 sub     edi, [ecx+30h]
                 mov     edx, [ecx+24h]
                 mov     ecx, [ecx+28h]
                 push    ebx
                 push    ecx
                 push    edx
                 push    edi
                 push    esi
                 mov     [ebp+var_8], edx
                 mov     [ebp+var_4], ecx
                 call    _GetRectWithLeastIntersects
                 add     esp, 2Ch
                 test    eax, eax
                 jl      short loc_436C5A
                 push    [ebp+var_4]
                 push    [ebp+var_8]
                 push    edi
                 push    esi
                 push    eax
                 lea     eax, [ebp+var_18]
                 push    eax
                 call    _GetRect
                 mov     ecx, [eax]
                 add     esp, 18h
                 mov     [ebx+4], ecx
                 mov     ecx, [eax+4]
                 mov     [ebx+8], ecx
                 mov     ecx, [eax+8]
                 mov     [ebx+0Ch], ecx
                 mov     eax, [eax+0Ch]
                 mov     [ebx+10h], eax
                 mov     eax, [ebx+4]
                 mov     ecx, [ebx+14h]
                 sub     eax, esi
                 mov     [ecx+2Ch], eax
                 mov     eax, [ebx+8]
                 mov     ecx, [ebx+14h]
                 sub     eax, edi
                 mov     [ecx+30h], eax

 loc_436C5A:                             ; CODE XREF: _CheckRects+1Bj
                                         ; _CheckRects+5Ej
                 mov     ebx, [ebx]
                 jmp     loc_436BC7
 ; ---------------------------------------------------------------------------

 loc_436C61:                             ; CODE XREF: _CheckRects+11j
                 pop     edi
                 pop     esi
                 pop     ebx
                 leave
                 retn
 _CheckRects     endp


_CountRectIntersects proc near          ; CODE XREF: _TryRect+80p
                                         ; _TryRect+134p

 var_14          = dword ptr -14h
 var_10          = dword ptr -10h
 var_C           = dword ptr -0Ch
 var_8           = dword ptr -8
 var_4           = dword ptr -4
 arg_0           = dword ptr  8
 arg_4           = dword ptr  0Ch
 arg_8           = dword ptr  10h
 arg_C           = dword ptr  14h

                 push    ebp             ; int __cdecl _CountRectIntersects(class CXRect
                 mov     ebp, esp
                 sub     esp, 14h
                 mov     eax, dword_5DF7E8
                 and     [ebp+var_4], 0
                 push    ebx
                 push    esi
                 test    eax, eax
                 push    edi
                 mov     ebx, eax
                 jz      short loc_43684A

 loc_4367F2:                             ; CODE XREF: _CountRectIntersects+6Ej
                 sub     esp, 10h
                 lea     esi, [ebx+4]
                 mov     edi, esp
                 lea     eax, [ebp+var_14]
                 movsd
                 movsd
                 movsd
                 push    eax
                 lea     ecx, [ebp+arg_0]
                 movsd
                 call    ??ICXRect@EQClasses@@QBE?AV01@V01@@Z
                 or      eax, 0FFFFFFFFh
                 cmp     [ebp+var_14], eax
                 jnz     short loc_436821
                 cmp     [ebp+var_10], eax
                 jnz     short loc_436821
                 cmp     [ebp+var_C], eax
                 jnz     short loc_436821
                 cmp     [ebp+var_8], eax
                 jz      short loc_436844

 loc_436821:                             ; CODE XREF: _CountRectIntersects+36j
                                         ; _CountRectIntersects+3Bj ...
                 mov     eax, [ebp+arg_4]
                 cmp     eax, [ebx+10h]
                 jz      short loc_436844
                 mov     eax, [ebp+arg_C]
                 cmp     eax, [ebx+8]
                 jz      short loc_436844
                 mov     eax, [ebp+arg_0]
                 cmp     eax, [ebx+0Ch]
                 jz      short loc_436844
                 mov     eax, [ebp+arg_8]
                 cmp     eax, [ebx+4]
                 jz      short loc_436844
                 inc     [ebp+var_4]

 loc_436844:                             ; CODE XREF: _CountRectIntersects+45j
                                         ; _CountRectIntersects+4Dj ...
                 mov     ebx, [ebx]
                 test    ebx, ebx
                 jnz     short loc_4367F2

 loc_43684A:                             ; CODE XREF: _CountRectIntersects+16j
                 mov     eax, [ebp+var_4]
                 pop     edi
                 pop     esi
                 pop     ebx
                 leave
                 retn
 _CountRectIntersects endp


 ; =============== S U B R O U T I N E =======================================

 ; Attributes: bp-based frame

 _GetRectWithLeastIntersects proc near   ; CODE XREF: _CheckRects+54p

 var_28          = byte ptr -28h
 var_18          = dword ptr -18h
 var_14          = dword ptr -14h
 var_10          = dword ptr -10h
 var_C           = dword ptr -0Ch
 var_8           = dword ptr -8
 var_4           = dword ptr -4
 arg_0           = dword ptr  8
 arg_4           = dword ptr  0Ch
 arg_8           = dword ptr  10h
 arg_C           = dword ptr  14h
 arg_10          = dword ptr  18h

                 push    ebp             ; int __cdecl _GetRectWithLeastIntersects(int,int,int,int,struct _rectlist *,int
                 mov     ebp, esp
                 sub     esp, 28h
                 or      [ebp+var_8], 0FFFFFFFFh
                 push    ebx
                 push    esi
                 push    edi
                 mov     [ebp+var_4], 32h
                 xor     ebx, ebx

 loc_436868:                             ; CODE XREF: _GetRectWithLeastIntersects+70j
                 push    [ebp+arg_C]
                 lea     eax, [ebp+var_28]
                 push    [ebp+arg_8]
                 push    [ebp+arg_4]
                 push    [ebp+arg_0]
                 push    ebx
                 push    eax
                 call    _GetRect
                 mov     ecx, [eax]
                 add     esp, 18h
                 mov     [ebp+var_18], ecx
                 mov     ecx, [eax+4]
                 push    [ebp+arg_10]
                 mov     [ebp+var_14], ecx
                 mov     ecx, [eax+8]
                 mov     eax, [eax+0Ch]
                 sub     esp, 10h
                 lea     esi, [ebp+var_18]
                 mov     edi, esp
                 mov     [ebp+var_10], ecx
                 mov     [ebp+var_C], eax
                 movsd
                 movsd
                 movsd
                 movsd
                 call    _CountRectIntersectIgnoreSelf
                 add     esp, 14h
                 cmp     eax, [ebp+var_4]
                 jge     short loc_4368BE
                 test    eax, eax
                 mov     [ebp+var_4], eax
                 mov     [ebp+var_8], ebx
                 jz      short loc_4368C4

 loc_4368BE:                             ; CODE XREF: _GetRectWithLeastIntersects+60j
                 inc     ebx
                 cmp     ebx, 18h
                 jl      short loc_436868

 loc_4368C4:                             ; CODE XREF: _GetRectWithLeastIntersects+6Aj
                 mov     eax, [ebp+var_8]
                 pop     edi
                 pop     esi
                 pop     ebx
                 leave
                 retn
 _GetRectWithLeastIntersects endp


 ; =============== S U B R O U T I N E =======================================

 ; Attributes: bp-based frame

 _CountRectIntersectIgnoreSelf proc near ; CODE XREF: _GetRectWithLeastIntersects+55p
                                         ; _CheckRects+2Ep

 var_14          = dword ptr -14h
 var_10          = dword ptr -10h
 var_C           = dword ptr -0Ch
 var_8           = dword ptr -8
 var_4           = dword ptr -4
 arg_0           = dword ptr  8
 arg_4           = dword ptr  0Ch
 arg_8           = dword ptr  10h
 arg_C           = dword ptr  14h
 arg_10          = dword ptr  18h

                 push    ebp             ; int __cdecl _CountRectIntersectIgnoreSelf(class CXRect,struct _rectlist *
                 mov     ebp, esp
                 sub     esp, 14h
                 mov     eax, dword_5DF7E8
                 and     [ebp+var_4], 0
                 push    ebx
                 push    esi
                 test    eax, eax
                 push    edi
                 mov     ebx, eax
                 jz      short loc_436941

 loc_4368E4:                             ; CODE XREF: _CountRectIntersectIgnoreSelf+73j
                 cmp     ebx, [ebp+arg_10]
                 jz      short loc_43693B
                 sub     esp, 10h
                 lea     esi, [ebx+4]
                 mov     edi, esp
                 lea     eax, [ebp+var_14]
                 movsd
                 movsd
                 movsd
                 push    eax
                 lea     ecx, [ebp+arg_0]
                 movsd
                 call    ??ICXRect@EQClasses@@QBE?AV01@V01@@Z
                 or      eax, 0FFFFFFFFh
                 cmp     [ebp+var_14], eax
                 jnz     short loc_436918
                 cmp     [ebp+var_10], eax
                 jnz     short loc_436918
                 cmp     [ebp+var_C], eax
                 jnz     short loc_436918
                 cmp     [ebp+var_8], eax
                 jz      short loc_43693B

 loc_436918:                             ; CODE XREF: _CountRectIntersectIgnoreSelf+3Bj
                                         ; _CountRectIntersectIgnoreSelf+40j ...
                 mov     eax, [ebp+arg_4]
                 cmp     eax, [ebx+10h]
                 jz      short loc_43693B
                 mov     eax, [ebp+arg_C]
                 cmp     eax, [ebx+8]
                 jz      short loc_43693B
                 mov     eax, [ebp+arg_0]
                 cmp     eax, [ebx+0Ch]
                 jz      short loc_43693B
                 mov     eax, [ebp+arg_8]
                 cmp     eax, [ebx+4]
                 jz      short loc_43693B
                 inc     [ebp+var_4]

 loc_43693B:                             ; CODE XREF: _CountRectIntersectIgnoreSelf+1Bj
                                         ; _CountRectIntersectIgnoreSelf+4Aj ...
                 mov     ebx, [ebx]
                 test    ebx, ebx
                 jnz     short loc_4368E4

 loc_436941:                             ; CODE XREF: _CountRectIntersectIgnoreSelf+16j
                 mov     eax, [ebp+var_4]
                 pop     edi
                 pop     esi
                 pop     ebx
                 leave
                 retn
 _CountRectIntersectIgnoreSelf endp



_GetRect        proc near               ; CODE XREF: _TryRect+1Dp
                                         ; _TryRect+10Cp ...

 var_10          = dword ptr -10h
 var_C           = dword ptr -0Ch
 var_8           = dword ptr -8
 var_4           = dword ptr -4
 arg_0           = dword ptr  8
 arg_4           = dword ptr  0Ch
 arg_8           = dword ptr  10h
 arg_C           = dword ptr  14h
 arg_10          = dword ptr  18h
 arg_14          = dword ptr  1Ch

                 push    ebp             ; class CXRect __cdecl _GetRect(int,int,int,int,int
                 mov     ebp, esp
                 sub     esp, 10h
                 mov     eax, [ebp+arg_8]
                 mov     edx, [ebp+arg_C]
                 push    ebx
                 push    esi
                 mov     esi, [ebp+arg_14]
                 push    edi
                 mov     edi, [ebp+arg_10]
                 mov     [ebp+var_10], eax
                 lea     ebx, [edx+esi]
                 mov     [ebp+var_C], edx
                 lea     ecx, [eax+edi]
                 mov     [ebp+var_4], ebx
                 mov     [ebp+var_8], ecx
                 lea     ecx, [ebp+var_10]
                 call    CXRect__Normalize
                 mov     eax, [ebp+arg_4]
                 cmp     eax, 17h        ; switch 24 cases
                 ja      loc_436554      ; default
                 jmp     off_436565[eax*4] ; switch jump

 loc_4363C6:                             ; DATA XREF: 65o
                 mov     eax, edi        ; jumptable 004363BF case 0
                 push    0FFFFFFFEh
                 cdq
                 pop     ecx
                 idiv    ecx
                 push    ecx
                 add     [ebp+var_10], eax
                 add     [ebp+var_8], eax
                 pop     eax
                 sub     eax, esi
                 jmp     loc_43654E
 ; ---------------------------------------------------------------------------

 loc_4363DD:                             ; CODE XREF: _GetRect+3Bj
                                         ; DATA XREF: 65o
                 mov     eax, edi        ; jumptable 004363BF case 1
                 push    0FFFFFFFEh
                 cdq
                 pop     ecx
                 add     [ebp+var_C], 2
                 idiv    ecx
                 add     [ebp+var_10], eax
                 add     [ebp+var_8], eax
                 add     [ebp+var_4], 2
                 jmp     loc_436554      ; default
 ; ---------------------------------------------------------------------------

 loc_4363F8:                             ; CODE XREF: _GetRect+3Bj
                                         ; DATA XREF: 65o
                 add     [ebp+var_10], 4 ; jumptable 004363BF case 2
                 add     [ebp+var_8], 4
                 jmp     short loc_436429
 ; ---------------------------------------------------------------------------

 loc_436402:                             ; CODE XREF: _GetRect+3Bj
                                         ; DATA XREF: 65o
                 add     [ebp+var_10], 4 ; jumptable 004363BF case 3
                 add     [ebp+var_8], 4

 loc_43640A:                             ; CODE XREF: _GetRect+BDj
                 neg     esi
                 jmp     loc_436538
 ; ---------------------------------------------------------------------------

 loc_436411:                             ; CODE XREF: _GetRect+3Bj
                                         ; DATA XREF: 65o
                 add     [ebp+var_10], 4 ; jumptable 004363BF case 4
                 add     [ebp+var_8], 4
                 jmp     loc_436554      ; default
 ; ---------------------------------------------------------------------------

 loc_43641E:                             ; CODE XREF: _GetRect+3Bj
                                         ; DATA XREF: 65o
                 push    0FFFFFFFCh      ; jumptable 004363BF case 5
                 pop     eax
                 sub     eax, edi
                 add     [ebp+var_10], eax
                 add     [ebp+var_8], eax

 loc_436429:                             ; CODE XREF: _GetRect+7Cj
                 mov     eax, esi
                 push    0FFFFFFFEh
                 cdq
                 pop     ecx
                 idiv    ecx
                 jmp     loc_43654E
 ; ---------------------------------------------------------------------------

 loc_436436:                             ; CODE XREF: _GetRect+3Bj
                                         ; DATA XREF: 65o
                 push    0FFFFFFFCh      ; jumptable 004363BF case 6
                 pop     eax
                 sub     eax, edi
                 add     [ebp+var_10], eax
                 add     [ebp+var_8], eax
                 jmp     short loc_43640A
 ; ---------------------------------------------------------------------------

 loc_436443:                             ; CODE XREF: _GetRect+3Bj
                                         ; DATA XREF: 65o
                 push    0FFFFFFFCh      ; jumptable 004363BF case 7
                 pop     eax
                 sub     eax, edi
                 add     [ebp+var_10], eax
                 add     [ebp+var_8], eax
                 jmp     loc_436554      ; default
 ; ---------------------------------------------------------------------------

 loc_436453:                             ; CODE XREF: _GetRect+3Bj
                                         ; DATA XREF: 65o
                 add     [ebp+var_10], 4 ; jumptable 004363BF case 8
                 add     [ebp+var_8], 4

 loc_43645B:                             ; CODE XREF: _GetRect+FCj
                 mov     eax, esi
                 cdq
                 sub     eax, edx
                 sar     eax, 1
                 neg     esi

 loc_436464:                             ; CODE XREF: _GetRect+177j
                 sub     esi, eax
                 jmp     loc_436538
 ; ---------------------------------------------------------------------------

 loc_43646B:                             ; CODE XREF: _GetRect+3Bj
                                         ; DATA XREF: 65o
                 add     [ebp+var_10], 4 ; jumptable 004363BF case 9
                 add     [ebp+var_8], 4
                 jmp     short loc_43648D
 ; ---------------------------------------------------------------------------

 loc_436475:                             ; CODE XREF: _GetRect+3Bj
                                         ; DATA XREF: 65o
                 push    0FFFFFFFCh      ; jumptable 004363BF case 10
                 pop     eax
                 sub     eax, edi
                 add     [ebp+var_10], eax
                 add     [ebp+var_8], eax
                 jmp     short loc_43645B
 ; ---------------------------------------------------------------------------

 loc_436482:                             ; CODE XREF: _GetRect+3Bj
                                         ; DATA XREF: 65o
                 push    0FFFFFFFCh      ; jumptable 004363BF case 11
                 pop     eax
                 sub     eax, edi
                 add     [ebp+var_10], eax
                 add     [ebp+var_8], eax

 loc_43648D:                             ; CODE XREF: _GetRect+EFj
                 mov     eax, esi
                 cdq
                 sub     eax, edx
                 sar     eax, 1
                 jmp     loc_43654E
 ; ---------------------------------------------------------------------------

 loc_436499:                             ; CODE XREF: _GetRect+3Bj
                                         ; DATA XREF: 65o
                 add     [ebp+var_10], 4 ; jumptable 004363BF case 12
                 add     [ebp+var_8], 4

 loc_4364A1:                             ; CODE XREF: _GetRect+13Ej
                 neg     esi
                 shl     esi, 1
                 jmp     loc_436538
 ; ---------------------------------------------------------------------------

 loc_4364AA:                             ; CODE XREF: _GetRect+3Bj
                                         ; DATA XREF: 65o
                 add     [ebp+var_10], 4 ; jumptable 004363BF case 13
                 add     [ebp+var_8], 4
                 jmp     loc_436538
 ; ---------------------------------------------------------------------------

 loc_4364B7:                             ; CODE XREF: _GetRect+3Bj
                                         ; DATA XREF: 65o
                 push    0FFFFFFFCh      ; jumptable 004363BF case 14
                 pop     eax
                 sub     eax, edi
                 add     [ebp+var_10], eax
                 add     [ebp+var_8], eax
                 jmp     short loc_4364A1
 ; ---------------------------------------------------------------------------

 loc_4364C4:                             ; CODE XREF: _GetRect+3Bj
                                         ; DATA XREF: 65o
                 push    0FFFFFFFCh      ; jumptable 004363BF case 15
                 pop     eax
                 sub     eax, edi
                 add     [ebp+var_10], eax
                 add     [ebp+var_8], eax
                 jmp     short loc_436538
 ; ---------------------------------------------------------------------------

 loc_4364D1:                             ; CODE XREF: _GetRect+3Bj
                                         ; DATA XREF: 65o
                 add     [ebp+var_10], 4 ; jumptable 004363BF case 16
                 add     [ebp+var_8], 4
                 jmp     short loc_4364F0
 ; ---------------------------------------------------------------------------

 loc_4364DB:                             ; CODE XREF: _GetRect+3Bj
                                         ; DATA XREF: 65o
                 add     [ebp+var_10], 4 ; jumptable 004363BF case 17
                 add     [ebp+var_8], 4
                 jmp     short loc_43650B
 ; ---------------------------------------------------------------------------

 loc_4364E5:                             ; CODE XREF: _GetRect+3Bj
                                         ; DATA XREF: 65o
                 push    0FFFFFFFCh      ; jumptable 004363BF case 18
                 pop     eax
                 sub     eax, edi
                 add     [ebp+var_10], eax
                 add     [ebp+var_8], eax

 loc_4364F0:                             ; CODE XREF: _GetRect+155j
                 mov     eax, esi
                 cdq
                 sub     eax, edx
                 neg     esi
                 sar     eax, 1
                 shl     esi, 1
                 jmp     loc_436464
 ; ---------------------------------------------------------------------------

 loc_436500:                             ; CODE XREF: _GetRect+3Bj
                                         ; DATA XREF: 65o
                 push    0FFFFFFFCh      ; jumptable 004363BF case 19
                 pop     eax
                 sub     eax, edi
                 add     [ebp+var_10], eax
                 add     [ebp+var_8], eax

 loc_43650B:                             ; CODE XREF: _GetRect+15Fj
                 mov     eax, esi
                 cdq
                 sub     eax, edx
                 sar     eax, 1
                 add     eax, esi
                 jmp     short loc_43654E
 ; ---------------------------------------------------------------------------

 loc_436516:                             ; CODE XREF: _GetRect+3Bj
                                         ; DATA XREF: 65o
                 add     [ebp+var_10], 4 ; jumptable 004363BF case 20
                 add     [ebp+var_8], 4
                 jmp     short loc_436535
 ; ---------------------------------------------------------------------------

 loc_436520:                             ; CODE XREF: _GetRect+3Bj
                                         ; DATA XREF: 65o
                 add     [ebp+var_10], 4 ; jumptable 004363BF case 21
                 add     [ebp+var_8], 4
                 jmp     short loc_43654B
 ; ---------------------------------------------------------------------------

 loc_43652A:                             ; CODE XREF: _GetRect+3Bj
                                         ; DATA XREF: 65o
                 push    0FFFFFFFCh      ; jumptable 004363BF case 22
                 pop     eax
                 sub     eax, edi
                 add     [ebp+var_10], eax
                 add     [ebp+var_8], eax

 loc_436535:                             ; CODE XREF: _GetRect+19Aj
                 imul    esi, -3

 loc_436538:                             ; CODE XREF: _GetRect+88j
                                         ; _GetRect+E2j ...
                 add     [ebp+var_C], esi
                 add     [ebp+var_4], esi
                 jmp     short loc_436554 ; default
 ; ---------------------------------------------------------------------------

 loc_436540:                             ; CODE XREF: _GetRect+3Bj
                                         ; DATA XREF: 65o
                 push    0FFFFFFFCh      ; jumptable 004363BF case 23
                 pop     eax
                 sub     eax, edi
                 add     [ebp+var_10], eax
                 add     [ebp+var_8], eax

 loc_43654B:                             ; CODE XREF: _GetRect+1A4j
                 lea     eax, [esi+esi]

 loc_43654E:                             ; CODE XREF: _GetRect+54j
                                         ; _GetRect+ADj ...
                 add     [ebp+var_C], eax
                 add     [ebp+var_4], eax

 loc_436554:                             ; CODE XREF: _GetRect+35j
                                         ; _GetRect+6Fj ...
                 mov     eax, [ebp+arg_0] ; default
                 lea     esi, [ebp+var_10]
                 mov     edi, eax
                 movsd
                 movsd
                 movsd
                 movsd
                 pop     edi
                 pop     esi
                 pop     ebx
                 leave
                 retn

off_436565:
	dd offset loc_4363C6    ; DATA XREF: _GetRect+3Br
	dd offset loc_4363DD    ; jump table for switch statement
	dd offset loc_4363F8
	dd offset loc_436402
	dd offset loc_436411
	dd offset loc_43641E
	dd offset loc_436436
	dd offset loc_436443
	dd offset loc_436453
	dd offset loc_43646B
	dd offset loc_436475
	dd offset loc_436482
	dd offset loc_436499
	dd offset loc_4364AA
	dd offset loc_4364B7
	dd offset loc_4364C4
	dd offset loc_4364D1
	dd offset loc_4364DB
	dd offset loc_4364E5
	dd offset loc_436500
	dd offset loc_436516
	dd offset loc_436520
	dd offset loc_43652A
	dd offset loc_436540
 _GetRect        endp
 



_TryRect        proc near               ; CODE XREF: _TryRect+E4p
                                         ; MapViewMap__CalcLabelRenderOffsets+16Bp ...

 var_20          = dword ptr -20h
 var_1C          = dword ptr -1Ch
 var_18          = dword ptr -18h
 var_14          = dword ptr -14h
 var_10          = dword ptr -10h
 var_C           = dword ptr -0Ch
 var_8           = dword ptr -8
 var_4           = dword ptr -4
 arg_0           = dword ptr  8
 arg_4           = dword ptr  0Ch
 arg_8           = dword ptr  10h
 arg_C           = dword ptr  14h
 arg_10          = dword ptr  18h
 arg_14          = byte ptr  1Ch
 arg_24          = dword ptr  2Ch
 arg_28          = dword ptr  30h

                 push    ebp             ; int __cdecl _TryRect(int,int,int,int,int,class CXRect,struct _mapviewlabel *,bool
                 mov     ebp, esp
                 sub     esp, 20h
                 push    ebx
                 push    esi
                 push    edi
                 mov     ebx, [ebp+arg_0]
                 push    [ebp+arg_10]
                 lea     eax, [ebp+var_10]
                 push    [ebp+arg_C]
                 push    [ebp+arg_8]
                 push    [ebp+arg_4]
                 push    ebx
                 push    eax
                 call    _GetRect
                 pop     ecx
                 lea     esi, [ebp+arg_14]
                 pop     ecx
                 lea     eax, [ebp+var_20]
                 mov     edi, esp
                 push    eax
                 movsd
                 movsd
                 movsd
                 lea     ecx, [ebp+var_10]
                 movsd
                 call    ??ICXRect@EQClasses@@QBE?AV01@V01@@Z
                 cmp     byte ptr [ebp+arg_28], 0
                 jnz     short loc_436639
                 mov     eax, [ebp+var_18]
                 mov     ecx, [ebp+var_14]
                 or      edx, 0FFFFFFFFh
                 cmp     [ebp+var_20], edx
                 jnz     short loc_43661F
                 cmp     [ebp+var_1C], edx
                 jnz     short loc_43661F
                 cmp     eax, edx
                 jnz     short loc_43661F
                 cmp     ecx, edx
                 jz      short loc_436684

 loc_43661F:                             ; CODE XREF: _TryRect+4Bj
                                         ; _TryRect+50j ...
                 mov     edx, [ebp+var_8]
                 sub     eax, [ebp+var_20]
                 sub     edx, [ebp+var_10]
                 cmp     eax, edx
                 jnz     short loc_436684
                 mov     eax, [ebp+var_4]
                 sub     ecx, [ebp+var_1C]
                 sub     eax, [ebp+var_C]
                 cmp     ecx, eax
                 jnz     short loc_436684

 loc_436639:                             ; CODE XREF: _TryRect+3Dj
                 sub     esp, 10h
                 lea     esi, [ebp+var_10]
                 mov     edi, esp
                 movsd
                 movsd
                 movsd
                 movsd
                 call    _CountRectIntersects
                 add     esp, 10h
                 test    eax, eax
                 jnz     short loc_436684
                 mov     ebx, [ebp+arg_24]
                 push    1
                 push    ebx
                 lea     esi, [ebp+var_10]
                 sub     esp, 10h
                 mov     edi, esp
                 movsd
                 movsd
                 movsd
                 movsd
                 call    _AddRect
                 mov     eax, [ebp+var_10]
                 add     esp, 18h
                 sub     eax, [ebp+arg_4]
                 mov     [ebx+2Ch], eax
                 mov     eax, [ebp+var_C]
                 sub     eax, [ebp+arg_8]
                 mov     [ebx+30h], eax
                 xor     eax, eax
                 jmp     loc_43671E
 ; ---------------------------------------------------------------------------

 loc_436684:                             ; CODE XREF: _TryRect+58j
                                         ; _TryRect+65j ...
                 cmp     ebx, 17h
                 jge     short loc_4366B3
                 push    [ebp+arg_28]
                 lea     esi, [ebp+arg_14]
                 push    [ebp+arg_24]
                 sub     esp, 10h
                 inc     ebx
                 mov     edi, esp
                 push    [ebp+arg_10]
                 movsd
                 push    [ebp+arg_C]
                 movsd
                 push    [ebp+arg_8]
                 movsd
                 push    [ebp+arg_4]
                 movsd
                 push    ebx
                 call    _TryRect
                 add     esp, 2Ch
                 jmp     short loc_43671E
 ; ---------------------------------------------------------------------------

 loc_4366B3:                             ; CODE XREF: _TryRect+C2j
                 or      [ebp+arg_24], 0FFFFFFFFh
                 mov     [ebp+arg_28], 32h
                 xor     ebx, ebx

 loc_4366C0:                             ; CODE XREF: _TryRect+152j
                 push    [ebp+arg_10]
                 lea     eax, [ebp+arg_14]
                 push    [ebp+arg_C]
                 push    [ebp+arg_8]
                 push    [ebp+arg_4]
                 push    ebx
                 push    eax
                 call    _GetRect
                 mov     ecx, [eax]
                 add     esp, 8
                 mov     [ebp+var_10], ecx
                 mov     ecx, [eax+4]
                 mov     [ebp+var_C], ecx
                 mov     ecx, [eax+8]
                 mov     [ebp+var_8], ecx
                 mov     eax, [eax+0Ch]
                 lea     esi, [ebp+var_10]
                 mov     edi, esp
                 mov     [ebp+var_4], eax
                 movsd
                 movsd
                 movsd
                 movsd
                 call    _CountRectIntersects
                 add     esp, 10h
                 cmp     eax, [ebp+arg_28]
                 jge     short loc_436713
                 lea     ecx, [ebx+1]
                 mov     [ebp+arg_28], eax
                 test    eax, eax
                 mov     [ebp+arg_24], ecx
                 jz      short loc_436719

 loc_436713:                             ; CODE XREF: _TryRect+13Fj
                 inc     ebx
                 cmp     ebx, 18h
                 jl      short loc_4366C0

 loc_436719:                             ; CODE XREF: _TryRect+14Cj
                 mov     eax, [ebp+arg_24]
                 neg     eax

 loc_43671E:                             ; CODE XREF: _TryRect+BAj
                                         ; _TryRect+ECj
                 pop     edi
                 pop     esi
                 pop     ebx
                 leave
                 retn
 _TryRect        endp


_AddRect        proc near               ; CODE XREF: _TryRect+9Ep
                                         ; MapViewMap__CalcLabelRenderOffsets+CBp ...

 arg_0           = dword ptr  8
 arg_4           = dword ptr  0Ch
 arg_8           = dword ptr  10h
 arg_C           = dword ptr  14h
 arg_10          = dword ptr  18h
 arg_14          = byte ptr  1Ch

                 push    ebp             ; void __cdecl _AddRect(class CXRect,struct _mapviewlabel *,bool
                 mov     ebp, esp
                 push    esi
                 xor     esi, esi
                 cmp     dword_5DF7E8, esi
                 push    1Ch             ; unsigned int
                 jz      short loc_436780
                 call    new
                 cmp     eax, esi
                 pop     ecx
                 jz      short loc_43674B
                 mov     [eax+10h], esi
                 mov     [eax+0Ch], esi
                 mov     [eax+8], esi
                 mov     [eax+4], esi
                 jmp     short loc_43674D
 ; ---------------------------------------------------------------------------

 loc_43674B:                             ; CODE XREF: _AddRect+18j
                 xor     eax, eax

 loc_43674D:                             ; CODE XREF: _AddRect+26j
                 mov     ecx, dword_5DF7E8
                 mov     [eax], ecx
                 mov     ecx, [ebp+arg_0]
                 mov     [eax+4], ecx
                 mov     ecx, [ebp+arg_4]
                 mov     [eax+8], ecx
                 mov     ecx, [ebp+arg_8]
                 mov     [eax+0Ch], ecx
                 mov     ecx, [ebp+arg_C]
                 mov     [eax+10h], ecx
                 mov     ecx, [ebp+arg_10]
                 mov     [eax+14h], ecx
                 mov     cl, [ebp+arg_14]
                 mov     [eax+18h], cl
                 mov     dword_5DF7E8, eax
                 jmp     short loc_4367D7
 ; ---------------------------------------------------------------------------

 loc_436780:                             ; CODE XREF: _AddRect+Ej
                 call    new
                 cmp     eax, esi
                 pop     ecx
                 jz      short loc_436798
                 mov     [eax+10h], esi
                 mov     [eax+0Ch], esi
                 mov     [eax+8], esi
                 mov     [eax+4], esi
                 jmp     short loc_43679A
 ; ---------------------------------------------------------------------------

 loc_436798:                             ; CODE XREF: _AddRect+65j
                 xor     eax, eax

 loc_43679A:                             ; CODE XREF: _AddRect+73j
                 mov     ecx, [ebp+arg_0]
                 mov     dword_5DF7E8, eax
                 mov     [eax], esi
                 mov     eax, dword_5DF7E8
                 add     eax, 4
                 mov     [eax], ecx
                 mov     ecx, [ebp+arg_4]
                 mov     [eax+4], ecx
                 mov     ecx, [ebp+arg_8]
                 mov     [eax+8], ecx
                 mov     ecx, [ebp+arg_C]
                 mov     [eax+0Ch], ecx
                 mov     eax, dword_5DF7E8
                 mov     ecx, [ebp+arg_10]
                 mov     [eax+14h], ecx
                 mov     ecx, dword_5DF7E8
                 mov     al, [ebp+arg_14]
                 mov     [ecx+18h], al

 loc_4367D7:                             ; CODE XREF: _AddRect+5Bj
                 pop     esi
                 pop     ebp
                 retn
 _AddRect        endp



_ClearRects     proc near               ; CODE XREF: MapViewMap__CalcLabelRenderOffsets+19p
                 mov     eax, dword_5DF7E8 ; void __cdecl _ClearRects(void
                 test    eax, eax
                 jz      short loc_436BB0
                 push    esi

 loc_436B9B:                             ; CODE XREF: _ClearRects+1Cj
                 mov     esi, [eax]
                 push    eax
                 call    operator__delete
                 mov     eax, esi
                 pop     ecx
                 test    esi, esi
                 mov     dword_5DF7E8, eax
                 jnz     short loc_436B9B
                 pop     esi

 loc_436BB0:                             ; CODE XREF: _ClearRects+7j
                 and     dword_5DF7E8, 0
                 retn
 _ClearRects     endp


MapViewMap__CalcLabelRenderOffsets proc near
                                         ; CODE XREF: MapViewMap__Draw+4D6p

 var_30          = dword ptr -30h
 var_2C          = dword ptr -2Ch
 var_28          = dword ptr -28h
 var_24          = dword ptr -24h
 var_20          = dword ptr -20h
 var_1C          = dword ptr -1Ch
 var_18          = dword ptr -18h
 var_14          = dword ptr -14h
 var_10          = dword ptr -10h
 var_C           = dword ptr -0Ch
 var_4           = dword ptr -4
 arg_0           = dword ptr  8
 arg_4           = dword ptr  0Ch

                 push    ebp             ; public: void __thiscall MapViewMap::CalcLabelRenderOffsets(class CXRect
                 mov     ebp, esp
                 sub     esp, 30h
                 push    ebx
                 push    esi
                 push    edi
                 mov     edi, ecx
                 xor     esi, esi
                 mov     [ebp+var_4], edi
                 cmp     [edi+44h], esi
                 jz      loc_436B8A
                 call    _ClearRects
                 mov     ebx, [edi+44h]

 loc_43696A:                             ; CODE XREF: MapViewMap__CalcLabelRenderOffsets+DAj
                 cmp     ebx, esi
                 jz      loc_436A28
                 push    dword ptr [ebx+20h]
                 mov     ecx, edi
                 call    MapViewMap__IsLayerVisible
                 test    al, al
                 jz      loc_436A21
                 mov     [ebp+var_24], esi
                 mov     [ebp+var_28], esi
                 mov     [ebp+var_2C], esi
                 mov     [ebp+var_30], esi
                 lea     esi, [ebx+8]
                 lea     edi, [ebp+var_1C]
                 movsd
                 mov     ecx, [ebp+var_4]
                 lea     eax, [ebp+var_1C]
                 movsd
                 push    eax
                 movsd
                 call    MapViewMap__TransformPoint
                 fild    [ebp+arg_0]
                 fadd    [ebp+var_1C]
                 fst     [ebp+var_1C]
                 fild    [ebp+arg_4]
                 fadd    [ebp+var_18]
                 fst     [ebp+var_18]
                 fld     ds:__real@4@3fff8000000000000000 ; __real@4@3fff800000000000000
                 fld     st(2)
                 fadd    st, st(1)
                 call    __ftol
                 fld     st(1)
                 fadd    st, st(1)
                 mov     esi, eax
                 call    __ftol
                 fld     st(2)
                 fsub    st, st(1)
                 mov     edi, eax
                 call    __ftol
                 fld     st(1)
                 fsub    st, st(1)
                 mov     [ebp+var_C], eax
                 call    __ftol
                 mov     ecx, [ebp+var_C]
                 mov     [ebp+var_2C], eax
                 fstp    st
                 fstp    st
                 mov     [ebp+var_30], ecx
                 lea     ecx, [ebp+var_30]
                 fstp    st
                 mov     [ebp+var_28], esi
                 mov     [ebp+var_24], edi
                 call    CXRect__Normalize
                 push    0
                 push    ebx
                 sub     esp, 10h
                 lea     esi, [ebp+var_30]
                 mov     edi, esp
                 movsd
                 movsd
                 movsd
                 movsd
                 call    _AddRect
                 mov     edi, [ebp+var_4]
                 add     esp, 18h
                 xor     esi, esi

 loc_436A21:                             ; CODE XREF: MapViewMap__CalcLabelRenderOffsets+35j
                 mov     ebx, [ebx]
                 jmp     loc_43696A
 ; ---------------------------------------------------------------------------

 loc_436A28:                             ; CODE XREF: MapViewMap__CalcLabelRenderOffsets+23j
                 mov     ebx, [edi+44h]

 loc_436A2B:                             ; CODE XREF: MapViewMap__CalcLabelRenderOffsets+22Dj
                 cmp     ebx, esi
                 jz      loc_436B7B
                 push    dword ptr [ebx+20h]
                 mov     ecx, edi
                 mov     [ebx+2Ch], esi
                 mov     [ebx+30h], esi
                 call    MapViewMap__IsLayerVisible
                 test    al, al
                 jz      loc_436B74
                 cmp     byte ptr [edi+80h], 0
                 jz      loc_436B74
                 mov     [ebp+var_14], esi
                 mov     [ebp+var_18], esi
                 mov     [ebp+var_1C], esi
                 mov     [ebp+var_20], esi
                 lea     esi, [ebx+8]
                 lea     edi, [ebp+var_10]
                 movsd
                 mov     ecx, [ebp+var_4]
                 lea     eax, [ebp+var_10]
                 movsd
                 push    eax
                 movsd
                 call    MapViewMap__TransformPoint
                 fild    [ebp+arg_0]
                 push    1
                 push    ebx
                 sub     esp, 10h
                 lea     esi, [ebp+arg_0]
                 fadd    [ebp+var_10]
                 mov     edi, esp
                 push    dword ptr [ebx+28h]
                 movsd
                 fstp    [ebp+var_10]
                 fild    [ebp+arg_4]
                 movsd
                 fadd    [ebp+var_C]
                 push    dword ptr [ebx+24h]
                 movsd
                 fstp    [ebp+var_C]
                 fld     [ebp+var_C]
                 movsd
                 call    __ftol
                 fld     [ebp+var_10]
                 push    eax
                 call    __ftol
                 push    eax
                 push    0
                 call    _TryRect
                 add     esp, 2Ch
                 test    eax, eax
                 jge     loc_436B6F
                 push    1
                 push    ebx
                 sub     esp, 10h
                 lea     esi, [ebp+arg_0]
                 mov     edi, esp
                 push    dword ptr [ebx+28h]
                 movsd
                 fld     [ebp+var_C]
                 movsd
                 push    dword ptr [ebx+24h]
                 movsd
                 movsd
                 call    __ftol
                 fld     [ebp+var_10]
                 push    eax
                 call    __ftol
                 push    eax
                 push    0
                 call    _TryRect
                 mov     esi, eax
                 add     esp, 2Ch
                 test    esi, esi
                 jge     short loc_436B6F
                 push    dword ptr [ebx+28h]
                 fld     [ebp+var_C]
                 push    dword ptr [ebx+24h]
                 call    __ftol
                 fld     [ebp+var_10]
                 push    eax
                 call    __ftol
                 push    eax
                 or      eax, 0FFFFFFFFh
                 sub     eax, esi
                 push    eax
                 lea     eax, [ebp+var_30]
                 push    eax
                 call    _GetRect
                 mov     ecx, [eax]
                 add     esp, 18h
                 mov     [ebp+var_20], ecx
                 mov     ecx, [eax+4]
                 push    1
                 push    ebx
                 mov     [ebp+var_1C], ecx
                 mov     ecx, [eax+8]
                 mov     eax, [eax+0Ch]
                 sub     esp, 10h
                 lea     esi, [ebp+var_20]
                 mov     edi, esp
                 mov     [ebp+var_18], ecx
                 mov     [ebp+var_14], eax
                 movsd
                 movsd
                 movsd
                 movsd
                 call    _AddRect
                 fild    [ebp+var_20]
                 add     esp, 18h
                 fsub    [ebp+var_10]
                 call    __ftol
                 fild    [ebp+var_1C]
                 mov     [ebx+2Ch], eax
                 fsub    [ebp+var_C]
                 call    __ftol
                 mov     [ebx+30h], eax

 loc_436B6F:                             ; CODE XREF: MapViewMap__CalcLabelRenderOffsets+175j
                                         ; MapViewMap__CalcLabelRenderOffsets+1B0j
                 mov     edi, [ebp+var_4]
                 xor     esi, esi

 loc_436B74:                             ; CODE XREF: MapViewMap__CalcLabelRenderOffsets+FCj
                                         ; MapViewMap__CalcLabelRenderOffsets+109j
                 mov     ebx, [ebx]
                 jmp     loc_436A2B
 ; ---------------------------------------------------------------------------

 loc_436B7B:                             ; CODE XREF: MapViewMap__CalcLabelRenderOffsets+E4j
                 call    _CheckRects
                 call    _CheckRects
                 call    _CheckRects

 loc_436B8A:                             ; CODE XREF: MapViewMap__CalcLabelRenderOffsets+13j
                 pop     edi
                 pop     esi
                 pop     ebx
                 leave
                 retn    10h
 MapViewMap__CalcLabelRenderOffsets endp



MapViewMap__DrawClippedLine2 proc near   ; CODE XREF: MapViewMap__Draw+400p
                                         ; MapViewMap__Draw+4A7p ...

 var_30          = qword ptr -30h
 var_28          = dword ptr -28h
 var_24          = dword ptr -24h
 var_1C          = dword ptr -1Ch
 var_18          = dword ptr -18h
 var_10          = dword ptr -10h
 var_C           = dword ptr -0Ch
 var_8           = dword ptr -8
 var_4           = dword ptr -4
 arg_0           = dword ptr  8
 arg_4           = dword ptr  0Ch
 arg_8           = dword ptr  10h
 arg_C           = dword ptr  14h
 arg_10          = dword ptr  18h
 arg_14          = dword ptr  1Ch

                 push    ebp             ; public: bool __thiscall MapViewMap::DrawClippedLine(struct T3D_XYZ *,struct T3D_RGB,class CXRect
                 mov     ebp, esp
                 sub     esp, 28h
                 fild    [ebp+arg_8]
                 mov     ecx, [ebp+arg_0]
                 fstp    [ebp+var_4]
                 fld     dword ptr [ecx]
                 fcomp   [ebp+var_4]
                 fnstsw  ax
                 sahf
                 jnb     short loc_437AF9
                 fld     dword ptr [ecx+0Ch]
                 fcomp   [ebp+var_4]
                 fnstsw  ax
                 sahf
                 jb      loc_437D2F

 loc_437AF9:                             ; CODE XREF: MapViewMap__DrawClippedLine+17j
                 fild    [ebp+arg_10]
                 fstp    [ebp+var_8]
                 fld     dword ptr [ecx]
                 fcomp   [ebp+var_8]
                 fnstsw  ax
                 sahf
                 jbe     short loc_437B18
                 fld     dword ptr [ecx+0Ch]
                 fcomp   [ebp+var_8]
                 fnstsw  ax
                 sahf
                 ja      loc_437D2F

 loc_437B18:                             ; CODE XREF: MapViewMap__DrawClippedLine+36j
                 fild    [ebp+arg_C]
                 fstp    [ebp+arg_0]
                 fld     dword ptr [ecx+4]
                 fcomp   [ebp+arg_0]
                 fnstsw  ax
                 sahf
                 jnb     short loc_437B38
                 fld     dword ptr [ecx+10h]
                 fcomp   [ebp+arg_0]
                 fnstsw  ax
                 sahf
                 jb      loc_437D2F

 loc_437B38:                             ; CODE XREF: MapViewMap__DrawClippedLine+56j
                 fild    [ebp+arg_14]
                 fstp    [ebp+arg_14]
                 fld     dword ptr [ecx+4]
                 fcomp   [ebp+arg_14]
                 fnstsw  ax
                 sahf
                 jbe     short loc_437B58
                 fld     dword ptr [ecx+10h]
                 fcomp   [ebp+arg_14]
                 fnstsw  ax
                 sahf
                 ja      loc_437D2F

 loc_437B58:                             ; CODE XREF: MapViewMap__DrawClippedLine+76j
                 push    esi
                 push    edi
                 mov     esi, ecx
                 lea     edi, [ebp+var_28]
                 movsd
                 movsd
                 movsd
                 lea     esi, [ecx+0Ch]
                 lea     edi, [ebp+var_1C]
                 movsd
                 movsd
                 movsd
                 fld     [ebp+var_28]
                 fsub    [ebp+var_1C]
                 pop     edi
                 pop     esi
                 fstp    [ebp+var_10]
                 fld     [ebp+var_24]
                 fsub    [ebp+var_18]
                 fstp    [ebp+var_C]
                 fld     [ebp+var_28]
                 fcomp   [ebp+var_4]
                 fnstsw  ax
                 sahf
                 jnb     short loc_437BA4
                 fld     [ebp+var_4]
                 fsub    [ebp+var_28]
                 push    ecx
                 push    ecx
                 fdiv    [ebp+var_10]
                 fstp    [esp+30h+var_30]
                 call    _fabs
                 mov     eax, [ebp+var_4]
                 pop     ecx
                 pop     ecx
                 jmp     short loc_437BC7
 ; ---------------------------------------------------------------------------

 loc_437BA4:                             ; CODE XREF: MapViewMap__DrawClippedLine+B7j
                 fld     [ebp+var_28]
                 fcomp   [ebp+var_8]
                 fnstsw  ax
                 sahf
                 jbe     short loc_437BD3
                 fld     [ebp+var_28]
                 fsub    [ebp+var_8]
                 push    ecx
                 push    ecx
                 fdiv    [ebp+var_10]
                 fstp    [esp+30h+var_30]
                 call    _fabs
                 mov     eax, [ebp+var_8]
                 pop     ecx
                 pop     ecx

 loc_437BC7:                             ; CODE XREF: MapViewMap__DrawClippedLine+D1j
                 fmul    [ebp+var_C]
                 mov     [ebp+var_28], eax
                 fsubr   [ebp+var_24]
                 fstp    [ebp+var_24]

 loc_437BD3:                             ; CODE XREF: MapViewMap__DrawClippedLine+DCj
                 fld     [ebp+var_1C]
                 fcomp   [ebp+var_4]
                 fnstsw  ax
                 sahf
                 jnb     short loc_437BF8
                 fld     [ebp+var_4]
                 fsub    [ebp+var_1C]
                 push    ecx
                 push    ecx
                 fdiv    dword ptr [ebp-10h]
                 fstp    qword ptr [esp]
                 call    _fabs
                 mov     eax, [ebp-4]
                 pop     ecx
                 pop     ecx
                 jmp     short loc_437C1B
 ; ---------------------------------------------------------------------------

 loc_437BF8:                             ; CODE XREF: MapViewMap__DrawClippedLine+10Bj
                 fld     dword ptr [ebp-1Ch]
                 fcomp   dword ptr [ebp-8]
                 fnstsw  ax
                 sahf
                 jbe     short loc_437C27
                 fld     [ebp+var_1C]
                 fsub    [ebp+var_8]
                 push    ecx
                 push    ecx
                 fdiv    [ebp+var_10]
                 fstp    [esp+30h+var_30]
                 call    _fabs
                 mov     eax, [ebp+var_8]
                 pop     ecx
                 pop     ecx

 loc_437C1B:                             ; CODE XREF: MapViewMap__DrawClippedLine+125j
                 fmul    [ebp+var_C]
                 mov     [ebp+var_1C], eax
                 fadd    [ebp+var_18]
                 fstp    [ebp+var_18]

 loc_437C27:                             ; CODE XREF: MapViewMap__DrawClippedLine+130j
                 fld     [ebp+var_24]
                 fcomp   [ebp+arg_0]
                 fnstsw  ax
                 sahf
                 jnb     short loc_437C41
                 fld     [ebp+var_18]
                 fcomp   [ebp+arg_0]
                 fnstsw  ax
                 sahf
                 jb      loc_437D2F

 loc_437C41:                             ; CODE XREF: MapViewMap__DrawClippedLine+15Fj
                 fld     [ebp+var_24]
                 fcomp   [ebp+arg_14]
                 fnstsw  ax
                 sahf
                 jbe     short loc_437C5B
                 fld     [ebp+var_18]
                 fcomp   [ebp+arg_14]
                 fnstsw  ax
                 sahf
                 ja      loc_437D2F

 loc_437C5B:                             ; CODE XREF: MapViewMap__DrawClippedLine+179j
                 fld     [ebp+var_24]
                 fcomp   [ebp+arg_0]
                 fnstsw  ax
                 sahf
                 jnb     short loc_437C80
                 fld     [ebp+arg_0]
                 fsub    [ebp+var_24]
                 push    ecx
                 push    ecx
                 fdiv    [ebp+var_C]
                 fstp    [esp+30h+var_30]
                 call    _fabs
                 mov     eax, [ebp+arg_0]
                 pop     ecx
                 pop     ecx
                 jmp     short loc_437CA3
 ; ---------------------------------------------------------------------------

 loc_437C80:                             ; CODE XREF: MapViewMap__DrawClippedLine+193j
                 fld     [ebp+var_24]
                 fcomp   [ebp+arg_14]
                 fnstsw  ax
                 sahf
                 jbe     short loc_437CAF
                 fld     [ebp+var_24]
                 fsub    [ebp+arg_14]
                 push    ecx
                 push    ecx
                 fdiv    [ebp+var_C]
                 fstp    [esp+30h+var_30]
                 call    _fabs
                 mov     eax, [ebp+arg_14]
                 pop     ecx
                 pop     ecx

 loc_437CA3:                             ; CODE XREF: MapViewMap__DrawClippedLine+1ADj
                 fmul    [ebp+var_10]
                 mov     [ebp+var_24], eax
                 fsubr   [ebp+var_28]
                 fstp    [ebp+var_28]

 loc_437CAF:                             ; CODE XREF: MapViewMap__DrawClippedLine+1B8j
                 fld     [ebp+var_18]
                 fcomp   [ebp+arg_0]
                 fnstsw  ax
                 sahf
                 jnb     short loc_437CD4
                 fld     [ebp+arg_0]
                 fsub    [ebp+var_18]
                 push    ecx
                 push    ecx
                 fdiv    [ebp+var_C]
                 fstp    [esp+30h+var_30]
                 call    _fabs
                 mov     eax, [ebp+arg_0]
                 pop     ecx
                 pop     ecx
                 jmp     short loc_437CF7
 ; ---------------------------------------------------------------------------

 loc_437CD4:                             ; CODE XREF: MapViewMap__DrawClippedLine+1E7j
                 fld     [ebp+var_18]
                 fcomp   [ebp+arg_14]
                 fnstsw  ax
                 sahf
                 jbe     short loc_437D03
                 fld     [ebp+var_18]
                 fsub    [ebp+arg_14]
                 push    ecx
                 push    ecx
                 fdiv    [ebp+var_C]
                 fstp    [esp+30h+var_30]
                 call    _fabs
                 mov     eax, [ebp+arg_14]
                 pop     ecx
                 pop     ecx

 loc_437CF7:                             ; CODE XREF: MapViewMap__DrawClippedLine+201j
                 fmul    [ebp+var_10]
                 mov     [ebp+var_18], eax
                 fadd    [ebp+var_1C]
                 fstp    [ebp+var_1C]

 loc_437D03:                             ; CODE XREF: MapViewMap__DrawClippedLine+20Cj
                 fld     [ebp+var_28]
                 fcomp   [ebp+var_4]
                 fnstsw  ax
                 sahf
                 jnb     short loc_437D19
                 fld     [ebp+var_1C]
                 fcomp   [ebp+var_4]
                 fnstsw  ax
                 sahf
                 jb      short loc_437D2F

 loc_437D19:                             ; CODE XREF: MapViewMap__DrawClippedLine+23Bj
                 fld     [ebp+var_28]
                 fcomp   [ebp+var_8]
                 fnstsw  ax
                 sahf
                 jbe     short loc_437D33
                 fld     [ebp+var_1C]
                 fcomp   [ebp+var_8]
                 fnstsw  ax
                 sahf
                 jbe     short loc_437D33

 loc_437D2F:                             ; CODE XREF: MapViewMap__DrawClippedLine+22j
                                         ; MapViewMap__DrawClippedLine+41j ...
                 xor     al, al
                 jmp     short locret_437D44
 ; ---------------------------------------------------------------------------

 loc_437D33:                             ; CODE XREF: MapViewMap__DrawClippedLine+251j
                                         ; MapViewMap__DrawClippedLine+25Cj
                 push    [ebp+arg_4]
                 lea     eax, [ebp+var_28]
                 push    eax
                 call    dword ptr [ds:__imp__t3dDeferLine] ; __imp__t3dDeferLine
                 pop     ecx
                 mov     al, 1
                 pop     ecx

 locret_437D44:                          ; CODE XREF: MapViewMap__DrawClippedLine+260j
                 leave
                 retn    18h
 MapViewMap__DrawClippedLine2 endp

 MapViewMap__DrawClippedLine proc near   ; CODE XREF: MapViewMap__Draw+54Fp
                                        ; MapViewMap__Draw+63Cp ...

var_30          = qword ptr -30h
var_28          = dword ptr -28h
var_24          = dword ptr -24h
var_20          = dword ptr -20h
var_1C          = dword ptr -1Ch
var_18          = dword ptr -18h
var_14          = dword ptr -14h
var_10          = dword ptr -10h
var_C           = dword ptr -0Ch
var_8           = dword ptr -8
var_4           = dword ptr -4
arg_0           = qword ptr  8
arg_8           = dword ptr  10h
arg_C           = dword ptr  14h
arg_10          = dword ptr  18h
arg_14          = dword ptr  1Ch

                push    ebp
                mov     ebp, esp
                sub     esp, 28h
                fild    [ebp+arg_8]
                mov     ecx, dword ptr [ebp+arg_0]
                fstp    [ebp+var_4]
                fld     dword ptr [ecx]
                fcomp   [ebp+var_4]
                fnstsw  ax
                test    ah, 5
                jp      short loc_533B83
                fld     dword ptr [ecx+0Ch]
                fcomp   [ebp+var_4]
                fnstsw  ax
                test    ah, 5
                jnp     loc_533DEB

loc_533B83:                             ; CODE XREF: MapViewMap__DrawClippedLine+19j
                fild    [ebp+arg_10]
                fstp    [ebp+var_8]
                fld     dword ptr [ecx]
                fcomp   [ebp+var_8]
                fnstsw  ax
                test    ah, 41h
                jnz     short loc_533BA6
                fld     dword ptr [ecx+0Ch]
                fcomp   [ebp+var_8]
                fnstsw  ax
                test    ah, 41h
                jz      loc_533DEB

loc_533BA6:                             ; CODE XREF: MapViewMap__DrawClippedLine+3Cj
                fild    [ebp+arg_C]
                fstp    dword ptr [ebp+arg_0]
                fld     dword ptr [ecx+4]
                fcomp   dword ptr [ebp+arg_0]
                fnstsw  ax
                test    ah, 5
                jp      short loc_533BCA
                fld     dword ptr [ecx+10h]
                fcomp   dword ptr [ebp+arg_0]
                fnstsw  ax
                test    ah, 5
                jnp     loc_533DEB

loc_533BCA:                             ; CODE XREF: MapViewMap__DrawClippedLine+60j
                fild    [ebp+arg_14]
                fstp    [ebp+arg_14]
                fld     dword ptr [ecx+4]
                fcomp   [ebp+arg_14]
                fnstsw  ax
                test    ah, 41h
                jnz     short loc_533BEE
                fld     dword ptr [ecx+10h]
                fcomp   [ebp+arg_14]
                fnstsw  ax
                test    ah, 41h
                jz      loc_533DEB

loc_533BEE:                             ; CODE XREF: MapViewMap__DrawClippedLine+84j
                mov     eax, [ecx]
                mov     [ebp+var_28], eax
                fld     [ebp+var_28]
                mov     eax, [ecx+4]
                mov     [ebp+var_24], eax
                mov     eax, [ecx+8]
                mov     [ebp+var_20], eax
                mov     eax, [ecx+0Ch]
                mov     [ebp+var_1C], eax
                fsub    [ebp+var_1C]
                mov     eax, [ecx+10h]
                mov     [ebp+var_18], eax
                mov     eax, [ecx+14h]
                fstp    [ebp+var_10]
                fld     [ebp+var_24]
                mov     [ebp+var_14], eax
                fsub    [ebp+var_18]
                fstp    [ebp+var_C]
                fld     [ebp+var_28]
                fcomp   [ebp+var_4]
                fnstsw  ax
                test    ah, 5
                jp      short loc_533C48
                fld     [ebp+var_4]
                push    ecx
                fsub    [ebp+var_28]
                push    ecx             ; double
                fdiv    [ebp+var_10]
                fstp    [esp+30h+var_30]
                call    _fabs
                mov     eax, [ebp+var_4]
                jmp     short loc_533C6B
; ---------------------------------------------------------------------------

loc_533C48:                             ; CODE XREF: MapViewMap__DrawClippedLine+D7j
                fld     [ebp+var_28]
                fcomp   [ebp+var_8]
                fnstsw  ax
                test    ah, 41h
                jnz     short loc_533C79
                fld     [ebp+var_28]
                push    ecx
                fsub    [ebp+var_8]
                push    ecx             ; double
                fdiv    [ebp+var_10]
                fstp    [esp+30h+var_30]
                call    _fabs
                mov     eax, [ebp+var_8]

loc_533C6B:                             ; CODE XREF: MapViewMap__DrawClippedLine+EFj
                fmul    [ebp+var_C]
                pop     ecx
                pop     ecx
                fsubr   [ebp+var_24]
                mov     [ebp+var_28], eax
                fstp    [ebp+var_24]

loc_533C79:                             ; CODE XREF: MapViewMap__DrawClippedLine+FCj
                fld     [ebp+var_1C]
                fcomp   [ebp+var_4]
                fnstsw  ax
                test    ah, 5
                jp      short loc_533C9E
                fld     [ebp+var_4]
                push    ecx
                fsub    [ebp+var_1C]
                push    ecx             ; double
                fdiv    [ebp+var_10]
                fstp    [esp+30h+var_30]
                call    _fabs
                mov     eax, [ebp+var_4]
                jmp     short loc_533CC1
; ---------------------------------------------------------------------------

loc_533C9E:                             ; CODE XREF: MapViewMap__DrawClippedLine+12Dj
                fld     [ebp+var_1C]
                fcomp   [ebp+var_8]
                fnstsw  ax
                test    ah, 41h
                jnz     short loc_533CCF
                fld     [ebp+var_1C]
                push    ecx
                fsub    [ebp+var_8]
                push    ecx             ; double
                fdiv    [ebp+var_10]
                fstp    [esp+30h+var_30]
                call    _fabs
                mov     eax, [ebp+var_8]

loc_533CC1:                             ; CODE XREF: MapViewMap__DrawClippedLine+145j
                fmul    [ebp+var_C]
                pop     ecx
                pop     ecx
                fadd    [ebp+var_18]
                mov     [ebp+var_1C], eax
                fstp    [ebp+var_18]

loc_533CCF:                             ; CODE XREF: MapViewMap__DrawClippedLine+152j
                fld     [ebp+var_24]
                fcomp   dword ptr [ebp+arg_0]
                fnstsw  ax
                test    ah, 5
                jp      short loc_533CED
                fld     [ebp+var_18]
                fcomp   dword ptr [ebp+arg_0]
                fnstsw  ax
                test    ah, 5
                jnp     loc_533DEB

loc_533CED:                             ; CODE XREF: MapViewMap__DrawClippedLine+183j
                fld     [ebp+var_24]
                fcomp   [ebp+arg_14]
                fnstsw  ax
                test    ah, 41h
                jnz     short loc_533D0B
                fld     [ebp+var_18]
                fcomp   [ebp+arg_14]
                fnstsw  ax
                test    ah, 41h
                jz      loc_533DEB

loc_533D0B:                             ; CODE XREF: MapViewMap__DrawClippedLine+1A1j
                fld     [ebp+var_24]
                fcomp   dword ptr [ebp+arg_0]
                fnstsw  ax
                test    ah, 5
                jp      short loc_533D30
                fld     dword ptr [ebp+arg_0]
                push    ecx
                fsub    [ebp+var_24]
                push    ecx             ; double
                fdiv    [ebp+var_C]
                fstp    [esp+30h+var_30]
                call    _fabs
                mov     eax, dword ptr [ebp+arg_0]
                jmp     short loc_533D53
; ---------------------------------------------------------------------------

loc_533D30:                             ; CODE XREF: MapViewMap__DrawClippedLine+1BFj
                fld     [ebp+var_24]
                fcomp   [ebp+arg_14]
                fnstsw  ax
                test    ah, 41h
                jnz     short loc_533D61
                fld     [ebp+var_24]
                push    ecx
                fsub    [ebp+arg_14]
                push    ecx             ; double
                fdiv    [ebp+var_C]
                fstp    [esp+30h+var_30]
                call    _fabs
                mov     eax, [ebp+arg_14]

loc_533D53:                             ; CODE XREF: MapViewMap__DrawClippedLine+1D7j
                fmul    [ebp+var_10]
                pop     ecx
                pop     ecx
                fsubr   [ebp+var_28]
                mov     [ebp+var_24], eax
                fstp    [ebp+var_28]

loc_533D61:                             ; CODE XREF: MapViewMap__DrawClippedLine+1E4j
                fld     [ebp+var_18]
                fcomp   dword ptr [ebp+arg_0]
                fnstsw  ax
                test    ah, 5
                jp      short loc_533D86
                fld     dword ptr [ebp+arg_0]
                push    ecx
                fsub    [ebp+var_18]
                push    ecx             ; double
                fdiv    [ebp+var_C]
                fstp    [esp+30h+var_30]
                call    _fabs
                mov     eax, dword ptr [ebp+arg_0]
                jmp     short loc_533DA9
; ---------------------------------------------------------------------------

loc_533D86:                             ; CODE XREF: MapViewMap__DrawClippedLine+215j
                fld     [ebp+var_18]
                fcomp   [ebp+arg_14]
                fnstsw  ax
                test    ah, 41h
                jnz     short loc_533DB7
                fld     [ebp+var_18]
                push    ecx
                fsub    [ebp+arg_14]
                push    ecx             ; double
                fdiv    [ebp+var_C]
                fstp    [esp+30h+var_30]
                call    _fabs
                mov     eax, [ebp+arg_14]

loc_533DA9:                             ; CODE XREF: MapViewMap__DrawClippedLine+22Dj
                fmul    [ebp+var_10]
                pop     ecx
                pop     ecx
                fadd    [ebp+var_1C]
                mov     [ebp+var_18], eax
                fstp    [ebp+var_1C]

loc_533DB7:                             ; CODE XREF: MapViewMap__DrawClippedLine+23Aj
                fld     [ebp+var_28]
                fcomp   [ebp+var_4]
                fnstsw  ax
                test    ah, 5
                jp      short loc_533DD1
                fld     [ebp+var_1C]
                fcomp   [ebp+var_4]
                fnstsw  ax
                test    ah, 5
                jnp     short loc_533DEB

loc_533DD1:                             ; CODE XREF: MapViewMap__DrawClippedLine+26Bj
                fld     [ebp+var_28]
                fcomp   [ebp+var_8]
                fnstsw  ax
                test    ah, 41h
                jnz     short loc_533DEF
                fld     [ebp+var_1C]
                fcomp   [ebp+var_8]
                fnstsw  ax
                test    ah, 41h
                jnz     short loc_533DEF

loc_533DEB:                             ; CODE XREF: MapViewMap__DrawClippedLine+26j
                                        ; MapViewMap__DrawClippedLine+49j ...
                xor     al, al
                jmp     short locret_533E07
; ---------------------------------------------------------------------------

loc_533DEF:                             ; CODE XREF: MapViewMap__DrawClippedLine+285j
                                        ; MapViewMap__DrawClippedLine+292j
                push    dword ptr [ebp+arg_0+4]
                ;mov     ecx, dword_99E364
                ;mov     eax, [ecx]
                ;lea     edx, [ebp+var_1C]
                ;push    edx
                lea     edx, [ebp+var_28]
                push    edx
                ;call    dword ptr [eax+70h]
				call    dword ptr [ds:__imp__t3dDeferLine] ; __imp__t3dDeferLine
                mov     al, 1

locret_533E07:                          ; CODE XREF: MapViewMap__DrawClippedLine+296j
                leave
                retn    18h
MapViewMap__DrawClippedLine endp

;				  push    [ebp+arg_4]
 ;                lea     eax, [ebp+var_28]
  ;               push    eax
   ;              call    dword ptr [ds:__imp__t3dDeferLine] ; __imp__t3dDeferLine
    ;             pop     ecx
     ;            mov     al, 1
      ;           pop     ecx

new             proc near               ; CODE XREF: CBuffWindow__CBuffWindow+148p
                                         ; sub_40A970+34p ...

 arg_0           = dword ptr  4

                 push    1
                 push    [esp+4+arg_0]
                 ;call    __nh_malloc
                 call    _malloc
                 pop     ecx
                 pop     ecx
                 retn
new             endp


operator__delete proc near              ; CODE XREF: sub_401307+10p
                                         ; sub_4022CF+26p ...

Memory          = dword ptr  4
                 push    [esp+Memory]    ; Memory
                 call    _free
                 pop     ecx
                 retn
operator__delete endp


_MapViewMap_SetMarkedLine proc near     ; CODE XREF: CMapToolbarWnd__WndNotification+5Bp
                                         ; CMapViewWnd__WndNotification+33Ep ...

 arg_0           = dword ptr  4

                 push    esi             ; public: void __thiscall MapViewMap::SetMarkedLine(struct _mapviewline *
                 push    edi
                 mov     edi, [esp+8+arg_0]
                 mov     esi, ecx
                 test    edi, edi
                 mov     eax, [esi+5Ch]
                 jnz     short loc_4381AC
                 test    eax, eax
                 jz      short loc_4381A6

 loc_438197:                             ; CODE XREF: MapViewMap__SetMarkedLine+20j
                 mov     edi, [eax]
                 push    eax
                 call    operator__delete
                 test    edi, edi
                 pop     ecx
                 mov     eax, edi
                 jnz     short loc_438197

 loc_4381A6:                             ; CODE XREF: MapViewMap__SetMarkedLine+11j
                 and     dword ptr [esi+5Ch], 0
                 jmp     short loc_4381CC
 ; ---------------------------------------------------------------------------

 loc_4381AC:                             ; CODE XREF: MapViewMap__SetMarkedLine+Dj
                                         ; MapViewMap__SetMarkedLine+33j
                 test    eax, eax
                 jz      short loc_4381B9
                 cmp     edi, [eax+4]
                 jz      short loc_4381CC
                 mov     eax, [eax]
                 jmp     short loc_4381AC
 ; ---------------------------------------------------------------------------

 loc_4381B9:                             ; CODE XREF: MapViewMap__SetMarkedLine+2Aj
                 push    8               ; unsigned int
                 call    new
                 pop     ecx
                 mov     [eax+4], edi
                 mov     ecx, [esi+5Ch]
                 mov     [eax], ecx
                 mov     [esi+5Ch], eax

 loc_4381CC:                             ; CODE XREF: MapViewMap__SetMarkedLine+26j
                                         ; MapViewMap__SetMarkedLine+2Fj
                 pop     edi
                 pop     esi
                 retn    4
_MapViewMap_SetMarkedLine endp


MapViewMap__PreCalcRenderValues proc near ; CODE XREF: MapViewMap__Draw+146p

 var_14          = qword ptr -14h
 var_4           = dword ptr -4

                 push    ebp             ; public: void __thiscall MapViewMap::PreCalcRenderValues(void
                 mov     ebp, esp
                 push    ecx
                 push    ecx
                 push    esi
                 mov     esi, ecx
                 fld     dword ptr [esi+8]
                 fsub    dword ptr [esi]
                 fld     dword ptr [esi+10h]
                 fdiv    st, st(1)
                 fst     dword ptr [esi+38h]
                 fld     dword ptr [esi+0Ch]
                 fsub    dword ptr [esi+4]
                 fst     [ebp+var_4]
                 fdivr   dword ptr [esi+14h]
                 fst     dword ptr [esi+3Ch]
                 fldz
                 fstp    dword ptr [esi+30h]
                 fldz
                 fstp    dword ptr [esi+34h]
                 fld     st(1)
                 fcomp   st(1)
                 fnstsw  ax
                 fstp    st
                 sahf
                 fstp    st
                 jnb     short loc_436D5E
                 fstp    st
                 fld     [ebp+var_4]
                 push    ecx
                 push    ecx
                 fstp    [esp+14h+var_14]
                 call    _fabs
                 fmul    dword ptr [esi+38h]
                 fstp    qword ptr [ebp-8]
                 fld     dword ptr [esi+0Ch]
                 fsub    dword ptr [esi+4]
                 fstp    [esp+14h+var_14]
                 call    _fabs
                 fmul    dword ptr [esi+3Ch]
                 mov     eax, [esi+38h]
                 pop     ecx
                 pop     ecx
                 mov     [esi+3Ch], eax
                 fsubr   qword ptr [ebp-8]
                 fmul    ds:__real@8@bffe8000000000000000 ; __real@8@bffe800000000000000
                 fstp    dword ptr [esi+34h]
                 jmp     short loc_436D92
 ; ---------------------------------------------------------------------------

 loc_436D5E:                             ; CODE XREF: MapViewMap__PreCalcRenderValues+39j
                 push    ecx
                 push    ecx
                 fstp    [esp+14h+var_14]
                 call    _fabs
                 fmul    dword ptr [esi+3Ch]
                 fstp    qword ptr [ebp-8]
                 fld     dword ptr [esi+8]
                 fsub    dword ptr [esi]
                 fstp    [esp+14h+var_14]
                 call    _fabs
                 fmul    dword ptr [esi+38h]
                 mov     eax, [esi+3Ch]
                 pop     ecx
                 pop     ecx
                 mov     [esi+38h], eax
                 fsubr   qword ptr [ebp-8]
                 fmul    ds:__real@8@bffe8000000000000000 ; __real@8@bffe800000000000000
                 fstp    dword ptr [esi+30h]

 loc_436D92:                             ; CODE XREF: MapViewMap__PreCalcRenderValues+75j
                 mov     eax, pinstLocalPlayer ; class EQPlayer * LocalPlaye
				 mov     eax, [eax]
                 fld     dword ptr [esi+8]
                 fsub    dword ptr [eax+4Ch] ; X
                 fstp    dword ptr [esi+28h]
                 mov     eax, pinstLocalPlayer ; class EQPlayer * LocalPlaye
				 mov     eax, [eax]
                 fld     dword ptr [esi+0Ch]
                 fsub    dword ptr [eax+48h] ; Y
                 fstp    dword ptr [esi+2Ch]
                 fld     dword ptr [esi+78h]
                 fmul    dword ptr [esi+28h]
                 fstp    dword ptr [esi+28h]
                 fld     dword ptr [esi+78h]
                 fmul    dword ptr [esi+2Ch]
                 fstp    dword ptr [esi+2Ch]
                 pop     esi
                 leave
                 retn
 MapViewMap__PreCalcRenderValues endp



MapViewMap__TransformPoint proc near    ; CODE XREF: MapViewMap__CalcLabelRenderOffsets+57p
                                         ; MapViewMap__CalcLabelRenderOffsets+12Bp ...

 arg_0           = dword ptr  4

                 mov     edx, [esp+arg_0] ; public: void __thiscall MapViewMap::TransformPoint(struct T3D_XYZ *
                 fld     dword ptr [ecx+8]
                 fadd    dword ptr [edx]
                 fstp    dword ptr [edx]
                 fld     dword ptr [ecx+0Ch]
                 fadd    dword ptr [edx+4]
                 fstp    dword ptr [edx+4]
                 fld     dword ptr [ecx+78h]
                 fcomp   ds:__real@4@3fff8000000000000000 ; 1.0 confirmed
                 fnstsw  ax
                 sahf
                 jz      short loc_436E00
                 fld     dword ptr [ecx+78h]
                 fmul    dword ptr [edx]
                 fst     dword ptr [edx]
                 fsub    dword ptr [ecx+28h]
                 fstp    dword ptr [edx]
                 fld     dword ptr [ecx+78h]
                 fmul    dword ptr [edx+4]
                 fst     dword ptr [edx+4]
                 fsub    dword ptr [ecx+2Ch]
                 fstp    dword ptr [edx+4]

 loc_436E00:                             ; CODE XREF: MapViewMap__TransformPoint+20j
                 fld     dword ptr [ecx+38h]
                 fmul    dword ptr [edx]
                 fstp    dword ptr [edx]
                 fld     dword ptr [ecx+3Ch]
                 fmul    dword ptr [edx+4]
                 fstp    dword ptr [edx+4]
                 fld     dword ptr [ecx+78h]
                 fcomp   ds:__real@4@3fff8000000000000000 ; 1.0 confirmed
                 fnstsw  ax
                 sahf
                 jz      short loc_436E36
                 fld     dword ptr [ecx+10h]
                 fmul    ds:__real@4@3ffe8000000000000000 ; 0.50 confirmed
                 fadd    dword ptr [edx]
                 fstp    dword ptr [edx]
                 fld     dword ptr [ecx+14h]
                 fmul    ds:__real@4@3ffe8000000000000000 ; 0.50 confirmed
                 jmp     short loc_436E40
 ; ---------------------------------------------------------------------------

 loc_436E36:                             ; CODE XREF: MapViewMap__TransformPoint+59j
                 fld     dword ptr [ecx+30h]
                 fadd    dword ptr [edx]
                 fstp    dword ptr [edx]
                 fld     dword ptr [ecx+34h]

 loc_436E40:                             ; CODE XREF: MapViewMap__TransformPoint+71j
                 fadd    dword ptr [edx+4]
                 fstp    dword ptr [edx+4]
                 fild    dword ptr [ecx+20h]
                 fadd    dword ptr [edx]
                 fstp    dword ptr [edx]
                 fild    dword ptr [ecx+24h]
                 fadd    dword ptr [edx+4]
                 fstp    dword ptr [edx+4]
                 retn    4
MapViewMap__TransformPoint endp



MapViewMap__IsLayerVisible proc near    ; CODE XREF: MapViewMap__CalcLabelRenderOffsets+2Ep
                                         ; MapViewMap__CalcLabelRenderOffsets+F5p ...

 arg_0           = dword ptr  4

                 mov     eax, ecx        ; public: bool __thiscall MapViewMap::IsLayerVisible(int
                 mov     ecx, [esp+arg_0]
                 cmp     ecx, 3
                 jle     short loc_436C75
                 xor     al, al
                 jmp     short locret_436C80
 ; ---------------------------------------------------------------------------

 loc_436C75:                             ; CODE XREF: MapViewMap__IsLayerVisible+9j
                 push    1
                 pop     edx
                 shl     edx, cl
                 test    [eax+64h], edx
                 setnz   al

 locret_436C80:                          ; CODE XREF: MapViewMap__IsLayerVisible+Dj
                 retn    4
 MapViewMap__IsLayerVisible endp



CXRect__Normalize proc near             ; CODE XREF: _GetRect+2Ap
                                         ; MapViewMap__CalcLabelRenderOffsets+B7p ...
                 mov     eax, [ecx]      ; public: void __thiscall CXRect::Normalize(void
                 mov     edx, [ecx+8]
                 cmp     eax, edx
                 jle     short loc_438306
                 mov     [ecx], edx
                 mov     [ecx+8], eax

 loc_438306:                             ; CODE XREF: CXRect__Normalize+7j
                 mov     eax, [ecx+4]
                 mov     edx, [ecx+0Ch]
                 cmp     eax, edx
                 jle     short locret_438316
                 mov     [ecx+4], edx
                 mov     [ecx+0Ch], eax

 locret_438316:                          ; CODE XREF: CXRect__Normalize+16j
                 retn
 CXRect__Normalize endp



MapViewMap__Draw proc near              ; CODE XREF: CMapViewWnd__PostDraw+61p

 var_2A0         = qword ptr -2A0h
 var_28C         = byte ptr -28Ch
 var_8C          = dword ptr -8Ch
 var_88          = dword ptr -88h
 var_84          = dword ptr -84h
 var_80          = dword ptr -80h
 var_7C          = dword ptr -7Ch
 var_78          = dword ptr -78h
 var_74          = dword ptr -74h
 var_70          = dword ptr -70h
 var_6C          = dword ptr -6Ch
 var_68          = dword ptr -68h
 var_64          = dword ptr -64h
 var_60          = dword ptr -60h
 var_5C          = dword ptr -5Ch
 var_58          = dword ptr -58h
 var_54          = dword ptr -54h
 var_50          = dword ptr -50h
 var_4C          = dword ptr -4Ch
 var_48          = dword ptr -48h
 var_44          = byte ptr -44h
 var_40          = dword ptr -40h
 var_3C          = dword ptr -3Ch
 var_38          = dword ptr -38h
 var_34          = dword ptr -34h
 var_30          = dword ptr -30h
 var_2C          = dword ptr -2Ch
 var_28          = dword ptr -28h
 var_24          = dword ptr -24h
 var_20          = dword ptr -20h
 var_1C          = dword ptr -1Ch
 var_18          = dword ptr -18h
 var_14          = dword ptr -14h
 var_10          = dword ptr -10h
 var_C           = dword ptr -0Ch
 var_8           = dword ptr -8
 var_1           = byte ptr -1
 arg_0           = dword ptr  8
 arg_4           = dword ptr  0Ch

                 push    ebp             ; public: void __thiscall MapViewMap::Draw(class CXRect
                 mov     ebp, esp
                 sub     esp, 28Ch
                 mov     eax, pinstCXWndManager ; class CXWndManager * g_pwndmg
 				 mov     eax, [eax]
                 and     byte ptr [ebp+var_18], 0
                 or      byte ptr [ebp+var_18+1], 0FFh
                 or      byte ptr [ebp+var_18+2], 0FFh
                 or      byte ptr [ebp+var_18+3], 0FFh
                 cmp     dword ptr [eax+0C8h], 0 ; 4A5954 has this confirmed to exist...
                 push    ebx
                 mov     ebx, ecx
                 push    esi
                 push    edi
                 mov     [ebp+var_C], ebx
                 jle     short loc_436E92
                 mov     ecx, [eax+0C4h] ; confirmed see above
                 test    ecx, ecx
                 jnz     short loc_436E98

 loc_436E92:                             ; CODE XREF: MapViewMap__Draw+2Dj
                 mov     ecx, [eax+0C4h]

 loc_436E98:                             ; CODE XREF: MapViewMap__Draw+37j
                 mov     ecx, [ecx]
                 cmp     dword ptr [eax+0C8h], 1
                 mov     [ebp+var_88], ecx
                 jle     short loc_436EB8
                 mov     ecx, [eax+0C4h]
                 test    ecx, ecx
                 jz      short loc_436EB8
                 add     ecx, 4
                 jmp     short loc_436EBE
 ; ---------------------------------------------------------------------------

 loc_436EB8:                             ; CODE XREF: MapViewMap__Draw+4Ej
                                         ; MapViewMap__Draw+58j
                 mov     ecx, [eax+0C4h]

 loc_436EBE:                             ; CODE XREF: MapViewMap__Draw+5Dj
                 mov     ecx, [ecx]
                 cmp     dword ptr [eax+0C8h], 2
                 mov     [ebp+var_7C], ecx
                 mov     [ebp+var_84], ecx
                 jle     short loc_436EE1
                 mov     ecx, [eax+0C4h]
                 test    ecx, ecx
                 jz      short loc_436EE1
                 lea     eax, [ecx+8]
                 jmp     short loc_436EE7
 ; ---------------------------------------------------------------------------

 loc_436EE1:                             ; CODE XREF: MapViewMap__Draw+77j
                                         ; MapViewMap__Draw+81j
                 mov     eax, [eax+0C4h]

 loc_436EE7:                             ; CODE XREF: MapViewMap__Draw+86j
                 fild    [ebp+arg_4]
                 mov     eax, [eax]
                 mov     [ebp+var_80], eax
                 fadd    dword ptr [ebx+18h]
                 call    __ftol
                 fild    [ebp+arg_0]
                 mov     [ebp+var_50], eax
                 fadd    dword ptr [ebx+1Ch]
                 call    __ftol
                 fild    [ebp+var_50]
                 mov     [ebp+var_54], eax
                 fadd    dword ptr [ebx+14h]
                 call    __ftol
                 fild    [ebp+var_54]
                 mov     [ebp+var_48], eax
                 fadd    dword ptr [ebx+10h]
                 call    __ftol
                 sub     esp, 10h
                 lea     esi, [ebp+var_54]
                 mov     edi, esp
                 mov     [ebp+var_4C], eax
                 movsd
                 movsd
                 movsd
                 lea     eax, [ebp+var_44]
                 lea     ecx, [ebp+arg_0]
                 push    eax
                 movsd
                 call    ??ICXRect@EQClasses@@QBE?AV01@V01@@Z
                 mov     ecx, [eax]
                 mov     [ebp+var_54], ecx
                 mov     ecx, [eax+4]
                 mov     [ebp+var_50], ecx
                 mov     ecx, [eax+8]
                 mov     eax, [eax+0Ch]
                 mov     [ebp+var_4C], ecx
                 mov     [ebp+var_48], eax
                 mov     eax, pinstCXWndManager ; class CXWndManager * g_pwndmg
				 mov     eax, [eax] ; added
                 mov     ecx, [eax+4Ch]
                 mov     eax, [eax+50h]
                 mov     [ebp+var_5C], eax
                 xor     eax, eax
                 cmp     byte_5DF7D8, al
                 mov     [ebp+var_60], ecx
                 mov     [ebp+var_78], eax
                 mov     [ebp+var_74], eax
                 mov     [ebp+var_70], eax
                 mov     [ebp+var_6C], eax
                 jz      short loc_436F9D
                 mov     eax, dword_5DF7A8
                 mov     [ebp+var_78], eax
                 mov     eax, dword_5DF7AC
                 mov     [ebp+var_74], eax
                 mov     eax, ecx
                 mov     [ebp+var_70], eax
                 mov     eax, [ebp+var_5C]
                 lea     ecx, [ebp+var_78]
                 mov     [ebp+var_6C], eax
                 call    CXRect__Normalize

 loc_436F9D:                             ; CODE XREF: MapViewMap__Draw+11Fj
                 mov     ecx, ebx
                 call    MapViewMap__PreCalcRenderValues
                 and     dword_5DF7D0, 0
                 and     _CurrentMapLabel, 0
                 mov     esi, [ebx+40h]
                 test    esi, esi
                 jz      loc_437279 ; from this point on there is a bug:
                 mov     [ebp+var_14], esi

 loc_436FC0:                             ; CODE XREF: MapViewMap__Draw+418j
                 push    dword ptr [esi+24h]
                 mov     ecx, ebx
                 call    MapViewMap__IsLayerVisible
                 test    al, al
                 jz      loc_437264
                 and     [ebp+var_1], 0
                 cmp     byte ptr [ebx+74h], 1
                 jnz     short loc_43702B ; if this jumps, our mouse will vanish... why?
                 mov     edx, pinstLocalPlayer ; class EQPlayer * LocalPlaye
				 mov     edx, [edx]
                 ;fld     dword ptr [edx+12Ch]
                 fld     dword ptr [edx+0F0h] ; changed i think this is height
                 fmul    ds:__real@4@3ffea000000000000000 ; __real@4@3ffea00000000000000
                 ;fsubr   dword ptr [edx+5Ch]
				 fsubr   dword ptr [edx+50h] ; changed to Z
                 fild    dword ptr [ebx+6Ch]
                 fsubr   st, st(1)
                 fcom    dword ptr [esi+10h]
                 fnstsw  ax
                 sahf
                 jbe     short loc_43700A
                 fcomp   dword ptr [esi+1Ch]
                 fnstsw  ax
                 sahf
                 jbe     short loc_43700C
                 fstp    st
                 jmp     short loc_43701F
 ; ---------------------------------------------------------------------------

 loc_43700A:                             ; CODE XREF: MapViewMap__Draw+1A3j
                 fstp    st

 loc_43700C:                             ; CODE XREF: MapViewMap__Draw+1ABj
                 fiadd   dword ptr [ebx+70h] ; I think this is SpeedHeading
                 ;fiadd   dword ptr [ebx+6Ch] ; nope its ebx the mapwindow
                 fcom    dword ptr [esi+10h]
                 fnstsw  ax
                 sahf
                 jnb     short loc_437029
                 fcomp   dword ptr [esi+1Ch]
                 fnstsw  ax
                 sahf
                 jnb     short loc_43702B

 loc_43701F:                             ; CODE XREF: MapViewMap__Draw+1AFj
                 mov     esi, [esi]
                 mov     [ebp+var_14], esi
                 jmp     loc_43726F
 ; ---------------------------------------------------------------------------

 loc_437029:                             ; CODE XREF: MapViewMap__Draw+1BCj
                 fstp    st

 loc_43702B:                             ; CODE XREF: MapViewMap__Draw+181j
                                         ; MapViewMap__Draw+1C4j
                 mov     eax, [ebp+var_14]
                 lea     edi, [ebp+var_30]
                 mov     ecx, ebx
                 lea     esi, [eax+8]
                 movsd
                 movsd
                 movsd
                 lea     esi, [eax+14h]
                 lea     edi, [ebp+var_24]
                 movsd
                 movsd
                 lea     eax, [ebp+var_30]
                 push    eax
                 movsd
                 call    MapViewMap__TransformPoint
                 lea     eax, [ebp+var_24]
                 mov     ecx, ebx
                 push    eax
                 call    MapViewMap__TransformPoint
                 fild    [ebp+var_54]
                 mov     eax, [ebp+var_54]
                 cmp     [ebp+var_60], eax
                 fld     st
                 fadd    [ebp+var_30]
                 fstp    [ebp+var_30]
                 fild    [ebp+var_50]
                 fst     [ebp+var_34]
                 fadd    [ebp+var_2C]
                 fstp    [ebp+var_2C]
                 fadd    [ebp+var_24]
                 fstp    [ebp+var_24]
                 fld     [ebp+var_34]
                 fadd    [ebp+var_20]
                 fstp    [ebp+var_20]
                 fld1
                 fstp    [ebp+var_28]
                 fld1
                 fstp    [ebp+var_1C]
                 jl      loc_437180
                 mov     eax, [ebp+var_4C]
                 cmp     [ebp+var_60], eax
                 jge     loc_437180
                 mov     eax, [ebp+var_5C]
                 cmp     eax, [ebp+var_50]
                 jl      loc_437180
                 cmp     eax, [ebp+var_48]
                 jge     loc_437180
                 mov     eax, _g_pMapToolbarWnd ; class CMapToolbarWnd * g_pMapToolbarWn
                 test    eax, eax
                 jz		 loc_437180
                 cmp     byte ptr [eax+170h], 0
                 jz      loc_437180
                 fld     [ebp+var_24]
                 fsub    [ebp+var_30]
                 fstp    [ebp+var_34]
                 fld     [ebp+var_20]
                 fsub    [ebp+var_2C]
                 fstp    [ebp+var_58]
                 fild    [ebp+var_60]
                 fst     [ebp+var_68]
                 fsub    [ebp+var_30]
                 fild    [ebp+var_5C]
                 fst     [ebp+var_64]
                 fsub    [ebp+var_2C]
                 fld     st
                 fmul    [ebp+var_58]
                 fld     st(2)
                 fmul    [ebp+var_34]
                 faddp   st(1), st
                 fst     [ebp+var_10]
                 fcomp   ds:__real@4@00000000000000000000 ; __real@4@0000000000000000000
                 fnstsw  ax
                 sahf
                 jbe     short loc_43714F
                 fstp    st
                 fstp    st
                 fld     [ebp+var_58]
                 fmul    [ebp+var_58]
                 fld     [ebp+var_34]
                 fmul    [ebp+var_34]
                 faddp   st(1), st
                 fcom    [ebp+var_10]
                 fnstsw  ax
                 sahf
                 ja      short loc_43712D
                 fstp    st
                 fld     [ebp+var_68]
                 fsub    [ebp+var_24]
                 fld     [ebp+var_64]
                 fsub    [ebp+var_20]
                 jmp     short loc_43714F
 ; ---------------------------------------------------------------------------

 loc_43712D:                             ; CODE XREF: MapViewMap__Draw+2C2j
                 fld     [ebp+var_10]
                 fdiv    st, st(1)
                 fstp    [ebp+var_10]
                 fstp    st
                 fld     [ebp+var_10]
                 fmul    [ebp+var_34]
                 fadd    [ebp+var_30]
                 fsubr   [ebp+var_68]
                 fld     [ebp+var_10]
                 fmul    [ebp+var_58]
                 fadd    [ebp+var_2C]
                 fsubr   [ebp+var_64]

 loc_43714F:                             ; CODE XREF: MapViewMap__Draw+2A8j
                                         ; MapViewMap__Draw+2D2j
                 fld     st
                 fmul    st, st(1)
                 fld     st(2)
                 fmul    st, st(3)
                 push    ecx
                 push    ecx
                 faddp   st(1), st
                 fstp    [esp+2A0h+var_2A0]
                 fstp    st
                 fstp    st
                 call    _sqrt
                 fcomp   ds:__real@4@4000c000000000000000 ; __real@4@4000c00000000000000
                 pop     ecx
                 pop     ecx
                 fnstsw  ax
                 sahf
                 jnb     short loc_437180
                 mov     eax, [ebp+var_14]
                 mov     [ebp+var_1], 1
                 mov     dword_5DF7D0, eax

 loc_437180:                             ; CODE XREF: MapViewMap__Draw+233j
                                         ; MapViewMap__Draw+23Fj ...
                 mov     eax, [ebx+5Ch]
                 test    eax, eax
                 jz      short loc_4371AA
                 mov     ecx, _g_pMapToolbarWnd ; class CMapToolbarWnd * g_pMapToolbarWn
                 test ecx,ecx ; added
				 jz      short loc_4371AA ; added
				 cmp     byte ptr [ecx+170h], 0
                 jz      short loc_4371AA

 loc_437196:                             ; CODE XREF: MapViewMap__Draw+34Bj
                 test    eax, eax
                 jz      short loc_4371AA
                 mov     ecx, [eax+4]
                 cmp     ecx, [ebp+var_14]
                 jz      short loc_4371A6
                 mov     eax, [eax]
                 jmp     short loc_437196
 ; ---------------------------------------------------------------------------

 loc_4371A6:                             ; CODE XREF: MapViewMap__Draw+347j
                 mov     [ebp+var_1], 1

 loc_4371AA:                             ; CODE XREF: MapViewMap__Draw+32Cj
                                         ; MapViewMap__Draw+33Bj ...
                 cmp     byte_5DF7D8, 0
                 jz      loc_43722A
                 mov     eax, _g_pMapToolbarWnd ; class CMapToolbarWnd * g_pMapToolbarWn
				 test eax,eax ; added
				 jz      short loc_43722A ; added
                 cmp     byte ptr [eax+170h], 0
                 jz      short loc_43722A
                 fld     [ebp+var_2C]
                 call    __ftol
                 fld     [ebp+var_30]
                 mov     edi, eax
                 call    __ftol
                 fld     [ebp+var_20]
                 mov     esi, eax
                 call    __ftol
                 fld     [ebp+var_24]
                 mov     [ebp+var_10], eax
                 call    __ftol
                 cmp     esi, [ebp+var_78]
                 jl      short loc_43722A
                 cmp     esi, [ebp+var_70]
                 jge     short loc_43722A
                 cmp     edi, [ebp+var_74]
                 jl      short loc_43722A
                 cmp     edi, [ebp+var_6C]
                 jge     short loc_43722A
                 cmp     eax, [ebp+var_78]
                 jl      short loc_43722A
                 cmp     eax, [ebp+var_70]
                 jge     short loc_43722A
                 mov     eax, [ebp+var_10]
                 cmp     eax, [ebp+var_74]
                 jl      short loc_43722A
                 cmp     eax, [ebp+var_6C]
                 jge     short loc_43722A
                 cmp     byte_5DF7D9, 0
                 mov     [ebp+var_1], 1
                 jz      short loc_437230
                 push    [ebp+var_14]
                 mov     ecx, ebx
                 call    _MapViewMap_SetMarkedLine

 loc_43722A:     cmp     [ebp+var_1], 0
                 jz      short loc_437241

 loc_437230:                             ; CODE XREF: MapViewMap__Draw+3C5j
                 sub     esp, 10h
                 lea     esi, [ebp+var_54]
                 mov     edi, esp
                 movsd
                 movsd
                 push    [ebp+var_18]
                 movsd
                 movsd
                 jmp     short loc_437253
 ; ---------------------------------------------------------------------------

 loc_437241:                             ; CODE XREF: MapViewMap__Draw+3D5j
                 sub     esp, 10h
                 lea     esi, [ebp+var_54]
                 mov     edi, esp
                 mov     eax, [ebp+var_14]
                 movsd
                 movsd
                 push    dword ptr [eax+20h]
                 movsd
                 movsd

 loc_437253:                             ; CODE XREF: MapViewMap__Draw+3E6j
                 lea     eax, [ebp+var_30]
                 mov     ecx, ebx
                 push    eax
                 call    MapViewMap__DrawClippedLine ; comment this one out and there is no hidden mouse on zoom
                 mov     esi, [ebp+var_14]
                 mov     [ebp+var_1], al

 loc_437264:                             ; CODE XREF: MapViewMap__Draw+173j
                 mov     esi, [esi]
                 mov     edx, pinstLocalPlayer ; class EQPlayer * LocalPlaye
				 mov     edx, [edx]
                 mov     [ebp+var_14], esi

 loc_43726F:                             ; CODE XREF: MapViewMap__Draw+1CBj
                 test    esi, esi
                 jnz     loc_436FC0
                 jmp     short loc_43727F
 ; ---------------------------------------------------------------------------

 loc_437279:                             ; CODE XREF: MapViewMap__Draw+15Ej
                 mov     edx, pinstLocalPlayer ; class EQPlayer * LocalPlaye
				 mov     edx, [edx]

 loc_43727F:                             ; CODE XREF: MapViewMap__Draw+41Ej
                 cmp     byte ptr [ebx+48h], 0
                 jz      loc_43730B
                 mov     eax, [ebx+4Ch]
                 mov     ecx, ebx
                 mov     [ebp+var_30], eax
                 mov     eax, [ebx+50h]
                 mov     [ebp+var_2C], eax
                 lea     eax, [ebp+var_30]
                 fld     dword ptr [edx+4Ch] ; X
                 fchs
                 fstp    [ebp+var_24]
                 fld     dword ptr [edx+48h] ; Y
                 fchs
                 fstp    [ebp+var_20]
                 push    eax
                 call    MapViewMap__TransformPoint
                 lea     eax, [ebp+var_24]
                 mov     ecx, ebx
                 push    eax
                 call    MapViewMap__TransformPoint
                 fild    [ebp+var_54]
                 sub     esp, 10h
                 lea     esi, [ebp+var_54]
                 mov     edi, esp
                 push    dword ptr [ebx+58h]
                 fld     st
                 fadd    [ebp+var_30]
                 movsd
                 fstp    [ebp+var_30]
                 fild    [ebp+var_50]
                 movsd
                 fst     [ebp+var_34]
                 fadd    [ebp+var_2C]
                 movsd
                 fstp    [ebp+var_2C]
                 lea     eax, [ebp+var_30]
                 mov     ecx, ebx
                 fadd    [ebp+var_24]
                 push    eax
                 movsd
                 fstp    [ebp+var_24]
                 fld     [ebp+var_34]
                 fadd    [ebp+var_20]
                 fstp    [ebp+var_20]
                 fld1
                 fstp    [ebp+var_28]
                 fld1
                 fstp    [ebp+var_1C]
                 call    MapViewMap__DrawClippedLine
                 mov     edx, pinstLocalPlayer ; class EQPlayer * LocalPlaye
				 mov     edx, [edx]

 loc_43730B:                             ; CODE XREF: MapViewMap__Draw+42Aj
                 cmp     dword ptr [ebx+44h], 0
                 jz      loc_4376EC ; we probably dont want this to jump
                 mov     ebx, [ebp+var_C]
                 cmp     byte ptr [ebx+81h], 1
                 jnz     short loc_437341
                 sub     esp, 10h
                 lea     esi, [ebp+var_54]
                 mov     edi, esp
                 mov     ecx, ebx
                 movsd
                 movsd
                 movsd
                 movsd
                 call    MapViewMap__CalcLabelRenderOffsets
                 and     byte ptr [ebx+81h], 0
                 mov     edx, pinstLocalPlayer ; class EQPlayer * LocalPlaye
				 mov     edx, [edx]

 loc_437341:                             ; CODE XREF: MapViewMap__Draw+4C6j
                 mov     ecx, [ebp+var_C]
                 mov     ebx, [ecx+44h]

 loc_437347:                             ; CODE XREF: MapViewMap__Draw+539j
                                         ; MapViewMap__Draw+88Ej
                 test    ebx, ebx
                 jz      loc_4376EC
                 push    dword ptr [ebx+20h]
                 call    MapViewMap__IsLayerVisible
                 test    al, al
                 jz      loc_4376DC
                 mov     ecx, [ebp+var_C]
                 and     [ebp+var_1], 0
                 cmp     byte ptr [ecx+74h], 1
                 jnz     short loc_4373A5 ; we probably dont want this to jump cause mouse will be gone...
                 mov     edx, pinstLocalPlayer ; class EQPlayer * LocalPlaye
				 mov     edx, [edx]
                 fld     dword ptr [edx+0F0h] ; changed i think this is height
                 fmul    ds:__real@4@3ffea000000000000000 ; __real@4@3ffea00000000000000
                 fsubr   dword ptr [edx+50h] ; Z
                 fild    dword ptr [ecx+6Ch]
                 fsubr   st, st(1)
                 fcomp   dword ptr [ebx+10h]
                 fnstsw  ax
                 sahf
                 jbe     short loc_437394
                 fstp    st

 loc_437390:                             ; CODE XREF: MapViewMap__Draw+54Aj
                 mov     ebx, [ebx]
                 jmp     short loc_437347
 ; ---------------------------------------------------------------------------

 loc_437394:                             ; CODE XREF: MapViewMap__Draw+533j
                 fild    dword ptr [ecx+70h]
                 fadd    st, st(1)
                 fld     dword ptr [ebx+10h]
                 fcompp
                 fnstsw  ax
                 sahf
                 fstp    st
                 ja      short loc_437390

 loc_4373A5:                             ; CODE XREF: MapViewMap__Draw+511j
                 lea     esi, [ebx+8]
                 lea     edi, [ebp+var_40]
                 movsd
                 mov     ecx, [ebp+var_C]
                 lea     eax, [ebp+var_40]
                 movsd
                 push    eax
                 movsd
                 call    MapViewMap__TransformPoint
                 fild    [ebp+var_54]
                 mov     eax, [ebp+var_54]
                 cmp     [ebp+var_60], eax
                 fadd    [ebp+var_40]
                 fstp    [ebp+var_40]
                 fild    [ebp+var_50]
                 fadd    [ebp+var_3C]
                 fstp    [ebp+var_3C]
                 fld1
                 fstp    [ebp+var_38]
                 jl      short loc_437429
                 mov     eax, [ebp+var_4C]
                 cmp     [ebp+var_60], eax
                 jge     short loc_437429
                 mov     eax, [ebp+var_5C]
                 cmp     eax, [ebp+var_50]
                 jl      short loc_437429
                 cmp     eax, [ebp+var_48]
                 jge     short loc_437429
                 fild    [ebp+var_60]
                 push    ecx
                 push    ecx
                 fsub    [ebp+var_40]
                 fild    [ebp+var_5C]
                 fsub    [ebp+var_3C]
                 fld     st
                 fmul    st, st(1)
                 fld     st(2)
                 fmul    st, st(3)
                 faddp   st(1), st
                 fstp    [esp+2A0h+var_2A0]
                 fstp    st
                 fstp    st
                 call    _sqrt
                 fcomp   ds:__real@4@4000c000000000000000 ; __real@4@4000c00000000000000 its checked as 3.0
                 pop     ecx
                 pop     ecx
                 fnstsw  ax
                 sahf
                 jnb     short loc_437429
                 mov     [ebp+var_1], 1
                 mov     _CurrentMapLabel, ebx

 loc_437429:                             ; CODE XREF: MapViewMap__Draw+57Ej
                                         ; MapViewMap__Draw+586j ...
                 mov     eax, [ebp+var_C]
                 cmp     [eax+60h], ebx
                 jnz     short loc_437435
                 mov     [ebp+var_1], 1

 loc_437435:                             ; CODE XREF: MapViewMap__Draw+5D6j
                 fld     [ebp+var_40]
                 fsub    ds:__real@4@3fff8000000000000000 ; __real@4@3fff800000000000000 1.0 confirmed
                 mov     eax, [ebp-3Ch]
                 cmp     byte ptr [ebp-1], 0
                 mov     [ebp-2Ch], eax
                 mov     [ebp-20h], eax
                 fstp    dword ptr [ebp-30h]
                 fld1
                 fstp    dword ptr [ebp-28h]
                 fld     dword ptr [ebp-40h]
                 fadd    ds:__real@4@40008000000000000000 ; __real@4@4000800000000000000 2.0 confirmed
                 fstp    dword ptr [ebp-24h]
                 fld1
                 fstp    dword ptr [ebp-1Ch]
                 jz      short loc_437477
                 sub     esp, 10h
                 lea     esi, [ebp-54h]
                 mov     edi, esp
                 movsd
                 movsd
                 push    dword ptr [ebp-18h]
                 movsd
                 movsd
                 jmp     short loc_437486
 ; ---------------------------------------------------------------------------

 loc_437477:                             ; CODE XREF: MapViewMap__Draw+60Bj
                 sub     esp, 10h
                 lea     esi, [ebp+var_54]
                 mov     edi, esp
                 push    dword ptr [ebx+14h]
                 movsd
                 movsd
                 movsd
                 movsd

 loc_437486:                             ; CODE XREF: MapViewMap__Draw+61Cj
                 mov     ecx, [ebp+var_C]
                 lea     eax, [ebp+var_30]
                 push    eax
                 call    MapViewMap__DrawClippedLine
                 fld     [ebp+var_40]
                 cmp     [ebp+var_1], 0
                 fst     [ebp+var_30]
                 fld     [ebp+var_3C]
                 fsub    ds:__real@4@3fff8000000000000000 ; __real@4@3fff800000000000000
                 fstp    [ebp+var_2C]
                 fld1
                 fstp    [ebp+var_28]
                 fstp    [ebp+var_24]
                 fld     [ebp+var_3C]
                 fadd    ds:__real@4@40008000000000000000 ; __real@4@4000800000000000000
                 fstp    [ebp+var_20]
                 fld1
                 fstp    [ebp+var_1C]
                 jz      short loc_4374D4
                 sub     esp, 10h
                 lea     esi, [ebp+var_54]
                 mov     edi, esp
                 movsd
                 movsd
                 push    [ebp+var_18]
                 movsd
                 movsd
                 jmp     short loc_4374E3
 ; ---------------------------------------------------------------------------

 loc_4374D4:                             ; CODE XREF: MapViewMap__Draw+668j
                 sub     esp, 10h
                 lea     esi, [ebp+var_54]
                 mov     edi, esp
                 push    dword ptr [ebx+14h]
                 movsd
                 movsd
                 movsd
                 movsd

 loc_4374E3:                             ; CODE XREF: MapViewMap__Draw+679j
                 mov     ecx, [ebp+var_C]
                 lea     eax, [ebp+var_30]
                 push    eax
                 call    MapViewMap__DrawClippedLine
                 mov     eax, [ebp+var_C]
                 cmp     byte ptr [eax+80h], 0
                 jz      loc_4375DD
                 mov     eax, [ebp+var_40]
                 mov     [ebp+var_30], eax
                 mov     eax, [ebp+var_3C]
                 fld1
                 mov     [ebp+var_2C], eax
                 fstp    [ebp+var_28]
                 push    dword ptr [ebx+2Ch]
                 call    _abs
                 cmp     eax, 4
                 pop     ecx
                 jle     short loc_437567
                 push    dword ptr [ebx+2Ch]
                 call    _abs
                 cmp     eax, [ebx+24h]
                 pop     ecx
                 jle     short loc_437548
                 fld     [ebp+var_40]
                 fsub    ds:__real@4@40018000000000000000 ; __real@4@4001800000000000000
                 fstp    [ebp+var_24]
                 mov     eax, [ebx+28h]
                 cdq
                 sub     eax, edx
                 sar     eax, 1
                 mov     [ebp+var_10], eax
                 fild    [ebp+var_10]
                 jmp     short loc_437581
 ; ---------------------------------------------------------------------------

 loc_437548:                             ; CODE XREF: MapViewMap__Draw+6D1j
                 mov     eax, [ebp+var_40]
                 fld     [ebp+var_3C]
                 mov     [ebp+var_24], eax
                 cmp     dword ptr [ebx+30h], 0
                 jle     short loc_43755F
                 fadd    ds:__real@4@4001a000000000000000
                 jmp     short loc_437587
 ; ---------------------------------------------------------------------------

 loc_43755F:                             ; CODE XREF: MapViewMap__Draw+6FCj
                 fsub    ds:__real@4@4001a000000000000000
                 jmp     short loc_437587
 ; ---------------------------------------------------------------------------

 loc_437567:                             ; CODE XREF: MapViewMap__Draw+6C3j
                 fld     [ebp+var_40]
                 fadd    ds:__real@4@40018000000000000000
                 fstp    [ebp+var_24]
                 mov     eax, [ebx+28h]
                 cdq
                 sub     eax, edx
                 sar     eax, 1
                 mov     [ebp+var_10], eax
                 fild    [ebp+var_10]

 loc_437581:                             ; CODE XREF: MapViewMap__Draw+6EDj
                 fiadd   dword ptr [ebx+30h]
                 fadd    [ebp+var_3C]

 loc_437587:                             ; CODE XREF: MapViewMap__Draw+704j
                                         ; MapViewMap__Draw+70Cj
                 fstp    [ebp+var_20]
                 cmp     [ebp+var_1], 0
                 fld1
                 fstp    [ebp+var_1C]
                 jz      short loc_4375BA
                 sub     esp, 10h
                 lea     esi, [ebp+var_54]
                 mov     edi, esp
                 mov     ecx, [ebp+var_C]
                 movsd
                 movsd
                 mov     byte ptr [ebp+var_18+3], 9Fh
                 push    [ebp+var_18]
                 movsd
                 lea     eax, [ebp+var_30]
                 push    eax
                 movsd
                 call    MapViewMap__DrawClippedLine
                 or      byte ptr [ebp+var_18+3], 0FFh
                 jmp     short loc_4375DD
 ; ---------------------------------------------------------------------------

 loc_4375BA:                             ; CODE XREF: MapViewMap__Draw+73Aj
                 sub     esp, 10h
                 lea     esi, [ebp+var_54]
                 mov     edi, esp
                 mov     ecx, [ebp+var_C]
                 movsd
                 movsd
                 mov     byte ptr [ebx+17h], 9Fh
                 push    dword ptr [ebx+14h]
                 movsd
                 lea     eax, [ebp+var_30]
                 push    eax
                 movsd
                 call    MapViewMap__DrawClippedLine
                 or      byte ptr [ebx+17h], 0FFh

 loc_4375DD:                             ; CODE XREF: MapViewMap__Draw+6A0j
                                         ; MapViewMap__Draw+75Fj
                 cmp     [ebp+var_1], 0
                 jz      loc_437683
                 mov     eax, [ebx+2Ch]
                 test    eax, eax
                 mov     [ebp+var_10], eax
                 jnz     short loc_4375F6
                 cmp     [ebx+30h], eax
                 jz      short loc_437602

 loc_4375F6:                             ; CODE XREF: MapViewMap__Draw+796j
                 mov     eax, [ebp+var_C]
                 cmp     byte ptr [eax+80h], 0
                 jnz     short loc_43764B

 loc_437602:                             ; CODE XREF: MapViewMap__Draw+79Bj
                 push    0
                 push    0
                 push    [ebp+var_18]
                 lea     esi, [ebp+var_54]
                 fild    dword ptr [ebx+28h]
                 sub     esp, 10h
                 mov     edi, esp
                 movsd
                 fsubr   [ebp+var_3C]
                 fsub    ds:__real@4@40008000000000000000 ; __real@4@4000800000000000000
                 movsd
                 movsd
                 movsd
                 push    12Ch
                 call    __ftol
                 push    eax
                 mov     eax, [ebx+24h]
                 cdq
                 sub     eax, edx
                 sar     eax, 1
                 mov     [ebp+var_10], eax
                 fild    [ebp+var_10]
                 fsubr   [ebp+var_40]
                 call    __ftol
                 push    eax
                 push    ecx
                 mov     ecx, esp
                 mov     [ebp+var_8], esp
                 jmp     loc_4376C5
  loc_43764B:                             ; CODE XREF: MapViewMap__Draw+7A7j
                 push    0
                 push    0
                 push    [ebp+var_18]
                 lea     esi, [ebp+var_54]
                 fild    dword ptr [ebx+30h]
                 sub     esp, 10h
                 mov     edi, esp
                 movsd
                 fadd    [ebp+var_3C]
                 movsd
                 movsd
                 movsd
                 push    12Ch
                 call    __ftol
                 fild    [ebp+var_10]
                 push    eax
                 fadd    [ebp+var_40]
                 call    __ftol
                 push    eax
                 push    ecx
                 mov     ecx, esp
                 mov     [ebp+var_8], esp
                 jmp     short loc_4376C5
 ; ---------------------------------------------------------------------------

 loc_437683:                             ; CODE XREF: MapViewMap__Draw+788j
                 mov     eax, [ebp+var_C]
                 cmp     byte ptr [eax+80h], 0
                 jz      short loc_4376DC
                 push    0
                 push    0
                 push    dword ptr [ebx+14h]
                 lea     esi, [ebp+var_54]
                 fild    dword ptr [ebx+30h]
                 sub     esp, 10h
                 mov     edi, esp
                 movsd
                 fadd    [ebp+var_3C]
                 movsd
                 movsd
                 movsd
                 push    12Ch
                 call    __ftol
                 fild    dword ptr [ebx+2Ch]
                 push    eax
                 fadd    [ebp+var_40]
                 call    __ftol
                 push    eax
                 push    ecx
                 mov     ecx, esp
                 mov     [ebp+var_8], esp

 loc_4376C5:                             ; CODE XREF: MapViewMap__Draw+7F0j
                                         ; MapViewMap__Draw+828j
                 push    dword ptr [ebx+1Ch]
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     eax, [ebx+18h]
                 mov     ecx, [ebp+eax*4+var_8C]
                 call    ?DrawWrappedText@CTextureFont@EQClasses@@QBEHVCXStr@2@HHHVCXRect@2@KGH@Z ; CTextureFont__DrawWrappedText

 loc_4376DC:                             ; CODE XREF: MapViewMap__Draw+500j
                                         ; MapViewMap__Draw+834j
                 mov     ebx, [ebx]
                 mov     edx, pinstLocalPlayer ; class EQPlayer * LocalPlaye
				 mov     edx, [edx]
                 mov     ecx, [ebp+var_C]
                 jmp     loc_437347
 ; ---------------------------------------------------------------------------

 loc_4376EC:                             ; CODE XREF: MapViewMap__Draw+4B6j
                                         ; MapViewMap__Draw+4F0j
                 test    edx, edx
                 jz      loc_4379C5
				 ;mov	 eax,pinstCharData ; added by me
				 ;mov	 eax,[eax] ; added by me
                 cmp     pinstCharData, 0
                 ;cmp	 eax,0
				 jz      loc_4379C5
                 fld     dword ptr [edx+4Ch] ; X
                 fchs
                 fstp    [ebp+var_40]
                 fld     dword ptr [edx+48h] ; Y
                 mov     ecx, [ebp+var_C]
                 or      byte ptr [ebp+var_14+3], 0FFh
                 and     byte ptr [ebp+var_14+2], 0
                 and     byte ptr [ebp+var_14+1], 0
                 and     byte ptr [ebp+var_14], 0
                 lea     eax, [ebp+var_40]
                 fchs
                 fstp    [ebp+var_3C]
                 fld1
                 push    eax
                 fstp    [ebp+var_38]
                 call    MapViewMap__TransformPoint
                 fild    [ebp+var_54]
                 mov     eax, pinstCharData
				 mov     eax, [eax]
                 fadd    [ebp+var_40]
                 fstp    [ebp+var_40]
                 fild    [ebp+var_50]
                 fadd    [ebp+var_3C]
                 fstp    [ebp+var_3C]
                 fld     [ebp+var_38]
                 fst     [ebp+var_28]
                 fstp    [ebp+var_1C]
                 ;cmp     dword ptr [eax+0BF8h], 0BEh ; compare sense heading to 190 (changed)
                 ;cmp     word ptr [eax+0BF8h], 0h ; lets bypass it...
                 ;jle     loc_43790B
                 mov     eax, pinstLocalPlayer
				 mov     eax, [eax]
                 push    ecx
                 fld     dword ptr [eax+54h] ; Heading
                 fstp    dword ptr [esp+29Ch+var_2A0+4]
                 call	 dword ptr [ds:__imp__t3dFloatFastCosine]
                 fmul    ds:__real@4@40018000000000000000
                 mov     eax, pinstLocalPlayer
				 mov     eax, [eax]
                 fstp    [ebp+var_34]
                 fld     dword ptr [eax+54h] ; Heading
                 fstp    dword ptr [esp+29Ch+var_2A0+4]
                 mov eax, __imp__t3dFloatFastSine
                 mov eax, [eax] ; added
				 call eax
                 fmul    ds:__real@4@40018000000000000000
                 mov     eax, pinstLocalPlayer
				 mov     eax, [eax]
                 fstp    [ebp+var_58]
                 fld     dword ptr [eax+54h] ; Heading
                 fadd    ds:__real@4@4004c000000000000000
                 fstp    dword ptr [esp+29Ch+var_2A0+4]
                 call dword ptr [ds:__imp__t3dFloatFastCosine]
                 fmul    ds:__real@4@4001c000000000000000
                 mov     eax, pinstLocalPlayer
				 mov     eax, [eax]
                 fstp    [ebp+var_68]
                 fld     dword ptr [eax+54h] ; Heading
                 fadd    ds:__real@4@4004c000000000000000
                 fstp    dword ptr [esp+29Ch+var_2A0+4]
				 call dword ptr [ds:__imp__t3dFloatFastSine]
                 fmul    ds:__real@4@4001c000000000000000
                 mov     eax, pinstLocalPlayer
				 mov     eax, [eax]
                 fstp    [ebp+var_64]
                 fld     dword ptr [eax+54h] ; Heading
                 fadd    ds:__real@4@4007e800000000000000
                 fstp    dword ptr [esp+29Ch+var_2A0+4]
                 call dword ptr [ds:__imp__t3dFloatFastCosine]
                 fmul    ds:__real@4@4001c000000000000000
                 mov     eax, pinstLocalPlayer
				 mov     eax, [eax]
                 fstp    [ebp+var_8]
                 fld     dword ptr [eax+54h] ; Heading
                 fadd    ds:__real@4@4007e800000000000000
                 fstp    dword ptr [esp+29Ch+var_2A0+4]
				 call dword ptr [ds:__imp__t3dFloatFastSine]
                 fmul    ds:__real@4@4001c000000000000000
                 fstp    [ebp+var_5C]
                 fld     [ebp+var_40]
                 call    __ftol
                 mov     [ebp+var_10], eax
                 fild    [ebp+var_10]
                 fld     st
                 fadd    [ebp+var_64]
                 fstp    [ebp+var_30]
                 fld     [ebp+var_3C]
                 call    __ftol
                 mov     [ebp+var_10], eax
                 sub     esp, 0Ch
                 fild    [ebp+var_10]
                 lea     esi, [ebp+var_54]
                 mov     edi, esp
                 movsd
                 fst     [ebp+var_18]
                 fadd    [ebp+var_68]
                 push    [ebp+var_14]
                 mov     ecx, [ebp+var_C]
                 movsd
                 fstp    [ebp+var_2C]
                 fsub    [ebp+var_58]
                 movsd
                 fstp    [ebp+var_24]
                 fld     [ebp+var_18]
                 fsub    [ebp+var_34]
                 lea     eax, [ebp+var_30]
                 push    eax
                 movsd
                 fstp    [ebp+var_20]
                 call    MapViewMap__DrawClippedLine
                 fld     [ebp+var_40]
                 call    __ftol
                 mov     [ebp+var_10], eax
                 fild    [ebp+var_10]
                 fld     st
                 fadd    [ebp+var_5C]
                 fstp    [ebp+var_30]
                 fld     [ebp+var_3C]
                 call    __ftol
                 mov     [ebp+var_5C], eax
                 sub     esp, 10h
                 fild    [ebp+var_5C]
                 lea     esi, [ebp+var_54]
                 mov     edi, esp
                 movsd
                 fst     [ebp+var_18]
                 fadd    [ebp+var_8]
                 push    [ebp+var_14]
                 mov     ecx, [ebp+var_C]
                 movsd
                 fstp    [ebp+var_2C]
                 fsub    [ebp+var_58]
                 movsd
                 fstp    [ebp+var_24]
                 fld     [ebp+var_18]
                 fsub    [ebp+var_34]
                 lea     eax, [ebp+var_30]
                 push    eax
                 movsd
                 fstp    [ebp+var_20]
                 call    MapViewMap__DrawClippedLine
                 fld     [ebp+var_40]
                 call    __ftol
                 mov     [ebp+var_8], eax
                 fild    [ebp+var_8]
                 fld     [ebp+var_58]
                 fadd    st, st
                 fadd    st, st(1)
                 fstp    [ebp+var_30]
                 fld     [ebp+var_3C]
                 call    __ftol
                 mov     [ebp+var_8], eax
                 fild    [ebp+var_8]
                 fst     [ebp+var_18]
                 fld     [ebp+var_34]
                 fadd    st, st
                 fadd    st, st(1)
                 fstp    [ebp+var_2C]
                 fstp    st
                 fsub    [ebp+var_58]
                 fstp    [ebp+var_24]
                 fld     [ebp+var_18]
                 fsub    [ebp+var_34]
                 jmp     loc_4379A7
 ; ---------------------------------------------------------------------------

 loc_43790B:                             ; CODE XREF: MapViewMap__Draw+903j
                 fld     [ebp+var_40]
                 fsub    ds:__real@4@40008000000000000000 ; __real@4@4000800000000000000
                 call    __ftol
                 mov     [ebp+var_8], eax
                 fild    [ebp+var_8]
                 fstp    [ebp+var_30]
                 fld     [ebp+var_3C]
                 call    __ftol
                 mov     [ebp+var_8], eax
                 fild    [ebp+var_8]
                 fst     [ebp+var_2C]
                 fld     [ebp+var_40]
                 fadd    ds:__real@4@4000c000000000000000 ; __real@4@4000c00000000000000
                 call    __ftol
                 sub     esp, 10h
                 lea     esi, [ebp+var_54]
                 mov     edi, esp
                 mov     [ebp+var_8], eax
                 fild    [ebp+var_8]
                 movsd
                 fstp    [ebp+var_24]
                 push    [ebp+var_14]
                 mov     ecx, [ebp+var_C]
                 movsd
                 fstp    [ebp+var_20]
                 movsd
                 lea     eax, [ebp+var_30]
                 push    eax
                 movsd
                 call    MapViewMap__DrawClippedLine
                 fld     [ebp+var_40]
                 call    __ftol
                 mov     [ebp+var_8], eax
                 fild    [ebp+var_8]
                 fst     [ebp+var_30]
                 fld     [ebp+var_3C]
                 fsub    ds:__real@4@40008000000000000000 ; __real@4@4000800000000000000
                 call    __ftol
                 mov     [ebp+var_8], eax
                 fild    [ebp+var_8]
                 fstp    [ebp+var_2C]
                 fstp    [ebp+var_24]
                 fld     [ebp+var_3C]
                 fadd    ds:__real@4@4000c000000000000000 ; __real@4@4000c00000000000000
                 call    __ftol
                 mov     [ebp+var_8], eax
                 fild    [ebp+var_8]

 loc_4379A7:                             ; CODE XREF: MapViewMap__Draw+AADj
                 sub     esp, 10h
                 lea     esi, [ebp+var_54]
                 mov     edi, esp
                 mov     ecx, [ebp+var_C]
                 movsd
                 fstp    [ebp+var_20]
                 push    [ebp+var_14]
                 lea     eax, [ebp+var_30]
                 movsd
                 movsd
                 push    eax
                 movsd
                 call    MapViewMap__DrawClippedLine

 loc_4379C5:                             ; CODE XREF: MapViewMap__Draw+895j
                                         ; MapViewMap__Draw+8A2j
                 cmp     byte_5DF7D8, 0
                 jz      short loc_437A33
                 mov     eax, _g_pMapToolbarWnd ; class CMapToolbarWnd * g_pMapToolbarWn
				 test eax,eax ; added
				 jz      short loc_437A33 ; added
                 cmp     byte ptr [eax+170h], 0
                 jz      short loc_437A33
                 sub     esp, 10h
                 xor     ebx, ebx
                 mov     eax, 270Fh ; 9999?
                 lea     esi, [ebp+var_8C]
                 mov     edi, esp
                 mov     [ebp+var_8C], ebx
                 mov     [ebp+var_88], ebx
                 mov     [ebp+var_84], eax
                 mov     [ebp+var_80], eax
                 push    0FFFFFFFFh ; white lasso...
                 movsd
                 movsd
                 movsd
                 movsd
                 sub     esp, 10h
                 lea     esi, [ebp+var_78]
                 mov     edi, esp
                 movsd
                 movsd
                 movsd
                 movsd
                 call    ?DrawLasso@CXWnd@EQClasses@@SAHVCXRect@2@K0@Z
                 add     esp, 24h
                 cmp     byte_5DF7D9, bl
                 jz      short loc_437A35
                 and     byte_5DF7D8, bl
                 and     byte_5DF7D9, bl
                 jmp     short loc_437A35
 ; ---------------------------------------------------------------------------

 loc_437A33:                             ; CODE XREF: MapViewMap__Draw+B73j
                                         ; MapViewMap__Draw+B81j
                 xor     ebx, ebx

 loc_437A35:                             ; CODE XREF: MapViewMap__Draw+BCAj
                                         ; MapViewMap__Draw+BD8j
                 push    ebx
                 mov     eax, [ebp+var_C]
                 push    ebx
                 push    ebx
                 push    ebx
                 push    ebx
                 push    ebx
                 push    ebx
                 push    ebx
                 push    0Ah             ; Radix
                 push    offset EQADDR_NUMBUFFER1
                 push    dword ptr [eax+7Ch] ; Value
                 call    _itoa
                 add     esp, 0Ch
                 push    eax
                 lea     eax, [ebp+var_28C]
                 push    1A4Ah ; Range = %1
                 push    eax
                 call    ?build_token_string_PARAM@EQUtil@EQClasses@@QAAPADPADH000000000@Z
                 add     esp, 28h
                 lea     eax, [ebp+var_28C]
                 mov     ecx, esp
                 mov     [ebp+var_8], esp
                 push    eax
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, [ebp+var_7C]
                 call    ?GetTextExtent@CTextureFont@EQClasses@@QBEHVCXStr@2@@Z
                 push    ebx
                 push    ebx
                 push    0FF000000h ; color (black)
                 lea     esi, [ebp+var_54]
                 sub     esp, 10h
                 mov     ecx, [ebp+var_7C]
                 mov     edi, esp
                 mov     [ebp+var_8], eax
                 movsd
                 movsd
                 movsd
                 push    12Ch
                 movsd
                 call    ?GetHeight@CTextureFont@EQClasses@@QBEHXZ
                 mov     ecx, [ebp+var_48]
                 sub     ecx, eax
                 mov     eax, [ebp+var_4C]
                 sub     eax, [ebp+var_8]
                 push    ecx
                 push    eax
                 push    ecx
                 lea     eax, [ebp+var_28C]
                 mov     ecx, esp
                 mov     [ebp+var_8], esp
                 push    eax
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, [ebp+var_7C]
                 call    ?DrawWrappedText@CTextureFont@EQClasses@@QBEHVCXStr@2@HHHVCXRect@2@KGH@Z
                 pop     edi
                 pop     esi
                 pop     ebx
                 leave
                 retn    10h
 MapViewMap__Draw endp

_CMapViewWnd_PostDraw   proc near

var_14          = dword ptr -14h
var_10          = dword ptr -10h
var_C           = dword ptr -0Ch
var_8           = dword ptr -8
var_4           = dword ptr -4

                 push    ebp
                 mov     ebp, esp
                 sub     esp, 14h
                 push    ebx
                 mov     ebx, ecx
                 push    esi
                 push    edi
                 cmp     byte ptr [ebx+134h], 0
                 jz      loc_435A14
                 mov     eax, [ebx]
                 lea     ecx, [ebp-14h]
                 push    ecx
                 mov     ecx, ebx
                 call    dword ptr [eax+0D8h] ; CXWnd__GetClientRect (changed)
                 mov     eax, [ebp+var_C]
                 sub     eax, [ebp-14h]
                 cmp     eax, 1
                 jl      loc_435A14
                 mov     eax, [ebp-8]
                 mov     edx, [ebp-10h]
                 sub     eax, edx
                 cmp     eax, 1
                 jl      loc_435A14
                 cmp     _bMappingEnabled, 0
                 jz      short loc_4359AB
                 sub     esp, 10h
                 lea     esi, [ebp-14h]
                 mov     edi, esp
                 lea     ecx, [ebx+1A8h] ; MapViewMap0x1a8
                 movsd
                 movsd
                 movsd
                 movsd
                 call    MapViewMap__Draw
                 jmp     short loc_435A14
 loc_4359AB:                             ; CODE XREF: CMapViewWnd__PostDraw+4Dj
                 mov     eax, pinstCXWndManager ; class CXWndManager * g_pwndmg
				 mov     eax, [eax]
                 add     eax, 0C4h
                 cmp     dword ptr [eax+4], 3
                 jle     short loc_4359C6
                 mov     ecx, [eax]
                 test    ecx, ecx
                 jz      short loc_4359C6
                 lea     eax, [ecx+0Ch]
                 jmp     short loc_4359C8
 ; ---------------------------------------------------------------------------

 loc_4359C6:                             ; CODE XREF: CMapViewWnd__PostDraw+76j
                                         ; CMapViewWnd__PostDraw+7Cj
                 mov     eax, [eax]

 loc_4359C8:                             ; CODE XREF: CMapViewWnd__PostDraw+81j
                 push    0
                 push    0
                 push    0FF000000h ; color
                 lea     esi, [ebp-14h]
                 sub     esp, 10h
                 mov     ebx, [eax]
                 mov     edi, esp
                 mov     eax, [ebp-14h]
                 movsd
                 movsd
                 mov     ecx, pinstStringTable
				 mov     ecx, [ecx]
                 add     edx, 1Eh
                 movsd
                 push    320h
                 add     eax, 1Eh
                 push    edx
                 push    eax
                 push    0
                 push    1A48h           ; Mapping is not available for this zone.
                 movsd
                 call    ?getString@StringTable@EQClasses@@QAEPADKPA_N@Z
                 push    ecx
                 mov     ecx, esp
                 mov     [ebp-4], esp
                 push    eax
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, ebx
                 call    ?DrawWrappedText@CTextureFont@EQClasses@@QBEHVCXStr@2@HHHVCXRect@2@KGH@Z

 loc_435A14:                             ; CODE XREF: CMapViewWnd__PostDraw+12j
                                         ; CMapViewWnd__PostDraw+2Fj ...
                 pop     edi
                 pop     esi
                 xor     eax, eax
                 pop     ebx
                 leave
                 retn
_CMapViewWnd_PostDraw endp
sub_58707C      proc near               ; DATA XREF: o
                 mov     ecx, [ebp-10h]
                 jmp     ??1CSidlScreenWnd@EQClasses@@QAE@XZ
sub_58707C      endp

stru_59C7C0    dd 19930520h            ; DATA XREF: sub_587092o
dd 2
dd offset dword_59C7E0
dd 0
dd 0
dd 0
dd 0
dd 0
dword_59C7E0    dd 0FFFFFFFFh           ; DATA XREF: o
dd offset sub_58707C
db    0
db    0
db    0
db    0
dd offset sub_587084

sub_587092      proc near               ; DATA XREF: CMapViewWnd__CMapViewWndo
                 ;mov     eax, offset stru_59C7C0
                 mov     eax, offset 059C7C0h
                 jmp     ___CxxFrameHandler
sub_587092      endp

sub_587084      proc near               ; DATA XREF: o
                 mov     ecx, [ebp-10h]
                 add     ecx, 1A8h
                 jmp     __MapViewMap__dMapViewMap
sub_587084      endp

aMapviewwnd     db 'MapViewWnd',0
aMvw_panleftbut db 'MVW_PanLeftButton',0
aMvw_panrightbu db 'MVW_PanRightButton',0
aMvw_panupbutto db 'MVW_PanUpButton',0
aMvw_pandownbut db 'MVW_PanDownButton',0
aMvw_panresetbu db 'MVW_PanResetButton',0
aMvw_maprendera db 'MVW_MapRenderArea',0
aMvw_toolbarbut db 'MVW_ToolbarButton',0
aMvw_zfilterbut db 'MVW_ZFilterButton',0
aMvw_maxzeditbo db 'MVW_MaxZEditBox',0  ; DATA XREF: CMapViewWnd__CMapViewWnd+33Bo
aMvw_minzeditbo db 'MVW_MinZEditBox',0  ; DATA XREF: CMapViewWnd__CMapViewWnd+31Eo
aMvw_labelstogg db 'MVW_LabelsToggleButton',0
aMvw_layer3acti db 'MVW_Layer3ActiveButton',0
aMvw_layer2acti db 'MVW_Layer2ActiveButton',0
aMvw_layer1acti db 'MVW_Layer1ActiveButton',0
aMvw_layer3butt db 'MVW_Layer3Button',0 ; DATA XREF: CMapViewWnd__CMapViewWnd+218o
aMvw_layer2butt db 'MVW_Layer2Button',0 ; DATA XREF: CMapViewWnd__CMapViewWnd+1FBo
aMvw_layer1butt db 'MVW_Layer1Button',0
aMvw_layer0butt db 'MVW_Layer0Button',0
aMvw_zoomoutbut db 'MVW_ZoomOutButton',0
aMvw_zoominbutt db 'MVW_ZoomInButton',0




__MapViewMap__MapViewMap proc near        ; CODE XREF: CMapViewWnd__CMapViewWnd+42p
	mov     eax, ecx        ; public: __thiscall MapViewMap::MapViewMap(void
	push    0Ah
	xor     ecx, ecx
	or      byte ptr [eax+5Bh], 0FFh
	mov     [eax+40h], ecx
	mov     [eax+44h], ecx
	mov     [eax+48h], cl
	mov     [eax+5Ch], ecx
	mov     [eax+5Ah], cl
	mov     [eax+59h], cl
	mov     [eax+58h], cl
	fldz
	pop     ecx
	mov     dword ptr [eax+64h], 0Fh
	fstp    dword ptr [eax+78h]
	mov     dword ptr [eax+68h], 1
	mov     [eax+6Ch], ecx
	mov     [eax+70h], ecx
	mov     byte ptr [eax+74h], 1
	mov     byte ptr [eax+80h], 1
	retn
__MapViewMap__MapViewMap endp

_CMapViewWnd_CMapViewWnd proc near      ; CODE XREF: CDisplay__InitGameUI+693p

 var_84          = dword ptr -84h
 Dest            = byte ptr -74h
 var_34          = byte ptr -34h
 var_24          = dword ptr -24h
 var_20          = dword ptr -20h
 var_1C          = dword ptr -1Ch
 var_18          = dword ptr -18h
 var_14          = dword ptr -14h
 var_10          = dword ptr -10h
 var_C           = dword ptr -0Ch
 var_4           = dword ptr -4
 arg_0           = dword ptr  8

                 ;mov     eax, offset sub_587092 ; public: __thiscall CMapViewWnd::CMapViewWnd(class CXWnd *
                 ;call    __EH_prolog
                 ;sub     esp, 68h
                 push    ebx
                 push    esi
                 xor     ebx, ebx
                 push    edi
                 mov     esi, ecx
                 push    ebx
                 push    0FFFFFDFFh
                 push    ecx
                 mov     ecx, esp
                 mov     [ebp+var_14], esp
                 push    offset aMapviewwnd ; "MapViewWnd"
                 mov     [ebp+var_10], esi
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 push    [ebp+arg_0]
                 mov     ecx, esi
                 call    ??0CSidlScreenWnd@EQClasses@@QAE@PAVCXWnd@1@VCXStr@1@HPAD@Z
                 lea     edi, [esi+1A8h]
                 mov     [ebp+var_4], ebx
                 mov     ecx, edi
                 call    __MapViewMap__MapViewMap
                 mov     eax, [esi+104h]
                 mov     byte ptr [ebp+var_4], 1
                 cmp     eax, ebx
                 mov     dword ptr [esi], offset 5EA98Ch ;CMapViewWnd (changed to a CSidlScreenWnd)
                 mov     [esi+134h], bl
                 mov     [esi+158h], bl
                 mov     [esi+138h], ebx
                 mov     [esi+13Ch], ebx
                 mov     [esi+140h], ebx
                 mov     [esi+144h], ebx
                 mov     [esi+148h], ebx
                 mov     [esi+14Ch], ebx
                 mov     [esi+150h], ebx
                 mov     [esi+188h], ebx
                 mov     [esi+18Ch], ebx
                 mov     [esi+190h], ebx
                 mov     [esi+194h], ebx
                 mov     [esi+198h], ebx
                 mov     [esi+19Ch], ebx
                 mov     [esi+1A0h], ebx
                 mov     [esi+178h], ebx
                 mov     [esi+17Ch], ebx
                 mov     [esi+180h], ebx
                 mov     [esi+184h], ebx ; MVW_ZFilterButton
                 mov     [esi+154h], ebx
                 mov     [esi+1A4h], ebx
                 jz      loc_434F23
                 mov     eax, [eax+60h]
                 mov     ecx, esi
                 or      [esi+58h], eax
                 call    ?CreateChildrenFromSidl@CSidlScreenWnd@EQClasses@@QAEXXZ
                 push    ecx
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aMvw_panleftbut ; "MVW_PanLeftButton"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 push    ecx
                 mov     [esi+138h], eax
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aMvw_panrightbu ; "MVW_PanRightButton"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 push    ecx
                 mov     [esi+13Ch], eax
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aMvw_panupbutto ; "MVW_PanUpButton"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 push    ecx
                 mov     [esi+140h], eax
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aMvw_pandownbut ; "MVW_PanDownButton"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 push    ecx
                 mov     [esi+144h], eax
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aMvw_panresetbu ; "MVW_PanResetButton"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 push    ecx
                 mov     [esi+148h], eax
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aMvw_zoominbutt ; "MVW_ZoomInButton"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 push    ecx
                 mov     [esi+14Ch], eax
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aMvw_zoomoutbut ; "MVW_ZoomOutButton"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 push    ecx
                 mov     [esi+150h], eax
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aMvw_layer0butt ; "MVW_Layer0Button"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 push    ecx
                 mov     [esi+188h], eax
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aMvw_layer1butt ; "MVW_Layer1Button"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 push    ecx
                 mov     [esi+18Ch], eax
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aMvw_layer2butt ; "MVW_Layer2Button"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 push    ecx
                 mov     [esi+190h], eax
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aMvw_layer3butt ; "MVW_Layer3Button"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 mov     ecx, [esi+188h]
                 mov     [esi+194h], eax
                 cmp     ecx, ebx
                 jz      short loc_434C4A
                 push    1

 loc_434C45:
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z

 loc_434C4A:                             ; CODE XREF: CMapViewWnd__CMapViewWnd+237j
                 mov     ecx, [esi+18Ch]
                 cmp     ecx, ebx
                 jz      short loc_434C5B
                 push    1
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z

 loc_434C5B:                             ; CODE XREF: CMapViewWnd__CMapViewWnd+248j
                 mov     ecx, [esi+190h]
                 cmp     ecx, ebx
                 jz      short loc_434C6C
                 push    1
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z

 loc_434C6C:                             ; CODE XREF: CMapViewWnd__CMapViewWnd+259j
                 mov     ecx, [esi+194h]
                 cmp     ecx, ebx
                 jz      short loc_434C7D
                 push    1
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z

 loc_434C7D:                             ; CODE XREF: CMapViewWnd__CMapViewWnd+26Aj
                 push    ecx
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aMvw_layer1acti ; "MVW_Layer1ActiveButton"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 push    ecx
                 mov     [esi+198h], eax
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aMvw_layer2acti ; "MVW_Layer2ActiveButton"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 push    ecx
                 mov     [esi+19Ch], eax
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aMvw_layer3acti ; "MVW_Layer3ActiveButton"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 mov     ecx, [esi+198h]
                 mov     [esi+1A0h], eax
                 cmp     ecx, ebx
                 jz      short loc_434CE5
                 push    1
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z

 loc_434CE5:                             ; CODE XREF: CMapViewWnd__CMapViewWnd+2D2j
                 mov     ecx, [esi+19Ch]
                 cmp     ecx, ebx
                 jz      short loc_434CF5
                 push    ebx
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z

 loc_434CF5:                             ; CODE XREF: CMapViewWnd__CMapViewWnd+2E3j
                 mov     ecx, [esi+1A0h]
                 cmp     ecx, ebx
                 jz      short loc_434D05
                 push    ebx
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z

 loc_434D05:                             ; CODE XREF: CMapViewWnd__CMapViewWnd+2F3j
                 push    ecx
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aMvw_labelstogg ; "MVW_LabelsToggleButton"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 push    ecx
                 mov     [esi+178h], eax
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aMvw_minzeditbo ; "MVW_MinZEditBox"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 push    ecx
                 mov     [esi+17Ch], eax
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aMvw_maxzeditbo ; "MVW_MaxZEditBox"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 push    ecx
                 mov     [esi+180h], eax
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aMvw_zfilterbut ; "MVW_ZFilterButton"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 push    ecx
                 mov     [esi+184h], eax ; MVW_ZFilterButton
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aMvw_toolbarbut ; "MVW_ToolbarButton"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 cmp     eax, ebx
                 mov     [esi+154h], eax
                 jz      short loc_434DA5
                 cmp     dword_70436C, ebx
                 jnz     short loc_434DA5
                 mov     [eax+51h], bl

 loc_434DA5:                             ; CODE XREF: CMapViewWnd__CMapViewWnd+38Ej
                                         ; CMapViewWnd__CMapViewWnd+396j
                 push    0Ah
                 pop     eax
                 push    64h
                 mov     [ebp+var_24], eax
                 mov     [ebp+var_20], eax
                 pop     eax
                 push    ecx
                 mov     [ebp+var_1C], eax
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aMvw_maprendera ; "MVW_MapRenderArea"
                 mov     [ebp+var_18], eax
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 cmp     eax, ebx
                 mov     [esi+1A4h], eax
                 jz      short loc_434DFA
                 lea     ecx, [ebp+var_34]
                 push    ecx
                 mov     ecx, eax
                 call    ?GetRelativeRect@CXWnd@EQClasses@@QBE?AVCXRect@2@XZ
                 mov     ecx, [eax]
                 mov     [ebp+var_24], ecx
                 mov     ecx, [eax+4]
                 mov     [ebp+var_20], ecx
                 mov     ecx, [eax+8]
                 mov     eax, [eax+0Ch]
                 mov     [ebp+var_1C], ecx
                 mov     [ebp+var_18], eax

 loc_434DFA:                             ; CODE XREF: CMapViewWnd__CMapViewWnd+3CCj
                 mov     ecx, 3E8h
                 mov     eax, 0FFFFFC18h
                 push    ecx
                 push    eax
                 push    ecx
                 push    eax
                 mov     ecx, edi
                 call    __MapViewMap__SetZoneExtents
                 fldz
                 push    ecx             ; float
                 mov     ecx, edi
                 fstp    [esp+84h+var_84]
                 call    __MapViewMap__SetZoom
                 mov     eax, [ebp+var_1C]
                 mov     byte ptr [edi+81h], 1
                 sub     eax, [ebp+var_24]
                 mov     ecx, esi
                 mov     [ebp+arg_0], eax
                 mov     eax, [ebp+var_18]
                 fild    [ebp+arg_0]
                 sub     eax, [ebp+var_20]
                 fstp    dword ptr [edi+10h]
                 mov     [ebp+arg_0], eax
                 fild    [ebp+arg_0]
                 fstp    dword ptr [edi+14h]

 loc_434E43:
                 fild    [ebp+var_24]
                 fstp    dword ptr [edi+18h]
                 fild    [ebp+var_20]
                 fstp    dword ptr [edi+1Ch]
                 mov     [esi+1C8h], ebx
                 mov     [esi+1CCh], ebx
                 mov     [esi+135h], bl
                 call    __CMapViewWnd__Init
                 mov     ecx, [esi+178h]
                 cmp     ecx, ebx
                 jz      short loc_434E7C
                 mov     al, [esi+228h]
                 push    eax
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z

 loc_434E7C:                             ; CODE XREF: CMapViewWnd__CMapViewWnd+464j
                 mov     ecx, [esi+184h] ; MVW_ZFilterButton
                 cmp     ecx, ebx
                 jz      short loc_434E92
                 mov     al, [esi+21Ch]
                 push    eax
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z

 loc_434E92:                             ; CODE XREF: CMapViewWnd__CMapViewWnd+47Aj
                 cmp     [esi+17Ch], ebx
                 jz      short loc_434EC8
                 lea     eax, [ebp+Dest]
                 push    0Ah             ; Radix
                 push    eax             ; Dest
                 mov     ecx, edi
                 call    __MapViewMap__GetMinZ
                 push    eax             ; Value
                 call    _itoa
                 pop     ecx
                 pop     ecx
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    eax
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, [esi+17Ch]
                 mov     eax, [ecx]
                 call    dword ptr [eax+0ECh] ; CEditWnd__SetWindowTextA

 loc_434EC8:                             ; CODE XREF: CMapViewWnd__CMapViewWnd+48Ej
                 cmp     [esi+180h], ebx
                 jz      short loc_434EFE
                 lea     eax, [ebp+Dest]
                 push    0Ah             ; Radix
                 push    eax             ; Dest
                 mov     ecx, edi
                 call    __MapViewMap__GetMaxZ
                 push    eax             ; Value
                 call    _itoa
                 pop     ecx
                 pop     ecx
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    eax
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, [esi+180h]
                 mov     eax, [ecx]
                 call    dword ptr [eax+0ECh] ; CEditWnd__SetWindowTextA

 loc_434EFE:                             ; CODE XREF: CMapViewWnd__CMapViewWnd+4C4j
                 cmp     byte_5DF7E4, bl
                 jz      short loc_434F23
                 push    offset _unk_5DF7B0
                 push    offset _unk_5DF7C0
                 push    dword_5DF7CC
                 mov     ecx, esi
                 call    __CMapViewWnd__SetCurrentZone
                 mov     byte_5DF7E4, bl

 loc_434F23:                             ; CODE XREF: CMapViewWnd__CMapViewWnd+DDj
                                         ; CMapViewWnd__CMapViewWnd+4FAj
                 mov     ecx, [ebp+var_C]
                 mov     eax, esi
                 pop     edi
                 pop     esi
                 ;mov     fs:0, ecx
                 pop     ebx
                 leave
                 retn    4
 _CMapViewWnd_CMapViewWnd endp

_CMapViewWnd_LoadIniInfo proc near      ; DATA XREF: .rdata:00593E08o

Default         = byte ptr -244h
Dest            = byte ptr -144h
aStr             = byte ptr -104h
var_4           = dword ptr -4

                push    ebp             ; public: virtual void __thiscall CMapViewWnd::LoadIniInfo(void
                mov     ebp, esp
                sub     esp, 244h
                push    ebx
                push    esi
                push    edi
                mov     edi, ecx
                call    ?_NewUIINI@MQ2Globals@@YAPADXZ
                test    eax, eax
                jz      loc_435E4D
                cmp     byte ptr [edi+228h], 0
                mov     eax, offset aTrue ; "true"
                jnz     short loc_435C03
                mov     eax, offset aFalse ; "false"

loc_435C03:                             ; CODE XREF: CMapViewWnd__LoadIniInfo+27j
                push    eax
                lea     eax, [ebp+Default]
                push    offset aS       ; "%s"
                push    eax             ; Dest
                call    _sprintf
                add     esp, 0Ch
                mov     ebx, 100h
                lea     eax, [ebp+aStr]
                lea     ecx, [edi+120h]
                push    ebx             ; nSize
                push    eax             ; lpReturnedString
                lea     eax, [ebp+Default]
                push    eax             ; lpDefault
                push    offset aLabelsactive ; "LabelsActive"
                call    ?operatorp@CXStr@EQClasses@@QBEXXZ ; CXStr__operator_char_p
                push    eax             ; lpAppName
                call    ?LoadStringFromUIIniFile@MQ2Globals@@YAXPAD000H@Z
                add     esp, 14h
                cmp     [ebp+aStr], 74h
                jz      short loc_435C64
                cmp     [ebp+aStr], 54h
                jz      short loc_435C64
                cmp     [ebp+aStr], 31h
                jz      short loc_435C64
                xor     eax, eax
                jmp     short loc_435C67
; ---------------------------------------------------------------------------

loc_435C64:                             ; CODE XREF: CMapViewWnd__LoadIniInfo+77j
                                        ; CMapViewWnd__LoadIniInfo+80j ...
                push    1
                pop     eax

loc_435C67:                             ; CODE XREF: CMapViewWnd__LoadIniInfo+8Dj
                lea     esi, [edi+1A8h]
                mov     [esi+80h], al
                mov     byte ptr [esi+81h], 1
                cmp     byte ptr [edi+21Ch], 0
                mov     eax, offset aTrue ; "true"
                jnz     short loc_435C8D
                mov     eax, offset aFalse ; "false"

loc_435C8D:                             ; CODE XREF: CMapViewWnd__LoadIniInfo+B1j
                push    eax
                lea     eax, [ebp+Default]
                push    offset aS       ; "%s"
                push    eax             ; Dest
                call    _sprintf
                add     esp, 0Ch
                lea     eax, [ebp+aStr]
                lea     ecx, [edi+120h]
                push    ebx             ; nSize
                push    eax             ; lpReturnedString
                lea     eax, [ebp+Default]
                push    eax             ; lpDefault
                push    offset aHeightfilter ; "HeightFilter"
                call    ?operatorp@CXStr@EQClasses@@QBEXXZ ; CXStr__operator_char_p
                push    eax             ; lpAppName
                call    ?LoadStringFromUIIniFile@MQ2Globals@@YAXPAD000H@Z
                add     esp, 14h
                cmp     [ebp+aStr], 74h
                jz      short loc_435CE9
                cmp     [ebp+aStr], 54h
                jz      short loc_435CE9
                cmp     [ebp+aStr], 31h
                jz      short loc_435CE9
                xor     eax, eax
                jmp     short loc_435CEC
; ---------------------------------------------------------------------------

loc_435CE9:                             ; CODE XREF: CMapViewWnd__LoadIniInfo+FCj
                                        ; CMapViewWnd__LoadIniInfo+105j ...
                push    1
                pop     eax

loc_435CEC:                             ; CODE XREF: CMapViewWnd__LoadIniInfo+112j
                mov     [esi+74h], al
                mov     byte ptr [esi+81h], 1
                push    dword ptr [edi+214h]
                lea     eax, [ebp+Default]
                push    offset aD_0     ; "%d"
                push    eax             ; Dest
                call    _sprintf
                add     esp, 0Ch
                lea     eax, [ebp+aStr]
                lea     ecx, [edi+120h]
                push    ebx             ; nSize
                push    eax             ; lpReturnedString
                lea     eax, [ebp+Default]
                push    eax             ; lpDefault
                push    offset aHeightlow ; "HeightLow"
                call    ?operatorp@CXStr@EQClasses@@QBEXXZ ; CXStr__operator_char_p
                push    eax             ; lpAppName
                call    ?LoadStringFromUIIniFile@MQ2Globals@@YAXPAD000H@Z
                lea     eax, [ebp+aStr]
                push    eax             ; Str
                call    _atoi
                add     esp, 18h
                mov     [esi+6Ch], eax
                mov     byte ptr [esi+81h], 1
                push    dword ptr [edi+218h]
                lea     eax, [ebp+Default]
                push    offset aD_0     ; "%d"
                push    eax             ; Dest
                call    _sprintf
                add     esp, 0Ch
                lea     eax, [ebp+aStr]
                lea     ecx, [edi+120h]
                push    ebx             ; nSize
                push    eax             ; lpReturnedString
                lea     eax, [ebp+Default]
                push    eax             ; lpDefault
                push    offset aHeighthigh ; "HeightHigh"
                call    ?operatorp@CXStr@EQClasses@@QBEXXZ ; CXStr__operator_char_p
                push    eax             ; lpAppName
                call    ?LoadStringFromUIIniFile@MQ2Globals@@YAXPAD000H@Z
                lea     eax, [ebp+aStr]
                push    eax             ; Str
                call    _atoi
                mov     [esi+70h], eax
                mov     byte ptr [esi+81h], 1
                mov     ecx, [edi+178h]
                add     esp, 18h
                test    ecx, ecx
                jz      short loc_435DBC
                mov     al, [edi+228h]
                push    eax
                call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z

loc_435DBC:                             ; CODE XREF: CMapViewWnd__LoadIniInfo+1D9j
                mov     ecx, [edi+184h] ; MVW_ZFilterButton
                test    ecx, ecx
                jz      short loc_435DD2
                mov     al, [edi+21Ch]
                push    eax
                call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z

loc_435DD2:                             ; CODE XREF: CMapViewWnd__LoadIniInfo+1EFj
                cmp     dword ptr [edi+17Ch], 0
                jz      short loc_435E0C
                lea     eax, [ebp+Dest]
                push    0Ah             ; Radix
                push    eax             ; Dest
                mov     ecx, esi
                call    __MapViewMap__GetMinZ
                push    eax             ; Value
                call    _itoa
                pop     ecx
                pop     ecx
                mov     ecx, esp
                mov     [ebp+var_4], esp
                push    eax             ; int
                call    ??0CXStr@EQClasses@@QAE@PBD@Z
                mov     ecx, [edi+17Ch]
                mov     eax, [ecx]
                ;call    dword ptr [eax+0E8h]
                call    dword ptr [eax+0ECh] ; CEditWnd__SetWindowTextA (changed)


loc_435E0C:                             ; CODE XREF: CMapViewWnd__LoadIniInfo+204j
                cmp     dword ptr [edi+180h], 0
                jz      short loc_435E46
                lea     eax, [ebp+Dest]
                push    0Ah             ; Radix
                push    eax             ; Dest
                mov     ecx, esi
                call    __MapViewMap__GetMaxZ
                push    eax             ; Value
                call    _itoa
                pop     ecx
                pop     ecx
                mov     ecx, esp
                mov     [ebp+var_4], esp
                push    eax             ; int
                call    ??0CXStr@EQClasses@@QAE@PBD@Z
                mov     ecx, [edi+180h]
                mov     eax, [ecx]
                ;call    dword ptr [eax+0E8h]
                call    dword ptr [eax+0ECh] ; CEditWnd__SetWindowTextA (changed)

loc_435E46:                             ; CODE XREF: CMapViewWnd__LoadIniInfo+23Ej
                mov     ecx, edi
                call    ?LoadIniInfo@CSidlScreenWnd@EQClasses@@QAEXXZ ; CSidlScreenWnd__LoadIniInfo

loc_435E4D:                             ; CODE XREF: CMapViewWnd__LoadIniInfo+15j
                pop     edi
                pop     esi
                pop     ebx
                leave
                retn
_CMapViewWnd_LoadIniInfo endp


; =============== S U B R O U T I N E =======================================

; Attributes: bp-based frame

_CMapViewWnd_StoreIniInfo proc near     ; DATA XREF: .rdata:00593E0Co

String          = byte ptr -100h

                push    ebp             ; public: virtual void __thiscall CMapViewWnd::StoreIniInfo(void
                mov     ebp, esp
                sub     esp, 100h
                push    esi
                mov     esi, ecx
                call    ?_NewUIINI@MQ2Globals@@YAPADXZ
                test    eax, eax
                jz      loc_435F6A
                cmp     byte ptr [esi+228h], 0
                mov     eax, offset aTrue ; "true"
                jnz     short loc_435E7E
                mov     eax, offset aFalse ; "false"

loc_435E7E:                             ; CODE XREF: CMapViewWnd__StoreIniInfo+25j
                push    ebx
                push    edi
                push    eax
                mov     edi, offset aS  ; "%s"
                lea     eax, [ebp+String]
                push    edi             ; Format
                push    eax             ; Dest
                call    _sprintf
                add     esp, 0Ch
                lea     eax, [ebp+String]
                lea     ebx, [esi+120h]
                push    eax             ; lpString
                push    offset aLabelsactive ; "LabelsActive"
                mov     ecx, ebx
                call    ?operatorp@CXStr@EQClasses@@QBEXXZ
                push    eax             ; lpAppName
                call    ?SaveToUIIniFile@MQ2Globals@@YAXPAD00@Z
                add     esp, 0Ch
                cmp     byte ptr [esi+21Ch], 0
                mov     eax, offset aTrue ; "true"
                jnz     short loc_435ECB
                mov     eax, offset aFalse ; "false"

loc_435ECB:                             ; CODE XREF: CMapViewWnd__StoreIniInfo+72j
                push    eax
                lea     eax, [ebp+String]
                push    edi             ; Format
                push    eax             ; Dest
                call    _sprintf
                add     esp, 0Ch
                lea     eax, [ebp+String]
                mov     ecx, ebx
                push    eax             ; lpString
                push    offset aHeightfilter ; "HeightFilter"
                call    ?operatorp@CXStr@EQClasses@@QBEXXZ
                push    eax             ; lpAppName
                call    ?SaveToUIIniFile@MQ2Globals@@YAXPAD00@Z
                add     esp, 0Ch
                mov     edi, offset aD_0 ; "%d"
                push    dword ptr [esi+214h]
                lea     eax, [ebp+String]
                push    edi             ; Format
                push    eax             ; Dest
                call    _sprintf
                add     esp, 0Ch
                lea     eax, [ebp+String]
                mov     ecx, ebx
                push    eax             ; lpString
                push    offset aHeightlow ; "HeightLow"
                call    ?operatorp@CXStr@EQClasses@@QBEXXZ
                push    eax             ; lpAppName
                call    ?SaveToUIIniFile@MQ2Globals@@YAXPAD00@Z
                add     esp, 0Ch
                lea     eax, [ebp+String]
                push    dword ptr [esi+218h]
                push    edi             ; Format
                push    eax             ; Dest
                call    _sprintf
                add     esp, 0Ch
                lea     eax, [ebp+String]
                mov     ecx, ebx
                push    eax             ; lpString
                push    offset aHeighthigh ; "HeightHigh"
                call    ?operatorp@CXStr@EQClasses@@QBEXXZ
                push    eax             ; lpAppName
                call    ?SaveToUIIniFile@MQ2Globals@@YAXPAD00@Z
                add     esp, 0Ch
                mov     ecx, esi
                call    ?StoreIniInfo@CSidlScreenWnd@EQClasses@@QAEXXZ ; CSidlScreenWnd__StoreIniInfo
                pop     edi
                pop     ebx

loc_435F6A:                             ; CODE XREF: CMapViewWnd__StoreIniInfo+13j
                pop     esi
                leave
                retn
_CMapViewWnd_StoreIniInfo endp


_TEXT   ENDS
END