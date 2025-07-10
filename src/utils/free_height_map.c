/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_height_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:56:03 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/10 14:09:37 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

inline void	free_height_map(
	long **height_map,
	size_t rows
)
{
	size_t	y;

	y = 0;
	while (y < rows)
		free(height_map[y++]);
	free(height_map);
}
