/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 11:01:25 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/22 11:03:44 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "utils.h"

void	exit_if_not_valid_scene(t_scene	*scene)
{
	if (errno != 0)
	{
		free_scene(scene);
		perror_exit("error in gnl");
	}
	if (!(scene->ambient_light_is_already_exist \
		&& scene->camera_is_already_exist))
	{
		free_scene(scene);
		perror_exit("no ambient light or camera");
	}
}
