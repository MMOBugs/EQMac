
        TITLE CMapToolbarWnd.asm
        .386P

include listing.inc
.model   flat
INCLUDELIB MQ2Main.lib

PUBLIC _CMapToolbarWnd_Deactivate
PUBLIC _CMapToolbarWnd_OnProcessFrame
EXTRN _CEditLabelWnd_GetLabelText:PROC
EXTRN _MapViewMap_SetCurrentColor:PROC
EXTRN _MapViewMap_SetMarkedLine:PROC
EXTRN _MapViewMap_AddLabel:PROC
EXTRN _MapViewMap_SetMarkedLineColor:PROC
EXTRN new:PROC
EXTRN operator__delete:PROC
EXTRN _MapViewMap_RecalcLabelExtents:PROC
EXTRN _MapViewMap_StartLine:PROC
EXTRN _MapViewMap_EndLine:PROC
EXTRN _MapViewMap_AddPoint:PROC
EXTRN _CEditLabelWnd_Activate:PROC
EXTRN _MapViewMap_RemoveLine_0:PROC
EXTRN _MapViewMap_RemoveLabel_0:PROC
EXTRN _MapViewMap_MoveLabel:PROC
EXTRN _MapViewMap_Save:PROC
EXTRN _MapViewMap_JoinLinesAtIntersect:PROC
PUBLIC _CMapToolbarWnd_WndNotification
PUBLIC _CMapToolbarWnd_Activate
EXTRN _MapViewMap_GetCurrentColor:PROC
EXTRN _MapViewMap_GetMarkedLineColor:PROC
EXTRN _CMapViewWnd_ActivateAutoMapping:PROC
EXTRN _CMapViewWnd_DeactivateAutoMapping:PROC
EXTRN _CMapViewWnd_IsMappingEnabled:PROC
EXTRN _g_pMapViewWnd:DWORD
EXTRN _g_pEditLabelWnd:DWORD
EXTRN ?operatorp@CXStr@EQClasses@@QBEXXZ:PROC ; CXStr__operator_char_p
EXTRN ?FreeRep@CXStr@EQClasses@@QAEXPAUCStrRep@2@@Z:PROC ; CXStr__FreeRep
EXTRN ?dsp_chat@CEverQuest@EQClasses@@QAEXPBD@Z:PROC ; CEverQuest__dsp_chat1
EXTRN ?GetKeyboardFlags@CXWndManager@EQClasses@@QBEIXZ:PROC ; CXWndManager__GetKeyboardFlags
EXTRN ?build_token_string_PARAM@EQUtil@EQClasses@@QAAPADPADH000000000@Z:PROC ; build_token_string_PARAM
EXTRN ?Activate@CConfirmationDialog@EQClasses@@QAEXHIPBD@Z:PROC ; CConfirmationDialog__Activate
EXTRN ?getString@StringTable@EQClasses@@QAEPADKPA_N@Z:PROC ; StringTable__getString
EXTRN ?Activate@CColorPickerWnd@EQClasses@@QAEXPAVCXWnd@2@K@Z:PROC ; CColorPickerWnd__Activate
EXTRN ?OnProcessFrame@CXWnd@EQClasses@@QAEHXZ:PROC ; CXWnd__OnProcessFrame
EXTRN ?IsNewbieZone@EQWorldData@EQClasses@@QBE_NW4EQZoneIndex@2@@Z:PROC ; EQWorldData__IsNewbieZone
EXTRN ?Show@CXWnd@EQClasses@@QAEH_N0@Z:PROC ; CXWnd__Show
EXTRN ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z:PROC ; CButtonWnd__SetCheck
EXTRN ?WndNotification@CSidlScreenWnd@EQClasses@@QAEHPAVCXWnd@2@IPAX@Z:PROC ; CSidlScreenWnd__WndNotification


EXTRN _toupper:PROC
EXTRN _strcpy:PROC
EXTRN _strlen:PROC

_DATA   SEGMENT PARA USE32 PUBLIC 'DATA'

pinstLocalPlayer DWORD 7F94CCh
byte_5DF785     db 0
dword_5DF788    dd 0
dword_70436C    dd 0
byte_5DF784     db 0
pinstWorldData DWORD 7F9494h
g_pColorPickerWnd DWORD 63D62Ch
pinstStringTable DWORD 7F9490h
g_pConfirmationDialog DWORD 63D5D4h
pinstCEverQuest DWORD 809478h
pinstCXWndManager DWORD 809DB4h
__real@4@3ffea000000000000000 REAL4 0.63 ; can be picked up from eqgame
_TEXT   SEGMENT PARA USE32 PUBLIC 'CODE'
ASSUME fs:NOTHING

_CMapToolbarWnd_Activate proc near      ; CODE XREF: CMapViewWnd__WndNotification+FCp
                                         ; CDisplay__ActivateMainUI+96p
                 push    esi
                 mov     esi, ecx
                 push    1
                 push    1
                 mov     byte ptr [esi+170h], 1
                 call    ?Show@CXWnd@EQClasses@@QAEH_N0@Z
                 pop     esi
                 retn
_CMapToolbarWnd_Activate endp


 ; =============== S U B R O U T I N E =======================================


_CMapToolbarWnd_Deactivate proc near    ; DATA XREF: .rdata:00592D70o
                                         ; .rdata:00593C90o
                 and     byte ptr [ecx+170h], 0 ; public: virtual void __thiscall CMapToolbarWnd::Deactivate(void
                 push    1
                 push    0
                 call    ?Show@CXWnd@EQClasses@@QAEH_N0@Z
                 retn
_CMapToolbarWnd_Deactivate endp


 ; =============== S U B R O U T I N E =======================================


_CMapToolbarWnd_OnProcessFrame proc near ; DATA XREF: .rdata:00593CB4o
                 push    esi             ; public: virtual int __thiscall CMapToolbarWnd::OnProcessFrame(void
                 mov     esi, ecx
                 mov     ecx, _g_pMapViewWnd ; class CMapViewWnd * g_pMapViewWn
                 test    ecx, ecx
                 jz      short loc_434437
                 call    _CMapViewWnd_IsMappingEnabled
                 cmp     al, 1
                 jz      short loc_434437
                 cmp     byte ptr [esi+170h], 1
                 jnz     short loc_434437
                 mov     eax, [esi]
                 mov     ecx, esi
                 call    dword ptr [eax+88h] ; (changed) CMapToolbarWnd__Deactivate

 loc_434437:                             ; CODE XREF: CMapToolbarWnd__OnProcessFrame+Bj
                                         ; CMapToolbarWnd__OnProcessFrame+14j ...
                 mov     ecx, esi
                 call    ?OnProcessFrame@CXWnd@EQClasses@@QAEHXZ
                 pop     esi
                 retn
_CMapToolbarWnd_OnProcessFrame endp


 ; =============== S U B R O U T I N E =======================================

 ; public: virtual int __thiscall CMapToolbarWnd::WndNotification(class CXWnd *,unsigned __int32,void *
 ; Attributes: bp-based frame

_CMapToolbarWnd_WndNotification proc near ; DATA XREF: .rdata:00593C8Co

 var_F0          = dword ptr -0F0h
 var_EC          = dword ptr -0ECh
 var_E8          = dword ptr -0E8h
 var_E4          = dword ptr -0E4h
 var_E0          = dword ptr -0E0h
 var_DC          = dword ptr -0DCh
 aStr             = byte ptr -0CCh
 File            = byte ptr -4Ch
 var_C           = dword ptr -0Ch
 var_4           = dword ptr -4
 arg_0           = dword ptr  8
 arg_4           = dword ptr  0Ch
 arg_8           = dword ptr  10h

                 ;mov     eax, offset sub_587070
                 ;call    __EH_prolog
				 push    ebp
				 mov     ebp, esp
				 push    0FFFFFFFFh ; we push this as well as 
                 push    eax ; a few of theese to fake the stack the ehprolog would populate 
                 push    eax ; since I had to rip it out...
                 push	 eax ; I should probably add a local exception handler at some point / mule
                 sub     esp, 0C0h
                 push    ebx
                 push    esi
                 mov     esi, ecx
                 push    edi
                 mov     al, [esi+170h]
                 test    al, al
                 jz      short loc_4344A0
                 mov     ecx, _g_pMapViewWnd ; class CMapViewWnd * g_pMapViewWn
                 xor     edi, edi
                 cmp     ecx, edi
                 jz      short loc_4344A0
                 cmp     [ebp+arg_4], 1Eh
                 jnz     short loc_4344C0
                 cmp     byte_5DF784, 1
                 push    [ebp+arg_8]
                 jnz     short loc_4344B3
                 add     ecx, 1A8h
                 call    _MapViewMap_SetMarkedLineColor
                 mov     eax, _g_pMapViewWnd ; class CMapViewWnd * g_pMapViewWn
                 and     byte_5DF784, 0
                 push    edi
                 lea     ecx, [eax+1A8h]
                 call    _MapViewMap_SetMarkedLine

 loc_4344A0:                             ; CODE XREF: CMapToolbarWnd__WndNotification+1Dj
                                         ; CMapToolbarWnd__WndNotification+29j ...
                 xor     eax, eax

 loc_4344A2:                             ; CODE XREF: CMapToolbarWnd__WndNotification+4FEj
                 mov     ecx, [ebp+var_C]
                 pop     edi
                 pop     esi
                 pop     ebx
;                 mov     large fs:0, ecx
                 leave
                 retn    0Ch
 ; ---------------------------------------------------------------------------

 loc_4344B3:                             ; CODE XREF: CMapToolbarWnd__WndNotification+3Bj
                 add     ecx, 1A8h
                 call    _MapViewMap_SetCurrentColor
                 jmp     short loc_4344A0
 ; ---------------------------------------------------------------------------

 loc_4344C0:                             ; CODE XREF: CMapToolbarWnd__WndNotification+2Fj
                 cmp     [ebp+arg_4], 6
                 jnz     loc_4345F9
                 mov     ecx, _g_pEditLabelWnd ; class CEditLabelWnd * g_pEditLabelWn
                 cmp     ecx, edi
                 jz      short loc_4344A0
                 cmp     [ebp+arg_0], ecx
                 jnz     short loc_4344A0
                 mov     ebx, [ecx+138h]
                 lea     eax, [ebp+arg_4]
                 push    eax
                 call    _CEditLabelWnd_GetLabelText
                 mov     eax, _g_pEditLabelWnd ; class CEditLabelWnd * g_pEditLabelWn
                 cmp     byte_5DF785, 0
                 mov     [ebp+var_4], edi
                 mov     esi, [eax+13Ch]
                 jnz     short loc_434554
                 mov     eax, pinstLocalPlayer ; class EQPlayer * LocalPlaye
                 mov     eax, [eax] ; added
                 lea     ecx, [ebp+arg_4]
                 ;mov     eax, [eax+12Ch]
                 mov     eax, [eax+0F0h] ; changed to F0 since its Unknown0x0f0
                 mov     [ebp+arg_8], eax
                 call    ?operatorp@CXStr@EQClasses@@QBEXXZ ; CXStr__operator_char_p
                 fld     [ebp+arg_8]
                 fmul    ds:__real@4@3ffea000000000000000 ; __real@4@3ffea00000000000000
                 push    eax             ; Str
                 mov     eax, pinstLocalPlayer ; class EQPlayer * LocalPlaye
                 mov     eax, [eax] ; added
				 push    esi             ; int
                 push    ebx             ; int
                 fsubr   dword ptr [eax+50h] ; changed
                 push    ecx             ; int
                 fstp    [esp+0E8h+var_E8]
                 fld     dword ptr [eax+48h] ; Y
                 push    ecx             ; int
                 fchs
                 fstp    [esp+0ECh+var_EC]
                 fld     dword ptr [eax+4Ch] ; X
                 mov     eax, _g_pMapViewWnd ; class CMapViewWnd * g_pMapViewWn
                 push    ecx             ; int
                 fchs
                 fstp    [esp+0F0h+var_F0]
                 lea     ecx, [eax+1A8h]
                 call    _MapViewMap_AddLabel
                 jmp     loc_4345DC
 ; ---------------------------------------------------------------------------

 loc_434554:                             ; CODE XREF: CMapToolbarWnd__WndNotification+BDj
                 mov     eax, dword_5DF788
                 mov     [eax+18h], esi
                 mov     ecx, dword_5DF788
                 mov     eax, ebx
                 shr     eax, 10h
                 mov     [ecx+16h], al
                 mov     ecx, dword_5DF788
                 mov     eax, ebx
                 shr     eax, 8
                 mov     [ecx+15h], al
                 mov     eax, dword_5DF788
                 mov     [eax+14h], bl
                 mov     eax, dword_5DF788
                 push    dword ptr [eax+1Ch]
                 call    operator__delete
                 pop     ecx
                 lea     ecx, [ebp+arg_4]
                 call    ?operatorp@CXStr@EQClasses@@QBEXXZ
                 push    eax             ; Str
                 call    _strlen
                 inc     eax
                 push    eax             ; unsigned int
                 call    new
                 pop     ecx
                 pop     ecx
                 mov     ecx, dword_5DF788
                 mov     [ecx+1Ch], eax
                 lea     ecx, [ebp+arg_4]
                 call    ?operatorp@CXStr@EQClasses@@QBEXXZ
                 push    eax             ; Source
                 mov     eax, dword_5DF788
                 push    dword ptr [eax+1Ch] ; Dest
                 call    _strcpy
                 mov     eax, _g_pMapViewWnd ; class CMapViewWnd * g_pMapViewWn
                 pop     ecx
                 pop     ecx
                 push    dword_5DF788
                 lea     ecx, [eax+1A8h]
                 call    _MapViewMap_RecalcLabelExtents

 loc_4345DC:                             ; CODE XREF: CMapToolbarWnd__WndNotification+10Fj
                 or      [ebp+var_4], 0FFFFFFFFh
                 cmp     [ebp+arg_4], edi
                 jz      loc_4344A0
                 push    [ebp+arg_4]
                 lea     ecx, [ebp+arg_4]
                 call    ?FreeRep@CXStr@EQClasses@@QAEXPAUCStrRep@2@@Z
                 jmp     loc_4344A0
 ; ---------------------------------------------------------------------------

 loc_4345F9:                             ; CODE XREF: CMapToolbarWnd__WndNotification+84j
                 cmp     [ebp+arg_4], 1
                 mov     ebx, [ebp+arg_0]
                 jnz     loc_434930
                 cmp     ebx, [esi+134h]
                 jnz     short loc_434648
                 mov     eax, pinstLocalPlayer ; class EQPlayer * LocalPlaye
                 mov     eax, [eax] ; added
				 push    ecx
                 fld     dword ptr [eax+0F0h] ; changed to F0 since its Unknown0x0f0
                 fmul    ds:__real@4@3ffea000000000000000 ; __real@4@3ffea00000000000000
                 fsubr   dword ptr [eax+50h] ; changed
                 fstp    [esp+0DCh+var_DC]
                 fld     dword ptr [eax+48h] ; Y
                 push    ecx
                 fchs
                 fstp    [esp+0E0h+var_E0]
                 fld     dword ptr [eax+4Ch] ; X
                 push    ecx
                 add     ecx, 1A8h
                 fchs
                 fstp    [esp+0E4h+var_E4]
                 call    _MapViewMap_StartLine
                 jmp     loc_434930
 ; ---------------------------------------------------------------------------

 loc_434648:                             ; CODE XREF: CMapToolbarWnd__WndNotification+1CCj
                 cmp     ebx, [esi+138h]
                 jnz     short loc_43468A
                 mov     eax, pinstLocalPlayer ; class EQPlayer * LocalPlaye
                 mov     eax, [eax] ; added
				 push    ecx             ; int
                 fld     dword ptr [eax+0F0h] ; changed to F0 since its Unknown0x0f0
                 fmul    ds:__real@4@3ffea000000000000000 ; __real@4@3ffea00000000000000
                 fsubr   dword ptr [eax+50h] ; changed
                 fstp    [esp+0DCh+var_DC]
                 fld     dword ptr [eax+48h] ; Y
                 push    ecx             ; float
                 fchs
                 fstp    [esp+0E0h+var_E0]
                 fld     dword ptr [eax+4Ch] ; X
                 push    ecx             ; float
                 add     ecx, 1A8h
                 fchs
                 fstp    [esp+0E4h+var_E4]
                 call    _MapViewMap_EndLine
                 jmp     loc_434930
 ; ---------------------------------------------------------------------------

 loc_43468A:                             ; CODE XREF: CMapToolbarWnd__WndNotification+20Ej
                 cmp     ebx, [esi+140h]
                 jnz     short loc_4346A2
                 add     ecx, 1A8h
                 call    _MapViewMap_RemoveLine_0
                 jmp     loc_434930
 ; ---------------------------------------------------------------------------

 loc_4346A2:                             ; CODE XREF: CMapToolbarWnd__WndNotification+250j
                 cmp     ebx, [esi+13Ch]
                 jnz     short loc_4346E4
                 mov     eax, pinstLocalPlayer ; class EQPlayer * LocalPlaye
                 mov     eax, [eax] ; added
				 push    ecx             ; int
                 fld     dword ptr [eax+0F0h] ; changed to F0 since its Unknown0x0f0
                 fmul    ds:__real@4@3ffea000000000000000 ; __real@4@3ffea00000000000000
                 fsubr   dword ptr [eax+50h] ; changed
                 fstp    [esp+0DCh+var_DC]
                 fld     dword ptr [eax+48h] ; Y
                 push    ecx             ; float
                 fchs
                 fstp    [esp+0E0h+var_E0]
                 fld     dword ptr [eax+4Ch] ; X
                 push    ecx             ; float
                 add     ecx, 1A8h
                 fchs
                 fstp    [esp+0E4h+var_E4]
                 call    _MapViewMap_AddPoint
                 jmp     loc_434930
 ; ---------------------------------------------------------------------------

 loc_4346E4:                             ; CODE XREF: CMapToolbarWnd__WndNotification+268j
                 cmp     ebx, [esi+150h]
                 jnz     short loc_434712
                 and     byte_5DF785, 0
                 push    0FF000000h
                 push    1
                 mov     dword_5DF788, edi
                 push    edi

 loc_434701:                             ; CODE XREF: CMapToolbarWnd__WndNotification+31Dj
                 mov     ecx, _g_pEditLabelWnd ; class CEditLabelWnd * g_pEditLabelWn
                 push    esi
                 call    _CEditLabelWnd_Activate
                 jmp     loc_434930
 ; ---------------------------------------------------------------------------

 loc_434712:                             ; CODE XREF: CMapToolbarWnd__WndNotification+2AAj
                 cmp     ebx, [esi+154h]
                 jnz     short loc_43475F
                 add     ecx, 208h
                 cmp     [ecx], edi
                 jz      loc_434930
                 mov     byte_5DF785, 1
                 mov     eax, [ecx]
                 mov     dword_5DF788, eax
                 mov     ecx, [eax+14h]
                 mov     [ebp+arg_0], ecx
                 movzx   edx, byte ptr [ebp+arg_0+2]
                 or      edx, 0FFFFFF00h
                 movzx   edi, ch
                 shl     edx, 8
                 or      edx, edi
                 movzx   ecx, cl
                 shl     edx, 8
                 or      edx, ecx
                 push    edx
                 push    dword ptr [eax+18h]
                 push    dword ptr [eax+1Ch]
                 jmp     short loc_434701
 ; ---------------------------------------------------------------------------

 loc_43475F:                             ; CODE XREF: CMapToolbarWnd__WndNotification+2D8j
                 cmp     ebx, [esi+158h]
                 jnz     short loc_4347B0
                 mov     edx, [ecx+208h]
                 cmp     edx, edi
                 jz      loc_434930
                 mov     eax, pinstLocalPlayer ; class EQPlayer * LocalPlaye
                 mov     eax, [eax] ; added
				 push    ecx             ; int
                 fld     dword ptr [eax+0F0h] ; changed to F0 since its Unknown0x0f0
                 fmul    ds:__real@4@3ffea000000000000000 ; __real@4@3ffea00000000000000
                 fsubr   dword ptr [eax+50h] ; changed
                 fstp    [esp+0DCh+var_DC]
                 fld     dword ptr [eax+48h] ; Y
                 push    ecx             ; int
                 fchs
                 fstp    [esp+0E0h+var_E0]
                 fld     dword ptr [eax+4Ch] ; X
                 push    ecx             ; float
                 add     ecx, 1A8h
                 fchs
                 fstp    [esp+0E4h+var_E4]
                 push    edx             ; int
                 call    _MapViewMap_MoveLabel
                 jmp     loc_434930
 ; ---------------------------------------------------------------------------

 loc_4347B0:                             ; CODE XREF: CMapToolbarWnd__WndNotification+325j
                 cmp     ebx, [esi+15Ch]
                 jnz     short loc_4347C8
                 add     ecx, 1A8h
                 call    _MapViewMap_RemoveLabel_0
                 jmp     loc_434930
 ; ---------------------------------------------------------------------------

 loc_4347C8:                             ; CODE XREF: CMapToolbarWnd__WndNotification+376j
                 cmp     ebx, [esi+16Ch]
                 jnz     short loc_43483A
                 add     ecx, 158h
                 lea     eax, [ebp+File]
                 push    ecx             ; Source
                 push    eax             ; Dest
                 call    _strcpy
                 pop     ecx
                 lea     eax, [ebp+File]
                 pop     ecx
                 push    eax             ; File
                 mov     eax, _g_pMapViewWnd ; class CMapViewWnd * g_pMapViewWn
                 lea     ecx, [eax+1A8h]
                 call    _MapViewMap_Save
                 movsx   eax, [ebp+File]
                 push    eax             ; C
                 call    _toupper
                 push    edi
                 push    edi
                 push    edi
                 push    edi
                 push    edi
                 mov     [ebp+File], al
                 push    edi
                 push    edi
                 lea     eax, [ebp+File]
                 push    edi
                 push    eax
                 lea     eax, [ebp+aStr]
                 push    3022h           ; %1 saved.
                 push    eax
                 call    ?build_token_string_PARAM@EQUtil@EQClasses@@QAAPADPADH000000000@Z
                 mov     ecx, pinstCEverQuest
                 mov     ecx, [ecx] ; added
                 add     esp, 30h
                 lea     eax, [ebp+aStr]
                 push    eax             ; Str
                 call    ?dsp_chat@CEverQuest@EQClasses@@QAEXPBD@Z
                 jmp     loc_434930
 ; ---------------------------------------------------------------------------

 loc_43483A:                             ; CODE XREF: CMapToolbarWnd__WndNotification+38Ej
                 cmp     ebx, [esi+148h]
                 jnz     short loc_43486B
                 mov     ecx, pinstCXWndManager ; class CXWndManager * g_pwndmg
                 mov     ecx, [ecx] ; added
                 call    ?GetKeyboardFlags@CXWndManager@EQClasses@@QBEIXZ
                 test    al, 2
                 jz      short loc_434868
                 push    1               ; float

 loc_434853:                             ; CODE XREF: CMapToolbarWnd__WndNotification+429j
                 mov     eax, _g_pMapViewWnd ; class CMapViewWnd * g_pMapViewWn
                 lea     ecx, [eax+1A8h]
                 call    _MapViewMap_JoinLinesAtIntersect
                 jmp     loc_434930
 ; ---------------------------------------------------------------------------

 loc_434868:                             ; CODE XREF: CMapToolbarWnd__WndNotification+40Fj
                 push    edi
                 jmp     short loc_434853
 ; ---------------------------------------------------------------------------

 loc_43486B:                             ; CODE XREF: CMapToolbarWnd__WndNotification+400j
                 cmp     ebx, [esi+168h]
                 jnz     short loc_434898
                 mov     ecx, pinstStringTable
                 mov     ecx, [ecx] ; added
                 push    edi
                 push    3AD5h           ; Are you sure you want to clear the current active layer of your map?
                 call    ?getString@StringTable@EQClasses@@QAEPADKPA_N@Z
                 push    eax
                 push    edi
                 push    2Ah

 loc_434888:                             ; CODE XREF: CMapToolbarWnd__WndNotification+475j
                 mov     ecx, g_pConfirmationDialog ; class CConfirmationDialog * g_pConfirmationDialo
                 mov     ecx, [ecx] ; added
                 call    ?Activate@CConfirmationDialog@EQClasses@@QAEXHIPBD@Z ; CConfirmationDialog__Activate
                 jmp     loc_434930
 ; ---------------------------------------------------------------------------

 loc_434898:                             ; CODE XREF: CMapToolbarWnd__WndNotification+431j
                 cmp     ebx, [esi+164h]
                 jnz     short loc_4348B7
                 mov     ecx, pinstStringTable
                 mov     ecx, [ecx] ; added
                 push    edi
                 push    3AD4h           ; Are you sure you want to clear the entire map?
                 call    ?getString@StringTable@EQClasses@@QAEPADKPA_N@Z
                 push    eax
                 push    edi
                 push    29h
                 jmp     short loc_434888
 ; ---------------------------------------------------------------------------

 loc_4348B7:                             ; CODE XREF: CMapToolbarWnd__WndNotification+45Ej
                 cmp     ebx, [esi+160h]
                 jnz     short loc_4348E0
                 and     byte_5DF784, 0
                 add     ecx, 1A8h
                 call    _MapViewMap_GetCurrentColor

 loc_4348D1:                             ; CODE XREF: CMapToolbarWnd__WndNotification+4CFj
                 mov     ecx, g_pColorPickerWnd ; class CColorPickerWnd * g_pColorPickerWn
				 mov	 ecx,[ecx] ; added
				 test	 ecx,ecx ; added
				 jz		 loc_434930 ; added to prevent crash
                 push    eax
                 push    esi
                 call    ?Activate@CColorPickerWnd@EQClasses@@QAEXPAVCXWnd@2@K@Z ; CColorPickerWnd__Activate
                 jmp     short loc_434930
 ; ---------------------------------------------------------------------------

 loc_4348E0:                             ; CODE XREF: CMapToolbarWnd__WndNotification+47Dj
                 cmp     ebx, [esi+144h]
                 jnz     short loc_434911
                 mov     eax, [ecx+204h]
                 add     ecx, 1A8h
                 cmp     eax, edi
                 jz      short loc_4348FD
                 mov     eax, [eax+4]
                 jmp     short loc_4348FF
 ; ---------------------------------------------------------------------------

 loc_4348FD:                             ; CODE XREF: CMapToolbarWnd__WndNotification+4B6j
                 xor     eax, eax

 loc_4348FF:                             ; CODE XREF: CMapToolbarWnd__WndNotification+4BBj
                 cmp     eax, edi
                 jz      short loc_434930
                 mov     byte_5DF784, 1
                 call    _MapViewMap_GetMarkedLineColor
                 jmp     short loc_4348D1
 ; ---------------------------------------------------------------------------

 loc_434911:                             ; CODE XREF: CMapToolbarWnd__WndNotification+4A6j
                 mov     eax, [esi+14Ch]
                 cmp     ebx, eax
                 jnz     short loc_434930
                 cmp     byte ptr [eax+108h], 0
                 jz      short loc_43492B
                 call    _CMapViewWnd_ActivateAutoMapping
                 jmp     short loc_434930
 ; ---------------------------------------------------------------------------

 loc_43492B:                             ; CODE XREF: CMapToolbarWnd__WndNotification+4E2j
                 call    _CMapViewWnd_DeactivateAutoMapping

 loc_434930:                             ; CODE XREF: CMapToolbarWnd__WndNotification+1C0j
                                         ; CMapToolbarWnd__WndNotification+203j ...
                 push    [ebp+arg_8]
                 mov     ecx, esi
                 push    [ebp+arg_4]
                 push    ebx
                 call    ?WndNotification@CSidlScreenWnd@EQClasses@@QAEHPAVCXWnd@2@IPAX@Z
                 jmp     loc_4344A2
_CMapToolbarWnd_WndNotification endp


 ; =============== S U B R O U T I N E =======================================


_CMapToolbarWnd_SetAutoMapButton proc near
                                         ; CODE XREF: CMapViewWnd__DeactivateAutoMapping+59p

 arg_0           = dword ptr  4

                 mov     ecx, [ecx+14Ch] ; public: void __thiscall CMapToolbarWnd::SetAutoMapButton(bool
                 test    ecx, ecx
                 jz      short locret_434956
                 push    [esp+arg_0]
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z

 locret_434956:                          ; CODE XREF: CMapToolbarWnd__SetAutoMapButton+8j
                 retn    4
_CMapToolbarWnd_SetAutoMapButton endp

_TEXT   ENDS
END