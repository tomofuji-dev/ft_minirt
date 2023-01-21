/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:47:00 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/20 14:46:52 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdbool.h>

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
				return (false);
		}
		else
		{
			if (*out >= (INT_MIN + tmp_digit) / 10)
				*out = 10 * (*out) - tmp_digit;
			else
				return (false);
		}
	}
	if (**tmp != '\0')
		return (false);
	*out *= sign;
	return (true);
}
