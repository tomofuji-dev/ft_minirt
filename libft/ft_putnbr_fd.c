/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 19:02:55 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/10/08 19:21:54 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	un;

	if (n < 0)
	{	
		ft_putchar_fd('-', fd);
		un = -n;
	}
	else
		un = n;
	if (un >= 10)
	{	
		ft_putnbr_fd(un / 10, fd);
		un = un % 10;
	}	
	ft_putchar_fd(un + '0', fd);
}
