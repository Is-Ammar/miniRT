/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammar <iammar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 03:53:44 by iammar            #+#    #+#             */
/*   Updated: 2025/09/22 12:52:51 by iammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_cor	*get_cordinate(char *str)
{
	char	**cor;
	t_cor	*cordin;

	cordin = malloc(sizeof(t_cor));
	garbage_collect(cordin, EXIT_FAILURE);
	cor = ft_split(str, ',');
	if (number_sp(cor) != 3)
	{
		fd_putstr(2, "Error:\ninvalid cordinate parameter\n");
		garbage_collect(NULL, EXIT_FAILURE);
	}
	cordin->x = ft_atoi(cor[0]);
	cordin->y = ft_atoi(cor[1]);
	cordin->z = ft_atoi(cor[2]);
	return (cordin);
}

t_vector	*get_vector(char *str)
{
	t_vector	*vect;
	char		**vec;

	vect = malloc(sizeof(t_vector));
	garbage_collect(vect, EXIT_FAILURE);
	vec = ft_split(str, ',');
	if (number_sp(vec) != 3)
	{
		fd_putstr(2, "Error:\ninvalid vector parameter\n");
		garbage_collect(NULL, EXIT_FAILURE);
	}
	vect->x = ft_atoi(vec[0]);
	vect->y = ft_atoi(vec[1]);
	vect->z = ft_atoi(vec[2]);
	return (vect);
}

void	check_direction(t_vector *vector)
{
	if (fabs(vector->x) > 1 || fabs(vector->y) > 1 || fabs(vector->z) > 1)
	{
		fd_putstr(2, "Error:\n vector should be in range [-1, 1]\n");
		garbage_collect(NULL, EXIT_FAILURE);
	}
}

void	camera(t_scene *scene, char **splitted)
{
	if (scene->camera)
	{
		fd_putstr(2, "Error:\n Too many cameras\n");
		garbage_collect(NULL, EXIT_FAILURE);
	}
	scene->camera = malloc(sizeof(t_camera));
	garbage_collect(scene->camera, EXIT_FAILURE);
	if (number_sp(splitted) != 4)
	{
		fd_putstr(2, "Error:\ninvalid camera parameter\n");
		garbage_collect(NULL, EXIT_FAILURE);
	}
	scene->camera->position = get_cordinate(splitted[1]);
	scene->camera->direction = get_vector(splitted[2]);
	check_direction(scene->camera->direction);
	scene->camera->fov = ft_atoi(splitted[3]);
	scene->camera->plane_height = 0;
	scene->camera->plane_width = 0;
	if (scene->camera->fov > 180 || scene->camera->fov < 0)
	{
		fd_putstr(2, "Error:\ninvalid camera FOV\n");
		garbage_collect(NULL, EXIT_FAILURE);
	}
}
