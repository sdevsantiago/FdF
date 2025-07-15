/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_keypress.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 02:08:19 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/14 12:20:19 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @param _keydata Not used in this context.
 * @param param
 */
void	check_keypress(mlx_key_data_t _keydata, void *param)
{
	mlx_t	*mlx;

	(void)_keydata;
	mlx = (mlx_t *)param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		ft_putendl("Up");
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		ft_putendl("Down");
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		ft_putendl("Left");
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		ft_putendl("Right");
}
