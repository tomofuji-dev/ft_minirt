/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:07:43 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/15 16:14:21 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>
# include "minirt.h"

int		encode_rgb(uint8_t r, uint8_t g, uint8_t b);
int		encode_trgb(t_rgb rgb);
void	set_trgb(t_rgb *rgb, float r, float g, float b);

#endif