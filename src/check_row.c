/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_row.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 02:06:53 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/11 18:22:20 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	is_valid_height(char *height);
static int	is_valid_color(char *color);

/**
 * @brief Checks that the row passed is valid.
 *
 * This function verifies that the row passed contains the correct number of
 * points and that none of them contain invalid characters.
 *
 * @param[in] splitted_row
 * @param[in,out] map
 *
 * @return Returns 1 if the passed row is valid and 0 if not.
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
