/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:27:14 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/22 11:24:23 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "color.h"
#include "rt_math.h"
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

void			init_scene(t_env *env, char *rt_file);
static bool		scene_setting(t_scene *scene, char *line);
static bool		branch_process_by_type_identifier(\
							t_scene *scene, char ***splited);
static t_scene	*calloc_scene(void);
static void		calc_basis_vector(t_env *env);

void	init_scene(t_env *env, char *rt_file)
{
	int		fd;
	char	*line;
	t_scene	*scene;

	fd = open(rt_file, O_RDWR);
	if (fd < 0)
		perror_exit("invalid fd");
	scene = calloc_scene();
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
	exit_if_not_valid_scene(scene);
	env->scene = scene;
	calc_basis_vector(env);
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

static t_scene	*calloc_scene(void)
{
	t_scene	*scene;

	scene = ft_calloc(1, sizeof(t_scene));
	scene->ambient_light_is_already_exist = false;
	scene->camera_is_already_exist = false;
	if (scene == NULL)
		perror_exit("failed to malloc scene");
	return (scene);
}

static void	calc_basis_vector(t_env *env)
{
	t_scene	*scene;

	scene = env->scene;
	env->window_width = WINDOW_WIDTH;
	env->window_height = WINDOW_HEIGHT;
	scene->c = constant_mul_vec(scene->eye_direction, \
						env->window_width / (2 * tan(scene->fov / 360 * M_PI)));
	if (scene->c.x == 0 && scene->c.y == 0)
	{
		scene->u = init_vec(1.0, 0.0, 0.0);
		scene->v = init_vec(0.0, 1.0, 0.0);
	}
	else
	{
		scene->u.x = -1 * scene->c.y / \
					sqrt(pow(scene->c.x, 2) + pow(scene->c.y, 2));
		scene->u.y = scene->c.x / sqrt(pow(scene->c.x, 2) + pow(scene->c.y, 2));
		scene->u.z = 0;
		scene->v = outer_product(scene->eye_direction, scene->u);
	}
}
