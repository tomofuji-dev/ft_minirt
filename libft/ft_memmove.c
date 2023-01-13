/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:27:55 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/10/06 10:26:37 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*dp;
	const unsigned char	*sp;

	if (!dst && !src)
		return (NULL);
	dp = dst;
	sp = src;
	if (dp > sp)
	{
		while (n-- > 0)
			dp[n] = sp[n];
	}
	else
	{
		while (n-- > 0)
			*dp++ = *sp++;
	}
	return (dst);
}
