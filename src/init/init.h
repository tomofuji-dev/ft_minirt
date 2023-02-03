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

void	init_scene(t_env *env, char *rt_file);
void	init_mlx(t_env *env, char *window_title);

bool	init_ambient_light(t_scene *scene, char ***splited);
bool	init_light(t_scene *scene, char ***splited);
bool	init_camera(t_scene *scene, char ***splited);

bool	init_sphere(t_scene *scene, char ***splited);
bool	init_plane(t_scene *scene, char ***splited);
bool	init_cylinder(t_scene *scene, char ***splited);
bool	init_cone(t_scene *scene, char ***splited);

bool	is_valid_format(char ***splited, \
						const size_t tp_len, const size_t dp_lens[]);
bool	is_valid_rgb(char **src, t_rgb *dest);
bool	is_valid_vec(char **src, t_vec *dest, bool norm);
bool	is_valid_double(char *src, double *dest, double lower, double upper);
bool	is_valid_int(char *src, int *dest, double lower, double upper);

int		rt_fname_to_fd(char *rt_file);
void	exit_if_not_valid_scene(t_scene	*scene);
bool	print_err_return_false(char *msg);

t_rgb	calc_rgb_ratio(t_rgb rgb, double ratio);
bool	append_light(t_scene *scene);
bool	append_shape(t_scene *scene);
t_light	*lst_last_light(t_light *light);
t_shape	*lst_last_shape(t_shape *shape);

void	default_material(t_material *material);

#endif