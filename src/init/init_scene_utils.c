/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 11:01:25 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/22 15:40:49 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define LEN_DOT_RT	3
#define DOT_RT		".rt"

int	rt_fname_to_fd(char *rt_file)
{
	int		fd;
	size_t	rt_name_size;

	rt_name_size = ft_strlen(rt_file);
	if (rt_name_size <= LEN_DOT_RT)
		perror_exit("invalid fname");
	if (ft_strcmp(&rt_file[rt_name_size - LEN_DOT_RT], DOT_RT) != 0)
		perror_exit("invalid extension");
	fd = open(rt_file, O_RDWR);
	if (fd < 0)
		perror_exit("invalid fd");
	return (fd);
}

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
