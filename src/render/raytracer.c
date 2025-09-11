/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 09:57:17 by yel-alja          #+#    #+#             */
/*   Updated: 2025/09/11 20:15:29 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_ray	generate_ray(t_scene *scene, int x, int y)
{
	t_ray	ray;
	float	u;
	float	v;

	u = ((x + 0.5) / WIDTH - 0.5f) * scene->camera->plane_width;
	v = (0.5f - (y + 0.5) / HEIGHT) * scene->camera->plane_height;
	ray.vec = *((t_vec3 *)scene->camera->position);
	ray.dir = vec_nor(vec_add(vec_add(*(scene->camera->direction),
					vec_scale(scene->camera->right_vec, u)),
				vec_scale(scene->camera->up_vec, v)));
	return (ray);
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
        hit->color = (plan->color->r << 16 | plan->color->g << 8 | plan->color->b);
	}
}

t_hit	trace_ray(t_scene *scene, t_ray ray)
{
	t_hit	hit;
	t_plane	*pln;

	// t_sphere *sph = scene->sphere;
	pln = scene->plane;
	// t_cylinder *cldr = scene->cylinder;
	hit = (t_hit){0};
	hit.distance = INFINITY;
	// while(sph)
	// {
	//         sphere_intersect(sph, &hit);
	//         sph = sph->next;
	// }
	while (pln)
	{
		plan_intersect(pln, &hit, ray);
		pln = pln->next;
	}
	return (hit);
}

void	ray_tracer(t_scene *scene)
{
	int		x;
	int		y;
	t_ray	ray;
	t_hit	hit;

	x = 0;
	y = 0;
	put_camera(scene->camera);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = generate_ray(scene, x, y);
			hit = trace_ray(scene, ray);
            mlx_pixel_put(scene->data->mlx, scene->data->win , x ,y , hit.color);
			x++;
		}
		y++;
	}
}
