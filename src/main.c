/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 22:05:37 by iammar            #+#    #+#             */
/*   Updated: 2025/09/16 09:44:01 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	__exit(t_mlx_data *data)
{
	if (data)
	{
		if (data->img && data->mlx)
			mlx_destroy_image(data->mlx, data->img);
		if (data->win && data->mlx)
			mlx_destroy_window(data->mlx, data->win);
		if (data->mlx)
			mlx_destroy_display(data->mlx);
	}
	garbage_collect(NULL, EXIT_SUCCESS);
	return (0);
}

int	key_hook(int key_code, t_scene *scene)
{
	if (key_code == ESC)
		__exit(scene->data);
	return (0);
}

void	init_mlx(t_scene *scene)
{
	scene->data = malloc(sizeof(t_mlx_data));
	garbage_collect(scene->data, EXIT_FAILURE);
	ft_memset(scene->data, 0, sizeof(t_mlx_data));
	scene->data->mlx = mlx_init();
	garbage_collect(scene->data->mlx, EXIT_FAILURE);
	scene->data->win = mlx_new_window(scene->data->mlx, WIDTH, HEIGHT,
			"miniRT");
	scene->data->img = mlx_new_image(scene->data->mlx, WIDTH, HEIGHT);
	scene->data->addr = mlx_get_data_addr(scene->data->img,
			&scene->data->bits_per_pixel, &scene->data->line_length,
			&scene->data->endian);
	mlx_hook(scene->data->win, 17, 0, __exit, scene->data);
	mlx_key_hook(scene->data->win, key_hook, scene);
}

void	check_name(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i <= 3 || (i > 3 && ft_strcmp(str + i - 3, ".rt")) || str[i - 4] == '/')
	{
		fd_putstr(2, "Error:\n invalid file name\n");
		exit(1);
	}
}

int	main(int ac, char **av)
{
	t_scene	*scene;

	check_name(av[1]);
	scene = NULL;
	if (ac == 2)
	{
		scene = parse_file(av[1]);
		if (!scene)
			garbage_collect(NULL, EXIT_FAILURE);
		init_mlx(scene);
		render(scene);
		mlx_loop(scene->data->mlx);
	}
	else
	{
		fd_putstr(2, "Error:\n ./minirt 'a scene in format *.rt'\n");
		return (1);
	}
}
