/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:55:10 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/15 17:17:24 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "MLX42.h"
# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>		// perror
# include <stdlib.h>	// exit
# include <string.h>	// strerror

# define TITLE "FdF by sede-san"

/* Window dimensions */
# define DEF_WIDTH (int32_t)1920
# define DEF_HEIGHT (int32_t)1080
# define MIN_WIDTH (int32_t)640
# define MIN_HEIGHT (int32_t)480

# define ISOMETRIC 30.0

# define HEIGHT 0
# define COLOR 1

/* Errors */
# define ENARGS 3
# define EFILEEXT 4
# define ENOMAP 5
# define EINVMAP 6
/**
 * ENOENT = 2
 * ENOMEM = 12
 * EACCESS = 13
 * EMFILE = 14
 */

typedef struct s_point
{
	size_t	x;
	double	x_prime;
	size_t	y;
	double	y_prime;
	long	z;
	char	*color;
}				t_point;

/**
 * When perspective is isometric, the sum of all 3 angles is 120,
 * use 30 as angle value
 */
typedef struct s_map
{
	char const	*name;
	size_t		rows;
	size_t		cols;
	t_point		**points;
	double		angle;
	double		angle_rads;
	double		cos_angle;
	double		sin_angle;
	double		x_prime;
}				t_map;

typedef struct s_monitor
{
	int32_t	height;
	int32_t	width;
}				t_monitor;

typedef struct s_fdf
{
	mlx_t		*mlx;
	t_map		map;
	mlx_image_t	*map_img;
	mlx_image_t	*fps_img;
	t_monitor	monitor;
}				t_fdf;

void	setup_mlx(t_fdf *fdf);
int		check_row(char **splitted_row, t_map *map);
int		save_row(char **splitted_row, t_map *map);

void	draw_map_bresenham(t_map *map, mlx_image_t *map_img);

/* ********************************* Hooks ********************************** */

void	check_keypress(mlx_key_data_t keydata, void *param);
void	update_window_size(int32_t width, int32_t height, void* param);
void	show_fps(void *param);

/* ********************************* Utils ********************************** */

void	free_map(t_point **points, size_t rows, size_t cols);
void	handle_error(int error);

#endif
