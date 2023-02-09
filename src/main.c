/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:07:56 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/02/03 18:19:09 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "init.h"
#include "hook.h"
#include "utils.h"
#include "error.h"
#include "draw.h"

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
	draw(&env);
	setup_hook(&env);
	close_env(&env);
}

// __attribute__((destructor))
// static void	destructor(void)
// {
// 	system("leaks -q minirt");
// }
