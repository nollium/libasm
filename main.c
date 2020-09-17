/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 14:44:48 by user42            #+#    #+#             */
/*   Updated: 2020/09/07 18:04:31 by user42           ###   ########.fr       */
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
#include <errno.h>

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
#define READ_SIZE	1024

#define TEST(test) (test == SUCCESS_CODE) ? \
fprintf(stdout, "%s%s |l:%d| %s\n%s", GREEN, "[OK]", __LINE__, #test , RESET) : \
fprintf(stderr, "%s%s |l:%d| %s\n%s", RED, "[KO]", __LINE__, #test, RESET)

#define TEST_TXT "bible"

char    *strings[] = {"ABCDEF", "Hello World!", "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
					"BBBBBBBBB", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "\n\n\n\n\n\n\n\n\n", "", "\0\0\0\0\0\0\0\0\0\0",
					"\\\\\\\\\\\\", "\"\"\"\"\'\'\'\'''", "", "", "a", "a", "AAA", "AAA", "AAA", 0};
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

ssize_t ft_write(int fd, const void *buf, size_t n)
/*
{
	return (write(fd, buf, n));
}
*/
;

ssize_t ft_read(int fd, void *buf, size_t n)
/*
{
	return (read(fd, buf, n));
}
*/
;

char	*ft_strdup(const char *s)
/*
{
	return(strdup(s));
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

int		tst_write(char *filename, char *src, char **dst,
ssize_t (*func)(int fd, const void *, size_t))
{
	char	*buf;
	int		error;
	size_t	len;
	int		fd;

	len =  strlen(src);
	buf = calloc(1, len + 1);
	fd = open(filename, O_RDWR | O_CREAT, 0664);
	error = func(fd, src, len);
	close(fd);
	fd = open(filename, O_RDWR | O_CREAT, 0664);
	read(fd, buf, len);
	close(fd);
	*dst = buf;
	return (error);
}

int		write_cmp(char *arg)
{
	char	*ft;
	char	*real;
	int		ft_error;
	int		real_error;
	int		error;
	int		ft_errno;
	int		real_errno;

	errno = -777;
	error = SUCCESS_CODE;
	real_error = tst_write("real_output", arg, &real, write);
	real_errno = errno;
	errno = -777;
	ft_error = tst_write("ft_ouput", arg, &ft, ft_write);
	ft_errno = errno;
	errno = -777;
	if (real_errno != ft_errno)
	{
		error = 1;
		fprintf(stderr, RED "[WRITE] ERRMO ERROR (%s): WRITE: [%d]\
		 FT_WRITE: [%d]\n" RESET, arg, real_errno, ft_errno);
	}
	if (real_error != ft_error)
	{
		error = 1;
		fprintf(stderr, RED "[WRITE] RETURN ERROR (%s): WRITE: [%d]\
		 FT_WRITE: [%d]\n" RESET, arg, real_error, ft_error);
	}
	if (strcmp(real, ft))
	{
		fprintf(stderr, RED "[WRITE] ERROR (%s): WRITE: [%s] FT_WRITE: [%s]\n" RESET, arg, real, ft);
		error = 1;
	}
	return (error);
}

int		tst_read(char *filename, char *src, char **dst,
ssize_t (*func)(int fd, void *, size_t))
{
	char	*buf;
	int		error;
	size_t	len;
	int		fd;

	len =  strlen(src);
	buf = calloc(1, len + 1);
	fd = open(filename, O_RDWR | O_CREAT, 0664);
	write(fd, src, len);
	close(fd);
	fd = open(filename, O_RDWR | O_CREAT, 0664);
	error = func(fd, buf, len);
	close(fd);
	*dst = buf;
	return (error);
}

int		read_cmp(char *arg)
{
	char	*ft;
	char	*real;
	int		ft_error;
	int		real_error;
	int		error;
	int		ft_errno;
	int		real_errno;
	
	error = SUCCESS_CODE;
	errno = -777;
	real_error = tst_read("real_output", arg, &real, read);
	real_errno = errno;
	errno = -777;
	ft_error = tst_read("ft_ouput", arg, &ft, ft_read);
	ft_errno=errno;
	errno = -777;
	if (real_errno != ft_errno)
	{
		error = 1;
		fprintf(stderr, RED "[READ] ERRMO ERROR (%s): READ: [%d]\
		 FT_READ: [%d]\n" RESET, arg, real_errno, ft_errno);
	}
	if (real_error != ft_error)
	{
		error = 1;
		fprintf(stderr, RED "[READ] RETURN ERROR (%s): READ: [%d]\
		 FT_READ: [%d]\n" RESET, arg, real_error, ft_error);
	}
	if (strcmp(real, ft))
	{
		fprintf(stderr, RED "[READ] ERROR (%s): READ: [%s] FT_READ: [%s]\n" RESET, arg, real, ft);
		error = 1;
	}
	return (error);
}

int		file_test(ssize_t (*real_funct)(), ssize_t (*ft_funct)())
{
	int	error = SUCCESS_CODE;
	int real_error;
	int	ft_error;
	int	real_errno;
	int	ft_errno;
	char	*buf;
	int		fd;
	
	buf = malloc(200);
	fd = open("./", O_RDONLY);
	errno = -8888;
	real_error = real_funct(fd, buf + 100, -42);
	real_errno = errno;
	errno = -8888;
	close(fd);
	fd = open("./", O_RDONLY);
	ft_error = ft_funct(fd, buf + 100, -42);
	ft_errno = errno;
	errno = -8888;
	close(fd);
	if ((error |= (ft_errno != real_errno)))
		fprintf(stderr, RED "[FILE] l:%d ERRNO ERROR (%s): REAL: [%d]\
		 FT: [%d]\n" RESET, __LINE__, "n=-42", real_errno, ft_errno);	
	if (real_error != ft_error && (error=1))
		fprintf(stderr, RED "[FILE] RETURN ERROR (%s): REAL: [%d]\
		 FT: [%d]\n" RESET, "n=-42", real_error, ft_error);
	free(buf);
	return (error);
}

int	strdup_cmp(char *arg)
{
	char	*dup;

	dup = ft_strdup(arg);
	if (!dup)
		return (1);
	if (strcmp(arg,dup))
	{
		fprintf(stderr, "%s[STRDUP] ERROR: REAL [%s] FT_STRDUP [%s]\n%s",
		RED, arg, dup, RESET);
		return (1);
	}
	return (SUCCESS_CODE);
}

int main(void)
{
	errno=0;
	TEST(str_test(strlen_cmp));
	TEST(str_test(strcpy_cmp));
	TEST(str_test(strcmp_cmp));
	TEST(str_test(write_cmp));
	TEST(file_test(write, ft_write));
	TEST(str_test(read_cmp));
	TEST(file_test(read, ft_read));
	TEST(str_test(strdup_cmp));
	return (0);
}
