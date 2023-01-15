/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:07:56 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/15 18:13:10 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hook.h"
#include "init.h"
#include "minirt.h"

int	main(void)
{
	t_env		env;

	init(&env);
	setup_hook(&env);
}
