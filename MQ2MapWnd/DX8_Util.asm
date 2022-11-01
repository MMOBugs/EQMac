
        TITLE DX8_Util.asm
        .386P

include listing.inc
.model   flat


PUBLIC _t3dGetWorldExtents

_TEXT   SEGMENT PARA USE32 PUBLIC 'CODE'
ASSUME fs:NOTHING

_t3dGetWorldExtents proc near

var_8           = dword ptr -8
var_4           = dword ptr -4
arg_0           = dword ptr  4
arg_4           = dword ptr  8
arg_8           = dword ptr  0Ch

                sub     esp, 8
                push    edi
                mov     edi, [esp+0Ch+arg_0]
                test    edi, edi
                jz      loc_1002DAA2
                mov     eax, [edi+18h]
                test    eax, eax
                jbe     loc_1002DAA2
                mov     ecx, [esp+0Ch+arg_8]
                mov     edx, [esp+0Ch+arg_4]
                mov     eax, 0C76A6000h ; -60000.000000
                mov     [ecx], eax
                mov     [ecx+4], eax
                mov     [ecx+8], eax
                mov     eax, 476A6000h  ; 60000.000000
                mov     [edx], eax
                mov     [edx+4], eax
                mov     [edx+8], eax
                mov     eax, [edi+18h]
                push    esi
                xor     esi, esi
                test    eax, eax
                jbe     loc_1002DA97
                push    ebx
                lea     esp, [esp+0]

loc_1002D9E0:                           ; CODE XREF: t3dGetWorldExtents+100j
                mov     eax, [edi+24h]
                mov     eax, [eax+esi*4]
                mov     ebx, [eax+18h]
                fld     dword ptr [eax+14h]
                mov     [esp+14h+var_8], ebx
                mov     ebx, [eax+1Ch]
                mov     eax, [eax+20h]
                mov     [esp+14h+arg_0], eax
                fld     [esp+14h+arg_0]
                mov     [esp+14h+var_4], ebx
                fadd    st, st(1)
                fcom    dword ptr [ecx]
                fnstsw  ax
                test    ah, 41h
                jnz     short loc_1002DA11
                fstp    dword ptr [ecx]
                jmp     short loc_1002DA13
; ---------------------------------------------------------------------------

loc_1002DA11:                           ; CODE XREF: t3dGetWorldExtents+7Bj
                fstp    st

loc_1002DA13:                           ; CODE XREF: t3dGetWorldExtents+7Fj
                fld     [esp+14h+arg_0]
                fadd    [esp+14h+var_8]
                fcom    dword ptr [ecx+4]
                fnstsw  ax
                test    ah, 41h
                jnz     short loc_1002DA2A
                fstp    dword ptr [ecx+4]
                jmp     short loc_1002DA2C
; ---------------------------------------------------------------------------

loc_1002DA2A:                           ; CODE XREF: t3dGetWorldExtents+93j
                fstp    st

loc_1002DA2C:                           ; CODE XREF: t3dGetWorldExtents+98j
                fld     [esp+14h+arg_0]
                fadd    [esp+14h+var_4]
                fcom    dword ptr [ecx+8]
                fnstsw  ax
                test    ah, 41h
                jnz     short loc_1002DA43
                fstp    dword ptr [ecx+8]
                jmp     short loc_1002DA45
; ---------------------------------------------------------------------------

loc_1002DA43:                           ; CODE XREF: t3dGetWorldExtents+ACj
                fstp    st

loc_1002DA45:                           ; CODE XREF: t3dGetWorldExtents+B1j
                fsub    [esp+14h+arg_0]
                fcom    dword ptr [edx]
                fnstsw  ax
                test    ah, 5
                jp      short loc_1002DA56
                fstp    dword ptr [edx]
                jmp     short loc_1002DA58
; ---------------------------------------------------------------------------

loc_1002DA56:                           ; CODE XREF: t3dGetWorldExtents+C0j
                fstp    st

loc_1002DA58:                           ; CODE XREF: t3dGetWorldExtents+C4j
                fld     [esp+14h+var_8]
                fsub    [esp+14h+arg_0]
                fcom    dword ptr [edx+4]
                fnstsw  ax
                test    ah, 5
                jp      short loc_1002DA6F
                fstp    dword ptr [edx+4]
                jmp     short loc_1002DA71
; ---------------------------------------------------------------------------

loc_1002DA6F:                           ; CODE XREF: t3dGetWorldExtents+D8j
                fstp    st

loc_1002DA71:                           ; CODE XREF: t3dGetWorldExtents+DDj
                fld     [esp+14h+var_4]
                fsub    [esp+14h+arg_0]
                fcom    dword ptr [edx+8]
                fnstsw  ax
                test    ah, 5
                jp      short loc_1002DA88
                fstp    dword ptr [edx+8]
                jmp     short loc_1002DA8A
; ---------------------------------------------------------------------------

loc_1002DA88:                           ; CODE XREF: t3dGetWorldExtents+F1j
                fstp    st

loc_1002DA8A:                           ; CODE XREF: t3dGetWorldExtents+F6j
                mov     eax, [edi+18h]
                inc     esi
                cmp     esi, eax
                jb      loc_1002D9E0
                pop     ebx

loc_1002DA97:                           ; CODE XREF: t3dGetWorldExtents+45j
                pop     esi
                mov     eax, 1
                pop     edi
                add     esp, 8
                retn
; ---------------------------------------------------------------------------

loc_1002DAA2:                           ; CODE XREF: t3dGetWorldExtents+Aj
                                        ; t3dGetWorldExtents+15j
                xor     eax, eax
                pop     edi
                add     esp, 8
                retn
_t3dGetWorldExtents endp

_TEXT   ENDS
END