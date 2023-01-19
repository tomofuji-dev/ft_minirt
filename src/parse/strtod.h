/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtod.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:39:02 by t.fuji            #+#    #+#             */
/*   Updated: 2023/01/19 13:50:27 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRTOD_H
# define STRTOD_H

# include <stdbool.h>

typedef struct s_strtod {
	bool		sign;
	bool		exp_sign;
	double		fraction;
	double		exp;
	const char	*p;
	int			frac_exp;
	int			mant_size;
	int			dec_pt;
	int			frac1;
	int			frac2;
}	t_strtod;

bool	rt_strtod(const char *string, double *out_d);

#endif