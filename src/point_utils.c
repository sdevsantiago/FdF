/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:19:53 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/29 18:32:32 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Sets the coordinates and their isometric projections for a point.
 *
 * This function initializes the x, y, and z coordinates of the given t_point
 * structure. It also calculates the isometric projection coordinates (x_prime
 * and y_prime) using the provided x, y, and z values, along with the
 * COS_ISOMETRIC and SIN_ISOMETRIC constants.
 *
 * Isometric projection formula:
 * x' = (x - y) * cos(30°)
 * y' = (x + y) * sin(30°) - z
 *
 * Where:
 * - cos(30°) = √3/2 ≈ 0.866
 * - sin(30°) = 1/2 = 0.5
 *
 * @param point Pointer to the t_point structure to be initialized.
 * @param x     The x-coordinate value.
 * @param y     The y-coordinate value.
 * @param z     The z-coordinate value.
 */
void	set_coords(
	t_point *point,
	size_t x,
	size_t y,
	size_t z
)
{
	point->x = x;
	point->y = y;
	point->z = z;
	point->x_prime = ((double)point->x + (double)point->y) * COS_ISOMETRIC;
	point->y_prime = ((double)point->y - (double)point->x) * SIN_ISOMETRIC
		- (double)point->z;
}

static void	set_colors_rgb(t_point *point, const char *color);
static void	set_colors_gb(t_point *point, const char *color);
static void	set_colors_b(t_point *point, const char *color);

/**
 * @brief Sets the color of a point based on a hexadecimal color string.
 *
 * This function takes a pointer to a `t_point` structure and a color string
 * in hexadecimal format (e.g., "#RRGGBB"). It extracts the red, green, and blue
 * components from the color string and assigns them to the corresponding fields
 * in the `point->color` structure. If the color string is NULL, the point's
 * color is set to white (255, 255, 255). The alpha component is always set to
 * 255.
 *
 * @param point A pointer to the `t_point` structure whose color will be set.
 * @param color A string representing the color in hexadecimal format. If NULL,
 *              the point's color will be set to white.
 */
void	set_color(t_point *point, char *color)
{
	size_t	i;

	if (color)
	{
		i = 2;
		while (i < ft_strlen(color))
		{
			color[i] = ft_toupper(color[i]);
			i++;
		}
		if (ft_strlen(color) >= 8)
			set_colors_rgb(point, color);
		else if (ft_strlen(color) >= 6)
			set_colors_gb(point, color);
		else if (ft_strlen(color) >= 4)
			set_colors_b(point, color);
	}
	else
	{
		point->color.r = 255;
		point->color.g = 255;
		point->color.b = 255;
	}
	point->color.a = 255;
}

/**
 * @brief Sets the RGB color values of a t_point structure from a hexadecimal
 *        color string.
 *
 * This function extracts the red, green, and blue components from the given
 * hexadecimal color string (expected in the format "0xRRGGBB") and assigns them
 * to the corresponding fields in the t_point's color structure.
 *
 * @param point Pointer to the t_point structure whose color will be set.
 * @param color String representing the color in hexadecimal format
 *              (e.g., "0xFFAABB").
 *
 * @note Assumes that the color string is at least 8 characters long and
 *       properly formatted.
 */
static void	set_colors_rgb(
	t_point *point,
	const char *color
)
{
	char	*tmp;

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

/**
 * @brief Sets the green and blue color components of a t_point structure from
 *        a hexadecimal color string.
 *
 * This function extracts the green and blue components from a hexadecimal
 * color string (assumed to be in the format "0xGGBB" or similar) and assign
 * them to the corresponding fields in the t_point structure.
 *
 * @param point Pointer to the t_point structure whose color components will be
 *              set.
 * @param color String representing the hexadecimal color value.
 */
static void	set_colors_gb(t_point *point, const char *color)
{
	char	*tmp;

	tmp = ft_substr(color, 2, 2);
	point->color.g = ft_atoi_base(tmp, HEX_BASE);
	free(tmp);
	tmp = ft_substr(color, 4, 2);
	point->color.b = ft_atoi_base(tmp, HEX_BASE);
	free(tmp);
}

/**
 * @brief Sets the blue component of a point's color from a hexadecimal color
 *        string.
 *
 * This function extracts the blue component from the given hexadecimal color
 * string and assigns it to the 'b' field of the point's color structure.
 *
 * @param point Pointer to the t_point structure whose color will be modified.
 * @param color String representing the color in hexadecimal format (e.g.,
 *              "0xBB").
 *
 * The function assumes that the blue component is located at positions 2 and 3
 * of the color string (after the "0x" prefix).
 */
static void	set_colors_b(t_point *point, const char *color)
{
	char	*tmp;

	tmp = ft_substr(color, 2, 2);
	point->color.b = ft_atoi_base(tmp, HEX_BASE);
	free(tmp);
}
