/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 03:52:26 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/13 13:30:58 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	setup_window_monitor(t_fdf *fdf);
static void	setup_hooks(t_fdf *fdf);

void	setup_mlx(
	t_fdf *fdf
)
{
	fdf->mlx = mlx_init(DEF_WIDTH, DEF_HEIGHT, TITLE, true);
	if (!fdf->mlx)
	{
		ft_eputendl("MLX failed to create a window.");
		exit(EXIT_FAILURE);
	}
	fdf->fps_img = mlx_new_image(fdf->mlx, 100, 100);
	if (!fdf->fps_img || mlx_image_to_window(fdf->mlx, fdf->fps_img, 10, 10) < 0)
	{
		ft_eputendl("Cagaste");
		exit(EXIT_FAILURE);
	}
	setup_window_monitor(fdf);
	setup_hooks(fdf);
}

static void	setup_window_monitor(
	t_fdf *fdf
)
{
	mlx_set_window_limit(fdf->mlx, MIN_WIDTH, MIN_HEIGHT, -1, -1);
	mlx_get_monitor_size(0, &fdf->monitor.width, &fdf->monitor.height);
	if (!fdf->monitor.width || !fdf->monitor.width)
	{
		ft_eputendl("MLX failed to get monitor size.");
		exit(EXIT_FAILURE);
	}
	else if (fdf->monitor.width < MIN_WIDTH || fdf->monitor.height < MIN_HEIGHT)
	{
		ft_eputendl("Screen is too small.");
		exit(EXIT_FAILURE);
	}
	mlx_set_window_size(fdf->mlx, fdf->monitor.width, fdf->monitor.height);
}

/**
 * @brief Sets up event hooks for the MLX window.
 *
 * This function registers callback functions for key press events,
 * window resize events, and the main loop hook to display FPS.
 *
 * @param fdf Pointer to the main FDF structure containing MLX and monitor data.
 */
static void	setup_hooks(
	t_fdf *fdf
)
{
	mlx_key_hook(fdf->mlx, &check_keypress, fdf->mlx);
	mlx_resize_hook(fdf->mlx, &update_window_size, &fdf->monitor);
	mlx_loop_hook(fdf->mlx, &show_fps, fdf);
}
