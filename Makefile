# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/18 18:31:28 by user42            #+#    #+#              #
#    Updated: 2020/08/18 18:41:25 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = exe

ASM = nasm
CC = clang-9
CFLAGS = -Wall -Wextra

ASM_FORMAT = -felf64

ASM_SRC = get_n.s ft_strlen.s

C_SRC = driver.c

ASM_OBJ = $(ASM_SRC:.s=.o)


all: $(NAME)

$(NAME): $(ASM_OBJ) $(C_SRC)
		$(CC) $(C_SRC) $(ASM_OBJ) -o $(NAME)

%.o: %.s
	$(ASM) $(ASM_FORMAT) $<

clean:
	rm -rf $(ASM_OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY : clean fclean re