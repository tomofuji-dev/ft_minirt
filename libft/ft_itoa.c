/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:38:38 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/10/08 08:44:52 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	cnt_digits(int n)
{
	int	digits;

	digits = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		digits++;
	while (n != 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	int		head;
	int		tail;
	long	ln;
	char	*toa;

	head = 0;
	tail = cnt_digits(n);
	toa = ft_calloc(tail + 1, sizeof(char));
	if (!toa)
		return (NULL);
	ln = (long) n;
	if (ln < 0)
	{
		toa[0] = '-';
		head = 1;
		ln *= -1;
	}
	while (tail-- > head)
	{
		toa[tail] = ln % 10 + '0';
		ln = (ln - ln % 10) / 10;
	}
	return (toa);
}
