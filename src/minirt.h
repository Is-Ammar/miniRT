/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 22:05:35 by iammar            #+#    #+#             */
/*   Updated: 2025/08/12 08:50:40 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "../minilibx-linux/mlx.h"

# define WIDTH       800
# define HEIGHT      600
# define ESC         65307

typedef struct s_vec3
{
    float x;
    float y;
    float z;
} t_vec3;

typedef t_vec3 t_cor;
typedef t_vec3 t_vector;


typedef struct s_color 
{
    int r;
    int g;
    int b;
} t_color;

typedef struct s_camera 
{
    t_cor      *position;
    t_vector   *direction;
    int        fov;
} t_camera;


typedef struct s_light 
{
    t_cor      *position;
    float      brightness;
    t_color    *color;
} t_light;


typedef struct s_ambient 
{
    float      intensity;
    t_color    *color;
} t_ambient;


typedef struct s_plane 
{
    t_cor      *point;
    t_vector   *normal;
    t_color    *color;
} t_plane;


typedef struct s_sphere 
{
    t_cor      *center;
    float      diameter;
    t_color    *color;
} t_sphere;


typedef struct s_cylinder 
{
    t_cor      *center;
    t_vector   *axis;
    float      diameter;
    float      height;
    t_color    *color;
} t_cylinder;


typedef struct s_scene 
{
    t_ambient  *ambient;
    t_camera   *camera;
    t_light    *light;
    

    t_sphere   *sphere;
    t_plane    *plane;
    t_cylinder *cylinder;
    
} t_scene;


typedef struct s_mlx_data 
{
    void       *mlx;
    void       *win;
    void       *img;
    char       *addr;
    int        bits_per_pixel;
    int        line_length;
    int        endian;
} t_mlx_data;



typedef struct s_atoi 
{
    float r;
    float f;
    float d;
    int   s;
} t_atoi;

typedef struct s_garabage
{
	void *ptr;
	struct s_garabage *next; 
} t_garbage;

void			garbage_collect(void *ptr,int exit_status);
char			*ft_strdup(char *src);
float			ft_atoi(const char *str);
size_t			ft_strlcpy(char *dst, char *src, size_t len);
char			**ft_split(char const *s, char c);
int				ft_strcmp(char *s1, char *s2);
char			*gnl(int fd);
t_scene			*parse_file(char *file);
int				number_sp(char **splitted);
void			camera(t_scene *scene, char **splitted);
t_cor			*get_cordinate(char *str);
void			light(t_scene *scene, char **splitted);
t_color			*get_color(char *str);
t_vector		*get_vector(char *str);
void			ambient(t_scene *scene, char **splitted);
void			spher(t_scene *scene, char **splitted);
void			plan(t_scene *scene, char **splitted);
void			cylinde(t_scene *scene, char **splitted);

#endif
