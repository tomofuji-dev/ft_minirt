/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:32:38 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/02/05 17:02:53 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "minirt.h"
#include "rt_math.h"
#include "utils.h"

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
	if (basis->c.x == 0 && basis->c.z == 0)
	{
		basis->u = norm_vec(outer_product(init_vec(0.0, 0.0, 1.0), norm_vec(basis->c)));
		basis->v = norm_vec(outer_product(norm_vec(basis->c), basis->u));
		print_vec(&basis->c);
		print_vec(&basis->u);
		print_vec(&basis->v);
	}
	else
	{
		basis->u = norm_vec(outer_product(init_vec(0.0, 1.0, 0.0), norm_vec(basis->c)));
		basis->v = norm_vec(outer_product(norm_vec(basis->c), basis->u));
		print_vec(&basis->c);
		print_vec(&basis->u);
		print_vec(&basis->v);
	}
}
