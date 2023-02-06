#include <stdbool.h>
#include "utils.h"
#include "minirt.h"
#include "rt_math.h"
#include "error.h"

bool	is_camera_in_sphere(t_scene *scene, t_sphere *sphere)
{
	double	distance_to_center;

	distance_to_center = abs_vec(diff_vec(scene->eye_pos, sphere->center));
	if (distance_to_center <= sphere->radius)
		return (true);
	return (false);
}
