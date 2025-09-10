/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammar <iammar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:17:54 by iammar            #+#    #+#             */
/*   Updated: 2025/09/08 18:39:07 by iammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vec3 vec3_add(t_vec3 a, t_vec3 b)
{
    return (t_vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

t_vec3 vec3_sub(t_vec3 a, t_vec3 b)
{
    return (t_vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

t_vec3 vec3_scale(t_vec3 v, float scale)
{
    return (t_vec3){v.x * scale, v.y * scale, v.z * scale};
}

float vec3_dot(t_vec3 a, t_vec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float vec3_length(t_vec3 v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec3 vec3_normalize(t_vec3 v)
{
    float len = vec3_length(v);
    if (len == 0)
        return (t_vec3){0, 0, 0};
    return vec3_scale(v, 1.0f / len);
}

t_vec3 vec3_cross(t_vec3 a, t_vec3 b)
{
    return (t_vec3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}
