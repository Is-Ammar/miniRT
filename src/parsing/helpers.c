/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammar <iammar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 00:40:58 by iammar            #+#    #+#             */
/*   Updated: 2025/08/02 04:11:12 by iammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	ft_isnum(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.' || str[i] == '-')
			i++;
		else
			return (1);
	}
	return (0);
}

float	ft_atoi(const char *str)
{
	t_atoi	strr;

	strr = (t_atoi){0};
	strr.d = 1;
	strr.s = 1;
	if (ft_isnum(str))
		{
			printf("error: values\n");
			exit(1);
		}
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

int	ft_strcmp(char *s1,char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
