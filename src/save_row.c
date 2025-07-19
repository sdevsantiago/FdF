/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_row.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:21:18 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/15 16:55:37 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int realloc_map(t_map *map);
// static void update_color_map();

/**
 *
 */
int save_row(
	char **splitted_row,
	t_map *map)
{
	char **splitted_cell;
	size_t x;

	if (!realloc_map(map))
	{
		if (map->points)
			free_map(map->points, map->rows, map->cols);
		return (0);
	}
	x = 0;
	while (x < map->cols)
	{
		splitted_cell = ft_split(splitted_row[x], ',');
		if (!splitted_cell)
			return (free_map(map->points, map->rows, map->cols), 0);
		if (!map->angle)
		{
			map->angle = ISOMETRIC;
			map->angle_rads = map->angle * M_PI / 180.0;
			map->sin_angle = sin(map->angle_rads);
			map->cos_angle = cos(map->angle_rads);
		}
		map->points[map->rows - 1][x].x = x;
		map->points[map->rows - 1][x].y = map->rows - 1;
		map->points[map->rows - 1][x].z = ft_atol(splitted_cell[HEIGHT]);
		map->points[map->rows - 1][x].x_prime = map->points[map->rows - 1][x].x + map->cos_angle * map->points[map->rows - 1][x].z;
		map->points[map->rows - 1][x].y_prime = map->points[map->rows - 1][x].y + map->sin_angle * map->points[map->rows - 1][x].z;
		if (splitted_cell[COLOR])
			map->points[map->rows - 1][x].color = ft_strdup(ft_strchr(splitted_cell[COLOR], ',') + 1);
		else
			map->points[map->rows - 1][x].color = ft_strdup("0xFFFFFF");
		if (!map->points[map->rows - 1][x].color)
		{
			free_map(map->points, map->rows, map->cols);
			ft_free_split(splitted_cell);
			return (0);
		}
		ft_free_split(splitted_cell);
		x++;
	}
	return (1);
}

/**
 * @param[in] map
 */
static int realloc_map(
	t_map *map)
{
	t_point **new_map;
	size_t x;
	size_t y;

	new_map = (t_point **)malloc(map->rows * sizeof(t_point *));
	if (!new_map)
		return (0);
	y = 0;
	if (map->points)
	{
		while (y < map->rows - 1)
		{
			new_map[y] = (t_point *)malloc(map->cols * sizeof(t_point));
			if (!new_map[y])
				return (free_map(new_map, y, map->cols), 0);
			x = 0;
			while (x < map->cols)
			{
				new_map[y][x].x = map->points[y][x].x;
				new_map[y][x].y = map->points[y][x].y;
				new_map[y][x].z = map->points[y][x].z;
				new_map[y][x].x_prime = map->points[y][x].x_prime;
				new_map[y][x].y_prime = map->points[y][x].y_prime;
				new_map[y][x].color = ft_strdup(map->points[y][x].color);
				if (!new_map[y][x].color)
					return (free_map(new_map, map->rows, map->cols), 1);
				x++;
			}
			y++;
		}
	}
	new_map[y] = (t_point *)malloc(map->cols * sizeof(t_point));
	if (!new_map[y])
		return (free_map(new_map, map->rows, map->cols), 0);
	return (free_map(map->points, map->rows - 1, map->cols), map->points = new_map, 1);
}

// static void dup_color_map();

// static void free_maps();
