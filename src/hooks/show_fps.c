/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_fps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:27:12 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/15 16:50:28 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	show_fps(void *param)
{
	t_fdf	*fdf;
	char	*fps;

	fdf = (t_fdf *)param;
	mlx_delete_image(fdf->mlx, fdf->fps_img);
	fps = ft_itoa((int)(1000 / fdf->mlx->delta_time));
	fdf->fps_img = mlx_put_string(fdf->mlx, fps, 10, 10);
	free(fps);
	if (mlx_image_to_window(fdf->mlx, fdf->fps_img, 10, 10) < 0)
		mlx_close_window(fdf->mlx);
}
