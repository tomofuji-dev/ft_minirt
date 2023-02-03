#!/bin/bash

# basic
./miniRT rt_files/basic/basic_cylinder.rt &
./miniRT rt_files/basic/basic_plane.rt &
./miniRT rt_files/basic/basic_sphere.rt &
./miniRT rt_files/basic/minimalist.rt &
./miniRT rt_files/basic/rotate_cylinder.rt &
./miniRT rt_files/basic/sample.rt &
./miniRT rt_files/basic/basic_bonus.rt &

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
