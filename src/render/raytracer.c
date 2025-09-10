/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammar <iammar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 09:57:17 by yel-alja          #+#    #+#             */
/*   Updated: 2025/09/10 20:52:42 by iammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_ray generate_ray(t_scene *scene , int x , int y)
{
        t_ray ray;
        
        float u = ((x + 0.5) / WIDTH  - 0.5f) * scene->camera->plane_width;
        float v = (0.5f - (y + 0.5 ) / HEIGHT) * scene->camera->plane_height;

        
        ray.vec = *((t_vec3 *)scene->camera->position);
        ray.dir = vec3_normalize(vec3_add(vec3_add(*(scene->camera->direction), 
                                          vec3_scale(scene->camera->right_vec, u)), 
                                          vec3_scale(scene->camera->up_vec, v)));
        return ray;
}

t_hit trace_ray(t_scene *scene, t_ray ray)
{
        t_hit hit;
        t_sphere *sph = scene->sphere;
        t_plane *pln = scene->plane;
        t_cylinder *cldr = scene->cylinder;
        
        while(sph)
        {
                sphere_intersect(sph, &hit);
                sph = sph->next;
        }
        
        
}

void ray_tracer(t_scene *scene)
{
        int x = 0;
        int y = 0;
        t_ray ray;
        t_hit hit;
        
        
        put_camera(scene->camera);
        while(y < HEIGHT)
        {
                x = 0;
                while(x < WIDTH)
                {
                        ray = generate_ray(scene , x , y);
                        hit = trace_ray(scene, ray);
                        x++;
                }
                y++;
        } 
}
