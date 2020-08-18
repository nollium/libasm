nasm -felf64 get_n.s
clang-9 -Wall -Wextra get_n.o driver.c -o program
