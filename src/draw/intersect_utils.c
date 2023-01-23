/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:10:53 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/23 11:16:19 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "draw.h"
#include <math.h>

void	process_discrim(t_discrim *d);
bool	set_output(t_shape *nearest_shape, t_intersect nearest_intp, \
					t_info info, t_shape_intp *shape_intp);

void	process_discrim(t_discrim *d)
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

bool	set_output(t_shape *nearest_shape, t_intersect nearest_intp, \
					t_info info, t_shape_intp *shape_intp)
{
	if (nearest_shape)
	{
		if (info.output_needed)
		{
			shape_intp->shape = nearest_shape;
			shape_intp->intp = nearest_intp;
		}
		return (true);
	}
	return (false);
}