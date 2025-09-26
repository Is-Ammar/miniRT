/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:29:17 by iammar            #+#    #+#             */
/*   Updated: 2025/09/26 09:25:07 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_ray	generate_ray(t_scene *scene, int x, int y)
{
	t_ray	ray;
	float	h;
	float	v;

	h = ((x + 0.5) / WIDTH - 0.5) * scene->camera->plane_width;
	v = (0.5 - (y + 0.5) / HEIGHT) * scene->camera->plane_height;
	ray.vec = *((t_vec3 *)scene->camera->position);
	ray.dir = vec_nor(vec_add(vec_add(*(scene->camera->direction),
					vec_scale(scene->camera->right_vec, h)),
				vec_scale(scene->camera->up_vec, v)));
	return (ray);
}

void	trace_ray(t_scene *scene, t_ray ray, t_hit *hit)
{
	t_sphere	*sph;
	t_plane		*pln;
	t_cylinder	*cldr;

	hit->distance = INFINITY;
	sph = scene->sphere;
	pln = scene->plane;
	cldr = scene->cylinder;
	while (sph)
	{
		sphere_intersect(sph, hit, &ray, 0);
		sph = sph->next;
	}
	while (pln)
	{
		plan_intersect(pln, hit, ray);
		pln = pln->next;
	}
	while (cldr)
	{
		cylinder_intersect(cldr, hit, ray);
		cldr = cldr->next;
	}
}

void	calculate_lighting(t_scene *scene, t_hit *hit)
{
	t_vec3	light_dir;
	float	intensity;

	if (scene->ambient && scene->ambient->intensity)
	{
		hit->color.r += hit->color.r * scene->ambient->intensity;
		hit->color.g += hit->color.g * scene->ambient->intensity;
		hit->color.b += hit->color.b * scene->ambient->intensity;
	}
	light_dir = vec_nor(vec_sub(*scene->light->position, hit->point));
	intensity = vec_dot(hit->normal, light_dir);
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

void	render(t_scene *scene)
{
	int		x;
	int		y;
	t_ray	ray;
	t_hit	hit;
	int		color;

	y = 0;
	put_camera(scene->camera);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			hit = (t_hit){0};
			ray = generate_ray(scene, x, y);
			trace_ray(scene, ray, &hit);
			calculate_lighting(scene, &hit);
			color = (hit.color.r << 16) | (hit.color.g << 8) | hit.color.b;
			pixel_color(scene, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene->data->mlx, scene->data->win,
		scene->data->img, 0, 0);
}
