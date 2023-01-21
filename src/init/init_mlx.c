/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:46:32 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/21 16:15:55 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "utils.h"
#include <mlx.h>

#define ERR_INIT_MLX	"failed to init mlx"
#define ERR_INIT_WINDOW	"failed to create new window"
#define ERR_INIT_IMG	"failed to create new img"

void		init_mlx(t_env *env);
static void	free_mlx_and_exit(t_env *env, bool destroy_display, \
								bool destroy_window, char *msg);

void	init_mlx(t_env *env)
{
	env->mlx_ptr = mlx_init();
	if (env->mlx_ptr == NULL)
		free_mlx_and_exit(env, false, false, ERR_INIT_MLX);
	env->win_ptr = mlx_new_window(env->mlx_ptr, env->window_width, \
									env->window_height, WINDOW_TITLE);
	if (env->win_ptr == NULL)
		free_mlx_and_exit(env, true, false, ERR_INIT_WINDOW);
	env->img_ptr = mlx_new_image(env->mlx_ptr, env->window_width, \
									env->window_height);
	if (env->img_ptr == NULL)
		free_mlx_and_exit(env, true, true, ERR_INIT_IMG);
	env->img_data = mlx_get_data_addr(env->img_ptr, &env->bits_per_pixel, \
										&env->bytes_per_line, &env->endian);
	env->bytes_per_pixel = env->bits_per_pixel / 8;
}

static void	free_mlx_and_exit(t_env *env, bool destroy_display, \
								bool destroy_window, char *msg)
{
	if (destroy_window)
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	if (destroy_display)
		mlx_destroy_display(env->mlx_ptr);
	free_scene(env->scene);
	perror_exit(msg);
}
