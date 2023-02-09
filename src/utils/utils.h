/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:39:02 by t.fuji            #+#    #+#             */
/*   Updated: 2023/02/06 16:46:47 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include "minirt.h"

typedef struct s_strtod {
	bool		sign;
	bool		exp_sign;
	double		fraction;
	double		exp;
	const char	*p;
	int			frac_exp;
	int			mant_size;
	int			dec_pt;
	int			frac1;
	int			frac2;
}	t_strtod;

bool	rt_strtod(const char *string, double *out);
bool	rt_atoi(char *str, int *out);

void	perror_exit(const char *msg, bool if_print_errno);
void	free_scene(t_scene *scene);
bool	print_err_return_false(char *msg);
void	close_env(t_env *env);

bool	rt_split(const char *str, char ****tp);
size_t	calc_dp_len(char **dp);
size_t	calc_tp_len(char ***tp);
void	free_tp(char ***tp);
void	free_dp(char **dp);
bool	free_and_return_false(char ****tp, char **dp);

void	print_scene(t_scene *scene);
void	print_vec(t_vec *vec);
void	print_rgb(t_rgb *rgb);
void	print_sphere(t_sphere *sphere);
void	print_plane(t_plane *plane);
void	print_cylinder(t_cylinder *cylinder);

#endif
