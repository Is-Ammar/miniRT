/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammar <iammar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 03:39:51 by iammar            #+#    #+#             */
/*   Updated: 2025/09/22 13:04:12 by iammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_color	*get_color(char *str)
{
	char	**rgb;
	t_color	*color;

	color = malloc(sizeof(t_color));
	garbage_collect(color, EXIT_FAILURE);
	rgb = ft_split(str, ',');
	if (number_sp(rgb) != 3)
	{
		fd_putstr(2, "Error:\n invalid color values\n");
		garbage_collect(NULL, EXIT_FAILURE);
	}
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	if (color->r > 255 || color->r < 0 || color->b > 255 || color->b < 0
		|| color->g > 255 || color->g < 0)
	{
		fd_putstr(2, "Error:\n invalid color values\n");
		garbage_collect(NULL, EXIT_FAILURE);
	}
	return (color);
}

static void	check_if(t_scene *scene, char **splitted, int *result)
{
	if (ft_strcmp(splitted[0], "A") == 0)
		ambient(scene, splitted);
	else if (ft_strcmp(splitted[0], "C") == 0)
		camera(scene, splitted);
	else if (ft_strcmp(splitted[0], "L") == 0)
		light(scene, splitted);
	else if (ft_strcmp(splitted[0], "sp") == 0)
		sphere_back(&scene->sphere, spher(splitted));
	else if (ft_strcmp(splitted[0], "pl") == 0)
		plane_back(&scene->plane, plan(splitted));
	else if (ft_strcmp(splitted[0], "cy") == 0)
		cylinder_back(&scene->cylinder, cylinde(splitted));
	else
	{
		fd_putstr(2, "Error:\ninvalid identifier!\n");
		*result = false;
	}
}

static int	parse_line(t_scene *scene, char *line)
{
	char	**splitted;
	int		result;

	result = true;
	if (!line || !scene)
		return (false);
	splitted = ft_split(line, ' ');
	if (!splitted)
		return (false);
	if (!splitted[0])
		return (true);
	check_if(scene, splitted, &result);
	return (result);
}

t_scene	*parse_file(char *file)
{
	int		fd;
	char	*line;
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	garbage_collect(scene, EXIT_FAILURE);
	ft_memset(scene, 0, sizeof(t_scene));
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		fd_putstr(2, "Error:\n open faild\n");
		garbage_collect(NULL, EXIT_FAILURE);
	}
	line = gnl(fd);
	while (line)
	{
		if (!parse_line(scene, line))
			garbage_collect(NULL, EXIT_FAILURE);
		line = gnl(fd);
	}
	if (!scene || !scene->camera || !scene->ambient || !scene->light)
		(fd_putstr(2, "Error:\n invalid scene\n"), \
		garbage_collect(NULL, EXIT_FAILURE));
	return (scene);
}
