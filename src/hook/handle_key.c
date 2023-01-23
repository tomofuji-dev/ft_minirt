/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 09:27:33 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/23 16:28:48 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include "hook.h"
#include "utils.h"

int			handle_key(int keysym, t_env *env);
int			handle_close_button(t_env *env);
static void	close_window(t_env *env);

int	handle_key(int keysym, t_env *env)
{
	if (keysym == XK_Escape)
	{
		free_scene(env->scene);
		close_window(env);
	}
	return (0);
}

int	handle_close_button(t_env *env)
{
	free_scene(env->scene);
	close_window(env);
	return (0);
}

static void	close_window(t_env *env)
{
	mlx_destroy_image(env->mlx_ptr, env->img_ptr);
	mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	mlx_destroy_display(env->mlx_ptr);
	exit(0);
}
