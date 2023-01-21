/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_is_valid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:37:41 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/21 17:58:50 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "utils.h"
#include "minirt.h"
#include "math_utils.h"

#define LEN_RGB 3
#define LEN_VEC 3

bool	is_valid_format(char ***splited, \
						const size_t tp_len, const size_t dp_lens[]);
bool	is_valid_rgb(char **str, t_rgb *rgb);
bool	is_valid_vec(char **str, t_vec *vec, bool norm);

bool	is_valid_format(char ***splited, \
						const size_t tp_len, const size_t dp_lens[])
{
	size_t	i;

	if (calc_tp_len(splited) != tp_len)
		return (false);
	i = 0;
	while (i < tp_len)
	{
		if (calc_dp_len(splited[i]) != dp_lens[i])
			return (false);
		i++;
	}
	return (true);
}

bool	is_valid_rgb(char **str, t_rgb *rgb)
{
	size_t	i;
	int		rgb_ls[LEN_RGB];

	i = 0;
	while (i < LEN_RGB)
	{
		if (!rt_atoi(str[i], &rgb_ls[i]))
			return (false);
		if (!(0 <= rgb_ls[i] && rgb_ls[i] <= 255))
			return (false);
		i++;
	}
	rgb->r = (double)rgb_ls[0];
	rgb->g = (double)rgb_ls[1];
	rgb->b = (double)rgb_ls[2];
	return (true);
}

bool	is_valid_vec(char **str, t_vec *vec, bool norm)
{
	size_t	i;
	double	vec_ls[LEN_VEC];

	i = 0;
	while (i < LEN_VEC)
	{
		if (!rt_strtod(str[i], &vec_ls[i]))
			return (false);
		i++;
	}
	vec->x = vec_ls[0];
	vec->y = vec_ls[1];
	vec->z = vec_ls[2];
	if (norm)
	{
		if (sum_of_squares(*vec) == 0)
			return (false);
		*vec = norm_vec(*vec);
	}
	return (true);
}
