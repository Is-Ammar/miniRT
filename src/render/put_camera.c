/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammar <iammar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:17:19 by yel-alja          #+#    #+#             */
/*   Updated: 2025/09/11 20:37:40 by iammar           ###   ########.fr       */
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
	if (fabs(vec_dot(forward, up)) > 0.99f)
		up = (t_vec3){0, 0, 1};
	camera->right_vec = vec_nor(vec_cro(forward, up));
	camera->up_vec = vec_cro(camera->right_vec, forward);
	fov_rad = camera->fov * (M_PI / 180.0f);
	camera->plane_width = 2.0f * tan(fov_rad / 2.0f);
	camera->plane_height = camera->plane_width / (WIDTH / HEIGHT);
}

float	vec_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
