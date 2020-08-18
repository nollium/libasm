global ft_strlen

ft_strlen:

    mov     rax,0

loop:
    cmp byte [rdi + rax], byte 0
    je end
    inc rax
    jmp loop

end:
    ret