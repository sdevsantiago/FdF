/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:01:20 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/28 18:15:07 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Initializes parameters for drawing a line between two points using
 * Bresenham's algorithm.
 *
 * This function calculates and sets up the necessary parameters for line
 * drawing between points 'a' and 'b'. The parameters array is filled as
 * follows:
 * - params[0]: Absolute difference in x coordinates (delta x)
 * - params[1]: Absolute difference in y coordinates (delta y)
 * - params[2]: Step direction for x (+1 or -1)
 * - params[3]: Step direction for y (+1 or -1)
 * - params[4]: Starting x coordinate
 * - params[5]: Starting y coordinate
 * - params[6]: Initial error value (delta x - delta y)
 * - params[7]: Counter or auxiliary variable (initialized to 0)
 * - params[8]: Maximum of delta x and delta y (used for iteration count)
 *
 * @param a      The starting point of the line (t_point struct).
 * @param b      The ending point of the line (t_point struct).
 * @param params An integer array of size at least 9 to store the computed
 * parameters.
 */
void	draw_line_init(t_point a, t_point b, int *params)
{
	params[0] = abs((int)b.x_prime - (int)a.x_prime);
	params[1] = abs((int)b.y_prime - (int)a.y_prime);
	if (a.x_prime < b.x_prime)
		params[2] = 1;
	else
		params[2] = -1;
	if (a.y_prime < b.y_prime)
		params[3] = 1;
	else
		params[3] = -1;
	params[6] = params[0] - params[1];
	params[4] = (int)a.x_prime;
	params[5] = (int)a.y_prime;
	params[7] = 0;
	if (params[0] > params[1])
		params[8] = params[0];
	else
		params[8] = params[1];
}

/**
 * @brief Draws a single pixel on the given image at specified coordinates.
 *
 * This function checks if the (x, y) coordinates are within the bounds of the image.
 * If so, it sets the pixel at (x, y) to the specified color using mlx_put_pixel.
 *
 * @param x       The x-coordinate of the pixel to draw.
 * @param y       The y-coordinate of the pixel to draw.
 * @param color   The color value to set for the pixel.
 * @param map_img Pointer to the mlx_image_t image where the pixel will be
 * drawn.
 */
void	draw_pixel(int x, int y, int color, mlx_image_t *map_img)
{
	if (x >= 0 && x < (int)map_img->width)
	{
		if (y >= 0 && y < (int)map_img->height)
			mlx_put_pixel(map_img, x, y, color);
	}
}

/**
 * @brief Performs a single step of Bresenham's line drawing algorithm.
 *
 * This function updates the parameters required for Bresenham's algorithm
 * to draw a line between two points. The parameters array contains all
 * necessary values for the algorithm, such as differences in coordinates,
 * current positions, and error values.
 *
 * @param params An integer array containing the Bresenham algorithm parameters:
 *        params[0] - delta x (dx)
 *        params[1] - delta y (dy)
 *        params[2] - step x (sx)
 *        params[3] - step y (sy)
 *        params[4] - current x position
 *        params[5] - current y position
 *        params[6] - error value (err)
 *        params[7] - step counter or auxiliary value
 */
void	bresenham_step(int *params)
{
	int	e2;

	e2 = 2 * params[6];
	if (e2 > -params[1])
	{
		params[6] -= params[1];
		params[4] += params[2];
		params[7]++;
	}
	if (e2 < params[0])
	{
		params[6] += params[0];
		params[5] += params[3];
		if (e2 <= -params[1])
			params[7]++;
	}
}

int	interpolate_color(int color1, int color2, float ratio)
{
	int	components[8];

	components[0] = (color1 >> 24) & 0xFF;
	components[1] = (color1 >> 16) & 0xFF;
	components[2] = (color1 >> 8) & 0xFF;
	components[3] = color1 & 0xFF;
	components[4] = (color2 >> 24) & 0xFF;
	components[5] = (color2 >> 16) & 0xFF;
	components[6] = (color2 >> 8) & 0xFF;
	components[7] = color2 & 0xFF;
	return (get_rgba(components[0] + (int)((components[4] - components[0])
			* ratio), components[1] + (int)((components[5]
			- components[1]) * ratio), components[2]
		+ (int)((components[6] - components[2]) * ratio),
		components[3] + (int)((components[7] - components[3]) * ratio)));
}

void	set_point_color(t_point *point, const char *color)
{
	char	*tmp;

	if (color)
	{
		tmp = ft_substr(color, 2, 2);
		point->color.r = ft_atoi_base(tmp, HEX_BASE);
		free(tmp);
		tmp = ft_substr(color, 4, 2);
		point->color.g = ft_atoi_base(tmp, HEX_BASE);
		free(tmp);
		tmp = ft_substr(color, 6, 2);
		point->color.b = ft_atoi_base(tmp, HEX_BASE);
		free(tmp);
	}
	else
	{
		point->color.r = 255;
		point->color.g = 255;
		point->color.b = 255;
	}
	point->color.a = 255;
}
