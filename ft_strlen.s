global ft_strlen

ft_strlen:

    xor     rax,rax

loop:
    cmp byte [rdi + rax], byte 0
    je end
    inc rax
    jmp loop

end:
    ret
