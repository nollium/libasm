global ft_strcpy

ft_strcpy:
	mov		r9,rdi
	xor     rdx, rdx   ; i = 0

loop:
	mov	eax, [rsi + rdx];	tmp = src[i]
	mov [rdi + rdx], eax; 	dst[i] = tmp
	cmp byte [rsi + rdx], byte 0; if src[i] == 0
	je end  ; then  | jump to end
	inc rdx ; else  | i++
	jmp loop ;      | jump to loop beginning

end:
	mov rax,r9
	ret ; return (dst)
