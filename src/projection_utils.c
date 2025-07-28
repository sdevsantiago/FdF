/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:47:23 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/28 16:47:25 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	find_bounds(t_map *map, double *bounds);
static void	calc_scale_offset(double *bounds, int w, int h, double *so);
static void	apply_transform(t_map *map, double scale, double ox, double oy);

void	scale_and_center_map(t_map *map, int window_width, int window_height)
{
	double	bounds[4];
	double	scale_offset[4];

	find_bounds(map, bounds);
	calc_scale_offset(bounds, window_width, window_height, scale_offset);
	apply_transform(map, scale_offset[0], scale_offset[2], scale_offset[3]);
}

static void	find_bounds(t_map *map, double *bounds)
{
	size_t	x;
	size_t	y;

	bounds[0] = map->points[0][0].x_prime;
	bounds[1] = map->points[0][0].x_prime;
	bounds[2] = map->points[0][0].y_prime;
	bounds[3] = map->points[0][0].y_prime;
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			if (map->points[y][x].x_prime < bounds[0])
				bounds[0] = map->points[y][x].x_prime;
			if (map->points[y][x].x_prime > bounds[1])
				bounds[1] = map->points[y][x].x_prime;
			if (map->points[y][x].y_prime < bounds[2])
				bounds[2] = map->points[y][x].y_prime;
			if (map->points[y][x].y_prime > bounds[3])
				bounds[3] = map->points[y][x].y_prime;
			x++;
		}
		y++;
	}
}

static void	calc_scale_offset(double *bounds, int w, int h, double *so)
{
	double	scale_x;
	double	scale_y;

	scale_x = (w * 0.8) / (bounds[1] - bounds[0]);
	scale_y = (h * 0.8) / (bounds[3] - bounds[2]);
	if (scale_x < scale_y)
		so[0] = scale_x;
	else
		so[0] = scale_y;
	so[2] = (w - (bounds[1] - bounds[0]) * so[0]) / 2.0 - bounds[0] * so[0];
	so[3] = (h - (bounds[3] - bounds[2]) * so[0]) / 2.0 - bounds[2] * so[0];
}

static void	apply_transform(t_map *map, double scale, double ox, double oy)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			map->points[y][x].x_prime *= scale;
			map->points[y][x].x_prime += ox;
			map->points[y][x].y_prime *= scale;
			map->points[y][x].y_prime += oy;
			x++;
		}
		y++;
	}
}

void	scale_and_center_map_with_zoom(t_map *map, int window_width,
	int window_height, double zoom_factor)
{
	double	bounds[4];
	double	scale_offset[4];

	find_bounds(map, bounds);
	calc_scale_offset(bounds, window_width, window_height, scale_offset);
	scale_offset[0] *= zoom_factor;
	scale_offset[2] = window_width / 2.0 - (bounds[1] + bounds[0]) / 2.0
		* scale_offset[0];
	scale_offset[3] = window_height / 2.0 - (bounds[3] + bounds[2]) / 2.0
		* scale_offset[0];
	apply_transform(map, scale_offset[0], scale_offset[2], scale_offset[3]);
}
