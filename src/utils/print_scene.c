/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 10:39:07 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/25 11:18:11 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "utils.h"

void		print_scene(t_scene *scene);
static void	print_scene_sub(t_scene *scene);
static void	print_shape(t_shape *shape);
static void	print_material(t_material *material);
static void	print_light(t_light *light);

void	print_scene(t_scene *scene)
{
	t_shape	*shape;
	t_light	*light;

	printf("--- shape ---\n");
	shape = scene->shape;
	while (shape != NULL)
	{
		print_shape(shape);
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
	print_scene_sub(scene);
}

static	void	print_scene_sub(t_scene *scene)
{
	printf("--- ambient_illuminance ---\n");
	print_rgb(&scene->ambient_illuminance);
	printf("--- eye_pos ---\n");
	print_vec(&scene->eye_pos);
	printf("--- eye_direction ---\n");
	print_vec(&scene->eye_direction);
	printf("--- fov ---\n");
	printf("%lf\n", scene->fov);
}

static void	print_shape(t_shape *shape)
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
	print_material(&shape->material);
	printf("checker_board_w: %lf\n", shape->checker_board_w);
}

static void	print_material(t_material *material)
{
	printf("ambient_ref: ");
	print_rgb(&material->ambient_ref);
	printf("diffuse_ref: ");
	print_rgb(&material->diffuse_ref);
	printf("specular_ref: ");
	print_rgb(&material->specular_ref);
	printf("shininess: %lf\n", material->shininess);
}

static void	print_light(t_light *light)
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
