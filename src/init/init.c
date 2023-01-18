/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:46:32 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/18 11:53:24 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "color.h"
#include "math_utils.h"
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

void			init(t_env *env);
static void		init_env(t_env *env);
void			init_shape(t_shape *shape, t_shape_type st, ...);
void			init_material(t_material *mat, \
						double ambR, double ambG, double ambB, \
						double difR, double difG, double difB, \
						double speR, double speG, double speB, \
						double shns);
void			init_light(t_light *light, t_light_type lt, \
						double vx, double vy, double vz, \
						double illR, double illG, double illB);
void			scene_setting(t_scene *scene);

void	init(t_env *env)
{
	init_env(env);
}

static void	init_env(t_env *env)
{
	t_scene	*scene;

	env->mlx_ptr = mlx_init();
	if (env->mlx_ptr == NULL)
	{
		perror("failed to init mlx");
		exit(1);
	}
	env->win_ptr = mlx_new_window(env->mlx_ptr, WINDOW_WIDTH, \
									WINDOW_HEIGHT, WINDOW_TITLE);
	if (env->win_ptr == NULL)
	{
		mlx_destroy_display(env->mlx_ptr);
		perror("failed to create new window");
		exit(1);
	}
	env->img_ptr = mlx_new_image(env->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (env->img_ptr == NULL)
	{
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
		mlx_destroy_display(env->mlx_ptr);
		perror("failed to create new window");
		exit(1);
	}
	env->img_data = mlx_get_data_addr(env->img_ptr, &env->bits_per_pixel, \
										&env->bytes_per_line, &env->endian);
	env->bytes_per_pixel = env->bits_per_pixel / 8;
	scene = malloc(sizeof(t_scene));
	scene_setting(scene);
	env->scene = scene;
}

void	init_shape(t_shape *shape, t_shape_type st, ...)
{
	va_list		args;
	t_sphere	*sph;
	t_plane		*plane;
	t_cylinder	*cy;

	va_start(args, st);
	shape->type = st;
	if (st == ST_SPHERE)
	{
		sph = &(shape->u_data.sphere);
		sph->center.x = va_arg(args, double);
		sph->center.y = va_arg(args, double);
		sph->center.z = va_arg(args, double);
		sph->radius = va_arg(args, double);
	}
	else if (st == ST_PLANE)
	{
		plane = &(shape->u_data.plane);
		plane->position.x = va_arg(args, double);
		plane->position.y = va_arg(args, double);
		plane->position.z = va_arg(args, double);
		plane->normal.x = va_arg(args, double);
		plane->normal.y = va_arg(args, double);
		plane->normal.z = va_arg(args, double);
	}
	else if (st == ST_CYLINDER)
	{
		cy = &(shape->u_data.cylinder);
		cy->position.x = va_arg(args, double);
		cy->position.y = va_arg(args, double);
		cy->position.z = va_arg(args, double);
		cy->direction.x = va_arg(args, double);
		cy->direction.y = va_arg(args, double);
		cy->direction.z = va_arg(args, double);
		cy->radius = va_arg(args, double);
		cy->height = va_arg(args, double);
	}
	va_end(args);
}

void	init_material(t_material *mat,
						double ambR, double ambG, double ambB,
						double difR, double difG, double difB,
						double speR, double speG, double speB,
						double shns)
{
	set_trgb(&mat->ambient_ref, ambR, ambG, ambB);
	set_trgb(&mat->diffuse_ref, difR, difG, difB);
	set_trgb(&mat->specular_ref, speR, speG, speB);
	mat->shininess = shns;
}

void	init_light(t_light *light, t_light_type lt,
					double vx, double vy, double vz,
					double illR, double illG, double illB)
{
	light->type = lt;
	set_vec(&light->vector, vx, vy, vz);
	set_trgb(&light->illuminance, illR, illG, illB);
}

void	scene_setting(t_scene *scene)
{
	scene->num_shapes_capacity = 16;
	scene->shapes = malloc(sizeof(t_shape) * scene->num_shapes_capacity);
	init_shape(&scene->shapes[0], ST_PLANE, \
				0.0, -1.0, 0.0, \
				0.0, 1.0, 0.0);
	init_material(&scene->shapes[0].material, \
					0.01, 0.01, 0.01, \
					0.69, 0.69, 0.69, \
					0.30, 0.30, 0.30, \
					8.0);
	// init_shape(&scene->shapes[1], ST_SPHERE, \
	// 			0.0, 0.0, 5.0, \
	// 			1.0);
	// init_material(&scene->shapes[1].material, \
	// 			0.01, 0.01, 0.01, \
	// 			0.69, 0.00, 0.00, \
	// 			0.30, 0.30, 0.30, \
	// 			8.0);
	init_shape(&scene->shapes[1], ST_CYLINDER, \
				0.0, 0.0, 10.0, \
				0.5773, 0.5773, 0.5773, \
				1.0, 5.0);
	init_material(&scene->shapes[1].material, \
				0.01, 0.01, 0.01, \
				0.69, 0.00, 0.00, \
				0.30, 0.30, 0.30, \
				8.0);
	init_shape(&scene->shapes[2], ST_CYLINDER, \
				0.0, 0.0, 10.0, \
				0.5773, 0.5773, -0.5773, \
				1.0, 5.0);
	init_material(&scene->shapes[2].material, \
				0.01, 0.01, 0.01, \
				0.00, 0.69, 0.00, \
				0.30, 0.30, 0.30, \
				8.0);
	init_shape(&scene->shapes[3], ST_CYLINDER, \
				0.0, 0.0, 10.0, \
				0.5773, -0.5773, 0.5773, \
				1.0, 5.0);
	init_material(&scene->shapes[3].material, \
				0.01, 0.01, 0.01, \
				0.00, 0.00, 0.69, \
				0.30, 0.30, 0.30, \
				8.0);
	// for (int i = 1; i < 16; i++)
	// {
	// 	init_shape(&scene->shapes[i], ST_SPHERE, \
	// 				rand_range(-2.5, 2.5), rand_range(0, 2.0), rand_range(0, 20.0), \
	// 				rand_range(0.25, 0.5));
	// 	init_material(&scene->shapes[i].material, \
	// 				0.1, 0.1, 0.1, \
	// 				rand_range(0.5, 1.0), rand_range(0.5, 1.0), rand_range(0.5, 1.0), \
	// 				rand_range(0.3, 0.5), rand_range(0.3, 0.5), rand_range(0.3, 0.5), \
	// 				8.0);
	// }
	scene->num_shapes = 4;
	set_trgb(&scene->ambient_illuminance, 0.1, 0.1, 0.1);
	scene->num_lights_capacity = 16;
	scene->lights = malloc(sizeof(t_light) * scene->num_lights_capacity);
	init_light(&scene->lights[0], LT_POINT, \
				5.0, 5.0, -5.0, \
				1.0, 1.0, 1.0);
	scene->num_lights = 1;
	scene->eye_pos = init_vec(0, 0, -5);
}
