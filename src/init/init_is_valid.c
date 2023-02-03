/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_is_valid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:37:41 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/02/03 13:13:44 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "utils.h"
#include "minirt.h"
#include "rt_math.h"
#include "libft.h"
#include "error.h"

#define LEN_RGB 3
#define LEN_VEC 3

bool	is_valid_format(char ***splited, \
						const size_t tp_len, const size_t dp_lens[]);
bool	is_valid_rgb(char **src, t_rgb *dest);
bool	is_valid_vec(char **src, t_vec *dest, bool norm);
bool	is_valid_double(char *src, double *dest, double lower, double upper);
bool	is_valid_int(char *src, int *dest, double lower, double upper);

bool	is_valid_format(char ***splited, \
						const size_t tp_len, const size_t dp_lens[])
{
	size_t	i;

	if (calc_tp_len(splited) != tp_len)
		return (print_err_return_false(ERR_COL_FORMAT));
	i = 0;
	while (i < tp_len)
	{
		if (calc_dp_len(splited[i]) != dp_lens[i])
			return (print_err_return_false(ERR_COL_FORMAT));
		i++;
	}
	return (true);
}

bool	is_valid_rgb(char **src, t_rgb *dest)
{
	size_t	i;
	int		rgb_ls[LEN_RGB];

	i = 0;
	while (i < LEN_RGB)
	{
		if (!rt_atoi(src[i], &rgb_ls[i]))
			return (print_err_return_false(ERR_RGB));
		if (!(0 <= rgb_ls[i] && rgb_ls[i] <= 255))
			return (print_err_return_false(ERR_RGB));
		i++;
	}
	dest->r = (double)rgb_ls[0];
	dest->g = (double)rgb_ls[1];
	dest->b = (double)rgb_ls[2];
	return (true);
}

bool	is_valid_vec(char **src, t_vec *dest, bool norm)
{
	size_t	i;
	double	vec_ls[LEN_VEC];

	i = 0;
	while (i < LEN_VEC)
	{
		if (!rt_strtod(src[i], &vec_ls[i]))
			return (print_err_return_false(ERR_VEC));
		i++;
	}
	*dest = (t_vec){.x = vec_ls[0], .y = vec_ls[1], .z = vec_ls[2]};
	if (norm)
	{
		if (sum_of_squares(*dest) == 0)
			return (print_err_return_false(ERR_NORM_VEC));
		*dest = norm_vec(*dest);
	}
	return (true);
}

bool	is_valid_double(char *src, double *dest, double lower, double upper)
{
	if (!rt_strtod(src, dest))
		return (false);
	if (!(lower <= *dest && *dest <= upper))
		return (print_err_return_false(ERR_RANGE));
	return (true);
}

bool	is_valid_int(char *src, int *dest, double lower, double upper)
{
	if (!rt_atoi(src, dest))
		return (false);
	if (!(lower <= *dest && *dest <= upper))
		return (print_err_return_false(ERR_RANGE));
	return (true);
}
