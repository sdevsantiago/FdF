/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 04:39:39 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/28 18:12:56 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Handles error reporting, resource cleanup, and program termination.
 *
 * This function prints an error message, frees allocated resources associated
 * with the provided t_fdf structure, and terminates the program with an exit
 * code based on errno. It closes the map file descriptor, frees the map points,
 * deletes the map image, and terminates the MLX context if they exist.
 *
 * @param err_msg The error message to display.
 * @param fdf Pointer to the t_fdf structure containing resources to clean up.
 */
void	error(const char *err_msg, t_fdf *fdf)
{
	if (fdf->map.fd > 0)
		close(fdf->map.fd);
	if (fdf->map.points)
		free_map(fdf->map.points, fdf->map.rows);
	if (fdf->map_img)
		mlx_delete_image(fdf->mlx, fdf->map_img);
	if (fdf->mlx)
		mlx_terminate(fdf->mlx);
	ft_eputstr(RED_TEXT"ERROR: ");
	ft_eputstr((char *)err_msg);
	ft_eputendl(RESET);
	if (errno)
		ft_eputendl(strerror(errno));
	else
		errno = 1;
	exit(errno);
}
