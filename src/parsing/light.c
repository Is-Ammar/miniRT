/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammar <iammar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 20:07:23 by iammar            #+#    #+#             */
/*   Updated: 2025/08/02 20:07:55 by iammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void light(t_scene *scene , char **splitted)
{
    scene->light = malloc(sizeof(t_light));
    if(number_sp(splitted) != 4)
    {
        printf("error!");
        exit(1);
    }
    scene->light->coordinate = get_cordinate(splitted[1]);
    scene->light->brightness = ft_atoi(splitted[2]);
    scene->light->color = get_color(splitted[3]);
}
