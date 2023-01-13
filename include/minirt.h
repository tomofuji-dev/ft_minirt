/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 09:28:41 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/13 15:40:33 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stddef.h>
# include <stdbool.h>
# include <stdint.h>

# define WINDOW_WIDTH 400
# define WINDOW_HEIGHT 400
# define WINDOW_TITLE "minirt"

typedef struct s_vec {
	float	x;
	float	y;
	float	z;
}	t_vec;

typedef struct s_env {
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*img_data;
	int			bits_per_pixel;
	int			bytes_per_pixel;
	int			bytes_per_line;
	int			endian;
}	t_env;

#endif