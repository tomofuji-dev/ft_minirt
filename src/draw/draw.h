/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 09:33:08 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/23 12:24:22 by tfujiwar         ###   ########.fr       */
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

typedef struct s_rt_vars {
	t_vec			l;
	double			nl_dot;
	double			dl;
	t_ray			shadow_ray;
	t_vec			v;
	t_vec			r;
	double			vr_dot;
	double			vr_dot_pow;
}			t_rt_vars;

typedef struct s_rt {
	t_shape_intp	shape_intp;
	t_light			*light;
	t_rt_vars		vars;
	t_info			info;
}			t_rt;

void	draw(t_env *env);
// raytrace.c
bool	raytrace(const t_scene *scene, const t_ray *eye_ray, t_rgb *rgb);
// raytrace_calc_ref.c
void	calc_ambient_ref(t_rgb *rgb, const t_scene *scene, t_rt *rt);
void	calc_diffuse_ref(t_rgb *rgb, t_rt *rt);
void	calc_specular_ref(t_rgb *rgb, const t_ray *eye_ray, t_rt *rt);
// intersect.c
bool	get_nearest_shape(const t_scene *scene, const t_ray *ray, \
							t_info info, t_shape_intp *shape_intp);
// intersect_plane.c
bool	intersect_plane(const t_shape *shape, const t_ray *ray, \
						t_intersect *out_intp);
// intersect_sphere.c
bool	intersect_sphere(const t_shape *shape, const t_ray *ray, \
						t_intersect *out_intp);
// intersect_cylinder.c
bool	intersect_cylinder(const t_shape *shape, const t_ray *ray, \
							t_intersect *out_intp);
// intersect_utils.c
void	process_discrim(t_discrim *d);
bool	set_output(t_shape *nearest_shape, t_intersect nearest_intp, \
					t_info info, t_shape_intp *shape_intp);

#endif