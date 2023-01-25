/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_for_gnl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 10:36:32 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/25 12:52:40 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	print_dp(char **dp)
{
	size_t	i;

	i = 0;
	while (dp[i] != NULL)
	{
		printf("%s ", dp[i]);
		i++;
	}
	printf("\n");
}

void	print_splited(char ***splited)
{
	size_t	i;

	i = 0;
	while (splited[i] != NULL)
	{
		printf("-----\n");
		print_dp(splited[i]);
		i++;
	}
}
