/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:02:23 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/28 16:31:40 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_line(t_point a, t_point b, mlx_image_t *map_img);

void	render_map(
	t_map *map,
	mlx_image_t *map_img
)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			if (x < map->cols - 1)
				draw_line(map->points[y][x], map->points[y][x + 1], map_img);
			if (y < map->rows - 1)
				draw_line(map->points[y][x], map->points[y + 1][x], map_img);
			x++;
		}
		y++;
	}
}

static void	draw_line(
	t_point a,
	t_point b,
	mlx_image_t *map_img
)
{
	int	params[9];
	int	color_a;
	int	color_b;

	draw_line_init(a, b, params);
	color_a = get_rgba(a.color.r, a.color.g, a.color.b, a.color.a);
	color_b = get_rgba(b.color.r, b.color.g, b.color.b, b.color.a);
	while (1)
	{
		if (params[8] > 0)
			draw_pixel(params[4], params[5], interpolate_color(color_a, color_b,
					(float)params[7] / (float)params[8]), map_img);
		else
			draw_pixel(params[4], params[5], interpolate_color(color_a, color_b,
					0.0f), map_img);
		if (params[4] == (int)b.x_prime && params[5] == (int)b.y_prime)
			break ;
		bresenham_step(params);
	}
}
