/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:55:10 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/29 14:31:29 by sede-san         ###   ########.fr       */
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
# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 1024

# define ISOMETRIC 30.0
# define COS_ISOMETRIC 0.86602540378443870761060452423407696187496185302734375
# define SIN_ISOMETRIC 0.5

# define HEIGHT 0
# define COLOR 1

/* Errors */
# define ENARGS 1003
# define EFILEEXT 1004
# define EINVMAP 1005
/**
 * ENOENT = 2
 * ENOMEM = 12
 * EACCESS = 13
 * EMFILE = 14
 */

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
}				t_color;

typedef struct s_point
{
	size_t	x;
	double	x_prime;
	size_t	y;
	double	y_prime;
	long	z;
	t_color	color;
}				t_point;

typedef struct s_map
{
	int			fd;
	size_t		rows;
	size_t		cols;
	t_point		**points;
	double		x_prime;
	long		min_z;
	long		max_z;
	double		view;
}				t_map;

typedef struct s_fdf
{
	mlx_t		*mlx;
	t_map		map;
	mlx_image_t	*map_img;
}				t_fdf;

void	setup_mlx(t_fdf *fdf);
int		check_row(char **splitted_row, t_map *map);
int		save_row(char **splitted_row, t_map *map);

void	render_map(t_map *map, mlx_image_t *map_img);
void	apply_isometric_projection(t_point *point);
void	apply_isometric_projection_with_transforms(t_point *point, double zoom,
			double rotation_z);
void	scale_and_center_map(t_map *map, int window_width, int window_height);
void	draw_line_init(t_point a, t_point b, int *params);
void	draw_pixel(int x, int y, int color, mlx_image_t *map_img);
void	bresenham_step(int *params);
// int		interpolate_color(int color1, int color2, float ratio);
void	set_point_color(t_point *point, char *color);

/* ********************************* Hooks ********************************** */

void	key_hook(mlx_key_data_t keydata, void *param);

/* ********************************* Utils ********************************** */

void	free_map(t_point **points, size_t rows);
int		get_rgba(int r, int g, int b, int a);

/* ********************************* Error ********************************** */

void	error(const char *err_msg, t_fdf *fdf);

#endif
