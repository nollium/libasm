global ft_write
extern print_shit
extern __errno_location

section .text:

    ft_write:
        mov rax,1;  set syscall to sys_write
        syscall; call sys_write
        cmp rax,0;  if returned valued >= 0
        jge end;            jump to end
        push rax
        call	__errno_location
        pop rdi
        neg rdi
        mov	[rax], rdi
        mov rax,-1; else    returned_value = -1
    end: 
        ret;    return (returned_value)
