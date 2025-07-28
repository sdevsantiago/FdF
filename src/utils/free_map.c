/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:33 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/27 16:30:52 by sede-san         ###   ########.fr       */
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
 * @param points A pointer to a structure containing all map info.
 * @param rows
 */
void	free_map(
	t_point **points,
	size_t	rows
)
{
	size_t	i;

	i = 0;
	while (i < rows)
	{
		free(points[i]);
		i++;
	}
	free(points);
}
