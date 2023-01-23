/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:47:15 by t.fuji            #+#    #+#             */
/*   Updated: 2023/01/23 17:37:38 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"

bool			rt_strtod(const char *string, double *out);
static bool		strtod_count_digits(const char *string, t_strtod *sd);
static bool		strtod_get_frac(t_strtod *sd);
static int		strtod_frac_splited(t_strtod *sd, int mant_size_limit);
static double	strtod_exp_frac(t_strtod *sd);

bool	rt_strtod(const char *string, double *out)
{
	t_strtod	sd;

	ft_bzero(&sd, sizeof(t_strtod));
	if (!strtod_count_digits(string, &sd))
		return (false);
	if (!strtod_get_frac(&sd))
		return (false);
	*out = strtod_exp_frac(&sd);
	if (sd.sign)
		*out *= -1;
	return (true);
}

static bool	strtod_count_digits(const char *string, t_strtod *sd)
{
	sd->p = string;
	while (ft_isspace(*sd->p))
		sd->p++;
	if (*sd->p == '-')
	{
		sd->sign = true;
		sd->p++;
	}
	else if (*sd->p == '+')
		sd->p++;
	sd->dec_pt = -1;
	while (true)
	{
		if (!ft_isdigit(*sd->p))
		{
			if (*sd->p != '.' || sd->dec_pt >= 0)
				break ;
			sd->dec_pt = sd->mant_size;
		}
		sd->p++;
		sd->mant_size++;
	}
	return (*sd->p == '\0');
}

static bool	strtod_get_frac(t_strtod *sd)
{
	sd->p -= sd->mant_size;
	if (sd->dec_pt < 0)
		sd->dec_pt = sd->mant_size;
	else
		sd->mant_size--;
	if (sd->mant_size == 0 || sd->mant_size > 18 \
		|| sd->mant_size - sd->dec_pt > 6)
		return (false);
	else
	{
		sd->frac_exp = sd->dec_pt - sd->mant_size;
		sd->frac1 = strtod_frac_splited(sd, 9);
		sd->frac2 = strtod_frac_splited(sd, 0);
		sd->fraction = (1.0e9 * sd->frac1) + sd->frac2;
		return (true);
	}
}

static int	strtod_frac_splited(t_strtod *sd, int mant_size_limit)
{
	char	c;
	int		ret_frac;

	ret_frac = 0;
	while (sd->mant_size > mant_size_limit)
	{
		c = *sd->p;
		sd->p++;
		if (c == '.')
		{
			c = *sd->p;
			sd->p++;
		}
		ret_frac = 10 * ret_frac + (c - '0');
		sd->mant_size--;
	}
	return (ret_frac);
}

static double	strtod_exp_frac(t_strtod *sd)
{
	const double	*d;
	const double	powers10[] = {
		10., 100., 1.0e4, 1.0e8, 1.0e16, 1.0e32, 1.0e64, 1.0e128, 1.0e256
	};

	if (sd->frac_exp < 0)
	{
		sd->exp_sign = true;
		sd->frac_exp = -1 * sd->frac_exp;
	}
	else
		sd->exp_sign = false;
	sd->exp = 1.0;
	d = powers10;
	while (sd->frac_exp != 0)
	{
		if (sd->frac_exp & 01)
			sd->exp *= *d;
		sd->frac_exp >>= 1;
		d++;
	}
	if (sd->exp_sign)
		return (sd->fraction / sd->exp);
	else
		return (sd->fraction * sd->exp);
}
