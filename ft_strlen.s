global ft_strlen

section .text:

    ft_strlen:

        xor     rax,rax

    loop:
        cmp byte [rdi + rax], byte 0
        je end
        inc rax
        jmp loop

    end:
        ret
