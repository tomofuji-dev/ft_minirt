/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:07:56 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/23 19:52:55 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "init.h"
#include "hook.h"
#include "utils.h"
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
		perror_exit("not valid argc");
	init_scene(&env, argv[1]);
	print_scene(env.scene);
	init_mlx(&env);
	setup_hook(&env);
}

__attribute__((destructor))
static void	destructor(void)
{
	system("leaks -q minirt");
}
