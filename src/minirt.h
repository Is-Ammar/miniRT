/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 22:05:35 by iammar            #+#    #+#             */
/*   Updated: 2025/09/01 09:22:46 by yel-alja         ###   ########.fr       */
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
# include <math.h>
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
    t_vec3      up_vec;      
    t_vec3      right_vec;      
    double      plane_width;
    double      plane_height;
    int         fov;
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
    struct s_plane *next;
} t_plane;


typedef struct s_sphere 
{
    t_cor      *center;
    float      diameter;
    t_color    *color;
    struct s_sphere *next;
} t_sphere;


typedef struct s_cylinder 
{
    t_cor      *center;
    t_vector   *axis;
    float      diameter;
    float      height;
    t_color    *color;
    struct s_cylinder *next;
} t_cylinder;

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

typedef struct s_scene 
{
    t_ambient  *ambient;
    t_camera   *camera;
    t_light    *light;
    t_sphere   *sphere;
    t_plane    *plane;
    t_cylinder *cylinder;
     t_mlx_data  *data;
} t_scene;



typedef struct s_atoi 
{
    float r;
    float f;
    float d;
    int   s;
} t_atoi;

typedef struct s_ray
{
    t_vec3 vec;
    t_vec3 dir;
} t_ray;

typedef struct s_garabage
{
	void *ptr;
	struct s_garabage *next; 
} t_garbage;

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
t_sphere		*spher(char **splitted);
t_plane			*plan(char **splitted);
void            fd_putstr(int fd, char *str);
t_cylinder     *cylinde(char **splitted);
void            sphere_back(t_sphere **sphere , t_sphere *new);
void            plane_back(t_plane **plane , t_plane *new);
void            cylinder_back(t_cylinder **cylinder , t_cylinder *new);
void			garbage_collect(void *ptr,int exit_status);


//math
t_vec3 vec_sub(t_vec3 v1, t_vec3 v2);
float vec_dot(t_vec3 v1, t_vec3 v2);
t_vec3 vec_cro(t_vec3 v1 , t_vec3 v2);
t_vec3 vec_add(t_vec3 v1 , t_vec3 v2);
t_vec3 vec_nor(t_vec3 v);


//test

void	put_camera(t_camera *camera);
#endif
