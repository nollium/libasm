global ft_strcmp

ft_strcmp:
	xor     rdx, rdx;	i = 0
	xor     rax, rax;	ret_value = 0;
	xor 	r9,r9;		tmp

loop:
	mov	al, byte [rdi + rdx];	ret_value = s2[i]
	mov r9b, byte[rsi + rdx];	tmp = s1[i]
	cmp byte al,byte r9b; 		if ret_value != tmp
	jne end; 						jump to end
	cmp	byte al, 0;				else if ret_value == 0
	je 	end;						jump to end
	inc rdx;					else	i++
	jmp loop;							jump to loop

end:
	sub rax, r9;	ret_value -= tmp
	ret; 			return (ret_value)
