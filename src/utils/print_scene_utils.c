/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 10:42:54 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/22 10:43:47 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minirt.h"

void	print_vec(t_vec *vec);
void	print_rgb(t_rgb *rgb);
void	print_sphere(t_sphere *sphere);
void	print_plane(t_plane *plane);
void	print_cylinder(t_cylinder *cylinder);

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
