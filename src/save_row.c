/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_row.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:21:18 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/29 18:22:31 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	realloc_map(t_map *map);
static void	process_cell(char **splitted_row, t_map *map, size_t x);
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
	set_color(&map->points[map->rows - 1][x], splitted_cell[COLOR]);
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
