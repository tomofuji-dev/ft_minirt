/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:07:56 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/02/03 12:28:59 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "init.h"
#include "hook.h"
#include "utils.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// void	s(int s)
// {
// 	if (s == SIGINT)
// 		exit(0);
// }

// embed the following code to main.
// signal(SIGINT, &s);

int	main(int argc, char *argv[])
{
	t_env		env;

	if (argc != 2)
		perror_exit(ERR_ARGC, false);
	init_scene(&env, argv[1]);
	init_mlx(&env, argv[1]);
	setup_hook(&env);
	close_env(&env);
}

// __attribute__((destructor))
// static void	destructor(void)
// {
// 	system("leaks -q minirt");
// }
