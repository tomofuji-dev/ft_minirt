/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 09:33:08 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/21 15:53:54 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "minirt.h"

typedef struct s_info
{
	double		max_dist;
	bool		exit_once_found;
}	t_info;

void	draw(t_env *env);
bool	get_nearest_shape(const t_scene *scene, const t_ray *ray, \
							t_info info, \
							t_shape **out_shape, t_intersect *out_intp);
bool	raytrace(const t_scene *scene, const t_ray *eye_ray, t_rgb *rgb);

#endif