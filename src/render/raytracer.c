/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 09:57:17 by yel-alja          #+#    #+#             */
/*   Updated: 2025/09/26 09:19:06 by yel-alja         ###   ########.fr       */
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

static int	intersect_cap(t_ray ray, t_hit *hit, t_cylinder *cyl, t_vec3 center)
{
	t_vec3	axis;
	float	t;
	t_vec3	p;

	axis = vec_nor(*cyl->axis);
	t = vec_dot(vec_sub(center, ray.vec), axis) / vec_dot(ray.dir, axis);
	if (t < 0 || t >= hit->distance)
		return (0);
	p = vec_add(ray.vec, vec_scale(ray.dir, t));
	if (vec_length(vec_sub(p, center)) > (cyl->diameter / 2.0))
		return (0);
	hit->hit = 1;
	hit->distance = t;
	hit->point = p;
	hit->color = *cyl->color;
	if (vec_dot(ray.dir, axis) > 0)
		hit->normal = vec_scale(axis, -1);
	else
		hit->normal = axis;
	return (1);
}

void	cylinder_intersect(t_cylinder *cylinder, t_hit *hit, t_ray ray)
{
	t_intsec	cy;

	init_cy(&cy, cylinder, ray);
	if (cy.delta < 0)
		return ;
	cy.t = fminf((-cy.b - sqrtf(cy.delta)) / (2 * cy.a), (-cy.b
				+ sqrtf(cy.delta)) / (2 * cy.a));
	if (cy.t < 0)
		return ;
	cy.hit_point = vec_add(ray.vec, vec_scale(ray.dir, cy.t));
	cy.height_pos = vec_dot(vec_sub(cy.hit_point, *cylinder->center), cy.axis);
	if (fabsf(cy.height_pos) <= cylinder->height / 2.0 && cy.t < hit->distance)
	{
		hit->hit = 1;
		hit->distance = cy.t;
		hit->point = cy.hit_point;
		hit->color = *cylinder->color;
		cy.proj = vec_scale(cy.axis, cy.height_pos);
		hit->normal = vec_nor(vec_sub(vec_sub(hit->point, *cylinder->center),
					cy.proj));
	}
	intersect_cap(ray, hit, cylinder, vec_add(*cylinder->center,
			vec_scale(cy.axis, cylinder->height / 2.0)));
	intersect_cap(ray, hit, cylinder, vec_sub(*cylinder->center,
			vec_scale(cy.axis, cylinder->height / 2.0)));
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
