/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 20:07:23 by iammar            #+#    #+#             */
/*   Updated: 2025/08/23 16:30:14 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void light(t_scene *scene , char **splitted)
{
    scene->light = malloc(sizeof(t_light));
    garbage_collect(scene->light , EXIT_FAILURE);
    if(number_sp(splitted) != 4 || ft_atoi(splitted[2]) > 1 || ft_atoi(splitted[2]) < 0)
    {
       fd_putstr(2, "Error:\n invalid light parameter");
        garbage_collect(NULL , EXIT_FAILURE);
    }
    scene->light->position = get_cordinate(splitted[1]);
    scene->light->brightness = ft_atoi(splitted[2]);
    scene->light->color = get_color(splitted[3]);
}
