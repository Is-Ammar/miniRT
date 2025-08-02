/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammar <iammar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 03:38:14 by iammar            #+#    #+#             */
/*   Updated: 2025/08/02 03:50:47 by iammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

char *gnl(int fd)
{
    static int pos;
    static int r;
    static char buffer[4096];
    char line[4096];
    int i =0;

    while(1)
    {
        if(pos >= r)
        {
            r = read(fd, buffer, 4096);
            pos = 0;
            if(r <= 0)
                break;
            }
            line[i++] = buffer[pos++];
            if(line[i - 1] == '\n')
                break;
    }
    line[i] = '\0';
    if(i == 0)
        return NULL;
    return ft_strdup(line);
}

size_t ft_strlen(char *str)
{
    size_t i = 0;
    while(str[i])
    {
        i++;
    }
    return i;
}

size_t	ft_strlcpy(char *dst,char *src, size_t len)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (len == 0)
		return (src_len);
	i = 0;
	while (src[i] && i < len - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

char	*ft_strdup(char *src)
{
	char	*new;
	size_t	size;

	size = ft_strlen(src);
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	ft_strlcpy(new, src, size + 1);
	return (new);
}

int number_sp(char **splitted)
{
    int i =0;
    while(splitted[i])
    {
        i++;
    }
    return(i);
}
