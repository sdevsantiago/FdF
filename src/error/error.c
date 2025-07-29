/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 04:39:39 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/29 19:34:44 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	is_custom_error(void);
static void	show_custom_error_info(void);

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
	if (is_custom_error())
		show_custom_error_info();
	else
		ft_eputendl(strerror(errno));
	exit(errno);
}

static int	is_custom_error(void)
{
	return (errno == ENARGS || errno == EFILEEXT || errno == EINVMAP);
}

static void	show_custom_error_info(void)
{
	if (errno == ENARGS || errno == EFILEEXT)
	{
		ft_eputendl("Usage: ./fdf <path-to-map>");
		errno = 1;
	}
	else if (errno == EINVMAP)
	{
		ft_eputendl("Check for illegal characters, format must be like shown:");
		ft_eputendl("[Height],[Color] -> 10,0xFF00AA");
	}
}
