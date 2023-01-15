/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:32:38 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/15 18:07:22 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

float	min(float x, float y)
{
	if (x <= y)
		return (x);
	else
		return (y);
}

float	max(float x, float y)
{
	if (x >= y)
		return (x);
	else
		return (y);
}

float	clamp(float f, float min, float max)
{
	if (f < min)
		return (min);
	else if (f > max)
		return (max);
	else
		return (f);
}

float	rand_range(float a, float b)
{
	return (a + (b - a) * (float)rand() / RAND_MAX);
}
