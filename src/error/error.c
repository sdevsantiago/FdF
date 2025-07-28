/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 04:39:39 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/27 16:44:40 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error(const char *err_msg, t_fdf *fdf)
{
	if (fdf->map.fd > 0)
		close(fdf->map.fd);
	if (fdf->map.points)
		free_map(fdf->map.points, fdf->map.rows);
	if (fdf->map_img)
		mlx_delete_image(fdf->mlx, fdf->map_img);
	if (fdf->mlx)
		mlx_terminate(fdf->mlx);
	ft_eputstr(RED_TEXT"ERROR: ");
	ft_eputstr((char *)err_msg);
	ft_eputendl(RESET);
	if (errno)
		ft_eputendl(strerror(errno));
	else
		errno = 1;
	exit(errno);
}
