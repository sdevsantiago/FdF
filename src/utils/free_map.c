/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:56:03 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/14 10:28:17 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Frees the memory allocated for a 2D array of t_point structures.
 *
 * This function iterates over each row of the given array of t_point pointers,
 * frees the memory allocated for the 'color' member of each t_point,
 * then frees the t_point structure itself, and finally frees the array of
 * pointers.
 *
 * @param points A pointer to an array of pointers to t_point structures.
 * @param rows The number of rows (t_point pointers) in the array.
 */
inline void	free_map(
	t_point **points,
	size_t rows,
	size_t cols
)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			free(points[y][x].color);
			x++;
		}
		free(points[y]);
		y++;
	}
	free(points);
}
