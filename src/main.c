/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammar <iammar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 22:05:37 by iammar            #+#    #+#             */
/*   Updated: 2025/08/02 20:57:00 by iammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void init_mlx(t_mlx_data *data)
{
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, data->line_length, &data->endian);
}
int main(int ac , char **av)
{
    t_scene *scene = NULL;
    t_mlx_data *data;
    if(ac == 2)
    {
        scene = parse_file(av[1]);
    }
    init_mlx(data);
}
