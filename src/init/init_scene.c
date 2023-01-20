/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:27:14 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/20 17:38:13 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "color.h"
#include "math_utils.h"
#include "utils.h"
#include "get_next_line.h"
#include "init.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void		init_scene(t_env *env, char *rt_file);
static bool	scene_setting(t_scene *scene, char *line);
static bool	branch_process_by_type_identifier(t_scene *scene, char ***splited);

static void	print_dp(char **dp);
static void	print_splited(char ***splited);

void	init_scene(t_env *env, char *rt_file)
{
	int		fd;
	char	*line;
	t_scene	*scene;

	fd = open(rt_file, O_RDWR);
	if (fd < 0)
		perror_exit("invalid fd");
	scene = ft_calloc(1, sizeof(t_scene));
	if (scene == NULL)
		perror_exit("failed to malloc scene");
	errno = 0;
	while (get_next_line(fd, &line))
	{
		printf("%s", line);
		if (!scene_setting(scene, line))
		{
			free_scene(scene);
			perror_exit("error in parse line");
		}
	}
	if (errno != 0)
	{
		free_scene(scene);
		perror_exit("error in gnl");
	}
	env->scene = scene;
}

static bool	scene_setting(t_scene *scene, char *line)
{
	char	***splited;
	bool	is_valid;

	if (*line == '\0')
	{
		free(line);
		return (true);
	}
	if (!rt_split(line, &splited))
	{
		free(line);
		return (false);
	}
	print_splited(splited);
	free(line);
	is_valid = branch_process_by_type_identifier(scene, splited);
	free_tp(splited);
	return (is_valid);
}

static bool	branch_process_by_type_identifier(t_scene *scene, char ***splited)
{
	if (splited == NULL || splited[0] == NULL)
		return (false);
	if (ft_strcmp(splited[0][0], "A") == 0)
		return (init_ambient_light(scene, splited));
	else if (ft_strcmp(splited[0][0], "C") == 0)
		return (init_camera(scene, splited));
	else if (ft_strcmp(splited[0][0], "L") == 0)
		return (init_light(scene, splited));
	else if (ft_strcmp(splited[0][0], "sp") == 0)
		return (init_sphere(scene, splited));
	else if (ft_strcmp(splited[0][0], "pl") == 0)
		return (init_plane(scene, splited));
	else if (ft_strcmp(splited[0][0], "cy") == 0)
		return (init_cylinder(scene, splited));
	else
		return (false);
}

static void	print_dp(char **dp)
{
	size_t	i;

	i = 0;
	while (dp[i] != NULL)
	{
		printf("%s\n", dp[i]);
		i++;
	}
}

static void	print_splited(char ***splited)
{
	size_t	i;

	i = 0;
	while (splited[i] != NULL)
	{
		printf("-----\n");
		print_dp(splited[i]);
		i++;
	}
}
