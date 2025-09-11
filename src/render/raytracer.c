/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammar <iammar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 09:57:17 by yel-alja          #+#    #+#             */
/*   Updated: 2025/09/11 20:27:57 by iammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_ray generate_ray(t_scene *scene , int x , int y)
{
        t_ray ray;
        
        float u = ((x + 0.5) / WIDTH  - 0.5) * scene->camera->plane_width;
        float v = (0.5 - (y + 0.5 ) / HEIGHT) * scene->camera->plane_height;

        
        ray.vec = *((t_vec3 *)scene->camera->position);
        ray.dir = vec3_normalize(vec3_add(vec3_add(*(scene->camera->direction), 
                                          vec3_scale(scene->camera->right_vec, u)), 
                                          vec3_scale(scene->camera->up_vec, v)));
        return ray;
}

void sphere_intersect(t_sphere *sphere, t_hit *hit, t_ray *ray)
{
        t_vec3 oc = vec3_sub(ray->vec, (t_vec3)(*sphere->center));
        float a = vec3_dot(ray->dir, ray->dir);
        float b = 2 * vec3_dot(ray->dir, oc);
        float c = vec3_dot(oc, oc) - sphere->diameter * sphere->diameter / 4;
        
        float delta = b * b - 4 * a * c;
        float x;
        if (delta < 0)
             return;
        if(delta > 0)
        {
        float x1 = (-b - sqrt(delta)) / (2 * a);
        float x2 = (-b + sqrt(delta)) / (2 * a);
        if(x1 > x2)
                x = x2;
        else 
                x = x1;
        }
        else 
                x = -b / 2 * a;
                
        hit->hit = 1;
        hit->distance = x;
        hit->point = vec3_add(ray->vec, vec3_scale(ray->dir, x));
        hit->normal = vec3_normalize(vec3_sub(hit->point, *sphere->center));
        hit->color = *sphere->color;
    
}

t_hit trace_ray(t_scene *scene, t_ray ray)
{
        t_hit hit = {0};
        hit.distance = INFINITY;
        t_sphere *sph = scene->sphere;
        // t_plane *pln = scene->plane;
        // t_cylinder *cldr = scene->cylinder;
        
        while(sph)
        {
                sphere_intersect(sph, &hit, &ray);
                sph = sph->next;
        }
        return hit;
}

void	pixel_color(t_scene *scene, int x, int y, int color)
{
	int	*buffer;

	buffer = (int *)scene->data->addr;
	buffer[(y * scene->data->line_length / 4) + x] = color;
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
                        int color = (hit.color.r << 16) | (hit.color.g << 8) | hit.color.b;
                        pixel_color(scene, x, y , color);
                        x++;
                }
                y++;
        }
        mlx_put_image_to_window(scene->data->mlx, scene->data->win, scene->data->img, 0, 0);
}
