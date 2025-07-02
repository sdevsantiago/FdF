/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:48:02 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/02 15:21:38 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	check_keypress(mlx_key_data_t key, void *param)
{
	// If ESC is pressed, kill the window
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_terminate(param);
}

int main(void)
{
	mlx_t			*mlx;

	mlx = mlx_init(256, 256, "Fdf by sede-san", true);
	mlx_key_hook(mlx, &check_keypress, (void *)mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
