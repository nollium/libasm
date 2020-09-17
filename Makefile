# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/18 18:31:28 by user42            #+#    #+#              #
#    Updated: 2020/09/07 18:11:35 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libasm.a
EXE=exe

ASM = nasm
CC = clang-9
LIBMAKER = ar rcs
CFLAGS = -Wall -Wextra -g3 

ASM_FORMAT = -felf64 -g

ASM_SRC = ft_strlen.s ft_strcpy.s ft_strcmp.s \
		  ft_write.s ft_read.s ft_strdup.s

C_SRC = main.c

ASM_OBJ = $(ASM_SRC:.s=.o)

TRASH = log real_output ft_ouput

all: $(NAME)

$(NAME): $(ASM_OBJ) $(ASM_SRC)
		$(LIBMAKER) $(NAME) $(ASM_OBJ)


$(EXE): $(C_SRC) $(NAME)
	$(CC) $(CFLAGS) $(C_SRC) $(ASM_OBJ) -o $(EXE)


run: $(NAME) $(EXE)


%.o: %.s
	$(ASM) $(ASM_FORMAT) $<

clean:
	rm -rf $(ASM_OBJ) $(TRASH)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(EXE)

re: fclean all

.PHONY : clean fclean re