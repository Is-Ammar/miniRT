/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammar <iammar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 00:40:58 by iammar            #+#    #+#             */
/*   Updated: 2025/09/22 12:49:06 by iammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void check_dot(char *str)
{
	int i = 0;
	int count_dot = 0;

	while (str[i])
	{
		if (str[i] == '.')
			count_dot++;
		i++;
	}
	if (count_dot > 1)
	{
		fd_putstr(2, "Error:\n values\n");
		garbage_collect(NULL, EXIT_FAILURE);
	}
}

void	ft_isnum(char *str)
{
	int	i;

	check_dot(str);
	i = 0;
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.' || str[i] == '-')
			i++;
		else
		{
			fd_putstr(2, "Error:\n values\n");
			garbage_collect(NULL, EXIT_FAILURE);
		}
	}
}

float	ft_atoi(char *str)
{
	t_atoi	strr;

	strr = (t_atoi){1, 0, 0, 1};
	ft_isnum(str);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			strr.s = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		strr.r = strr.r * 10 + (*str++ - '0');
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			strr.f = strr.f * 10 + (*str++ - '0');
			strr.d *= 10;
		}
	}
	return (strr.s * (strr.r + strr.f / strr.d));
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n--)
	{
		*ptr++ = (unsigned char)c;
	}
	return (s);
}
