/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 11:01:25 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/25 12:23:44 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "error.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define LEN_DOT_RT	3
#define DOT_RT		".rt"

int			rt_fname_to_fd(char *rt_file);
static bool	is_valid_fname(char *rt_file);
static bool	dp_last(char **dest, char **dp);
void		exit_if_not_valid_scene(t_scene	*scene);
bool		print_err_return_false(char *msg);

int	rt_fname_to_fd(char *rt_file)
{
	int		fd;

	if (!is_valid_fname(rt_file))
		perror_exit(ERR_FNAME, true);
	fd = open(rt_file, O_RDWR);
	if (fd < 0)
		perror_exit(ERR_FD, true);
	return (fd);
}

static bool	is_valid_fname(char *rt_file)
{
	char	**splited;
	char	*last;
	size_t	rt_name_size;

	splited = ft_split(rt_file, '/');
	if (splited == NULL)
		perror_exit(ERR_MALLOC, true);
	if (!dp_last(&last, splited))
	{
		free_dp(splited);
		return (false);
	}
	rt_name_size = ft_strlen(last);
	if (rt_name_size <= LEN_DOT_RT \
		|| !ft_streq(&last[rt_name_size - LEN_DOT_RT], DOT_RT))
	{
		free_dp(splited);
		return (false);
	}
	free_dp(splited);
	return (true);
}

static bool	dp_last(char **dest, char **dp)
{
	size_t	i;

	i = 0;
	while (dp[i] != NULL)
		i++;
	if (i == 0)
		return (false);
	*dest = dp[i - 1];
	return (true);
}

void	exit_if_not_valid_scene(t_scene	*scene)
{
	if (errno != 0)
	{
		free_scene(scene);
		perror_exit(ERR_GNL, true);
	}
	if (!(scene->ambient_light_is_already_exist \
		&& scene->camera_is_already_exist))
	{
		free_scene(scene);
		perror_exit(ERR_NO_AMB_CAM, false);
	}
}
