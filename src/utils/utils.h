/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:39:02 by t.fuji            #+#    #+#             */
/*   Updated: 2023/01/20 17:11:22 by tfujiwar         ###   ########.fr       */
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
void	perror_exit(const char *msg);
void	free_scene(t_scene *scene);

bool	rt_split(const char *str, char ****tp);
size_t	calc_dp_len(char **dp);
size_t	calc_tp_len(char ***tp);
void	free_tp(char ***tp);

bool	rt_atoi(char *str, int *out);

#endif