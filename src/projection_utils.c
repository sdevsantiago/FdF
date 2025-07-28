/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:47:23 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/28 19:50:28 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	find_bounds(t_map *map, double *bounds);
static void	calc_scale_offset(double *bounds, int w, int h, double *so);
static void	apply_transform(t_map *map, double scale, double ox, double oy);

/**
 * Scales and centers the map within the specified window dimensions.
 *
 * This function calculates the bounds of the map, determines the appropriate
 * scaling factor and offsets to fit the map within the window, and applies
 * the transformation to the map coordinates.
 *
 * @param map           Pointer to the map structure to be transformed.
 * @param window_width  Width of the window in which the map will be displayed.
 * @param window_height Height of the window in which the map will be displayed.
 */
void	scale_and_center_map(t_map *map, int window_width, int window_height)
{
	double	bounds[4];
	double	scale_offset[4];

	find_bounds(map, bounds);
	calc_scale_offset(bounds, window_width, window_height, scale_offset);
	apply_transform(map, scale_offset[0], scale_offset[2], scale_offset[3]);
}

/**
 * @brief Finds the minimum and maximum x' and y' coordinates in a map.
 *
 * This function iterates over all points in the given map and determines the
 * smallest and largest values of the x_prime and y_prime fields. The results
 * are stored in the bounds array as follows:
 *   bounds[0] - minimum x_prime
 *   bounds[1] - maximum x_prime
 *   bounds[2] - minimum y_prime
 *   bounds[3] - maximum y_prime
 *
 * @param map Pointer to the t_map structure containing the points.
 * @param bounds Array of 4 doubles where the results will be stored.
 */
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

/**
 * @brief Calculates the optimal scale and offset for projecting a set of bounds
 * onto a 2D viewport.
 *
 * This function computes the scaling factor and offset required to fit a
 * rectangular region, defined by `bounds`, into a viewport of width `w` and
 * height `h`. The scaling preserves the aspect ratio and ensures the region
 * fits within 80% of the viewport dimensions.
 *
 * @param bounds Pointer to an array of 4 doubles representing the region to
 *               project:
 *               bounds[0] = min_x,
 *               bounds[1] = max_x,
 *               bounds[2] = min_y,
 *               bounds[3] = max_y.
 * @param w      Width of the viewport.
 * @param h      Height of the viewport.
 * @param so     Pointer to an array of doubles where results are stored:
 *               so[0] = scale factor,
 *               so[2] = x offset,
 *               so[3] = y offset.
 */
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

/**
 * @brief Applies a scaling and translation transformation to all points in the
 * map.
 *
 * This function iterates over each point in the given map and modifies its
 * `x_prime` and `y_prime` coordinates by first scaling them by the specified
 * `scale` factor and then translating them by the offsets `ox` (for x) and
 * `oy` (for y).
 *
 * @param map Pointer to the t_map structure containing the points to transform.
 * @param scale The scaling factor to apply to each point's coordinates.
 * @param ox The offset to add to each point's x coordinate after scaling.
 * @param oy The offset to add to each point's y coordinate after scaling.
 */
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
