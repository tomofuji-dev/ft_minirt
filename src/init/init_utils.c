/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:04:12 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/20 17:25:44 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include <stdbool.h>

t_rgb	calc_rgb_ratio(t_rgb rgb, double ratio);
bool	append_light(t_scene *scene);
bool	append_shape(t_scene *scene);
t_light	*lst_last_light(t_light *light);
t_shape	*lst_last_shape(t_shape *shape);

t_rgb	calc_rgb_ratio(t_rgb rgb, double ratio)
{
	return ((t_rgb){
		.r = ratio * rgb.r / 255,
		.g = ratio * rgb.g / 255,
		.b = ratio * rgb.b / 255,
	});
}

bool	append_light(t_scene *scene)
{
	t_light	*light;

	if (scene->light == NULL)
	{
		scene->light = ft_calloc(1, sizeof(t_light));
		light = scene->light;
	}
	else
	{
		light = lst_last_light(scene->light);
		light->next = ft_calloc(1, sizeof(t_light));
		light = light->next;
	}
	return (light != NULL);
}

bool	append_shape(t_scene *scene)
{
	t_shape	*shape;

	if (scene->shape == NULL)
	{
		scene->shape = ft_calloc(1, sizeof(t_shape));
		shape = scene->shape;
	}
	else
	{
		shape = lst_last_shape(scene->shape);
		shape->next = ft_calloc(1, sizeof(t_shape));
		shape = shape->next;
	}
	return (shape != NULL);
}

t_light	*lst_last_light(t_light *light)
{
	t_light	*cur;

	if (light == NULL)
		return (NULL);
	cur = light;
	while (cur->next != NULL)
		cur = cur->next;
	return (cur);
}

t_shape	*lst_last_shape(t_shape *shape)
{
	t_shape	*cur;

	if (shape == NULL)
		return (NULL);
	cur = shape;
	while (cur->next != NULL)
		cur = cur->next;
	return (cur);
}
