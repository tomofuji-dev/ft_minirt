/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:43:27 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/15 16:14:34 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "minirt.h"

int	encode_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	return (r << 16 | g << 8 | b);
}

t_rgb	float_to_trgb(float r, float g, float b)
{
	return ((t_rgb){
		.r = r,
		.g = g,
		.b = b
	});
}

void	set_trgb(t_rgb *rgb, float r, float g, float b)
{
	rgb->r = r;
	rgb->g = g;
	rgb->b = b;
}

int	encode_trgb(t_rgb rgb)
{
	return ((int)rgb.r << 16 | (int)rgb.g << 8 | (int)rgb.b);
}
