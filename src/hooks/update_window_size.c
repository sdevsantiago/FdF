/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_window_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 03:34:02 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/11 04:43:27 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	update_window_size(int32_t width, int32_t height, void* param)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)param;
	monitor->width = width;
	monitor->height = height;
}
