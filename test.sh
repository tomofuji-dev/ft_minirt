#!/bin/bash

# ng
echo "=== directory.rt ==="
./miniRT rt_files/ng/directory.rt || true
echo "=== .rt ==="
./miniRT rt_files/ng/.rt || true
echo "=== color_is_greater_than_intmax.rt ==="
./miniRT rt_files/ng/color_is_greater_than_intmax.rt || true
echo "=== color_is_greater.rt ==="
./miniRT rt_files/ng/color_is_greater.rt || true
echo "=== color_is_lower.rt ==="
./miniRT rt_files/ng/color_is_lower.rt || true
echo "=== color_is_not_integer.rt ==="
./miniRT rt_files/ng/color_is_not_integer.rt || true
echo "=== double_long_precision.rt ==="
./miniRT rt_files/ng/double_long_precision.rt || true
echo "=== empty.rt ==="
./miniRT rt_files/ng/empty.rt || true
echo "=== fov_is_greater.rt ==="
./miniRT rt_files/ng/empty.rt || true
echo "=== fov_is_lower.rt ==="
./miniRT rt_files/ng/empty.rt || true
echo "=== fov_is_not_integer.rt ==="
./miniRT rt_files/ng/empty.rt || true
echo "=== invalid_identifier.rt ==="
./miniRT rt_files/ng/invalid_identifier.rt || true
echo "=== light_ration_is_greater.rt ==="
./miniRT rt_files/ng/light_ration_is_greater.rt || true
echo "=== light_ration_is_lower.rt ==="
./miniRT rt_files/ng/light_ration_is_lower.rt || true
echo "=== line_with_only_spaces.rt ==="
./miniRT rt_files/ng/line_with_only_spaces.rt || true
echo "=== missing_color_value.rt ==="
./miniRT rt_files/ng/missing_color_value.rt || true
echo "=== multi_ambient.rt ==="
./miniRT rt_files/ng/multi_ambient.rt || true
echo "=== multi_camera.rt ==="
./miniRT rt_files/ng/multi_camera.rt || true
echo "=== no_ambient.rt ==="
./miniRT rt_files/ng/no_ambient.rt || true
echo "=== no_camera.rt ==="
./miniRT rt_files/ng/no_camera.rt || true
echo "=== no_extension ==="
./miniRT rt_files/ng/no_extension || true
echo "=== tabs_instead_of_spaces.rt ==="
./miniRT rt_files/ng/tabs_instead_of_spaces.rt || true
echo "=== wrong_extension.tr ==="
./miniRT rt_files/ng/wrong_extension.tr || true

# basic
./miniRT rt_files/basic/basic_cylinder.rt &
./miniRT rt_files/basic/basic_plane.rt &
./miniRT rt_files/basic/basic_sphere.rt &
./miniRT rt_files/basic/minimalist.rt &
./miniRT rt_files/basic/rotate_cylinder.rt &
./miniRT rt_files/basic/sample.rt &

# ok
./miniRT rt_files/ok/..rt &
./miniRT rt_files/ok/any_order.rt &
./miniRT rt_files/ok/camera_and_light_is_same_position.rt &
./miniRT rt_files/ok/light_on_plane.rt &
./miniRT rt_files/ok/line_breaks_head.rt &
./miniRT rt_files/ok/line_breaks_middle.rt &
./miniRT rt_files/ok/line_breaks_tail.rt &
./miniRT rt_files/ok/no_eof.rt &
./miniRT rt_files/ok/no_object.rt &
./miniRT rt_files/ok/spaces_before_identifier.rt &
