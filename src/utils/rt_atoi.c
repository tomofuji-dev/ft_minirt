/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:47:00 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/25 12:26:07 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "error.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

bool		rt_atoi(char *str, int *out);
static bool	handle_digit(char **tmp, int sign, int *out);

bool	rt_atoi(char *str, int *out)
{
	char	*tmp;
	int		sign;

	sign = 1;
	tmp = str;
	if (*tmp == '-')
	{
		sign = -1;
		tmp++;
	}
	return (handle_digit(&tmp, sign, out));
}

static bool	handle_digit(char **tmp, int sign, int *out)
{
	int	tmp_digit;

	*out = 0;
	while ((**tmp >= '0') && (**tmp <= '9'))
	{
		tmp_digit = *((*tmp)++) - '0';
		if (sign > 0)
		{
			if (*out <= (INT_MAX - tmp_digit) / 10)
				*out = 10 * (*out) + tmp_digit;
			else
				return (print_err_return_false(ERR_ATOI));
		}
		else
		{
			if (*out >= (INT_MIN + tmp_digit) / 10)
				*out = 10 * (*out) - tmp_digit;
			else
				return (print_err_return_false(ERR_ATOI));
		}
	}
	if (**tmp != '\0')
		return (print_err_return_false(ERR_ATOI));
	return (true);
}
