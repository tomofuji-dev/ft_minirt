/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:32:38 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/02/03 19:00:37 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "minirt.h"
#include "rt_math.h"

double	rt_min(double x, double y)
{
	if (x <= y)
		return (x);
	else
		return (y);
}

double	rt_max(double x, double y)
{
	if (x >= y)
		return (x);
	else
		return (y);
}

double	rt_clamp(double f, double min, double max)
{
	if (f < min)
		return (min);
	else if (f > max)
		return (max);
	else
		return (f);
}

void	calc_basis(t_basis *basis)
{
	if (basis->c.x == 0 && basis->c.y == 0)
	{
		basis->u = init_vec(1.0, 0.0, 0.0);
		basis->v = init_vec(0.0, 1.0, 0.0);
	}
	else
	{
		basis->u = norm_vec(outer_product(basis->c, init_vec(0.0, 0.0, -1.0)));
		basis->v = norm_vec(outer_product(basis->c, basis->u));
	}
}
