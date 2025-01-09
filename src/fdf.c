/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:48:02 by sede-san          #+#    #+#             */
/*   Updated: 2024/12/30 02:44:58 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int main(void)
{
	mlx_t			*mlx;
	// mlx_texture_t	*icon;

	mlx = mlx_init(256, 256, "Fdf by sede-san", true);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	
	return (0);
}
