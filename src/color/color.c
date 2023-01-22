/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:43:27 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/22 11:23:37 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "rt_math.h"

void	set_trgb(t_rgb *rgb, double r, double g, double b)
{
	rgb->r = r;
	rgb->g = g;
	rgb->b = b;
}

int	encode_trgb(t_rgb rgb)
{
	return ((int)rgb.r << 16 | (int)rgb.g << 8 | (int)rgb.b);
}

void	add_on_rgb(t_rgb *rgb, t_rgb ref, t_light light, double dot)
{
	rgb->r += ref.r * light.illuminance.r * dot;
	rgb->g += ref.g * light.illuminance.g * dot;
	rgb->b += ref.b * light.illuminance.b * dot;
}

void	multiple_rgb(t_rgb *product, t_rgb rgb1, t_rgb rgb2)
{
	product->r = rgb1.r * rgb2.r;
	product->g = rgb1.g * rgb2.g;
	product->b = rgb1.b * rgb2.b;
}

void	clamp_mul_rgb(t_rgb *rgb, double n)
{
	rgb->r = n * ft_clamp(rgb->r, 0, 1);
	rgb->g = n * ft_clamp(rgb->g, 0, 1);
	rgb->b = n * ft_clamp(rgb->b, 0, 1);
}
