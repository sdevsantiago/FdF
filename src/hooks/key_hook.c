/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 02:08:19 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/29 12:32:02 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	switch_view(t_fdf *fdf);

/**
 * @brief Handles keyboard input events for the application.
 *
 * This function is called whenever a key event occurs. It checks if the
 * pressed key is the Escape key (MLX_KEY_ESCAPE). If so, it closes the
 * application's window.
 *
 * @param keydata The key event data, containing information about the key
 * pressed.
 * @param param A pointer to the application's main data structure (t_fdf).
 */
void	key_hook(
	mlx_key_data_t keydata,
	void *param
)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(fdf->mlx);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_V))
		switch_view(fdf);
}

static void	switch_view(
	t_fdf *fdf
)
{
	size_t	x;
	size_t	y;

	if (fdf->map.view == ISOMETRIC)
		fdf->map.view = 30.0;
	else
		fdf->map.view = ISOMETRIC;
	mlx_delete_image(fdf->mlx, fdf->map_img);
	fdf->map_img = mlx_new_image(fdf->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	y = 0;
	while (y < fdf->map.rows)
	{
		x = 0;
		while (x < fdf->map.cols)
		{
			fdf->map.points[y][x].x_prime = ((double)fdf->map.points[y][x].x - (double)fdf->map.points[y][x].y) * cos(fdf->map.view * M_PI / 180);
			fdf->map.points[y][x].y_prime = ((double)fdf->map.points[y][x].x + (double)fdf->map.points[y][x].y) * sin(fdf->map.view * M_PI / 180)
				- (double)fdf->map.points[y][x].z;
			x++;
		}
		y++;
	}
	scale_and_center_map(&fdf->map, WINDOW_WIDTH, WINDOW_HEIGHT);
	render_map(&fdf->map, fdf->map_img);
}
