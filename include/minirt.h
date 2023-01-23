/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 09:28:41 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/23 18:05:43 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stddef.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>

# define RETURN_SUCCESS 0
# define RETURN_FAILURE 1

# define WINDOW_WIDTH 400
# define WINDOW_HEIGHT 400
# define WINDOW_TITLE "minirt"
# define C_EPSILON 0.002

typedef struct s_vec {
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_rgb {
	double	r;
	double	g;
	double	b;
}	t_rgb;

typedef struct s_discrim {
	double	a;
	double	b;
	double	c;
	double	d;
	double	t;
	double	t1;
	double	t2;
	double	m;
}	t_discrim;

typedef struct s_ray
{
	t_vec	start;
	t_vec	direction;
}	t_ray;

typedef struct s_sphere
{
	t_vec	center;
	double	radius;
}	t_sphere;

typedef struct s_plane
{
	t_vec	normal;
	t_vec	position;
}	t_plane;

typedef struct s_cylinder
{
	t_vec	position;
	t_vec	direction;
	double	radius;
	double	height;
}	t_cylinder;

typedef enum e_shape
{
	ST_SPHERE,
	ST_PLANE,
	ST_CYLINDER,
}	t_shape_type;

typedef struct s_material
{
	t_rgb	ambient_ref;
	t_rgb	diffuse_ref;
	t_rgb	specular_ref;
	double	shininess;
}	t_material;

typedef struct s_shape
{
	t_shape_type	type;
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
	}	u_data;
	t_material		material;
	bool			is_checker_board;
	struct s_shape	*next;
}	t_shape;

typedef enum e_light_type
{
	LT_POINT,
	LT_DIRECTIONAL,
}	t_light_type;

typedef struct s_light
{
	t_light_type	type;
	t_vec			vector;
	t_rgb			illuminance;
	struct s_light	*next;
}	t_light;

typedef struct s_intersect
{
	double	distance;
	t_vec	position;
	t_vec	normal;
}	t_intersect;

typedef struct s_scene
{
	t_shape	*shape;
	t_light	*light;
	t_rgb	ambient_illuminance;
	t_vec	eye_pos;
	t_vec	eye_direction;
	double	fov;
	t_vec	c;
	t_vec	u;
	t_vec	v;
	bool	ambient_light_is_already_exist;
	bool	camera_is_already_exist;
}	t_scene;

typedef struct s_env {
	void		*mlx_ptr;
	void		*win_ptr;
	double		window_width;
	double		window_height;
	void		*img_ptr;
	char		*img_data;
	int			bits_per_pixel;
	int			bytes_per_pixel;
	int			bytes_per_line;
	int			endian;
	t_scene		*scene;
}	t_env;

#endif