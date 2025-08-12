/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 20:36:24 by iammar            #+#    #+#             */
/*   Updated: 2025/08/10 20:44:54 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void ambient(t_scene *scene,char **splitted)
{
    scene->ambient = malloc(sizeof(t_ambient));
    garbage_collect(scene->ambient , EXIT_FAILURE);
    if(number_sp(splitted) != 3)
    {
        printf("error: invalid ambient parameters!\n");
        garbage_collect(NULL , EXIT_FAILURE);
    }
    scene->ambient->ambience = ft_atoi(splitted[1]);
    scene->ambient->color = get_color(splitted[2]);
}

void spher(t_scene *scene, char **splitted)
{
    scene->sphere = malloc(sizeof(t_sphere));
    garbage_collect(scene->sphere , EXIT_FAILURE);
    if (number_sp(splitted) != 4)
    {
        printf("error: invalid sphere parameters!\n");
        garbage_collect(NULL , EXIT_FAILURE);
    }
    scene->sphere->coordinate = get_cordinate(splitted[1]);
    scene->sphere->diameter = ft_atoi(splitted[2]);
    scene->sphere->color = get_color(splitted[3]);
}

void plan(t_scene *scene, char **splitted)
{
    scene->plane = malloc(sizeof(t_plane));
    garbage_collect(scene->plane , EXIT_FAILURE);
    if (number_sp(splitted) != 4)
    {
        printf("error: invalid plane parameters!\n");
         garbage_collect(NULL , EXIT_FAILURE);
    }
    scene->plane->coordinate = get_cordinate(splitted[1]);
    scene->plane->vector = get_vector(splitted[2]);
    scene->plane->color = get_color(splitted[3]);

    if (scene->plane->vector->x < -1 || scene->plane->vector->x > 1 || 
        scene->plane->vector->y < -1 || scene->plane->vector->y > 1 || 
        scene->plane->vector->z < -1 || scene->plane->vector->z > 1)
    {
        printf("error: normal vector must be in range [-1,1]!\n");
         garbage_collect(NULL , EXIT_FAILURE);
    }
}

void cylinde(t_scene *scene, char **splitted)
{
    scene->cylinder = malloc(sizeof(t_cylinder));
    garbage_collect(scene->cylinder , EXIT_FAILURE);
    if (number_sp(splitted) != 6)
    {
        printf("error: invalid cylinder parameters!");
        garbage_collect(NULL , EXIT_FAILURE);
    }
    scene->cylinder->coordinate = get_cordinate(splitted[1]);
    scene->cylinder->vector = get_vector(splitted[2]);
    scene->cylinder->diameter = ft_atoi(splitted[3]);
    scene->cylinder->height = ft_atoi(splitted[4]);
    scene->cylinder->color = get_color(splitted[5]);
    if (scene->cylinder->vector->x < -1 || scene->cylinder->vector->x > 1 || 
        scene->cylinder->vector->y < -1 || scene->cylinder->vector->y > 1 || 
        scene->cylinder->vector->z < -1 || scene->cylinder->vector->z > 1)
    {
        printf("error: axis vector must be in range [-1,1]!\n");
        garbage_collect(NULL , EXIT_FAILURE);
    }
}
