/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:35:53 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/15 18:09:40 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hook.h"
#include <mlx.h>
#include <X11/X.h>

void	setup_hook(t_env *env)
{
	mlx_loop_hook(env->mlx_ptr, &handle_loop, env);
	mlx_hook(env->win_ptr, KeyPress, KeyPressMask, &handle_key, env);
	mlx_hook(env->win_ptr, ClientMessage, StructureNotifyMask, \
			&handle_close_button, env);
	mlx_loop(env->mlx_ptr);
}
