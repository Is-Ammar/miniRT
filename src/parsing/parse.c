/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammar <iammar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 03:39:51 by iammar            #+#    #+#             */
/*   Updated: 2025/08/02 20:36:52 by iammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_color *get_color(char *str)
{
    t_color *color = malloc(sizeof(t_color));
    char **rgb;
    rgb = ft_split(str, ',');
    if(number_sp(rgb) != 3)
    {
        printf("error: invalid color values\n");
        exit(1);
    }
    color->r = atoi(rgb[0]);
    color->g = atoi(rgb[1]);
    color->b = atoi(rgb[2]);
    return color;
}

static bool parse_line(t_scene *scene, char *line)
{
    char **splitted;
    bool result = true;

    if (!line || !scene)
        return false;

    splitted = ft_split(line, ' ');
    if (!splitted)
        return false;
    if (!splitted[0])
        return true;
    if (ft_strcmp(splitted[0], "A") == 0)
        ambient(scene, splitted);
    else if (ft_strcmp(splitted[0], "C") == 0)
        camera(scene, splitted);
    else if (ft_strcmp(splitted[0], "L") == 0)
        light(scene, splitted);
    else if (ft_strcmp(splitted[0], "sp") == 0)
        spher(scene, splitted);
    else if (ft_strcmp(splitted[0], "pl") == 0)
        plan(scene, splitted);
    else if (ft_strcmp(splitted[0], "cy") == 0)
        cylinde(scene, splitted);
    else
    {
        printf("error: invalid identifier '%s'!\n", splitted[0]);
        result = false;
    }
    return result;
}


t_scene *parse_file(char *file)
{
    int fd ;
    char *line ;
    t_scene *scene = malloc(sizeof(t_scene));
    fd = open(file, O_RDWR);
    if (!scene)
        return NULL;
    memset(scene, 0, sizeof(t_scene));
    while ((line = gnl(fd)) != NULL)
    {
        if(!parse_line(scene, line))
            return NULL;
    }
    return scene;
}
