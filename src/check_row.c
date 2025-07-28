/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_row.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 02:06:53 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/28 18:12:31 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	is_valid_height(char *height);
static int	is_valid_color(char *color);

/**
 * @brief Validates a row of map data and updates map dimensions.
 *
 * This function checks each cell in the given row (splitted_row) to ensure
 * that the height and optional color values are valid. It splits each cell
 * by ',' to separate height and color, then validates them using
 * is_valid_height() and is_valid_color(). If any cell is invalid, the
 * function returns 0. If the row is valid, it updates the map's column count
 * (map->cols) if not already set, and ensures all rows have the same number
 * of columns. It also increments the map's row count (map->rows).
 *
 * @param splitted_row Array of strings representing the cells in the row.
 * @param map Pointer to the map structure to update dimensions.
 *
 * @return int Returns 1 if the row is valid and dimensions are updated,
 *             otherwise returns 0.
 */
int	check_row(
	char **splitted_row,
	t_map *map
)
{
	size_t	cols;
	char	**splitted_cell;

	cols = 0;
	while (splitted_row[cols] && *splitted_row[cols] != '\n')
	{
		splitted_cell = ft_split(splitted_row[cols], ',');
		if (!splitted_cell)
			return (0);
		if (!is_valid_height(splitted_cell[HEIGHT])
			|| (splitted_cell[COLOR] && !is_valid_color(splitted_cell[COLOR])))
			return (ft_free_split(splitted_cell), 0);
		cols++;
		ft_free_split(splitted_cell);
	}
	if (!map->cols)
		map->cols = cols;
	else if (map->cols != cols)
		return (0);
	map->rows++;
	return (1);
}

/**
 * @brief Checks if the given string represents a valid integer height value.
 *
 * This function trims leading and trailing spaces and newlines from the input
 * string, then verifies if the resulting string is a valid integer. It allows
 * an optional '+' or '-' sign at the beginning, followed by one or more digits.
 *
 * @param height The string to validate as an integer height.
 * @return 1 if the string is a valid integer height, 0 otherwise.
 */
static int	is_valid_height(
	char *height
)
{
	unsigned int	i;
	char			*trimmed_height;

	i = 0;
	trimmed_height = ft_strtrim(height, " \n");
	if (trimmed_height[i] == '+' || trimmed_height[i] == '-')
	{
		i++;
		if (!trimmed_height[i])
			return (free(trimmed_height), 0);
	}
	while (trimmed_height[i])
	{
		if (!ft_isdigit(trimmed_height[i]))
			return (free(trimmed_height), 0);
		i++;
	}
	return (free(trimmed_height), 1);
}

/**
 * @brief Checks if a given string represents a valid hexadecimal color value.
 *
 * This function trims whitespace and newline characters from the input string,
 * then verifies that the string starts with "0x" and that all subsequent
 * characters are valid hexadecimal digits (0-9, A-F).
 * The check is case-insensitive.
 *
 * @param color The input string to validate as a hexadecimal color.
 *
 * @return 1 if the string is a valid hexadecimal color, 0 otherwise.
 */
static int	is_valid_color(
	char *color
)
{
	unsigned int	i;
	char			*trimmed_color;

	trimmed_color = ft_strtrim(color, " \n");
	if (!trimmed_color || trimmed_color[0] != '0' || trimmed_color[1] != 'x')
		return (0);
	i = 2;
	while (trimmed_color[i])
	{
		trimmed_color[i] = ft_toupper(trimmed_color[i]);
		if (!ft_isdigit(trimmed_color[i])
			&& trimmed_color[i] != 'A'
			&& trimmed_color[i] != 'B'
			&& trimmed_color[i] != 'C'
			&& trimmed_color[i] != 'D'
			&& trimmed_color[i] != 'E'
			&& trimmed_color[i] != 'F')
			return (free(trimmed_color), 0);
		i++;
	}
	return (free(trimmed_color), 1);
}
