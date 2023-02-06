/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:10:14 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/02/06 16:47:04 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <mlx.h>

void	perror_exit(const char *msg, bool if_print_errno)
{
	if (if_print_errno && errno != 0)
		perror(msg);
	else
		ft_putendl_fd((char *)msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

bool	print_err_return_false(char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	return (false);
}

void	free_scene(t_scene *scene)
{
	t_shape	*tmp_shape;
	t_light	*tmp_light;

	if (scene == NULL)
		return ;
	while (scene->shape != NULL)
	{
		tmp_shape = scene->shape->next;
		free(scene->shape);
		scene->shape = tmp_shape;
	}
	while (scene->light != NULL)
	{
		tmp_light = scene->light->next;
		free(scene->light);
		scene->light = tmp_light;
	}
	free(scene);
}

void	close_env(t_env *env)
{
	mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	mlx_destroy_display(env->mlx_ptr);
	free_scene(env->scene);
}

bool	free_and_return_false(char ****tp, char **dp)
{
	free_tp(*tp);
	free_dp(dp);
	return (false);
}
