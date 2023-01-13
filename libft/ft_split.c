/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:32:21 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/10/11 08:56:39 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ret_doublep(char const *s, char c)
{
	size_t	i;
	int		splen;

	if (!s)
		return (NULL);
	i = 0;
	splen = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			splen++;
		while (s[i] && (s[i] != c))
			i++;
	}
	return ((char **)ft_calloc(splen + 1, sizeof(char *)));
}

static char	*ft_strndup(const char *s, size_t n)
{
	char	*str;

	str = (char *)ft_calloc(n + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s, n);
	return (str);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	sp_ind;
	char	**sp;

	i = 0;
	sp_ind = 0;
	sp = ret_doublep(s, c);
	if (sp == NULL)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > j)
		{
			sp[sp_ind] = ft_strndup(s + j, i - j);
			sp_ind++;
		}
	}
	return (sp);
}
