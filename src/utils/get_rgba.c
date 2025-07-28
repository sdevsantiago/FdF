/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgba.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:16:39 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/27 13:18:57 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Combines individual red, green, blue, and alpha components into a
 * single 32-bit RGBA value.
 *
 * This function takes four 8-bit integer values representing the red, green,
 * blue, and alpha channels, and packs them into a single 32-bit integer in the
 * format: 0xRRGGBBAA.
 *
 * @param r The red component (0-255).
 * @param g The green component (0-255).
 * @param b The blue component (0-255).
 * @param a The alpha component (0-255).
 *
 * @return int The combined 32-bit RGBA value.
 */
int	get_rgba(
	int r,
	int g,
	int b,
	int a
)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
