#include <stdbool.h>
#include "utils.h"
#include "minirt.h"
#include "rt_math.h"
#include "error.h"

bool	is_camera_in_sphere(t_scene *scene, t_sphere *sphere)
{
	double	dist_to_center;

	dist_to_center = abs_vec(diff_vec(scene->eye_pos, sphere->center));
	if (dist_to_center <= sphere->radius)
		return (true);
	return (false);
}

bool	is_camera_in_cylinder(t_scene *scene, t_cylinder *cy)
{
	double	shortest_dist_to_axis;
	double	h;

	h = inner_product(diff_vec(scene->eye_pos, cy->position), cy->direction);

	if (- cy->height / 2 <= h && h <= cy->height / 2)
	{
		shortest_dist_to_axis = abs_vec(diff_vec(scene->eye_pos, \
			add_vec(cy->position, constant_mul_vec(norm_vec(cy->direction), \
			inner_product(diff_vec(scene->eye_pos, cy->position),\
            norm_vec(cy->direction))))));
		if (shortest_dist_to_axis <= cy->radius)
			return (true);
	}
	return (false);
}
