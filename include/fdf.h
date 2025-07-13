/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:55:10 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/11 18:59:34 by sede-san         ###   ########.fr       */
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

# define TITLE "Fdf by sede-san"

/* Window dimensions */
# define DEF_WIDTH (int32_t)1920
# define DEF_HEIGHT (int32_t)1080

# define MIN_WIDTH (int32_t)640
# define MIN_HEIGHT (int32_t)480

# define HEIGHT 0
# define COLOR 1

typedef struct s_point
{
	long	height;
	char	*color;
}				t_point;

typedef struct s_map
{
	char const	*name;
	size_t		rows;
	size_t		cols;
	long		**height_map; //TODO update to point **map
	char		**color_map;
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

//TODO handle_error function

/* ********************************* Hooks ********************************** */

void	check_keypress(mlx_key_data_t keydata, void *param);
void	update_window_size(int32_t width, int32_t height, void* param);
void	show_fps(void *param);

/* ********************************* Utils ********************************** */

void	free_height_map(long **map, size_t rows);

#endif
