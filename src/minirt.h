/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammar <iammar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 22:05:35 by iammar            #+#    #+#             */
/*   Updated: 2025/08/02 04:12:31 by iammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>

typedef struct s_atoi
{
	float	r;
	float	f;
	float	d;
	int		s;
}			t_atoi;

typedef struct s_cor 
{
    float x;
    float y;
    float z;
} t_cor;

typedef struct s_color 
{
    int r;
    int g;
    int b;
} t_color;

typedef struct s_vector 
{
    float x;
    float y;
    float z;
} t_vector;

typedef struct s_camera 
{
    t_cor    *coordinate;
    t_vector *vector;
    int     fov;
} t_camera;


typedef struct s_light 
{
    t_cor    *coordinate;
    float     brightness;
    t_color  *color;
} t_light;

typedef struct s_ambient 
{
    float     ambience;
    t_color  *color;
} t_ambient;

typedef struct s_plane 
{
    t_cor    *coordinate;
    t_vector *vector;
    t_color  *color;
} t_plane;


typedef struct s_sphere 
{
    t_cor   *coordinate;
    float    diameter;
    t_color *color;
} t_sphere;


typedef struct s_cylinder 
{
    t_cor    *coordinate;
    t_vector *vector;
    float     diameter;
    float     height;
    t_color  *color;
} t_cylinder;


typedef struct s_scene 
{
    t_sphere   *sphere;
    t_cylinder *cylinder;
    t_plane    *plane;
    t_camera   *camera;
    t_light    *light;
    t_ambient  *ambient;
} t_scene;

char	*ft_strdup(char *src);
float	ft_atoi(const char *str);
size_t	ft_strlcpy(char *dst,char *src, size_t len);
char	**ft_split(char const *s, char c);
int	ft_strcmp(char *s1,char *s2);
char *gnl(int fd);
t_scene *parse_file(char *file);
int number_sp(char **splitted);
void camera(t_scene *scene, char **splitted);

#endif
