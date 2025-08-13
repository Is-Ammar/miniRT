/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 22:05:37 by iammar            #+#    #+#             */
/*   Updated: 2025/08/13 11:35:09 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void print_vec3(const char *name, t_vec3 *v)
{
    if (!v)
    {
        printf("%s: (null)\n", name);
        return;
    }
    printf("%s: (%.2f, %.2f, %.2f)\n", name, v->x, v->y, v->z);
}

static void print_color(const char *name, t_color *c)
{
    if (!c)
    {
        printf("%s: (null)\n", name);
        return;
    }
    printf("%s: (R=%d, G=%d, B=%d)\n", name, c->r, c->g, c->b);
}

void print_scene(t_scene *scene)
{
    if (!scene)
    {
        printf("Scene is NULL\n");
        return;
    }

    printf("=== SCENE ===\n");

    // Ambient
    if (scene->ambient)
    {
        printf("[Ambient]\n");
        printf("  Intensity: %.2f\n", scene->ambient->intensity);
        print_color("  Color", scene->ambient->color);
    }

    // Camera
    if (scene->camera)
    {
        printf("[Camera]\n");
        print_vec3("  Position", scene->camera->position);
        print_vec3("  Direction", scene->camera->direction);
        printf("  FOV: %d\n", scene->camera->fov);
    }

    // Light
    if (scene->light)
    {
        printf("[Light]\n");
        print_vec3("  Position", scene->light->position);
        printf("  Brightness: %.2f\n", scene->light->brightness);
        print_color("  Color", scene->light->color);
    }

    // Spheres
    t_sphere *sp = scene->sphere;
    int i = 1;
    while (sp)
    {
        printf("[Sphere %d]\n", i++);
        print_vec3("  Center", sp->center);
        printf("  Diameter: %.2f\n", sp->diameter);
        print_color("  Color", sp->color);
        sp = sp->next;
    }

    // Planes
    t_plane *pl = scene->plane;
    i = 1;
    while (pl)
    {
        printf("[Plane %d]\n", i++);
        print_vec3("  Point", pl->point);
        print_vec3("  Normal", pl->normal);
        print_color("  Color", pl->color);
        pl = pl->next;
    }

    // Cylinders
    t_cylinder *cy = scene->cylinder;
    i = 1;
    while (cy)
    {
        printf("[Cylinder %d]\n", i++);
        print_vec3("  Center", cy->center);
        print_vec3("  Axis", cy->axis);
        printf("  Diameter: %.2f\n", cy->diameter);
        printf("  Height: %.2f\n", cy->height);
        print_color("  Color", cy->color);
        cy = cy->next;
    }

    printf("=== END SCENE ===\n");
}

int __exit(t_mlx_data *data)
{
    if (data)
    {
        if (data->img && data->mlx)
            mlx_destroy_image(data->mlx, data->img);
        if (data->win && data->mlx)
            mlx_destroy_window(data->mlx, data->win);
        if (data->mlx)
            mlx_destroy_display(data->mlx);
    }
    garbage_collect(NULL, EXIT_SUCCESS);
    return (0);
}

int	key_hook(int key_code, t_mlx_data *data)
{
	if (key_code == ESC)
		__exit(data);
	return (0);
}

void init_mlx(t_mlx_data *data)
{
    data = malloc(sizeof(t_mlx_data));
    garbage_collect(data , EXIT_FAILURE);
    memset(data, 0, sizeof(t_mlx_data));
    data->mlx = mlx_init();
    garbage_collect(data->mlx , EXIT_FAILURE);
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
    mlx_key_hook(data->win, key_hook, data);
    mlx_hook(data->win, 17, 0, __exit, data);
    mlx_loop(data->mlx);
}
int main(int ac , char **av)
{
    t_scene *scene = NULL;
    
    if(ac == 2)
    {
        scene = parse_file(av[1]);
        print_scene(scene);
        init_mlx(scene->data);
    }
    else
    {
        fd_putstr(2 , "Usage: ./minirt 'a scene in format *.rt'\n");
        return (1);
    }
        
    // render(data);
}
