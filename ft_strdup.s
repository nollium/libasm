global  ft_strdup

extern malloc
extern ft_strlen
extern ft_strcpy

ft_strdup:
    call ft_strlen; rax = strlen(arg)
    push rbx
    mov rbx,rdi; r9 = arg
    mov r8,rax; r8 = len
    mov rdi,rax; rdi = len
    call malloc; rax = malloc(len)
    mov rdi,rax; s1 = rax
    mov rsi,rbx; s2 = arg
    call ft_strcpy; return (ft_strcpy(s1,s2))
    pop rbx
    ret