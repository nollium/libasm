global ft_read
extern print_shit

ft_read:
    mov rax,0;  set syscall to sys_write
    syscall; call sys_write
    cmp rax,0;  if returned valued >= 0
    jge end;            jump to end
    mov rax,-1; else    returned_value = -1
end: 
    ret;    return (returned_value)
