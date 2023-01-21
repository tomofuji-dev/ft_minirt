/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 09:33:08 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/18 12:59:49 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "minirt.h"

typedef struct s_info
{
	double		max_dist;
	bool		exit_once_found;
	bool		output_needed;
}				t_info;

typedef struct s_shape_intp
{
	t_shape		*shape;
	t_intersect	intp;
}				t_shape_intp;

void	draw(t_env *env);
// intersect.c
bool	get_nearest_shape(const t_scene *scene, const t_ray *ray, \
							t_info info, t_shape_intp *shape_intp);
void	process_discrim(t_discrim *d);
bool	intersect_plane(const t_shape *shape, const t_ray *ray, \
						t_intersect *out_intp);
bool	raytrace(const t_scene *scene, const t_ray *eye_ray, t_rgb *rgb);
// util.c
void	pixel_put(t_env *env, int x, int y, int color);
t_vec	screen_to_coord(t_env *env, int x, int y);
// intersect_sphere.c
bool	intersect_sphere(const t_shape *shape, const t_ray *ray, \
						t_intersect *out_intp);
// intersect_cylinder.c
bool	intersect_cylinder(const t_shape *shape, const t_ray *ray, \
							t_intersect *out_intp);

#endif