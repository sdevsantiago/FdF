/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 02:08:19 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/27 20:41:56 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(fdf->mlx);
}
