/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 09:57:17 by yel-alja          #+#    #+#             */
/*   Updated: 2025/08/31 09:57:58 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// t_ray *generate_ray(t_scene *scene , int x , int y)
// {
        
// }

void ray_tracer(t_scene *scene)
{
        int x = 0;
        int y = 0;
        // t_ray *ray;
        
        

        while(x < WIDTH)
        {
                y = 0;
                while(y < HEIGHT)
                {
                        // ray = generate_ray(scene , x , y);
                        y++;
                }
                x++;
        } 
}