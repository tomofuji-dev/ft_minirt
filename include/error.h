/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:55:32 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/25 12:55:39 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERR_ARGC			"not valid argc."
# define ERR_AMBIENT_LIGHT	"ambient light is already exist."
# define ERR_CAMERA			"camera is already exist."
# define ERR_COL_FORMAT		"wrong column format."
# define ERR_STRTOD			"error in strtod."
# define ERR_ATOI			"error in atoi."
# define ERR_RANGE			"error about value range."
# define ERR_RGB			"wrong rgb."
# define ERR_VEC			"wrong vector."
# define ERR_NORM_VEC		"this vec is need to norm, but abs == 0."
# define ERR_MALLOC			"error in malloc."
# define ERR_INIT_MLX		"failed to init mlx."
# define ERR_INIT_WINDOW	"failed to create new window."
# define ERR_INIT_IMG		"failed to create new img."
# define ERR_FNAME			"invalid fname."
# define ERR_FD				"invalid fd."
# define ERR_GNL			"error in gnl."
# define ERR_NO_AMB_CAM		"no ambient light or camera."
# define ERR_IDENTIFIER		"invalid identifier."

#endif