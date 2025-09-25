/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:17:19 by yel-alja          #+#    #+#             */
/*   Updated: 2025/09/25 23:33:09 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	put_camera(t_camera *camera)
{
	t_vec3	up;
	t_vec3	forward;
	float	fov_rad;

	forward = vec_nor(*(camera->direction));
	up = (t_vec3){0, 1, 0};
	if (fabs(vec_dot(forward, up)) > 0.99)
		up = (t_vec3){0, 0, 1};
	camera->right_vec = vec_nor(vec_cro(forward, up));
	camera->up_vec = vec_cro(camera->right_vec, forward);
	fov_rad = camera->fov * 0.0174533;
	camera->plane_width = 2 * tan(fov_rad / 2);
	camera->plane_height = camera->plane_width / (WIDTH / HEIGHT);
}

float	vec_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3	vec_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

void	init_cy(t_intsec *cy, t_cylinder *cylinder, t_ray ray)
{
	cy->oc = vec_sub(ray.vec, *cylinder->center);
	cy->axis = vec_nor(*cylinder->axis);
	cy->radius = cylinder->diameter / 2.0;
	cy->d = vec_sub(ray.dir, vec_scale(cy->axis, vec_dot(ray.dir, cy->axis)));
	cy->p = vec_sub(cy->oc, vec_scale(cy->axis, vec_dot(cy->oc, cy->axis)));
	cy->a = vec_dot(cy->d, cy->d);
	cy->b = 2 * vec_dot(cy->d, cy->p);
	cy->c = vec_dot(cy->p, cy->p) - cy->radius * cy->radius;
	cy->delta = cy->b * cy->b - 4 * cy->a * cy->c;
}
