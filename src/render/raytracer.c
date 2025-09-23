/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 09:57:17 by yel-alja          #+#    #+#             */
/*   Updated: 2025/09/23 11:14:57 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	sphere_intersect(t_sphere *sphere, t_hit *hit, t_ray *ray, float x)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	delta;

	oc = vec_sub(ray->vec, (t_vec3)(*sphere->center));
	a = vec_dot(ray->dir, ray->dir);
	b = 2 * vec_dot(ray->dir, oc);
	c = vec_dot(oc, oc) - sphere->diameter * sphere->diameter / 4;
	delta = b * b - 4 * a * c;
	x = 0;
	if (delta < 0)
		return ;
	if (delta > 0)
		x = fminf((-b - sqrt(delta)) / (2 * a), (-b + sqrt(delta)) / (2 * a));
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

	if (vec_dot(*plan->normal, ray.dir) == 0)
		return ;
	t = vec_dot(*plan->normal, vec_sub(*plan->point, ray.vec))
		/ vec_dot(*plan->normal, ray.dir);
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

void	cylinder_intersect(t_cylinder *cylinder, t_hit *hit, t_ray ray)
{
	t_vec3	oc;
	t_vec3	axis;
	float	radius;
	t_vec3	d;
	t_vec3	p;
	float	a;
	float	b;
	float	c;
	float	delta;
	float	t;
	float	t1;
	float	t2;
	t_vec3	hit_point;
	float	height_pos;
	t_vec3	proj;

	oc = vec_sub(ray.vec, *cylinder->center);
	axis = vec_nor(*cylinder->axis);
	radius = cylinder->diameter / 2.0;
	d = vec_sub(ray.dir, vec_scale(axis, vec_dot(ray.dir, axis)));
	p = vec_sub(oc, vec_scale(axis, vec_dot(oc, axis)));
	a = vec_dot(d, d);
	b = 2 * vec_dot(d, p);
	c = vec_dot(p, p) - radius * radius;
	delta = b * b - 4 * a * c;
	if (delta < 0)
		return ;
	t1 = (-b - sqrtf(delta)) / (2 * a);
	t2 = (-b + sqrtf(delta)) / (2 * a);
	t = -1;
	if (t1 > 0 && t1 < hit->distance)
	{
		hit_point = vec_add(ray.vec, vec_scale(ray.dir, t1));
		height_pos = vec_dot(vec_sub(hit_point, *cylinder->center), axis);
		if (fabsf(height_pos) <= cylinder->height / 2.0)
			t = t1;
	}
	if ((t < 0 || t2 < t) && t2 > 0 && t2 < hit->distance)
	{
		hit_point = vec_add(ray.vec, vec_scale(ray.dir, t2));
		height_pos = vec_dot(vec_sub(hit_point, *cylinder->center), axis);
		if (fabsf(height_pos) <= cylinder->height / 2.0)
			t = t2;
	}
	if (t < 0 || t > hit->distance)
		return ;
	hit->hit = 1;
	hit->distance = t;
	hit->point = hit_point;
	hit->color = *cylinder->color;
	proj = vec_scale(axis, vec_dot(vec_sub(hit_point, *cylinder->center),
				axis));
	hit->normal = vec_nor(vec_sub(vec_sub(hit_point, *cylinder->center), proj));
}

void	shadow_trace(t_scene *scene, t_hit *hit)
{
	t_ray	shad;
	t_hit	shadd;

	shad.vec = vec_add(hit->point, vec_scale(hit->normal, 0.0001));
	shad.dir = vec_sub(*scene->light->position, hit->point);
	trace_ray(scene, shad, &shadd);
	if (shadd.distance > 0 && shadd.distance < vec_length(shad.dir))
	{
		hit->color.r *= 0.15;
		hit->color.g *= 0.15;
		hit->color.b *= 0.15;
	}
}
