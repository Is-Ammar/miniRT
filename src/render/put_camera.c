/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:17:19 by yel-alja          #+#    #+#             */
/*   Updated: 2025/09/09 18:37:10 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	put_camera(t_camera *camera)
{
	t_vec3	up;
	t_vec3	*forward;

	if (camera->direction->z != 0)
		up = (t_vec3){1,  0,  0};
	else
		up = (t_vec3){0,  0,  1};
	forward = (t_vec3 *)camera->direction;
	camera->forward = *forward;
	camera->right_vec = vec_nor(vec_cro(*forward, up));
	camera->up_vec = vec_cro(camera->right_vec, *forward);
    camera->plane_width = 2 * tan(camera->fov * 0.0174533 / 2);
    camera->plane_height = camera->plane_width / (WIDTH / HEIGHT);
}




// void plan_equation(t_scene *scene) // n.(p - p0) = 0 // n is the nromal vector  //  p is a point on the plane //p0 is a konwn point on the plane
// {
//         // scene->plane->normal
// }
