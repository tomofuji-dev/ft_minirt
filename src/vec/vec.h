/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:33:29 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/13 15:32:16 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

t_vec	init_vec(float x, float y, float z);
t_vec	diff_vec(t_vec v1, t_vec v2);
float	inner_product(t_vec v1, t_vec v2);
float	abs_vec(t_vec v);

#endif