;Extended Ineger Arithmetics
.586
.model flat, C

addInteger PROTO fnum:ptr dword, snum:ptr dword, res:ptr dword, sz:dword
subInteger PROTO, fnum:ptr dword, snum:ptr dword, res:ptr dword, sz:dword

.code 

;--------------------------------------------------------------
;addInteger
;Calculates the sum of two extended integers stored as arrays of bytes 
;Storage for the sum must be one byte longer than 
;the input operands 
;void addInteger(void *fnum, void *snum, void *result, size_t size)
;--------------------------------------------------------------
addInteger PROC, fnum:ptr dword, snum:ptr dword, result:ptr dword, sz:dword 
    pushad 
    clc 
    mov ecx, sz

    ;make pointer to data 
    mov esi, fnum 
    mov edi, snum 
    mov ebx, result 

L1: mov al, [esi]
    adc al, byte ptr [edi]
    pushfd 
    mov [ebx], al 
    
    inc esi
    inc edi 
    inc ebx 
    popfd 
    loop L1 

    ;mov byte ptr [ebx], 0
    ;adc byte ptr [ebx], 0
    popad
    ret
addInteger ENDP 

;--------------------------------------------------------------
;subInteger
;Subtracts two extended integers stored as arrays of bytes 
;Storage for the sum must be one byte longer than 
;the input operands 
;void subInteger(void *fnum, void *snum, void *result, size_t size)
;--------------------------------------------------------------
subInteger PROC, fnum:ptr dword, snum:ptr dword, result:ptr dword, sz:dword 
    pushad 
    clc 

    mov ecx, sz 
    mov esi, fnum 
    mov edi, snum 
    mov ebx, result 

L1: mov al, [esi]
    sbb al, byte ptr [edi]
    pushfd 
    mov byte ptr [ebx], al
    inc esi 
    inc edi
    inc ebx
    popfd 
    loop L1 

    ;mov byte ptr [ebx], 0
    ;sbb byte ptr [ebx], 0
    popad 
    ret
subInteger ENDP
END