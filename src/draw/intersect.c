/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:36:47 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/18 11:41:30 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "color.h"
#include "util.h"
#include "math_utils.h"
#include <math.h>
#include <stdio.h>

bool	get_nearest_shape(const t_scene *scene, const t_ray *ray, \
							t_info info, t_shape **out_shape, \
							t_intersect *out_intp);
bool				intersect(const t_shape *shape, const t_ray *ray, \
								t_intersect *out_intp);
static bool			intersect_sphere(const t_shape *shape, const t_ray *ray, \
									t_intersect *out_intp);
static bool			intersect_plane(const t_shape *shape, const t_ray *ray, \
									t_intersect *out_intp);
static bool			intersect_cylinder(const t_shape *shape, const t_ray *ray, \
									t_intersect *out_intp);
static t_discrim	intersect_sphere_discrim(const t_shape *shape, \
												const t_ray *ray);
static t_discrim	intersect_cylinder_discrim(const t_shape *shape, \
											const t_ray *ray);
static bool			intersect_cylinder_bottom(const t_shape *shape, \
											const t_ray *ray, t_intersect *out_intp);
static void			process_discrim(t_discrim *d);

bool	get_nearest_shape(const t_scene *scene, const t_ray *ray, \
							t_info info, t_shape **out_shape, \
							t_intersect *out_intp)
{
	size_t		i;
	t_shape		*nearest_shape;
	t_intersect	nearest_intp;
	t_intersect	intp;

	nearest_shape = NULL;
	nearest_intp.distance = info.max_dist;
	i = 0;
	while (i < scene->num_shapes)
	{
		if (intersect(&scene->shapes[i], ray, &intp) && \
			intp.distance < nearest_intp.distance)
		{
			nearest_shape = &scene->shapes[i];
			nearest_intp = intp;
			if (info.exit_once_found)
				break ;
		}
		i++;
	}
	if (nearest_shape)
	{
		if (out_shape)
			*out_shape = nearest_shape;
		if (out_intp)
			*out_intp = nearest_intp;
		return (true);
	}
	return (false);
}

bool	intersect(const t_shape *shape, const t_ray *ray, t_intersect *out_intp)
{
	if (shape->type == ST_SPHERE)
		return (intersect_sphere(shape, ray, out_intp));
	else if (shape->type == ST_PLANE)
		return (intersect_plane(shape, ray, out_intp));
	else if (shape->type == ST_CYLINDER)
		return (intersect_cylinder(shape, ray, out_intp));
	return (false);
}

static bool	intersect_sphere(const t_shape *shape, const t_ray *ray, \
						t_intersect *out_intp)
{
	const t_sphere	*sph;
	t_discrim		d;

	d = intersect_sphere_discrim(shape, ray);
	sph = &shape->u_data.sphere;
	if (d.t > 0)
	{
		if (out_intp)
		{
			out_intp->distance = d.t;
			out_intp->position = add_vec(ray->start, \
								constant_mul_vec(ray->direction, d.t));
			out_intp->normal = diff_vec(out_intp->position, sph->center);
			out_intp->normal = norm_vec(out_intp->normal);
		}
		return (true);
	}
	else
		return (false);
}

static bool	intersect_plane(const t_shape *shape, const t_ray *ray, \
						t_intersect *out_intp)
{
	const t_plane	*pln;
	double			dn_dot;
	double			t;
	t_vec			s_p;

	pln = &shape->u_data.plane;
	dn_dot = inner_product(ray->direction, pln->normal);
	if (dn_dot != 0)
	{
		s_p = diff_vec(ray->start, pln->position);
		t = -1 * inner_product(s_p, pln->normal) / dn_dot;
		if (t > 0)
		{
			if (out_intp)
			{
				out_intp->distance = t;
				out_intp->position = add_vec(ray->start, \
										constant_mul_vec(ray->direction, t));
				out_intp->normal = pln->normal;
			}
			return (true);
		}
		return (false);
	}
	return (false);
}

static bool	intersect_cylinder(const t_shape *shape, const t_ray *ray, \
						t_intersect *out_intp)
{
	const t_cylinder	*cy;
	t_discrim			d;

	d = intersect_cylinder_discrim(shape, ray);
	if (intersect_cylinder_bottom(shape, ray, out_intp))
	{
		if (d.t <= 0 || (d.t > 0 && out_intp->distance < d.t))
			return (true);
	}
	cy = &shape->u_data.cylinder;
	if (d.t > 0)
	{
		if (out_intp)
		{
			out_intp->distance = d.t;
			out_intp->position = add_vec(ray->start, \
								constant_mul_vec(ray->direction, d.t));
			out_intp->normal.x = 2 * cy->direction.z * (cy->direction.z * (out_intp->position.x - cy->position.x) - cy->direction.x * ((out_intp->position.z - cy->position.z))) - 2 * cy->direction.y * (cy->direction.x * (out_intp->position.y - cy->position.y) - cy->direction.y * ((out_intp->position.x - cy->position.x)));
			out_intp->normal.y = 2 * cy->direction.x * (cy->direction.x * (out_intp->position.y - cy->position.y) - cy->direction.y * ((out_intp->position.x - cy->position.x))) - 2 * cy->direction.z * (cy->direction.y * (out_intp->position.z - cy->position.z) - cy->direction.z * ((out_intp->position.y - cy->position.y)));
			out_intp->normal.z = 2 * cy->direction.y * (cy->direction.y * (out_intp->position.z - cy->position.z) - cy->direction.z * ((out_intp->position.y - cy->position.y))) - 2 * cy->direction.x * (cy->direction.z * (out_intp->position.x - cy->position.x) - cy->direction.x * ((out_intp->position.z - cy->position.z)));
			out_intp->normal = norm_vec(out_intp->normal);
		}
		return (true);
	}
	else
		return (false);
}

static t_discrim	intersect_sphere_discrim(const t_shape *shape, \
											const t_ray *ray)
{
	const t_sphere	*sph;
	t_vec			pe_pc;
	t_discrim		d;

	sph = &shape->u_data.sphere;
	pe_pc = diff_vec(ray->start, sph->center);
	d.a = inner_product(ray->direction, ray->direction);
	d.b = 2 * inner_product(ray->direction, pe_pc);
	d.c = inner_product(pe_pc, pe_pc) - sph->radius * sph->radius;
	d.d = d.b * d.b - 4 * d.a * d.c;
	process_discrim(&d);
	return (d);
}

static t_discrim	intersect_cylinder_discrim(const t_shape *shape, \
											const t_ray *ray)
{
	const t_cylinder	*cy;
	t_vec				pe_pc;
	t_discrim			d;

	cy = &shape->u_data.cylinder;
	pe_pc = diff_vec(ray->start, cy->position);
	d.a = inner_product(ray->direction, ray->direction) \
			- pow(inner_product(cy->direction, ray->direction), 2);
	d.b = 2 * (inner_product(ray->direction, pe_pc) \
				- inner_product(ray->direction, cy->direction) \
				* inner_product(pe_pc, cy->direction));
	d.c = inner_product(pe_pc, pe_pc) \
			- pow(inner_product(pe_pc, cy->direction), 2) \
			- pow(cy->radius, 2);
	d.d = d.b * d.b - 4 * d.a * d.c;
	d.t = -1.0f;
	process_discrim(&d);
	d.m = inner_product(pe_pc, cy->direction) \
			+ d.t * inner_product(ray->direction, cy->direction);
	if (d.m < -cy->height / 2 || d.m > cy->height / 2)
		d.t = -1;
	return (d);
}

static bool	intersect_cylinder_bottom(const t_shape *shape, \
								const t_ray *ray, t_intersect *out_intp)
{
	const t_cylinder	*cy;
	t_shape				s;
	t_vec				plane_pos;
	bool				ret;
	t_intersect			intp;

	ret = false;
	cy = &shape->u_data.cylinder;
	s.u_data.plane.normal = constant_mul_vec(cy->direction, -1);
	plane_pos = add_vec(cy->position, constant_mul_vec(cy->direction, -1 * cy->height / 2));
	s.u_data.plane.position = plane_pos;
	if (intersect_plane(&s, ray, &intp) && \
		abs_vec(diff_vec(intp.position, plane_pos)) <= cy->radius)
	{
		ret = true;
		*out_intp = intp;
	}
	s.u_data.plane.normal = cy->direction;
	plane_pos = add_vec(cy->position, constant_mul_vec(cy->direction, cy->height / 2));
	s.u_data.plane.position = plane_pos;
	if (intersect_plane(&s, ray, &intp) && \
		abs_vec(diff_vec(intp.position, plane_pos)) <= cy->radius)
	{
		if (!ret || intp.distance < out_intp->distance)
		{
			ret = true;
			*out_intp = intp;
		}
	}
	return (ret);
}

static void	process_discrim(t_discrim *d)
{
	d->t = -1.0f;
	if (d->d == 0)
		d->t = -d->b / (2 * d->a);
	else if (d->d > 0)
	{
		d->t1 = (-d->b + sqrt(d->d)) / (2 * d->a);
		d->t2 = (-d->b - sqrt(d->d)) / (2 * d->a);
		if (d->t1 > 0)
			d->t = d->t1;
		if (d->t2 > 0 && d->t2 < d->t)
			d->t = d->t2;
	}
}
