/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:43:03 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/10/11 09:25:56 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in(char const c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*p;

	if (!s1 || !set)
		return (NULL);
	if (ft_strlen(s1) == 0)
		return (ft_calloc(1, sizeof(char)));
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && is_in(s1[start], set))
		start++;
	while (start < end && is_in(s1[end], set))
		end--;
	p = ft_calloc(end - start + 2, sizeof(char));
	if (!p)
		return (NULL);
	ft_memcpy(p, s1 + start, end - start + 1);
	return (p);
}
