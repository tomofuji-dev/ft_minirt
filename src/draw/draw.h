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

void	draw(t_env *env);
bool	get_nearest_shape(const t_scene *scene, const t_ray *ray, \
							double max_dist, bool exit_once_found, \
							t_shape **out_shape, t_intersect *out_intp);
bool	raytrace(const t_scene *scene, const t_ray *eye_ray, t_rgb *rgb);
void	pixel_put(t_env *env, int x, int y, int color);
t_vec	screen_to_coord(t_env *env, int x, int y);

#endif