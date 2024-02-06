.686
.model flat
.data
.code
_sumthree proc
mov eax, [esp+4]
mov ebx, [esp+8]
mov ecx, [esp+12]
add eax, ebx
add eax, ecx
ret
_sumthree endp
end