/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammar <iammar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 22:05:37 by iammar            #+#    #+#             */
/*   Updated: 2025/08/03 14:34:00 by iammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int __exit(t_mlx_data *data)
{
    if (data)
    {
        if (data->img && data->mlx)
            mlx_destroy_image(data->mlx, data->img);
        if (data->win && data->mlx)
            mlx_destroy_window(data->mlx, data->win);
        if (data->mlx)
        {
            mlx_destroy_display(data->mlx);
            free(data->mlx);
        }
        free(data);
    }
    exit(0);
}

int	key_hook(int key_code, t_mlx_data *data)
{
	if (key_code == ESC)
		__exit(data);
	return (0);
}

void init_mlx(t_mlx_data *data)
{
    data = malloc(sizeof(t_mlx_data));
    memset(data, 0, sizeof(t_mlx_data));
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
    mlx_key_hook(data->win, key_hook, data);
    mlx_hook(data->win, 17, 0, __exit, data);
    mlx_loop(data->mlx);
}
int main(int ac , char **av)
{
    t_scene *scene = NULL;
    t_mlx_data *data = NULL;;
    if(ac == 2)
    {
        scene = parse_file(av[1]);
    }
    init_mlx(data);
    // render(data);
}
