#!/bin/bash -ex
nasm -felf64 get_n.s
nasm -felf64 ft_strlen.s
clang-9 -Wall -Wextra get_n.o ft_strlen.o driver.c -o program
