/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 20:07:23 by iammar            #+#    #+#             */
/*   Updated: 2025/08/12 08:51:31 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void light(t_scene *scene , char **splitted)
{
    scene->light = malloc(sizeof(t_light));
    garbage_collect(scene->light , EXIT_FAILURE);
    if(number_sp(splitted) != 4)
    {
        printf("error!");
        garbage_collect(NULL , EXIT_FAILURE);
    }
    scene->light->position = get_cordinate(splitted[1]);
    scene->light->brightness = ft_atoi(splitted[2]);
    scene->light->color = get_color(splitted[3]);
}
