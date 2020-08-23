/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 14:44:48 by user42            #+#    #+#             */
/*   Updated: 2020/08/23 14:28:57 by user42           ###   ########.fr       */
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
#define READ_SIZE	256

#define TEST(test, ...) (test(__VA_ARGS__) == SUCCESS_CODE) ? fprintf(stdout, "%sl:%d| %s(%s): [%s]\n%s", GREEN, __LINE__, #test, #__VA_ARGS__, "OK", RESET) : \
fprintf(stderr,"%sl:%d| %s(%s): [%s]\n%s", RED, __LINE__, #test, #__VA_ARGS__, "KO", RESET)

#define TEST_TXT "bible"

char    *strings[] = {"ABCDEF", "Hello World!", "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
					"BBBBBBBBB", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "\n\n\n\n\n\n\n\n\n", "", "\0\0\0\0\0\0\0\0\0\0",
					"\\\\\\\\\\\\", "\"\"\"\"\'\'\'\'''", "", "a", 0};
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

int     ft_strcmp(const char *s1, const char *s2)
/*
{
        int		res;
        size_t  i;

        i = 0;
        res = 0;
        while (res == 0)
        {
                if (s1[i] == 0 && s2[i] == 0)
                        return (0);
                res = (unsigned char)s1[i] - (unsigned char)s2[i];
                i++;
        }
        return (res);
}
*/
;

int	strlen_cmp(char *arg)
{
	int		real_ret;
	int		ft_ret;
	
	real_ret = strlen(arg);
	ft_ret = ft_strlen(arg);
	if (real_ret != ft_ret)
	{
		fprintf(stderr, RED "[STRLEN] ERROR : [%s]\nSTRLEN: %d\nFT_STRLEN: %d\n" RESET,
				arg, real_ret, ft_ret);
		return (1);
	}
	return (0);
}

int	strcpy_cmp(char *arg)
{
	size_t	len;
	char	*real_dst;
	char	*ft_dst;
	char	*ret;
	size_t	i;

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
		fprintf(stderr, RED "[STRCPY] RETURN ERROR [%s][%p]: FT:%p REAL %p\n" RESET,
		arg, arg, ret, ft_dst);
		return (1);
	}
	
	if (strcmp(real_dst, ft_dst))
	{
		fprintf(stderr, RED "[STRCPY] ERROR [%s]: STRCPY: [%s] FT_STRCPY: [%s]\n" RESET,
				arg, real_dst, ft_dst);
		return (1);
	}
	return (0);
}

int	strcmp_cmp(char *arg)
{
	static char	*arg_0 = NULL;
	int		real_ret;
	int		ft_ret;
	int 	error;

	error = 0;
	if (!arg)
		return (SUCCESS_CODE);
	if (!arg_0)
		arg_0 = strdup(arg);
	real_ret = strcmp(arg, arg_0);
	ft_ret = ft_strcmp(arg, arg_0);
	if ((error |= (real_ret != ft_ret)))
		fprintf(stderr, RED "[STRCMP] ERROR (%s, %s): STRCMP: [%d] FT_STRCMP: [%d]\n" RESET, arg, arg_0, real_ret, ft_ret);
	real_ret = strcmp(arg_0, arg);
	ft_ret = ft_strcmp(arg_0, arg);
	if ((error |= (real_ret != ft_ret)))
		fprintf(stderr, RED "[STRCMP] ERROR (%s, %s): STRCMP: [%d] FT_STRCMP: [%d]\n" RESET, arg_0, arg, real_ret, ft_ret);
	return (error);
}

int	str_test(int (*test)(char *))
{
	int 	i;
	char	ascii[CHAR_MAX + 1];
	char	rd_buff[READ_SIZE + 1];
	int		fd;
	int 	err;
	char	**split;

	split = strings;
	i = -1;
	err = 0;
	while (split[++i])
		err |= test(split[i]);
	i = -1;
	while (++i < CHAR_MAX)
		ascii[i] = i + 1;
	ascii[i] = 0;
	err |= test(ascii);
	fd = open(TEST_TXT, O_RDONLY);
	while (read(fd, rd_buff, READ_SIZE) > 0)
	{
		rd_buff[READ_SIZE] = 0;
		err |= test(rd_buff);
	}
	close(fd);
	return (err);
}

void print_shit(char *a, char *b, int c)
{
	printf("/******************\\\n");
	printf("|    a: %s          |\n", a);
	printf("|    b: %s          |\n", b);
	printf("|    c: %d          |\n", c);
	printf("\\******************/\n");
}

int main(void)
{
	//TEST(str_test, strlen_cmp);
	//TEST(str_test, strcpy_cmp);
	TEST(str_test, strcmp_cmp);
	//printf("%d %d\n", strcmp("1", "1"), ft_strcmp("12", "12"));
	printf(MAGENTA"%d\n"RESET, get_n());
	//printf("%zu\n", ft_strlen("012345"));
	return (0);
}
