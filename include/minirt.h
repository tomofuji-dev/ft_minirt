/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 09:28:41 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/15 18:10:45 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stddef.h>
# include <stdbool.h>
# include <stdint.h>

# define WINDOW_WIDTH 400
# define WINDOW_HEIGHT 400
# define WINDOW_TITLE "minirt"

typedef struct s_vec {
	float	x;
	float	y;
	float	z;
}	t_vec;

typedef struct s_rgb {
	float	r;
	float	g;
	float	b;
}	t_rgb;

typedef struct s_discrim {
	float	a;
	float	b;
	float	c;
	float	d;
	float	t;
	float	t1;
	float	t2;
}	t_discrim;

typedef struct s_raytrace {
	t_vec	l;
	float	nl_dot;
	t_vec	v;
	t_vec	r;
	float	vr_dot;
	float	vr_dot_pow;
}	t_raytrace;

typedef struct s_ray
{
	t_vec	start;
	t_vec	direction;
}	t_ray;

typedef struct s_sphere
{
	t_vec	center;
	float	radius;
}	t_sphere;

typedef struct s_plane
{
	t_vec	normal;
	t_vec	position;
}	t_plane;

typedef enum e_shape
{
	ST_SPHERE,
	ST_PLANE,
}	t_shape_type;

typedef struct s_material
{
	t_rgb	ambient_ref;
	t_rgb	diffuse_ref;
	t_rgb	specular_ref;
	float	shininess;
}	t_material;

typedef struct s_shape
{
	t_shape_type	type;
	union
	{
		t_sphere	sphere;
		t_plane		plane;
	}	u_data;
	t_material		material;
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
}	t_light;

typedef struct s_intersect
{
	float	distance;
	t_vec	position;
	t_vec	normal;
}	t_intersect;

typedef struct s_scene
{
	t_shape	*shapes;
	size_t	num_shapes_capacity;
	size_t	num_shapes;
	t_light	*lights;
	size_t	num_lights_capacity;
	size_t	num_lights;
	t_rgb	ambient_illuminance;
	t_vec	eye_pos;
}	t_scene;

typedef struct s_env {
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*img_data;
	int			bits_per_pixel;
	int			bytes_per_pixel;
	int			bytes_per_line;
	int			endian;
	t_scene		*scene;
}	t_env;

#endif