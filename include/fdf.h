/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:55:10 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/10 14:09:59 by sede-san         ###   ########.fr       */
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

# define WINDOW_TITLE "Fdf by sede-san"
# define WINDOW_WIDTH 256
# define WINDOW_HEIGHT 256

# define ERROR_ARGS 1
# define ERROR_INVALID_FILE_EXTENSION 3
# define ERROR_UNABLE_TO_OPEN_FILE 2
# define ERROR_INVALID_MAP 4

# define HEIGHT 0
# define COLOR 1

typedef struct s_fdf_map
{
	char const		*name;
	size_t			rows;
	size_t			cols;
	long			**height_map;
	char			**color_map;
}				t_fdf_map;

typedef struct s_fdf
{
	mlx_t		*mlx;
	mlx_image_t	*map_img;
	mlx_image_t	*fps_img;
	t_fdf_map	map;
}				t_fdf;

int		check_row(char **splitted_row, t_fdf_map *map);
int		save_row(char **splitted_row, t_fdf_map *map);

/* ********************************* Utils ********************************** */

void	free_height_map(long **map, size_t rows);

#endif
