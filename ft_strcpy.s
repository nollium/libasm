global ft_strcpy

ft_strcpy:
	xor     rdx, rdx;	i = 0

loop:
	mov	ah, [rsi + rdx];	tmp = src[i]
	mov [rdi + rdx], ah; 	dst[i] = tmp
	cmp byte [rsi + rdx], byte 0; if src[i] == 0
	je end; 						|then	jump to end
	inc rdx; 						|else	| i++
	jmp loop;						|		| jump to loop

end:
	mov rax,rdi;	return_value = dst
	ret; 			return (return_value)
