/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 13:17:17 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/10/08 12:00:00 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*usp;
	unsigned char	uc;

	usp = (unsigned char *) s;
	uc = (unsigned char) c;
	while (n-- > 0)
	{
		if (*usp == uc)
			return (usp);
		usp++;
	}
	return (NULL);
}
