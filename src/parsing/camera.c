/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 03:53:44 by iammar            #+#    #+#             */
/*   Updated: 2025/08/12 08:51:02 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_cor *get_cordinate(char *str)
{
    char **cor;
    t_cor *cordin = malloc(sizeof(t_cor));
    garbage_collect(cordin , EXIT_FAILURE);
    cor = ft_split(str, ',');
    if(number_sp(cor) != 3)
    {
        printf("error: values");//?
        garbage_collect(NULL , EXIT_FAILURE);
    }
    cordin->x = ft_atoi(cor[0]);
    cordin->y = ft_atoi(cor[1]);
    cordin->z = ft_atoi(cor[2]);
    return cordin;
}

t_vector *get_vector(char *str)
{
    t_vector *vect = malloc(sizeof(t_vector));
    garbage_collect(vect , EXIT_FAILURE);
    char **vec;
    vec = ft_split(str, ',');
    if(number_sp(vec) != 3)
    {
        printf("error: values"); //?
        garbage_collect(NULL , EXIT_FAILURE);
    }
    vect->x = ft_atoi(vec[0]);
    vect->y = ft_atoi(vec[1]);
    vect->z = ft_atoi(vec[2]);
    return vect;
}

void camera(t_scene *scene, char **splitted)
{
    scene->camera = malloc(sizeof(t_ambient));
    garbage_collect(scene->camera , EXIT_FAILURE);
    if(number_sp(splitted) != 4)
    {
        printf("error!"); ///?
        garbage_collect(NULL , EXIT_FAILURE);
    }
    scene->camera->position = get_cordinate(splitted[1]);
    scene->camera->direction = get_vector(splitted[2]);
    scene->camera->fov = atoi(splitted[3]);
}
