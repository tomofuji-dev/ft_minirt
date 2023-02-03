/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:27:14 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/02/03 12:24:35 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "color.h"
#include "rt_math.h"
#include "utils.h"
#include "get_next_line.h"
#include "init.h"
#include "error.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void			init_scene(t_env *env, char *rt_file);
static bool		scene_setting(t_scene *scene, char *line);
static bool		branch_process_by_type_identifier(\
							t_scene *scene, char ***splited);
static t_scene	*calloc_scene(void);
static void		set_basis_scene(t_env *env);

void	init_scene(t_env *env, char *rt_file)
{
	int		fd;
	char	*line;
	t_scene	*scene;

	fd = rt_fname_to_fd(rt_file);
	scene = calloc_scene();
	errno = 0;
	while (get_next_line(fd, &line))
	{
		if (!scene_setting(scene, line))
		{
			free_scene(scene);
			exit(EXIT_FAILURE);
		}
	}
	close(fd);
	exit_if_not_valid_scene(scene);
	env->scene = scene;
	set_basis_scene(env);
	print_scene(scene);
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
	free(line);
	is_valid = branch_process_by_type_identifier(scene, splited);
	free_tp(splited);
	return (is_valid);
}

static bool	branch_process_by_type_identifier(t_scene *scene, char ***splited)
{
	if (splited == NULL || splited[0] == NULL)
		return (false);
	if (ft_streq(splited[0][0], "A"))
		return (init_ambient_light(scene, splited));
	else if (ft_streq(splited[0][0], "C"))
		return (init_camera(scene, splited));
	else if (ft_streq(splited[0][0], "L"))
		return (init_light(scene, splited));
	else if (ft_streq(splited[0][0], "sp"))
		return (init_sphere(scene, splited));
	else if (ft_streq(splited[0][0], "pl"))
		return (init_plane(scene, splited));
	else if (ft_streq(splited[0][0], "cy"))
		return (init_cylinder(scene, splited));
	else if (ft_streq(splited[0][0], "co"))
		return (init_cone(scene, splited));
	else
		return (print_err_return_false(ERR_IDENTIFIER));
}

static t_scene	*calloc_scene(void)
{
	t_scene	*scene;

	scene = ft_calloc(1, sizeof(t_scene));
	if (scene == NULL)
		perror_exit(ERR_MALLOC, true);
	scene->ambient_light_is_already_exist = false;
	scene->camera_is_already_exist = false;
	return (scene);
}

static void	set_basis_scene(t_env *env)
{
	t_scene	*scene;

	scene = env->scene;
	env->window_width = WINDOW_WIDTH;
	env->window_height = WINDOW_HEIGHT;
	scene->basis.c = constant_mul_vec(scene->eye_direction, \
						env->window_width / (2 * tan(scene->fov / 360 * M_PI)));
	calc_basis(&scene->basis);
}
