/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:46:02 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/10/11 08:18:31 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t		len;
	char		*p;

	len = ft_strlen(s1) + 1;
	p = ft_calloc(len, sizeof(char));
	if (!p)
		return (NULL);
	ft_memcpy(p, s1, len);
	return (p);
}
