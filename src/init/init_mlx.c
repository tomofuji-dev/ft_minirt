/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:46:32 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/20 12:13:15 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "utils.h"
#include <mlx.h>

void	init_mlx(t_env *env);

void	init_mlx(t_env *env)
{
	env->window_width = WINDOW_WIDTH;
	env->window_height = WINDOW_HEIGHT;
	env->mlx_ptr = mlx_init();
	if (env->mlx_ptr == NULL)
	{
		free_scene(env->scene);
		perror_exit("failed to init mlx");
	}
	env->win_ptr = mlx_new_window(env->mlx_ptr, env->window_width, \
									env->window_height, WINDOW_TITLE);
	if (env->win_ptr == NULL)
	{
		free_scene(env->scene);
		mlx_destroy_display(env->mlx_ptr);
		perror_exit("failed to create new window");
	}
	env->img_ptr = mlx_new_image(env->mlx_ptr, env->window_width, \
									env->window_height);
	if (env->img_ptr == NULL)
	{
		free_scene(env->scene);
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
		mlx_destroy_display(env->mlx_ptr);
		perror_exit("failed to create new img");
	}
	env->img_data = mlx_get_data_addr(env->img_ptr, &env->bits_per_pixel, \
										&env->bytes_per_line, &env->endian);
	env->bytes_per_pixel = env->bits_per_pixel / 8;
}
