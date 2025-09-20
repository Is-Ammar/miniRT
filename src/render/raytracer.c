/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 09:57:17 by yel-alja          #+#    #+#             */
/*   Updated: 2025/09/19 21:53:39 by yel-alja         ###   ########.fr       */
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

	if (vec_dot((t_vec3)*plan->normal, ray.dir) == 0)
		return ;
	t = vec_dot((t_vec3)*plan->normal, vec_sub((t_vec3)*plan->point, ray.vec))
		/ vec_dot((t_vec3)*plan->normal, ray.dir);
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

void cylinder_intersect(t_cylinder *cylinder, t_hit *hit, t_ray ray)
{
    if (!cylinder || !cylinder->center || !cylinder->axis || !cylinder->color)
        return;

    t_vec3 oc = vec_sub(ray.vec, *cylinder->center);
    t_vec3 axis = *cylinder->axis; // normalize cylinder axis

    float radius = cylinder->diameter / 2.0;

    // Components perpendicular to the cylinder axis
    t_vec3 d = vec_sub(ray.dir, vec_scale(axis, vec_dot(ray.dir, axis)));
    t_vec3 delta_p = vec_sub(oc, vec_scale(axis, vec_dot(oc, axis)));

    float a = vec_dot(d, d);
    float b = 2 * vec_dot(d, delta_p);
    float c = vec_dot(delta_p, delta_p) - radius * radius;

    float delta = b * b - 4 * a * c;

    if (delta < 0)
        return;

    float sqrt_delta = sqrtf(delta);
    float t1 = (-b - sqrt_delta) / (2 * a);
    float t2 = (-b + sqrt_delta) / (2 * a);
    float t;

    // Choose the nearest positive intersection
    if (t1 > 0.001 && t1 < hit->distance)
        t = t1;
    else if (t2 > 0.001 && t2 < hit->distance)
        t = t2;
    else
        return;

    // Compute hit point
    t_vec3 hit_point = vec_add(ray.vec, vec_scale(ray.dir, t));

    // Compute position along the cylinder axis
    float height_pos = vec_dot(vec_sub(hit_point, *cylinder->center), axis);
    if (fabsf(height_pos) > cylinder->height / 2.0)
        return;

    // Valid hit within cylinder height
    hit->hit = 1;
    hit->distance = t;
    hit->point = hit_point;

    // Compute normal at hit point
    t_vec3 center_to_hit = vec_sub(hit_point, *cylinder->center);
    t_vec3 proj = vec_scale(axis, vec_dot(center_to_hit, axis));
    hit->normal = vec_nor(vec_sub(center_to_hit, proj));

    hit->color = *cylinder->color;
}

t_hit	trace_ray(t_scene *scene, t_ray ray)
{
	t_hit		hit;
	t_sphere	*sph;
	t_plane		*pln;
	t_cylinder	*cldr;

	hit = (t_hit){0};
	hit.distance = INFINITY;
	sph = scene->sphere;
	pln = scene->plane;
	cldr = scene->cylinder;
	while (sph)
	{
		sphere_intersect(sph, &hit, &ray);
		sph = sph->next;
	}
	while (pln)
	{
		plan_intersect(pln, &hit, ray);
		pln = pln->next;
	}
	while (cldr)
	{
		cylinder_intersect(cldr, &hit, ray);
		cldr = cldr->next;
	}
	return (hit);
}

void	shadow_trace(t_scene *scene, t_hit *hit)
{
	t_ray	shad;
	t_hit	shadd;

	shad.vec = vec_add(hit->point, vec_scale(hit->normal, 0.0001));
	shad.dir = vec_sub(*scene->light->position, hit->point);
	shadd = trace_ray(scene, shad);
	if (shadd.distance > 0 && shadd.distance < vec_length(shad.dir))
	{
		hit->color.r *= 0.2;
		hit->color.g *= 0.2;
		hit->color.b *= 0.2;
	}
}

void	calculate_lighting(t_scene *scene, t_hit *hit)
{
        if(scene->ambient && scene->ambient->intensity)
        {
        hit->color.r += hit->color.r * scene->ambient->intensity;
        hit->color.g += hit->color.g * scene->ambient->intensity;
        hit->color.b += hit->color.b * scene->ambient->intensity;
        }
        t_vec3 light_dir = vec_nor(vec_sub(*scene->light->position, hit->point));
        float intensity = vec_dot(hit->normal, light_dir);
        if (intensity < 0)
                intensity = 0;
         hit->color.r = (int)(hit->color.r * intensity + scene->light->brightness);
        hit->color.g = (int)(hit->color.g * intensity + scene->light->brightness);
        hit->color.b = (int)(hit->color.b * intensity + scene->light->brightness);
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
