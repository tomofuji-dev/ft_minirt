/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:32:38 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/13 17:32:50 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	min(float x, float y)
{
	if (x <= y)
		return (x);
	else
		return (y);
}

float	max(float x, float y)
{
	if (x >= y)
		return (x);
	else
		return (y);
}
