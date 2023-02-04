/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:26:12 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/23 19:51:21 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdbool.h>

bool		rt_split(const char *str, char ****tp);
size_t		calc_dp_len(char **dp);
size_t		calc_tp_len(char ***tp);
void		free_tp(char ***tp);
void		free_dp(char **dp);

bool	rt_split(const char *str, char ****tp)
{
	char	**dp;
	size_t	i;

	dp = ft_split(str, ' ');
	if (dp == NULL)
		return (false);
	*tp = ft_calloc(calc_dp_len(dp) + 1, sizeof(char **));
	if (*tp == NULL)
	{
		free_dp(dp);
		return (false);
	}
	i = 0;
	while (dp[i] != NULL)
	{
		if (dp[i][ft_strlen((const char *)dp[i])-1] == ',')
		{
			printf("フリーの処理\n");
		}
		(*tp)[i] = ft_split(dp[i], ',');
		if ((*tp)[i++] == NULL)
		{
			free_tp(*tp);
			free_dp(dp);
			return (false);
		}
	}
	free_dp(dp);
	return (true);
}

size_t	calc_dp_len(char **dp)
{
	size_t	i;

	if (dp == NULL)
		return (0);
	i = 0;
	while (dp[i] != NULL)
		i++;
	return (i);
}

size_t	calc_tp_len(char ***tp)
{
	size_t	i;

	if (tp == NULL)
		return (0);
	i = 0;
	while (tp[i] != NULL)
		i++;
	return (i);
}

void	free_dp(char **dp)
{
	size_t	i;

	if (dp == NULL)
		return ;
	i = 0;
	while (dp[i] != NULL)
	{
		free(dp[i]);
		i++;
	}
	free(dp);
}

void	free_tp(char ***tp)
{
	size_t	i;

	if (tp == NULL)
		return ;
	i = 0;
	while (tp[i] != NULL)
	{
		free_dp(tp[i]);
		i++;
	}
	free(tp);
}
