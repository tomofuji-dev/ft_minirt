/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:59:15 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/13 15:39:00 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

void	pixel_put(t_env *env, int x, int y, int color)
{
	char	*dst;

	dst = env->img_data + (y * env->bytes_per_line + x * env->bytes_per_pixel);
	*(int *)dst = color;
}

t_vec	screen_to_coord(int x, int y)
{
	return ((t_vec){
		.x = 2 * (float)x / (WINDOW_WIDTH - 1) - 1,
		.y = -2 * (float)y / (WINDOW_HEIGHT - 1) + 1,
		.z = 0
	});
}
