/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 09:57:17 by yel-alja          #+#    #+#             */
/*   Updated: 2025/09/09 18:48:44 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void    generate_ray(t_scene *scene, t_ray *ray, int x, int y)
{
        float u;
        float j;
        
        u = (x + 0.5) / WIDTH - 0.5;
        j = 0.5 -((y + 0.5) / HEIGHT);
        ray->vec = *(t_vec3 *)scene->camera->position;
        ray->dir = vec_add(vec_add(scene->camera->forward ,
                vec_scale(scene->camera->right_vec ,u)), vec_scale(scene->camera->up_vec , j));
        ray->dir = vec_nor(ray->dir);
}

void ray_tracer(t_scene *scene)
{
        int x = 0;
        int y = 0;
        t_ray ray;
        
        

        while(x < WIDTH)
        {
                y = 0;
                while(y < HEIGHT)
                {
                        generate_ray(scene, &ray, x, y);
                printf("%f\t%f\t%f\n" , ray.dir.x , ray.dir.y , ray.dir.z);
                        y++;
                }
                x++;
        } 
}