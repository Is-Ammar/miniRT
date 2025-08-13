/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammar <iammar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:17:54 by iammar            #+#    #+#             */
/*   Updated: 2025/08/10 14:18:10 by iammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vec3 vec_sub(t_vec3 v1, t_vec3 v2)
{
    t_vec3 result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
    return result;
}

float vec_dot(t_vec3 v1, t_vec3 v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
