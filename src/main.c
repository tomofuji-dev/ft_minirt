/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:07:56 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/21 15:13:20 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "init.h"
#include "hook.h"
#include "utils.h"
#include <stdio.h>

void	print_vec(t_vec *vec)
{
	printf("(%lf, %lf, %lf)\n", vec->x, vec->y, vec->z);
}

void	print_rgb(t_rgb *rgb)
{
	printf("(%lf, %lf, %lf)\n", rgb->r, rgb->g, rgb->b);
}

void	print_sphere(t_sphere *sphere)
{
	printf("center: ");
	print_vec(&sphere->center);
	printf("radius: %lf\n", sphere->radius);
}

void	print_plane(t_plane *plane)
{
	printf("normal: ");
	print_vec(&plane->normal);
	printf("position: ");
	print_vec(&plane->position);
}

void	print_cylinder(t_cylinder *cylinder)
{
	printf("position: ");
	print_vec(&cylinder->position);
	printf("direction: ");
	print_vec(&cylinder->direction);
	printf("radius: %lf\n", cylinder->radius);
	printf("height: %lf\n", cylinder->height);
}

void	print_shape(t_shape *shape)
{
	if (shape->type == ST_SPHERE)
	{
		printf("type: sphere\n");
		print_sphere(&shape->u_data.sphere);
	}
	else if (shape->type == ST_PLANE)
	{
		printf("type: plane\n");
		print_plane(&shape->u_data.plane);
	}
	else if (shape->type == ST_CYLINDER)
	{
		printf("type: cylinder\n");
		print_cylinder(&shape->u_data.cylinder);
	}
}

void	print_material(t_material *material)
{
	printf("ambient_ref: ");
	print_rgb(&material->ambient_ref);
	printf("diffuse_ref: ");
	print_rgb(&material->diffuse_ref);
	printf("specular_ref: ");
	print_rgb(&material->specular_ref);
	printf("shininess: %lf\n", material->shininess);
}

void	print_light(t_light *light)
{
	if (light->type == LT_POINT)
		printf("type: LT_POINT\n");
	else
		printf("type: LT_DIRECTIONAL\n");
	printf("vector: ");
	print_vec(&light->vector);
	printf("illluminance: ");
	print_rgb(&light->illuminance);
}

void	print_scene(t_scene *scene)
{
	t_shape	*shape;
	t_light	*light;

	printf("--- shape ---\n");
	shape = scene->shape;
	while (shape != NULL)
	{
		print_shape(shape);
		print_material(&shape->material);
		printf("\n");
		shape = shape->next;
	}
	printf("--- light ---\n");
	light = scene->light;
	while (light != NULL)
	{
		print_light(light);
		printf("\n");
		light = light->next;
	}
	printf("--- ambient_illuminance ---\n");
	print_rgb(&scene->ambient_illuminance);
	printf("--- eye_pos ---\n");
	print_vec(&scene->eye_pos);
	printf("--- eye_direction ---\n");
	print_vec(&scene->eye_direction);
	printf("--- fov ---\n");
	printf("%lf\n", scene->fov);
}

int	main(int argc, char *argv[])
{
	t_env		env;

	if (argc != 2)
		perror_exit("not valid argc");
	init_scene(&env, argv[1]);
	print_scene(env.scene);
	init_mlx(&env);
	setup_hook(&env);
}
