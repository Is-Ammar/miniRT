/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammar <iammar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:44:31 by iammar            #+#    #+#             */
/*   Updated: 2025/09/22 12:51:35 by iammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	sphere_back(t_sphere **sphere, t_sphere *new)
{
	t_sphere	*tmp;

	if ((*sphere) == NULL)
		(*sphere) = new;
	else
	{
		tmp = (*sphere);
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
	}
}

void	plane_back(t_plane **plane, t_plane *new)
{
	t_plane	*tmp;

	if ((*plane) == NULL)
		(*plane) = new;
	else
	{
		tmp = *plane;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
	}
}

void	cylinder_back(t_cylinder **cylinder, t_cylinder *new)
{
	t_cylinder	*tmp;

	if ((*cylinder) == NULL)
		(*cylinder) = new;
	else
	{
		tmp = *cylinder;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
	}
}

void	fd_putstr(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
}
