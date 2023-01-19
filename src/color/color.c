/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:43:27 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/15 18:48:07 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "minirt.h"

int	encode_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	return (r << 16 | g << 8 | b);
}

t_rgb	double_to_trgb(double r, double g, double b)
{
	return ((t_rgb){
		.r = r,
		.g = g,
		.b = b
	});
}

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
