/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammar <iammar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:17:19 by yel-alja          #+#    #+#             */
/*   Updated: 2025/09/08 18:37:17 by iammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void put_camera(t_camera *camera)
{
    t_vec3 up;
    t_vec3 forward;

    forward = vec3_normalize(*(camera->direction));
    up = (t_vec3){0, 1, 0};
    
    if (fabs(vec3_dot(forward, up)) > 0.99f)
        up = (t_vec3){0, 0, 1};
    camera->right_vec = vec3_normalize(vec3_cross(forward, up));
    camera->up_vec = vec3_cross(camera->right_vec, forward);
    float fov_rad = camera->fov * (M_PI / 180.0f);
    camera->plane_width = 2.0f * tan(fov_rad / 2.0f);
    camera->plane_height = camera->plane_width / WIDTH / HEIGHT;
}




// void plan_equation(t_scene *scene) // n.(p - p0) = 0 // n is the nromal vector  //  p is a point on the plane //p0 is a konwn point on the plane
// {
//         // scene->plane->normal
// }
