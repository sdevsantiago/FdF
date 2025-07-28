/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_row.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:21:18 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/28 18:21:47 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	realloc_map(t_map *map);
static void	process_cell(char **splitted_row, t_map *map, size_t x);
static void	set_coords(t_point *point, size_t x, size_t y, size_t z);
static int	copy_old_rows(t_map *map, t_point **new_map);

int	save_row(
	char **splitted_row,
	t_map *map)
{
	size_t	x;

	if (!realloc_map(map))
	{
		if (map->points)
			free_map(map->points, map->rows);
		return (0);
	}
	x = 0;
	while (x < map->cols)
	{
		process_cell(splitted_row, map, x);
		x++;
	}
	return (1);
}

static void	process_cell(char **splitted_row, t_map *map, size_t x)
{
	char	**splitted_cell;

	splitted_cell = ft_split(splitted_row[x], ',');
	if (!splitted_cell)
	{
		free_map(map->points, map->rows);
		return ;
	}
	set_coords(&map->points[map->rows - 1][x],
		x, map->rows - 1, ft_atol(splitted_cell[HEIGHT]));
	set_point_color(&map->points[map->rows - 1][x], splitted_cell[COLOR]);
	ft_free_split(splitted_cell);
}

static int	realloc_map(
	t_map *map)
{
	t_point	**new_map;
	size_t	y;

	new_map = (t_point **)malloc(map->rows * sizeof(t_point *));
	if (!new_map)
		return (0);
	if (map->points && !copy_old_rows(map, new_map))
		return (0);
	y = map->rows - 1;
	if (!map->points)
		y = 0;
	new_map[y] = (t_point *)malloc(map->cols * sizeof(t_point));
	if (!new_map[y])
		return (free_map(new_map, map->rows),
			free_map(map->points, map->rows - 1), 0);
	return (free_map(map->points, map->rows - 1), map->points = new_map, 1);
}

static int	copy_old_rows(t_map *map, t_point **new_map)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < map->rows - 1)
	{
		new_map[y] = (t_point *)malloc(map->cols * sizeof(t_point));
		if (!new_map[y])
			return (0);
		x = 0;
		while (x < map->cols)
		{
			ft_memcpy(&new_map[y][x], &map->points[y][x], sizeof(t_point));
			x++;
		}
		y++;
	}
	return (1);
}

/**
 * @brief Sets the coordinates and their isometric projections for a point.
 *
 * This function initializes the x, y, and z coordinates of the given t_point
 * structure. It also calculates the isometric projection coordinates (x_prime
 * and y_prime) using the provided x, y, and z values, along with the
 * COS_ISOMETRIC and SIN_ISOMETRIC constants.
 *
 * Isometric projection formula:
 * x' = (x - y) * cos(30°)
 * y' = (x + y) * sin(30°) - z
 *
 * Where:
 * - cos(30°) = √3/2 ≈ 0.866
 * - sin(30°) = 1/2 = 0.5
 *
 * @param point Pointer to the t_point structure to be initialized.
 * @param x The x-coordinate value.
 * @param y The y-coordinate value.
 * @param z The z-coordinate value.
 */
static void	set_coords(
	t_point *point,
	size_t x,
	size_t y,
	size_t z
)
{
	point->x = x;
	point->y = y;
	point->z = z;
	point->x_prime = ((double)point->x - (double)point->y) * COS_ISOMETRIC;
	point->y_prime = ((double)point->x + (double)point->y) * SIN_ISOMETRIC
		- (double)point->z;
}
