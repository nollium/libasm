# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/18 18:31:28 by user42            #+#    #+#              #
#    Updated: 2020/08/23 20:31:36 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = exe

ASM = nasm
CC = clang-9
CFLAGS = -Wall -Wextra -g3 

ASM_FORMAT = -felf64 -g

ASM_SRC = ft_strlen.s ft_strcpy.s ft_strcmp.s \
		  ft_write.s ft_read.s ft_strdup.s

C_SRC = driver.c

ASM_OBJ = $(ASM_SRC:.s=.o)

TRASH = log real_output ft_ouput

all: $(NAME)

$(NAME): $(ASM_OBJ) $(C_SRC)
		$(CC) $(CFLAGS) $(C_SRC) $(ASM_OBJ) -o $(NAME)

%.o: %.s
	$(ASM) $(ASM_FORMAT) $<

clean:
	rm -rf $(ASM_OBJ) $(TRASH)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY : clean fclean re