/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:01:18 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/10/11 09:21:58 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	psize;
	int		buff;

	if (!s)
		return (NULL);
	buff = (int)ft_strlen(s) - (int)start;
	if (buff <= 0 || len == 0)
		return ((char *)ft_calloc(1, sizeof(char)));
	if ((size_t)buff < len)
		psize = buff;
	else
		psize = len;
	p = (char *)ft_calloc(psize + 1, sizeof(char));
	if (!p)
		return (NULL);
	ft_memcpy(p, s + start, psize);
	return (p);
}

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*p;
// 	size_t	i;

// 	if (!s)
// 		return (NULL);
// 	p = (char *)malloc((len + 1) * sizeof(char));
// 	if (!p)
// 		return (NULL);
// 	i = 0;
// 	while ((size_t)start + i < ft_strlen(s) && i < len)
// 	{
// 		p[i] = s[start + i];
// 		i++;
// 	}
// 	p[i] = '\0';
// 	return (p);
// }
