/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammar <iammar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 20:36:24 by iammar            #+#    #+#             */
/*   Updated: 2025/09/22 12:57:05 by iammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	ambient(t_scene *scene, char **splitted)
{
	if (scene->ambient)
	{
		fd_putstr(2, "Error:\n Too many ambients\n");
		garbage_collect(NULL, EXIT_FAILURE);
	}
	scene->ambient = malloc(sizeof(t_ambient));
	garbage_collect(scene->ambient, EXIT_FAILURE);
	if (number_sp(splitted) != 3 || (ft_atoi(splitted[1]) > 1
			|| ft_atoi(splitted[1]) < 0))
	{
		fd_putstr(2, "Error\n: invalid ambient parameters!\n");
		garbage_collect(NULL, EXIT_FAILURE);
	}
	scene->ambient->intensity = ft_atoi(splitted[1]);
	scene->ambient->color = get_color(splitted[2]);
}

t_sphere	*spher(char **splitted)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	garbage_collect(sphere, EXIT_FAILURE);
	if (number_sp(splitted) != 4)
	{
		fd_putstr(2, "Error\n: invalid sphere parameters!\n");
		garbage_collect(NULL, EXIT_FAILURE);
	}
	sphere->center = get_cordinate(splitted[1]);
	sphere->diameter = ft_atoi(splitted[2]);
	sphere->color = get_color(splitted[3]);
	sphere->next = NULL;
	return (sphere);
}

t_plane	*plan(char **splitted)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	garbage_collect(plane, EXIT_FAILURE);
	if (number_sp(splitted) != 4)
	{
		fd_putstr(2, "Error\n: invalid plane parameters!\n");
		garbage_collect(NULL, EXIT_FAILURE);
	}
	plane->point = get_cordinate(splitted[1]);
	plane->normal = get_vector(splitted[2]);
	plane->color = get_color(splitted[3]);
	plane->next = NULL;
	check_direction(plane->normal);
	return (plane);
}

t_cylinder	*cylinde(char **splitted)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	garbage_collect(cylinder, EXIT_FAILURE);
	if (number_sp(splitted) != 6)
	{
		fd_putstr(2, "Error\n: invalid cylinder parameters!");
		garbage_collect(NULL, EXIT_FAILURE);
	}
	cylinder->center = get_cordinate(splitted[1]);
	cylinder->axis = get_vector(splitted[2]);
	cylinder->diameter = ft_atoi(splitted[3]);
	cylinder->height = ft_atoi(splitted[4]);
	cylinder->color = get_color(splitted[5]);
	cylinder->next = NULL;
	if (cylinder->axis->x < -1 || cylinder->axis->x > 1 || cylinder->axis->y < \
		-1 || cylinder->axis->y > 1 || cylinder->axis->z < -1
		|| cylinder->axis->z > 1)
	{
		fd_putstr(2, "Error\n: axis vector must be in range [-1,1]!\n");
		garbage_collect(NULL, EXIT_FAILURE);
	}
	return (cylinder);
}
