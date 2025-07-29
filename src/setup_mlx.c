/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 03:52:26 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/29 17:55:34 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Initializes the MLX graphics context and window for the FdF
 * application.
 *
 * This function sets up the MLX environment, creates a window with the
 * specified dimensions and title, and ensures the window fits within the
 * monitor size. If the requested window size exceeds the monitor's dimensions,
 * it resizes the window to fit. It also creates an image buffer for rendering
 * the map and attaches it to the window. Additionally, it sets up a key event
 * hook for handling keyboard input.
 *
 * @param fdf Pointer to the `t_fdf` structure containing application state.
 *
 * @note If MLX initialization or image creation fails, the function calls
 *       the error handler and may terminate the application.
 */
void	setup_mlx(
	t_fdf *fdf
)
{
	int		width;
	int		height;

	fdf->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE, false);
	if (!fdf->mlx)
		error("MLX failed to create a window", fdf);
	mlx_get_monitor_size(0, &width, &height);
	fdf->map_img = mlx_new_image(fdf->mlx, fdf->mlx->width, fdf->mlx->height);
	if (!fdf->map_img
		|| mlx_image_to_window(fdf->mlx, fdf->map_img, 0, 0) < 0)
		error("MLX failed to create map image", fdf);
	mlx_key_hook(fdf->mlx, &key_hook, fdf);
}
