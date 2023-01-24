/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_board.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:22:57 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/24 16:06:50 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdio.h>

bool		checker_board(double x, double y);
static int	is_even_odd(double n);

bool	checker_board(double x, double y)
{
	if (x > 0)
	{
		if (y > 0)
			return (is_even_odd(x) == is_even_odd(y));
		else
			return (!(is_even_odd(x) == is_even_odd(y)));
	}
	else
	{
		if (y > 0)
			return (!(is_even_odd(x) == is_even_odd(y)));
		else
			return ((is_even_odd(x) == is_even_odd(y)));
	}
}

static int	is_even_odd(double n)
{
	int	i;

	i = (int)n;
	if (i < 0)
		i *= -1;
	return (i % 2);
}
