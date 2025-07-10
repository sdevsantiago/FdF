/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_row.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:21:18 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/11 01:06:22 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	realloc_height_map(t_fdf_map *map);
// static void update_color_map();

/**
 *
 */
int	save_row(
	char **splitted_row,
	t_fdf_map *map
)
{
	char	**splitted_cell;
	size_t	x;

	if (!realloc_height_map(map))
	{
		if (map->height_map)
			free_height_map(map->height_map, map->rows);
		return (0);
	}
	x = 0;
	while (x < map->cols)
	{
		splitted_cell = ft_split(splitted_row[x], ',');
		if (!splitted_cell)
			return (free_height_map(map->height_map, map->rows), 0);
		map->height_map[map->rows - 1][x] = ft_atol(splitted_cell[HEIGHT]);
		ft_free_split(splitted_cell);
		x++;
	}
	return (1);
}

/**
 * @param[in] map
 */
static int	realloc_height_map(
	t_fdf_map *map
)
{
	long	**new_height_map;
	size_t	x;
	size_t	y;

	new_height_map = (long **)malloc(map->rows * sizeof(long *));
	if (!new_height_map)
		return (0);
	y = 0;
	if (map->height_map)
	{
		while (y < map->rows - 1)
		{
			new_height_map[y] = (long *)malloc(map->cols * sizeof(long));
			if (!new_height_map[y])
				return (free_height_map(new_height_map, y), 0);
			x = 0;
			while (x < map->cols)
			{
				new_height_map[y][x] = map->height_map[y][x];
				x++;
			}
			y++;
		}
	}
	new_height_map[y] = (long *)malloc(map->cols * sizeof(long));
	if (!new_height_map[y])
		return (free_height_map(new_height_map, map->rows), 0);
	return (free_height_map(map->height_map, map->rows - 1),
		map->height_map = new_height_map, 1);
}

// static void dup_color_map();

// static void free_maps();
