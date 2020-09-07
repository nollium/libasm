global  ft_strdup

extern malloc
extern ft_strlen
extern ft_strcpy

ft_strdup:
    push rdi;       push arg to stack
    call ft_strlen; rax = strlen(arg)
    mov rdi,rax;    rdi = len
    call malloc;    rax = malloc(len)
    mov rdi,rax;    s1 = rax
    pop rsi;        s2 = arg from stack
    call ft_strcpy; return (ft_strcpy(s1,s2))
    ret