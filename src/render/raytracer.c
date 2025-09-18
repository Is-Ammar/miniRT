/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammar <iammar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 09:57:17 by yel-alja          #+#    #+#             */
/*   Updated: 2025/09/18 13:35:22 by iammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_ray	generate_ray(t_scene *scene, float x, float y)
{
	t_ray ray;
	
	float u = ((x + 0.5) / WIDTH  - 0.5) * scene->camera->plane_width;
	float v = (0.5 - (y + 0.5) / HEIGHT) * scene->camera->plane_height;

	ray.vec = *((t_vec3 *)scene->camera->position);
	ray.dir = vec_nor(vec_add(vec_add(*(scene->camera->direction), 
					  vec_scale(scene->camera->right_vec, u)), 
					  vec_scale(scene->camera->up_vec, v)));
	return ray;
}


void sphere_intersect(t_sphere *sphere, t_hit *hit, t_ray *ray)
{
        t_vec3 oc = vec_sub(ray->vec, (t_vec3)(*sphere->center));
        float a = vec_dot(ray->dir, ray->dir);
        float b = 2 * vec_dot(ray->dir, oc);
        float c = vec_dot(oc, oc) - sphere->diameter * sphere->diameter / 4;
        
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
                x = -b / (2 * a);
        if (x > 0 && x < hit->distance)
        {
        hit->hit = 1;
        hit->distance = x;
        hit->point = vec_add(ray->vec, vec_scale(ray->dir, x));
        hit->normal = vec_nor(vec_sub(hit->point, *sphere->center));
        hit->color = *sphere->color;
        }
}

void	plan_intersect(t_plane *plan, t_hit *hit, t_ray ray)
{
	float	t;

	if (vec_dot((t_vec3) *plan->normal, ray.dir) == 0)
		return ;
	t = vec_dot((t_vec3) *plan->normal, vec_sub((t_vec3) *plan->point, ray.vec))
		/ vec_dot((t_vec3) *plan->normal, ray.dir);
	if (t < 0)
		return ;
	if (t > 0 && t < hit->distance)
	{
		hit->distance = t;
		hit->hit = 1;
                hit->point = vec_add(ray.vec, vec_scale(ray.dir, t));
                hit->normal = *plan->normal;
                hit->color = *plan->color;
	}
}


t_hit	trace_ray(t_scene *scene, t_ray ray)
{
        t_hit hit = {0};
        hit.distance = INFINITY;
        t_sphere *sph = scene->sphere;
        t_plane *pln = scene->plane;
        // t_cylinder *cldr = scene->cylinder;
        
        while(sph)
        {
                sphere_intersect(sph, &hit, &ray);
                sph = sph->next;
        }
        while (pln)
	{
		plan_intersect(pln, &hit, ray);
		pln = pln->next;
	}
        return hit;
}

void shadow_trace(t_scene *scene, t_hit *hit)
{
        t_ray shad;
        t_hit shadd;
        shad.vec = vec_add(hit->point, vec_scale(hit->normal, 0.0001));
        shad.dir = vec_sub(*scene->light->position, hit->point);
        shadd = trace_ray(scene, shad);
        if(shadd.distance > 0 && shadd.distance < vec_length(shad.dir))
        {
                hit->color.r *= 0.2;
                hit->color.g *= 0.2;
                hit->color.b *= 0.2;
        }
}

void calculate_lighting(t_scene *scene, t_hit *hit)
{
        if(scene->ambient && scene->ambient->color)
        {
        hit->color.r += hit->color.r * scene->light->brightness + scene->light->color->r / 255;
        hit->color.g += hit->color.g * scene->light->brightness + scene->light->color->g / 255;      
        hit->color.b += hit->color.b * scene->light->brightness + scene->light->color->b / 255;
        }
        shadow_trace(scene, hit);
        hit->color.r = fminf(255, fmaxf(0, hit->color.r));
        hit->color.g = fminf(255, fmaxf(0, hit->color.g));
        hit->color.b = fminf(255, fmaxf(0, hit->color.b));
}

void	pixel_color(t_scene *scene, int x, int y, int color)
{
	int	*buffer;

	buffer = (int *)scene->data->addr;
	buffer[(y * scene->data->line_length / 4) + x] = color;
}

t_color anti_aliasing(t_scene *scene,int x, int y)
{
        t_color total = {0};
        t_color final = {0};
        	t_ray ray;
	t_hit hit;
        int i = 0;
        while (i++ < 4) 
        {
                float offset_x = x + 0.25 + (i % 2) * 0.5;
                float offset_y = y + 0.25 + (i / 2)* 0.5;
                
                ray = generate_ray(scene, offset_x, offset_y);
                hit = trace_ray(scene, ray);
                calculate_lighting(scene, &hit);
                
                total.r += hit.color.r;
                total.g += hit.color.g;
                total.b += hit.color.b;
        }
        final.r = total.r / 4;
        final.g = total.g / 4;
        final.b = total.b / 4;
        return final;
}

void	ray_tracer(t_scene *scene)
{
	int x = 0;
	int y = 0;

	
	put_camera(scene->camera);
	
	while (y < HEIGHT) 
	{
		x = 0;
		while (x < WIDTH) 
		{
			t_color final = anti_aliasing(scene, x, y);
			
			int color = (final.r << 16) | (final.g << 8) | final.b;
			pixel_color(scene, x, y, color);
			x++;
		}
		y++;
	}
	
	mlx_put_image_to_window(scene->data->mlx, scene->data->win, scene->data->img, 0, 0);
}
