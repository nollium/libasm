/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 14:44:48 by user42            #+#    #+#             */
/*   Updated: 2020/08/19 15:57:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#define BLACK	 	"\e[30m"
#define RED 		"\e[31m"
#define GREEN 		"\e[32m"
#define YELLOW 		"\e[33m"
#define BLUE 		"\e[34m"
#define MAGENTA 	"\e[35m"
#define CYAN 		"\e[36m"
#define WHITE 		"\e[37m"
#define RESET 		"\e[0m"

#define SUCCESS_CODE 0
#define READ_SIZE	4096

#define TEST(test, ...) (test(__VA_ARGS__) == SUCCESS_CODE) ? printf("%s%s (l:%d): [%s]\n%s", GREEN, #test, __LINE__, "OK", RESET) : printf("%s%s (l:%d): [%s]\nARGS : " #__VA_ARGS__ "\n%s", RED, #test, __LINE__, "KO", RESET)

#define TEST_TXT "bible"

char    *strings[] = {"ABCDEF", "Hello World!", "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
					"BBBBBBBBB", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "\n\n\n\n\n\n\n\n\n", "", "\0\0\0\0\0\0\0\0\0\0",
					"\\\\\\\\\\\\", "\"\"\"\"\'\'\'\'''"};

int		get_n();
size_t	ft_strlen(const char *str);

char 	*ft_strcpy(char *dest, const char *src)
/*{
	int	i;

	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = src[i];
	return (dest);
}*/;

int	strlen_cmp(char *arg)
{
	int		real_ret;
	int		ft_ret;
	
	real_ret = strlen(arg);
	ft_ret = ft_strlen(arg);
	if (real_ret != ft_ret)
	{
		printf(RED "[STRLEN] ERROR : [%s]\nSTRLEN: %d\nFT_STRLEN: %d\n" RESET,
				arg, real_ret, ft_ret);
		return (1);
	}
	return (0);
}

int strlen_test(char **split)
{
	int 	i;
	char	ascii[CHAR_MAX + 1];
	char	rd_buff[READ_SIZE + 1];
	int		fd;
	int 	err;

	i = -1;
	err = 0;
	while (split[++i])
		err |= strlen_cmp(split[i]);
	i = -1;
	while (++i < CHAR_MAX)
		ascii[i] = i + 1;
	ascii[i] = 0;
	err |= strlen_cmp(ascii);
	fd = open(TEST_TXT, O_RDONLY);
	while (read(fd, rd_buff, READ_SIZE) > 0)
	{
		rd_buff[READ_SIZE] = 0;
		err |= strlen_cmp(rd_buff);
	}
	close(fd);
	return (err);
}

int	strcpy_cmp(char *arg)
{
	size_t	len;
	char	*real_dst;
	char	*ft_dst;
	char	*ret;
	int		i;

	len = strlen(arg);
	real_dst = malloc(len + 1);
	ft_dst = malloc(len + 1);
	i = -1;
	while (++i <= len)
	{
		real_dst[i] = (char)(i ^ (i << 15) ^ ((long long int) i << 30));
		ft_dst[i] = real_dst[i];
	}
	strcpy(real_dst, arg);
	ret = ft_strcpy(ft_dst, arg);
	if (ret != ft_dst)
	{
		printf(RED "[STRCPY] RETURN ERROR [%s][%p]: FT:%p REAL %p\n" RESET,
		arg, arg, ret, ft_dst);
		return (1);
	}
	
	if (strcmp(real_dst, ft_dst))
	{
		printf(RED "[STRCPY] ERROR [%s]: STRCPY: [%s] FT_STRCPY: [%s]\n" RESET,
				arg, real_dst, ft_dst);
		return (1);
	}
	return (0);
}

int	strcpy_test(char **split)
{
	int 	i;
	char	ascii[CHAR_MAX + 1];
	char	rd_buff[READ_SIZE + 1];
	int		fd;
	int 	err;

	i = -1;
	err = 0;
	while (split[++i])
		err |= strcpy_cmp(split[i]);
	i = -1;
	while (++i < CHAR_MAX)
		ascii[i] = i + 1;
	ascii[i] = 0;
	err |= strcpy_cmp(ascii);
	fd = open(TEST_TXT, O_RDONLY);
	while (read(fd, rd_buff, READ_SIZE) > 0)
	{
		rd_buff[READ_SIZE] = 0;
		err |= strcpy_cmp(rd_buff);
	}
	close(fd);
	return (err);
}

int main(void)
{
	TEST(strlen_test, strings);
	TEST(strcpy_test, strings);
	printf(MAGENTA"%d\n"RESET, get_n());
	//printf("%zu\n", ft_strlen("012345"));
	return (0);
}
