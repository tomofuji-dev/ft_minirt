/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:53:32 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/02/03 13:13:35 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

// init_scene.c
void	init_scene(t_env *env, char *rt_file);

// init_mlx.c
void	init_mlx(t_env *env, char *window_title);

// init_light.c
bool	init_ambient_light(t_scene *scene, char ***splited);
bool	init_light(t_scene *scene, char ***splited);
bool	init_camera(t_scene *scene, char ***splited);

// init_shape.c
bool	init_sphere(t_scene *scene, char ***splited);
bool	init_plane(t_scene *scene, char ***splited);
bool	init_cylinder(t_scene *scene, char ***splited);
bool	init_cone(t_scene *scene, char ***splited);

// init_scene_utils.c
int		rt_fname_to_fd(char *rt_file);
bool	is_valid_format(char ***splited, \
						const size_t tp_len, const size_t dp_lens[]);
void	default_material(t_material *material);
void	exit_if_not_valid_scene(t_scene	*scene);
bool	print_err_return_false(char *msg);

// init_camera_in_shape.c
bool	is_camera_in_sphere(t_scene *scene, t_sphere *sphere);

// init_is_valid.c
bool	is_valid_rgb(char **src, t_rgb *dest);
bool	is_valid_vec(char **src, t_vec *dest, bool norm);
bool	is_valid_double(char *src, double *dest, double lower, double upper);
bool	is_valid_int(char *src, int *dest, double lower, double upper);

// utils.c
t_rgb	calc_rgb_ratio(t_rgb rgb, double ratio);
bool	append_light(t_scene *scene);
bool	append_shape(t_scene *scene);
t_light	*lst_last_light(t_light *light);
t_shape	*lst_last_shape(t_shape *shape);

#endif