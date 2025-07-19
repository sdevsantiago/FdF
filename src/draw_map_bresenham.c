/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_bresenham.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:02:23 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/15 17:22:06 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// static void	draw_line(t_point a, t_point b, mlx_image_t *map_img);

static int	get_rgba(
	int r,
	int g,
	int b,
	int a
)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_map_bresenham(
	t_map *map,
	mlx_image_t *map_img
)
{
	t_point	p;
	size_t	x;
	size_t	y;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			p = map->points[y][x];
			mlx_put_pixel(map_img, (int)p.x_prime, (int)p.y_prime, get_rgba(255, 255, 255, 255)); //! crash
			// if (x < map->cols - 1)
			// 	draw_line(p, map->points[y][x + 1], map_img);
			// if (y < map->rows - 1)
			// 	draw_line(p, map->points[y + 1][x], map_img);
			x++;
		}
		y++;
	}

}

// static void	draw_line(
// 	t_point a,
// 	t_point b,
// 	mlx_image_t *map_img
// )
// {
// 	int dx = abs((int)b.x_prime - (int)a.x_prime);
// 	int dy = -abs((int)b.y_prime - (int)a.y_prime);
// 	int sx = (a.x_prime < b.x_prime) ? 1 : -1;
// 	int sy = (a.y_prime < b.y_prime) ? 1 : -1;
// 	int err = dx + dy;
// 	int e2;

// 	while (1)
// 	{
// 		mlx_put_pixel(map_img, a.x * 10, a.y * 10, get_rgba(255, 255, 255, 255));
// 		if ((int)a.x_prime == (int)b.x_prime && (int)a.y_prime == (int)b.y_prime)
// 			break;
// 		e2 = 2 * err;
// 		if (e2 >= dy)
// 		{
// 			err += dy;
// 			a.x_prime += sx;
// 		}
// 		if (e2 <= dx)
// 		{
// 			err += dx;
// 			a.y_prime += sy;
// 		}
// 	}
// }
