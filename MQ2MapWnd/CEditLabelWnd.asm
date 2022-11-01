
        TITLE CEditLabelWnd.asm
        .386P

include listing.inc
.model   flat
INCLUDELIB MQ2Main.lib
EXTRN _g_pEditLabelWnd:DWORD
PUBLIC _CEditLabelWnd_Deactivate
PUBLIC _CEditLabelWnd_GetLabelText
PUBLIC _CEditLabelWnd_Activate
PUBLIC _CEditLabelWnd_WndNotification
EXTRN ?CreateChildrenFromSidl@CSidlScreenWnd@EQClasses@@QAEXXZ:PROC ; CSidlScreenWnd__CreateChildrenFromSidl
EXTRN ??0CSidlScreenWnd@EQClasses@@QAE@PAVCXWnd@1@VCXStr@1@HPAD@Z:PROC ; CSidlScreenWnd__CSidlScreenWnd1
EXTRN ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z:PROC ; CSidlScreenWnd__GetChildItem
EXTRN ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z:PROC ; CButtonWnd__SetCheck
EXTRN ?Show@CXWnd@EQClasses@@QAEH_N0@Z:PROC ; CXWnd__Show
EXTRN ?Activate@CColorPickerWnd@EQClasses@@QAEXPAVCXWnd@2@K@Z:PROC ; CColorPickerWnd__Activate
EXTRN ?WndNotification@CSidlScreenWnd@EQClasses@@QAEHPAVCXWnd@2@IPAX@Z:PROC ; CSidlScreenWnd__WndNotification
EXTRN ??0CXStr@EQClasses@@QAE@PBD@Z:PROC ; CXStr__CXStr3
_DATA   SEGMENT PARA USE32 PUBLIC 'DATA'
ValueName       db 17Ch dup(0)
aEditlabelwnd   db 'EditLabelWnd',0
aElw_donebutton db 'ELW_DoneButton',0   ; DATA XREF: CEditLabelWnd__CEditLabelWnd+171o
aElw_cancelbutt db 'ELW_CancelButton',0 ; DATA XREF: CEditLabelWnd__CEditLabelWnd+154o
aElw_labelsmall db 'ELW_LabelSmallButton',0
aElw_labelmediu db 'ELW_LabelMediumButton',0
aElw_labellarge db 'ELW_LabelLargeButton',0
aElw_choosecolo db 'ELW_ChooseColorButton',0
aElw_labeltexte db 'ELW_LabelTextEditbox',0

g_pColorPickerWnd DWORD 63D62Ch
_TEXT   SEGMENT PARA USE32 PUBLIC 'CODE'
ASSUME fs:NOTHING

_CEditLabelWnd_GetLabelText proc near   ; CODE XREF: CMapToolbarWnd__WndNotification+A3p

 var_4           = dword ptr -4
 arg_0           = dword ptr  8

                 push    ebp             ; public: class CXStr __thiscall CEditLabelWnd::GetLabelText(void
                 mov     ebp, esp
                 push    ecx
                 mov     ecx, [ecx+140h]
                 push    [ebp+arg_0]
                 and     [ebp+var_4], 0
                 mov     eax, [ecx]
                 ;call    dword ptr [eax+110h]
				 call    dword ptr [eax+114h] ; CEditWnd__GetWindowTextA (changed)
                 mov     eax, [ebp+arg_0]
                 leave
                 retn    4
 _CEditLabelWnd_GetLabelText endp


CEditLabelWnd__CEditLabelWnd proc near  ; CODE XREF: CDisplay__InitGameUI+6C1p

 var_14          = dword ptr -14h
 var_10          = dword ptr -10h
 var_C           = dword ptr -0Ch
 var_4           = dword ptr -4
 arg_0           = dword ptr  8

                 ;mov     eax, offset sub_586014 ; public: __thiscall CEditLabelWnd::CEditLabelWnd(class CXWnd *
                 ;call    __EH_prolog
				 ; got to add code here if we are to call this...
                 push    ecx
                 push    ecx
                 push    ebx
                 xor     ebx, ebx
                 push    esi
                 mov     esi, ecx
                 push    ebx
                 push    0FFFFFFFFh
                 push    ecx
                 mov     [ebp+var_10], esi
                 mov     ecx, esp
                 mov     [ebp+var_14], esp
                 push    offset aEditlabelwnd ; "EditLabelWnd"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 push    [ebp+arg_0]
                 mov     ecx, esi
                 call    ??0CSidlScreenWnd@EQClasses@@QAE@PAVCXWnd@1@VCXStr@1@HPAD@Z
                 cmp     [esi+104h], ebx
                 mov     [ebp+var_4], ebx
                 mov     dword ptr [esi], offset 5EA98Ch ; we change this to a regular CSidlScreenWnd instead of CEditLabelWnd
                 mov     [esi+15Ch], bl
                 mov     [esi+134h], ebx
                 mov     dword ptr [esi+13Ch], 1
                 mov     dword ptr [esi+138h], 0FF000000h
                 mov     [esi+140h], ebx
                 mov     [esi+144h], ebx
                 mov     [esi+148h], ebx
                 mov     [esi+14Ch], ebx
                 mov     [esi+150h], ebx
                 mov     [esi+154h], ebx
                 mov     [esi+158h], ebx
                 jz      loc_41BEA7
                 mov     ecx, esi
                 call    ?CreateChildrenFromSidl@CSidlScreenWnd@EQClasses@@QAEXXZ
                 push    ecx
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aElw_labeltexte ; "ELW_LabelTextEditbox"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 push    ecx
                 mov     [esi+140h], eax
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aElw_choosecolo ; "ELW_ChooseColorButton"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 push    ecx
                 mov     [esi+144h], eax
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aElw_labellarge ; "ELW_LabelLargeButton"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 cmp     eax, ebx
                 mov     [esi+148h], eax
                 jz      short loc_41BE1A
                 push    ebx
                 mov     ecx, eax
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z

 loc_41BE1A:                             ; CODE XREF: CEditLabelWnd__CEditLabelWnd+F1j
                 push    ecx
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aElw_labelmediu ; "ELW_LabelMediumButton"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 cmp     eax, ebx
                 mov     [esi+14Ch], eax
                 jz      short loc_41BE43
                 push    ebx
                 mov     ecx, eax
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z

 loc_41BE43:                             ; CODE XREF: CEditLabelWnd__CEditLabelWnd+11Aj
                 push    ecx
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aElw_labelsmall ; "ELW_LabelSmallButton"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 cmp     eax, ebx
                 mov     [esi+150h], eax
                 jz      short loc_41BE6D
                 push    1
                 mov     ecx, eax
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z

 loc_41BE6D:                             ; CODE XREF: CEditLabelWnd__CEditLabelWnd+143j
                 push    ecx
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aElw_cancelbutt ; "ELW_CancelButton"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 push    ecx
                 mov     [esi+154h], eax
                 mov     ecx, esp
                 mov     [ebp+arg_0], esp
                 push    offset aElw_donebutton ; "ELW_DoneButton"
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, esi
                 call    ?GetChildItem@CSidlScreenWnd@EQClasses@@QBEPAVCXWnd@2@VCXStr@2@@Z
                 mov     [esi+158h], eax

 loc_41BEA7:                             ; CODE XREF: CEditLabelWnd__CEditLabelWnd+8Bj
                 mov     ecx, [ebp+var_C]
                 mov     eax, esi
                 pop     esi
;                 mov     large fs:0, ecx
                 pop     ebx
                 leave
                 retn    4
 CEditLabelWnd__CEditLabelWnd endp


 ; =============== S U B R O U T I N E =======================================

 ; Attributes: bp-based frame

 _CEditLabelWnd_Activate proc near       ; CODE XREF: CMapToolbarWnd__WndNotification+2C8p

 arg_0           = dword ptr  8
 arg_4           = dword ptr  0Ch
 arg_8           = dword ptr  10h
 arg_C           = dword ptr  14h

                 push    ebp             ; public: void __thiscall CEditLabelWnd::Activate(class CXWnd *,char *,int,unsigned long
                 mov     ebp, esp
                 mov     eax, [ebp+arg_0]
                 push    esi
                 mov     esi, ecx
                 push    edi
                 xor     edi, edi
                 mov     ecx, [esi+150h]
                 mov     [esi+134h], eax
                 mov     eax, [ebp+arg_8]
                 cmp     ecx, edi
                 mov     [esi+13Ch], eax
                 jz      short loc_41BF36
                 cmp     [esi+14Ch], edi
                 jz      short loc_41BF36
                 cmp     [esi+148h], edi
                 jz      short loc_41BF36
                 dec     eax
                 jz      short loc_41BF17
                 dec     eax
                 jz      short loc_41BF0D
                 dec     eax
                 jnz     short loc_41BF36
                 push    edi
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z
                 mov     ecx, [esi+14Ch]
                 push    edi
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z
                 push    1
                 jmp     short loc_41BF2B
 ; ---------------------------------------------------------------------------

 loc_41BF0D:                             ; CODE XREF: CEditLabelWnd__Activate+39j
                 push    edi
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z
                 push    1
                 jmp     short loc_41BF1F
 ; ---------------------------------------------------------------------------

 loc_41BF17:                             ; CODE XREF: CEditLabelWnd__Activate+36j
                 push    1
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z
                 push    edi

 loc_41BF1F:                             ; CODE XREF: CEditLabelWnd__Activate+5Cj
                 mov     ecx, [esi+14Ch]
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z
                 push    edi

 loc_41BF2B:                             ; CODE XREF: CEditLabelWnd__Activate+52j
                 mov     ecx, [esi+148h]
                 call    ?SetCheck@CButtonWnd@EQClasses@@QAEX_N@Z

 loc_41BF36:                             ; CODE XREF: CEditLabelWnd__Activate+23j
                                         ; CEditLabelWnd__Activate+2Bj ...
                 mov     eax, [ebp+arg_C]
                 cmp     [ebp+arg_4], edi
                 push    ecx
                 mov     [esi+138h], eax
                 mov     ecx, esp
                 jz      short loc_41BF4F
                 mov     [ebp+arg_0], esp
                 push    [ebp+arg_4]
                 jmp     short loc_41BF57
 ; ---------------------------------------------------------------------------

 loc_41BF4F:                             ; CODE XREF: CEditLabelWnd__Activate+8Cj
                 mov     [ebp+arg_4], esp
                 push    offset ValueName ; int

 loc_41BF57:                             ; CODE XREF: CEditLabelWnd__Activate+94j
                 call    ??0CXStr@EQClasses@@QAE@PBD@Z
                 mov     ecx, [esi+140h]
                 mov     eax, [ecx]
                 ;call    dword ptr [eax+0E8h] ; CXWnd__SetWindowTextA
                 call    dword ptr [eax+0ECh] ; changed
                 push    1
                 push    1
                 mov     ecx, esi
                 mov     byte ptr [esi+15Ch], 1
                 call    ?Show@CXWnd@EQClasses@@QAEH_N0@Z
                 pop     edi
                 pop     esi
                 pop     ebp
                 retn    10h
 _CEditLabelWnd_Activate endp


 ; =============== S U B R O U T I N E =======================================


_CEditLabelWnd_Deactivate proc near     ; DATA XREF: .o
                 xor     eax, eax        ; public: virtual void __thiscall CEditLabelWnd::Deactivate(void
                 push    1
                 push    eax
                 mov     [ecx+15Ch], al
                 mov     [ecx+134h], eax
                 call    ?Show@CXWnd@EQClasses@@QAEH_N0@Z
                 retn
_CEditLabelWnd_Deactivate endp


 ; =============== S U B R O U T I N E =======================================

 ; Attributes: bp-based frame

 _CEditLabelWnd_WndNotification proc near ; DATA XREF: .o

 arg_0           = dword ptr  8
 arg_4           = dword ptr  0Ch
 arg_8           = dword ptr  10h

                 push    ebp             ; public: virtual int __thiscall CEditLabelWnd::WndNotification(class CXWnd *,unsigned __int32,void *
                 mov     ebp, esp
                 push    esi
                 mov     esi, ecx
                 cmp     byte ptr [esi+15Ch], 0
                 jz      short loc_41BFB7
                 cmp     [ebp+arg_4], 1Eh
                 jnz     short loc_41BFBE
                 mov     eax, [ebp+arg_8]
                 mov     [esi+138h], eax

 loc_41BFB7:                             ; CODE XREF: CEditLabelWnd__WndNotification+Dj
                 xor     eax, eax
                 jmp     loc_41C062
 ; ---------------------------------------------------------------------------

 loc_41BFBE:                             ; CODE XREF: CEditLabelWnd__WndNotification+13j
                 push    edi
                 mov     edi, [ebp+arg_0]
                 push    1
                 pop     eax
                 cmp     [ebp+arg_4], eax
                 jnz     loc_41C053
                 cmp     edi, [esi+158h]
                 jnz     short loc_41BFF9
                 mov     ecx, [esi+134h]
                 test    ecx, ecx
                 jz      short loc_41C053
                 mov     eax, [ecx]
                 push    0
                 push    6
                 push    esi
                 ;call    dword ptr [eax+80h] ; CXWnd__WndNotification
                 call    dword ptr [eax+84h] ; changed

 loc_41BFED:                             ; CODE XREF: CEditLabelWnd__WndNotification+66j
                 mov     eax, [esi]
                 mov     ecx, esi
                 ;call    dword ptr [eax+84h] ; CXWnd__Deactivate
                 call    dword ptr [eax+88h] ; changed
                 jmp     short loc_41C053
 ; ---------------------------------------------------------------------------

 loc_41BFF9:                             ; CODE XREF: CEditLabelWnd__WndNotification+3Bj
                 cmp     edi, [esi+154h]
                 jz      short loc_41BFED
                 cmp     edi, [esi+148h]
                 jnz     short loc_41C015
                 mov     dword ptr [esi+13Ch], 3
                 jmp     short loc_41C053
 ; ---------------------------------------------------------------------------

 loc_41C015:                             ; CODE XREF: CEditLabelWnd__WndNotification+6Ej
                 cmp     edi, [esi+14Ch]
                 jnz     short loc_41C029
                 mov     dword ptr [esi+13Ch], 2
                 jmp     short loc_41C053
 ; ---------------------------------------------------------------------------

 loc_41C029:                             ; CODE XREF: CEditLabelWnd__WndNotification+82j
                 cmp     edi, [esi+150h]
                 jnz     short loc_41C039
                 mov     [esi+13Ch], eax
                 jmp     short loc_41C053
 ; ---------------------------------------------------------------------------

 loc_41C039:                             ; CODE XREF: CEditLabelWnd__WndNotification+96j
                 cmp     edi, [esi+144h]
                 jnz     short loc_41C053
                 mov     ecx, g_pColorPickerWnd ; class CColorPickerWnd * g_pColorPickerWn
                 mov     ecx, [ecx] ; added
				 test	 ecx,ecx ; added
				 jz		 loc_41C053 ; added
                 push    dword ptr [esi+138h] ; moved this here
                 push    esi
                 call    ?Activate@CColorPickerWnd@EQClasses@@QAEXPAVCXWnd@2@K@Z

 loc_41C053:                             ; CODE XREF: CEditLabelWnd__WndNotification+2Fj
                                         ; CEditLabelWnd__WndNotification+45j ...
                 push    [ebp+arg_8]
                 mov     ecx, esi
                 push    [ebp+arg_4]
                 push    edi
                 call    ?WndNotification@CSidlScreenWnd@EQClasses@@QAEHPAVCXWnd@2@IPAX@Z
                 pop     edi

 loc_41C062:                             ; CODE XREF: CEditLabelWnd__WndNotification+20j
                 pop     esi
                 pop     ebp
                 retn    0Ch
_CEditLabelWnd_WndNotification endp

 _TEXT   ENDS
END
