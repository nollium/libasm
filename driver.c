/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 14:44:48 by user42            #+#    #+#             */
/*   Updated: 2020/08/18 17:46:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stddef.h>

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

#define TEST(test, ...) (test(__VA_ARGS__) == SUCCESS_CODE) ? printf("%s%s (l:%d): [%s]\n%s", GREEN, #test, __LINE__, "OK", RESET) : printf("%s%s (l:%d): [%s]\nARGS : " #__VA_ARGS__ "\n%s", RED, #test, __LINE__, "KO", RESET)

char    *strings[] = {"ABCDEF", "Hello World!", "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
					"BBBBBBBBB", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "\n\n\n\n\n\n\n\n\n", "", "\0\0\0\0\0\0\0\0\0\0",
					"\\\\\\\\\\\\", "\"\"\"\"\'\'\'\'''"};

int	ft_strlen(char *str)
{
	(void)str;
	return(0);
}

int strlen_test(char **split)
{
	int 	i;
	int		real_ret;
	int		ft_ret;

	i = -1;
	while (split[++i])
	{
		real_ret = strlen(strings[i]);
		ft_ret = ft_strlen(strings[i]);
		if (real_ret != ft_ret)
		{
			printf(RED "[STRLEN] ERROR : [%s]\nSTRLEN: %d\nFT_STRLEN: %d\n" RESET,
					split[i], real_ret, ft_ret);
			return (1);
		}
	}
	return (0);
}

extern int get_n();

int main(void)
{
	//TEST(strlen_test, strings);
	printf("%d\n", get_n());
	return (0);
}
