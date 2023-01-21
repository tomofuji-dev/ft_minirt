/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:07:43 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/15 18:48:07 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>
# include "minirt.h"

int		encode_rgb(uint8_t r, uint8_t g, uint8_t b);
int		encode_trgb(t_rgb rgb);
void	set_trgb(t_rgb *rgb, double r, double g, double b);
void	add_on_rgb(t_rgb *rgb, t_rgb ref, t_light light, double dot);
void	multiple_rgb(t_rgb *product, t_rgb rgb1, t_rgb rgb2);
void	clamp_mul_rgb(t_rgb *rgb, double n);

#endif